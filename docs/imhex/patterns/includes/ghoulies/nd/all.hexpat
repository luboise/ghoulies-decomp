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

fn section1innersptr(u32 offset) {
    return 0x40;
};

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

struct ndMtxSomething
{
  u32 something1;
  u32 something2;
};

struct ndPushBufferDescriptor
{
  NdHeader subres;
  u32 numDraws;
  u32 idk1;
  u32 idk2;
  u32 idk3;
  // Pointer lists
  u32* pushDataPtrs[numDraws]: u32;
  u32* primitiveTypes[numDraws]: u32;
  u32* vertexCounts[numDraws]: u32;
  u8 doNotCull;  // Bool
  u8 pad[3];

  u8 pushData[while((subres.right_sibling_ptr == 0 || $ < subres.right_sibling_ptr) && (subres.next_node_ptr == 0 || $ < subres.next_node_ptr))] @ pushDataPtrs;
};

struct ndBGPushBufferDescriptor
{
  NdHeader subres;
  u32 numDraws;
  u32 idk1;
  u32 idk2;
  u32 idk3;
  // Pointer lists
  u32* pushDataPtrs : u32;
  u32* primitiveTypes : u32;
  u32* vertexCounts : u32;
  u8 doNotCull;  // Bool
  u8 pad[3];
};

struct ndSkeleton
{
  NdHeader subres;

  // 0x20
  u32 numBones;
  u32* bonesStart : u32;
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

struct NDSP2Assignment {
	u32 namePtr;
	if (namePtr > 0) {
		std::string::NullString name @ namePtr;
	}
	u32 idk2;
	u32 idk3;
	u32 idk4;
};

struct ShaderMatrix {
	mat4 matrix;
	u32 val1;
	u32 val2;
};

struct ndShaderParam2Payload {
  // Pixel constants to set in the pixel shader (into 0-255 f32),
  // starting from index 0
  u32 pixelShaderColoursPtr; 
  u32 matricesPtr;
  u32 textureAssignmentsPtr;

  u32 numTextureAssignments;
  // 0x10
  u32 numMatrices;
  u32 numPixelShaderColours;

  if (textureAssignmentsPtr > 0 && numTextureAssignments > 0) {
	TextureAssignment textureAssignments[numTextureAssignments] @ textureAssignmentsPtr;
  }

  if (matricesPtr > 0 && numMatrices > 0) {
	ShaderMatrix matrices[numMatrices] @ matricesPtr;
  }

  if (pixelShaderColoursPtr > 0 && numPixelShaderColours > 0) {
	RawColour pixelShaderConstants[numPixelShaderColours] @ pixelShaderColoursPtr;
  }

  // 0x18
  u8 alphaReference;
  u8 flag1;
  u8 flag2;
  u8 numWeirdTextures;

  u32 someU32_5;

  // 0x20
  u32 childPtr;

  u32 assignmentsPtr;
  u32 numAssignments;

  if (numAssignments > 0 && assignmentsPtr > 0) {
	  NDSP2Assignment assignments[numAssignments] @ assignmentsPtr;
  }

  u32 idkPad[5];
  // if (    idkPad[0] != 0 || 
  //   idkPad[1] != 0 || 
  //   idkPad[2] != 0 || 
  //   idkPad[3] != 0 || 
  //   idkPad[4] != 0 || 
  //   idkPad[5] != 0) {
  //  s128 BRUH = $ [[hex::editor_export]];
  // }
  
  // 0x40
  u32 weirdTexIndex;
  u32 lastValue [[hex::editor_export]];
  
  // 0x48
} [[hex::editor_export]];

struct ndShaderParam2Assignment
{
  std::string::NullString* namePtr : u32;
  u32 someVal1;
  u32 textureSlot;  // The slot in the renderer which the texture will be loaded
                    // in
  u32 someVal3;
};


struct PixelShader {
	u32 pixelShaderType;	// used at runtime, expect 0?
	u32 shaderPtr;
	u32 length;
	u32 shaderHandle;		// used at runtime for handle
	if (shaderPtr > 0 && length > 0) {
		u8 shader[length] @ shaderPtr;
	}
};

struct NdShader2Details {
	PixelShader* pixelShader1: u32;
	NullPtr<PixelShader> pixelShader2;
};

struct NdShaderParam2Details
{
  // 0x20
  ndShaderParam2Payload* payload1 : u32;

  // Payload 2 is optional
  u32 payload2Ptr;
  if (payload2Ptr > 0) {
    ndShaderParam2Payload payload2 @ payload2Ptr;
  }
};

struct NdMtxArrayEntry {
	u16 index;
	u16 idk1;
	// 0x4
	u8 idk2;
	u8 flags;
	u16 idk3;
};

struct NdMtxArrayDetails {
	u32 entriesPtr;
	u32 numEntries;
	u16 count2;
	u16 calc1;
	u32 matricesPtr;
	u32 numMatrices;

	if (entriesPtr > 0 && numEntries > 0) {
		NdMtxArrayEntry entries[numEntries] @ entriesPtr;
	}

	if (matricesPtr > 0 && numMatrices > 0) {
		mat4 matrices @ matricesPtr;
	}
};

struct VertexShader {
	u16 idk1;
	u16 numDwords;

	u32 data[4 * numDwords];

};

struct OtherStream {
	u8 data[while (std::mem::read_unsigned($, 4, std::mem::Endian::Little) != 0xffffffff)];
	u32 sentinel; // 0xffffffff
};

struct NdVertexShaderDetails {
	u32 streamSourceIndicesPtr;
	u32 numStreamSources;
	u32 constant1;
	u16 constant2;
	u16 idk1;
	// 0x10
	u32 idk2;
	u32 idk3;
	u32 idk4;
	u32 count1;
	// 0x20
	u32 count2;
	u32 count3;
	u32 idk_2_1;
	u32 idk_2_2;
	// 0x30
	NullPtr<OtherStream> broski;
	VertexShader* shaderPtr: u32;
	u8* strides[numStreamSources]: u32;

	if (streamSourceIndicesPtr > 0 && numStreamSources > 0) {
		u32 streamSourceIndices[numStreamSources] @ streamSourceIndicesPtr;
	} 
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

struct NdHeader
{
  std::ptr::NullablePtr<std::string::NullString, u32> name;
  NdType nd_type;
  u16 idk1b;
  u32 unknown_ptr_1;
  u32 unknown_ptr_2;
  u32 unknown_u32_1;
  u32 children_ptr;
  u32 right_sibling_ptr;
  u32 prev_node_ptr;

  if (children_ptr != 0) {
    NdHeader first_child @children_ptr;
  }

  if (right_sibling_ptr != 0) {
    NdHeader next_sibling @right_sibling_ptr;
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
    (NdType::ndVertexShader)
        : NdVertexShaderDetails;
    (NdType::ndShader2)
        : NdShader2Details;
    (NdType::ndShaderParam2)
        : NdShaderParam2Details;
    (NdType::ndMtxArray)
        : NdMtxArrayDetails;
  }
};


