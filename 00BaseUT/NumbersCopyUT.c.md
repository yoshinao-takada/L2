# Control
```
{
    "OUT": "NumbersCopyUT.c",
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
File: NumbersCopyUT.c
Description: Test codes for functions in "00Base/NumbersCopy.c".

Revision history
Rev.     Date   Author  Description
00.00.00 231107 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Log.h"
#include "SLC/NumbersCopy.h"
#include <stdlib.h>
```
## R32 Test Data
```
static const SLC_R32_t R32_SRC0[] = { -1.0f, -0.3f, 1.1f };
static const SLC_R32_t R32_SRC1[] = { 1.2f, 0.1f, -1.5f };
```
## R64 Test Data
```
static const SLC_R64_t R64_SRC0[] = { -1.0, -0.3, 1.1 };
static const SLC_R64_t R64_SRC1[] = { 1.2, 0.1, -1.5 };
```
## C64 Test Data
```
static const SLC_C64_t C64_SRC0[] = 
{
    CMPLXF(-1.0f, -0.3f), CMPLXF(1.1f, 2.1f),
    CMPLXF(3.3f, 4.5f), CMPLXF(6.7f, 7.0f)
};
static const SLC_C64_t C64_SRC1[] = 
{
    CMPLXF(1.2f, 0.1f), CMPLXF(-1.5f, -2.5f),
    CMPLXF(-3.3f, -3.8f), CMPLXF(-4.5f, -5.5f)
};
```
## C128 Test Data
```
static const SLC_C128_t C128_SRC0[] = 
{
    CMPLX(-1.0, -0.3), CMPLX(1.1, 2.1),
    CMPLX(3.3, 4.5), CMPLX(6.7, 7.0)
};
static const SLC_C128_t C128_SRC1[] = 
{
    CMPLX(1.2, 0.1), CMPLX(-1.5, -2.5),
    CMPLX(-3.3, -3.8), CMPLX(-4.5, -5.5)
};
```

# Generic
Generic definitions of base number specific functions, types, etc.
## Unit Test for SLC_<VTYPE>Copy()
```
#pragma region <VTYPE>_functions
static SLC_errno_t <VTYPE>CopyUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLC_<VTYPE>_t dst[4];
    const SLC_<ITYPE>_t srcSize = SLC_ARRAY_SIZE(<VTYPE>_SRC0);
    do
    {
        // 1-by-1 copy
        SLC_<VTYPE>Copy(dst, 1, <VTYPE>_SRC0, 1, srcSize);
        for (SLC_<ITYPE>_t i = 0; i < srcSize; i++)
        {
            if (dst[i] != <VTYPE>_SRC0[i])
            {
                err = SLC_EVALMISMATCH;
                SLCLog_ERR(err, "Value mismatch @ %s,%s,%d\n",
                    __FILE__, __FUNCTION__, __LINE__);
                break;
            }
        }
        
        // 2-by-3 copy
        dst[0] = dst[1] = dst[2] = dst[3] = SLC_<VTYPE>_0;
        SLC_<VTYPE>Copy(dst, 2, <VTYPE>_SRC0, 3, 2);
        if (dst[0] != <VTYPE>_SRC0[0])
        {
            SLCLog_ERR(err, "Value mismatch @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        if (dst[1] != SLC_<VTYPE>_0)
        {
            SLCLog_ERR(err, "Value mismatch @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        if (dst[2] != <VTYPE>_SRC0[3])
        {
            SLCLog_ERR(err, "Value mismatch @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Unit Test for SLC_<VTYPE>Swap()
```
static SLC_errno_t <VTYPE>SwapUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {

    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Unit Test for SLC_<VTYPE>Gather()
```
static SLC_errno_t <VTYPE>GatherUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {

    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Unit Test for SLC_<VTYPE>Scatter()
```
static SLC_errno_t <VTYPE>ScatterUT()
{
    SLC_errno_t err = EXIT_SUCCESS;
    do
    {

    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
## Test harness for SLC_<VTYPE>XXX() functions
```
static SLC_errno_t <VTYPE>NumbersCopyUT()
{
    SLC_errno_t  err = EXIT_SUCCESS;
    do 
    {
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>CopyUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>SwapUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>GatherUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, <VTYPE>ScatterUT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
SLC_errno_t NumbersCopyUT()
{
    SLC_errno_t  err = EXIT_SUCCESS;
    do 
    {
        SLCTest_RUN_ERROR_BREAK(&err, R32NumbersCopyUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, R64NumbersCopyUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, C64NumbersCopyUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, C128NumbersCopyUT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
