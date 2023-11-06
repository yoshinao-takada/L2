# Control
```
{
    "OUT": "00BaseUT.c",
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
File: 00BaseUT.c
Description: Test harness for functions and macros defined in 00Base

Revision history
Rev.     Date   Author  Description
00.00.00 231106 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Log.h"
#include <stdlib.h>

SLC_errno_t NumbersUT();
SLC_errno_t NumbersCopyUT();
SLC_errno_t LogUT();
SLC_errno_t ArrayUT();
SLC_errno_t StopwatchUT();

int main()
{
    SLCLog_Sink = stderr;
    SLC_errno_t err = EXIT_SUCCESS;
    do 
    {
        if (EXIT_SUCCESS != (err = NumbersUT())) break;
        if (EXIT_SUCCESS != (err = NumbersCopyUT())) break;
        if (EXIT_SUCCESS != (err = LogUT())) break;
        if (EXIT_SUCCESS != (err = ArrayUT())) break;
        if (EXIT_SUCCESS != (err = StopwatchUT())) break;
    }
    while (0);
    SLCTest_END(err, __FILE__, __FUNCTION__, __LINE__);
    return err;
}
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
