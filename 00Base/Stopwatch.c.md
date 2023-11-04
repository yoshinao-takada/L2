# Control
```
{
    "OUT": "Stopwatch.c",
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
## File Header
Head contains definitions common to all base number types.
```
/*
(C) Copyright 2023, Yoshinao Takada
All source files and data files are protected by the license term of
`LICENSE` in the project root directory.

File description
File: Stopwatch.c
Description: Time measurement utility mainly for performance tests.
    The stopwatch supports multiple sets of (start, lap, end) times.
    The set is called channel.

Revision history
Rev.     Date   Author  Description
00.00.00 231102 YT      Initial creation

Note:
Date format: YYMMDD (YY: lower 2 digits of dominical year, 
             MM:month(1..12), DD: day of month (1..31))
Author: Initials of revision authors
*/
#include "SLC/Stopwatch.h"
#include "SLC/Array.h"
#include "SLC/errno.h"
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <memory.h>
```
## Implementation of Stopwatch functions
```
/**
\brief entry of stopwatch array
*/
typedef struct
{
    struct timespec start;
    char* caption;
    SLCStopwatch_Resolution_t resolution;
}
StopwatchEntry_t, *StopwatchEntry_pt;
typedef const StopwatchEntry_t *StopwatchEntry_cpt;

typedef struct
{
    StopwatchEntry_pt channels;
    char* captions;
    SLC_I32_t channelCount, captionLength;
}
StopwatchArray_t, *StopwatchArray_pt;

typedef const StopwatchArray_t *StopwatchArray_cpt;

// stopwatch body
static StopwatchArray_t stopwatch = { NULL, NULL, 0 };

#define ENTRY_SIZE  SLC_ALIGN8(sizeof(StopwatchEntry_t))

SLC_errno_t SLCStopwatch_Init(SLC_I32_t channelCount, SLC_I32_t captionLength)
{
    SLC_errno_t err = EXIT_SUCCESS;
    do 
    {
        stopwatch.channels = 
            (StopwatchEntry_pt)calloc(ENTRY_SIZE, channelCount);
        if (!stopwatch.channels)
        {
            err = ENOMEM;
            break;
        }
        SLC_I32_t captionBufferSize = captionLength * channelCount;
        stopwatch.captions = (char*)malloc(captionBufferSize);
        if (!stopwatch.captions)
        {
            err = ENOMEM;
            break;
        }
        stopwatch.channelCount = channelCount;
        stopwatch.captionLength = captionLength;
        memset(stopwatch.captions, '\0', captionBufferSize);
        char* caption = stopwatch.captions;
        for (int i = 0; i < channelCount; i++, caption += captionLength)
        {
            stopwatch.channels[i].caption = caption;
            stopwatch.channels[i].resolution = 
                SLCStopwatch_Resolution_MICROSECOND;
            stopwatch.channels[i].start.tv_sec = 0; // clear start time
            stopwatch.channels[i].start.tv_nsec = 0;
        }
    }
    while (0);
    if (err)
    {
        SLC_SAFE_FREE(&stopwatch.channels);
        SLC_SAFE_FREE(&stopwatch.captions);
        stopwatch.channelCount = 0;
    }
    return err;
}

#undef ENTRY_SIZE

void SLCStopwatch_Destroy()
{
    SLC_SAFE_FREE(&stopwatch.channels);
    SLC_SAFE_FREE(&stopwatch.captions);
    stopwatch.channelCount = stopwatch.captionLength = 0;
}

// get the first index of unused channels in stopwatch.
static SLC_I32_t FindUnused()
{
    SLC_I32_t unusedIndex = -1;
    for (SLC_I32_t i = 0; i < stopwatch.channelCount; i++)
    {
        const struct timespec* start = &stopwatch.channels[i].start;
        if (start->tv_sec == 0 && start->tv_nsec == 0)
        {
            unusedIndex = i;
            break;
        }
    }
    return unusedIndex;
}

SLC_I32_t SLCStopwatch_Start(
    const char* caption, SLCStopwatch_Resolution_t resolution)
{
    assert(strlen(caption) < stopwatch.captionLength);
    SLC_I32_t unusedIndex = -1;
    do {
        if (0 > (unusedIndex = FindUnused()))
        {
            break;
        }

        StopwatchEntry_pt channel = stopwatch.channels + unusedIndex;
        strcpy(channel->caption, caption);
        channel->resolution = resolution;
        channel->start.tv_sec = 1;
    } while (0);
    return unusedIndex;
}

