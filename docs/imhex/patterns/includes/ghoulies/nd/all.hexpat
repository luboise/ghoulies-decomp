#pragma once
#pragma eval_depth 99

#include <std/math>
#include <std/ptr>
#include <std/string>

#include "ghoulies/nd/push_buffer"
#include "ghoulies/nd/rigid_skin_idx"
#include "ghoulies/nd/skeleton"
#include "ghoulies/nd/vertex_buffer"
#include "ghoulies/types"

struct SubresHeader
{
  u32 dataSize;
  u32* dataStart : u32;
};

struct SubresDef
{
  u32 subresType;
  SubresHeader* header : u32;
};

/*
SubresDef subresheader_at_0x5720 @ 0x5720;
SubresDef subresdef_at_0x5730 @ 0x5730;
SubresDef subresdef_at_0x5738 @ 0x5738;
SubresDef subresdef_at_0x5740 @ 0x5740;
SubresDef subresdef_at_0x5748 @ 0x5748;
SubresDef subresdef_at_0x5750 @ 0x5750;
*/

struct TEXTURE_HEADER
{
  s128 start = $;

  u32 format;
  u32 headerSize;  // 28
  u16 width;
  u16 height;
  u8 flag1;
  u8 flag2;
  u8 flag3;
  u8 num_mip_levels;
  u32 unknown_3a;
  u32 texture_offset;
  u32 dataSize;

  s128 end = $;

  if ((end - start) < headerSize) {
  	u8 rest[headerSize - (end - start)];
  }
};

bitfield CollisionMask
{
  bool mask01 : 1;
  bool mask02 : 1;
  bool Wall : 1;
  bool Ground : 1;
  bool mask0x10 : 1;
  bool mask0x20 : 1;
  bool mask0x40 : 1;
  bool mask0x80 : 1;

  bool mask0x100 : 1;
  bool mask0x200 : 1;
  bool mask0x400 : 1;
  bool mask0x800 : 1;
  bool mask0x1000 : 1;
  bool mask0x2000 : 1;
  bool mask0x4000 : 1;
  bool mask0x8000 : 1;

  bool mask0x10000 : 1;
  bool mask0x20000 : 1;
  bool mask0x40000 : 1;
  bool mask0x80000 : 1;
  bool mask0x100000 : 1;
  bool mask0x200000 : 1;
  bool mask0x400000 : 1;
  bool mask0x800000 : 1;

  bool mask0x1000000 : 1;
  bool mask0x2000000 : 1;
  bool mask0x4000000 : 1;
  bool mask0x8000000 : 1;
  bool mask0x10000000 : 1;
  bool mask0x20000000 : 1;
  bool mask0x40000000 : 1;
  bool mask0x80000000 : 1;
};

struct DataSpan<T>
{
  u32 numItems;
  T* items : u32;
};

struct ResourceView
{
  u32 offset;
  u32 size;
  u32 unknown1;
  u32 unknown2;
  u32 unknown3;
  u32 unknown4;
};

// DataView dataview_at_0x5420 @ 0x5420;
// DataSpan<TexHeaderPtr> type9header_at_0x5420 @ 0x5420;

/*
ResourceView res1[5] @ 0x1A0;
ResourceView res2 @ 0x260;
ResourceView resourceview_at_0x1B8 @ 0x1B8;
ResourceView resourceview_at_0x1D0 @ 0x1D0;
*/

struct SizedBlock
{
  u32 size;
  u32 data[size - 4];
};

enum NdType : u16
{
  ndGroup = 0x01,
  ndSkeleton = 0x02,

  ndRigidSkinIdx = 0x0b,
  ndMtxArray = 0x0c,

  ndShader2 = 0x11,
  ndShaderParam2 = 0x12,
  ndVertexBuffer = 0x13,
  ndPushBuffer = 0x14,
  ndVertexShader = 0x15,
  ndBGPushBuffer = 0x16,
  ndBlendShape = 0x17,
};

// SizedBlock sizedblock_at_0x40 @ 0x40;

using NdHeader;

struct NdHeader
{
  s128 model_root = parent.model_root;

  u32 name_ptr;
  NdType nd_type;
  u16 idk1b;
  u32 unknown_ptr_1;
  u32 unknown_ptr_2;
  u32 unknown_u32_1;
  u32 children_ptr;
  u32 right_sibling_ptr;
  u32 prev_node_ptr;

  if (name_ptr != 0) {
    std::string::NullString name @model_root + name_ptr;
  }

  if (children_ptr != 0) {
    NdHeader first_child @model_root + children_ptr;
  }

  if (right_sibling_ptr != 0) {
    NdHeader next_sibling @model_root + right_sibling_ptr;
  }

  match(nd_type)
  {
    (NdType::ndVertexBuffer)
        : NdVertexBufferDetails;
    (NdType::ndPushBuffer)
        : NdPushBufferDetails;
    (NdType::ndBGPushBuffer)
        : NdBGPushBufferDetails;
    (NdType::ndSkeleton)
        : NdSkeletonDetails;
    (NdType::ndRigidSkinIdx)
        : NdRigidSkinIdxDetails;
  }
};

