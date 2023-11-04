# Control
```
{
    "OUT": "../include/SLC/MiniLA.h",
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
File: MiniLA.h
Description: LAPACK like linear algebraic API.
    SLCArray_t objects are used as matrices.
    Size mismatching are checked only in debug build by assert().
    Release build does not check any size mismatching.

Revision history
Rev.     Date   Author  Description
00.00.00 231104 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_01MATH_MINILA_H)
#define _01MATH_MINILA_H
#include "SLC/Numbers.h"
#include "SLC/Array.h"
#include "SLC/errno.h"
#include <stdio.h>
```
## Matrix specific accesors to SLCArray_t
```
#define SLCMat_ROWS(_arrayPtr)          (_arrayPtr)->Control.I16[2]
#define SLCMat_COLUMNS(_arrayPtr)       (_arrayPtr)->Control.I16[1]
#define SLCMat_UNIT_SIZE(_arrayPtr)     (_arrayPtr)->Control.I16[0]
```
## Working matrix set for LSM overly determined equation solver
```
/**
\brief working matrix set for an LMS solver for 
    overly determined linear equation
*/
typedef struct
{
    SLCArray_pt
        leftT, //!< transpose of left
        leftTC, //!< transpose-conjugate of left
        leftTCLeft, // !< leftTC * left
        rightT, //!< transpose of right
        leftTCRight, //!< leftTC * right
        work; //!< working matrix for fully-determined linear equation
}
SLCMat_LmsSolverMatSet_t, *SLCMat_LmsSolverMatSet_pt;

typedef const SLCMat_LmsSolverMatSet_t *SLCMat_LmsSolverMatSet_cpt;

/**
\brief Initialize a working matrix set.
\param workSet [out] working matrix set
\param left [in] LHS of an overly determined linear equation
\param right [in] RHS of an overly determined linear equation
*/
SLC_errno_t SLCMat_InitLmsSolverMatSet(
    SLCMat_LmsSolverMatSet_pt workSet, 
    SLCArray_cpt left, SLCArray_cpt right);

/**
\brief Destroy a working matrix set to release allocated resources.
\param workSet [in,out] working matrix set
*/
void SLCMat_DestroyLmsSolverMatSet(SLCMat_LmsSolverMatSet_pt workSet);
```
# Generic
Generic definitions of base number specific functions, types, etc.
## Basic matrix operations
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_BASIC_MATRIX_OPERATIONS
/**
\brief dst = src0 + src1
*/
void SLCMat_<VTYPE>Add(
    SLCArray_pt dst, SLCArray_cpt src0, SLCArray_cpt src1);

/**
\brief dst = src0 * scale0 + src1 + scale1
*/
void SLCMat_<VTYPE>ScaleAdd(
    SLCArray_pt dst, SLCArray_cpt src0, const SLC_<VTYPE>_t* scale0,
    SLCArray_cpt src1, const SLC_<VTYPE>_t* scale1);

/**
\brief dst = src * scale
*/
void SLCMat_<VTYPE>Scale(
    SLCArray_pt dst, SLCArray_cpt src, const SLC_<VTYPE>_t* scale);

/**
\brief dst = src0 * src1
\param dst [in,out] products of two matrices. 
    dst must be allocated with correct size in advance.
\param src0 [in]
\param src1 [in]
\param work [in,out] working matrix to fill with transpose of dst.
*/
void SLCMat_<VTYPE>Multiply(
    SLCArray_pt dst, SLCArray_cpt src0, SLCArray_cpt src1,
    SLCArray_pt work);

/**
\brief dst = transpose of src
\param dst [in,out] transpose of src.
\param src [in]
*/
void SLCMat_<VTYPE>Transpose(SLCArray_pt dst, SLCArray_cpt src);

/**
\brief dst = transposed conjugate of src
\param dst [in,out] transposed conjugate of src
\param src [in]
*/
void SLCMat_<VTYPE>TransConj(SLCArray_pt dst, SLCArray_cpt src);

/**
\brief dst = invese of src.
\param dst [in,out] inverse of src
\param src [in]
\param work [in,out] holds a working matrix during Gaussian elimination.
    Its row count is equal to src row count. Its column count is twice of
    src column count.
*/
SLC_errno_t SLCMat_<VTYPE>Inv(
    SLCArray_pt dst, SLCArray_cpt src, SLCArray_pt work);
#pragma endregion <VTYPE>_BASIC_MATRIX_OPERATIONS
```
## Constant matrix
```
#pragma region <VTYPE>_CONSTANT_MATRIX
/**
\brief fill dst with a zero matrix.
\param dst [in,out] A matrix to fill with zero.
    dst must be allocated in advance.
*/
void SLCMat_<VTYPE>Zero(SLCArray_pt dst);

/**
\brief fill dst with an identity matrix
\param dst [in,out] A matrix to fill with identity matrix.
    dst must be allocated as a square  matrix in advance.
*/
void SLCMat_<VTYPE>Identity(SLCArray_pt dst);
#pragma endregion <VTYPE>_CONSTANT_MATRIX
```
## Linear equation solver
```
#pragma region <VTYPE>_LINEAR_EQUATION_SOLVER
// --- linear equation solvers ---
// solve fully determined linear equation
// left * dst = right, where left and right are known matrices.
// dst is the unknown solution.
// work is a matrix for Gaussian elimination and back assignment.
/**
\brief Solve a fully determined linear equation; left * dst = right
\param dst [out] unknown solution matrix
\param left [in] known matrix of LHS.
\param right [in] known matrix of RHS.
\param work [in] working matrix
*/
SLC_errno_t SLCMat_<VTYPE>Solve(SLCArray_pt dst, SLCArray_cpt left,
    SLCArray_cpt right, SLCArray_pt work);

/**
\brief Solve overly determined linear equation with an easy API
    which hides working matrix set.
\param dst [out] unknown solution matrix
\param left [in] known matrix of LHS.
\param right [in] known matrix of RHS.
*/
SLC_errno_t SLCMat_<VTYPE>EasySolveOd(
    SLCArray_pt dst, SLCArray_cpt left, SLCArray_cpt right);

/**
\brief Solve overly determined linear equation with an explicitly defined
    working matrix set. It is a little quicker than the easy version.
\param dst [out] unknown solution matrix
\param left [in] known matrix of LHS.
\param right [in] known matrix of RHS.
\param workSet [in] working matrix set
*/
SLC_errno_t SLCMat_<VTYPE>SolveOd(
    SLCArray_pt dst, SLCArray_cpt left, SLCArray_cpt right,
    SLCMat_LmsSolverMatSet_pt workSet);
#pragma endregion <VTYPE>_LINEAR_EQUATION_SOLVER
```
## QR decomposition
```
#pragma region <VTYPE>_QR_DECOMPOSITION
SLC_errno_t SLCMat_<VTYPE>Qrd(SLCArray_pt dst, SLCArray_pt src);
#pragma endregion <VTYPE>_QR_DECOMPOSITION
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _01MATH_MINILA_H */
```
