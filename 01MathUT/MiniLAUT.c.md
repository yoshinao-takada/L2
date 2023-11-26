# Control
```
{
    "OUT": "MiniLAUT.c",
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
(C) CopyRIGHT 2023, Yoshinao Takada
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
#include "SLC/MiniBLAS.h"
#include "SLC/MiniLA.h"
#include <stdlib.h>
#include <stdio.h>
```
## R32 test data
```
#pragma region R32_test_data
// source values
static const SLC_R32_t R32SRC0[] = {
    1.0f, 2.0f, 2.5f,
    1.2f, -10.0f, -5.5f
};
static const SLC_R32_t R32SRC1[] = {
    -1.0f, -2.0f, -2.0f,
    -1.5f, 10.5f, 6.0f
};
static const SLC_R32_t R32SRC2[] = {
    -1.0f, -2.0f, -2.0f, -4.0f,
    2.0f, 2.2f, -3.3f, -5.0f,
    1.5f, -1.5f, -2.2f, -5.0f
};
static const SLC_R32_t R32SRC3[] = {
    -1.0f, -2.0f, -2.0f,
    -4.0f, 2.0f, 2.2f,
    -3.3f, -5.0f, 1.5f
};
static const SLC_R32_t R32RIGHT[] = {
    1.0f, 1.2f,
    2.0f, -10.0f,
    2.5f, -5.5f
};
// 5x3 matrix
static const SLC_R32_t R32LEFTOD[] = {
    -1.0f, -2.0f, -2.0f,
    -4.0f, 2.0f, 2.2f,
    -3.3f, -5.0f, 1.5f,
    -4.0f, 2.2f, 2.0f,
    -3.3f, 1.5f, -5.0f,
};
// SOLUTION for overly determined linear equation
static const SLC_R32_t* R32SOLUTIONOD = R32RIGHT;

static const SLC_R32_t R32SCALE0 = 1.1f, R32SCALE1 = -1.5f;

// test reference values
// SRC0 + SRC1
static const SLC_R32_t R32_SRC0_PLUS_SRC1[] = {
    0.0f, 0.0f, 0.5f,
    -0.3f, 0.5f, 0.5f
};
// SCALE0 * SRC0 + SCALE1 * SRC1
static const SLC_R32_t R32_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = {
    2.6f, 5.2f, 5.75f,
    3.57f, -26.75f, -15.05f
};
// SCALE0 * SRC0
static const SLC_R32_t R32_SCALE0_SRC0[] = {
    1.1f, 2.2f, 2.75f,
    1.32f, -11.0f, -6.05f
};
// SRC0 * SRC2
static const SLC_R32_t R32_SRC0_SRC2[] = {
    6.75f, -1.35f, -14.1f, -26.5f,
    -29.45f, -16.15f, 42.7f, 72.7f
};
#pragma endregion R32_test_data
```
## R64 test data
```
#pragma region R64_test_data
// source values
static const SLC_R64_t R64SRC0[] = {
    1.0, 2.0, 2.5,
    1.2, -10.0, -5.5
};
static const SLC_R64_t R64SRC1[] = {
    -1.0, -2.0, -2.0,
    -1.5, 10.5, 6.0f
};
static const SLC_R64_t R64SRC2[] = {
    -1.0, -2.0, -2.0, -4.0,
    2.0, 2.2, -3.3, -5.0,
    1.5, -1.5, -2.2, -5.0
};
static const SLC_R64_t R64SRC3[] = {
    -1.0, -2.0, -2.0,
    -4.0, 2.0, 2.2,
    -3.3, -5.0, 1.5
};
static const SLC_R64_t R64RIGHT[] = {
    1.0, 1.2,
    2.0, -10.0,
    2.5, -5.5
};
// 5x3 matrix
static const SLC_R64_t R64LEFTOD[] = {
    -1.0, -2.0, -2.0,
    -4.0, 2.0, 2.2,
    -3.3, -5.0, 1.5,
    -4.0, 2.2, 2.0,
    -3.3, 1.5, -5.0
};
// SOLUTION for overly determined linear equation
static const SLC_R64_t* R64SOLUTIONOD = R64RIGHT;

static const SLC_R64_t R64SCALE0 = 1.1, R64SCALE1 = -1.5f;

// test reference values
// SRC0 + SRC1
static const SLC_R64_t R64_SRC0_PLUS_SRC1[] = {
    0.0, 0.0, 0.5,
    -0.3, 0.5, 0.5
};
// SCALE0 * SRC0 + SCALE1 * SRC1
static const SLC_R64_t R64_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = {
    2.6, 5.2, 5.75,
    3.57, -26.75, -15.05
};
// SCALE0 * SRC0
static const SLC_R64_t R64_SCALE0_SRC0[] = {
    1.1, 2.2, 2.75,
    1.32, -11.0, -6.05
};
// SRC0 * SRC2
static const SLC_R64_t R64_SRC0_SRC2[] = {
    6.75, -1.35, -14.1, -26.5,
    -29.45, -16.15, 42.7, 72.7
};
#pragma endregion R64_test_data
```
## C64 test data
```
#pragma region C64_test_data
// source values
static const SLC_C64_t C64SRC0[] = {
    CMPLXF(1.0f, 2.0f), CMPLXF(2.5f,-2.2f), CMPLXF(-0.5f,0.5f),
    CMPLXF(1.2f, -10.0f), CMPLXF(-5.5f, -2.5f), CMPLXF(2.5f,2.2f)
};
static const SLC_C64_t C64SRC1[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, 0.0f), CMPLXF(-0.0f,0.5f),
    CMPLXF(-1.5f, 10.5f), CMPLXF(6.0f, 0.0f), CMPLXF(0.0f,0.2f)
};
static const SLC_C64_t C64SRC2[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f), CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f),
    CMPLXF(2.0f, 2.2f), CMPLXF(-3.3f, -5.0f), CMPLXF(2.0f, -2.2f), CMPLXF(3.3f, -5.0f),
    CMPLXF(1.5f, -1.5f), CMPLXF(-2.2f, -5.0f), CMPLXF(-1.5f, -1.5f), CMPLXF(2.2f, -5.0f),
};
static const SLC_C64_t C64SRC3[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f), CMPLXF(2.0f, 2.2f),
    CMPLXF(-4.0f, 2.0f), CMPLXF(2.2f, -3.3f), CMPLXF(-5.0f, 1.5f),
    CMPLXF(-3.3f, -5.0f), CMPLXF(1.5f, -1.0f), CMPLXF(-2.0f, -2.0f)
};
static const SLC_C64_t C64RIGHT[] = {
    CMPLXF(1.0f, 2.0f), CMPLXF(1.2f, -10.0f),
    CMPLXF(2.5f, -2.2f), CMPLXF(-5.5f, -2.5f),
    CMPLXF(-0.5f, 0.5f), CMPLXF(2.5f, 2.2f)
};
// 5x3 matrix
static const SLC_C64_t C64LEFTOD[] = {
    CMPLXF(-1.0f, -2.0f), CMPLXF(-2.0f, -4.0f), CMPLXF(2.0f, 2.2f),
    CMPLXF(-4.0f, 2.0f), CMPLXF(2.2f, -3.3f), CMPLXF(-5.0f, 1.5f),
    CMPLXF(-3.3f, -5.0f), CMPLXF(1.5f, -1.0f), CMPLXF(-2.0f, -2.0f),
    CMPLXF(-4.0f, 2.0f), CMPLXF(-5.0f, 1.5f), CMPLXF(2.2f, -3.3f),
    CMPLXF(-3.3f, -5.0f), CMPLXF(-2.0f, -2.0f), CMPLXF(1.5f, -1.0f)
};
// SOLUTION for overly determined linear equation
static const SLC_C64_t* C64SOLUTIONOD = C64RIGHT;

static const SLC_C64_t C64SCALE0 = CMPLXF(0.1f,1.1f), C64SCALE1 = CMPLXF(-1.5f,0.1f);

// test reference values
// SRC0 + SRC1
static const SLC_C64_t C64_SRC0_PLUS_SRC1[] = {
    CMPLXF(0.0f, 0.0f), CMPLXF(0.5f,-2.2f), CMPLXF(-0.5f,1.0f),
    CMPLXF(-0.3f,0.5f), CMPLXF(0.5f,-2.5f), CMPLXF(2.5f,2.4f)
};
// SCALE0 * SRC0 + SCALE1 * SRC1
static const SLC_C64_t C64_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = {
    CMPLXF(-0.4f,4.2f), CMPLXF(5.67f,2.33f), CMPLXF(-0.65f,-1.25f),
    CMPLXF(12.32f,-15.58f), CMPLXF(-6.8f, -5.7f), CMPLXF(-2.19f,2.67f)
};
// SCALE0 * SRC0
static const SLC_C64_t C64_SCALE0_SRC0[] = {
    CMPLXF(-2.1f,1.3f), CMPLXF(2.67f,2.53f), CMPLXF(-0.6f,-0.5f),
    CMPLXF(11.12f,0.32f), CMPLXF(2.2f,-6.3f), CMPLXF(-2.17f,2.97f)
};
// SRC0 * SRC2
static const SLC_C64_t C64_SRC0_SRC2[] = {
    CMPLXF(12.84f,-1.4f), CMPLXF(-9.65f,-11.84f), CMPLXF(4.66f,-13.9f), CMPLXF(4.65f,-24.16f),
    CMPLXF(-19.65f,-9.95f), CMPLXF(-31.25f,33.61f), CMPLXF(-38.15f,7.65f), CMPLXF(-56.55f,26.79f)
};
#pragma endregion C64_test_data
```
## C128 test data
```
#pragma region C128_test_data
// source values
static const SLC_C128_t C128SRC0[] = {
    CMPLX(1.0, 2.0), CMPLX(2.5,-2.2), CMPLX(-0.5,0.5),
    CMPLX(1.2, -10.0), CMPLX(-5.5, -2.5), CMPLX(2.5,2.2)
};
static const SLC_C128_t C128SRC1[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, 0.0), CMPLX(-0.0,0.5),
    CMPLX(-1.5, 10.5), CMPLX(6.0, 0.0), CMPLX(0.0,0.2)
};
static const SLC_C128_t C128SRC2[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0), CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0),
    CMPLX(2.0, 2.2), CMPLX(-3.3, -5.0), CMPLX(2.0, -2.2), CMPLX(3.3, -5.0),
    CMPLX(1.5, -1.5), CMPLX(-2.2, -5.0), CMPLX(-1.5, -1.5), CMPLX(2.2, -5.0),
};
static const SLC_C128_t C128SRC3[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0), CMPLX(2.0, 2.2),
    CMPLX(-4.0, 2.0), CMPLX(2.2, -3.3), CMPLX(-5.0, 1.5),
    CMPLX(-3.3, -5.0), CMPLX(1.5, -1.0), CMPLX(-2.0, -2.0)
};
static const SLC_C128_t C128RIGHT[] = {
    CMPLX(1.0, 2.0), CMPLX(1.2, -10.0),
    CMPLX(2.5, -2.2), CMPLX(-5.5, -2.5),
    CMPLX(-0.5, 0.5), CMPLX(2.5, 2.2)
};
// 5x3 matrix
static const SLC_C128_t C128LEFTOD[] = {
    CMPLX(-1.0, -2.0), CMPLX(-2.0, -4.0), CMPLX(2.0, 2.2),
    CMPLX(-4.0, 2.0), CMPLX(2.2, -3.3), CMPLX(-5.0, 1.5),
    CMPLX(-3.3, -5.0), CMPLX(1.5, -1.0), CMPLX(-2.0, -2.0),
    CMPLX(-4.0, 2.0), CMPLX(-5.0, 1.5), CMPLX(2.2, -3.3),
    CMPLX(-3.3, -5.0), CMPLX(-2.0, -2.0), CMPLX(1.5, -1.0)
};
// SOLUTION for overly determined linear equation
static const SLC_C128_t* C128SOLUTIONOD = C128RIGHT;

static const SLC_C128_t C128SCALE0 = CMPLX(0.1,1.1), C128SCALE1 = CMPLX(-1.5,0.1);

// test reference values
// SRC0 + SRC1
static const SLC_C128_t C128_SRC0_PLUS_SRC1[] = {
    CMPLX(0.0, 0.0), CMPLX(0.5,-2.2), CMPLX(-0.5,1.0),
    CMPLX(-0.3,0.5), CMPLX(0.5,-2.5), CMPLX(2.5,2.4)
};
// SCALE0 * SRC0 + SCALE1 * SRC1
static const SLC_C128_t C128_SCALE0_SRC0_PLUS_SCALE1_SRC1[] = {
    CMPLX(-0.4,4.2), CMPLX(5.67,2.33), CMPLX(-0.65,-1.25),
    CMPLX(12.32,-15.58), CMPLX(-6.8, -5.7), CMPLX(-2.19,2.67)
};
// SCALE0 * SRC0
static const SLC_C128_t C128_SCALE0_SRC0[] = {
    CMPLX(-2.1,1.3), CMPLX(2.67,2.53), CMPLX(-0.6,-0.5),
    CMPLX(11.12,0.32), CMPLX(2.2,-6.3), CMPLX(-2.17,2.97)
};
// SRC0 * SRC2
static const SLC_C128_t C128_SRC0_SRC2[] = {
    CMPLX(12.84,-1.4), CMPLX(-9.65,-11.84), CMPLX(4.66,-13.9), CMPLX(4.65,-24.16),
    CMPLX(-19.65,-9.95), CMPLX(-31.25,33.61), CMPLX(-38.15,7.65), CMPLX(-56.55,26.79)
};
#pragma endregion C128_test_data
```
# Generic
Generic definitions of base number specific functions, types, etc.
## matrix sizes
```
#pragma region <VTYPE>_test_functions
#define NUMSIZE sizeof(SLC_<VTYPE>_t)
static const SLC_4I16_t <VTYPE>MATSIZE2x3 = { NUMSIZE, 3, 2, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE2x4 = { NUMSIZE, 4, 2, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE4x2 = { NUMSIZE, 2, 4, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE3x2 = { NUMSIZE, 2, 3, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE3x4 = { NUMSIZE, 4, 3, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE4x3 = { NUMSIZE, 3, 4, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE3x3 = { NUMSIZE, 3, 3, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE3x6 = { NUMSIZE, 6, 3, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE3x5 = { NUMSIZE, 5, 3, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE5x2 = { NUMSIZE, 2, 5, 1 };
static const SLC_4I16_t <VTYPE>MATSIZE2x5 = { NUMSIZE, 5, 2, 1 };
```
## add two matrices
```
static SLC_errno_t <VTYPE>AddUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    const SLCArray_t SRC0 = { {{NUMSIZE, 3, 2, 1}}, { <VTYPE>SRC0 } };
    const SLCArray_t SRC1 = { {{NUMSIZE, 3, 2, 1}}, { <VTYPE>SRC1 } };
    SLCArray_pt dst = SLCArray_ALLOC(SRC0.Dimensions.I16);
    do {
        SLCMat_<VTYPE>Add(dst, &SRC0, &SRC1);
        const SLC_<ITYPE>_t elementCount = 
            SLCMat_ROWS(dst) * SLCMat_COLUMNS(dst);
        for (SLC_<ITYPE>_t i = 0; i < elementCount; i++) 
        {
            if (!SLC_<VTYPE>_ARE_EQUAL
                (<VTYPE>_SRC0_PLUS_SRC1[i], dst->Data.<VTYPE>[i],
                SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>_ERR_ARRAY_MISMATCH
                (err, "<VTYPE>_SRC0_PLUS_SRC1", "dst->Data.<VTYPE>", i,
                    <VTYPE>_SRC0_PLUS_SRC1, dst->Data.<VTYPE>,
                    __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_SAFE_FREE(&dst);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Scaling and add two matrices
```
static SLC_errno_t <VTYPE>ScaleAddUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    const SLCArray_t SRC0 = { {{NUMSIZE, 3, 2, 1}}, { <VTYPE>SRC0 } };
    const SLCArray_t SRC1 = { {{NUMSIZE, 3, 2, 1}}, { <VTYPE>SRC1 } };
    SLCArray_pt dst = SLCArray_ALLOC(SRC0.Dimensions.I16);
    do {
        SLCMat_<VTYPE>ScaleAdd
            (dst, &SRC0, &<VTYPE>SCALE0, &SRC1, &<VTYPE>SCALE1);
        const SLC_<ITYPE>_t elementCount = 
            SLCMat_ROWS(dst) * SLCMat_COLUMNS(dst);
        for (SLC_<ITYPE>_t i = 0; i < elementCount; i++) 
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(
                <VTYPE>_SCALE0_SRC0_PLUS_SCALE1_SRC1[i], 
                dst->Data.<VTYPE>[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_SUCCESS;
                SLCLog_<VTYPE>_ERR_ARRAY_MISMATCH(err,
                    "<VTYPE>_SCALE0_SRC0_PLUS_SCALE1_SRC1",
                    "dst->Data.<VTYPE>", i,
                    <VTYPE>_SCALE0_SRC0_PLUS_SCALE1_SRC1,
                    dst->Data.<VTYPE>,
                    __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_SAFE_FREE(&dst);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Scaling a matrix
```
static SLC_errno_t <VTYPE>ScaleUT() 
{
    SLC_errno_t err = EXIT_SUCCESS;
    const SLCArray_t SRC0 = { {{NUMSIZE, 3, 2, 1}}, { <VTYPE>SRC0 } };
    SLCArray_pt dst = SLCArray_ALLOC(SRC0.Dimensions.I16);
    do {
        SLCMat_<VTYPE>Scale(dst, &SRC0, &<VTYPE>SCALE0);
        SLC_<ITYPE>_t elementCount = 
            SLCMat_ROWS(dst) * SLCMat_COLUMNS(dst);
        for (SLC_<ITYPE>_t i = 0; i < elementCount; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(<VTYPE>_SCALE0_SRC0[i],
                dst->Data.<VTYPE>[i], SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>_ERR_ARRAY_MISMATCH(err,
                    "<VTYPE>_SCALE0_SRC0", "dst->Data.<VTYPE>",
                    i, <VTYPE>_SCALE0_SRC0, dst->Data.<VTYPE>,
                    __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_SAFE_FREE(&dst);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## multiply two matrices
```
static SLC_errno_t <VTYPE>MultiplyUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    const SLCArray_t SRC0 = { {{NUMSIZE, 3, 2, 1}}, { <VTYPE>SRC0 } };
    const SLCArray_t SRC2 = { {{NUMSIZE, 4, 3, 1}}, { <VTYPE>SRC2 } };
    SLCArray_pt dst = SLCArray_ALLOC(<VTYPE>MATSIZE2x4);
    SLCArray_pt work = SLCArray_ALLOC(<VTYPE>MATSIZE4x3);
    do {
        SLCMat_<VTYPE>Multiply(dst, &SRC0, &SRC2, work);
        SLC_<ITYPE>_t elementCount = 
            SLCMat_ROWS(dst) * SLCMat_COLUMNS(dst);
        for (SLC_<ITYPE>_t i = 0; i < elementCount; i++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL(
                <VTYPE>_SRC0_SRC2[i], dst->Data.<VTYPE>[i],
                SLC_<VTYPE>_STDTOL))
            {
                err = EXIT_FAILURE;
                SLCLog_<VTYPE>_ERR_ARRAY_MISMATCH(err,
                    "<VTYPE>_SRC0_SRC2", "dst->Data.<VTYPE>",
                    i, <VTYPE>_SRC0_SRC2, dst->Data.<VTYPE>,
                    __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
    } while (0);
    SLC_SAFE_FREE(&dst);
    SLC_SAFE_FREE(&work);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Invert a matrix
```
static SLC_errno_t <VTYPE>IsIdentity3x3(SLCArray_cpt mat)
{
    const SLC_<VTYPE>_t _0 = SLC_<VTYPE>_0, _1 = SLC_<VTYPE>_1;
    SLC_errno_t err = (3 == SLCMat_ROWS(mat))
                    && (3 == SLCMat_COLUMNS(mat)) ?
                    EXIT_SUCCESS : SLC_EVALMISMATCH;
    const SLC_<VTYPE>_t* element_ptr = mat->Data.<VTYPE>;
    for (SLC_<ITYPE>_t row = 0; row < 3; row++)
    {
        for (SLC_<ITYPE>_t column = 0; column < 3;
            column++, element_ptr++)
        {
            const SLC_<VTYPE>_t refval = (row == column) ? _1 : _0;
            if (!SLC_<VTYPE>_ARE_EQUAL
                (refval, *element_ptr, SLC_<VTYPE>_STDTOL))
            {
                err = SLC_EVALMISMATCH;
                // SLCLog_ERR(err, "(row,column) = (%d,%d) @ %s,%d\n",
                //     row, column, __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
        if (err) break;
    }
    return err;
}

static SLC_errno_t <VTYPE>InvertUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLCArray_t SRC3 = { {{ NUMSIZE, 3, 3, 1 }}, { <VTYPE>SRC3 }};
    SLCArray_pt dst = SLCArray_ALLOC(<VTYPE>MATSIZE3x3),
        work = SLCArray_ALLOC(<VTYPE>MATSIZE3x6),
        work_mult = SLCArray_ALLOC(<VTYPE>MATSIZE3x3),
        imat = SLCArray_ALLOC(<VTYPE>MATSIZE3x3);
    do {
        err = SLCMat_<VTYPE>Inv(dst, &SRC3, work);
        SLCMat_<VTYPE>Multiply(imat, &SRC3, dst, work_mult);
        // SLCMat_<VTYPE>Print(SLCLog_Sink, "imat = ", imat, "");
        if (EXIT_SUCCESS != (err = <VTYPE>IsIdentity3x3(imat))) break;
    } while (0);
    SLC_SAFE_FREE(&dst);
    SLC_SAFE_FREE(&work);
    SLC_SAFE_FREE(&work_mult);
    SLC_SAFE_FREE(&imat);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Solve a fully determined equation
```
static SLC_errno_t 
<VTYPE>CompareMat(SLCArray_cpt matref, SLCArray_cpt mattest)
{
    const SLC_I16_t
        REFROWS = SLCMat_ROWS(matref),
        REFCOLUMNS = SLCMat_COLUMNS(matref);
    SLC_errno_t err = 
        ((REFROWS == SLCMat_ROWS(mattest)) &&
        (REFCOLUMNS == SLCMat_COLUMNS(mattest))) ?
        EXIT_SUCCESS : SLC_EVALMISMATCH;
    if (err) return err;
    const SLC_<VTYPE>_t
        *refptr = matref->Data.<VTYPE>, *testptr = mattest->Data.<VTYPE>;
    for (SLC_I16_t row = 0; row < REFROWS; row++)
    {
        for (SLC_I16_t column = 0; column < REFCOLUMNS;
            column++, refptr++, testptr++)
        {
            if (!SLC_<VTYPE>_ARE_EQUAL
                (*refptr, *testptr, SLC_<VTYPE>_STDTOL))
            {
                err = SLC_EVALMISMATCH;
                SLCLog_ERR(err,
                    "Value mismatch (row, column) = (%d, %d) @ %s,%s,%d\n",
                    row, column, __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
        if (err) break;
    }
    return err;
}

static SLC_errno_t <VTYPE>SolveUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLCArray_t left = {{{NUMSIZE, 3, 3, 1}}, { <VTYPE>SRC3 }},
        right = {{{NUMSIZE, 2, 3, 1}}, { <VTYPE>RIGHT }};
    SLCArray_pt work = SLCArray_ALLOC(<VTYPE>MATSIZE3x5),
        dst = SLCArray_ALLOC(<VTYPE>MATSIZE3x2),
        work_mult = SLCArray_ALLOC(<VTYPE>MATSIZE2x3),
        right2 = SLCArray_ALLOC(right.Dimensions.I16);
    do {
        SLCMat_<VTYPE>Solve(dst, &left, &right, work);
        SLCMat_<VTYPE>Multiply(right2, &left, dst, work_mult);
        if (EXIT_SUCCESS != (err = <VTYPE>CompareMat(&right, right2)))
            break;
    } while (0);
    SLC_SAFE_FREE(&work);
    SLC_SAFE_FREE(&dst);
    SLC_SAFE_FREE(&work_mult);
    SLC_SAFE_FREE(&right2);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Solve an overly determined equation
```
static SLC_errno_t <VTYPE>SolveOdUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLCArray_t left = {{{NUMSIZE, 3, 5, 1}}, { <VTYPE>LEFTOD }};
    SLCArray_t ref_solution = 
        {{{NUMSIZE, 2, 3, 1}}, { <VTYPE>SOLUTIONOD }};
    SLCArray_pt right = SLCArray_ALLOC(<VTYPE>MATSIZE5x2),
        work_mult = SLCArray_ALLOC(<VTYPE>MATSIZE2x3),
        dst = SLCArray_ALLOC(ref_solution.Dimensions.I16);
    SLCMat_LmsSolverMatSet_t wkset = 
        { NULL, NULL, NULL, NULL, NULL, NULL };
    do {
        // create RHS
        SLCMat_<VTYPE>Multiply(right, &left, &ref_solution, work_mult);

        // create working matrix set
        err = SLCMat_InitLmsSolverMatSet(&wkset, &left, right);
        if (err)
        {
            SLCLog_ERR(err,
                "Fail in SLCMat_InitLmsSolverMatSet() @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }

        // solve equation
        err = SLCMat_<VTYPE>SolveOd(dst, &left, right, &wkset);
        if (err)
        {
            SLCLog_ERR(err, 
                "Fail in SLCMat_<VTYPE>SolveOD() @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }

        // compare results
        err = <VTYPE>CompareMat(&ref_solution, dst);
        if (err)
        {
            SLCLog_ERR(err, "Value mismatcin @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLC_SAFE_FREE(&right);
    SLC_SAFE_FREE(&work_mult);
    SLC_SAFE_FREE(&dst);
    SLCMat_DestroyLmsSolverMatSet(&wkset);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Simplified API to solve overly determined equation
```
static SLC_errno_t <VTYPE>EasySolveOdUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLCArray_t left = {{{NUMSIZE, 3, 5, 1}}, { <VTYPE>LEFTOD }};
    SLCArray_t ref_solution = {{{NUMSIZE, 2, 3, 1}}, { <VTYPE>SOLUTIONOD }};
    SLCArray_pt right = SLCArray_ALLOC(<VTYPE>MATSIZE5x2),
        work_mult = SLCArray_ALLOC(<VTYPE>MATSIZE2x3),
        dst = SLCArray_ALLOC(ref_solution.Dimensions.I16);
    do {
        // create RHS
        SLCMat_<VTYPE>Multiply(right, &left, &ref_solution, work_mult);

        // solve
        err = SLCMat_<VTYPE>EasySolveOd(dst, &left, right);
        if (err)
        {
            SLCLog_ERR(err,
                "Fail in SLCMat_<VTYPE>EasySolveOd() @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }

        // compare results
        err = <VTYPE>CompareMat(&ref_solution, dst);
        if (err)
        {
            SLCLog_ERR(err, "Value mismatcin @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
    } while (0);
    SLC_SAFE_FREE(&right);
    SLC_SAFE_FREE(&work_mult);
    SLC_SAFE_FREE(&dst);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Test harness for <VTYPE> functions
```
static SLC_errno_t MiniLA_<VTYPE>UT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do 
    {
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>AddUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>ScaleAddUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>ScaleUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>MultiplyUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>InvertUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>SolveUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>SolveOdUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>EasySolveOdUT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#undef NUMSIZE
#pragma region <VTYPE>_test_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
SLC_errno_t MiniLAUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        SLCTest_RUN_ERROR_BREAK(&err, MiniLA_R32UT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, MiniLA_R64UT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, MiniLA_C64UT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, MiniLA_C128UT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
