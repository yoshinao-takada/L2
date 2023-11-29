# Control
```
{
    "OUT": "MiniLA.c",
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
#include "SLC/MiniLA.h"
#include "SLC/MiniBLAS.h"
#include "SLC/NumbersCopy.h"
#include "SLC/ExIO.h"
#include "SLC/Log.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* enable debug print in SLCMat_<VTYPE>Inv()
 (<VTYPE>=[r32 | r64 | c64 | c128]) */
// #define DEBUG_INV

/* enable debug print in SLCMat_<VTYPE>Solve()
 (<VTYPE>=[r32 | r64 | c64 | c128]) */
// #define DEBUG_SOLVE

/* enable debug print in SLCMat_<VTYPE>SolveOD()
 (<VTYPE>=[r32 | r64 | c64 | c128]) */
// #define DEBUG_SOLVEOD
```
## Working matrix set for LSM overly determined equation solver
```
SLC_errno_t SLCMat_InitLmsSolverMatSet(
    SLCMat_LmsSolverMatSet_pt workSet, 
    SLCArray_cpt left, SLCArray_cpt right)
{
    const SLC_I16_t unitsize = SLCMat_UNIT_SIZE(left);
    assert(SLCMat_UNIT_SIZE(right) == unitsize);

    const SLC_4I16_t leftTSize = 
        { unitsize, left->Dimensions.I16[2], left->Dimensions.I16[1], 1 };
    const SLC_4I16_t leftTCLeftSize = 
        { unitsize, SLCMat_COLUMNS(left), SLCMat_COLUMNS(left), 1 };
    const SLC_4I16_t rightTSize = 
        { unitsize, right->Dimensions.I16[2], right->Dimensions.I16[1], 1 };
    const SLC_4I16_t leftTCRightSize = 
        { unitsize, SLCMat_COLUMNS(right), SLCMat_COLUMNS(left), 1 };
    const SLC_4I16_t workSize = 
        { unitsize, leftTCLeftSize[1] + leftTCRightSize[1],
         leftTCLeftSize[2], 1 };
    workSet->leftT = SLCArray_ALLOC(leftTSize);
    workSet->leftTC = SLCArray_ALLOC(leftTSize);
    workSet->leftTCLeft = SLCArray_ALLOC(leftTCLeftSize);
    workSet->rightT = SLCArray_ALLOC(rightTSize);
    workSet->leftTCRight = SLCArray_ALLOC(leftTCRightSize);
    workSet->work = SLCArray_ALLOC(workSize);
    SLC_errno_t err = EXIT_SUCCESS;
    if ((workSet->leftT == NULL) || (workSet->leftTC == NULL) ||
        (workSet->leftTCLeft == NULL) || (workSet->rightT == NULL) ||
        (workSet->leftTCRight == NULL) || (workSet->work == NULL))
    {
        err = ENOMEM;
        SLCMat_DestroyLmsSolverMatSet(workSet);
    }
    return err;
}

void SLCMat_DestroyLmsSolverMatSet(SLCMat_LmsSolverMatSet_pt workSet)
{
    assert(workSet);
    SLCArray_SAFE_FREE(workSet->leftT);
    SLCArray_SAFE_FREE(workSet->leftTC);
    SLCArray_SAFE_FREE(workSet->leftTCLeft);
    SLCArray_SAFE_FREE(workSet->rightT);
    SLCArray_SAFE_FREE(workSet->leftTCRight);
    SLCArray_SAFE_FREE(workSet->work);
}
```
# Generic
Generic definitions of base number specific functions, types, etc.
## Basic matrix operations
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_BASIC_MATRIX_OPERATIONS
```
### matrix-matrix addition
```
void SLCMat_<VTYPE>Add(
    SLCArray_pt dst, SLCArray_cpt src0, SLCArray_cpt src1)
{
    const SLC_<ITYPE>_t src0Rows = SLCMat_ROWS(src0);
    const SLC_<ITYPE>_t src0Columns = SLCMat_COLUMNS(src0);
    const SLC_<ITYPE>_t src1Rows = SLCMat_ROWS(src1);
    const SLC_<ITYPE>_t src1Columns = SLCMat_COLUMNS(src1);
    const SLC_<ITYPE>_t dstRows = SLCMat_ROWS(dst);
    const SLC_<ITYPE>_t dstColumns = SLCMat_COLUMNS(dst);
    assert(src0Rows == dstRows);
    assert(src0Columns == dstColumns);
    assert(src1Rows == dstRows);
    assert(src1Columns == dstColumns);
    const SLC_<VTYPE>_t* src0Elements = src0->Data.<VTYPE>;
    const SLC_<VTYPE>_t* src1Elements = src1->Data.<VTYPE>;
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    SLCBLAS_<VTYPE>Add(dstElements, src0Elements, src1Elements,
        dstRows * dstColumns);
}
```
### matrix-matrix addition with scaling factors for each matrix
```
void SLCMat_<VTYPE>ScaleAdd(
    SLCArray_pt dst, SLCArray_cpt src0, const SLC_<VTYPE>_t* scale0,
    SLCArray_cpt src1, const SLC_<VTYPE>_t* scale1)
{
    const SLC_<ITYPE>_t src0Rows = SLCMat_ROWS(src0);
    const SLC_<ITYPE>_t src0Columns = SLCMat_COLUMNS(src0);
    const SLC_<ITYPE>_t src1Rows = SLCMat_ROWS(src1);
    const SLC_<ITYPE>_t src1Columns = SLCMat_COLUMNS(src1);
    const SLC_<ITYPE>_t dstRows = SLCMat_ROWS(dst);
    const SLC_<ITYPE>_t dstColumns = SLCMat_COLUMNS(dst);
    assert(src0Rows == dstRows);
    assert(src0Columns == dstColumns);
    assert(src1Rows == dstRows);
    assert(src1Columns == dstColumns);
    const SLC_<VTYPE>_t* src0Elements = src0->Data.<VTYPE>;
    const SLC_<VTYPE>_t* src1Elements = src1->Data.<VTYPE>;
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    SLCBLAS_<VTYPE>ScaleAdd(dstElements,
        src0Elements, scale0,
        src1Elements, scale1,
        dstRows * dstColumns);
}
```
### matrix-scalar scaling
```
void SLCMat_<VTYPE>Scale(
    SLCArray_pt dst, SLCArray_cpt src, const SLC_<VTYPE>_t* scale)
{
    const SLC_<ITYPE>_t dstRows = SLCMat_ROWS(dst);
    const SLC_<ITYPE>_t dstColumns = SLCMat_COLUMNS(dst);
    const SLC_<ITYPE>_t srcRows = SLCMat_ROWS(src);
    const SLC_<ITYPE>_t srcColumns = SLCMat_COLUMNS(src);
    assert(dstRows == srcRows);
    assert(dstColumns == srcColumns);
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    const SLC_<VTYPE>_t* srcElements = src->Data.<VTYPE>;
    SLCBLAS_<VTYPE>Scale(
        dstElements, srcElements, scale, dstRows * dstColumns);
}
```
### matrix-matrix multiplication
```
void SLCMat_<VTYPE>Multiply(
    SLCArray_pt dst, SLCArray_cpt src0, SLCArray_cpt src1,
    SLCArray_pt work)
{
    const SLC_<ITYPE>_t dstRows = SLCMat_ROWS(dst);
    const SLC_<ITYPE>_t dstColumns = SLCMat_COLUMNS(dst);
    const SLC_<ITYPE>_t src0Rows = SLCMat_ROWS(src0);
    const SLC_<ITYPE>_t src0Columns = SLCMat_COLUMNS(src0);
    const SLC_<ITYPE>_t src1Rows = SLCMat_ROWS(src1);
    const SLC_<ITYPE>_t src1Columns = SLCMat_COLUMNS(src1);
    assert(dstRows == src0Rows);
    assert(dstColumns == src1Columns);
    assert(src0Columns == src1Rows);
    SLCMat_<VTYPE>Transpose(work, src1);
    const SLC_<VTYPE>_t* src0Elements = src0->Data.<VTYPE>;
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    for (SLC_<ITYPE>_t row = 0; row < dstRows; row++)
    {
        const SLC_<VTYPE>_t* workElements = work->Data.<VTYPE>;
        for (SLC_<ITYPE>_t column = 0; column < dstColumns; column++)
        {
            *dstElements++ = SLCBLAS_<VTYPE>ProductSum(
                src0Elements, workElements, src0Columns);
            workElements += src1Rows;
        }
        src0Elements += src0Columns;
    }
}
```
### transpose and transpose-conjugate
```
void SLCMat_<VTYPE>Transpose(SLCArray_pt dst, SLCArray_cpt src)
{
    const SLC_<ITYPE>_t srcRows = SLCMat_ROWS(src);
    const SLC_<ITYPE>_t srcColumns = SLCMat_COLUMNS(src);
    const SLC_<ITYPE>_t dstRows = SLCMat_ROWS(dst);
    const SLC_<ITYPE>_t dstColumns = SLCMat_COLUMNS(dst);
    assert(srcRows == dstColumns);
    assert(srcColumns == dstRows);
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    const SLC_<VTYPE>_t* srcElements = src->Data.<VTYPE>;
    for (SLC_<ITYPE>_t  srcRow = 0; srcRow < srcRows; srcRow++)
    {
        SLC_<VTYPE>Scatter(
            dstElements, dstColumns, srcElements, srcColumns);
        dstElements++;
        srcElements += srcColumns;
    }
}

