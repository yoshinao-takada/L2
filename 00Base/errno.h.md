# Control
```
{
    "OUT": "../include/SLC/errno.h",
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
File: errno.h
Description: error numbers specific to SLC library

Revision history
Rev.     Date   Author  Description
00.00.00 231030 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_00BASE_ERRNO_H)
#define _00BASE_ERRNO_H
#include "SLC/Numbers.h"

typedef SLC_I32_t SLC_errno_t;
#define SLC_ESINGULAR   0x10000 /* matrix is near singular */
#define SLC_ENOCONV     0x10001 /* not converged within iteration limit */
#define SLC_EMATSIZE    0x10002 /* Matrix size mismatch */
#define SLC_EINVAL      0x10003 /* Invalid operation (usually in objective function or Jacobian) */
#define SLC_EVALMISMATCH    0x10004 /* value mismatch */
#define SLC_EDIVBY0     0x10005 /* divide by 0 error */
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _00BASE_ERRNO_H */
```
