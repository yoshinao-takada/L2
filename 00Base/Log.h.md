# Control
```
{
    "OUT": "../include/SLC/Log.h",
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
## File Header and Includes
```
/*
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

File description
File: Log.h
Description: Logging utility macros and functions

Revision history
Rev.     Date   Author  Description
00.00.00 231030 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#if !defined(_00BASE_LOG_H)
#include "SLC/Numbers.h"
#include "SLC/errno.h"
#include "SLC/ExIO.h"
#include <stdio.h>
#include <pthread.h>
```
## Declaring Log Levels and Common Functions
```
#pragma region Logging_Common
typedef enum
{
    SLCLog_Level_NONE = 0, // disable output
    SLCLog_Level_ERR = 1, // output only ERR
    SLCLog_Level_INF = 2, // output ERR and INF
    SLCLog_Level_DBG = 4, // output ERR, INF, and DBG
    SLCLog_Level_PERF = 8, // output performance test message
    SLCLog_Level_TEST = 16, // output test message
    SLCLog_Level_ALL = 31, // enable all log levels.
}
SLCLog_Level_t;

/**
\brief Log-sink output file stream.
    Setting NULL disables logging. Default value is stderr.
*/
#if !defined(_00BASE_LOG_C)
extern FILE* SLCLog_Sink;
extern SLCLog_Level_t SLCLog_Level;
extern pthread_spinlock_t SLCLog_Lock;
#endif

/**
\brief Log writer core function
\param loglevel [in]
*/
void SLCLog_WriteHeader(SLCLog_Level_t loglevel);

/**
\brief Log writer core function for error events
\param err [in] error number
*/
void SLCLog_WriteErrHeader(SLC_errno_t err);
#pragma endregion Logging_Common
```
## Level Specific Log Writer
```
#pragma region LevelSpecificLogWriter
/**
\brief wrapper log writer for error events
\param err [in] error number
\param ... [in] variadic parameters of variadic macro
*/
#define SLCLog_ERR(err, ...) \
if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_Level_ERR)) \
{ \
    SLCLog_WriteErrHeader(err); \
    fprintf(SLCLog_Sink, _VA_ARGS_); \
}

/**
\brief wrapper log writer for loglevel INF
*/
#define SLCLog_INF(...) \
if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_Level_INF)) \
{ \
    SLCLog_WriteHeader(SLCLog_Level_INF); \
    fprintf(SLCLog_Sink, _VA_ARGS_); \
}

/**
\brief wrapper log writer for loglevel DBG
*/
#define SLCLog_DBG(...) \
if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_Level_DBG)) \
{ \
    SLCLog_WriteHeader(SLCLog_Level_DBG); \
    fprintf(SLCLog_Sink, _VA_ARGS_); \
}

/**
\brief wrapper log writer for loglevel PERF
*/
#define SLCLog_PERF(...) \
if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_Level_PERF)) \
{ \
    SLCLog_WriteHeader(SLCLog_Level_PERF); \
    fprintf(SLCLog_Sink, _VA_ARGS_); \
}

/**
\brief wrapper log writer for loglevel TEST
*/
#define SLCLog_TEST(...) \
if ((SLCLog_Sink) && (SLCLog_Level & SLCLog_Level_TEST)) \
{ \
    SLCLog_WriteHeader(SLCLog_Level_TEST); \
    fprintf(SLCLog_Sink, _VA_ARGS_); \
}
#pragma endregion LevelSpecificLogWriter
```
## Test Specific Utility Macros
```
#pragma region test_utility_macros
/**
\brief Standard test function parameter
*/
typedef struct
{
    SLC_I32_t       settings;
    SLC_Void_cpt    data;
}
SLCTest_Args_t, *SLCTest_Args_pt;
typedef const SLCTest_Args_t *SLCTest_Args_cpt;

/**
\brief Standard test function signature without arguments
*/
typedef SLC_errno_t (*SLCTest_Method_f)();

/**
\brief Standard test function signature with arguments
*/
typedef SLC_errno_t (*SLCTest_Method2_f)(SLCTest_Args_cpt args);

/**
\brief Test function execution macro
\param _errnoPtr [out]
\param _methodToTest [in] test function with no argument
\param _file [in] caller __FILE__ macro
\param _func [in] caller __FUNCTION__ macro
\param _line [in] caller __LINE__ macro
*/
#define SLCTest_RUN(_errnoPtr, _methodToTest, _file, _func, _line) \
    *_errnoPtr = _methodToTest(); \
    if (*_errnoPtr) \
    { \
        SLCLog_ERR(*_errnoPtr, "file=%s, func=%s, line=%d\n", \
            _file, _func, _line); \
    }


/**
\brief Test function execution macro with break statement
\param _errnoPtr [out]
\param _methodToTest [in] test function with 
\param _file [in] caller __FILE__ macro
\param _func [in] caller __FUNCTION__ macro
\param _line [in] caller __LINE__ macro
*/
#define SLCTest_RUN_ERROR_BREAK( \
    _errnoPtr, _methodToTest, _file, _func, _line) \
    SLCTest_RUN(_errnoPtr, _methodToTest, _file, _func, _line); \
    if (*_errnoPtr) break


#define SLCTest_RUN2 \
    (_errnoPtr, _methodToTest, _settingPtr, _file, _func, _line) \
    *_errnoPtr = _methodToTest(_settingPtr); \
    if (*_errnoPtr) { \
        SLCLog_ERR(*_errnoPtr, "file=%s, func=%s, line=%d\n", _file, _func, _line); \
        if (SLC_TEST_ABORT_ON_FAIL) break; }

#define SLCTest_RUN2_ERROR_BREAK( \
    _errnoPtr, _methodToTest, _settingPtr, _file, _func, _line) \
    SLCTest_RUN2( \
        _errnoPtr, _methodToTest, _settingPtr, _file, _func, _line); \
    if (*_errnoPtr) break

#define SLCTest_END(_errnoPtr, _file, _func, _line) \
    SLCLog_TEST( \
        "errno=0x%x(%d) @ %s,%d\n", \
        *_errnoPtr, *_errnoPtr, _file, _func, _line)

#pragma endregion test_utility_macros
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _00BASE_LOG_H */
```
