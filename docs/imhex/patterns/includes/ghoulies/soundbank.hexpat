#pragma once

#include "ghoulies/types"

const u32 XSB_SOUND_FLAG_TRIVIAL = 1 << 3;
const u32 XSB_SOUND_FLAG_SIMPLE = 1 << 4;

struct BankIndex {
	u16 waveIndex;
	u16 wavebankIndex;
};

struct CueU32 {
	u32 cue;
};

struct CueTable {
    u32 idk;
};

struct CueEntry {
	u8 bruh[20];
	/*
	u16 flags;
	u16 soundIndex;
	char* name: u32;
	u32 a;
	u32 b;
	u32 c;
	*/
};

enum SoundEventType: u8 {
	PLAY_COMPLEX = 0x01,
	PITCH = 0x04,
	ENVELOPE_AMPLITUDE = 0x0a,
	MIXBINSPAN = 0x10,
};


bitfield VariationParams {
	variationCount: 13;
	variationSelectionMethod: 4;
	currentVariation: 13;
	flags: 2;
};

struct SimpleVariationList { 
	VariationParams params;
	// wave index + wavebank index u16s
	BankIndex variations[params.variationCount];
};


struct A {
	u8 bytes[8];
};

struct ComplexVariationList { 
	VariationParams params;
	A values[params.variationCount];
};

struct SoundEvent {
	u8 eventType;

	if (eventType == SoundEventType::PLAY_COMPLEX) {
		u24 timestampMs;
		u8 paramSize;
		u8 flags;
		u16 loopCount;

		// if XSB_PLAY_EVENT_FLAG_COMPLEX
		if (flags & 0x4) {
			// if (parent.parent.flags & XSB_SOUND_FLAG_SIMPLE) {
			// 	SimpleVariationList* variationList: u32;
			// }
			ComplexVariationList* variationList: u32;
		} else {
			BankIndex bankIndex;
		}
		u16 pitchVariationMin;
		u16 pitchVariationMax;
		u16 volumeVariationMin;
		u16 volumeVariationMax;
		u16 maxDelay;
		u16 idk1;
	} else if (eventType == SoundEventType::PITCH) {
		u24 timestampMs;
		u8 paramSize;
		u8 flags;
		u16 fadeSteps;
		u16 pitchMin;
		u16 pitchMax;
		u8 unknown;
		u24 fadeDuration;
	} else if (eventType == SoundEventType::ENVELOPE_AMPLITUDE) {
		u24 timestampMs;
		u8 paramSize;
		u8 flags;
		u16 loopCount;
		u16 delaySeconds;
		u16 attackSeconds;
		u16 holdSeconds;
		u16 decaySeconds;
		u16 releaseSeconds;
		u8 sustainPower;
		u8 unknown1;
	} else {
		u24 idk1;
		u8 paramSize;
		u8 flags;
		u16 idk2;
		if (paramSize > 0) {
			u8 params[paramSize];
		}
	}
};

struct ComplexSound {
	u8 eventCount;
	u24 eventsPtr;

	SoundEvent events[eventCount] @ eventsPtr;
	// SoundEvent events[1] @ eventsPtr;
 };

// 3dparams
struct TDParams {
	u16 insideConeAngle;
	u16 outsideConeAngle;
	u16 outsideConeVolume;
	u16 unknown1;
	float minimumDistance;
	float maximumDistance;
	float distanceFactor;
	float rolloffFactor;
	u32 unknown2;
	u32 unknown3;
	u32 unknown4;
	u32 unknown5;
};


struct SoundEntry {
	u32 entryU32;
	u16 volume;
	u16 pitch;
	u8 trackCount;
	u8 layer;
	u8 category;
	u8 flags;
	u16 parameters3DIndex;
	u8 priority;
	u8 i3dl2Volume;
	u16 eqGain;
	u16 eqQ;

	if (flags & XSB_SOUND_FLAG_TRIVIAL) {
		u16 waveIndex = entryU32;
		u16 wavebankIndex = entryU32 >> 16;
	}
	else if (flags & XSB_SOUND_FLAG_SIMPLE) {
		ComplexVariationList simple @ entryU32;
	}
	else {
		ComplexSound complex @ entryU32;
	}
};

struct Sound {
	u32 flags;
	u32 idk1;
	float f1;
	float f2;
	float f3;
	float f4;
	// float f5;
};

struct SoundTable {
	u32 flags;
	u32 idk1;
	float soundFloats[5];

	u32 idk2;
	u32 idk3;
	u32 idk4;

	CueU32 cues[parent.numEntries1];
	Sound sounds[parent.numEntries2];
};

struct WavebankName {
	char name[16];
};

struct WavebankArray {
	WavebankName names[parent.wavebankArrayLen];
	char NULL[4];
};

struct XSoundbank { 
    u32 sdbk;
    u16 version;
    u16 crc;
    u32 wavebankArrayPtr;

	// resolved by individual Entry1s
	u32 cueTable;
    // NullPtr<NullPtr<CueTable>> cueTable;

	// 0x10

	TDParams* tdParameters: u32;
    u32 fileSize;

    u16 xsbFlags;

    u16 numSomething;

    u16 soundCount;
    u16 cueCount;

	// 0x20

    u16 numEntries4;
    u16 wavebankArrayLen;
    u16 short7;
    u16 short8;
    char soundbankName[16];

    CueEntry cueEntries[cueCount];
	SoundEntry soundEntries[soundCount];

    WavebankArray wavebankArray @ wavebankArrayPtr;

	// SoundTable soundTable @ soundsPtr;
};

bitfield WaveBankMiniWaveFormat3 {
    wFormatTag: 2;
    nChannels: 3;
    nSamplesPerSec: 18;
    wBlockAlign: 8;
    wBitsPerSample: 1;
};

struct WaveEntry {
    u32 unknown_1;

	WaveBankMiniWaveFormat3 format;

	u32 bytesPtr;
	u32 numBytes;

	if (numBytes > 0) {
		u8 wavData[10] @ bytesPtr + parent.wavDataPtr;
	}

    u32 unknown_2;
    u32 unknown_3;
};



struct XWavebank {
	u32 wbnd;
	u32 version;
	u32 idk1;
	u32 wavebanksPtr;

	u32 entriesPtr;
	u32 entriesSize;

	u32 count2;
	u32 idk2;
	u32 wavDataPtr;
	u32 wavDataLength;

	if (entriesPtr > 0 && entriesSize > 0) 
		WaveEntry waves[entriesSize/24] @ entriesPtr;

	// if (wavDataPtr > 0 && wavDataLength > 0) {
	// 	u8 wavData[wavDataLength] @ wavDataPtr;
	// }
};

