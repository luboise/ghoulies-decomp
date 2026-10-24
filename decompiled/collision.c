/* collision.c - Collision system: EDB2 broadphase, colliders, physics, A* pathfinding
   Synced to Ghidra default.xbe. */
#include "collision.h"

/* Walks every node of a BackgroundCollisionThing and, for each node whose
   12-bit type id (low 12 bits of the node's +0xc word) equals layerId, flips the
   node's active bit: param_2==1 sets it, ==0 clears it. Returns the number of
   nodes matched. Nodes are 0x12 bytes apart. */
int updateCollisionThingLayerFlags(ushort layerId,short enable,BackgroundCollisionThing *thing)

{
  ushort uVar1;
  int matched;
  int nodeOffset;
  int node;
  int nodeCount;
  int i;
  
  nodeCount = *(int *)thing * (int)thing->maxFloatVal;
  i = 0;
  matched = 0;
  /* *(int*)thing = numNodes/major, maxFloatVal = major divisor => node count */
  if (0 < nodeCount) {
    nodeOffset = 0;
    do {
      node = thing->field10_0x10 + nodeOffset;
      uVar1 = *(ushort *)(node + 0xc);
      /* node +0xc word: low 12 bits = type id, bit 0x1000 = active bit */
      if ((uVar1 & 0xfff) == layerId) {
        *(ushort *)(node + 0xc) = (enable << 0xc ^ uVar1) & 0x1000 ^ uVar1;
        matched = matched + 1;
      }
      i = i + 1;
      nodeOffset = nodeOffset + 0x12;
    } while (i < nodeCount);
  }
  return matched;
}




/* Expands aabb over the `matrixPtr` point cloud: for each of 3 axes (indexed by
   colliders in `collider`), take the min/max of every vertex and write the
   resulting bounds into aabb->aabb. Used to derive an EDB2 cell range. */
undefined4 ColliderPairValue::calculateAABB(Collider *collider,AABBFat *aabb)

{
  float fVar1;
  int i;
  float fVar2;
  vec3 *vertices;
  
  vertices = (vec3 *)aabb->matrixPtr;
  i = 0;
  do {
    /* axis 0 (x): clamp each vertex x into the running [min,max] */
    fVar1 = (float)(aabb->aabb).maxX;
    fVar2 = uVar1[*(int *)(&param_1->field_0x0 + i * 4)].x;
    if (fVar1 < uVar1[*(int *)(&param_1->field_0x0 + i * 4)].x) {
      fVar2 = fVar1;
    }
    fVar1 = (float)(aabb->aabb).maxY;
    (aabb->aabb).maxX = (int32_t)fVar2;
    fVar2 = uVar1[*(int *)(&param_1->field_0x0 + i * 4)].y;
    if (fVar1 < uVar1[*(int *)(&param_1->field_0x0 + i * 4)].y) {
      fVar2 = fVar1;
    }
    fVar1 = (float)(aabb->aabb).maxZ;
    (aabb->aabb).maxY = (int32_t)fVar2;
    fVar2 = uVar1[*(int *)(&param_1->field_0x0 + i * 4)].z;
    if (fVar1 < uVar1[*(int *)(&param_1->field_0x0 + i * 4)].z) {
      fVar2 = fVar1;
    }
    fVar1 = (float)(aabb->aabb).minX;
    (aabb->aabb).maxZ = (int32_t)fVar2;
    fVar2 = uVar1[*(int *)(&param_1->field_0x0 + i * 4)].x;
    if (uVar1[*(int *)(&param_1->field_0x0 + i * 4)].x <= fVar1) {
      fVar2 = fVar1;
    }
    fVar1 = (float)(aabb->aabb).minY;
    (aabb->aabb).minX = (int32_t)fVar2;
    fVar2 = uVar1[*(int *)(&param_1->field_0x0 + i * 4)].y;
    if (uVar1[*(int *)(&param_1->field_0x0 + i * 4)].y <= fVar1) {
      fVar2 = fVar1;
    }
    fVar1 = (float)(aabb->aabb).minZ;
    (aabb->aabb).minY = (int32_t)fVar2;
    fVar2 = uVar1[*(int *)(&param_1->field_0x0 + i * 4)].z;
    if (uVar1[*(int *)(&param_1->field_0x0 + i * 4)].z <= fVar1) {
      fVar2 = fVar1;
    }
    i = i + 1;
    (aabb->aabb).minZ = (int32_t)fVar2;
  } while (i < 3);
  return 1;
}




void ColliderType2::processDescriptor(ColliderType2 *this,int resBase)

{
  ColliderType2Entry_ptr_4_uint32_t puVar1;
  int i;
  
  i = 0;
  if (*(short *)&this->field_0x20 != 0) {
    puVar1 = (ColliderType2Entry_ptr_4_uint32_t)(this->entries).entries;
    do {
      if (ADJ(puVar1)->entries[0] != 0) {
        ADJ(puVar1)->entries[0] = ADJ(puVar1)->entries[0] + resBase;
      }
      i = i + 1;
      puVar1 = puVar1 + 2;
    } while (i < (int)(uint)*(ushort *)&this->field_0x20);
  }
  return;
}



undefined4
ColliderType2::update
          (ColliderSet *set,AffineTransform *affine1,AffineTransform *affine2,Skeleton *skeleton,
          float *matrixPtr,vec3 *result1,vec3 *result2,CollisionMask collisionMask,
          undefined4 param_9,Collision0x54 *outCol)

{
  float fVar1;
  float fVar2;
  AffineTransform *pAVar3;
  int i;
  int iVar4;
  float fVar5;
  float mx;
  float fVar6;
  float my;
  float fVar7;
  float mz;
  float fVar8;
  vec3 corner2;
  int local_3c;
  int local_38;
  int local_34;
  vec3 local_30;
  vec3 corner1;
  int local_18;
  int local_14;
  int local_10;
  vec3 local_c;
  
  mx = affine2->m[0][1] * result1->y + result1->x * affine2->m[0][0] + result1->z * affine2->m[0][2]
       + affine2->m[0][3];
  my = affine2->m[1][2] * result1->z + result1->x * affine2->m[1][0] + affine2->m[1][1] * result1->y
       + affine2->m[1][3];
  mz = affine2->m[2][1] * result1->y + result1->x * affine2->m[2][0] + affine2->m[2][2] * result1->z
       + affine2->m[2][3];
  corner2.x = result2->x * affine2->m[0][0] + result2->z * affine2->m[0][2] +
              affine2->m[0][1] * result2->y + affine2->m[0][3];
  corner2.y = affine2->m[1][2] * result2->z + affine2->m[1][1] * result2->y +
              affine2->m[1][0] * result2->x + affine2->m[1][3];
  corner2.z = result2->x * affine2->m[2][0] + affine2->m[2][2] * result2->z +
              affine2->m[2][1] * result2->y + affine2->m[2][3];
  local_30.x = corner2.x - mx;
  local_30.y = corner2.y - my;
  local_30.z = corner2.z - mz;
  fVar6 = mx;
  fVar7 = my;
  fVar8 = mz;
  corner1.x = mx;
  corner1.y = my;
  corner1.z = mz;
  ColliderSet::AABBFromCorners(&corner1,&corner2,&local_3c,&local_18,set,0.0);
  affine2 = (AffineTransform *)0x0;
  if (local_10 <= local_34) {
    do {
      i = local_14;
      if (local_14 <= local_38) {
        do {
          iVar4 = local_18;
          if (local_18 <= local_3c) {
            do {
               /* Narrow-phase test for this EDB2 cell; result1 is a scratch
                  segment (from local_30) that collideWithColliders mutates. */
               pAVar3 = (AffineTransform *)
                        collideWithColliders(&set[2].flags0x1235 +
                                     ((uint)*(ushort *)((int)&set[1].flags0x1235 + 2) * local_10 +
                                     (uint)(ushort)set[1].flags0x1235 * i + iVar4) * 2,
                                     (vec3 *)matrixPtr,&corner1,&local_30,&local_c,collisionMask,
                                     param_9,&result1);
              if ((pAVar3 != (AffineTransform *)0x0) &&
                 (fVar6 = mx, fVar7 = my, fVar8 = mz, affine2 = pAVar3, (float)result1 == 0.0))
              goto LAB_0005398e;
              iVar4 = iVar4 + 1;
              fVar6 = mx;
              fVar7 = my;
              fVar8 = mz;
            } while (iVar4 <= local_3c);
          }
          i = i + 1;
        } while (i <= local_38);
      }
      local_10 = local_10 + 1;
    } while (local_10 <= local_34);
LAB_0005398e:
    if (affine2 != (AffineTransform *)0x0) {
      mx = affine1->m[1][1];
      corner2.x = local_30.x + fVar6;
      corner2.y = local_30.y + fVar7;
      corner2.z = local_30.z + fVar8;
      fVar6 = affine1->m[1][2];
      fVar5 = affine1->m[0][2] * corner2.z + affine1->m[0][1] * corner2.y +
              affine1->m[0][0] * corner2.x + affine1->m[0][3];
      fVar7 = affine1->m[1][0];
      fVar8 = affine1->m[2][2];
      my = affine1->m[1][3];
      mz = affine1->m[2][1];
      fVar1 = affine1->m[2][0];
      fVar2 = affine1->m[2][3];
      result2->x = fVar5;
      result2->y = fVar6 * corner2.z + mx * corner2.y + fVar7 * corner2.x + my;
      result2->z = fVar8 * corner2.z + mz * corner2.y + fVar1 * corner2.x + fVar2;
      if (outCol != (Collision0x54 *)0x0) {
        createCollisionHit(&local_c,&corner2,affine2,affine1,matrixPtr,outCol,fVar5,0);
      }
      return 1;
    }
  }
  return 0;
}



/* Narrow-phase collision for a cylinder-shaped collider region. Transforms the
   two endpoints (param_3 start / param_7 out) by the caller affines, sweeps a
   cylinder of radius param_8 down the resulting segment, and calls
   collideWithCollisionThings() over the set's EDB2 cells. Returns 1 if a hit was
   found, writing the hit into outCol (param_11) via createCollisionHit. */
