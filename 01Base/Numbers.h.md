# Control
```
{
    "OUT": "../include/SLC/Numbers.h",
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
## File header and includes
```
/*
\verbatim
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

File description
File: Numbers.h
Description:
    * Base number types and their small size arrays
    * Redeclarations of elementary math functions
    * Small utility operations of numbers

Revision history
Rev.     Date   Author  Description
00.00.00 231028 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
\endverbatim
*/
#if !defined(_01BASE_NUMBERS_H)
#define _01BASE_NUMBERS_H
#include <stdint.h>
#include <complex.h>
#include <stdbool.h>
#include <math.h>
```
## Base numbers and small arrays
```
#pragma region builtin_type_redefinitions
typedef int8_t          SLCI8_t;
typedef int16_t         SLCI16_t;
typedef int32_t         SLCI32_t;
typedef int64_t         SLCI64_t;
typedef float           SLCR32_t;
typedef double          SLCR64_t;
typedef float complex   SLCC64_t;
typedef double complex  SLCC128_t;
typedef bool            SLCBool_t;
typedef void*           SLCPtr_t;
#pragma endregion builtin_type_redefinitions

#pragma region two_element_arrays
typedef int8_t          SLC2I8_t[2];
typedef int16_t         SLC2I16_t[2];
typedef int32_t         SLC2I32_t[2];
typedef int64_t         SLC2I64_t[2];
typedef float           SLC2R32_t[2];
typedef double          SLC2R64_t[2];
typedef float complex   SLC2C64_t[2];
typedef double complex  SLC2C128_t[2];
typedef bool            SLC2Bool_t[2];
typedef void*           SLC2Ptr_t[2];
#pragma endregion two_element_arrays

#pragma region three_element_arrays
typedef int8_t          SLC3I8_t[3];
typedef int16_t         SLC3I16_t[3];
typedef int32_t         SLC3I32_t[3];
typedef int64_t         SLC3I64_t[3];
typedef float           SLC3R32_t[3];
typedef double          SLC3R64_t[3];
typedef float complex   SLC3C64_t[3];
typedef double complex  SLC3C128_t[3];
typedef bool            SLC3Bool_t[3];
typedef void*           SLC3Ptr_t[3];
#pragma endregion three_element_arrays

#pragma region four_element_arrays
typedef int8_t          SLC4I8_t[4];
typedef int16_t         SLC4I16_t[4];
typedef int32_t         SLC4I32_t[4];
typedef int64_t         SLC4I64_t[4];
typedef float           SLC4R32_t[4];
typedef double          SLC4R64_t[4];
typedef float complex   SLC4C64_t[4];
typedef double complex  SLC4C128_t[4];
typedef bool            SLC4Bool_t[4];
typedef void*           SLC4Ptr_t[4];
#pragma endregion four_element_arrays

#pragma region eight_element_arrays
typedef int8_t          SLC8I8_t[8];
typedef int16_t         SLC8I16_t[8];
typedef int32_t         SLC8I32_t[8];
typedef int64_t         SLC8I64_t[8];
typedef float           SLC8R32_t[8];
typedef double          SLC8R64_t[8];
typedef float complex   SLC8C64_t[8];
typedef double complex  SLC8C128_t[8];
typedef bool            SLC8Bool_t[8];
typedef void*           SLC8Ptr_t[8];
#pragma endregion eight_element_arrays

#pragma region sixteen_element_arrays
typedef int8_t          SLC16I8_t[16];
typedef int16_t         SLC16I16_t[16];
typedef int32_t         SLC16I32_t[16];
typedef int64_t         SLC16I64_t[16];
typedef float           SLC16R32_t[16];
typedef double          SLC16R64_t[16];
typedef float complex   SLC16C64_t[16];
typedef double complex  SLC16C128_t[16];
typedef bool            SLC16Bool_t[16];
typedef void*           SLC16Ptr_t[16];
#pragma endregion sixteen_element_arrays
```
## Elementary math functions
```
#pragma region elementary_math_functions
#define SLCR32_M_PI         (4.0f * atanf(1.0f))
#define SLCR64_M_PI         (4.0f * atan(1.0f))
#define SLCR32DEG2RAD(_deg) (SLCR32_M_PI * _deg / 180.0f)
#define SLCR64DEG2RAD(_deg) (SLCR64_M_PI * _deg / 180.0)
#define SLCR32COS(_a)       cosf(_a)
#define SLCR64COS(_a)       cos(_a)
#define SLCC64COS(_a)       ccosf(_a)
#define SLCC128COS(_a)      ccos(_a)
#define SLCR32SIN(_a)       sinf(_a)
#define SLCR64SIN(_a)       sin(_a)
#define SLCC64SIN(_a)       csinf(_a)
#define SLCC128SIN(_a)      csin(_a)
#define SLCR32TAN(_a)       tanf(_a)
#define SLCR64TAN(_a)       tan(_a)
#define SLCC64TAN(_a)       ctanf(_a)
#define SLCC128TAN(_a)      ctan(_a)
#define SLCR32ATAN(_a)      atanf(_a)
#define SLCR64ATAN(_a)      atan(_a)
#define SLCC64ATAN(_a)      catanf(_a)
#define SLCC128ATAN(_a)     catan(_a)
#define SLCR32ATAN2(_a, _b) atan2f(_a, _b)
#define SLCR64ATAN2(_a, _b) atan2(_a, _b)
#define SLCR32SQRT(_a)      sqrtf(_a)
#define SLCR64SQRT(_a)      sqrt(_a)
#define SLCC64SQRT(_a)      csqrtf(_a)
#define SLCC128SQRT(_a)     csqrt(_a)
#pragma endregion elementary_math_functions

