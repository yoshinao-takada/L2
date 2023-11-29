# Control
```
{
    "OUT": "NLSLUT.c",
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
## File header
Head contains definitions common to all base number types.
```
/*
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

File description
File: NLSLUT.c
Description: Test functions for NLSL.c (Continuous nonlinear equation
    solver)

Revision history
Rev.     Date   Author  Description
00.00.00 231104 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Log.h"
#include "SLC/NLSL.h"
#include "SLC/MiniLA.h"
#include "SLC/MiniBLAS.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <memory.h>
```
## test data
### common test data
```
#pragma region TEST_DATA
static const SLC_I32_t POLY_ORDER = 3;
static const SLC_I32_t POLY_COEFF_COUNT = 4;
static const SLC_I32_t XPOINT_COUNT = 20;
```
### test data for R32
```
#pragma region R32_TEST_DATA
static const SLC_4R32_t R32PolyCoeff = { 0.5f, -1.0f, -0.3f, 0.1f };
static const SLC_R32_t
    R32XBegin0 = -2.0f, R32XBegin1 = -4.5f,
    R32XStep0 = 0.15f, R32XStep1 = 0.33f;
static const SLC_R32_t* R32Mat2x2 = R32PolyCoeff;
static const SLC_2R32_t R32DiagonalOffsets = { 0.2f, -0.3f };
#pragma endregion R32_TEST_DATA
```
### test data for R64
```
#pragma region R64_TEST_DATA
static const SLC_4R64_t R64PolyCoeff = { 0.5, -1.0, -0.3, 0.1 };
static const SLC_R64_t
    R64XBegin0 = -2.0, R64XBegin1 = -4.5,
    R64XStep0 = 0.15, R64XStep1 = 0.33;
static const SLC_R64_t* R64Mat2x2 = R64PolyCoeff;
static const SLC_2R64_t R64DiagonalOffsets = { 0.2, -0.3 };
#pragma endregion R64_TEST_DATA
```
### test data for C64
```
#pragma region C64_TEST_DATA
static const SLC_4C64_t C64PolyCoeff = {
    CMPLXF(0.5f,-0.45f), CMPLXF(-1.0f,0.95f),
    CMPLXF(-0.3f,-0.27f), CMPLXF(0.1f,0.0f) };
static const SLC_C64_t
    C64XBegin0 = CMPLXF(-2.0f,-1.5f), C64XBegin1 = CMPLXF(-2.2f, 1.5f),
    C64XStep0 = CMPLXF(0.15f,0.15f), C64XStep1 = CMPLXF(0.33f,-0.2f);
static const SLC_C64_t* C64Mat2x2 = C64PolyCoeff;
static const SLC_2C64_t C64DiagonalOffsets = 
    { CMPLXF(0.2f, 0.0f), CMPLXF(-0.3f, -1.0f) };
#pragma endregion C64_TEST_DATA
```
### test data for C128
```
#pragma region C128_TEST_DATA
static const SLC_4C128_t C128PolyCoeff = {
    CMPLX(0.5,-0.45), CMPLX(-1.0,0.95),
    CMPLX(-0.3,-0.27), CMPLX(0.1,0.0) };
static const SLC_C128_t
    C128XBegin0 = CMPLX(-2.0,-1.5), C128XBegin1 = CMPLX(-2.2, 1.5),
    C128XStep0 = CMPLX(0.15,0.15), C128XStep1 = CMPLX(0.33,-0.2);
static const SLC_C128_t* C128Mat2x2 = C128PolyCoeff;
static const SLC_2C128_t C128DiagonalOffsets = { CMPLX(0.2, 0.0), CMPLX(-0.3, -1.0) };
#pragma endregion C128_TEST_DATA
#pragma endregion TEST_DATA
```
# Generic
Generic definitions of base number specific functions, types, etc.
## Overly determined linear equation: 3rd order polynomial fitting
```
#pragma region <VTYPE>_functions
#define NUMSIZE sizeof(SLC_<VTYPE>_t)
#pragma region <VTYPE>_Overly_determined_linear_equation
// calculate test polynomial value for independent variable x.
static SLC_<VTYPE>_t <VTYPE>PolyFit_PolyValue(SLC_<VTYPE>_t x)
{
    SLC_<VTYPE>_t value = SLC_<VTYPE>_0;
    SLC_<ITYPE>_t order_index = POLY_COEFF_COUNT;
    for (SLC_<ITYPE>_t i = 0; i < POLY_COEFF_COUNT; i++)
    {
        --order_index;
        value = value * x + <VTYPE>PolyCoeff[order_index];
    }
    return value;
}

static void <VTYPE>PolyFit_CreateTestRHS(SLCArray_pt rhs)
{
    SLC_<VTYPE>_t x = <VTYPE>XBegin0, xstep = <VTYPE>XStep0;
    SLC_<ITYPE>_t count2 = XPOINT_COUNT / 2;
    SLC_<ITYPE>_t i = 0;
    for (; i < count2; i++, x += xstep)
    {
        rhs->Data.<VTYPE>[i] = <VTYPE>PolyFit_PolyValue(x);
    }
    x = <VTYPE>XBegin1, xstep = <VTYPE>XStep1;
    for (; i < XPOINT_COUNT; i++, x += xstep) 
    {
        rhs->Data.<VTYPE>[i] = <VTYPE>PolyFit_PolyValue(x);
    }
}

static void <VTYPE>PolyFit_CreateXPowers(SLC_<VTYPE>_t* XpowN, SLC_<VTYPE>_t x)
{
    XpowN[0] = SLC_<VTYPE>_1;
    XpowN[1] = XpowN[0] * x;
    XpowN[2] = XpowN[1] * x;
    XpowN[3] = XpowN[2] * x;
}

static void <VTYPE>PolyFit_CreateTestLHS(SLCArray_pt lhs)
{
    SLC_<VTYPE>_t x = <VTYPE>XBegin0, xstep = <VTYPE>XStep0;
    SLC_<ITYPE>_t count2 = XPOINT_COUNT / 2;
    SLC_<VTYPE>_t* lhs_elements = lhs->Data.<VTYPE>;
    SLC_<ITYPE>_t i = 0;
    for (; i < count2; i++, x += xstep, lhs_elements += POLY_COEFF_COUNT)
    {
        <VTYPE>PolyFit_CreateXPowers(lhs_elements, x);
    }
    x = <VTYPE>XBegin1, xstep = <VTYPE>XStep1;
    for (; i < XPOINT_COUNT; i++, x += xstep, lhs_elements += POLY_COEFF_COUNT)
    {
        <VTYPE>PolyFit_CreateXPowers(lhs_elements, x);
    }
}

static SLC_errno_t <VTYPE>SolveOdUT()
{
    const SLC_I16_t left_size[] = 
        { NUMSIZE, POLY_COEFF_COUNT, XPOINT_COUNT, 1 };
    const SLC_I16_t right_size[] = 
        { NUMSIZE, 1, XPOINT_COUNT, 1 };
    const SLC_I16_t x_size[] = 
        { NUMSIZE, 1, (SLC_I16_t)POLY_COEFF_COUNT, 1 };
    SLCArray_pt left = NULL, right = NULL, xretrieved = NULL;
    SLCMat_LmsSolverMatSet_t wkset = 
        { NULL, NULL, NULL, NULL, NULL, NULL };
    SLC_errno_t err = EXIT_SUCCESS;
    do {
        left = SLCArray_ALLOC(left_size);
        right = SLCArray_ALLOC(right_size);
        xretrieved = SLCArray_ALLOC(x_size);
        if (!left || !right || !xretrieved)
        {
            err = ENOMEM;
            SLCLog_ERR(err, 
                "Insufficient memory @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        err = SLCMat_InitLmsSolverMatSet(&wkset, left, right);
        if (err)
        {
            SLCLog_ERR(err,
                "Fail in SLCMat_InitSolveOdWorkMatSet() @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        <VTYPE>PolyFit_CreateTestRHS(right);
        <VTYPE>PolyFit_CreateTestLHS(left);
        err = SLCMat_<VTYPE>SolveOd(xretrieved, left, right, &wkset);
        if (err)
        {
            SLCLog_ERR(err,
                "Fail in SLCMat_<VTYPE>SolveOd() @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        for (SLC_<ITYPE>_t i = 0; i < POLY_COEFF_COUNT; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL
                (<VTYPE>PolyCoeff[i], xretrieved->Data.<VTYPE>[i],
                SLC_<VTYPE>_BIGTOL))
            {
                err = SLC_EVALMISMATCH;
                SLCLog_ERR(err, 
                    "Value mismatch, <VTYPE>PolyCoeff[%d]=%f, xretrieved[%d]=%f @ %s,%s,%d\n",
                    i, <VTYPE>PolyCoeff[i], i, xretrieved->Data.<VTYPE>[i], __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_SAFE_FREE(&left);
    SLC_SAFE_FREE(&right);
    SLC_SAFE_FREE(&xretrieved);
    SLCMat_DestroyLmsSolverMatSet(&wkset);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_Overly_determined_linear_equation
```
## Nonlinear equation: A 2x2 matrix to the power of 2 and 3
Details of the problem are described in [NLSL Sample 0](NLSLSample0.md).
### Objective and Jacobian: context and its memory management
```
#pragma region <VTYPE>_Objective_and_Jacobian
typedef struct <VTYPE>MatPower2And3 {
    SLCArray_pt M1, dM1dx0, dM1dx1, dM1dx2, dM1dx3;
    SLCArray_pt work[8];
    SLC_<VTYPE>_t C0, C1;
    SLC_<VTYPE>_t YOffset[8];
} <VTYPE>MatPower2And3_t, *<VTYPE>MatPower2And3_pt;

// memory allocation
static void 
<VTYPE>MatPower2And3_Init(<VTYPE>MatPower2And3_pt context)
{
    SLC_4I16_t matsize = { NUMSIZE, 2, 2, 1 };
    SLC_<VTYPE>_t _0 = SLC_<VTYPE>_0;
    context->M1 = SLCArray_ALLOC(matsize);
    context->dM1dx0 = SLCArray_ALLOC(matsize);
    context->dM1dx1 = SLCArray_ALLOC(matsize);
    context->dM1dx2 = SLCArray_ALLOC(matsize);
    context->dM1dx3 = SLCArray_ALLOC(matsize);
    // zero clear all dM1dxN.
    SLC_<VTYPE>Copy(context->dM1dx0->Data.<VTYPE>, 1, &_0, 0, 4);
    SLC_<VTYPE>Copy(context->dM1dx1->Data.<VTYPE>, 1, &_0, 0, 4);
    SLC_<VTYPE>Copy(context->dM1dx2->Data.<VTYPE>, 1, &_0, 0, 4);
    SLC_<VTYPE>Copy(context->dM1dx3->Data.<VTYPE>, 1, &_0, 0, 4);
    // set 1 elements in dM1dxN.
    context->dM1dx0->Data.<VTYPE>[0] = 
    context->dM1dx1->Data.<VTYPE>[1] = 
    context->dM1dx2->Data.<VTYPE>[2] = 
    context->dM1dx3->Data.<VTYPE>[3] = SLC_<VTYPE>_1;
    for (SLC_<ITYPE>_t i = 0; i < SLC_ARRAY_SIZE(context->work); i++)
    {
        context->work[i] = SLCArray_ALLOC(matsize);
    }
}

static void <VTYPE>MatPower2And3_Destroy(<VTYPE>MatPower2And3_pt context)
{
    SLC_SAFE_FREE(&context->M1);
    SLC_SAFE_FREE(&context->dM1dx0);
    SLC_SAFE_FREE(&context->dM1dx1);
    SLC_SAFE_FREE(&context->dM1dx2);
    SLC_SAFE_FREE(&context->dM1dx3);
    for (SLC_<ITYPE>_t i = 0; i < SLC_ARRAY_SIZE(context->work); i++)
    {
        SLC_SAFE_FREE(&context->work[i]);
    }
}
```
### Objective and Jacobian: Test parameter initializer
```
static void 
<VTYPE>MatPower2And3_InitContext(<VTYPE>MatPower2And3_pt context)
{
    <VTYPE>MatPower2And3_Init(context);
    const SLC_<VTYPE>_t MINUS1 = SLC_<VTYPE>_M1;
    context->C0 = <VTYPE>DiagonalOffsets[0];
    context->C1 = <VTYPE>DiagonalOffsets[1];
    context->M1->Data.<VTYPE>[0] = <VTYPE>Mat2x2[0] + context->C0;
    context->M1->Data.<VTYPE>[1] = <VTYPE>Mat2x2[1];
    context->M1->Data.<VTYPE>[2] = <VTYPE>Mat2x2[2];
    context->M1->Data.<VTYPE>[3] = <VTYPE>Mat2x2[3] + context->C1;
    SLCArray_t M2 = { context->M1->Dimensions, context->YOffset };
    SLCArray_t M3 = { context->M1->Dimensions, context->YOffset + 4 };
    SLCMat_<VTYPE>Multiply(&M2, context->M1, context->M1, context->work[0]);
    SLCMat_<VTYPE>Multiply(&M3, &M2, context->M1, context->work[0]);
    SLCBLAS_<VTYPE>ScaleAss(context->YOffset, &MINUS1, 8);
}
```
### Objective and Jacobian: Objective function
```
static SLC_errno_t <VTYPE>Objective00(
    SLC_<VTYPE>_t* y, SLC_I32_t cy,
    const SLC_<VTYPE>_t* x, SLC_I32_t cx,
    void* context
) {
    SLC_errno_t err = EXIT_SUCCESS;
    <VTYPE>MatPower2And3_pt ctx = (<VTYPE>MatPower2And3_pt)context;
    ctx->M1->Data.<VTYPE>[0] = x[0] + ctx->C0;
    ctx->M1->Data.<VTYPE>[1] = x[1];
    ctx->M1->Data.<VTYPE>[2] = x[2];
    ctx->M1->Data.<VTYPE>[3] = x[3] + ctx->C1;
    SLCArray_t M2 = { ctx->M1->Dimensions, {(void*)y} };
    SLCArray_t M3 = { ctx->M1->Dimensions, {(void*)(y + 4)} };
    do {
        SLCMat_<VTYPE>Multiply(&M2, ctx->M1, ctx->M1, ctx->work[0]);
        SLCMat_<VTYPE>Multiply(&M3, &M2, ctx->M1, ctx->work[0]);
        SLCBLAS_<VTYPE>AddAss(y, ctx->YOffset, cy);
    } while (0);
    return err;
}
```
### Objective and Jacobian: Jacobian
```
// Jacobian column common
static SLC_errno_t <VTYPE>Jcommon(
    SLC_<VTYPE>_t* y, SLC_I32_t cy,
    const SLC_<VTYPE>_t* x, SLC_I32_t cx,
    void* context,
    SLCArray_cpt dM1dx
) {
    <VTYPE>MatPower2And3_pt ctx = (<VTYPE>MatPower2And3_pt)context;
    // work[0] = M1 * dM1dx, work[1] = dM1dx * M1,
    // *y = M1 * dM1dx + dM1dx * M1
    SLCMat_<VTYPE>Multiply(ctx->work[0], ctx->M1, dM1dx, ctx->work[7]);
    SLCMat_<VTYPE>Multiply(ctx->work[1], dM1dx, ctx->M1, ctx->work[7]);
    SLCBLAS_<VTYPE>Add(y, 
        ctx->work[0]->Data.<VTYPE>, ctx->work[1]->Data.<VTYPE>, 4);
    // work[2] = M1 * M1 * dM1dx, 
    // work[3] = M1 * dM1dx * M1, 
    // work[4] = dM1dx * M1 * M1
    // *(y + 4) = M1 * M1 * dM1dx + M1 * dM1dx * M1 + dM1dx * M1 * M1
    SLCMat_<VTYPE>Multiply(ctx->work[2], ctx->M1, ctx->work[0], ctx->work[7]);
    SLCMat_<VTYPE>Multiply(ctx->work[3], ctx->M1, ctx->work[1], ctx->work[7]);
    SLCMat_<VTYPE>Multiply(ctx->work[4], ctx->work[1], ctx->M1, ctx->work[7]);
    SLCBLAS_<VTYPE>Add(y + 4, ctx->work[2]->Data.<VTYPE>, ctx->work[3]->Data.<VTYPE>, 4);
    SLCBLAS_<VTYPE>AddAss(y + 4, ctx->work[4]->Data.<VTYPE>, 4);
    return EXIT_SUCCESS;
}
// Jacobian column 0
static SLC_errno_t <VTYPE>J0(
    SLC_<VTYPE>_t* y, SLC_I32_t cy,
    const SLC_<VTYPE>_t* x, SLC_I32_t cx,
    void* context
) {
    SLC_errno_t err = EXIT_SUCCESS;
    <VTYPE>MatPower2And3_pt ctx = (<VTYPE>MatPower2And3_pt)context;
    SLCArray_cpt dM1dx = ctx->dM1dx0;
    return <VTYPE>Jcommon(y, cy, x, cx, context, dM1dx);
}

// Jacobian column 1
static SLC_errno_t <VTYPE>J1(
    SLC_<VTYPE>_t* y, SLC_I32_t cy,
    const SLC_<VTYPE>_t* x, SLC_I32_t cx,
    void* context
) {
    SLC_errno_t err = EXIT_SUCCESS;
    <VTYPE>MatPower2And3_pt ctx = (<VTYPE>MatPower2And3_pt)context;
    SLCArray_cpt dM1dx = ctx->dM1dx1;
    return <VTYPE>Jcommon(y, cy, x, cx, context, dM1dx);
}
// Jacobian column 2
static SLC_errno_t <VTYPE>J2(
    SLC_<VTYPE>_t* y, SLC_I32_t cy,
    const SLC_<VTYPE>_t* x, SLC_I32_t cx,
    void* context
) {
    SLC_errno_t err = EXIT_SUCCESS;
    <VTYPE>MatPower2And3_pt ctx = (<VTYPE>MatPower2And3_pt)context;
    SLCArray_cpt dM1dx = ctx->dM1dx2;
    return <VTYPE>Jcommon(y, cy, x, cx, context, dM1dx);
}
// Jacobian column 3
static SLC_errno_t <VTYPE>J3(
    SLC_<VTYPE>_t* y, SLC_I32_t cy,
    const SLC_<VTYPE>_t* x, SLC_I32_t cx,
    void* context
) {
    SLC_errno_t err = EXIT_SUCCESS;
    <VTYPE>MatPower2And3_pt ctx = (<VTYPE>MatPower2And3_pt)context;
    SLCArray_cpt dM1dx = ctx->dM1dx3;
    return <VTYPE>Jcommon(y, cy, x, cx, context, dM1dx);
}
#pragma endregion <VTYPE>_Objective_and_Jacobian
```
### Execute Testing Gauss-Newton Solver
```
SLC_errno_t <VTYPE>NLSLGNMat2x2Pow2And3UT()
{
    const SLC_<VTYPE>_t _0 = SLC_<VTYPE>_0, _1 = SLC_<VTYPE>_1;
    SLC_errno_t err = EXIT_SUCCESS;
    <VTYPE>MatPower2And3_t context;
    const SLC_<ITYPE>_t cx = 4, cy = 8;
    const SLC_<VTYPE>_t xIni[] = { _1, -_1, _0, _0 };
    SLCGnSolver_<VTYPE>_pt solver = NULL;
    const SLC_<VTYPE>_t* xresult = NULL;
    do {
        solver = SLCGnSolver_<VTYPE>New(cx, cy);
        SLCGnSolver_<VTYPE>Conf_pt conf = SLCGnSolver_<VTYPE>Conf(solver);
        conf->Jacobian[0] = <VTYPE>J0;
        conf->Jacobian[1] = <VTYPE>J1;
        conf->Jacobian[2] = <VTYPE>J2;
        conf->Jacobian[3] = <VTYPE>J3;
        SLCNlsl_<VTYPE>Conf_pt confbase = &conf->Base;
        confbase->TraceOut = NULL;
        confbase->MaxIter = 20;
        memcpy(confbase->XInitial, xIni, sizeof(xIni));
        <VTYPE>MatPower2And3_InitContext(&context);
        confbase->NormDxMax = SLC_<VTYPE>_STDTOL;
        confbase->NormYMax = SLC_<VTYPE>_STDTOL;
        confbase->Objective = <VTYPE>Objective00;
        confbase->Context = &context;
        if (EXIT_SUCCESS != (err = SLCGnSolver_<VTYPE>Init(solver)))
        {
            SLCLog_ERR(err, 
                "Fail in SLCGnSolver_<VTYPE>Init() @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        if (EXIT_SUCCESS != (err = SLCGnSolver_<VTYPE>Execute(solver)))
        {
            SLCLog_ERR(err,
                "Fail in SLCGnSolver_<VTYPE>Execute() @ %s,%s,%d\n", 
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        // check x tolerances
        xresult = SLCGnSolver_<VTYPE>X(solver);
        for (SLC_<ITYPE>_t i = 0; i < cx; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(<VTYPE>Mat2x2[i], xresult[i], SLC_<VTYPE>_STDTOL))
            {
                err = SLC_EVALMISMATCH;
                SLCLog_<VTYPE>_ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>Mat2x2", "xresult", i, <VTYPE>Mat2x2,
                    xresult, __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
    } while (0);
    SLCGnSolver_<VTYPE>Delete(&solver);
    <VTYPE>MatPower2And3_Destroy(&context);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## <VTYPE> function test harness
```
SLC_errno_t <VTYPE>NLSLUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>SolveOdUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>NLSLGNMat2x2Pow2And3UT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#undef NUMSIZE
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
SLC_errno_t NLSLUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        SLCTest_RUN_ERROR_BREAK(&err, R32NLSLUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, R64NLSLUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, C64NLSLUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, C128NLSLUT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
