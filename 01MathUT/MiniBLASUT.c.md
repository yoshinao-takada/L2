# Control
```
{
    "OUT": "MiniBLASUT.c",
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
File: Template.md
Description: A template file for 'slcpp.js' preprocessor input.

Revision history
Rev.     Date   Author  Description
00.00.00 231104 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Log.h"
#include "SLC/NumbersCopy.h"
#include "SLC/MiniBLAS.h"
#include <stdlib.h>
#include <stdio.h>
```
## R32 test data
```
#pragma region R32_TEST_DATA
static const SLC_R32_t
    R32_SRC0[] = { -1.8f, -1.0f, 0.0f, 1.2f, 1.6f },
    R32_SRC1[] = { 16.0f, 12.0f, 0.0f, -10.0f, -18.0f },
    R32_SCALE0 = 1.5f, R32_SCALE1 = -2.0f;

static const SLC_R32_t
// src0 + src1
    R32_SRC0_PLUS_SRC1[] = { 14.2f, 11.0f, 0.0f, -8.8f, -16.4f },
// src0 + scale1 * src1
    R32_SRC0_PLUS_SCALE1_SRC1[] = { -33.8f, -25.0f, 0.0f, 21.2f, 37.6f },
// scale0 * src0 + scale1 * src1
    R32_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = { -34.7f, -25.5f, 0.0f, 21.8f, 38.4f },
// { src0[i]*src1[i] (i = 0..4) }
    R32_SRC0_SRC1_EBE[] = { -28.8f, -12.0f, 0.0f, -12.0f, -28.8f },
// scale0 * src0
    R32_SCALE0_SRC0[] = { -2.7f, -1.5f, 0.0f, 1.8f, 2.4f },
// conj(src0)
    R32_CONJ_SRC0[] = { -1.8f, -1.0f, 0.0f, 1.2f, 1.6f },
// sum(src0), abssum(src0), productsum(src0, src1), innerproduct(src0, src1)
    R32_SUM_SRC0 = 0.0f, R32_ABSSUM_SRC0 = 5.6f, R32_PRODSUM_SRC0_SRC1 = -81.6f,
    R32_INNER_PRODUCT_SRC0_SRC1 = -81.6f;
static const SLC_I32_t R32_ARRAY_SIZE = SLC_ARRAY_SIZE(R32_SRC0);
#pragma endregion R32_TEST_DATA
```
## R64 test data
```
#pragma region R32_TEST_DATA
static const SLC_R64_t
    R64_SRC0[] = { -1.8, -1.0, 0.0, 1.2, 1.6 },
    R64_SRC1[] = { 16.0, 12.0, 0.0, -10.0, -18.0 },
    R64_SCALE0 = 1.5, R64_SCALE1 = -2.0;

static const SLC_R64_t
// src0 + src1
    R64_SRC0_PLUS_SRC1[] = { 14.2, 11.0, 0.0, -8.8, -16.4 },
// src0 + scale1 * src1
    R64_SRC0_PLUS_SCALE1_SRC1[] = { -33.8, -25.0, 0.0, 21.2, 37.6 },
// scale0 * src0 + scale1 * src1
    R64_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = { -34.7, -25.5, 0.0, 21.8, 38.4 },
// { src0[i]*src1[i] (i = 0..4) }
    R64_SRC0_SRC1_EBE[] = { -28.8, -12.0, 0.0, -12.0, -28.8 },
// scale0 * src0
    R64_SCALE0_SRC0[] = { -2.7, -1.5, 0.0, 1.8, 2.4 },
// conj(src0)
    R64_CONJ_SRC0[] = { -1.8, -1.0, 0.0, 1.2, 1.6 },
// sum(src0), abssum(src0), productsum(src0, src1), innerproduct(src0, src1)
    R64_SUM_SRC0 = 0.0, R64_ABSSUM_SRC0 = 5.6, R64_PRODSUM_SRC0_SRC1 = -81.6,
    R64_INNER_PRODUCT_SRC0_SRC1 = -81.6;
static const SLC_I32_t R64_ARRAY_SIZE = SLC_ARRAY_SIZE(R64_SRC0);
#pragma endregion R64_TEST_DATA
```
## C64 test data
```
#pragma region C64_TEST_DATA
static  const SLC_C64_t
    C64_SRC0[] = { CMPLXF(-1.8f,-1.0f), CMPLXF(0.0f,1.2f), CMPLXF(1.6f,-1.8f) },
    C64_SRC1[] = { CMPLXF(16.0f,12.0f), CMPLXF(0.0f,-10.0f), CMPLXF(-18.0f,16.0f) },
    C64_SCALE0 = CMPLXF(1.5f,-2.0f), C64_SCALE1 = CMPLXF(-2.0f,1.5f);

static  const SLC_C64_t
// src0 + src1
    C64_SRC0_PLUS_SRC1[] = { CMPLXF(14.2f,11.0f), CMPLXF(0.0f,-8.8f), CMPLXF(-16.4f,14.2f) },
// src0 + scale1 * src1
    C64_SRC0_PLUS_SCALE1_SRC1[] = { CMPLXF(-51.8f,-1.0f), CMPLXF(15.0f,21.2f), CMPLXF(13.6f,-60.8f) },
// scale0 * src0 + scale1 * src1
    C64_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = { CMPLXF(-54.7f,2.1f), CMPLXF(17.4f,21.8f), CMPLXF(10.8f,-64.9f) },
// { src0[i]*src1[i] (i = 0..4) }
    C64_SRC0_SRC1_EBE[] = { CMPLXF(-16.8f,-37.6f), CMPLXF(12.0f,0.0f), CMPLXF(0.0f,58.0f) },
// scale0 * src0
    C64_SCALE0_SRC0[] = { CMPLXF(-4.7f,2.1f), CMPLXF(2.4f,1.8f), CMPLXF(-1.2f,-5.9f) },
// conj(src0)
    C64_CONJ_SRC0[] = { CMPLXF(-1.8f,1.0f), CMPLXF(0.0f,-1.2f), CMPLXF(1.6f,1.8f) },
// sum(src0), productsum(src0, src1), innerproduct(src0, src1)
    C64_SUM_SRC0 = CMPLXF(-0.2f, -1.6f), C64_PRODSUM_SRC0_SRC1 = CMPLXF(-4.8f, 20.4f),
    C64_INNER_PRODUCT_SRC0_SRC1 = CMPLXF(-110.4f, 12.4f);
// abssum(src0)
    SLC_R32_t C64_ABSSUM_SRC0 = 5.6674f;
static const SLC_I32_t C64_ARRAY_SIZE = SLC_ARRAY_SIZE(C64_SRC0);
#pragma endregion C64_TEST_DATA
```
## C128 test data
```
#pragma region C128_TEST_DATA
static  const SLC_C128_t
    C128_SRC0[] = { CMPLX(-1.8,-1.0), CMPLX(0.0,1.2), CMPLX(1.6,-1.8) },
    C128_SRC1[] = { CMPLX(16.0,12.0), CMPLX(0.0,-10.0), CMPLX(-18.0,16.0) },
    C128_SCALE0 = CMPLX(1.5,-2.0), C128_SCALE1 = CMPLX(-2.0,1.5);

static  const SLC_C128_t
// src0 + src1
    C128_SRC0_PLUS_SRC1[] = { CMPLX(14.2,11.0), CMPLX(0.0,-8.8), CMPLX(-16.4,14.2) },
// src0 + scale1 * src1
    C128_SRC0_PLUS_SCALE1_SRC1[] = { CMPLX(-51.8,-1.0), CMPLX(15.0,21.2), CMPLX(13.6,-60.8) },
// scale0 * src0 + scale1 * src1
    C128_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = { CMPLX(-54.7,2.1), CMPLX(17.4,21.8), CMPLX(10.8,-64.9) },
// { src0[i]*src1[i] (i = 0..4) }
    C128_SRC0_SRC1_EBE[] = { CMPLX(-16.8,-37.6), CMPLX(12.0,0.0), CMPLX(0.0,58.0) },
// scale0 * src0
    C128_SCALE0_SRC0[] = { CMPLX(-4.7,2.1), CMPLX(2.4,1.8), CMPLX(-1.2,-5.9) },
// conj(src0)
    C128_CONJ_SRC0[] = { CMPLX(-1.8,1.0), CMPLX(0.0,-1.2), CMPLX(1.6,1.8) },
// sum(src0), abssum(src0), productsum(src0, src1), innerproduct(src0, src1)
    C128_SUM_SRC0 = CMPLX(-0.2, -1.6), C128_PRODSUM_SRC0_SRC1 = CMPLX(-4.8, 20.4),
    C128_INNER_PRODUCT_SRC0_SRC1 = CMPLX(-110.4, 12.4);
// abssum(src0)
    SLC_R64_t C128_ABSSUM_SRC0 = 5.66744494396;
static const SLC_I32_t C128_ARRAY_SIZE = SLC_ARRAY_SIZE(C128_SRC0);
#pragma endregion C128_TEST_DATA
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_functions
```
## AddAss, ScaleAss, ScaleAddAss, MultiplyEbeAss
```
static SLC_errno_t <VTYPE>AddAssUT() 
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLC_<VTYPE>Copy(dst, 1, <VTYPE>_SRC0, 1, <VTYPE>_ARRAY_SIZE);
        SLCBLAS_<VTYPE>AddAss(dst, <VTYPE>_SRC1, <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i], <VTYPE>_SRC0_PLUS_SRC1[i],
                SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SRC0_PLUS_SRC1", "dst", i,
                    <VTYPE>_SRC0_PLUS_SRC1, dst, __FILE__, __FUNCTION__,
                    __LINE__);
                break;
            }
        }
    } while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}

static SLC_errno_t <VTYPE>ScaleAssUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLC_<VTYPE>Copy(dst, 1, <VTYPE>_SRC0, 1, <VTYPE>_ARRAY_SIZE);
        SLCBLAS_<VTYPE>ScaleAss(dst, &<VTYPE>_SCALE0, <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i], <VTYPE>_SCALE0_SRC0[i],
                SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SCALE0_SRC0", "dst", i,
                    <VTYPE>_SCALE0_SRC0, dst, __FILE__, __FUNCTION__,
                    __LINE__);
                break;
            }
        }
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}

static SLC_errno_t <VTYPE>ScaleAddAssUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLC_<VTYPE>Copy(dst, 1, <VTYPE>_SRC0, 1, <VTYPE>_ARRAY_SIZE);
        SLCBLAS_<VTYPE>ScaleAddAss(dst, <VTYPE>_SRC1, &<VTYPE>_SCALE1,
            <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i],
                <VTYPE>_SRC0_PLUS_SCALE1_SRC1[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SRC0_PLUS_SCALE1_SRC1", "dst", i,
                    <VTYPE>_SRC0_PLUS_SCALE1_SRC1, dst, __FILE__,
                    __FUNCTION__, __LINE__);
                break;
            }
        }
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}

static SLC_errno_t <VTYPE>MultiplyEbeAssUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLC_<VTYPE>Copy(dst, 1, <VTYPE>_SRC0, 1, <VTYPE>_ARRAY_SIZE);
        SLCBLAS_<VTYPE>MultiplyEbeAss(
            dst, <VTYPE>_SRC1, <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i],
                <VTYPE>_SRC0_SRC1_EBE[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SRC0_SRC1_EBE", "dst", i,
                    <VTYPE>_SRC0_SRC1_EBE, dst, __FILE__,
                    __FUNCTION__, __LINE__);
                break;
            }
        }
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Add, Scale, ScaleAdd, MultiplyEbe
```
static SLC_errno_t <VTYPE>AddUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLCBLAS_<VTYPE>Add(
            dst, <VTYPE>_SRC0, <VTYPE>_SRC1, <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i],
                <VTYPE>_SRC0_PLUS_SRC1[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SRC0_PLUS_SRC1", "dst", i,
                    <VTYPE>_SRC0_PLUS_SRC1, dst, __FILE__,
                    __FUNCTION__, __LINE__);
                break;
            }        
        }
    }
    while(0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}

