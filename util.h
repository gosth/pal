#ifndef UTIL_H
#define UTIL_H

#include "common.h"

//#define ENABLE_LOG 1

#ifdef __cplusplus
extern "C"
{
#endif

void
trim(
   char *str
);

char *va(
   const char *format,
   ...
);

int
RandomLong(
   int from,
   int to
);

float
RandomFloat(
   float from,
   float to
);

void
UTIL_Delay(
   unsigned int ms
);

void
TerminateOnError(
   const char *fmt,
   ...
);

void *
UTIL_malloc(
   size_t    buffer_size
);

void *
UTIL_calloc(
   size_t    n,
   size_t    size
);

FILE *
UTIL_OpenRequiredFile(
   LPCSTR     lpszFileName
);

FIlE *
UTIL_OpenFile(
   LPCSTR     lpszFileName
);

VOID
UTIL_CloseFile(
   FILE        *fp
);

#ifdef __IOS__

LPCSTR
UTIL_IOS_BasePath(
   VOID
);

LPCSTR
UTIL_IOS_SavePath(
   VOID
);
    
#endif

#define _PATH_LOG         PAL_PREFIX "log.txt"
#define LOG_EMERG           0 /* system is unusable */
#define LOG_ALERT           1 /* action must be taken immediately */
#define LOG_CRIT            2 /* critical conditions */
#define LOG_ERR             3 /* error conditions */
#define LOG_WARNING         4 /* warning conditions */
#define LOG_NOTICE          5 /* normal but significant condition */
#define LOG_INFO            6 /* informational */
#define LOG_DEBUG           7 /* debug-level messages */
#define LOG_LAST_PRIORITY   8 /* last level */

#ifdef ENABLE_LOG

FILE *
UTIL_OpenLog(
   VOID
);

VOID
UTIL_CloseLog(
   VOID
);

VOID
UTIL_WriteLog(
   int             Priority,
   const char     *Fmt,
   ...
);

#else

#define UTIL_OpenLog()       ((void)(0))
#define UTIL_CloseLog()      ((void)(0))
#ifdef _MSC_VER
__forceinline VOID UTIL_WriteLog(int i, const char *p, ...) {}
#else
#define UTIL_WriteLog(...)   ((void)(0))
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
