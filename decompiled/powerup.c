/* powerup.c - Powerups */
#include "powerup.h"

void powerup::playSound(uint param_1,char *soundName)

{
  char c1;
  char c2;
  char *in_name;
  GlobalAudioContext_ptr_816_float_6_ pfVar1;
  int iVar1;
  GlobalAudioContext *loaded_name;
  
  loaded_name = &Audio::LoadedNames;
  pfVar1 = (GlobalAudioContext_ptr_816_float_6_)Audio::LoadedNames.PlaybackHeadsSec;
  iVar1 = (int)&Audio::LoadedNames - (int)soundName;
  do {
    c1 = *soundName;
    c2 = loaded_name->LoadedNames[0][0];
    in_name = soundName;
                    // Search loaded names for sound name
    if (c1 == c2) {
      do {
        in_name = in_name + 1;
        if (c1 == '\0') goto LAB_000388bc;
        c1 = *in_name;
        c2 = in_name[iVar1];
      } while (c1 == c2);
    }
    if (c1 == c2) {
LAB_000388bc:
                    // If its loaded already
      if (ADJ(pfVar1)->IsPlayingFlags[0] == JustLoaded) {
        return;
      }
                    // If the audio status is 2
      if (ADJ(pfVar1)->IsPlayingFlags[0] == Playing) {
                    // If the powerup sound was playing less than a quarter of a second ago, dont
                    // play it again?
        if (ADJ(pfVar1)->PlaybackHeadsSec[0] <= 0.24 && ADJ(pfVar1)->PlaybackHeadsSec[0] != 0.24) {
          return;
        }
                    // Otherwise, its loaded and not playing. Play it
        Audio::PlayOneOff(soundName);
      }
    }
    loaded_name = (GlobalAudioContext *)(loaded_name->LoadedNames + 1);
    iVar1 = iVar1 + 0x80;
    pfVar1 = (GlobalAudioContext_ptr_816_float_6_)(ADJ(pfVar1)->PlaybackHeadsSec + 1);
                    // If we run out of slots, maybe queue it up??
    if (0x4e029f < (int)loaded_name) {
      Audio::loadAudioIntoEmptySlot(param_1,soundName);
      return;
    }
  } while( true );
}




void powerup::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x9e4;
  param_1->paramsSize = 0x3c4;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void powerup::getVTable(void)