static SLC_errno_t <VTYPE>ScaleUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLCBLAS_<VTYPE>Scale(
            dst, <VTYPE>_SRC0, &<VTYPE>_SCALE0, <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i],
                <VTYPE>_SCALE0_SRC0[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SCALE0_SRC0", "dst", i,
                    <VTYPE>_SCALE0_SRC0, dst, __FILE__,
                    __FUNCTION__, __LINE__);
                break;
            }        
        }
    }
    while(0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}

static SLC_errno_t <VTYPE>ScaleAddUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLCBLAS_<VTYPE>ScaleAdd(
            dst, <VTYPE>_SRC0, &<VTYPE>_SCALE0, <VTYPE>_SRC1,
            &<VTYPE>_SCALE1, <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i],
                <VTYPE>_SCALE0_SRC0_PLUS_SCALE1_SRC1[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SCALE0_SRC0_PLUS_SCALE1_SRC1", "dst", i,
                    <VTYPE>_SCALE0_SRC0_PLUS_SCALE1_SRC1, dst, __FILE__,
                    __FUNCTION__, __LINE__);
                break;
            }        
        }
    }
    while(0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}

static SLC_errno_t <VTYPE>MultiplyEbeUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[SLC_ARRAY_SIZE(<VTYPE>_SRC0)];
    do
    {
        SLCBLAS_<VTYPE>MultiplyEbe(
            dst, <VTYPE>_SRC0, <VTYPE>_SRC1, <VTYPE>_ARRAY_SIZE);
        for (SLC_<ITYPE>_t i = 0; i < <VTYPE>_ARRAY_SIZE; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(dst[i],
                <VTYPE>_SRC0_SRC1_EBE[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>ERR_ARRAY_MISMATCH(
                    err, "<VTYPE>_SRC0_SRC1_EBE", "dst", i,
                    <VTYPE>_SRC0_SRC1_EBE, dst, __FILE__,
                    __FUNCTION__, __LINE__);
                break;
            }        
        }
    }
    while(0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Copy conjugate
```
```
## Inner product, product sum, sum, abs sum
```
```
## R32 test harness
```
SLC_errno_t MiniBLAS_<VTYPE>UT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>AddAssUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>ScaleAssUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>ScaleAddAssUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>MultiplyEbeAssUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>AddUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>ScaleUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>ScaleAddUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>MultiplyEbeUT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while(0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
SLC_errno_t MiniBLASUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        SLCTest_RUN_ERROR_BREAK(&err, MiniBLAS_R32UT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, MiniBLAS_R64UT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, MiniBLAS_C64UT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, MiniBLAS_C128UT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
