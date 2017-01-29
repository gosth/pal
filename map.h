#ifndef _MAP_H
#define _MAP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

typedef struct tagPALMAP
{
   DWORD     Tiles[128][64][2];
   LPSPRITE  pTileSprite;
   INT       iMapNum;
}PALMAP, *LPPALMAP;

typedef const PALMAP *LPCPALMAP;

LPPALMAP
PAL_LoadMap(
   INT               iMapNum,
   FILE             *fpMapMKF,
   FILE             *fpGopMKF
);

VOID
PAL_FreeMap(
   LPPALMAP          lpMap
);

LPCBITMAPRLE
PAL_MapGetTileBitmap(
   BYTE       x,
   BYTE       y,
   BYTE       h,
   BYTE       ucLayer,
   LPCPALMAP  lpMap
);

BOOL
PAL_MapTileIsBlocked(
   BYTE       x,
   BYTE       y,
   BYTE       h,
   LPCPALMAP  lpMap
);

BYTE
PAL_MapGetTileHeight(
   BYTE       x,
   BYTE       y,
   BYTE       h,
   BYTE       ucLayer,
   LPCPALMAP  lpMap
);

VOID
PAL_MapBlitToSurface(
   LPCPALMAP             lpMap,
   SDL_Surface          *lpSurface,
   const SDL_Rect       *lpSrcRect,
   BYTE                  ucLayer
);

#define PAL_XYH_TO_POS(x, y, h)      \
   PAL_POS((x) * 32 + (h) * 16, (y) * 16 + (h) * 8)

#define PAL_POS_TO_XYH(pos, x, y, h)  \
{                                     \
   (h) = (BYTE)(((PAL_X(pos) % 32) != 0) ? 1 : 0);     \
   (x) = (BYTE)(PAL_X(pos) / 32);                      \
   (y) = (BYTE)(PAL_Y(pos) / 16);                      \
}

#ifdef __cpluscplus
}
#endif

#endif

#endif
