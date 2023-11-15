# Control
```
{
    "OUT": "NLSL.c",
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
File: NLSL.c
Description: Nonlinear equation solver implementation

Revision history
Rev.     Date   Author  Description
00.00.00 231104 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/NLSL.h"
#include "SLC/Log.h"
#include "SLC/NumbersCopy.h"
#include "SLC/MiniBLAS.h"
#include "SLC/MiniLA.h"
#include "SLC/errno.h"
#include "SLC/ExIO.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <errno.h>

```
# Generic
Generic definitions of base number specific functions, types, etc.
## Internal Declarations
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_INTERNAL_DECLARATIONS
/**
\brief Declare type of trace functions for Gauss-Newton solvers.
*/
typedef void (*GnSolver_<VTYPE>Trace_f)(SLCGnSolver_<VTYPE>_cpt solver);

/**
\brief Discriminate where the solver is converged or not.
*/
typedef bool (*GnSolver_<VTYPE>Converged_f)(SLCGnSlver_<VTYPE>_cpt solver);

/**
\brief Full definition of Gauss-Newton solver struct
*/
struct SLCGnSolver_<VTYPE>
{
    // Configuration parameters
    SLCGnSolver_<VTYPE>Conf_t conf;

    // working matrices
    SLCArray_pt
        x, // X column vector
        deltaX, // == x_new - x; i.e. x_new = x + delta_x.
        y, negy, // Y and -Y column vectors
        jcolbuf, // Jacobian column buffer
        j; // Jacobian
    SLCMat_LmsSolverMatSet_t wkset;

    // operation state
    SLCNlsl_State_t state;

    // iteration counter
    SLC_<ITYPE>_t iter;

    // Convergence parameters
    // L1 norm of deltaX and y
    SLC_<RTYPE>_t normDx, normY;

    // convergence discriminator
    GnSolver_<VTYPE>Converged_f convDisc;

    // trace functions
    GnSolver_<VTYPE>Trace_f
        traceXY, // trace x and y
        traceJ, // trace Jacobian
        traceNormDxY; // trace deltaX and y
};
#pragma endregion <VTYPE>_INTERNAL_DECLARATIONS
```
## Trace Functions and Convergence Discriminators
```
#pragma region TRACE_FUNC_AND_CONV_DISC
#pragma endregion TRACE_FUNC_AND_CONV_DISC
```
## Initializer and Momory Management
```
#pragmaa region INITIALIZER
#pragmaa endregion INITIALIZER
```
## Public Functions
```
#pragma region PUBLIC_FUNCTIONS
#pragma endregion PUBLIC_FUNCTIONS
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
