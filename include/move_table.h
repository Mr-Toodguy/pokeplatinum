#ifndef POKEPLATINUM_MOVE_TABLE_H
#define POKEPLATINUM_MOVE_TABLE_H

typedef struct MoveContestData {
    u8 effect;
    u8 type;
    u8 padding02[2]; // needed to match
} MoveContestData;

typedef struct MoveTable {
    u16 effect;
    u8 class;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 effectChance;
    u16 range;
    s8 priority;
    u8 flags;
    MoveContestData contest;
} MoveTable;

typedef enum MoveAttribute {
    MOVEATTRIBUTE_EFFECT = 0,
    MOVEATTRIBUTE_CLASS,
    MOVEATTRIBUTE_POWER,
    MOVEATTRIBUTE_TYPE,
    MOVEATTRIBUTE_ACCURACY,
    MOVEATTRIBUTE_PP,
    MOVEATTRIBUTE_EFFECT_CHANCE,
    MOVEATTRIBUTE_RANGE,
    MOVEATTRIBUTE_PRIORTY,
    MOVEATTRIBUTE_FLAGS,
    MOVEATTRIBUTE_CONTEST_EFFECT,
    MOVEATTRIBUTE_CONTEST_TYPE,
} MoveAttribute;

void MoveTable_Load(void * dest);
u32 MoveTable_LoadAttribute(int moveID, int attrno);
u8 MoveTable_CalcMaxPP(u16 moveID, u8 ppUps);
u32 MoveTable_Attribute(MoveTable * moveTable, int attribute);

#endif // POKEPLATINUM_MOVE_TABLE_H