{
  avatar::initVTable(&AvatarVTable_0050e108);
  AvatarVTable_0050e108.getAllocDetails = getAllocDetails;
  AvatarVTable_0050e108.ctor = ctor;
  AvatarVTable_0050e108.dtor = FUN_0010a120;
  AvatarVTable_0050e108.onMessage = onMessage;
  AvatarVTable_0050e108.update = update;
  AvatarVTable_0050e108.func6 = FUN_00109e30;
  AvatarVTable_0050e108.draw = draw;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 powerup::draw(powerup *param_1,undefined4 param_2,int param_3)

{
  float *pfVar1;
  powerup *rootActor;
  undefined4 uVar2;
  float10 fVar3;
  float local_14;
  float local_10;
  vec3 local_c;
  
  rootActor = param_1;
  if (param_1->field9_0x93c == 2) {
    uVar2 = 0;
  }
  else {
    uVar2 = avatar::draw(&param_1->avatar,param_2,param_3);
  }
  if ((param_1->textureDesc != (TextureDescriptor *)0x0) && (param_3 == 2)) {
    local_14 = param_1->texX * 5.0;
    pfVar1 = &param_1->texY;
    param_1 = (powerup *)CONCAT13((char)param_1->field87_0x9a8,0xffffff);
    local_10 = *pfVar1 * 5.0;
    ::actor::getTransformedBonePos((actor *)rootActor,&Game::someGlobalPos,0,&local_c);
    fVar3 = (float10)FUN_0003db90();
    local_c.y = (float)((float10)(rootActor->avatar).scale.y * (float10)2.5 +
                       fVar3 + (float10)local_c.y);
    FUN_0005c1a0(&local_c,&local_14,rootActor->textureDesc,param_1,0);
    uVar2 = 1;
  }
  return uVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 powerup::ctor(powerup *this,powerupParams *params)

{
  TextureDescriptor *pTVar1;
  AnimEventMapping *anim_mapping;
  powerupId id;
  
  if (params == (powerupParams *)0x0) {
    return 0;
  }
  id = params->powerupId;
  if ((((id != Book) ||
       ((*(byte *)((params->rightShift >> 3) + (int)PTR_00506c54->field2_0x8) &
        '\x01' << ((byte)params->rightShift & 7)) == 0)) && ((*SomeAS15->flags & 8) == 0)) &&
     ((g_globalFlagset & 0x200000) == 0)) {
    this->pwupType = id;
    this->field11_0x944 = *(undefined4 *)&params->field_0x338;
    this->field12_0x948 = *(undefined4 *)&params->field_0x33c;
    this->field13_0x94c = params->rightShift;
    this->field87_0x9a8 = 0xc0;
    if (id == RandomNasty) {
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      this->pwupType =
           bad_random_powerup_indices
           [-(int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * -3.0)];
    }
    if (*(int *)params->powerupTexture == 0x5f646961) {
      pTVar1 = Assets::GetResourceBytesOrExit(params->powerupTexture);
      this->textureDesc = pTVar1;
      this->texX = 1.0;
      this->texY = 1.0;
    }
    this->field9_0x93c = 1;
    if ((this->avatar).animTable != (AnimtableResource *)0x0) {
      anim_mapping = avatar::getAnimEventByName(&this->avatar,"wait",0);
      if (anim_mapping != (AnimEventMapping *)0x0) {
        avatar::activateAnimation(&this->avatar,anim_mapping);
      }
    }
    return 1;
  }
  return 0;
}




void powerup::onMessage(powerup *pwup,Avatar_AnimationEventMessage *msg)

{
  int iVar1;
  int *piVar2;
  vec3 pos;
  float fx;
  float fy;
  float fz;
  ObjMsgID gs;
  
  gs = msg->msgId;
  if (gs == Avatar_AnimationEvent) {
    switch(msg->animEvent->events[0].animEventType) {
    case PlayCue_Impact:
    case PlayCue_Vocal:
    case PlayCue_Vocal2:
    case PlayCue_FootStep:
    case PlayCue_VocalIfNotActive:
      fx = (Graphics::CurrentCameraStruct->pos).x;
      fy = (Graphics::CurrentCameraStruct->pos).y;
      fz = (Graphics::CurrentCameraStruct->pos).z;
      avatar::getWorldPosition(&pwup->avatar,&pos);
      fz = fz - pos.z;
      fy = fy - pos.y;
      fx = fx - pos.x;
                    // If the player is <= 10000 units from the powerup, play the sound
      if (fz * fz + fy * fy + fx * fx <= 10000.0) {
                    // Avatar = icon
        avatar::onMessage(&pwup->avatar,(Message *)msg);
      }
    }
    return;
  }
  if (gs != Avatar_SceneInsert) {
    if (gs != Weapon_BounceToDestination) {
      avatar::onMessage(&pwup->avatar,(Message *)msg);
      return;
    }
    FUN_00109d10(pwup,&msg->field1_0x4);
    return;
  }
  avatar::onMessage(&pwup->avatar,(Message *)msg);
  iVar1 = 0x511b2c;
  if (Game::SceneInfo.field19_0x90 != 0) {
    piVar2 = &Game::SceneInfo.field19_0x90;
    do {
      iVar1 = *piVar2;
      piVar2 = (int *)(iVar1 + 4);
    } while (*(int *)(iVar1 + 4) != 0);
  }
  *(undefined1 **)(iVar1 + 4) = &pwup->field_0x934;
  *(int *)&pwup->field_0x934 = iVar1;
  *(undefined4 *)&pwup->field_0x938 = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void powerup::update(powerup *pwup)

{
  actor_0x93c_conflict5 *ppNVar1;
  powerup *pwup_00;
  int iVar2;
  actor_0x93c_conflict5 pNVar3;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 fVar4;
  float fVar5;
  float fVar6;
  powerup *ppVar7;
  float fVar8;
  undefined1 local_20 [4];
  vec3 local_1c;
  undefined4 local_10;
  float local_c;
  
  pwup_00 = pwup;
  local_c = 1.527812e-39;
  avatar::update(&pwup->avatar);
  if (runtime::dx_timer <= 0.0) {
    fVar8 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar8 = 0.0;
  }
  fVar5 = 0.0;
  if ((pwup->avatar).movementFreezeTimer <= 0.0) {
    fVar5 = (pwup->avatar).actionSpeed;
  }
  fVar8 = fVar5 * fVar8 + pwup->xAccumulator;
  pwup->xAccumulator = fVar8;
  if (runtime::dx_timer <= 0.0) {
    fVar5 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar5 = 0.0;
  }
  fVar6 = 0.0;
  if ((pwup->avatar).movementFreezeTimer <= 0.0) {
    fVar6 = (pwup->avatar).actionSpeed;
  }
  fVar5 = fVar6 * fVar5 + pwup->yAccumulator;
  pwup->yAccumulator = fVar5;
  if (1.0 < fVar8) {
    fVar8 = pwup->xAccumulator;
    do {
      fVar8 = fVar8 - 1.0;
    } while (1.0 < fVar8);
    pwup->xAccumulator = fVar8;
  }
  if (1.5 < fVar5) {
    fVar8 = pwup->yAccumulator;
    do {
      fVar8 = fVar8 - 1.5;
    } while (1.5 < fVar8);
    pwup->yAccumulator = fVar8;
  }
                    // Multiplying by 2pi, probably calculating rotation of the can
  ppVar7 = (powerup *)(pwup->xAccumulator * 6.2831855);
  if ((float)ppVar7 <= 6.2831855) {
    pwup = (powerup *)0x0;
    if (0.0 <= (float)ppVar7) {
      pwup = ppVar7;
    }
  }
  else {
                    // 2pi
    pwup = (powerup *)0x40c90fdb;
  }
  local_c = 1.52825e-39;
  sin((float)pwup);
  ppVar7 = (powerup *)(pwup_00->yAccumulator * 0.6666667 * 6.2831855);
  pwup_00->texX =
       (float)((extraout_ST0 + (float10)1.0) * (float10)0.5 * (float10)0.20000005 + (float10)0.9);
  if ((float)ppVar7 <= 6.2831855) {
    pwup = (powerup *)0x0;
    if (0.0 <= (float)ppVar7) {
      pwup = ppVar7;
    }
  }
  else {
    pwup = (powerup *)0x40c90fdb;
  }
  local_c = 1.528396e-39;
  sin((float)pwup);
  iVar2 = pwup_00->field9_0x93c;
  pwup_00->texY =
       (float)((extraout_ST0_00 + (float10)1.0) * (float10)0.5 * (float10)0.20000005 + (float10)0.9)
  ;
  if (iVar2 == 0) {
    local_c = 1.528752e-39;
    FUN_001099c0((actor *)pwup_00);
    return;
  }
  if (iVar2 != 1) {
    if (iVar2 == 2) {
      if (runtime::dx_timer <= 0.0) {
        fVar8 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar8 = 0.0;
      }
      fVar5 = 0.0;
      if ((pwup_00->avatar).movementFreezeTimer <= 0.0) {
        fVar5 = (pwup_00->avatar).actionSpeed;
      }
      if ((0.0 < pwup_00->field88_0x9ac) &&
         (fVar8 = pwup_00->field88_0x9ac - fVar5 * fVar8, pwup_00->field88_0x9ac = fVar8,
         fVar8 <= 0.0)) {
        pwup_00->field88_0x9ac = 0.0;
      }
      fVar8 = pwup_00->field88_0x9ac * 192.0;
      if (fVar8 <= 192.0) {
        if (fVar8 < 0.0) {
          fVar8 = 0.0;
        }
      }
      else {
        fVar8 = 192.0;
      }
      pwup_00->field87_0x9a8 = (int)fVar8;
      local_c = 1.52871e-39;
      iVar2 = FUN_00041cb0();
      if ((iVar2 == 0) && ((int)fVar8 == 0)) {
        local_c = 1.528728e-39;
        avatar::destroy(&pwup_00->avatar);
      }
    }
    return;
  }
  avatar::getWorldPosition(&pwup_00->avatar,&local_1c);
  fVar4 = (float10)FUN_0003db90();
  local_c = (float)fVar4;
  fVar8 = 0.0;
  local_10 = 0;
  FUN_0003db30();
  pNVar3 = Game::SceneInfo.playerActors.prev;
  if (Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) {
    return;
  }
  do {
    if (*(int *)&ADJ(pNVar3)->field_0xce0 != 0) {
      if (ADJ(pNVar3)->actorType == Human) {
LAB_0010a623:
        iVar2 = 1;
      }
      else {
        if (pNVar3->prev == (actor_0x93c_conflict5)0x0) goto LAB_0010a682;
        if ((ADJ(pNVar3)->actorType == Human) || (pNVar3->prev != (actor_0x93c_conflict5)0x0))
        goto LAB_0010a623;
        iVar2 = 0;
      }
      if (((ShouldntDroneBools[iVar2] == 0) && ("\x01"[Game::CheckMoveOn] != '\0')) &&
         (ADJ(pNVar3)->body->health != 0)) {
        if ((pwup_00->pwupType != Book) && (-1 < (char)*PTR_00506c6c->field2_0x8)) {
          FUN_000414f0(ADJ(pNVar3));
          if (900.0 < fVar8) {
            return;
          }
          iVar2 = FUN_0013ff00();
          if (iVar2 == 0) {
            return;
          }
          *PTR_00506c6c->field2_0x8 = *PTR_00506c6c->field2_0x8 | 0x80;
          return;
        }
        iVar2 = FUN_0010a6d0(pwup_00,local_20,ADJ(pNVar3));
        if (iVar2 != 0) {
          return;
        }
      }
    }
LAB_0010a682:
    ppNVar1 = &pNVar3->next;
    pNVar3 = *ppNVar1;
    if (*ppNVar1 == (actor_0x93c_conflict5)0x0) {
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


