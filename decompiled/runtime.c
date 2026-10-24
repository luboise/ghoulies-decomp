/* runtime.c - Runtime data structures: BigBlock, EDB2, buffers, loctext, fonts */
#include "runtime.h"

void runtime::TriggerAppError(void)

{
  float *pfVar1;
  float baseX;
  float baseY;
  Scene *pSVar2;
  LoctextValueContext *pLVar3;
  int in_EAX;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  undefined4 local_88 [7];
  undefined4 local_6a [25];
  
  if (DAT_004dd900 == 3) {
    UnregisterScript__((int)DAT_004dea10);
    DAT_004dea10 = (LoctextValueContext *)0x0;
    if (DAT_004de9a0 != (Scene *)0x0) {
      Scene::free(DAT_004de9a0);
      DAT_004de9a0 = (Scene *)0x0;
    }
    Cutscene::dtor(g_cutsceneBuffer);
    g_cutsceneBuffer = (Cutscene *)0x0;
    Camera::setActiveCamera(&Camera::ErrorDialogPage1Camera);
  }
  pSVar2 = DAT_004de9a0;
  DAT_004dd900 = in_EAX;
  if (in_EAX == 1) {
    pcVar5 = "aid_loctext_ghoulies_apperror";
    puVar6 = local_88;
    for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      puVar6 = puVar6 + 1;
    }
    *(undefined2 *)puVar6 = *(undefined2 *)pcVar5;
    puVar6 = local_6a;
    for (iVar4 = 0x18; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    *(undefined2 *)puVar6 = 0;
    Scripting::CreateInputHandler3((InputHandlerType3 **)&DAT_004de99c);
    Camera::ctor(&Camera::ErrorDialogPage1Camera,"AppMainErrorDialog",(ProjectionSetBitField)0x8);
    Camera::ErrorDialogPage1Camera.aspectRatioType = 0;
    Camera::ComputeTangents
              (Camera::ErrorDialogPage1Camera.fov,(int *)&local_a8,&local_90,&local_8c,
               &Camera::ErrorDialogPage1Camera.aspectRatio,
               &Camera::ErrorDialogPage1Camera.cotangentOffset,0,&local_a0,&local_98);
    Camera::AppendAndSelect(&Camera::ErrorDialogPage1Camera,0);
    g_cutsceneBuffer =
         Assets::LoadCutscene
                   ("aid_cutscene_ghoulies_dialogs_dialogpage1",6,&Camera::ErrorDialogPage1Camera);
    Camera::SetActiveCameraConfig(0,"AppMainErrorDialog");
    local_a8 = g_DXContext.field32_0x58 + FLOAT_00339f78;
    local_a4 = g_DXContext.field35_0x64 - FLOAT_00339f7c;
    local_a0 = FLOAT_00339f88 * 0.0;
    local_94 = FLOAT_00339f80 * 0.5 * FLOAT_00339f88;
    local_98 = local_94 + FLOAT_00339f84;
    local_9c = 0.0 - FLOAT_00339f88 * FLOAT_00339f80;
    local_94 = 0.0 - local_94;
    TransitionAndLoadScene
              (0,DAT_004de9a4,&local_a8,&local_a0,&local_98,0,FLOAT_00339f88,FLOAT_00339f8c,
               "apperror",local_88,0x80);
    pSVar2 = DAT_004de9a0;
    pfVar1 = &DAT_004de9a0->someTimer;
    DAT_004de9a0->originalTimerValue = 0.2;
    if (0.2 < *pfVar1) {
      pSVar2->someTimer = 0.2;
    }
    *(undefined4 *)(pSVar2->field3814_0x1020 + 0x20) = 0x3e4ccccd;
    iVar4 = DAT_004de9a0->field3814_0x1020;
    *(float *)(iVar4 + 0x14) = _DAT_00339f90;
    *(undefined4 *)(iVar4 + 0x18) = s___333_AppMainErrorDialogMenu_1_00339f92._2_4_;
    *(undefined4 *)(iVar4 + 0x1c) = 3;
    AllocateForLoctext_(0,1,(void *)0xc0,&DAT_004dea10);
    pLVar3 = DAT_004dea10;
    baseY = FLOAT_00339f64;
    baseX = FLOAT_00339f60;
    (DAT_004dea10->somePos).x = _DAT_00339f90;
    (pLVar3->somePos).y = (float)s___333_AppMainErrorDialogMenu_1_00339f92._2_4_;
    pLVar3->maybeState = 3;
    DAT_004dea14 = CreateLoctext(DAT_004dea10,(LPWSTR)&DAT_004dd904,baseX,baseY,FLOAT_00339f68,
                                 FLOAT_00339f68,1.0,1,0,1);
    DAT_004dea18 = CreateLoctext(DAT_004dea10,(LPWSTR)&DAT_004dd984,FLOAT_00339f6c,FLOAT_00339f70,
                                 FLOAT_00339f74,FLOAT_00339f74,1.0,1,0,1);
    DAT_004dea10->lineWidth = FLOAT_00339f5c;
  }
  else {
    if (in_EAX == 3) {
      DAT_004de9a0->field2160_0x950 = 0;
      FUN_00142c20(3,pSVar2);
      FUN_0005f970(DAT_004dea10);
      return;
    }
    if (in_EAX == 4) {
      g_globalFlagset = g_globalFlagset & ~DoRenderLoop?;
      (**(code **)(&DAT_004de98c + DAT_004dea1c * 4))
                (*(undefined4 *)(&DAT_004de994 + DAT_004dea1c * 4));
      if (DAT_004de99c != 0) {
        FUN_00108230();
        DAT_004de99c = 0;
        return;
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void SetupSomeAssetLoader(void)

{
  g_openBundles = malloc_(192);
  g_openBundles->head = g_openBundles->values;
  g_openBundles->tail = g_openBundles->values;
  g_openBundles->valueSize = 44;
  g_openBundles->capacity = 4;
  g_openBundles->end = (BundleContext *)&g_openBundles[3].end;
  g_openBundleContexts_ = 0;
  g_some0x2cMinSize = 0;
  g_some0x2cBufferSize = 0;
  game::bundle_opened_successfully = 0;
  Assets::createDirectoryResolver
            (someResource::getAssetDescription,someResource::SetFilePointerFromBundle,
             someResource::dtor,3,0);
  return;
}




void runtime::OpenOrDeleteFolder(PCSZ dirName,uint param_2,uint param_3)

{
  undefined1 uVar1;
  char cVar2;
  PCSZ pTVar3;
  char *pcVar4;
  HANDLE dir;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  FILE_DIRECTORY_INFORMATION dir_info;
  
  pTVar3 = dirName;
  do {
    pcVar4 = pTVar3;
    pTVar3 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  pcVar4[0] = '\\';
  pcVar4[1] = '*';
  pcVar4[2] = '\0';
  dir = System__OpenDirectory(dirName,&dir_info);
  if (dir != (HANDLE)0xffffffff) {
    do {
      uVar8 = 0;
      pbVar9 = (byte *)((int)&dir_info.EndOfFile + 4);
      uVar1 = dir_info.EndOfFile.s.HighPart._0_1_;
      while (uVar1 != 0) {
        uVar8 = ((byte)uVar1 & 0xdf) + uVar8 * 0x10;
        pbVar9 = pbVar9 + 1;
        uVar5 = uVar8 & 0xf0000000;
        if (uVar5 != 0) {
          uVar8 = uVar8 ^ (uVar5 >> 0x18 | uVar5);
        }
        uVar1 = *pbVar9;
      }
      if ((uVar8 != param_2) && (uVar8 != param_3)) {
        pcVar6 = (char *)((int)&dir_info.EndOfFile + 4);
        iVar7 = 1 - (int)pcVar6;
        do {
          cVar2 = *pcVar6;
          pcVar6[(int)(pcVar4 + iVar7)] = cVar2;
          pcVar6 = pcVar6 + 1;
        } while (cVar2 != '\0');
        MarkForDeletion(dirName);
      }
      iVar7 = FUN_0014b22f(dir,&dir_info);
    } while (iVar7 != 0);
    XAPILIB::CloseHandle(dir);
  }
  *pcVar4 = '\0';
  return;
}




void SetupWeirdStruct1Array(void)

{
  AudioStruct1OffsetPtr ptr;
  
  ptr = &g_AudioSources[0].next_;
  do {
    ADJ(ptr).parentIndex = 0xffff;
    *(undefined1 *)&ADJ(ptr)->field1_0x2 = 0;
    ADJ(ptr)->next_ = 0;
    ptr = ptr + 0x23;
  } while ((int)ptr < 0x4e0c54);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void NothingApparently2_(void)

{
  AudioParentState state;
  audio_struct_1 *source;
  ushort parentIndex;
  
  source = g_AudioSources;
  do {
    parentIndex = source->parentIndex;
    if (parentIndex != 0xffff) {
      state = Free;
                    // If it should be playing? (ie, shouldn't be paused or ended)
      if (((Audio::SoundSources[(short)parentIndex].cue == (IXACT_Cue *)0x0) ||
          ((((state = Audio::SoundSources[(short)parentIndex].state, state != ShouldGoTo4_1 &&
             (state != ShouldGoTo4_2)) && (state != ShouldPause1)) &&
           ((state != ShouldPause2 && (state != ShouldPause3)))))) && (source->next_ != 0)) {
        *(undefined1 *)&source->field1_0x2 = 0;
        AudioParent::UpdateState(0,Audio::SoundSources + (short)parentIndex,state);
        source->parentIndex = 0xffff;
        source->soundSourceState = 0;
        source->next_ = 0;
      }
    }
    source = source + 1;
  } while ((int)source < 0x4e0bcc);
  _DAT_004e0bcc = 1.0;
  return;
}




byte runtime::GetSpaceUsedByDiskType(DiskId diskId,uint *outSum1,uint *outSum2)

{
  uint sum1;
  uint sum2;
  int uVar1;
  CacheContext **ppCVar1;
  uint val1;
  uint val2;
  
  sum1 = 0;
  sum2 = 0;
  ppCVar1 = &g_someCacheContextPtr;
  uVar1 = 0;
  do {
    if ((*(DiskId *)((int)&Audio::WavebankDrives[0].diskId + uVar1) == diskId) &&
       (*ppCVar1 != (CacheContext *)0x0)) {
      GetValsFromCacheContext_(*ppCVar1,&val1,&val2);
      sum1 = sum1 + val1;
      sum2 = sum2 + val2;
    }
    uVar1 = uVar1 + 0x14;
    ppCVar1 = ppCVar1 + 3;
  } while ((uint)uVar1 < 0xf0);
  if (outSum1 != (uint *)0x0) {
    *outSum1 = sum1;
  }
  if (outSum2 != (uint *)0x0) {
    *outSum2 = sum2;
  }
  return -(sum1 != 0) & 0xea;
}



// WARNING: Inlined function: FUN_0015d060


BOOL SetModelInParent(AvatarParent *parent,avatar *av,int *someAID)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  Model *pMVar4;
  char *pcVar5;
  
  avatar::setModel(av,g_GlobalAssetName);
  if ((someAID != (int *)0x0) && (*someAID == 0x5f646961)) {
    piVar3 = someAID;
    do {
      iVar2 = *piVar3;
                    // write model AID
      *(char *)((int)av + (0x208 - (int)someAID) + (int)piVar3) = (char)iVar2;
      piVar3 = (int *)((int)piVar3 + 1);
    } while ((char)iVar2 != '\0');
    pMVar4 = Model::copyWithPoseFrom((char *)someAID,(parent->avatar).model);
    av->model = pMVar4;
    return 1;
  }
  pcVar5 = (parent->avatar).modelAID;
  iVar2 = 0x208 - (int)pcVar5;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)av + iVar2] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  pMVar4 = (parent->avatar).model;
  if (pMVar4 != (Model *)0x0) {
    pMVar4 = Model::init(pMVar4);
    av->model = pMVar4;
    return 1;
  }
  av->model = (Model *)0x0;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void runtime::ClearAllCams(void)

{
  char cVar1;
  char *pcVar2;
  CameraLLNode *avail_cam;
  int iVar3;
  Camera **active_cam;
  
  iVar3 = 0x1cbc18;
  active_cam = Camera::ActiveConfigs;
  avail_cam = Camera::AvailableConfigs;
  do {
    avail_cam->head = (Camera *)0x0;
    avail_cam->projectionSet = (Camera *)0x0;
    *active_cam = (Camera *)0x0;
    pcVar2 = "";
    do {
      cVar1 = *pcVar2;
      pcVar2[iVar3] = cVar1;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    avail_cam = avail_cam + 1;
    active_cam = active_cam + 1;
    iVar3 = iVar3 + 0x21;
  } while ((int)avail_cam < 0x4e16a0);
  _DAT_004e1734 = 0;
  g_itemsToClear = 0;
  return;
}




void runtime::Clear_g_itemsToClear(void)

{
  int *mem;
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  mem = g_itemsToClear;
  while (mem != (int *)0x0) {
    g_itemsToClear = mem;
    if (*mem != 0) {
      *(int *)(*mem + 4) = mem[1];
    }
    if ((int *)mem[1] != (int *)0x0) {
      *(int *)mem[1] = *mem;
    }
    *mem = 0;
    mem[1] = 0;
    iVar2 = FindHeapOf(mem);
    uVar1 = CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
      pHVar3 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar3 = g_HeapTableBase + iVar2;
    }
    CurrentHeapToAllocateFrom = iVar2;
    XAPILIB::HeapFree(pHVar3->heapHandle,0,mem);
    mem = g_itemsToClear;
    CurrentHeapToAllocateFrom = uVar1;
  }
  g_itemsToClear = mem;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int DataViewList::GetResourceByAddress(DataViewList *resource,void *offsetIntoRes)

{
  void *total_size;
  void *pvVar1;
  uint i;
  ChunkLocator *data_view;
  
  i = 0;
  if (resource->numItems != 0) {
    data_view = (ChunkLocator *)&resource->items[0].size;
    total_size = (void *)0x0;
    do {
      pvVar1 = (void *)((int)total_size + data_view->offset);
      if (offsetIntoRes < pvVar1) {
        return (resource->items[i].offset - (int)total_size) + (int)offsetIntoRes;
      }
      i = i + 1;
      data_view = data_view + 1;
      total_size = pvVar1;
    } while (i < resource->numItems);
  }
  return 0;
}




void runtime::InitialiseFontResources(void)

{
  undefined2 *puVar1;
  FontDescriptor *pFVar2;
  astruct_29 *paVar3;
  RuntimeFonts *pRVar4;
  int i;
  HeapTableEntry *pHVar5;
  LanguageID id;
  FontDescriptor *local_10;
  FontDescriptor *local_c;
  FontDescriptor *local_8;
  FontDescriptor *local_4;
  
  Assets::GetResourceBytes("aid_texture_ghoulies_font_nullchar",(void **)&id);
  if (id == ENGLISH) {
    ExitGame(2);
  }
  Font::NullCharResource = (FontDescriptor *)id;
  id = LanguageID;
  if (((int)LanguageID < 6) || (LanguageIsJapanese = 1, 8 < (int)LanguageID)) {
    LanguageIsJapanese = 0;
  }
  pRVar4 = &GloopyFontResource;
  i = 0;
  do {
    if (id == KOREAN) {
      if (*(int *)(asset_name_ARRAY_002ff5e8[0] + i) == 0x5f646961) {
        Assets::GetResourceBytes(asset_name_ARRAY_002ff5e8[0] + i,&local_4);
        pFVar2 = local_4;
        goto LAB_00060448;
      }
      pFVar2 = (FontDescriptor *)0x0;
    }
    else if (id == CHINESE) {
      if (*(int *)(asset_name_ARRAY_002ff3e8[0] + i) == 0x5f646961) {
        Assets::GetResourceBytes(asset_name_ARRAY_002ff3e8[0] + i,&local_8);
        pFVar2 = local_8;
        goto LAB_00060448;
      }
      pFVar2 = (FontDescriptor *)0x0;
    }
    else if (id == JAPANESE) {
      if (*(int *)(asset_name_ARRAY_002ff4e8[0] + i) == 0x5f646961) {
        Assets::GetResourceBytes(asset_name_ARRAY_002ff4e8[0] + i,&local_c);
        pFVar2 = local_c;
        goto LAB_00060448;
      }
      pFVar2 = (FontDescriptor *)0x0;
    }
    else if (*(int *)(asset_name_ARRAY_002ff2e8[0] + i) == 0x5f646961) {
      Assets::GetResourceBytes(asset_name_ARRAY_002ff2e8[0] + i,&local_10);
      pFVar2 = local_10;
LAB_00060448:
      if (pFVar2 == (FontDescriptor *)0x0) {
        ExitGame(2);
      }
    }
    else {
      pFVar2 = (FontDescriptor *)0x0;
    }
    pRVar4->gloopy = pFVar2;
    pRVar4 = (RuntimeFonts *)&pRVar4->dialog;
    i = i + 0x80;
    if (0x50444b < (int)pRVar4) {
      FLOAT_005043e0 = (float)-1;
      Font::DefaultFontScale.x = 1.0;
      Font::DefaultFontScale.y = 1.0;
      UINT_005043dc = 0;
      UINT_005043ec = 0;
      g_halfDialogTextHeight =
           (float)(int)(&GloopyFontResource.gloopy)[currentFontType]->lineHeight * 0.5;
      DAT_00504404 = 0x80000000;
      g_halfDialogTextOffset_ =
           (float)(int)(&GloopyFontResource.gloopy)[currentFontType]->xOffset_ * 0.5;
      DAT_005043f0 = 0;
      Font::DefaultSize = 0.0;
      DAT_00504408 = 2.0;
      _DAT_0050440c = 2.0;
      DAT_00504400 = 0;
      if (g_HeapTableBase[CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
        pHVar5 = (HeapTableEntry *)0x0;
      }
      else {
        pHVar5 = g_HeapTableBase + CurrentHeapToAllocateFrom;
      }
      paVar3 = (astruct_29 *)AllocateOnHeap(pHVar5->heapHandle,0,0x24);
      if (paVar3 != (astruct_29 *)0x0) {
        i = FUN_0014ded0(pHVar5->heapHandle,0,paVar3);
        puVar1 = (undefined2 *)(i + -4 + (int)paVar3);
        *puVar1 = 0x1234;
        *(undefined1 *)(puVar1 + 1) = *(undefined1 *)&pHVar5->field32_0x20;
      }
      paVar3->head = (astruct_55 *)(paVar3 + 1);
      paVar3->tail = (astruct_55 *)(paVar3 + 1);
      paVar3->valueSize = 4;
      paVar3->capacity = 4;
      paVar3->end = (astruct_55 *)(paVar3 + 2);
      LoctextValueBuffer = paVar3;
      paVar3->tail = paVar3->head;
      LoctextIndex = 1;
      FUN_0005f210();
      return;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void ClearIDKBigStruct(void)

{
  IdkBigStruct_00504450.field0_0x0 = 0xff000000;
  IdkBigStruct_00504450.field1_0x4 = 0xff000000;
  IdkBigStruct_00504450.field2_0x8 = 0xff000000;
  IdkBigStruct_00504450.field3_0xc.x = 0.0;
  IdkBigStruct_00504450.field3_0xc.y = 0.0;
  IdkBigStruct_00504450.field3_0xc.z = 0.0;
  IdkBigStruct_00504450.field3_0xc.w = 0.0;
  IdkBigStruct_00504450.field4_0x1c = 0;
  IdkBigStruct_00504450.g_float1 = 0.0;
  IdkBigStruct_00504450.field10_0x34 = 0;
  IdkBigStruct_00504450.field11_0x38 = 0;
  IdkBigStruct_00504450.field12_0x3c = 0;
  IdkBigStruct_00504450.field13_0x40 = 0;
  IdkBigStruct_00504450.field14_0x44 = 0;
  IdkBigStruct_00504450.field15_0x48 = 0;
  IdkBigStruct_00504450.field8_0x2c = 0;
  IdkBigStruct_00504450.field9_0x30 = 0;
  IdkBigStruct_00504450.field6_0x24 = 0;
  IdkBigStruct_00504450.field7_0x28 = 0;
  IdkBigStruct_00504450.field17_0x50 = 0;
  IdkBigStruct_00504450.field18_0x54 = 0;
  IdkBigStruct_00504450.field16_0x4c = 0;
  IdkBigStruct_00504450.field19_0x58 = (float)-1;
  IdkBigStruct_00504450.field20_0x5c = 1.0;
  IdkBigStruct_00504450.field21_0x60 = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


Buffer * runtime::ExtendArray(Buffer *buf)

{
  int old_size;
  Buffer<> *new_buffer;
  int new_size;
  int *data;
  
  old_size = ((int)buf->tail - (int)buf->head) / (int)(uint)buf->valueSize;
  new_size = (uint)(ushort)buf->capacity + old_size;
  new_buffer = (Buffer<> *)AllocateMoreAStruct_33((uint)buf->valueSize * new_size + 0x10,buf);
  data = (int *)new_buffer->values;
  new_buffer->tail = (Asset *)((int)data + (uint)new_buffer->valueSize * old_size);
  new_buffer->head = (Asset *)data;
  new_buffer->end = (Asset *)((int)data + (uint)new_buffer->valueSize * new_size);
  return (Buffer *)new_buffer;
}




void * ExtendBuffer2(Buffer **param_1,int param_2)

{
  ushort uVar1;
  void *pvVar2;
  void *pvVar3;
  Buffer *pBVar4;
  int iVar5;
  void *pvVar6;
  
  pBVar4 = *param_1;
  pvVar2 = pBVar4->tail;
  pvVar6 = pBVar4->head;
  uVar1 = pBVar4->valueSize;
  if (pBVar4->tail == pBVar4->end) {
    pBVar4 = runtime::ExtendArray(pBVar4);
    *param_1 = pBVar4;
  }
  pvVar3 = pBVar4->tail;
  pBVar4->tail = (void *)((uint)pBVar4->valueSize + (int)pvVar3);
  if (param_2 != ((int)pvVar2 - (int)pvVar6) / (int)(uint)uVar1) {
    pBVar4 = *param_1;
    pvVar2 = pBVar4->head;
    iVar5 = (param_2 + 1) * (uint)pBVar4->valueSize;
    pvVar6 = (void *)((uint)pBVar4->valueSize * param_2 + (int)pvVar2);
    _memmove((void *)(iVar5 + (int)pvVar2),pvVar6,(int)pBVar4->tail + (-(int)pvVar2 - iVar5));
    return pvVar6;
  }
  return pvVar3;
}




BOOL obj::returnOne(void)

{
  return 1;
}




void runtime::ClearSomeType3AssetNames(void)

{
  char (*pacVar1) [128];
  
  resource::next_menu_id = 1;
  g_wString[0] = L'\0';
  game::nextPlaycamScriptWide[0] = L'\0';
  Audio::PauseMusicPlaying = 0;
  g_cutsceneDelta = 0.0;
  DAT_0042a0c8 = 0;
  DAT_0042a0c4 = 0;
  pacVar1 = g_someType3AssetNames;
  do {
    *(char *)((int)pacVar1 + 0) = '\0';
    *(char *)((int)pacVar1 + 1) = '\0';
    pacVar1 = pacVar1 + 2;
  } while ((int)pacVar1 < 0x42a0c4);
  Scripting::CreateInputHandler3(&Input::MenuInputHandler);
  return;
}




int __fastcall runtime::GetValsFromCacheContext_(CacheContext *cacheCtx,uint *param_2,uint *param_3)

{
  int err;
  uint uVar1;
  CacheContext *ctx;
  
  err = 0x490;
  ctx = &CacheContext;
  do {
    if (err != 0x490) break;
    if (ctx == cacheCtx) {
      err = 0;
    }
    ctx = (CacheContext *)ctx->nextCache;
  } while (ctx != (CacheContext *)0x0);
  if (err == 0) {
    uVar1 = cacheCtx->allocationSize - *(int *)cacheCtx->field6_0x18;
                    // (uVar1 & 0x10000000) ? uVar1 : 0
    *param_2 = ((int)uVar1 < 0) - 1 & uVar1;
    *param_3 = cacheCtx->allocationSize;
    err = 0xea;
  }
  return err;
}



uint runtime::ReadBNLFile
               (char *bnlFullPath,char *bnlName,astruct_20 **param_3,int callback,int param_5)

{
  FileSizeBlock fsb;
  FileSizeBlock fsb_00;
  DWORD err;
  FileContext *file2_2;
  uint unaff_EDI;
  bool error_occurred;
  FileContext *ctx2;
  FileContext *file1;
  FileContext *file1_1;
  
  file2_2 = (FileContext *)0x0;
  file1 = (FileContext *)0x0;
  ctx2 = (FileContext *)0x0;
  err = FileContext::Create(&file1,bnlFullPath,0x80000000,3);
  file1_1 = file1;
  if ((((err == 0) &&
       (fsb.field1_0x4 = unaff_EDI, fsb.bigStruct = (DWORD)&file1,
       err = FileContext::GetFileSizeOuter(file1,fsb), err == 0)) &&
      (err = FileContext::Create(&ctx2,bnlName,0x40000000,4), file2_2 = ctx2, err == 0)) &&
     (fsb_00.field1_0x4 = unaff_EDI, fsb_00.bigStruct = (DWORD)&ctx2,
     err = FileContext::GetFileSizeOuter(ctx2,fsb_00), err == 0)) {
    CreateCacheContext(file1_1,file2_2,param_3,callback,param_5);
    TryReadFileContexts(file2_2,file1);
    return 0;
  }
                    // All of this is error state
  if (file1_1 != (FileContext *)0x0) {
    FileContext::Close(file1_1);
  }
  if (file2_2 != (FileContext *)0x0) {
    FileContext::Close(file2_2);
  }
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    error_occurred = err == 0;
  }
  else {
    error_occurred = err == 0x4de;
  }
  if (!error_occurred) {
    GetErrorById(err,(char **)&ctx2,(char **)&file1);
  }
  return err;
}



void runtime::CreateCacheContext
               (FileContext *ctx1,FileContext *ctx2,astruct_20 **outA20,int callback,int param_5)

{
  FileSizeBlock fsb;
  astruct_20 *new_a20;
  CacheContext *cache_ptr;
  CacheContext *ppFVar1;
  uint uVar1;
  
  uVar1 = 0x34;
  new_a20 = malloc_(0x34);
  new_a20->file2 = ctx2;
  new_a20->callback = (void *)callback;
  new_a20->field2_0x8 = 0;
  new_a20->fileCtx = ctx1;
  new_a20->field23_0x30 = param_5;
  fsb.field1_0x4 = uVar1;
  fsb.bigStruct = (DWORD)&new_a20->filesize;
  FileContext::GetFileSizeOuter(ctx1,fsb);
  cache_ptr = &CacheContext;
  if (CacheContext.nextCache != (astruct_20 *)0x0) {
    cache_ptr = &CacheContext;
    do {
      ppFVar1 = (CacheContext *)&cache_ptr->nextCache;
      cache_ptr = (CacheContext *)ppFVar1->field0_0x0;
    } while (cache_ptr->nextCache != (astruct_20 *)0x0);
  }
  cache_ptr->nextCache = new_a20;
  new_a20->parent = (FileContext *)cache_ptr;
  new_a20->next_ = (astruct_20 *)0x0;
  if (outA20 != (astruct_20 **)0x0) {
    *outA20 = new_a20;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void GetErrorById(uint id,char **errorName,char **errorMessage)

{
  uint32_t curr_id;
  ErrorEntry *pEVar1;
  int i;
  
  i = 0;
  if (g_ErrorEntries[0].id != 0) {
    pEVar1 = g_ErrorEntries;
    curr_id = g_ErrorEntries[0].id;
    do {
      if (curr_id == id) {
        *errorName = g_ErrorEntries[i].name;
        *errorMessage = g_ErrorEntries[i].message;
        return;
      }
      curr_id = pEVar1[1].id;
      pEVar1 = pEVar1 + 1;
      i = i + 1;
    } while (curr_id != 0);
  }
  __snprintf(0x506608,0xf,"%d",id);
  *errorName = "Error Code";
  *errorMessage = runtime::CacheContext.field6_0x18;
  return;
}




void InitialiseCache(void)

{
  int i;
  char *pcVar1;
  
  FUN_000e8f10();
  XAPILIB::XSetFileCacheSize(0x20000);
  i = 0;
  do {
    pcVar1 = g_DISC_DRIVE_PREFIX + i;
    runtime::RootDirectory[i] = *pcVar1;
    i = i + 1;
  } while (*pcVar1 != '\0');
  pcVar1 = runtime::CacheContext.field523_0x278;
  for (i = 26; i != 0; i = i + -1) {
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = pcVar1 + 4;
  }
  runtime::CacheContext.field7_0x28 = (FileContext *)0x0;
  runtime::CacheContext.fileHead = (FileContext *)0x0;
  runtime::CacheContext.field9_0x30 = 0;
  runtime::CacheContext.field10_0x34 = 0;
  runtime::CacheContext.wavebankDrive = malloc_(0x20000);
  runtime::CacheContext.cache2 = malloc_(0x20000);
  runtime::CacheContext.field0_0x0 = 0;
  runtime::CacheContext.nextCache = (astruct_20 *)0x0;
  runtime::CacheContext._312_4_ = 0;
  runtime::CacheContext.field265_0x13c = 0;
  runtime::CacheContext.allocationSize = 0x20000;
  return;
}




void runtime::CreateHeapTables(uint param_1)

{
  HeapDataParams *params;
  uint i;
  
  i = 1;
  params = HeapTables;
  do {
    if (params->heap != (undefined *)0x0) {
      CreateNewHeap(params->index,i,params->heap,i,CONCAT44(param_1,params));
    }
    i = i + 1;
  } while ((params->index != 0) && (params = params + 1, params != (HeapDataParams *)0x0));
  return;
}




int FindHeapOf(void *mem)

{
  byte bVar1;
  int iVar2;
  int i;
  HANDLE *curr;
  
  i = 0;
  curr = &g_HeapTableBase[0].heapHandle;
  do {
    if (*curr != (void *)0x0) {
      iVar2 = FUN_0014ded0(*curr,0,mem);
      if (iVar2 == -1) {
        bVar1 = 0xff;
      }
      else {
        bVar1 = *(byte *)(iVar2 + -2 + (int)mem);
      }
      if ((HANDLE)(uint)bVar1 == curr[-1]) {
        return i;
      }
    }
    curr = curr + 0xc;
    i = i + 1;
    if (5273843 < (int)curr) {
      return 3;
    }
  } while( true );
}



void runtime::CreateNewHeap
               (uint tableIndex,uint index,undefined4 param_3,uint minHeapSize,ulonglong maxHeapSize
               )

{
  char cVar1;
  HANDLE new_heap;
  char *pcVar2;
  int i;
  int *puVar4;
  
  puVar4 = (int *)(g_HeapTableBase + tableIndex);
  for (i = 11; i != 0; i = i + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  new_heap = XAPILIB::HeapCreate(0,(ulonglong)minHeapSize << 0x20,maxHeapSize);
  g_HeapTableBase[tableIndex].heapHandle = new_heap;
  pcVar2 = "";
  do {
    cVar1 = *pcVar2;
    pcVar2[tableIndex * 0x30 + 0x1f1d78] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  g_HeapTableBase[tableIndex].field32_0x20 = tableIndex;
  g_HeapTableBase[tableIndex].field34_0x28 = 4;
  g_HeapTableBase[tableIndex].field34_0x28 = 8;
  g_HeapTableBase[tableIndex].field35_0x2c = index;
  return;
}




void FreePhysical(LPVOID lpAddress)

{
  XAPILIB::XPhysicalFree(lpAddress);
  return;
}




int SizeOf_g_int_12__array(void)

{
  int (*int_12__ptr) [12];
  int count;
  int i;
  
  i = 1;
  do {
    if (i == 0) {
      return count;
    }
    count = 1;
    int_12__ptr = (int (*) [12])&g_int_12__array;
    do {
      if ((*int_12__ptr)[0] == i) {
        if (count == 0) {
          i = 0;
        }
        else {
          i = i + 1;
        }
        goto LAB_000f72c3;
      }
      int_12__ptr = int_12__ptr + 1;
      count = count + 1;
    } while ((int)int_12__ptr < 0x5078fc);
    count = 0;
    i = 0;
LAB_000f72c3:
    if (count == 0) {
      return 0;
    }
  } while( true );
}




char * __thiscall AllocateMoreAStruct_33(uint size,void *param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  HeapTableEntry *pHVar5;
  
  iVar3 = FindHeapOf(param_2);
  uVar2 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
    pHVar5 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar5 = g_HeapTableBase + iVar3;
  }
  runtime::CurrentHeapToAllocateFrom = iVar3;
  pcVar4 = (char *)FUN_0014f1e1(pHVar5->heapHandle,0,param_2,size + 4);
  if (pcVar4 != (char *)0x0) {
    iVar3 = FUN_0014ded0(pHVar5->heapHandle,0,pcVar4);
    pcVar1 = pcVar4 + iVar3 + -4;
    pcVar1[0] = '4';
    pcVar1[1] = '\x12';
    pcVar1[2] = *(char *)&pHVar5->field32_0x20;
  }
  runtime::CurrentHeapToAllocateFrom = uVar2;
  return pcVar4;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void AllocateGlobalShorts(void)

{
  uint *puVar1;
  uint *puVar2;
  
  SomeGlobalAudioBuffer = malloc_(688);
  SomeGlobalAudioBuffer->head = SomeGlobalAudioBuffer->values;
  SomeGlobalAudioBuffer->tail = SomeGlobalAudioBuffer->values;
  SomeGlobalAudioBuffer->valueSize = 84;
  SomeGlobalAudioBuffer->capacity = 8;
  SomeGlobalAudioBuffer->end = (Audio0x54 *)(SomeGlobalAudioBuffer + 1);
  DAT_00507df4 = 0;
  puVar2 = &Input::RumbleContexts[0].uint0x8;
  puVar1 = g_AudioContext_[0].g_INT_ARRAY + 1;
  if ((*(byte *)PTR_00506c70->head & 4) != 0) {
    do {
      *puVar1 = 0;
      *puVar2 = 0;
      puVar1 = puVar1 + 7;
      puVar2 = puVar2 + 4;
    } while ((int)puVar1 < 0x507e04);
    return;
  }
  do {
    *puVar1 = 1;
    *puVar2 = 1;
    puVar1 = puVar1 + 7;
    puVar2 = puVar2 + 4;
  } while ((int)puVar1 < 0x507e04);
  return;
}




BOOL IsValidString(LPWSTR str)

{
  if ((str != (LPWSTR)0x0) && (*str != 0)) {
    return 0;
  }
  return 1;
}




void runtime::UpdateClocks(void)

{
  uint hz;
  uint hz2;
  float local_c;
  LARGE_INTEGER pc;
  float blanks;
  
  if ((Config::IsPal == 0) || (hz = 50, Config::Use60Hz != 0)) {
    hz = 60;
  }
  XAPILIB::QueryPerformanceCounter(&pc);
  ULONG_005096bc = pc.s.LowPart - g_PERFORMANCE_COUNTER;
  if ((Config::IsPal == 0) || (hz2 = 50, Config::Use60Hz != 0)) {
    hz2 = 60;
  }
  blanks = (float)VBlanksSinceLastFrame;
  if (VBlanksSinceLastFrame < 0) {
    blanks = blanks + 4.2949673e+09;
  }
  TrueDeltaTime = blanks / (float)hz2;
  DeltaTime = 5.0 / (float)hz;
  if (TrueDeltaTime <= 5.0 / (float)hz) {
    DeltaTime = TrueDeltaTime;
  }
  blanks = DeltaTime * 300.0 + TotalTicks;
  DeltaTicks = (int)blanks;
  TotalTicks = blanks - (float)DeltaTicks;
  return;
}



// Skip comments???


BOOL loctext::get_text(char *loctextAID,char *group,char *name,LPWSTR valueOut)

{
  int iVar1;
  BOOL BVar2;
  asset_name loctext_aid;
  char val [128];
  char local_180 [128];
  char val_to_get [256];
  char c;
  
                    // If mainStr not null, copy param 1 into asset_name
  if (loctextAID != (char *)0x0) {
    iVar1 = -(int)loctextAID;
    do {
      c = *loctextAID;
      loctextAID[(int)(loctext_aid + iVar1)] = c;
      loctextAID = loctextAID + 1;
    } while (c != '\0');
  }
  copy__a_zA_Z0_9__(val,name);
  _sprintf(val_to_get,"%s__%s",group,val);
  BVar2 = getStringFromLoctextResource(valueOut,loctext_aid,val_to_get);
  return BVar2;
}



// WARNING: Inlined function: Get20


char * copy__a_zA_Z0_9__(char *out,char *in)

{
  char *cPtr;
  char *length;
  int i;
  char c;
  
  cPtr = in;
  do {
    c = *cPtr;
    cPtr = cPtr + 1;
  } while (c != '\0');
  length = cPtr + -(int)(in + 1);
  cPtr = length + 1;
  i = 0;
  if (0 < (int)cPtr) {
    do {
      c = in[i];
      length = (char *)CONCAT31((int3)((uint)length >> 8),c);
      if ((((('/' < c) && (c < ':')) || (('@' < c && (c < '[')))) ||
          ((('`' < c && (c < '{')) || (c == '_')))) || (c == '\0')) {
        *out = c;
        out = out + 1;
      }
      i = i + 1;
    } while (i < (int)cPtr);
  }
  return length;
}



// WARNING: Inlined function: Get20


BOOL loctext::getStringFromLoctextResource(LPWSTR outStr,char *loctextAID,char *stringToGet)

{
  uint32_t hash;
  LoctextHeader *header;
  LPWSTR wString;
  
  if (*(int *)loctextAID == L'\x5f646961') {
    Assets::GetResourceBytes(loctextAID,&header);
    if (header == (LoctextHeader *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    header = (LoctextHeader *)0x0;
  }
  game::current_loctext_header = header;
  game::current_loctext_lookup_table = malloc_(20);
  LoctextHeaderReader::init(game::current_loctext_header,game::current_loctext_lookup_table);
  hash = LoctextHeader::getStringFromLookupTable
                   (game::current_loctext_header,game::current_loctext_lookup_table,stringToGet,
                    &wString);
                    // If string found
  if (hash != LOCTEXT_BAD_LOOKUP) {
    XAPILIB::lstrcpyW(outStr,wString);
    free(game::current_loctext_lookup_table);
    Assets::DestroyAssetOrDecrement(game::current_loctext_header);
    game::current_loctext_header = (LoctextHeader *)0x0;
    return 1;
  }
  *outStr = L'\0';
  free(game::current_loctext_lookup_table);
  Assets::DestroyAssetOrDecrement(game::current_loctext_header);
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void obj::getAllocDetails(ObjectAllocDetails *obj)

{
  obj->entitySize = 8;
  obj->paramsSize = 8;
  return;
}




ObjectFullVTable * obj::GetVTable(void)

{
  vtable.func0 = getAllocDetails;
  vtable.ctor = ctor;
  vtable.func2 = switchD_000d4179::EmptyFunction;
  vtable.func3 = switchD_000d4179::EmptyFunction;
  return (ObjectFullVTable *)&vtable;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// resourceType is 0 for cutscenes???


void __thiscall obj::destroy(Object *param_1,ushort param_2,int param_3)

{
  code *pcVar1;
  int vtable;
  
  while( true ) {
    vtable = (*(code *)(&VTableTable)[(uint)param_2 * 3])();
    pcVar1 = *(code **)(vtable + 8);
    if ((pcVar1 != (code *)0x0) && ((code *)param_3 != pcVar1)) {
                    // Destroy entitySceneControlGameSelect
      (*pcVar1)(param_1);
    }
    param_2 = *(ushort *)(&PreConstructorTable + (uint)param_2 * 0xc);
    if (param_2 == 0) break;
    param_3 = *(undefined4 *)(vtable + 8);
  }
  return;
}




BOOL obj::ctor(obj *object,objParams *params)

{
  object->tag = params->objInitValue;
  return 1;
}




ushort GetActorTagIndex(char *param_1)

{
  uint uVar1;
  
  uVar1 = Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,param_1);
  if (uVar1 == 0xffffffff) {
    return 0;
  }
  return (short)uVar1 + 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void CopySomeActorBodyList(SomeActorBodyList *src,SomeActorBodyList *dst)

{
  int8_t iVar1;
  int8_t iVar2;
  int8_t iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  uVar6 = 0x20;
  if (dst != src) {
    if ((((uint)dst & 7) == 0) && (((uint)src & 7) == 0)) {
      iVar4 = 4;
      do {
        iVar1 = src->field1_0x1;
        iVar2 = src->field2_0x2;
        iVar3 = src->field3_0x3;
        dst->field0_0x0 = src->field0_0x0;
        dst->field1_0x1 = iVar1;
        dst->field2_0x2 = iVar2;
        dst->field3_0x3 = iVar3;
        (dst->pos).x = (src->pos).x;
        dst = (SomeActorBodyList *)&(dst->pos).y;
        src = (SomeActorBodyList *)&(src->pos).y;
        uVar6 = uVar6 - 8;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    if (((((uint)dst & 3) == 0) && (((uint)src & 3) == 0)) && (3 < uVar6)) {
      uVar5 = uVar6 >> 2;
      do {
        iVar1 = src->field1_0x1;
        iVar2 = src->field2_0x2;
        iVar3 = src->field3_0x3;
        dst->field0_0x0 = src->field0_0x0;
        dst->field1_0x1 = iVar1;
        dst->field2_0x2 = iVar2;
        dst->field3_0x3 = iVar3;
        dst = (SomeActorBodyList *)&dst->pos;
        src = (SomeActorBodyList *)&src->pos;
        uVar6 = uVar6 - 4;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
    if (uVar6 != 0) {
      iVar4 = (int)src - (int)dst;
      do {
        dst->field0_0x0 = *(int8_t *)(iVar4 + (int)dst);
        dst = (SomeActorBodyList *)&dst->field1_0x1;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
  }
  return;
}




void runtime::GetLatestLoadableScript(char *param_1,LPCWSTR param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  SaveEntry *save_entry;
  Buffer<SaveEntry> *save;
  
  save = Saves->save1;
  save_entry = save->head;
  if (save_entry < save->tail) {
    while( true ) {
      iVar2 = XAPILIB::lstrcmpW((LPCWSTR)&save_entry->entries->field1_0x2,param_2);
      if (iVar2 == 0) break;
      save_entry = (SaveEntry *)((int)&save_entry->val1 + (uint)save->valueSize);
      if (save->tail <= save_entry) {
        return;
      }
    }
    pcVar3 = save_entry->entries->latestScriptToLoad;
    do {
      cVar1 = *pcVar3;
      *param_1 = cVar1;
      param_1 = param_1 + 1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
  }
  return;
}




void runtime::ClearSceneInfo(void)

{
  undefined4 *puVar1;
  
  Game::SceneInfo.avatars.prev = (avatar_0x900_conflict6)0x0;
  Game::SceneInfo.avatars.next = (avatar_0x900_conflict6)0x0;
  Game::SceneInfo.backgrounds.prevNode = (void *)0x0;
  Game::SceneInfo.backgrounds.head = (background_0x934_conflict3)0x0;
  Game::SceneInfo.field16_0x84 = 0;
  Game::SceneInfo.sceneTree_ = 0;
  Game::SceneInfo.field18_0x8c = 0;
  Game::SceneInfo.field19_0x90 = 0;
  puVar1 = Game::SceneInfo.bruhs + 3;
  do {
    puVar1[-3] = 0;
    puVar1[-2] = 0;
    puVar1[-1] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1 = puVar1 + 8;
  } while ((int)puVar1 < 0x511af4);
  Game::SceneInfo.field3_0x48 = 0;
  Game::SceneInfo.field4_0x4c = 0;
  Game::SceneInfo.field26_0xb4 = 0;
  Game::SceneInfo.field27_0xb8 = 0;
  Game::SceneInfo.avatarsWithCollision.next = (avatar_0x1e0)0x0;
  Game::SceneInfo.avatarsWithCollision.head = (avatar_0x1e0)0x0;
  Game::SceneInfo._88_4_ = 0;
  Game::SceneInfo.field10_0x5c = 0;
  Game::SceneInfo.avatars_0x110.sentinel = (void *)0x0;
  Game::SceneInfo.avatars_0x110.head = (EmbeddedNode<>_conflict *)0x0;
  Game::SceneInfo.newAvatars.prev = (avatar_0x900_conflict6)0x0;
  Game::SceneInfo.newAvatars.next = (avatar_0x900_conflict6)0x0;
  Game::SceneInfo.field13_0x70 = (void *)0x0;
  Game::SceneInfo.sceneTree.sentinel = (void *)0x0;
  Game::SceneInfo.sceneTree.head = (EmbeddedNode<>_conflict3 *)0x0;
  Game::SceneInfo.actors_0x934.next = (actor_0x934_conflict5)0x0;
  Game::SceneInfo.actors_0x934.head = (actor_0x934_conflict5)0x0;
  Game::SceneInfo.playerActors.next = (actor_0x93c_conflict5)0x0;
  Game::SceneInfo.playerActors.prev = (actor_0x93c_conflict5)0x0;
  Game::SceneInfo.field22_0xa4 = 0;
  Game::SceneInfo.enemies = (actor_0x944)0x0;
  Game::SceneInfo.field24_0xac = 0;
  Game::SceneInfo.field25_0xb0 = 0;
  return;
}




void runtime::FinaliseLoad(void)

{
  (*(code *)g_callback6Sets[*(int *)(&DAT_00431478 + TransitionData.transitionIndex * 0x110)][3])
            (&TransitionData);
  Camera::setActiveCamera(&Camera::TransitionConfig);
  if (TransitionData.discReadEnum == 0) {
    Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
    GlobalCounter2 = GlobalCounter2 + 1;
  }
  else if (TransitionData.discReadEnum == 1) {
    Game::GameState.currentScene = 0;
  }
  else if (TransitionData.discReadEnum == 3) {
    Game::GameState.currentChapter = 0;
  }
  Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
  GlobalCounter2 = GlobalCounter2 + -1;
  g_globalFlagset = g_globalFlagset & 0xfffffeff;
  TransitionData.discReadEnum = 0;
  if (TransitionData.field12_0x24 != 0) {
    UnregisterScript__(TransitionData.field12_0x24);
    g_globalFlagset = g_globalFlagset & 0xffffdfff;
    TransitionData.field12_0x24 = 0;
  }
  GlobalCounter2 = GlobalCounter2 + -1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void obj::closeObject(obj *param_1)

{
  Message local_8;
  
  local_8.header.someActor = (actor *)0x0;
  local_8.header.msgId = General_Close;
  (*param_1->vtable->onMessage)(param_1,&local_8);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Buffer<EDB2Entry>::addAvatarToSet(Buffer<EDB2Entry> *buf,avatar *av)

{
  EDB2Entry *val;
  EDB2Entry *end;
  
  if (buf != (Buffer<EDB2Entry> *)0x0) {
    val = buf->head;
    end = buf->tail;
    if (val < end) {
      while (val->avatar != av) {
        val = val + 1;
        if (end <= val) {
          return;
        }
      }
      end = (EDB2Entry *)((int)end - (uint)buf->valueSize);
      if (val < end) {
        memcpy(val,end,(uint)buf->valueSize);
      }
      buf->tail = (EDB2Entry *)((int)buf->tail - (uint)buf->valueSize);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


XBE_SECTION_HEADER * runtime::GetXbeSectionByName(PCHAR sectionName)

{
  BOOLEAN cVar1;
  XBE_SECTION_HEADER *pXVar2;
  STRING ansi_target;
  STRING ansi_cur;
  
  RtlInitAnsiString(&ansi_target,sectionName);
  pXVar2 = XBE_SECTION_HEADER_ARRAY_00010370;
  while( true ) {
    if ((XBE_SECTION_HEADER *)(XBE_SECTION_HEADER_ARRAY_00010370[0x1f].CheckSum + 0x13) < pXVar2) {
      XAPILIB::SetLastError(ERROR_NOT_FOUND);
      return (XBE_SECTION_HEADER *)0xffffffff;
    }
    RtlInitAnsiString(&ansi_cur,pXVar2->SectionName);
    cVar1 = RtlEqualString(&ansi_target,&ansi_cur,'\x01');
    if (cVar1 != '\0') break;
    pXVar2 = pXVar2 + 1;
  }
  return pXVar2;
}




ushort * runtime::AllocateOnHeap(int param_1,uint flags,uint param_3)

{
  uint *puVar1;
  byte *pbVar2;
  char cVar3;
  uint real_size;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  ushort uVar7;
  int *piVar8;
  ushort *puVar9;
  ushort *puVar10;
  int unaff_FS_OFFSET;
  bool bVar11;
  _EXCEPTION_RECORD local_194;
  ushort *local_144;
  int *local_140;
  int *local_13c;
  undefined4 *local_138;
  int *local_134;
  int local_130;
  int *local_12c;
  int local_128;
  int *local_124;
  int *local_120;
  int *local_11c;
  undefined4 *local_118;
  ushort *local_114;
  ushort *local_110;
  int local_10c;
  undefined4 *local_108;
  int local_104;
  int *local_100;
  uint local_fc;
  int *local_f8;
  int local_f4;
  int local_f0;
  ushort *local_ec;
  int *local_e8;
  undefined4 *local_e4;
  int local_e0;
  undefined4 *local_dc;
  int *local_d8;
  int *local_d4;
  int *local_d0;
  int *local_cc;
  int *local_c8;
  int *local_c4;
  undefined4 *local_c0;
  int *local_bc;
  ushort *local_b8;
  int local_b4;
  undefined4 *local_b0;
  int *local_ac;
  int *local_a8;
  uint local_a4;
  int *local_a0;
  int local_9c;
  int local_98;
  uint local_94;
  byte *local_90;
  int local_8c;
  uint local_88;
  undefined4 *local_84;
  undefined4 *local_80;
  byte *local_7c;
  undefined4 *local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  byte *local_68;
  byte *local_64;
  ushort *local_60;
  uint local_5c;
  undefined4 local_58;
  uint local_54;
  byte *local_50;
  NTSTATUS local_4c;
  int *local_48;
  uint local_44;
  ushort *local_40;
  ushort *local_3c;
  ushort *local_38;
  uint *local_34;
  int *local_30;
  uint local_2c;
  int *local_28;
  uint alloc_size;
  char local_1e;
  byte local_1d;
  undefined4 uStack_c;
  undefined4 local_8;
  
  uStack_c = 0x14e881;
  local_8c = param_1;
  local_1e = 0;
  flags = flags | *(uint *)(param_1 + 0x18);
  real_size = param_3;
  if (param_3 == 0) {
    real_size = 1;
  }
  alloc_size = real_size + 0x1f & 0xfffffff0;
  real_size = real_size + 0x1f >> 4;
  local_8 = 0;
  bVar11 = (flags & 1) == 0;
  local_2c = real_size;
  if (bVar11) {
    RtlEnterCriticalSection(*(PRTL_CRITICAL_SECTION *)(param_1 + 0x580));
  }
  local_1e = bVar11;
  if (0x7f < real_size) {
    if (*(uint *)(param_1 + 0x1c) < real_size) {
      if ((*(byte *)(param_1 + 0x14) & 2) == 0) {
        local_4c = -0x3fffffdd;
      }
      else {
        local_28 = (int *)0x0;
        alloc_size = alloc_size + 0x20;
        local_4c = NtAllocateVirtualMemory
                             (&local_28,0,&alloc_size,~(flags << 0x14) & 0x800000 | 0x1000,4);
        if (-1 < local_4c) {
          piVar8 = local_28;
          for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
            *piVar8 = 0;
            piVar8 = piVar8 + 1;
          }
          *(short *)(local_28 + 8) = (short)alloc_size - (short)param_3;
          *(undefined1 *)((int)local_28 + 0x25) = 0xb;
          local_28[6] = alloc_size;
          local_28[7] = alloc_size;
          local_130 = param_1 + 0x58;
          local_138 = *(undefined4 **)(param_1 + 0x5c);
          *local_28 = local_130;
          local_28[1] = (int)local_138;
          *local_138 = local_28;
          *(int **)(param_1 + 0x5c) = local_28;
          puVar9 = (ushort *)(local_28 + 0xc);
          local_40 = puVar9;
          goto LAB_0014ef94;
        }
      }
    }
    else {
LAB_0014ea71:
      local_30 = (int *)(param_1 + 0x180);
      local_48 = *(int **)(param_1 + 0x184);
      if ((local_30 != local_48) && (local_38 = (ushort *)(local_48 + -2), local_2c <= *local_38)) {
        for (local_48 = (int *)*local_30; local_30 != local_48; local_48 = (int *)*local_48) {
          local_38 = (ushort *)(local_48 + -2);
          if (local_2c <= *local_38) {
            iVar6 = *local_48;
            piVar8 = (int *)local_48[1];
            local_bc = piVar8;
            local_98 = iVar6;
            goto LAB_0014eae7;
          }
        }
      }
      local_38 = (ushort *)FUN_0014e01d(param_1,alloc_size);
      if (local_38 != (ushort *)0x0) {
        iVar6 = *(int *)(local_38 + 4);
        piVar8 = *(int **)(local_38 + 6);
        local_104 = iVar6;
        local_c4 = piVar8;
LAB_0014eae7:
        *piVar8 = iVar6;
        *(int **)(iVar6 + 4) = piVar8;
        goto LAB_0014eaec;
      }
      local_4c = -0x3fffffe9;
    }
    if ((flags & 4) != 0) {
      local_194.ExceptionCode = -0x3fffffe9;
      local_194.ExceptionRecord = (_EXCEPTION_RECORD *)0x0;
      local_194.NumberParameters = 1;
      local_194.ExceptionFlags = 0;
      local_194.ExceptionInformation[0] = alloc_size;
      RtlRaiseException(&local_194);
    }
    puVar9 = (ushort *)0x0;
    local_40 = puVar9;
    goto LAB_0014ef94;
  }
  local_30 = (int *)(param_1 + 0x180 + real_size * 8);
  if ((int *)*local_30 == local_30) {
    local_a4 = local_2c >> 5;
    puVar1 = (uint *)(param_1 + 0x160 + local_a4 * 4);
    local_44 = ~((1 << ((byte)local_2c & 0x1f)) - 1U) & *puVar1;
    local_34 = puVar1 + 1;
    if (local_a4 == 0) {
      if (local_44 == 0) {
        local_44 = *local_34;
        local_34 = puVar1 + 2;
        goto LAB_0014e9c5;
      }
      iVar6 = param_1 + 0x180;
    }
    else if (local_a4 == 1) {
LAB_0014e9c5:
      if (local_44 == 0) {
        local_44 = *local_34;
        local_34 = local_34 + 1;
        goto LAB_0014e9dc;
      }
      iVar6 = param_1 + 0x280;
    }
    else {
      if (local_a4 == 2) {
LAB_0014e9dc:
        if (local_44 != 0) {
          iVar6 = param_1 + 0x380;
          goto LAB_0014e9fd;
        }
        local_44 = *local_34;
        local_34 = local_34 + 1;
      }
      else if (local_a4 != 3) goto LAB_0014ea71;
      if (local_44 == 0) goto LAB_0014ea71;
      iVar6 = param_1 + 0x480;
    }
LAB_0014e9fd:
    local_30 = (int *)iVar6;
    cVar3 = FUN_001516a0();
    local_30 = (int *)(iVar6 + cVar3 * 8);
    puVar4 = (undefined4 *)local_30[1];
    local_38 = (ushort *)(puVar4 + -2);
    local_134 = (int *)*puVar4;
    local_ac = (int *)puVar4[1];
    *local_ac = (int)local_134;
    local_134[1] = (int)local_ac;
    if (local_134 == local_ac) {
      local_fc = (uint)(*local_38 >> 3);
      local_b4 = 1 << ((byte)*local_38 & 7);
      pbVar2 = (byte *)(local_fc + 0x160 + param_1);
      *pbVar2 = *pbVar2 ^ (byte)local_b4;
    }
LAB_0014eaec:
    local_1d = *(byte *)((int)local_38 + 5);
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) - (uint)*local_38;
    *(undefined1 *)((int)local_38 + 5) = 1;
    local_6c = *local_38 - local_2c;
    *local_38 = (ushort)local_2c;
    *(char *)(local_38 + 3) = (char)alloc_size - (char)param_3;
    *(undefined1 *)((int)local_38 + 7) = 0;
    local_3c = local_38;
    if (local_6c != 0) {
      if (local_6c == 1) {
        *local_38 = *local_38 + 1;
        *(char *)(local_38 + 3) = (char)local_38[3] + '\x10';
      }
      else {
        puVar9 = local_38 + local_2c * 8;
        *(byte *)((int)puVar9 + 5) = local_1d;
        puVar9[1] = (ushort)local_2c;
        *(char *)(puVar9 + 2) = (char)local_38[2];
        uVar7 = (ushort)local_6c;
        *puVar9 = uVar7;
        local_144 = puVar9;
        if ((local_1d & 0x10) == 0) {
          local_ec = puVar9 + local_6c * 8;
          if ((*(byte *)((int)local_ec + 5) & 1) != 0) {
            local_ec[1] = uVar7;
            *(byte *)((int)puVar9 + 5) = *(byte *)((int)puVar9 + 5) & 0x10;
            if (uVar7 < 0x80) {
              piVar8 = (int *)(param_1 + 0x180 + (local_6c & 0xffff) * 8);
              if ((int *)*piVar8 == piVar8) {
                local_70 = (uint)(*puVar9 >> 3);
                local_9c = 1 << ((byte)*puVar9 & 7);
                local_90 = (byte *)(local_70 + 0x160 + param_1);
                *local_90 = *local_90 | (byte)local_9c;
              }
              piVar5 = (int *)piVar8[1];
              local_11c = piVar8;
              local_a8 = piVar5;
              local_a0 = piVar8;
              goto LAB_0014eddb;
            }
            local_b0 = (undefined4 *)(param_1 + 0x180);
            for (puVar4 = (undefined4 *)*local_b0;
                (local_b0 != puVar4 && (local_b8 = (ushort *)(puVar4 + -2), *local_b8 < uVar7));
                puVar4 = (undefined4 *)*puVar4) {
            }
            piVar8 = (int *)puVar4[1];
            local_c8 = piVar8;
            local_c0 = puVar4;
            local_78 = puVar4;
LAB_0014ec14:
            puVar10 = puVar9 + 4;
            *(undefined4 **)puVar10 = puVar4;
            *(int **)(puVar9 + 6) = piVar8;
            *piVar8 = (int)puVar10;
            puVar4[1] = puVar10;
            goto LAB_0014ec21;
          }
          *(byte *)((int)puVar9 + 5) = *(byte *)((int)local_ec + 5);
          local_d0 = *(int **)(local_ec + 4);
          local_d8 = *(int **)(local_ec + 6);
          *local_d8 = (int)local_d0;
          local_d0[1] = (int)local_d8;
          if ((local_d0 == local_d8) && (uVar7 = *local_ec, uVar7 < 0x80)) {
            local_54 = (uint)(uVar7 >> 3);
            local_e0 = 1 << ((byte)uVar7 & 7);
            local_64 = (byte *)(local_54 + 0x160 + param_1);
            *local_64 = *local_64 ^ (byte)local_e0;
          }
          *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) - (uint)*local_ec;
          local_6c = local_6c + *local_ec;
          if (local_6c < 0xff01) {
            uVar7 = (ushort)local_6c;
            *puVar9 = uVar7;
            if ((*(byte *)((int)puVar9 + 5) & 0x10) == 0) {
              puVar9[local_6c * 8 + 1] = uVar7;
            }
            *(byte *)((int)puVar9 + 5) = *(byte *)((int)puVar9 + 5) & 0x10;
            if (uVar7 < 0x80) {
              piVar8 = (int *)(param_1 + 0x180 + (local_6c & 0xffff) * 8);
              if ((int *)*piVar8 == piVar8) {
                local_74 = (uint)(*puVar9 >> 3);
                local_f0 = 1 << ((byte)*puVar9 & 7);
                local_7c = (byte *)(local_74 + 0x160 + param_1);
                *local_7c = *local_7c | (byte)local_f0;
              }
              piVar5 = (int *)piVar8[1];
              local_100 = piVar5;
              local_f8 = piVar8;
              local_e8 = piVar8;
              goto LAB_0014eddb;
            }
            local_108 = (undefined4 *)(param_1 + 0x180);
            for (puVar4 = (undefined4 *)*local_108;
                (local_108 != puVar4 && (local_110 = (ushort *)(puVar4 + -2), *local_110 < uVar7));
                puVar4 = (undefined4 *)*puVar4) {
            }
            piVar8 = (int *)puVar4[1];
            local_120 = piVar8;
            local_118 = puVar4;
            local_84 = puVar4;
            goto LAB_0014ec14;
          }
          FUN_0014d9bc(param_1,puVar9,local_6c);
        }
        else {
          *(byte *)((int)puVar9 + 5) = *(byte *)((int)puVar9 + 5) & 0x10;
          if (0x7f < uVar7) {
            local_dc = (undefined4 *)(param_1 + 0x180);
            for (puVar4 = (undefined4 *)*local_dc;
                (local_dc != puVar4 && (local_114 = (ushort *)(puVar4 + -2), *local_114 < uVar7));
                puVar4 = (undefined4 *)*puVar4) {
            }
            piVar8 = (int *)puVar4[1];
            local_13c = piVar8;
            local_e4 = puVar4;
            local_80 = puVar4;
            goto LAB_0014ec14;
          }
          piVar8 = (int *)(param_1 + 0x180 + (local_6c & 0xffff) * 8);
          if ((int *)*piVar8 == piVar8) {
            local_88 = (uint)(*puVar9 >> 3);
            local_10c = 1 << ((byte)*puVar9 & 7);
            local_68 = (byte *)(local_88 + 0x160 + param_1);
            *local_68 = *local_68 | (byte)local_10c;
          }
          piVar5 = (int *)piVar8[1];
          local_12c = piVar5;
          local_d4 = piVar8;
          local_cc = piVar8;
LAB_0014eddb:
          puVar10 = puVar9 + 4;
          *(int **)puVar10 = piVar8;
          *(int **)(puVar9 + 6) = piVar5;
          *piVar5 = (int)puVar10;
          piVar8[1] = (int)puVar10;
LAB_0014ec21:
          *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + local_6c;
        }
        local_1d = 0;
        if ((*(byte *)((int)puVar9 + 5) & 0x10) != 0) {
          local_128 = *(int *)(param_1 + 0x60 + (uint)(byte)puVar9[2] * 4);
          *(ushort **)(local_128 + 0x40) = puVar9;
        }
      }
    }
    if ((local_1d & 0x10) != 0) {
      *(byte *)((int)local_3c + 5) = *(byte *)((int)local_3c + 5) | 0x10;
    }
  }
  else {
    puVar4 = (undefined4 *)local_30[1];
    local_3c = (ushort *)(puVar4 + -2);
    local_1d = *(byte *)((int)puVar4 + -3);
    local_124 = (int *)*puVar4;
    local_140 = (int *)puVar4[1];
    *local_140 = (int)local_124;
    local_124[1] = (int)local_140;
    if (local_124 == local_140) {
      local_94 = (uint)(*local_3c >> 3);
      local_f4 = 1 << ((byte)*local_3c & 7);
      local_50 = (byte *)(local_94 + 0x160 + param_1);
      *local_50 = *local_50 ^ (byte)local_f4;
    }
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) - local_2c;
    *(byte *)((int)puVar4 + -3) = local_1d & 0x10 | 1;
    *(char *)((int)puVar4 + -2) = (char)alloc_size - (char)param_3;
    *(undefined1 *)((int)puVar4 + -1) = 0;
    local_38 = local_3c;
  }
  puVar9 = local_3c + 8;
  local_40 = puVar9;
  if (local_1e != '\0') {
    RtlLeaveCriticalSection(*(PRTL_CRITICAL_SECTION *)(param_1 + 0x580));
    local_1e = '\0';
  }
  if ((flags & 8) != 0) {
    puVar10 = puVar9;
    for (real_size = param_3 >> 2; real_size != 0; real_size = real_size - 1) {
      puVar10[0] = 0;
      puVar10[1] = 0;
      puVar10 = puVar10 + 2;
    }
    for (real_size = param_3 & 3; real_size != 0; real_size = real_size - 1) {
      *(undefined1 *)puVar10 = 0;
      puVar10 = (ushort *)((int)puVar10 + 1);
    }
  }
LAB_0014ef94:
  local_8 = 0xffffffff;
  FUN_0014efda();
  if (puVar9 != (ushort *)0x0) {
    local_5c = param_3;
    local_58 = 0;
    iVar6 = *(int *)(*(int *)(unaff_FS_OFFSET + 0x20) + 0x250);
    if (iVar6 != 0) {
      local_60 = puVar9;
      (**(code **)(iVar6 + 0x14))(10,&local_60);
    }
  }
  return puVar9;
}




void InitBigBlock(BigBlock *bigBlock,NamedCallbackTable *nameTable)

{
  DisplayMatrices *pDVar1;
  uint uVar2;
  DisplayMatrices *display_type;
  
  uVar2 = Graphics::DisplayMatrixIndex;
  g_bigBlockAllocFn = (D3D_AllocContiguousMemory *)bigBlock;
  g_bigBlockFreeFn = (FreePhysical *)nameTable;
  BigBlock_004370a0.texture1 = 0;
  BigBlock_004370a0.numTextures = 0;
  BigBlock_004370a0.field68_0x64 = 0;
  BigBlock_004370a0.field60_0x46 = 0;
  BigBlock_004370a0.field64_0x4c = 0;
  BigBlock_004370a0.someVec3.x = 0.0;
  BigBlock_004370a0.someVec3.y = 0.0;
  BigBlock_004370a0.someVec3.z = 0.0;
  BigBlock_004370a0.callback = BigBlock::draw;
  BigBlock_004370a0.field358_0x1f0 = 0;
  BigBlock_004370a0.field63_0x4a = 0;
  BigBlock_004370a0.roomLightingR = '\0';
  BigBlock_004370a0.roomLightingG = '\0';
  BigBlock_004370a0.roomLightingB = '\0';
  BigBlock_004370a0.roomLightingA = 0xff;
  BigBlock_004370a0.field314_0x188 = 0;
  BigBlock_004370a0.field315_0x18c = 0xffffffff;
  BigBlock_004370a0.fogColour = 0xffffffff;
  BigBlock_004370a0.field320_0x1a8 = 0;
  BigBlock_004370a0.vsConstant.c1 = 0.0;
  BigBlock_004370a0.vsConstant.c2 = 0.0;
  BigBlock_004370a0.field364_0x1fc = 0;
  BigBlock_004370a0.field365_0x200 = 0;
  pDVar1 = &Graphics::DisplayMatrices + Graphics::DisplayMatrixIndex;
  (&Graphics::DisplayMatrices)[Graphics::DisplayMatrixIndex].worldMat.m[3][2] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[3][1] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[3][0] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[2][3] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[2][1] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[2][0] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[1][3] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[1][2] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[1][0] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[0][3] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[0][2] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[0][1] = 0.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[3][3] = 1.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[2][2] = 1.0;
  (&Graphics::DisplayMatrices)[uVar2].worldMat.m[1][1] = 1.0;
  (pDVar1->worldMat).m[0][0] = 1.0;
  GetNextNameTable(&NamedCallbackTable_00434968,&nameTable);
  BigBlock_004370a0.callbackTable = nameTable;
  NamedCallbackTable::addEntry(nameTable,"ndGroup",&ndGroup);
  NamedCallbackTable::addEntry(nameTable,"ndPixelShaderParam",&ndPixelShaderParam);
  NamedCallbackTable::addEntry(nameTable,"ndPixelShader",&ndPixelShader);
  NamedCallbackTable::addEntry(nameTable,"ndVertexShader",&ndVertexShader);
  NamedCallbackTable::addEntry(nameTable,"ndVertexBuffer",&ndVertexBuffer);
  NamedCallbackTable::addEntry(nameTable,"ndPushBuffer",&ndPushBuffer);
  NamedCallbackTable::addEntry(nameTable,"ndBGPushBuffer",&ndBGPushBuffer);
  NamedCallbackTable::addEntry(nameTable,"ndSkeleton",&ndSkeleton);
  NamedCallbackTable::addEntry(nameTable,"ndVisibility",&ndVisibility);
  NamedCallbackTable::addEntry(nameTable,"ndTransform",&ndTransform);
  NamedCallbackTable::addEntry(nameTable,"nd2D",&nd2D);
  NamedCallbackTable::addEntry(nameTable,"ndShaderParam2",&ndShaderParam2FunctionSet);
  NamedCallbackTable::addEntry(nameTable,"ndShader2",&ndShader2);
  NamedCallbackTable::addEntry(nameTable,"ndMtxArray",&ndMtxArray);
  NamedCallbackTable::addEntry(nameTable,"ndRigidSkinIdx",&ndRigidSkinIdx);
  NamedCallbackTable::addEntry(nameTable,"ndVtxDesc",&ndVertexShader);
  NamedCallbackTable::addEntry(nameTable,"ndBlendShape",&ndBlendShape);
  Assets::LoadGhoulieBinaryEntries();
  return;
}




void BigBlock::SetTextures(undefined4 param_1,undefined4 numTextures)

{
  BigBlock_004370a0.texture1 = param_1;
  BigBlock_004370a0.numTextures = numTextures;
  return;
}



// WARNING: Inlined function: GetDisplayMatrices


void updateKeyValueTableOffsets(ModelSection1 *dataStart,int dataBase)

{
  ModelKeyValue *v3;
  uint i;
  int i_ptr;
  
  dataStart->valuesStart = (ModelKeyValue *)((int)&dataStart->valuesStart->key + dataBase);
  i = 0;
  if (dataStart->numValues != 0) {
    i_ptr = 0;
    do {
      v3 = (ModelKeyValue *)((int)&dataStart->valuesStart->key + i_ptr);
      v3->key = (char *)(*(int *)((int)&dataStart->valuesStart->key + i_ptr) + dataBase);
      v3->value = (void *)((int)v3->value + dataBase);
      i = i + 1;
      i_ptr = i_ptr + 0xc;
    } while (i < dataStart->numValues);
  }
  return;
}




void GetBigBlock(BigBlock **param_1)

{
  *param_1 = &BigBlock_004370a0;
  return;
}



// WARNING: This is an inlined function


void NamedCallbackTable::addEntry(NamedCallbackTable *table,char *name,void *callback)

{
  char cVar1;
  char *pNVar2;
  
  table->names[table->count].callback = callback;
  pNVar2 = table->names[table->count].name;
  do {
    cVar1 = *name;
    name = name + 1;
    *pNVar2 = cVar1;
    pNVar2 = pNVar2 + 1;
  } while (cVar1 != '\0');
  table->count = table->count + 1;
  return;
}




void BigBlock::findNameInCallbackTable(NamedCallbackTable *param_1,ndHeader *param_2)

{
  byte bVar1;
  NamedCallbackEntry *pNVar2;
  int iVar3;
  int i;
  byte *pbVar4;
  NamedCallbackEntry *callback_ptr;
  bool bVar5;
  NamedCallbackEntry *names;
  
  i = 0;
  if ((int)param_1->count < 1) {
    return;
  }
  names = param_1->names;
  pNVar2 = names;
  pbVar4 = (byte *)param_2->subresName;
  callback_ptr = names;
LAB_001587a0:
  do {
    bVar1 = pNVar2->name[0];
    bVar5 = bVar1 < *pbVar4;
    if (bVar1 == *pbVar4) {
      if (bVar1 != 0) {
        bVar1 = pNVar2->name[1];
        bVar5 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_001587c4;
        pNVar2 = (NamedCallbackEntry *)(pNVar2->name + 2);
        pbVar4 = pbVar4 + 2;
        if (bVar1 != 0) goto LAB_001587a0;
      }
      iVar3 = 0;
    }
    else {
LAB_001587c4:
      iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
    }
    if (iVar3 == 0) {
      param_2->callbackCtx = (BigBlockCallbackCtx *)(names + i);
      param_2->nd_type = (NdType)i;
      return;
    }
    i = i + 1;
    pNVar2 = callback_ptr + 1;
    pbVar4 = (byte *)param_2->subresName;
    callback_ptr = pNVar2;
    if ((int)param_1->count <= i) {
      return;
    }
  } while( true );
}




int IndexOfKeyInTable(NamedCallbackTable *table,char *key)

{
  uint uint;
  NamedCallbackEntry *local_4;
  
  uint = IndexOfTableItem(table,key,&local_4);
  return uint;
}



void FUN_001588c0(BigBlockCallbackCtx *param_1,ndHeader *mesh,ModelSubresource *bytesBase,
                 undefined4 resBase)

{
  (*param_1->callbacks[2])(mesh,bytesBase,resBase);
  return;
}




void BigBlockCallbackCtx::getCallbackTable(BigBlockCallbackCtx *param_1,void **param_2)

{
  *param_2 = *param_1->callbacks;
  return;
}




void BigBlock::draw(int param_1,ushort param_2,ushort bigBlock44,ModelVariableData *param_4)

{
  BigBlock *local_8;
  
  Graphics::BuildScaleMatrix();
  BigBlock_004370a0.field366_0x204 = (NamedCallbackTable *)0x0;
  D3D8::D3DDevice_SetRenderState_CullMode(CULL_CW);
  D3D8::D3DDevice_SetRenderState_FogColor(BigBlock_004370a0.fogColour);
  D3D8::D3DRS_FogEnable = (uint)BigBlock_004370a0.field320_0x1a8;
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0b0010000000000000;
  DAT_00181ce4 = 0;
  BigBlock_004370a0.field59_0x44 = bigBlock44;
  Graphics::PushNdNode((void *)0x0,(ndHeader *)0x0);
  Graphics::PushNdNode
            ((void *)**(undefined4 **)
                       (*(int *)(*(int *)(*(int *)(param_1 + 8) + (uint)param_2 * 4) + 0x10) + 0x50)
             ,*(ndHeader **)(*(int *)(param_1 + 8) + (uint)param_2 * 4));
  Graphics::DrawAndConsumeNdNodes(BigBlock_004370a0.field59_0x44,param_4);
  return;
}




void SearchBinaryEntriesLL(undefined4 *param_1,void *param_2)

{
  uint uVar1;
  
  uVar1 = Game::GraphicsFlags;
  if ((char)param_2 == '\0') {
    uVar1 = 0;
  }
  ModelInstance::BinaryEntry::getPtr((int)(g_ghoulieBinaryEntries + uVar1 % 0xef),&param_2);
  if (param_2 != (void *)0x0) {
    while (*(uint *)((int)param_2 + 8) != uVar1) {
      ModelInstance::BinaryEntry::getPtr((int)param_2,&param_2);
      if (param_2 == (void *)0x0) {
        return;
      }
    }
    *param_1 = *(undefined4 *)((int)param_2 + 0xc);
  }
  return;
}




void List::Init(uint *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}




void List::PushGlobal(Node *root,Node *newSource)

{
  void *pvVar1;
  
  pvVar1 = root->next;
  while (pvVar1 != (void *)0x0) {
    root = root->next;
    pvVar1 = root->next;
  }
  root->next = newSource;
  newSource->prev = root;
  newSource->next = (void *)0x0;
  return;
}




char * runtime::GetLastError(int param_1)

{
  XAPILIB::GetLastError(param_1);
  return (char *)0x80004005;
}




void LoctextHeaderReader::init(LoctextHeader *param_1,LoctextLookupTable *param_2)

{
  LSBLValueSection *map;
  
  map = (LSBLValueSection *)(param_1->loctext->lsbl + param_1->loctext->values_ptr2);
  param_2->valuesSection = map;
  param_2->lookups = map->lookups;
  param_2->charsStart = (wchar_t *)(map->lookups + map->numValues + 1);
  param_2->isInvalid = 0;
  param_2->flags = 0;
  return;
}



// Setting this to always have the same ID completely breaks almost all visual strings in the game

uint32_t LoctextHeader::getStringFromLookupTable
                   (LoctextHeader *header,LoctextLookupTable *reader,char *stringToGet,
                   LPWSTR *outStr)

{
  byte bVar1;
  ushort loctextHash;
  wchar_t *pwVar2;
  char *char_i;
  int diff;
  int i;
  wchar_t *pbVar8;
  LoctextCollision *map;
  bool _matches;
  char *mapname_it;
  char c2;
  
  i = 27;
  _matches = true;
  mapname_it = "mapname__servantsdormitory";
  char_i = stringToGet;
  do {
    if (i == 0) break;
    i = i + -1;
    _matches = *mapname_it == *char_i;
    mapname_it = mapname_it + 1;
    char_i = char_i + 1;
  } while (_matches);
                    // If mapName == mapname__servantsdormitory
  if (_matches) {
    loctextHash = 0xc49;
  }
  else {
    loctextHash = getLoctextHash(stringToGet);
  }
  i = 0;
  if (header->numCollisions != 0) {
    map = header->collisions;
    do {
                    // //////////// Linear search through overrides /////////////////////////
      if (loctextHash == map->hash) {
        pbVar8 = (wchar_t *)map->keyName;
        char_i = stringToGet;
        do {
          c2 = *char_i;
          _matches = (byte)c2 < (byte)*pbVar8;
          if (c2 != (byte)*pbVar8) {
LAB_001629c6:
            diff = (1 - (uint)_matches) - (uint)(_matches != 0);
            goto LAB_001629cb;
          }
          if (c2 == '\0') break;
          bVar1 = char_i[1];
          _matches = bVar1 < *(byte *)((int)pbVar8 + 1);
          if (bVar1 != *(byte *)((int)pbVar8 + 1)) goto LAB_001629c6;
          char_i = char_i + 2;
          pbVar8 = pbVar8 + 1;
        } while (bVar1 != 0);
                    // //////////// End search ///////////////////////////////////
        diff = 0;
LAB_001629cb:
        if (diff == 0) {
          loctextHash = header->collisions[i].substitutedHash;
          break;
        }
      }
      i = i + 1;
      map = map + 1;
    } while (i < (int)(uint)header->numCollisions);
  }
  pwVar2 = LoctextLookupTable::getByHash(reader,(uint)loctextHash);
  *outStr = pwVar2;
  if (*pwVar2 != L'\0') {
    return (uint)loctextHash;
  }
  return 0xffffffff;
}




wchar_t * LoctextLookupTable::getByHash(LoctextLookupTable *lut,uint32_t hash)

{
  LSBLValueLookup *key;
  
  if ((lut != (LoctextLookupTable *)0x0) && (lut->isInvalid == 0)) {
    key = _bsearch((void *)hash,lut->lookups,lut->valuesSection->numValues,6,cmp_fn);
    if (key != (LSBLValueLookup *)0x0) {
      return lut->charsStart + key->charOffset;
    }
  }
  return (wchar_t *)loctext::bad_string_lookup;
}




void g_zalloc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_00168012(param_2,param_3);
  return;
}




void SetUnknownCallbacks(void *callback1,void *callback2)

{
  graphics::alloc = callback1;
  graphics::dealloc = callback2;
  return;
}




void __thiscall std::basic_string<char>::assign(basic_string<char> *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_001893d5(param_1,(int)pcVar2 - (int)(param_1 + 1));
  return;
}




int SkipStringWhitespace(int *param_1)

{
  char c;
  
  while ((c = *(char *)*param_1, c != '\0' &&
         ((((c == ' ' || (c == '\t')) || (c == '\r')) || ((c == '\n' || (c == '\x1a'))))))) {
    *param_1 = *param_1 + 1;
  }
  return 0;
}




