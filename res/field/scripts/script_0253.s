    .include "macros/scrcmd.inc"

    .data

    .long _0006-.-4
    .short 0xFD13

_0006:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_020 210
    ScrCmd_01C 1, _00C7
    ScrCmd_020 232
    ScrCmd_01C 1, _004F
    ScrCmd_07E 0x1A8, 1, 0x800C
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _0044
    ScrCmd_02C 0
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0044:
    ScrCmd_02C 1
    ScrCmd_016 _004F
    ScrCmd_002

_004F:
    ScrCmd_05E 0, _00D4
    ScrCmd_05F
    ScrCmd_02C 2
    ScrCmd_03E 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _007C
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _00B8
    ScrCmd_002

_007C:
    ScrCmd_02C 3
    ScrCmd_028 0x8004, 75
    ScrCmd_028 0x8005, 1
    ScrCmd_07D 0x8004, 0x8005, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _00AE
    ScrCmd_01E 210
    ScrCmd_014 0x7E0
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_00AE:
    ScrCmd_014 0x7E1
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_00B8:
    ScrCmd_01E 232
    ScrCmd_02C 4
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_00C7:
    ScrCmd_02C 5
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

    .balign 4, 0
_00D4:
    MoveAction_04B
    EndMovement
