# Control
```
{
    "OUT": "01MathUT.c",
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
00.00.00 231118 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Log.h"
#include <stdlib.h>
#include <stdio.h>
SLC_errno_t MiniBLASUT();
SLC_errno_t MiniLAUT();
SLC_errno_t NLSLUT();
SLC_errno_t GeomUT();
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
int main()
{
    SLC_errno_t err = EXIT_SUCCESS;
    SLCLog_Sink = stderr;
    do
    {
        SLCTest_RUN_ERROR_BREAK(
            &err, MiniBLASUT, __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(
            &err, MiniLAUT, __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(
            &err, NLSLUT, __FILE__, __FUNCTION__, __LINE__);
        SLCTest_RUN_ERROR_BREAK(
            &err, GeomUT, __FILE__, __FUNCTION__, __LINE__);
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
