# Control
```
{
    "OUT": "NLSLUT.c",
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
File: NLSLUT.c
Description: Test functions for NLSL.c (Continuous nonlinear equation
    solver)

Revision history
Rev.     Date   Author  Description
00.00.00 231104 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Log.h"
#include "SLC/MiniBLAS.h"
#include "SLC/MiniLA.h"
#include "SLC/NLSL.h"
#include <stdlib.h>
#include <stdio.h>
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_functions
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
SLC_errno_t NLSLUT()
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