struct ndMtxSomething
{
  u32 something1;
  u32 something2;
};

struct ndMtxArray
{
  NdHeader subres;

  // 0x20
  ndMtxSomething* somePtr : u32 [[pointer_base("section1innersptr")]];
  u32 numSomethings;

  // 0x28
  u16 unknown2;
  u16 maybeNext;

  // 0x2c
  mat4* matrices : u32 [[pointer_base("section1innersptr")]];
  u32 numMatrices;
  // 0x30
};

struct ndPushBufferDescriptor
{
  NdHeader subres;
  u32 numDraws;
  u32 idk1;
  u32 idk2;
  u32 idk3;
  // Pointer lists
  u32* pushDataPtrs : u32 [[pointer_base("section1innersptr")]];
  u32* primitiveTypes : u32 [[pointer_base("section1innersptr")]];
  u32* vertexCounts : u32 [[pointer_base("section1innersptr")]];
  u8 doNotCull;  // Bool
  u8 pad[3];
};

struct ndSkeleton
{
  NdHeader subres;

  // 0x20
  u32 numBones;
  u32* bonesStart : u32 [[pointer_base("section1innersptr")]];
};

struct RawColour
{
  u8 r;
  u8 g;
  u8 b;
  u8 w;
};

struct TextureAssignment
{
  u32 textureIndex;
  u8 flag1;
  u8 flag2;
  u8 flag3;
  bool skipDiffuseTexture;
  u32 unknown3;
  u32 unknown4;
  u32 unknown5;
  u32 unknown6;
  u32 unknown7;
};

struct NDSP2Bruh
{
};

struct ndShaderParam2Payload
{
  RawColour* pixelShaderConstants : u32 [[pointer_base("section1innersptr")]];
  u32* somePtr2 : u32 [[pointer_base("section1innersptr")]];
  TextureAssignment* textureAssignments : u32
      [[pointer_base("section1innersptr")]];
  u32 numTextureAssignments;
  u32 numBruhs;
  u32 numPixelShaderConstants;

  // 0x18
  u8 alphaReference;
  u8 flag1;
  u8 flag2;
  u8 someCount;

  u32 someU32_5;

  // 0x20
  u32* child : u32 [[pointer_base("section1innersptr")]];

  u32* assignmentsStart : u32 [[pointer_base("section1innersptr")]];
  u32 numAssignments;
};

struct ndShaderParam2Assignment
{
  std::string::NullString* namePtr : u32 [[pointer_base("section1innersptr")]];
  u32 someVal1;
  u32 textureSlot;  // The slot in the renderer which the texture will be loaded
                    // in
  u32 someVal3;
};

struct ndShaderParam2
{
  NdHeader header;

  // 0x20
  ndShaderParam2Payload* payload1 : u32 [[pointer_base("section1innersptr")]];

  // Payload 2 is optional
  ndShaderParam2Payload* payload2 : u32 [[pointer_base("section1innersptr")]];
};

struct ndBGPushBufferDescriptor
{
  NdHeader subres;
  u32 numDraws;
  u32 idk1;
  u32 idk2;
  u32 idk3;
  // Pointer lists
  u32* pushDataPtrs : u32 [[pointer_base("section1innersptr")]];
  u32* primitiveTypes : u32 [[pointer_base("section1innersptr")]];
  u32* vertexCounts : u32 [[pointer_base("section1innersptr")]];
  u8 doNotCull;  // Bool
  u8 pad[3];
};

struct TextureSubresource
{
  u32 numTextures;
  std::ptr::NullablePtr<TEXTURE_HEADER, u32>* texture_headers[numTextures]
      : u32;
};

struct SamplerAssignment
{
  u32 numAssignments;
  u32* assignments[numAssignments] : u32;
};

struct ModelSubresource0xe
{
  u32 idk1;
  u32 idk2;

  u32* somePtr : u32;
  u32* somePtr2 : u32;

  // 0x10
  u32 idk3;
  u32 numSamplerAssignments;
  u32 idk4;
  u32 idk5;

  // 0x20
  u32 idk6;
  vec3 someVec1;

  // 0x30
  vec3 someVec2;
  u32 idk13;

  // 0x40
  float someFloat;
  SamplerAssignment* samplerAssignments[numSamplerAssignments] : u32;
};

bitfield ModelBitfield
{
  bool bruh1 : 1;
  bool bruh2 : 2;
  bool bruh3 : 3;
  bool bruh4 : 4;
  bool bruh5 : 5;
  bool bruh6 : 6;
  bool bruh7 : 7;
  bool bruh8 : 8;
};

struct NdHeaderPtr
{
  s128 model_root = parent.model_root;

  u32 nd_header_ptr;
  if (nd_header_ptr != 0) {
    NdHeader header @model_root + nd_header_ptr;
  }
};
