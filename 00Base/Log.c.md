# Control
```
{
    "OUT": "Log.c",
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
File: Log.c
Description: Logging utility functions

Revision history
Rev.     Date   Author  Description
00.00.00 231030 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#define _01BASE_LOG_C
#include "SLC/Log.h"
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>


static const char* LogLabelERR = "ERR";
static const char* LogLabels[] =
{
    NULL, "INF", "DBG", NULL, "PERF", NULL, NULL, NULL,
    "TEST"
};

#if defined(_01BASE_LOG_C)
FILE* SLCLog_Sink = NULL;
SLCLog_Level_t SLCLog_Level = SLCLog_Level_ALL;
pthread_spinlock_t SLCLog_Lock = 0;
#endif

void SLCLog_WriteHeader(SLCLog_Level_t loglevel)
{
    struct timespec ts;
    struct tm tm;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm);
    fprintf(SLCLog_Sink, "%04d-%02d-%02d %02d:%02d:%02d.%06ld,%s,",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
        tm.tm_min, tm.tm_sec, ts.tv_nsec/1000, LogLabels[loglevel >> 1]);
}

void SLCLog_WriteErrHeader(SLC_errno_t err)
{
    struct timespec ts;
    struct tm tm;
    clock_gettime(CLOCK_REALTIME, &ts);
    localtime_r(&ts.tv_sec, &tm);
    fprintf(SLCLog_Sink,
        "%04d-%02d-%02d %02d:%02d:%02d.%06ld,%s,0x%08x(%d)",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
        tm.tm_min, tm.tm_sec, ts.tv_nsec/1000, LogLabelERR, err, err);
}
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_functions
void SLCLog_<VTYPE>Err(SLC_errno_t err,
    const char* refname, const char* testname, SLC_I32_t index,
    const SLC_<VTYPE>_t* refarray, const SLC_<VTYPE>_t* testarray)
{
    if ((!SLCLog_Sink) || (0 == (SLCLog_Level & SLCLog_Level_ERR))) return;
    SLCLog_WriteErrHeader(err);
    fprintf(SLCLog_Sink, "Number mismatch, %s[%d] = ", refname, index);
    SLC_<VTYPE>_PRINT(SLCLog_Sink, refarray[index]);
    fprintf(SLCLog_Sink, ", %s[%d] = ");
    SLC_<VTYPE>_PRINT(SLCLog_Sink, testarray[index]);
    SLC_NEWLINE(SLCLog_Sink);
}
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
