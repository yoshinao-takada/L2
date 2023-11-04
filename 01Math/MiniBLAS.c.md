# Control
```
{
    "OUT": "MiniBLAS.c",
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
File: MiniBLAS.c
Description: BLAS like number array operations

Revision history
Rev.     Date   Author  Description
00.00.00 231103 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/MiniBLAS.h"
#include "SLC/NumbersCopy.h"
#include <stdio.h>
```
# Generic
Generic definitions of base number specific functions, types, etc.
## Assignment operations
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_ASSIGNMENT_OPERATION
void SLCBLAS_<VTYPE>AddAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count)
{
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++, src++)
    {
        *dst += *src;
    }
}

void SLCBLAS_<VTYPE>ScaleAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* scale, SLC_<ITYPE>_t count)
{
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++)
    {
        *dst *= *scale;
    }
}

void SLCBLAS_<VTYPE>ScaleAddAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src, 
    const SLC_<VTYPE>_t* scale,SLC_<ITYPE>_t count)
{
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++, src++)
    {
        *dst += *src * *scale;
    }
}

void SLCBLAS_<VTYPE>MultiplyEbeAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count)
{
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++, src++)
    {
        *dst *= *src;
    }
}
#pragma endregion <VTYPE>_ASSIGNMENT_OPERATION
```
## non-assignment operators
```
#pragma region <VTYPE>_NON_ASSIGNMENT_OPERATION
void SLCBLAS_<VTYPE>Add(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src0,
    const SLC_<VTYPE>_t* src1, SLC_<ITYPE>_t count)
{
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++, src0++, src1++)
    {
        *dst = *src0 + *src1;
    }
}

void SLCBLAS_<VTYPE>Scale(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src, 
    const SLC_<VTYPE>_t* scale, SLC_<ITYPE>_t count)
{
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++, src++)
    {
        *dst = *src * *scale;
    }
}

void SLCBLAS_<VTYPE>ScaleAdd(
    SLC_<VTYPE>_t* dst, 
    const SLC_<VTYPE>_t* src0, const SLC_<VTYPE>_t* scale0, 
    const SLC_<VTYPE>_t* src1, const SLC_<VTYPE>_t* scale1,
    SLC_<ITYPE>_t count
) {
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++, src0++, src1++)
    {
        *dst = (*src0) * (*scale0) + (*src1) * (*scale1);
    }
}

void SLCBLAS_<VTYPE>MultiplyEbe(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src0,
    const SLC_<VTYPE>_t* src1, SLC_<ITYPE>_t count)
{
    for (SLC_<ITYPE>_t i = 0; i < count; i++, dst++, src0++, src1++)
    {
        *dst = *src0 * *src1;
    }
}

void SLCBLAS_<VTYPE>CopyConj(
    SLC_<VTYPE>_t* dst, SLC_<ITYPE>_t dst_step,
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t src_step,
    SLC_<ITYPE>_t count
) {
    for (SLC_<ITYPE>_t i = 0; i < count; i++)
    {
        *dst = SLC_<VTYPE>_CONJ(*src);
        dst += dst_step;
        src += src_step;
    }
}
#pragma endregion <VTYPE>_NON_ASSIGNMENT_OPERATION
```
## vector-in scalar-out operations
```
#pragma region <VTYPE>_VECTOR_IN_SCALAR_OUT_OPERATION
SLC_<VTYPE>_t SLCBLAS_<VTYPE>InnerProduct(
    const SLC_<VTYPE>_t* src0, const SLC_<VTYPE>_t* src1, 
    SLC_<ITYPE>_t count)
{
    SLC_<VTYPE>_t result = (SLC_<VTYPE>_t)0;
    for (SLC_<ITYPE>_t i = 0; i < count; i++, src0++, src1++)
    {
        result += *src0 * SLC_<VTYPE>_CONJ(*src1);
    }
    return result;
}

SLC_<VTYPE>_t SLCBLAS_<VTYPE>ProductSum(
    const SLC_<VTYPE>_t* src0, const SLC_<VTYPE>_t* src1, 
    SLC_<ITYPE>_t count)
{
    SLC_<VTYPE>_t result = (SLC_<VTYPE>_t)0;
    for (SLC_<ITYPE>_t i = 0; i < count; i++, src0++, src1++)
    {
        result += *src0 * *src1;
    }
    return result;
}

SLC_<VTYPE>_t SLCBLAS_<VTYPE>Sum(
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count)
{
    SLC_<VTYPE>_t result = (SLC_<VTYPE>_t)0;
    for (SLC_<ITYPE>_t i = 0; i < count; i++, src++)
    {
        result += *src;
    }
    return result;
}

SLC_<RTYPE>_t SLCBLAS_<VTYPE>AbsSum(
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count)
{
    SLC_<RTYPE>_t result = (SLC_<RTYPE>_t)0;
    for (SLC_<ITYPE>_t i = 0; i < count; i++, src++)
    {
        result += SLC_<VTYPE>_ABS(*src);
    }
    return result;
}
#pragma endregion <VTYPE>_VECTOR_IN_SCALAR_OUT_OPERATION
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