void SLCStopwatch_Elapsed(SLC_I32_t channel, struct timespec* time)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    SLCTimespec_AMinusB(time, &now, &stopwatch.channels[channel].start);
}

static const SLC_I32_t timeDigits[] =
{
    8, // no fractional second
    8 + 4, // second + dot + millisecond part
    8 + 7, // second + dot + microsecond part
    8 + 10 // second + dot + nanosecond prt
};

SLC_I32_t SLCStopwatch_WriteBufferSize(SLC_I32_t channelIndex)
{
    assert(channelIndex < stopwatch.channelCount);
    StopwatchEntry_cpt channel = stopwatch.channels + channelIndex;
    return strlen(channel->caption) +
        timeDigits[(SLC_I32_t)(channel->resolution)];
}

static const char* timeFormats[] =
{
    "%s%8d", "%s%8d.%03d", "%s%8d.%06d", "%s%8d.%09d"
};

void SLCStopwatch_SWriteElapsed(SLC_I32_t channelIndex, char* buffer)
{
    assert(channelIndex < stopwatch.channelCount);
    StopwatchEntry_cpt channel = stopwatch.channels + channelIndex;
    const char* format = timeFormats[(SLC_I32_t)(channel->resolution)];
    struct timespec elapsed;
    SLCStopwatch_Elapsed(channelIndex, &elapsed);
    switch (channel->resolution)
    {
        case SLCStopwatch_Resolution_SECOND:
            sprintf(buffer, format, channel->caption, elapsed.tv_sec);
            break;
        case SLCStopwatch_Resolution_MILLISECOND:
            sprintf(buffer, format, channel->caption, elapsed.tv_sec,
                elapsed.tv_nsec / 1000000);
            break;
        case SLCStopwatch_Resolution_MICROSECOND:
            sprintf(buffer, format, channel->caption, elapsed.tv_sec,
                elapsed.tv_nsec / 1000);
            break;
        case SLCStopwatch_Resolution_NANOSECOND:
            sprintf(buffer, format, channel->caption, elapsed.tv_sec,
                elapsed.tv_nsec);
            break;
    }
}

void SLCStopwatch_FWriteElapsed(SLC_I32_t channelIndex, FILE* outfile)
{
    assert(channelIndex < stopwatch.channelCount);
    StopwatchEntry_cpt channel = stopwatch.channels + channelIndex;
    const char* format = timeFormats[(SLC_I32_t)(channel->resolution)];
    struct timespec elapsed;
    SLCStopwatch_Elapsed(channelIndex, &elapsed);
    switch (channel->resolution)
    {
        case SLCStopwatch_Resolution_SECOND:
            fprintf(outfile, format, channel->caption, elapsed.tv_sec);
            break;
        case SLCStopwatch_Resolution_MILLISECOND:
            fprintf(outfile, format, channel->caption, elapsed.tv_sec,
                elapsed.tv_nsec / 1000000);
            break;
        case SLCStopwatch_Resolution_MICROSECOND:
            fprintf(outfile, format, channel->caption, elapsed.tv_sec,
                elapsed.tv_nsec / 1000);
            break;
        case SLCStopwatch_Resolution_NANOSECOND:
            fprintf(outfile, format, channel->caption, elapsed.tv_sec,
                elapsed.tv_nsec);
            break;
    }
}

void SLCStopwatch_Release(SLC_I32_t channelIndex)
{
    assert(channelIndex < stopwatch.channelCount);
    StopwatchEntry_pt channel = stopwatch.channels + channelIndex;
    memset(channel->caption, '\0', stopwatch.captionLength);
    channel->start.tv_sec = 0;
    channel->start.tv_nsec = 0;
}
```

## Math operation of two timespec objects
```
void SLCTimespec_AMinusB(
    struct timespec* aMinusB, struct timespec* a, struct timespec* b)
{
    aMinusB->tv_sec = a->tv_sec - b->tv_sec;
    if (b->tv_nsec > a->tv_nsec)
    {
        aMinusB->tv_sec--;
        aMinusB->tv_nsec = (1000000000 - b->tv_nsec) + a->tv_nsec;
    }    
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
