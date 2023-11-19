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
#if !defined(_00BASE_NUMBERS_H)
#define _00BASE_NUMBERS_H
#include <stdint.h>
#include <complex.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
```
## Base numbers and small arrays
```
#pragma region builtin_type_redefinitions
typedef int8_t          SLC_I8_t;
typedef int16_t         SLC_I16_t;
typedef int32_t         SLC_I32_t;
typedef int64_t         SLC_I64_t;
typedef float           SLC_R32_t;
typedef double          SLC_R64_t;
typedef float complex   SLC_C64_t;
typedef double complex  SLC_C128_t;
typedef bool            SLC_Bool_t;
typedef void*           SLC_Void_pt;
typedef const void*     SLC_Void_cpt;
#pragma endregion builtin_type_redefinitions

#pragma region two_element_arrays
typedef int8_t          SLC_2I8_t[2];
typedef int16_t         SLC_2I16_t[2];
typedef int32_t         SLC_2I32_t[2];
typedef int64_t         SLC_2I64_t[2];
typedef float           SLC_2R32_t[2];
typedef double          SLC_2R64_t[2];
typedef float complex   SLC_2C64_t[2];
typedef double complex  SLC_2C128_t[2];
typedef bool            SLC_2Bool_t[2];
typedef void*           SLC_2Void_pt[2];
typedef const void*     SLC_2Void_cpt[2];
#pragma endregion two_element_arrays

#pragma region three_element_arrays
typedef int8_t          SLC_3I8_t[3];
typedef int16_t         SLC_3I16_t[3];
typedef int32_t         SLC_3I32_t[3];
typedef int64_t         SLC_3I64_t[3];
typedef float           SLC_3R32_t[3];
typedef double          SLC_3R64_t[3];
typedef float complex   SLC_3C64_t[3];
typedef double complex  SLC_3C128_t[3];
typedef bool            SLC_3Bool_t[3];
typedef void*           SLC_3Void_pt[3];
typedef const void*     SLC_3Void_cpt[3];
#pragma endregion three_element_arrays

#pragma region four_element_arrays
typedef int8_t          SLC_4I8_t[4];
typedef int16_t         SLC_4I16_t[4];
typedef int32_t         SLC_4I32_t[4];
typedef int64_t         SLC_4I64_t[4];
typedef float           SLC_4R32_t[4];
typedef double          SLC_4R64_t[4];
typedef float complex   SLC_4C64_t[4];
typedef double complex  SLC_4C128_t[4];
typedef bool            SLC_4Bool_t[4];
typedef void*           SLC_4Void_pt[4];
typedef const void*     SLC_4Void_cpt[4];
#pragma endregion four_element_arrays

#pragma region eight_element_arrays
typedef int8_t          SLC_8I8_t[8];
typedef int16_t         SLC_8I16_t[8];
typedef int32_t         SLC_8I32_t[8];
typedef int64_t         SLC_8I64_t[8];
typedef float           SLC_8R32_t[8];
typedef double          SLC_8R64_t[8];
typedef float complex   SLC_8C64_t[8];
typedef double complex  SLC_8C128_t[8];
typedef bool            SLC_8Bool_t[8];
typedef void*           SLC_8Void_pt[8];
typedef const void*     SLC_8Void_cpt[8];
#pragma endregion eight_element_arrays

#pragma region sixteen_element_arrays
typedef int8_t          SLC_16I8_t[16];
typedef int16_t         SLC_16I16_t[16];
typedef int32_t         SLC_16I32_t[16];
typedef int64_t         SLC_16I64_t[16];
typedef float           SLC_16R32_t[16];
typedef double          SLC_16R64_t[16];
typedef float complex   SLC_16C64_t[16];
typedef double complex  SLC_16C128_t[16];
typedef bool            SLC_16Bool_t[16];
typedef void*           SLC_16Void_pt[16];
typedef const void*     SLC_16Void_cpt[16];
#pragma endregion sixteen_element_arrays
```
## Elementary math functions
```
#pragma region elementary_math_functions
#define SLC_R32_M_PI            (4.0f * atanf(1.0f))
#define SLC_R64_M_PI            (4.0f * atan(1.0f))
#define SLC_R32_DEG2RAD(_deg)   (SLC_R32M_PI * _deg / 180.0f)
#define SLC_R64_DEG2RAD(_deg)   (SLC_R64M_PI * _deg / 180.0)
#define SLC_R32_COS(_a)         cosf(_a)
#define SLC_R64_COS(_a)         cos(_a)
#define SLC_C64_COS(_a)         ccosf(_a)
#define SLC_C128_COS(_a)        ccos(_a)
#define SLC_R32_SIN(_a)         sinf(_a)
#define SLC_R64_SIN(_a)         sin(_a)
#define SLC_C64_SIN(_a)         csinf(_a)
#define SLC_C128_SIN(_a)        csin(_a)
#define SLC_R32_TAN(_a)         tanf(_a)
#define SLC_R64_TAN(_a)         tan(_a)
#define SLC_C64_TAN(_a)         ctanf(_a)
#define SLC_C128_TAN(_a)        ctan(_a)
#define SLC_R32_ATAN(_a)        atanf(_a)
#define SLC_R64_ATAN(_a)        atan(_a)
#define SLC_C64_ATAN(_a)        catanf(_a)
#define SLC_C128_ATAN(_a)       catan(_a)
#define SLC_R32_ATAN2(_a, _b)   atan2f(_a, _b)
#define SLC_R64_ATAN2(_a, _b)   atan2(_a, _b)
#define SLC_R32_SQRT(_a)        sqrtf(_a)
#define SLC_R64_SQRT(_a)        sqrt(_a)
#define SLC_C64_SQRT(_a)        csqrtf(_a)
#define SLC_C128_SQRT(_a)       csqrt(_a)
#pragma endregion elementary_math_functions