void SLCMat_<VTYPE>TransConj(SLCArray_pt dst, SLCArray_cpt src)
{
    const SLC_<ITYPE>_t srcRows = SLCMat_ROWS(src);
    const SLC_<ITYPE>_t srcColumns = SLCMat_COLUMNS(src);
    const SLC_<ITYPE>_t dstRows = SLCMat_ROWS(dst);
    const SLC_<ITYPE>_t dstColumns = SLCMat_COLUMNS(dst);
    assert(srcRows == dstColumns);
    assert(srcColumns == dstRows);
    const SLC_<VTYPE>_t* srcElements = src->Data.<VTYPE>;
    for (SLC_<ITYPE>_t  srcRow = 0; srcRow < srcRows; srcRow++)
    {
        SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE> + srcRow;
        for (SLC_<ITYPE>_t srcColumn = 0; srcColumn < srcColumns;
             srcColumn++)
        {
            *dstElements = SLC_<VTYPE>_CONJ(srcElements[srcColumn]);
            dstElements += dstColumns;
        }
        srcElements += srcColumns;
    }
}
```
### matrix inversion utility functions
```
// unit numbers { 0, 1, -1, 2, complex(0,1), complex(0,-1)}
static const SLC_<VTYPE>_t <VTYPE>_UNITS[] = SLC_<VTYPE>_UNITS;

