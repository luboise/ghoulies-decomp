/* collision.h - Collision system: EDB2 broadphase, colliders, physics
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern int FUN_00036a00(ushort param_1,short param_2,BackgroundCollisionThing *param_3);
extern undefined4 ColliderPairValue::calculateAABB(Collider *param_1,AABBFat *aabb);
extern void ColliderType2::processDescriptor(ColliderType2 *this,int resBase);
extern void BoxCollider::processDescriptor(BoxCollider *box,int basePtr);
extern void ColliderSet::processDescriptor(ColliderSetDescriptor *set,int resBase);
extern BOOL ColliderSetDescriptor::hasCollision0x1235_(ColliderSetDescriptor *desc);
extern void updateColliderPositions(entityBodyHuman *body,avatar *av,vec3 *param_3);
extern int __fastcall FUN_000eca20(void *param_1,CollisionMask param_2,vec3 *param_3,float param_4);
extern void Physics::UpdateVelocity(PhysicsStruct *ps,float delta,float newT);
extern BOOL Physics::CalculateInterpolations(PhysicsStruct *idk,float delta);
extern void resolveCollision(Collision0x54 *smth1,Collision0x54 *smth2);
extern undefined4 Collision0x54Data::AreColliding(Collision0x54Data *param_1,Collision0x54Data *param_2);
extern void runBroadPhaseTests(int *param_1,vec3 *param_2,int param_3,float param_4,int param_5);
extern char FUN_001117a0(int collisionThingIndex,vec3 *param_2);
extern undefined4 runCollisionTest(vec3 *param_1,vec3 *param_2,CollisionContext *param_3,int cylinder_);
extern Buffer<> ** Physics::RefreshCollisionContexts(void);
extern void InitialiseColliders(void);
extern void Collision::RunColliderCallbackOnAllAvatars(undefined4 param_1,void *aabbCallback,void *param_3);
extern BOOL Collider::addFlags(Collider *param_1,uint param_2);
extern BOOL Collider::removeFlags(Collider *param_1,uint param_2);
