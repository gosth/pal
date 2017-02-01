#ifndef VIDEO_H
#define VIDEO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

extern SDL_Surface *gpScreen;
extern SDL_Surface *gpScreenBak;
extern volatile BOOL g_bRenderPaused;

INT
#ifdef GEKKO // Rikku2000: Crash on compile, allready define on WIISDK
VIDEO_Init_GEKKO(
#else
VIDEO_Init(
#endif
   WORD             wScreenWidth,
   WORD             wScreenHeight,
   BOOL             fFullScreen
);

VOID
VIDEO_Shutdown(
   VOID
);

VOID
VIDEO_UpdateScreen(
   const SDL_Rect  *lpRect
);

VOID
VIDEO_SetPalette(
   SDL_Color        rgPalette[256]
);

VOID
VIDEO_Resize(
   INT             w,
   INT             h
);

SDL_Color *
VIDEO_GetPalette(
   VOID
);

VOID
VIDEO_ToggleFullscreen(
   VOID
);

VOID
VIDEO_SaveScreenshot(
   VOID
);

VOID
VIDEO_BackupScreen(
   VOID
);

VOID
VIDEO_RestoreScreen(
   VOID
);

VOID
VIDEO_ShakeScreen(
   WORD           wShakeTime,
   WORD           wShakeLevel
);

VOID
VIDEO_SwitchScreen(
   WORD           wSpeed
);

VOID
VIDEO_FadeScreen(
   WORD           wSpeed
);

#if SDL_VERSION_ATLEAST(2,0,0)
//
// For compatibility with SDL2.
//
VOID
SDL_WM_SetCaption(
   LPCSTR         lpszCaption,
   LPVOID         lpReserved
);
#endif

#ifdef __cplusplus
}
#endif

#endif
