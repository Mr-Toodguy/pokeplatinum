#include <nitro.h>
#include <string.h>

#include <stdlib.h>

#include "assert.h"

#include "struct_decls/struct_02002F38_decl.h"
#include "struct_decls/struct_02006C24_decl.h"
#include "message.h"
#include "struct_decls/struct_0200B358_decl.h"
#include "struct_decls/struct_0200C6E4_decl.h"
#include "struct_decls/struct_0200C704_decl.h"
#include "struct_decls/struct_02018340_decl.h"
#include "struct_decls/sys_task.h"
#include "strbuf.h"
#include "pokemon.h"

#include "struct_defs/struct_0200D0F4.h"
#include "struct_defs/struct_0205AA50.h"
#include "overlay016/struct_ov16_022674C4.h"
#include "struct_defs/sprite_template.h"

#include "unk_02002F38.h"
#include "narc.h"
#include "message.h"
#include "unk_0200B358.h"
#include "unk_0200C440.h"
#include "unk_0200C6E4.h"
#include "unk_0200D9E8.h"
#include "heap.h"
#include "unk_02018340.h"
#include "unk_0201D15C.h"
#include "unk_0201D670.h"
#include "unk_020218BC.h"
#include "strbuf.h"
#include "pokemon.h"
#include "unk_0208C098.h"
#include "overlay016/ov16_0223DF00.h"
#include "battle/healthbar.h"

#define HEALTHBAR_SCROLL_SPEED  24
#define HEALTHBAR_SCROLL_OUT_OFFSET 160

#define HEALTHBAR_X_OFFSET_SOLO_PLAYER      192
#define HEALTHBAR_Y_OFFSET_SOLO_PLAYER      116
#define HEALTHBAR_X_OFFSET_SOLO_ENEMY       58
#define HEALTHBAR_Y_OFFSET_SOLO_ENEMY       36
#define HEALTHBAR_X_OFFSET_PLAYER_SLOT_1    HEALTHBAR_X_OFFSET_SOLO_PLAYER
#define HEALTHBAR_Y_OFFSET_PLAYER_SLOT_1    HEALTHBAR_Y_OFFSET_SOLO_PLAYER - 13
#define HEALTHBAR_X_OFFSET_PLAYER_SLOT_2    HEALTHBAR_X_OFFSET_SOLO_PLAYER + 6
#define HEALTHBAR_Y_OFFSET_PLAYER_SLOT_2    HEALTHBAR_Y_OFFSET_SOLO_PLAYER + 16
#define HEALTHBAR_X_OFFSET_ENEMY_SLOT_1     HEALTHBAR_X_OFFSET_SOLO_ENEMY + 6
#define HEALTHBAR_Y_OFFSET_ENEMY_SLOT_1     HEALTHBAR_Y_OFFSET_SOLO_ENEMY - 20
#define HEALTHBAR_X_OFFSET_ENEMY_SLOT_2     HEALTHBAR_X_OFFSET_SOLO_ENEMY
#define HEALTHBAR_Y_OFFSET_ENEMY_SLOT_2     HEALTHBAR_Y_OFFSET_SOLO_ENEMY + 9