undefined4
updateCylinder(ColliderSet *set,AffineTransform *affine,undefined4 param_4,
            undefined4 param_5,float *param_6,float *outParam,float param_8,uint param_9,
            uint param_10,int param_11)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  ColliderSet *pCVar6;
  AffineTransform *pAVar7;
  int iVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  vec3 local_48;
  float local_3c;
  float local_38;
  float local_34;
  vec3 local_30;
  vec3 local_24;
  int local_18;
  int local_14;
  int local_10;
  vec3 local_c;
  
  pCVar6 = param_1;
  local_54 = param_3[1] * param_6[1] + param_6[2] * param_3[2] + *param_6 * *param_3 + param_3[3];
  local_50 = param_3[6] * param_6[2] + *param_6 * param_3[4] + param_3[5] * param_6[1] + param_3[7];
  local_4c = param_3[9] * param_6[1] + *param_6 * param_3[8] + param_3[10] * param_6[2] +
             param_3[0xb];
  local_48.x = *param_7 * *param_3 + param_7[2] * param_3[2] + param_3[1] * param_7[1] + param_3[3];
  local_48.y = param_3[6] * param_7[2] + param_3[5] * param_7[1] + *param_7 * param_3[4] +
               param_3[7];
  local_48.z = *param_7 * param_3[8] + param_3[10] * param_7[2] + param_3[9] * param_7[1] +
               param_3[0xb];
  fVar14 = param_3[8] * param_3[8] + param_3[4] * param_3[4] + *param_3 * *param_3;
  local_3c = local_48.x;
  local_38 = local_48.y;
  local_34 = local_48.z;
  local_24.x = local_54;
  local_24.y = local_50;
  local_24.z = local_4c;
  if (fVar14 == 0.0) {
    fVar9 = (float10)0.0;
  }
  else {
    fVar9 = scaled_invsqrt(fVar14);
  }
  local_30.x = local_3c - local_54;
  local_30.y = local_38 - local_50;
  fVar14 = (float)(fVar9 * (float10)param_8);
  local_30.z = local_34 - local_4c;
  fVar11 = local_54;
  fVar12 = local_50;
  fVar13 = local_4c;
  ColliderSet::AABBFromCorners(&local_24,&local_48,&local_3c,&local_18,param_1,fVar14);
  param_1 = (ColliderSet *)0x0;
  param_6 = (float *)local_10;
  if (local_10 <= (int)local_34) {
    do {
      param_3 = (float *)local_14;
      if (local_14 <= (int)local_38) {
        do {
          iVar8 = local_18;
          if (local_18 <= (int)local_3c) {
            do {
              pAVar7 = (AffineTransform *)
                       collideWithCollisionThings(&local_24,fVar14,&local_c,param_9,param_10,&local_58,
                                    &pCVar6[2].flags0x1235 +
                                    ((uint)*(ushort *)((int)&pCVar6[1].flags0x1235 + 2) *
                                     (int)param_6 +
                                    (uint)(ushort)pCVar6[1].flags0x1235 * (int)param_3 + iVar8) * 2,
                                    param_5,&local_30);
              fVar11 = local_54;
              fVar12 = local_50;
              fVar13 = local_4c;
              if ((pAVar7 != (AffineTransform *)0x0) &&
                 (param_1 = (ColliderSet *)pAVar7, local_58 == 0.0)) goto LAB_00053e08;
              iVar8 = iVar8 + 1;
            } while (iVar8 <= (int)local_3c);
          }
          param_3 = (float *)((int)param_3 + 1);
        } while ((int)param_3 <= (int)local_38);
      }
      param_6 = (float *)((int)param_6 + 1);
    } while ((int)param_6 <= (int)local_34);
LAB_00053e08:
    if (param_1 != (ColliderSet *)0x0) {
      fVar1 = param_2->m[1][1];
      local_48.x = local_30.x + fVar11;
      local_48.y = local_30.y + fVar12;
      local_48.z = local_30.z + fVar13;
      fVar11 = param_2->m[1][2];
      fVar10 = param_2->m[0][2] * local_48.z + param_2->m[0][1] * local_48.y +
               param_2->m[0][0] * local_48.x + param_2->m[0][3];
      fVar12 = param_2->m[1][0];
      fVar13 = param_2->m[2][2];
      fVar2 = param_2->m[1][3];
      fVar3 = param_2->m[2][1];
      fVar4 = param_2->m[2][0];
      fVar5 = param_2->m[2][3];
      *param_7 = fVar10;
      param_7[1] = fVar11 * local_48.z + fVar1 * local_48.y + fVar12 * local_48.x + fVar2;
      param_7[2] = fVar13 * local_48.z + fVar3 * local_48.y + fVar4 * local_48.x + fVar5;
      if (param_11 != 0) {
        createCollisionHit(&local_c,&local_48,(AffineTransform *)param_1,param_2,param_5,param_11,fVar10,
                     fVar14);
      }
      return 1;
    }
  }
  return 0;
}



