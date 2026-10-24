/* camera.c - Camera configs and management (playcam/director) */
#include "camera.h"

void GamePauseContext::loadShaderPages(BOOL gpc,GamePauseContext *param_2)

{
  BOOL BVar1;
  undefined4 *puVar2;
  int iVar3;
  ShaderEntry *entry;
  GamePausePage_ptr_4_int piVar5;
  undefined4 uVar4;
  BOOL local_4;
  ModelSubresource *mesh_header;
  
  entry = Graphics::ShaderPageEntries;
  piVar5 = &(param_2->field18_0x8c).field1_0x4;
  local_4 = gpc;
  do {
    mesh_header = *(ModelSubresource **)
                   (*(int *)(**(int **)(param_2->eventId_ + 0x204) + 0x10) + 0x24);
    if (mesh_header != (ModelSubresource *)0x0) {
      BVar1 = ModelSubresource::getMapValue(mesh_header,entry->pageName,(void **)&local_4);
      if ((BVar1 != 0) && (local_4 != 0)) {
        puVar2 = FUN_000f8540(entry->pageName,"colour0",*(Model **)(param_2->eventId_ + 0x204));
        ADJ(piVar5).field0_0x0 = (int)puVar2;
        iVar3 = DAT_005047e4;
        if ((char)entry->someFlag == '\0') {
          iVar3 = DAT_005047d8;
        }
        ADJ(piVar5)->field1_0x4 = iVar3;
        puVar2[3] = iVar3;
        puVar2[4] = 0;
        puVar2[5] = 0;
        if (iVar3 == 0) {
          uVar4 = 0;
        }
        else {
          if (*(char *)(iVar3 + 0x11) != '\0') {
            *(undefined1 *)(iVar3 + 0x13) = 0;
          }
          uVar4 = puVar2[3];
        }
        FUN_0015b2b0(puVar2[1],puVar2[2],uVar4);
        ADJ(piVar5)->field2_0x8 = 0;
        ADJ(piVar5)->field3_0xc = 0;
      }
    }
    entry = entry + 1;
    piVar5 = piVar5 + 4;
  } while ((int)entry < 0x4231b4);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


GamePauseContext * GamePauseContext::ctor(uint id,uint param_2,char *name)

{
  Camera *mv;
  GamePauseContext *pauseContext;
  char *piVar3;
  Cutscene *csb;
  uint uVar1;
  int i;
  BOOL gpc;
  Asset *out_asset;
  char *paVar6;
  char *puVar1;
  Camera *head_cfg;
  
  pauseContext = malloc_(123556);
  paVar6 = (char *)pauseContext;
                    // Memset new asset to 0
  for (i = 30889; i != 0; i = i + -1) {
    paVar6[0] = '\0';
    paVar6[1] = '\0';
    paVar6[2] = '\0';
    paVar6[3] = '\0';
    paVar6 = paVar6 + 4;
  }
  pauseContext->id = id;
  *(uint *)&pauseContext->flags_ = param_2;
  mv = &pauseContext->cameraCfg;
  pauseContext->field17_0x88 = 0.0;
  pauseContext->field7_0x10 = 0;
  pauseContext->field6_0xc = 0;
  pauseContext->field5_0x8 = 0;
  pauseContext->field8_0x14 = 0;
  pauseContext->initialisationState = 0xffff;
  Camera::ctor(mv,"book",(ProjectionSetBitField)0xc);
  piVar3 = (char *)Camera::AvailableConfigs;
  head_cfg = Camera::AvailableConfigs[0].head;
  while (head_cfg != (Camera *)0x0) {
    piVar3 = (char *)((Camera *)piVar3)->next;
    head_cfg = ((Camera *)piVar3)->next;
  }
  head_cfg = ((Camera *)piVar3)->prev;
  ((Camera *)piVar3)->prev = mv;
  mv->next = (Camera *)piVar3;
  (pauseContext->cameraCfg).prev = head_cfg;
  if (head_cfg != (Camera *)0x0) {
    head_cfg->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(pauseContext->cameraCfg).name);
  }
  csb = Assets::LoadCutscene
                  (Cutscene::PauseCutsceneLookupTable[pauseContext->id].cutsceneName,0x36,mv);
                    // Triggers on pause
  pauseContext->cutsceneBuffer = csb;
  Cutscene::update(csb,Cutscene::PauseCutsceneLookupTable[pauseContext->id].fadeAmount_,0.0,0);
  uVar1 = Cutscene::getEventIdFromModelName
                    (pauseContext->cutsceneBuffer,
                     Cutscene::PauseCutsceneLookupTable[pauseContext->id].cutsceneModel);
  pauseContext->eventId_ = uVar1;
  loadShaderPages(gpc,pauseContext);
  if ((name != (char *)0x0) && (Cutscene::PauseCutsceneLookupTable[pauseContext->id].someInt != -1))
  {
    if (*(int *)name == 0x5f646961) {
      Assets::GetResourceBytes(name,(void **)&id);
      out_asset = (Asset *)id;
      if (id == 0) {
        runtime::ExitGame(2);
      }
    }
    else {
      out_asset = (Asset *)0x0;
    }
    pauseContext->asset = out_asset;
    FUN_000f86f0(out_asset,0,
                 *(Asset **)
                  ((int)(&pauseContext->cameraCfg + 1) +
                  (Cutscene::PauseCutsceneLookupTable[pauseContext->id].someInt * 4 + 1) * 4));
  }
  FUN_000481e0(pauseContext);
  if ((pauseContext->flags_ & 1) != 0) {
    PTR_005462a0 = pauseContext;
  }
  return pauseContext;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall Camera::AppendAndSelect(Camera *proj,uint index)

{
  Camera *pCVar1;
  CameraLLNode *curr;
  CameraLLNode *next;
  
  curr = AvailableConfigs + index;
  next = (CameraLLNode *)AvailableConfigs[index].head;
  while ((Camera *)next != (Camera *)0x0) {
    curr = (CameraLLNode *)((Camera *)curr)->next;
    next = (CameraLLNode *)curr->head;
  }
  pCVar1 = ((Camera *)curr)->prev;
  ((Camera *)curr)->prev = proj;
  proj->next = (Camera *)curr;
  proj->prev = pCVar1;
  if (pCVar1 != (Camera *)0x0) {
    pCVar1->next = proj;
  }
  if (ActiveConfigs[index] == (Camera *)0x0) {
    SetActiveCameraConfig(index,proj->name);
  }
  return;
}




void Camera::setActiveCamera(Camera *cam)

{
  BOOL BVar1;
  uint cameraIndex;
  
  if (cam->next != (Camera *)0x0) {
    cam->next->prev = cam->prev;
  }
  if (cam->prev != (Camera *)0x0) {
    cam->prev->next = cam->next;
  }
  cam->next = (Camera *)0x0;
  cam->prev = (Camera *)0x0;
  cameraIndex = 0;
  do {
    if (ActiveConfigs[cameraIndex] == cam) {
      BVar1 = SetActiveCameraConfig(cameraIndex,(char *)(PreviousConfigNames + cameraIndex));
      if (BVar1 == 0) {
        if (AvailableConfigs[cameraIndex].projectionSet != (Camera *)0x0) {
          SetActiveCameraConfig(cameraIndex,(AvailableConfigs[cameraIndex].projectionSet)->name);
          return;
        }
        ActiveConfigs[cameraIndex] = (Camera *)0x0;
      }
      return;
    }
    cameraIndex = cameraIndex + 1;
  } while ((int)cameraIndex < 4);
  return;
}




BOOL Camera::SetActiveCameraConfig(uint cameraIndex,char *name)

{
  char cVar1;
  MainCameraStruct *pMVar3;
  byte bVar4;
  byte bVar5;
  char *pGVar6;
  char *ps_name;
  uint uVar6;
  int iVar7;
  float local_1c;
  int local_18;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  vec3 v1;
  Camera *new_ps;
  MainCameraStruct *pMVar2;
  uint ps_index;
  
  ps_index = cameraIndex;
  pMVar2 = Graphics::CurrentCameraStruct;
  new_ps = AvailableConfigs[cameraIndex].projectionSet;
  uVar6 = cameraIndex;
  while( true ) {
    if (new_ps == (Camera *)0x0) {
      ActiveConfigs[cameraIndex] = (Camera *)0x0;
      return 0;
    }
    ps_name = new_ps->name;
    iVar7 = (int)name - (int)ps_name;
    while( true ) {
      bVar4 = *ps_name;
      if (0x20 < bVar4) {
        bVar4 = bVar4 & 0xdf;
      }
      bVar5 = ps_name[iVar7];
      if (0x20 < bVar5) {
        bVar5 = bVar5 & 0xdf;
      }
      if (bVar4 != bVar5) break;
      ps_name = ps_name + 1;
      if (bVar4 == 0) goto SelectCamera_Found;
    }
    uVar6 = (uint)bVar4 - (uint)bVar5;
    if (uVar6 == 0) break;
    new_ps = new_ps->prev;
  }
SelectCamera_Found:
  cameraIndex = uVar6;
  if ((new_ps->flags).updateCamera? != 0) {
    if (ActiveConfigs[ps_index] == (Camera *)0x0) {
      (new_ps->pos).y = 15.0;
      (new_ps->pos).x = 0.0;
      (new_ps->pos).z = 30.0;
    }
    else {
                    // These all use MainCamera->pos
      (new_ps->pos).x = (Graphics::CurrentCameraStruct->pos).x;
      (new_ps->pos).y = (pMVar2->pos).y;
      (new_ps->pos).z = (pMVar2->pos).z;
    }
    pMVar3 = Graphics::CurrentCameraStruct;
    if ((new_ps->flags).useEuler == 0) {
      (new_ps->rotQuat).x = (Graphics::CurrentCameraStruct->rotQuat).x;
      (new_ps->rotQuat).y = (pMVar3->rotQuat).y;
      (new_ps->rotQuat).z = (pMVar3->rotQuat).z;
      (new_ps->rotQuat).w = (pMVar3->rotQuat).w;
    }
    else {
      if (ActiveConfigs[ps_index] == (Camera *)0x0) {
        v1.x = 0.0;
        v1.y = 0.0;
        v1.z = 1.0;
      }
      else {
        v1.x = 0.0 - (Graphics::CurrentCameraStruct->forwards).x;
        v1.y = 0.0 - (Graphics::CurrentCameraStruct->forwards).y;
        v1.z = 0.0 - (Graphics::CurrentCameraStruct->forwards).z;
      }
      FUN_00105e20(&v1,&(new_ps->rotQuat).y,&(new_ps->rotQuat).x);
      (new_ps->rotQuat).z = 0.0;
    }
  }
                    // Store the previous camera
  if (ActiveConfigs[ps_index] != (Camera *)0x0) {
    ps_name = ActiveConfigs[ps_index]->name;
    pGVar6 = (char *)(PreviousConfigNames + ps_index);
    do {
      cVar1 = *ps_name;
      *pGVar6 = cVar1;
      pGVar6 = pGVar6 + 1;
      ps_name = ps_name + 1;
    } while (cVar1 != '\0');
  }
  ActiveConfigs[ps_index] = new_ps;
  ComputeTangents(new_ps->fov,&local_18,&local_1c,(float *)&cameraIndex,&new_ps->aspectRatio,
                  &new_ps->cotangentOffset,new_ps->aspectRatioType,local_14,local_10);
  return 1;
}



// Revert the camera which is currently using config (param_1) to its previous value.


void Camera::RevertCameraUsingConfig(Camera *config)

{
  BOOL success;
  uint cameraIndex;
  
  cameraIndex = 0;
  do {
    if (ActiveConfigs[cameraIndex] == config) {
      success = SetActiveCameraConfig(cameraIndex,(char *)(PreviousConfigNames + cameraIndex));
                    // If we couldn't set the previous config (because there wasn't one)
      if (success == 0) {
        if (AvailableConfigs[cameraIndex].projectionSet != (Camera *)0x0) {
          SetActiveCameraConfig(cameraIndex,(AvailableConfigs[cameraIndex].projectionSet)->name);
          return;
        }
        ActiveConfigs[cameraIndex] = (Camera *)0x0;
      }
      return;
    }
    cameraIndex = cameraIndex + 1;
  } while ((int)cameraIndex < 4);
  return;
}




float __fastcall Camera::ctor(Camera *mv,char *name,ProjectionSetBitField flags)

{
  float fovScale;
  float discardedFloat;
  float local_10;
  vec3 local_c;
  char c;
  int c_offset;
  
  (mv->pos).z = 0.0;
  (mv->pos).y = 0.0;
  (mv->pos).x = 0.0;
  mv->flags = flags;
  if (flags.useEuler == 0) {
    (mv->rotQuat).x = 0.0;
    (mv->rotQuat).y = 0.0;
    (mv->rotQuat).z = 0.0;
    (mv->rotQuat).w = 1.0;
  }
  else {
    (mv->rotQuat).z = 0.0;
    (mv->rotQuat).y = 0.0;
    (mv->rotQuat).x = 0.0;
  }
  mv->fov = -1.0;
  mv->aspectRatioType = 3;
  mv->field5_0x28 = 1e+09;
  mv->float5 = 0.0;
  c_offset = 0x34 - (int)name;
                    // memcpy into name
  do {
    c = *name;
    name[(int)mv + c_offset] = c;
    name = name + 1;
  } while (c != '\0');
  mv->next = (Camera *)0x0;
  mv->prev = (Camera *)0x0;
  fovScale = ComputeTangents(mv->fov,(int *)&local_c,&local_10,&discardedFloat,&mv->aspectRatio,
                             &mv->cotangentOffset,mv->aspectRatioType,&local_c.y,&local_c.z);
  return fovScale;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


AspectRatioType CameraDescriptor::interpolateVal9(CameraDescriptor *param_1,float t)

{
  float fVar1;
  float local_8;
  float local_4;
  
  if ((param_1->aspectRatioValues).numFloats != 0) {
    fVar1 = FloatSet::interpolateAtT(&param_1->aspectRatioValues,t,&local_8,&local_4);
    fVar1 = (1.0 - fVar1) * local_8 + local_4 * fVar1;
    if (1.9 < fVar1) {
      return WellOver;
    }
    if (1.5 < fVar1) {
      return Over;
    }
  }
  return Zero;
}




