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
SLCLog_Level_t SLCLog_Level = SLCLog_LevelALL;
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

void SLCLog_WriteErrHeader(SLCerrno_t err)
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

static pthread_spinlock_t lock;
typedef struct {
    struct timespec start;
    char caption[0];
} StopwatchEntry_t, *pStopwatchEntry_t;

static pStopwatchEntry_t entries = NULL;
static SLCI32_t entrysize = 0;
static SLCI32_t entrycount = 0;
static SLCI32_t caption_buffersize = 0;

void SLCStopwatch_Init(SLCSLCI32_t channels, SLCSLCI32_t caption_length)
{
    entrysize = SLCalign8(sizeof(StopwatchEntry_t)) + SLCalign8(caption_length);
    entries = (pStopwatchEntry_t)aligned_alloc(8, entrysize * channels);
    entrycount = channels;
    memset(entries, 0, entrysize * channels);
    assert(0 == pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE));
    caption_buffersize = caption_length;
}

void SLCStopwatch_Destroy()
{
    free(entries);
    entries = NULL;
    entrysize = entrycount = 0;
    assert(0 == pthread_spin_destroy(&lock));
}

#define Stopwatch_ENTRY(__index) (pStopwatchEntry_t)(((uint8_t*)entries) + (__index) * entrysize)

static SLCI32_t UnusedEntry()
{
    SLCI32_t found = -1;
    for (SLCI32_t i = 0; i < entrycount; i++)
    {
        pStopwatchEntry_t entry = Stopwatch_ENTRY(i);
        if (entry->start.tv_sec != 0)
        {
            found = (SLCI32_t)i;
            break;
        }
    }
    return found;
}

SLCI32_t SLCStopwatch_Start(const char* caption)
{
    SLCI32_t entry_index = UnusedEntry();
    if (-1 == entry_index)
    { // no entry is available.
        SLCLog_ERR(ENOBUFS, "No Stopwatch entry.\n");
        return entry_index;
    }
    if (strlen(caption) + 1 > caption_buffersize)
    {
        SLCLog_ERR(E2BIG, "caption:\"%s\" too long/n", caption);
        return -1;
    }
    pStopwatchEntry_t entry = Stopwatch_ENTRY(entry_index);
    strcpy(entry->caption, caption);
    clock_gettime(CLOCK_REALTIME, &entry->start);
    return entry_index;
}

void SLCStopwatch_Measure(SLCI32_t channel_index)
{
    pStopwatchEntry_t entry = Stopwatch_ENTRY(channel_index);
    struct timespec now, elapsed;
    clock_gettime(CLOCK_REALTIME, &now);
    SLC_Timespec_A_minus_B(&elapsed, &now, &entry->start);
    SLCLog_PERF("elapsed time = %ld.%06ld [sec]\n", elapsed.tv_sec, elapsed.tv_nsec / 1000);
}

void SLCStopwatch_Release(SLCI32_t channel_index)
{
    pStopwatchEntry_t entry = Stopwatch_ENTRY(channel_index);
    memset(entry, 0, entrysize);
}

void SLC_Timespec_A_minus_B(
    struct timespec* a_minus_b, struct timespec* a, struct timespec* b
) {
    if (b->tv_nsec > a->tv_nsec)
    {
        b->tv_nsec += 1000000000;
        b->tv_sec--;
    }
    a_minus_b->tv_sec = a->tv_sec - b->tv_sec;
    a_minus_b->tv_nsec = a->tv_nsec - b->tv_nsec;
}
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
#pragma region <VTYPE>_functions
void SLCLog<VTYPE>_Err(SLCerrno_t err,
    const char* refname, const char* testname, SLCI32_t index,
    const SLC<VTYPE>_t* refarray, const SLC<VTYPE>_t testarray)
{
    if ((!SLCLog_Sink) || (0 == (SLCLog_Level & SLCLog_LevelERR))) return;
    SLCLog_WriteErrHeader(err);
    fprintf(SLCLog_Sink, "Number mismatch, %s[%d] = ", refname, index);
    SLC<VTYPE>_PRINT(SLCLog_Sink, refarray[index]);
    fprintf(SLCLog_Sink, ", %s[%d] = ");
    SLC<VTYPE>_PRINT(SLCLog_Sink, testarray[index]);
    SLCNEWLINE(SLCLog_Sink);
}
#pragma endregion <VTYPE>_functions
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
```
