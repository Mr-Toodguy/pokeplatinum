    .include "macros/scrcmd.inc"

    .data

    .long _000A-.-4
    .long _002E-.-4
    .short 0xFD13

_000A:
    ScrCmd_292 25, 0x4000
    ScrCmd_011 0x4000, 1
    ScrCmd_01C 1, _0022
    ScrCmd_01E 0x27C
    ScrCmd_002

_0022:
    ScrCmd_01F 0x27C
    ScrCmd_028 0x4111, 1
    ScrCmd_002

_002E:
    ScrCmd_060
    ScrCmd_05E 1, _004C
    ScrCmd_05F
    ScrCmd_01E 0x27C
    ScrCmd_065 1
    ScrCmd_028 0x4111, 0
    ScrCmd_061
    ScrCmd_002

    .balign 4, 0
_004C:
    MoveAction_041
    MoveAction_001
    MoveAction_041
    MoveAction_049
    MoveAction_00D 2
    MoveAction_04A
    MoveAction_045
    EndMovement