// copy LHS square matrix to the left half of the working matrix.
static void <VTYPE>CopyToLeftSquare(
    SLC_<VTYPE>_t* dst, SLC_<ITYPE>_t dstStride,
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t rows)
{
    for (SLC_<ITYPE>_t row = 0; row < rows; row++)
    {
        SLC_<VTYPE>Copy(dst, 1, src, 1, rows);
        dst += dstStride;
        src += rows;
    }
}

// fill the right half of the working matrix with an identify matrix
static void <VTYPE>PrepareRightHalf(
    SLC_<VTYPE>_t* dst, SLC_<ITYPE>_t rows, SLC_<ITYPE>_t dstStride)
{
    dst += rows;
    SLC_<ITYPE>_t columns = dstStride - rows;
    for (SLC_<ITYPE>_t row = 0; row < rows; row++, dst += dstStride)
    {
        // fill the row with 0
        SLC_<VTYPE>Copy(dst, 1, <VTYPE>_UNITS, 0, columns);
        // set diagonal element to 1
        dst[row] = <VTYPE>_UNITS[1];
    }
}

// copy the right half of the working matrix to a square matrix
static void <VTYPE>CopyFromRightHalf(
    SLC_<VTYPE>_t* dst, SLC_<ITYPE>_t dstRows,
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t src_stride)
{
    src+= dstRows; // point the beginning of the right half of the work matrix
    for (SLC_<ITYPE>_t row = 0; row < dstRows;
         row++, dst += dstRows, src += src_stride)
    {
        SLC_<VTYPE>Copy(dst, 1, src, 1, dstRows);
    }
}

