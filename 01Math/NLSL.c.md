# Control
```
{
    "OUT": "NLSL.c",
    "VTYPES": ["R32", "R64", "C64", "C128"],
    "RTYPES": ["R32", "R64", "R32", "R64"],
    "ITYPE": "I32"
}
```
Description:
* OUT: output filepath
* VTYPES: base number types
    - R32: 32 bit real number; i.e. float
    - R64: 64 bit real number; i.e. double
    - C64: 64 bit complex number; i.e. float complex
    - C128: 128 bit complex number; i.e. double complex
* RTYPES: real number types used for aboslute values and tolerances
* ITYPE: default integral number type
# Head
Head contains definitions common to all base number types.
```
/*
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

File description
File: NLSL.c
Description: Nonlinear equation solver implementation

Revision history
Rev.     Date   Author  Description
00.00.00 231104 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/NLSL.h"
#include "SLC/Log.h"
#include "SLC/NumbersCopy.h"
#include "SLC/MiniBLAS.h"
#include "SLC/MiniLA.h"
#include "SLC/errno.h"
#include "SLC/ExIO.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <errno.h>

```
# Generic
Generic definitions of base number specific functions, types, etc.
## Internal Declarations
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_INTERNAL_DECLARATIONS
/**
\brief Declare type of trace functions for Gauss-Newton solvers.
*/
typedef void (*GnSolver_<VTYPE>Trace_f)(SLCGnSolver_<VTYPE>_cpt solver);

/**
\brief Discriminate where the solver is converged or not.
*/
typedef SLCNlsl_State_t
    (*GnSolver_<VTYPE>Converged_f)(SLCGnSolver_<VTYPE>_cpt solver);

/**
\brief Full definition of Gauss-Newton solver struct
*/
struct SLCGnSolver_<VTYPE>
{
    // Configuration parameters
    SLCGnSolver_<VTYPE>Conf_t conf;

    // working matrices
    SLCArray_pt
        x, // X column vector
        deltaX, // == x_new - x; i.e. x_new = x + delta_x.
        y, negy, // Y and -Y column vectors
        jcolbuf, // Jacobian column buffer
        j; // Jacobian
    SLCMat_LmsSolverMatSet_t wkset;

    // operation state and iteration counter
    SLCNlsl_State_t state;
    SLC_<ITYPE>_t iter;

    // Convergence parameters
    SLC_<RTYPE>_t normDx, normY;
    GnSolver_<VTYPE>Converged_f convDisc;

    // trace functions
    GnSolver_<VTYPE>Trace_f
        traceXY, // trace x and y
        traceJ, // trace Jacobian
        traceNormDxY; // trace deltaX and y
};
#pragma endregion <VTYPE>_INTERNAL_DECLARATIONS
```
## Trace Functions and Convergence Discriminators
```
#pragma region TRACE_FUNC_AND_CONV_DISC
static void <VTYPE>TraceXY(SLCGnSolver_<VTYPE>_cpt solver)
{
    fprintf(solver->conf.Base.TraceOut, "x = {");
    SLC_<VTYPE>_PRINTV(
        solver->conf.Base.TraceOut,
        solver->x->Data.<VTYPE>, solver->conf.Base.Cx);
    fprintf(solver->conf.Base.TraceOut, "}\ny = {");
    SLC_<VTYPE>_PRINTV(
        solver->conf.Base.TraceOut,
        solver->y->Data.<VTYPE>, solver->conf.Base.Cy);
    fprintf(solver->conf.Base.TraceOut, "}\n");
}

static void <VTYPE>TraceJ(SLCGnSolver_<VTYPE>_cpt solver)
{
    SLCMat_<VTYPE>Print(solver->conf.Base.TraceOut, "J = ",
        solver->j, "");
}

static void <VTYPE>TraceNormDxY(SLCGnSolver_<VTYPE>_cpt solver)
{
    fprintf(solver->conf.Base.TraceOut,
        "normDx = %e, normY = %e\n", solver->normDx, solver->normY);
}

// a dummy function does nothing
static void <VTYPE>TraceNone(SLCGnSolver_<VTYPE>_cpt solver) {}

