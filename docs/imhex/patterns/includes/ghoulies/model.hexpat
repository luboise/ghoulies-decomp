#pragma once
#pragma array_limit 900000

#include <std/ptr>
import std.array;

#include "ghoulies/nd/all"
#include "ghoulies/collision"
#include "ghoulies/types"

enum ModelSubresourceType : u32
{
  ModelSubres = 0x0,
  Unknown0x2 = 0x2,
  Unknown0x3 = 0x3,
  RigidSkinSubres = 0x4,
  MatrixSubres = 0x5,
  CollidersSubres = 0x6,
  TexturesSubres = 0x7,
  GridSubres = 0x8,
  BoneIndexSubres = 0x9,
  Unknown0xa = 0xa,
  Unknown0xc = 0xc,
  Unknown0xd = 0xd,
  Unknown0xf = 0xf,
  Unknown0x11 = 0x11,
  TilesSubres = 0x12
};

struct Subres0x4Value
{
  s128 start = $;

  CollisionObjectType setType;
  u8 size;
  u16 blendTargetIndex;

  CollisionMask collisionMask;
  u16 short1;
  u16 short2;

  u32 padZero;
  float f1;
  vec3 v;
  u32 group;

  s128 end = $;

  padding[std::math::max(0, 36 - (end - start))];
};

struct Subres0x4
{
  u32 numValues;
  u32 idk1;
  Subres0x4Value values[numValues];
};

struct VerticesEntry {
    u32 numVertices;
    vec3* vertices[numVertices] : u32;
};

struct Some0x11Inner {
	char bytes[80];
};

struct IndexList32 {
	u32 count;
	Vec3<u32>* items[count]: u32; 
};

/*
struct Subresource0x11 {
    u8 a;
    u8 count;
    u8 c;
    u8 d;
    
	u32 name_ptr;
	if (name_ptr) {
   		char name @name_ptr;
	}
    
    VerticesEntry* some_pt[count]: u32;
    IndexList32* indexLists[count]: u32;
    u32* ptrsList[count]: u32;
};
*/

struct Mesh
{
  u32 mesh_data;
};

struct PrefixedCollection<T> {
	u32 numItems;
	T items[numItems];
};

struct ModelSubresource0xa {
	// TODO: Switch to transform
	PrefixedCollection<std::Array<float, 10>> matrices;
};


struct SizedCollection<T>
{
  u32 numValues;
  u32 dataStart;
  // TODO: Check this is correct
  T values[numValues] @ dataStart;
};

struct SubresourcePtr
{
  u32* ptr : u32;
};

struct ModelProperty
{
  NdPtr<std::string::NullString> key;
  u32 value_ptr;
  u32 value_size;

  if (value_size > 0 && value_ptr != 0) {
    u8 data[value_size] @value_ptr;
  }
};

using ModelProperties = SizedCollection<ModelProperty>;

struct ModelSomething {
	u32 ptr1;
	u32 ptr2;
	u32 val;
};


struct ModelMap2 {

};

struct ModelSubresource
{
  std::ptr::NullablePtr<u32, u32> ptr1;
  u32 idk2;
  u32 nd_nodes_ptr;
  u32 num_nd_nodes;

  // 0x10
  NullPtr<ModelProperties> properties;
  std::ptr::NullablePtr<ModelMap2, u32> map2;
  float float1;
  float float2;

  // 0x20
  float float3;
  float float4;
  u32* nextPtr : u32 [[pointer_base("section1innersptr")]];
  u32 model_model_root;

  // Derived
  if (nd_nodes_ptr != 0 && num_nd_nodes > 0) {
	  NullPtr<NdHeader> nd_header_ptrs[num_nd_nodes] @nd_nodes_ptr;
  }
};

struct TexturesSubresource
{
  u32 num_textures;
  NullPtr<std::Array<NullPtr<TEXTURE_HEADER>, num_textures>> textures;
};


struct CollidersSubres
{
  u32 numObjects;
  u16 minFlagMaybe;
  u16 maxFlagMaybe;
  u32 numVertices;
  u32 verticesPtr;
  CollisionObject objects[numObjects];

  if (numVertices > 0 && verticesPtr != 0) {
  	vec3 vertices[numVertices] @ verticesPtr;
  }
};

struct BoneIndexSubres
{
  u8 indices[32];
};

