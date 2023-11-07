# Control
```
{
    "OUT": "../include/SLC/ExIO.h",
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
File: ExIO.h
Description: Extended I/O macros

Revision history
Rev.     Date   Author  Description
00.00.00 231030 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_01BASE_EXIO_H)
#define _01BASE_EXIO_H
#include "SLC/Numbers.h"
#include <stdio.h>

// scalar output
#define SLC_R32_PRINT(_out, _x) fprintf(_out, "%f", _x)
#define SLC_R64_PRINT(_out, _x) fprintf(_out, "%f", _x)
#define SLC_C64_PRINT(_out, _x) \
    fprintf(_out, "%f, %f", crealf(_x), cimagf(_x))
#define SLC_C128_PRINT(_out, _x) \
    fprintf(_out, "%f, %f", creal(_x), cimag(_x))
#define SLC_NEWLINE(_out) fprintf(_out, "\n")
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_macros
/**
\brief print a raw number array
\param _out [in] output FILE*
\param _x [in] the pointer to the head of the number array
\param _count [in] the element count of the array
*/
#define SLC_<VTYPE>_PRINTV(_out, _x, _count) \
    for (SLC_<ITYPE>_t _index = 0; _index < _count; _index++) \
    { \
        fprintf(_out, (_index == 0) ? "" : ", "); \
        SLC_<VTYPE>_PRINT(_out, _x[_index]); \
    }

/**
\brief print newline after SLC_<VTYPE>_PRINTV().
*/
#define SLC_<VTYPE>_PRINTVN(_out, _x, _count) \
    SLC_<VTYPE>_PRINTV(_out, _x, _count); SLC_NEWLINE(_out);
#pragma endregion <VTYPE>_macros
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _01BASE_EXIO_H */
```
