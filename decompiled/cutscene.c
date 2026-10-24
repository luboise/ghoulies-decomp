/* cutscene.c - Cutscenes, playcams, transitions, storybook */
#include "cutscene.h"

void UpdateCutscenes_(void)

{
  Scene *pSVar1;
  int *piVar2;
  int iVar3;
  
  if (g_cutsceneBuffer != (Cutscene *)0x0) {
    if (g_cutsceneBuffer->length <= g_cutsceneBuffer->t) {
      Cutscene::update(g_cutsceneBuffer,0.0,0.0,0);
    }
    RuncutsceneAndShouldEnd(runtime::DeltaTime,g_cutsceneBuffer,&Camera::ErrorDialogPage1Camera);
  }
  if ((((DAT_004de9a0 != (Scene *)0x0) && (0 < DAT_004dd900)) && (DAT_004dd900 < 4)) &&
     (DAT_004de99c != (InputHandlerType3 *)0x0)) {
    Input::UpdateMenuInput(DAT_004de99c,DAT_004de9a0);
  }
  piVar2 = DAT_004dea10;
  pSVar1 = DAT_004de9a0;
  if (DAT_004dd900 == 1) {
    if (DAT_004de9a0 != (Scene *)0x0) {
      iVar3 = FUN_0005ffa0(DAT_004dea10,DAT_004dea14);
      if (iVar3 == 0) {
        iVar3 = FUN_0005ffa0(piVar2,DAT_004dea18);
        if ((iVar3 == 0) && (pSVar1->inputContextStart != (SceneInputContext *)0x0)) {
          DAT_004dd900 = 2;
        }
      }
    }
  }
  else if (((DAT_004dd900 == 3) && (*(uint *)(*DAT_004dea10 + 8) <= *(uint *)(*DAT_004dea10 + 4)))
          && (DAT_004de9a0->inputContextStart == (SceneInputContext *)0x0)) {
    runtime::TriggerAppError();
    return;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::freeEvents(CutsceneEvents *events)

{
  SoundSourceImpl *pSVar1;
  short sVar2;
  IXACT_Cue *cue;
  int iVar3;
  
  iVar3 = 0;
  do {
    sVar2 = *(short *)(events->field6_0x6 + iVar3 * 2 + -6);
    if (sVar2 != -1) {
      cue = Audio::SoundSources[sVar2].cue;
      pSVar1 = Audio::SoundSources + sVar2;
      if (cue == (IXACT_Cue *)0x0) {
        pSVar1->state = Finished;
      }
      else {
        switch(pSVar1->state) {
        case ShouldGoTo4_1:
        case ShouldGoTo4_2:
          pSVar1->state = State4;
          break;
        case ShouldPause1:
        case ShouldPause2:
        case ShouldPause3:
          pSVar1->state = Paused;
          IXACT_Cue::stop(cue,0);
        }
      }
      (events->field6_0x6 + iVar3 * 2 + -6)[0] = -1;
      (events->field6_0x6 + iVar3 * 2 + -6)[1] = -1;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 3);
  return;
}




Cutscene * Cutscene::ctor(float length,uint flags,uint numAnims,CutsceneDescriptor *descriptor)

{
  byte bVar1;
  Cutscene *cutscene;
  
  cutscene = malloc_(numAnims * 0x30 + 0x190);
  (cutscene->v2).z = 0.0;
  (cutscene->v2).y = 0.0;
  (cutscene->v2).x = 0.0;
  (cutscene->eulerRot).z = 0.0;
  (cutscene->eulerRot).y = 0.0;
  (cutscene->eulerRot).x = 0.0;
  (cutscene->v4).z = 1.0;
  (cutscene->v4).y = 1.0;
  (cutscene->v4).x = 1.0;
  bVar1 = descriptor->numCameras;
  cutscene->length = length;
  cutscene->t = 0.0;
  cutscene->prevT = 0.0;
  cutscene->camIndex = bVar1 - 1;
  cutscene->cameraEvents = (CutsceneCameraEvent *)0x0;
  cutscene->onEndCallback = 0;
  cutscene->owningScene = (sceneControlObj *)0x0;
  cutscene->field18_0x158 = 0;
  cutscene->field19_0x15c = 0;
  cutscene->field20_0x160 = 0;
  cutscene->field21_0x164 = 0;
  cutscene->descriptor = descriptor;
  cutscene->numAnims = numAnims;
  cutscene->flags = flags;
  cutscene->val1 = -1.0;
  cutscene->val2 = -1.0;
  cutscene->animAllocsPtr = cutscene->animAllocs;
  (cutscene->rotEuler).z = 0.0;
  (cutscene->rotEuler).y = 0.0;
  (cutscene->rotEuler).x = 0.0;
  (cutscene->rotQuat).x = 0.0;
  (cutscene->rotQuat).y = 0.0;
  (cutscene->rotQuat).z = 0.0;
  (cutscene->rotQuat).w = 1.0;
  *(undefined4 *)&cutscene->events = 0xffffffff;
  *(undefined2 *)&(cutscene->events).field_0x4 = 0xffff;
  return cutscene;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::dtor(Cutscene *buf)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  uint i;
  
  freeCameraEvents(buf);
  i = 0;
  if (buf->numAnims != 0) {
    do {
      freeAnimations(buf);
      i = i + 1;
    } while (i < buf->numAnims);
  }
  buf->prevT = 0.0;
  buf->t = 0.0;
  buf->numAnims = 0;
  if (buf->descriptor != (CutsceneDescriptor *)0x0) {
    Assets::DestroyAssetOrDecrement(buf->descriptor);
    buf->descriptor = (CutsceneDescriptor *)0x0;
  }
  if (buf->cameraEvents != (CutsceneCameraEvent *)0x0) {
    Assets::DestroyAssetOrDecrement(buf->cameraEvents);
  }
  buf->cameraEvents = (CutsceneCameraEvent *)0x0;
  freeEvents(&buf->events);
  iVar2 = FindHeapOf(buf);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,buf);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


float Cutscene::updateCameraFromCutscene(Cutscene *cutscene,Camera *camera)

{
  AspectRatioType interpolationStatus;
  Camera *val2;
  float t;
  float lerp_v2;
  float local_2c;
  int iStack_28;
  int local_24;
  float fStack_20;
  vec3 pos;
  Quaternion q;
  Camera *cam;
  
  cam = camera;
  PosAndRotAtT(cutscene,&pos,&q,cutscene->t);
  if (0.0 < cutscene->val1) {
    t = cutscene->val2;
    if (t == 0.0) {
      camera = (Camera *)1.0;
    }
    else {
      val2 = (Camera *)((cutscene->val1 - t) / (0.0 - t));
      if ((float)val2 <= 1.0) {
        camera = (Camera *)0x0;
        if (0.0 <= (float)val2) {
          camera = val2;
        }
      }
      else {
        camera = (Camera *)1.0;
      }
    }
    pos.x = (pos.x - (cutscene->rotEuler).x) * (float)camera + (cutscene->rotEuler).x;
    pos.y = (pos.y - (cutscene->rotEuler).y) * (float)camera + (cutscene->rotEuler).y;
    pos.z = (pos.z - (cutscene->rotEuler).z) * (float)camera + (cutscene->rotEuler).z;
                    // Slerp between cutscene rotQuat and q, and then store the result in q
    Quaternion::SLERP(&cutscene->rotQuat,&q,&q,(float)camera);
  }
  (cam->pos).x = pos.x;
  (cam->pos).y = pos.y;
  (cam->pos).z = pos.z;
  (cam->rotQuat).x = q.x;
  (cam->rotQuat).y = q.y;
  (cam->rotQuat).z = q.z;
  (cam->rotQuat).w = q.w;
  camera = (Camera *)cutscene->t;
  t = FloatSet::interpolateAtT
                (&(cutscene->descriptor->cameras[cutscene->camIndex].descriptor)->zoomValues,
                 (float)camera,(float *)&camera,&lerp_v2);
  camera = (Camera *)((1.0 - t) * (float)camera + lerp_v2 * t);
  interpolationStatus =
       CameraDescriptor::interpolateVal9
                 (cutscene->descriptor->cameras[cutscene->camIndex].descriptor,cutscene->t);
  if ((cutscene->flags & 8) == 0) {
    cam->aspectRatioType = interpolationStatus;
    Camera::ComputeTangents
              (cam->fov,&iStack_28,&local_2c,&lerp_v2,&cam->aspectRatio,&cam->cotangentOffset,
               interpolationStatus,&local_24,&fStack_20);
  }
  else {
    if (interpolationStatus == Unknown3) {
      interpolationStatus = g_currentAspectRatioIndex;
    }
    if (cam->aspectRatioType == 3) {
      t = g_aspectRatioLookups[g_currentAspectRatioIndex].halfFovX;
    }
    else {
      t = g_aspectRatioLookups[cam->aspectRatioType].halfFovX;
    }
    camera = (Camera *)((t * (float)camera) / g_aspectRatioLookups[interpolationStatus].halfFovX);
  }
  cam->fov = (float)camera;
  t = Camera::ComputeTangents
                ((float)camera,&local_24,&fStack_20,(float *)&camera,&cam->aspectRatio,
                 &cam->cotangentOffset,cam->aspectRatioType,&iStack_28,&local_2c);
  return t;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0004dbd0(Cutscene *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  if (0 < (int)param_1->numAnims) {
    iVar3 = 0;
    do {
      piVar1 = (int *)((int)&param_1->animAllocsPtr->id_ + iVar3);
      if (((*(int *)(&param_1->animAllocsPtr->field_0x10 + iVar3) == 0) && (piVar1[5] != 0)) &&
         (piVar1 = (int *)*piVar1, piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 0x14))
                  (piVar1,(int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,1);
        (**(code **)(*piVar1 + 0x14))
                  (piVar1,(int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,2);
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x30;
    } while (iVar2 < (int)param_1->numAnims);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::loadAnimations(Cutscene *cutscene,CutsceneDescriptor *desc,BOOL flag1,BOOL flag2)

{
  undefined1 *puVar1;
  avatar_0x900 pEVar2;
  AnimResource *pAVar3;
  AnimInstance *pAVar4;
  entityAvatarMiscProp *av;
  KeyframeContext *kfc;
  uint i;
  int anim_ptr;
  Avatar_CutScene_BeginMessage msg;
  float local_b4;
  KFCParams anim_cfg;
  
  i = 0;
  if (0 < (int)cutscene->numAnims) {
    anim_ptr = 0;
    do {
      av = GetAnimMiscPropFromCutscene_(desc,flag1,i);
      if (av != (entityAvatarMiscProp *)0x0) {
        if (flag2 == 0) {
          *(undefined4 *)(&cutscene->animAllocsPtr->field_0x10 + anim_ptr) = 1;
        }
        else {
          pEVar2 = (av->avatar).node0x900.prev;
          if (pEVar2 != (avatar_0x900)0x0) {
            pEVar2->next = (av->avatar).node0x900.next;
          }
          pEVar2 = (av->avatar).node0x900.next;
          if (pEVar2 != (avatar_0x900)0x0) {
            pEVar2->prev = (av->avatar).node0x900.prev;
          }
          (av->avatar).node0x900.prev = (avatar_0x900)0x0;
          (av->avatar).node0x900.next = (avatar_0x900)0x0;
          *(undefined4 *)(&cutscene->animAllocsPtr->field_0x10 + anim_ptr) = 0;
        }
                    // Runs when creating pause menu
        *(undefined4 *)(&cutscene->animAllocsPtr->field_0x14 + anim_ptr) = 1;
        anim_cfg.someUshort = 1;
        msg.msgId = Avatar_CutScene_Begin;
        pAVar3 = *(AnimResource **)(desc->animRes->ANIM + (char)i * 100 + 8);
        anim_cfg.playbackSpeed_ = 0.0;
        anim_cfg.someFloat = 0.0;
        anim_cfg.MixP = 0x4d697850;
        anim_cfg.someIdOrCount = 0x21;
        anim_cfg.length = 0.2;
        anim_cfg.someFloat3 = -10.0;
        anim_cfg.someValue4 = 0x31;
        anim_cfg.someFloat2 = 0.2;
        anim_cfg.animEventAID[0] = '\0';
        anim_cfg.someValue5 = (void *)0x0;
        anim_cfg.animResource = (AnimResource *)0x0;
        anim_cfg.animEvent = (AnimEventResource *)0x0;
        if ((av->avatar).keyframeContext == (KeyframeContext *)0x0) {
          kfc = KeyframeContext::ctor(4);
          (av->avatar).keyframeContext = kfc;
          kfc->animEventCallback = avatar::triggerAnimationEvent;
          kfc->avatar = &av->avatar;
        }
        KeyframeContext::setFromAnimName
                  ((av->avatar).keyframeContext,0,&anim_cfg,(char *)0x0,pAVar3);
        FUN_00051430(desc,(vec3 *)&msg.animFloat,(char)i,0.0);
        if (((msg.animFloat != (av->avatar).scale.x) || ((float)msg._8_4_ != (av->avatar).scale.y))
           || (local_b4 != (av->avatar).scale.z)) {
          (av->avatar).scale.x = msg.animFloat;
          (av->avatar).scale.y = (float)msg._8_4_;
          (av->avatar).scale.z = local_b4;
          (av->avatar).anglesCalculated = 0;
        }
        avatar::onScenePrepare(av);
        kfc = (av->avatar).keyframeContext;
        if (kfc != (KeyframeContext *)0x0) {
          pAVar4 = kfc->kfcAnims->animInstance;
          if (pAVar4 != (AnimInstance *)0x0) {
            puVar1 = &pAVar4->restartAnimation;
            *puVar1 = *puVar1 + '\x01';
          }
          kfc->free = 1;
        }
                    // Calls func3 (entityAvatarMiscProp.getVTable()[3])
        (*((av->avatar).vtable)->onMessage)(av,&msg);
      }
      *(entityAvatarMiscProp **)((int)&cutscene->animAllocsPtr->id_ + anim_ptr) = av;
      *(undefined4 *)((int)&cutscene->animAllocsPtr->someInt + anim_ptr) = 0;
      *(undefined4 *)(&cutscene->animAllocsPtr->field_0x8 + anim_ptr) = 0;
      *(undefined4 *)(&cutscene->animAllocsPtr->field_0xc + anim_ptr) = 0;
      i = i + 1;
      anim_ptr = anim_ptr + 0x30;
    } while ((int)i < (int)cutscene->numAnims);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

entityAvatarMiscProp *

void Cutscene::loadEvents(Cutscene *cutscene,char *cutsceneName,int eventName)

{
  int iVar1;
  char cVar2;
  int iVar3;
  CutsceneCameraEvent *pCVar4;
  char *in_stack_ffffff80;
  char *in_stack_ffffff84;
  
  iVar3 = 4;
  cVar2 = cutsceneName[4];
  while (cVar2 != '_') {
    iVar1 = iVar3 + 1;
    iVar3 = iVar3 + 1;
    cVar2 = cutsceneName[iVar1];
  }
  Utils::SprintfToUpper
            (&stack0xffffff80,"aid_cutsceneevents%s_camera",cutsceneName + iVar3,(char *)eventName,
             in_stack_ffffff80,in_stack_ffffff84);
  pCVar4 = CutsceneEvents::Get(&cutscene->events,&stack0xffffff80);
  cutscene->cameraEvents = pCVar4;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::freeCameraEvents(Cutscene *csb)

{
  int cameraEvents;
  int i_ptr;
  int i;
  
  if (csb->cameraEvents != (CutsceneCameraEvent *)0x0) {
    UpdateCameraEvent_(csb,&csb->events,csb->cameraEvents,csb->t,csb->prevT,0);
  }
  i = 0;
  if (0 < (int)csb->numAnims) {
    i_ptr = 0;
    do {
      cameraEvents = *(int *)((int)&csb->animAllocsPtr->someInt + i_ptr);
      if (cameraEvents != 0) {
        UpdateCameraEvent_(csb,&csb->events,cameraEvents,csb->t,csb->prevT,
                           *(undefined4 *)((int)&csb->animAllocsPtr->id_ + i_ptr));
      }
      i = i + 1;
      i_ptr = i_ptr + 0x30;
    } while (i < (int)csb->numAnims);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::PosAndRotAtT(Cutscene *cutscene,vec3 *pos,Quaternion *q,float cutsceneProgress)

{
  float angle2;
  Quaternion quatRot;
  AnimationContext *animCtx;
  
  animCtx = (AnimationContext *)cutscene->descriptor->cameras[cutscene->camIndex].descriptor;
  if (pos != (vec3 *)0x0) {
    FUN_0004f770(cutsceneProgress,&pos->x,cutscene->flags >> 5 & 1,animCtx);
    pos->x = (cutscene->v4).x * pos->x;
    pos->y = (cutscene->v4).y * pos->y;
    angle2 = (cutscene->v4).z * pos->z;
    pos->z = angle2;
    FUN_00106770(pos->x,pos->y,angle2,&cutscene->eulerRot,pos);
    pos->x = (cutscene->v2).x + pos->x;
    pos->y = (cutscene->v2).y + pos->y;
    pos->z = (cutscene->v2).z + pos->z;
  }
  if (q != (Quaternion *)0x0) {
    GetQuaternionFromCurrentProgress(cutsceneProgress,cutscene->flags >> 5 & 1,animCtx,q);
    Quaternion::fromEuler
              (0,(cutscene->eulerRot).x,(cutscene->eulerRot).y,(cutscene->eulerRot).z,&quatRot);
    Quaternion::Multiply(&quatRot,q,q);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void Cutscene::updateAvatarsAndAnims
               (Cutscene *cutscene,float param_2,float progress1,float progress2)

{
  avatar *av;
  CutsceneCameraEvent *cameraEvents;
  CutsceneAnimAllocation *pCVar1;
  KeyframeContext *pKVar2;
  AnimInstance *pAVar3;
  uint *puVar4;
  Cutscene *csb;
  uint i;
  vec3 new_pos;
  vec3 v1;
  vec3 *v_ptr;
  vec3 *pfVar2;
  
  csb = cutscene;
  i = 0;
  if (0 < (int)cutscene->numAnims) {
    cutscene = (Cutscene *)0x0;
    do {
      av = *(avatar **)
            ((cutscene->events).field6_0x6 + (int)(&csb->animAllocsPtr[-2].field_0x18 + -6));
      puVar4 = &csb->animAllocsPtr->id_;
      if (av != (avatar *)0x0) {
        cameraEvents = *(CutsceneCameraEvent **)
                        ((cutscene->events).field6_0x6 + (int)(puVar4 + -0x11) + -6);
        if (*(int *)((cutscene->events).field6_0x6 + (int)(puVar4 + -0xf) + -6) == 0) {
          GetKeyframePosition(i,csb->t,&new_pos,(float)(csb->flags >> 6 & 1),csb->descriptor,
                              progress2);
          if (0.0 < csb->val1) {
            pfVar2 = (vec3 *)((int)&csb->animAllocsPtr->id_ + (int)&(cutscene->eulerRot).x);
            new_pos.x = (new_pos.x -
                        *(float *)((int)&csb->animAllocsPtr->id_ + (int)&(cutscene->eulerRot).x)) *
                        param_2 + pfVar2->x;
            new_pos.y = (new_pos.y - pfVar2->y) * param_2 + pfVar2->y;
            new_pos.z = (new_pos.z - pfVar2->z) * param_2 + pfVar2->z;
          }
          FUN_00106770(new_pos.x,new_pos.y,new_pos.z,&csb->eulerRot,&new_pos);
          new_pos.x = (csb->v2).x + new_pos.x;
          new_pos.y = (csb->v2).y + new_pos.y;
          new_pos.z = (csb->v2).z + new_pos.z;
          avatar::setPosition(av,&new_pos);
          Maths::NormaliseAngles2PI(&csb->eulerRot,&av->rotEuler);
          av->anglesCalculated = 0;
          FUN_00051430(csb->descriptor,&v1,(char)i,csb->t);
          progress2 = v1.z;
          if (0.0 < csb->val1) {
            pCVar1 = csb->animAllocsPtr;
            v_ptr = (vec3 *)((int)&cutscene->cameraEvents + (int)pCVar1);
            v1.x = (v1.x - *(float *)((int)&cutscene->cameraEvents + (int)pCVar1)) * param_2 +
                   v_ptr->x;
            v1.y = (v1.y - *(float *)((int)&cutscene->camIndex + (int)pCVar1)) * param_2 + v_ptr->y;
            progress2 = (v1.z - *(float *)((int)&cutscene->t + (int)pCVar1)) * param_2 + v_ptr->z;
          }
          v1.x = (csb->v4).x * v1.x;
          v1.y = (csb->v4).y * v1.y;
          v1.z = (csb->v4).z * progress2;
          if (((v1.x != (av->scale).x) || (v1.y != (av->scale).y)) || (v1.z != (av->scale).z)) {
            (av->scale).x = v1.x;
            (av->scale).y = v1.y;
            (av->scale).z = v1.z;
            av->anglesCalculated = 0;
          }
          pKVar2 = av->keyframeContext;
          if (pKVar2 != (KeyframeContext *)0x0) {
            pAVar3 = pKVar2->kfcAnims->animInstance;
            if (pAVar3 != (AnimInstance *)0x0) {
              pAVar3->t = progress1;
              pAVar3->defaultT = progress1;
              progress2 = progress1;
            }
            pKVar2->free = 1;
          }
        }
        if (cameraEvents != (CutsceneCameraEvent *)0x0) {
          FUN_0004d370((float)&csb->events,csb,&csb->events,av,csb->t,csb->prevT,0,0,cameraEvents);
        }
        if (*(int *)((int)&(cutscene->v4).y + (int)csb->animAllocsPtr) == 0) {
          (*av->vtable->update)(av);
          avatar::updateBaseTransform(av);
        }
      }
      i = i + 1;
      cutscene = (Cutscene *)&cutscene->prevT;
    } while ((int)i < (int)csb->numAnims);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::update(Cutscene *cutscene,float delta,float sampleRotation,int param_4)

{
  int iVar2;
  AnimInstance *this;
  int iVar3;
  float prevT;
  uint kfIndex;
  float tAgain;
  int i_ptr;
  CutsceneAnimAllocation *iVar1;
  
  if (0.0 < sampleRotation) {
    PosAndRotAtT(cutscene,&cutscene->rotEuler,&cutscene->rotQuat,cutscene->t);
  }
  kfIndex = 0;
  cutscene->val2 = sampleRotation;
  cutscene->val1 = sampleRotation;
  if (cutscene->numAnims != 0) {
    i_ptr = 0;
    do {
      iVar1 = *(CutsceneAnimAllocation **)((int)&cutscene->animAllocsPtr->id_ + i_ptr);
      if (iVar1 != (CutsceneAnimAllocation *)0x0) {
        iVar2 = *(int *)&iVar1[1].field_0x20;
        if (sampleRotation <= 0.0) {
          if (iVar2 != 0) {
            iVar3 = **(int **)(iVar2 + 0x58);
            if (iVar3 != 0) {
              *(float *)(iVar3 + 0x14) = delta;
              *(float *)(iVar3 + 0x10c) = delta;
            }
            *(undefined4 *)(iVar2 + 0x5c) = 1;
          }
        }
        else {
          this = (AnimInstance *)**(undefined4 **)(iVar2 + 0x58);
          GetKeyframePosition(kfIndex,cutscene->t,
                              (vec3 *)(&cutscene->animAllocsPtr->field_0x18 + i_ptr),0.0,
                              cutscene->descriptor,sampleRotation);
          FUN_00051430(cutscene->descriptor,(vec3 *)(&cutscene->animAllocsPtr->field_0x24 + i_ptr),
                       (char)kfIndex,cutscene->t);
          this->timeRemaining2 = sampleRotation;
          AnimInstance::loadAnimFromExistingResource
                    (this->animResource,this,delta,-1.0,'\x01',0,(char *)0x0);
        }
      }
      kfIndex = kfIndex + 1;
      i_ptr = i_ptr + 0x30;
    } while (kfIndex < cutscene->numAnims);
  }
  prevT = cutscene->t;
  tAgain = cutscene->length * delta;
  cutscene->t = tAgain;
  cutscene->prevT = prevT;
  *(undefined4 *)&cutscene->field_0x38 = 0;
  if ((param_4 != 0) && (cutscene->cameraEvents != (CutsceneCameraEvent *)0x0)) {
    FUN_0004d370((float)&cutscene->events,cutscene,&cutscene->events,0,tAgain,prevT,0,1,
                 cutscene->cameraEvents);
  }
  return;
}




void CloseDoorAndUpdateState(int param_1,Cutscene *csb)

{
  int iVar1;
  uchar index;
  
  if (param_1 == 0) {
    iVar1 = csb->field18_0x158 + -1;
  }
  else {
    iVar1 = csb->field18_0x158 + 1;
  }
  csb->field18_0x158 = iVar1;
  index = '\0';
  if (0 < (int)csb->numAnims) {
    do {
      Cutscene::doSomething(csb,param_1,index);
      index = index + '\x01';
    } while ((int)(char)index < (int)csb->numAnims);
  }
  if ((csb->flags & 0x10) == 0) {
    iVar1 = 0;
    do {
      if (*(short *)((csb->events).field6_0x6 + iVar1 * 2 + -6) != -1) {
        FUN_00039aa0();
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 3);
  }
  if ((((code *)csb->field20_0x160 != (code *)0x0) && (param_1 == 0)) && (csb->field18_0x158 == 0))
  {
    (*(code *)csb->field20_0x160)(csb,csb->field21_0x164,0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::doSomething(Cutscene *csb,int param_2,uchar index)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = csb->animAllocsPtr[(char)index].id_;
  if (uVar2 != 0) {
    iVar4 = *(int *)&csb->animAllocsPtr[(char)index].field_0xc;
    if (param_2 == 0) {
      if ((iVar4 != 0) && (iVar4 = *(int *)(uVar2 + 0x50), iVar4 != 0)) {
        iVar3 = *(int *)(*(int *)(iVar4 + 0x58) + 0x28);
        if (iVar3 != 0) {
          pcVar1 = (char *)(iVar3 + 0x125);
          *pcVar1 = *pcVar1 + -1;
        }
        *(undefined4 *)(iVar4 + 0x5c) = 1;
      }
      iVar4 = *(int *)(uVar2 + 0x50);
      if (iVar4 == 0) {
        return;
      }
      if (**(int **)(iVar4 + 0x58) != 0) {
        pcVar1 = (char *)(**(int **)(iVar4 + 0x58) + 0x125);
        *pcVar1 = *pcVar1 + -1;
      }
    }
    else {
      if ((iVar4 != 0) && (iVar4 = *(int *)(uVar2 + 0x50), iVar4 != 0)) {
        iVar3 = *(int *)(*(int *)(iVar4 + 0x58) + 0x28);
        if (iVar3 != 0) {
          pcVar1 = (char *)(iVar3 + 0x125);
          *pcVar1 = *pcVar1 + '\x01';
        }
        *(undefined4 *)(iVar4 + 0x5c) = 1;
      }
      iVar4 = *(int *)(uVar2 + 0x50);
      if (iVar4 == 0) {
        return;
      }
      if (**(int **)(iVar4 + 0x58) != 0) {
        pcVar1 = (char *)(**(int **)(iVar4 + 0x58) + 0x125);
        *pcVar1 = *pcVar1 + '\x01';
        *(undefined4 *)(iVar4 + 0x5c) = 1;
        return;
      }
    }
    *(undefined4 *)(iVar4 + 0x5c) = 1;
  }
  return;
}




void Cutscene::freeAnimations(Cutscene *param_1)

{
  void *pvVar1;
  char in_AL;
  CutsceneAnimAllocation *extraout_EAX;
  CutsceneAnimAllocation *pOVar2;
  
  pOVar2 = (CutsceneAnimAllocation *)param_1->animAllocsPtr[in_AL].id_;
  if ((avatar *)pOVar2 != (avatar *)0x0) {
    if ((((avatar *)pOVar2)->node0x918).prev == (avatar_0x918)0x0) {
      if (*(int *)&param_1->animAllocsPtr[in_AL].field_0x10 != 0) {
        FUN_0003ee70((int)pOVar2);
        pOVar2 = extraout_EAX;
      }
      Assets::DeleteResource_(pOVar2);
    }
    else {
      avatar::destroy((avatar *)pOVar2);
    }
    param_1->animAllocsPtr[in_AL].id_ = 0;
  }
  pvVar1 = (void *)param_1->animAllocsPtr[in_AL].someInt;
  if (pvVar1 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(pvVar1);
    param_1->animAllocsPtr[in_AL].someInt = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint Cutscene::getEventIdFromModelName(Cutscene *csb,char *modelName)

{
  char *pcVar4;
  BOOL matches;
  int i;
  char someModelName [128];
  char cVar1;
  int iVar3;
  uint numModels;
  AnimResource *something;
  
  numModels = csb->numAnims;
  i = 0;
  if (0 < (int)numModels) {
    something = csb->descriptor->animRes;
    do {
      pcVar4 = *(char **)(something->ANIM + (char)i * 100);
      iVar3 = *(int *)(something->ANIM + (char)i * 100);
      do {
        cVar1 = *pcVar4;
        pcVar4[(int)(someModelName + -iVar3)] = cVar1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      matches = Assets::AssetNamesMatch(someModelName,modelName);
      if (matches != 0) {
        return csb->animAllocsPtr[i].id_;
      }
      i = i + 1;
    } while (i < (int)numModels);
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void UpdateCutsceneProgress(void)

{
  float delta;
  
  delta = 0.0;
  if (runtime::dx_timer <= 0.0) {
    delta = runtime::DeltaTime * runtime::TimeScale;
  }
  if ((uint)Cutscene::CurrentCutsceneIndex < 0x80000000) {
    if (Cutscene::LoadedCutscenes[4] != (Cutscene *)0x0) {
      Cutscene::SetCutsceneCam();
      Cutscene::LoadedCutscenes[4] = (Cutscene *)0x0;
      return;
    }
    if (g_someAssetName._0_4_ == 0x5f646961) {
      _DAT_004e1c28 =
           Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex]->length + _DAT_004e1c28;
      DAT_004e1c2c = _DAT_004e1c28;
      EventLoop::PopImportantStack();
      Assets::LoadCutsceneSimple(g_someAssetName,DAT_004e1bc0);
      g_someAssetName._0_4_ = g_someAssetName._0_4_ & 0xffffff00;
    }
    _DAT_004e1c30 = DAT_004e1c2c;
    DAT_004e1c2c = DAT_004e1c2c + delta;
    RuncutsceneAndShouldEnd
              (delta,Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex],
               &Cutscene::CutsceneCam);
    FUN_0004f110(delta);
  }
  else if (Cutscene::LoadedCutscenes[6] != (Cutscene *)0x0) {
    Assets::DestroyAssetOrDecrement(Cutscene::LoadedCutscenes[6]);
    Cutscene::LoadedCutscenes[6] = (Cutscene *)0x0;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::SetCutsceneCam(void)

{
  if (-1 < CurrentCutsceneIndex) {
                    // End cutscene?
    if (runtime::InCutscene != 0) {
      Camera::setActiveCamera(&CutsceneCam);
      runtime::InCutscene = 0;
    }
    if (-1 < CurrentCutsceneIndex) {
      do {
        drop(LoadedCutscenes[CurrentCutsceneIndex]);
        LoadedCutscenes[CurrentCutsceneIndex] = (Cutscene *)0x0;
        CurrentCutsceneIndex = CurrentCutsceneIndex - 1;
        g_stateStack = g_stateStack + -1;
        if (g_stateStack < 0) {
          g_stateStack = 0;
        }
      } while ((uint)CurrentCutsceneIndex < 0x80000000);
    }
    if (LoadedCutscenes[6] != (Cutscene *)0x0) {
      Assets::DestroyAssetOrDecrement(LoadedCutscenes[6]);
      LoadedCutscenes[6] = (Cutscene *)0x0;
    }
    if (LoadedCutscenes[7] != (Cutscene *)0x0) {
      Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
      GlobalCounter2 = GlobalCounter2 + -1;
      LoadedCutscenes[7] = (Cutscene *)0x0;
    }
                    // Unmark as in cutscene???
    g_globalFlagset = g_globalFlagset & ~InCutscene?;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Disabling this entire function breaks event flow?


Cutscene * Cutscene::LoadFromLevel(char *ctscAID,BOOL someFlag,BOOL someOtherFlag)

{
  if (LoadedCutscenes[7] == (Cutscene *)0x0) {
    Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
    GlobalCounter2 = GlobalCounter2 + 1;
    LoadedCutscenes[7] = (Cutscene *)0x1;
  }
  g_globalFlagset = g_globalFlagset | InCutscene?;
                    // Mark global as "In cutscene"
  EventLoop::PopImportantStack();
  if (runtime::InCutscene == 0) {
    Camera::ctor(&CutsceneCam,"cutscene",(ProjectionSetBitField)((someFlag == 0) - 1U & 8));
  }
  Assets::LoadCutsceneSimple(ctscAID,someOtherFlag);
  _DAT_004e1c28 = 0;
  DAT_004e1c2c = 0;
  if (runtime::InCutscene == 0) {
    Camera::AppendAndSelect(&CutsceneCam,0);
    Camera::SetActiveCameraConfig(0,"cutscene");
    runtime::InCutscene = 1;
    updateCameraFromCutscene(LoadedCutscenes[CurrentCutsceneIndex],&CutsceneCam);
    return LoadedCutscenes[CurrentCutsceneIndex];
  }
  return LoadedCutscenes[CurrentCutsceneIndex];
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_0004eea0(Cutscene *param_1)

{
  int iVar1;
  
  if (Cutscene::CurrentCutsceneIndex < 1) {
    Cutscene::LoadedCutscenes[4] = param_1;
    return;
  }
  iVar1 = 0;
  if (0 < Cutscene::CurrentCutsceneIndex + 1) {
    do {
      if (param_1 == Cutscene::LoadedCutscenes[iVar1]) {
        Cutscene::drop(Cutscene::LoadedCutscenes[iVar1]);
        iVar1 = iVar1 + 1;
        if (iVar1 < Cutscene::CurrentCutsceneIndex + 1) {
          do {
            (&Cutscene::CurrentCutsceneIndex)[iVar1] = (int)Cutscene::LoadedCutscenes[iVar1];
            iVar1 = iVar1 + 1;
          } while (iVar1 < Cutscene::CurrentCutsceneIndex + 1);
        }
        Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex] = (Cutscene *)0x0;
        Cutscene::CurrentCutsceneIndex = Cutscene::CurrentCutsceneIndex + -1;
        return;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < Cutscene::CurrentCutsceneIndex + 1);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::RerenderFromEulerAngles(vec3 *eulers)

{
  Cutscene *cutscene;
  float cutscene_progress;
  
  cutscene = LoadedCutscenes[CurrentCutsceneIndex];
  (cutscene->eulerRot).x = eulers->x;
  (cutscene->eulerRot).y = eulers->y;
  (cutscene->eulerRot).z = eulers->z;
  cutscene_progress = cutscene->t / cutscene->length;
  updateAvatarsAndAnims(cutscene,-1.0,cutscene_progress,cutscene_progress);
  updateCameraFromCutscene(LoadedCutscenes[CurrentCutsceneIndex],&CutsceneCam);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL Cutscene::InACutscene(void)

{
  if ((-1 < CurrentCutsceneIndex) &&
     (LoadedCutscenes[CurrentCutsceneIndex]->length <= LoadedCutscenes[CurrentCutsceneIndex]->t)) {
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Cutscene::drop(Cutscene *cutscene)

{
  sceneControlObj **ppsVar1;
  sceneControlObj **ppsVar2;
  Message local_8;
  sceneControlObj_0x8 scene_controls;
  
  local_8.header.msgId = Scene_CutsceneFree;
  local_8.header.someActor = (actor *)cutscene;
  EventLoop::DispatchMessage((ObjMsgID *)&local_8);
  scene_controls = Game::SceneControls.next;
                    // Run all scene controls then begin the cutscene
  while (scene_controls != (sceneControlObj_0x8)0x0) {
    ppsVar1 = (sceneControlObj **)(scene_controls + -8);
    ppsVar2 = (sceneControlObj **)(scene_controls + -8);
    scene_controls = *(sceneControlObj_0x8 *)(scene_controls + 4);
    (*(code *)((*ppsVar1)->obj_0x8).next)(ppsVar2,&local_8);
  }
  dtor(cutscene);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Assets::CutsceneResource::processDescriptor(CutsceneDescriptor *desc,uint resourceBase)

{
  float *pfVar1;
  int iVar2;
  char *pcVar3;
  CameraDescriptor *cam_desc;
  int i;
  CutsceneCameraHeader *cam_headers;
  
                    // Update cam headers ptr
  if (desc->cameras != (CutsceneCameraHeader *)0x0) {
    desc->cameras = (CutsceneCameraHeader *)((int)&desc->cameras->camName + resourceBase);
  }
  i = 0;
  if (desc->numCameras != '\0') {
    do {
      cam_headers = desc->cameras;
                    // Update camera config pointer
      cam_desc = (CameraDescriptor *)
                 ((int)&((cam_headers[i].descriptor)->posXValues).numFloats + resourceBase);
      cam_headers[i].descriptor = cam_desc;
      cam_headers[i].camName = cam_headers[i].camName + resourceBase;
      (cam_desc->posYValues).floats = (float *)((int)(cam_desc->posYValues).floats + (int)cam_desc);
      (cam_desc->posXValues).floats = (float *)((int)(cam_desc->posXValues).floats + (int)cam_desc);
      (cam_desc->rotXValues).floats = (float *)((int)(cam_desc->rotXValues).floats + (int)cam_desc);
      (cam_desc->posZValues).floats = (float *)((int)(cam_desc->posZValues).floats + (int)cam_desc);
      (cam_desc->rotZValues).floats = (float *)((int)(cam_desc->rotZValues).floats + (int)cam_desc);
      (cam_desc->rotYValues).floats = (float *)((int)(cam_desc->rotYValues).floats + (int)cam_desc);
      (cam_desc->zoomValues).floats = (float *)((int)(cam_desc->zoomValues).floats + (int)cam_desc);
      pfVar1 = (cam_desc->aspectRatioValues).floats;
      (cam_desc->rotWValues).floats = (float *)((int)(cam_desc->rotWValues).floats + (int)cam_desc);
      if (pfVar1 != (float *)0x0) {
        (cam_desc->aspectRatioValues).floats = (float *)((int)pfVar1 + (int)cam_desc);
      }
      i = i + 1;
    } while (i < (int)(uint)desc->numCameras);
  }
  if (desc->animRes != (AnimResource *)0x0) {
    desc->animRes = (AnimResource *)(desc->animRes->ANIM + resourceBase);
  }
  i = 0;
  if (desc->numAnimResources != '\0') {
    do {
      iVar2 = (char)i * 100;
      pcVar3 = desc->animRes->ANIM + iVar2;
      *(uint *)pcVar3 = *(int *)(desc->animRes->ANIM + iVar2) + resourceBase;
      if (*(int *)(pcVar3 + 0x18) != 0) {
        *(uint *)(pcVar3 + 0x18) = *(int *)(pcVar3 + 0x18) + resourceBase;
      }
      *(uint *)(pcVar3 + 4) = (int)*(float *)(pcVar3 + 4) + resourceBase;
      *(uint *)(pcVar3 + 8) = (int)*(float *)(pcVar3 + 8) + resourceBase;
      *(uint32_t *)(pcVar3 + 0x24) = *(uint32_t *)(pcVar3 + 0x24) + resourceBase;
      *(uint32_t *)(pcVar3 + 0x30) = *(uint32_t *)(pcVar3 + 0x30) + resourceBase;
      *(uint32_t *)(pcVar3 + 0x3c) = *(uint32_t *)(pcVar3 + 0x3c) + resourceBase;
      *(uint *)(pcVar3 + 0x48) = (int)*(float *)(pcVar3 + 0x48) + resourceBase;
      *(uint *)(pcVar3 + 0x54) = *(int *)(pcVar3 + 0x54) + resourceBase;
      *(uint *)(pcVar3 + 0x60) = *(int *)(pcVar3 + 0x60) + resourceBase;
      AnimResource::processMetadata
                (*(AnimResource **)(pcVar3 + 8),(uint)*(AnimResource **)(pcVar3 + 8),
                 (DataViewList *)0x0);
      i = i + 1;
    } while (i < (int)(uint)desc->numAnimResources);
  }
  return;
}




void Assets::CutsceneResource::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_000512a7;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_000512a7:
  pRVar2->typeStr = "cutscene";
  pRVar2->processDescriptor = processDescriptor;
  pRVar2->ctor = (AfterLoadFn *)0x0;
  pRVar2->dtor = switchD_000d4179::EmptyFunction;
  return;
}



void GetKeyframePosition(uint kfIndex,float t,vec3 *outPos,float interpolationStrength,
                        CutsceneDescriptor *cutsceneDescriptor,float param_6)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  float fVar5;
  uint64_t uVar6;
  vec3 *pfVar1;
  AnimDescriptor *anim_desc;
  vec3 *pos_ptr;
  
  pos_ptr = outPos;
  anim_desc = (AnimDescriptor *)cutsceneDescriptor->animRes;
  cVar1 = (char)kfIndex;
  if (interpolationStrength != 0.0) {
    fVar5 = FloatSet::interpolateAtT
                      ((FloatSet *)((int)anim_desc + (char)kfIndex * 100 + 0x1c),t,(float *)&kfIndex
                       ,&interpolationStrength);
    pos_ptr->x = (1.0 - fVar5) * (float)kfIndex + interpolationStrength * fVar5;
    fVar5 = FloatSet::interpolateAtT
                      ((FloatSet *)((int)anim_desc + cVar1 * 100 + 0x28),t,(float *)&kfIndex,
                       &interpolationStrength);
    pos_ptr->y = (1.0 - fVar5) * (float)kfIndex + interpolationStrength * fVar5;
    fVar5 = FloatSet::interpolateAtT
                      ((FloatSet *)((int)anim_desc + cVar1 * 100 + 0x34),t,(float *)&kfIndex,
                       &interpolationStrength);
    pos_ptr->z = (1.0 - fVar5) * (float)kfIndex + interpolationStrength * fVar5;
    return;
  }
  uVar3 = (uint)*(ushort *)((int)anim_desc + (char)kfIndex * 100 + 0x1c);
  iVar4 = (int)(char)kfIndex;
  kfIndex = uVar3;
  uVar6 = float10::to_uint64_t
                    (((float10)t / (float10)*(float *)((int)anim_desc + iVar4 * 100 + 0x20)) *
                     (float10)uVar3);
  uVar2 = (uint)uVar6;
  if (uVar3 <= uVar2) {
    uVar2 = uVar3 - 1;
  }
  pos_ptr->x = *(float *)(*(int *)((int)anim_desc + cVar1 * 100 + 0x24) + uVar2 * 4);
  uVar3 = (uint)*(ushort *)((int)anim_desc + cVar1 * 100 + 0x28);
  kfIndex = uVar3;
  uVar6 = float10::to_uint64_t
                    (((float10)t / (float10)*(float *)((int)anim_desc + cVar1 * 100 + 0x2c)) *
                     (float10)uVar3);
  uVar2 = (uint)uVar6;
  if (uVar3 <= uVar2) {
    uVar2 = uVar3 - 1;
  }
  pos_ptr->y = *(float *)(*(int *)((int)anim_desc + cVar1 * 100 + 0x30) + uVar2 * 4);
  uVar3 = (uint)*(ushort *)((int)anim_desc + cVar1 * 100 + 0x34);
  kfIndex = uVar3;
  uVar6 = float10::to_uint64_t
                    (((float10)t / (float10)*(float *)((int)anim_desc + cVar1 * 100 + 0x38)) *
                     (float10)uVar3);
  uVar2 = (uint)uVar6;
  if (uVar3 <= uVar2) {
    uVar2 = uVar3 - 1;
  }
  pos_ptr->z = *(float *)(*(int *)((int)anim_desc + cVar1 * 100 + 0x3c) + uVar2 * 4);
  return;
}




void CreateTrophyAttacksCutscene(void *this,undefined4 param_2,int headIndex)

{
  char *unaff_EBX;
  char *unaff_ESI;
  char *unaff_EDI;
  int iVar1;
  char *pcVar2;
  char *args;
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  char local_2d8 [128];
  char local_258 [128];
  objParams local_1d8 [41];
  int local_90;
  
  iVar1 = headIndex * 0x18;
  args = *(char **)("aid_model_ghoulies_cutscene_reliccandle" + iVar1 + 0x70);
  pcVar2 = "aid_cutscene_ghoulies_chapter1_trophyroom_%sattack1";
  Utils::SprintfToUpper
            (local_258,"aid_cutscene_ghoulies_chapter1_trophyroom_%sattack1",args,unaff_EDI,
             unaff_ESI,unaff_EBX);
  Utils::SprintfToUpper
            (local_2d8,"aid_cutscene_ghoulies_chapter1_trophyroom_%sattack2",
             *(char **)("aid_model_ghoulies_cutscene_reliccandle" + iVar1 + 0x70),pcVar2,args,
             unaff_EDI);
  local_2e0 = *(undefined4 *)("aid_model_ghoulies_cutscene_reliccandle" + iVar1 + 0x74);
  local_2e4 = 0;
  local_2dc = 0;
  FUN_000873a0((avatar *)local_1d8,local_258,param_2,0x3f0ccccd,0x3f0ccccd,(undefined4 *)0x0,
               (undefined4 *)0x0,1,&local_2e4,1,0,0,local_2d8);
  if ((int)this < 3) {
    local_90 = (int)this + 1;
  }
  else {
    local_90 = 4;
  }
  Assets::CreateEntityFromParams(local_1d8);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void CutsceneResource::alloc(void)

{
  malloc_(0x250);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void UpdateStorybookPosition_(void)

{
  float *pfVar1;
  float local_8;
  float local_4;
  
  switch(Game::g_pauseState) {
  case Playing:
  case EnteringPause:
  case Paused:
  case ExitingPause:
  case MapScreen:
  case 8:
  case 9:
    if (DAT_00510e30 != 0) {
      DrawXboxButtons_(1);
    }
  }
  if (DAT_00510e40 == 0) goto switchD_0011db9e_caseD_4;
  switch(Game::g_pauseState) {
  case EnteringPause:
    if (DAT_00510e24 == 0) {
LAB_0011dc3c:
      local_8 = 1.0;
    }
    else {
      local_8 = (*(float *)(*(int *)(DAT_00510e24 + 0x24) + 0x2c) /
                *(float *)(*(int *)(DAT_00510e24 + 0x24) + 0x34)) * 8.130081 * 0.75;
      if (local_8 <= 0.75) {
        if (local_8 < 0.0) {
          local_8 = 0.0;
        }
      }
      else {
        local_8 = 0.75;
      }
    }
    break;
  case Paused:
  case MapScreen:
  case 9:
    pfVar1 = (float *)&DAT_00510e4c;
    goto LAB_0011dc72;
  default:
    goto switchD_0011db9e_caseD_4;
  case ExitingPause:
    if (DAT_00510e24 == 0) goto LAB_0011dc3c;
    local_8 = 0.75 - (*(float *)(*(int *)(DAT_00510e24 + 0x24) + 0x2c) /
                      *(float *)(*(int *)(DAT_00510e24 + 0x24) + 0x34) - 0.815) * 5.4054055 * 0.75;
    if (0.0 <= local_8) {
      if (0.75 < local_8) {
        local_8 = 0.75;
      }
    }
    else {
      local_8 = 0.0;
    }
  }
  pfVar1 = &local_8;
  local_4 = local_8;
LAB_0011dc72:
  DrawMalloced100Value(DAT_00510e40,&DAT_00510e44,pfVar1,0,(TextDrawData *)-1,0xffffffff);
switchD_0011db9e_caseD_4:
  if (DAT_00510e24 != 0) {
    Graphics::CopyRectsAndDraw(DAT_00510e24);
  }
  if ((Game::g_pauseState == 8) && (DAT_00510e30 != 0)) {
    FUN_000f6f70();
    DrawXboxButtons_(1);
  }
  return;
}




void runtime::UpdateNewEntities(GameState *param_1)

{
  sceneControlObj::processNew();
                    // Add new avatars and scene controls to global lists
  avatar::processNew();
                    // Tell the new ones that the scene has begun
  sceneControlObj::BeginScene();
  avatar::BeginScene();
                    // Update them once (this would be at the end of the event loop)
  sceneControlObj::UpdateNewSceneControls();
  avatar::UpdateNewAvatars();
                    // If normal or state 2
                    // 
                    // If we're in a normal state, update fx and timers
  if ((0 < (int)param_1->load_state) && ((int)param_1->load_state < 3)) {
    UpdatePowerups();
    UpdateFX();
    UpdateGlobalTimers();
  }
  UpdateAvatarAudio();
  sceneControlObj::destroyStaleControls();
  avatar::destroyStaleAvatars();
  NumDeadEnemies = 0;
  avatar::updateShadows();
  return;
}



// WARNING: Inlined function: SetCurrentPlaycamScript
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void LoadCutsceneSkip(void)

{
  g_successfullyLoadedCutsceneSkip = 0;
  g_someScriptType2 = (InputHandlerType4 *)0x0;
  if ((Game::CheckMoveOn == 3) && ((g_globalFlagset & CutsceneSkipRelated) == 0)) {
    Scripting::CreateScriptType2(&g_someScriptType2);
    runtime::PushInputHandlerAndSetActive(&g_someScriptType2->header,"cutscene skip");
    g_successfullyLoadedCutsceneSkip = 1;
  }
  return;
}




int RegularLoadInTransition(GiantLoctextStruct *gls)

{
  GamePauseContext *pGVar1;
  Scene *scene;
  uint uVar2;
  float t;
  Cutscene *iVar2;
  PauseCutsceneStruct *pcs;
  Cutscene *cutscene;
  int read;
  
  read = gls->discReadEnum;
                    // If still reading?
  if (read == 1) {
    FUN_000483e0(gls->gamePauseCtx);
    if (gls->gamePauseCtx->field7_0x10 != 0) {
      if (gls[1].transitionIndex != 0) {
        if (*(int *)&gls[2].field_0xfd0 == 0) {
          OnDeath_();
        }
        FUN_00109470(*(InputHandlerType4 **)&gls[2].field_0xfd8);
        read = Input::UpdateMenuInput
                         (*(InputHandlerType3 **)&gls[2].field_0xfd8,*(Scene **)&gls[2].field_0xfd4)
        ;
        if (read == 0) goto LAB_0012b557;
        if ((gls[1].transitionIndex != 0) && (*(int *)&gls[2].field_0xfd0 != 0)) {
          if (*(int *)&gls[2].field_0xfd8 != 0) {
            Scripting::PopInputHandler();
            FUN_00108230();
            *(undefined4 *)&gls[2].field_0xfd8 = 0;
          }
          scene = *(Scene **)&gls[2].field_0xfd4;
          if (scene != (Scene *)0x0) {
            scene->field2160_0x950 = 0;
            FUN_00142c20(3,scene);
          }
          FUN_0005f970(gls[1].discReadEnum);
          gls[1].transitionIndex = 0;
        }
      }
      FUN_0012c830((int *)gls,2);
    }
    goto LAB_0012b557;
  }
  if (read == 2) {
    if (*(Scene **)&gls[2].field_0xfd4 != (Scene *)0x0) {
      Input::UpdateMenuInput((InputHandlerType3 *)0x0,*(Scene **)&gls[2].field_0xfd4);
      return gls->discReadEnum;
    }
    goto LAB_0012b557;
  }
  if (read != 3) goto LAB_0012b557;
  if (*(Scene **)&gls[2].field_0xfd4 != (Scene *)0x0) {
    Input::UpdateMenuInput((InputHandlerType3 *)0x0,*(Scene **)&gls[2].field_0xfd4);
  }
  cutscene = gls->gamePauseCtx->cutsceneBuffer;
  t = cutscene->t / cutscene->length;
  if ((Cutscene::PauseCutsceneLookupTable[gls->gamePauseCtx->id].tToSwapBuffers <= t &&
       t != Cutscene::PauseCutsceneLookupTable[gls->gamePauseCtx->id].tToSwapBuffers) &&
     (*(int *)&gls[2].field_0xfdc == 0)) {
    DoneReadingLoad = DoneReadingLoad + -1;
    *(undefined4 *)&gls[2].field_0xfdc = 1;
  }
  pGVar1 = gls->gamePauseCtx;
  uVar2 = pGVar1->id;
  iVar2 = pGVar1->cutsceneBuffer;
  t = iVar2->t / iVar2->length;
  if (t < Cutscene::PauseCutsceneLookupTable[uVar2].tToDoLoad ||
      t == Cutscene::PauseCutsceneLookupTable[uVar2].tToDoLoad) {
    uVar2 = Cutscene::PauseCutsceneLookupTable[uVar2].field5_0x10c;
LAB_0012b424:
    if (uVar2 != 0xffffffff) {
      *(float *)((int)(&pGVar1->cameraCfg + 1) + (uVar2 * 4 + 3) * 4) = 1.4013e-45;
    }
  }
  else {
    t = iVar2->t / iVar2->length;
    if (Cutscene::PauseCutsceneLookupTable[uVar2].tToSwapBuffers <= t &&
        t != Cutscene::PauseCutsceneLookupTable[uVar2].tToSwapBuffers) {
      uVar2 = Cutscene::PauseCutsceneLookupTable[uVar2].field6_0x110;
      goto LAB_0012b424;
    }
  }
  FUN_000483e0(gls->gamePauseCtx);
  if (gls->gamePauseCtx->field7_0x10 != 0) {
    FUN_0012c830((int *)gls,0);
    return gls->discReadEnum;
  }
LAB_0012b557:
  return gls->discReadEnum;
}




void FUN_0012b5a0(TransitionData *param_1)

{
  ScriptType4 *script;
  
  if (*(Scene **)&param_1[0x2d].field_0x74 != (Scene *)0x0) {
    Scene::free(*(Scene **)&param_1[0x2d].field_0x74);
    *(undefined4 *)&param_1[0x2d].field_0x74 = 0;
  }
  script = *(ScriptType4 **)&param_1[0x2d].field_0x78;
  if (script != (ScriptType4 *)0x0) {
    switch((script->header).type) {
    case TYPE_1:
      Scripting::FreeScript123(&script->header);
      break;
    case TYPE_2:
      Scripting::FreeScript123(&script->header);
      break;
    case TYPE_3:
      Scripting::FreeScript123(&script->header);
      break;
    case TYPE_4_NESTED:
      Scripting::FreeScript4(script);
      break;
    case TYPE_5:
      Scripting::FreeScript5(script);
    }
    *(undefined4 *)&param_1[0x2d].field_0x78 = 0;
  }
  FromPlayToPause(*(undefined4 *)&param_1[0xf].field_0x44);
  *(undefined4 *)&param_1[0xf].field_0x44 = 0;
  if (*(int *)&param_1[0xf].field_0x4c != 0) {
    UnregisterScript__(*(int *)&param_1[0xf].field_0x4c);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void StartLoadingRegularTransition(GiantLoctextStruct *gsl)

{
  GamePauseContext *ctx;
  LPCWSTR pWVar1;
  uint uVar2;
  float fVar3;
  Cutscene *cutscene;
  
  ctx = GamePauseContext::ctor(*(uint *)&gsl->scriptHeaderVal2,0,gsl->transitionAssetName_);
  gsl->gamePauseCtx = ctx;
  switch(*(undefined4 *)&gsl->scriptHeaderVal2) {
  case 0:
  case 1:
  case 0xd:
  case 0xe:
    gsl[1].transitionIndex = 0;
    ctx->field6_0xc = 1;
    break;
  case 2:
    gsl[1].transitionIndex = 1;
    *(undefined4 *)&gsl[2].field_0xfd0 = 0;
    ctx->field6_0xc = 1;
    pWVar1 = (LPCWSTR)FUN_0004b550();
    XAPILIB::lstrcpyW((LPWSTR)&gsl[1].transitionVal1,pWVar1);
    pWVar1 = (LPCWSTR)FUN_0004b5a0();
    XAPILIB::lstrcpyW((LPWSTR)&gsl[1].field_0x1008,pWVar1);
    runtime::AllocateForLoctext_(0,1,(void *)0x80,(LoctextValueContext **)&gsl[1].discReadEnum);
    goto switchD_0012b678_caseD_8;
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
    gsl[1].transitionIndex = 0;
    ctx->field6_0xc = 1;
    ctx->field8_0x14 = 1;
    *(undefined4 *)&ctx->field_0x18 = 0;
    ctx->locationStr[0] = '\0';
    ctx->field_0x138 = 0;
    *(uint *)&gsl->gamePauseCtx->field_0x18 = gsl->transitionVal2;
    break;
  default:
    goto switchD_0012b678_caseD_8;
  }
  *(undefined2 *)&gsl[1].field_0x1008 = 0;
  *(undefined2 *)&gsl[1].transitionVal1 = 0;
  gsl[1].discReadEnum = 0;
switchD_0012b678_caseD_8:
  ctx = gsl->gamePauseCtx;
  uVar2 = ctx->id;
  cutscene = ctx->cutsceneBuffer;
  fVar3 = cutscene->t / cutscene->length;
  if (fVar3 < Cutscene::PauseCutsceneLookupTable[uVar2].tToDoLoad ||
      fVar3 == Cutscene::PauseCutsceneLookupTable[uVar2].tToDoLoad) {
    uVar2 = Cutscene::PauseCutsceneLookupTable[uVar2].field5_0x10c;
  }
  else {
    fVar3 = cutscene->t / cutscene->length;
    if (fVar3 < Cutscene::PauseCutsceneLookupTable[uVar2].tToSwapBuffers ||
        fVar3 == Cutscene::PauseCutsceneLookupTable[uVar2].tToSwapBuffers) {
      return;
    }
    uVar2 = Cutscene::PauseCutsceneLookupTable[uVar2].field6_0x110;
  }
  if (uVar2 != 0xffffffff) {
    *(float *)((int)(&ctx->cameraCfg + 1) + (uVar2 * 4 + 3) * 4) = 1.4013e-45;
  }
  return;
}




void UpdateStorybook(void)

{
                    // Whether or not to display loading state
  if ((((0 < TransitionData.discReadEnum) && (TransitionData.discReadEnum < 4)) &&
      (*(int *)&g_globalTransitionStates[TransitionData.transitionIndex].field_0x8 != 0)) &&
     ((TransitionData.field12_0x24 != (LoctextValueContext *)0x0 &&
      ((TransitionData.field12_0x24)->buffer->tail <= (TransitionData.field12_0x24)->buffer->head)))
     ) {
    LoctextValueContext::Initialise
              (TransitionData.field12_0x24,TransitionData.g_LoadingText,
               (float)g_DXContext.backBufferWidth * 0.5,(float)g_DXContext.backBufferHeight * 0.8,
               1.5,1.5,1.5,0,1);
    FUN_0005f550(0x3f000000);
  }
                    // When still loading
  if (TransitionData.discReadEnum == 1) {
    if ((TransitionData.field11_0x20 != 0) &&
       (TransitionData.field11_0x20 = TransitionData.field11_0x20 + -1,
       TransitionData.field11_0x20 == 0)) {
      g_globalFlagset = g_globalFlagset | 0x2000;
    }
    if ((DoneReadingLoad < 1) && (0 < TransitionData.doneReading_)) {
      DoneReadingLoad = DoneReadingLoad + 1;
    }
    else {
      TransitionData.doneReading_ = TransitionData.doneReading_ + 1;
    }
    (*(code *)g_callback6Sets[*(int *)(&DAT_00431478 + TransitionData.transitionIndex * 0x110)][1])
              (&TransitionData);
  }
  else {
                    // When finished loading
    if (TransitionData.discReadEnum == 3) {
      (*(code *)g_callback6Sets[*(int *)(&DAT_00431478 + TransitionData.transitionIndex * 0x110)][1]
      )(&TransitionData);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void CheckEndOfCutscene(void)

{
  if (Game::DialogState == NotInDialog) {
    if (EndCurrentSceneOrDialog != 0) {
      Events::UpdateActionBeginEnds(0xff,1);
      Scripting::numScriptConditions = Scripting::numScriptConditions + -1;
      EndCurrentSceneOrDialog = 0;
    }
    Game::UpdateActionType = 0;
    DAT_00545b44 = 0;
    DAT_00545bc4 = 0;
  }
  return;
}



// WARNING: Unable to use type for symbol markerInstance
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


