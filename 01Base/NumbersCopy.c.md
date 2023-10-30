# Control
```
{
    "OUT": "NumbersCopy.c",
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
File: NumbersCopy.c
Description: Functions to copy array of numbers in a raw memory block

Revision history
Rev.     Date   Author  Description
00.00.00 231028 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/NumbersCopy.h"
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_array_copy_functions
void SLC<VTYPE>_copy(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count)
{
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst = *src;
        dst += dststep;
        src += srcstep;
    }
}

void SLC<VTYPE>_swap(SLC<VTYPE>_t* var0, SLC<ITYPE>_t step0, SLC<VTYPE>_t* var1, SLC<ITYPE>_t step1, SLC<ITYPE>_t count)
{
    SLC<VTYPE>_t temp;
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        temp = *var0;
        *var0 = *var1;
        *var1 = temp;
        var0 += step0;
        var1 += step1;
    }
}

void SLC<VTYPE>_gather(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count)
{
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst++ = *src;
        src += srcstep;
    }
}

void SLC<VTYPE>_scatter(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t count)
{
    for (SLC<ITYPE>_t i = 0; i < count; i++)
    {
        *dst = *src++;
        dst += dststep;
    }
}
#pragma endregion <VTYPE>_array_copy_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
