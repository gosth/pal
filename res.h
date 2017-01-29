#ifndef RES_H
#define RES_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum tagLOADRESFLAG
{
   kLoadScene          = (1 << 0),
   kLoadPlayerSprite   = (1 << 1),
} LOADRESFLAG, *LPLOADRESFLAG;

VOID
PAL_InitResources(
   VOID
);

VOID
PAL_FreeResources(
   VOID
);

VOID
PAL_SetLoadFlags(
   BYTE   bFlags
);

VOID
PAL_LoadResources(
   VOID
);

LPPALMAP
PAL_GetCurrentMap(
   VOID
);

LPSPRITE
PAL_GetPlayerSprite(
   BYTE      bPlayerIndex
);

LPSPRITE
PAL_GetBattleSprite(
   BYTE      bPlayerIndex
);

LPSPRITE
PAL_GetEventObjectSprite(
   WORD      wEventObjectID
);

#ifdef __cplusplus
}
#endif

#endif