undefined4
sampleSphereGrid(ColliderSet *param_1,undefined4 param_2,AffineTransform *affine,undefined4 param_4,
            undefined4 param_5,vec3 *pos,float param_7,undefined4 param_8,undefined4 param_9,
            undefined4 param_10)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float fVar8;
  int local_24;
  int local_20;
  int local_1c;
  vec3 local_18;
  int local_c;
  int local_8;
  vec3 *local_4;
  
  local_18.x = affine->m[0][2] * pos->z + affine->m[0][1] * pos->y + pos->x * affine->m[0][0] +
               affine->m[0][3];
  local_18.y = affine->m[1][2] * pos->z + affine->m[1][1] * pos->y + pos->x * affine->m[1][0] +
               affine->m[1][3];
  local_18.z = affine->m[2][2] * pos->z + affine->m[2][1] * pos->y + pos->x * affine->m[2][0] +
               affine->m[2][3];
  fVar8 = affine->m[0][0];
  fVar1 = affine->m[2][0];
  fVar2 = affine->m[1][0];
  fVar8 = fVar1 * fVar1 + fVar8 * fVar8 + fVar2 * fVar2;
  if (fVar8 == 0.0) {
    fVar7 = (float10)0.0;
  }
  else {
    fVar7 = scaled_invsqrt(fVar8);
  }
  fVar3 = (float10)param_7;
  ColliderSet::AABBFromCorners
            (&local_18,&local_18,&local_24,&local_c,param_1,(float)(fVar7 * fVar3));
  param_7 = 0.0;
  pos = local_4;
  if (local_1c < (int)local_4) {
    return 0;
  }
  do {
    iVar5 = local_8;
    if (local_8 <= local_20) {
      do {
        iVar6 = local_c;
        if (local_c <= local_24) {
          do {
            iVar4 = applyCollisionsToBuffer(param_2,&local_18,(float)(fVar7 * fVar3),param_8,param_9,param_10);
            if (iVar4 != 0) {
              param_7 = 1.4013e-45;
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 <= local_24);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 <= local_20);
    }
    pos = (vec3 *)((int)&pos->x + 1);
  } while ((int)pos <= local_1c);
  return param_7;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL ColliderType2::ctor(ColliderType2 *collider,uint param_2,undefined4 param_3,undefined4 param_4,
                        void *aabbCallback,background *bg)

{
  BOOL BVar1;
  ColliderType2Entry *entry;
  int i;
  
  i = 0;
  entry = &collider->entries;
  if (*(short *)&collider->field_0x20 != 0) {
    do {
      BVar1 = Collision::CalculateAABBForColliders
                        (param_2,param_3._0_1_,aabbCallback,bg,entry,param_4._0_1_);
      if (BVar1 == 0) {
        return 0;
      }
      i = i + 1;
      entry = entry + 1;
    } while (i < (int)(uint)*(ushort *)&collider->field_0x20);
  }
  return 1;
}



void createCollisionHit(vec3 *param_1,vec3 *param_2,AffineTransform *param_3,AffineTransform *param_4,
                 int param_5,float *param_6,undefined4 param_7,float param_8)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  if (param_8 == 0.0) {
    *param_6 = param_2->x;
    param_6[1] = param_2->y;
    param_6[2] = param_2->z;
  }
  else {
    fVar3 = param_1->y;
    fVar4 = param_1->z;
    fVar13 = 0.0 - param_8;
    *param_6 = param_2->x + param_1->x * fVar13;
    param_6[1] = param_2->y + fVar3 * fVar13;
    param_6[2] = param_2->z + fVar4 * fVar13;
  }
  param_6[3] = param_1->x;
  param_6[4] = param_1->y;
  param_6[5] = param_1->z;
  pfVar1 = (float *)(param_5 + (int)param_3->m[0][2] * 0xc);
  fVar3 = param_3->m[0][1];
  fVar4 = param_3->m[0][0];
  *(undefined1 *)((int)param_6 + 0x29) = 0x28;
  *(undefined1 *)(param_6 + 10) = 0;
  *(undefined1 *)((int)param_6 + 0x2a) = 1;
  pfVar2 = (float *)(param_5 + (int)fVar4 * 0xc);
  param_6[0xb] = *pfVar2;
  param_6[0xc] = pfVar2[1];
  param_6[0xd] = pfVar2[2];
  param_6[0xe] = *(float *)(param_5 + (int)fVar3 * 0xc);
  param_6[0xf] = *(float *)(param_5 + 4 + (int)fVar3 * 0xc);
  param_6[0x10] = *(float *)(param_5 + (int)fVar3 * 0xc + 8);
  param_6[0x11] = *pfVar1;
  param_6[0x12] = pfVar1[1];
  param_6[0x13] = pfVar1[2];
  *(undefined1 *)((int)param_6 + 0x29) = 0x28;
  fVar3 = param_4->m[1][1];
  fVar4 = param_4->m[2][1];
  fVar13 = param_6[1];
  fVar5 = param_4->m[1][2];
  fVar6 = param_4->m[1][0];
  fVar7 = *param_6;
  fVar8 = param_4->m[2][2];
  fVar9 = param_4->m[1][3];
  fVar10 = param_4->m[2][0];
  fVar11 = *param_6;
  fVar12 = param_4->m[2][3];
  *param_6 = param_4->m[0][2] * param_6[2] + param_4->m[0][1] * param_6[1] +
             param_4->m[0][0] * *param_6 + param_4->m[0][3];
  param_6[1] = fVar5 * param_6[2] + fVar3 * param_6[1] + fVar6 * fVar7 + fVar9;
  param_6[2] = fVar8 * param_6[2] + fVar4 * fVar13 + fVar10 * fVar11 + fVar12;
  Math::RotatePointUsingAffine((vec3 *)(param_6 + 3),param_4,(vec3 *)(param_6 + 3));
  applyHitBasisTransform();
  *(undefined2 *)(param_6 + 7) = 0;
  *(undefined1 *)((int)param_6 + 0x1e) = *(undefined1 *)((int)param_3->m[1] + 1);
  *(undefined1 *)((int)param_6 + 0x27) = *(undefined1 *)param_3->m[1];
  param_6[8] = param_3->m[0][3];
  param_6[6] = -NAN;
  *(undefined2 *)(param_6 + 9) = 0;
  param_6[0x14] = (float)param_3;
  *(undefined1 *)((int)param_6 + 0x26) = 1;
  return;
}



void ColliderSet::AABBFromCorners
               (vec3 *c1,vec3 *c2,int param_3,int param_4,ColliderSet *set,float aabbMargin)

{
  float fVar1;
  ushort uVar2;
  ushort uVar3;
  int max;
  int offset;
  ColliderSet_0x10 col_set;
  AABB aabb;
  int *max_ptr;
  float x2;
  
  x2 = c2->x;
  if (x2 < c1->x || x2 == c1->x) {
    aabb.minX = (int)c2->x;
    x2 = c1->x;
  }
  else {
    aabb.minX = (int)c1->x;
  }
  fVar1 = c2->y;
  aabb.maxX = (int)x2;
  if (fVar1 < c1->y || fVar1 == c1->y) {
    aabb.minY = (int)c2->y;
    fVar1 = c1->y;
  }
  else {
    aabb.minY = (int)c1->y;
  }
  x2 = c2->z;
  aabb.maxY = (int)fVar1;
  if (x2 < c1->z || x2 == c1->z) {
    aabb.minZ = (int)c2->z;
    aabb.maxZ = (int)c1->z;
  }
  else {
    aabb.minZ = (int)c1->z;
    aabb.maxZ = (int)x2;
  }
  col_set = &set[1].colliderType;
  offset = 0;
  do {
    max = (*(int *)((int)&aabb.minX + offset) - (int)*(short *)(col_set + 0x14)) -
          (int)(aabbMargin + 1.0);
    max_ptr = (int *)((int)&aabb.maxX + offset);
    *max_ptr = *max_ptr + ((int)(aabbMargin + 1.0) - (int)*(short *)(col_set + 0x14));
    uVar2._0_1_ = set[2].field2_0x2;
    uVar2._1_1_ = set[2].field3_0x3;
    *(int *)((int)&aabb.minX + offset) = max;
    if (max < 0) {
      max = max / (int)(uint)uVar2 + -1;
    }
    else {
      max = max / (int)(uint)uVar2;
    }
    *(int *)(offset + param_4) = max;
    max = *(int *)((int)&aabb.maxX + offset);
    uVar3._0_1_ = set[2].field2_0x2;
    uVar3._1_1_ = set[2].field3_0x3;
    if (max < 0) {
      max = max / (int)(uint)uVar3 + -1;
    }
    else {
      max = max / (int)(uint)uVar3;
    }
    *(int *)(offset + param_3) = max;
    max = (int)*(short *)col_set;
    if ((*(int *)(offset + param_4) < max) ||
       (max = (int)*(short *)(col_set + 6), max < *(int *)(offset + param_4))) {
      *(int *)(offset + param_4) = max;
    }
    max = (int)*(short *)col_set;
    if ((*(int *)(offset + param_3) < max) ||
       (max = (int)*(short *)(col_set + 6), max < *(int *)(offset + param_3))) {
      *(int *)(offset + param_3) = max;
    }
    *(int *)(offset + param_4) = *(int *)(offset + param_4) - (int)*(short *)col_set;
    *(int *)(offset + param_3) = *(int *)(offset + param_3) - (int)*(short *)col_set;
    offset = offset + 4;
    col_set = col_set + 2;
  } while (offset < 0xc);
  return;
}




void BoxCollider::processDescriptor(BoxCollider *box,int basePtr)

{
  if (*(int *)&box->field_0x14 != 0) {
    *(int *)&box->field_0x14 = *(int *)&box->field_0x14 + basePtr;
  }
  return;
}



void resolveCollideAffines(Skeleton *skeleton,AffineTransform *affineB1,AffineTransform *affineA1,
                 AffineTransform *affineB2,D3DMATRIX *affineA2,uint param_6)

{
  D3DXMATRIX *this;
  
  if (skeleton != (Skeleton *)0x0) {
    this = (D3DXMATRIX *)Skeleton::getBoneAffineIntoGlobal(skeleton,param_6);
    Maths::InvertAffineMatrix(this,affineA2);
    Graphics::leftCombineTransforms
              ((AffineTransform *)&affineA2->field1,(AffineTransform *)affineA2,affineA1);
    Graphics::leftCombineTransforms(affineB2,affineB1,(AffineTransform *)&this->field1);
    return;
  }
  affineA2->m[0][0] = affineA1->m[0][0];
  affineA2->m[0][1] = affineA1->m[0][1];
  affineA2->m[0][2] = affineA1->m[0][2];
  affineA2->m[0][3] = affineA1->m[0][3];
  affineA2->m[1][0] = affineA1->m[1][0];
  affineA2->m[1][1] = affineA1->m[1][1];
  affineA2->m[1][2] = affineA1->m[1][2];
  affineA2->m[1][3] = affineA1->m[1][3];
  affineA2->m[2][0] = affineA1->m[2][0];
  affineA2->m[2][1] = affineA1->m[2][1];
  affineA2->m[2][2] = affineA1->m[2][2];
  affineA2->m[2][3] = affineA1->m[2][3];
  affineB2->m[0][0] = affineB1->m[0][0];
  affineB2->m[0][1] = affineB1->m[0][1];
  affineB2->m[0][2] = affineB1->m[0][2];
  affineB2->m[0][3] = affineB1->m[0][3];
  affineB2->m[1][0] = affineB1->m[1][0];
  affineB2->m[1][1] = affineB1->m[1][1];
  affineB2->m[1][2] = affineB1->m[1][2];
  affineB2->m[1][3] = affineB1->m[1][3];
  affineB2->m[2][0] = affineB1->m[2][0];
  affineB2->m[2][1] = affineB1->m[2][1];
  affineB2->m[2][2] = affineB1->m[2][2];
  affineB2->m[2][3] = affineB1->m[2][3];
  return;
}



undefined4
BoxCollider::update(BoxCollider *collider,AffineTransform *affine1,AffineTransform *affine2,
                   Skeleton *param_4,float *someMatrix,vec3 *param_6,vec3 *param_7,
                   undefined4 param_8,undefined4 param_9,int param_10)

{
  int *piVar1;
  vec3 local_a0;
  vec3 local_94;
  vec3 local_88;
  vec3 local_7c;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  vec3 auStack_4c;
  AffineTransform AStack_40;
  undefined1 local_10 [4];
  vec3 local_c;
  
  resolveCollideAffines(param_4,affine1,affine2,&AStack_40,(D3DMATRIX *)&local_7c,
               *(undefined4 *)&collider->field_0x18);
  local_88.x = param_6->y * local_7c.y + param_6->z * local_7c.z + param_6->x * local_7c.x +
               (float)uStack_70;
  local_88.y = param_6->y * (float)uStack_68 + param_6->z * (float)uStack_64 +
               param_6->x * (float)uStack_6c + (float)uStack_60;
  local_88.z = param_6->y * (float)uStack_58 + param_6->z * (float)uStack_54 +
               param_6->x * (float)uStack_5c + (float)uStack_50;
  local_a0.x = param_7->x * local_7c.x + param_7->y * local_7c.y + param_7->z * local_7c.z +
               (float)uStack_70;
  local_a0.y = param_7->x * (float)uStack_6c + param_7->y * (float)uStack_68 +
               param_7->z * (float)uStack_64 + (float)uStack_60;
  local_a0.z = param_7->x * (float)uStack_5c + param_7->y * (float)uStack_58 +
               param_7->z * (float)uStack_54 + (float)uStack_50;
  local_94.x = local_a0.x - local_88.x;
  local_94.y = local_a0.y - local_88.y;
  local_94.z = local_a0.z - local_88.z;
  auStack_4c.x = local_88.x;
  auStack_4c.y = local_88.y;
  auStack_4c.z = local_88.z;
  piVar1 = (int *)collideWithColliders(&collider->somePtr,(vec3 *)someMatrix,&auStack_4c,&local_94,&local_c,
                               param_8,param_9,local_10);
  if (piVar1 != (int *)0x0) {
    local_a0.y = local_94.y + local_88.y;
    local_a0.z = local_94.z + local_88.z;
    local_a0.x = local_94.x + local_88.x;
    param_7->x = AStack_40.m[0][2] * local_a0.z + AStack_40.m[0][1] * local_a0.y +
                 AStack_40.m[0][0] * local_a0.x + AStack_40.m[0][3];
    param_7->y = AStack_40.m[1][2] * local_a0.z + AStack_40.m[1][1] * local_a0.y +
                 AStack_40.m[1][0] * local_a0.x + AStack_40.m[1][3];
    param_7->z = AStack_40.m[2][2] * local_a0.z + AStack_40.m[2][1] * local_a0.y +
                 AStack_40.m[2][0] * local_a0.x + AStack_40.m[2][3];
    if (param_10 != 0) {
      createCollisionHitFromMatrix(&local_c,param_10,0,(float *)0x0,(int)someMatrix,piVar1,&AStack_40,&local_a0.x);
    }
    return 1;
  }
  return 0;
}



undefined4
updatePartSphere(BoxCollider *collider,AffineTransform *param_2,AffineTransform *param_3,
            Skeleton *skeleton,int param_5,vec3 *outPos1,vec3 *outPos2,float param_8,uint param_9,
            uint param_10,int param_11)

{
  int *piVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  vec3 local_94;
  float local_88;
  vec3 local_84;
  AffineTransform local_70;
  vec3 someVec;
  AffineTransform AStack_34;
  float local_4;
  
  resolveCollideAffines(skeleton,param_2,param_3,&AStack_34,(D3DMATRIX *)&local_70,
               *(undefined4 *)&collider->field_0x18);
  fVar4 = outPos1->y * local_70.m[0][1] + outPos1->z * local_70.m[0][2] +
          outPos1->x * local_70.m[0][0] + local_70.m[0][3];
  fVar5 = outPos1->x * local_70.m[1][0] + outPos1->y * local_70.m[1][1] +
          outPos1->z * local_70.m[1][2] + local_70.m[1][3];
  fVar6 = outPos1->x * local_70.m[2][0] + outPos1->y * local_70.m[2][1] +
          outPos1->z * local_70.m[2][2] + local_70.m[2][3];
  local_94.x = outPos2->x * local_70.m[0][0] + outPos2->y * local_70.m[0][1] +
               outPos2->z * local_70.m[0][2] + local_70.m[0][3];
  local_94.y = outPos2->x * local_70.m[1][0] + outPos2->y * local_70.m[1][1] +
               outPos2->z * local_70.m[1][2] + local_70.m[1][3];
  local_94.z = outPos2->x * local_70.m[2][0] + outPos2->y * local_70.m[2][1] +
               outPos2->z * local_70.m[2][2] + local_70.m[2][3];
  fVar7 = local_70.m[2][0] * local_70.m[2][0] + local_70.m[1][0] * local_70.m[1][0] +
          local_70.m[0][0] * local_70.m[0][0];
  local_88 = local_94.x;
  local_84.x = local_94.y;
  local_84.y = local_94.z;
  someVec.x = fVar4;
  someVec.y = fVar5;
  someVec.z = fVar6;
  if (fVar7 == 0.0) {
    fVar2 = (float10)0.0;
  }
  else {
    fVar2 = scaled_invsqrt(fVar7);
  }
  local_84.z = local_94.x - fVar4;
  fVar7 = local_94.y - fVar5;
  fVar3 = local_94.z - fVar6;
  piVar1 = (int *)collideWithCollisionThings(&someVec,(float)(fVar2 * (float10)param_8),&local_94,param_9,param_10
                               ,&local_4,&collider->somePtr,param_5,(vec3 *)&local_84.z);
  if (piVar1 != (int *)0x0) {
    local_84.x = fVar7 + fVar5;
    local_84.y = fVar3 + fVar6;
    local_88 = local_84.z + fVar4;
    outPos2->x = AStack_34.m[0][2] * local_84.y + AStack_34.m[0][1] * local_84.x +
                 AStack_34.m[0][0] * local_88 + AStack_34.m[0][3];
    outPos2->y = AStack_34.m[1][2] * local_84.y + AStack_34.m[1][1] * local_84.x +
                 AStack_34.m[1][0] * local_88 + AStack_34.m[1][3];
    outPos2->z = AStack_34.m[2][2] * local_84.y + AStack_34.m[2][1] * local_84.x +
                 AStack_34.m[2][0] * local_88 + AStack_34.m[2][3];
    if (param_11 != 0) {
      createCollisionHitFromMatrix(&local_94,param_11,(float)(fVar2 * (float10)param_8),(float *)0x0,param_5,piVar1,
                   &AStack_34,&local_88);
    }
    return 1;
  }
  return 0;
}



void updatePartSphereSkeleton(int param_1,AffineTransform *param_2,AffineTransform *param_3,Skeleton *param_4,
                 undefined4 param_5,float *param_6,float param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10)

{
  float10 fVar1;
  float x;
  float fVar2;
  float local_6c;
  float local_68;
  float local_64;
  undefined1 local_60 [96];
  
  resolveCollideAffines(param_4,param_2,param_3,(AffineTransform *)(local_60 + 0x30),(D3DMATRIX *)local_60,
               *(undefined4 *)(param_1 + 0x18));
  local_6c = param_6[1] * (float)local_60._4_4_ + param_6[2] * (float)local_60._8_4_ +
             *param_6 * (float)local_60._0_4_ + (float)local_60._12_4_;
  local_68 = param_6[1] * (float)local_60._20_4_ + param_6[2] * (float)local_60._24_4_ +
             *param_6 * (float)local_60._16_4_ + (float)local_60._28_4_;
  x = (float)local_60._32_4_ * (float)local_60._32_4_ +
      (float)local_60._16_4_ * (float)local_60._16_4_ +
      (float)local_60._0_4_ * (float)local_60._0_4_;
  fVar2 = 0.0;
  local_64 = param_6[1] * (float)local_60._36_4_ + param_6[2] * (float)local_60._40_4_ +
             *param_6 * (float)local_60._32_4_ + (float)local_60._44_4_;
  if (x != 0.0) {
    fVar1 = scaled_invsqrt(x);
    fVar2 = (float)fVar1;
  }
  applyCollisionsToBuffer(local_60 + 0x30,&local_6c,fVar2 * param_7,param_8,param_9,param_10);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL BoxCollider::ctor(BoxCollider *this,uint param_2,bool param_3,bool param_4,void *param_5,
                      AABBFat *param_6)

{
  BOOL BVar1;
  
  BVar1 = Collision::CalculateAABBForColliders
                    (param_2,param_3,param_5,(background *)param_6,
                     (ColliderType2Entry *)&this->somePtr,param_4);
  return BVar1;
}



void createCollisionHitFromMatrix(float *param_1,float *param_2,float param_3,float *param_4,int param_5,
                 int *param_6,AffineTransform *param_7,float *param_8)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  float fVar53;
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fVar58;
  float fVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar64;
  int iVar65;
  int iVar66;
  float fVar67;
  
  if (param_3 == 0.0) {
    *param_2 = *param_8;
    param_2[1] = param_8[1];
    param_2[2] = param_8[2];
  }
  else {
    fVar3 = param_1[1];
    fVar4 = param_1[2];
    fVar67 = 0.0 - param_3;
    *param_2 = *param_8 + *param_1 * fVar67;
    param_2[1] = param_8[1] + fVar3 * fVar67;
    param_2[2] = param_8[2] + fVar4 * fVar67;
  }
  param_2[3] = *param_1;
  param_2[4] = param_1[1];
  param_2[5] = param_1[2];
  if (param_4 == (float *)0x0) {
    iVar66 = *param_6;
    pfVar1 = (float *)(param_5 + param_6[2] * 0xc);
    iVar65 = param_6[1];
    *(undefined1 *)(param_2 + 10) = 0;
    *(undefined1 *)((int)param_2 + 0x29) = 0x28;
    *(undefined1 *)((int)param_2 + 0x2a) = 1;
    pfVar2 = (float *)(param_5 + iVar65 * 0xc);
    iVar65 = param_5 + iVar66 * 0xc;
    param_2[0xb] = *(float *)(param_5 + iVar66 * 0xc);
    param_2[0xc] = *(float *)(iVar65 + 4);
    param_2[0xd] = *(float *)(iVar65 + 8);
    param_2[0xe] = *pfVar2;
    param_2[0xf] = pfVar2[1];
    param_2[0x10] = pfVar2[2];
    param_2[0x11] = *pfVar1;
    param_2[0x12] = pfVar1[1];
    param_2[0x13] = pfVar1[2];
  }
  else {
    iVar65 = *param_6;
    fVar3 = *(float *)(param_5 + 4 + iVar65 * 0xc);
    fVar4 = *(float *)(param_5 + iVar65 * 0xc);
    fVar67 = *param_4;
    fVar5 = param_4[1];
    fVar6 = *(float *)(param_5 + 4 + iVar65 * 0xc);
    fVar7 = param_4[5];
    fVar8 = *(float *)(param_5 + iVar65 * 0xc);
    fVar9 = param_4[8];
    pfVar1 = (float *)(param_5 + iVar65 * 0xc);
    fVar10 = param_4[2];
    fVar11 = pfVar1[2];
    fVar12 = param_4[6];
    fVar13 = pfVar1[2];
    fVar14 = param_4[4];
    fVar15 = *pfVar1;
    fVar16 = param_4[9];
    fVar17 = param_4[10];
    fVar18 = pfVar1[2];
    fVar19 = pfVar1[1];
    fVar20 = param_4[9];
    iVar65 = param_6[1];
    fVar21 = *(float *)(param_5 + 4 + iVar65 * 0xc);
    fVar22 = param_4[1];
    fVar23 = *(float *)(param_5 + 4 + iVar65 * 0xc);
    fVar24 = *(float *)(param_5 + 8 + iVar65 * 0xc);
    fVar25 = param_4[6];
    pfVar1 = (float *)(param_5 + iVar65 * 0xc);
    fVar26 = *pfVar1;
    fVar27 = *param_4;
    fVar28 = pfVar1[2];
    fVar29 = param_4[2];
    fVar30 = param_4[4];
    fVar31 = *pfVar1;
    fVar32 = pfVar1[1];
    fVar33 = param_4[5];
    fVar34 = param_4[3];
    fVar35 = param_4[7];
    fVar36 = param_4[0xb];
    fVar37 = param_4[3];
    fVar38 = param_4[10];
    fVar39 = pfVar1[2];
    fVar40 = *pfVar1;
    fVar41 = param_4[8];
    iVar65 = param_6[2];
    fVar42 = param_4[7];
    fVar43 = param_4[0xb];
    fVar44 = *(float *)(param_5 + 4 + iVar65 * 0xc);
    fVar45 = param_4[1];
    fVar46 = *(float *)(param_5 + iVar65 * 0xc);
    fVar47 = *param_4;
    fVar48 = *(float *)(param_5 + 8 + iVar65 * 0xc);
    fVar49 = param_4[2];
    pfVar1 = (float *)(param_5 + iVar65 * 0xc);
    fVar50 = param_4[3];
    fVar51 = pfVar1[2];
    fVar52 = param_4[6];
    fVar53 = *pfVar1;
    fVar54 = param_4[4];
    fVar55 = pfVar1[1];
    fVar56 = param_4[5];
    fVar57 = param_4[7];
    fVar58 = param_4[10];
    fVar59 = pfVar1[2];
    fVar60 = *pfVar1;
    fVar61 = param_4[8];
    fVar62 = param_4[9];
    fVar63 = pfVar1[1];
    fVar64 = param_4[0xb];
    *(undefined1 *)(param_2 + 10) = 0;
    *(undefined1 *)((int)param_2 + 0x2a) = 1;
    param_2[0xb] = fVar3 * fVar5 + fVar4 * fVar67 + fVar10 * fVar11 + fVar34;
    param_2[0xc] = fVar12 * fVar13 + fVar6 * fVar7 + fVar14 * fVar15 + fVar35;
    param_2[0xd] = fVar17 * fVar18 + fVar8 * fVar9 + fVar19 * fVar20 + fVar36;
    param_2[0xe] = fVar26 * fVar27 + fVar21 * fVar22 + fVar28 * fVar29 + fVar37;
    param_2[0xf] = fVar30 * fVar31 + fVar24 * fVar25 + fVar32 * fVar33 + fVar42;
    param_2[0x10] = fVar38 * fVar39 + fVar16 * fVar23 + fVar40 * fVar41 + fVar43;
    param_2[0x11] = fVar44 * fVar45 + fVar46 * fVar47 + fVar48 * fVar49 + fVar50;
    param_2[0x12] = fVar53 * fVar54 + fVar51 * fVar52 + fVar55 * fVar56 + fVar57;
    param_2[0x13] = fVar60 * fVar61 + fVar58 * fVar59 + fVar62 * fVar63 + fVar64;
  }
  *(undefined1 *)((int)param_2 + 0x29) = 0x28;
  fVar3 = param_7->m[1][1];
  fVar4 = param_7->m[2][1];
  fVar67 = param_2[1];
  fVar5 = param_7->m[1][2];
  fVar6 = param_7->m[1][0];
  fVar7 = *param_2;
  fVar8 = param_7->m[2][2];
  fVar9 = param_7->m[1][3];
  fVar10 = param_7->m[2][0];
  fVar11 = *param_2;
  fVar12 = param_7->m[2][3];
  *param_2 = param_7->m[0][2] * param_2[2] + param_7->m[0][1] * param_2[1] +
             param_7->m[0][0] * *param_2 + param_7->m[0][3];
  param_2[1] = fVar5 * param_2[2] + fVar3 * param_2[1] + fVar6 * fVar7 + fVar9;
  param_2[2] = fVar8 * param_2[2] + fVar4 * fVar67 + fVar10 * fVar11 + fVar12;
  Math::RotatePointUsingAffine((vec3 *)(param_2 + 3),param_7,(vec3 *)(param_2 + 3));
  applyHitBasisTransform();
  *(undefined2 *)(param_2 + 7) = 0;
  *(undefined1 *)((int)param_2 + 0x1e) = *(undefined1 *)((int)param_6 + 0x11);
  *(char *)((int)param_2 + 0x27) = (char)param_6[4];
  fVar3 = (float)param_6[3];
  param_2[0x14] = (float)param_6;
  param_2[8] = fVar3;
  param_2[6] = -NAN;
  *(undefined2 *)(param_2 + 9) = 0;
  *(undefined1 *)((int)param_2 + 0x26) = 1;
  return;
}



int * collideWithColliders(int *param_1,vec3 *param_2,vec3 *param_3,vec3 *param_4,vec3 *param_5,uint param_6
                  ,uint param_7,float *param_8)

{
  int *piVar1;
  vec3 *pvVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  int *local_18;
  
  piVar8 = (int *)param_1[1];
  piVar1 = piVar8 + *param_1 * 5;
  piVar6 = (int *)0x0;
  local_18 = (int *)0x0;
  if (piVar1 <= piVar8) {
    return (int *)0x0;
  }
  do {
    uVar3 = piVar8[3];
    if (((((param_6 & uVar3) != 0) && (((param_7 & 0xfff3bfff) == 0 || ((param_7 & uVar3) == 0))))
        && (((uVar3 & 0xc4000) == 0 || ((~param_7 & uVar3 & 0xc4000) != 0)))) &&
       (iVar7 = collidePoints(param_4,param_2 + piVar8[2],param_2 + *piVar8,param_8,
                             param_2 + piVar8[1],param_3), piVar6 = local_18, iVar7 != 0)) {
      fVar10 = *param_8;
      param_4->x = param_4->x * fVar10;
      param_4->y = param_4->y * fVar10;
      param_4->z = param_4->z * fVar10;
      iVar7 = piVar8[1];
      iVar4 = *piVar8;
      iVar5 = piVar8[2];
      fVar11 = param_2[iVar7].y - param_2[iVar4].y;
      fVar14 = param_2[iVar7].z - param_2[iVar4].z;
      fVar13 = param_2[iVar7].x - param_2[iVar4].x;
      pvVar2 = param_2 + iVar4;
      fVar10 = param_2[iVar5].y - pvVar2->y;
      fVar12 = param_2[iVar5].z - pvVar2->z;
      fVar15 = param_2[iVar5].x - pvVar2->x;
      param_5->x = fVar12 * fVar11 - fVar10 * fVar14;
      param_5->y = fVar15 * fVar14 - fVar12 * fVar13;
      param_5->z = fVar10 * fVar13 - fVar11 * fVar15;
      fVar10 = param_5->x * param_5->x + param_5->y * param_5->y + param_5->z * param_5->z;
      if (fVar10 != 0.0) {
        fVar9 = (float10)invsqrt(fVar10);
        param_5->x = (float)(fVar9 * (float10)param_5->x);
        param_5->y = (float)(fVar9 * (float10)param_5->y);
        param_5->z = (float)(fVar9 * (float10)param_5->z);
      }
      piVar6 = piVar8;
      local_18 = piVar8;
      if (*param_8 == 0.0) {
        return piVar8;
      }
    }
    piVar8 = piVar8 + 5;
    if (piVar1 <= piVar8) {
      return piVar6;
    }
  } while( true );
}



uint collideWithCollisionThings(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,uint param_5
                 ,float *param_6,int *param_7,int param_8,vec3 *param_9)

{
  uint uVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint local_8;
  
  uVar5 = param_7[1];
  uVar1 = uVar5 + *param_7 * 0x14;
  local_8 = 0;
  do {
    if (uVar1 <= uVar5) {
      return local_8;
    }
    uVar3 = *(uint *)(uVar5 + 0xc);
    if (((((param_4 & uVar3) != 0) && (((param_5 & 0xfff3bfff) == 0 || ((param_5 & uVar3) == 0))))
        && (((uVar3 & 0xc4000) == 0 || ((~param_5 & uVar3 & 0xc4000) != 0)))) &&
       (iVar4 = collideSphereWithThing(param_8 + *(int *)(uVar5 + 4) * 0xc,param_8 + *(int *)(uVar5 + 8) * 0xc
                             ,param_1,param_9,param_2,param_3,param_6), iVar4 != 0)) {
      fVar2 = *param_6;
      param_9->x = param_9->x * fVar2;
      param_9->y = param_9->y * fVar2;
      param_9->z = param_9->z * fVar2;
      local_8 = uVar5;
      if (*param_6 == 0.0) {
        return uVar5;
      }
    }
    uVar5 = uVar5 + 0x14;
  } while( true );
}



undefined4
applyCollisionsToBuffer(AffineTransform *param_1,float *param_2,undefined4 param_3,uint param_4,uint param_5,
            undefined4 *param_6)

{
  int *piVar1;
  uint uVar2;
  void *pvVar3;
  int *in_EAX;
  int iVar4;
  Buffer *buf;
  int unaff_EBX;
  int *piVar5;
  undefined4 local_8;
  
  piVar5 = (int *)in_EAX[1];
  piVar1 = piVar5 + *in_EAX * 5;
  local_8 = 0;
  for (; piVar5 < piVar1; piVar5 = piVar5 + 5) {
    uVar2 = piVar5[3];
    if (((((param_4 & uVar2) != 0) && (((param_5 & 0xfff3bfff) == 0 || ((param_5 & uVar2) == 0))))
        && (((uVar2 & 0xc4000) == 0 || ((~param_5 & uVar2 & 0xc4000) != 0)))) &&
       (iVar4 = segmentsIntersectWithinDistance(param_2,param_3,unaff_EBX + *piVar5 * 0xc,unaff_EBX + piVar5[1] * 0xc,
                             unaff_EBX + piVar5[2] * 0xc), iVar4 != 0)) {
      if (param_6 != (undefined4 *)0x0) {
        buf = (Buffer *)*param_6;
        if (buf->tail == buf->end) {
          buf = runtime::ExtendArray(buf);
          *param_6 = buf;
        }
        pvVar3 = buf->tail;
        buf->tail = (void *)((uint)buf->valueSize + (int)pvVar3);
        createCollisionHitFromMatrix(&Game::someGlobalPos,pvVar3,param_3,(float *)0x0,unaff_EBX,piVar5,param_1,
                     param_2);
      }
      local_8 = 1;
    }
  }
  return local_8;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

BOOL Collision::CalculateAABBForColliders
               (uint mask,bool param_2,void *aabbCallback,background *bg,ColliderType2Entry *entry,
               bool param_6)

{
  int iVar1;
  Collider *collider;
  Collider *endCollider;
  
  collider = (Collider *)entry->entries[0];
  endCollider = collider + entry->numEntries;
  while( true ) {
    if (endCollider <= collider) {
      return 1;
    }
    if ((((mask == 0) || ((collider->collisionMask & mask) != 0)) &&
        ((!param_2 || ((bool)collider->field13_0x10 == param_2)))) &&
       (((!param_6 || ((bool)collider->field14_0x11 == param_6)) &&
        (iVar1 = (*aabbCallback)(collider,bg), iVar1 == 0)))) break;
    collider = collider + 1;
  }
  return 0;
}




void ColliderSet::processDescriptor(ColliderSetDescriptor *set,int resBase)

{
  int i;
  ColliderSet *colliderSet;
  
  set->matrixPtr = (D3DXMATRIX *)((int)set->matrixPtr + resBase);
  colliderSet = set->colliderSets;
  if (0 < set->numColliderSets) {
    i = 0;
    do {
      if ((code *)Physics::ColliderVTables[colliderSet->colliderType].processDescriptor !=
          (code *)0x0) {
        (*(code *)Physics::ColliderVTables[colliderSet->colliderType].processDescriptor)
                  (colliderSet,resBase);
      }
      i = i + 1;
                    // Offsets into itself
      colliderSet = (ColliderSet *)(&colliderSet->colliderType + colliderSet->size);
    } while (i < set->numColliderSets);
  }
  return;
}



int ColliderSetDescriptor::narrowCollisionCheck
              (vec3 *result1,vec3 *result2,ColliderSetDescriptor *desc,AffineTransform *affine1,
              AffineTransform *affine2,Skeleton *skeleton,uint collisionMask,undefined4 param_8,
              Collision0x54 *outCol)

{
  int collided;
  ColliderSet *set;
  float dx;
  float dy;
  float dz;
  int i;
  BOOL had_collision;
  
  dz = result1->z - result2->z;
  dx = result1->x - result2->x;
  dy = result1->y - result2->y;
                    // If same value return 0
  if (dz * dz + dx * dx + dy * dy <= 2e-07) {
    result2->x = result1->x;
    result2->y = result1->y;
    result2->z = result1->z;
    return 0;
  }
  set = desc->colliderSets;
  had_collision = 0;
  i = 0;
  collided = 0;
  if (0 < desc->numColliderSets) {
    do {
      if (((set->collisionMask & collisionMask) != Nothing) &&
         ((code *)Physics::ColliderVTables[set->colliderType].update != (code *)0x0)) {
        collided = (*(code *)Physics::ColliderVTables[set->colliderType].update)
                             (set,affine1,affine2,skeleton,desc->matrixPtr,result1,result2,
                              collisionMask,param_8,outCol);
        if (collided != 0) {
          had_collision = 1;
        }
      }
      set = (ColliderSet *)(&set->colliderType + set->size);
      i = i + 1;
    } while (i < desc->numColliderSets);
    collided = had_collision;
    if ((had_collision != 0) && (outCol != (Collision0x54 *)0x0)) {
      (outCol->v).x = (outCol->velocity).x * 0.001 + (outCol->v).x;
      (outCol->v).y = (outCol->velocity).y * 0.001 + (outCol->v).y;
      (outCol->v).z = (outCol->velocity).z * 0.001 + (outCol->v).z;
      result2->x = (outCol->velocity).x * 0.001 + result2->x;
      result2->y = (outCol->velocity).y * 0.001 + result2->y;
      result2->z = (outCol->velocity).z * 0.001 + result2->z;
    }
  }
  return collided;
}



int ColliderSetDescriptor::runCollisionCallbacks
              (ColliderSetDescriptor *colDescriptor,undefined4 param_2,undefined4 param_3,
              Skeleton *skeleton,undefined4 param_5,uint param_6,undefined4 param_7,
              Collision0x54 *col54,vec3 *param_9,vec3 *diff)

{
  int iVar1;
  ColliderSet *pCVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int local_8;
  int collisionOccurred;
  
  fVar5 = param_9->z - diff->z;
  fVar3 = param_9->x - diff->x;
  fVar4 = param_9->y - diff->y;
  if (fVar5 * fVar5 + fVar3 * fVar3 + fVar4 * fVar4 <= 2e-07) {
    diff->x = param_9->x;
    diff->y = param_9->y;
    diff->z = param_9->z;
    return 0;
  }
  pCVar2 = colDescriptor->colliderSets;
  collisionOccurred = 0;
  local_8 = 0;
  iVar1 = 0;
  if (0 < colDescriptor->numColliderSets) {
    do {
      if (((pCVar2->collisionMask & param_6) != Nothing) &&
         ((code *)Physics::ColliderVTables[pCVar2->colliderType].callback2 != (code *)0x0)) {
        iVar1 = (*(code *)Physics::ColliderVTables[pCVar2->colliderType].callback2)
                          (pCVar2,param_2,param_3,skeleton,colDescriptor->matrixPtr,param_9,diff,
                           param_5,param_6,param_7,col54);
        if (iVar1 != 0) {
          collisionOccurred = 1;
        }
      }
      pCVar2 = (ColliderSet *)(&pCVar2->colliderType + pCVar2->size);
      local_8 = local_8 + 1;
    } while (local_8 < colDescriptor->numColliderSets);
    iVar1 = collisionOccurred;
    if ((collisionOccurred != 0) && (col54 != (Collision0x54 *)0x0)) {
      (col54->v).x = (col54->velocity).x * 0.001 + (col54->v).x;
      (col54->v).y = (col54->velocity).y * 0.001 + (col54->v).y;
      (col54->v).z = (col54->velocity).z * 0.001 + (col54->v).z;
      diff->x = (col54->velocity).x * 0.001 + diff->x;
      diff->y = (col54->velocity).y * 0.001 + diff->y;
      diff->z = (col54->velocity).z * 0.001 + diff->z;
    }
  }
  return iVar1;
}



undefined4
runCollisionThingCallbacks(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            Buffer<> *bufferSomething)

{
  int iVar1;
  undefined4 uVar2;
  uint unaff_EBX;
  byte *pbVar3;
  int *unaff_EDI;
  int local_8;
  undefined4 local_4;
  
  pbVar3 = (byte *)(unaff_EDI + 4);
  local_4 = 0;
  local_8 = 0;
  uVar2 = 0;
  if (0 < *unaff_EDI) {
    do {
      if ((((*(uint *)(pbVar3 + 4) & unaff_EBX) != 0) &&
          ((code *)Physics::ColliderVTables[*pbVar3].callback3 != (code *)0x0)) &&
         (iVar1 = (*(code *)Physics::ColliderVTables[*pbVar3].callback3)
                            (pbVar3,param_1,param_2,param_3,unaff_EDI[3],param_4,bufferSomething),
         iVar1 != 0)) {
        local_4 = 1;
      }
      local_8 = local_8 + 1;
      pbVar3 = pbVar3 + *(int *)(pbVar3 + 8);
      uVar2 = local_4;
    } while (local_8 < *unaff_EDI);
  }
  return uVar2;
}




BOOL ColliderSetDescriptor::hasCollision0x1235_(ColliderSetDescriptor *desc)

{
  ColliderSet *colliderSet;
  int i;
  
  colliderSet = desc->colliderSets;
  i = 0;
  if (0 < desc->numColliderSets) {
    do {
      if ((colliderSet->flags0x1235 == 0b0001001000110101) &&
         (colliderSet->colliderType < PartSphere)) {
        return 1;
      }
      i = i + 1;
                    // Go to next collider
      colliderSet = (ColliderSet *)(&colliderSet->colliderType + colliderSet->size);
    } while (i < desc->numColliderSets);
  }
  return 0;
}



uint background::runCallbackOnColliders
               (ColliderSetDescriptor *param_1,CollisionMask collisionMask,undefined4 param_3,
               undefined4 param_4,void *aabbCallback,void *callbackParam)

{
  int iVar1;
  uint num_colliders;
  int iVar2;
  ColliderSet *collider;
  
  num_colliders = param_1->numColliderSets;
  iVar2 = 0;
  collider = param_1->colliderSets;
  if (0 < (int)num_colliders) {
    do {
      if ((((collisionMask == Nothing) || ((collider->collisionMask & collisionMask) != Nothing)) &&
          ((code *)Physics::ColliderVTables[collider->colliderType].ctor != (code *)0x0)) &&
         (iVar1 = (*(code *)Physics::ColliderVTables[collider->colliderType].ctor)
                            (collider,collisionMask,param_3,param_4,aabbCallback,callbackParam),
         iVar1 == 0)) {
        return 0;
      }
      num_colliders = param_1->numColliderSets;
      iVar2 = iVar2 + 1;
      collider = (ColliderSet *)(&collider->colliderType + collider->size);
    } while (iVar2 < (int)num_colliders);
  }
  return num_colliders;
}




void updateColliderPositions(entityBodyHuman *body,avatar *av,vec3 *param_3)

{
  float fVar1;
  float fVar2;
  byte bVar3;
  Model *pMVar4;
  AnimCollisionSubresourceEntry *pAVar5;
  SomeActorBodyList *list;
  CollisionMask CVar6;
  Skeleton *local_48;
  int i2;
  int i;
  vec3 local_3c;
  AffineTransform local_30;
  
  bVar3 = (body->body).shatsheetInitialised_;
  if ((bVar3 == 0) || ((1 < bVar3 && (bVar3 < 4)))) {
    (body->body).v2.x = Game::someGlobalPos.x;
    (body->body).v2.y = Game::someGlobalPos.y;
    (body->body).v2.z = Game::someGlobalPos.z;
    return;
  }
  if (body->animCollidersData == (HumanAnimColliderData *)0x0) {
    local_3c.x = param_3->x;
    local_3c.y = param_3->y;
    local_3c.z = param_3->z;
    updateAvatarColliderPosition((((body->body).actor)->avatar).scale.z * (body->body).closenessDistance);
    fVar1 = param_3->y;
    fVar2 = param_3->z;
    (body->body).v2.x = param_3->x - local_3c.x;
    (body->body).v2.y = fVar1 - local_3c.y;
    (body->body).v2.z = fVar2 - local_3c.z;
    return;
  }
  avatar::updateAndGetAffine(av,&local_30,param_3);
  pMVar4 = av->model;
  if (pMVar4 == (Model *)0x0) {
    local_48 = (Skeleton *)0x0;
  }
  else {
    local_48 = pMVar4->skeleton;
    if (local_48 == (Skeleton *)0x0) {
      local_48 = pMVar4->skeleton2;
    }
  }
  list = (SomeActorBodyList *)body->animCollidersData;
  i2 = 0;
  i = 0;
  if (0 < body->numAnimColliders) {
    do {
      pAVar5 = body->animColliders[i];
      if (av->model == (Model *)0x0) {
        CVar6 = Everything;
      }
      else {
        CVar6 = av->model->boneIndices[pAVar5->blendTargetIndex];
      }
      if ((pAVar5->collisionMask & CVar6 & Walls) != Nothing) {
        if (pAVar5->colliderType == Sphere) {
          SomeActorBodyList::accumulateCollisionsFromSkeletonAndAnim(list,local_48,pAVar5,&local_30)
          ;
        }
        else {
          if (pAVar5->colliderType != Cylinder) goto LAB_00075891;
          processCylinderCollider(list);
        }
        list = list + 1;
        i2 = i2 + 1;
      }
LAB_00075891:
      i = i + 1;
    } while (i < body->numAnimColliders);
    if (0 < i2) {
      updateAllAvatarColliders(param_3,av,body->animCollidersData,i2,&local_3c);
      param_3->x = param_3->x + local_3c.x;
      param_3->y = local_3c.y + param_3->y;
      param_3->z = param_3->z + local_3c.z;
      (body->body).v2.x = local_3c.x;
      (body->body).v2.y = local_3c.y;
      (body->body).v2.z = local_3c.z;
      return;
    }
  }
  (body->body).v2.x = Game::someGlobalPos.x;
  (body->body).v2.y = Game::someGlobalPos.y;
  (body->body).v2.z = Game::someGlobalPos.z;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4 __fastcall
UpdateEntityHumanState
          (undefined4 param_1,undefined4 param_2,entityBodyHuman *bodyHuman,undefined4 param_4,
          undefined4 param_5,undefined4 param_6)

{
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  actorState *actorState;
  
  local_1c = 0;
  local_18 = 0;
  local_c = param_4;
  actorState = (bodyHuman->body).actorState;
  local_20 = 0x62;
  local_8 = param_5;
  local_4 = param_6;
  if (actorState != (actorState *)0x0) {
    local_14 = param_1;
    local_10 = param_2;
    (*actorState->vtable->onMessage)(actorState,&local_20);
    if ((local_1c != 0) && (local_18 != 0)) {
      return 1;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int __fastcall collideWithGroundOrScene(void *param_1,CollisionMask param_2,vec3 *param_3,float param_4)

{
  BackgroundCollisionThing *pBVar1;
  Collision0x54 *pCVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  vec3 *unaff_ESI;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  if (in_EAX == 0) {
    if (param_4 == 0.0) {
      iVar3 = Collision::checkAvatarsWithCollisionInScene(unaff_ESI,param_3,param_2,param_1);
    }
    else {
      iVar3 = Collision::runCollisionFunctionWithAllAvatars
                        (param_3,unaff_ESI,param_4,param_2,param_1);
    }
    if (iVar3 != 0) {
      pCVar2 = (Physics::CollisionContexts[0].ctx)->head;
      DAT_0050691c = pCVar2->field_0x1e;
      _DAT_00506920 = *(undefined4 *)&pCVar2->field_0x20;
      DAT_00506924 = (pCVar2->velocity).x;
      DAT_00506928 = (pCVar2->velocity).y;
      DAT_0050692c = (pCVar2->velocity).z;
      return iVar3;
    }
  }
  else {
    iVar3 = findFloorLayerByPosition(param_3,-1,0);
    iVar4 = Background::isCollisionThings(iVar3,param_3);
    pBVar1 = BackgroundCollisionThings[iVar3];
    if (iVar4 != -1) {
      fVar7 = param_3->x - unaff_ESI->x;
      fVar8 = param_3->y - unaff_ESI->y;
      fVar9 = param_3->z - unaff_ESI->z;
      fVar5 = ((unaff_ESI->z + unaff_ESI->x) * 0.0 + unaff_ESI->y) -
              (float)(int)*(short *)(pBVar1->field10_0x10 + 2 + iVar4 * 0x12);
      if ((0.0 <= fVar5) && (fVar6 = (fVar9 + fVar7) * 0.0 - fVar8, fVar5 <= fVar6)) {
        fVar5 = fVar5 / fVar6;
        if (fVar6 == 0.0) {
          fVar5 = 0.0;
        }
        param_3->x = unaff_ESI->x + fVar7 * fVar5;
        param_3->y = fVar8 * fVar5 + unaff_ESI->y;
        param_3->z = unaff_ESI->z + fVar9 * fVar5;
        iVar3 = pBVar1->field10_0x10 + iVar4 * 0x12;
        DAT_0050691c = *(char *)(iVar3 + 0xb);
        if (DAT_0050691c == '\0') {
          DAT_0050691c = *(char *)(iVar3 + 10);
        }
        _DAT_00506920 = 8;
        DAT_00506924 = 0.0;
        DAT_00506928 = 1.0;
        DAT_0050692c = 0.0;
        return 1;
      }
    }
  }
  return 0;
}




void Physics::UpdateVelocity(PhysicsStruct *ps,float delta,float newT)

{
  float10 new_val;
  
  ps->next = newT;
  if (0.0 < delta) {
    new_val = abs_float((newT - ps->prev) / delta);
    ps->value = (float)new_val;
    return;
  }
  ps->prev = newT;
  ps->value = 0.0;
  return;
}




BOOL Physics::CalculateInterpolations(PhysicsStruct *idk,float delta)

{
  BOOL BVar1;
  PhysicsStruct *ps;
  int i;
  int success_count;
  
  i = 0;
  success_count = 0;
  ps = idk;
  do {
    BVar1 = interpolatePhysicsValue(ps,delta,(float *)(idk[2].count + i));
    if (BVar1 != 0) {
      success_count = success_count + 1;
    }
    i = i + 60;
    ps = ps + 1;
  } while (i < 120);
  return (uint)(success_count == 2);
}




void resolveCollision(Collision0x54 *smth1,Collision0x54 *smth2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0x54;
  if (smth2 != smth1) {
    if ((((uint)smth2 & 7) == 0) && (((uint)smth1 & 7) == 0)) {
      iVar1 = 10;
      do {
        (smth2->v).x = (smth1->v).x;
        (smth2->v).y = (smth1->v).y;
        smth2 = (Collision0x54 *)&(smth2->v).z;
        smth1 = (Collision0x54 *)&(smth1->v).z;
        uVar3 = uVar3 - 8;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    if (((((uint)smth2 & 3) == 0) && (((uint)smth1 & 3) == 0)) && (3 < uVar3)) {
      uVar2 = uVar3 >> 2;
      do {
        (smth2->v).x = (smth1->v).x;
        smth2 = (Collision0x54 *)&(smth2->v).y;
        smth1 = (Collision0x54 *)&(smth1->v).y;
        uVar3 = uVar3 - 4;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    if (uVar3 != 0) {
      iVar1 = (int)smth1 - (int)smth2;
      do {
        *(undefined1 *)&(smth2->v).x = *(undefined1 *)(iVar1 + (int)smth2);
        smth2 = (Collision0x54 *)((int)&(smth2->v).x + 1);
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
  }
  return;
}




undefined4 Collision0x54Data::AreColliding(Collision0x54Data *param_1,Collision0x54Data *param_2)

{
  float fVar1;
  
  if (((((((param_2->field0_0x0 == '\0') && (param_1->field0_0x0 == '\0')) &&
         (fVar1 = param_2->field4_0x4 - param_1->field4_0x4, -0.01 <= fVar1)) &&
        ((fVar1 <= 0.01 && (fVar1 = param_2->field5_0x8 - param_1->field5_0x8, -0.01 <= fVar1)))) &&
       (((fVar1 <= 0.01 &&
         ((fVar1 = param_2->field6_0xc - param_1->field6_0xc, -0.01 <= fVar1 && (fVar1 <= 0.01))))
        && (fVar1 = param_2->field7_0x10 - param_1->field7_0x10, -0.01 <= fVar1)))) &&
      ((((fVar1 <= 0.01 && (fVar1 = param_2->field8_0x14 - param_1->field8_0x14, -0.01 <= fVar1)) &&
        (fVar1 <= 0.01)) &&
       (((fVar1 = param_2->field9_0x18 - param_1->field9_0x18, -0.01 <= fVar1 && (fVar1 <= 0.01)) &&
        ((fVar1 = param_2->field10_0x1c - param_1->field10_0x1c, -0.01 <= fVar1 &&
         ((fVar1 <= 0.01 && (fVar1 = param_2->field11_0x20 - param_1->field11_0x20, -0.01 <= fVar1))
         )))))))) &&
     ((fVar1 <= 0.01 &&
      ((fVar1 = param_2->field12_0x24 - param_1->field12_0x24, -0.01 <= fVar1 && (fVar1 <= 0.01)))))
     ) {
    return 1;
  }
  return 0;
}




void runBroadPhaseTests(int *param_1,vec3 *param_2,int param_3,float param_4,int param_5)

{
  ushort *puVar1;
  ushort uVar2;
  BackgroundCollisionThing *pBVar3;
  int *piVar4;
  bool bVar5;
  byte bVar6;
  undefined2 *puVar7;
  int iVar8;
  ushort *puVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  float fVar13;
  float fVar14;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  float local_3c;
  float local_38;
  int local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  pBVar3 = BackgroundCollisionThings[param_3];
  if (pBVar3 != (BackgroundCollisionThing *)0x0) {
    local_2c = param_2->y;
    local_28 = param_2->z - param_4;
    local_20 = param_2->y;
    local_1c = param_2->z - param_4;
    local_30 = param_2->x - param_4;
    local_14 = param_2->y;
    local_24 = param_2->x + param_4;
    local_10 = param_2->z + param_4;
    local_8 = param_2->y;
    local_18 = param_2->x + param_4;
    local_c = param_2->x - param_4;
    local_4 = param_2->z + param_4;
    fVar13 = param_4;
    computeBroadPhaseBounds(&local_4c,&local_40,&local_44,&local_48);
    iVar8 = *param_1;
    if (iVar8 == 0) {
      puVar7 = malloc_(0x40);
      *(undefined2 **)(puVar7 + 2) = puVar7 + 8;
      *(undefined2 **)(puVar7 + 4) = puVar7 + 8;
      *puVar7 = 0xc;
      puVar7[1] = 4;
      *(undefined2 **)(puVar7 + 6) = puVar7 + 0x20;
      *param_1 = (int)puVar7;
      fVar13 = param_4;
    }
    else {
      piVar4 = *(int **)(iVar8 + 8);
      for (piVar10 = *(int **)(iVar8 + 4); piVar10 < piVar4; piVar10 = piVar10 + 3) {
        if (piVar10[1] == 0) {
          iVar8 = pBVar3->field10_0x10 + *piVar10 * 0x12;
          uVar2 = *(ushort *)(iVar8 + 6);
          bVar6 = (byte)uVar2;
          *(ushort *)(iVar8 + 6) = (byte)(bVar6 - 1 ^ bVar6) & 0x1f ^ uVar2;
        }
        else {
          iVar8 = pBVar3->field10_0x10 + *piVar10 * 0x12;
          uVar2 = *(ushort *)(iVar8 + 6);
          *(ushort *)(iVar8 + 6) = (((uVar2 >> 5) - 1) * 0x20 ^ uVar2) & 0x1e0 ^ uVar2;
        }
      }
      *(undefined4 *)(*param_1 + 8) = *(undefined4 *)(*param_1 + 4);
    }
    local_38 = fVar13 * fVar13;
    if (BackgroundCollisionThings[0] == (BackgroundCollisionThing *)0x0) {
      fVar14 = 0.0;
    }
    else {
      fVar14 = (float)(int)BackgroundCollisionThings[0]->someF * 0.5;
    }
    local_3c = (fVar14 + fVar13) * (fVar14 + fVar13);
    local_34 = Background::isCollisionThings(param_3,param_2);
    param_3 = local_4c;
    bVar5 = local_4c <= local_40;
    local_4c = local_44;
    iVar8 = local_48;
    if (bVar5) {
      do {
        iVar11 = local_4c;
        if (local_4c <= iVar8) {
          do {
            iVar11 = *(int *)pBVar3 * local_4c + param_3;
            iVar8 = pBVar3->field10_0x10 + iVar11 * 0x12;
            fVar13 = (float)(int)*(short *)(pBVar3->field10_0x10 + iVar11 * 0x12) - param_2->x;
            fVar14 = (float)(int)*(short *)(iVar8 + 4) - param_2->z;
            fVar13 = fVar14 * fVar14 + fVar13 * fVar13;
            if (fVar13 <= local_3c) {
              if (((param_5 != 0) || (fVar13 < local_38)) || (iVar11 == local_34)) {
                bVar6 = (byte)*(ushort *)(iVar8 + 6);
                *(ushort *)(iVar8 + 6) = (byte)(bVar6 + 1 ^ bVar6) & 0x1f ^ *(ushort *)(iVar8 + 6);
                puVar9 = (ushort *)*param_1;
                if (*(int *)(puVar9 + 4) == *(int *)(puVar9 + 6)) {
                  iVar8 = (*(int *)(puVar9 + 4) - *(int *)(puVar9 + 2)) / (int)(uint)*puVar9;
                  iVar12 = (uint)puVar9[1] + iVar8;
                  puVar9 = (ushort *)AllocateMoreAStruct_33((uint)*puVar9 * iVar12 + 0x10,puVar9);
                  puVar1 = puVar9 + 8;
                  *(ushort **)(puVar9 + 2) = puVar1;
                  *(ushort **)(puVar9 + 4) = (ushort *)((uint)*puVar9 * iVar8 + (int)puVar1);
                  *(ushort **)(puVar9 + 6) = (ushort *)((uint)*puVar9 * iVar12 + (int)puVar1);
                  *param_1 = (int)puVar9;
                }
                piVar10 = *(int **)(puVar9 + 4);
                *(uint *)(puVar9 + 4) = (uint)*puVar9 + (int)piVar10;
                piVar10[1] = 0;
              }
              else {
                uVar2 = *(ushort *)(iVar8 + 6);
                *(ushort *)(iVar8 + 6) = ((uVar2 & 0xffe0) + 0x20 ^ uVar2) & 0x1e0 ^ uVar2;
                puVar9 = (ushort *)*param_1;
                if (*(int *)(puVar9 + 4) == *(int *)(puVar9 + 6)) {
                  iVar8 = (*(int *)(puVar9 + 4) - *(int *)(puVar9 + 2)) / (int)(uint)*puVar9;
                  iVar12 = (uint)puVar9[1] + iVar8;
                  puVar9 = (ushort *)AllocateMoreAStruct_33((uint)*puVar9 * iVar12 + 0x10,puVar9);
                  puVar1 = puVar9 + 8;
                  *(ushort **)(puVar9 + 2) = puVar1;
                  *(ushort **)(puVar9 + 4) = (ushort *)((uint)*puVar9 * iVar8 + (int)puVar1);
                  *(ushort **)(puVar9 + 6) = (ushort *)((uint)*puVar9 * iVar12 + (int)puVar1);
                  *param_1 = (int)puVar9;
                }
                piVar10 = *(int **)(puVar9 + 4);
                *(uint *)(puVar9 + 4) = (uint)*puVar9 + (int)piVar10;
                piVar10[1] = 1;
              }
              *piVar10 = iVar11;
            }
            local_4c = local_4c + 1;
            iVar11 = local_44;
            iVar8 = local_48;
          } while (local_4c <= local_48);
        }
        param_3 = param_3 + 1;
        local_4c = iVar11;
      } while (param_3 <= local_40);
    }
  }
  return;
}




char getFloorMovementIndex(int collisionThingIndex,vec3 *param_2)

{
  char cVar1;
  BackgroundCollisionThing *pBVar2;
  int iVar3;
  
  pBVar2 = BackgroundCollisionThings[collisionThingIndex];
  if (pBVar2 != (BackgroundCollisionThing *)0x0) {
    iVar3 = Background::isCollisionThings(collisionThingIndex,param_2);
    if (iVar3 != -1) {
      iVar3 = pBVar2->field10_0x10 + iVar3 * 0x12;
      cVar1 = *(char *)(iVar3 + 0xb);
      if (cVar1 != '\0') {
        return cVar1;
      }
      return *(char *)(iVar3 + 10);
    }
  }
  return '\0';
}




undefined4 runCollisionTest(vec3 *param_1,vec3 *param_2,CollisionContext *param_3,int cylinder_)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  vec3 local_18;
  float local_c;
  float local_4;
  
  fVar7 = (param_3->currentPos).y + param_1->y;
  local_c = param_1->x + (param_3->currentPos).x;
  local_4 = (param_3->currentPos).z + param_1->z;
  if ((fVar7 <= *(float *)(cylinder_ + 8) + *(float *)(cylinder_ + 0x14)) &&
     (*(float *)(cylinder_ + 8) <= param_3->field9_0x14 + fVar7)) {
    fVar8 = *(float *)(cylinder_ + 0x1c) + param_3->field14_0x1c;
    local_18.z = local_4 - *(float *)(cylinder_ + 0xc);
    local_18.x = local_c - *(float *)(cylinder_ + 4);
    local_18.y = 0.0;
    fVar6 = scaled_invsqrt(local_18.z * local_18.z + local_18.x * local_18.x);
    fVar7 = (float)fVar6;
    if (fVar6 < (float10)1e-05) {
      local_18.x = 1.0;
      fVar7 = fVar8 - 0.01;
    }
    if (fVar7 < fVar8) {
      scaleVecByMagnitude(fVar8,&local_18);
      fVar7 = *(float *)(cylinder_ + 0xc);
      param_2->x = (*(float *)(cylinder_ + 4) + local_18.x) - local_c;
      param_2->z = (fVar7 + local_18.z) - local_4;
      param_2->y = 0.0;
      fVar7 = param_3->field9_0x14;
      fVar8 = *(float *)(cylinder_ + 0xc);
      fVar2 = (param_3->currentPos).z;
      fVar9 = *(float *)(cylinder_ + 0x14) * 0.5 + *(float *)(cylinder_ + 8);
      fVar3 = (param_3->currentPos).y;
      fVar4 = param_1->y;
      fVar5 = param_1->z;
      iVar1 = DAT_00511188 * 0xc;
      *(float *)(&DAT_005111ac + iVar1) =
           ((param_1->x + (param_3->currentPos).x) - *(float *)(cylinder_ + 4)) * 0.5 +
           *(float *)(cylinder_ + 4);
      *(float *)(&DAT_005111b0 + iVar1) = ((fVar4 + fVar7 * 0.5 + fVar3) - fVar9) * 0.5 + fVar9;
      *(float *)(&DAT_005111b4 + iVar1) = ((fVar5 + fVar2) - fVar8) * 0.5 + fVar8;
      return 1;
    }
  }
  return 0;
}



undefined4
testCylinderCollision(undefined4 param_1,int param_2,undefined4 param_3,int param_4,float *param_5,
            float *param_6)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_8 = *(float *)(param_4 + 8) + param_6[1];
  local_c = *(float *)(param_4 + 4) + *param_6;
  local_4 = *(float *)(param_4 + 0xc) + param_6[2];
  if ((*(float *)(param_2 + 8) + *(float *)(param_2 + 0x14) < local_8) ||
     (*(float *)(param_4 + 0x14) + local_8 < *(float *)(param_2 + 8))) {
    return 0;
  }
  fVar7 = local_4 - *(float *)(param_2 + 0xc);
  fVar8 = *(float *)(param_2 + 0x1c) + *(float *)(param_4 + 0x1c);
  fVar6 = local_c - *(float *)(param_2 + 4);
  fVar5 = scaled_invsqrt(fVar7 * fVar7 + fVar6 * fVar6);
  fVar6 = (float)fVar5;
  if (fVar5 < (float10)1e-05) {
    fVar6 = fVar8 - 0.01;
  }
  if (fVar8 <= fVar6) {
    return 0;
  }
  getXZDeltaBetweenAvatars(param_3);
  if (param_5 != (float *)0x0) {
    fVar6 = *param_5 * -1.0;
    fVar7 = param_5[2] * -1.0;
    if (0.0 <= local_10 * fVar7 + fVar6 * local_18 + local_14 * 0.0) {
      local_14 = 0.0;
      local_18 = fVar6;
      local_10 = fVar7;
    }
    else {
      local_14 = -0.0;
      local_18 = fVar6 * -1.0;
      local_10 = fVar7 * -1.0;
    }
  }
  rayCollideWithColliders(*(undefined4 *)(param_4 + 0x1c),*(undefined4 *)(param_2 + 0x1c),&local_18);
  fVar6 = *(float *)(param_2 + 0xc);
  fVar7 = *(float *)(param_4 + 0x14);
  fVar8 = *(float *)(param_4 + 0xc);
  fVar9 = *(float *)(param_2 + 0x14) * 0.5 + *(float *)(param_2 + 8);
  fVar2 = *(float *)(param_4 + 8);
  fVar3 = param_6[1];
  fVar4 = param_6[2];
  iVar1 = DAT_00511188 * 0xc;
  *(float *)(&DAT_005111ac + iVar1) =
       ((*param_6 + *(float *)(param_4 + 4)) - *(float *)(param_2 + 4)) * 0.5 +
       *(float *)(param_2 + 4);
  *(float *)(&DAT_005111b0 + iVar1) = ((fVar3 + fVar7 * 0.5 + fVar2) - fVar9) * 0.5 + fVar9;
  *(float *)(&DAT_005111b4 + iVar1) = ((fVar4 + fVar8) - fVar6) * 0.5 + fVar6;
  return 1;
}




Buffer<> ** Physics::RefreshCollisionContexts(void)

{
  Buffer<> *pBVar1;
  Buffer<> *new_buffer;
  Buffer<> **ppuVar1;
  
  pBVar1 = CollisionContexts[NumCollisions].ctx;
  ppuVar1 = &CollisionContexts[NumCollisions].ctx;
  if (pBVar1 == (Buffer<> *)0x0) {
    new_buffer = malloc_(0x358);
    new_buffer->head = new_buffer->values;
    new_buffer->tail = new_buffer->values;
    new_buffer->valuesize = 0x54;
    new_buffer->capacity = 10;
    new_buffer->end = (Collision0x54 *)(new_buffer + 1);
    *ppuVar1 = new_buffer;
    return ppuVar1;
  }
  pBVar1->tail = pBVar1->head;
  return ppuVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void InitialiseColliders(void)

{
  uint8_t uVar1;
  int i;
  code *callback;
  
  i = 0;
  if (0 < Game::SomeThingsToSetUp) {
    do {
      if (GameColliderSetupBitfield_ARRAY_00512420[i].field2_0x2 == 0) {
        uVar1 = GameColliderSetupBitfield_ARRAY_00512420[i].field0_0x0;
        callback = Collider::removeFlags;
      }
      else {
        uVar1 = GameColliderSetupBitfield_ARRAY_00512420[i].field0_0x0;
        callback = Collider::addFlags;
      }
      Collision::RunColliderCallbackOnAllAvatars(uVar1,callback,4);
      i = i + 1;
    } while (i < Game::SomeThingsToSetUp);
  }
  Game::SomeThingsToSetUp = 0;
  return;
}




void Collision::RunColliderCallbackOnAllAvatars(undefined4 param_1,void *aabbCallback,void *param_3)

{
  avatar_0x1e0 pEVar1;
  byte bVar2;
  ColliderSet *collider;
  int iVar3;
  ColliderSetDescriptor *col_set;
  ModelDescriptor *model_desc;
  
  pEVar1 = Game::SceneInfo.avatarsWithCollision.head;
  do {
    if (pEVar1 == (avatar_0x1e0)0x0) {
      return;
    }
    if (((ADJ(pEVar1)->model != (Model *)0x0) &&
        (model_desc = ADJ(pEVar1)->model->descriptor, model_desc != (ModelDescriptor *)0x0)) &&
       (col_set = model_desc->runtimeCtx->colliders, col_set != (ColliderSetDescriptor *)0x0)) {
      iVar3 = 0;
      collider = col_set->colliderSets;
      if (0 < col_set->numColliderSets) {
        do {
          if ((collider->flags0x1235 == 0x1235) && (collider->colliderType < PartSphere)) {
            bVar2 = 1;
            goto LAB_0012c8ec;
          }
          iVar3 = iVar3 + 1;
          collider = (ColliderSet *)(&collider->colliderType + collider->size);
        } while (iVar3 < col_set->numColliderSets);
      }
      bVar2 = 0;
LAB_0012c8ec:
      if ((ColliderSetDescriptor *)(-(uint)bVar2 & (uint)col_set) != (ColliderSetDescriptor *)0x0) {
        background::runCallbackOnColliders
                  ((ColliderSetDescriptor *)(-(uint)bVar2 & (uint)col_set),0,param_1,0,aabbCallback,
                   param_3);
      }
    }
    pEVar1 = pEVar1->next;
  } while( true );
}




BOOL Collider::addFlags(Collider *param_1,uint param_2)

{
  param_1->collisionMask = param_1->collisionMask | param_2;
  return 1;
}




BOOL Collider::removeFlags(Collider *param_1,uint param_2)

{
  param_1->collisionMask = param_1->collisionMask & ~param_2;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void testSphereCollideAtPosition(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  avatar *in_EAX;
  undefined1 local_10 [4];
  vec3 local_c;
  
  avatar::getWorldPosition(in_EAX,&local_c);
  pathfindingLineOfSight(param_1,param_2,param_3,param_4,0,param_5,local_10,in_EAX->tag);
  return;
}



undefined4 __thiscall
testSphereCollideInBackgroundThing(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  undefined1 local_10 [4];
  float local_c;
  float local_8;
  float local_4;
  
  if (in_EAX == -1) {
    return 0;
  }
  iVar1 = BackgroundCollisionThings[param_1]->field10_0x10 + in_EAX * 0x12;
  local_c = (float)(int)*(short *)(BackgroundCollisionThings[param_1]->field10_0x10 + in_EAX * 0x12)
  ;
  local_8 = (float)(int)*(short *)(iVar1 + 2);
  local_4 = (float)(int)*(short *)(iVar1 + 4);
  uVar2 = pathfindingLineOfSight(param_2,param_3,param_4,0,param_5,0,local_10,0);
  return uVar2;
}




