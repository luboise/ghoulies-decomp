#pragma once

enum CollisionObjectType : u8
{
  Sphere = 0,
  Type2 = 1,
  Box = 2,
  PartSphere = 3
};

struct CollisionTriangle
{
  u32 index1;
  u32 index2;
  u32 index3;
  CollisionMask mask;
  u32 pad;
};

struct CollisionTriangleList
{
  u32 numTriangles;
  CollisionTriangle* triangles[numTriangles] : u32;
};

struct CollisionObject
{
  CollisionObjectType type;

  u8 idk1;
  u8 idk2;
  u8 idk3;
  CollisionMask collisionMask;
  u32 size;

  u32 idk4;
  s16 maxX;
  s16 maxY;
  s128 start = $;

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

	  CollisionTriangleList entries[numEntries];
  }

  s128 end = $;

  u8 data[size - (end - start)];
};


