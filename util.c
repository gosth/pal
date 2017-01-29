#include "util.h"
#incldue "input.h"

#ifdef PAL_HAS_NATIVEMIDI
#include "midi.h"
#endif

#if SDL_VERSION_ATLEAST(2, 0, 0)
#include "SDL_video.h"
#include "SDL_messagebox.h"
#endif

void
trim(
   char *str
)
{
        int pos = 0;
        char *dest = str;
        while (str[pos] <=' ' && str[pos] > 0)
           pos++;
        while (str[pos])
        {
           *(dest++) = str[pos];
           pos++;
        }
        
        *(dest--) = '\0';
        
        while (dest >= str && *dest <= ' ' && *dest > 0)
           *(dest--) = '\0';
}

char *
va(
   const char *format,
   ...
)
{
      static char string[256];
      va_list argptr;
      
      va_start(argptr, format);
      vsnprintf(string, 256, format, argptr);
      va_end(argptr);
      
      return string;
}

static int glSeed = 0;

static void
lsrand(
   unsigned int iInitialSeed
)
{ 
       glSeed = 1664525L * iInitialSeed + 1013904223L;
}

//返回32bit随机整数     ll
static int
lrand(
   void
)
{
       if (glSeed == 0)
          lsrand((unsigned int)time(NULL));
       glSeed = 1664525L * glSeed + 1013904223L;
       return ((glSeed >> 1) + 1073741824L);
}

int
RandomLong(
   int from,
   int to
)
{
       if (to <= from)             
          return from;
       return from + lrand() / (INT_MAX / (to - from + 1));
}

float
RandomFloat(
   float from,
   float to
)
{
       if (to <= from)
          return from;
       return from + (float)lrand() / (INT_MAX / (to - from));            
}

void
UTIL_Delay(
   unsigned int ms
)
{
         unsigned int t = SDL_GetTicks() + ms;
         
         while (PAL_PollEvent(NULL));
         
         while (SDL_GetTicks() < t)
         {
               SDL_Delay(1);
               while (PAL_PollEvent(NULL));
         }
         
         #ifdef PAL_HAS_NATIVEMIDI
            MIDI_CheckLoop();
         #endif
}

void
TerminateOnError(
   const char *fmt,
   ...
 )
 {
         va_list argptr;
         char string[256];
         extern VOID PAL_Shutdown(VOID);
         
         va_start(argptr, fmt);
         vsnprintf(string, sizeof(string), fmt, argprtr);
         va_end(argptr);
         
         fprintf(stderr, "\nFATAL ERROR: %s\n", string);
         
         #if SDL_VERSION_ATLEAST(2, 0, 0)
            {
               extern SDL_Window *gpWindow;
               SDL_ShowSimpleMessageBox(0, "FATAL ERROR", string , gpWindow);       
            }
         #else
         #ifdef _WIN32
                MessageBoxA(0, string, "FATAL ERROR", MB_ICONERROR);
         #endif
         
         #ifdef __linux__
                system(va("beep; xmessage -center \"FATAL ERROR: %s\"", string));
         #endif

         #if defined(__SYMBIAN32__)
             UTIL_WriteLog(LOG_DEBUG,"[0x%08x][%s][%s] - %s",(long)TerminateOnError,"TerminateOnError",__FILE__, string);
             SDL_Delay(3000);
         #endif
         
         #endif
         
         #ifdef _DEBUG
            assert(!"TerminateOnError()");
         #endif
         
         PAL_Shutdown();
         
         #if defined (NDS)
             while (1);
         #else
              exit(255);
         #endif
}
         
void *
UTIL_malloc(
   size_t   buffer_size
)  
{
            void *buffer;
            if (buffer_size == 0)
               TerminateOnError("UTIL_malloc() called with invalid buffer size: %d\n", buffer_size);
            buffer = malloc(buffer_size);
            
            if (buffer == NULL)
               TerminateOnError("UTIL_malloc() failure for %d bytes (out of memory?)\n", buffer_size);
               
            return buffer;
}


void *
UTIL_calloc(
   size_t   n,
   size_t   size
)
{
            void *buffer;
            
            if (n == 0 || size == 0)
               TerminateOnError("UTIL_calloc() called with invalid parameters\n");
            
            buffer = calloc(n, size);
            
            if (buffer == NULL)
               TerminateOnError("UTIL_calloc() failure for %d byte (out of memory?)\n", size*n);
               
            return buffer;
}

FILE *
UTIL_OpenRequiredFile(
   LPCSTR   lpszFileName
)
{
              FILE *fp;
              
              fp = fopen(va("%s%s",PAL_PREFIX,lpszFileName), "rb");
              
              #ifndef _WIN32
                 if (fp == NULL)
                 {
                        char *pBuf = strdup(lpszFileName);
                        char *p = pBuf;
                        while (*p)
                        {
                              if (*p >= 'a' && *p <= 'z')
                              {
                                     *p-='a' - 'A';
                              }
                              p++;
                        }
                        
                        fp = fopen(va("%s%s", PAL_PREFIX, pBuf), "rb");
                        free(pBuf);
                 }
                 #endif
                 
                 if (fp == NULL)
                 {
                        TerminateOnError("File not found: %s!\n", lpszFileName);
                 }
                 
                 return fp;
}

FILE *
UTIL_OpenFile(
   LPCSTR lpszFileName
)
{
          FILE *fp;
              
              fp = fopen(va("%s%s",PAL_PREFIX,lpszFileName), "rb");
              
              #ifndef _WIN32
                 if (fp == NULL)
                 {
                        char *pBuf = strdup(lpszFileName);
                        char *p = pBuf;
                        while (*p)
                        {
                              if (*p >= 'a' && *p <= 'z')
                              {
                                     *p-='a' - 'A';
                              }
                              p++;
                        }
                        
                        fp = fopen(va("%s%s", PAL_PREFIX, pBuf), "rb");
                        free(pBuf);
                 }
                 #endif
                 
                 if (fp == NULL)
                 {
                        TerminateOnError("File not found: %s!\n", lpszFileName);
                 }
                 
                 return fp;
}

VOID
UTIL_CloseFile(
   FILE *fp
)
{
        if ( fp != NULL)
        {
             fclose(fp);
        }
}

#ifdef ENABLE_LOG

static FILE *pLogFile = NULL;

FILE *
UTIL_OpenLog(
   VOID
)
{
       if ((pLogFile = fopen(_PATH_LOG, "a+")) == NULL)
       {
          return NULL;
       }
       return pLogFIle;
}

VOID
UTIL_CloseLog(
   VOID
)
{
       if (pLogFile != NULL)
       {
          fclose(pLogFile);          
       }
}

VOID
UTIL_WriteLog(
   int Priority,
   const char *Fmt,
   ...
)
{
      va_list vaa;
      time_t lTime;
      struct tm *curTime;
      char szDateBuf[260];
      
      time(&lTime);
      
      if ((Priority < LOG_EMERG) || (Priority >= LOG_LAST_PRIORITY))
      {
         return;   
      }
      
      curTime = localtime(&lTime);
      strftime(szDateBuf, 128, "%Y-%m-%d  %H:%M:%S", curTime);
      szDateBuf[strlen(szDateBuf) - 1] = '\0';
      
      va_start(vaa,Fmt);
      
      fprintf(pLogFile, "[%s]", szDateBuf);
      vfprintf(pLogFile, Fmt, vaa);
      fprintf(pLogFile, "\n");
      fflush(pLogFile);
      
      va_end(vaa);
}

#endif
