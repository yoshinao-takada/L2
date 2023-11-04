# Control
```
{
    "OUT": "../include/SLC/MiniBLAS.h",
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
File: MiniBLAS.h
Description: BLAS like number array operations

Revision history
Rev.     Date   Author  Description
00.00.00 231103 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_01MATH_MINIBLAS_H)
#define _01MATH_MINIBLAS_H
#include "SLC/Numbers.h"
#include <stdio.h>
```
# Generic
Generic definitions of base number specific functions, types, etc.
## Assignment operations
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_ASSIGNMENT_OPERATION
/**
\brief Additional assignment (dst[*] += src[*])
\param dst [in] a pointer to a destination number memory block
\param src [in] a pointer to a source number memory block
\param count [in] element count of destination memory block
*/
void SLCBLAS_<VTYPE>AddAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count);

/**
\brief Scaling assignment (dst[*] *= scale[0])
\param dst [in] a pointer to a destination number memory block
\param scale [in] a pointer to a source number variable
\param count [in] element count of destination memory block
*/
void SLCBLAS_<VTYPE>ScaleAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* scale, SLC_<ITYPE>_t count);

/**
\brief Scaling additional assignment (dst[*] += src[*] * scale[0])
\param dst [in] a pointer to a destination number memory block
\param src [in] a pointer to a source number variable
\param scale [in] a pointer to a source number variable
\param count [in] element count of destination and source memory block
*/
void SLCBLAS_<VTYPE>ScaleAddAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src,
    const SLC_<VTYPE>_t* scale, SLC_<ITYPE>_t count);

/**
\brief element-by-element multiplication assignment(dst[*]) *= src[*]
\param dst [in] a pointer to a destination number memory block
\param src [in] a pointer to a source number memory block
\param count [in] element count of destination memory block
*/
void SLCBLAS_<VTYPE>MultiplyEbeAss(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count);
#pragma endregion <VTYPE>_ASSIGNMENT_OPERATION
```
## non-assignment operators
```
#pragma region <VTYPE>_NON_ASSIGNMENT_OPERATION
/**
\brief non-assignment addition(dst[*] = src0[*] + src[1])
\param dst [out] pointer to a number memory block of sum
\param src0 [in] pointer to the first source number memory block
\param src1 [in] pointer to the second source number memory block
\param count [in] element count of each memory block
*/
void SLCBLAS_<VTYPE>Add(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src0,
    const SLC_<VTYPE>_t* src1, SLC_<ITYPE>_t count);

/**
\brief non-assignment scaling (dst[*] = src[*] * scale[0])
\param dst [out] pointer to a number memory block of scaled vector
\param src [in] pointer to the source number memory block
\param scale [in] pointer to the multiplier number variable
\param count [in] element count of each memory block
*/
void SLCBLAS_<VTYPE>Scale(
    SLC_<VTYPE>_t* dst, const SLC_<VTYPE>_t* src, 
    const SLC_<VTYPE>_t* scale, SLC_<ITYPE>_t count);

/**
\brief non-assignment scaling addition; 
    i.e. += scale0 * src0[i] + scale1 * src1[i]
\param dst [out] pointer to a number memory block of result vector
\param src0 [in] pointer to the first source number memory block
\param scale0 [in] pointer to the first multiplier number variable
\param src1 [in] pointer to the second source number memory block
\param scale1 [in] pointer to the second multiplier number variable
\param count [in] element count of each memory block
*/
void SLCBLAS_<VTYPE>ScaleAdd(
    SLC_<VTYPE>_t* dst, 
    const SLC_<VTYPE>_t* src0, const SLC_<VTYPE>_t* scale0, 
    const SLC_<VTYPE>_t* src1, const SLC_<VTYPE>_t* scale1,
    SLC_<ITYPE>_t count);

// element-by-element operation has a postfix 'ebe'
// element-by-element product
/**
\brief non-assignment element-by-element multiplication
\param dst [out] pointer to a number memory block of result vector
\param src0 [in] pointer to the first source number memory block
\param src1 [in] pointer to the second source number memory block
\param count [in] element count of each memory block
*/
void SLCBLAS_<VTYPE>MultiplyEbe(SLC_<VTYPE>_t* dst, 
    const SLC_<VTYPE>_t* src0, const SLC_<VTYPE>_t* src1,
    SLC_<ITYPE>_t count);

/**
\brief copy conjugate of a number array in scatter, gather, or continuous
    manner.
\param dst [out] copy destinatin
\param dst_step [in] destination index increment step
\param src [in] copy source
\param src_step [in] source index increment step
\param count [in] copy size
*/
void SLCBLAS_<VTYPE>CopyConj(
    SLC_<VTYPE>_t* dst, SLC_<ITYPE>_t dst_step,
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t src_step,
    SLC_<ITYPE>_t count
);
#pragma endregion <VTYPE>_NON_ASSIGNMENT_OPERATION
```
## vector-in scalar-out operations
```
#pragma region <VTYPE>_VECTOR_IN_SCALAR_OUT_OPERATION
/**
\brief Inner product of two vectors; i.e. sum(src0[*] * conj(src1[*]))
\param src0 [in] a pointer to the first number memory block
\param src1 [in] a pointer to the second number memory block
    (to be conjugated, 
    for real number type, no difference with ProductSum)
\param count [in] element count of each memory block
\return Inner product result
*/
SLC_<VTYPE>_t SLCBLAS_<VTYPE>InnerProduct(
    const SLC_<VTYPE>_t* src0, const SLC_<VTYPE>_t* src1,
    SLC_<ITYPE>_t count);

/**
\brief Product sum of two vectors
\param src0 [in] a pointer to the first number memory block
\param src1 [in] a pointer to the second number memory block
\param count [in] element count of each memory block
\brief return product sum result
*/
SLC_<VTYPE>_t SLCBLAS_<VTYPE>ProductSum(
    const SLC_<VTYPE>_t* src0, const SLC_<VTYPE>_t* src1,
    SLC_<ITYPE>_t count);

/**
\brief sum of vector elements
\param src [in] a pionter to a number memory block
\param count [in] element count of the memory block
\return sum of the elements in the memory block
*/
SLC_<VTYPE>_t SLCBLAS_<VTYPE>Sum(
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count);

/**
\brief Absolute sum of vector elements
\param src [in] a pionter to a number memory block
\param count [in] element count of the memory block
\return Absolute sum of the elements in the memory block
*/
SLC_<RTYPE>_t SLCBLAS_<VTYPE>AbsSum(
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t count);
#pragma endregion <VTYPE>_VECTOR_IN_SCALAR_OUT_OPERATION
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _01MATH_MINIBLAS_H */
```
