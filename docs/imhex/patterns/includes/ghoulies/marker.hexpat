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
    Scare = 0x16,
};

struct GhoulyBox {
    u32 someU32;
    char ghoulyBoxAID[128];
    char actorAttribsAID[128];
    u16 someCount;
    u16 pad16;
    u32 someValDiv100;
};

struct Marker {
	s128 start = $;

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
    } else if (markerType == MarkerType::Powerup) {
		char objParamsAID[128];
	} else if (markerType == MarkerType::GhoulyBoxGhouly) {
		char objParamsAID[128];
		char someAID1[128];
		char someAID2[128];
		char actorAttribsAID[128];
	} else if (markerType == MarkerType::FxEmitter) {
		char fxEmitterAID[128];
	} else if (markerType == MarkerType::Scare) {
		u32 scareIndex;
		float float1;
		u32 idk1;
		float float2;
		u32 idk2;
		float float3;
	}

	s128 end = $;
	if (end - start < size) {
		u8 data[size - (end - start)];
	}
};
