#pragma once

#include "ghoulies/types"

struct Sound {
	u32 flags;
	u32 idk1;
	float f1;
	float f2;
	float f3;
	float f4;
	float f5;
	u32 idk3;
};

struct Cue {
	u32 cue;
};

struct CueTable {
    u32 idk;
};

struct Entry1 {
    u32 flags;
    u32 ptr1;
    u32 mask1;
    u32 idk1;
    u32 mask2;
};

struct Entry2 {
    NullPtr<Cue> cue;
    u32 wavebankPtr;
    u32 mask1;
    u32 flags;
    u32 idk;
};

struct XSoundbank { 
    u32 sdbk;
    u16 version;
    u16 idk;
    char* diskNames: u32;

	// resolved by individual Entry1s
	u32 cueTable;
    // NullPtr<NullPtr<CueTable>> cueTable;
	u32 soundsPtr;
    u32 fileSize;
    u16 numGroups;
    u16 numEntries1;
    u16 numEntries2;
    u16 numEntries3;
    u16 numEntries4;
    u16 short6;
    u16 short7;
    u16 short8;
    char soundbankName[16];
    
    Entry1 entries1[numEntries1];
    Entry2 entries2[numEntries2];

	Sound sounds[numEntries3] @ soundsPtr;
};