#pragma region number_conversion_functions
#define SLCR32MIN(_a, _b)   fminf(_a, _b)
#define SLCR64MIN(_a, _b)   fmin(_a, _b)
#define SLCR32MAX(_a, _b)   fmaxf(_a, _b)
#define SLCR64MAX(_a, _b)   fmax(_a, _b)
#define SLCR32FLOOR(_a)     floorf(_a)
#define SLCR64FLOOR(_a)     floor(_a)
#define SLCR32CEIL(_a)      ceilf(_a)
#define SLCR64CEIL(_a)      ceil(_a)
#define SLCR32ABS(_a)       fabsf(_a)
#define SLCR64ABS(_a)       fabs(_a)
#define SLCC64ABS(_a)       cabsf(_a)
#define SLCC128ABS(_a)      cabs(_a)
#define SLCR32CONJ(_a)      (_a)
#define SLCR64CONJ(_a)      (_a)
#define SLCC64CONJ(_a)      conjf(_a)
#define SLCC128CONJ(_a)     conj(_a)
#define SLCR32FROMREAL(_a)  (_a)
#define SLCR64FROMREAL(_a)  (_a)
#define SLCC64FROMREAL(_a)  CMPLXF(_a, 0.0f)
#define SLCC128FROMREAL(_a) CMPLX(_a, 0.0)
#pragma endregion number_conversion_functions

#pragma region random_number_generator
#define SLCR32RAND          \
        ((SLCR32_t)(rand()-0.5f*RAND_MAX)/(0.5f*RAND_MAX))
#define SLCR64RAND          \
        ((SLCR64_t)(rand()-0.5*RAND_MAX)/(0.5*RAND_MAX ))
#define SLCC64RAND          CMPLXF(SLCR32RAND, SLCR32RAND)
#define SLCC128RAND         CMPLX(SLCR64RAND, SLCR64RAND)
#define SLCALIGN4(_n)       ((0 == (_n & 3)) ? _n : ((_n | 3) + 1))
#define SLCALIGN8(_n)       ((0 == (_n & 7)) ? _n : ((_n | 7) + 1))
#pragma endregion random_number_generator
```
## Small array operation
```
#define SLCARRAYSIZE(_a)    (sizeof(_a)/sizeof(_a[0]))
#define SLCPROD2(_a)        (_a)[0] * (_a)[1]
#define SLCPROD3(_a)        (_a)[0] * (_a)[1] * (_a)[2]
#define SLCPROD4(_a)        (_a)[0] * (_a)[1] * \
                            (_a)[2] * (_a)[3]
#define SLCCOPY2(_dst, _src)    (_dst)[0] = (_src)[0]; \
                                (_dst)[1] = (_src)[1]
#define SLCCOPY3(_dst, _src)    (_dst)[0] = (_src)[0]; \
                                (_dst)[1] = (_src)[1]; \
                                (_dst)[2] = (_src)[2]
#define SLCCOPY4(_dst, _src)    (_dst)[0] = (_src)[0]; \
                                (_dst)[1] = (_src)[1]; \
                                (_dst)[2] = (_src)[2]; \
                                (_dst)[3] = (_src)[3]
#define SLCCOPY8(_dst, _src)    SLCCOPY4(_dst, _src); \
                                (_dst)[4] = (_src)[4]; \
                                (_dst)[5] = (_src)[5]; \
                                (_dst)[6] = (_src)[6]; \
                                (_dst)[7] = (_src)[7]
#define SLCCOPY8(_dst, _src)    SLCCOPY8(_dst, _src); \
                                (_dst)[8] = (_src)[8]; \
                                (_dst)[9] = (_src)[9]; \
                                (_dst)[10] = (_src)[10]; \
                                (_dst)[11] = (_src)[11]; \
                                (_dst)[12] = (_src)[12]; \
                                (_dst)[13] = (_src)[13]; \
                                (_dst)[14] = (_src)[14]; \
                                (_dst)[15] = (_src)[15]
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _01BASE_NUMBERS_H */
```
