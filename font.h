#ifndef FONT_H
#define FONT_H

#include "common.h"
#include "palcommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

INT
PAL_InitFont(
   VOID
);

VOID
PAL_FreeFont(
   VOID
);

VOID
PAL_DrawCharOnSurface(
   WORD             wChar,
   SDL_Surface     *lpSurface,
   PAL_POS          pos,
   BYTE             bColor
);

VOID
PAL_DrawASCIICharOnSurface(
   BYTE             wChar,
   SDL_Surface     *lpSurface,
   PAL_POS          pos,
   BYTE             bColor
);

VOID
PAL_DrawASCIICharOnSurface(
   BYTE             bChar,
   SDL_Surface     *lpSurface,
   PAL_POS          pos,
   BYTE             bColor
);

#ifdef __cplusplus
}
#endif

#endif
