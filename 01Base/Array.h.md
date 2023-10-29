# Control
```
{
    "OUT": "../include/SLC/Array.h",
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
## File header and array struct definition
```
/*
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

File description
File: Array.h
Description: Generic array similar to c++ std::vector<T>

Revision history
Rev.     Date   Author  Description
00.00.00 231028 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_01BASE_ARRAY_H)
#define _01BASE_ARRAY_H
#include "SLC/Numbers.h"
#include <malloc.h>
#include <alloca.h>

#pragma region struct_definition
/**
\brief control block of multidimensional array
*/
typedef union {
    SLC4I16_t   i16;
    SLC2I32_t   i32;
    SLCI64_t    i64;
    SLC8I8_t    i8;
} SLCArrayControl_t, *SLCPArrayControl_t;
typedef const SLCArrayControl_t *SLCPCArrayControl_t;

/**
\brief data buffer header of multidimensional array
*/
typedef uinion {
    const void* cvptr;
    SLCPtr_t    ptr;
    SLCPtr_t*   pptr;
    SLCI8_t*    i8;
    SLCI16_t*   i16;
    SLCI32_t*   i32;
    SLCI64_t*   i64;
    SLCR32_t*   r32;
    SLCR64_t*   r64;
    SLCC64_t*   c64;
    SLCC128_t*  c128;
} SLCArrayData_t, *SLCPArrayData_t;
typedef const SLCArrayData_t    *SLCPCArrayData_t;

/**
\brief multidimensional array of arbitrary base number type
*/
typedef struct {
    SLCArrayControl_t   cont;
    SLCArrayData_t      data;
} SLCArray_t, *SLCPArray_t;
typedef const SLCArray_t *SLCPCArray_t;
#pragma endregion struct_definition
```
## Array initializers
```
#pragma region array_initializers
/**
\brief initialize an allocated memory block as an array.
\param ptr [in] allocated memory block
\param size [in] multidimensional array size<br/>
[0]:unit size
[1]:1st dimension
[2]:2dn dimension
[3]:3rd dimension
\return ptr
*/
SLCPArray_t SLCArray_Init(SLCPArray_t ptr, const SLC4I16_t size);

/**
\brief a variable for debugging memory allocation for SLCArray_t.
It holds byte count of the latest memory allocation.
*/
#if !defined(_01BASE_ARRAY_C)
extern
#endif
SLCI64_t SLCArray_LatestAllocated;

#define SLCArray_ALLOC(_size) SLCArray_Init( \
    (SLCPArray_t)malloc( \
        SLCArray_LatestAllocated = \
        SLCALIGN8(SLCPROD4(_size) + sizeof(SLCArray_t))), \
        _size)

#define SLCArray_ALLOCA(_size) SLCArray_Init( \
    (SLCPArray_t)malloca( \
        SLCArray_LatestAllocated = \
        SLCALIGN8(SLCPROD4(_size) + sizeof(SLCArray_t))), \
        _size)

/**
\brief safety wrapper of free() preventing from double free.
\param _a [in,out] a pointer to an SLCArray_t object.
*/
#define SLCArray_SAFEFREE(_a)   if (_a) { free(_a); _a = NULL; }
#pragma endregion array_initializers
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _01BASE_ARRAY_H */
```