// select the best pivot row
static SLC_<ITYPE>_t 
    <VTYPE>BestPivot(SLC_<VTYPE>_t* workRowHead, SLC_<ITYPE>_t row,
    SLC_<ITYPE>_t workRows, SLC_<ITYPE>_t workColumns)
{
    SLC_<RTYPE>_t pivotRelativeMaginitude = <RTYPE>_UNITS[2]; // = -1
    SLC_<ITYPE>_t 
        candidatePivotIndex = -1,
        leftPartRemaining = workRows - row;
    for (; row < workRows; row++, workRowHead += workColumns)
    {
        SLC_<RTYPE>_t pivotMagnitude = SLC_<VTYPE>_ABS(*workRowHead);
        SLC_<RTYPE>_t rowMagnitude = 
            SLCBLAS_<VTYPE>AbsSum(workRowHead, leftPartRemaining);
        SLC_<RTYPE>_t pivotRelativeMaginitude2 =
            pivotMagnitude / rowMagnitude;

        if ((pivotRelativeMaginitude2 < SLC_<VTYPE>_STDTOL) ||
                // pivotRelativeMaginitude2 is too small to accept
            (pivotRelativeMaginitude2 <= pivotRelativeMaginitude))
                // pivotRelativeMaginitude2 is 
                // NOT better than the current best
        { // candidatePivotIndex is NOT updated.
            continue;
        }

        // candidatePivotIndex is updated.
        pivotRelativeMaginitude = pivotRelativeMaginitude2;
        candidatePivotIndex = row;
    }
    return candidatePivotIndex;
}
```
### main body of matrix inversion
```
#if defined(_DEBUG)
#define DBG_PRINT_MAT(_parray, ...) if (SLCLog_Sink) \
{\
    fprintf(SLCLog_Sink, __VA_ARGS__); \
    SLCMat_<VTYPE>Print(SLCLog_Sink, "", _parray, ""); \
}
#else
#define DBG_PRINT_MAT(_parray, ...)
#endif /* _DEBUG */

#if defined(DEBUG_INV)
#define DBG_INV_PRINT_MAT(_parray, ...) \
    DBG_PRINT_MAT(_parray, __VA_ARGS__)
#else
#define DBG_INV_PRINT_MAT(_parray, ...)
#endif /* DEBUG_INV */

