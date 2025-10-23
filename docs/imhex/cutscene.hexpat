#include <std/string>
#include <std/ptr>
// #include <std/array>

// using Ptr<T> = std::ptr::NullablePtr<T, u32>;

fn bruh(u32 offset) {
    return 0x4c;
};

struct CameraFloats {
    u16 numFloats;
    u16 idk;
    float length;
    float* values[numFloats]: u32 [[pointer_base("bruh")]];
};

struct CameraDescriptor {
    CameraFloats posX;
    CameraFloats posY;
    CameraFloats posZ;
    CameraFloats rotX;
    CameraFloats rotY;
    CameraFloats rotZ;
    CameraFloats rotW;
    CameraFloats zoom;
    CameraFloats aspectRatio;
    
};

struct CameraHeader {
    std::string::NullString* name: u32;
    CameraDescriptor* descriptor: u32;
};

struct CutsceneDescriptor {
    u16 idk1;
    u8 numCameras;
    u8 numAnims;
    
    float length;
    CameraHeader* cameras[numCameras]: u32;
};

CutsceneDescriptor cutscenedescriptor_at_0x00 @ 0x00;