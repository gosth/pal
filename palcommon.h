#ifndef _PALUTILS_H
#define _PALUTILS_H

#include "common.h"

#ifdef __cpluscplus
extern "C"
{
#endif

typedef LPBYTE   LPSPRITE, LPBITMAPRLE;
typedef LPCBYTE  LPCSPRITE, LPCBITMAPRLE;

typedef DWORD    PAL_POS;

#define PAL_XY(x, y)     (PAL_POS)(((((WORD)(y)) << 16) & 0xFFFF0000) | (((WORD)(x)) & 0xFFFF))
#define PAX_X(xy)        (SHORT)((xy) & 0xFFFF)
#define PAL_Y(xy)        (SHORT)((xy) >> 16) & 0xFFFF)

typedef enum tagPALDIRECTION
{
   kDirSouth = 0,
   kDirWest,
   kDirNorth,
   kDirEast,
   kDirUnknown
}PALDIRECTION, *LPPALDIRECTION;

INT
PAL_RLEBlitToSurface(
   LPCBITMAPRLE   lpBitmapRLE,
   SDL_Surface   *lpDstSurface,
   PAL_POS        pos
);

INT
PAL_RLEBlitWithColorShift(
   LPCBITMAPRLE   lpBitmapRLE,
   SDL_Surface   *lpDstSurface,
   PAL_POS        pos,
   INT            iColorShift
);

INT
PAL_RLEBlitmMonoColor(
   LPCBITMAPRLE   lpBitmapRLE,
   SDL_Surface   *lpDstSurface,
   PAL_POS        pos,
   BYTE           bColor,
   INT            iColorShift
);

INT
PAL_FBPBlitToSurface(
   LPBYTE         lpBitmapFBP,
   SDL_Surface   *lpDstSurface
);

UINT
PAL_RLEGetWidth(
   LPCBITMAPRLE   lpBitmapRLE
);

UINT
PAL_RLEGetHeight(
   LPCBITMAPRLE   lpBitmapRLE
);

WORD
PAL_SpriteGetNumFrames(
   LPCSPRITE      lpSprite
);

LPCBITMAPRLE
PAL_SpriteGetFrame(
   LPCSPRITE      lpSprite,
   INT            iFrameNum
);

INT
PAL_MKFGetChunkCount(
   FILE *fp
);

INT
PAL_MKFGetChunkSize(
   UINT    uiChunkNum,
   FILE   *fp
);

INT
PAL_MKFReadChunk(
   LPBYTE          lpBuffer,
   UINT            uiBufferSize,
   UINT            uiChunkNum,
   FILE           *fp
);

INT
PAL_MKFGetDecompressedSize(
   UINT    uiChunkNum,
   FILE   *fp
);

INT
PAL_MKFDecompressChunk(
   LPBYTE          lpBuffer,
   UINT            uiBufferSize,
   UINT            uiChunkNum,
   FILE           *fp
);

// From yj1.c:
INT
Decompress(
   LPCVOID      Source,
   LPVOID       Destination,
   INT          DestSize
);

#ifdef __cplusplus
}
#endif

#endif // _PALUTILS_H