static SLCNlsl_State_t
<VTYPE>DiscriminateDx(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->normDx < solver->conf.Base.NormDxMax ?
        SLCNlsl_State_DX_CONVERGED : SLCNlsl_State_RUNNING;
}

static SLCNlsl_State_t
<VTYPE>DiscriminateY(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->normY < solver->conf.Base.NormYMax ?
        SLCNlsl_State_Y_CONVERGED : SLCNlsl_State_RUNNING;
}

static SLCNlsl_State_t
<VTYPE>DiscriminateBoth(SLCGnSolver_<VTYPE>_cpt solver)
{
    return
        (solver->normDx < solver->conf.Base.NormDxMax) &&
        (solver->normY < solver->conf.Base.NormYMax) ?
        SLCNlsl_State_BOTH_CONVERGED : SLCNlsl_State_RUNNING;
}
#pragma endregion TRACE_FUNC_AND_CONV_DISC
```
## Initializer and Momory Management
### Low Level Memory Management
```
#pragma region INITIALIZER
static void <VTYPE>FreeArrays(SLCGnSolver_<VTYPE>_pt solver)
{
    SLC_SAFE_FREE(&solver->x);
    SLC_SAFE_FREE(&solver->deltaX);
    SLC_SAFE_FREE(&solver->y);
    SLC_SAFE_FREE(&solver->negy);
    SLC_SAFE_FREE(&solver->jcolbuf);
    SLC_SAFE_FREE(&solver->j);
    SLCMat_DestroyLmsSolverMatSet(&solver->wkset);
}

static SLC_errno_t <VTYPE>AllocArrays(SLCGnSolver_<VTYPE>_pt solver)
{
    const SLC_I16_t
        cx = solver->conf.Base.Cx,
        cy = solver->conf.Base.Cy;
    const SLC_I16_t usize = sizeof(SLC_<VTYPE>_t);
    const SLC_4I16_t
        xsize = { usize, 1, cx, 1 },
        ysize = { usize, 1, cy, 1 },
        jsize = { usize, cx, cy, 1 };
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        if (!(solver->x = SLCArray_ALLOC(xsize)) ||
            !(solver->deltaX = SLCArray_ALLOC(xsize)) ||
            !(solver->y = SLCArray_ALLOC(ysize)) ||
            !(solver->negy = SLCArray_ALLOC(ysize)) ||
            !(solver->jcolbuf = SLCArray_ALLOC(ysize)) ||
            !(solver->j = SLCArray_ALLOC(jsize)))
        {
            err = ENOMEM;
            break;
        }

        if (EXIT_SUCCESS != 
            (err = SLCMat_InitLmsSolverMatSet(
            &solver->wkset, solver->j, solver->y)))
        {
            break;
        }
    }
    while (0);
    if (err)
    {
        <VTYPE>FreeArrays(solver);
    }
    return err;
}
```
### Memory Management APIs
```
SLCGnSolver_<VTYPE>_pt
SLCGnSolver_<VTYPE>New(SLC_<ITYPE>_t cx, SLC_<ITYPE>_t cy)
{
    const SLC_<ITYPE>_t
        headSize = SLC_ALIGN8(sizeof(SLCGnSolver_<VTYPE>_t)),
        xInitialSize = SLC_ALIGN8(cx * sizeof(SLC_<VTYPE>_t)),
        jacobianSize = SLC_ALIGN8(cx * sizeof(SLCNlsl_R32Gvv_f)),
        allocSize = headSize + xInitialSize + jacobianSize;
    SLC_errno_t err = EXIT_SUCCESS;
    SLCGnSolver_<VTYPE>_pt pobj = NULL;
    SLC_I8_t* p = NULL;
    do
    {
        pobj = (SLCGnSolver_<VTYPE>_pt)(p = (SLC_I8_t*)malloc(allocSize));
        if (!p)
        {
            err = ENOMEM;
            break;
        }
        memset(p, 0, allocSize);
        p += headSize;
        pobj->conf.Base.XInitial = (SLC_<VTYPE>_t*)p;
        p += xInitialSize;
        pobj->conf.Jacobian = (SLCNlsl_<VTYPE>Gvv_f*)p;
        pobj->conf.Base.Cx = cx;
        pobj->conf.Base.Cy = cy;
        pobj->conf.Base.MaxIter = 10;
        pobj->conf.Base.ConvergenceCondition
            = SLCNlsl_ConvergenceCondition_DX;
        pobj->conf.Base.NormDxMax = pobj->conf.Base.NormYMax
            = SLC_<VTYPE>_STDTOL;
        pobj->conf.Base.Objective = NULL;
        pobj->conf.Base.Context = NULL;
        pobj->conf.Base.TraceOut = NULL;

        // set trace functions and convergence discriminator
        pobj->traceXY = pobj->traceJ = pobj->traceNormDxY
            = <VTYPE>TraceNone;
        pobj->convDisc = <VTYPE>DiscriminateDx;

        // clear XInital and Jacobian
        for (SLC_<ITYPE>_t i = 0; i < cx; i++)
        {
            pobj->conf.Base.XInitial[i] = SLC_<VTYPE>_0;
            pobj->conf.Jacobian[i] = NULL;
        }
        pobj->state = SLCNlsl_State_CREATED;
        pobj->iter = 0;
        // Initialize internal working matrices
        err = <VTYPE>AllocArrays(pobj);
    }
    while (0);
    if (err)
    {
        SLC_SAFE_FREE(&pobj);
    }
    return pobj;
}