SLC_errno_t 
SLCMat_<VTYPE>Inv(SLCArray_pt dst, SLCArray_cpt src, SLCArray_pt work)
{
    const SLC_<ITYPE>_t srcRows = SLCMat_ROWS(src);
    const SLC_<ITYPE>_t workColumns = SLCMat_COLUMNS(work);
    assert(srcRows == SLCMat_COLUMNS(src));
    assert(srcRows == SLCMat_ROWS(dst));
    assert(srcRows == SLCMat_COLUMNS(dst));
    assert(srcRows == SLCMat_ROWS(work));
    assert((srcRows * 2) == workColumns);
    SLC_errno_t err = EXIT_SUCCESS;
    const SLC_<VTYPE>_t* srcElements = src->Data.<VTYPE>;
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    SLC_<VTYPE>_t* workElements = work->Data.<VTYPE>;
    do {
        // prepare working matrix
        <VTYPE>CopyToLeftSquare(
            workElements, workColumns, srcElements, srcRows);
        <VTYPE>PrepareRightHalf(workElements, srcRows, workColumns);

        // Gaussian elimination
        // the head element of the current pivot row
        SLC_<VTYPE>_t* workRowHead = workElements;
        // working length of current row basic operation
        SLC_<ITYPE>_t workRowLength = workColumns;
        for (SLC_<ITYPE>_t row = 0; row < srcRows; row++,
            workRowHead += (workColumns + 1), // move diagonal direction
            workRowLength--)
        {
            DBG_INV_PRINT_MAT(
                work, "row=%d, before pivot selection -- ", row);
            // Select the best pivot row
            SLC_<ITYPE>_t newPivotRow = <VTYPE>BestPivot(
                workRowHead, row, srcRows, workColumns);
            if (newPivotRow == -1)
            { // src matrix is singular.
                err = SLC_ESINGULAR;
                break;
            }
            if (newPivotRow != row)
            { // swap pivot row
                SLC_<VTYPE>_t* rowHeadToSwap = 
                workRowHead + (newPivotRow - row) * workColumns;
                SLC_<VTYPE>Swap(
                    workRowHead, 1, rowHeadToSwap, 1, workRowLength);
            }

            DBG_INV_PRINT_MAT(
                work, "row=%d, before normalizing pivot -- ", row);
            // Normalize pivot row
            SLC_<VTYPE>_t scale = <VTYPE>_UNITS[1] / *workRowHead;
            SLCBLAS_<VTYPE>ScaleAss(workRowHead, &scale, workRowLength);

            DBG_INV_PRINT_MAT(work, 
                "row=%d, before eliminating pivot column -- ", row);
            // Eliminate pivot column elements except the pivot element
            SLC_<VTYPE>_t* rowHeadToEliminate = workElements + row;
            for (SLC_<ITYPE>_t row2 = 0; row2 < srcRows; row2++,
                 rowHeadToEliminate += workColumns)
            {
                if (row == row2) continue; // skip pivot row to eliminate
                scale = -(*rowHeadToEliminate);
                SLCBLAS_<VTYPE>ScaleAddAss(rowHeadToEliminate,
                    workRowHead, &scale, workRowLength);
            }
        }

        DBG_INV_PRINT_MAT(work, "After whole Gaussian elimination -- ");
        if (err) continue; // src is singular
        // copy from work to dst
        <VTYPE>CopyFromRightHalf(
            dstElements, srcRows, workElements, workColumns);
        DBG_INV_PRINT_MAT(dst, "dst -- ");
    } while (0);
    return err;
}

#pragma endregion <VTYPE>_BASIC_MATRIX_OPERATIONS
```
## Constant matrix
```
#pragma region <VTYPE>_CONSTANT_MATRIX
void SLCMat_<VTYPE>Zero(SLCArray_pt dst)
{
    assert(sizeof(SLC_<VTYPE>_t) == SLCMat_UNIT_SIZE(dst));
    SLC_<ITYPE>_t count = SLCMat_ROWS(dst) * SLCMat_COLUMNS(dst);
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    SLC_<VTYPE>Copy(dstElements, 1, <VTYPE>_UNITS, 0, count);
}

