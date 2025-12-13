#pragma once

#include <std/math>
#include "ghoulies/types"

enum MarkerType : u16 {
    Player = 0x02,
    GhoulyBoxGhouly = 0x04,
    Weapon = 0x05,
    Powerup = 0x06,
    FxEmitter = 0x0a,
    Unknown0x0b = 0x0b,
    Unknown0x0c = 0x0c,
    BgBreak = 0x0D,
};

struct GhoulyBox {
    u32 someU32;
    char ghoulyBoxAID[128];
    char actorAttribsAID[128];
    u16 someCount;
    u16 pad16;
    u32 someValDiv100;
};

struct RawMarker {
    u32 size; 
    MarkerType markerType;
    u16 markerId;
    u32 idk1;
    vec3 pos;
    vec3 rotEuler;
    float scale;
    if (markerType == MarkerType::BgBreak) {
        u32 someU32;
        char ghoulyBoxAID[128];
        char actorAttribsAID[128];
        u16 someCount;
        u16 pad16;
        u32 someValDiv100;

    }
    else {
        u8 data[size-40];
    }
};