void SLCGnSolver_<VTYPE>Delete(SLCGnSolver_<VTYPE>_pt* ppsolver)
{
    if (ppsolver && *ppsolver)
    {
        <VTYPE>FreeArrays(*ppsolver);
        SLC_SAFE_FREE(ppsolver);
    }
}

SLCGnSolver_<VTYPE>Conf_pt
SLCGnSolver_<VTYPE>Conf(SLCGnSolver_<VTYPE>_pt solver)
{
    return &solver->conf;
}
```
### Initializer Low Level Utility Functions
```
static void <VTYPE>SetTraceFunctions(SLCGnSolver_<VTYPE>_pt solver)
{
    if (solver->conf.Base.TraceOut)
    {
        solver->traceXY = <VTYPE>TraceXY;
        solver->traceJ = <VTYPE>TraceJ;
        solver->traceNormDxY = <VTYPE>TraceNormDxY;
    }
    else
    {
        solver->traceXY = solver->traceJ = solver->traceNormDxY =
            <VTYPE>TraceNone;
    }
}

static void
<VTYPE>SetConvergenceDiscriminator(SLCGnSolver_<VTYPE>_pt solver)
{
    switch (solver->conf.Base.ConvergenceCondition)
    {
        case SLCNlsl_ConvergenceCondition_DX:
            solver->convDisc = <VTYPE>DiscriminateDx;
            break;
        case SLCNlsl_ConvergenceCondition_Y:
            solver->convDisc = <VTYPE>DiscriminateY;
            break;
        case SLCNlsl_ConvergenceCondition_BOTH:
            solver->convDisc = <VTYPE>DiscriminateBoth;
            break;
        default:
            assert(false);
    }
}
#pragma endregion INITIALIZER
```
### 
## Public Functions
```
#pragma region PUBLIC_FUNCTIONS
SLC_errno_t
SLCGnSolver_<VTYPE>Init(SLCGnSolver_<VTYPE>_pt solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        // check null pointer
        bool isNull = !(solver->conf.Base.Context)
            || !(solver->conf.Base.Objective);
        for (SLC_<ITYPE>_t i = 0; i < solver->conf.Base.Cx; i++)
        {
            isNull |= !(solver->conf.Jacobian[i]);
        }
        if (isNull)
        {
            err = SLC_ENULLPTR;
            break;
        }
        <VTYPE>SetTraceFunctions(solver);
        <VTYPE>SetConvergenceDiscriminator(solver);
        // copy XInitial to x
        SLC_<VTYPE>Copy(solver->x->Data.<VTYPE>, 1,
            solver->conf.Base.XInitial, 1, solver->conf.Base.Cx);
        solver->state = SLCNlsl_State_INITIALIZED;
    }
    while (0);
    return err;
}