// identity matrix
void SLCMat_<VTYPE>Identity(SLCArray_pt dst)
{
    SLC_<ITYPE>_t rows = SLCMat_ROWS(dst);
    SLC_<ITYPE>_t columns = SLCMat_COLUMNS(dst);
    assert(rows == columns);
    SLCMat_<VTYPE>Zero(dst);
    SLC_<ITYPE>_t diagonalStep = columns + 1;
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    SLC_<VTYPE>Copy(dstElements, diagonalStep, <VTYPE>_UNITS + 1, 0, rows);
}
#pragma endregion <VTYPE>_CONSTANT_MATRIX
```
## Linear equation solver utility functions
Backward assignmet after triangulate the matrix of fully determined
linear equation is described.
Considering a upper trianglular matrix and a multicolumn right hand side matrix.
Consequently a solution is also a multicolumn matrix.

$$\begin{equation}
\bold{\text{L}} = \begin{bmatrix}
1 & l_{12} & l_{13} & \cdots & l_{1N} \\
0 & 1 & l_{23} & \cdots & l_{2N} \\
\vdots & 0 & \ddots & & \vdots \\
0 & 0 & \cdots & 1 & l_{N-1,N}\\
0 & 0 & \cdots & 0 & 1
\end{bmatrix}\end{equation}$$

$$\begin{equation}\bold{\text{R}} = \begin{bmatrix}
r_{11} & r_{12} & \cdots & r_{1M} \\
r_{21} & r_{22} & \cdots & r_{2M} \\
\vdots & \vdots & \ddots & \vdots \\
r_{N-1,1} & r_{N-1,2} & \cdots & r_{N-1,M} \\
r_{N1} & r_{N2} & \cdots & r_{NM}
\end{bmatrix}
\end{equation}$$

The solution matrix $\bold{\text{X}}$ is
$$\begin{equation}
\bold{\text{X}} = \begin{bmatrix}
x_{11} & x_{12} & \cdots & x_{1M} \\
x_{21} & x_{22} & \cdots & x_{2M} \\
\vdots & \vdots & \ddots & \vdots \\
x_{N-1,1} & x_{N-1,2} & \cdots & x_{N-1,M} \\
x_{N1} & x_{N2} & \cdots & x_{NM}
\end{bmatrix}
\end{equation}$$
The fully determined linear equation is
$$\begin{equation}
\bold{\text{LX}} = \bold{\text{R}}
\end{equation}$$
Expanding the equation in line-by-line form and in backward order,
$$\begin{equation}\begin{matrix}
x_{N1} & = & r_{N1} \\
x_{N-1,1} + l_{N-1,N}x_{N1} & = & r_{N-1,1} \\
x_{N-2,1} + l_{N-2,N-1}x_{N-1,1} + l_{N-2,N}x_{N,1} &= & r_{N-2,1} \\
x_{N-3,1} + l_{N-3,N-2}x_{N-2,1} + l_{N-3,N-1}x_{N-1,1} + l_{N-3,N}x_{N1} & = & r_{N-3,1} \\
\cdots & = & \cdots \\
x_{21} + l_{23}x_{31} + l_{24}x_{41} + \cdots + l_{2,N-1}x_{N-1,1} + l_{2,N}x_{N1} &= & r_{21} \\
x_{11} + l_{12}x_{21} + l_{13}x_{31} + l_{14}x_{41} + \cdots + l_{1,N-1}x_{N-1,1} + l_{1N}x_{N1} &= & r_{11}
\end{matrix}\end{equation}$$
```
#pragma region <VTYPE>_LINEAR_EQUATION_SOLVER_UTILITY_FUNCTIONS
#if defined(DEBUG_SOLVE)
#define DBG_SOLVE_PRINT_MAT(_parray, ...) \
    DBG_PRINT_MAT(_parray, __VA_ARGS__)
#else
#define DBG_SOLVE_PRINT_MAT(_parray, ...)
#endif /* DEBUG_SOLVE */

static void <VTYPE>CopyRHS(
    SLC_<VTYPE>_t* dst, SLC_<ITYPE>_t dstStride,
    const SLC_<VTYPE>_t* src, SLC_<ITYPE>_t srcRows, SLC_<ITYPE>_t srcColumns
) {
    for (SLC_<ITYPE>_t row = 0; row < srcRows; row++, src+= srcColumns, dst += dstStride)
    {
        SLC_<VTYPE>Copy(dst, 1, src, 1, srcColumns);
    }
}

static void <VTYPE>AssignBackward(SLCArray_pt dst, SLCArray_cpt work)
{
    SLC_<ITYPE>_t dstRows = SLCMat_ROWS(dst);
    SLC_<ITYPE>_t dstColumns = SLCMat_COLUMNS(dst);
    SLC_<VTYPE>_t* dstElements = dst->Data.<VTYPE>;
    SLC_<ITYPE>_t workRows = SLCMat_ROWS(work);
    SLC_<ITYPE>_t workColumns = SLCMat_COLUMNS(work);
    const SLC_<VTYPE>_t
        *workElements = work->Data.<VTYPE>,
        *workLeftRowHead = workElements + workColumns * (workRows - 1),
        *workRightRowHead = workLeftRowHead + workRows;
    SLC_<VTYPE>_t *dstRowHead = dstElements + dstColumns * (dstRows - 1);
    for (SLC_<ITYPE>_t backward_index = 0, workRow = workRows - 1;
        backward_index < workRows;
        backward_index++,
        workRow--,
        workLeftRowHead -= workColumns,
        workRightRowHead -= workColumns,
        dstRowHead -= dstColumns)
    {
        // copy the most significant term
        SLC_<VTYPE>Copy(dstRowHead, 1, workRightRowHead, 1, dstColumns);
        for (SLC_<ITYPE>_t leftColumn = workRow + 1;
            leftColumn < workRows; leftColumn++)
        {
            for (SLC_<ITYPE>_t dstColumn = 0; dstColumn < dstColumns;
                 dstColumn++)
            {
                dstRowHead[dstColumn] -= workLeftRowHead[leftColumn] *
                    (dstElements + leftColumn * dstColumns)[dstColumn];
            }
        }
        DBG_SOLVE_PRINT_MAT(dst, "workRow = %d -- ", workRow)
    }
}
#pragma endregion <VTYPE>_LINEAR_EQUATION_SOLVER_UTILITY_FUNCTIONS
```
## Linear equation solver main body
```
#pragma region <VTYPE>_LINEAR_EQUATION_SOLVER_MAIN_BODY