#pragma region number_conversion_functions
#define SLC_R32_MIN(_a, _b)     fminf(_a, _b)
#define SLC_R64_MIN(_a, _b)     fmin(_a, _b)
#define SLC_R32_MAX(_a, _b)     fmaxf(_a, _b)
#define SLC_R64_MAX(_a, _b)     fmax(_a, _b)
#define SLC_R32_FLOOR(_a)       floorf(_a)
#define SLC_R64_FLOOR(_a)       floor(_a)
#define SLC_R32_CEIL(_a)        ceilf(_a)
#define SLC_R64_CEIL(_a)        ceil(_a)
#define SLC_R32_ABS(_a)         fabsf(_a)
#define SLC_R64_ABS(_a)         fabs(_a)
#define SLC_C64_ABS(_a)         cabsf(_a)
#define SLC_C128_ABS(_a)        cabs(_a)
#define SLC_R32_CONJ(_a)        (_a)
#define SLC_R64_CONJ(_a)        (_a)
#define SLC_C64_CONJ(_a)        conjf(_a)
#define SLC_C128_CONJ(_a)       conj(_a)
#define SLC_R32_FROM_REAL(_a)    (_a)
#define SLC_R64_FROM_REAL(_a)    (_a)
#define SLC_C64_FROM_REAL(_a)    CMPLXF(_a, 0.0f)
#define SLC_C128_FROM_REAL(_a)   CMPLX(_a, 0.0)
#pragma endregion number_conversion_functions

#pragma region random_number_generator
#define SLC_R32_RAND         \
        ((SLC_R32_t)(rand()-0.5f*RAND_MAX)/(0.5f*RAND_MAX))
#define SLC_R64_RAND         \
        ((SLC_R64_t)(rand()-0.5*RAND_MAX)/(0.5*RAND_MAX ))
#define SLC_C64_RAND         CMPLXF(SLC_R32RAND, SLC_R32RAND)
#define SLC_C128_RAND        CMPLX(SLC_R64RAND, SLC_R64RAND)
#define SLC_ALIGN4(_n)       ((0 == (_n & 3)) ? _n : ((_n | 3) + 1))
#define SLC_ALIGN8(_n)       ((0 == (_n & 7)) ? _n : ((_n | 7) + 1))
#pragma endregion random_number_generator
```
## Small array operation
```
#define SLC_ARRAY_SIZE(_a)       (sizeof(_a)/sizeof(_a[0]))
#define SLC_PROD2(_a)           (_a)[0] * (_a)[1]
#define SLC_PROD3(_a)           (_a)[0] * (_a)[1] * (_a)[2]
#define SLC_PROD4(_a)           (_a)[0] * (_a)[1] * \
                                (_a)[2] * (_a)[3]
#define SLC_PROD4EX(_a,_T)      ((_T)((_a)[0]) * (_T)((_a)[1]) * \
                                (_T)((_a)[2]) * (_T)((_a)[3]))
#define SLC_COPY2(_dst, _src)   (_dst)[0] = (_src)[0]; \
                                (_dst)[1] = (_src)[1]
#define SLC_COPY3(_dst, _src)   (_dst)[0] = (_src)[0]; \
                                (_dst)[1] = (_src)[1]; \
                                (_dst)[2] = (_src)[2]
#define SLC_COPY4(_dst, _src)   (_dst)[0] = (_src)[0]; \
                                (_dst)[1] = (_src)[1]; \
                                (_dst)[2] = (_src)[2]; \
                                (_dst)[3] = (_src)[3]
#define SLC_COPY8(_dst, _src)   SLC_COPY4(_dst, _src); \
                                (_dst)[4] = (_src)[4]; \
                                (_dst)[5] = (_src)[5]; \
                                (_dst)[6] = (_src)[6]; \
                                (_dst)[7] = (_src)[7]
