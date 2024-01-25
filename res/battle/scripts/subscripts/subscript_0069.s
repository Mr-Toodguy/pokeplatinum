    .include "macros/btlcmd.inc"

    .data

_000:
    PlayBattleAnimationOnMons BTLSCR_MSG_ATTACKER, BTLSCR_MSG_DEFENDER, BATTLE_ANIMATION_DAMAGE_LEECH_SEED
    Wait 
    UpdateMonDataFromVar OPCODE_GET, BTLSCR_MSG_DEFENDER, BATTLEMON_MAX_HP, BTLVAR_HP_CALC_TEMP
    DivideVarByValue BTLVAR_HP_CALC_TEMP, 8
    UpdateVar OPCODE_MUL, BTLVAR_HP_CALC_TEMP, -1
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_SKIP_SPRITE_BLINK
    UpdateVarFromVar OPCODE_SET, BTLVAR_MSG_BATTLER_TEMP, BTLVAR_MSG_DEFENDER
    Call BATTLE_SUBSCRIPT_UPDATE_HP
    UpdateVarFromVar OPCODE_SET, BTLVAR_HP_CALC_TEMP, BTLVAR_HIT_DAMAGE
    CheckItemHoldEffect CHECK_NOT_HAVE, BTLSCR_MSG_ATTACKER, HOLD_EFFECT_LEECH_BOOST, _050
    GetItemEffectParam BTLSCR_MSG_ATTACKER, BTLVAR_CALC_TEMP
    UpdateVar OPCODE_ADD, BTLVAR_CALC_TEMP, 0x00000064
    UpdateVarFromVar OPCODE_MUL, BTLVAR_HP_CALC_TEMP, BTLVAR_CALC_TEMP
    UpdateVar OPCODE_DIV, BTLVAR_HP_CALC_TEMP, 100

_050:
    UpdateVarFromVar OPCODE_SET, BTLVAR_MSG_BATTLER_TEMP, BTLVAR_MSG_ATTACKER
    UpdateVar OPCODE_FLAG_ON, BTLVAR_BATTLE_CTX_STATUS, SYSCTL_SKIP_SPRITE_BLINK
    CheckAbility CHECK_HAVE, BTLSCR_MSG_DEFENDER, ABILITY_LIQUID_OOZE, _096
    CompareMonDataToValue OPCODE_NEQ, BTLSCR_MSG_TEMP, BATTLEMON_HEAL_BLOCK_TURNS, 0, _083
    UpdateVar OPCODE_MUL, BTLVAR_HP_CALC_TEMP, -1
    Call BATTLE_SUBSCRIPT_UPDATE_HP
    // {0}’s health is sapped by Leech Seed!
    PrintMessage pl_msg_00000368_00296, TAG_NICKNAME, BTLSCR_MSG_DEFENDER
    Wait 
    WaitButtonABTime 30
    End 

_083:
    UpdateVar OPCODE_SET, BTLVAR_MSG_MOVE_TEMP, MOVE_HEAL_BLOCK
    // {0} was prevented from healing due to {1}!
    PrintMessage pl_msg_00000368_01054, TAG_NICKNAME_MOVE, BTLSCR_MSG_TEMP, BTLSCR_MSG_TEMP
    Wait 
    WaitButtonABTime 30
    End 

_096:
    CheckAbility CHECK_HAVE, BTLSCR_MSG_ATTACKER, ABILITY_MAGIC_GUARD, _110
    Call BATTLE_SUBSCRIPT_UPDATE_HP
    // It sucked up the liquid ooze!
    PrintMessage pl_msg_00000368_00720, TAG_NONE
    Wait 
    WaitButtonABTime 30
    End 

_110:
    // It sucked up the liquid ooze!
    PrintMessage pl_msg_00000368_00720, TAG_NONE
    Wait 
    WaitButtonABTime 30
    // {0}’s {1} suppressed {2}’s {3}!
    PrintMessage pl_msg_00000368_00727, TAG_NICKNAME_ABILITY_NICKNAME_ABILITY, BTLSCR_MSG_ATTACKER, BTLSCR_MSG_ATTACKER, BTLSCR_MSG_DEFENDER, BTLSCR_MSG_DEFENDER
    Wait 
    WaitButtonABTime 30
    End 