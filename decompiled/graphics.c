/* graphics.c - Rendering: textures, shaders, XGBuffers, burnups, camera mgmt */
#include "graphics.h"

void SwapBuffers_(int param_1)

{
  HANDLE section_handle;
  char *swap_fence;
  PVOID section;
  int section_size;
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  DWORD fence;
  int iVar4;
  int iVar5;
  int unaff_FS_OFFSET;
  int local_10;
  int local_c;
  
  section_handle = runtime::GetXbeSectionByName("dirtydisk_bitmap");
  if ((((section_handle != (HANDLE)0xffffffff) ||
       (swap_fence = XAPILIB::GetLastError(unaff_FS_OFFSET), swap_fence == (char *)0x0)) &&
      ((section = XAPILIB::XLoadSectionByHandle(section_handle), section != (PVOID)0x0 ||
       (swap_fence = XAPILIB::GetLastError(unaff_FS_OFFSET), swap_fence == (char *)0x0)))) &&
     ((section_size = XAPILIB::XGetSectionSize(section_handle), section_size != 0 ||
      (swap_fence = XAPILIB::GetLastError(unaff_FS_OFFSET), swap_fence == (char *)0x0)))) {
    if (Graphics::BackbufferReferences == 0) {
      D3D_g_BackBuffer2 = (D3DResource *)D3D8::D3DDevice_GetBackBuffer2(-1);
      D3D8::D3DSurface_LockRect(D3D_g_BackBuffer2,&Graphics::D3D_g_LOCKED_RECT,(void *)0x0,0x40);
    }
    Graphics::BackbufferReferences = Graphics::BackbufferReferences + 1;
    Graphics::ColorRect(0x280,0,0,(uchar  [4])0xff000000,(void *)0x1e0);
    section_size = *(int *)((int)section + 0x12);
    iVar1 = 0x140 - section_size;
    local_c = 0;
    iVar5 = 0xd0;
    do {
      local_10 = 0;
      if (0 < section_size) {
        iVar4 = iVar1 * 4;
        do {
          iVar2 = Graphics::D3D_g_SURFACE_BASE_PTR;
          section_size = ((*(int *)((int)section + 0x16) - local_c) + param_1 * -0x20 + -1) *
                         section_size + local_10;
          if ((*(byte *)((section_size >> 3) + 0x3e + (int)section) &
              (byte)(1 << (7 - ((byte)section_size & 7) & 0x1f))) != 0) {
            section_size = iVar5 * Graphics::D3D_g_LOCKED_RECT + iVar4;
            *(undefined1 *)(section_size + 2 + Graphics::D3D_g_SURFACE_BASE_PTR) = 0xff;
            *(undefined1 *)(section_size + 1 + iVar2) = 0xff;
            *(undefined1 *)(section_size + iVar2) = 0xff;
            *(undefined1 *)(section_size + 3 + iVar2) = 0xff;
            section_size = Graphics::D3D_g_SURFACE_BASE_PTR;
            iVar2 = iVar5 * Graphics::D3D_g_LOCKED_RECT + iVar4;
            *(undefined1 *)(iVar2 + 6 + Graphics::D3D_g_SURFACE_BASE_PTR) = 0xff;
            *(undefined1 *)(iVar2 + 5 + section_size) = 0xff;
            *(undefined1 *)(iVar2 + 4 + section_size) = 0xff;
            *(undefined1 *)(iVar2 + 7 + section_size) = 0xff;
            puVar3 = (undefined1 *)
                     ((iVar5 + 1) * Graphics::D3D_g_LOCKED_RECT + iVar4 +
                     Graphics::D3D_g_SURFACE_BASE_PTR);
            puVar3[2] = 0xff;
            puVar3[1] = 0xff;
            *puVar3 = 0xff;
            puVar3[3] = 0xff;
            puVar3 = (undefined1 *)
                     ((iVar5 + 1) * Graphics::D3D_g_LOCKED_RECT + iVar4 + 4 +
                     Graphics::D3D_g_SURFACE_BASE_PTR);
            puVar3[2] = 0xff;
            puVar3[1] = 0xff;
            *puVar3 = 0xff;
            puVar3[3] = 0xff;
          }
          section_size = *(int *)((int)section + 0x12);
          local_10 = local_10 + 1;
          iVar4 = iVar4 + 8;
        } while (local_10 < section_size);
      }
      local_c = local_c + 1;
      iVar5 = iVar5 + 2;
    } while (iVar5 < 0x110);
    Graphics::BackbufferReferences = Graphics::BackbufferReferences + -1;
    if (Graphics::BackbufferReferences == 0) {
      D3D8::D3DResource_Release((D3DResource *)D3D_g_BackBuffer2);
      D3D_g_BackBuffer2 = (D3DResource *)0x0;
      fence = D3D8::D3DDevice_InsertFence();
      D3D8::D3DDevice_Swap(0);
      D3D8::D3DDevice_BlockOnFence(fence);
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::UpdateCamerasAndDraw(void)

{
  float fVar1;
  Camera *pCVar2;
  int iVar3;
  float *extraout_ECX;
  float *extraout_EDX;
  int i;
  
  i = 0;
  do {
    pCVar2 = Camera::ActiveConfigs[i];
    iVar3 = FUN_000489e0(pCVar2);
    if (iVar3 != 0) {
      RecalculateWorldAndViews();
      FUN_0013c490(&pCVar2->float5,&pCVar2->field5_0x28,&CurrentCameraStruct->affineT);
      fVar1 = *extraout_ECX;
      CurrentCameraStruct->near = *extraout_EDX;
      CurrentCameraStruct->far = fVar1;
      UpdatePerspectiveProj();
      UpdateViewport2();
      DrawEverything___();
    }
    i = i + 1;
  } while (i < 4);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Graphics::Update(void)

{
  undefined4 uVar1;
  FileContext *i2;
  
  uVar1 = 3;
  if (((DAT_00512af0 == 0) && (DAT_004dea50 == 0)) || (TransitionData.discReadEnum != 0)) {
    uVar1 = 0xf3;
  }
                    // Clear stuff
  D3D8::D3DDevice_SetViewport((D3DVIEWPORT8 *)&D3DVIEWPORT8_0033a5b8);
  FUN_00154a20(uVar1);
  UnbindAll();
                    // Start doing stuff
  FUN_000f9780();
  FUN_00036180();
  if ((DoDat0x0050e0b8 == 0) && (i2 = (FileContext *)g_MovieListHead, g_PlayingMovies__ == 0)) {
    for (; i2 != (FileContext *)0x0; i2 = i2->next) {
      AllocatedMovie::MustRead__((AllocatedMovie *)i2);
    }
  }
  RunDrawingCallbacks();
  UpdateCamerasAndDraw();
  FUN_000f6f70();
  FUN_00066080();
  PresentFrame();
  if ((DoDat0x0050e0b8 == 0) && (i2 = (FileContext *)g_MovieListHead, g_PlayingMovies__ == 0)) {
    for (; i2 != (FileContext *)0x0; i2 = i2->next) {
      AllocatedMovie::MustRead__((AllocatedMovie *)i2);
    }
  }
  return;
}



// WARNING: Unable to use type for symbol i2
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0003e850(entityAvatarFxBurnup *param_1)

{
  avatar_0x1e0 pEVar1;
  int iVar2;
  undefined4 *puVar3;
  
  (param_1->avatar).collisionMask = Nothing;
  pEVar1 = (param_1->avatar).avatarCollider.prev;
  if (pEVar1 != (avatar_0x1e0)0x0) {
    pEVar1->next = (param_1->avatar).avatarCollider.next;
  }
  pEVar1 = (param_1->avatar).avatarCollider.next;
  if (pEVar1 != (avatar_0x1e0)0x0) {
    pEVar1->prev = (param_1->avatar).avatarCollider.prev;
  }
  (param_1->avatar).avatarCollider.prev = (avatar_0x1e0)0x0;
  (param_1->avatar).avatarCollider.next = (avatar_0x1e0)0x0;
  iVar2 = *(int *)&(param_1->avatar).field_0x1e8;
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)&(param_1->avatar).field_0x1ec;
  }
  puVar3 = *(undefined4 **)&(param_1->avatar).field_0x1ec;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = *(undefined4 *)&(param_1->avatar).field_0x1e8;
  }
  *(undefined4 *)&(param_1->avatar).field_0x1e8 = 0;
  *(undefined4 *)&(param_1->avatar).field_0x1ec = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void removeavatarfromsomelistsshit(entityAvatarFxBurnup *param_1)

{
  uint *puVar1;
  avatar_0x900 pEVar2;
  uint uVar3;
  uint *puVar4;
  avatar_0x900 pEVar5;
  
  puVar1 = &(param_1->avatar).skipUpdate;
  if ((param_1->avatar).skipUpdate == 0) {
    uVar3 = 0x511b54;
    if (Game::SceneInfo.field27_0xb8 != 0) {
      puVar4 = &Game::SceneInfo.field27_0xb8;
      do {
        uVar3 = *puVar4;
        puVar4 = (uint *)(uVar3 + 4);
      } while (*(int *)(uVar3 + 4) != 0);
    }
    *(uint **)(uVar3 + 4) = puVar1;
    *puVar1 = uVar3;
    *(undefined4 *)&(param_1->avatar).field_0x90c = 0;
    avatar::onDrawListAdd(&param_1->avatar);
    FUN_0003e850(param_1);
    entityAvatarFxBurnup::checkCollision0x4(param_1);
    pEVar2 = (param_1->avatar).node0x900.prev;
    if (pEVar2 == (avatar_0x900)0x0) {
      pEVar5 = (avatar_0x900)0x0;
    }
    else {
      do {
        pEVar5 = pEVar2;
        pEVar2 = pEVar5->prev;
      } while (pEVar5->prev != (avatar_0x900)0x0);
    }
    if ((EmbeddedNode<>_conflict6 *)pEVar5 == &Game::SceneInfo.newAvatars) {
      pEVar2 = (param_1->avatar).node0x900.prev;
      if (pEVar2 != (avatar_0x900)0x0) {
        pEVar2->next = (param_1->avatar).node0x900.next;
      }
      pEVar2 = (param_1->avatar).node0x900.next;
      if (pEVar2 != (avatar_0x900)0x0) {
        pEVar2->prev = (param_1->avatar).node0x900.prev;
      }
      (param_1->avatar).node0x900.prev = (avatar_0x900)0x0;
      (param_1->avatar).node0x900.next = (avatar_0x900)0x0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Graphics::SetShaderParamFromAvatar(avatar *this,char *mapKey,void *valueToSet)

{
  BOOL BVar1;
  int iVar2;
  undefined4 uVar3;
  int *local_4;
  ModelSubresource *subres;
  
  if (this->model == (Model *)0x0) {
    return 0;
  }
  subres = this->model->descriptor->runtimeCtx->modelSubresource;
  if (subres != (ModelSubresource *)0x0) {
    BVar1 = ModelSubresource::getMapValue(subres,mapKey,&local_4);
    if ((BVar1 != 0) && (local_4 != (int *)0x0)) {
      iVar2 = FUN_0015b270(*(undefined4 *)((int)&subres->field8_0x20 + *local_4),valueToSet);
      if (iVar2 != -1) {
        uVar3 = FUN_000f9b00();
        return uVar3;
      }
    }
  }
  return 0;
}




void Graphics::CopyRectsAndDraw(int param_1)

{
  float fVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  BOOL BVar5;
  float *extraout_ECX;
  float *extraout_EDX;
  int iVar6;
  D3DTexture *pDVar7;
  uint cameraIndex;
  int *piVar8;
  int local_4;
  
  if (*(int *)(param_1 + 0x24) != 0) {
    UseDefaultPixelC0 = UseDefaultPixelC0 + 1;
    DAT_005077fc = 1;
    DAT_00509b00 = 1;
    FUN_00156ea0(false);
    piVar8 = (int *)(param_1 + 0x94);
    local_4 = 4;
    do {
      if (*piVar8 != 0) {
        iVar6 = piVar8[-1];
        pDVar7 = (D3DTexture *)(*(int *)(iVar6 + 4) + (uint)*(byte *)(iVar6 + 0x12) * 0x14 + iVar6);
        PTR_00545b2c = (D3DResource *)D3D8::D3DDevice_GetBackBuffer2(0);
        _DAT_00545b30 = 0;
        PTR_00545b28 = (D3DResource *)D3D8::D3DTexture_GetSurfaceLevel2(pDVar7,0);
        _DAT_00545b30 = ((D3DSurface *)PTR_00545b28 != (D3DSurface *)0x0) - 1 & 0x8007000e;
        D3D8::D3DDevice_CopyRects
                  ((D3DSurface *)PTR_00545b2c,(RECT *)0x0,0,(D3DSurface *)PTR_00545b28,(POINT *)0x0)
        ;
        _DAT_00545b30 = 0;
        D3D8::D3DResource_Release(PTR_00545b2c);
        D3D8::D3DResource_Release(PTR_00545b28);
        if ((g_DXContext.widescreen != false) &&
           (((g_paused_ == 0 || (Game::g_pauseState == New_Name_(2))) ||
            (Game::g_pauseState == ChallengeRules)))) {
          CurrentCameraStruct->aspectRatioIndex = 4.2039e-45;
          UpdateViewport2();
          FUN_0005ce80(piVar8[-1],&FLOAT_004231b4,&FLOAT_004231bc);
          PTR_00545b2c = (D3DResource *)D3D8::D3DDevice_GetBackBuffer2(0);
          _DAT_00545b30 = 0;
          PTR_00545b28 = (D3DResource *)D3D8::D3DTexture_GetSurfaceLevel2(pDVar7,0);
          _DAT_00545b30 = ((D3DSurface *)PTR_00545b28 != (D3DSurface *)0x0) - 1 & 0x8007000e;
          D3D8::D3DDevice_CopyRects
                    ((D3DSurface *)PTR_00545b2c,(RECT *)0x0,0,(D3DSurface *)PTR_00545b28,
                     (POINT *)0x0);
          _DAT_00545b30 = 0;
          D3D8::D3DResource_Release(PTR_00545b2c);
          D3D8::D3DResource_Release(PTR_00545b28);
        }
        *piVar8 = 0;
      }
      piVar8 = piVar8 + 4;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
    piVar8 = (int *)(param_1 + 0x98);
    iVar6 = 4;
    do {
      if ((*piVar8 != 0) && (iVar3 = piVar8[-2], iVar3 != 0)) {
        bVar2 = *(byte *)(iVar3 + 0x12);
        iVar4 = *(int *)(iVar3 + 4);
        FUN_00061b40(DAT_004231c4);
        PTR_00545b2c = (D3DResource *)D3D8::D3DDevice_GetBackBuffer2(0);
        _DAT_00545b30 = 0;
        PTR_00545b28 = (D3DResource *)
                       D3D8::D3DTexture_GetSurfaceLevel2
                                 ((D3DTexture *)(iVar4 + (uint)bVar2 * 0x14 + iVar3),0);
        _DAT_00545b30 = ((D3DSurface *)PTR_00545b28 != (D3DSurface *)0x0) - 1 & 0x8007000e;
        D3D8::D3DDevice_CopyRects
                  ((D3DSurface *)PTR_00545b2c,(RECT *)0x0,0,(D3DSurface *)PTR_00545b28,(POINT *)0x0)
        ;
        _DAT_00545b30 = 0;
        D3D8::D3DResource_Release(PTR_00545b2c);
        D3D8::D3DResource_Release(PTR_00545b28);
        *piVar8 = 0;
      }
      piVar8 = piVar8 + 4;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    FUN_00061b40(DAT_005462a4);
    iVar6 = FUN_000489e0((Camera *)(param_1 + 0x28));
    if (iVar6 != 0) {
      RecalculateWorldAndViews();
      FUN_0013c490((float *)(param_1 + 0x54),(float *)(param_1 + 0x50),&CurrentCameraStruct->affineT
                  );
      fVar1 = *extraout_ECX;
      CurrentCameraStruct->near = *extraout_EDX;
      CurrentCameraStruct->far = fVar1;
      UpdatePerspectiveProj();
      UpdateViewport2();
    }
    FUN_0004dbd0(*(Cutscene **)(param_1 + 0x24));
    FUN_00047770();
    cameraIndex = 0;
    do {
      if (Camera::ActiveConfigs[cameraIndex] == (Camera *)(param_1 + 0x28)) {
        BVar5 = Camera::SetActiveCameraConfig
                          (cameraIndex,(char *)(Camera::PreviousConfigNames + cameraIndex));
        if (BVar5 == 0) {
          if (Camera::AvailableConfigs[cameraIndex].projectionSet == (Camera *)0x0) {
            Camera::ActiveConfigs[cameraIndex] = (Camera *)0x0;
          }
          else {
            Camera::SetActiveCameraConfig
                      (cameraIndex,(Camera::AvailableConfigs[cameraIndex].projectionSet)->name);
          }
        }
        break;
      }
      cameraIndex = cameraIndex + 1;
    } while ((int)cameraIndex < 4);
    UseDefaultPixelC0 = UseDefaultPixelC0 + -1;
    if (UseDefaultPixelC0 == 0) {
      DAT_00509b00 = 0;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0004c000(TextureMaybeSomething *param_1)

{
  code *pcVar1;
  int iVar2;
  
  if (param_1->field444_0x1e6 == '\0') {
    pcVar1 = (code *)param_1->field122_0x98;
  }
  else {
    if ((code *)param_1->field124_0xa0 != (code *)0x0) {
      (*(code *)param_1->field124_0xa0)(param_1);
    }
    FUN_00102500();
    if ((param_1->field121_0x94 == (undefined *)0x0) || (param_1->field125_0xa4 == 0)) {
      iVar2 = 2;
      do {
        FUN_00102030();
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    else {
      iVar2 = 2;
      do {
        FUN_00102030();
        (*(code *)param_1->field121_0x94)(param_1);
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    if (param_1->field452_0x1ee == '\0') {
      FUN_0004b800();
      pcVar1 = (code *)param_1->field123_0x9c;
    }
    else {
      FUN_0004ba90();
      pcVar1 = (code *)param_1->field123_0x9c;
    }
  }
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(param_1);
  }
  return;
}




BOOL RuncutsceneAndShouldEnd(float delta,Cutscene *csb,Camera *cameraConfig)

{
  CutsceneCameraEvent *cameraEvents;
  float fVar1;
  float fVar2;
  float local_4;
  
  if (csb->field18_0x158 != 0) {
    if ((csb->field19_0x15c != 0) && (Game::DialogState == NotInDialog)) {
      CloseDoorAndUpdateState(0,csb);
    }
    if (csb->field18_0x158 != 0) goto LAB_0004dac6;
  }
  fVar1 = csb->t + delta;
  csb->prevT = csb->t;
                    // Update cutscene progress
  csb->t = fVar1;
  *(float *)&csb->field_0x38 = delta;
  if (csb->length <= fVar1 && fVar1 != csb->length) {
    csb->t = csb->length;
  }
                    // Can go to next event?
  if (csb->t <= 0.0 && csb->t != 0.0) {
    csb->t = 0.0;
  }
LAB_0004dac6:
  if (csb->val1 <= 0.0) {
    local_4 = -1.0;
  }
  else {
    fVar1 = csb->val2;
    fVar2 = csb->val1 - delta;
    csb->val1 = fVar2;
    if (fVar1 == 0.0) {
      local_4 = 1.0;
    }
    else {
      local_4 = (fVar2 - fVar1) / (0.0 - fVar1);
      if (1.0 < local_4) {
        local_4 = 1.0;
      }
      else if (local_4 < 0.0) {
        local_4 = 0.0;
      }
    }
  }
  if ((csb->descriptor->numCameras != '\0') && (cameraConfig != (Camera *)0x0)) {
    Cutscene::updateCameraFromCutscene(csb,cameraConfig);
  }
  cameraEvents = csb->cameraEvents;
  if (((cameraEvents != (CutsceneCameraEvent *)0x0) && (csb->field18_0x158 == 0)) && (delta != 0.0))
  {
    FUN_0004d370((float)cameraEvents,csb,&csb->events,0,csb->t,csb->prevT,0,0,cameraEvents);
  }
  fVar1 = csb->t / csb->length;
  Cutscene::updateAvatarsAndAnims(csb,local_4,fVar1,fVar1);
  if (csb->t < csb->length) {
    return 0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Assets__LoadCutsceneCamera_(int param_1)

{
  Cutscene *local_4;
  
  if (*(int *)param_1 != 0x5f646961) {
    Cutscene::LoadedCutscenes[6] = (Cutscene *)0x0;
    Cutscene::LoadedCutscenes[5] = pCRam00000004;
    return;
  }
  Assets::GetResourceBytes((char *)param_1,&local_4);
  if (local_4 == (Cutscene *)0x0) {
    runtime::ExitGame(2);
  }
  Cutscene::LoadedCutscenes[6] = local_4;
  Cutscene::LoadedCutscenes[5] = (Cutscene *)(local_4->v2).y;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Graphics::SplitQuadForRendering(vec3 *src,vec3 *dst)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  dst->x = src->x;
  dst->y = src->y;
  dst->z = src->z;
  dst[1].x = src[1].x;
  dst[1].y = src[1].y;
  dst[1].z = src[1].z;
  dst[2].x = src[2].x;
  dst[2].y = src[2].y;
  dst[2].z = src[2].z;
  dst[3].x = src[3].x;
  dst[3].y = src[3].y;
  dst[3].z = src[3].z;
                    // sort by y value
  _qsort(dst,4,0xc,vec3::CmpYDescending);
  fVar1 = dst->x - dst[2].x;
  fVar3 = dst->y - dst[2].y;
  fVar2 = dst->z - dst[2].z;
  fVar4 = dst->x - dst[3].x;
  fVar6 = dst->y - dst[3].y;
  fVar5 = dst->z - dst[3].z;
  if (SQRT(fVar1 * fVar1 + fVar3 * fVar3 + fVar2 * fVar2) <
      SQRT(fVar4 * fVar4 + fVar6 * fVar6 + fVar5 * fVar5)) {
    fVar1 = dst[2].x;
    fVar2 = dst[2].y;
    fVar3 = dst[2].z;
    dst[2].x = dst[3].x;
    dst[2].y = dst[3].y;
    dst[2].z = dst[3].z;
    dst[3].x = fVar1;
    dst[3].y = fVar2;
    dst[3].z = fVar3;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

uint * Subresource0xd::doSomething
                 (Subresource0xd *this,vec3 *param_2,uint param_3,undefined4 param_4,uint param_5,
                 Entry0xd *entry,short drawType,undefined4 param_8,undefined4 param_9,
                 undefined4 param_10)

{
  undefined4 *puVar1;
  float fVar2;
  uint *extraout_EAX;
  int iVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  float fVar11;
  float fVar12;
  vec3 local_3c;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_8;
  
  local_20 = param_2[3].y - param_2->y;
  local_1c = param_2[3].z - param_2->z;
  local_2c = param_2[1].y - param_2->y;
  local_28 = param_2[1].z - param_2->z;
  local_30 = param_2[1].x - param_2->x;
  local_24 = param_2[3].x - param_2->x;
  local_3c.x = local_1c * local_2c - local_20 * local_28;
  local_3c.y = local_28 * local_24 - local_1c * local_30;
  local_3c.z = local_20 * local_30 - local_2c * local_24;
  local_18 = local_3c.x;
  local_14 = local_3c.y;
  local_10 = local_3c.z;
  D3DX8::D3DXVec3Normalize(&local_3c,&local_3c);
  FUN_0004b5f0((undefined2)param_4,(ushort)param_3,(ushort)param_5);
  *(undefined1 *)((int)extraout_EAX + 0x1e5) = 3;
  extraout_EAX[0x2a] = 0;
  if ((uint)entry->numTextures < this->numTextures) {
    extraout_EAX[0x2a] = (uint)this->textures[entry->numTextures];
  }
  entry = (Entry0xd *)0x0;
  if ((short)extraout_EAX[0xc] != 0) {
    do {
      uVar7 = 0;
      if (*(short *)((int)extraout_EAX + 0x32) != 0) {
        do {
          local_8 = param_2->y;
          fVar2 = param_2->z;
          fVar10 = (float10)fsin(((float10)((uint)entry & 0xffff) /
                                 ((float10)(ushort)extraout_EAX[0xc] * (float10)0.33333334)) *
                                 (float10)6.2831855);
          fVar11 = (float)((uint)entry & 0xffff) / (float)(int)((ushort)extraout_EAX[0xc] - 1);
          fVar12 = (float)uVar7 / (float)(int)(*(ushort *)((int)extraout_EAX + 0x32) - 1);
          iVar3 = (((uint)entry & 0xffff) * (uint)*(ushort *)((int)extraout_EAX + 0x32) +
                  (uint)uVar7) * 0x30;
          pfVar5 = (float *)(extraout_EAX[1] + iVar3);
          uVar7 = uVar7 + 1;
          fVar10 = fVar10 + fVar10;
          *pfVar5 = (float)((float10)local_3c.x * fVar10) +
                    param_2->x + local_30 * fVar11 + local_24 * fVar12;
          pfVar5[1] = local_8 + local_2c * fVar11 + local_20 * fVar12 +
                      (float)((float10)local_3c.y * fVar10);
          pfVar5[2] = fVar2 + local_28 * fVar11 + local_1c * fVar12 +
                      (float)((float10)local_3c.z * fVar10);
          *(undefined1 *)(iVar3 + 0x28 + extraout_EAX[1]) = 0;
          puVar1 = (undefined4 *)(iVar3 + 0x18 + extraout_EAX[1]);
          *puVar1 = param_8;
          puVar1[1] = param_9;
          puVar1[2] = param_10;
          *(float *)(iVar3 + 0x24 + extraout_EAX[1]) = 1.0;
        } while (uVar7 < *(ushort *)((int)extraout_EAX + 0x32));
      }
      entry = (Entry0xd *)((int)&entry->positions[0].x + 1);
    } while ((ushort)entry < (ushort)extraout_EAX[0xc]);
  }
  local_10 = 1.0 / (float)(ushort)extraout_EAX[0xc];
  local_18 = local_10 * local_30;
  local_14 = local_2c * local_10;
  local_10 = local_28 * local_10;
  local_28 = 1.0 / (float)*(ushort *)((int)extraout_EAX + 0x32);
  local_30 = local_28 * local_24;
  local_2c = local_20 * local_28;
  local_28 = local_1c * local_28;
  uVar7 = 0;
  extraout_EAX[0xd] = (uint)SQRT(local_14 * local_14 + local_10 * local_10 + local_18 * local_18);
  extraout_EAX[0xe] = (uint)SQRT(local_2c * local_2c + local_28 * local_28 + local_30 * local_30);
  if ((ushort)extraout_EAX[0xc] != 0) {
    do {
      *(undefined1 *)
       ((uint)uVar7 * (uint)*(ushort *)((int)extraout_EAX + 0x32) * 0x30 + 0x28 + extraout_EAX[1]) =
           1;
      uVar7 = uVar7 + drawType;
    } while (uVar7 < (ushort)extraout_EAX[0xc]);
  }
  *(undefined1 *)
   (((ushort)extraout_EAX[0xc] - 1) * (uint)*(ushort *)((int)extraout_EAX + 0x32) * 0x30 + 0x28 +
   extraout_EAX[1]) = 1;
  uVar6 = 0;
  if (*extraout_EAX != 0) {
    iVar3 = 0;
    do {
      iVar4 = extraout_EAX[1] + iVar3;
      *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(extraout_EAX[1] + iVar3);
      *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(iVar4 + 4);
      *(undefined4 *)(iVar4 + 0x14) = *(undefined4 *)(iVar4 + 8);
      uVar6 = uVar6 + 1;
      iVar3 = iVar3 + 0x30;
    } while (uVar6 < *extraout_EAX);
  }
  entry = (Entry0xd *)0x0;
  if ((short)extraout_EAX[0xc] != 0) {
    do {
      uVar7 = 0;
      if (*(short *)((int)extraout_EAX + 0x32) != 0) {
        do {
          iVar3 = ((uint)entry & 0xffff) * (uint)*(ushort *)((int)extraout_EAX + 0x32) + (uint)uVar7
          ;
          if ((int)((uint)entry & 0xffff) < (int)((ushort)extraout_EAX[0xc] - 1)) {
            uVar6 = extraout_EAX[1];
            iVar9 = (uint)*(ushort *)((int)extraout_EAX + 0x32) + iVar3;
            iVar8 = iVar3 * 0x30 + uVar6;
            iVar4 = iVar9 * 0x30;
            fVar2 = *(float *)(iVar3 * 0x30 + uVar6) - *(float *)(iVar4 + uVar6);
            iVar4 = iVar4 + uVar6;
            fVar11 = *(float *)(iVar8 + 4) - *(float *)(iVar4 + 4);
            fVar12 = *(float *)(iVar8 + 8) - *(float *)(iVar4 + 8);
            fVar2 = SQRT(fVar11 * fVar11 + fVar12 * fVar12 + fVar2 * fVar2);
            if ((char)extraout_EAX[6] == '\0') {
              *(int *)(extraout_EAX[2] * 0x1c + extraout_EAX[5]) = iVar3;
              *(int *)(extraout_EAX[2] * 0x1c + 4 + extraout_EAX[5]) = iVar9;
              *(float *)(extraout_EAX[2] * 0x1c + 0x10 + extraout_EAX[5]) = fVar2;
              *(float *)(extraout_EAX[2] * 0x1c + 0x14 + extraout_EAX[5]) = 1.0 / (fVar2 * fVar2);
              *(float *)(extraout_EAX[2] * 0x1c + 0x18 + extraout_EAX[5]) = fVar2 * fVar2;
              extraout_EAX[2] = extraout_EAX[2] + 1;
            }
          }
          if ((int)(uint)uVar7 < (int)(*(ushort *)((int)extraout_EAX + 0x32) - 1)) {
            uVar6 = extraout_EAX[1];
            iVar8 = iVar3 * 0x30 + uVar6;
            iVar4 = (iVar3 + 1) * 0x30;
            fVar2 = *(float *)(iVar3 * 0x30 + uVar6) - *(float *)(iVar4 + uVar6);
            iVar4 = iVar4 + uVar6;
            fVar11 = *(float *)(iVar8 + 4) - *(float *)(iVar4 + 4);
            fVar12 = *(float *)(iVar8 + 8) - *(float *)(iVar4 + 8);
            fVar2 = SQRT(fVar11 * fVar11 + fVar12 * fVar12 + fVar2 * fVar2);
            if ((char)extraout_EAX[6] == '\0') {
              *(int *)(extraout_EAX[2] * 0x1c + extraout_EAX[5]) = iVar3;
              *(int *)(extraout_EAX[2] * 0x1c + 4 + extraout_EAX[5]) = iVar3 + 1;
              *(float *)(extraout_EAX[2] * 0x1c + 0x10 + extraout_EAX[5]) = fVar2;
              *(float *)(extraout_EAX[2] * 0x1c + 0x14 + extraout_EAX[5]) = 1.0 / (fVar2 * fVar2);
              *(float *)(extraout_EAX[2] * 0x1c + 0x18 + extraout_EAX[5]) = fVar2 * fVar2;
              extraout_EAX[2] = extraout_EAX[2] + 1;
            }
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 < *(ushort *)((int)extraout_EAX + 0x32));
      }
      entry = (Entry0xd *)((int)&entry->positions[0].x + 1);
    } while ((ushort)entry < (ushort)extraout_EAX[0xc]);
  }
  FUN_001024a0();
  extraout_EAX[0x1e] = (uint)(param_2[1].x + param_2->x);
  extraout_EAX[0x1f] = (uint)(param_2[1].y + param_2->y);
  extraout_EAX[0x20] = (uint)(param_2[1].z + param_2->z);
  extraout_EAX[0x1e] = (uint)((float)extraout_EAX[0x1e] + param_2[2].x);
  extraout_EAX[0x1f] = (uint)((float)extraout_EAX[0x1f] + param_2[2].y);
  extraout_EAX[0x20] = (uint)((float)extraout_EAX[0x20] + param_2[2].z);
  extraout_EAX[0x1e] = (uint)((float)extraout_EAX[0x1e] + param_2[3].x);
  extraout_EAX[0x1f] = (uint)((float)extraout_EAX[0x1f] + param_2[3].y);
  extraout_EAX[0x20] = (uint)((float)extraout_EAX[0x20] + param_2[3].z);
  extraout_EAX[0x1e] = (uint)((float)extraout_EAX[0x1e] * 0.25);
  extraout_EAX[0x1f] = (uint)((float)extraout_EAX[0x1f] * 0.25);
  extraout_EAX[0x20] = (uint)((float)extraout_EAX[0x20] * 0.25);
  fVar2 = (float)extraout_EAX[0x1e] - param_2->x;
  fVar11 = (float)extraout_EAX[0x1f] - param_2->y;
  fVar12 = (float)extraout_EAX[0x20] - param_2->z;
  extraout_EAX[0x24] = (uint)SQRT(fVar11 * fVar11 + fVar12 * fVar12 + fVar2 * fVar2);
  extraout_EAX[0x21] = (uint)local_3c.x;
  extraout_EAX[0x22] = (uint)local_3c.y;
  extraout_EAX[0x23] = (uint)local_3c.z;
  extraout_EAX[0x77] = 1;
  return extraout_EAX;
}




void CreateTexturesForModel(TexturesSubresource *param_1,ModelDescriptor *param_2)

{
  uint i;
  TextureDescriptor *tex_descriptor;
  byte bank_index;
  D3DFORMAT format;
  ushort height;
  ushort width;
  
  i = 0;
  if (param_1->numTextures != 0) {
    do {
      Assets::TextureDescriptor::ctor(param_1->textures[i]);
      bank_index = param_1->textures[i]->flag3;
      if ((bank_index != 0) && (bank_index < 0x28)) {
        tex_descriptor = param_1->textures[i];
        bank_index = tex_descriptor->flag3;
        format = tex_descriptor->format;
        height = tex_descriptor->height;
        width = tex_descriptor->width;
        Graphics::ModelTextureBanks[bank_index].someCallback = ModelDescriptor::getTextureByIndex;
        Graphics::ModelTextureBanks[bank_index].modelDescriptor = param_2;
        Graphics::ModelTextureBanks[bank_index].indexInModel = i;
        Graphics::ModelTextureBanks[bank_index].width = width;
        Graphics::ModelTextureBanks[bank_index].height = height;
        Graphics::ModelTextureBanks[bank_index].format = format;
      }
      i = i + 1;
    } while (i < param_1->numTextures);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void FreePhysicalTexture(void *param_1)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  XAPILIB::XPhysicalFree(*(PVOID *)((int)param_1 + 0x14));
  iVar2 = FindHeapOf(param_1);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,param_1);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Graphics::SetTextureStage(DWORD stage,DXTextureInstance *textureStruct)

{
  byte bVar1;
  char cVar2;
  uint64_t uVar3;
  
  bVar1 = textureStruct->field14_0x11;
  if (1 < bVar1) {
    if (textureStruct->field16_0x13 == -1) {
      if ((float)textureStruct->field13_0x10 == 0.0) {
        cVar2 = '\0';
      }
      else {
        uVar3 = float10::to_uint64_t
                          ((float10)g_totalTimeSpentThisSession *
                           (float10)textureStruct->field13_0x10);
        cVar2 = (char)((uVar3 & 0xffffffff) % (ulonglong)bVar1);
      }
      textureStruct->field16_0x13 = cVar2;
    }
    textureStruct->field15_0x12 = textureStruct->field16_0x13;
  }
  textureStruct->field16_0x13 = -1;
  D3D8::D3DDevice_SetTexture
            (stage,(D3DBaseTexture *)
                   (&textureStruct[textureStruct->field15_0x12].field_0x0 +
                   textureStruct->field4_0x4));
  return;
}




Graphics::ColorRect(int rectWidth,int writeSize,int col,uchar colour [4],void *surfaceBase)

{
  int iVar1;
  int surfaceEnd;
  char *ptr;
  
  surfaceEnd = (int)surfaceBase + writeSize;
  if (writeSize < surfaceEnd) {
    iVar1 = col;
    do {
      for (; iVar1 < rectWidth + col; iVar1 = iVar1 + 1) {
        ptr = (char *)(D3D_g_LOCKED_RECT * writeSize + D3D_g_SURFACE_BASE_PTR + iVar1 * 4);
        *ptr = colour[2];
        ptr[2] = colour[0];
        ptr[1] = colour[1];
        ptr[3] = colour[3];
      }
      writeSize = writeSize + 1;
      iVar1 = col;
    } while (writeSize < surfaceEnd);
  }
  return;
}




void UpdateCutsceneAndDraws(void)

{
  Draw2D *pDVar1;
  bool bVar2;
  BOOL BVar3;
  Draw2D *pDVar4;
  float fVar5;
  
  bVar2 = false;
  if (game::doors != (Buffer<Draw2D> *)0x0) {
    pDVar4 = game::doors->head;
    pDVar1 = game::doors->tail;
    if ((((int)pDVar1 - (int)pDVar4) / (int)(uint)game::doors->valueSize != 0) && (pDVar4 < pDVar1))
    {
      do {
        if (pDVar4->active != 0) {
          if ((*(int *)&pDVar4->field_0x14c != 0) &&
             (BVar3 = Game::AllGhoulyBoxesFinishedOpening(), BVar3 != 0)) {
            CloseDoorAndUpdateState(0,*(Cutscene **)&pDVar4->field_0x140);
            *(undefined4 *)&pDVar4->field_0x14c = 0;
          }
          fVar5 = 0.0;
          if (runtime::dx_timer <= 0.0) {
            fVar5 = runtime::DeltaTime * runtime::TimeScale;
          }
          BVar3 = RuncutsceneAndShouldEnd
                            (fVar5,*(Cutscene **)&pDVar4->field_0x140,
                             (Camera *)((*(int *)&pDVar4->field_0x144 != 0) - 1 & 0x4ee2bc));
          if (BVar3 != 0) {
            if ((*(int *)&pDVar4->field_0x144 != 0) && (*(int *)&pDVar4->field_0x150 == 0)) {
              bVar2 = true;
            }
            if ((pDVar4->active != 0) && (pDVar4->active = 0, DAT_004ee320 != 0)) {
              Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
              GlobalCounter2 = GlobalCounter2 + -1;
              g_globalFlagset = g_globalFlagset & ~DoorCutscene;
              DAT_004ee320 = 0;
            }
            FUN_0005bdb0();
          }
          if (*(Cutscene **)&pDVar4->field_0x144 != (Cutscene *)0x0) {
            fVar5 = 0.0;
            if (runtime::dx_timer <= 0.0) {
              fVar5 = runtime::DeltaTime * runtime::TimeScale;
            }
            RuncutsceneAndShouldEnd(fVar5,*(Cutscene **)&pDVar4->field_0x144,&g_doorsProjectionSet);
          }
        }
        pDVar4 = pDVar4 + 1;
      } while (pDVar4 < pDVar1);
      if ((bVar2) && (DAT_004ee31c != 0)) {
        Camera::setActiveCamera(&g_doorsProjectionSet);
        DAT_004ee31c = 0;
      }
    }
  }
  return;
}



undefined4 __fastcall

Graphics::Draw::ComputeMinMaxes(Draw2D *draw,float *min1,float *max1,float *min2,float *max2)

{
  float c1;
  float c3;
  float c2;
  float cx;
  float cy;
  float cz;
  
  cy = (CurrentCameraStruct->pos).y;
  cz = (CurrentCameraStruct->pos).z;
  cx = (CurrentCameraStruct->pos).x;
  c1 = (draw->v1).z * cz + (draw->v1).y * cy + (draw->v1).x * cx + draw->t1;
  c2 = (draw->v2).z * cz + (draw->v2).y * cy + (draw->v2).x * cx + draw->t2;
  c3 = (draw->v3).z * cz + (draw->v3).y * cy + (draw->v3).x * cx + draw->t3;
  if ((((c1 <= draw->min1) && (draw->max1 <= c1)) || ((draw->min1 <= c1 && (c1 <= draw->max1)))) &&
     ((((c2 <= draw->min2 && (draw->max2 <= c2)) || ((draw->min2 <= c2 && (c2 <= draw->max2)))) &&
      (((c3 <= draw->min3 && (draw->max3 <= c3)) || ((draw->min3 <= c3 && (c3 <= draw->max3))))))))
  {
    return 0;
  }
  cz = draw->min3 - c3;
  cx = draw->max3 - c3;
  cy = (&Draw2DDetails)[draw->index].pos_.y;
  if (cz * cz < cx * cx) {
    *min2 = cy + 15.0;
    *max2 = (&Draw2DDetails)[draw->index].pos_.y - 15.0;
    *min1 = (&Draw2DDetails)[draw->index].pos_.z;
    *max1 = *(float *)&(&Draw2DDetails)[draw->index].field5_0x10;
    return 1;
  }
  *min2 = cy - 15.0;
  *max2 = (&Draw2DDetails)[draw->index].pos_.y + 15.0;
  *min1 = *(float *)&(&Draw2DDetails)[draw->index].field5_0x10;
  *max1 = (&Draw2DDetails)[draw->index].pos_.z;
  return 1;
}



// Draws UI in vertical strips, likely for a bar that fills up


void Graphics::Draw::Execute2DDraw(Draw2D *draw,D3DXMATRIX *view,D3DXMATRIX *proj)

{
  int colliding;
  DWORD *push_buf;
  float fVar5;
  D3DMATRIX *pfVar6;
  uint64_t uVar7;
  float min2;
  float min1;
  float max2;
  float max1;
  float left;
  float right;
  D3DXMATRIX mat;
  D3DMATRIX *data_start;
  float fVar1;
  float fVar2;
  
  left = (&Draw2DDetails)[draw->index].pos_.x - 20.0;
  right = (&Draw2DDetails)[draw->index].pos_.x + 20.0;
  colliding = ComputeMinMaxes(draw,&min1,&max1,&min2,&max2);
  if (colliding != 0) {
    D3DX8::D3DXMatrixMultiply(&mat,&draw->modelMat,view);
    D3DX8::D3DXMatrixMultiply(&mat,&mat,proj);
    D3DX8::D3DXMatrixTranspose(&mat,&mat);
                    // Sets constant to mat
    D3D8::D3DDevice_SetVertexShaderConstant4(0x60,(DirectXShaderConstant *)&mat.field1);
    push_buf = D3D8::D3DDevice_BeginPush_4(261);
    fVar2 = right;
    fVar1 = left;
    max1 = max1 - min1;
    draw = (Draw2D *)0x0;
    max2 = max2 - min2;
    *push_buf = 0x417fc;
    push_buf[1] = 8;
    push_buf[2] = 0x44001818;
    data_start = (D3DMATRIX *)(push_buf + 3);
    do {
      pfVar6 = data_start;
      right = max2 * (float)draw + min2;
                    // Compute blend weight?
      uVar7 = float10::to_uint64_t((float10)max1 * (float10)(float)draw + (float10)min1);
      pfVar6->m[0][0] = fVar1;
      pfVar6->m[0][1] = DAT_005462a8;
      pfVar6->m[0][2] = right;
      draw = (Draw2D *)((float)draw + 0.0625);
      fVar5 = (float)((int)uVar7 << 0x18);
      pfVar6->m[0][3] = fVar5;
      pfVar6->m[1][0] = fVar2;
      pfVar6->m[1][1] = DAT_005462a8;
      pfVar6->m[1][2] = right;
      pfVar6->m[1][3] = fVar5;
      pfVar6->m[2][0] = fVar2;
      pfVar6->m[2][1] = FLOAT_00425114;
      pfVar6->m[2][2] = right;
      pfVar6->m[2][3] = fVar5;
      pfVar6->m[3][0] = fVar1;
      pfVar6->m[3][1] = FLOAT_00425114;
      pfVar6->m[3][2] = right;
      pfVar6->m[3][3] = fVar5;
      data_start = pfVar6 + 1;
    } while ((float)draw < 1.0);
    pfVar6[1].m[0][0] = 3.75946e-40;
    *(undefined4 *)((int)pfVar6 + 0x44) = 0;
    D3D8::D3DDevice_EndPush((DWORD *)((int)pfVar6 + 0x48));
  }
  return;
}




void Graphics::DrawUIStuff_(void)

{
  Draw2D *head;
  D3DXMATRIX proj;
  D3DMATRIX view;
  Draw2D *tail;
  
  if (game::doors != (Buffer<Draw2D> *)0x0) {
    tail = game::doors->tail;
    head = game::doors->head;
    if (((int)tail - (int)head) / (int)(uint)game::doors->valueSize != 0) {
      D3D8::D3DDevice_SetModelView((D3DMATRIX *)0x0,(D3DMATRIX *)0x0,(D3DMATRIX *)0x0);
      D3D8::D3DDevice_SetRenderState_CullMode(0);
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_BLENDOP,0x8006);
      RenderState.blendOp = D3DBLENDOP_ADD;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,0x302);
      RenderState.srcBlend = D3DBLEND_SRCALPHA;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,0x303);
      RenderState.destBlend = D3DBLEND_INVSRCALPHA;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,1);
      RenderState.alphaBlendingEnabled = 1;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,1);
      RenderState.alphaTestingEnabled = 1;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHAREF,5);
      RenderState.alphaRef = 5;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
      RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
      RenderState.zWriteEnabled = 1;
      D3D8::D3DDevice_SetRenderState_ZEnable(1);
      D3D8::D3D_g_DeferredTextureState.count1 = 3;
      D3D8::D3D_g_DeferredTextureState.count2 = 3;
      D3D8::D3D_g_DeferredTextureState.field4_0x10 = 2;
      D3D8::D3D_g_DeferredTextureState.field3_0xc = 2;
      GraphicsFlags = GraphicsFlags | 1;
      D3D8::D3D_g_DeferredTextureState.field5_0x14 = 2;
                    // Flat vertex shader (pos, mvp, texcoord only)
      SetVertexShader(19);
      D3D8::D3DDevice_SetPixelShader(PixelShaders[0x13].handle);
      D3D8::D3DDevice_GetTransform(D3DTS_VIEW,(D3DMATRIX *)&view.field1);
      D3D8::D3DDevice_GetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&proj.field1);
      for (; head < tail; head = head + 1) {
        if ((*(int *)(&Draw::Draw2DDetails + head->index) != 0) &&
           ((head->invalidDraw_skipDraw == 0 ||
            ((head->active != 0 && (head->drawIfFalseAnd0xb8 == 0)))))) {
          Draw::Execute2DDraw(head,&view,&proj);
        }
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


Draw2D * FUN_0005c0a0(void)

{
  float fVar1;
  Draw2D *pDVar2;
  Draw2D *pDVar3;
  float *pfVar4;
  float *unaff_EDI;
  float local_4;
  
  pDVar2 = (Draw2D *)0x0;
  local_4 = 999999.9;
  if (game::doors == (Buffer<Draw2D> *)0x0) {
    return pDVar2;
  }
  pDVar3 = game::doors->head;
  if (pDVar3 < game::doors->tail) {
    pfVar4 = (float *)&pDVar3->field_0x14;
    do {
      fVar1 = SQRT((unaff_EDI[2] - *pfVar4) * (unaff_EDI[2] - *pfVar4) +
                   (unaff_EDI[1] - pfVar4[-1]) * (unaff_EDI[1] - pfVar4[-1]) +
                   (*unaff_EDI - pfVar4[-2]) * (*unaff_EDI - pfVar4[-2]));
      if (fVar1 < local_4) {
        pDVar2 = pDVar3;
        local_4 = fVar1;
      }
      pDVar3 = pDVar3 + 1;
      pfVar4 = pfVar4 + 0x55;
    } while (pDVar3 < game::doors->tail);
  }
  return pDVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_0005c7f0(DXTextureInstance *param_1,uint param_2)

{
  int iVar1;
  int in_EAX;
  float *unaff_EBX;
  float *unaff_EDI;
  DirectXShaderConstant local_10;
  
  if ((in_EAX != -1) && (in_EAX < (int)(uint)param_1->field14_0x11)) {
    param_1->field16_0x13 = (char)in_EAX;
  }
  Graphics::SetTextureStage(0,param_1);
  local_10.c1 = (float)(param_2 & 0xff) * 0.003921569;
  local_10.c2 = (float)(param_2 >> 8 & 0xff) * 0.003921569;
  local_10.c3 = (float)(param_2 >> 0x10 & 0xff) * 0.003921569;
  local_10.c4 = (float)(param_2 >> 0x18) * 0.003921569;
  D3D8::D3DDevice_SetPixelShaderConstant(0,&local_10,1);
  iVar1 = *(int *)param_1;
  if (((iVar1 != 0x12) && (iVar1 != 0x1e)) && (iVar1 != 0x3f)) {
    *unaff_EBX = 1.0;
    *unaff_EDI = 1.0;
    return;
  }
  *unaff_EBX = (float)*(ushort *)&param_1->field_0x8;
  *unaff_EDI = (float)*(ushort *)&param_1->field_0xa;
  return;
}




void Graphics::ReconfigureRenderer(void)

{
  FUN_000f6260();
  UnbindAll();
  EnableAlphaBlend();
  FUN_0005e2a0();
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,0);
  RenderState.zWriteEnabled = 0;
  D3D8::D3DDevice_SetRenderState_ZEnable(1);
  UseDefaultPixelC0 = UseDefaultPixelC0 + 1;
  DAT_00509b00 = 1;
  FUN_00156ea0(false);
  return;
}



void DrawMalloced100Value
               (DXTextureInstance *param_1,vec2 *param_2,vec2 *param_3,float param_4,
               TextDrawData *drawData,int param_6)

{
  Graphics::ReconfigureRenderer();
  Graphics::DrawTexture(param_6,0,param_1,param_3,0,param_4,drawData,param_2);
  Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
  if (Graphics::UseDefaultPixelC0 == 0) {
    DAT_00509b00 = 0;
  }
  return;
}




void FUN_0005ce80(DXTextureInstance *param_1,vec2 *param_2,vec2 *param_3)

{
  Graphics::ReconfigureRenderer();
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_BLENDOP,0x8006);
  Graphics::RenderState.blendOp = D3DBLENDOP_ADD;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,1);
  Graphics::RenderState.srcBlend = D3DBLEND_ONE;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,0);
  Graphics::RenderState.destBlend = D3DBLEND_ZERO;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,0);
  Graphics::RenderState.alphaTestingEnabled = 0;
  Graphics::DrawTexture(0,0,param_1,param_3,0,0.0,-1,param_2);
  Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
  if (Graphics::UseDefaultPixelC0 == 0) {
    DAT_00509b00 = 0;
  }
  return;
}




void __thiscall FUN_0005cf90(DXTextureInstance *param_1,float *param_2,uint param_3)

{
  float fVar1;
  int iVar2;
  WeirdTransform *pWVar3;
  int in_EAX;
  undefined4 *unaff_EBX;
  float *unaff_EDI;
  float fVar4;
  FLOAT local_4;
  
  if ((in_EAX != -1) && (in_EAX < (int)(uint)param_1->field14_0x11)) {
    param_1->field16_0x13 = (char)in_EAX;
  }
  Graphics::SetTextureStage(0,param_1);
  fVar4 = 0.0;
  local_4 = 1.0;
  graphics::bone_acc = (WeirdTransform *)&g_affine;
  g_affine.m[0][0] = 1.0;
  g_affine.m[0][1] = 0.0;
  g_affine.m[0][2] = 0.0;
  g_affine.m[0][3] = 0.0;
  g_affine.m[1][0] = 0.0;
  g_affine.m[1][1] = 1.0;
  g_affine.m[1][2] = 0.0;
  g_affine.m[1][3] = 0.0;
  g_affine.m[2][0] = 0.0;
  g_affine.m[2][1] = 0.0;
  g_affine.m[2][2] = 1.0;
  g_affine.m[2][3] = 0.0;
  if (unaff_EDI != (float *)0x0) {
    Graphics::ComputedTextureAffine.m[2][3] = unaff_EDI[2];
    Graphics::ComputedTextureAffine.m[1][3] = unaff_EDI[1];
    Graphics::ComputedTextureAffine.m[0][3] = *unaff_EDI;
    Graphics::ComputedTextureAffine.m[0][0] = 1.0;
    Graphics::ComputedTextureAffine.m[0][1] = 0.0;
    Graphics::ComputedTextureAffine.m[0][2] = 0.0;
    Graphics::ComputedTextureAffine.m[1][0] = 0.0;
    Graphics::ComputedTextureAffine.m[1][1] = 1.0;
    Graphics::ComputedTextureAffine.m[1][2] = 0.0;
    Graphics::ComputedTextureAffine.m[2][0] = 0.0;
    Graphics::ComputedTextureAffine.m[2][1] = 0.0;
    Graphics::ComputedTextureAffine.m[2][2] = 1.0;
    Graphics::leftCombineTransforms(&g_affine,&g_affine,&Graphics::ComputedTextureAffine);
  }
  if (unaff_EBX != (undefined4 *)0x0) {
    FUN_00104160(0x79,unaff_EBX[1]);
    FUN_00104160(0x78,*unaff_EBX);
    FUN_00104160(0x7a,unaff_EBX[2]);
    local_4 = 1.0;
    fVar4 = 0.0;
  }
  pWVar3 = graphics::bone_acc;
  if (param_2 != (float *)0x0) {
    fVar1 = param_2[1];
    (graphics::bone_acc->affine2).m[0][0] = *param_2;
    (pWVar3->affine2).m[0][1] = fVar4;
    (pWVar3->affine2).m[0][2] = fVar4;
    (pWVar3->affine2).m[0][3] = fVar4;
    (pWVar3->affine2).m[1][0] = fVar4;
    (pWVar3->affine2).m[1][1] = local_4;
    (pWVar3->affine2).m[1][2] = fVar4;
    (pWVar3->affine2).m[1][3] = fVar4;
    (pWVar3->affine2).m[2][0] = fVar4;
    (pWVar3->affine2).m[2][1] = fVar4;
    (pWVar3->affine2).m[2][2] = fVar1;
    (pWVar3->affine2).m[2][3] = fVar4;
    Graphics::leftCombineTransforms
              (&graphics::bone_acc->affine1,&graphics::bone_acc->affine1,
               &graphics::bone_acc->affine2);
  }
  iVar2 = *(int *)param_1;
  if (((iVar2 == 0x12) || (iVar2 == 0x1e)) || (param_2 = (float *)local_4, iVar2 == 0x3f)) {
    local_4 = (FLOAT)*(ushort *)&param_1->field_0x8;
    param_2 = (float *)(float)*(ushort *)&param_1->field_0xa;
  }
  Graphics::UpdateWorldMatrix((D3DMATRIX *)graphics::bone_acc);
  D3D8::D3DDevice_SetVertexDataColor
            (3,(((uint)(param_3._2_2_ >> 8) << 8 | param_3 & 0xff) << 8 | param_3 >> 8 & 0xff) << 8
               | param_3._2_2_ & 0xff);
  D3D8::D3DDevice_Begin(D3DPT_QUADLIST);
  D3D8::D3DDevice_SetVertexData2f(9,0.0,0.0);
  D3D8::D3DDevice_SetVertexData4f(-1,-1.0,0.0,-1.0,1.0);
  D3D8::D3DDevice_SetVertexData2f(9,0.0,(FLOAT)param_2);
  D3D8::D3DDevice_SetVertexData4f(-1,-1.0,0.0,1.0,1.0);
  D3D8::D3DDevice_SetVertexData2f(9,local_4,(FLOAT)param_2);
  D3D8::D3DDevice_SetVertexData4f(-1,1.0,0.0,1.0,1.0);
  D3D8::D3DDevice_SetVertexData2f(9,local_4,0.0);
  D3D8::D3DDevice_SetVertexData4f(-1,1.0,0.0,-1.0,1.0);
  D3D8::D3DDevice_End();
  return;
}




void Graphics::useVertexShader0xe(void)

{
  DirectXShaderConstant local_140;
  DirectXShaderConstant local_130;
  DirectXShaderConstant local_120;
  DirectXShaderConstant local_110;
  D3DXMATRIX local_100;
  D3DXMATRIX local_c0;
  D3DXMATRIX local_80;
  D3DXMATRIX local_40;
  
  local_110.c1 = 1.0;
  local_110.c2 = 1.0;
  local_110.c3 = 1.0;
  local_130.c1 = 1.0;
  local_130.c2 = 1.0;
  local_130.c3 = 1.0;
  local_130.c4 = 1.0;
  local_110.c4 = 0.0;
  local_120.c1 = 0.333;
  local_120.c2 = 0.333;
  local_120.c3 = 0.333;
  local_120.c4 = 0.0;
  local_140.c1 = -1.0;
  local_140.c2 = -1.0;
  local_140.c3 = -1.0;
  local_140.c4 = -1.0;
  UpdateViewport2();
  UnbindAll();
  FUN_0005e2a0();
  D3D8::D3DDevice_SetRenderState_StencilEnable(0);
  D3D8::D3DDevice_SetPixelShader(0);
  D3D8::D3DDevice_SetPixelShader(PixelShaders[0xe].handle);
  D3D8::D3DDevice_SetVertexShader(VertexShaders[0xe].shaderHandle);
  if (VertexShaders[0xe].constants != (ShaderConstant *)0x0) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline(0x60,VertexShaders[0xe].constants,0xc);
  }
  D3D8::D3DDevice_GetTransform(D3DTS_WORLD,(D3DMATRIX *)&local_c0.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_VIEW,(D3DMATRIX *)&local_80.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&local_40.field1);
  D3DX8::D3DXMatrixMultiply(&local_100,&local_c0,&local_80);
  D3DX8::D3DXMatrixMultiply(&local_100,&local_100,&local_40);
  D3DX8::D3DXMatrixTranspose(&local_100,&local_100);
  D3D8::D3DDevice_SetVertexShaderConstant4(0x60,(DirectXShaderConstant *)&local_100.field1);
  D3D8::D3DDevice_SetVertexShaderConstant1(0x64,&local_110);
  D3D8::D3DDevice_SetVertexShaderConstant1(0x65,&local_120);
  D3D8::D3DDevice_SetVertexShaderConstant1(0x66,&local_130);
  D3D8::D3DDevice_SetVertexShaderConstant1(0x67,&local_140);
  D3D8::D3DDevice_SetTexture(1,(D3DBaseTexture *)g_someTexture2);
  D3D8::D3DDevice_SetTexture(2,(D3DBaseTexture *)g_someTexture2);
  D3D8::D3DDevice_SetRenderState_TwoSidedLighting(1);
  GraphicsFlags = GraphicsFlags | 0x1000;
  DAT_00181d14 = 0;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SHADEMODE,0x1d01);
  RenderState._36_4_ = 0x1d01;
  D3D8::D3DDevice_SetRenderState_CullMode(0);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,0);
  RenderState.alphaTestingEnabled = 0;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x201);
  RenderState.zCmpFunc = D3DCMP_LESS;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
  RenderState.zWriteEnabled = 1;
  return;
}




void Graphics::DrawVS0xdAND0xe(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  DXTextureInstance *textureStruct;
  DWORD *pDVar4;
  ushort uVar5;
  uint uVar6;
  DWORD *pDVar7;
  float fVar8;
  float local_2c;
  float local_24;
  uint local_20;
  int local_1c;
  
  uVar1 = *(ushort *)(param_1 + 0x30);
  uVar2 = *(ushort *)(param_1 + 0x32);
  if (*(char *)(param_1 + 0x1e4) == '\x01') {
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,1);
    RenderState.srcBlend = D3DBLEND_ONE;
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,1);
    RenderState.destBlend = D3DBLEND_ONE;
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,0);
    RenderState.zWriteEnabled = 0;
  }
  if (*(char *)(param_1 + 0x1eb) == '\0') {
    D3D8::D3DDevice_SetPixelShader(PixelShaders[0xd].handle);
    D3D8::D3DDevice_SetVertexShader(VertexShaders[0xd].shaderHandle);
    if (VertexShaders[0xd].constants != (ShaderConstant *)0x0) {
      D3D8::D3DDevice_SetVertexShaderConstantNotInline(0x60,VertexShaders[0xd].constants,0xc);
    }
  }
  textureStruct = *(DXTextureInstance **)(param_1 + 0xa8);
  if (textureStruct != (DXTextureInstance *)0x0) {
    if (textureStruct->field14_0x11 != 0) {
      textureStruct->field16_0x13 = '\0';
    }
    SetTextureStage(0,textureStruct);
    uVar3 = *(ushort *)(param_1 + 0x32);
    local_24 = 0.0;
    local_20 = 0;
    local_1c = 0;
    if (*(ushort *)(param_1 + 0x30) != 1 && -1 < (int)(*(ushort *)(param_1 + 0x30) - 1)) {
      do {
        fVar8 = local_24 + 1.0 / (float)uVar1;
        local_2c = 0.0;
        pDVar4 = D3D8::D3DDevice_BeginPush_4((uint)uVar3 * 0xc + 5);
        pDVar4[2] = (uint)uVar3 * 0x300000 + 0x40001818;
        *pDVar4 = 0x417fc;
        pDVar4[1] = 6;
        pDVar4 = pDVar4 + 3;
        uVar5 = 0;
        if (*(short *)(param_1 + 0x32) != 0) {
          do {
            uVar6 = (uint)uVar5;
            pDVar7 = (DWORD *)((uVar6 + local_1c) * 0x30 + *(int *)(param_1 + 4));
            *pDVar4 = *pDVar7;
            pDVar4[1] = pDVar7[1];
            pDVar4[2] = pDVar7[2];
            pDVar4[3] = *(DWORD *)(*(int *)(param_1 + 0x2c) + (uVar6 + local_1c) * 4);
            pDVar4[4] = (DWORD)local_24;
            pDVar4[5] = (DWORD)local_2c;
            pDVar7 = (DWORD *)((*(ushort *)(param_1 + 0x32) + uVar6 + local_1c) * 0x30 +
                              *(int *)(param_1 + 4));
            pDVar4[6] = *pDVar7;
            pDVar4[7] = pDVar7[1];
            pDVar4[8] = pDVar7[2];
            pDVar4[9] = *(DWORD *)(*(int *)(param_1 + 0x2c) +
                                  (*(ushort *)(param_1 + 0x32) + uVar6 + local_1c) * 4);
            pDVar4[0xb] = (DWORD)local_2c;
            pDVar4[10] = (DWORD)fVar8;
            pDVar4 = pDVar4 + 0xc;
            uVar5 = uVar5 + 1;
            local_2c = local_2c + 1.0 / (float)uVar2;
          } while (uVar5 < *(ushort *)(param_1 + 0x32));
        }
        *pDVar4 = 0x417fc;
        pDVar4[1] = 0;
        D3D8::D3DDevice_EndPush(pDVar4 + 2);
        local_20 = local_20 + 1;
        local_1c = local_1c + (uint)*(ushort *)(param_1 + 0x32);
        local_24 = fVar8;
      } while ((int)(local_20 & 0xffff) < (int)(*(ushort *)(param_1 + 0x30) - 1));
    }
    if (*(char *)(param_1 + 0x1eb) == '\0') {
      D3D8::D3DDevice_SetPixelShader(PixelShaders[0xe].handle);
      D3D8::D3DDevice_SetVertexShader(VertexShaders[0xe].shaderHandle);
      if (VertexShaders[0xe].constants != (ShaderConstant *)0x0) {
        D3D8::D3DDevice_SetVertexShaderConstantNotInline(0x60,VertexShaders[0xe].constants,0xc);
      }
    }
  }
  return;
}




void Graphics::EnableAlphaBlend(void)

{
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,1);
  RenderState.alphaTestingEnabled = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHAREF,5);
  RenderState.alphaRef = 5;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,1);
  RenderState.alphaBlendingEnabled = 1;
  return;
}




void Graphics::UnbindAll(void)

{
  undefined4 *puVar1;
  UINT StreamNumber;
  DWORD Stage;
  
  Stage = 0;
  D3D8::D3DDevice_SetRenderState_Dxt1NoiseEnable(0);
  GraphicsFlags = GraphicsFlags | 0x2000;
  DAT_00181cf0 = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DITHERENABLE,0);
  RenderState._32_4_ = 0;
  D3D8::D3DDevice_SetRenderState_CullMode(0);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_BLENDOP,0x8006);
  RenderState.blendOp = D3DBLENDOP_ADD;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,0x302);
  RenderState.srcBlend = D3DBLEND_SRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,0x303);
  RenderState.destBlend = D3DBLEND_INVSRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,1);
  RenderState.alphaBlendingEnabled = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHAFUNC,0x204);
  GraphicsFlags = GraphicsFlags | 0x1200;
  RenderState.alphaCmpFunction = D3DCMP_GREATER;
  DAT_00181d08 = 0;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_COLORWRITEENABLE,0x1010101);
  RenderState._40_4_ = 0x1010101;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
  RenderState.zWriteEnabled = 1;
  D3D8::D3DDevice_SetRenderState_ZEnable(1);
  puVar1 = &DAT_001819b0;
  do {
    D3D8::D3DDevice_SetTexture(Stage,(D3DBaseTexture *)0x0);
    puVar1[-4] = 1;
    *puVar1 = 1;
    puVar1[-0xc] = 2;
    GraphicsFlags = GraphicsFlags | 1 << ((byte)Stage & 0x1f) | 0x800U;
    puVar1[-0xd] = 2;
    puVar1 = puVar1 + 0x20;
    Stage = Stage + 1;
  } while ((int)puVar1 < 0x181bb0);
  D3D8::D3DDevice_SetVertexShaderInput(0,0,(STREAMINPUT *)0x0);
  StreamNumber = 0;
  do {
    D3D8::D3DDevice_SetStreamSource(StreamNumber,(D3DVertexBuffer *)0x0,0);
    StreamNumber = StreamNumber + 1;
  } while ((int)StreamNumber < 0x10);
  D3D8::D3DDevice_SetPixelShader(0);
  D3D8::D3DDevice_SetVertexShader(0);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::DrawText(TextDrawData *param_1,vec2 *param_2,vec2 *param_3)

