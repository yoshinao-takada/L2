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
typedef bool (*GnSolver_<VTYPE>Converged_f)(SLCGnSlver_<VTYPE>_cpt solver);

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

    // operation state
    SLCNlsl_State_t state;

    // iteration counter
    SLC_<ITYPE>_t iter;

    // Convergence parameters
    // L1 norm of deltaX and y
    SLC_<RTYPE>_t normDx, normY;

    // convergence discriminator
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
    fprintf(solver->conf.base.TraceOut, "x = {");
    SLC_<VTYPE>_PRINTV(
        solver->conf.base.TraceOut,
        solver->x->data.<VTYPE>, solver->conf.base.cx);
    fprintf(solver->conf.base.TraceOut, "}\ny = {");
    SLC_<VTYPE>_PRINTV(
        solver->conf.base.TraceOut,
        solver->y->data.<VTYPE>, solver->conf.base.cy);
    fprintf(solver->conf.base.TraceOut, "}\n");
}

static void <VTYPE>TraceJ(SLCGnSolver_<VTYPE>_cpt solver)
{
    SLCMat_<VTYPE>Print(solver->conf.base.TraceOut, "J = ",
        solver->j, "");
}

static void <VTYPE>TraceNormDxY(SLCGnSolver_<VTYPE>_cpt solver)
{
    fprintf(solver->conf.base.TraceOut,
        "normDx = %e, normY = %e\n", solver->normDx, solver->normY);
}

// a dummy function does nothing
static void <VTYPE>TraceNone(SLCGnSolver_<VTYPE>_cpt solver) {}

static bool <VTYPE>DiscriminateDx(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->normDx < solver->conf.base.NormDxMax;
}

static bool <VTYPE>DiscriminateY(SLCGnSolver_<VTYPE>_cpt solver)
{
    return solver->normY < solver->conf.base.NormYMax;
}

static bool <VTYPE>DiscriminateBoth(SLCGnSolver_<VTYPE>_cpt solver)
{
    return
        (solver->normDx < solver->conf.base.NormDxMax) &&
        (solver->normY < solver->conf.base.NormYMax);
}
#pragma endregion TRACE_FUNC_AND_CONV_DISC
```
## Initializer and Momory Management
```
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
        cx = solver->conf.base.Cx,
        cy = solver->conf.base.Cy;
    const SLC_I16_t usize = sizeof(SLC_<VTYPE>_t);
    const SLC_4I16_t
        xsize = { usize, 1, cx, 1 },
        ysize = { usize, 1, cy, 1 },
        jsize = { usize, cx, cy, 1 };
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        if (!(solver->x = SLCMat_ALLOC(xsize)) ||
            !(solver->deltaX = SLCMat_ALLOC(xsize)) ||
            !(solver->y = SLCMat_ALLOC(ysize)) ||
            !(solver->negy = SLCMat_ALLOC(ysize)) ||
            !(solver->jcolbuf = SLCMat_ALLOC(ysize)) ||
            !(solvre->j = SLCMat_ALLOC(jsize)))
        {
            err = ENOMEM;
            break;
        }

        if (EXIT_SUCCESS != 
            err = SLCMat_SLCMat_InitLmsSolverMatSet(
            &solver->wkset, solver->j, solver->y))
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
        pobj->conf.base.XInitial = (SLC_<VTYPE>_t*)p;
        p += xInitialSize;
        pobj->conf.Jacobian = (SLCNlsl_<VTYPE>Gvv_f*)p;
        pobj->conf.base.Cx = cx;
        pobj->conf.base.Cy = cy;
        pobj->conf.base.MaxIter = 10;
        pobj->conf.base.ConvergenceConditions
            = SLCNlsl_ConvergencCondition_DX;
        pobj->conf.base.NormDxMax = pobj->conf.base.NormYMax
            = SLC_<VTYPE>_STDTOL;
        pobj->conf.base.Objective = NULL;
        pobj->conf.base.Context = NULL;
        pobj->conf.base.TraceOut = NULL;

        // set trace functions and convergence discriminator
        pobj->traceXY = pobj->traceJ = pobj->traceNormDxY
            = <VTYPE>TraceNone;
        pobj->convDisc = <VTYPE>DiscriminateDx;

        // clear XInital and Jacobian
        for (SLC_<ITYPE>_t i = 0; i < cx; i++)
        {
            pobj->conf.base.XInitial[i] = SLC_<VTYPE>_0;
            pobj->conf.Jacobian[i] = NULL;
        }

        pobj->state = SLCNlsl_State_CREATED;
        pobj->iter = 0;

        err = <VTYPE>AllocArrays(pobj);
    }
    while (0);
    if (err)
    {
        SLC_SAFE_FREE(&pobj);
    }
    return pobj;
}
#pragmaa region INITIALIZER
#pragmaa endregion INITIALIZER
```
## Public Functions
```
#pragma region PUBLIC_FUNCTIONS
#pragma endregion PUBLIC_FUNCTIONS
```
## Public Functions; Accessors
```
const SLC_<VTYPE>_t* SLCGnSolver_<VTYPE>X(SLCGnSolver_<TYPE>_cpt solver)
{
    return solver->x.Data.<VTYPE>;
}

const SLC_<VTYPE>_t* SLCGnSolver_<VTYPE>Y(SLCGnSolver_<TYPE>_cpt solver)
{
    return solver->y.Data.<VTYPE>;
}

SLC_<VTYPE>_t SLCGnSolver_<VTYPE>NormDx(SLCGnSolver_<TYPE>_cpt solver)
{
    return solver->normDx;
}

SLC_<VTYPE>_t SLCGnSolver_<VTYPE>NormY(SLCGnSolver_<VTYPE>_cpt solver)
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
