#include <std/ptr>

struct AnimValue{
    s128 start = $;
    u16 someU16;
    s128 end = $;
    
    padding[100 - (end-start)];
};

struct AnimDescriptor{
    u8 ANIM[4];
    float f1;
    float duration;

    std::ptr::NullablePtr<u32, u32> cValsPtr;

    // 0x10
    u32 idk2;
    u16 numAllocdValues;
    u16 idk16_1;
    u16 idk16_2;
    u16 numSomethingsOrSize;
    u32 idk5;

    // 0x20
    std::ptr::NullablePtr<u32, u32> idk0x20;

    u32 idk7;
    std::ptr::NullablePtr<u32, u32> tailDataPtr;
    u32 idk9;

    // 0x30
    u32 idk10;
    u32 idk11;
    u32 idk12;
    u32 idk13;

    // 0x40
    u16 bruh;
    u16 bruh2;
    u16 bruh3;
    
    AnimValue values[69];
};