{
  DWORD *pDVar1;
  DirectXShaderConstant local_110;
  D3DXMATRIX local_100;
  D3DXMATRIX local_c0;
  D3DXMATRIX local_80;
  D3DXMATRIX local_40;
  
  local_110.c1 = (float)((uint)param_1 & 0xff) * 0.003921569;
  local_110.c2 = (float)((uint)param_1 >> 8 & 0xff) * 0.003921569;
  local_110.c3 = (float)((uint)param_1 >> 0x10 & 0xff) * 0.003921569;
  local_110.c4 = (float)((uint)param_1 >> 0x18) * 0.003921569;
  D3D8::D3DDevice_SetVertexShader(VertexShaders[0x14].shaderHandle);
  if (VertexShaders[0x14].constants != (ShaderConstant *)0x0) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline(0x60,VertexShaders[0x14].constants,0xc);
  }
  D3D8::D3DDevice_SetPixelShader(PixelShaders[8].handle);
  D3D8::D3DDevice_GetTransform(D3DTS_WORLD,(D3DMATRIX *)&local_80.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_VIEW,(D3DMATRIX *)&local_c0.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&local_40.field1);
  D3DX8::D3DXMatrixMultiply(&local_100,&local_80,&local_c0);
  D3DX8::D3DXMatrixMultiply(&local_100,&local_100,&local_40);
  D3DX8::D3DXMatrixTranspose(&local_100,&local_100);
  D3D8::D3DDevice_SetVertexShaderConstant4(0x60,(DirectXShaderConstant *)&local_100.field1);
  D3D8::D3DDevice_SetVertexShaderConstant1(100,&local_110);
  pDVar1 = D3D8::D3DDevice_BeginPush_4(0x19);
  *pDVar1 = 0x417fc;
  pDVar1[1] = 8;
  pDVar1[2] = 0x40501818;
  pDVar1[3] = (DWORD)param_3->x;
  pDVar1[4] = (DWORD)param_2->y;
  pDVar1[5] = DAT_005462b4;
  pDVar1[6] = DAT_005462b4;
  pDVar1[7] = (DWORD)FLOAT_0042515c;
  pDVar1[8] = (DWORD)param_2->x;
  pDVar1[9] = (DWORD)param_2->y;
  pDVar1[10] = DAT_005462b4;
  pDVar1[0xb] = (DWORD)FLOAT_0042515c;
  pDVar1[0xc] = (DWORD)FLOAT_0042515c;
  pDVar1[0xd] = (DWORD)param_2->x;
  pDVar1[0xe] = (DWORD)param_3->y;
  pDVar1[0xf] = DAT_005462b4;
  pDVar1[0x10] = (DWORD)FLOAT_0042515c;
  pDVar1[0x11] = DAT_005462b4;
  pDVar1[0x12] = (DWORD)param_3->x;
  pDVar1[0x13] = (DWORD)param_3->y;
  pDVar1[0x14] = DAT_005462b4;
  pDVar1[0x15] = DAT_005462b4;
  pDVar1[0x16] = DAT_005462b4;
  pDVar1[0x17] = 0x417fc;
  pDVar1[0x18] = 0;
  D3D8::D3DDevice_EndPush(pDVar1 + 0x19);
  return;
}




void Graphics::PushTextureDraw(DWORD *param_1,uint param_2)

{
  DWORD *pDVar1;
  DWORD *unaff_EBX;
  DWORD *unaff_ESI;
  DWORD *unaff_EDI;
  DirectXShaderConstant local_110;
  D3DXMATRIX local_100;
  D3DXMATRIX local_c0;
  D3DXMATRIX local_80;
  D3DXMATRIX local_40;
  
  local_110.c1 = (float)(param_2 & 0xff) * 0.003921569;
  local_110.c2 = (float)(param_2 >> 8 & 0xff) * 0.003921569;
  local_110.c3 = (float)(param_2 >> 0x10 & 0xff) * 0.003921569;
  local_110.c4 = (float)(param_2 >> 0x18) * 0.003921569;
  D3D8::D3DDevice_SetVertexShader(VertexShaders[0x14].shaderHandle);
  if (VertexShaders[0x14].constants != (ShaderConstant *)0x0) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline(0x60,VertexShaders[0x14].constants,0xc);
  }
  D3D8::D3DDevice_SetPixelShader(PixelShaders[8].handle);
  D3D8::D3DDevice_GetTransform(D3DTS_WORLD,(D3DMATRIX *)&local_80.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_VIEW,(D3DMATRIX *)&local_c0.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&local_40.field1);
  D3DX8::D3DXMatrixMultiply(&local_100,&local_80,&local_c0);
  D3DX8::D3DXMatrixMultiply(&local_100,&local_100,&local_40);
  D3DX8::D3DXMatrixTranspose(&local_100,&local_100);
  D3D8::D3DDevice_SetVertexShaderConstant4(0x60,(DirectXShaderConstant *)&local_100.field1);
  D3D8::D3DDevice_SetVertexShaderConstant1(0x64,&local_110);
  pDVar1 = D3D8::D3DDevice_BeginPush_4(0x19);
  *pDVar1 = 0x417fc;
  pDVar1[1] = 8;
  pDVar1[2] = 0x40501818;
  pDVar1[3] = *param_1;
  pDVar1[4] = unaff_EBX[1];
  pDVar1[5] = DAT_005462bc;
  pDVar1[6] = *unaff_EDI;
  pDVar1[7] = unaff_ESI[1];
  pDVar1[8] = *unaff_EBX;
  pDVar1[9] = unaff_EBX[1];
  pDVar1[10] = DAT_005462bc;
  pDVar1[0xb] = *unaff_ESI;
  pDVar1[0xc] = unaff_ESI[1];
  pDVar1[0xd] = *unaff_EBX;
  pDVar1[0xe] = param_1[1];
  pDVar1[0xf] = DAT_005462bc;
  pDVar1[0x10] = *unaff_ESI;
  pDVar1[0x11] = unaff_EDI[1];
  pDVar1[0x12] = *param_1;
  pDVar1[0x13] = param_1[1];
  pDVar1[0x14] = DAT_005462bc;
  pDVar1[0x15] = *unaff_EDI;
  pDVar1[0x16] = unaff_EDI[1];
  pDVar1[0x17] = 0x417fc;
  pDVar1[0x18] = 0;
  D3D8::D3DDevice_EndPush(pDVar1 + 0x19);
  return;
}



void FUN_0005e950(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                 undefined4 param_5)