static void <VTYPE>CalcJacobian(SLCGnSolver_<VTYPE>_pt solver)
{
    SLC_<ITYPE>_t cx = solver->conf.Base.Cx;
    SLC_<ITYPE>_t cy = solver->conf.Base.Cy;
    SLC_<VTYPE>_t* jelement = solver->j->Data.<VTYPE>;
    for (SLC_<ITYPE>_t column = 0; column < cx; column++, jelement++)
    {
        if (EXIT_SUCCESS != solver->conf.Jacobian[column](
            solver->jcolbuf->Data.<VTYPE>, cy,
            solver->x->Data.<VTYPE>, cx,
            solver->conf.Base.Context))
        {
            solver->state = SLCNlsl_State_ERROR_ABORT;
            break;
        }
        SLC_<VTYPE>Copy(
            jelement, cx, solver->jcolbuf->Data.<VTYPE>, 1, cy);
    }
    solver->traceJ(solver);
}

static void <VTYPE>CalcDeltaX(SLCGnSolver_<VTYPE>_pt solver)
{
    // negate y into negy.
    for (SLC_<ITYPE>_t i = 0; i < solver->conf.Base.Cy; i++)
    {
        solver->negy->Data.<VTYPE>[i] = -solver->y->Data.<VTYPE>[i];
    }
    // solve linear equation -Y = J * deltaX
    SLC_errno_t err = SLCMat_<VTYPE>SolveOd(
        solver->deltaX, solver->j, solver->negy, &solver->wkset);
    if (EXIT_SUCCESS != err)
    {
        solver->state = SLCNlsl_State_ERROR_ABORT;
    }
}

static void <VTYPE>CalcNorm(SLCGnSolver_<VTYPE>_pt solver)
{
    solver->normDx = SLCBLAS_<VTYPE>AbsSum(
        solver->deltaX->Data.<VTYPE>, solver->conf.Base.Cx);
    solver->normY = SLCBLAS_<VTYPE>AbsSum(
        solver->y->Data.<VTYPE>, solver->conf.Base.Cy);
    solver->traceNormDxY(solver);
}

static void <VTYPE>CalcObjective(SLCGnSolver_<VTYPE>_pt solver)
{
    SLC_errno_t err = solver->conf.Base.Objective(
        solver->y->Data.<VTYPE>, solver->conf.Base.Cy,
        solver->x->Data.<VTYPE>, solver->conf.Base.Cx,
        solver->conf.Base.Context);
    if (EXIT_SUCCESS != err)
    {
        solver->state = SLCNlsl_State_ERROR_ABORT;
    }
    solver->traceXY(solver);
}

SLC_errno_t SLCGnSolver_<VTYPE>Execute(SLCGnSolver_<VTYPE>_pt solver)
{
    SLC_errno_t err = EXIT_SUCCESS;
    solver->state = SLCNlsl_State_RUNNING;
    for (; solver->iter < solver->conf.Base.MaxIter &&
        solver->state == SLCNlsl_State_RUNNING; solver->iter++)
    {
        // calculate objective function
        <VTYPE>CalcObjective(solver);
        if (solver->state != SLCNlsl_State_RUNNING) continue;
        // calculate Jacobian
        <VTYPE>CalcJacobian(solver);
        if (solver->state != SLCNlsl_State_RUNNING) continue;
        <VTYPE>CalcDeltaX(solver);
        if (solver->state != SLCNlsl_State_RUNNING) continue;
        solver->state = solver->convDisc(solver);
    }
    if (solver->state == SLCNlsl_State_RUNNING)
    {
        solver->state = SLCNlsl_State_ITER_LIMIT;
    }
    return err;
}
#pragma endregion PUBLIC_FUNCTIONS
```
## Public Functions; Accessors
```
const SLC_<VTYPE>_t* SLCGnSolver_<VTYPE>X(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->x->Data.<VTYPE>;
}

const SLC_<VTYPE>_t* SLCGnSolver_<VTYPE>Y(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->y->Data.<VTYPE>;
}

SLC_<RTYPE>_t SLCGnSolver_<VTYPE>NormDx(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->normDx;
}

SLC_<RTYPE>_t SLCGnSolver_<VTYPE>NormY(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->normY;
}
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
