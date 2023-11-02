# Control
```
{
    "OUT": "../include/SLC/Stopwatch.h",
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
File: Stopwatch.md
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
#if !defined(_00BASE_STOPWATCH_H)
#define _00BASE_STOPWATCH_H
#include "SLC/Numbers.h"
#include "SLC/errno.h"
#include <stdio.h>
#include <time.h>
#pragma regioon stopwatch_functions
/**
\brief initialize variables which are hidden in the library.
\param channelCount [in] channel count
\param captionLength [in] buffer length of each channel for a caption
*/
SLC_errno_t SLCStopwatch_Init(SLC_I32_t channelCount, SLC_I32_t captionLength);

/**
\brief Release the memory block initialized by SLCStopwatch_Init().
*/
void SLCStopwatch_Destroy();

/**
\brief Time measurement resolution selector
*/
typedef enum
{
    SLCStopwatch_Resolution_SECOND,
    SLCStopwatch_Resolution_MILLISECOND,
    SLCStopwatch_Resolution_MICROSECOND,
    SLCStopwatch_Resolution_NANOSECOND,
}
SLCStopwatch_Resolution_t;

/**
\brief Start a stopwatch. The active channel is automatically assigned.
*/
SLC_I32_t SLCStopwatch_Start(
    const char* caption, SLCStopwatch_Resolution_t resolution);

/**
\brief Measure an elapsed time from the instance time when
    SLCStopwatch_Start() was called.
\param channel [in] A channel number of a stopwatch.
\param time [out] measurement result
*/
void SLCStopwatch_Elapsed(SLC_I32_t channel, struct timespec* time);

/**
\brief get a buffer size for a channel
\param channelIndex [in]
\return necessary buffer size to write time measurement result.
*/
SLC_I32_t SLCStopwatch_WriteBufferSize(SLC_I32_t channelIndex);

/**
\brief Write an elapsed time to a buffer.
\param channelIndex [in] A channel number of a stopwatch
\param buffer [out] A buffer length is acquired by
    SLCStopwatch_WriteBufferSize.
*/
void SLCStopwatch_SWriteElapsed(SLC_I32_t channelIndex, char* buffer);

/**
\brief write an elapsed time to a file.
\param channelIndex [in] A channel number of a stopwatch
\param outfile [in] A file pointer of an output file.
*/
void SLCStopwatch_FWriteElapsed(SLC_I32_t channelIndex, FILE* outfile);

/**
\brief Release a channel assigned by SLCStopwatch_Start().
\param channel [in] A channel number of a stopwatch
*/
void SLCStopwatch_Release(SLC_I32_t channel);

/**
\brief Difference of two timespec objects
*/
void SLCTimespec_AMinusB(
    struct timespec* aMinusB, struct timespec* a, struct timespec* b);
```
# Generic
Generic definitions of base number specific functions, types, etc.
```
```
# Foot
Foot contains definitions common to all base number types.
Foot is placed after all generic code are placed.
```
#endif /* _00BASE_STOPWATCH_H */
```
