# Control
```
{
    "OUT": "NumbersUT.c",
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
## File Header
Head contains definitions common to all base number types.
```
/*
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

File description
File: NumbersUT.c
Description: Test codes for "00Base/Numbers.h"

Revision history
Rev.     Date   Author  Description
00.00.00 231106 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Log.h"
#include <stdlib.h>
```
## R32 Test Data
```
#pragma region R32_TEST_DATA
static const SLC_R32_t
    R32_PLUS_SMALL = 0.9f * SLC_R32_STDTOL,
    R32_MINUS_SMALL = -0.9f * SLC_R32_STDTOL,
    R32_PLUS_LARGE = SLC_R32_1,
    R32_PLUS_LARGE_MINUS_SMALL = R32_PLUS_LARGE - R32_PLUS_SMALL,
    R32_PLUS_LARGE_MINUS_2SMALL = 
        R32_PLUS_LARGE - (R32_PLUS_SMALL - R32_PLUS_SMALL);
#pragma endregion R32_TEST_DATA

```
## R64 Test Data
```
#pragma region R64_TEST_DATA
static const SLC_R64_t
    R64_PLUS_SMALL = 0.9 * SLC_R64_STDTOL,
    R64_MINUS_SMALL = -0.9 * SLC_R64_STDTOL,
    R64_PLUS_LARGE = SLC_R64_1,
    R64_PLUS_LARGE_MINUS_SMALL = R64_PLUS_LARGE - R64_PLUS_SMALL,
    R64_PLUS_LARGE_MINUS_2SMALL = 
        R64_PLUS_LARGE - (R64_PLUS_SMALL - R64_PLUS_SMALL);
#pragma endregion R64_TEST_DATA

```
## C64 Test Data
```
#pragma region C64_TEST_DATA
static const SLC_C64_t
    C64_PLUS_SMALL = CMPLXF(0.9f, 0.0f) * SLC_C64_STDTOL,
    C64_MINUS_SMALL = CMPLXF(-0.9f, 0.0f) * SLC_C64_STDTOL,
    C64_PLUS_LARGE = SLC_C64_1,
    C64_PLUS_LARGE_MINUS_SMALL = C64_PLUS_LARGE - C64_PLUS_SMALL,
    C64_PLUS_LARGE_MINUS_2SMALL = 
        C64_PLUS_LARGE - (C64_PLUS_SMALL - C64_PLUS_SMALL);
#pragma endregion C64_TEST_DATA

```
## C128 Test Data
```
#pragma region C128_TEST_DATA
static const SLC_C128_t
    C128_PLUS_SMALL = CMPLX(0.9, 0.0) * SLC_C128_STDTOL,
    C128_MINUS_SMALL = CMPLX(-0.9, 0.0) * SLC_C128_STDTOL,
    C128_PLUS_LARGE = SLC_C128_1,
    C128_PLUS_LARGE_MINUS_SMALL = C128_PLUS_LARGE - C128_PLUS_SMALL,
    C128_PLUS_LARGE_MINUS_2SMALL = 
        C128_PLUS_LARGE - (C128_PLUS_SMALL - C128_PLUS_SMALL);
#pragma endregion C128_TEST_DATA

```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_FUNCTION_UNIT_TESTS
```
## Test for equality checker with two small numbers
```
SLC_errno_t <VTYPE>EqalityTwoSmallNumbersUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {
        bool b =
    }
    while (0);
    return err;
}
```
## Test for equality checker with two medium numbers
```
SLC_errno_t <VTYPE>EqalityTwoMediumNumbersUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {

    }
    while (0);
    return err;
}
```
## Test for equality checker with a small number and a medium number
```
SLC_errno_t <VTYPE>EqalitySmallAndMediumNumbersUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {

    }
    while (0);
    return err;
}
```
## Test Harness for <VTYPE> macros.
```
static SLC_errno_t <VTYPE>NumbersUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {

    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_FUNCTION_UNIT_TESTS
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
// Test harness for Numbers.h macros
SLC_errno_t NumbersUT()
{
    SLC_errno_t  err = EXIT_SUCCESS;
    do 
    {
        SLCTest_RUN_ERROR_BREAK(&err, R32NumbersUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, R64NumbersUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, C64NumbersUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, C128NumbersUT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
