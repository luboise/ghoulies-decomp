/* background.h - Background rendering, collision things, GhoulyBox
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void background::getAllocDetails(ObjectAllocDetails *param_1);
extern void background::getVTable(void);
extern undefined4 background::draw(avatar *param_1,undefined4 param_2,BOOL someFlag);
extern undefined4 background::ctor(background *bg,backgroundParams *params);
extern void background::dtor(background *bg);
extern int background::calculateAABB(background *bg);
extern void background::loadModelSubres0x2(background *bg);
extern void background::loalModelSubres0xf(background *bg);
extern undefined4 Background::RegisterColliderCallback(Collider *collider,background *bg);
extern void background::onMessage(background *bg,Avatar_HitByActorMessage *msg);
extern void LoadBackgroundPartTables(void);
extern void background::doBigUpdate(background *bg);
extern void background::update(background *bg);
extern void GhoulyBox::loadFromDescriptor(GhoulyBox *this,GhoulyBoxDescriptor *res);
extern void __fastcall FocusOnDoors_(int param_1,int param_2);
extern void background::bigCollisionCheck2(undefined4 param_1);
extern void background::bigCollisionCheck1(undefined4 param_1);
extern GhoulyBox * GhoulyBox::fromAID(char *ghoulyBoxAID);
extern void GhoulyBox::dtor(void *param_1);
extern int Background::isCollisionThings(int index,vec3 *param_2);
extern void LoadBackgroundTiles(void);
extern void Background::updateViews(void);
extern void SetupBackgroundEntries(void);
extern void background::updateModelChildren_(int *param_1,float param_2);