typedef struct {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_ov16_0226F64C;

typedef struct {
    Healthbar * unk_00;
    u8 * unk_04;
    u8 unk_08;
    u8 unk_09;
    s8 unk_0A;
} UnkStruct_ov16_0226834C;

static s32 ov16_02267EDC(Healthbar * param0, int param1);
static s32 ov16_022680D8(s32 param0, s32 param1, s32 param2, s32 * param3, u8 param4, u16 param5);
static u8 ov16_02268194(s32 param0, s32 param1, s32 param2, s32 * param3, u8 * param4, u8 param5);
static u32 ov16_02268210(s32 param0, s32 param1, s32 param2, u8 param3);
static const u8 * ov16_02268250(int param0);
static void ov16_02267F70(Healthbar * param0, u8 param1);
static void ov16_02267864(Healthbar * param0);
static void ov16_022679C8(Healthbar * param0);
static void ov16_02267A4C(Healthbar * param0);
static void ov16_02267B6C(Healthbar * param0, u32 param1);
static void ov16_02267BF8(Healthbar * param0);
static void ov16_02267C58(Healthbar * param0);
static void ov16_02267CA8(Healthbar * param0, int param1);
static void ov16_02267CE8(Healthbar * param0, u32 param1);
static void ov16_02267DC4(Healthbar * param0, u32 param1);
static void ov16_02266FE4(SpriteRenderer * param0, SpriteGfxHandler * param1, NARC * param2, PaletteData * param3, int param4);
static void ov16_02267244(Healthbar * param0);
static void ov16_0226728C(Healthbar * param0);
static const SpriteTemplate* Healthbar_SpriteTemplate(u8 type);
static const SpriteTemplate * ov16_02268314(u8 param0);
static void ScrollHealthbarTask(SysTask *task, void *data);
static void ov16_02268380(SysTask * param0, void * param1);
void ov16_02268470(Healthbar * param0);
void ov16_02268498(Healthbar * param0);
static void ov16_022684BC(SysTask * param0, void * param1);
static void Healthbar_EnableArrow(Healthbar * param0, int param1);

__attribute__((aligned(4))) static const s8 sArrowOffsetX[] = {
    [HEALTHBAR_TYPE_PLAYER_SOLO]   = 72,
    [HEALTHBAR_TYPE_ENEMY_SOLO]    = 0,
    [HEALTHBAR_TYPE_PLAYER_SLOT_1] = 72,
    [HEALTHBAR_TYPE_ENEMY_SLOT_1]  = 0,
    [HEALTHBAR_TYPE_PLAYER_SLOT_2] = 72,
    [HEALTHBAR_TYPE_ENEMY_SLOT_2]  = 0,
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F64C[][4] = {
    {
        {0x260, 0xA0},
        {0x360, 0xA0},
        {0xA00, 0x60},
        {0xB00, 0x60}
    },
    {
        {0x220, 0xE0},
        {0x320, 0xE0},
        {0xA00, 0x20},
        {0xB00, 0x20}
    },
    {
        {0x240, 0xC0},
        {0x340, 0xC0},
        {0xA00, 0x40},
        {0xB00, 0x40}
    },
    {
        {0x220, 0xE0},
        {0x320, 0xE0},
        {0xA00, 0x20},
        {0xB00, 0x20}
    },
    {
        {0x240, 0xC0},
        {0x340, 0xC0},
        {0xA00, 0x40},
        {0xB00, 0x40}
    },
    {
        {0x220, 0xE0},
        {0x320, 0xE0},
        {0xA00, 0x20},
        {0xB00, 0x20}
    }
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F47C[][2] = {
    {
        {0xA60, 0x40},
        {0xB60, 0x40}
    },
    {
        {0xA20, 0x40},
        {0xB20, 0x40}
    },
    {
        {0xA40, 0x40},
        {0xB40, 0x40}
    },
    {
        {0xA20, 0x40},
        {0xB20, 0x40}
    },
    {
        {0xA40, 0x40},
        {0xB40, 0x40}
    },
    {
        {0xA20, 0x40},
        {0xB20, 0x40}
    }
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F3EC[][2] = {
    {
        {0xAA0, 0x60},
        {0xBA0, 0x60}
    },
    {
        {0xA60, 0x60},
        {0xB60, 0x60}
    },
    {
        {0xA80, 0x60},
        {0xB80, 0x60}
    },
    {
        {0xA60, 0x60},
        {0xB60, 0x60}
    },
    {
        {0xA80, 0x60},
        {0xB80, 0x60}
    },
    {
        {0xA60, 0x60},
        {0xB60, 0x60}
    }
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F41C[][2] = {
    {
        {0x0, 0x0},
        {0xD00, 0x60}
    },
    {
        {0x620, 0x60},
        {0x0, 0x0}
    },
    {
        {0x0, 0x0},
        {0xC00, 0x60}
    },
    {
        {0x620, 0x60},
        {0x0, 0x0}
    },
    {
        {0x0, 0x0},
        {0xC00, 0x60}
    },
    {
        {0x620, 0x60},
        {0x0, 0x0}
    }
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F3BC[] = {
    {0xD80, 0x60},
    {0x6A0, 0x60},
    {0xC80, 0x60},
    {0x6A0, 0x60},
    {0xC80, 0x60},
    {0x6A0, 0x60}
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F44C[][2] = {
    {
        {0x4E0, 0x0},
        {0xC20, 0xC0}
    },
    {
        {0x4E0, 0x20},
        {0xC00, 0xA0}
    },
    {
        {0x4E0, 0x0},
        {0xC00, 0xC0}
    },
    {
        {0x4E0, 0x20},
        {0xC00, 0xA0}
    },
    {
        {0x4E0, 0x0},
        {0xC00, 0xC0}
    },
    {
        {0x4E0, 0x20},
        {0xC00, 0xA0}
    }
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F38C[] = {
    {0x460, 0x20},
    {0x420, 0x20},
    {0x440, 0x20},
    {0x420, 0x20},
    {0x440, 0x20},
    {0x420, 0x20}
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F35C[] = {
    {0x480, 0x60},
    {0x440, 0x60},
    {0x460, 0x60},
    {0x440, 0x60},
    {0x460, 0x60},
    {0x440, 0x60}
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F33C[4] = {
    {0x240, 0xC0},
    {0x340, 0xC0},
    {0xA00, 0xE0},
    {0xB00, 0xE0}
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F34C[4] = {
    {0x440, 0xC0},
    {0x540, 0xC0},
    {0xC00, 0xE0},
    {0xD00, 0xE0}
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F374[] = {
    {0x0, 0x0},
    {0x0, 0x0},
    {0x4C0, 0x40},
    {0x0, 0x0},
    {0x4C0, 0x40},
    {0x0, 0x0}
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F3A4[] = {
    {0x0, 0x0},
    {0x0, 0x0},
    {0xCC0, 0x20},
    {0x0, 0x0},
    {0xCC0, 0x20},
    {0x0, 0x0}
};

static const UnkStruct_ov16_0226F64C Unk_ov16_0226F3D4[] = {
    {0x0, 0x0},
    {0x0, 0x0},
    {0xC60, 0x20},
    {0x0, 0x0},
    {0xC60, 0x20},
    {0x0, 0x0}
};

static const SpriteTemplate sHealthbarTemplate_SoloPlayer = {
    .x = HEALTHBAR_X_OFFSET_SOLO_PLAYER,
    .y = HEALTHBAR_Y_OFFSET_SOLO_PLAYER,
    .z = 0,
    .animIdx = 0,
    .priority = 23,
    .plttIdx = 0,
    .vramType = NNS_G2D_VRAM_TYPE_2DMAIN,
    .resources = {
        0xBF,
        0x4E26,
        0xBE,
        0xBD,
        SPRITE_RESOURCE_NONE,
        SPRITE_RESOURCE_NONE,
    },
    .bgPriority = 0,
    .transferToVRAM = FALSE,
};

static const SpriteTemplate sHealthbarTemplate_SoloEnemy = {
    .x = HEALTHBAR_X_OFFSET_SOLO_ENEMY,
    .y = HEALTHBAR_Y_OFFSET_SOLO_ENEMY,
    .z = 0,
    .animIdx = 0,
    .priority = 24,
    .plttIdx = 0,
    .vramType = NNS_G2D_VRAM_TYPE_2DMAIN,
    .resources = {
        0xBC,
        0x4E26,
        0xBB,
        0xBA,
        SPRITE_RESOURCE_NONE,
        SPRITE_RESOURCE_NONE,
    },
    .bgPriority = 0,
    .transferToVRAM = FALSE,
};

static const SpriteTemplate sHealthbarTemplate_PlayerSlot1 = {
    .x = HEALTHBAR_X_OFFSET_PLAYER_SLOT_1,
    .y = HEALTHBAR_Y_OFFSET_PLAYER_SLOT_1,
    .z = 0,
    .animIdx = 0,
    .priority = 28,
    .plttIdx = 0,
    .vramType = NNS_G2D_VRAM_TYPE_2DMAIN,
    .resources = {
        0xC8,
        0x4E26,
        0xC7,
        0xC6,
        SPRITE_RESOURCE_NONE,
        SPRITE_RESOURCE_NONE,
    },
    .bgPriority = 0,
    .transferToVRAM = FALSE,
};

static const SpriteTemplate sHealthbarTemplate_EnemySlot1 = {
    .x = HEALTHBAR_X_OFFSET_ENEMY_SLOT_1,
    .y = HEALTHBAR_Y_OFFSET_ENEMY_SLOT_1,
    .z = 0,
    .animIdx = 0,
    .priority = 25,
    .plttIdx = 0,
    .vramType = NNS_G2D_VRAM_TYPE_2DMAIN,
    .resources = {
        0xC2,
        0x4E26,
        0xC1,
        0xC0,
        SPRITE_RESOURCE_NONE,
        SPRITE_RESOURCE_NONE,
    },
    .bgPriority = 0,
    .transferToVRAM = FALSE,
};

static const SpriteTemplate sHealthbarTemplate_PlayerSlot2 = {
    .x = HEALTHBAR_X_OFFSET_PLAYER_SLOT_2,
    .y = HEALTHBAR_Y_OFFSET_PLAYER_SLOT_2,
    .z = 0,
    .animIdx = 0,
    .priority = 26,
    .plttIdx = 0,
    .vramType = NNS_G2D_VRAM_TYPE_2DMAIN,
    .resources = {
        0xCB,
        0x4E26,
        0xCA,
        0xC9,
        SPRITE_RESOURCE_NONE,
        SPRITE_RESOURCE_NONE,
    },
    .bgPriority = 0,
    .transferToVRAM = FALSE,
};

static const SpriteTemplate sHealthbarTemplate_EnemySlot2 = {
    .x = HEALTHBAR_X_OFFSET_ENEMY_SLOT_2,
    .y = HEALTHBAR_Y_OFFSET_ENEMY_SLOT_2,
    .z = 0,
    .animIdx = 0,
    .priority = 27,
    .plttIdx = 0,
    .vramType = NNS_G2D_VRAM_TYPE_2DMAIN,
    .resources = {
        0xC5,
        0x4E26,
        0xC4,
        0xC3,
        SPRITE_RESOURCE_NONE,
        SPRITE_RESOURCE_NONE,
    },
    .bgPriority = 0,
    .transferToVRAM = FALSE,
};

static const SpriteTemplate Unk_ov16_0226F514 = {
    0x0,
    0x0,
    0x0,
    0x0,
    17,
    0x0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    {0xB9, 0x4E26, 0xB8, 0xB7, 0xFFFFFFFF, 0xFFFFFFFF},
    0x0,
    0x0
};

static const SpriteTemplate sHealthbarTemplate_NoPlayerMon = {
    .x = HEALTHBAR_X_OFFSET_SOLO_PLAYER,
    .y = HEALTHBAR_Y_OFFSET_SOLO_PLAYER,
    .z = 0,
    .animIdx = 0,
    .priority = 23,
    .plttIdx = 0,
    .vramType = NNS_G2D_VRAM_TYPE_2DMAIN,
    .resources = {
        0xFD,
        0x4E28,
        0xFE,
        0xFF,
        SPRITE_RESOURCE_NONE,
        SPRITE_RESOURCE_NONE,
    },
    .bgPriority = 0,
    .transferToVRAM = FALSE,
};

#include "overlay016/rodata_ov16_0226F6AC.h"

void ov16_02266F1C (SpriteRenderer * param0, SpriteGfxHandler * param1, NARC * param2, PaletteData * param3, int param4)
{
    const SpriteTemplate * v0;

    v0 = Healthbar_SpriteTemplate(param4);

    SpriteRenderer_LoadCharResObjFromOpenNarc(param0, param1, param2, v0->resources[0], 1, NNS_G2D_VRAM_TYPE_2DMAIN, v0->resources[0]);
    SpriteRenderer_LoadPalette(param3, 2, param0, param1, param2, 71, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 20006);
    SpriteRenderer_LoadCellResObjFromOpenNarc(param0, param1, param2, v0->resources[2], 1, v0->resources[2]);
    SpriteRenderer_LoadAnimResObjFromOpenNarc(param0, param1, param2, v0->resources[3], 1, v0->resources[3]);
    SpriteRenderer_LoadPalette(param3, 2, param0, param1, param2, 71, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 20007);

    if ((param4 == 6) || (param4 == 7)) {
        SpriteRenderer_LoadPalette(param3, 2, param0, param1, param2, 81, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 20008);
    }
}

static void ov16_02266FE4 (SpriteRenderer * param0, SpriteGfxHandler * param1, NARC * param2, PaletteData * param3, int param4)
{
    const SpriteTemplate * v0;

    v0 = ov16_02268314(param4);

    if (v0 != NULL) {
        SpriteRenderer_LoadCharResObjFromOpenNarc(param0, param1, param2, v0->resources[0], 1, NNS_G2D_VRAM_TYPE_2DMAIN, v0->resources[0]);
        SpriteRenderer_LoadPalette(param3, 2, param0, param1, param2, 71, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 20006);
        SpriteRenderer_LoadCellResObjFromOpenNarc(param0, param1, param2, v0->resources[2], 1, v0->resources[2]);
        SpriteRenderer_LoadAnimResObjFromOpenNarc(param0, param1, param2, v0->resources[3], 1, v0->resources[3]);
    }
}

CellActorData * ov16_02267060 (SpriteRenderer * param0, SpriteGfxHandler * param1, int param2)
{
    const SpriteTemplate * v0;
    CellActorData * v1;

    v0 = Healthbar_SpriteTemplate(param2);
    v1 = SpriteActor_LoadResources(param0, param1, v0);

    SpriteActor_UpdateObject(v1->unk_00);
    return v1;
}

void Healthbar_DrawInfo(Healthbar *healthbar, u32 hp, u32 flags)
{
    BOOL caughtSpecies = FALSE;

    GF_ASSERT(healthbar->mainActor != NULL);

    u32 flagsCopy = flags;

    if (healthbar->type == HEALTHBAR_TYPE_SAFARI_ZONE) {
        flags &= HEALTHBAR_INFO_ALL_SAFARI;
    } else if (healthbar->type == HEALTHBAR_TYPE_PAL_PARK) {
        flags &= HEALTHBAR_INFO_ALL_PARK;
    } else {
        flags &= ~(HEALTHBAR_INFO_ALL_SAFARI | HEALTHBAR_INFO_ALL_PARK);
    }

    switch (healthbar->type) {
    case HEALTHBAR_TYPE_ENEMY_SOLO:
    case HEALTHBAR_TYPE_ENEMY_SLOT_1:
    case HEALTHBAR_TYPE_ENEMY_SLOT_2:
        // Never display current HP, max HP, or the EXP bar on an enemy healthbar
        flags &= ~HEALTHBAR_INFO_NOT_ON_ENEMY;
        caughtSpecies = TRUE;
        break;

    case HEALTHBAR_TYPE_PLAYER_SLOT_1:
    case HEALTHBAR_TYPE_PLAYER_SLOT_2:
        // Never display the EXP bar in doubles
        flags &= ~(HEALTHBAR_INFO_EXP_GAUGE | HEALTHBAR_INFO_CAUGHT_SPECIES);

        // Allow toggling between showing the HP bar and raw current/max numbers
        if (healthbar->numberMode == FALSE) {
            flags &= ~(HEALTHBAR_INFO_CURRENT_HP | HEALTHBAR_INFO_MAX_HP);
        } else {
            flags &= ~HEALTHBAR_INFO_HP_GAUGE;
        }
        break;

    case HEALTHBAR_TYPE_PLAYER_SOLO:
        // Never show the pokeball icon on a player's healthbar for a captured species
        flags &= ~HEALTHBAR_INFO_CAUGHT_SPECIES;
        break;

    case HEALTHBAR_TYPE_SAFARI_ZONE:
    case HEALTHBAR_TYPE_PAL_PARK:
        break;
    }

    if (BattleSystem_BattleType(healthbar->battleSys) & BATTLE_TYPE_TRAINER) {
        // Never show the pokeball icon on an enemy trainer's healthbar
        flags &= ~HEALTHBAR_INFO_CAUGHT_SPECIES;
    }

    if (flags & HEALTHBAR_INFO_HP_GAUGE) {
        ov16_022674C4(healthbar, 0);
        ov16_02267EDC(healthbar, 0);
    }

    if (flags & HEALTHBAR_INFO_CURRENT_HP) {
        ov16_02267B6C(healthbar, hp);
    }

    if (flags & HEALTHBAR_INFO_MAX_HP) {
        ov16_02267BF8(healthbar);
    }

    if ((flags & HEALTHBAR_INFO_LEVEL_TEXT) || (flags & HEALTHBAR_INFO_GENDER)) {
        ov16_022679C8(healthbar);
    }

    if (flags & HEALTHBAR_INFO_LEVEL) {
        ov16_02267A4C(healthbar);
    }

    if (flags & HEALTHBAR_INFO_NAME) {
        ov16_02267864(healthbar);
    }

    if (flags & HEALTHBAR_INFO_EXP_GAUGE) {
        ov16_0226752C(healthbar, 0);
        ov16_02267EDC(healthbar, 1);
    }

    if (flags & HEALTHBAR_INFO_CAUGHT_SPECIES) {
        ov16_02267C58(healthbar);
    }

    if (flags & HEALTHBAR_INFO_STATUS) {
        switch (healthbar->status) {
        default:
        case 0:
            ov16_02267CA8(healthbar, 38);
            break;
        case 1:
            ov16_02267CA8(healthbar, 47);
            break;
        case 2:
            ov16_02267CA8(healthbar, 50);
            break;
        case 3:
            ov16_02267CA8(healthbar, 53);
            break;
        case 4:
            ov16_02267CA8(healthbar, 44);
            break;
        case 5:
            ov16_02267CA8(healthbar, 41);
            break;
        }
    }

    if (flags & (HEALTHBAR_INFO_COUNT_SAFARI_BALLS | HEALTHBAR_INFO_COUNT_PARK_BALLS)) {
        ov16_02267CE8(healthbar, flags);
    }

    if (flags & (HEALTHBAR_INFO_REMAINING_SAFARI_BALLS | HEALTHBAR_INFO_REMAINING_PARK_BALLS)) {
        ov16_02267DC4(healthbar, flags);
    }
}

void ov16_02267220 (Healthbar * param0)
{
    if (param0->unk_50 != NULL) {
        SysTask_Done(param0->unk_50);
        param0->unk_50 = NULL;
    }

    if (param0->mainActor == NULL) {
        return;
    }

    sub_0200D0F4(param0->mainActor);
    param0->mainActor = NULL;
}

static void ov16_02267244 (Healthbar * param0)
{
    if (param0->arrowActor == NULL) {
        return;
    }

    sub_0200D0F4(param0->arrowActor);
    param0->arrowActor = NULL;
}

void ov16_02267258 (Healthbar * param0)
{
    SpriteRenderer * v0;
    SpriteGfxHandler * v1;
    const SpriteTemplate * v2;

    v2 = Healthbar_SpriteTemplate(param0->type);
    v0 = ov16_0223E010(param0->battleSys);
    v1 = ov16_0223E018(param0->battleSys);

    SpriteGfxHandler_UnloadCharObjById(v1, v2->resources[0]);
    SpriteGfxHandler_UnloadCellObjById(v1, v2->resources[2]);
    SpriteGfxHandler_UnloadAnimObjById(v1, v2->resources[3]);
}

static void ov16_0226728C (Healthbar * param0)
{
    SpriteRenderer * v0;
    SpriteGfxHandler * v1;
    const SpriteTemplate * v2;

    v2 = ov16_02268314(param0->type);

    if (v2 == NULL) {
        return;
    }

    v0 = ov16_0223E010(param0->battleSys);
    v1 = ov16_0223E018(param0->battleSys);

    SpriteGfxHandler_UnloadCharObjById(v1, v2->resources[0]);
    SpriteGfxHandler_UnloadCellObjById(v1, v2->resources[2]);
    SpriteGfxHandler_UnloadAnimObjById(v1, v2->resources[3]);
}

void ov16_022672C4 (Healthbar * param0)
{
    const SpriteTemplate * v0;
    SpriteRenderer * v1;
    SpriteGfxHandler * v2;
    PaletteData * v3;
    NARC * v4;

    v4 = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__PL_BATT_OBJ, 5);
    v1 = ov16_0223E010(param0->battleSys);
    v2 = ov16_0223E018(param0->battleSys);
    v3 = BattleSystem_PaletteSys(param0->battleSys);
    v0 = Healthbar_SpriteTemplate(param0->type);

    ov16_02266F1C(v1, v2, v4, v3, param0->type);
    param0->mainActor = ov16_02267060(v1, v2, param0->type);

    ov16_02266FE4(v1, v2, v4, v3, param0->type);

    if (param0->arrowActor != NULL) {
        SpriteActor_SetPositionXY(param0->arrowActor->unk_00, v0->x - sArrowOffsetX[param0->type], v0->y + 0);
    }

    NARC_dtor(v4);
}

void ov16_02267360 (Healthbar * param0)
{
    ov16_02267220(param0);
    ov16_02267258(param0);
    ov16_02267244(param0);
    ov16_0226728C(param0);
}

void ov16_0226737C (Healthbar * param0)
{
    const u8 * v0;
    NNSG2dImageProxy * v1;
    void * v2;

    switch (param0->type) {
    case 2:
    case 4:
        break;
    default:
        return;
    }

    param0->numberMode ^= 1;

    v2 = G2_GetOBJCharPtr();
    v1 = sub_02021F98(param0->mainActor->unk_00);

    if (param0->numberMode == 1) {
        v0 = ov16_02268250(70);
        MI_CpuCopy16(v0, (void *)((u32)v2 + Unk_ov16_0226F374[param0->type].unk_00 + 0x20 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);
        v0 = ov16_02268250(71);
        MI_CpuCopy16(v0, (void *)((u32)v2 + Unk_ov16_0226F3A4[param0->type].unk_00 + 0x20 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);

        v0 = ov16_02268250(69);
        MI_CpuCopy16(v0, (void *)((u32)v2 + Unk_ov16_0226F3D4[param0->type].unk_00 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F3D4[param0->type].unk_02);

        Healthbar_DrawInfo(param0, param0->unk_28, HEALTHBAR_INFO_CURRENT_HP | HEALTHBAR_INFO_MAX_HP);
    } else {
        v0 = ov16_02268250(66);
        MI_CpuCopy16(v0, (void *)((u32)v2 + Unk_ov16_0226F374[param0->type].unk_00 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F374[param0->type].unk_02);

        v0 = ov16_02268250(68);
        MI_CpuCopy16(v0, (void *)((u32)v2 + Unk_ov16_0226F3A4[param0->type].unk_00 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F3A4[param0->type].unk_02);

        v0 = ov16_02268250(38);
        MI_CpuCopy16(v0, (void *)((u32)v2 + Unk_ov16_0226F3A4[param0->type].unk_00 + 0x20 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);

        Healthbar_DrawInfo(param0, param0->unk_28, HEALTHBAR_INFO_HP_GAUGE);
    }
}

void ov16_022674C4 (Healthbar * param0, int param1)
{
    param0->unk_34 = -2147483648;

    if (param0->unk_28 + param1 < 0) {
        param1 -= param0->unk_28 + param1;
    }

    if (param0->unk_28 + param1 > param0->unk_2C) {
        param1 -= (param0->unk_28 + param1) - param0->unk_2C;
    }

    param0->unk_30 = -param1;

    if (param0->unk_28 < 0) {
        param0->unk_28 = 0;
    }

    if (param0->unk_28 > param0->unk_2C) {
        param0->unk_28 = param0->unk_2C;
    }
}

s32 ov16_022674F8 (Healthbar * param0)
{
    s32 v0;

    v0 = ov16_02267EDC(param0, 0);

    if (v0 == -1) {
        param0->unk_28 -= param0->unk_30;
        Healthbar_DrawInfo(param0, param0->unk_28, HEALTHBAR_INFO_CURRENT_HP);
    } else {
        Healthbar_DrawInfo(param0, v0, HEALTHBAR_INFO_CURRENT_HP);
    }

    return v0;
}

void ov16_0226752C (Healthbar * param0, int param1)
{
    param0->unk_44 = -2147483648;

    if (param0->unk_38 + param1 < 0) {
        param1 -= param0->unk_38 + param1;
    }

    if (param0->unk_38 + param1 > param0->unk_3C) {
        param1 -= (param0->unk_38 + param1) - param0->unk_3C;
    }

    param0->unk_40 = -param1;

    if (param0->unk_38 < 0) {
        param0->unk_38 = 0;
    }

    if (param0->unk_38 > param0->unk_3C) {
        param0->unk_38 = param0->unk_3C;
    }
}

s32 ov16_02267560 (Healthbar * param0)
{
    s32 v0;

    v0 = ov16_02267EDC(param0, 1);

    if (v0 == -1) {
        param0->unk_38 -= param0->unk_40;
    }

    return v0;
}

void ov16_0226757C (Healthbar * param0)
{
    if (param0->arrowActor != NULL) {
        sub_02021CC8(param0->arrowActor->unk_00, 1);
        Healthbar_EnableArrow(param0, 1);
    }

    if ((BattleSystem_BattleType(param0->battleSys) & (0x20 | 0x200)) == 0) {
        ov16_02268470(param0);
    }
}

void ov16_022675AC (Healthbar * param0)
{
    if (param0->arrowActor != NULL) {
        sub_02021CC8(param0->arrowActor->unk_00, 0);
        SpriteActor_SetAnimFrame(param0->arrowActor->unk_00, 0);
        Healthbar_EnableArrow(param0, 0);
    }

    ov16_02268498(param0);
}

void ov16_022675D8 (Healthbar * param0, int param1)
{
    if (param0->mainActor == NULL) {
        return;
    }

    sub_0200D460(param0->mainActor, param1);

    if (param0->arrowActor != NULL) {
        sub_0200D460(param0->arrowActor, param1);
    }
}

/**
 * @brief Enable the extended arrow-graphic used by the healthbar for Pokemon battlers.
 * 
 * @param battleSys 
 * @param enable 
 */
static void Healthbar_EnableArrow(Healthbar *battleSys, BOOL enable)
{
    if (battleSys->arrowActor == NULL) {
        return;
    }

    // Safari battles don't get an arrow.
    if ((BattleSystem_BattleType(battleSys->battleSys) & (BATTLE_TYPE_SAFARI | BATTLE_TYPE_PAL_PARK))
            && enable == TRUE) {
        return;
    }

    SpriteActor_EnableObject(battleSys->arrowActor, enable);
}

void Healthbar_Enable(Healthbar *battleSys, BOOL enable)
{
    if (battleSys->mainActor == NULL) {
        return;
    }

    SpriteActor_EnableObject(battleSys->mainActor, enable);
    Healthbar_EnableArrow(battleSys, enable);
}

void Healthbar_OffsetPositionXY(Healthbar *healthbar, int x, int y)
{
    GF_ASSERT(healthbar->mainActor != NULL);
    const SpriteTemplate *template = Healthbar_SpriteTemplate(healthbar->type);

    SpriteActor_SetPositionXY(healthbar->mainActor->unk_00, template->x + x, template->y + y);
    if (healthbar->arrowActor != NULL) {
        SpriteActor_SetPositionXY(healthbar->arrowActor->unk_00,
            template->x + x - sArrowOffsetX[healthbar->type],
            template->y + y + 0);
    }
}

void Healthbar_Scroll(Healthbar *healthbar, enum HealthbarScrollDirection direction)
{
    GF_ASSERT(healthbar != NULL);
    GF_ASSERT(healthbar->mainActor != NULL);

    healthbar->doneScrolling = 0;
    healthbar->scrollDirection = direction;

    if (direction == HEALTHBAR_SCROLL_IN) {
        switch (healthbar->type) {
        case HEALTHBAR_TYPE_PLAYER_SOLO:
        case HEALTHBAR_TYPE_PLAYER_SLOT_1:
        case HEALTHBAR_TYPE_PLAYER_SLOT_2:
        case HEALTHBAR_TYPE_SAFARI_ZONE:
        case HEALTHBAR_TYPE_PAL_PARK:
            // Player-side healthbar
            Healthbar_OffsetPositionXY(healthbar, HEALTHBAR_SCROLL_OUT_OFFSET, 0);
            break;

        default:
            // Enemy-side healthbar
            Healthbar_OffsetPositionXY(healthbar, -HEALTHBAR_SCROLL_OUT_OFFSET, 0);
            break;
        }
    } else {
        Healthbar_OffsetPositionXY(healthbar, 0, 0);
    }

    SysTask_Start(ScrollHealthbarTask, healthbar, 990);
}

/**
 * @brief Scroll the healthbar in or out by the configured scroll-speed value.
 * 
 * @param task 
 * @param data 
 */
static void ScrollHealthbarTask(SysTask *task, void *data)
{
    Healthbar *healthbar = data;
    int done = 0;
    const SpriteTemplate *template = Healthbar_SpriteTemplate(healthbar->type);

    s16 x, y;
    SpriteActor_GetSpritePositionXY(healthbar->mainActor, &x, &y);

    // Determine new X and Y based on the type of healthbar
    switch (healthbar->type) {
    case HEALTHBAR_TYPE_PLAYER_SOLO:
    case HEALTHBAR_TYPE_PLAYER_SLOT_1:
    case HEALTHBAR_TYPE_PLAYER_SLOT_2:
    case HEALTHBAR_TYPE_SAFARI_ZONE:
    case HEALTHBAR_TYPE_PAL_PARK:
        // Player-side healthbar
        if (healthbar->scrollDirection == HEALTHBAR_SCROLL_IN) {
            x -= HEALTHBAR_SCROLL_SPEED;

            if (x < template->x) {
                x = template->x;
                done++;
            }
        } else {
            x += HEALTHBAR_SCROLL_SPEED;

            if (x > template->x + HEALTHBAR_SCROLL_OUT_OFFSET) {
                x = template->x + HEALTHBAR_SCROLL_OUT_OFFSET;
                done++;
            }
        }
        break;

    default:
        // Enemy-side healthbar
        if (healthbar->scrollDirection == HEALTHBAR_SCROLL_IN) {
            x += HEALTHBAR_SCROLL_SPEED;

            if (x > template->x) {
                x = template->x;
                done++;
            }
        } else {
            x -= HEALTHBAR_SCROLL_SPEED;

            if (x < template->x - HEALTHBAR_SCROLL_SPEED) {
                x = template->x - HEALTHBAR_SCROLL_SPEED;
                done++;
            }
        }
        break;
    }

    // Update positions of the sprites on the screen
    SpriteActor_SetSpritePositionXY(healthbar->mainActor, x, y);
    if (healthbar->arrowActor != NULL) {
        SpriteActor_SetSpritePositionXY(healthbar->arrowActor, x - sArrowOffsetX[healthbar->type], y + 0);
    }

    // If the sprites are now in position, we're done
    if (done > 0) {
        healthbar->doneScrolling = TRUE;
        SysTask_Done(task);
    }
}

static void ov16_02267864 (Healthbar * param0)
{
    BGL * v0;
    u8 * v1;
    NNSG2dImageProxy * v2;
    Window v3;
    MessageLoader * v4;
    Strbuf* v5, * v6;
    Pokemon * v7;
    BoxPokemon * v8;
    UnkStruct_0200B358 * v9;

    v0 = BattleSystem_BGL(param0->battleSys);
    v4 = BattleSystem_MessageLoader(param0->battleSys);
    v9 = ov16_0223E0D0(param0->battleSys);
    v5 = Strbuf_Init((12 + (5 * 2)), 5);
    v6 = MessageLoader_GetNewStrbuf(v4, 964);
    v7 = BattleSystem_PartyPokemon(param0->battleSys, param0->unk_24, param0->unk_26);
    v8 = Pokemon_GetBoxPokemon(v7);

    sub_0200B5CC(v9, 0, v8);
    StringFormatter_Format(v9, v5, v6);
    sub_0201A870(v0, &v3, 8, 2, 0, 0xf);
    sub_0201D7E0(&v3, 0, v5, 0, 0, 0xff, ((u32)(((0xe & 0xff) << 16) | ((2 & 0xff) << 8) | (((0xf & 0xff) << 0)))), 0, 0, NULL);

    v1 = v3.unk_0C;

    {
        void * v10;
        u8 * v11, * v12;

        v10 = G2_GetOBJCharPtr();
        v2 = sub_02021F98(param0->mainActor->unk_00);
        v11 = v1;
        v12 = &v1[8 * 0x20];

        MI_CpuCopy16(v11, (void *)((u32)v10 + Unk_ov16_0226F64C[param0->type][0].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F64C[param0->type][0].unk_02);
        MI_CpuCopy16(v12, (void *)((u32)v10 + Unk_ov16_0226F64C[param0->type][1].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F64C[param0->type][1].unk_02);

        MI_CpuCopy16(&v11[Unk_ov16_0226F64C[param0->type][0].unk_02], (void *)((u32)v10 + Unk_ov16_0226F64C[param0->type][2].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F64C[param0->type][2].unk_02);
        MI_CpuCopy16(&v12[Unk_ov16_0226F64C[param0->type][1].unk_02], (void *)((u32)v10 + Unk_ov16_0226F64C[param0->type][3].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F64C[param0->type][3].unk_02);
    }

    BGL_DeleteWindow(&v3);
    Strbuf_Free(v5);
    Strbuf_Free(v6);
}

static void ov16_022679C8 (Healthbar * param0)
{
    NNSG2dImageProxy * v0;
    const u8 * v1;
    const u8 * v2;
    int v3, v4;

    if (param0->unk_49 == 0) {
        v3 = 74;
        v4 = 62;
    } else if (param0->unk_49 == 1) {
        v3 = 72;
        v4 = 60;
    } else {
        v3 = 76;
        v4 = 64;
    }

    v1 = ov16_02268250(v3);
    v2 = ov16_02268250(v4);

    {
        void * v5;

        v5 = G2_GetOBJCharPtr();
        v0 = sub_02021F98(param0->mainActor->unk_00);

        MI_CpuCopy16(v2, (void *)((u32)v5 + Unk_ov16_0226F47C[param0->type][0].unk_00 + v0->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F47C[param0->type][0].unk_02);
        MI_CpuCopy16(v1, (void *)((u32)v5 + Unk_ov16_0226F47C[param0->type][1].unk_00 + v0->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F47C[param0->type][1].unk_02);
    }
}

static void ov16_02267A4C (Healthbar * param0)
{
    u8 * v0, * v1;
    NNSG2dImageProxy * v2;
    int v3, v4, v5, v6;

    v3 = 3 * 0x20;
    v0 = Heap_AllocFromHeap(5, v3);
    v1 = Heap_AllocFromHeap(5, v3 * 2);

    MI_CpuFill8(v0, 0xf | (0xf << 4), v3);
    sub_0200C67C(ov16_0223E054(param0->battleSys), param0->unk_48, 3, 0, v0);

    {
        void * v7;
        u8 * v8, * v9;

        v7 = G2_GetOBJCharPtr();
        v2 = sub_02021F98(param0->mainActor->unk_00);

        MI_CpuCopy16((void *)((u32)v7 + Unk_ov16_0226F3EC[param0->type][0].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), v1, Unk_ov16_0226F3EC[param0->type][0].unk_02);
        MI_CpuCopy16((void *)((u32)v7 + Unk_ov16_0226F3EC[param0->type][1].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), &v1[v3], Unk_ov16_0226F3EC[param0->type][1].unk_02);

        v6 = 0;

        for (v5 = 0; v5 < v3; v5 += 32) {
            for (v4 = 0; v4 < 16; v4++) {
                v1[v5 + 16 + v4] = v0[v6];
                v1[v5 + v4 + v3] = v0[v6 + 16];
                v6++;
            }

            v6 += 16;
        }

        v8 = v1;
        v9 = &v1[v3];

        MI_CpuCopy16(v8, (void *)((u32)v7 + Unk_ov16_0226F3EC[param0->type][0].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F3EC[param0->type][0].unk_02);
        MI_CpuCopy16(v9, (void *)((u32)v7 + Unk_ov16_0226F3EC[param0->type][1].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F3EC[param0->type][1].unk_02);
    }

    Heap_FreeToHeap(v0);
    Heap_FreeToHeap(v1);
}

static void ov16_02267B6C (Healthbar * param0, u32 param1)
{
    u8 * v0;
    NNSG2dImageProxy * v1;

    v0 = Heap_AllocFromHeap(5, 3 * 0x20);

    MI_CpuFill8(v0, 0xf | (0xf << 4), 3 * 0x20);
    sub_0200C67C(ov16_0223E04C(param0->battleSys), param1, 3, 1, v0);

    {
        void * v2;
        u8 * v3;

        v2 = G2_GetOBJCharPtr();
        v1 = sub_02021F98(param0->mainActor->unk_00);
        v3 = v0;

        MI_CpuCopy16(v3, (void *)((u32)v2 + Unk_ov16_0226F41C[param0->type][0].unk_00 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F41C[param0->type][0].unk_02);
        MI_CpuCopy16(&v3[Unk_ov16_0226F41C[param0->type][0].unk_02], (void *)((u32)v2 + Unk_ov16_0226F41C[param0->type][1].unk_00 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F41C[param0->type][1].unk_02);
    }

    Heap_FreeToHeap(v0);
}

static void ov16_02267BF8 (Healthbar * param0)
{
    u8 * v0;
    NNSG2dImageProxy * v1;

    v0 = Heap_AllocFromHeap(5, 3 * 0x20);

    MI_CpuFill8(v0, 0xf | (0xf << 4), 3 * 0x20);
    sub_0200C67C(ov16_0223E04C(param0->battleSys), param0->unk_2C, 3, 0, v0);

    {
        void * v2;
        u8 * v3;

        v2 = G2_GetOBJCharPtr();
        v1 = sub_02021F98(param0->mainActor->unk_00);
        v3 = v0;

        MI_CpuCopy16(v3, (void *)((u32)v2 + Unk_ov16_0226F3BC[param0->type].unk_00 + v1->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F3BC[param0->type].unk_02);
    }

    Heap_FreeToHeap(v0);
}

static void ov16_02267C58 (Healthbar * param0)
{
    NNSG2dImageProxy * v0;
    const u8 * v1;

    if (param0->unk_4B == 1) {
        v1 = ov16_02268250(59);
    } else {
        v1 = ov16_02268250(38);
    }

    {
        void * v2;

        v2 = G2_GetOBJCharPtr();
        v0 = sub_02021F98(param0->mainActor->unk_00);

        MI_CpuCopy16(v1, (void *)((u32)v2 + Unk_ov16_0226F38C[param0->type].unk_00 + v0->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F38C[param0->type].unk_02);
    }
}

static void ov16_02267CA8 (Healthbar * param0, int param1)
{
    NNSG2dImageProxy * v0;
    const u8 * v1;

    v1 = ov16_02268250(param1);

    {
        void * v2;

        v2 = G2_GetOBJCharPtr();
        v0 = sub_02021F98(param0->mainActor->unk_00);

        MI_CpuCopy16(v1, (void *)((u32)v2 + Unk_ov16_0226F35C[param0->type].unk_00 + v0->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F35C[param0->type].unk_02);
    }
}

static void ov16_02267CE8 (Healthbar * param0, u32 param1)
{
    BGL * v0;
    u8 * v1;
    NNSG2dImageProxy * v2;
    Window v3;
    MessageLoader * v4;
    Strbuf* v5;

    v0 = BattleSystem_BGL(param0->battleSys);
    v4 = BattleSystem_MessageLoader(param0->battleSys);

    if (param1 & (1 << 10)) {
        v5 = MessageLoader_GetNewStrbuf(v4, 950);
    } else {
        v5 = MessageLoader_GetNewStrbuf(v4, 1220);
    }

    sub_0201A870(v0, &v3, 13, 2, 0, 0xf);
    sub_0201D7E0(&v3, 0, v5, 0, 0, 0xff, ((u32)(((0xe & 0xff) << 16) | ((2 & 0xff) << 8) | (((0xf & 0xff) << 0)))), 0, 0, NULL);

    v1 = v3.unk_0C;

    {
        void * v6;
        u8 * v7, * v8;

        v6 = G2_GetOBJCharPtr();
        v2 = sub_02021F98(param0->mainActor->unk_00);
        v7 = v1;
        v8 = &v1[13 * 0x20];

        MI_CpuCopy16(v7, (void *)((u32)v6 + Unk_ov16_0226F33C[0].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F33C[0].unk_02);
        MI_CpuCopy16(v8, (void *)((u32)v6 + Unk_ov16_0226F33C[1].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F33C[1].unk_02);

        MI_CpuCopy16(&v7[Unk_ov16_0226F33C[0].unk_02], (void *)((u32)v6 + Unk_ov16_0226F33C[2].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F33C[2].unk_02);
        MI_CpuCopy16(&v8[Unk_ov16_0226F33C[1].unk_02], (void *)((u32)v6 + Unk_ov16_0226F33C[3].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F33C[3].unk_02);
    }

    BGL_DeleteWindow(&v3);
    Strbuf_Free(v5);
}

static void ov16_02267DC4 (Healthbar * param0, u32 param1)
{
    BGL * v0;
    u8 * v1;
    NNSG2dImageProxy * v2;
    Window v3;
    MessageLoader * v4;
    Strbuf* v5, * v6;
    UnkStruct_0200B358 * v7;

    v0 = BattleSystem_BGL(param0->battleSys);
    v4 = BattleSystem_MessageLoader(param0->battleSys);
    v7 = ov16_0223E0D0(param0->battleSys);
    v5 = Strbuf_Init(30, 5);

    if (param1 & (1 << 10)) {
        v6 = MessageLoader_GetNewStrbuf(v4, 951);
    } else {
        v6 = MessageLoader_GetNewStrbuf(v4, 1221);
    }

    sub_0200B60C(v7, 0, param0->unk_27, 2, 1, 1);
    StringFormatter_Format(v7, v5, v6);
    sub_0201A870(v0, &v3, 13, 2, 0, 0xf);
    sub_0201D7E0(&v3, 0, v5, 0, 0, 0xff, ((u32)(((0xe & 0xff) << 16) | ((2 & 0xff) << 8) | (((0xf & 0xff) << 0)))), 0, 0, NULL);

    v1 = v3.unk_0C;

    {
        void * v8;
        u8 * v9, * v10;

        v8 = G2_GetOBJCharPtr();
        v2 = sub_02021F98(param0->mainActor->unk_00);
        v9 = v1;
        v10 = &v1[13 * 0x20];

        MI_CpuCopy16(v9, (void *)((u32)v8 + Unk_ov16_0226F34C[0].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F34C[0].unk_02);
        MI_CpuCopy16(v10, (void *)((u32)v8 + Unk_ov16_0226F34C[1].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F34C[1].unk_02);
        MI_CpuCopy16(&v9[Unk_ov16_0226F34C[0].unk_02], (void *)((u32)v8 + Unk_ov16_0226F34C[2].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F34C[2].unk_02);
        MI_CpuCopy16(&v10[Unk_ov16_0226F34C[1].unk_02], (void *)((u32)v8 + Unk_ov16_0226F34C[3].unk_00 + v2->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), Unk_ov16_0226F34C[3].unk_02);
    }

    BGL_DeleteWindow(&v3);
    Strbuf_Free(v5);
    Strbuf_Free(v6);
}

static s32 ov16_02267EDC (Healthbar * param0, int param1)
{
    s32 v0;
    s32 v1;

    if (param1 == 0) {
        v0 = ov16_022680D8(param0->unk_2C, param0->unk_28, param0->unk_30, &param0->unk_34, 6, 1);
    } else {
        v1 = ov16_02268210(param0->unk_38, param0->unk_40, param0->unk_3C, 12);

        if (v1 == 0) {
            v1 = 1;
        }

        v1 = abs(param0->unk_40 / v1);
        v0 = ov16_022680D8(param0->unk_3C, param0->unk_38, param0->unk_40, &param0->unk_44, 12, v1);
    }

    if ((param1 == 0) && (param0->numberMode == 1)) {
        (void)0;
    } else {
        ov16_02267F70(param0, param1);
    }

    if (v0 == -1) {
        if (param1 == 0) {
            param0->unk_34 = 0;
        } else {
            param0->unk_44 = 0;
        }
    }

    return v0;
}

static void ov16_02267F70 (Healthbar * param0, u8 param1)
{
    u8 v0;
    u8 v1[12];
    u8 v2, v3;
    u8 v4;
    u8 v5;
    const u8 * v6;
    void * v7;
    NNSG2dImageProxy * v8;
    int v9;

    v7 = G2_GetOBJCharPtr();
    v8 = sub_02021F98(param0->mainActor->unk_00);

    switch (param1) {
    case 0:
        v4 = ov16_02268194(param0->unk_2C, param0->unk_28, param0->unk_30, &param0->unk_34, v1, 6);

        {
            int v10;

            v10 = App_BarColor(v4, (8 * 6));

            switch (v10) {
            case 3:
                v3 = 2;
                break;
            case 2:
                v3 = 11;
                break;
            case 1:
            default:
                v3 = 20;
                break;
            }
        }

        v6 = ov16_02268250(v3);
        v9 = Unk_ov16_0226F44C[param0->type][0].unk_02 / 0x20;

        for (v0 = 0; v0 < 6; v0++) {
            if (v0 < v9) {
                MI_CpuCopy16(v6 + (v1[v0] << 5), (void *)((u32)v7 + Unk_ov16_0226F44C[param0->type][0].unk_00 + (v0 * 0x20) + v8->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);
            } else {
                MI_CpuCopy16(v6 + (v1[v0] << 5), (void *)((u32)v7 + Unk_ov16_0226F44C[param0->type][1].unk_00 + ((v0 - v9) * 0x20) + v8->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);
            }
        }
        break;
    case 1:
        ov16_02268194(param0->unk_3C, param0->unk_38, param0->unk_40, &param0->unk_44, v1, 12);
        v5 = param0->unk_48;

        if (v5 == 100) {
            for (v0 = 0; v0 < 12; v0++) {
                v1[v0] = 0;
            }
        }

        v6 = ov16_02268250(29);

        for (v0 = 0; v0 < 12; v0++) {
            if (v0 < 5) {
                MI_CpuCopy16(v6 + (v1[v0] << 5), (void *)((u32)v7 + 1632 + (v0 * 0x20) + v8->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);
            } else {
                MI_CpuCopy16(v6 + (v1[v0] << 5), (void *)((u32)v7 + 3584 + ((v0 - 5) * 0x20) + v8->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);
            }
        }
        break;
    }
}

static s32 ov16_022680D8 (s32 param0, s32 param1, s32 param2, s32 * param3, u8 param4, u16 param5)
{
    s32 v0;
    s32 v1;
    u8 v2;
    s32 v3;

    v2 = param4 * 8;

    if (*param3 == -2147483648) {
        if (param0 < v2) {
            *param3 = param1 << 8;
        } else {
            *param3 = param1;
        }
    }

    v0 = param1 - param2;

    if (v0 < 0) {
        v0 = 0;
    } else if (v0 > param0) {
        v0 = param0;
    }

    if (param0 < v2) {
        if ((v0 == (*param3 >> 8)) && ((*param3 & 0xff) == 0)) {
            return -1;
        }
    } else {
        if (v0 == *param3) {
            return -1;
        }
    }

    if (param0 < v2) {
        v3 = param0 * 0x100 / v2;

        if (param2 < 0) {
            *param3 += v3;
            v1 = *param3 >> 8;

            if (v1 >= v0) {
                *param3 = v0 << 8;
                v1 = v0;
            }
        } else {
            *param3 -= v3;
            v1 = *param3 >> 8;

            if ((*param3 & 0xff) > 0) {
                v1++;
            }

            if (v1 <= v0) {
                *param3 = v0 << 8;
                v1 = v0;
            }
        }
    } else {
        if (param2 < 0) {
            *param3 += param5;

            if (*param3 > v0) {
                *param3 = v0;
            }
        } else {
            *param3 -= param5;

            if (*param3 < v0) {
                *param3 = v0;
            }
        }

        v1 = *param3;
    }

    return v1;
}

static u8 ov16_02268194 (s32 param0, s32 param1, s32 param2, s32 * param3, u8 * param4, u8 param5)
{
    int v0;
    u32 v1;
    u32 v2, v3;
    s32 v4;

    v4 = param1 - param2;

    if (v4 < 0) {
        v4 = 0;
    } else if (v4 > param0) {
        v4 = param0;
    }

    v1 = 8 * param5;

    for (v0 = 0; v0 < param5; v0++) {
        param4[v0] = 0;
    }

    if (param0 < v1) {
        v2 = (*param3 * v1 / param0) >> 8;
    } else {
        v2 = *param3 * v1 / param0;
    }

    v3 = v2;

    if ((v2 == 0) && (v4 > 0)) {
        param4[0] = 1;
        v3 = 1;
    } else {
        for (v0 = 0; v0 < param5; v0++) {
            if (v2 >= 8) {
                param4[v0] = 8;
                v2 -= 8;
            } else {
                param4[v0] = v2;
                break;
            }
        }
    }

    return v3;
}

static u32 ov16_02268210 (s32 param0, s32 param1, s32 param2, u8 param3)
{
    s8 v0, v1;
    u8 v2;
    s32 v3;

    v2 = param3 * 8;
    v3 = param0 - param1;

    if (v3 < 0) {
        v3 = 0;
    } else if (v3 > param2) {
        v3 = param2;
    }

    v0 = param0 * v2 / param2;
    v1 = v3 * v2 / param2;

    return abs(v0 - v1);
}

static const u8 * ov16_02268250 (int param0)
{
    return &Unk_ov16_0226F6AC[param0 * 0x20];
}

u8 Healthbar_Type(int battlerType, u32 battleType)
{
    switch (battlerType) {
    case BATTLER_TYPE_SOLO_PLAYER:
        if (battleType & BATTLE_TYPE_PAL_PARK) {
            return HEALTHBAR_TYPE_PAL_PARK;
        }

        if (battleType & BATTLE_TYPE_SAFARI) {
            return HEALTHBAR_TYPE_SAFARI_ZONE;
        }

        return HEALTHBAR_TYPE_PLAYER_SOLO;

    case BATTLER_TYPE_SOLO_ENEMY:
        return HEALTHBAR_TYPE_ENEMY_SOLO;

    case BATTLER_TYPE_PLAYER_SIDE_SLOT_1:
        return HEALTHBAR_TYPE_PLAYER_SLOT_1;

    case BATTLER_TYPE_ENEMY_SIDE_SLOT_1:
        return HEALTHBAR_TYPE_ENEMY_SLOT_1;

    case BATTLER_TYPE_PLAYER_SIDE_SLOT_2:
        return HEALTHBAR_TYPE_PLAYER_SLOT_2;

    case BATTLER_TYPE_ENEMY_SIDE_SLOT_2:
        return HEALTHBAR_TYPE_ENEMY_SLOT_2;

    default:
        GF_ASSERT(FALSE);
        return NULL;
    }
}

/**
 * @brief Grab the sprite template that applies to a given healthbar type.
 * 
 * @param type  The healthbar type. See enum HealthbarType for accepted values.
 * @return      Address of the SpriteTemplate struct which applies to this
 *              healthbar type.
 */
static const SpriteTemplate* Healthbar_SpriteTemplate(u8 type)
{
    switch (type) {
    case HEALTHBAR_TYPE_PLAYER_SOLO:
        return &sHealthbarTemplate_SoloPlayer;

    case HEALTHBAR_TYPE_ENEMY_SOLO:
        return &sHealthbarTemplate_SoloEnemy;

    case HEALTHBAR_TYPE_PLAYER_SLOT_1:
        return &sHealthbarTemplate_PlayerSlot1;

    case HEALTHBAR_TYPE_ENEMY_SLOT_1:
        return &sHealthbarTemplate_EnemySlot1;

    case HEALTHBAR_TYPE_PLAYER_SLOT_2:
        return &sHealthbarTemplate_PlayerSlot2;

    case HEALTHBAR_TYPE_ENEMY_SLOT_2:
        return &sHealthbarTemplate_EnemySlot2;

    case HEALTHBAR_TYPE_SAFARI_ZONE:
    case HEALTHBAR_TYPE_PAL_PARK:
        return &sHealthbarTemplate_NoPlayerMon;

    default:
        GF_ASSERT(FALSE);
        return NULL;
    }
}

static const SpriteTemplate * ov16_02268314 (u8 param0)
{
    const SpriteTemplate * v0;

    switch (param0) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 7:
        v0 = &Unk_ov16_0226F514;
        break;
    case 1:
    case 3:
    case 5:
        return NULL;
    default:
        GF_ASSERT(0);
        return NULL;
    }

    return v0;
}

void ov16_0226834C (Healthbar * param0, u8 * param1)
{
    UnkStruct_ov16_0226834C * v0;

    *param1 = 0;

    v0 = Heap_AllocFromHeap(5, sizeof(UnkStruct_ov16_0226834C));
    MI_CpuClear8(v0, sizeof(UnkStruct_ov16_0226834C));

    v0->unk_00 = param0;
    v0->unk_04 = param1;

    SysTask_Start(ov16_02268380, v0, 1000);
}

static void ov16_02268380 (SysTask * param0, void * param1)
{
    UnkStruct_ov16_0226834C * v0 = param1;
    SpriteGfxHandler * v1;
    int v2;
    PaletteData * v3;

    v1 = ov16_0223E018(v0->unk_00->battleSys);
    v3 = BattleSystem_PaletteSys(v0->unk_00->battleSys);

    switch (v0->unk_08) {
    case 0:
        v2 = sub_0200D05C(v1, 20007, NNS_G2D_VRAM_TYPE_2DMAIN);
        sub_0200D41C(v0->unk_00->mainActor, v2);
        v0->unk_09 = v2;
        v0->unk_08++;
    case 1:
        v0->unk_0A += 2;

        if (v0->unk_0A >= 10) {
            v0->unk_0A = 10;
            v0->unk_08++;
        }

        sub_020039B0(v3, 2, v0->unk_09 * 16 + 0, 16, v0->unk_0A, 0x73a5);
        break;
    case 2:
        v0->unk_0A -= 2;

        if (v0->unk_0A <= 0) {
            v0->unk_0A = 0;
            v0->unk_08++;
        }

        sub_020039B0(v3, 2, v0->unk_09 * 16 + 0, 16, v0->unk_0A, 0x73a5);
        break;
    default:
        v2 = sub_0200D05C(v1, 20006, NNS_G2D_VRAM_TYPE_2DMAIN);
        sub_0200D41C(v0->unk_00->mainActor, v2);

        (*(v0->unk_04)) = 1;

        Heap_FreeToHeap(param1);
        SysTask_Done(param0);

        return;
    }
}

void ov16_02268468 (Healthbar * param0)
{
    return;
}

void ov16_0226846C (Healthbar * param0)
{
    return;
}

void ov16_02268470 (Healthbar * param0)
{
    if (param0->unk_50 != NULL) {
        return;
    }

    param0->unk_54 = 0;
    param0->unk_50 = SysTask_Start(ov16_022684BC, param0, 1010);
}

void ov16_02268498 (Healthbar * param0)
{
    if (param0->unk_50 != NULL) {
        SysTask_Done(param0->unk_50);
        param0->unk_50 = NULL;
    }

    param0->unk_54 = 0;
    Healthbar_OffsetPositionXY(param0, 0, 0);
}

static void ov16_022684BC (SysTask * param0, void * param1)
{
    Healthbar * v0 = param1;
    int v1;

    v0->unk_54 += 20;

    if (v0->unk_54 >= 360) {
        v0->unk_54 -= 360;
    }

    v1 = FX_Mul(sub_0201D15C(v0->unk_54), 0x1800) / FX32_ONE;
    Healthbar_OffsetPositionXY(v0, 0, v1);
}
