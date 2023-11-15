# Control
```
{
    "OUT": "ArrayUT.c",
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
File: ArrayUT.c
Description: Test codes for functions in "00Base/Array.c".

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
#include "SLC/Array.h"
#include "SLC/errno.h"
#include <stdlib.h>
```
## Check memory allocation sizes
```
#pragma region CHECK_MEMORY_ALLOCATION_SIZES
static bool AreEqual_SLC_4I16(const SLC_4I16_t x, const SLC_4I16_t y)
{
    return (x[0] == y[0]) && (x[1] == y[1]) && (x[2] == y[2]) &&
        (x[3] == y[3]);
}

static SLC_errno_t MemoryAllocSizeUT()
{
    static const SLC_4I16_t SIZE = { 4, 12, 100, 4 };
    const SLC_I64_t totalSize = sizeof(SLCArray_t) +
        (SLC_I64_t)(SIZE[0] * SIZE[1] * SIZE[2] * SIZE[3]);
    SLC_errno_t err = EXIT_SUCCESS;
    SLCArray_pt array0 = NULL, array1 = NULL;
    do
    {
        array0 = SLCArray_ALLOC(SIZE);
        if (SLCArray_LatestAllocated != totalSize)
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        if (!AreEqual_SLC_4I16(SIZE, array0->Dimensions.I16))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Dimension mismatch @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
        }
        array1 = SLCArray_ALLOCA(SIZE);
        if (SLCArray_LatestAllocated != totalSize)
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        if (!AreEqual_SLC_4I16(SIZE, array1->Dimensions.I16))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Dimension mismatch @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
        }
        SLC_SAFE_FREE(&array0);
        if (NULL != array0)
        {
            err = EINVAL;
            SLCLog_ERR(err, "Fail in SLC_SAFEFREE @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion CHECK_MEMORY_ALLOCATION_SIZES
```
## Create large arrays and copying their data one another.
```
#pragma region CREATE_AND_COPY_LARGE_ARRAYS
static SLC_errno_t CreateCopyLargeArraysUT()
{
    static const SLC_4I16_t SIZE = { sizeof(SLC_R64_t), 8192, 8192, 1 };
    static const SLC_I64_t LINEAR_ELEMENT_COUNT =
        (SLC_I64_t)SIZE[1] * (SLC_I64_t)SIZE[2] * (SLC_I64_t)SIZE[3];
    static const SLC_I64_t LAST_INDEX = LINEAR_ELEMENT_COUNT - 1;
    SLC_errno_t err = EXIT_SUCCESS;
    SLCArray_pt array0 = NULL, array1 = NULL;
    do
    {
        array0 = SLCArray_ALLOC(SIZE);
        array1 = SLCArray_ALLOC(SIZE);
        if (!array0 || !array1)
        {
            err = ENOMEM;
            SLCLog_ERR(err, "Fail to alloc array @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        for (SLC_I64_t i = 0; i < LINEAR_ELEMENT_COUNT; i++)
        {
            array0->Data.R64[i] = (SLC_R64_t)i;
        }
        SLC_I64_t ri = LINEAR_ELEMENT_COUNT;
        for (SLC_I64_t i = 0; i < LINEAR_ELEMENT_COUNT; i++)
        {
            array1->Data.R64[--ri] = array0->Data.R64[i];
        }
        if (!AreEqual_SLC_4I16(SIZE, array0->Dimensions.I16) ||
            !AreEqual_SLC_4I16(SIZE, array1->Dimensions.I16))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Array dimensions were broken @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        if ((array0->Data.R64[0] != array1->Data.R64[LAST_INDEX]) ||
            (array0->Data.R64[LAST_INDEX] != array1->Data.R64[0]))
        {
            err = SLC_EVALMISMATCH;
            SLCLog_ERR(err, "Value mismatch between two arrays @ %s,%s,%d\n",
                __FILE__, __FUNCTION__, __LINE__);
            break;
        }
    }
    while (0);
    SLC_SAFE_FREE(&array0);
    SLC_SAFE_FREE(&array1);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
#pragma endregion CREATE_AND_COPY_LARGE_ARRAYS
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
SLC_errno_t ArrayUT()
{
    SLC_errno_t  err = EXIT_SUCCESS;
    do 
    {
        SLCTest_RUN_ERROR_BREAK(&err, MemoryAllocSizeUT,
            __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(&err, CreateCopyLargeArraysUT,
            __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