SLC_errno_t SLCMat_<VTYPE>Solve(SLCArray_pt dst,
    SLCArray_cpt left, SLCArray_cpt right, SLCArray_pt work)
{
    SLC_<ITYPE>_t commonRows = SLCMat_ROWS(left);
    SLC_<ITYPE>_t leftColumns = SLCMat_COLUMNS(left);
    SLC_<ITYPE>_t rightColumns = SLCMat_COLUMNS(right);
    SLC_<ITYPE>_t workColumns = SLCMat_COLUMNS(work);
    assert(commonRows == leftColumns);
    assert(SLCMat_ROWS(dst) == commonRows);
    assert(SLCMat_COLUMNS(dst) == rightColumns); 
    assert(SLCMat_ROWS(right) == commonRows);
    assert(SLCMat_ROWS(work) == commonRows); 
    assert(workColumns == (leftColumns + SLCMat_COLUMNS(dst)));
    SLC_errno_t err = EXIT_SUCCESS;
    const SLC_<VTYPE>_t* leftElements = left->Data.<VTYPE>;
    const SLC_<VTYPE>_t* rightElements = right->Data.<VTYPE>;
    SLC_<VTYPE>_t* workElements = work->Data.<VTYPE>;
    do {
        // copy to work matrix
        <VTYPE>CopyToLeftSquare(
            workElements, workColumns, leftElements, commonRows);
        <VTYPE>CopyRHS(
            workElements + leftColumns, workColumns,
            rightElements, commonRows, rightColumns);
        
        // Upper triangulation
        SLC_<VTYPE>_t* workRowHead = workElements;
        for (SLC_<ITYPE>_t row = 0, work_row_length = workColumns;
            row < commonRows;
            row++, work_row_length--, workRowHead += (workColumns + 1))
        {
            DBG_SOLVE_PRINT_MAT(work,
                "row = %d, work_row_length = %d\n", row, work_row_length);
            // select the best pivot row
            SLC_<ITYPE>_t pivotRow = <VTYPE>BestPivot(
                workRowHead, row, commonRows, workColumns);
            if (pivotRow == -1)
            {
                err = SLC_ESINGULAR;
                break;
            }
            if (pivotRow != row)
            {
                SLC_<VTYPE>Swap(workRowHead, 1,
                    workRowHead + (pivotRow - row) * workColumns, 1,
                    work_row_length);
            }
            DBG_SOLVE_PRINT_MAT(work, "Before normalizing pivot row -- ");
            // normalize the pivot row
            SLC_<VTYPE>_t scale = <VTYPE>_UNITS[1] / *workRowHead;
            *workRowHead = <VTYPE>_UNITS[1];
            SLCBLAS_<VTYPE>ScaleAss(workRowHead + 1, &scale, 
                work_row_length - 1);

            DBG_SOLVE_PRINT_MAT(work,
                "Before eliminating pivot column -- ");
            // eliminate pivot column elements beneath the pivot row
            if ((row + 1) == commonRows) continue;
            SLC_<VTYPE>_t* rowHeadToEliminate = workRowHead + workColumns;
            for (SLC_<ITYPE>_t row2 = row + 1; row2 < commonRows;
                row2++, rowHeadToEliminate += workColumns)
            {
                scale = -(*rowHeadToEliminate);
                *rowHeadToEliminate = <VTYPE>_UNITS[0];
                SLCBLAS_<VTYPE>ScaleAddAss(rowHeadToEliminate + 1,
                    workRowHead + 1, &scale, work_row_length - 1);
            }
        }

        DBG_SOLVE_PRINT_MAT(work, "After whole Gaussian elimination -- ");
        if (err) continue; // left is singular.
        // backward assignment
        <VTYPE>AssignBackward(dst, work);
    } while (0);
    return err;
}
#pragma endregion <VTYPE>_LINEAR_EQUATION_SOLVER_MAIN_BODY
```
## LMS solver for overly determined linear equations
```
#pragma region <VTYPE>_LINEAR_EQUATION_SOLVER
#if defined(DEBUG_SOLVEOD)
#define DBG_SOLVEOD_PRINT_MAT(_mat, ...) \
    DBG_PRINT_MAT(_parray, __VA_ARGS__)
