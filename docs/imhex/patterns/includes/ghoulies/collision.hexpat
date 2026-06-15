#pragma once

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


enum CollisionObjectType : u8
{
  Sphere = 0,
  Type2 = 1,
  Box = 2,
  PartSphere = 3
};

struct CollisionObjectBase {
  CollisionObjectType type;
  u8 idk1;
  u8 idk2;
  u8 idk3;
  CollisionMask collisionMask;
  u32 size;
  u32 flags2;
};

struct CollisionTriangle
{
  u32 index1;
  u32 index2;
  u32 index3;
  CollisionMask mask;
  u32 pad;
};

struct BoxCollider
{
  s128 start = $;
  CollisionObjectBase base;

  u32 numTriangles;
  CollisionTriangle* triangles[numTriangles]: u32;
  u32 otherPtrOrFlags;
  /*
  u32 size;

  u32 idk4;
  s16 maxX;
  s16 maxY;

  if (type == CollisionObjectType::Type2) {
   s16 maxZ;
   u16 count1;
   u16 count2;
   u16 count3;
   u16 count5;
   u16 count6;
   u16 numEntries;
   u16 gridDivisions;
   s16 minX;
   s16 minY;
   s16 minZ;
   u16 idk5;

   CollisionPrimitive entries[numEntries];
  }
  */

  s128 end = $;


  if (base.size - (end - start) > 0) {
	  u8 data[base.size - (end - start)];
  }
};

struct CollisionObject {
	if (std::mem::read_unsigned($, 2) == 2) {
		BoxCollider collider;
	}

};

struct CollisionSubres
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


