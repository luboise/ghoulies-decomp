/* weapon.h - Weapons, projectiles, extinguishers, wield logic
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern BOOL entityWeaponProjectileHome::hasAudioEntry(char *param_1);
extern void switchD_000c6114::caseD_10(weapon *param_1);
extern void entityWeaponExtinguisher::initProjectiles(entityWeaponExtinguisher *param_1);
extern void entityWeaponExtinguisher::updateParticleLists(entityWeaponExtinguisher *param_1);
extern void entityWeaponExtinguisher::updateParticles2(entityWeaponExtinguisher *param_1,float dt);
extern void entityWeaponWaterPistol::getVTable(void);
extern void entityWeaponGun::getVTable(void);
extern void entityWeaponGun::onMessage(entityWeaponGun *param_1,Message *param_2);
extern void entityWeaponProjectile::getAllocDetails(undefined4 *param_1);
extern void entityWeaponProjectile::getVTable(void);
extern undefined4 entityWeaponProjectile::ctor(avatar *param_1,int param_2);
extern void entityWeaponProjectile::dtor(int param_1);
extern void entityWeaponProjectile::func17(entityWeaponProjectile *param_1,undefined4 param_2);
extern void entityWeaponProjectile::onMessage(entityWeaponProjectile *wpn,Message *msg);
extern void entityWeaponProjectile::func16(actor *param_1,WeaponSignal param_2,uint newState);
extern void entityWeaponProjectileHome::getAllocDetails(undefined4 *param_1);
extern void entityWeaponProjectileHome::getVTable(void);
extern void entityWeaponProjectileHome::func17(entityWeaponProjectileHome *param_1,undefined4 param_2);
extern void entityWeaponProjectileHome::onMessage(weapon *wpn,Message *param_2);
extern undefined4 entityWeaponProjectileHome::draw(avatar *param_1,undefined4 param_2,int param_3);
extern void entityWeaponProjectileLarge::getAllocDetails(undefined4 *param_1);
extern void entityWeaponProjectileLarge::getVTable(void);
extern void entityWeaponProjectileLarge::onMessage(entityWeaponProjectileLarge *param_1,Message *param_2);
extern void entityWeaponWielding::getAllocDetails(undefined4 *param_1);
extern void entityWeaponWielding::getVTable(void);
extern void entityWeaponWielding::ctor(entityWeaponWielding *weapon,entityWeaponWieldingParams *params);
extern void entityWeaponWielding::onMessage(entityWeaponWielding *weapon,Message *param_2);
extern void weapon::initPickupHitboxes(weapon *wpn,weaponParams *params);
extern int weapon::onDestroy(weapon *weapon);
extern void weapon::getAllocDetails(undefined4 *param_1);
extern void weapon::getVTable(void);
extern undefined4 weapon::func5(avatar *param_1,undefined4 param_2,BOOL param_3);
extern undefined4 weapon::ctor(weapon *weapon,weaponParams *param_2);
extern void weapon::dtor(int param_1);
extern int * weapon::getIntOrStruct(int param_1);
extern uint32_t weapon::getAttribute(ushort param_1,weapon *wpn);
extern void weapon::onMessage(weapon *weapon,Message *param_2);
extern void weapon::onBreakableHit(weapon *weapon,Avatar_BreakableHitMessage *msg);
extern void weapon::loadGraphics(weapon *param_1);
extern void weapon::calculateRandomValues(weapon *weapon,weaponParams *params);
extern void weapon::func17OnSomething(void);
extern void weapon::func17(void);
extern void weapon::doSomething(weapon *wpn,void *this);
extern void weapon::func15(int param_1,undefined2 param_2);
extern void weapon::func16(int param_1,undefined2 param_2);
extern void weapon::func17(weapon *param_1,undefined2 param_2);
extern void weapon::onSignal(weapon *wpn,WeaponSignal signal);
extern void weapon::update(weapon *weapon);
