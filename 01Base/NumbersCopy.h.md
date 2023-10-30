# Control
```
{
    "OUT": "../include/SLC/NumbersCopy.h",
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
File: NumbersCopy.h
Description: Functions to copy array of numbers in a raw memory block

Revision history
Rev.     Date   Author  Description
00.00.00 231030 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_01BASE_NUMBERSCOPY_H)
#define _01BASE_NUMBERSCOPY_H
#include "SLC/Numbers.h"
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_array_copy_functions
/*!
\brief copy multiple elements in an array to another array.
\param dst [in] destination array pointer
\param dststep [in] step of elements in dst
\param src [in] source array pointer
\param srcstep [in] step of elements in src
\param count [in] numbers of elements to copy
*/
void SLC<VTYPE>_copy(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count);

/*!
\brief swap multiple elements in two arrays
\param var0 [in] pointer to an array
\param step0 [in] step of elements in var0
\param var1 [in] pointer to another array
\param step1 [in] step of elements in var1
\param count [in] numbers of elements to swap
*/
void SLC<VTYPE>_swap(SLC<VTYPE>_t* var0, SLC<ITYPE>_t step0, SLC<VTYPE>_t* var1, SLC<ITYPE>_t step1, SLC<ITYPE>_t count);

/*!
\brief special type of copy with destination step is 1
\param dst [in] destination array pointer
\param src [in] source array pointer
\param srcstep [in] step of elements in src
\param count [in] numbers of elements to copy
*/
void SLC<VTYPE>_gather(SLC<VTYPE>_t* dst, const SLC<VTYPE>_t* src, SLC<ITYPE>_t srcstep, SLC<ITYPE>_t count);

/*!
\brief special type of copy with source step is 1
\param dst [in] destination array pointer
\param dststep [in] step of elements in dst
\param src [in] source array pointer
\param count [in] numbers of elements to copy
*/
void SLC<VTYPE>_scatter(SLC<VTYPE>_t* dst, SLC<ITYPE>_t dststep, const SLC<VTYPE>_t* src, SLC<ITYPE>_t count);
#pragma endregion <VALTYPE>_array_copy_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _01BASE_NUMBERSCOPY_H */
```
