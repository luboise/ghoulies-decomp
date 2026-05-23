#pragma once

struct Vec3<T> {
	T x;
	T y;
	T z;
};

using vec3 = Vec3<float>;
using u8vec3 = Vec3<u8>;

struct vec4
{
  float x;
  float y;
  float z;
  float w;
};

struct mat4
{
  vec4 r1;
  vec4 r2;
  vec4 r3;
  vec4 r4;
};

struct quat {
    float x;
    float y;
    float z;
    float w;
};

enum AssetType : u32
{
    Texture = 1,
    Anim = 2,
    Unknown3 = 3,
    Model = 4,
    AnimEvents = 5,

    Cutscene = 7,
    CutsceneEvents = 8,

    Misc = 10,
    ActorGoals = 11,
    Marker = 12,
    FxCallout = 13,
    AidList = 14,

    Loctext = 16,

    XSoundbank = 18,
    XDSP = 19,
    XCueList = 20,
    Font = 21,
    Ghoulybox = 22,
    Ghoulyspawn = 23,
    Script = 24,
    ActorAttribs = 25,
    Emitter = 26,
    Particle = 27,
    Rumble = 28,
    ShakeCam = 29,

    Count, // This will automatically take the next value (30)
};

struct AssetChunkInfo
{
  AssetType asset_type;
  u32 idk1;
  u32 idk2;
  u32 numChunks;
  u32 descriptor_ptr;
  u32 descriptor_size;
  u32 resource_view_ptr;
  u32 resource_size;
};