#else
#define DBG_SOLVEOD_PRINT_MAT(_mat, ...)
#endif /* DEBUG_SOLVEOD */

SLC_errno_t SLCMat_<VTYPE>EasySolveOd(SLCArray_pt dst, SLCArray_cpt left,
    SLCArray_cpt right)
{
    SLCMat_LmsSolverMatSet_t objWorkSet;
    SLCMat_InitLmsSolverMatSet(&objWorkSet, left, right);
    SLC_errno_t err = 
        SLCMat_<VTYPE>SolveOd(dst, left, right, &objWorkSet);
    SLCMat_DestroyLmsSolverMatSet(&objWorkSet);
    return err;
}

SLC_errno_t SLCMat_<VTYPE>SolveOd(SLCArray_pt dst, SLCArray_cpt left,
    SLCArray_cpt right, SLCMat_LmsSolverMatSet_pt workSet)
{
    SLC_errno_t err = EXIT_SUCCESS;
    assert(SLCMat_UNIT_SIZE(dst) == SLCMat_UNIT_SIZE(left));
    assert(SLCMat_COLUMNS(left) == SLCMat_ROWS(dst));
    assert(SLCMat_COLUMNS(right) == SLCMat_COLUMNS(dst));
    SLCMat_<VTYPE>TransConj(workSet->leftTC, left);
    SLCMat_<VTYPE>Multiply(workSet->leftTCLeft, workSet->leftTC, left,
        workSet->leftT);
    SLCMat_<VTYPE>Multiply(workSet->leftTCRight, workSet->leftTC, right,
        workSet->rightT);
    DBG_SOLVEOD_PRINT_MAT(workSet->leftTC, "leftTC -- ");
    DBG_SOLVEOD_PRINT_MAT(workSet->leftTCLeft, "leftTCLeft -- ");
    DBG_SOLVEOD_PRINT_MAT(workSet->leftTCRight, "leftTCRight -- ");
    err = SLCMat_<VTYPE>Solve(dst, workSet->leftTCLeft,
        workSet->leftTCRight, workSet->work);
    return err;
}

#pragma endregion <VTYPE>_LINEAR_EQUATION_SOLVER
```
## QR Decomposition
```
```
## Print a Matrix
```
void SLCMat_<VTYPE>Print(
    FILE* out, const char* header, SLCArray_cpt mat, const char* footer)
{
    fprintf(out, "%s: rows=%d, columns=%d\n", header,
        mat->Dimensions.I16[2], mat->Dimensions.I16[1]);
    const SLC_<VTYPE>_t *e = mat->Data.<VTYPE>;
    for (SLC_I16_t row = 0; row < mat->Dimensions.I16[2];
        row++, e += mat->Dimensions.I16[1])
    {
        SLC_<VTYPE>_PRINTVN(out, e, mat->Dimensions.I16[1]);
    }
    fprintf(out, footer);
}
#undef DBG_PRINT_MAT
#undef DBG_INV_PRINT_MAT
#undef DBG_SOLVE_PRINT_MAT
#undef DBG_SOLVEOD_PRINT_MAT
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
