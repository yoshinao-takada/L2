# Control
```
{
    "OUT": "../include/SLC/NLSL.h",
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
File: NLSL.h
Description: Nonlinear equation solver header file

Revision history
Rev.     Date   Author  Description
00.00.00 231115 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_01MATH_NLSL_H)
#define _01MATH_NLSL_H
#include "SLC/Numbers.h"
#include "SLC/NumbersCopy.h"
#include "SLC/errno.h"
#include <stdio.h>

// The nonlinear solvers are very simple statemachine controlled by
// a state variable.
typedef enum {
    SLCNlsl_State_CREATED, // created but not initialized
    SLCNlsl_State_INITIALIZED, // just after initialized
    SLCNlsl_State_RUNNING, // running execution
    SLCNlsl_State_ITER_LIMIT, // stopped by iteration limit
    SLCNlsl_State_DX_CONVERGED, // stopped by convergence of normDx
    SLCNlsl_State_Y_CONVERGED, // stopped by convergence of normY
    SLCNlsl_State_BOTH_CONVERGED, 
        // stopped by convergence of both of normDX and normY
    SLCNlsl_State_ERR_ABORT, // stopped by error in objective or Jacobian
} SLCNlsl_State_t;

// Convergence conditions of solvers.
typedef enum {
    SLCNlsl_ConvergencCondition_DX = 1, // x satisfy criterion
    SLCNlsl_ConvergencCondition_Y = 2, // y satisfy criterion
    SLCNlsl_ConvergencCondition_BOTH = 3, // both of x and y satisfy criteria
} SLCNlsl_ConvergenceCondition_t;
```
# Generic
Generic definitions of base number specific functions, types, etc.
## Type Definitions
```
#pragma region <VTYPE>_functions
#pragma region <VTYPE>_TYPE_DEFINITIONS
/**
\brief Function pointer type definition of generalized 
    vector-vector function
\param y [out] dependent variable
\param cy [in] vector dimension of y
\param x [in] independent variable
\param cx [in] vector dimension of x
\param context [in,out] is any data type holding
    constant parameters and  common work area.
*/
typedef SLC_errno_t (*SLCNlsl_<VTYPE>Gvv_f)
(
    SLC_<VTYPE>_t* y, SLC_<ITYPE>_t cy,
    SLC_<VTYPE>_t* x, SLC_<ITYPE>_t cx,
    void* context
);

/**
\brief Base type of configuration struct of all nonlinear solver types
*/
typedef struct
{
    FILE* TraceOut; //!< Trace output stream
    SLC_<ITYPE>_t Cx; // !< Dimension of independent variable vector
    SLC_<ITYPE>_t Cy; // !< Dimension of dependent variable vector
    SLC_<ITYPE>_t MaxIter; // !< Maximum iteration count
    /*!
    \brief Convergence condition descriptor
    */
    SLCNlsl_ConvergenceCondition_t ConvergenceCondition;
    SLC_<VTYPE>_t *XInitial; //!< Initial value of x
    SLC_<RTYPE>_t NormDxMax; //!< Convergence criteria of delta-X
    SLC_<RTYPE>_t NormYMax; // !< Convergence criteria of Y
    SLCNlsl_<VTYPE>Gvv_f Objective; // !< Objective function
    void* Context; // !< Context of objective and Jacobian
}
SLCNlsl_<VTYPE>Conf_t, *SLCNlsl_<VTYPE>Conf_pt;
typedef const SLCNlsl_<VTYPE>Conf_t *SLCNlsl_<VTYPE>Conf_cpt;

/**
\brief Configuration struct of Gauss-Newton nonlinear solver type
*/
typedef struct
{
    SLCNlsl_<VTYPE>Conf_t Base;
    SLCNlsl_<VTYPE>Gvv_f* Jacobian;
}
SLCGnSolver_<VTYPE>Conf_t, *SLCGnSolver_<VTYPE>Conf_pt;
typedef const SLCGnSolver_<VTYPE>Conf_t *SLCGnSolver_<VTYPE>Conf_cpt;

typedef struct SLCGnSolver_<VTYPE> SLCGnSolver_<VTYPE>_t;
typedef SLCGnSolver_<VTYPE>_t *SLCGnSolver_<VTYPE>_pt;
typedef const SLCGnSolver_<VTYPE>_t *SLCGnSolver_<VTYPE>_cpt;
#pragma endregion <VTYPE>_TYPE_DEFINITIONS
```
## Math Operations
```
/**
\brief Create a new instance of a Gauss-Newton solver.
\param cx [in] dimension of independent variable vector of objective
\param cy [in] dimension of dependent variable vector of objective
*/
SLCGnSolver_<VTYPE>_pt
    SLCGnSolver_<VTYPE>New(SLC_<ITYPE>_t cx, SLC_<ITYPE>_t cy);

/**
\brief Delete an existing instance of a Gauss-Newton solver.
\param ppsolver [in,out] pointer-pointer to the instance.
*/
void SLCGnSolver_<VTYPE>Delete(SLCGnSolver_<VTYPE>_pt* ppsolver);

/**
\brief Retrieve a configuration struct of a Gauss-Newton solver.
\param solver [in] Pointer to the solver
\return the configration struct pointer.
*/
SLCGnSolver_<VTYPE>Conf_pt 
    SLCGnSolver_<VTYPE>Conf(SLCGnSolver_<VTYPE>_pt solver);

/**
\brief The initializer must be called after setting configuration
    parameters.
\param solver [in] Pointer to the solver
\return error status
*/
SLC_errno_t
    SLCGnSolver_<VTYPE>Init(SLCGnSolver_<VTYPE>_pt solver);

/**
\brief Solve a nonlinear equation.
\param solver [in] Pointer to the solver
\return error status
*/
SLC_errno_t
    SLCGnSolver_<VTYPE>Execute(SLCGnSolver_<VTYPE>_pt solver);

/**
\brief Retrieve the internal X vector of solver
\param solver [in] Pointer to the solver
\return pointer to the 1st element of the raw array of independent
    variable vector.
*/
const SLC_<VTYPE>_t* SLCGnSolver_<VTYPE>X(SLCGnSolver_<VTYPE>_cpt solver);

/**
\brief Retrieve the internal Y vector of solver
\param solver [in] Pointer to the solver
\return pointer to the 1st element of the raw array of independent
    variable vector.
*/
const SLC_<VTYPE>_t* SLCGnSolver_<VTYPE>Y(SLCGnSolver_<VTYPE>_cpt solver);

/**
\brief Retrieve the L1 norm of delta-X in current iteration.
\param solver [in] Pointer to the solver
\return L1 norm of delta-X
*/
SLC_<RTYPE>_t SLCGnSolver_<VTYPE>NormDx(SLCGnSolver_<VTYPE>_cpt solver);

/**
\brief Retrieve the L1 norm of Y in current interation.
\param solver [in] Pointer to the solver
\return L1 norm of Y
*/
SLC_<RTYPE>_t SLCGnSolver_<VTYPE>NormY(SLCGnSolver_<VTYPE>_cpt solver);
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _01MATH_NLSL_H */
```