{
  int iVar1;
  int unaff_ESI;
  LARGE_INTEGER local_8;
  
  iVar1 = DAT_00504410;
  if ((unaff_ESI != -1) && (iVar1 = unaff_ESI, unaff_ESI == 0)) {
    XAPILIB::QueryPerformanceCounter(&local_8);
    iVar1 = local_8.s.LowPart - g_PERFORMANCE_COUNTER;
  }
  DAT_00504410 = iVar1;
  if (param_4 == 0) {
    FUN_0005ed80(param_3,param_5);
    return;
  }
  FUN_0005ef40(param_2,param_3,param_5);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

void FUN_0005e9f0(uint param_1,float *param_2,float *param_3,TextureDescriptor *param_4,
                 TextureDescriptor *param_5,undefined4 param_6,int param_7,undefined4 param_8,
                 int param_9)

{
  FontDescriptor *pFVar1;
  bool bVar2;
  uint index;
  uint uVar3;
  TextureDescriptor *pTVar4;
  float fVar5;
  vec2 local_20;
  float local_18;
  TextureDescriptor *local_14;
  float local_10;
  TextureDescriptor *local_c;
  vec2 local_8;
  
  index = currentFontType;
  local_8.x = Font::DefaultFontScale.x;
  local_8.y = Font::DefaultFontScale.y;
  if ((Font::DefaultFontScale.x == 0.0) && (Font::DefaultFontScale.y == 0.0)) {
    return;
  }
  pTVar4 = param_4;
  if (((float)param_4 == 0.0) || (bVar2 = true, pTVar4 = param_5, (float)param_5 == 0.0)) {
    bVar2 = false;
  }
  local_20.x = 0.0;
  local_18 = 0.0;
  if (bVar2) {
    FUN_0005f190(param_6,param_5,param_4);
    *param_3 = *param_3 + (float)pTVar4;
    local_c = pTVar4;
  }
  fVar5 = FLOAT_005043e0;
  if (param_9 != 0) {
    local_10 = DAT_00504408 + *param_2;
    pTVar4 = (TextureDescriptor *)(*param_3 + _DAT_0050440c);
    FLOAT_005043e0 = DAT_00504404;
    local_14 = pTVar4;
    FUN_0005e9f0(param_1,&local_10,&local_14,0,0,0,param_7,param_8,0);
  }
  pFVar1 = (&runtime::GloopyFontResource.gloopy)[index];
  uVar3 = param_1 & 0xffff;
  if (((int)pFVar1->startGlyph <= (int)uVar3) && ((int)uVar3 <= (int)pFVar1->endGlyph)) {
    local_14 = pFVar1->dataStart[uVar3 - pFVar1->startGlyph].texHeaders;
    if ((local_14 != (TextureDescriptor *)0x0) &&
       ((ushort)pFVar1->dataStart[uVar3 - pFVar1->startGlyph].field1_0x4 != 0xffffffff))
    goto LAB_0005eb69;
  }
  local_14 = (TextureDescriptor *)Font::NullCharResource;
  param_1 = 0;
LAB_0005eb69:
  FLOAT_005043e0 = fVar5;
  GetText((ushort)param_8,(ushort)param_1,&local_8,&local_20.x,&local_18,index);
  FUN_000608d0();
  fVar5 = FLOAT_005043e0;
  local_20.x = (*param_2 - (float)pTVar4) + g_halfDialogTextOffset_ + local_20.x;
  local_20.y = *param_3 + g_halfDialogTextHeight + local_18;
  local_10 = DAT_005043f0;
  Graphics::ReconfigureRenderer();
  Graphics::DrawTexture(param_7,0,(DXTextureInstance *)local_14,&local_8,0,local_10,fVar5,&local_20)
  ;
  Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
  if (Graphics::UseDefaultPixelC0 == 0) {
    DAT_00509b00 = 0;
  }
  fVar5 = FUN_00060980((ushort)param_8,(ushort)param_1,index,0);
  *param_2 = fVar5 + *param_2;
  if (bVar2) {
    *param_3 = *param_3 - (float)local_c;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

void FUN_0005ec60(float *param_1,float *param_2,int param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  WCHAR WVar1;
  uint fontTableIndex;
  LPWSTR in_EAX;
  undefined4 uVar2;
  undefined2 extraout_var;
  float *extraout_ECX;
  float *pfVar3;
  int iVar5;
  float fVar6;
  float fVar7;
  float local_8;
  float local_4;
  undefined2 uVar4;
  
  fontTableIndex = currentFontType;
  local_4 = *param_2;
  uVar2 = 0;
  iVar5 = 0;
  WVar1 = *in_EAX;
  fVar7 = *param_1;
  do {
    if ((WVar1 == 0) || (param_3 <= iVar5)) {
      *param_1 = fVar7;
      *param_2 = local_4;
      return;
    }
    WVar1 = *in_EAX;
    if (WVar1 == 10) {
      local_4 = (float)(int)(&runtime::GloopyFontResource.gloopy)[fontTableIndex]->lineHeight *
                Font::DefaultFontScale.y + local_4;
      local_8 = *param_1;
      pfVar3 = param_1;
LAB_0005ed3d:
      uVar4 = (undefined2)((uint)pfVar3 >> 0x10);
    }
    else {
      local_8 = fVar7;
      if (WVar1 == 0x20) {
        uVar2 = 0;
        fVar6 = Font::GetGlyph(fontTableIndex,0.0);
        Font::CalculateWStringWidth(in_EAX,0,fontTableIndex,uVar2);
        local_8 = fVar6 + fVar7;
        pfVar3 = extraout_ECX;
        goto LAB_0005ed3d;
      }
      FUN_0005e9f0(WVar1,&local_8,&local_4,param_5,param_6,param_7,
                   *(undefined4 *)(param_4 + iVar5 * 4),uVar2,param_8);
      uVar4 = extraout_var;
    }
    uVar2 = CONCAT22(uVar4,*in_EAX);
    in_EAX = in_EAX + 1;
    iVar5 = iVar5 + 1;
    WVar1 = *in_EAX;
    fVar7 = local_8;
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

void FUN_0005ed80(float *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  WCHAR WVar1;
  uint uVar2;
  uint fontTableIndex;
  LPWSTR in_EAX;
  undefined4 uVar3;
  float *unaff_EBX;
  WCHAR WVar4;
  float fVar5;
  undefined4 uVar6;
  float fVar7;
  float fVar8;
  float local_14;
  float local_10;
  undefined4 *local_c;
  float local_8;
  float local_4;
  
  fontTableIndex = currentFontType;
  fVar7 = *param_1;
  WVar4 = 0;
  local_8 = DAT_00504400;
  if (DAT_00504400 == 0.0) {
    local_8 = g_DXContext.field31_0x54;
  }
  WVar1 = *in_EAX;
  fVar8 = *unaff_EBX;
  local_10 = fVar7;
  local_c = param_3;
  do {
    if (WVar1 == 0) {
      *unaff_EBX = fVar8;
      *param_1 = fVar7;
      return;
    }
    uVar6 = 0;
    uVar3 = param_2;
    if (param_3 != (undefined4 *)0x0) {
      uVar3 = *local_c;
    }
    WVar1 = *in_EAX;
    if (WVar1 == 10) {
      uVar2 = (&runtime::GloopyFontResource.gloopy)[fontTableIndex]->lineHeight;
LAB_0005eed8:
      local_14 = *unaff_EBX;
      local_10 = (float)(int)uVar2 * Font::DefaultFontScale.y + fVar7;
      fVar7 = local_10;
    }
    else {
      local_14 = fVar8;
      if (WVar1 == 0x20) {
        local_4 = Font::GetGlyph(fontTableIndex,0.0);
        fVar5 = Font::CalculateWStringWidth(in_EAX,0,fontTableIndex,uVar6);
        if (local_8 < fVar5 + local_4 + fVar8) {
          uVar2 = (&runtime::GloopyFontResource.gloopy)[fontTableIndex]->lineHeight;
          goto LAB_0005eed8;
        }
        local_14 = local_4 + fVar8;
      }
      else {
        FUN_0005e9f0(WVar1,&local_14,&local_10,param_4,param_5,param_6,uVar3,WVar4,param_7);
        fVar7 = local_10;
        if (local_8 < local_14 - *unaff_EBX) {
          local_10 = (float)(int)(&runtime::GloopyFontResource.gloopy)[fontTableIndex]->lineHeight *
                     Font::DefaultFontScale.y + local_10;
          local_14 = *unaff_EBX;
          fVar7 = local_10;
        }
      }
    }
    WVar4 = *in_EAX;
    in_EAX = in_EAX + 1;
    if (local_c != (undefined4 *)0x0) {
      local_c = local_c + 1;
    }
    WVar1 = *in_EAX;
    fVar8 = local_14;
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

void FUN_0005ef40(float *param_1,float *param_2,undefined4 param_3,float param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,int param_8,undefined4 param_9)

{
  uint fontTableIndex;
  LPWSTR in_EAX;
  int iVar1;
  int iVar2;
  float in_XMM0_Da;
  float fVar3;
  float fVar4;
  float fVar5;
  float local_1c;
  float local_18;
  int local_14;
  LPWSTR local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = (int)param_4;
  fontTableIndex = currentFontType;
  fVar4 = 0.0;
  FUN_00060710();
  local_18 = DAT_00504400;
  if (DAT_00504400 == fVar4) {
    local_18 = g_DXContext.field31_0x54;
  }
  param_4 = *param_1 - in_XMM0_Da * 0.5;
  local_1c = *param_2;
  if (local_18 <= in_XMM0_Da) {
    local_14 = iVar1;
    local_10 = in_EAX;
    fVar3 = Font::CalculateWStringWidth(in_EAX,0,fontTableIndex,fVar4);
    iVar2 = 0;
    fVar5 = fVar3;
    if (*in_EAX != 0) {
      while( true ) {
        fVar3 = fVar5;
        if (*in_EAX == 0x20) {
          in_EAX = in_EAX + 1;
          iVar2 = iVar2 + 1;
          iVar1 = iVar1 + 4;
          fVar4 = Font::GetGlyph(fontTableIndex,fVar4);
          local_4 = Font::CalculateWStringWidth(in_EAX,0,fontTableIndex,0);
          local_4 = local_4 + fVar4;
          fVar3 = local_4 + fVar5;
          if (local_18 < fVar3) {
            local_c = local_1c;
            local_8 = (float)(int)(&runtime::GloopyFontResource.gloopy)[fontTableIndex]->lineHeight
                      * Font::DefaultFontScale.y;
            param_4 = *param_1 - fVar5 * 0.5;
            FUN_0005ec60(&param_4,&local_c,iVar2,local_14,param_5,param_6,param_7,param_9);
            local_1c = local_8 + local_c;
            iVar2 = 0;
            fVar3 = local_4;
            local_14 = iVar1;
            local_10 = in_EAX;
          }
        }
        in_EAX = in_EAX + 1;
        iVar2 = iVar2 + 1;
        if (iVar1 != 0) {
          iVar1 = iVar1 + 4;
        }
        if (*in_EAX == 0) break;
        fVar4 = 0.0;
        fVar5 = fVar3;
      }
    }
    param_4 = *param_1 - fVar3 * 0.5;
    iVar1 = local_14;
    if (param_8 != -1) {
      FUN_000606a0();
      iVar1 = local_14;
    }
  }
  FUN_0005ed80(&local_1c,param_3,iVar1,param_5,param_6,param_7,param_9);
  *param_1 = param_4;
  *param_2 = local_1c;
  return;
}




void DrawAndUpdateUIItems(void)

{
  LoctextValueContext *pLVar1;
  uint uVar2;
  astruct_29 *paVar3;
  uint uVar4;
  
  uVar2 = ((int)LoctextValueBuffer->tail - (int)LoctextValueBuffer->head) /
          (int)(uint)LoctextValueBuffer->valueSize;
  uVar4 = 0;
  paVar3 = LoctextValueBuffer;
  if (uVar2 != 0) {
    do {
      pLVar1 = *(LoctextValueContext **)((int)&paVar3->head->field0_0x0 + paVar3->valueSize * uVar4)
      ;
      if ((pLVar1->buffer != (Buffer<> *)0x0) && (((uint)pLVar1->callback & g_globalFlagset) == 0))
      {
        FUN_0005fb80(pLVar1);
        paVar3 = LoctextValueBuffer;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar2);
  }
  return;
}



void runtime::AllocateForLoctext_
               (uint param_1,undefined4 param_2,void *callback,LoctextValueContext **lvCtx)

{
  LoctextValueContext *pLVar2;
  Buffer<> *buf;
  astruct_55 *puVar1;
  
  pLVar2 = malloc_(0x30);
  *lvCtx = pLVar2;
  buf = malloc_(0x48f0);
  buf->valueSize = 0x1238;
  buf->capacity = 4;
  buf->head = buf->values;
  buf->tail = buf->values;
  buf->end = (LoctextValue *)(buf + 1);
  (*lvCtx)->buffer = buf;
  (*lvCtx)->fontIndex = param_1;
  *(undefined4 *)&(*lvCtx)->field_0x8 = param_2;
  (*lvCtx)->callback = callback;
  ((*lvCtx)->somePos).x = 0.0;
  ((*lvCtx)->somePos).y = 0.0;
  (*lvCtx)->maybeState = 0;
  (*lvCtx)->lineWidth = 0.0;
  (*lvCtx)->field10_0x20 = 0.5;
  *(undefined4 *)&(*lvCtx)->field_0x24 = 1;
  (*lvCtx)->field15_0x28 = 2.0;
  (*lvCtx)->field16_0x2c = 2.0;
  if (LoctextValueBuffer->tail == LoctextValueBuffer->end) {
    LoctextValueBuffer = (astruct_29 *)ExtendArray((Buffer *)LoctextValueBuffer);
  }
  puVar1 = LoctextValueBuffer->tail;
  LoctextValueBuffer->tail =
       (astruct_55 *)((int)&puVar1->field0_0x0 + (uint)LoctextValueBuffer->valueSize);
  puVar1->field0_0x0 = *lvCtx;
  return;
}




void FUN_00061ee0(uint vertexShaderIndex,uint colour,int pixelShaderIndex)

{
  vec4 local_10;
  
  D3D8::D3DDevice_SetTexture(2,(D3DBaseTexture *)0x0);
  D3D8::D3DDevice_SetTexture(3,(D3DBaseTexture *)0x0);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_COLORWRITEENABLE,0x1010101);
  Graphics::RenderState._40_4_ = 0x1010101;
  D3D8::D3DDevice_SetRenderState_ZEnable(0);
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 1;
  DAT_0018199c = 4;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_BLENDOP,0x8006);
  Graphics::RenderState.blendOp = D3DBLENDOP_ADD;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,0x302);
  Graphics::RenderState.srcBlend = D3DBLEND_SRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,0x303);
  Graphics::RenderState.destBlend = D3DBLEND_INVSRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,1);
  Graphics::RenderState.alphaBlendingEnabled = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_STENCILZFAIL,0x1e00);
  Graphics::RenderState._44_4_ = 0x1e00;
  D3D8::D3DDevice_SetRenderState_StencilFail(0x1e00);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_STENCILPASS,0x1e00);
  Graphics::RenderState._48_4_ = 0x1e00;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_STENCILFUNC,0x202);
  Graphics::RenderState._52_4_ = 0x202;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_STENCILMASK,0xffffffff);
  Graphics::RenderState._60_4_ = 0xffffffff;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_STENCILREF,0);
  Graphics::RenderState._56_4_ = 0;
  D3D8::D3DDevice_SetVertexShader(Graphics::VertexShaders[vertexShaderIndex].shaderHandle);
  if (Graphics::VertexShaders[vertexShaderIndex].constants != (ShaderConstant *)0x0) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline
              (0x60,Graphics::VertexShaders[vertexShaderIndex].constants,0xc);
  }
  D3D8::D3DDevice_SetTexture(0,g_d3dBaseTexture);
  D3D8::D3DDevice_SetPixelShader(Graphics::PixelShaders[pixelShaderIndex].handle);
  local_10.x = (float)(colour & 0xff) * 0.003921569;
  local_10.y = (float)(colour >> 8 & 0xff) * 0.003921569;
  local_10.z = (float)(colour >> 0x10 & 0xff) * 0.003921569;
  local_10.w = (float)(colour >> 0x18) * 0.003921569;
  D3D8::D3DDevice_SetPixelShaderConstant(0,(DirectXShaderConstant *)&local_10,1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Graphics::Create256Texture(void)

{
  undefined1 local_40 [4];
  void *local_3c;
  undefined4 local_38 [5];
  UINT local_24;
  UINT local_20;
  D3DSURFACE_DESC backbuf_desc;
  
  g_tex256x256 = D3D8::D3DDevice_CreateTexture2(0x100,0x100,1,1,1,D3DFMT_A8R8G8B8,D3DRTYPE_TEXTURE);
  g_tex256x256_surface_level = D3D8::D3DTexture_GetSurfaceLevel2((D3DTexture *)g_tex256x256,0);
  g_backBuffer = D3D8::D3DDevice_GetBackBuffer2(0);
  D3D8::D3DSurface_GetDesc(g_backBuffer,&backbuf_desc);
  DAT_005047d8 = CreateTextureHeader((ushort)backbuf_desc.Width,(ushort)backbuf_desc.Height,'\x01',
                                     backbuf_desc.Format,(void *)0x0);
  g_d3dBaseTexture =
       (D3DTexture *)
       ((int)&DAT_005047d8->format +
       DAT_005047d8->d3dResourceOffset + (uint)DAT_005047d8->flag2 * 0x14);
  SomeDepthStencil = D3D8::D3DTexture_GetSurfaceLevel2(g_d3dBaseTexture,0);
  if (SomeDepthStencil != (D3DSurface *)0x0) {
    D3D8::D3DResource_Release((D3DResource *)g_backBuffer);
    g_depthStencilSurface = D3D8::D3DDevice_GetDepthStencilSurface2();
    if (g_depthStencilSurface != (D3DSurface *)0x0) {
      D3D8::D3DSurface_GetDesc(g_depthStencilSurface,local_38);
      ZStencil = (void *)FUN_00175c90(local_24,local_20,0,local_38[0]);
      if (ZStencil != (void *)0x0) {
        XGRAPHC::XGSetTextureHeader
                  (local_24,local_20,1,0,D3DFMT_LIN_A8R8G8B8,D3DPOOL_DEFAULT,&D3DTexture_005047e8,
                   *(UINT *)((int)ZStencil + 4),0);
        D3D8::D3DSurface_LockRect(ZStencil,local_40,(void *)0x0,0x80);
        DAT_005047e4 = CreateTextureHeader((ushort)backbuf_desc.Width,(ushort)backbuf_desc.Height,
                                           '\x01',D3DFMT_LIN_A8R8G8B8,local_3c);
        D3D8::D3DResource_Release((D3DResource *)g_depthStencilSurface);
        _DAT_00504800 = 0;
        DoneReadingLoad = 0;
      }
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void __thiscall FUN_00062580(DXTextureInstance *param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  DWORD *pDVar2;
  DirectXShaderConstant local_10;
  
  iVar1 = FUN_000623c0(param_2,3);
  if (iVar1 != 0) {
    if (param_1 != (DXTextureInstance *)0x0) {
      Graphics::SetTextureStage(1,param_1);
    }
    local_10.c1 = (float)(param_3 & 0xff) * 0.003921569;
    local_10.c2 = (float)(param_3 >> 8 & 0xff) * 0.003921569;
    local_10.c3 = (float)(param_3 >> 0x10 & 0xff) * 0.003921569;
    local_10.c4 = (float)(param_3 >> 0x18) * 0.003921569;
    D3D8::D3DDevice_SetPixelShaderConstant(1,&local_10,1);
    pDVar2 = D3D8::D3DDevice_BeginPush_4(0x15);
    *pDVar2 = 0x417fc;
    pDVar2[1] = 8;
    pDVar2[2] = 0x40401818;
    pDVar2[3] = DAT_00504804;
    pDVar2[4] = DAT_00504808;
    pDVar2[5] = DAT_0042516c;
    pDVar2[6] = DAT_00425170;
    pDVar2[7] = DAT_0050480c;
    pDVar2[8] = DAT_00504810;
    pDVar2[9] = DAT_00425174;
    pDVar2[10] = (DWORD)FLOAT_00425178;
    pDVar2[0xb] = DAT_00504814;
    pDVar2[0xc] = DAT_00504818;
    pDVar2[0xd] = (DWORD)FLOAT_0042517c;
    pDVar2[0xe] = (DWORD)FLOAT_00425180;
    pDVar2[0xf] = DAT_0050481c;
    pDVar2[0x10] = DAT_00504820;
    pDVar2[0x11] = (DWORD)FLOAT_00425184;
    pDVar2[0x12] = DAT_00425188;
    pDVar2[0x13] = 0x417fc;
    pDVar2[0x14] = 0;
    D3D8::D3DDevice_EndPush(pDVar2 + 0x15);
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 1;
    DAT_0018199c = 0;
    D3D8::D3DDevice_SetRenderState_ZEnable(1);
    D3D8::D3DDevice_SetRenderState_StencilEnable(0);
    D3D8::D3DDevice_SetVertexShader(0);
    D3D8::D3DDevice_SetPixelShader(0);
    D3D8::D3DDevice_SetTexture(0,(D3DBaseTexture *)0x0);
    D3D8::D3DDevice_SetTexture(1,(D3DBaseTexture *)0x0);
    D3D8::D3DDevice_SetTexture(2,(D3DBaseTexture *)0x0);
    D3D8::D3DDevice_SetTexture(3,(D3DBaseTexture *)0x0);
  }
  return;
}



void FUN_00062750(DXTextureInstance *texture1,DXTextureInstance *texture2,undefined4 param_3,
                 uint colour1,uint colour2)

{
  int iVar1;
  DWORD *pDVar2;
  DirectXShaderConstant local_20;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = FUN_000623c0(param_3,4);
  if (iVar1 != 0) {
    if (texture1 != (DXTextureInstance *)0x0) {
      Graphics::SetTextureStage(1,texture1);
    }
    if (texture2 != (DXTextureInstance *)0x0) {
      Graphics::SetTextureStage(2,texture2);
    }
                    // Sets colours
    local_20.c1 = (float)(colour1 & 0xff) * 0.003921569;
    local_20.c2 = (float)(colour1 >> 8 & 0xff) * 0.003921569;
    local_20.c3 = (float)(colour1 >> 0x10 & 0xff) * 0.003921569;
    local_20.c4 = (float)(colour1 >> 0x18) * 0.003921569;
    local_10 = (float)(colour2 & 0xff) * 0.003921569;
    local_c = (float)(colour2 >> 8 & 0xff) * 0.003921569;
    local_8 = (float)(colour2 >> 0x10 & 0xff) * 0.003921569;
    local_4 = (float)(colour2 >> 0x18) * 0.003921569;
    D3D8::D3DDevice_SetPixelShaderConstant(1,&local_20,2);
    pDVar2 = D3D8::D3DDevice_BeginPush_4(0x1d);
    *pDVar2 = 0x417fc;
    pDVar2[1] = 8;
    pDVar2[2] = 0x40601818;
    pDVar2[3] = DAT_00504804;
    pDVar2[4] = DAT_00504808;
    pDVar2[5] = DAT_0042518c;
    pDVar2[6] = DAT_00425190;
    pDVar2[7] = DAT_0042518c;
    pDVar2[8] = DAT_00425190;
    pDVar2[9] = DAT_0050480c;
    pDVar2[10] = DAT_00504810;
    pDVar2[0xb] = DAT_00425194;
    pDVar2[0xc] = (DWORD)FLOAT_00425198;
    pDVar2[0xd] = DAT_00425194;
    pDVar2[0xe] = (DWORD)FLOAT_00425198;
    pDVar2[0xf] = DAT_00504814;
    pDVar2[0x10] = DAT_00504818;
    pDVar2[0x11] = (DWORD)FLOAT_0042519c;
    pDVar2[0x12] = (DWORD)FLOAT_004251a0;
    pDVar2[0x13] = (DWORD)FLOAT_0042519c;
    pDVar2[0x14] = (DWORD)FLOAT_004251a0;
    pDVar2[0x15] = DAT_0050481c;
    pDVar2[0x16] = DAT_00504820;
    pDVar2[0x17] = (DWORD)FLOAT_004251a4;
    pDVar2[0x18] = DAT_004251a8;
    pDVar2[0x19] = (DWORD)FLOAT_004251a4;
    pDVar2[0x1a] = DAT_004251a8;
    pDVar2[0x1b] = 0x417fc;
    pDVar2[0x1c] = 0;
    D3D8::D3DDevice_EndPush(pDVar2 + 0x1d);
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 1;
    DAT_0018199c = 0;
    D3D8::D3DDevice_SetRenderState_ZEnable(1);
    D3D8::D3DDevice_SetRenderState_StencilEnable(0);
    D3D8::D3DDevice_SetVertexShader(0);
    D3D8::D3DDevice_SetPixelShader(0);
    D3D8::D3DDevice_SetTexture(0,(D3DBaseTexture *)0x0);
    D3D8::D3DDevice_SetTexture(1,(D3DBaseTexture *)0x0);
    D3D8::D3DDevice_SetTexture(2,(D3DBaseTexture *)0x0);
    D3D8::D3DDevice_SetTexture(3,(D3DBaseTexture *)0x0);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_000629d0(D3DTexture *tex,D3DTexture *fallback)

{
  g_backBuffer = D3D8::D3DDevice_GetBackBuffer2(0);
  g_depthStencilSurface = D3D8::D3DDevice_GetDepthStencilSurface2();
  if (tex == (D3DTexture *)0x0) {
    Graphics::ZStencil = D3D8::D3DTexture_GetSurfaceLevel2(fallback,0);
    D3D8::D3DDevice_SetRenderTarget(g_backBuffer,DAT_00504840);
    _DAT_00504834 = (D3DTexture *)0x0;
    _DAT_0050483c = fallback;
    _DAT_00504800 = 1;
    return;
  }
  DAT_00504838 = D3D8::D3DTexture_GetSurfaceLevel2(tex,0);
  if (fallback != (D3DTexture *)0x0) {
    DAT_00504840 = D3D8::D3DTexture_GetSurfaceLevel2(fallback,0);
    D3D8::D3DDevice_SetRenderTarget(DAT_00504838,DAT_00504840);
    _DAT_00504834 = tex;
    _DAT_0050483c = fallback;
    _DAT_00504800 = 1;
    return;
  }
  D3D8::D3DDevice_SetRenderTarget(DAT_00504838,g_depthStencilSurface);
  _DAT_00504834 = tex;
  _DAT_0050483c = (D3DTexture *)0x0;
  _DAT_00504800 = 1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


PIXEL_SHADER CreatePixelShader(void)

{
  int i;
  D3DPIXELSHADERDEF *dword_i;
  PIXEL_SHADER shader;
  D3DPIXELSHADERDEF local_f8;
  
  dword_i = &local_f8;
                    // Clear pixel shader
  for (i = uVar1; i != 0; i = i + -1) {
    dword_i->PSAlphaInputs[0] = 0;
    dword_i = (D3DPIXELSHADERDEF *)(dword_i->PSAlphaInputs + 1);
  }
  local_f8.PSTextureModes = 0x54421;
  local_f8.PSInputTexture = 0x110000;
  local_f8.PSDotMapping = 0x440;
  local_f8.PSCombinerCount = 1;
  local_f8.PSFinalCombinerInputsABCD = 0x20080000;
  local_f8.PSFinalCombinerInputsEFG = 0x1800;
  D3D8::D3DDevice_CreatePixelShader(&local_f8,&shader);
  return shader;
}




void Graphics::CompilePixelShaders(void)

{
  uint uVar1;
  HRESULT HVar2;
  OffsetPixelShader ppuVar3;
  XGBuffer *compiled_shader;
  uint handle;
  XGBuffer *pXStack_8;
  XGBuffer *pXStack_4;
  
  ppuVar3 = &PixelShaders[0].constants;
  do {
    if (ADJ(ppuVar3)->constants == (code *)0x0) {
      HVar2 = XGRAPHICS::XGAssembleShader
                        ((LPCSTR)0x0,ADJ(ppuVar3).data,ADJ(ppuVar3)->size,0,(XGBuffer **)0x0,
                         &compiled_shader,&pXStack_4,&pXStack_8,(SASM_ResolverCallback *)0x0,
                         (LPVOID)0x0,(LPDWORD)0x0);
      if (HVar2 == 0) {
        D3D8::D3DDevice_CreatePixelShader(compiled_shader->pData,&handle);
        uVar1 = handle;
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = (*ADJ(ppuVar3)->constants)();
    }
    ADJ(ppuVar3)->handle = uVar1;
    ppuVar3 = ppuVar3 + 4;
  } while ((int)ppuVar3 < 0x425f28);
  return;
}



void FUN_00064030(D3DXMATRIX *view,void *this,D3DXMATRIX *proj,float *param_4,float *param_5,
                 float param_6)

{
  uint uVar1;
  uint uVar2;
  float *pfVar3;
  float *pfVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  int i;
  ShaderConstant *constant;
  vec3 local_10c;
  vec4 constantt;
  D3DXMATRIX invView;
  D3DXMATRIX invProj;
  float local_70 [5];
  float local_5c [22];
  
  D3DXMATRIX::getInverse(&invView,0,view);
  D3DXMATRIX::getInverse(&invProj,0,proj);
  pfVar3 = local_70 + 1;
  constant = ShaderConstant_ARRAY_002ff6e8;
  i = 8;
  do {
    constantt.x = constant->field0_0x0;
    constantt.y = constant->field1_0x4;
    constantt.z = constant->field2_0x8;
    constantt.w = constant->field3_0xc;
    multMatWithVec4(&constantt,&constantt,&invProj);
    multMatWithVec4(&constantt,&constantt,&invView);
    fVar6 = 1.0 / constantt.w;
    pfVar3[-1] = fVar6 * constantt.x;
    *pfVar3 = fVar6 * constantt.y;
    pfVar3[1] = fVar6 * constantt.z;
    constant = constant + 1;
    pfVar3 = pfVar3 + 3;
    i = i + -1;
  } while (i != 0);
  local_10c.x = *param_5 - *param_4;
  local_10c.y = param_5[1] - param_4[1];
  local_10c.z = param_5[2] - param_4[2];
  fVar6 = *param_5;
  fVar9 = param_5[1];
  fVar12 = param_5[2];
  D3DX8::D3DXVec3Normalize(&local_10c,&local_10c);
  fVar13 = local_10c.z * 100.0;
  fVar7 = local_10c.x * 100.0;
  fVar11 = local_10c.y * 100.0;
  *(float *)((int)this + 0x98) = 0.0 - local_10c.x;
  *(float *)((int)this + 0x9c) = 0.0 - local_10c.y;
  fVar8 = 0.0 - local_10c.z;
  *(float *)((int)this + 0xa0) = fVar8;
  fVar10 = *(float *)((int)this + 0x9c);
  *(float *)((int)this + 0xa4) =
       (fVar10 * (local_10c.y * param_6 + fVar9) + (local_10c.z * param_6 + fVar12) * fVar8 +
       *(float *)((int)this + 0x98) * (local_10c.x * param_6 + fVar6)) /
       (*(float *)((int)this + 0x98) * *(float *)((int)this + 0x98) + fVar10 * fVar10 +
       fVar8 * fVar8);
  local_10c.x = 0.0 - (0.0 - local_10c.x);
  *(float *)((int)this + 0x88) = local_10c.x;
  local_10c.y = 0.0 - (0.0 - local_10c.y);
  *(float *)((int)this + 0x8c) = local_10c.y;
  local_10c.z = 0.0 - fVar8;
  *(float *)((int)this + 0x90) = local_10c.z;
  fVar10 = *(float *)((int)this + 0x88);
  fVar8 = *(float *)((int)this + 0x8c);
  *(float *)((int)this + 0x94) =
       (fVar8 * (fVar11 + fVar9) + fVar10 * (fVar7 + fVar6) + (fVar13 + fVar12) * local_10c.z) /
       (fVar10 * fVar10 + fVar8 * fVar8 + local_10c.z * local_10c.z);
  uVar2 = 3;
  pfVar3 = local_70 + 5;
  pfVar4 = (float *)((int)this + 0x4c);
  do {
    uVar1 = uVar2 & 7;
    constantt.x = pfVar3[-2] - local_70[uVar1 * 3];
    fVar6 = (*pfVar3 - local_70[uVar1 * 3 + 2]) * (pfVar3[-1] - pfVar3[-4]) -
            (pfVar3[-1] - local_70[uVar1 * 3 + 1]) * (*pfVar3 - pfVar3[-3]);
    fVar9 = (*pfVar3 - pfVar3[-3]) * constantt.x -
            (*pfVar3 - local_70[uVar1 * 3 + 2]) * (pfVar3[-2] - pfVar3[-5]);
    fVar12 = (pfVar3[-1] - local_70[uVar1 * 3 + 1]) * (pfVar3[-2] - pfVar3[-5]) -
             (pfVar3[-1] - pfVar3[-4]) * constantt.x;
    fVar10 = fVar12 * fVar12 + fVar9 * fVar9 + fVar6 * fVar6;
    if (fVar10 != 0.0) {
      fVar5 = (float10)invsqrt(fVar10);
      fVar6 = (float)((float10)fVar6 * fVar5);
      fVar9 = (float)((float10)fVar9 * fVar5);
      fVar12 = (float)((float10)fVar12 * fVar5);
    }
    fVar10 = pfVar3[-1];
    pfVar4[-1] = fVar6;
    *pfVar4 = fVar9;
    fVar6 = *pfVar3;
    pfVar4[1] = fVar12;
    fVar9 = *pfVar4;
    fVar8 = pfVar4[-1];
    pfVar4[2] = (fVar6 * fVar12 + fVar10 * fVar9 + pfVar3[-2] * fVar8) /
                (fVar12 * fVar12 + fVar8 * fVar8 + fVar9 * fVar9);
    uVar2 = uVar2 + 2;
    pfVar3 = pfVar3 + 6;
    pfVar4 = pfVar4 + 4;
  } while (uVar2 < 10);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::UseBurnupRenderer(void)

{
  ShaderConstant *pConstantData;
  DirectXShaderConstant local_130;
  DirectXShaderConstant local_120;
  D3DXMATRIX local_110;
  D3DXMATRIX local_d0;
  D3DXMATRIX local_90;
  D3DXMATRIX local_50;
  
  local_130.c1 = 1.0;
  local_130.c2 = 1.0;
  local_130.c3 = 1.0;
  local_130.c4 = 1.0;
  local_120.c1 = 0.0;
  local_120.c2 = 0.0;
  local_120.c3 = 0.0;
  local_120.c4 = 0.0;
  UnbindAll();
  FUN_0005e2a0();
  EnableAlphaBlend();
  D3D8::D3DDevice_SetRenderState_MultiSampleAntiAlias(0);
  D3D8::D3DDevice_SetRenderState_MultiSampleMode(1);
  D3D8::D3DDevice_SetRenderState_MultiSampleRenderTargetMode(1);
  if (DAT_00504940 == 0) {
    D3D8::D3DDevice_SetPixelShader(PixelShaders[8].handle);
    D3D8::D3DDevice_SetVertexShader(VertexShaders[7].shaderHandle);
    pConstantData = VertexShaders[7].constants;
  }
  else {
    D3D8::D3DDevice_SetPixelShader(PixelShaders[9].handle);
    D3D8::D3DDevice_SetVertexShader(VertexShaders[8].shaderHandle);
    pConstantData = VertexShaders[8].constants;
  }
  if (pConstantData != (ShaderConstant *)0x0) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline(0x60,pConstantData,0xc);
  }
  GraphicsFlags = GraphicsFlags | 0x801;
  DAT_001819a0 = 4;
  DAT_001819a8 = 2;
  _DAT_001819ac = 0;
  D3D8::D3D_g_DeferredTextureState.count1 = 4;
  D3D8::D3D_g_DeferredTextureState.count2 = 4;
  D3D8::D3DDevice_SetTextureState_BorderColor(0,0);
  GraphicsFlags = GraphicsFlags | 1;
  D3D8::D3D_g_DeferredTextureState.field4_0x10 = 2;
  D3D8::D3D_g_DeferredTextureState.field3_0xc = 2;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_ZBias(4);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,0);
  RenderState.zWriteEnabled = 0;
  D3D8::D3DDevice_SetRenderState_CullMode(0x900);
  D3D8::D3DDevice_SetRenderState_StencilEnable(0);
  D3D8::D3DDevice_GetTransform(D3DTS_WORLD,(D3DMATRIX *)&local_d0.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_VIEW,(D3DMATRIX *)&local_90.field1);
  D3D8::D3DDevice_GetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&local_50.field1);
  Maths::MultiplyMat4s(&local_110,&local_d0,&local_90);
  Maths::MultiplyMat4s(&local_110,&local_110,&local_50);
  CopyMat4IntoShaderConstant((ShaderConstant *)&local_110.field1,&local_110);
  D3D8::D3DDevice_SetVertexShaderConstant4(0x60,(DirectXShaderConstant *)&local_110.field1);
  D3D8::D3DDevice_SetVertexShaderConstant1(0x6a,&local_130);
  D3D8::D3DDevice_SetVertexShaderConstant1(0x73,&local_120);
  D3DXMATRIX_00504880.m[3][2] = 0.0;
  D3DXMATRIX_00504880.m[3][1] = 0.0;
  D3DXMATRIX_00504880.m[3][0] = 0.0;
  D3DXMATRIX_00504880.m[2][3] = 0.0;
  D3DXMATRIX_00504880.m[2][1] = 0.0;
  D3DXMATRIX_00504880.m[2][0] = 0.0;
  D3DXMATRIX_00504880.m[1][3] = 0.0;
  D3DXMATRIX_00504880.m[1][2] = 0.0;
  D3DXMATRIX_00504880.m[1][0] = 0.0;
  D3DXMATRIX_00504880.m[0][3] = 0.0;
  D3DXMATRIX_00504880.m[0][2] = 0.0;
  D3DXMATRIX_00504880.m[0][1] = 0.0;
  D3DXMATRIX_00504880.m[3][3] = 1.0;
  D3DXMATRIX_00504880.m[2][2] = 1.0;
  D3DXMATRIX_00504880.m[0][0] = 0.5;
  D3DXMATRIX_00504880.m[1][1] = -0.5;
  D3DXMATRIX_005048c0.m[3][2] = 0.0;
  D3DXMATRIX_005048c0.m[3][1] = 0.0;
  D3DXMATRIX_005048c0.m[3][0] = 0.0;
  D3DXMATRIX_005048c0.m[2][3] = 0.0;
  D3DXMATRIX_005048c0.m[1][3] = 0.0;
  D3DXMATRIX_005048c0.m[1][2] = 0.0;
  D3DXMATRIX_005048c0.m[1][0] = 0.0;
  D3DXMATRIX_005048c0.m[0][3] = 0.0;
  D3DXMATRIX_005048c0.m[0][2] = 0.0;
  D3DXMATRIX_005048c0.m[0][1] = 0.0;
  D3DXMATRIX_005048c0.m[3][3] = 1.0;
  D3DXMATRIX_005048c0.m[2][2] = 1.0;
  D3DXMATRIX_005048c0.m[1][1] = 1.0;
  D3DXMATRIX_005048c0.m[0][0] = 1.0;
  D3DXMATRIX_005048c0.m[2][0] = 0.5;
  D3DXMATRIX_005048c0.m[2][1] = 0.5;
  Maths::MultiplyMat4s(&BuildBGSubres0x12Matrix,&D3DXMATRIX_00504880,&D3DXMATRIX_005048c0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

int __fastcall
DrawSubresource0x12(TilesSubresource *subres0x12,vec3 *someVOut,vec3 *param_3,D3DBaseTexture *tex,
                   float param_5,uint param_6,char param_7)

{
  uint *pStreamData;
  Model *pMVar1;
  ModelTile *pMVar2;
  int in_EAX;
  int iVar3;
  BOOL BVar4;
  D3DVertexBuffer *pStreamData_00;
  int iVar5;
  ModelDescriptor *pMVar6;
  int iVar7;
  float *pfVar8;
  UINT UVar9;
  float10 fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float local_440;
  float local_438;
  char local_431;
  int local_430;
  int local_42c;
  int local_428;
  int local_424;
  int local_420;
  float local_41c;
  float local_418;
  float local_414;
  int local_410;
  int local_40c;
  int local_408;
  int local_404;
  DirectXShaderConstant local_400;
  DirectXShaderConstant local_3f0;
  float local_3e0;
  float local_3dc;
  float local_3d8;
  vec3 local_3d4;
  vec3 local_3c8;
  undefined4 local_3bc;
  float local_3b8;
  undefined4 local_3b4;
  DirectXShaderConstant local_3b0;
  DirectXShaderConstant local_3a0;
  DirectXShaderConstant local_390;
  ShaderConstant constant [4];
  D3DXMATRIX someMat;
  D3DXMATRIX local_300;
  D3DXMATRIX viewmat;
  D3DXMATRIX local_280;
  D3DXMATRIX local_240;
  D3DXMATRIX local_200;
  D3DXMATRIX proj;
  D3DXMATRIX local_180;
  D3DXMATRIX local_140;
  D3DXMATRIX local_100;
  GraphicsCamera local_b8;
  
  local_3bc = 0;
  local_3b8 = 1.0;
  local_3b4 = 0;
  local_404 = 0;
  if (subres0x12 != (TilesSubresource *)0x0) {
    BuildViewMatrix(&viewmat,param_3,someVOut,&local_3bc);
    fVar10 = (float10)getfovfy();
    BuildProjectionMatrix(&proj,(float)(fVar10 + fVar10),1.0,0.1,100.1);
    Maths::MultiplyMat4s(&someMat,&viewmat,&proj);
    Maths::MultiplyMat4s(&someMat,&someMat,&BuildBGSubres0x12Matrix);
    FUN_00064030(&viewmat,&local_b8,&proj,&param_3->x,&someVOut->x,0.0);
    CopyMat4IntoShaderConstant((ShaderConstant *)&someMat.field1,&someMat);
    D3D8::D3DDevice_SetVertexShaderConstant4(0x66,(DirectXShaderConstant *)&someMat.field1);
    local_418 = param_3->y - someVOut->y;
    local_414 = param_3->z - someVOut->z;
    local_41c = param_3->x - someVOut->x;
    fVar14 = local_414 * local_414 + local_418 * local_418 + local_41c * local_41c;
    if (fVar14 != 0.0) {
      fVar10 = (float10)invsqrt(fVar14);
      local_41c = (float)((float10)local_41c * fVar10);
      local_418 = (float)((float10)local_418 * fVar10);
      local_414 = (float)(fVar10 * (float10)local_414);
    }
    local_400.c4 = 1.0;
    local_400.c1 = local_41c;
    local_400.c2 = local_418;
    local_400.c3 = local_414;
    D3D8::D3DDevice_SetVertexShaderConstant1(0x65,&local_400);
    local_390.c1 = (float)(param_6 & 0xff) * 0.003921569;
    local_390.c2 = (float)(param_6 >> 8 & 0xff) * 0.003921569;
    local_390.c3 = (float)(param_6._2_2_ & 0xff) * 0.003921569;
    local_390.c4 = (float)(param_6._2_2_ >> 8) * 0.003921569;
    D3D8::D3DDevice_SetVertexShaderConstant1(100,&local_390);
    fVar12 = param_3->y - someVOut->y;
    fVar11 = param_3->z - someVOut->z;
    fVar14 = param_3->x - someVOut->x;
    fVar15 = fVar11 * fVar11 + fVar12 * fVar12 + fVar14 * fVar14;
    if (fVar15 != 0.0) {
      fVar10 = (float10)invsqrt(fVar15);
      fVar14 = (float)((float10)fVar14 * fVar10);
      fVar12 = (float)((float10)fVar12 * fVar10);
      fVar11 = (float)(fVar10 * (float10)fVar11);
    }
    local_3b0.c1 = someVOut->x + fVar14 * param_5;
    local_3b0.c2 = someVOut->y + fVar12 * param_5;
    local_3b0.c3 = someVOut->z + fVar11 * param_5;
    local_3a0.c1 = param_3->x;
    local_3a0.c2 = param_3->y;
    local_3a0.c3 = param_3->z;
    local_3a0.c4 = 1.0;
    local_3b0.c4 = 1.0;
    D3D8::D3DDevice_SetVertexShaderConstant1(0x74,&local_3a0);
    D3D8::D3DDevice_SetVertexShaderConstant1(0x75,&local_3b0);
    if (DAT_00504940 != 0) {
      local_3f0.c1 = DAT_00504944;
      local_3f0.c2 = DAT_00504948;
      local_3f0.c3 = DAT_0050494c;
      local_3f0.c4 = DAT_00504950;
      D3D8::D3DDevice_SetVertexShaderConstant1(0x72,&local_3f0);
    }
    D3D8::D3DDevice_SetTexture(0,tex);
    fVar11 = local_414;
    fVar12 = local_41c;
    fVar14 = 0.0;
    if ((local_41c == 0.0) && (local_414 == 0.0)) {
      fVar12 = someVOut->x;
      fVar14 = someVOut->y;
      fVar11 = someVOut->z;
    }
    else {
      local_438 = local_414;
      fVar15 = local_414 * local_414 + local_41c * local_41c;
      local_440 = local_41c;
      if (fVar15 != 0.0) {
        fVar10 = (float10)invsqrt(fVar15);
        local_440 = (float)((float10)fVar12 * fVar10);
        fVar14 = (float)((float10)0.0 * fVar10);
        local_438 = (float)(fVar10 * (float10)fVar11);
      }
      fVar11 = subres0x12->scale * -0.5;
      fVar12 = someVOut->x + fVar11 * local_440;
      fVar14 = someVOut->y + fVar11 * fVar14;
      fVar11 = someVOut->z + fVar11 * local_438;
    }
    fVar15 = 1.0 / subres0x12->scale;
    iVar7 = (int)((fVar12 - (subres0x12->someV).x) * fVar15);
    fVar13 = fVar14 - (subres0x12->someV).y;
    iVar3 = (int)((fVar14 - (subres0x12->someV).y) * fVar15);
    local_428 = iVar7 - in_EAX;
    iVar5 = (int)((fVar11 - (subres0x12->someV).z) * fVar15);
    local_408 = iVar5 - in_EAX;
    fVar13 = fVar13 - (float)(int)(fVar13 / subres0x12->scale) * subres0x12->scale;
    local_410 = iVar3 - in_EAX;
    local_40c = iVar3;
    if ((subres0x12->scale * 0.5 < fVar13) &&
       (local_40c = in_EAX + iVar3, subres0x12->scale * 0.8 <= fVar13)) {
      local_410 = iVar3;
    }
    fVar12 = fVar12 - (subres0x12->someV).x;
    fVar12 = fVar12 - (float)(int)(fVar12 / subres0x12->scale) * subres0x12->scale;
    local_42c = iVar7;
    local_420 = local_428;
    if ((subres0x12->scale * 0.19999999 < fVar12) &&
       (local_42c = iVar7 + in_EAX, local_420 = local_428, subres0x12->scale * 0.8 <= fVar12)) {
      local_420 = iVar7;
    }
    fVar11 = fVar11 - (subres0x12->someV).z;
    fVar11 = fVar11 - (float)(int)(fVar11 / subres0x12->scale) * subres0x12->scale;
    local_424 = iVar5;
    if ((subres0x12->scale * 0.19999999 < fVar11) &&
       (local_424 = iVar5 + in_EAX, subres0x12->scale * 0.8 <= fVar11)) {
      local_408 = iVar5;
    }
    local_431 = '\0';
    iVar3 = local_40c;
    iVar5 = local_408;
    if (local_408 <= local_424) {
      do {
        local_3c8.z = (float)iVar5 * subres0x12->scale + (subres0x12->someV).z;
        local_3d4.z = subres0x12->scale + local_3c8.z;
        local_430 = local_410;
        iVar7 = local_410;
        if (local_410 <= iVar3) {
          do {
            local_3c8.y = (float)iVar7 * subres0x12->scale + (subres0x12->someV).y;
            local_3d4.y = subres0x12->scale + local_3c8.y;
            local_428 = local_420;
            local_430 = iVar7;
            if (local_420 <= local_42c) {
              do {
                if ((((local_428 < subres0x12->size1) && (iVar7 < subres0x12->size2)) &&
                    (iVar5 < subres0x12->size3)) &&
                   (((-1 < local_428 && (-1 < iVar7)) &&
                    ((-1 < iVar5 &&
                     (iVar3 = (subres0x12->size2 * iVar5 + iVar7) * subres0x12->size1 + local_428,
                     currentBg != (background *)0x0)))))) {
                  pMVar1 = (currentBg->avatar).model;
                  if (pMVar1 == (Model *)0x0) {
                    pMVar6 = (ModelDescriptor *)0x0;
                  }
                  else {
                    pMVar6 = pMVar1->descriptor;
                  }
                  pMVar2 = pMVar6->runtimeCtx->subres0x12->tiles;
                  if ((pMVar2[iVar3].resPtr != 0) &&
                     (pStreamData = &pMVar2[iVar3].bufferHeader, iVar7 = local_430,
                     pStreamData != (uint *)0x0)) {
                    local_3c8.x = (float)local_428 * subres0x12->scale + (subres0x12->someV).x;
                    local_3d4.x = subres0x12->scale + local_3c8.x;
                    BVar4 = Graphics::AABBvsFrustum
                                      ((GraphicsCamera *)&Graphics::CurrentCameraStruct->field_0x138
                                       ,&local_3c8,&local_3d4,
                                       &Graphics::CurrentCameraStruct->field_0x1e0);
                    iVar7 = local_430;
                    if ((BVar4 != 0) &&
                       (BVar4 = Graphics::AABBvsFrustum(&local_b8,&local_3c8,&local_3d4,&local_431),
                       iVar7 = local_430, BVar4 != 0)) {
                      D3D8::D3DDevice_SetStreamSource(0,(D3DVertexBuffer *)pStreamData,0x10);
                      if (currentBg == (background *)0x0) {
                        UVar9 = 0;
                      }
                      else {
                        pMVar1 = (currentBg->avatar).model;
                        if (pMVar1 == (Model *)0x0) {
                          UVar9 = *(uint *)(*(int *)(*piRam00000010 + 0x3c) + 8 + iVar3 * 0x1c) >> 4
                          ;
                        }
                        else {
                          UVar9 = pMVar1->descriptor->runtimeCtx->subres0x12->tiles[iVar3].resSize
                                  >> 4;
                        }
                      }
                      D3D8::D3DDevice_DrawVertices(D3DPT_TRIANGLELIST,0,UVar9);
                      local_404 = local_404 + 1;
                      iVar7 = local_430;
                    }
                  }
                }
                local_428 = local_428 + 1;
                iVar3 = local_40c;
              } while (local_428 <= local_42c);
            }
            local_430 = iVar7 + 1;
            iVar7 = local_430;
          } while (local_430 <= iVar3);
        }
        iVar7 = local_404;
        iVar5 = iVar5 + 1;
      } while (iVar5 <= local_424);
      if (local_404 != 0) {
        if ((param_7 != '\0') && (DAT_0050e384 != 0)) {
          fVar12 = (float)local_420 * subres0x12->scale + (subres0x12->someV).x;
          fVar11 = (float)local_410 * subres0x12->scale + (subres0x12->someV).y;
          fVar15 = (float)local_408 * subres0x12->scale + (subres0x12->someV).z;
          local_3e0 = (float)(local_42c + 1) * subres0x12->scale + (subres0x12->someV).x;
          local_3dc = (float)(iVar3 + 1) * subres0x12->scale + (subres0x12->someV).y;
          local_3d8 = (float)(local_424 + 1) * subres0x12->scale + (subres0x12->someV).z;
          fVar14 = currentBg->somePtr;
          if (fVar14 != 0.0) {
            D3D8::D3DDevice_GetTransform(D3DTS_WORLD,(D3DMATRIX *)&local_280.field1);
            D3D8::D3DDevice_GetTransform(D3DTS_VIEW,(D3DMATRIX *)&local_180.field1);
            D3D8::D3DDevice_GetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&local_240.field1);
            Maths::MultiplyMat4s(&local_140,&local_180,&local_240);
            CopyMat4IntoShaderConstant((ShaderConstant *)&someMat.field1,&someMat);
            iVar3 = 0;
            if (0 < DAT_0050e384) {
              pfVar8 = (float *)((int)fVar14 + 0x1b8);
              do {
                if (((((fVar12 < pfVar8[-2] || fVar12 == pfVar8[-2]) && (pfVar8[-2] <= local_3e0))
                     && (fVar11 < pfVar8[-1] || fVar11 == pfVar8[-1])) &&
                    ((pfVar8[-1] <= local_3dc && (fVar15 < *pfVar8 || fVar15 == *pfVar8)))) &&
                   (*pfVar8 <= local_3d8)) {
                  Maths::MultiplyMat4s
                            (&local_200,(D3DXMATRIX *)(pfVar8 + -0x22),
                             (D3DXMATRIX *)(pfVar8 + -0x42));
                  Maths::MultiplyMat4s((D3DXMATRIX *)constant,&local_280,&local_200);
                  Maths::MultiplyMat4s((D3DXMATRIX *)constant,(D3DXMATRIX *)constant,&local_140);
                  CopyMat4IntoShaderConstant(constant,(D3DXMATRIX *)constant);
                  D3D8::D3DDevice_SetVertexShaderConstant4(0x60,(DirectXShaderConstant *)constant);
                  Maths::MultiplyMat4s
                            (&local_100,(D3DXMATRIX *)(pfVar8 + -0x12),
                             (D3DXMATRIX *)(pfVar8 + -0x62));
                  FUN_00151dd9(&local_3f0,&local_41c,&local_100);
                  local_400.c1 = local_3f0.c1;
                  local_400.c2 = local_3f0.c2;
                  local_400.c3 = local_3f0.c3;
                  local_400.c4 = 1.0;
                  D3D8::D3DDevice_SetVertexShaderConstant1(0x65,&local_400);
                  Maths::MultiplyMat4s(&local_300,&local_200,&someMat);
                  CopyMat4IntoShaderConstant((ShaderConstant *)&local_300.field1,&local_300);
                  D3D8::D3DDevice_SetVertexShaderConstant4
                            (0x66,(DirectXShaderConstant *)&local_300.field1);
                  if (uint32_t_0050e37c == 0) {
                    pStreamData_00 = (D3DVertexBuffer *)0x0;
                  }
                  else {
                    pStreamData_00 = *(D3DVertexBuffer **)(uint32_t_0050e37c + iVar3 * 4);
                  }
                  D3D8::D3DDevice_SetStreamSource(0,pStreamData_00,0x10);
                  if (uint32_t_0050e37c == 0) {
                    UVar9 = 0;
                  }
                  else {
                    UVar9 = *(UINT *)(DAT_0050e380 + iVar3 * 4);
                  }
                  D3D8::D3DDevice_DrawVertices(D3DPT_TRIANGLELIST,0,UVar9);
                }
                iVar3 = iVar3 + 1;
                pfVar8 = pfVar8 + 0x78;
              } while (iVar3 < DAT_0050e384);
            }
            Maths::MultiplyMat4s((D3DXMATRIX *)constant,&local_280,&local_180);
            Maths::MultiplyMat4s((D3DXMATRIX *)constant,(D3DXMATRIX *)constant,&local_240);
            CopyMat4IntoShaderConstant(constant,(D3DXMATRIX *)constant);
            D3D8::D3DDevice_SetVertexShaderConstant4(0x60,(DirectXShaderConstant *)constant);
          }
        }
        return iVar7;
      }
    }
  }
  return 0;
}




void FUN_00065460(byte param_1,DXTextureInstance *param_2)

{
  Graphics::UpdateViewport2();
  Graphics::UnbindAll();
  Graphics::EnableAlphaBlend();
  FUN_0005e2a0();
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  Graphics::RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
  Graphics::RenderState.zWriteEnabled = 1;
  D3D8::D3DDevice_SetRenderState_ZEnable(1);
  Graphics::UpdateWorldMatrix((D3DMATRIX *)0x0);
  if ((param_1 != 0xffffffff) && ((uint)param_1 < (uint)param_2->field14_0x11)) {
    param_2->field16_0x13 = param_1;
  }
  Graphics::SetTextureStage(0,param_2);
  return;
}




void Graphics::CompileVertexShaders(void)

{
  DWORD *pDeclaration;
  HRESULT err;
  uint handle;
  HRESULT HVar1;
  Shader_ptr_4_uint props;
  XGBuffer *compiled_shader;
  uint new_handle;
  XGBuffer *listing;
  XGBuffer *errors;
  
  props = &VertexShaders[0].size;
  do {
    pDeclaration = (DWORD *)ADJ(props)->pDeclaration;
    err = XGRAPHICS::XGAssembleShader
                    ((LPCSTR)0x0,ADJ(props).data,ADJ(props)->size,0,(XGBuffer **)0x0,
                     &compiled_shader,&errors,&listing,(SASM_ResolverCallback *)0x0,(LPVOID)0x0,
                     (LPDWORD)0x0);
    if (err == 0) {
      HVar1 = D3D8::D3DDevice_CreateVertexShader(pDeclaration,compiled_shader->pData,&new_handle,0);
      handle = ~-(uint)(HVar1 != 0) & new_handle;
    }
    else {
      handle = 0;
    }
    ADJ(props)->shaderHandle = handle;
    props = props + 6;
  } while ((int)props < 0x427424);
  return;
}




void Graphics::SetVertexShader(uint index)

{
  D3D8::D3DDevice_SetVertexShader(VertexShaders[index].shaderHandle);
  if (VertexShaders[index].constants != (ShaderConstant *)0x0) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline(0x60,VertexShaders[index].constants,0xc);
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00065fe6)

void Graphics::TestVisibility_
               (float param_1,float param_2,int param_3,vec3 *v1,OcclusionValue *param_5)

{
  int iVar1;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar2;
  uint testResult;
  vec2 v2;
  
  iVar1 = FUN_0013bb70(param_5,&v2.x,&testResult);
  param_5->occType = UNKNOWN;
  if ((iVar1 != 0) && (testResult != 0)) {
    fVar5 = param_1 / (1.0 - ((float)(*(uint *)(param_3 + ((int)v2.y * 0x280 + (int)v2.x) * 4) >> 8)
                             * 5.960465e-08) / (param_2 / (param_2 - param_1)));
    param_5->field1_0xc = fVar5;
    fVar5 = param_5->field2_0x10 + fVar5;
    fVar2 = v1->x - (param_5->pos).x;
    fVar3 = v1->y - (param_5->pos).y;
    fVar4 = v1->z - (param_5->pos).z;
    if (fVar5 * fVar5 <= fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4) {
      param_5->occType = GREATER;
      return;
    }
    param_5->occType = LESS;
  }
  return;
}




void FUN_0006f5c0(entityAvatarFxBurnup *param_1,Message *param_2)

{
  avatar::onMessage(&param_1->avatar,param_2);
  if ((param_2->header).msgId == Avatar_SceneInsert) {
    if (*(int *)&param_1[1].avatar.field_0x128 == 0) {
      avatar::onDrawListAdd(&param_1->avatar);
    }
    FUN_0003e850(param_1);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000706e0(entityAvatarFxBurnup *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  
  avatar::onMessage(&param_1->avatar,param_2);
  OVar1 = (param_2->header).msgId;
  if (OVar1 == Avatar_SceneInsert) {
    FUN_0003e850(param_1);
    entityAvatarFxBurnup::checkCollision0x4(param_1);
  }
  else if (OVar1 == Scene_AvatarCreatedFromProjectile) {
    FUN_000709f0(param_1);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000715b0(entityAvatarFxBurnup *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  actor *paVar2;
  AnimEventMapping *pAVar3;
  
  avatar::onMessage(&param_1->avatar,param_2);
  OVar1 = (param_2->header).msgId;
  if (OVar1 == Avatar_SceneInsert) {
    if (*(int *)(param_1->someAID2 + 0x74) == 0) {
      avatar::onDrawListAdd(&param_1->avatar);
      FUN_0003e850(param_1);
      entityAvatarFxBurnup::checkCollision0x4(param_1);
    }
  }
  else if (((OVar1 == Scene_SuperScaryStateChange) && (*(int *)&param_1->field_0x93c == 2)) &&
          ((paVar2 = (param_2->header).someActor, paVar2 == (actor *)0x7 || (paVar2 == (actor *)0x8)
           ))) {
    if ((param_1->avatar).animTable != (AnimtableResource *)0x0) {
      pAVar3 = avatar::getAnimEventByName(&param_1->avatar,"in",0);
      if (pAVar3 != (AnimEventMapping *)0x0) {
        avatar::activateAnimation(&param_1->avatar,pAVar3);
      }
    }
    *(undefined4 *)&param_1->field_0x93c = 3;
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00071d50(entityAvatarFxBurnup *param_1,Message *param_2)

{
  ObjMsgID OVar1;
  actor *paVar2;
  AnimEventMapping *pAVar3;
  
  avatar::onMessage(&param_1->avatar,param_2);
  OVar1 = (param_2->header).msgId;
  if (OVar1 == Avatar_SceneInsert) {
    avatar::onDrawListAdd(&param_1->avatar);
    FUN_0003e850(param_1);
    entityAvatarFxBurnup::checkCollision0x4(param_1);
  }
  else if (((OVar1 == Scene_SuperScaryStateChange) && (*(int *)(param_1->someAID1 + 4) == 3)) &&
          ((paVar2 = (param_2->header).someActor, paVar2 == (actor *)0x7 || (paVar2 == (actor *)0x8)
           ))) {
    Events::UpdateActionBeginEnds(0xff,1);
    if ((param_1->avatar).animTable != (AnimtableResource *)0x0) {
      pAVar3 = avatar::getAnimEventByName(&param_1->avatar,"leapoff",0);
      if (pAVar3 != (AnimEventMapping *)0x0) {
        avatar::activateAnimation(&param_1->avatar,pAVar3);
      }
    }
    param_1->someAID1[0xc] = '\0';
    param_1->someAID1[0xd] = '\0';
    param_1->someAID1[0xe] = -0x60;
    param_1->someAID1[0xf] = '@';
    param_1->someAID1[4] = '\x04';
    param_1->someAID1[5] = '\0';
    param_1->someAID1[6] = '\0';
    param_1->someAID1[7] = '\0';
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000724c0(entityAvatarFxBurnup *param_1,actor *param_2)

{
  AvatarVTable *pAVar1;
  entityAvatarFxBurnup *peVar2;
  actor *paVar3;
  
  paVar3 = param_2;
  peVar2 = param_1;
  avatar::onMessage(&param_1->avatar,(Message *)param_2);
  pAVar1 = (paVar3->avatar).vtable;
  if (pAVar1 == (AvatarVTable *)0x23) {
    FUN_0003e850(peVar2);
    entityAvatarFxBurnup::checkCollision0x4(peVar2);
  }
  else {
    if (pAVar1 == (AvatarVTable *)0x88) {
      FUN_00072750();
      return;
    }
    if (pAVar1 == (AvatarVTable *)0x8e) {
      switch(*(actor **)&(paVar3->avatar).field_0x4) {
      case (actor *)0x0:
        FUN_00072980(peVar2->fx_y_from_scale,*(undefined4 *)&peVar2->field_0x93c,
                     &peVar2[1].avatar.field_0x78,1);
        return;
      case (actor *)0x2:
        FUN_00072980(peVar2->fx_y_from_scale,0xbf800000,&peVar2[1].avatar.infoList.prev,0);
        return;
      case (actor *)0x4:
        PlayCutsceneMusic(audio_asset_name_00427438);
        peVar2[1].avatar.baseTransform.m[2][0] = 0.0;
        return;
      case (actor *)0x7:
      case (actor *)0x8:
        param_2 = (actor *)0xa;
        (**(code **)(*(int *)peVar2->fx_y_from_scale + 0xc))
                  ((int *)peVar2->fx_y_from_scale,&param_2);
        avatar::destroy(&peVar2->avatar);
        param_1 = (entityAvatarFxBurnup *)0xb3;
        EventLoop::NewMessage((MessageHeader *)&param_1);
        return;
      }
    }
  }
  return;
}



void __thiscall
FUN_000725e0(float *param_1,float param_2,float param_3,undefined4 param_4,undefined4 param_5,
            int *param_6,char *param_7,char *param_8,char *param_9,char *param_10,char *param_11,
            char *param_12,undefined4 param_13)

{
  char cVar1;
  int iVar2;
  int iVar3;
  avatarParams *in_EAX;
  avatarParams *paVar4;
  char *pcVar5;
  char *unaff_EBX;
  float *unaff_EDI;
  
  paVar4 = avatarParams::init(in_EAX);
  (paVar4->pos).x = *unaff_EDI;
  (paVar4->pos).y = unaff_EDI[1];
  (paVar4->pos).z = unaff_EDI[2];
  (paVar4->rotEuler).x = *param_1;
  (paVar4->rotEuler).y = param_1[1];
  (paVar4->rotEuler).z = param_1[2];
  paVar4[1].pos.y = param_2;
  paVar4[1].pos.z = param_3;
  *(undefined4 *)(paVar4[1].standAnimationAID + 0x6c) = param_4;
  *(undefined4 *)(paVar4[2].standAnimationAID + 0x40) = param_13;
  (paVar4->objParams).paramsSize = 0x754;
  (paVar4->objParams).objInitValue = 0x6a;
  (paVar4->objParams).typeIndex = 0x22;
  *(undefined4 *)(paVar4[1].standAnimationAID + 0x70) = param_5;
  iVar2 = 0x348 - (int)unaff_EBX;
  do {
    cVar1 = *unaff_EBX;
    unaff_EBX[(int)paVar4 + iVar2] = cVar1;
    unaff_EBX = unaff_EBX + 1;
  } while (cVar1 != '\0');
  if (*param_6 == 0x5f646961) {
    iVar2 = 0x3c8 - (int)param_6;
    do {
      iVar3 = *param_6;
      *(char *)((int)paVar4 + iVar2 + (int)param_6) = (char)iVar3;
      param_6 = (int *)((int)param_6 + 1);
    } while ((char)iVar3 != '\0');
  }
  else {
    pcVar5 = "aid_objparams_ghoulies_misc_prop";
    do {
      cVar1 = *pcVar5;
      (paVar4[-0xefb].calloutAID + 0x34)[(int)pcVar5] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
  }
  iVar2 = 0x450 - (int)param_7;
  do {
    cVar1 = *param_7;
    param_7[(int)paVar4 + iVar2] = cVar1;
    param_7 = param_7 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0x4d0 - (int)param_8;
  do {
    cVar1 = *param_8;
    param_8[(int)paVar4 + iVar2] = cVar1;
    param_8 = param_8 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0x550 - (int)param_9;
  do {
    cVar1 = *param_9;
    param_9[(int)paVar4 + iVar2] = cVar1;
    param_9 = param_9 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0x5d0 - (int)param_10;
  do {
    cVar1 = *param_10;
    param_10[(int)paVar4 + iVar2] = cVar1;
    param_10 = param_10 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0x650 - (int)param_11;
  do {
    cVar1 = *param_11;
    param_11[(int)paVar4 + iVar2] = cVar1;
    param_11 = param_11 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0x6d0 - (int)param_12;
  do {
    cVar1 = *param_12;
    param_12[(int)paVar4 + iVar2] = cVar1;
    param_12 = param_12 + 1;
  } while (cVar1 != '\0');
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00079320(entityMindCinema *mind,vec3 *param_2,AnotherCameraGoal *param_3)

{
  int iVar1;
  undefined4 local_1c;
  vec3 local_18;
  vec3 local_c;
  
  if (param_3[1].header.prev != (actorMindGoal *)0x0) {
    FUN_000791a0(param_3[1].header.next,FLOAT_004274fc,0,FLOAT_004274f8,1);
    return;
  }
  if (param_3->field645_0x294 != (actorMindGoal *)0x0) {
    iVar1 = FUN_0012cef0(FLOAT_0042751c,FLOAT_00427520,1);
    if (iVar1 == 0) {
      local_18.z = *(float *)&param_3->field_0x20;
      local_18.x = *(float *)&param_3->field_0x18;
      local_18.y = *(float *)&param_3->field_0x28 * 0.5 + *(float *)&param_3->field_0x1c;
      local_c.x = param_2->x;
      local_c.y = param_2->y;
      local_c.z = param_2->z;
      iVar1 = FUN_000790b0(mind,&local_18,&local_1c,(int)FLOAT_00427538,&local_c);
      if (iVar1 != 0) {
        FUN_000791a0(local_1c,FLOAT_00427514,1,FLOAT_004274f4,0);
      }
      mind->someBool = 0;
      return;
    }
    mind->someBool = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

undefined4

void UpdateCameraTarget_(entityMoveCrane *param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int unaff_EDI;
  float10 fVar4;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if (*(char *)(unaff_EDI + 0x308) != '\0') {
    if (FLOAT_004275c4 == 0.0) {
      local_1c = 0.0;
    }
    else {
      iVar3 = *(int *)(*(int *)(*(int *)(*(int *)(*(int *)(unaff_EDI + 8) + 0x958) + 0xc) + 0x95c) +
                      8);
      fVar1 = *(float *)(iVar3 + 0x3c);
      fVar2 = *(float *)(iVar3 + 0x44);
      fVar4 = scaled_invsqrt(fVar1 * fVar1 + fVar2 * fVar2);
      local_1c = (float)fVar4;
    }
    FUN_0013ce80(FLOAT_004275bc,local_1c,FLOAT_004275c0);
    FUN_001405e0(*(undefined4 *)(unaff_EDI + 0x334));
    if (FLOAT_004275c8 != 0.0) {
      (param_1->v2).x = local_18;
      (param_1->v2).y = local_14;
      (param_1->v2).z = local_10;
    }
  }
  return;
}




void ResetCameraAndRecalculate(actorBody *body)

{
  vec3 local_28;
  vec3 local_1c;
  vec3 *local_10;
  float local_c;
  float local_8;
  float local_4;
  actor *actor;
  
  actor = body->actor;
  local_28.x = (actor->avatar).physicsPos.x;
  local_c = (body->velocity).y;
  local_8 = (body->velocity).z;
  local_28.y = (actor->avatar).physicsPos.y;
  local_28.z = (actor->avatar).physicsPos.z;
  local_10 = (vec3 *)(body->velocity).x;
  local_4 = body->airResistance;
  local_1c.z = 0.0;
  local_1c.y = 0.0;
  local_1c.x = 0.0;
  calculatePhysicsWithCallbacks
            (&local_10,&local_28,&local_1c,&local_28,&local_1c,0.0033333334,g_ticksToRun,
             FUN_00140700,FUN_00140770,switchD_000d4179::EmptyFunction);
  actor = body->actor;
                    // actually updates the camera to the player
  (actor->avatar).physicsPos.x = local_28.x;
  (actor->avatar).physicsPos.y = local_28.y;
  (actor->avatar).physicsPos.z = local_28.z;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Graphics::UpdateCameraValues(void)

{
  D3DXMATRIX *pDVar1;
  int i;
  MainCameraStruct *cam;
  MainCameraStruct *camm;
  
  i = 0;
  cam = CameraStructs;
  do {
    CurrentCameraStruct = cam;
                    // Adds the "1" flag if the camera is index 0?
    cam->flags = cam->flags ^ ((uint)(i == 0) ^ cam->flags) & 1;
    CurrentCameraStruct->fov = -1.0;
    CurrentCameraStruct->aspectRatioIndex = 4.2039e-45;
    BackbufferWidth = (uint)g_DXContext.backBufferWidth;
    BackbufferHeight = (float)(uint)g_DXContext.backBufferHeight;
    CurrentCameraStruct->field11_0x48 = 0;
    CurrentCameraStruct->field12_0x4c = 0;
    CurrentCameraStruct->width = BackbufferWidth;
    CurrentCameraStruct->height = BackbufferHeight;
    Camera::ComputeTangents
              (CurrentCameraStruct->fov,&CurrentCameraStruct->calculatedWidth_,
               &CurrentCameraStruct->computedFov_,&CurrentCameraStruct->circleAngle_,
               &CurrentCameraStruct->ratioDiff_,&CurrentCameraStruct->cotangentOffset_,
               (uint)CurrentCameraStruct->aspectRatioIndex,&CurrentCameraStruct->field16_0x5c,
               &CurrentCameraStruct->calculatedHeight__unused);
    camm = CurrentCameraStruct;
    (CurrentCameraStruct->pos).z = 0.0;
    (camm->pos).y = 0.0;
    (camm->pos).x = 0.0;
    Maths::EulerToQuaternion(&g_someEulerRotation,&CurrentCameraStruct->rotQuat);
    SetCurCamStructForwardsFromQuat(&CurrentCameraStruct->rotQuat);
    CurrentCameraStruct->near = 1.0;
    CurrentCameraStruct->far = 1000.0;
    camm = CurrentCameraStruct;
    (CurrentCameraStruct->affineT).m[0][0] = 1.0;
    (camm->affineT).m[0][1] = 0.0;
    (camm->affineT).m[0][2] = 0.0;
    (camm->affineT).m[0][3] = 0.0;
    (camm->affineT).m[1][0] = 0.0;
    (camm->affineT).m[1][1] = 1.0;
    (camm->affineT).m[1][2] = 0.0;
    (camm->affineT).m[1][3] = 0.0;
    (camm->affineT).m[2][0] = 0.0;
    (camm->affineT).m[2][1] = 0.0;
    (camm->affineT).m[2][2] = 1.0;
    (camm->affineT).m[2][3] = 0.0;
    camm = CurrentCameraStruct;
    pDVar1 = &CurrentCameraStruct->transformMat;
    (CurrentCameraStruct->transformMat).m[3][2] = 0.0;
    (camm->transformMat).m[3][1] = 0.0;
    (camm->transformMat).m[3][0] = 0.0;
    (camm->transformMat).m[2][3] = 0.0;
    (camm->transformMat).m[2][1] = 0.0;
    (camm->transformMat).m[2][0] = 0.0;
    (camm->transformMat).m[1][3] = 0.0;
    (camm->transformMat).m[1][2] = 0.0;
    (camm->transformMat).m[1][0] = 0.0;
    (camm->transformMat).m[0][3] = 0.0;
    (camm->transformMat).m[0][2] = 0.0;
    (camm->transformMat).m[0][1] = 0.0;
    (camm->transformMat).m[3][3] = 1.0;
    (camm->transformMat).m[2][2] = 1.0;
    (camm->transformMat).m[1][1] = 1.0;
    pDVar1->m[0][0] = 1.0;
    cam = cam + 1;
    i = i + 1;
    CurrentCameraStruct->field_0x1e0 = 0;
  } while ((int)cam < 0x5077a8);
  return;
}




void Graphics::SetCurCamStructForwardsFromQuat(Quaternion *q)

{
  vec3 *pvVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  MainCameraStruct *cam;
  
  cam = CurrentCameraStruct;
                    // Copy q into current camera
  (CurrentCameraStruct->rotQuat).x = q->x;
  (cam->rotQuat).y = q->y;
  (cam->rotQuat).z = q->z;
  (cam->rotQuat).w = q->w;
  cam = CurrentCameraStruct;
  (CurrentCameraStruct->forwards).z = -1.0;
  (cam->forwards).x = 0.0;
  (cam->forwards).y = 0.0;
  cam = CurrentCameraStruct;
  pvVar1 = &CurrentCameraStruct->forwards;
  fVar3 = (q->w * (CurrentCameraStruct->forwards).x - (CurrentCameraStruct->forwards).y * q->z) +
          (CurrentCameraStruct->forwards).z * q->y;
  fVar4 = (q->w * (CurrentCameraStruct->forwards).y - (CurrentCameraStruct->forwards).z * q->x) +
          pvVar1->x * q->z;
  fVar5 = ((CurrentCameraStruct->forwards).z * q->w - (CurrentCameraStruct->forwards).x * q->y) +
          (CurrentCameraStruct->forwards).y * q->x;
  fVar6 = pvVar1->x * q->x + (CurrentCameraStruct->forwards).z * q->z +
          (CurrentCameraStruct->forwards).y * q->y;
  pvVar1->x = (q->w * fVar3 + q->x * fVar6 + fVar5 * q->y) - q->z * fVar4;
  (cam->forwards).y = (q->w * fVar4 + q->z * fVar3 + fVar6 * q->y) - q->x * fVar5;
  (cam->forwards).z = (q->w * fVar5 + q->z * fVar6 + q->x * fVar4) - fVar3 * q->y;
  cam = CurrentCameraStruct;
  fVar3 = (CurrentCameraStruct->forwards).y;
  fVar4 = (CurrentCameraStruct->forwards).z;
  fVar5 = (CurrentCameraStruct->forwards).x;
  pvVar1 = &CurrentCameraStruct->forwards;
  fVar3 = fVar5 * fVar5 + fVar3 * fVar3 + fVar4 * fVar4;
  if (fVar3 != 0.0) {
    fVar2 = (float10)invsqrt(fVar3);
    pvVar1->x = (float)(fVar2 * (float10)pvVar1->x);
    (cam->forwards).y = (float)(fVar2 * (float10)(cam->forwards).y);
    (cam->forwards).z = (float)(fVar2 * (float10)(cam->forwards).z);
  }
  return;
}




void Graphics::RecalculateWorldAndViews(void)

{
  float fVar1;
  float fVar2;
  Quaternion local_40;
  AffineTransform local_30;
  MainCameraStruct *cam;
  
  Camera::ComputeTangents
            (CurrentCameraStruct->fov,&CurrentCameraStruct->calculatedWidth_,
             &CurrentCameraStruct->computedFov_,&CurrentCameraStruct->circleAngle_,
             &CurrentCameraStruct->ratioDiff_,&CurrentCameraStruct->cotangentOffset_,
             (uint)CurrentCameraStruct->aspectRatioIndex,&CurrentCameraStruct->field16_0x5c,
             &CurrentCameraStruct->calculatedHeight__unused);
  FUN_00153d80(&CurrentCameraStruct->rotQuat,&local_40);
  AffineTransform::fromQuaternion((AffineTransform *)&CurrentCameraStruct->field_0xd8,&local_40);
  fVar1 = 0.0;
  fVar2 = 1.0;
  local_30.m[0][3] = 0.0 - (CurrentCameraStruct->pos).x;
  local_30.m[1][3] = 0.0 - (CurrentCameraStruct->pos).y;
  local_30.m[2][3] = 0.0 - (CurrentCameraStruct->pos).z;
  local_30.m[0][0] = 1.0;
  local_30.m[0][1] = 0.0;
  local_30.m[0][2] = 0.0;
  local_30.m[1][0] = 0.0;
  local_30.m[1][1] = 1.0;
  local_30.m[1][2] = 0.0;
  local_30.m[2][0] = 0.0;
  local_30.m[2][1] = 0.0;
  local_30.m[2][2] = 1.0;
  leftCombineTransforms
            (&CurrentCameraStruct->affineT,(AffineTransform *)&CurrentCameraStruct->field_0xd8,
             &local_30);
  cam = CurrentCameraStruct;
  (CurrentCameraStruct->transformMat).m[0][0] = (CurrentCameraStruct->affineT).m[0][0];
  (cam->transformMat).m[0][1] = (cam->affineT).m[1][0];
  (cam->transformMat).m[0][2] = (cam->affineT).m[2][0];
  (cam->transformMat).m[1][0] = (cam->affineT).m[0][1];
  (cam->transformMat).m[1][1] = (cam->affineT).m[1][1];
  (cam->transformMat).m[1][2] = (cam->affineT).m[2][1];
  (cam->transformMat).m[2][0] = (cam->affineT).m[0][2];
  (cam->transformMat).m[2][1] = (cam->affineT).m[1][2];
  (cam->transformMat).m[2][2] = (cam->affineT).m[2][2];
  (cam->transformMat).m[3][0] = (cam->affineT).m[0][3];
  (cam->transformMat).m[3][1] = (cam->affineT).m[1][3];
  (cam->transformMat).m[3][2] = (cam->affineT).m[2][3];
  (cam->transformMat).m[2][3] = fVar1;
  (cam->transformMat).m[1][3] = fVar1;
  (cam->transformMat).m[0][3] = fVar1;
  (cam->transformMat).m[3][3] = fVar2;
  SetSomeMemoryMatrix((D3DXVECTOR3 *)&(CurrentCameraStruct->transformMat).field1);
  Maths::InvertAffineMatrix
            ((D3DXMATRIX *)&CurrentCameraStruct->affineT,
             (D3DMATRIX *)&CurrentCameraStruct->field_0x108);
  UpdateWorldMatrix((D3DMATRIX *)0x0);
  return;
}




void Graphics::UpdatePerspectiveProj(void)

{
  float10 fVar1;
  float fVar2;
  float aspsect_ratio;
  float far;
  float near;
  
  if (5000.0 < CurrentCameraStruct->far) {
    CurrentCameraStruct->far = 5000.0;
  }
  if (CurrentCameraStruct->aspectRatioIndex == 4.2039e-45) {
    aspsect_ratio = g_aspectRatioLookups[g_currentAspectRatioIndex].ratio;
  }
  else {
    aspsect_ratio = g_aspectRatioLookups[(int)CurrentCameraStruct->aspectRatioIndex].ratio;
  }
  if (g_DXContext.use10x11PixelAspect == false) {
    aspsect_ratio = aspsect_ratio * 1.1;
  }
  far = CurrentCameraStruct->far;
  near = CurrentCameraStruct->near;
  fVar1 = (float10)FastCotangent(CurrentCameraStruct->circleAngle_ * 0.5 * 0.017453292);
  fVar2 = 1.0 / (far - near);
  PerspectiveProjMat_.m[2][3] = 0.0 - near * far * 2.0 * fVar2;
  PerspectiveProjMat_.m[2][2] = 0.0 - (near + far) * fVar2;
  PerspectiveProjMat_.m[0][1] = 0.0;
  PerspectiveProjMat_.m[0][2] = 0.0;
  PerspectiveProjMat_.m[0][3] = 0.0;
  PerspectiveProjMat_.m[1][0] = 0.0;
  PerspectiveProjMat_.m[1][2] = 0.0;
  PerspectiveProjMat_.m[1][3] = 0.0;
  PerspectiveProjMat_.m[2][0] = 0.0;
  PerspectiveProjMat_.m[2][1] = 0.0;
  PerspectiveProjMat_.m[3][0] = 0.0;
  PerspectiveProjMat_.m[3][1] = 0.0;
  PerspectiveProjMat_.m[3][2] = -1.0;
  PerspectiveProjMat_.m[3][3] = 0.0;
  PerspectiveProjMat_.m[0][0] = (float)(((float10)1.0 / fVar1) / (float10)aspsect_ratio);
  PerspectiveProjMat_.m[1][1] = (float)((float10)1.0 / fVar1);
  FUN_000f6630();
  FUN_00156350(&CurrentCameraStruct->field_0x138);
  return;
}




void Graphics::UpdateViewport2(void)

{
  D3DVIEWPORT8 local_18;
  
  D3DX8::D3DXMatrixTranspose((D3DMATRIX *)&DAT_00506fd8,&PerspectiveProjMat_);
  D3D8::D3DDevice_SetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&DAT_00506fd8);
  local_18.X = (DWORD)CurrentCameraStruct->computedFov_;
  local_18.Width = CurrentCameraStruct->calculatedWidth_;
  local_18.Y = (DWORD)CurrentCameraStruct->field16_0x5c;
  local_18.Height = (DWORD)CurrentCameraStruct->calculatedHeight__unused;
  local_18.MinZ = 0.0;
  local_18.MaxZ = 1.0;
  D3D8::D3DDevice_SetViewport(&local_18);
  SetSpecificProjectionMatrix((D3DMATRIX *)&DAT_00506fd8);
  RecalculateWorldAndViews();
  return;
}




void Graphics::UpdateViewport(void)

{
  D3DVIEWPORT8 viewport;
  
  D3DX8::D3DXMatrixTranspose((D3DMATRIX *)&ProjectionMatrix,&PerspectiveProjMat_);
  D3D8::D3DDevice_SetTransform(D3DTS_PROJECTION,(D3DMATRIX *)&ProjectionMatrix);
  viewport.X = (DWORD)CurrentCameraStruct->computedFov_;
  viewport.Width = CurrentCameraStruct->calculatedWidth_;
  viewport.Y = (DWORD)CurrentCameraStruct->field16_0x5c;
  viewport.Height = (DWORD)CurrentCameraStruct->calculatedHeight__unused;
  viewport.MinZ = 0.0;
  viewport.MaxZ = 1.0;
  D3D8::D3DDevice_SetViewport(&viewport);
  SetSpecificProjectionMatrix((D3DMATRIX *)&ProjectionMatrix);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::UpdateWorldMatrix(D3DMATRIX *newWorldMat)

{
  D3DMATRIX *pMatrix;
  
  ViewMatrix2.m[0][0] = (CurrentCameraStruct->affineT).m[0][0];
  ViewMatrix2.m[0][1] = (CurrentCameraStruct->affineT).m[1][0];
  ViewMatrix2.m[0][2] = (CurrentCameraStruct->affineT).m[2][0];
  ViewMatrix2.m[1][0] = (CurrentCameraStruct->affineT).m[0][1];
  ViewMatrix2.m[1][1] = (CurrentCameraStruct->affineT).m[1][1];
  ViewMatrix2.m[1][2] = (CurrentCameraStruct->affineT).m[2][1];
  ViewMatrix2.m[2][0] = (CurrentCameraStruct->affineT).m[0][2];
  ViewMatrix2.m[2][1] = (CurrentCameraStruct->affineT).m[1][2];
  ViewMatrix2.m[2][2] = (CurrentCameraStruct->affineT).m[2][2];
  ViewMatrix2.m[3][0] = (CurrentCameraStruct->affineT).m[0][3];
  ViewMatrix2.m[3][1] = (CurrentCameraStruct->affineT).m[1][3];
  ViewMatrix2.m[3][2] = (CurrentCameraStruct->affineT).m[2][3];
  ViewMatrix2.m[2][3] = 0.0;
  ViewMatrix2.m[1][3] = 0.0;
  ViewMatrix2.m[0][3] = 0.0;
  ViewMatrix2.m[3][3] = 1.0;
  D3D8::D3DDevice_SetTransform(D3DTS_VIEW,(D3DMATRIX *)&ViewMatrix2.field1);
  if (newWorldMat != (D3DMATRIX *)0x0) {
    MatrixCpy(&WorldMatrix2,newWorldMat);
    D3D8::D3DDevice_SetTransform(D3DTS_WORLD,pMatrix);
    return;
  }
  WorldMatrix2.m[0][0] = AffineTransform::Identity.m[0][0];
  WorldMatrix2.m[0][1] = AffineTransform::Identity.m[1][0];
  WorldMatrix2.m[0][2] = AffineTransform::Identity.m[2][0];
  WorldMatrix2.m[1][0] = AffineTransform::Identity.m[0][1];
  WorldMatrix2.m[1][1] = AffineTransform::Identity.m[1][1];
  WorldMatrix2.m[1][2] = AffineTransform::Identity.m[2][1];
  WorldMatrix2.m[2][0] = AffineTransform::Identity.m[0][2];
  WorldMatrix2.m[2][1] = AffineTransform::Identity.m[1][2];
  WorldMatrix2.m[2][2] = AffineTransform::Identity.m[2][2];
  WorldMatrix2.m[3][0] = AffineTransform::Identity.m[0][3];
  WorldMatrix2.m[3][1] = AffineTransform::Identity.m[1][3];
  WorldMatrix2.m[3][2] = AffineTransform::Identity.m[2][3];
  WorldMatrix2.m[2][3] = 0.0;
  WorldMatrix2.m[1][3] = 0.0;
  WorldMatrix2.m[0][3] = 0.0;
  WorldMatrix2.m[3][3] = 1.0;
  D3D8::D3DDevice_SetTransform(D3DTS_WORLD,(D3DMATRIX *)&WorldMatrix2.field1);
  return;
}




void Graphics::SetViewMatrix(D3DXMATRIX *mat)

{
  MainCameraStruct *cam;
  float fVar1;
  AffineTransform *pDVar2;
  
  cam = CurrentCameraStruct;
  pDVar2 = &CurrentCameraStruct->affineT;
  (CurrentCameraStruct->affineT).m[0][0] = mat->m[0][0];
  pDVar2->m[0][1] = mat->m[0][1];
  (cam->affineT).m[0][2] = mat->m[0][2];
  (cam->affineT).m[0][3] = mat->m[0][3];
  (cam->affineT).m[1][0] = mat->m[1][0];
  (cam->affineT).m[1][1] = mat->m[1][1];
  (cam->affineT).m[1][2] = mat->m[1][2];
  (cam->affineT).m[1][3] = mat->m[1][3];
  (cam->affineT).m[2][0] = mat->m[2][0];
  (cam->affineT).m[2][1] = mat->m[2][1];
  (cam->affineT).m[2][2] = mat->m[2][2];
  (cam->affineT).m[2][3] = mat->m[2][3];
  cam = CurrentCameraStruct;
  (CurrentCameraStruct->transformMat).m[0][0] = (CurrentCameraStruct->affineT).m[0][0];
  (cam->transformMat).m[0][1] = (cam->affineT).m[1][0];
  (cam->transformMat).m[0][2] = (cam->affineT).m[2][0];
  (cam->transformMat).m[1][0] = (cam->affineT).m[0][1];
  (cam->transformMat).m[1][1] = (cam->affineT).m[1][1];
  (cam->transformMat).m[1][2] = (cam->affineT).m[2][1];
  (cam->transformMat).m[2][0] = (cam->affineT).m[0][2];
  (cam->transformMat).m[2][1] = (cam->affineT).m[1][2];
  (cam->transformMat).m[2][2] = (cam->affineT).m[2][2];
  (cam->transformMat).m[3][0] = (cam->affineT).m[0][3];
  (cam->transformMat).m[3][1] = (cam->affineT).m[1][3];
  fVar1 = (cam->affineT).m[2][3];
  (cam->transformMat).m[2][3] = 0.0;
  (cam->transformMat).m[1][3] = 0.0;
  (cam->transformMat).m[0][3] = 0.0;
  (cam->transformMat).m[3][2] = fVar1;
  (cam->transformMat).m[3][3] = 1.0;
  SetSomeMemoryMatrix((D3DXVECTOR3 *)&(CurrentCameraStruct->transformMat).field1);
  return;
}




void FUN_000f84a0(int param_1,ndShader *param_2)

{
  if (*(int *)(param_1 + 0x1c0) != 0) {
    if ((*(char *)(param_1 + 0x1cb) != '\0') && (*(char *)(param_1 + 0x1c7) != -1)) {
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
      Graphics::RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
      D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,0);
      Graphics::RenderState.zWriteEnabled = 0;
      D3D8::D3DDevice_SetRenderState_ZEnable(1);
      Graphics::EnableAlphaBlend();
    }
    DAT_005078d0 = FUN_0015b670(param_2);
    if (DAT_005078d0 < 7) {
      FUN_000f7420(*(uint *)((int)param_2->shaderStart + 0xd4) >> 8,DAT_005078d0);
      return;
    }
    DAT_005078d0 = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Graphics::SetupPipelineCallbacks(void)

{
  SomeMatrices = (SomeMatrices *)FUN_000f7330(0x1f400,0x20);
  SomeMatricesSize = 0x1f400;
  SomeMatricesAlt = (D3DXMATRIX *)SomeMatrices;
  SomeMatricesAlt2 = (D3DXMATRIX *)SomeMatrices;
  g_NewAssetBuffer_ = malloc_(0x60);
  g_NewAssetBuffer_->head = g_NewAssetBuffer_->values;
  g_NewAssetBuffer_->tail = g_NewAssetBuffer_->values;
  g_NewAssetBuffer_->valueSize = 8;
  g_NewAssetBuffer_->capacity = 10;
  g_NewAssetBuffer_->end = (Asset *)(g_NewAssetBuffer_->values[0].name + 0x50);
  callback4 = FUN_000f9b40;
  FUN_0015b2d0(FUN_000f9b90);
  FUN_0015b2e0(TexturePipelineCallback);
  FUN_0015b2f0(FUN_000f9c00);
  FUN_001565f0(FUN_000f9be0);
  FUN_00165ab0();
  SetUnknownCallbacks(malloc_,resource::genericDealloc);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void FUN_000f9b40(ndShader *param_1)

{
  if (DAT_005079e4 != '\0') {
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x207);
    Graphics::RenderState.zCmpFunc = D3DCMP_ALWAYS;
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,0);
    Graphics::RenderState.zWriteEnabled = 0;
    D3D8::D3DDevice_SetRenderState_ZEnable(1);
  }
  FUN_000f84a0((int)Graphics::CurrentModelBeingDrawn,param_1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Graphics::TexturePipelineCallback(DXTextureInstance *param_1,DWORD param_2)

{
  SetTextureStage(param_2,param_1);
  return;
}




void Graphics::InitialiseDirectX(void)

{
  int iVar1;
  uint videoFlags;
  
  InitialiseDXSettings(&g_DXContext);
  iVar1 = XAPILIB::XGetVideoStandard();
  runtime::Config::IsPal = (BOOL)(iVar1 == 3);
  videoFlags = XAPILIB::XGetVideoFlags();
  runtime::Config::Use60Hz = videoFlags & XC_VIDEO_FLAGS_PAL_60Hz    ;
  g_DXContext.vsyncFrames = 2;
  g_DXContext.backbufferCount = 1;
  videoFlags = XAPILIB::XGetVideoFlags();
  if ((videoFlags & XC_VIDEO_FLAGS_WIDESCREEN) != 0) {
    g_DXContext.widescreen = true;
  }
  if (g_DXContext.backBufferWidth == 640) {
    g_DXContext.use10x11PixelAspect = DAT_0042a54c == 0;
  }
  g_DXContext.field15_0x1d = DAT_0042a548;
  if (runtime::Config::Use60Hz != 0) {
    g_DXContext.refreshRate = 60;
  }
  CreateDirectXContext(&g_DXContext);
  D3D8::D3DDevice_SetVerticalBlankCallback(onVerticalBlank);
  FUN_000fc190();
  return;
}




void Graphics::BuildCameraMatrices(D3DXMATRIX *viewMatrix,D3DXMATRIX *projMatrix)

{
  vec3 *v;
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  vec3 someV;
  vec3 local_c8;
  vec3 local_bc;
  AffineTransform scalar_affine;
  AffineTransform proj;
  AffineTransform view;
  Quaternion quat1;
  Quaternion quat2;
  
  local_bc.x = (CurrentCameraStruct->forwards).x;
  local_bc.y = (CurrentCameraStruct->forwards).y;
  local_bc.z = (CurrentCameraStruct->forwards).z;
  v = GetSomeVec3();
  local_c8.y = (v->y + local_bc.y) * 0.5;
  local_c8.z = (v->z + local_bc.z) * 0.5;
  local_c8.x = (v->x + local_bc.x) * 0.5;
  fVar2 = local_c8.z * local_c8.z + local_c8.y * local_c8.y + local_c8.x * local_c8.x;
  if (fVar2 != 0.0) {
    fVar1 = (float10)invsqrt(fVar2);
    local_c8.x = (float)((float10)local_c8.x * fVar1);
    local_c8.y = (float)((float10)local_c8.y * fVar1);
    local_c8.z = (float)((float10)local_c8.z * fVar1);
  }
  fVar2 = local_bc.z + Left.z;
  fVar4 = local_bc.x + Left.x;
  fVar3 = local_bc.y + Left.y;
  if (0.001 <= fVar2 * fVar2 + fVar3 * fVar3 + fVar4 * fVar4) {
    someV.x = fVar4 * 0.5;
    someV.y = fVar3 * 0.5;
    someV.z = fVar2 * 0.5;
    fVar2 = someV.z * someV.z + someV.y * someV.y + someV.x * someV.x;
    if (fVar2 != 0.0) {
      fVar1 = (float10)invsqrt(fVar2);
      someV.x = (float)((float10)someV.x * fVar1);
      someV.y = (float)((float10)someV.y * fVar1);
      someV.z = (float)((float10)someV.z * fVar1);
    }
  }
  else {
    someV.x = Left.x;
    someV.y = Left.y;
    someV.z = Left.z;
  }
  Quaternion::fromAToB(&local_c8,&local_bc,&quat1);
  Quaternion::fromAToB(&someV,&local_bc,&quat2);
  scalar_affine.m[0][0] = 0.5;
  scalar_affine.m[0][1] = 0.0;
  scalar_affine.m[0][2] = 0.0;
  scalar_affine.m[0][3] = 0.0;
  scalar_affine.m[1][0] = 0.0;
  scalar_affine.m[1][1] = -0.5;
  scalar_affine.m[1][2] = 0.0;
  scalar_affine.m[1][3] = 0.0;
  scalar_affine.m[2][0] = 0.0;
  scalar_affine.m[2][1] = 0.0;
  scalar_affine.m[2][2] = 0.0;
  scalar_affine.m[2][3] = 0.0;
  AffineTransform::fromQuaternion(&proj,&quat1);
  AffineTransform::fromQuaternion(&view,&quat2);
  leftCombineTransforms(&proj,&scalar_affine,&proj);
  leftCombineTransforms(&view,&scalar_affine,&view);
  fVar2 = 0.0;
  fVar3 = 1.0;
  scalar_affine.m[0][0] = 1.0;
  scalar_affine.m[0][1] = 0.0;
  scalar_affine.m[0][2] = 0.0;
  scalar_affine.m[0][3] = 0.5;
  scalar_affine.m[1][0] = 0.0;
  scalar_affine.m[1][1] = 1.0;
  scalar_affine.m[1][2] = 0.0;
  scalar_affine.m[1][3] = 0.5;
  scalar_affine.m[2][0] = 0.0;
  scalar_affine.m[2][1] = 0.0;
  scalar_affine.m[2][2] = 1.0;
  scalar_affine.m[2][3] = 1.0;
  leftCombineTransforms(&proj,&scalar_affine,&proj);
  leftCombineTransforms(&view,&scalar_affine,&view);
  projMatrix->m[0][0] = proj.m[0][0];
  projMatrix->m[0][1] = proj.m[0][1];
  projMatrix->m[0][2] = proj.m[0][2];
  projMatrix->m[0][3] = proj.m[0][3];
  projMatrix->m[1][0] = proj.m[1][0];
  projMatrix->m[1][1] = proj.m[1][1];
  projMatrix->m[1][2] = proj.m[1][2];
  projMatrix->m[1][3] = proj.m[1][3];
  projMatrix->m[2][0] = proj.m[2][0];
  projMatrix->m[2][1] = proj.m[2][1];
  projMatrix->m[2][2] = proj.m[2][2];
  projMatrix->m[2][3] = proj.m[2][3];
  projMatrix->m[3][0] = fVar2;
  projMatrix->m[3][1] = fVar2;
  projMatrix->m[3][2] = fVar2;
  projMatrix->m[3][3] = fVar3;
  viewMatrix->m[0][0] = view.m[0][0];
  viewMatrix->m[0][1] = view.m[0][1];
  viewMatrix->m[0][2] = view.m[0][2];
  viewMatrix->m[0][3] = view.m[0][3];
  viewMatrix->m[1][0] = view.m[1][0];
  viewMatrix->m[1][1] = view.m[1][1];
  viewMatrix->m[1][2] = view.m[1][2];
  viewMatrix->m[1][3] = view.m[1][3];
  viewMatrix->m[2][0] = view.m[2][0];
  viewMatrix->m[2][1] = view.m[2][1];
  viewMatrix->m[2][2] = view.m[2][2];
  viewMatrix->m[2][3] = view.m[2][3];
  viewMatrix->m[3][0] = fVar2;
  viewMatrix->m[3][1] = fVar2;
  viewMatrix->m[3][2] = fVar2;
  viewMatrix->m[3][3] = fVar3;
  return;
}




void Graphics::UpdateMatrices(vec3 *param_1,bool param_2)

{
  DirectXShaderConstant *constant;
  vec3 v;
  AffineTransform local_c0;
  ShaderConstant shader_constant;
  D3DXMATRIX local_80;
  D3DXMATRIX local_40;
  
  UpdateFog_();
  v.x = (CurrentCameraStruct->affineT).m[0][0];
  v.y = (CurrentCameraStruct->affineT).m[1][0];
  v.z = (CurrentCameraStruct->affineT).m[2][0];
  SetGraphicsFlag0x80000000(param_2);
  SetSomeFlag1(false);
  FUN_00158f20(&v);
  constant = &ShaderConstants::Black;
  if (UseDefaultPixelC0 == 0) {
    constant = &SetShaderConstant;
  }
  SetPixelShaderC0(constant);
  FUN_000fd850(&shader_constant,param_1);
  FUN_00156f70(&shader_constant);
  BuildCameraMatrices(&local_40,&local_80);
  SetMatrix1(&local_80);
  SetMatrix2(&local_40);
  return;
}




void Graphics::SetModelSubres0x3Values(vec3 *param_1)

{
  uint uVar1;
  vec3 *pvVar2;
  char i;
  ReflectionData *ref_data;
  float fVar3;
  
  SetRoomLighting(RoomLightingColour.x,RoomLightingColour.y,RoomLightingColour.z,0x3f800000);
  ModelInstance::ClearBinaryEntry();
  fVar3 = FLOAT_0042a580;
  if (UseDefaultPixelC0 == 0) {
    fVar3 = FLOAT_00509b4c;
  }
  ::ReflectionData::setField0x8((ReflectionData *)&DAT_00509ab0,1);
  FUN_001592a0(&DAT_00509ab0,fVar3,fVar3,fVar3,0x3f800000);
  pvVar2 = GetSomeVec3();
  FUN_001592e0(&DAT_00509ab0,pvVar2);
  FUN_00158d80(&DAT_00509ab0);
  i = '\0';
  do {
    if (Model::Subres0x3Values[i] != (Subres0x3Val *)0x0) goto LAB_000fd498;
    i = i + '\x01';
  } while (i < '(');
  i = -1;
LAB_000fd498:
  if (i != -1) {
    ref_data = ReflectionData;
    do {
      if (0x50984f < (int)ref_data) break;
      ::ReflectionData::setField0x8(ref_data,0xe);
      FUN_00159300(ref_data,&Model::Subres0x3Values[i]->field_0x40);
      FUN_00159330(ref_data,*(float *)&Model::Subres0x3Values[i]->field_0x70 * 0.5,
                   *(undefined4 *)&Model::Subres0x3Values[i]->field_0x70);
      uVar1 = *(uint *)&Model::Subres0x3Values[i]->field_0x78;
      FUN_001592a0(ref_data,(float)(uVar1 & 0xff) * 0.003921569,
                   (float)(uVar1 >> 8 & 0xff) * 0.003921569,
                   (float)(uVar1 >> 0x10 & 0xff) * 0.003921569,(float)(uVar1 >> 0x18) * 0.003921569)
      ;
      FUN_00158d80(ref_data);
      do {
        i = i + '\x01';
        if ('\'' < i) {
          i = -1;
          break;
        }
      } while (Model::Subres0x3Values[i] == (Subres0x3Val *)0x0);
      ref_data = ref_data + 1;
    } while (i != -1);
  }
  UpdateMatrices(param_1,true);
  return;
}




void Graphics::UpdateFog_(void)

{
  bool bVar1;
  
  if ((DAT_00509b00 == 0) && (DAT_00509afc != 0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  FUN_00156ea0(bVar1);
  FUN_00156ed0(DAT_00509b08,DAT_00509b0c,DAT_00509b04,DAT_00509b05,DAT_00509b06,DAT_00509b07);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_000fd850(ShaderConstant *param_1,vec3 *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  if (Graphics::UseDefaultPixelC0 != 0) {
    param_1->field0_0x0 = FLOAT_0042a560;
    param_1->field1_0x4 = FLOAT_0042a564;
    param_1->field2_0x8 = FLOAT_0042a568;
    param_1->field3_0xc = FLOAT_0042a56c;
    return;
  }
  FUN_000fee90(param_2,param_1);
  param_1->field0_0x0 = param_1->field0_0x0 * vec3_00509b20.x;
  param_1->field1_0x4 = param_1->field1_0x4 * vec3_00509b20.y;
  param_1->field2_0x8 = vec3_00509b20.z * param_1->field2_0x8;
  if (DAT_005120f0 != 0) {
    iVar3 = 0;
    piVar1 = &DAT_00511b98;
    while (*piVar1 == 0) {
      piVar1 = piVar1 + 0xb;
      iVar3 = iVar3 + 1;
      if (0x512117 < (int)piVar1) {
        return;
      }
    }
    while (-1 < iVar3) {
      iVar2 = iVar3 * 0x2c;
      fVar5 = param_2->y - *(float *)((int)&vec3_00511b74 + iVar2);
      fVar4 = param_2->x - *(float *)(&DAT_00511b70 + iVar2);
      fVar6 = param_2->z - *(float *)((int)&vec3_00511b74 + iVar2 + 4);
      fVar4 = fVar4 * fVar4 + fVar5 * fVar5 + fVar6 * fVar6;
      if (0.0 < fVar4) {
        fVar4 = (1.0 / fVar4) * 5000.0;
        param_1->field0_0x0 = fVar4 + param_1->field0_0x0;
        param_1->field1_0x4 = param_1->field1_0x4 + fVar4;
        param_1->field2_0x8 = fVar4 + param_1->field2_0x8;
        param_1->field3_0xc = param_1->field3_0xc + fVar4;
      }
      iVar3 = iVar3 + 1;
      if (0x1f < iVar3) {
        return;
      }
      piVar1 = &DAT_00511b98 + iVar3 * 0xb;
      while (*piVar1 == 0) {
        piVar1 = piVar1 + 0xb;
        iVar3 = iVar3 + 1;
        if (0x512117 < (int)piVar1) {
          return;
        }
      }
    }
  }
  return;
}




vec3 * Graphics::GetSomeVec3(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  SomeVec3.x = 0.0;
  SomeVec3.y = 0.0;
  SomeVec3.z = 0.0;
  fVar2 = UnknownAngle1;
  fVar1 = UnknownAngle2;
  if (UseDefaultPixelC0 != 0) {
    fVar2 = FLOAT_0042a584 * 0.017453292;
    fVar1 = FLOAT_0042a588 * 0.017453292;
  }
  Math::MovePointForwards(&SomeVec3,fVar2,fVar1 + 3.1415927,1.0);
  if (DAT_00509b58 != 0) {
    Maths::InvertAffineMatrix
              ((D3DXMATRIX *)&CurrentCameraStruct->field_0xd8,(D3DMATRIX *)&stack0xffffffd0);
    fVar2 = SomeVec3.z * (float)local_28;
    fVar3 = SomeVec3.y * (float)local_2c;
    fVar1 = SomeVec3.y * (float)local_c;
    SomeVec3.y = SomeVec3.y * (float)local_1c + SomeVec3.z * (float)local_18 +
                 SomeVec3.x * (float)local_20;
    SomeVec3.z = fVar1 + SomeVec3.z * (float)local_8 + SomeVec3.x * (float)local_10;
    SomeVec3.x = fVar2 + SomeVec3.x * (float)local_30 + fVar3;
    D3DX8::D3DXVec3Normalize(&SomeVec3,&SomeVec3);
  }
  return &SomeVec3;
}




void __fastcall Graphics::MatrixCpy(D3DMATRIX *dst,D3DMATRIX *src)

{
  float fVar1;
  
  dst->m[0][0] = src->m[0][0];
  dst->m[0][1] = src->m[1][0];
  dst->m[0][2] = src->m[2][0];
  dst->m[1][0] = src->m[0][1];
  dst->m[1][1] = src->m[1][1];
  dst->m[1][2] = src->m[2][1];
  dst->m[2][0] = src->m[0][2];
  dst->m[2][1] = src->m[1][2];
  dst->m[2][2] = src->m[2][2];
  dst->m[3][0] = src->m[0][3];
  dst->m[3][1] = src->m[1][3];
  fVar1 = src->m[2][3];
  dst->m[2][3] = 0.0;
  dst->m[1][3] = 0.0;
  dst->m[0][3] = 0.0;
  dst->m[3][2] = fVar1;
  dst->m[3][3] = 1.0;
  return;
}




void FreeOldTextures_(void)

{
  int iVar1;
  DrawingData *pDVar2;
  
  pDVar2 = g_drawingData;
  do {
    iVar1 = *(int *)pDVar2;
    if ((((iVar1 != 0) && (1 < (byte)pDVar2->field_0x5)) &&
        ((*(int *)(iVar1 + 0x28) != 0 ||
         (((*(int *)(iVar1 + 8) != 0 && (*(int *)(iVar1 + 0x14) == 0)) &&
          (*(uint *)(*(int *)(iVar1 + 8) + 8) <= *(uint *)(*(int *)(iVar1 + 8) + 0xc))))))) &&
       (*(int *)(iVar1 + 0x20) < 1)) {
      FUN_001072b0();
      *(int *)pDVar2 = 0;
      pDVar2->textureBankIndex = '\0';
      pDVar2->field_0x5 = 0;
    }
    pDVar2 = (DrawingData *)&pDVar2[3].field_0x1f;
  } while ((int)pDVar2 < 0x50dfb0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Graphics::RunDrawingCallbacks(void)

{
  int iVar1;
  DrawingData *pDVar2;
  byte index;
  
  pDVar2 = g_drawingData;
  do {
    if (*(int *)pDVar2 != 0) {
      index = pDVar2->textureBankIndex;
      if ((ModelTextureBanks[index].someCallback != (code *)0x0) &&
         (iVar1 = (*ModelTextureBanks[index].someCallback)
                            (ModelTextureBanks[index].modelDescriptor,
                             ModelTextureBanks[index].indexInModel), iVar1 != 0)) {
        FUN_00107360();
      }
    }
    pDVar2 = (DrawingData *)&pDVar2[3].field_0x1f;
  } while ((int)pDVar2 < 0x50dfb0);
  return;
}




void UpdateDrawingData___(void)

{
  int *piVar1;
  DrawingData_ptr_5_undefined pcVar2;
  
  pcVar2 = &g_drawingData[0].field_0x5;
  do {
    if ((*(int *)ADJ(pcVar2) != 0) && (*pcVar2 == '\x03')) {
      piVar1 = (int *)(*(int *)ADJ(pcVar2) + 0x18);
      *piVar1 = *piVar1 + 1;
      *pcVar2 = '\x02';
    }
    pcVar2 = pcVar2 + 0x88;
  } while ((int)pcVar2 < 0x50dfb5);
  UINT_0050dd8c = 2;
  return;
}




void UnloadGraphicsTextures_(void)

{
  undefined2 *puVar1;
  Buffer<> *mem;
  undefined4 uVar2;
  Buffer<Some0x40> *lpMem;
  int iVar3;
  HeapTableEntry *pHVar4;
  undefined2 *puVar5;
  
  FUN_001134a0();
  if (g_bufferTextureMaybeSomething != (Buffer<> *)0x0) {
    puVar1 = g_bufferTextureMaybeSomething->tail;
    mem = g_bufferTextureMaybeSomething;
    for (puVar5 = g_bufferTextureMaybeSomething->head; g_bufferTextureMaybeSomething = mem,
        puVar5 < puVar1; puVar5 = puVar5 + 2) {
      FUN_0004b770();
      mem = g_bufferTextureMaybeSomething;
    }
    iVar3 = FindHeapOf(mem);
    uVar2 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
      pHVar4 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar4 = g_HeapTableBase + iVar3;
    }
    runtime::CurrentHeapToAllocateFrom = iVar3;
    XAPILIB::HeapFree(pHVar4->heapHandle,0,mem);
    lpMem = g_bufferSome0x40;
    g_bufferTextureMaybeSomething = (Buffer<> *)0x0;
    runtime::CurrentHeapToAllocateFrom = uVar2;
    iVar3 = FindHeapOf(g_bufferSome0x40);
    uVar2 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
      pHVar4 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar4 = g_HeapTableBase + iVar3;
    }
    runtime::CurrentHeapToAllocateFrom = iVar3;
    XAPILIB::HeapFree(pHVar4->heapHandle,0,lpMem);
    g_bufferSome0x40 = (Buffer<Some0x40> *)0x0;
    runtime::CurrentHeapToAllocateFrom = uVar2;
  }
  if (g_someTexture != (D3DResource *)0x0) {
    D3D8::D3DResource_Release(g_someTexture);
    g_someTexture = (D3DResource *)0x0;
    g_someTexture2 = (D3DResource *)0x0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_001151f0(TextureMaybeSomething *param_1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  float *pfVar10;
  float fVar11;
  float local_4;
  
  fVar11 = 0.0;
  uVar7 = param_1->field0_0x0;
  local_4 = 0.0;
  if (uVar7 != 0) {
    pfVar10 = param_1->field1_0x4;
    pfVar8 = pfVar10 + 5;
    iVar9 = (uVar7 - 1) / 10 + 1;
    do {
      pfVar1 = pfVar8 + -3;
      fVar5 = *pfVar8;
      fVar6 = *pfVar10;
      pfVar2 = pfVar8 + -2;
      pfVar3 = pfVar8 + -4;
      pfVar4 = pfVar8 + -1;
      pfVar10 = pfVar10 + 0x78;
      pfVar8 = pfVar8 + 0x78;
      iVar9 = iVar9 + -1;
      fVar11 = (*pfVar1 - fVar5) * (*pfVar1 - fVar5) + (fVar6 - *pfVar2) * (fVar6 - *pfVar2) +
               (*pfVar3 - *pfVar4) * (*pfVar3 - *pfVar4) + fVar11;
      local_4 = fVar11;
    } while (iVar9 != 0);
  }
  fVar11 = (float)(int)uVar7;
  if ((int)uVar7 < 0) {
    fVar11 = fVar11 + 4.2949673e+09;
  }
  if (0.0001 <= (local_4 * 10.0) / fVar11) {
    return 0;
  }
  param_1->field444_0x1e6 = '\0';
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void NormaliseGraphicsCamera_(void)

{
  ushort *puVar1;
  Entry0xdType EVar2;
  TextureMaybeSomething *extraout_EAX;
  void *pvVar3;
  uint uVar4;
  float *pfVar5;
  TextureMaybeSomething *pTVar6;
  int iVar7;
  ushort *puVar8;
  Buffer<> *pBVar9;
  TextureMaybeSomething *pTVar10;
  ModelDescriptor *desc;
  TextureMaybeSomething *pTVar11;
  int iVar12;
  Entry0xd *entry;
  uint uVar13;
  float *pfVar14;
  float10 fVar15;
  int local_50;
  void *local_4c;
  TextureMaybeSomething *local_48;
  ModelDescriptor *local_44;
  TextureMaybeSomething *local_40;
  TextureMaybeSomething *local_3c;
  float local_38;
  Subresource0xd *res0xd;
  float local_30;
  float local_2c;
  float local_28;
  vec3 local_24;
  float local_18;
  float local_14;
  float local_10;
  vec3 rangeV;
  Model *model;
  
  if (((Game::SceneInfo.backgrounds.head != (background_0x934_conflict3)0x0) &&
      (model = ADJ(Game::SceneInfo.backgrounds.head).avatar.modelInstance, model != (Model *)0x0))
     && (desc = model->descriptor, desc != (ModelDescriptor *)0x0)) {
    res0xd = desc->runtimeCtx->subresource0xd;
    rangeV.x = (Background::MaxVector.x + Background::MinVector.x) * 0.5;
    rangeV.y = (Background::MaxVector.y + Background::MinVector.y) * 0.5;
    rangeV.z = (Background::MaxVector.z + Background::MinVector.z) * 0.5;
    if (res0xd != (Subresource0xd *)0x0) {
      local_48 = (TextureMaybeSomething *)0x0;
      local_44 = desc;
      if (res0xd->numEntries != 0) {
        local_50 = 0;
        do {
          EVar2 = *(Entry0xdType *)((int)(res0xd->entries->positions + 4) + local_50);
          entry = (Entry0xd *)((int)&res0xd->entries->positions[0].x + local_50);
          if (((EVar2 == 1) || (EVar2 == 2)) || ((EVar2 == 3 || (EVar2 == 8)))) {
            pTVar6 = (TextureMaybeSomething *)FUN_00050880(entry,desc);
            if (pTVar6 != (TextureMaybeSomething *)0x0) {
              pTVar6->field121_0x94 = FUN_00114910;
              pTVar6->field125_0xa4 = 1;
              pTVar6->field123_0x9c = FUN_001151f0;
              pTVar6->field122_0x98 = FUN_001152c0;
              local_2c = *(float *)&pTVar6->field_0x7c - rangeV.y;
              local_28 = *(float *)&pTVar6->field_0x80 - rangeV.z;
              local_30 = *(float *)&pTVar6->field_0x78 - rangeV.x;
              local_38 = local_28 * local_28 + local_2c * local_2c + local_30 * local_30;
              if (local_38 != 0.0) {
                fVar15 = (float10)invsqrt(local_38);
                local_30 = (float)((float10)local_30 * fVar15);
                local_2c = (float)((float10)local_2c * fVar15);
                local_28 = (float)((float10)local_28 * fVar15);
              }
              pTVar6->field_0x1e9 = 1;
              *(float *)&pTVar6->field_0x3c = local_30;
              *(float *)&pTVar6->field_0x40 = local_2c;
              *(float *)&pTVar6->field_0x44 = local_28;
              if (entry->entryType == 8) {
                pTVar6->field_0x1e7 = 0;
              }
LAB_0011585a:
              Graphics::PushTextureMaybeSomething(pTVar6);
            }
          }
          else if (EVar2 == 7) {
            FUN_00050940(entry);
            if (extraout_EAX != (TextureMaybeSomething *)0x0) {
              extraout_EAX->field_0x1e7 = 0;
              extraout_EAX->field121_0x94 = &LAB_001145f0;
              extraout_EAX->field125_0xa4 = 1;
              extraout_EAX->field124_0xa0 = &LAB_00114580;
              extraout_EAX->field_0x1eb = 0;
              extraout_EAX->field_0x1ec = 1;
              *(float *)&extraout_EAX->field_0x1c = 0.01;
              extraout_EAX->field_0x1ed = 1;
              extraout_EAX->field452_0x1ee = '\x01';
              pTVar6 = extraout_EAX;
              goto LAB_0011585a;
            }
          }
          else if (EVar2 == 6) {
            pvVar3 = malloc_(0x18);
            local_4c = pvVar3;
            uVar4 = FUN_000509e0(desc,entry,&local_4c);
            uVar13 = 0;
            if (uVar4 != 0) {
              do {
                *(code **)(*(int *)((int)pvVar3 + uVar13 * 4) + 0x94) = FUN_00114910;
                *(undefined4 *)(*(int *)((int)pvVar3 + uVar13 * 4) + 0xa4) = 1;
                *(code **)(*(int *)((int)pvVar3 + uVar13 * 4) + 0x9c) = FUN_001151f0;
                *(code **)(*(int *)((int)pvVar3 + uVar13 * 4) + 0x98) = FUN_001152c0;
                *(undefined1 *)(*(int *)((int)pvVar3 + uVar13 * 4) + 0x1e7) = 0;
                *(float *)(*(int *)((int)pvVar3 + uVar13 * 4) + 0x1c) = 0.05;
                Graphics::PushTextureMaybeSomething
                          (*(TextureMaybeSomething **)((int)pvVar3 + uVar13 * 4));
                uVar13 = uVar13 + 1;
              } while (uVar13 < uVar4);
            }
            FUN_00050990();
            desc = local_44;
          }
          else if (EVar2 == 5) {
            FUN_00050cc0(desc,&local_40,&local_3c);
            pTVar6 = local_40;
            FUN_0004c0b0();
            pTVar10 = local_3c;
            FUN_0004c0b0();
            Graphics::PushTextureMaybeSomething(pTVar6);
            Graphics::PushTextureMaybeSomething(pTVar10);
            pTVar6->field123_0x9c = FUN_001151f0;
            pTVar10->field123_0x9c = FUN_001151f0;
            pTVar6->field122_0x98 = FUN_001152c0;
            pTVar10->field122_0x98 = FUN_001152c0;
            pTVar6->field_0x1eb = 0;
            pTVar10->field_0x1eb = 0;
            FUN_00113620(pTVar6);
          }
          else if ((EVar2 == 4) && (g_bufferSome0x40 != (Buffer<Some0x40> *)0x0)) {
            pfVar5 = (float *)FUN_000662f0(&g_bufferSome0x40);
            pfVar5[4] = entry->positions[0].x;
            pfVar5[5] = entry->positions[0].y;
            pfVar5[6] = entry->positions[0].z;
            pfVar5[7] = entry->positions[1].x;
            pfVar5[8] = entry->positions[1].y;
            pfVar5[9] = entry->positions[1].z;
            pfVar5[10] = entry->positions[2].x;
            pfVar5[0xb] = entry->positions[2].y;
            pfVar5[0xc] = entry->positions[2].z;
            pfVar5[0xd] = entry->positions[3].x;
            pfVar5[0xe] = entry->positions[3].y;
            pfVar5[0xf] = entry->positions[3].z;
            local_24.x = (pfVar5[0xc] - pfVar5[6]) * (pfVar5[8] - pfVar5[5]) -
                         (pfVar5[0xb] - pfVar5[5]) * (pfVar5[9] - pfVar5[6]);
            local_24.y = (pfVar5[9] - pfVar5[6]) * (pfVar5[10] - pfVar5[4]) -
                         (pfVar5[0xc] - pfVar5[6]) * (pfVar5[7] - pfVar5[4]);
            local_24.z = (pfVar5[0xb] - pfVar5[5]) * (pfVar5[7] - pfVar5[4]) -
                         (pfVar5[8] - pfVar5[5]) * (pfVar5[10] - pfVar5[4]);
            local_18 = local_24.x;
            local_14 = local_24.y;
            local_10 = local_24.z;
            D3DX8::D3DXVec3Normalize(&local_24,&local_24);
            *pfVar5 = local_24.x;
            pfVar5[1] = local_24.y;
            pfVar5[2] = local_24.z;
            pfVar5[3] = 0.0 - (pfVar5[6] * local_24.z + pfVar5[5] * local_24.y +
                              pfVar5[4] * local_24.x);
          }
          local_48 = (TextureMaybeSomething *)((int)local_48 + 1);
          local_50 = local_50 + 0x34;
        } while (local_48 < res0xd->numEntries);
      }
      if ((g_bufferSome0x40 != (Buffer<Some0x40> *)0x0) &&
         (g_bufferTextureMaybeSomething != (Buffer<> *)0x0)) {
        pTVar6 = (TextureMaybeSomething *)g_bufferSome0x40->head;
        pTVar10 = (TextureMaybeSomething *)g_bufferSome0x40->tail;
        pBVar9 = g_bufferTextureMaybeSomething;
        local_40 = pTVar10;
        if (pTVar6 < pTVar10) {
          do {
            pTVar11 = (TextureMaybeSomething *)pBVar9->head;
            local_3c = (TextureMaybeSomething *)pBVar9->tail;
            local_48 = pTVar6;
            if (pTVar11 < local_3c) {
              do {
                res0xd = *(Subresource0xd **)(pTVar11->field0_0x0 + 0x90);
                iVar7 = FUN_0015a440(pTVar11->field0_0x0 + 0x78,res0xd,&pTVar6->field_0x10,
                                     &pTVar6->field_0x1c,&pTVar6->field_0x28);
                if (iVar7 == 0) {
                  local_38 = *(float *)(pTVar11->field0_0x0 + 0x90);
                  iVar7 = FUN_0015a440(pTVar11->field0_0x0 + 0x78,local_38,&pTVar6->field_0x1c,
                                       &pTVar6->field_0x28,&pTVar6->field_0x34);
                  if (iVar7 != 0) goto LAB_00115924;
                }
                else {
LAB_00115924:
                  uVar4 = pTVar11->field0_0x0;
                  puVar8 = *(ushort **)(uVar4 + 0x150);
                  if (*(int *)(puVar8 + 4) == *(int *)(puVar8 + 6)) {
                    iVar7 = (*(int *)(puVar8 + 4) - *(int *)(puVar8 + 2)) / (int)(uint)*puVar8;
                    iVar12 = (uint)puVar8[1] + iVar7;
                    puVar8 = (ushort *)AllocateMoreAStruct_33(iVar12 * (uint)*puVar8 + 0x10,puVar8);
                    puVar1 = puVar8 + 8;
                    *(ushort **)(puVar8 + 6) = (ushort *)((uint)*puVar8 * iVar12 + (int)puVar1);
                    *(ushort **)(puVar8 + 2) = puVar1;
                    *(ushort **)(puVar8 + 4) = (ushort *)((uint)*puVar8 * iVar7 + (int)puVar1);
                    *(ushort **)(uVar4 + 0x150) = puVar8;
                    pTVar6 = local_48;
                  }
                  pfVar5 = *(float **)(puVar8 + 4);
                  *(uint *)(puVar8 + 4) = (uint)*puVar8 + (int)pfVar5;
                  pTVar10 = pTVar6;
                  pfVar14 = pfVar5;
                  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                    *pfVar14 = (float)pTVar10->field0_0x0;
                    pTVar10 = (TextureMaybeSomething *)&pTVar10->field1_0x4;
                    pfVar14 = pfVar14 + 1;
                  }
                  uVar4 = pTVar11->field0_0x0;
                  if (*(float *)(uVar4 + 0x7c) * pfVar5[1] + *(float *)(uVar4 + 0x78) * *pfVar5 +
                      *(float *)(uVar4 + 0x80) * pfVar5[2] + pfVar5[3] < 0.0) {
                    *pfVar5 = 0.0 - *pfVar5;
                    pfVar5[1] = 0.0 - pfVar5[1];
                    pfVar5[2] = 0.0 - pfVar5[2];
                    pfVar5[3] = 0.0 - pfVar5[3];
                  }
                }
                pTVar11 = (TextureMaybeSomething *)&pTVar11->field1_0x4;
                pBVar9 = g_bufferTextureMaybeSomething;
                pTVar10 = local_40;
              } while (pTVar11 < local_3c);
            }
            pTVar6 = (TextureMaybeSomething *)&pTVar6->field_0x40;
          } while (pTVar6 < pTVar10);
        }
      }
    }
  }
  return;
}




void Graphics::PushTextureMaybeSomething(TextureMaybeSomething *param_1)

{
  undefined4 *puVar1;
  
  if (g_bufferTextureMaybeSomething != (Buffer<> *)0x0) {
    if (g_bufferTextureMaybeSomething->tail == g_bufferTextureMaybeSomething->end) {
      g_bufferTextureMaybeSomething =
           (Buffer<> *)runtime::ExtendArray((Buffer *)g_bufferTextureMaybeSomething);
    }
    puVar1 = (undefined4 *)g_bufferTextureMaybeSomething->tail;
    g_bufferTextureMaybeSomething->tail =
         (undefined2 *)((uint)g_bufferTextureMaybeSomething->valueSize + (int)puVar1);
    *puVar1 = param_1;
    FUN_0004c000(param_1);
    FUN_0004c0e0((CurtainAlloc *)param_1);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Graphics::RenderSomethingLeadsToVS0xe(uint param_1)

{
  Model *pMVar1;
  ModelDescriptor *pMVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  BOOL BVar6;
  int *piVar7;
  
  if ((((Game::SceneInfo.backgrounds.head != (background_0x934_conflict3)0x0) &&
       (pMVar1 = ADJ(Game::SceneInfo.backgrounds.head).avatar.modelInstance, pMVar1 != (Model *)0x0)
       ) && (pMVar2 = pMVar1->descriptor, pMVar2 != (ModelDescriptor *)0x0)) &&
     (g_bufferTextureMaybeSomething != (Buffer<> *)0x0)) {
    piVar3 = (int *)g_bufferTextureMaybeSomething->tail;
    piVar7 = (int *)g_bufferTextureMaybeSomething->head;
    piVar4 = piVar7;
    if (((int)piVar3 - (int)piVar7) / (int)(uint)g_bufferTextureMaybeSomething->valueSize != 0) {
      for (; piVar4 < piVar3; piVar4 = piVar4 + 1) {
        if (((*(byte *)(*piVar4 + 0x1ed) == param_1) && (*(char *)(*piVar4 + 0x1e7) != '\0')) &&
           (iVar5 = FUN_00114090(), iVar5 != 0)) {
          FUN_0005da50();
          FUN_0005deb0();
          FUN_0005dfa0(pMVar2->runtimeCtx->subres0x12);
          FUN_0005df30();
        }
      }
      useVertexShader0xe();
      for (; piVar7 < piVar3; piVar7 = piVar7 + 1) {
        iVar5 = *piVar7;
        if ((*(byte *)(iVar5 + 0x1ed) == param_1) &&
           ((*(int *)(iVar5 + 0x1e0) != 0 ||
            (BVar6 = AABBvsFrustum((GraphicsCamera *)&CurrentCameraStruct->field_0x138,
                                   (vec3 *)(iVar5 + 0x48),(vec3 *)(iVar5 + 0x54),
                                   &CurrentCameraStruct->field_0x1e0), BVar6 != 0)))) {
          if (*(char *)(*piVar7 + 0x1ec) == '\0') {
            DrawVS0xdAND0xe(*piVar7);
          }
          else {
            FUN_0005d710();
          }
        }
      }
      D3D8::D3DDevice_SetRenderState_TwoSidedLighting(0);
    }
  }
  return;
}




void Graphics::CleanupResources_(void)

{
  float fVar1;
  int *mem;
  undefined4 uVar2;
  int iVar3;
  HeapTableEntry *pHVar4;
  int *piVar5;
  
  piVar5 = burnups;
  mem = burnups;
  if (0x10 < (int)NumBurnups) {
    for (; mem = burnups, piVar5 != (int *)0x0; piVar5 = (int *)piVar5[1]) {
      if (piVar5[0xc] != 0) {
        piVar5[0xc] = 0;
        NumBurnups = NumBurnups + -1;
      }
    }
  }
  while (mem != (int *)0x0) {
    piVar5 = mem;
    if ((mem[0xc] == 0) &&
       (fVar1 = (float)mem[0xb], mem[0xb] = (int)(fVar1 - 0.01), fVar1 - 0.01 < 0.0)) {
      piVar5 = (int *)*mem;
      D3D8::D3DResource_Release((D3DResource *)mem[8]);
      if (*mem != 0) {
        *(int *)(*mem + 4) = mem[1];
      }
      if ((int *)mem[1] != (int *)0x0) {
        *(int *)mem[1] = *mem;
      }
      *mem = 0;
      mem[1] = 0;
      iVar3 = FindHeapOf(mem);
      uVar2 = runtime::CurrentHeapToAllocateFrom;
      if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
        pHVar4 = (HeapTableEntry *)0x0;
      }
      else {
        pHVar4 = g_HeapTableBase + iVar3;
      }
      runtime::CurrentHeapToAllocateFrom = iVar3;
      XAPILIB::HeapFree(pHVar4->heapHandle,0,mem);
      runtime::CurrentHeapToAllocateFrom = uVar2;
    }
    mem = (int *)piVar5[1];
  }
  return;
}




void UnloadBurnups(void)

{
  int *mem;
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  mem = burnups;
  while (mem != (int *)0x0) {
    burnups = mem;
    D3D8::D3DResource_Release((D3DResource *)mem[8]);
    if (*mem != 0) {
      *(int *)(*mem + 4) = mem[1];
    }
    if ((int *)mem[1] != (int *)0x0) {
      *(int *)mem[1] = *mem;
    }
    *mem = 0;
    mem[1] = 0;
    iVar2 = FindHeapOf(mem);
    uVar1 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
      pHVar3 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar3 = g_HeapTableBase + iVar2;
    }
    runtime::CurrentHeapToAllocateFrom = iVar2;
    XAPILIB::HeapFree(pHVar3->heapHandle,0,mem);
    mem = burnups;
    runtime::CurrentHeapToAllocateFrom = uVar1;
  }
  burnups = mem;
  ModelSubresource0x12 = (TilesSubresource *)0x0;
  NumBurnups = (undefined *)0x0;
  return;
}




void renderBurnups(void)

{
  float fVar1;
  uint64_t uVar2;
  undefined4 local_8;
  undefined4 local_4;
  int burnup;
  
  if (ModelSubresource0x12 != (TilesSubresource *)0x0) {
    Graphics::UseBurnupRenderer();
    for (burnup = burnups; burnup != 0; burnup = *(int *)(burnup + 4)) {
      local_4 = *(uint *)(burnup + 0x28);
      if (*(int *)(burnup + 0x30) == 0) {
        fVar1 = 0.0;
        local_8 = (float)(local_4 >> 0x18) * *(float *)(burnup + 0x2c);
        if ((local_8 < 0.0) || (fVar1 = 255.0, 255.0 < local_8)) {
          local_8 = fVar1;
        }
        uVar2 = float10::to_uint64_t((float10)local_8);
        local_4 = CONCAT13((char)uVar2,(undefined3)local_4);
      }
      DrawSubresource0x12(ModelSubresource0x12,(vec3 *)(burnup + 0x14),(vec3 *)(burnup + 8),
                          *(D3DBaseTexture **)(burnup + 0x20),*(float *)(burnup + 0x24),local_4,'\0'
                         );
    }
    D3D8::D3DDevice_SetRenderState_ZBias(0);
    D3D8::D3DDevice_SetRenderState_CullMode(0);
    D3D8::D3DDevice_SetRenderState_MultiSampleAntiAlias(0);
    D3D8::D3DDevice_SetRenderState_MultiSampleMode(0);
    D3D8::D3DDevice_SetRenderState_MultiSampleRenderTargetMode(0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void burnupInit(avatar *param_1)

{
  MalloccdGraphicsEye *pMVar1;
  undefined **ppuVar2;
  undefined **ppuVar3;
  
  pMVar1 = FUN_00116530(param_1);
  ppuVar2 = &burnupsSentinel;
  if (burnups != 0) {
    ppuVar3 = (undefined **)&burnups;
    do {
      ppuVar2 = (undefined **)*ppuVar3;
      ppuVar3 = ppuVar2 + 1;
    } while (ppuVar2[1] != (undefined *)0x0);
  }
  ppuVar2[1] = (undefined *)pMVar1;
  *(undefined ***)pMVar1 = ppuVar2;
  *(undefined4 *)&pMVar1->field_0x4 = 0;
  NumBurnups = NumBurnups + 1;
  return;
}




void CreateGradientTexture(void)

{
  uint uVar1;
  uint *puVar2;
  D3DLOCKED_RECT rect;
  D3DSURFACE_DESC desc;
  
  g_someTextureAtlas =
       D3D8::D3DDevice_CreateTexture2(0x1000,1,1,1,0,D3DFMT_A8R8G8B8,D3DRTYPE_TEXTURE);
  D3D::D3DTexture_GetLevelDesc(g_someTextureAtlas,0,&desc);
  D3D8::D3DTexture_LockRect(g_someTextureAtlas,0,&rect,0,0);
  uVar1 = 0;
  puVar2 = rect.pBits;
  do {
    *puVar2 = ((int)uVar1 >> 4 & 0xfU | (uVar1 & 0xf) << 8) << 8 | (int)uVar1 >> 8 & 0xfU;
    puVar2 = puVar2 + 1;
    uVar1 = uVar1 + 1;
  } while ((int)uVar1 < 0x1000);
  XGRAPHC::XGSwizzleRect(rect.pBits,0,(LPCRECT)0x0,rect.pBits,0x1000,1,(LPPOINT)0x0,4);
  Game::Subres0x14Instances[0].subres = (ModelSubresource0x14 *)0x0;
  Game::Subres0x14Instances[1].subres = (ModelSubresource0x14 *)0x0;
  Game::Subres0x14Instances[2].subres = (ModelSubresource0x14 *)0x0;
  Game::Subres0x14Instances[3].subres = (ModelSubresource0x14 *)0x0;
  Game::Subres0x14Instances[4].subres = (ModelSubresource0x14 *)0x0;
  Game::Subres0x14Instances[5].subres = (ModelSubresource0x14 *)0x0;
  Game::Subres0x14Instances[6].subres = (ModelSubresource0x14 *)0x0;
  Game::Subres0x14Instances[7].subres = (ModelSubresource0x14 *)0x0;
  Game::NumSubres0x14s = 0;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::InitialiseScreenSpaceQuads(void)

{
  uint width;
  QuadVertex_ptr_4_float pfVar1;
  uint height;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  width = (uint)g_DXContext.backBufferWidth;
  height = (uint)g_DXContext.backBufferHeight;
  pfVar1 = &g_globalQuadVertices[0].field1_0x4;
  do {
    fVar3 = 1.0;
    if ((pfVar1 == &g_globalQuadVertices[0].field1_0x4) ||
       (fVar4 = 1.0, pfVar1 == &g_globalQuadVertices[3].field1_0x4)) {
      fVar4 = 0.0;
    }
    if ((pfVar1 == &g_globalQuadVertices[0].field1_0x4) ||
       (pfVar1 == &g_globalQuadVertices[1].field1_0x4)) {
      fVar3 = 0.0;
    }
    fVar1 = fVar4 * (float)width;
    fVar2 = fVar3 * (float)height;
    ADJ(pfVar1)->field3_0xc = 1.0;
    ADJ(pfVar1).field0_0x0 = fVar1;
    ADJ(pfVar1)->field1_0x4 = fVar2;
    ADJ(pfVar1)->field2_0x8 = 0.0;
    ADJ(pfVar1)->field4_0x10 = DAT_00510648 + fVar4;
    ADJ(pfVar1)->field5_0x14 = DAT_0051064c + fVar3;
    ADJ(pfVar1)->field6_0x18 = (float)width * 0.1;
    ADJ(pfVar1)->field7_0x1c = 0.0;
    ADJ(pfVar1)->field8_0x20 = fVar1;
    ADJ(pfVar1)->field9_0x24 = 0.0;
    ADJ(pfVar1)->field10_0x28 = (float)height * 0.1;
    ADJ(pfVar1)->field11_0x2c = fVar2;
    pfVar1 = pfVar1 + 0xc;
  } while ((int)pfVar1 < 0x51064c);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void CreateWavyTexture_(void)

{
  undefined4 uVar1;
  char cVar2;
  void *pSource;
  int iVar3;
  HeapTableEntry *pHVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  float10 fVar8;
  unkbyte10 extraout_ST0;
  uint64_t uVar9;
  uint64_t uVar10;
  int local_c;
  DWORD rect;
  LPVOID local_4;
  
  g_wavyTexture =
       (D3DTexture *)
       D3D8::D3DDevice_CreateTexture2(0x80,0x80,1,1,0,D3DFMT_A8R8G8B8,D3DRTYPE_TEXTURE);
  D3D8::D3DTexture_LockRect(g_wavyTexture,0,&rect,0,0);
  pSource = malloc_(0x10000);
  local_c = 0;
  pcVar7 = (char *)((int)pSource + 1);
  do {
    fVar8 = (float10)fsin((float10)local_c * (float10)0.0078125 * (float10)62.831856);
    uVar9 = float10::to_uint64_t(fVar8 * (float10)-1.5);
    fVar8 = (float10)fcos(extraout_ST0);
    uVar10 = float10::to_uint64_t(fVar8 * (float10)-5.0);
    iVar5 = 0x80;
    pcVar6 = pcVar7;
    do {
      pcVar6[-1] = -1;
      *pcVar6 = '\x7f';
      pcVar6[1] = '\x7f';
      pcVar6[2] = '\x7f';
      iVar3 = FUN_00166c29();
      cVar2 = *pcVar6 + (char)(iVar3 % 3) + -1;
      *pcVar6 = cVar2;
      *pcVar6 = cVar2 - (char)uVar9;
      iVar3 = FUN_00166c29();
      pcVar7 = pcVar6 + 4;
      iVar5 = iVar5 + -1;
      pcVar6[1] = pcVar6[1] + ((char)(iVar3 % 3) - (char)uVar10) + -1;
      pcVar6 = pcVar7;
    } while (iVar5 != 0);
    local_c = local_c + 1;
  } while (local_c < 0x80);
  XGRAPHC::XGSwizzleRect(pSource,rect,(LPCRECT)0x0,local_4,0x80,0x80,(LPPOINT)0x0,4);
  iVar5 = FindHeapOf(pSource);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar5].heapHandle == (HANDLE)0x0) {
    pHVar4 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar4 = g_HeapTableBase + iVar5;
  }
  runtime::CurrentHeapToAllocateFrom = iVar5;
  XAPILIB::HeapFree(pHVar4->heapHandle,0,pSource);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::DrawEverything___(void)

{
  int iVar1;
  int iVar2;
  void *this;
  int *piVar2;
  void *next;
  sceneControlObj_0x8 scene_control_obj;
  
  DrawUI__();
  DrawRenderables_();
  iVar2 = (int)&CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4;
  DAT_0051120c = 0;
  iVar1 = iVar2 * 8 + 0x511aa8;
  FUN_0012ab10();
  FUN_00121730(iVar1);
  FUN_00121880(0,iVar2);
                    // Update avatars
  this = (void *)Events::RenderAllFromNode
                           (iVar1,iVar2,0,(EmbeddedSentinel<> *)&Game::SceneInfo.backgrounds);
                    // Draw UI elements (like icons above cans)
  DrawBackgrounds(iVar2,this,0,&Game::SceneInfo.backgrounds);
  FUN_00121ec0();
  scene_control_obj = Game::SceneControls.next;
                    // Draw menu items
  while (scene_control_obj != (sceneControlObj_0x8)0x0) {
    next = *(void **)(scene_control_obj + 4);
    (**(code **)&(*(sceneControlObj **)(scene_control_obj + uVar3))->field_0x14)
              (scene_control_obj + -8);
    scene_control_obj = next;
  }
  piVar2 = &DAT_00506930;
  do {
    if (*piVar2 != 0) {
      FUN_000ed390();
    }
    piVar2 = piVar2 + 1;
  } while ((int)piVar2 < 0x506c50);
  FUN_000ec470();
  FUN_000ebcb0();
  FUN_0005c250();
  FUN_0011af90();
  FUN_00119230();
  FUN_0011ba50();
  FUN_000615e0();
  FUN_00058150();
  if (g_cutsceneBuffer != (Cutscene *)0x0) {
    FUN_00048bc0();
                    // Updates camera in menus and during dialog, but NOT during
                    // - regular cutscenes
                    // - book cutscenes
    FUN_0004dbd0(g_cutsceneBuffer);
  }
  if (DAT_004de9a0 != 0) {
    DrawXboxButtons_(0);
  }
  if (INT_004e17c8 == 6) {
    DrawXboxButtons_(0);
  }
  FUN_00122230();
  FUN_00132290();
  if ((g_globalFlagset & 0x2000) != 0) {
    UpdateStorybookPosition_();
    if (PTR_005462a0 != (GamePauseContext *)0x0) {
      CopyRectsAndDraw(PTR_005462a0);
    }
    FUN_0012c490();
    DrawAndUpdateUIItems();
    return;
  }
  DrawAndUpdateUIItems();
  UpdateStorybookPosition_();
  if (PTR_005462a0 != (GamePauseContext *)0x0) {
    CopyRectsAndDraw(PTR_005462a0);
  }
  FUN_0012c490();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Graphics::DrawUI__(void)

{
  ushort *puVar1;
  float *pfVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  bool bVar8;
  BOOL colliding;
  void **commands;
  void **ppvVar6;
  uint i;
  uint data_index;
  int iVar9;
  int iVar10;
  ushort uVar11;
  float10 fVar12;
  float fVar13;
  float fVar14;
  D3DXMATRIX *pDVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  uint local_210;
  float new_x;
  float new_y;
  float new_z;
  float local_200;
  float local_1fc;
  float local_1f8;
  D3DXMATRIX *local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  D3DXVECTOR3 normal;
  D3DXVECTOR3 matrix;
  float fStack_1bc;
  float fStack_1b8;
  float fStack_1b4;
  float fStack_1b0;
  float fStack_1ac;
  float fStack_1a8;
  float fStack_1a4;
  int iStack_1a0;
  D3DXMATRIX staging_mat;
  undefined4 uStack_15c;
  float fStack_158;
  undefined4 uStack_154;
  float fStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  float fStack_144;
  float fStack_140;
  D3DXPlane plane;
  D3DXMATRIX view_applied;
  float local_ec;
  D3DMATRIX view_matrix;
  D3DXMATRIX combined_transforms;
  D3DXMATRIX data;
  float bruh;
  MainCameraStruct *cam;
  
  data_index = 0;
  if ((Game::GameState._568_4_ != 0) && (Game::GameState.field95_0x25c != 0)) {
    local_1f4 = (D3DXMATRIX *)0x0;
    local_1e4 = (CurrentCameraStruct->pos).x;
    local_1e0 = (CurrentCameraStruct->pos).y;
    bVar8 = false;
    local_1dc = (CurrentCameraStruct->pos).z;
    i = 0;
    local_210 = 0;
    if (0 < (int)Game::GameState._568_4_) {
      do {
        iVar9 = data_index * 0x18;
        colliding = AABBvsFrustum((GraphicsCamera *)&CurrentCameraStruct->field_0x138,
                                  (vec3 *)(Game::GameState._576_4_ + iVar9),
                                  (vec3 *)(Game::GameState._576_4_ + iVar9) + 1,
                                  &CurrentCameraStruct->field_0x1e0);
        if ((colliding != 0) &&
           ((fVar17 = ((*(float *)(iVar9 + 0xc + Game::GameState._576_4_) -
                       *(float *)(iVar9 + Game::GameState._576_4_)) * 0.5 +
                      *(float *)(iVar9 + Game::GameState._576_4_)) - local_1e4,
            fVar13 = (*(float *)(iVar9 + 4 + Game::GameState._576_4_) +
                     (*(float *)(iVar9 + 0x10 + Game::GameState._576_4_) -
                     *(float *)(iVar9 + 4 + Game::GameState._576_4_)) * 0.5) - local_1e0,
            fVar14 = (*(float *)(iVar9 + 8 + Game::GameState._576_4_) +
                     (*(float *)(iVar9 + 0x14 + Game::GameState._576_4_) -
                     *(float *)(iVar9 + 8 + Game::GameState._576_4_)) * 0.5) - local_1dc,
            pDVar15 = (D3DXMATRIX *)(fVar14 * fVar14 + fVar13 * fVar13 + fVar17 * fVar17), !bVar8 ||
            ((float)pDVar15 < (float)local_1f4)))) {
          bVar8 = true;
          local_210 = i;
          local_1f4 = pDVar15;
        }
        i = i + 1;
        data_index = i & 0xffff;
      } while ((int)data_index < (int)Game::GameState._568_4_);
      if (bVar8) {
        local_210 = local_210 & 0xffff;
        iVar9 = local_210 * 0x18;
        colliding = AABBvsFrustum((GraphicsCamera *)&CurrentCameraStruct->field_0x138,
                                  (vec3 *)(Game::GameState._576_4_ + iVar9),
                                  (vec3 *)(Game::GameState._576_4_ + iVar9) + 1,
                                  &CurrentCameraStruct->field_0x1e0);
        if (colliding != 0) {
          D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
          RenderState.zWriteEnabled = 1;
          D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
          RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
          D3D8::D3DDevice_SetRenderState_MultiSampleMode(2);
          UpdateViewport2();
          fStack_1a4 = CurrentCameraStruct->field16_0x5c;
          local_1d8 = CurrentCameraStruct->computedFov_;
          fStack_1bc = CurrentCameraStruct->near;
          new_x = (CurrentCameraStruct->pos).x;
          new_y = (CurrentCameraStruct->pos).y;
          new_z = (CurrentCameraStruct->pos).z;
          fStack_1a8 = CurrentCameraStruct->far;
          iStack_1a0 = CurrentCameraStruct->calculatedWidth_;
          fStack_1ac = CurrentCameraStruct->calculatedHeight__unused;
          puVar1 = (ushort *)
                   (*(int *)(Game::GameState._572_4_ + 0xc) +
                   (uint)*(ushort *)(*(int *)(Game::GameState._572_4_ + 4) + 2 + local_210 * 4) * 6)
          ;
          iVar7 = *(int *)(Game::GameState._572_4_ + 8);
          pfVar2 = (float *)(iVar7 + (uint)puVar1[1] * 0xc);
          iVar10 = (uint)*puVar1 * 0xc;
          local_ec = *pfVar2 - *(float *)(iVar7 + iVar10);
          fVar16 = *(float *)(iVar7 + 4 + (uint)puVar1[1] * 0xc) - *(float *)(iVar7 + 4 + iVar10);
          i = (uint)puVar1[2];
          fVar13 = pfVar2[2] - *(float *)(iVar7 + 8 + iVar10);
          fVar14 = *(float *)(iVar7 + i * 0xc) - *(float *)(iVar7 + iVar10);
          fVar18 = *(float *)(iVar7 + 8 + i * 0xc) - *(float *)(iVar7 + 8 + iVar10);
          fVar17 = *(float *)(iVar7 + i * 0xc + 4) - *(float *)(iVar7 + 4 + iVar10);
          local_200 = fVar18 * fVar16 - fVar17 * fVar13;
          local_1fc = fVar13 * fVar14 - fVar18 * local_ec;
          local_1f8 = fVar17 * local_ec - fVar16 * fVar14;
          fVar13 = local_1f8 * local_1f8 + local_1fc * local_1fc + local_200 * local_200;
          local_1f0 = local_200;
          fStack_1b8 = new_x;
          fStack_1b4 = new_y;
          fStack_1b0 = new_z;
          if (fVar13 != 0.0) {
            local_1ec = local_1fc;
            local_1e8 = local_1f8;
            fVar12 = (float10)invsqrt(fVar13);
            local_200 = (float)((float10)local_200 * fVar12);
            local_1fc = (float)((float10)local_1fc * fVar12);
            local_1f8 = (float)(fVar12 * (float10)local_1f8);
          }
          cam = CurrentCameraStruct;
          iVar7 = *(int *)(Game::GameState._572_4_ + 8);
          DAT_00511174 = 0.0 - (*(float *)(iVar7 + 8 + iVar10) * local_1f8 +
                                *(float *)(iVar7 + 4 + iVar10) * local_1fc +
                               *(float *)(iVar7 + iVar10) * local_200);
          fVar13 = 0.0 - (new_z * local_1f8 + new_y * local_1fc + new_x * local_200 + DAT_00511174);
          local_1e8 = (fVar13 * local_1f8 + new_z) - new_z;
          local_1ec = ((fVar13 * local_1fc + new_y) - new_y) * 2.0;
          new_x = ((fVar13 * local_200 + new_x) - new_x) * 2.0 + new_x;
          new_z = local_1e8 * 2.0 + new_z;
          new_y = local_1ec + new_y;
          DAT_00511168 = local_200;
          DAT_0051116c = local_1fc;
          DAT_00511170 = local_1f8;
          (CurrentCameraStruct->pos).x = new_x;
          (cam->pos).y = new_y;
          (cam->pos).z = new_z;
          matrix.x = *(float *)(*(int *)(Game::GameState._572_4_ + 8) + iVar10);
          iVar10 = *(int *)(Game::GameState._572_4_ + 8) + iVar10;
          matrix.y = *(float *)(iVar10 + 4);
          matrix.z = *(float *)(iVar10 + 8);
          normal.x = local_200;
          normal.y = local_1fc;
          normal.z = local_1f8;
          D3D8::D3DDevice_GetTransform(D3DTS_VIEW,(D3DMATRIX *)&view_matrix.field1);
          D3DX8::D3DXVec3TransformCoord(&matrix,&matrix,(D3DXVECTOR3 *)view_matrix.m);
          D3DX8::D3DXVec3TransformNormal(&normal,&normal,(D3DXVECTOR3 *)view_matrix.m);
          D3DX8::D3DXPlaneFromPointNormal(&plane,&matrix,&normal);
          D3DX8::D3DXMatrixReflect(&data,&plane);
          D3DX8::D3DXMatrixMultiply(&view_applied,&view_matrix,&data);
          SetSomeMemoryMatrix((D3DXVECTOR3 *)&view_applied.field1);
          staging_mat.m[0][0] = view_applied.m[0][0];
          staging_mat.m[0][1] = view_applied.m[1][0];
          staging_mat.m[0][2] = view_applied.m[2][0];
          staging_mat.m[0][3] = view_applied.m[3][0];
          staging_mat.m[1][0] = view_applied.m[0][1];
          staging_mat.m[1][1] = view_applied.m[1][1];
          staging_mat.m[1][2] = view_applied.m[2][1];
          staging_mat.m[1][3] = view_applied.m[3][1];
          staging_mat.m[2][0] = view_applied.m[0][2];
          staging_mat.m[2][1] = view_applied.m[1][2];
          staging_mat.m[2][2] = view_applied.m[2][2];
          staging_mat.m[2][3] = view_applied.m[3][2];
          SetViewMatrix(&staging_mat);
          staging_mat.m[3][1] = 0.0;
          staging_mat.m[3][2] = 0.0;
          staging_mat.m[3][3] = new_x;
          uStack_15c = 0;
          uStack_154 = 0;
          uStack_14c = 0;
          uStack_148 = 0;
          staging_mat.m[3][0] = 1.0;
          fStack_158 = 1.0;
          fStack_150 = new_y;
          fStack_144 = 1.0;
          fStack_140 = new_z;
          leftCombineTransforms
                    ((AffineTransform *)&combined_transforms.field1,
                     (AffineTransform *)&staging_mat.field1,(AffineTransform *)(staging_mat.m + 3));
          cam = CurrentCameraStruct;
          local_1f4 = &combined_transforms;
          puVar4 = &CurrentCameraStruct->field_0xdc;
          *(float *)&CurrentCameraStruct->field_0xd8 = combined_transforms.m[0][0];
          *(float *)puVar4 = combined_transforms.m[0][1];
          *(float *)&cam->field_0xe0 = combined_transforms.m[0][2];
          *(float *)&cam->field_0xe4 = combined_transforms.m[0][3];
          *(float *)&cam->field_0xe8 = combined_transforms.m[1][0];
          *(float *)&cam->field_0xec = combined_transforms.m[1][1];
          *(float *)&cam->field_0xf0 = combined_transforms.m[1][2];
          *(float *)&cam->field_0xf4 = combined_transforms.m[1][3];
          *(float *)&cam->field_0xf8 = combined_transforms.m[2][0];
          *(float *)&cam->field_0xfc = combined_transforms.m[2][1];
          *(float *)&cam->field_0x100 = combined_transforms.m[2][2];
          *(float *)&cam->field_0x104 = combined_transforms.m[2][3];
          Maths::InvertAffineMatrix(&staging_mat,(D3DMATRIX *)(combined_transforms.m + 3));
          FUN_000f6e60(combined_transforms.m + 3);
          cam = CurrentCameraStruct;
          (CurrentCameraStruct->pos).x = new_x;
          (cam->pos).y = new_y;
          (cam->pos).z = new_z;
          CurrentCameraStruct->near = 1.0;
          CurrentCameraStruct->far = 1000.0;
          UpdatePerspectiveProj();
          UpdateViewport();
          pfVar2 = (float *)(Game::GameState._576_4_ + 0xc + iVar9);
          local_1e0 = (*(float *)(Game::GameState._576_4_ + 0x10 + iVar9) +
                      *(float *)(Game::GameState._576_4_ + 4 + iVar9)) * 0.5;
          local_1e4 = (*(float *)(Game::GameState._576_4_ + 0xc + iVar9) +
                      *(float *)(Game::GameState._576_4_ + iVar9)) * 0.5;
          local_1dc = (pfVar2[2] + *(float *)(Game::GameState._576_4_ + 8 + iVar9)) * 0.5;
          fVar13 = *(float *)(Game::GameState._576_4_ + iVar9) - *pfVar2;
          fVar17 = *(float *)(Game::GameState._576_4_ + 4 + iVar9) - pfVar2[1];
          fVar14 = *(float *)(Game::GameState._576_4_ + 8 + iVar9) - pfVar2[2];
          g_IdkGraphicsVec3.x = new_x;
          g_IdkGraphicsVec3.y = new_y;
          g_IdkGraphicsVec3.z = new_z;
          bruh = SQRT(fVar13 * fVar13 + fVar17 * fVar17 + fVar14 * fVar14) * 0.5;
          bVar8 = bruh * bruh <
                  (new_z - local_1dc) * (new_z - local_1dc) +
                  (new_y - local_1e0) * (new_y - local_1e0) +
                  (new_x - local_1e4) * (new_x - local_1e4);
          if (bVar8) {
            FUN_0013e520(bruh,(char *)&local_1e4,(char *)&new_x);
          }
          DAT_00511160 = (uint)bVar8;
          uVar11 = 0;
          FUN_001565e0(0x901);
          FUN_00120e80(1);
          FUN_001565e0(0x900);
          cam = CurrentCameraStruct;
          (CurrentCameraStruct->pos).x = fStack_1b8;
          (cam->pos).y = fStack_1b4;
          (cam->pos).z = fStack_1b0;
          CurrentCameraStruct->near = fStack_1bc;
          CurrentCameraStruct->far = fStack_1a8;
          FUN_000f5cc0(fStack_1a4,iStack_1a0,fStack_1ac);
          RecalculateWorldAndViews();
          UpdatePerspectiveProj();
          UpdateViewport2();
          D3D8::D3DDevice_SetRenderState_MultiSampleMode(0);
          D3D8::D3DDevice_Clear(0,(D3DRECT *)0x0,3,0,1.0,0);
          UnbindAll();
          GraphicsFlags = GraphicsFlags | 0x800;
          DAT_001819a0 = 2;
          DAT_001819b0 = 2;
          DAT_001819a8 = 0;
          _DAT_001819b8 = 0;
          D3D8::D3DDevice_SetVertexShader(0x42);
          D3D8::D3DDevice_SetRenderState_Simple(D3DRS_COLORWRITEENABLE,0);
          RenderState._40_4_ = 0;
          D3D8::D3DDevice_SetVertexShader(2);
          D3D8::D3DDevice_SetVertexDataColor(3,0x64646464);
          D3D8::D3DDevice_SetRenderState_CullMode(0);
          D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
          RenderState.zWriteEnabled = 1;
          D3D8::D3DDevice_SetRenderState_StencilEnable(1);
          D3D8::D3DDevice_SetVertexShader(2);
          D3D8::D3DDevice_SetVertexDataColor(3,BLACK);
          D3D8::D3DDevice_SetRenderState_CullMode(0);
                    // Draw something
          commands = (void **)D3D8::D3DDevice_BeginPush_4
                                        ((uint)*(ushort *)
                                                (*(int *)(Game::GameState._572_4_ + 4) +
                                                local_210 * 4) * 9 + 5);
          *commands = (void *)0x417fc;
          commands[1] = &DAT_00000005;
          commands[2] = (void *)((uint)*(ushort *)
                                        (*(int *)(Game::GameState._572_4_ + 4) + local_210 * 4) *
                                 0x240000 + 0x40001818);
          ppvVar6 = commands + 3;
          if (*(short *)(*(int *)(Game::GameState._572_4_ + 4) + local_210 * 4) != 0) {
            do {
              iVar9 = (uint)*(ushort *)(*(int *)(Game::GameState._572_4_ + 4) + 2 + local_210 * 4) +
                      (uint)uVar11;
              uVar5 = *(ushort *)(*(int *)(Game::GameState._572_4_ + 0xc) + 2 + iVar9 * 6);
              puVar1 = (ushort *)(*(int *)(Game::GameState._572_4_ + 0xc) + iVar9 * 6);
              uVar6 = puVar1[2];
              local_1d8 = (float)CONCAT22(local_1d8._2_2_,uVar6);
              puVar3 = (undefined4 *)(*(int *)(Game::GameState._572_4_ + 8) + (uint)*puVar1 * 0xc);
              *ppvVar6 = (void *)*puVar3;
              ppvVar6[1] = (void *)puVar3[1];
              ppvVar6[2] = (void *)puVar3[2];
              puVar3 = (undefined4 *)(*(int *)(Game::GameState._572_4_ + 8) + (uint)uVar5 * 0xc);
              ppvVar6[3] = (void *)*puVar3;
              ppvVar6[4] = (void *)puVar3[1];
              ppvVar6[5] = (void *)puVar3[2];
              puVar3 = (undefined4 *)(*(int *)(Game::GameState._572_4_ + 8) + (uint)uVar6 * 0xc);
              ppvVar6[6] = (void *)*puVar3;
              ppvVar6[7] = (void *)puVar3[1];
              ppvVar6[8] = (void *)puVar3[2];
              ppvVar6 = ppvVar6 + 9;
              uVar11 = uVar11 + 1;
                    // Draw all of the renderables
            } while (uVar11 < *(ushort *)(*(int *)(Game::GameState._572_4_ + 4) + local_210 * 4));
          }
          *ppvVar6 = (void *)0x417fc;
          ppvVar6[1] = (void *)0x0;
          D3D8::D3DDevice_EndPush((DWORD *)(ppvVar6 + 2));
          UpdateViewport2();
          D3D8::D3DDevice_SetRenderState_StencilEnable(0);
          D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
          RenderState.zWriteEnabled = 1;
        }
        UnbindAll();
        D3D8::D3DDevice_Clear(0,(D3DRECT *)0x0,2,0,1.0,0);
      }
    }
  }
  return;
}




void DrawBackgrounds(int param_1,void *this,int param_3,void *param_4)

{
  int iVar1;
  int *piVar2;
  int iVar4;
  background_0x934 iVar3;
  
  for (iVar3 = *(background_0x934 *)((int)param_4 + 4); iVar3 != (background_0x934)0x0;
      iVar3 = iVar3->next) {
    (*(ADJ(iVar3).avatar.vtable)->draw)(ADJ(iVar3),param_1,2);
  }
  if ((this != (void *)0x0) && (iVar4 = *(int *)((int)this + 4), iVar4 != 0)) {
    do {
      iVar1 = iVar4 + (param_1 + param_3 * 4) * -0xc;
      piVar2 = (int *)(iVar1 + -0x124);
      if ((1 << ((byte)param_1 & 0x1f) & (uint)*(ushort *)(iVar1 + 0x70)) != 0) {
        (**(code **)(*piVar2 + 0x14))(piVar2,param_1,2);
      }
      iVar4 = *(int *)(iVar4 + 4);
    } while (iVar4 != 0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Graphics::DrawRenderables_(void)

{
  code *pcVar1;
  background_0x934_conflict3 pEVar2;
  int iVar3;
  int iVar4;
  uint unaff_EBX;
  
  for (pEVar2 = Game::SceneInfo.backgrounds.head; pEVar2 != (background_0x934_conflict3)0x0;
      pEVar2 = pEVar2->next) {
    pcVar1 = (ADJ(pEVar2).avatar.object.vtable)->getCheerState;
    if (pcVar1 != (code *)0x0) {
      (*pcVar1)(ADJ(pEVar2));
    }
  }
  if ((unaff_EBX & 0x1fffffff) != 0x1ff5dcab) {
    for (iVar3 = Game::SceneInfo.bruhs[unaff_EBX * 2 + 1]; iVar3 != 0; iVar3 = *(int *)(iVar3 + 4))
    {
      iVar4 = iVar3 + unaff_EBX * -0xc;
      pcVar1 = *(code **)(*(int *)(iVar4 + -0x124) + 0x38);
      if (pcVar1 != (code *)0x0) {
        (*pcVar1)(iVar4 + -0x124);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void DrawSomething(int param_1)

{
  if (*(int *)(param_1 + 0x1034) != 0) {
    Graphics::CopyRectsAndDraw(*(int *)(param_1 + 0x1034));
  }
  if (*(int *)(param_1 + 0x3044) != 0) {
    DrawXboxButtons_();
    return;
  }
  return;
}




bool FUN_00131c50(uint param_1,BaronDraw *param_2)

{
  float *extraout_ECX;
  float *extraout_ECX_00;
  float *extraout_ECX_01;
  float *pfVar2;
  float *extraout_ECX_02;
  float *extraout_ECX_03;
  float *extraout_EDX;
  float *extraout_EDX_00;
  float *pfVar3;
  UIState UVar1;
  
  switch(param_2->type) {
  case New_Name:
    if (0.0 < param_2->scalar) {
      UI__SetState(param_2,New_Name_(1));
      return param_2->type != New_Name;
    }
    break;
  case New_Name_(1):
    Timer::reduce(&param_2->stateScalar);
    if (*extraout_ECX == 0.0) {
      UVar1 = param_2->type;
      if (param_2->field4_0x10 == 0) {
        if ((1 < (int)UVar1) && ((int)UVar1 < 4)) {
          param_2->scalar = 0.0;
        }
        param_2->type = New_Name_(2);
        *extraout_ECX = g_timeSpentInCurrentLevel;
        return param_2->type != New_Name;
      }
      if ((1 < (int)UVar1) && ((int)UVar1 < 4)) {
        param_2->scalar = 0.0;
      }
      param_2->type = New_Name_(3);
      *extraout_ECX = g_timeSpentInCurrentLevel;
      return param_2->type != New_Name;
    }
    break;
  case New_Name_(2):
    if (param_1 == 0) {
      FUN_0012b2f0();
    }
    else {
      Timer::reduce(&param_2->scalar);
    }
    Timer::reduce(&param_2->stateScalar);
    pfVar2 = extraout_ECX_00;
    pfVar3 = extraout_EDX;
    if (*extraout_ECX_00 != 0.0) {
      if (param_2->field4_0x10 != 0) {
        if ((1 < (int)param_2->type) && ((int)param_2->type < 4)) {
          *extraout_ECX_00 = 0.0;
        }
        param_2->type = New_Name_(3);
        UVar1 = param_2->type;
        *extraout_EDX = g_timeSpentInCurrentLevel;
        return UVar1 != New_Name;
      }
      break;
    }
    goto LAB_00131d97;
  case New_Name_(3):
    FUN_0012b2f0();
    Timer::reduce(&param_2->stateScalar);
    pfVar2 = extraout_ECX_01;
    pfVar3 = extraout_EDX_00;
    if (*extraout_ECX_01 != 0.0) {
      if (param_2->field4_0x10 == 0) {
        if ((1 < (int)param_2->type) && ((int)param_2->type < 4)) {
          *extraout_ECX_01 = 0.0;
        }
        param_2->type = New_Name_(2);
        UVar1 = param_2->type;
        *extraout_EDX_00 = g_timeSpentInCurrentLevel;
        return UVar1 != New_Name;
      }
      break;
    }
LAB_00131d97:
    if (param_2->field3_0xc == 0) {
      if ((1 < (int)param_2->type) && ((int)param_2->type < 4)) {
        *pfVar2 = 0.0;
      }
      param_2->type = New_Name_(4);
      UVar1 = param_2->type;
      *pfVar3 = 0.8;
      return UVar1 != New_Name;
    }
    UVar1 = param_2->type;
    if (param_2->field3_0xc == 1) {
      if ((1 < (int)UVar1) && ((int)UVar1 < 4)) {
        *pfVar2 = 0.0;
      }
      param_2->type = New_Name_(5);
      UVar1 = param_2->type;
      *pfVar3 = 1.5;
      return UVar1 != New_Name;
    }
    if ((1 < (int)UVar1) && ((int)UVar1 < 4)) {
      *pfVar2 = 0.0;
      param_2->type = New_Name;
      return param_2->type != New_Name;
    }
LAB_00131ec9:
    param_2->type = New_Name;
    break;
  case New_Name_(4):
  case New_Name_(6):
    Timer::reduce(&param_2->stateScalar);
    if (*extraout_ECX_03 != 0.0) break;
    if ((1 < (int)param_2->type) && ((int)param_2->type < 4)) {
      param_2->scalar = 0.0;
    }
    goto LAB_00131ec9;
  case New_Name_(5):
    Timer::reduce(&param_2->stateScalar);
    if (*extraout_ECX_02 == 0.0) {
      if ((1 < (int)param_2->type) && ((int)param_2->type < 4)) {
        param_2->scalar = 0.0;
      }
      param_2->type = New_Name_(6);
      *extraout_ECX_02 = 0.8;
      return param_2->type != New_Name;
    }
  }
  return param_2->type != New_Name;
}




void __fastcall UI__SetState(BaronDraw *ui,UIState newState)

{
  if ((1 < (int)ui->type) && ((int)ui->type < 4)) {
    ui->scalar = 0.0;
  }
  ui->type = newState;
  switch(newState) {
  case New_Name_(1):
    ui->stateScalar = 0.6;
    return;
  case New_Name_(2):
  case New_Name_(3):
    ui->stateScalar = g_timeSpentInCurrentLevel;
    return;
  case New_Name_(4):
  case New_Name_(6):
    ui->stateScalar = 0.8;
    break;
  case New_Name_(5):
    ui->stateScalar = 1.5;
    return;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void CopyMat4IntoShaderConstant(ShaderConstant *param_1,D3DXMATRIX *param_2)

{
  float fVar1;
  float fVar2;
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
  
  fVar1 = param_2->m[0][1];
  fVar2 = param_2->m[0][2];
  fVar3 = param_2->m[0][3];
  fVar4 = param_2->m[1][0];
  fVar5 = param_2->m[1][1];
  fVar6 = param_2->m[1][2];
  fVar7 = param_2->m[1][3];
  fVar8 = param_2->m[2][0];
  fVar9 = param_2->m[2][1];
  fVar10 = param_2->m[2][2];
  fVar11 = param_2->m[2][3];
  fVar12 = param_2->m[3][0];
  fVar13 = param_2->m[3][1];
  fVar14 = param_2->m[3][2];
  fVar15 = param_2->m[3][3];
  param_1->field0_0x0 = param_2->m[0][0];
  param_1->field1_0x4 = fVar4;
  param_1->field2_0x8 = fVar8;
  param_1->field3_0xc = fVar12;
  param_1[1].field0_0x0 = fVar1;
  param_1[1].field1_0x4 = fVar5;
  param_1[1].field2_0x8 = fVar9;
  param_1[1].field3_0xc = fVar13;
  param_1[2].field0_0x0 = fVar2;
  param_1[2].field1_0x4 = fVar6;
  param_1[2].field2_0x8 = fVar10;
  param_1[2].field3_0xc = fVar14;
  param_1[3].field0_0x0 = fVar3;
  param_1[3].field1_0x4 = fVar7;
  param_1[3].field2_0x8 = fVar11;
  param_1[3].field3_0xc = fVar15;
  return;
}




void BuildViewMatrix(D3DXMATRIX *mat,vec3 *v,undefined4 param_3,undefined4 param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  FUN_00151c86(&local_10,param_3,v);
  FUN_00151ce0(&local_10,&local_10);
  FUN_00151c38(&local_1c,param_4,&local_10);
  FUN_00151ce0(&local_1c,&local_1c);
  FUN_00151c38(&local_28,&local_10,&local_1c);
  mat->m[0][0] = local_1c;
  mat->m[1][0] = local_18;
  mat->m[2][0] = local_14;
  fVar1 = v->x;
  fVar2 = v->z;
  fVar3 = v->y;
  mat->m[0][1] = local_28;
  mat->m[1][1] = local_24;
  mat->m[2][1] = local_20;
  mat->m[3][0] = -(local_18 * fVar3 + local_14 * fVar2 + local_1c * fVar1);
  fVar1 = v->x;
  fVar2 = v->z;
  fVar3 = v->y;
  mat->m[0][2] = local_10;
  mat->m[1][2] = local_c;
  mat->m[2][2] = local_8;
  mat->m[3][1] = -(local_24 * fVar3 + local_20 * fVar2 + local_28 * fVar1);
  mat->m[3][2] = -(local_c * v->y + local_8 * v->z + local_10 * v->x);
  mat->m[0][3] = 0.0;
  mat->m[1][3] = 0.0;
  mat->m[2][3] = 0.0;
  mat->m[3][3] = 1.0;
  return;
}




void BuildProjectionMatrix(D3DXMATRIX *param_1,float fov,float aspect,float far,float near)

{
  float10 fVar1;
  float fVar2;
  float10 fVar3;
  
  fVar1 = (float10)fcos((float10)(fov * 0.5));
  fVar3 = (float10)fsin((float10)(fov * 0.5));
  param_1->m[0][0] = ((float)fVar1 / (float)fVar3) / aspect;
  param_1->m[0][1] = 0.0;
  param_1->m[0][2] = 0.0;
  param_1->m[0][3] = 0.0;
  param_1->m[1][0] = 0.0;
  param_1->m[1][1] = (float)fVar1 / (float)fVar3;
  param_1->m[1][2] = 0.0;
  param_1->m[1][3] = 0.0;
  param_1->m[2][0] = 0.0;
  param_1->m[2][1] = 0.0;
  fVar2 = near / (near - far);
  param_1->m[2][2] = fVar2;
  param_1->m[2][3] = 1.0;
  param_1->m[3][0] = 0.0;
  param_1->m[3][1] = 0.0;
  param_1->m[3][2] = -(fVar2 * far);
  param_1->m[3][3] = 0.0;
  return;
}



HRESULT XGRAPHC::XGWriteSurfaceOrTextureToXPR
                  (LPVOID pResource,char *cPath,BOOL bWriteSurfaceAsTexture)

{
  uint *lpBuffer;
  HANDLE pvVar1;
  LPVOID pvVar2;
  int iVar3;
  char *pcVar4;
  HRESULT HVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  int unaff_FS_OFFSET;
  DWORD nNumberOfBytesToWrite;
  char local_92c [2048];
  char local_12c [256];
  undefined4 local_2c;
  char *local_28;
  undefined4 local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  HANDLE local_8;
  
  pvVar2 = pResource;
  local_1c = *(uint *)pResource & 0x70000;
  if ((local_1c != 0x40000) && (local_1c != 0x50000)) {
    return -0x7fffbffb;
  }
  lpBuffer = (uint *)((int)pResource + 0xc);
  uVar6 = *lpBuffer >> 2;
  local_18 = CONCAT31(local_18._1_3_,(char)uVar6) & 0xffffff01;
  if ((*lpBuffer >> 4 & 0xf) == 3) {
    pResource = (LPVOID)CONCAT31(pResource._1_3_,1);
    if ((uVar6 & 1) == 0) goto LAB_00152511;
  }
  pResource = (LPVOID)((uint)pResource & 0xffffff00);
LAB_00152511:
  if (*(int *)((int)pvVar2 + 0x10) == 0) {
    uVar6 = *lpBuffer;
    local_14 = (char *)(uVar6 >> 0x10 & 0xf);
    iVar3 = 1 << ((byte)(uVar6 >> 0x14) & 0xf);
    local_8 = (HANDLE)(1 << ((byte)(uVar6 >> 0x18) & 0xf));
    iVar7 = 1 << (byte)(*lpBuffer >> 0x1c);
  }
  else {
    iVar3 = (*(uint *)((int)pvVar2 + 0x10) & 0xfff) + 1;
    local_8 = (HANDLE)((*(uint *)((int)pvVar2 + 0x10) >> 0xc & 0xfff) + 1);
    local_14 = (char *)0x1;
    iVar7 = 1;
  }
  local_10 = (char *)XGSetTextureHeaderImpl
                               (iVar3,local_8,iVar7,local_14,*(undefined1 *)((int)pvVar2 + 0xd),0,
                                local_18,pResource,&local_18,&local_18);
  local_8 = CreateFileForHandle(cPath,0x40000000,0,(char *)0x0,2,0);
  if (local_8 == (HANDLE)0xffffffff) {
    pcVar4 = XAPILIB::GetLastError(unaff_FS_OFFSET);
    _sprintf(local_12c,"Unable to open file (%s):  error %x\n",cPath,pcVar4);
    HVar5 = -0x7fffbffb;
  }
  else {
    local_28 = local_10 + 0x800;
    local_2c = 0x30525058;
    local_24 = 0x800;
    XAPILIB::WriteFile(local_8,&local_2c,0xc,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
    local_20 = *(uint *)pvVar2;
    if ((local_1c == 0x50000) && (bWriteSurfaceAsTexture != 0)) {
      local_20 = local_20 & 0xfffcffff | 0x40000;
    }
    local_20 = local_20 & 0xffffff;
    XAPILIB::WriteFile(local_8,&local_20,4,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
    local_c = 0;
    XAPILIB::WriteFile(local_8,&local_c,4,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
    local_c = 0;
    XAPILIB::WriteFile(local_8,&local_c,4,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
    pvVar1 = local_8;
    XAPILIB::WriteFile(local_8,lpBuffer,8,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
    pcVar4 = (char *)(*(uint *)((int)pvVar2 + 4) | 0x80000000);
    local_14 = pcVar4;
    if ((local_1c == 0x40000) || (bWriteSurfaceAsTexture != 0)) {
      local_c = 0xffffffff;
      XAPILIB::WriteFile(pvVar1,&local_c,4,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
      nNumberOfBytesToWrite = 0x7dc;
    }
    else {
      local_c = 0;
      XAPILIB::WriteFile(pvVar1,&local_c,4,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
      local_c = 0xffffffff;
      XAPILIB::WriteFile(pvVar1,&local_c,4,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
      nNumberOfBytesToWrite = 0x7d8;
    }
    XAPILIB::WriteFile(pvVar1,local_92c,nNumberOfBytesToWrite,(LPDWORD)&pResource,(LPOVERLAPPED)0x0)
    ;
    for (; 0 < (int)local_10; local_10 = local_10 + -(int)cPath) {
      cPath = (char *)0x800;
      if ((int)local_10 < 0x801) {
        cPath = local_10;
      }
      pcVar8 = local_92c;
      for (uVar6 = (uint)cPath >> 2; pvVar1 = local_8, uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar6 = (uint)cPath & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar8 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar8 = pcVar8 + 1;
      }
      XAPILIB::WriteFile(pvVar1,local_92c,(DWORD)cPath,(LPDWORD)&pResource,(LPOVERLAPPED)0x0);
      pcVar4 = local_14 + (int)cPath;
      local_14 = pcVar4;
      pvVar1 = local_8;
    }
    XAPILIB::CloseHandle(pvVar1);
    HVar5 = 0;
  }
  return HVar5;
}




void Graphics::InitialiseDXSettings(DirectXContext *param_1)

{
  param_1->backBufferWidth = 0;
  param_1->backBufferHeight = 0;
  *(undefined4 *)&param_1->progressiveScan = 0;
  param_1->useCopySwapInsteadOfDiscard = 0;
  param_1->pushBufferSize = 0;
  param_1->kickOffSize = 0;
  param_1->backbufferCount = 0;
  param_1->vsyncFrames = '\0';
  param_1->immediateEnabled = false;
  param_1->useAutoDepthStencil = 0;
  param_1->widescreen = false;
  param_1->use10x11PixelAspect = false;
  param_1->field15_0x1d = 0;
  param_1->refreshRate = '\0';
  param_1->field_0x1f = 0;
  param_1->backBufferWidth = 640;
  param_1->backBufferHeight = 480;
  param_1->backbufferCount = 1;
  param_1->useAutoDepthStencil = 1;
  param_1->useCopySwapInsteadOfDiscard = 1;
  param_1->vsyncFrames = '\x01';
  param_1->pushBufferSize = 0x200000;
  param_1->kickOffSize = 0x8000;
  param_1->field15_0x1d = 0x11;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Graphics::CreatePresentParams(DirectXContext *ctx,D3DPRESENT_PARAMETERS *pres)

{
  char cVar1;
  int iVar2;
  uint refresh_rate;
  D3DPRESENT_PARAMETERS *pDVar3;
  
                    // memset present params to 0
  pDVar3 = pres;
  for (iVar2 = 0x11; iVar2 != 0; iVar2 = iVar2 + -1) {
    pDVar3->BackBufferWidth = 0;
    pDVar3 = (D3DPRESENT_PARAMETERS *)&pDVar3->BackBufferHeight;
  }
  pres->BackBufferWidth = (uint)ctx->backBufferWidth;
  pres->BackBufferHeight = (uint)ctx->backBufferHeight;
  pres->BackBufferFormat = D3DFMT_A8R8G8B8;
  pres->BackBufferCount = ctx->backbufferCount;
  pres->EnableAutoDepthStencil = (uint)ctx->useAutoDepthStencil;
  pres->MultiSampleType = (uint)ctx->field15_0x1d;
  pres->AutoDepthStencilFormat = D3DFMT_D24S8;
  pres->SwapEffect = (uint)(ctx->useCopySwapInsteadOfDiscard == 2) * 2 + 1;
  refresh_rate = (uint)ctx->refreshRate;
  if (ctx->refreshRate == 0) {
    refresh_rate = 0;
  }
  pres->FullScreen_RefreshRateInHz = refresh_rate;
  cVar1 = ctx->vsyncFrames;
  if (cVar1 == '\x01') {
    pres->FullScreen_PresentationInterval = 1;
  }
  else if (cVar1 == '\x02') {
    pres->FullScreen_PresentationInterval = 2;
  }
  else if (cVar1 == '\x03') {
    pres->FullScreen_PresentationInterval = 4;
  }
  else {
    pres->FullScreen_PresentationInterval = 0;
  }
  if (ctx->immediateEnabled != false) {
    pres->FullScreen_PresentationInterval = pres->FullScreen_PresentationInterval | 0x80000000;
  }
  if (ctx->progressiveScan != false) {
    pres->Flags = pres->Flags | 0x40;
  }
  if (ctx->widescreen != false) {
    pres->Flags = pres->Flags | 0x10;
  }
  if (ctx->use10x11PixelAspect != false) {
    pres->Flags = pres->Flags | 0x100;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Graphics::CreateDirectXContext(DirectXContext *ctx)

{
  D3DPRESENT_PARAMETERS present_params;
  
  if (g_DirectXDevice != (IDirect3DDevice8 *)0x0) {
    D3D8::D3D_KickOffAndWaitForIdle();
    if (g_BackBuffer_0 != (D3DSurface *)0x0) {
      D3D8::D3DResource_Release((D3DResource *)g_BackBuffer_0);
    }
    if (g_DepthStencilSurface != (D3DSurface *)0x0) {
      D3D8::D3DResource_Release((D3DResource *)g_DepthStencilSurface);
    }
    D3D8::D3DDevice_Release();
  }
  CreatePresentParams(ctx,&present_params);
  D3D::Direct3D_SetPushBufferSize(ctx->pushBufferSize,ctx->kickOffSize);
  D3D8::Direct3D_CreateDevice
            (0,D3DDEVTYPE_HAL,(HWND)0x0,0x50,(D3DPRESENT_PARAMETERS *)&present_params,
             &g_DirectXDevice);
  g_DepthStencilSurface = D3D8::D3DDevice_GetDepthStencilSurface2();
  g_BackBuffer_0 = D3D8::D3DDevice_GetBackBuffer2(0);
  g_backbufferWidth = ctx->backBufferWidth;
  g_backbufferHeight = ctx->backBufferHeight;
  return;
}




void Graphics::PresentFrame(void)

{
  if (SwapCallback != (code *)0x0) {
    (*SwapCallback)(0);
  }
  D3D8::D3DDevice_Swap(0);
  if (SwapCallback != (code *)0x0) {
    (*SwapCallback)(1);
  }
  return;
}



void __fastcall

void Graphics::SetSomeMemoryMatrix(D3DXVECTOR3 *param_1)

{
  (&DisplayMatrices)[DisplayMatrixIndex].viewMatrix = (D3DXMATRIX *)param_1;
  return;
}



// WARNING: Inlined function: GetBigBlock


D3DXMATRIX * Graphics::GetWorldTransform(D3DXMATRIX *param_1)

{
  DisplayMatrices *pDVar1;
  uint uVar2;
  D3DXMATRIX *pDVar3;
  int iVar4;
  D3DXMATRIX *pDVar5;
  DisplayMatrices *local_4;
  
  uVar2 = DisplayMatrixIndex;
  pDVar3 = &(&DisplayMatrices)[DisplayMatrixIndex].projMatrix;
  if (param_1 != (D3DXMATRIX *)0x0) {
    pDVar5 = &(&DisplayMatrices)[DisplayMatrixIndex].worldMat;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pDVar5->m[0][0] = param_1->m[0][0];
      param_1 = (D3DXMATRIX *)(param_1->m[0] + 1);
      pDVar5 = (D3DXMATRIX *)((int)pDVar5 + 4);
    }
    return pDVar3;
  }
  pDVar1 = &DisplayMatrices + DisplayMatrixIndex;
  (&DisplayMatrices)[DisplayMatrixIndex].worldMat.m[3][2] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[3][1] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[3][0] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[2][3] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[2][1] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[2][0] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[1][3] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[1][2] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[1][0] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[0][3] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[0][2] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[0][1] = 0.0;
  (&DisplayMatrices)[uVar2].worldMat.m[3][3] = 1.0;
  (&DisplayMatrices)[uVar2].worldMat.m[2][2] = 1.0;
  (&DisplayMatrices)[uVar2].worldMat.m[1][1] = 1.0;
  (pDVar1->worldMat).m[0][0] = 1.0;
  return &pDVar1->worldMat;
}



// WARNING: Inlined function: GetDisplayMatrices


void Graphics::SetSpecificProjectionMatrix(D3DMATRIX *val)

{
  DisplayMatrices *pDVar1;
  uint uVar2;
  int i;
  float *f_ptr;
  DisplayMatrices *display_type;
  
  uVar2 = DisplayMatrixIndex;
                    // If an input matrix isn't give, initialise it as below
  if (val != (D3DMATRIX *)0x0) {
    f_ptr = (float *)&(&DisplayMatrices)[DisplayMatrixIndex].projectionMat;
    for (i = 0x10; i != 0; i = i + -1) {
      *f_ptr = val->m[0][0];
      val = (D3DMATRIX *)(val->m[0] + 1);
      f_ptr = f_ptr + 1;
    }
    return;
  }
  pDVar1 = &DisplayMatrices + DisplayMatrixIndex;
  (&DisplayMatrices)[DisplayMatrixIndex].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._43 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._42 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._41 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._34 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._32 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._31 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._24 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._23 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._21 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._14 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._13 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._12 = 0.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._44 = 1.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._33 = 1.0;
  (&DisplayMatrices)[uVar2].projectionMat.DUMMYUNIONNAME.DUMMYSTRUCTNAME._22 = 1.0;
  (pDVar1->projectionMat).DUMMYUNIONNAME.DUMMYSTRUCTNAME._11 = 1.0;
  return;
}



// WARNING: Inlined function: GetBigBlock


void Graphics::SetRoomLighting(uint8_t r,uint8_t g,uint8_t b,uint8_t a)

{
  BigBlock_004370a0.roomLightingR = r;
  BigBlock_004370a0.roomLightingG = g;
  BigBlock_004370a0.roomLightingB = b;
  BigBlock_004370a0.roomLightingA = a;
  return;
}



// WARNING: Inlined function: GetBigBlock


void Graphics::SetSomePtr1(void *param_1)

{
  BigBlock_004370a0.modelSomePtr1 = param_1;
  return;
}




void Graphics::GetDisplayMatrices(DisplayMatrices **displayTypeOut)

{
  *displayTypeOut = &DisplayMatrices + DisplayMatrixIndex;
  return;
}



// WARNING: Unknown calling convention


void Graphics::PushNdNode(void *param_1,ndHeader *param_2)

{
  NdGroupsProcessed = NdGroupsProcessed + 1;
  NdGroupDatas[NdGroupsProcessed].callback = param_1;
  NdGroupDatas[NdGroupsProcessed].node = param_2;
  return;
}




void Graphics::PopNdNode(undefined4 *callback,ndHeader **header)

{
  *callback = NdGroupDatas[NdGroupsProcessed].callback;
  *header = NdGroupDatas[NdGroupsProcessed].node;
  NdGroupsProcessed = NdGroupsProcessed + -1;
  return;
}




void Graphics::SetPixelShaderC0(DirectXShaderConstant *constant)

{
  BigBlock_004370a0.pixelShaderConstantValues[0].c1 = constant->c1;
  BigBlock_004370a0.pixelShaderConstantValues[0].c2 = constant->c2;
  BigBlock_004370a0.pixelShaderConstantValues[0].c3 = constant->c3;
  BigBlock_004370a0.pixelShaderConstantValues[0].c4 = constant->c4;
  return;
}




void FUN_00156f70(ShaderConstant *param_1)

{
  BigBlock_004370a0.pixelShaderConstantValues[1].c1 = param_1->field0_0x0;
  BigBlock_004370a0.pixelShaderConstantValues[1].c2 = param_1->field1_0x4;
  BigBlock_004370a0.pixelShaderConstantValues[1].c3 = param_1->field2_0x8;
  BigBlock_004370a0.pixelShaderConstantValues[1].c4 = param_1->field3_0xc;
  if (BigBlock_004370a0.pixelShaderConstantValues[1].c1 <= 1.0) {
    if (BigBlock_004370a0.pixelShaderConstantValues[1].c1 < 0.0) {
      BigBlock_004370a0.pixelShaderConstantValues[1].c1 = 0.0;
    }
  }
  else {
    BigBlock_004370a0.pixelShaderConstantValues[1].c1 = 1.0;
  }
  if (BigBlock_004370a0.pixelShaderConstantValues[1].c2 <= 1.0) {
    if (BigBlock_004370a0.pixelShaderConstantValues[1].c2 < 0.0) {
      BigBlock_004370a0.pixelShaderConstantValues[1].c2 = 0.0;
    }
  }
  else {
    BigBlock_004370a0.pixelShaderConstantValues[1].c2 = 1.0;
  }
  if (BigBlock_004370a0.pixelShaderConstantValues[1].c3 <= 1.0) {
    if (BigBlock_004370a0.pixelShaderConstantValues[1].c3 < 0.0) {
      BigBlock_004370a0.pixelShaderConstantValues[1].c3 = 0.0;
    }
  }
  else {
    BigBlock_004370a0.pixelShaderConstantValues[1].c3 = 1.0;
  }
  if (1.0 < BigBlock_004370a0.pixelShaderConstantValues[1].c4) {
    BigBlock_004370a0.pixelShaderConstantValues[1].c4 = 1.0;
    return;
  }
  if (BigBlock_004370a0.pixelShaderConstantValues[1].c4 < 0.0) {
    BigBlock_004370a0.pixelShaderConstantValues[1].c4 = 0.0;
  }
  return;
}



// WARNING: Inlined function: GetBigBlock


void FUN_00157140(int *param_1,GraphicsCamera *param_2,undefined4 *param_3)

{
  BOOL BVar1;
  
  do {
    while (*(char *)(*param_1 + 2) != 'B') {
      if (param_1[5] != 0) {
        FUN_00157140(param_1[5],param_2,param_3);
      }
      param_1 = (int *)param_1[6];
      if (param_1 == (int *)0x0) {
        return;
      }
    }
    BVar1 = Graphics::AABBvsFrustum
                      (param_2,(vec3 *)(param_1 + 0x12),(vec3 *)(param_1 + 0x15),&DAT_0043f4b8);
    if (BVar1 == 0) {
      *(undefined1 *)((int)param_1 + 0x3f) = 1;
    }
    else {
      *(undefined1 *)((int)param_1 + 0x3f) = 0;
      *param_3 = 1;
    }
    param_1 = (int *)param_1[6];
  } while (param_1 != (int *)0x0);
  return;
}



// WARNING: Inlined function: GetBigBlock
// WARNING: Inlined function: GetDisplayMatrices
// WARNING: Inlined function: SetParam2Value
// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::SetPixelShaderConstant(BigBlock *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  DisplayMatrices *pDVar3;
  int local_4;
  
  uVar2 = DisplayMatrixIndex;
  _DAT_00546310 = _DAT_00546310 + 1;
  iVar1 = *(int *)&param_1->field_0xc;
  local_4 = 0;
  pDVar3 = &DisplayMatrices + DisplayMatrixIndex;
  FUN_00157140(*(undefined4 *)&param_1->field_0x14,BigBlock_004370a0.field68_0x64,&local_4);
  if (local_4 == 0) {
    DAT_0054630c = DAT_0054630c + 1;
    ndBGPushBuffer::updateSiblings((ndBGPushBuffer *)param_1);
    return;
  }
  if (BigBlock_004370a0.numTextures != 0) {
    SetSomeTextureVar(BigBlock_004370a0.texture1);
  }
  SetViewMatrix((&DisplayMatrices)[uVar2].viewMatrix);
  SetFromDisplayType(pDVar3);
  SetSomeVec3(&BigBlock_004370a0.someVec3);
  if (*(int *)&param_1->field_0x24 != 0) {
    Param2Value = ndShaderParam2::UpdatePayload2((ndShaderParam2 *)param_1);
  }
  ndShaderParam2::setTextures
            (param_1->param2Payload,*(ndShader2Param2TextureAssignment **)(iVar1 + param_2 + 4));
  D3D8::D3DDevice_SetPixelShaderConstant(6,BigBlock_004370a0.pixelShaderConstantValues,2);
  ndHeader::update((ndHeader *)param_1);
  return;
}




void Graphics::DX::ndTransform(ndHeader *param_1,undefined4 param_2)

{
  stackPushProjMatrix();
  FUN_00157f10(param_1,param_2);
  if (param_1->nextSibling != (ndHeader *)0x0) {
    PushNdNode(*param_1->nextSibling->callbackCtx->callbacks,param_1->nextSibling);
  }
  PushNdNode(&LAB_00157ed0,param_1);
  if (param_1->nextChild != (ndHeader *)0x0) {
    PushNdNode(*param_1->nextChild->callbackCtx->callbacks,param_1->nextChild);
  }
  return;
}




void Graphics::DrawAndConsumeNdNodes(ushort drawMask,ModelVariableData *param_2)

{
  code *callback;
  ndHeader *node;
  
  PopNdNode(&callback,&node);
                    // Draw items
  while (callback != (code *)0x0) {
                    // Actually seems to draw the item?
    if ((node->drawMask & drawMask) == 0) {
      if (node->nextSibling != (ndHeader *)0x0) {
        callback = *node->nextSibling->callbackCtx->callbacks;
        PushNdNode(callback,node->nextSibling);
      }
    }
    else {
                    // Draw the thing
      (*callback)(node,param_2);
    }
    PopNdNode(&callback,&node);
  }
  return;
}



// WARNING: Inlined function: GetBigBlock
// WARNING: Inlined function: getCallbackTable


D3DXMATRIX * Graphics::BuildScaleMatrix(void)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  D3DXMATRIX *pOut;
  D3DXMATRIX *pDVar4;
  int iVar5;
  D3DXMATRIX *pDVar6;
  float10 fVar7;
  float fVar8;
  DisplayMatrices *local_54;
  float local_4c [3];
  D3DXMATRIX scalingMatrix;
  
  pOut = &(&DisplayMatrices)[DisplayMatrixIndex].projMatrix;
  D3DX8::D3DXMatrixMultiply
            (pOut,&(&DisplayMatrices)[DisplayMatrixIndex].worldMat,
             (&DisplayMatrices)[DisplayMatrixIndex].viewMatrix);
  pDVar4 = pOut;
  pDVar6 = &scalingMatrix;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    (pDVar6->field1)._11 = pDVar4->m[0][0];
    pDVar4 = (D3DXMATRIX *)(pDVar4->m[0] + 1);
    pDVar6 = (D3DXMATRIX *)(pDVar6->m[0] + 1);
  }
  iVar5 = 0;
  do {
    pfVar2 = (float *)((int)local_4c + iVar5);
    iVar1 = (0x20 - (int)local_4c) + (int)pfVar2;
    fVar8 = *(float *)(iVar1 + -0x10 + (int)pOut);
    fVar3 = *(float *)(iVar1 + (int)pOut);
    fVar8 = fVar3 * fVar3 + fVar8 * fVar8 +
            *(float *)(iVar5 + (int)pOut) * *(float *)(iVar5 + (int)pOut);
    *pfVar2 = fVar8;
    fVar7 = (float10)invsqrt(fVar8);
    *pfVar2 = (float)fVar7;
    iVar5 = iVar5 + 4;
  } while (iVar5 < 0xc);
  D3DX8::D3DXMatrixScaling(&scalingMatrix,local_4c[0],local_4c[1],local_4c[2]);
  pDVar4 = D3DX8::D3DXMatrixMultiply(&scalingMatrix,pOut,&scalingMatrix);
  return pDVar4;
}




void Graphics::SetRoomLighting(float param_1,float param_2,float param_3,float param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint64_t uVar4;
  
  RoomLighting.x = param_1;
  RoomLighting.y = param_2;
  RoomLighting.z = param_3;
  RoomLighting.w = param_4;
  uVar4 = float10::to_uint64_t((float10)param_4 * (float10)255.0);
  uVar1 = (undefined4)uVar4;
  uVar4 = float10::to_uint64_t((float10)param_3 * (float10)255.0);
  uVar2 = (undefined4)uVar4;
  uVar4 = float10::to_uint64_t((float10)param_2 * (float10)255.0);
  uVar3 = (undefined4)uVar4;
  uVar4 = float10::to_uint64_t((float10)param_1 * (float10)255.0);
  SetRoomLighting((int)uVar4,uVar3,uVar2,uVar1);
  return;
}



void FUN_001592a0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  *(undefined4 *)(param_1 + 0xc) = param_2;
  *(undefined4 *)(param_1 + 0x10) = param_3;
  *(undefined4 *)(param_1 + 0x14) = param_4;
  *(undefined4 *)(param_1 + 0x18) = param_5;
  return;
}




void SetGraphicsFlag0x80000000(bool param_1)

{
  if (param_1) {
    Game::GraphicsFlags = Game::GraphicsFlags | 0x80000000;
    return;
  }
  Game::GraphicsFlags = Game::GraphicsFlags & 0x7fffffff;
  return;
}



// WARNING: This is an inlined function


uint Graphics::GetBinaryEntriesCount(void)

{
  return Game::GraphicsFlags;
}




void Graphics::SetSomeFlag1(bool param_1)

{
  SomeFlag1 = param_1;
  return;
}




DWORD SpliceShader(VertexShaderInstance *param_1,int lightingType)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  DWORD DVar4;
  DWORD NumShaders;
  int iVar5;
  void *shaders [3];
  DWORD size;
  DWORD local_884 [545];
  
                    // If it's 6, it's fully compiled?
  if (param_1->compilationState != 6) {
    uVar1 = param_1->field3_0x908[1][3];
    uVar2 = param_1->field3_0x908[1][0];
    param_1->field3_0x908[1][4] = param_1->field3_0x908[1][2];
    uVar3 = param_1->field3_0x908[1][1];
    *(uint *)&param_1->field_0x930 = uVar1;
    uVar1 = param_1->field3_0x908[0][3];
    param_1->field3_0x908[1][2] = uVar2;
    uVar2 = param_1->field3_0x908[0][4];
    param_1->field3_0x908[1][3] = uVar3;
    uVar3 = param_1->field3_0x908[0][1];
    param_1->field3_0x908[1][0] = uVar1;
    uVar1 = param_1->field3_0x908[0][2];
    param_1->field3_0x908[1][1] = uVar2;
    DVar4 = param_1->handle;
    param_1->field3_0x908[0][3] = uVar3;
    uVar2 = param_1->field3_0x908[0][0];
    param_1->field3_0x908[0][4] = uVar1;
    param_1->field3_0x908[0][1] = DVar4;
    param_1->field3_0x908[0][2] = uVar2;
    shaders[0] = param_1;
    if (param_1->id1 == 0) {
      NumShaders = 2;
      if (lightingType < 0) {
        shaders[1] = Graphics::Shaders::__0;
      }
      else {
        shaders[1] = Graphics::Shaders::__1;
      }
    }
    else {
                    // pull shader out of model
      SearchBinaryEntriesLL(shaders + 1,(void *)(uint)(byte)param_1->id2);
      switch(param_1->id3) {
      case 0:
        shaders[2] = &Graphics::Shaders::__0;
        break;
      case 1:
        shaders[2] = &Graphics::Shaders::__1;
        break;
      case 2:
        shaders[2] = &Graphics::Shaders::__2;
        break;
      case 3:
        shaders[2] = &Graphics::Shaders::__3;
        break;
      default:
        shaders[2] = Graphics::Shaders::__4;
      }
      NumShaders = 3;
    }
    size = 0x884;
    XGRAPHICS::XGSpliceVertexShaders(local_884,&size,(DWORD *)0x0,(DWORD *)shaders,NumShaders,0);
    D3D8::D3DDevice_CreateVertexShader((DWORD *)param_1->declaration,local_884,&param_1->handle,0);
    iVar5 = param_1->compilationState + 1;
    param_1->field3_0x908[0][0] = lightingType;
    param_1->compilationState = iVar5;
    if (5 < iVar5) {
      param_1->compilationState = 6;
    }
    return param_1->handle;
  }
  return param_1->field3_0x908[1][4];
}




DWORD GetCachedVertexShader(uint shaderIndex,uint vertexShaderId)

{
  int i;
  DWORD DVar1;
  uint (*pauVar2) [5];
  
                    // If we can find it cached, return that instead
  i = 0;
  if (0 < VertexShaders[shaderIndex].compilationState) {
    pauVar2 = VertexShaders[shaderIndex].field3_0x908;
    do {
      if ((*pauVar2)[0] == vertexShaderId) {
        return *(DWORD *)(shaderIndex * 0x944 + 0x445ad4 + i * 8);
      }
      i = i + 1;
      pauVar2 = (uint (*) [5])(*pauVar2 + 2);
    } while (i < VertexShaders[shaderIndex].compilationState);
  }
  DVar1 = SpliceShader(VertexShaders + shaderIndex,vertexShaderId);
  return DVar1;
}




BOOL Graphics::AABBvsFrustum(GraphicsCamera *camera,vec3 *pos1,vec3 *pos2,char *collisionType)

{
  byte bVar1;
  ushort uVar3;
  byte plane_index;
  ushort uVar5;
  float fVar6;
  float fVar7;
  float ymult1;
  float ymult2;
  float xmult1;
  float xmult2;
  vec3 *v;
  D3DXPlane *f1;
  char *puVar1;
  
  puVar1 = collisionType;
  plane_index = *collisionType;
  uVar5 = 0;
  collisionType = (char *)0x0;
  while( true ) {
    f1 = (D3DXPlane *)(camera->field0_0x0 + (uint)plane_index * 0x10 + 0x48);
    v = (vec3 *)(camera->field0_0x0 + (uint)plane_index * 0x10 + 0x48);
    if (0.0 < (f1->normal).x || (f1->normal).x == 0.0) {
      xmult1 = pos1->x;
      xmult2 = pos2->x;
    }
    else {
      xmult1 = pos2->x;
      xmult2 = pos1->x;
    }
    if (0.0 < v->y || v->y == 0.0) {
      ymult1 = pos1->y;
      ymult2 = pos2->y;
    }
    else {
      ymult1 = pos2->y;
      ymult2 = pos1->y;
    }
    if (0.0 < v->z || v->z == 0.0) {
      fVar6 = pos1->z;
      fVar7 = pos2->z;
    }
    else {
      fVar6 = pos2->z;
      fVar7 = pos1->z;
    }
    if ((v->y * ymult1 + v->x * xmult1 + fVar6 * v->z) - v[1].x <= 0.0) {
      if ((v->y * ymult2 + v->x * xmult2 + fVar7 * v->z) - v[1].x <= 0.0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      uVar3 = 3;
    }
    uVar5 = uVar5 | uVar3;
    if (uVar5 == 3) break;
    plane_index = plane_index + 1;
    if (5 < plane_index) {
      plane_index = 0;
    }
    bVar1 = (char)collisionType + 1;
    collisionType = (char *)(uint)bVar1;
    if (5 < bVar1) {
      return (uVar5 != 1) + 1;
    }
  }
  *puVar1 = plane_index;
  return 0;
}



undefined4
FUN_00159cc0(float *param_1,float *param_2,float *param_3,float param_4,float *param_5,float param_6
            ,float *param_7)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar8 = *param_1 - *param_3;
  fVar2 = param_1[1] - param_3[1];
  fVar9 = param_1[2] - param_3[2];
  fVar6 = param_2[2] - param_5[2];
  fVar5 = param_2[1] - param_5[1];
  fVar3 = *param_2 - *param_5;
  fVar4 = fVar6 * fVar6 + fVar3 * fVar3 + fVar5 * fVar5;
  fVar7 = (fVar8 * fVar8 + fVar9 * fVar9 + fVar2 * fVar2) - param_4 * param_4;
  if (1e-06 <= fVar4) {
    fVar2 = fVar3 * fVar8 + fVar6 * fVar9 + fVar5 * fVar2;
    if ((fVar2 <= 0.0) || (fVar7 <= 0.0)) {
      fVar3 = fVar2 * fVar2 - fVar7 * fVar4;
      if ((0.0 <= fVar3) &&
         ((fVar5 = fVar4 * param_6 + fVar2, 0.0 <= fVar5 || (fVar5 * fVar5 <= fVar3)))) {
        fVar1 = scaled_invsqrt(fVar3);
        *param_7 = (float)-((fVar1 + (float10)fVar2) / (float10)fVar4);
        return 1;
      }
    }
  }
  else if (fVar7 <= 0.0) {
    *param_7 = 0.0;
    return 1;
  }
  return 0;
}



undefined4
FUN_00159e20(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
            float *param_6,float param_7,float *param_8,float *param_9,float *param_10)

{
  float fVar1;
  float fVar2;
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
  
  fVar14 = param_2[1] - param_6[1];
  fVar12 = param_5[2] - param_3[2];
  fVar5 = param_5[1] - param_3[1];
  fVar1 = *param_5 - *param_3;
  fVar4 = *param_2 - *param_6;
  fVar10 = param_4[1] - param_3[1];
  fVar11 = param_4[2] - param_3[2];
  fVar9 = *param_4 - *param_3;
  fVar15 = param_2[2] - param_6[2];
  fVar16 = fVar14 * fVar12 - fVar15 * fVar5;
  fVar13 = fVar15 * fVar1 - fVar12 * fVar4;
  fVar6 = fVar5 * fVar4 - fVar14 * fVar1;
  fVar2 = fVar6 * fVar11 + fVar13 * fVar10 + fVar9 * fVar16;
  if (0.0 <= fVar2) {
    if (1e-06 <= fVar2) {
      fVar7 = param_1[1] - param_3[1];
      fVar3 = *param_1 - *param_3;
      fVar8 = param_1[2] - param_3[2];
      fVar6 = fVar8 * fVar6 + fVar7 * fVar13 + fVar3 * fVar16;
      if ((0.0 <= fVar6) && (fVar6 <= fVar2)) {
        fVar13 = fVar7 * fVar11 - fVar8 * fVar10;
        fVar11 = fVar8 * fVar9 - fVar3 * fVar11;
        fVar9 = fVar3 * fVar10 - fVar7 * fVar9;
        fVar4 = fVar9 * fVar15 + fVar11 * fVar14 + fVar4 * fVar13;
        if (0.0 <= fVar4) {
          if (((fVar4 + fVar6 <= fVar2) &&
              (fVar1 = fVar9 * fVar12 + fVar11 * fVar5 + fVar1 * fVar13, fVar1 <= fVar2 * param_7))
             && (0.0 <= fVar1)) goto LAB_0015a230;
        }
      }
    }
  }
  else if (fVar2 <= -1e-06) {
    fVar7 = param_1[1] - param_3[1];
    fVar3 = *param_1 - *param_3;
    fVar8 = param_1[2] - param_3[2];
    fVar6 = fVar8 * fVar6 + fVar7 * fVar13 + fVar3 * fVar16;
    if ((fVar6 <= 0.0) && (fVar2 <= fVar6)) {
      fVar13 = fVar7 * fVar11 - fVar8 * fVar10;
      fVar11 = fVar8 * fVar9 - fVar3 * fVar11;
      fVar9 = fVar3 * fVar10 - fVar7 * fVar9;
      fVar4 = fVar9 * fVar15 + fVar11 * fVar14 + fVar4 * fVar13;
      if (fVar4 <= 0.0) {
        if (((fVar2 <= fVar4 + fVar6) &&
            (fVar1 = fVar9 * fVar12 + fVar11 * fVar5 + fVar1 * fVar13, fVar2 * param_7 <= fVar1)) &&
           (fVar1 <= 0.0)) {
LAB_0015a230:
          fVar2 = 1.0 / fVar2;
          *param_8 = fVar2 * fVar1;
          *param_9 = fVar2 * fVar6;
          *param_10 = fVar2 * fVar4;
          return 1;
        }
      }
    }
  }
  return 0;
}




void Graphics::GetFallbackTexture(int param_1,D3DBaseTexture **param_2)

{
  undefined4 uVar1;
  int local_4;
  
  ModelInstance::BinaryEntry::getPtr(0x4d9644,&local_4);
  while (local_4 != 0) {
    if (*(int *)(local_4 + 0xc4) == param_1) {
      *(undefined4 *)(local_4 + 0x68) = 1;
      *param_2 = (D3DBaseTexture *)(local_4 + 200);
      return;
    }
    ModelInstance::BinaryEntry::getPtr(local_4,&local_4);
  }
  if (DAT_0054d950 != (code *)0x0) {
    uVar1 = (*DAT_0054d950)(param_1);
    GetFallbackTexture(uVar1,param_2);
    return;
  }
  *param_2 = (D3DBaseTexture *)0x0;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void Graphics::SetMatrix1(D3DXMATRIX *param_1)

{
  int iVar1;
  ShaderConstant *pSVar2;
  
  pSVar2 = Graphics::Matrix1;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pSVar2->field0_0x0 = param_1->m[0][0];
    param_1 = (D3DXMATRIX *)(param_1->m[0] + 1);
    pSVar2 = (ShaderConstant *)&pSVar2->field1_0x4;
  }
  return;
}




void Graphics::SetMatrix2(D3DXMATRIX *param_1)

{
  int iVar1;
  ShaderConstant *pSVar2;
  
  pSVar2 = Matrix2;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pSVar2->field0_0x0 = param_1->m[0][0];
    param_1 = (D3DXMATRIX *)(param_1->m[0] + 1);
    pSVar2 = (ShaderConstant *)&pSVar2->field1_0x4;
  }
  return;
}




void ndShader2Payload::UpdateOffsets(ndShader *param_1,int modelBase)

{
  param_1->shaderStart = (void *)((int)param_1->shaderStart + modelBase);
  return;
}




void FUN_0015b360(ndShader2Payload *param_1)

{
  D3D8::D3DDevice_CreatePixelShader(param_1->pixelShaderDef,&param_1->pixelShaderHandle);
  return;
}




void ndShader2Payload::useType0(void)

{
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  Graphics::RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_ZEnable(1);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
  Graphics::RenderState.zWriteEnabled = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,0);
  Graphics::RenderState.alphaBlendingEnabled = 0;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,0);
  Graphics::RenderState.alphaTestingEnabled = 0;
  return;
}




void ndShader2Payload::useType2(void)

{
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  Graphics::RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_ZEnable(1);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,1);
  Graphics::RenderState.zWriteEnabled = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,1);
  Graphics::RenderState.alphaBlendingEnabled = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,0);
  Graphics::RenderState.alphaTestingEnabled = 0;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_BLENDOP,0x8006);
  Graphics::RenderState.blendOp = D3DBLENDOP_ADD;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,0x302);
  Graphics::RenderState.srcBlend = D3DBLEND_SRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,0x303);
  Graphics::RenderState.destBlend = D3DBLEND_INVSRCALPHA;
  return;
}




void ndShader2Payload::useType1(void)

{
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  Graphics::RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_ZEnable(1);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZWRITEENABLE,0);
  Graphics::RenderState.zWriteEnabled = 0;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,1);
  Graphics::RenderState.alphaBlendingEnabled = 1;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,0);
  Graphics::RenderState.alphaTestingEnabled = 0;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_BLENDOP,D3DBLENDOP_ADD);
  Graphics::RenderState.blendOp = D3DBLENDOP_ADD;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
  Graphics::RenderState.srcBlend = D3DBLEND_SRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
  Graphics::RenderState.destBlend = D3DBLEND_INVSRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHAREF,5);
  Graphics::RenderState.alphaRef = 5;
  return;
}




void ndShader2Payload::useType3(void)

{
  useType1();
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_BLENDOP,0x8006);
  Graphics::RenderState.blendOp = D3DBLENDOP_ADD;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_SRCBLEND,0x302);
  Graphics::RenderState.srcBlend = D3DBLEND_SRCALPHA;
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_DESTBLEND,1);
  Graphics::RenderState.destBlend = D3DBLEND_ONE;
  return;
}




void Graphics::setCallback4(undefined *param_1)

{
  callback4 = param_1;
  return;
}




uint FUN_0015b670(ndShader *param_1)

{
  return *(uint *)((int)param_1->shaderStart + 0xd4) & 0xf;
}




void Graphics::SetSomeVec3(vec3 *param_1)

{
  vec3::Copy1Into2(param_1,&SomeVec3);
  return;
}




void Graphics::SetSomeTextureVar(DXTextureInstance **param_1)

{
  TextureInstanceList = param_1;
  return;
}




void Graphics::SetViewMatrix(D3DXMATRIX *viewMatrix)

{
  int iVar1;
  D3DXMATRIX *pDVar2;
  
  pDVar2 = &ViewMatrix;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pDVar2->m[0][0] = viewMatrix->m[0][0];
    viewMatrix = (D3DXMATRIX *)(viewMatrix->m[0] + 1);
    pDVar2 = (D3DXMATRIX *)((int)pDVar2 + 4);
  }
  return;
}




void Graphics::SetFromDisplayType(DisplayMatrices *param_1)

{
  vec3 rowMultiplier;
  vec3 eulers;
  
  AffineTransform::getEulers((AffineTransform *)param_1,&eulers);
  rowMultiplier.y = eulers.y;
  rowMultiplier.x = eulers.x;
  rowMultiplier.z = eulers.z;
  D3DXMATRIX::MultiplyByVec3(&param_1->projMatrix,&SomeMat4,rowMultiplier);
  return;
}



// WARNING: This is an inlined function


void Graphics::SetParam2Value(undefined4 param_1)

{
  Param2Value = param_1;
  return;
}



// WARNING: This is an inlined function


void FUN_00172ee0(DirectXShaderConstant *param_1,float *param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  float *pfVar6;
  float *pfVar7;
  DirectXShaderConstant *pDVar8;
  
  pfVar1 = &param_1[0x11].c2;
  param_2 = (float *)(&D3D8::D3D_g_pDevice->field2754_0x1098 + (int)param_2 * 4);
  do {
    uVar5 = (uint)*pfVar1 >> 0x12;
    pfVar2 = pfVar1 + 1;
    if (uVar5 == 1) {
      param_1 = DirectX::VertexShaderRegisters + (int)*pfVar2;
    }
    else {
      uVar4 = uVar5;
      pfVar6 = pfVar2;
      pDVar8 = param_1;
      pfVar7 = param_2;
      if (((uint)*pfVar1 & 0xffff) == 0xb00) {
        for (; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pfVar7 = *pfVar6;
          pfVar6 = pfVar6 + 1;
          pfVar7 = pfVar7 + 1;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)pfVar7 = *(undefined1 *)pfVar6;
          pfVar6 = (float *)((int)pfVar6 + 1);
          pfVar7 = (float *)((int)pfVar7 + 1);
        }
        param_2 = param_2 + uVar5;
      }
      else {
        for (; uVar4 != 0; uVar4 = uVar4 - 1) {
          pDVar8->c1 = *pfVar6;
          pfVar6 = pfVar6 + 1;
          pDVar8 = (DirectXShaderConstant *)&pDVar8->c2;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)&pDVar8->c1 = *(undefined1 *)pfVar6;
          pfVar6 = (float *)((int)pfVar6 + 1);
          pDVar8 = (DirectXShaderConstant *)((int)&pDVar8->c1 + 1);
        }
        param_1 = (DirectXShaderConstant *)(&param_1->c1 + uVar5);
      }
    }
    pfVar1 = pfVar2 + uVar5;
  } while (pfVar2[uVar5] != 0.0);
  return;
}




void FUN_001768b0(D3DSurface *param_1,D3DBaseTexture *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint32_t uVar3;
  D3D__Device *pDVar4;
  undefined1 local_170 [368];
  
  pDVar4 = D3D8::D3D_g_pDevice;
  FUN_00176200();
  D3D8::D3DDevice_SetRenderTarget(param_1,(D3DSurface *)0x0);
  D3D8::D3DDevice_SetTexture(0,param_2);
  FUN_00175d60();
  FUN_00175f60();
  uVar3 = D3D8::D3D_g_DeferredTextureState.field4_0x10;
  uVar1 = pDVar4->field2294_0x968;
  uVar2 = pDVar4->field2295_0x96c;
  pDVar4->field2294_0x968 = param_3;
  pDVar4->field2295_0x96c = param_3;
  D3D8::D3D_g_DeferredTextureState.field4_0x10 = 5;
  FUN_00176300();
  pDVar4->field2294_0x968 = uVar1;
  pDVar4->field2295_0x96c = uVar2;
  D3D8::D3D_g_DeferredTextureState.field4_0x10 = uVar3;
  FUN_00176080(local_170);
  FUN_00176290();
  return;
}



// WARNING: Control flow encountered bad instruction data
// WARNING: Switch with 1 destination removed at 0x00176a66
// WARNING: Exceeded maximum restarts with more pending

void D3D8::D3DDevice_Clear
               (DWORD Count,D3DRECT *pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)

{
  int iVar1;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar2;
  int iVar9;
  int iVar10;
  int iStack_34;
  uint local_28;
  D3DRECT DStack_10;
  float fVar2;
  D3D__Device *pDVar3;
  
  pDVar3 = D3D_g_pDevice;
  iVar1 = D3D_g_pDevice->field3354_0x19f8;
  iVar9 = D3D_g_pDevice->field3353_0x19f4;
  local_28 = 0;
  if (((&DAT_0017f958)[*(byte *)(iVar9 + 0xd)] & 1) != 0) {
    local_28 = FUN_0017af60(iVar9,iVar1);
    puVar2 = pDVar3->State;
    if (pDVar3->field1_0x4 <= puVar2) {
      D3DDevice_MakeSpace();
      puVar2 = puVar4;
    }
    *puVar2 = 0x40208;
    puVar2[1] = local_28 & 0xfffffdff | 0x100;
    pDVar3->State = puVar2 + 2;
  }
  if ((Flags & 0xf0) != 0) {
    switch(*(undefined1 *)(iVar9 + 0xd)) {
    case 3:
    case 0x1c:
      uVar5 = (Color >> 3 & 0x1f0000 | Color & 0xf800) >> 3;
      break;
    default:
      goto switchD_001769f7_caseD_4;
    case 5:
    case 0x11:
      uVar5 = (Color >> 3 & 0x1f0000 | Color & 0xfc00) >> 2;
    }
    Color = (uVar5 | Color & 0xf8) >> 3;
  }
switchD_001769f7_caseD_4:
  if ((iVar1 != 0) || (Flags = Flags & 0xfffffffc, Flags != 0)) {
    if ((Flags & 1) != 0) {
                    // WARNING: Bad instruction - Truncating control flow here
      halt_baddata();
    }
    iVar1 = pDVar3->field2640_0xed0;
    fVar2 = (float)pDVar3->field2641_0xed4;
    iVar9 = pDVar3->field2642_0xed8 + iVar1;
    iVar10 = pDVar3->field2643_0xedc + (int)fVar2;
    if (Count == 0) {
      pRects = &DStack_10;
      DStack_10.x1 = iVar1;
      DStack_10.y1 = (LONG)fVar2;
      DStack_10.x2 = iVar9;
      DStack_10.y2 = iVar10;
      Count = 1;
    }
    do {
      iStack_34 = pRects->x1;
      if (pRects->x1 <= iVar1) {
        iStack_34 = iVar1;
      }
      Z = (float)pRects->y1;
      if (pRects->y1 <= (int)fVar2) {
        Z = fVar2;
      }
      iVar6 = pRects->x2;
      if (iVar9 <= pRects->x2) {
        iVar6 = iVar9;
      }
      iVar8 = pRects->y2;
      if (iVar10 <= pRects->y2) {
        iVar8 = iVar10;
      }
      if ((iStack_34 < iVar6) && ((int)Z < iVar8)) {
        uVar5 = FUN_001782c0((float)iStack_34 * (float)pDVar3->field2290_0x958 + 0.5);
        iVar6 = FUN_001782c0((float)iVar6 * (float)pDVar3->field2290_0x958 + 0.5);
        uVar7 = FUN_001782c0((float)(int)Z * (float)pDVar3->field2291_0x95c + 0.5);
        iVar8 = FUN_001782c0((float)iVar8 * (float)pDVar3->field2291_0x95c + 0.5);
        puVar2 = pDVar3->State;
        if (pDVar3->field1_0x4 <= puVar2) {
          D3DDevice_MakeSpace();
          puVar2 = extraout_EAX;
        }
        *puVar2 = 0x81d98;
        puVar2[1] = iVar6 * 0x10000 - 0x10000U | uVar5;
        puVar2[2] = iVar8 * 0x10000 - 0x10000U | uVar7;
        puVar2[3] = 0xc1d8c;
        puVar2[4] = Stencil;
        puVar2[5] = Color;
        puVar2[6] = Flags;
        pDVar3->State = puVar2 + 7;
      }
      pRects = pRects + 1;
      Count = Count - 1;
    } while (Count != 0);
    if (local_28 != 0) {
      puVar2 = pDVar3->State;
      if (pDVar3->field1_0x4 <= puVar2) {
        D3DDevice_MakeSpace();
        puVar2 = extraout_EAX_00;
      }
      *puVar2 = 0x40208;
      puVar2[1] = local_28;
      pDVar3->State = puVar2 + 2;
    }
  }
  return;
}




HRESULT CreateNewXGBuffer(XGBufferCreationProps *props,XGBuffer **newBuffer)

{
  LPVOID buffer;
  uint uVar1;
  undefined4 *puVar2;
  HRESULT local_8;
  uint size;
  
  local_8 = 0;
  if ((props != (XGBufferCreationProps *)0x0) && (newBuffer != (XGBuffer **)0x0)) {
    size = props->size;
    local_8 = XGRAPHICS::XGBufferCreate(size,newBuffer);
                    // If error
    if (-1 < local_8) {
      buffer = XGRAPHICS::XGBuffer_GetBufferPointer(*newBuffer);
      puVar2 = props->data;
      for (uVar1 = size >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
        *(undefined4 *)buffer = *puVar2;
        puVar2 = puVar2 + 1;
        buffer = (undefined4 *)((int)buffer + 4);
      }
      for (size = size & 3; size != 0; size = size - 1) {
        *(undefined1 *)buffer = *(undefined1 *)puVar2;
        puVar2 = (undefined4 *)((int)puVar2 + 1);
        buffer = (undefined4 *)((int)buffer + 1);
      }
    }
  }
  return local_8;
}




undefined4 FUN_0018b009(XGBuffer *param_1)

{
  bool bVar1;
  uint *puVar2;
  int iVar3;
  LPVOID pvVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  
  puVar2 = XGRAPHICS::XGBuffer_GetBufferPointer(param_1);
  iVar3 = XGRAPHICS::XGBuffer_GetBufferSize(param_1);
  pvVar4 = XGRAPHICS::XGBuffer_GetBufferPointer(param_1);
  puVar5 = XGRAPHICS::XGBuffer_GetBufferPointer(param_1);
  *puVar5 = *puVar2;
  bVar1 = false;
  do {
    puVar5 = puVar5 + 1;
    puVar2 = puVar2 + 1;
switchD_0018b07a_default:
    do {
      while( true ) {
        puVar8 = puVar2;
        if (((uint *)((int)pvVar4 + iVar3) <= puVar8) || (bVar1)) {
          pvVar4 = XGRAPHICS::XGBuffer_GetBufferPointer(param_1);
          param_1->size = (int)puVar5 - (int)pvVar4;
          return 0;
        }
        uVar6 = *puVar8;
        uVar7 = uVar6 & 0xffff;
        puVar2 = puVar8 + 1;
        if (0x42 < uVar7) break;
        if (0x3f < uVar7) {
          *puVar5 = uVar6;
          goto LAB_0018b17a;
        }
        switch(uVar7) {
        case 0:
          *puVar5 = uVar6;
          puVar5 = puVar5 + 1;
          break;
        case 1:
        case 6:
        case 7:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x13:
          goto switchD_0018b07a_caseD_1;
        case 2:
        case 3:
        case 5:
        case 8:
        case 9:
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0x11:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
          goto switchD_0018b07a_caseD_2;
        case 4:
        case 0x12:
switchD_0018b07a_caseD_4:
          *puVar5 = uVar6;
          uVar6 = *puVar2;
          puVar5 = puVar5 + 1;
          puVar2 = puVar2 + 1;
          goto switchD_0018b07a_caseD_2;
        }
      }
      if (0x101 < uVar7) {
        if (uVar7 < 0x102) goto switchD_0018b07a_default;
        if (uVar7 < 0x104) {
LAB_0018b146:
          *puVar5 = uVar6;
          puVar5 = puVar5 + 1;
          *puVar5 = *puVar2;
          puVar2 = puVar8 + 2;
        }
        else {
          if (0x105 < uVar7) {
            if (uVar7 == 0x106) goto LAB_0018b146;
            if (uVar7 == 0xfffe) {
              puVar2 = puVar2 + (uVar6 >> 0x10 & 0x7fff);
            }
            else if (uVar7 == 0xffff) {
              *puVar5 = uVar6;
              puVar5 = puVar5 + 1;
              bVar1 = true;
            }
            goto switchD_0018b07a_default;
          }
          *puVar5 = uVar6;
        }
        puVar5[1] = *puVar2;
        uVar6 = puVar2[1];
        puVar5 = puVar5 + 2;
        puVar2 = puVar2 + 2;
        goto switchD_0018b07a_caseD_4;
      }
      if (uVar7 == 0x101) goto switchD_0018b07a_caseD_1;
      if (0x4f < uVar7) {
        if (uVar7 == 0x50) goto switchD_0018b07a_caseD_4;
        if (uVar7 == 0x100) break;
        goto switchD_0018b07a_default;
      }
      if (0x4c < uVar7) goto switchD_0018b07a_caseD_1;
      if (uVar7 < 0x43) goto switchD_0018b07a_default;
      if (uVar7 < 0x45) goto switchD_0018b07a_caseD_1;
      if (uVar7 < 0x47) goto switchD_0018b07a_default;
      if (uVar7 < 0x4c) goto switchD_0018b07a_caseD_1;
    } while (uVar7 != 0x4c);
switchD_0018b07a_caseD_2:
    *puVar5 = uVar6;
    uVar6 = *puVar2;
    puVar5 = puVar5 + 1;
    puVar2 = puVar2 + 1;
switchD_0018b07a_caseD_1:
    *puVar5 = uVar6;
    puVar5 = puVar5 + 1;
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
LAB_0018b17a:
    puVar5 = puVar5 + 1;
    *puVar5 = *puVar2;
  } while( true );
}




undefined4 __thiscall FUN_0019f7e3(undefined4 *param_1,XGBuffer *param_2,char *param_3)

{
  char cVar1;
  LPVOID pvVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *pcVar5;
  uint uVar6;
  char *pcVar7;
  
  FUN_0019f466();
  *param_1 = param_2;
  XGRAPHICS::XGBuffer_AddRef(param_2);
  pvVar2 = XGRAPHICS::XGBuffer_GetBufferPointer(param_2);
  param_1[1] = pvVar2;
  uVar3 = XGRAPHICS::XGBuffer_GetBufferSize(param_2);
  param_1[3] = 0;
  param_1[2] = uVar3;
  *(undefined1 *)(param_1 + 4) = 0;
  *(undefined1 *)((int)param_1 + 0x11) = 0;
  pcVar4 = param_3;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar4 = pcVar4 + (1 - (int)(param_3 + 1));
  pcVar5 = XAPILIB::XMemAlloc((uint)pcVar4,0x24870000);
  if (pcVar5 != (char *)0x0) {
    pcVar7 = pcVar5;
    for (uVar6 = (uint)pcVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)param_3;
      param_3 = param_3 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar6 = (uint)pcVar4 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar7 = *param_3;
      param_3 = param_3 + 1;
      pcVar7 = pcVar7 + 1;
    }
  }
  param_1[6] = 0xffffffff;
  param_1[0x12] = pcVar5;
  param_1[0x11] = 1;
  *(undefined1 *)((int)param_1 + 0x13) = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0x15) = 1;
  return 0;
}




int __fastcall PrintShaderException(char *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    if ((*(char *)(*(int *)(param_1 + 0x38) + 0x11) == '\0') &&
       (*(char *)(*(int *)(param_1 + 0x38) + 0x10) != '\0')) {
LAB_0019ff7f:
      if (-1 < iVar3) {
        return iVar3;
      }
LAB_0019ff83:
      FUN_0019ed5f(param_1,1,0xc,s_Source_line_too_long__001a49a8);
      return iVar3;
    }
    if (iVar3 < 0) goto LAB_0019ff83;
    iVar2 = FUN_0019fa8d();
    if (iVar2 == -1) goto LAB_0019ff7f;
    if (iVar2 == 10) {
      return 0;
    }
    if (iVar2 == 0xd) {
      FUN_0019f8ce(10);
      return 0;
    }
    if (iVar2 == 0x2f) {
      iVar3 = FUN_0019fa8d();
      if (iVar3 == 0x2a) {
        do {
          if ((*(char *)(*(int *)(param_1 + 0x38) + 0x11) == '\0') &&
             (*(char *)(*(int *)(param_1 + 0x38) + 0x10) != '\0')) {
            FUN_0019ed5f(param_1,1,0x17,s_Un_terminated_C_style_comment__E_001a49c0);
            return -0x7fffbffb;
          }
          iVar3 = FUN_0019fa8d();
        } while ((iVar3 != 0x2a) || (cVar1 = FUN_0019fad1(0x2f), cVar1 == '\0'));
        iVar2 = 0x20;
      }
      else {
        if (iVar3 == 0x2f) {
LAB_0019ff4f:
          FUN_0019faf5();
          return 0;
        }
        FUN_0019edfa(iVar3);
        iVar2 = 0x2f;
      }
    }
    else if (iVar2 == 0x3b) goto LAB_0019ff4f;
    iVar3 = FUN_0018941c(iVar2);
  } while( true );
}




int LoadShader(undefined4 param_1)

{
  void *pvVar1;
  int success;
  int iVar2;
  undefined4 uVar3;
  int local_68;
  char *local_64;
  int local_60;
  char local_5c [4];
  char local_58 [4];
  char local_54 [4];
  char acStack_50 [2];
  char cStack_4e;
  char local_4c [4];
  char acStack_48 [2];
  char cStack_46;
  undefined4 local_44;
  undefined2 uStack_40;
  undefined1 uStack_3e;
  char local_3c [8];
  char local_34 [4];
  char acStack_30 [4];
  char local_2c [4];
  char acStack_28 [4];
  char local_24 [4];
  char acStack_20 [4];
  undefined4 local_1c;
  undefined1 uStack_18;
  undefined4 local_14;
  undefined1 uStack_10;
  void *local_c;
  char local_8;
  char cStack_6;
  
  local_4c = (char  [4])s_define_001a4cc4._0_4_;
  acStack_48 = (char  [2])s_define_001a4cc4._4_2_;
  cStack_46 = s_define_001a4cc4[6];
  local_54 = (char  [4])s_pragma_001a4cbc._0_4_;
  acStack_50 = (char  [2])s_pragma_001a4cbc._4_2_;
  cStack_4e = s_pragma_001a4cbc[6];
  local_34 = (char  [4])s_undef_001a4cb4._0_4_;
  acStack_30._0_2_ = s_undef_001a4cb4._4_2_;
  builtin_strncpy(local_3c,"error",6);
  _local_8 = _if_;
  cStack_6 = s__001a4cb2[0];
  local_24 = (char  [4])s_ifdef_001a4ca0._0_4_;
  acStack_20._0_2_ = s_ifdef_001a4ca0._4_2_;
  local_44 = DAT_001a4c98;
  uStack_40 = DAT_001a4c9c;
  uStack_3e = DAT_001a4c9e;
  local_1c = DAT_001a4c90;
  uStack_18 = DAT_001a4c94;
  local_14 = DAT_001a4c88;
  local_5c = (char  [4])s_include_001a4ca8._0_4_;
  uStack_10 = DAT_001a4c8c;
  local_58 = (char  [4])s_include_001a4ca8._4_4_;
  local_2c = (char  [4])s_endif_001a4c80._0_4_;
  acStack_28._0_2_ = s_endif_001a4c80._4_2_;
  success = FUN_0019eaef(&local_68,&param_1,1);
  pvVar1 = local_c;
  if (success < 0) {
    return success;
  }
  if (local_68 != 0) {
    FUN_0019ed5f(local_c,1,1,s_Unknown_preprocessor_directive_001a4c60);
    success = -0x7fffbffb;
  }
  if (success < 0) {
    return success;
  }
  if (*(char *)(*(int *)((int)pvVar1 + 0x38) + 0x15) == '\0') {
    if (local_60 == 2) {
      iVar2 = _strncmp(local_64,&local_8,2);
      if (iVar2 != 0) {
        return success;
      }
LAB_001a12bb:
      success = FUN_0019f1cc(param_1);
      return success;
    }
    if (local_60 == 5) {
      iVar2 = _strncmp(local_64,local_24,5);
      if (iVar2 != 0) {
        iVar2 = _strncmp(local_64,local_2c,5);
        if (iVar2 != 0) {
          return success;
        }
LAB_001a12f8:
        success = FUN_0019f248(param_1);
        return success;
      }
LAB_001a121c:
      uVar3 = 1;
    }
    else {
      if (local_60 != 6) {
        if (local_60 != 4) {
          return success;
        }
        iVar2 = _strncmp(local_64,(char *)&local_14,4);
        if (iVar2 != 0) {
          iVar2 = _strncmp(local_64,(char *)&local_1c,4);
          if (iVar2 != 0) {
            return success;
          }
LAB_001a1370:
          success = FUN_0019f21d(param_1);
          return success;
        }
LAB_001a134e:
        success = FUN_0019f1fd(param_1);
        return success;
      }
      iVar2 = _strncmp(local_64,(char *)&local_44,6);
      if (iVar2 != 0) {
        return success;
      }
      uVar3 = 0;
    }
LAB_001a132b:
    success = FUN_0019f687(param_1,uVar3);
  }
  else {
    if (local_60 == 7) {
      success = _strncmp(local_64,local_5c,7);
      local_c = pvVar1;
      if (success == 0) {
        success = FUN_001a0ee8(param_1);
        return success;
      }
    }
    else if (local_60 == 6) {
      success = _strncmp(local_64,local_4c,6);
      if (success == 0) {
        success = FUN_001a03a9(param_1);
        return success;
      }
      success = _strncmp(local_64,local_54,6);
      if (success == 0) {
        success = FUN_001a0eca(param_1);
        return success;
      }
      success = _strncmp(local_64,(char *)&local_44,6);
      local_c = pvVar1;
      if (success == 0) {
        uVar3 = 0;
        goto LAB_001a132b;
      }
    }
    else if (local_60 == 5) {
      success = _strncmp(local_64,local_34,5);
      if (success == 0) {
        success = FUN_001a0599(param_1);
        return success;
      }
      success = _strncmp(local_64,local_3c,5);
      if (success == 0) {
        success = FUN_0019f273(param_1);
        return success;
      }
      success = _strncmp(local_64,local_24,5);
      if (success == 0) goto LAB_001a121c;
      success = _strncmp(local_64,local_2c,5);
      if (success == 0) goto LAB_001a12f8;
    }
    else if (local_60 == 2) {
      success = _strncmp(local_64,&local_8,2);
      if (success == 0) goto LAB_001a12bb;
    }
    else if (local_60 == 4) {
      success = _strncmp(local_64,(char *)&local_14,4);
      if (success == 0) goto LAB_001a134e;
      success = _strncmp(local_64,(char *)&local_1c,4);
      if (success == 0) goto LAB_001a1370;
    }
    FUN_0019ed5f(local_c,1,1,s_Unknown_preprocessor_directive_001a4c60);
    success = -0x7fffbffb;
  }
  return success;
}




