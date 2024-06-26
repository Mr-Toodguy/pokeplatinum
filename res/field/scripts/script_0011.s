    .include "macros/scrcmd.inc"

    .data

    .long _0028-.-4
    .long _002A-.-4
    .long _003D-.-4
    .long _003F-.-4
    .long _027E-.-4
    .long _0291-.-4
    .long _02A4-.-4
    .long _0026-.-4
    .long _02A6-.-4
    .short 0xFD13

_0026:
    ScrCmd_002

_0028:
    ScrCmd_002

_002A:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 0
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_003D:
    ScrCmd_002

_003F:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_011 0x40F2, 0
    ScrCmd_01C 5, _0257
    ScrCmd_020 0xAB3
    ScrCmd_01C 1, _00A0
    ScrCmd_020 0xAA9
    ScrCmd_01C 1, _0084
    ScrCmd_02C 1
    ScrCmd_03E 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _00B6
    ScrCmd_016 _00AB

_0084:
    ScrCmd_02C 18
    ScrCmd_03E 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _00B6
    ScrCmd_016 _00AB
    ScrCmd_002

_00A0:
    ScrCmd_02C 2
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_00AB:
    ScrCmd_02C 3
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_00B6:
    ScrCmd_01E 0xAA9
    ScrCmd_02C 4
    ScrCmd_24E 0x8000
    ScrCmd_280 0, 0x8000, 2, 5
    ScrCmd_02C 5
    ScrCmd_24F 0x8001, 0x8002, 0x8003, 0x8000
    ScrCmd_011 0x8002, 0
    ScrCmd_01C 1, _00F5
    ScrCmd_011 0x8003, 0
    ScrCmd_01C 1, _0100
    ScrCmd_016 _010E

_00F5:
    ScrCmd_02C 8
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0100:
    ScrCmd_0D6 0, 0x8001
    ScrCmd_02C 6
    ScrCmd_016 _011C

_010E:
    ScrCmd_251 0, 0x8001
    ScrCmd_02C 7
    ScrCmd_016 _011C

_011C:
    ScrCmd_029 0x8008, 0x8002
    ScrCmd_011 0x8008, 1
    ScrCmd_01C 1, _0165
    ScrCmd_011 0x8008, 2
    ScrCmd_01C 1, _0170
    ScrCmd_011 0x8008, 3
    ScrCmd_01C 1, _0179
    ScrCmd_011 0x8008, 4
    ScrCmd_01C 1, _0182
    ScrCmd_011 0x8008, 5
    ScrCmd_01C 1, _018B
    ScrCmd_002

_0165:
    ScrCmd_02C 9
    ScrCmd_016 _0194
    ScrCmd_002

_0170:
    ScrCmd_02C 11
    ScrCmd_016 _0194

_0179:
    ScrCmd_02C 12
    ScrCmd_016 _0194

_0182:
    ScrCmd_02C 13
    ScrCmd_016 _0194

_018B:
    ScrCmd_02C 14
    ScrCmd_016 _0194

_0194:
    ScrCmd_029 0x8008, 0x8002
    ScrCmd_011 0x8008, 1
    ScrCmd_01C 1, _01DD
    ScrCmd_011 0x8008, 2
    ScrCmd_01C 1, _01EB
    ScrCmd_011 0x8008, 3
    ScrCmd_01C 1, _01F7
    ScrCmd_011 0x8008, 4
    ScrCmd_01C 1, _0203
    ScrCmd_011 0x8008, 5
    ScrCmd_01C 1, _020F
    ScrCmd_002

_01DD:
    ScrCmd_028 0x8003, 2
    ScrCmd_016 _021B
    ScrCmd_002

_01EB:
    ScrCmd_028 0x8003, 51
    ScrCmd_016 _021B

_01F7:
    ScrCmd_028 0x8003, 216
    ScrCmd_016 _021B

_0203:
    ScrCmd_028 0x8003, 29
    ScrCmd_016 _021B

_020F:
    ScrCmd_028 0x8003, 1
    ScrCmd_016 _021B

_021B:
    ScrCmd_029 0x8004, 0x8003
    ScrCmd_028 0x8005, 1
    ScrCmd_07D 0x8004, 0x8005, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _0246
    ScrCmd_014 0x7FC
    ScrCmd_016 _0269

_0246:
    ScrCmd_029 0x40F2, 0x8002
    ScrCmd_02C 15
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0257:
    ScrCmd_0CD 0
    ScrCmd_02C 16
    ScrCmd_029 0x8002, 0x40F2
    ScrCmd_016 _0194

_0269:
    ScrCmd_028 0x40F2, 0
    ScrCmd_01E 0xAB3
    ScrCmd_02C 17
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_027E:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 19
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0291:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 20
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_02A4:
    ScrCmd_002

_02A6:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 21
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

    .byte 0
    .byte 0
    .byte 0