struct Inner0x2 {
	u16 bone1;
	u16 bone2;
	float floats[12];
};


struct RigidSkinSubresourceEntry {
	s128 start = $;

	s128 end = $;

	if (end - start < 36) {
		u8 rest[36 - (end - start)];
	}
};

using Model0x2Subresource = PrefixedCollection<Inner0x2>;
using RigidSkinSubresource = PrefixedCollection<RigidSkinSubresourceEntry>;

struct FloatSet0xc {
    float float1;
    float float2;
    float float3;
    u32 flags;
    float float4;
    float float5;
};

struct Subresource0xc {
    u32 count1;
    FloatSet0xc* floatSets[count1]: u32;
    u32 numTextures;
	std::ptr::NullablePtr<TEXTURE_HEADER, u32>* texture_ptrs[numTextures]: u32;
};

struct Data0xd{
    u8 data[52];
};

struct Subresource0xd {
    u32 count1;
    Data0xd* data1[count1]: u32;
    u32 numTextures;
    std::ptr::NullablePtr<TEXTURE_HEADER, u32>* texture_ptrs[numTextures]: u32;
};


using Subresource0xf = PrefixedCollection<std::Array<float, 11>>;

struct Tile {
    u32 idk1;
    u32 idk2;
    u32 resSize;
    u32 resPtr;
    
    u32 d3dVertexBufferHeader;
    
    u8 entry[0x8];
};

struct TilesSubresource {
    u32 idka1;
    u32 idka2;
    u8 pad8[8];
    
    u32 numX;
    u32 numY;
    u32 numZ;
    u32 numTiles;
    
    vec3 someVec3;   
    u32 idk0x2c;
    
    u32 idk0x30;
    u32 idk0x34;
    float scale;
    
    Tile* Tile[numTiles]: u32;
};

struct GridSubresource {
    float baseX;
    float baseZ;
    float floats[4];
    float scaleX;
    float scaleY;
    float scaleZ;
    u16 numX;
    u16 numY;
    u16 numZ;
    u16 unused;
    
    Vec3<u8> positions[numX * numY * numZ];
};

struct ModelFooterEntry
{
  s128 start = parent.start;
  s128 cur = $;

  ModelSubresourceType subres_type;
  u32 offset;

  if (offset != 0) {
    // Model subresource
    if (subres_type == ModelSubresourceType::ModelSubres) {
	  s128 sectionSize = cur - start - 0x40;
	  u8 sectionBytes[sectionSize] @ 0x40 [[hex::editor_export]];

	  std::mem::Section modelFileSection = std::mem::create_section("model file");
	  std::mem::set_section_size(modelFileSection, sectionSize);
	  std::mem::copy_value_to_section(sectionBytes, modelFileSection, 0);

	  ModelSubresource subres @ 0 in modelFileSection;
    }

	// Non-model
	else if (subres_type == ModelSubresourceType::Unknown0x2) {
      Model0x2Subresource subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::RigidSkinSubres) {
      RigidSkinSubresource subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::MatrixSubres) {
      mat4 subres @parent.start + offset;
	  if ($ % 32 != 0) {
		  u8 subresPad[32 - ($ % 32)];
	  }
    } else if (subres_type == ModelSubresourceType::CollidersSubres) {
      CollidersSubres subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::TexturesSubres) {
      TexturesSubresource subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::GridSubres) {
      GridSubresource subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::BoneIndexSubres) {
      BoneIndexSubres subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::Unknown0xa) {
      ModelSubresource0xa subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::Unknown0xc) {
      Subresource0xc subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::Unknown0xd) {
      Subresource0xd subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::Unknown0xf) {
      Subresource0xf subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::Unknown0x11) {
      // Subresource0x11 subres @parent.start + offset;
    } else if (subres_type == ModelSubresourceType::TilesSubres) {
	  TilesSubresource subres @parent.start + offset;
	} else {
	  u32 section @parent.start + offset;
	}
  }
};

struct ModelDescriptor
{
  s128 start = $;

  u32 footer_ptr;
  u32 num_footer_entries;
  u32 flags;
  u32 unknown_u32_1;
  u32 model_runtime_context;
  u32 unknown_u32_2;

  if (footer_ptr != 0 && num_footer_entries > 0) {
    ModelFooterEntry footer_entries[num_footer_entries] @start + footer_ptr;
  }
};