#define SLC_COPY16(_dst, _src)  SLC_COPY8(_dst, _src); \
                                (_dst)[8] = (_src)[8]; \
                                (_dst)[9] = (_src)[9]; \
                                (_dst)[10] = (_src)[10]; \
                                (_dst)[11] = (_src)[11]; \
                                (_dst)[12] = (_src)[12]; \
                                (_dst)[13] = (_src)[13]; \
                                (_dst)[14] = (_src)[14]; \
                                (_dst)[15] = (_src)[15]

/**
\brief free buffer preventing multiple freeing.
\param _ppbuffer [in,out] pointer pointer to a buffer
*/
#define SLC_SAFE_FREE(_ppbuffer) if (_ppbuffer && (*_ppbuffer)) \
{ \
    free(*_ppbuffer); \
    *_ppbuffer = NULL; \
}
```
## Constant numbers of identity element of math operations
```
#define SLC_R32_0       (0.0f)
#define SLC_R32_1       (1.0f)
#define SLC_R32_M1      (-1.0f)
#define SLC_R32_2       (2.0f)
#define SLC_R64_0       (0.0)
#define SLC_R64_1       (1.0)
#define SLC_R64_M1      (-1.0)
#define SLC_R64_2       (2.0)
#define SLC_C64_0       CMPLXF(0.0f, 0.0f)
#define SLC_C64_1       CMPLXF(1.0f, 0.0f)
#define SLC_C64_M1      CMPLXF(-1.0f, 0.0f)
#define SLC_C64_I       CMPLXF(0.0f, 1.0f)
#define SLC_C64_MI      CMPLXF(0.0f, -1.0f)
#define SLC_C64_2       CMPLXF(2.0f, 0.0f)
#define SLC_C128_0      CMPLX(0.0, 0.0)
#define SLC_C128_1      CMPLX(1.0, 0.0)
#define SLC_C128_M1     CMPLX(-1.0, 0.0)
#define SLC_C128_I      CMPLX(0.0, 1.0)
#define SLC_C128_MI     CMPLX(0.0, -1.0)
#define SLC_C128_2      CMPLX(2.0, 0.0)
#define SLC_R32_UNITS   { \
    SLC_R32_0, SLC_R32_1, SLC_R32_M1, SLC_R32_2 }
#define SLC_R64_UNITS   { \
    SLC_R64_0, SLC_R64_1, SLC_R64_M1, SLC_R64_2 }
#define SLC_C64_UNITS   { \
    SLC_C64_0, SLC_C64_1, SLC_C64_M1, SLC_C64_2, \
    SLC_C64_I, SLC_C64_MI }
#define SLC_C128_UNITS   { \
    SLC_C128_0, SLC_C128_1, SLC_C128_M1, SLC_C128_2, \
    SLC_C128_I, SLC_C128_MI }
```
## Constant numbers of tolerances
```
#define SLC_R32_STDTOL  (1.0e-5f)
#define SLC_R64_STDTOL  (1.0e-10)
#define SLC_C64_STDTOL  (1.0e-5f)
#define SLC_C128_STDTOL (1.0e-10)
#define SLC_R32_BIGTOL  (1.0e-3f)
#define SLC_R64_BIGTOL  (1.0e-7)
#define SLC_C64_BIGTOL  (1.0e-3f)
#define SLC_C128_BIGTOL (1.0e-7)
```
# Generic
Generic definitions of base number specific functions, types, etc.
```

#pragma region <VTYPE>_NUMBER_NUMBER_COMPARISON
#define SLC_<VTYPE>_SUM_ABS2(_x0, _x1)  \
    (SLC_<VTYPE>_ABS(_x0) + SLC_<VTYPE>_ABS(_x1))

#define SLC_<VTYPE>_ABS_DIFF(_x0, _x1) \
    (SLC_<VTYPE>_ABS(_x0 - _x1))

#define SLC_<VTYPE>_REL_ABS_DIFF(_x0, _x1) \
    SLC_<VTYPE>_ABS_DIFF(_x0, _x1) / \
    SLC_<VTYPE>_SUM_ABS2(_x0, _x1)

#define SLC_<VTYPE>_SAFE_REL_ABS_DIFF(_x0, _x1, _TOL) \
    (((SLC_<VTYPE>_ABS(_x0) < _TOL) || \
     (SLC_<VTYPE>_ABS(_x1) < _TOL)) ? \
        SLC_<VTYPE>_ABS_DIFF(_x0, _x1) : \
        SLC_<VTYPE>_REL_ABS_DIFF(_x0, _x1))

#define SLC_<VTYPE>_ARE_EQUAL(_x0, _x1, _TOL) \
    (SLC_<VTYPE>_SAFE_REL_ABS_DIFF(_x0, _x1, _TOL) < _TOL)
#pragma endregion <VTYPE>_NUMBER_NUMBER_COMPARISON
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```

#endif /* _00BASE_NUMBERS_H */
```
