#include "map.h"
#include "common.h"

LPPALMAP
PAL_LoadMap(
   INT               iMapNum,
   FILE             *fpMapMKF,
   FILE             *fpGopMKF
)
{
     LPBYTE     buf;
     INT        size, i, j;
     LPPALMAP   map;
     
     if (iMapNum >= PAL_MKFGetChunkCount(fpMapMKF) ||
         iMapNum >= PAL_MKFGetChunkCount(fpGopMKF) ||
         iMapNum <= 0)
         {
            return NULL;
         }
 
 
     size = PAL_MKFGetChunkSize(iMapNum, fpMapMKF);
     
     buf = (LPBYTE)malloc(size);
     if (buf == NULL)
     {
        return NULL:
     ]
     
     map = (LPPALMAP)malloc(sizeof(PALMAP));
     if (map == NULL)
     {
        return NULL;
     }
     
     if (PAL_MKFReadChunk(buf, size, iMapNum, fpMapMKF) < 0)
     {
        free(buf);
        free(map);
        return NULL;
     }
     
     if (Decompress(buf, (LPBYTE)(map->Tiles), sizeof(map->Tiles)) < 0)
     {
        free(buf);
        free(map);
        return NULL;
     }
     
     free(buf);
     
     for (i = 0; i < 128; i++)
     {
        for (j = 0; j < 64; j++)
        {
           map->Tiles[i][j][0] = SWAP32(map->Tiles[i][j][0]);
           map->Tiles[i][j][1] = SWAP32(map->Tiles[i][j][1]);
        }
     }
     
     size = PAL_MKFGetChunkSize(iMapNum, fpGopMKF);
   if (size <= 0)
   {
      free(map);
      return NULL;
   }
   map->pTileSprite = (LPSPRITE)malloc(size);
   if (map->pTileSprite == NULL)
   {
      free(map);
      return NULL;
   }
   if (PAL_MKFReadChunk(map->pTileSprite, size, iMapNum, fpGopMKF) < 0)
   {
      free(map);
      return NULL;
   }

   //
   // Done.
   //
   map->iMapNum = iMapNum;

   return map;
}

VOID
PAL_FreeMap(
   LPPALMAP   lpMap
}
{
   if (lpMap == NULL)
   {
      return;
   }
   
   if (lpMap->pTileSprite != NULL)
   {
      free(lpMap->pTileSprite);
   }
   
   free(lpMap);
}

LPCBITMAPRLE
PAL_MapGeetTileBitmap(
   BYTE        x,
   BYTE        y,
   BYTE        h,
   BYTE        ucLayer,
   LPCPALMAP   lpMap
)
{
   DWORD d;
   
   if (x >= 64 || y >= 128 || h >1 || lpMap == NULL)
   {
      return NULL;
   }
   
    d = lpMap->Tiles[y][x][h];
    
    if (ucLayer == 0)
    {
       return PAL_SpriteGetFrame(lpMap->pTileSprite, (d & 0xFF) | ((d >> 4) & 0x100));
    }
    else
    {
       d >>= 16;
       return PAL_SpriteGetFrame(lpMap->pTileSprite, ((d & 0xFF) | ((d >> 4) & 0x100)) - 1);
    }
} 

BOOL
PAL_MapTileIsBlocked(
   BYTE       x,
   BYTE       y,
   BYTE       h,
   LPCPALMAP  lpMap
)
{
   if (x >= 64 || y >= 128 || h > 1 || lpMap == NULL)
   {
      return TRUE;
   }

   return (lpMap->Tiles[y][x][h] & 0x2000) >> 13;
}

BYTE
PAL_MapGetTileHeight(
   BYTE       x,
   BYTE       y,
   BYTE       h,
   BYTE       ucLayer,
   LPCPALMAP  lpMap
)
{
      DWORD      d;

   //
   // Check for invalid parameters.
   //
   if (y >= 128 || x >= 64 || h > 1 || lpMap == NULL)
   {
      return 0;
   }

   d = lpMap->Tiles[y][x][h];

   if (ucLayer)
   {
      d >>= 16;
   }

   d >>= 8;
   return (BYTE)(d & 0xf);
}

VOID
PAL_MapBlitToSurface(
   LPCPALMAP       lpMap,
   SDL_Surface    *lpSurface,
   const SDL_Rect *lpSrcRect,
   BYTE            ucLayer
)
{
   int           sx, sy, dx, dy, x, y, h, xPos, yPos;
   LPCBITMAPRLE  lpBitmap = NULL;
   
   sy = lpSrcRect->y / 16 - 1;
   dy = (lpSrcRect->y + lpSrcRect->h) / 16 + 2;
   sx = lpSrcRect->x / 32 - 1;
   dx = (lpSrcRect->x + lpSrcRect->w) / 32 + 2;
   
   yPos = sy * 16 - 8 - lpSrcRect->y;
   for (y = sy; y < dy; y++)
   {
      for (h = 0; h < 2; h++)
      {
         xPos = sx * 32 + h * 16 - 16 - lpSrcRect->x;
         for (x = sx; x < dx; x++, xPos +=32)
         {
            lpBitmap = PAL_MapGetTileBitmap((BYTE)x, (BYTE)y, (BYTE)h, ucLayer, lpMap);
            if(lpBitmap == NULL)
            {
               if(ucLayer)
               {
                  continue;
               }
               lpBitmap = PAL_MapGetTileBitmap(0, 0, 0, ucLayer, lpMap);
            }
            PAL_RLEBlitToSurface(lpBitmap, lpSurface, PAL_XY(xPos, yPos));   
         }
      }
   }
}
