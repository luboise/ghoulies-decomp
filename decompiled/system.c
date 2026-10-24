/* system.c - Entry point, XBE init, main game loop, state machine */
#include "system.h"

void CodeCave1(void)

{
  return;
}




void FUN_000320f0(AS58Entry *entry,Model *instance)

{
  uint uVar1;
  ModelFooterEntry *pMVar2;
  uint uVar3;
  uint flags;
  byte index;
  ModelFooterEntry *pMVar4;
  uint i;
  uint num_entries;
  
  uVar1 = entry->field185_0xc0;
                    // 16 times
  i = 0;
  do {
    num_entries = instance->descriptor->numFooterEntries;
    uVar3 = 0;
    if (num_entries != 0) {
      pMVar2 = instance->descriptor->footerEntries;
      pMVar4 = pMVar2;
      do {
        if (pMVar4->subresourceType == ModelFlags) {
          flags = pMVar2[uVar3].offset;
          goto LAB_0003211f;
        }
        uVar3 = uVar3 + 1;
        pMVar4 = pMVar4 + 1;
      } while (uVar3 < num_entries);
    }
    flags = 0;
LAB_0003211f:
    index = (byte)i;
                    // if bit 0 is enabled
    if ((flags & 1 << (index & 0x1f)) != 0) {
      ModelInstance::searchForValueWithFlags
                ((byte)(uVar1 >> (index * '\x02' & 0x1f)) & 3,instance,index);
    }
    i = i + 1;
    if (0xf < i) {
      return;
    }
  } while( true );
}



AnimEventMapping *

void main(void)

{
  uint uVar1;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int unaff_FS_OFFSET;
  LPMEMORYSTATUS memoryStatus;
  uint local_14;
  int iVar2;
  
  XAPILIB::QueryPerformanceCounter((LARGE_INTEGER *)&g_PERFORMANCE_COUNTER);
  XAPILIB::QueryPerformanceFrequency((LARGE_INTEGER *)&g_PERFORMANCE_FREQUENCY);
  XAPILIB::GlobalMemoryStatus((LPMEMORYSTATUS)&memoryStatus);
  UINT_0054f7bc = (-(uint)(0x4000000 < local_14) & 0x4000000) + 0x4000000;
  GetLaunchData();
  InitialiseEverything();
  FUN_00032630();
  g_AudioCallbacks = Audio::Audio__RunCallbacks;
  INT_005462d4 = 5;
  uVar1 = QueryFile("d:\\movie\\0de65e94");
  iVar2 = extraout_ECX;
  if (uVar1 == 0xffffffff) {
    XAPILIB::GetLastError(unaff_FS_OFFSET);
    iVar2 = extraout_ECX_00;
  }
  do {
    GameLoop(iVar2);
    iVar2 = extraout_ECX_01;
  } while( true );
}




void GetLaunchData(void)

{
  DWORD DVar1;
  int iVar2;
  char *pcVar3;
  undefined4 *puVar4;
  
  DVar1 = XAPILIB::XGetLaunchInfo(&g_LAUNCH_TYPE,&g_LAUNCH_DATA);
                    // If an error occurred
  DAT_0054e9a4 = (uint)(DVar1 == 0);
  if (DVar1 != 0) {
switchD_00032495_caseD_1:
    iVar2 = 7;
    _DAT_0054f5a8 = 0;
    _DAT_0054f5ac = 0;
    _DAT_0054f7b8 = 0;
    builtin_strncpy(g_DISC_DRIVE_PREFIX,"D:\\",4);
    pcVar3 = "D:\\GrabbedByTheGhoulies.xbe";
    puVar4 = &DAT_0054f6b4;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      puVar4 = puVar4 + 1;
    }
    return;
  }
  switch(g_LAUNCH_TYPE) {
  case 0:
    break;
  default:
    goto switchD_00032495_caseD_1;
  case 2:
    break;
  case 3:
  case 4:
    iVar2 = 7;
    _DAT_0054f5a8 = 0;
    _DAT_0054f5ac = 0;
    _DAT_0054f7b8 = 0;
    builtin_strncpy(g_DISC_DRIVE_PREFIX,"D:\\",4);
    DAT_0054e9a4 = 1;
    pcVar3 = "D:\\GrabbedByTheGhoulies.xbe";
    puVar4 = &DAT_0054f6b4;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      puVar4 = puVar4 + 1;
    }
    return;
  }
  DAT_0054f5a8 = g_LAUNCH_DATA.Data[0];
  DAT_0054f5a8_1._0_1_ = g_LAUNCH_DATA.Data[1];
  DAT_0054f5a8_1._1_1_ = g_LAUNCH_DATA.Data[2];
  DAT_0054f5a8_1._2_1_ = g_LAUNCH_DATA.Data[3];
  iVar2 = 7;
  _DAT_0054f5ac = 0;
  _DAT_0054f7b8 = 0;
  builtin_strncpy(g_DISC_DRIVE_PREFIX,"D:\\",4);
  DAT_0054e9a4 = 1;
  pcVar3 = "D:\\GrabbedByTheGhoulies.xbe";
  puVar4 = &DAT_0054f6b4;
  for (; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    puVar4 = puVar4 + 1;
  }
  return;
}




void ReturnToDashboard_(LPCSTR path,PLAUNCH_DATA data)

{
  game::prevent_exiting = (bool *)0x1;
  FUN_0015b770();
  while (runtime::CacheContext.field265_0x13c != 0) {
    FUN_000ea630();
  }
  FUN_000e8f80();
  FUN_000e9dc0();
  XAPILIB::XLaunchNewImageA(path,data);
  runtime::ExitGame(0x6e);
  return;
}




void BigSetupFunction_(void)

{
  int hz;
  AudioPlayingContext *pAVar1;
  StatsheetResource *ghoulies_statsheet;
  StatsheetResource *generalsettings_asset;
  
  SetRumblesAndMaybeOthers();
  ULONG_005096bc = 0;
  if ((runtime::Config::IsPal == 0) || (hz = 50, runtime::Config::Use60Hz != 0)) {
    hz = 60;
  }
  runtime::DeltaTime = 1.0 / (float)hz;
  runtime::DeltaTicks = (int)(runtime::DeltaTime * 300.0);
  runtime::TotalTicks = runtime::DeltaTime * 300.0 - (float)runtime::DeltaTicks;
  Input::Initialise();
  INT_004e5e08 = 4;
  INT_004e5e0c = 6;
  INT_004e5e14 = -1;
  INT_004e5e18 = -0x1000000;
  FLOAT_005044b8 = 1.0;
  FLOAT_005044bc = 1.0;
  FLOAT_005044c0 = 1.0;
  FLOAT_005044c4 = 1.0;
  FUN_00061c40();
  if ((g_float1 != 1.0) || (g_float2 != 1.0)) {
    g_float1 = 1.0;
    g_float2 = 1.0;
    FUN_00061c40();
  }
  g_TopLevelExceptionFilter = XAPILIB::SetUnhandledExceptionFilter(UnhandledExceptionFilter);
  PTR_004e1c94 = malloc_(0x400);
  _DAT_004e1c98 = PTR_004e1c94 + 1;
  _DAT_004e1ca0 = 0;
  _DAT_004e1c9c = PTR_004e1c94;
  FUN_000ff040();
  g_resourceReaders = malloc_(0x310);
  g_resourceReaders->head = g_resourceReaders->data;
  g_resourceReaders->tail = g_resourceReaders->data;
  g_resourceReaders->valueSize = 0x18;
  g_resourceReaders->capacity = 0x20;
  g_resourceReaders->end = g_resourceReaders + 1;
  Assets::InitGlobalBuffersAndLoaderCallbackTables();
  Assets::InitAssetGroups();
  SetupSomeAssetLoader();
  FUN_00035010();
  FUN_001243b0();
  Audio::Initialise();
  Assets::GetResourceBytes("aid_misc_ghoulies_audio_generalsettings",&ghoulies_statsheet);
  generalsettings_asset = ghoulies_statsheet;
  if (ghoulies_statsheet == (StatsheetResource *)0x0) {
    runtime::ExitGame(2);
  }
  Audio::MiscGeneralSettings = (Asset *)generalsettings_asset;
  SetupWeirdStruct1Array();
  pAVar1 = Audio::PlayingContexts;
  do {
    pAVar1->playFlags = 0;
    pAVar1 = pAVar1 + 1;
  } while ((int)pAVar1 < 0x4dffa0);
  Audio::ClearAudioContext();
  UpdateRumblesOrAudio_();
  Graphics::SetupPipelineCallbacks();
  g_currentAspectRatioIndex = (uint)(g_DXContext.widescreen != false);
  Graphics::UpdateCameraValues();
  runtime::ClearAllCams();
  runtime::ClearSomeType3AssetNames();
  runtime::Player1PortBit = 1;
  runtime::Player2PortBit = 2;
  runtime::Player3PortBit = 4;
  runtime::Player4PortBit = 8;
  UINT_0050e0f0 = 0;
  UINT_0050e0f4 = 0;
  Input::InputHandlers = malloc_(0x150);
  Input::InputHandlers->head = Input::InputHandlers->values;
  Input::InputHandlers->tail = Input::InputHandlers->values;
  Input::InputHandlers->valueSize = 0x50;
  Input::InputHandlers->capacity = 4;
                    // This is correct ignore this
  Input::InputHandlers->end = (Script2TypeNode *)(Input::InputHandlers + 1);
  Input::NumInputHandlers = 0;
  runtime::InitialiseFontResources();
  Graphics::Create256Texture();
  Graphics::CompileVertexShaders();
  Graphics::CompilePixelShaders();
  g_someBuffer = malloc_(0x70);
  g_someBuffer->head = g_someBuffer->values;
  g_someBuffer->tail = g_someBuffer->values;
  g_someBuffer->valueSize = 0x18;
  g_someBuffer->capacity = 4;
  g_someBuffer->end = (OcclusionValue *)(g_someBuffer + 1);
  UINT_0050dd8c = 3;
  PTR_00506c70 = malloc_(13);
  if (PTR_00506c70 == (astruct_13 *)0x0) {
    PTR_00506c70 = (astruct_13 *)0x0;
  }
  else {
    PTR_00506c70->valueSize = 4;
    PTR_00506c70->capacity = 1;
    PTR_00506c70->head = (undefined4 *)&PTR_00506c70->field3_0xc;
    PTR_00506c70->field3_0xc = '\0';
  }
  PTR_00506c6c = malloc_(0x14);
  if (PTR_00506c6c == (astruct_14 *)0x0) {
    PTR_00506c6c = (astruct_14 *)0x0;
  }
  else {
    PTR_00506c6c->field0_0x0 = 0x3e;
    PTR_00506c6c->field1_0x4 = 8;
    PTR_00506c6c->field2_0x8 = (undefined *)&PTR_00506c6c->field3_0xc;
    PTR_00506c6c->field3_0xc = 0;
    PTR_00506c6c->field4_0x10 = 0;
  }
  FUN_000f2b60();
  game::oldNextPlaycamScriptWide[0] = L'\0';
  PTR_00506c54 = malloc_(25);
  if (PTR_00506c54 == (astruct_16 *)0x0) {
    PTR_00506c54 = (astruct_16 *)0x0;
  }
  else {
    PTR_00506c54->field0_0x0 = 100;
    PTR_00506c54->copySize = 0xd;
    PTR_00506c54->field2_0x8 = &PTR_00506c54->field3_0xc;
    PTR_00506c54->field3_0xc = 0;
    PTR_00506c54->field4_0x10 = 0;
    PTR_00506c54->field5_0x14 = 0;
    PTR_00506c54->field6_0x18 = 0;
  }
  INT_004e17c8 = 0;
  challengeId_004e17cc = ~Attacks;
  PTR_004e17d8 = (Buffer<> *)0x0;
  INT_004e19a0 = 0;
  DAT_004e19a4 = 0;
  DAT_004e19b0 = 0;
  g_someWString[0x40] = L'\0';
  g_someWString[0x41] = L'\0';
  g_someWString[0] = L'\0';
  BOOL_004e17ec = false;
  DAT_004e1740 = 0;
  FLOAT_004e1744 = 0.0;
  DAT_004e1748 = 0;
  DAT_00506c5c = 0;
  if (DAT_00506c58 != 0) {
    DAT_00506c58 = 0;
    FUN_0012fdc0();
    DAT_00506c60 = -1.0;
    DAT_00506c68 = 0;
  }
  FUN_0011ea50();
  Assets::GetResourceBytes("aid_misc_ghoulies_statsheet_actors",&ghoulies_statsheet);
  if (ghoulies_statsheet == (StatsheetResource *)0x0) {
    runtime::ExitGame(2);
  }
  Assets::GetStatsheetTag((char *)ghoulies_statsheet);
  Assets::GhouliesStatsheet = &ghoulies_statsheet->entries;
  Assets::GhouliesStatsheetTagIndex = Assets::ValidateStatsheet(&ghoulies_statsheet->entries);
  LoadBackgroundPartTables();
  LoadWeaponStatTables();
  setNextPlaycamScriptAID(1,Assets::SceneOrderAHandle.sceneOrder);
  __controlfp(_PC_24,0x30000);
  return;
}




void InitialiseEverything(void)

{
  uint unaff_EBP;
  
  InitialiseLocale();
  runtime::CreateHeapTables(unaff_EBP);
  runtime::CurrentHeapToAllocateFrom = 3;
  runtime::ExitCode = 0;
  game::prevent_exiting = (bool *)0x0;
  Graphics::InitialiseDirectX();
  InitialiseCache();
  g_GHOULIES = "ghoulies";
  BigSetupFunction_();
  DAT_004dea3c = g_DXContext.field28_0x48;
  DAT_004dea2c = 0;
  Input::NoControllerHandler = 0;
  _DAT_004dea20 = 0;
  GlobalCounter2 = 0;
  DAT_004dea48 = 0;
  DAT_004dd900 = 0;
  DAT_004dea40 = g_DXContext.__0;
  DAT_004dea30 = 0xffffffff;
  Input::ResolvingInputs = 4;
  return;
}




void GameLoop(int param_1)

{
  int extraout_ECX;
  GameSaveSet *i2;
  AllocatedMovie *i;
  
  runtime::UpdateClocks();
  Events::Update();
  Graphics::CurrentCameraStruct = Graphics::CameraStructs;
  Input::ProcessRawInputs();
  Input::UpdateRumbles();
  Audio::Update(runtime::DeltaTime);
  Audio::UpdateListener();
  Audio::UpdatePlayerContexts();
  Audio::ResolveFightingAudioChannels();
  NothingApparently2_();
  runtime::StreamFiles();
  if (((runtime::CacheContext.field10_0x34 == 0) && (runtime::CacheContext.utilityDriveError == 0))
     && (runtime::CacheContext.nextCache != (astruct_20 *)0x0)) {
    CloseUnneededOpenFiles_(extraout_ECX,(z_stream *)runtime::CacheContext.nextCache);
  }
  Audio::ProcessSamples();
  SizeOf_g_int_12__array();
  if ((DoDat0x0050e0b8 == 0) && (i = g_MovieListHead, g_PlayingMovies__ == 0)) {
    for (; i != (AllocatedMovie *)0x0; i = (AllocatedMovie *)i->nextMovie) {
      AllocatedMovie::MustRead__(i);
    }
  }
  FreeOldTextures_();
  i2 = runtime::Saves;
                    // Maybe update time played on save file??
  if (0.0 < (float)runtime::Saves->timer) {
    runtime::Saves->timer = (float)runtime::Saves->timer - runtime::DeltaTime;
  }
  if ((i2->save3 != (Buffer<SaveEntry> *)0x0) && ((float)i2->timer <= 0.0)) {
    runtime::SomethingSaveRelated();
  }
                    // If a controller is connected
  if (-1 < (char)g_globalFlagset) {
                    // Likely to be "If we need to update physics or anything on a fixed tick"
    if ((g_globalFlagset & DoRenderLoop?) == 0) {
                    // Update events????
      runtime::UpdateGameState(&Game::GameState);
      runtime::UpdateNewEntities(&Game::GameState);
                    // Draw the UI and handle blocks related to the UI
      HandleUIUpdate();
      PeriodicUpdateWithPi_();
                    // No tangible difference?
                    // 
      UpdateAttacks_();
    }
    FUN_00033480();
    UpdateCutscenes_();
                    // Update video
    Graphics::Update();
    return;
  }
  FUN_0011d410();
  FUN_00033480();
  Graphics::Update();
  return;
}




void addEntryToLinkedList(int entries,char *entryName)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  
  pcVar5 = entryName;
  pcVar3 = entryName;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  iVar4 = AddSoundbankLine(&entries,pcVar3 + (9 - (int)(entryName + 1)));
  iVar6 = (iVar4 + 8) - (int)pcVar5;
  do {
    cVar1 = *pcVar5;
    pcVar5[iVar6] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(iVar4 + 4) = 0;
  iVar6 = *(int *)(entries + 4);
  if (iVar6 == 0) {
    *(int *)(entries + 4) = iVar4;
    return;
  }
  iVar2 = *(int *)(iVar6 + 4);
  while (iVar2 != 0) {
    iVar6 = *(int *)(iVar6 + 4);
    iVar2 = *(int *)(iVar6 + 4);
  }
  *(int *)(iVar6 + 4) = iVar4;
  return;
}



SoundbankEntryNode *

void FUN_0003a830(AnimEventEntry *param_1,avatar *param_2)

{
  int iVar1;
  
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  if ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0 <= param_1->footstepChance) {
    iVar1 = param_1->field7_0x10;
    if (*(char *)&param_1->field8_0x14 != '\0') {
      FUN_0012a260((uint)AnimEventPlayCueTypes[iVar1],(actor *)param_2,(short)iVar1,(vec3 *)0x0,
                   (vec3 *)0x0,1.0,(astruct_25 *)&param_2->model0x9s[iVar1 + -1].field_0xb0,
                   (char *)&param_1->field8_0x14);
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint * FUN_00050880(Entry0xd *param_1,ModelDescriptor *param_2)

{
  Entry0xdType EVar1;
  uint *puVar2;
  short drawType;
  vec3 splitted [4];
  
  EVar1 = param_1->entryType;
  if ((EVar1 == 2) || (EVar1 == 8)) {
    Graphics::SplitQuadForRendering(param_1->positions,splitted);
    drawType = 5;
  }
  else {
    if (EVar1 != 1) {
      return (uint *)0;
    }
    Graphics::SplitQuadForRendering(param_1->positions,splitted);
    drawType = 0x13;
  }
  puVar2 = Subresource0xd::doSomething
                     (param_2->runtimeCtx->subresource0xd,splitted,0x14,0x10,0x25c,param_1,drawType,
                      0,0xc0200000,0);
  return puVar2;
}




undefined4 FUN_000509e0(int param_1,Entry0xd *param_2,int *param_3)

{
  uint uVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  uint *puVar5;
  char *pcVar6;
  uint uVar7;
  char *pcVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  vec3 local_60;
  float local_54;
  float local_50;
  float local_4c;
  float local_3c;
  float local_38;
  float local_34;
  vec3 local_30;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  Graphics::SplitQuadForRendering(param_2->positions,&local_60);
  local_3c = local_3c - local_60.x;
  local_38 = local_38 - local_60.y;
  local_34 = local_34 - local_60.z;
  fVar12 = (local_54 - local_60.x) * 0.16666667;
  fVar13 = (local_50 - local_60.y) * 0.16666667;
  fVar14 = (local_4c - local_60.z) * 0.16666667;
  fVar9 = (local_54 - local_60.x) * 0.05;
  fVar10 = (local_50 - local_60.y) * 0.05;
  fVar11 = (local_4c - local_60.z) * 0.05;
  uVar7 = 0;
  do {
    fVar3 = (float)(int)uVar7;
    if ((int)uVar7 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    uVar1 = uVar7 + 1;
    fVar4 = (float)(int)uVar1;
    if ((int)uVar1 < 0) {
      fVar4 = fVar4 + 4.2949673e+09;
    }
    local_30.x = fVar12 * fVar3 + local_60.x + fVar9;
    local_30.y = fVar13 * fVar3 + local_60.y + fVar10;
    local_30.z = fVar14 * fVar3 + local_60.z + fVar11;
    local_24 = (fVar12 * fVar4 + local_60.x) - fVar9;
    local_20 = (fVar13 * fVar4 + local_60.y) - fVar10;
    local_18 = local_24 + local_3c;
    local_1c = (fVar14 * fVar4 + local_60.z) - fVar11;
    local_14 = local_20 + local_38;
    local_10 = local_1c + local_34;
    local_c = local_30.x + local_3c;
    local_8 = local_30.y + local_38;
    local_4 = local_30.z + local_34;
    puVar5 = Subresource0xd::doSomething
                       (*(Subresource0xd **)(*(int *)(param_1 + 0x10) + 0xc),&local_30,2,0x10,0x114,
                        param_2,1,0,0xc1280000,0);
    *(uint **)(*param_3 + uVar7 * 4) = puVar5;
    *(undefined1 *)(*(int *)(*param_3 + uVar7 * 4) + 0x1ea) = 1;
    pcVar6 = "XACT_SOUNDBANK_GPROPS_PLASTICCURTAINS";
    pcVar8 = (char *)(*(int *)(*param_3 + uVar7 * 4) + 0x15a);
    do {
      cVar2 = *pcVar6;
      *pcVar8 = cVar2;
      pcVar8 = pcVar8 + 1;
      pcVar6 = pcVar6 + 1;
    } while (cVar2 != '\0');
    uVar7 = uVar1;
  } while (uVar1 < 6);
  return 6;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


BOOL FUN_00052f80(byte param_1,ModelFooterEntry *param_2)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = 0;
  if (param_2->offset != 0) {
    piVar2 = (int *)param_2->subresourceType;
    do {
      if (*piVar2 == 1) {
        uVar1 = ((int *)param_2->subresourceType)[uVar1 * 2 + 1];
        goto LAB_00052f9f;
      }
      uVar1 = uVar1 + 1;
      piVar2 = piVar2 + 2;
    } while (uVar1 < param_2->offset);
  }
  uVar1 = 0;
LAB_00052f9f:
  return (uint)((1 << (param_1 & 0x1f) & uVar1) != 0);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


LONG UnhandledExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo)

{
  DWORD *pDVar1;
  DWORD *pDVar2;
  LAUNCH_DATA *launch_data;
  LONG LVar3;
  undefined4 *puVar4;
  int unaff_FS_OFFSET;
  
  XAPILIB::GetLastError(unaff_FS_OFFSET);
  pDVar2 = &DAT_002fe930;
  do {
    if (*pDVar2 == ExceptionInfo->ExceptionRecord->ExceptionCode) break;
    pDVar1 = pDVar2 + 3;
    pDVar2 = pDVar2 + 2;
  } while (*pDVar1 != 0);
  FUN_000e9d80();
  if ((DAT_0054e9a4 == 0) || (g_LAUNCH_TYPE != 0)) {
    launch_data = (LAUNCH_DATA *)0x0;
    puVar4 = &DAT_0054f6b4;
  }
  else {
    launch_data = &g_LAUNCH_DATA;
    puVar4 = (undefined4 *)0x54ddac;
  }
  ReturnToDashboard_(puVar4,launch_data);
  if (DAT_004e5ce4 == 0) {
    DAT_004e5ce4 = 1;
    _DAT_004e5ce0 = 0;
    g_PlayingMovies__ = 1;
    LVar3 = (*g_TopLevelExceptionFilter)(ExceptionInfo);
    return LVar3;
  }
  LVar3 = FUN_00056cb0();
  return LVar3;
}



void __fastcall

void SecDialogVars(void)

{
  _DAT_004e61c8 = 0;
  DAT_004ee1e0 = 0;
  NumDialogs = 0;
  NumDialogsAgain__ = 0;
  Game::DialogState = NotInDialog;
  PlayDialogAudio = 1;
  DAT_004ee290 = 1;
  DAT_004ee298 = 0.1;
  _DAT_004ee29c = 0;
  _DAT_004ee2a0 = 0;
  DAT_004ee2a8 = 0;
  InMapView = 0;
  DAT_004ee2b4 = 0;
  FUN_00056df0();
  FUN_00057400();
  DAT_004e60c4 = 0;
  DAT_004e60c0 = 0x36;
  return;
}




void PeriodicUpdateWithPi_(void)

{
  float fVar1;
  BOOL BVar2;
  float10 extraout_ST0;
  float fVar3;
  float fVar4;
  float max_of_pi;
  
  fVar3 = IdkBigStruct_00504450.field0_0x0;
  fVar4 = 0.0;
  if (IdkBigStruct_00504450.field6_0x24 != 0) {
    if (0.0 <= IdkBigStruct_00504450.g_float1) {
      if (runtime::dx_timer <= 0.0) {
        fVar3 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar3 = 0.0;
      }
      if ((0.0 < IdkBigStruct_00504450.g_float1) &&
         (IdkBigStruct_00504450.g_float1 = IdkBigStruct_00504450.g_float1 - fVar3,
         IdkBigStruct_00504450.g_float1 <= 0.0)) {
        IdkBigStruct_00504450.g_float1 = 0.0;
        FUN_00060bc0();
        goto LAB_00060f56;
      }
      if (IdkBigStruct_00504450.field4_0x1c == 0.0) {
        max_of_pi = 3.1415927;
      }
      else {
        max_of_pi = ((IdkBigStruct_00504450.g_float1 - IdkBigStruct_00504450.field4_0x1c) /
                    (0.0 - IdkBigStruct_00504450.field4_0x1c)) * 3.1415927;
        if (max_of_pi <= 3.1415927) {
          if (max_of_pi < 0.0) {
            max_of_pi = 0.0;
          }
        }
        else {
          max_of_pi = 3.1415927;
        }
      }
      sin(max_of_pi);
      fVar3 = IdkBigStruct_00504450.field2_0x8;
      if (IdkBigStruct_00504450.field4_0x1c * 0.5 <= IdkBigStruct_00504450.g_float1) {
        fVar3 = IdkBigStruct_00504450.field0_0x0;
      }
      fVar3 = (float)FUN_00101730(IdkBigStruct_00504450.field1_0x4,fVar3,(float)extraout_ST0);
    }
    else {
      IdkBigStruct_00504450.field0_0x0 = -1.7014118e+38;
      IdkBigStruct_00504450.field1_0x4 = -1.7014118e+38;
      IdkBigStruct_00504450.field2_0x8 = -1.7014118e+38;
      IdkBigStruct_00504450.field4_0x1c = 0.0;
      IdkBigStruct_00504450.g_float1 = 0.0;
      IdkBigStruct_00504450.field6_0x24 = 0;
    }
    IdkBigStruct_00504450.field3_0xc.z = (float)((uint)fVar3 >> 0x10 & 0xff) * 0.003921569;
    IdkBigStruct_00504450.field3_0xc.y = (float)((uint)fVar3 >> 8 & 0xff) * 0.003921569;
    IdkBigStruct_00504450.field3_0xc.x = (float)((uint)fVar3 & 0xff) * 0.003921569;
    fVar4 = 0.0;
    IdkBigStruct_00504450.field3_0xc.w = (float)((uint)fVar3 >> 0x18) * 0.003921569;
    IdkBigStruct_00504450.field7_0x28 = 1;
  }
LAB_00060f56:
  fVar1 = IdkBigStruct_00504450.field13_0x40;
  fVar3 = IdkBigStruct_00504450.field10_0x34;
  if (IdkBigStruct_00504450.field17_0x50 == 0) {
    return;
  }
  if (IdkBigStruct_00504450.field9_0x30 < fVar4) {
    IdkBigStruct_00504450.field18_0x54 = 1;
    IdkBigStruct_00504450.field10_0x34 = fVar4;
    IdkBigStruct_00504450.field11_0x38 = fVar4;
    IdkBigStruct_00504450.field13_0x40 = fVar4;
    IdkBigStruct_00504450.field14_0x44 = fVar4;
    IdkBigStruct_00504450.field17_0x50 = 0;
    IdkBigStruct_00504450.field16_0x4c = 0;
    IdkBigStruct_00504450.field8_0x2c = fVar4;
    IdkBigStruct_00504450.field9_0x30 = fVar4;
    IdkBigStruct_00504450.field12_0x3c = fVar3;
    IdkBigStruct_00504450.field15_0x48 = fVar1;
    return;
  }
  if (TransitionData.discReadEnum != 3) {
    if ((IdkBigStruct_00504450.field9_0x30 != fVar4) &&
       (BVar2 = Timer::reduce((float *)&IdkBigStruct_00504450.field9_0x30), BVar2 == 0)) {
      IdkBigStruct_00504450.field18_0x54 = 1;
      goto LAB_0006103a;
    }
    if (IdkBigStruct_00504450.field16_0x4c == 0) {
      FUN_00060c20();
      if (IdkBigStruct_00504450.field18_0x54 == 0) {
        return;
      }
      goto LAB_0006103a;
    }
  }
  IdkBigStruct_00504450.field18_0x54 = 1;
LAB_0006103a:
  IdkBigStruct_00504450.field12_0x3c = IdkBigStruct_00504450.field11_0x38;
  if (fVar4 != IdkBigStruct_00504450.field8_0x2c) {
    IdkBigStruct_00504450.field12_0x3c =
         ((IdkBigStruct_00504450.field9_0x30 - IdkBigStruct_00504450.field8_0x2c) /
         (fVar4 - IdkBigStruct_00504450.field8_0x2c)) *
         (IdkBigStruct_00504450.field11_0x38 - IdkBigStruct_00504450.field10_0x34) +
         IdkBigStruct_00504450.field10_0x34;
    if (IdkBigStruct_00504450.field11_0x38 <= IdkBigStruct_00504450.field10_0x34) {
      if (IdkBigStruct_00504450.field11_0x38 <= IdkBigStruct_00504450.field12_0x3c) {
        if (IdkBigStruct_00504450.field10_0x34 < IdkBigStruct_00504450.field12_0x3c) {
          IdkBigStruct_00504450.field12_0x3c = IdkBigStruct_00504450.field10_0x34;
        }
      }
      else {
        IdkBigStruct_00504450.field12_0x3c = IdkBigStruct_00504450.field11_0x38;
      }
    }
    else if (IdkBigStruct_00504450.field12_0x3c <= IdkBigStruct_00504450.field11_0x38) {
      if (IdkBigStruct_00504450.field12_0x3c < IdkBigStruct_00504450.field10_0x34) {
        IdkBigStruct_00504450.field12_0x3c = IdkBigStruct_00504450.field10_0x34;
      }
    }
    else {
      IdkBigStruct_00504450.field12_0x3c = IdkBigStruct_00504450.field11_0x38;
    }
  }
  if (fVar4 == IdkBigStruct_00504450.field8_0x2c) {
    IdkBigStruct_00504450.field15_0x48 = IdkBigStruct_00504450.field14_0x44;
    return;
  }
  IdkBigStruct_00504450.field15_0x48 =
       ((IdkBigStruct_00504450.field9_0x30 - IdkBigStruct_00504450.field8_0x2c) /
       (fVar4 - IdkBigStruct_00504450.field8_0x2c)) *
       (IdkBigStruct_00504450.field14_0x44 - IdkBigStruct_00504450.field13_0x40) +
       IdkBigStruct_00504450.field13_0x40;
  if (IdkBigStruct_00504450.field13_0x40 < IdkBigStruct_00504450.field14_0x44) {
    if (IdkBigStruct_00504450.field15_0x48 <= IdkBigStruct_00504450.field14_0x44) {
      if (IdkBigStruct_00504450.field13_0x40 <= IdkBigStruct_00504450.field15_0x48) {
        return;
      }
      IdkBigStruct_00504450.field15_0x48 = IdkBigStruct_00504450.field13_0x40;
      return;
    }
  }
  else if (IdkBigStruct_00504450.field14_0x44 <= IdkBigStruct_00504450.field15_0x48) {
    if (IdkBigStruct_00504450.field13_0x40 < IdkBigStruct_00504450.field15_0x48) {
      IdkBigStruct_00504450.field15_0x48 = IdkBigStruct_00504450.field13_0x40;
      return;
    }
    return;
  }
  IdkBigStruct_00504450.field15_0x48 = IdkBigStruct_00504450.field14_0x44;
  return;
}




BOOL createGameselectString(char *category,char *entry,LPWSTR param_3,LoctextDescriptor *param_4)

{
  uint32_t uVar1;
  LPCWSTR local_204;
  char local_200 [256];
  char local_100 [256];
  
  game::current_loctext_lookup_table = malloc_(20);
  LoctextHeaderReader::init((LoctextHeader *)param_4,game::current_loctext_lookup_table);
  copy__a_zA_Z0_9__(local_200,entry);
  _sprintf(local_100,"%s__%s",category,local_200);
  uVar1 = LoctextHeader::getStringFromLookupTable
                    ((LoctextHeader *)param_4,game::current_loctext_lookup_table,local_100,
                     &local_204);
  if (uVar1 == 0xffffffff) {
    *param_3 = L'\0';
    free(game::current_loctext_lookup_table);
    return 0;
  }
  XAPILIB::lstrcpyW(param_3,local_204);
  free(game::current_loctext_lookup_table);
  return 1;
}




void InitialiseLocale(void)

{
  undefined4 uVar1;
  int i;
  uint success;
  char *pcVar2;
  int unaff_FS_OFFSET;
  char disc_drive_prefix [256];
  char loctext [256];
  char c;
  
  uVar1 = XAPILIB::XGetLanguage();
  switch(uVar1) {
  case 1:
    i = 0;
    do {
      c = "english"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    goto LAB_000ff301;
  case 2:
    i = 0;
    do {
      c = "japanese"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = JAPANESE;
    break;
  case 3:
    i = 0;
    do {
      c = "german"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = GERMAN;
    break;
  case 4:
    i = 0;
    do {
      c = "french"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = FRENCH;
    break;
  case 5:
    i = 0;
    do {
      c = "spanish"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = SPANISH;
    break;
  case 6:
    i = 0;
    do {
      c = "italian"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = ITALIAN;
    break;
  case 7:
    i = 0;
    do {
      c = "korean"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = KOREAN;
    break;
  case 8:
    i = 0;
    do {
      c = "chinese"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = CHINESE;
    break;
  default:
    i = 0;
    do {
      c = "english"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
LAB_000ff301:
    runtime::LanguageID = ENGLISH;
  }
  i = 0;
  do {
    c = g_DISC_DRIVE_PREFIX[i];
    disc_drive_prefix[i] = c;
    i = i + 1;
  } while (c != '\0');
  _sprintf(loctext,"%sloctext\\%s",disc_drive_prefix,runtime::LanguageStr);
                    // loctext = D:\\loctext\\english
  success = QueryFile(loctext);
  if (success == 0xffffffff) {
    pcVar2 = XAPILIB::GetLastError(unaff_FS_OFFSET);
  }
  else {
    pcVar2 = (char *)(-(uint)((success & 0x10) != 0) & 0x10b);
  }
  if (pcVar2 != (char *)0x10b) {
    i = 0;
    do {
      c = "english"[i];
      runtime::LanguageStr[i] = c;
      i = i + 1;
    } while (c != '\0');
    runtime::LanguageID = ENGLISH;
  }
  return;
}




undefined4 FUN_0010da80(SaveEntryValue *param_1)

{
  Buffer<SaveEntry> *pBVar1;
  LPCWSTR in_EAX;
  int iVar2;
  SaveEntry *pSVar3;
  
  pBVar1 = runtime::Saves->save1;
  pSVar3 = pBVar1->head;
  if (pSVar3 < pBVar1->tail) {
    do {
      iVar2 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar3->entries->field1_0x2,in_EAX);
      if (iVar2 == 0) {
        if ((pSVar3->val4 == 0) && (pSVar3[1].val1 == 0)) {
          if ((float)runtime::Saves->timer <= 0.0) {
            FUN_0010eb60(param_1);
            return 1;
          }
          pSVar3[1].entries = param_1;
          FUN_0010f2d0();
        }
        return 1;
      }
      pSVar3 = (SaveEntry *)((int)&pSVar3->val1 + (uint)pBVar1->valueSize);
    } while (pSVar3 < pBVar1->tail);
  }
  return 0;
}




void __cdecl Scene::cleanup(EVP_PKEY_CTX *ctx)

{
  MindMemoryTargetWantedToAttack *pMVar1;
  MindMemoryTargetWantedToAttack *mem;
  int unaff_EDI;
  
  pMVar1 = g_scriptRelatedLinkedList_;
  while (mem = pMVar1, mem != (MindMemoryTargetWantedToAttack *)0x0) {
    pMVar1 = (MindMemoryTargetWantedToAttack *)(mem->header).next;
    if (*(int *)&(mem->header).memId == unaff_EDI) {
      MindMemory::dtor(mem);
    }
  }
  return;
}




void ResetStateVariables(void)

{
  undefined1 *puVar1;
  undefined2 *puVar2;
  AudioPlayingContext *pAVar3;
  AudioPlayingContext *pAVar4;
  Buffer<weapon> *pBVar5;
  Buffer<> *buffer;
  int iVar6;
  HeapTableEntry *pHVar7;
  
  ShouldntDroneBools[0] = 0;
  ShouldntDroneBools[1] = 0;
  PlayerExitedBox = 0;
  CheckLevelExits = 0;
  Scripting::GoToNextLevelScript = 0;
  BookmarkGroup = 4;
  Scripting::Bookmark = 0;
  Scripting::numScriptConditions = 0;
  if (Audio::SomeGlobalPlayingContext[0] != '\0') {
    pAVar3 = Audio::GetPlayingContext(Audio::SomeGlobalPlayingContext);
    iVar6 = pAVar3->numReferences + -1;
    pAVar3->numReferences = iVar6;
    if (iVar6 < 1) {
      if (pAVar3->playFlags != 0x12) {
        pAVar4 = Audio::GetSomePlayingThing(pAVar3);
        if (pAVar4 != (AudioPlayingContext *)0x0) {
          AudioPlayingContext::updateSomething(pAVar4);
        }
      }
      FUN_00038260(pAVar3);
      pAVar3->playFlags = 0;
    }
    Audio::SomeGlobalPlayingContext[0] = '\0';
  }
  FUN_00116da0();
  _DAT_0050e4d8 = 0;
  g_scriptRelatedLinkedList_ = (void *)0x0;
  if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
    pHVar7 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar7 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
  }
  pBVar5 = (Buffer<weapon> *)runtime::AllocateOnHeap(pHVar7->heapHandle,0,100);
  if (pBVar5 != (Buffer<weapon> *)0x0) {
    iVar6 = FUN_0014ded0(pHVar7->heapHandle,0,pBVar5);
    puVar2 = (undefined2 *)((int)pBVar5->values + iVar6 + -0x14);
    *puVar2 = 0x1234;
    *(undefined1 *)(puVar2 + 1) = *(undefined1 *)&pHVar7->field32_0x20;
  }
  pBVar5->head = pBVar5->values;
  pBVar5->tail = pBVar5->values;
  pBVar5->valueSize = 8;
  pBVar5->capacity = 10;
  pBVar5->end = (weapon *)&pBVar5->values[0].avatar.keyframeContext;
  g_pauseMenuState_ = New_Name;
  EventLoop::ChallengeShort = 0;
  _DAT_0050652c = 0;
  DAT_00506534 = 0;
  FLOAT_00506538 = 0.0;
  DAT_0050653c = 0;
  g_weapons = pBVar5;
  FUN_0012af10();
  Game::KillsInCurrentLevel = 0;
  Game::PrisonersSavedInCurrentLevel = 0;
  DAT_00545978 = 0;
  DAT_0054597c = 0;
  DAT_00545980 = 0;
  INT_004e17c8 = 1;
  challengeId_004e17cc = ~Attacks;
  DAT_004e17d0 = 0;
  DAT_004e19a8 = 0;
  INT_004e19a0 = 0;
  DAT_004e19a4 = 0;
  g_someWString[0x40] = L'\0';
  g_someWString[0x41] = L'\0';
  FUN_001287f0();
  if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
    pHVar7 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar7 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
  }
  buffer = (Buffer<> *)runtime::AllocateOnHeap(pHVar7->heapHandle,0,0x54);
  if (buffer != (Buffer<> *)0x0) {
    iVar6 = FUN_0014ded0(pHVar7->heapHandle,0,buffer);
    puVar2 = (undefined2 *)((int)buffer->values + iVar6 + -0x10);
    *puVar2 = 0x1234;
    *(undefined1 *)(puVar2 + 1) = *(undefined1 *)&pHVar7->field32_0x20;
  }
  puVar1 = &buffer->values[0].field_0x4;
  buffer->head = (Something0x20 *)puVar1;
  buffer->tail = (Something0x20 *)puVar1;
  buffer->valueSize = 0x20;
  buffer->capacity = 2;
  *(Something0x20 ***)buffer->values = &buffer[1].head;
  Scripting::ScriptConditions = buffer;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void WipeGameState(GameState *param_1)

{
  GameState *pGVar1;
  int iVar4;
  char *ppuVar5;
  undefined4 *puVar6;
  InputHandlerType4 **input_handler;
  GameState *pGVar3;
  
  pGVar1 = param_1;
  input_handler = &param_1->field81_0x230;
  Scripting::CreateScriptType2(input_handler);
                    // Basic handler
  runtime::PushInputHandlerAndSetActive(&(*input_handler)->header,"Scene Master Pad");
  Game::GameState.currentScene = 0;
  Game::GameState.currentChapter = 0;
  ppuVar5 = (char *)g_callback6Sets;
  do {
    (**(code **)ppuVar5)(&TransitionData);
    ppuVar5 = ppuVar5 + 0x18;
  } while ((int)ppuVar5 < 0x312a08);
  DAT_00506df8 = 0;
  Assets::GetResourceBytes("aid_loctext_ghoulies_actor_ghoulyintro",&param_1);
  pGVar3 = param_1;
  if (param_1 == (GameState *)0x0) {
    runtime::ExitGame(2);
  }
  g_timeSpentInCurrentLevel = 0.0;
  Game::TimeInCurrentLevel = 0.0;
  g_loctextGhouliesActorGhoulyintro_NEEDS_FIXING_ = (Asset *)pGVar3;
  actorMind::NumObjectTypes = 0;
  Game::NumFrozenAttackTimers = 0;
  Assets::NumSomethingBodies = 0;
  g_AssetBodySearchList[8] = 0;
  g_AssetBodySearchList[9] = 0;
  g_AssetBodySearchList[0x3a] = 0;
  g_AssetBodySearchList[0x3b] = 0;
  Game::GameState.cameraActor = (actor *)0x0;
  g_ticksInCurrentLevel = 0;
  TicksInCurrentLevel = 0;
  runtime::TimeScale = 1.0;
  Entity::Count = 0;
  runtime::ClearSceneInfo();
  FUN_0011b630();
  FUN_00129f30();
  FUN_00123b30();
  burnupsSentinel = (undefined *)0x0;
  burnups = 0;
  ModelSubresource0x12 = (TilesSubresource *)0x0;
  NumBurnups = (undefined *)0x0;
  FUN_000fd620();
  FUN_00118470();
  _DAT_0042a424 = uint32_t_0042a420 + DAT_0042a41c;
  _DAT_0042a42c = uint32_t_0042a428 + _DAT_0042a424;
  Cutscene::CurrentCutsceneIndex = -1;
  g_someAssetName[0] = '\0';
  Cutscene::LoadedCutscenes[7] = (Cutscene *)0x0;
  puVar6 = &DAT_00506930;
  for (iVar4 = 200; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  SecDialogVars();
  DAT_00511a10 = 0;
  CreateGradientTexture();
  SetGlobalSceneOrder("aid_aidlist_ghoulies_sceneorder_game");
  reuse_old_playcam_id();
  runtime::SetupHeapSaveData();
  pGVar1->currentSceneScript[0] = '\0';
  pGVar1->newSceneScriptAID[0] = '\0';
  pGVar1->prev_load_state = 0;
  pGVar1->newLoadState2___ = 0;
  pGVar1->new_load_state = Null;
  pGVar1->load_state = Null;
  g_stateStack = g_stateStack + 1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void InitialiseDoors(void)

{
  background_conflict8 *pbVar1;
  background_conflict8 *pbVar2;
  ushort uVar3;
  undefined4 uVar4;
  background_0x934_conflict3 pEVar5;
  BackgroundCollisionThing *pBVar6;
  int i;
  int local_8;
  ObjMsgID local_4;
  
  FUN_0005c020();
  i = 0;
  if (0 < Game::NumDoors) {
    do {
      UpdateDoor(Game::Doors[i].id,Game::Doors[i].isShut,0,0);
      i = i + 1;
    } while (i < Game::NumDoors);
  }
  local_8 = 0;
  pBVar6 = BackgroundCollisionThings[4];
  if (0 < g_someIndex) {
    do {
      uVar4 = (&DAT_005123b4)[local_8 * 2];
      uVar3 = (&DAT_005123b0)[local_8 * 4];
      if ((pBVar6 != (BackgroundCollisionThing *)0x0) && (i = 0, 0 < (int)pBVar6)) {
        do {
          FUN_00036a00(uVar3,(short)uVar4,BackgroundCollisionThings[i]);
          i = i + 1;
          pBVar6 = BackgroundCollisionThings[4];
        } while (i < (int)BackgroundCollisionThings[4]);
      }
      local_8 = local_8 + 1;
    } while (local_8 < g_someIndex);
  }
  Game::NumDoors = 0;
  g_someIndex = 0;
  local_4 = Background_PostAStarInit;
  pEVar5 = Game::SceneInfo.backgrounds.head;
  while (pEVar5 != (background_0x934_conflict3)0x0) {
    pbVar1 = ADJ(pEVar5);
    pbVar2 = ADJ(pEVar5);
    pEVar5 = pEVar5->next;
    (*((pbVar1->avatar).object.vtable)->onMessage)(pbVar2,&local_4);
  }
  return;
}




void OnDeath_(void)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  int unaff_EBX;
  undefined4 *puVar5;
  undefined4 uStack_98;
  undefined4 uStack_94;
  float fStack_90;
  float fStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 auStack_5d [23];
  
  CreateLoctext(*(LoctextValueContext **)(unaff_EBX + 0x103c),(LPWSTR)(unaff_EBX + 0x1040),
                (float)g_DXContext.backBufferWidth * 0.5,(float)g_DXContext.backBufferHeight * 0.1,
                1.2,1.2,7.5,1,0,1);
  CreateLoctext(*(LoctextValueContext **)(unaff_EBX + 0x103c),(LPWSTR)(unaff_EBX + 0x2040),
                (float)g_DXContext.backBufferWidth * 0.5,(float)g_DXContext.backBufferHeight * 0.6,
                0.9,0.9,7.5,1,0,1);
  if (*(int *)(unaff_EBX + 0x3048) == 0) {
    Scripting::CreateScriptType2((InputHandlerType4 **)(unaff_EBX + 0x3048));
    runtime::PushInputHandlerAndSetActive
              (&(*(InputHandlerType4 **)(unaff_EBX + 0x3048))->header,"Chapter splash screen");
  }
  if (*(int *)(unaff_EBX + 0x3044) == 0) {
    pcVar2 = "aid_loctext_ghoulies_menu_menutext";
    puVar5 = &local_80;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      puVar5 = puVar5 + 1;
    }
    *(undefined2 *)puVar5 = *(undefined2 *)pcVar2;
    *(char *)((int)puVar5 + 2) = pcVar2[2];
    puVar5 = auStack_5d;
    for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined1 *)puVar5 = 0;
    fStack_90 = (float)g_DXContext.backBufferWidth * 0.5;
    fStack_8c = g_DXContext.field35_0x64 - 16.0;
    uStack_98 = 0;
    uStack_94 = 0xc2900000;
    uStack_88 = 0x42200000;
    uStack_84 = 0xc2100000;
    TransitionAndLoadScene
              (0,"transitionMenu_basic",&fStack_90,&uStack_98,&uStack_88,0,0x3fc00000,&DAT_3f400000,
               "menutext",&local_80,0x400c0);
    FUN_00142860(0x40000000,0);
    pcVar4 = audio_asset_name_004312e8;
    pcVar2 = (char *)(*(int *)(unaff_EBX + 0x3044) + 0x1034);
    do {
      cVar1 = *pcVar4;
      *pcVar2 = cVar1;
      pcVar2 = pcVar2 + 1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
  }
  *(undefined4 *)(unaff_EBX + 0x3040) = 1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


BOOL InitEDB2Entry(Buffer<EDB2Entry> **outBuffer,avatar *av,bool_t param_3)

{
  background_0x934_conflict3 pEVar1;
  Buffer<EDB2Entry> *piVar5;
  int iVar2;
  EDB2Entry *entry;
  int iVar3;
  Buffer<EDB2Entry> *buf;
  
  for (pEVar1 = Game::SceneInfo.backgrounds.head; pEVar1 != (background_0x934_conflict3)0x0;
      pEVar1 = pEVar1->next) {
    if (ADJ(pEVar1) == (background_conflict8 *)av) {
      return 1;
    }
  }
  if (av->skipUpdate != 0) {
    return 1;
  }
  buf = *outBuffer;
  if (buf == (Buffer<EDB2Entry> *)0x0) {
    piVar5 = malloc_(0x50);
    piVar5->head = piVar5->_data;
    piVar5->tail = piVar5->_data;
    piVar5->valueSize = 0x10;
    piVar5->capacity = 4;
    piVar5->end = (EDB2Entry *)(piVar5 + 1);
    *outBuffer = piVar5;
  }
  else {
    for (entry = buf->head; entry < buf->tail; entry = entry + 1) {
      if (entry->avatar == av) {
        return 0;
      }
    }
  }
  if ((param_3 != 0) && (av->collisionMask == Nothing)) {
    return 0;
  }
  buf = *outBuffer;
  if (buf->tail == buf->end) {
    iVar2 = ((int)buf->tail - (int)buf->head) / (int)(uint)buf->valueSize;
    iVar3 = (uint)buf->capacity + iVar2;
    buf = (Buffer<EDB2Entry> *)AllocateMoreAStruct_33((uint)buf->valueSize * iVar3 + 0x10,buf);
    entry = buf->_data;
    buf->head = entry;
    buf->end = (EDB2Entry *)((int)&entry->avatar + (uint)buf->valueSize * iVar3);
    buf->tail = (EDB2Entry *)((int)&entry->avatar + (uint)buf->valueSize * iVar2);
    *outBuffer = buf;
  }
  entry = buf->tail;
  buf->tail = (EDB2Entry *)((int)&entry->avatar + (uint)buf->valueSize);
  entry->avatar = av;
  entry->collisionMask = av->collisionMask;
  *(undefined4 *)&entry->field_0x8 = 0;
  entry->maskNotChecked = 0;
  if (param_3 != 0) {
    av->collisionMask = Nothing;
    entry->maskNotChecked = 1;
  }
  return 1;
}




void RecalculateEDB2Collisions(Buffer<EDB2Entry> *param_1)

{
  EDB2Entry *str;
  EDB2Entry *pEVar1;
  EDB2Entry *dst;
  CollisionMask mask;
  
  pEVar1 = param_1->tail;
  dst = param_1->head;
  if (dst < pEVar1) {
    do {
      if (dst->maskNotChecked == 0) {
        mask = dst->avatar->collisionMask;
        if (mask == Nothing) {
          str = (EDB2Entry *)((int)param_1->tail - (uint)param_1->valueSize);
          if (dst < str) {
            memcpy(dst,str,(uint)param_1->valueSize);
          }
          pEVar1 = pEVar1 + -1;
          param_1->tail = (EDB2Entry *)((int)param_1->tail - (uint)param_1->valueSize);
          dst = dst + -1;
        }
        else {
          dst->avatar->collisionMask = Nothing;
          dst->collisionMask = mask;
          dst->maskNotChecked = 1;
        }
      }
      dst = dst + 1;
    } while (dst < pEVar1);
  }
  return;
}




int FUN_0013eeb0(int param_1,Buffer<EDB2Entry> **param_2)

{
  Buffer<> *pBVar1;
  void *mem;
  avatar *av;
  undefined4 *puVar2;
  Buffer<EDB2Entry> *pBVar3;
  EDB2Entry *pEVar4;
  AnimCollisionSubresourceEntry *entry;
  Skeleton *skeleton;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  EDB2Entry *pEVar9;
  HeapTableEntry *pHVar10;
  int *piVar11;
  int iVar12;
  float10 extraout_ST0;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined4 local_a0;
  void *local_9c;
  float local_98;
  float local_94;
  float local_90;
  vec3 local_8c;
  undefined4 auStack_80 [32];
  
  local_b0 = 0;
  if (*param_2 != (Buffer<EDB2Entry> *)0x0) {
    RecalculateEDB2Collisions(*param_2);
  }
  entry = (AnimCollisionSubresourceEntry *)FUN_00042560(1);
  iVar5 = 0;
  if (entry == (AnimCollisionSubresourceEntry *)0x0) {
LAB_0013f0bd:
    pBVar3 = *param_2;
    if (pBVar3 != (Buffer<EDB2Entry> *)0x0) {
      pEVar4 = pBVar3->tail;
      for (pEVar9 = pBVar3->head; pEVar9 < pEVar4; pEVar9 = pEVar9 + 1) {
        if (pEVar9->maskNotChecked != 0) {
          pEVar9->avatar->collisionMask = pEVar9->collisionMask;
          pEVar9->maskNotChecked = 0;
        }
      }
    }
    return iVar5;
  }
  do {
    iVar5 = *(int *)(param_1 + 0x204);
    if (iVar5 == 0) {
      skeleton = (Skeleton *)0x0;
    }
    else {
      skeleton = *(Skeleton **)(iVar5 + 0x168);
      if (skeleton == (Skeleton *)0x0) {
        skeleton = *(Skeleton **)(iVar5 + 0x164);
      }
    }
    checkCollisionAgainstSkeleton(entry,skeleton,&local_8c,(AffineTransform *)(param_1 + 0x2ac));
    iVar5 = FUN_00122b00(&local_8c,(float)extraout_ST0,0x20002);
    if (iVar5 != 0) {
      local_b0 = local_b0 + iVar5;
      local_a8 = 0;
      local_a0 = 0;
      local_9c = (void *)0x0;
      local_98 = 0.0;
      local_94 = 0.0;
      iVar12 = 0;
      local_90 = 0.0;
      local_ac = 0x1b;
      local_a4 = param_1;
      if (0 < iVar5) {
        do {
          pBVar1 = Physics::CollisionContexts[iVar12].ctx;
          auStack_80[iVar12 * 2] = Physics::CollisionContexts[iVar12].collidingAvatar;
          uVar6 = FUN_000fcc90(pBVar1);
          auStack_80[iVar12 * 2 + 1] = uVar6;
          iVar12 = iVar12 + 1;
        } while (iVar12 < iVar5);
      }
      iVar12 = 0;
      if (0 < iVar5) {
        do {
          mem = (void *)auStack_80[iVar12 * 2 + 1];
          av = (avatar *)auStack_80[iVar12 * 2];
          local_98 = local_8c.x;
          local_94 = local_8c.y;
          local_90 = local_8c.z;
          local_9c = mem;
          (*av->vtable->onMessage)(av,&local_ac);
          iVar7 = FindHeapOf(mem);
          uVar6 = runtime::CurrentHeapToAllocateFrom;
          if (g_HeapTableBase[iVar7].heapHandle == (HANDLE)0x0) {
            pHVar10 = (HeapTableEntry *)0x0;
          }
          else {
            pHVar10 = g_HeapTableBase + iVar7;
          }
          runtime::CurrentHeapToAllocateFrom = iVar7;
          XAPILIB::HeapFree(pHVar10->heapHandle,0,mem);
          runtime::CurrentHeapToAllocateFrom = uVar6;
          InitEDB2Entry(param_2,av,1);
          iVar12 = iVar12 + 1;
        } while (iVar12 < iVar5);
      }
    }
    if ((*(int **)(param_1 + 0x204) != (int *)0x0) &&
       (puVar2 = (undefined4 *)**(int **)(param_1 + 0x204), puVar2 != (undefined4 *)0x0)) {
      uVar8 = 0;
      if (puVar2[1] != 0) {
        piVar11 = (int *)*puVar2;
        do {
          if (*piVar11 == 4) break;
          uVar8 = uVar8 + 1;
          piVar11 = piVar11 + 2;
        } while (uVar8 < (uint)puVar2[1]);
      }
    }
    iVar5 = local_b0;
    if (entry->size == 0) goto LAB_0013f0bd;
    entry = (AnimCollisionSubresourceEntry *)(&entry->colliderType + (byte)entry->size);
    while( true ) {
      if (entry == (AnimCollisionSubresourceEntry *)0x0) goto LAB_0013f0bd;
      if (((entry->collisionMask & Mask0x1) != Nothing) && (entry->colliderType == Sphere)) break;
      if (entry->size == 0) goto LAB_0013f0bd;
      entry = (AnimCollisionSubresourceEntry *)(&entry->colliderType + (byte)entry->size);
    }
  } while( true );
}




void entry(void)

{
  HANDLE hObject;
  LPDWORD unaff_ESI;
  DWORD unaff_EDI;
  
  if (0xddc < XBE_CERTIFICATE_HEADER_00010184.SizeOfHeader) {
    XBE_CERTIFICATE_HEADER_00010184.SizeOfHeader = 0xddc;
  }
  DAT_00549528 = 0x94;
  XAPILIB::_tls_index = 0xffffffdb;
  hObject = XAPILIB::CreateThread
                      ((LPSECURITY_ATTRIBUTES)0x0,0x14fa75,(LPTHREAD_START_ROUTINE)0x0,(LPVOID)0x0,
                       unaff_EDI,unaff_ESI);
  if (hObject == (HANDLE)0x0) {
    XAPILIB::XapiBootToDash(1,1,0);
  }
  XAPILIB::CloseHandle(hObject);
  return;
}




ULONG __cdecl DbgPrint(PCSTR Format,...)

{
  ULONG UVar1;
  
                    // WARNING: Could not recover jumptable at 0x00152776. Too many branches
                    // WARNING: Treating indirect jump as call
  UVar1 = DbgPrint(Format);
  return UVar1;
}




uint IndexOfTableItem(NamedCallbackTable *param_1,char *param_2,NamedCallbackEntry **val)

{
  int iVar2;
  NamedCallbackEntry *base;
  NamedCallbackEntry *pbVar5;
  char *char_i;
  uint i;
  bool bVar3;
  NamedCallbackEntry *basePtr;
  byte bVar1;
  
  i = 0;
  if (param_1->count != 0) {
    basePtr = param_1->names;
    pbVar5 = basePtr;
    char_i = param_2;
    base = basePtr;
LAB_00158840:
    do {
      bVar1 = pbVar5->name[0];
      bVar3 = bVar1 < (byte)*char_i;
      if (bVar1 == *char_i) {
        if (bVar1 != 0) {
          bVar1 = pbVar5->name[1];
          bVar3 = bVar1 < (byte)char_i[1];
          if (bVar1 != char_i[1]) goto LAB_00158864;
          char_i = char_i + 2;
          pbVar5 = (NamedCallbackEntry *)(pbVar5->name + 2);
          if (bVar1 != 0) goto LAB_00158840;
        }
        iVar2 = 0;
      }
      else {
LAB_00158864:
        iVar2 = (1 - (uint)bVar3) - (uint)(bVar3 != 0);
      }
      if (iVar2 == 0) {
        *val = basePtr + i;
        return i;
      }
      i = i + 1;
      pbVar5 = base + 1;
      char_i = param_2;
      base = pbVar5;
    } while (i < param_1->count);
  }
  *val = (NamedCallbackEntry *)0x0;
  return 0;
}




void * __cdecl _memmove(void *__dest,void *__src,size_t __n)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((__src < __dest) && (__dest < (void *)(__n + (int)__src))) {
    puVar3 = (undefined4 *)((__n - 4) + (int)__src);
    puVar4 = (undefined4 *)((__n - 4) + (int)__dest);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = __n >> 2;
      uVar2 = __n & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return __dest;
        case 2:
          goto switchD_00165cab_caseD_2;
        case 3:
          goto switchD_00165cab_caseD_3;
        }
        goto switchD_00165cab_caseD_1;
      }
    }
    else {
      switch(__n) {
      case 0:
        goto switchD_00165cab_caseD_0;
      case 1:
        goto switchD_00165cab_caseD_1;
      case 2:
        goto switchD_00165cab_caseD_2;
      case 3:
        goto switchD_00165cab_caseD_3;
      default:
        uVar1 = __n - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return __dest;
            case 2:
              goto switchD_00165cab_caseD_2;
            case 3:
              goto switchD_00165cab_caseD_3;
            }
            goto switchD_00165cab_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return __dest;
            case 2:
              goto switchD_00165cab_caseD_2;
            case 3:
              goto switchD_00165cab_caseD_3;
            }
            goto switchD_00165cab_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return __dest;
            case 2:
              goto switchD_00165cab_caseD_2;
            case 3:
              goto switchD_00165cab_caseD_3;
            }
            goto switchD_00165cab_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_00165cab_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return __dest;
    case 2:
switchD_00165cab_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return __dest;
    case 3:
switchD_00165cab_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return __dest;
    }
switchD_00165cab_caseD_0:
    return __dest;
  }
  puVar3 = __dest;
  if (((uint)__dest & 3) == 0) {
    uVar1 = __n >> 2;
    uVar2 = __n & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *(undefined4 *)__src;
        __src = (undefined4 *)((int)__src + 4);
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return __dest;
      case 2:
        goto switchD_00165b25_caseD_2;
      case 3:
        goto switchD_00165b25_caseD_3;
      }
      goto switchD_00165b25_caseD_1;
    }
  }
  else {
    switch(__n) {
    case 0:
      goto switchD_00165b25_caseD_0;
    case 1:
      goto switchD_00165b25_caseD_1;
    case 2:
      goto switchD_00165b25_caseD_2;
    case 3:
      goto switchD_00165b25_caseD_3;
    default:
      uVar1 = (__n - 4) + ((uint)__dest & 3);
      switch((uint)__dest & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)__dest = *(undefined1 *)__src;
        *(undefined1 *)((int)__dest + 1) = *(undefined1 *)((int)__src + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)__dest + 2) = *(undefined1 *)((int)__src + 2);
        __src = (void *)((int)__src + 3);
        puVar3 = (undefined4 *)((int)__dest + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)__src;
            __src = (undefined4 *)((int)__src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return __dest;
          case 2:
            goto switchD_00165b25_caseD_2;
          case 3:
            goto switchD_00165b25_caseD_3;
          }
          goto switchD_00165b25_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)__dest = *(undefined1 *)__src;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)__dest + 1) = *(undefined1 *)((int)__src + 1);
        __src = (void *)((int)__src + 2);
        puVar3 = (undefined4 *)((int)__dest + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)__src;
            __src = (undefined4 *)((int)__src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return __dest;
          case 2:
            goto switchD_00165b25_caseD_2;
          case 3:
            goto switchD_00165b25_caseD_3;
          }
          goto switchD_00165b25_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)__dest = *(undefined1 *)__src;
        __src = (void *)((int)__src + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)__dest + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)__src;
            __src = (undefined4 *)((int)__src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return __dest;
          case 2:
            goto switchD_00165b25_caseD_2;
          case 3:
            goto switchD_00165b25_caseD_3;
          }
          goto switchD_00165b25_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = *(undefined4 *)((int)__src + (uVar1 - 7) * 4);
  case 6:
    puVar3[uVar1 - 6] = *(undefined4 *)((int)__src + (uVar1 - 6) * 4);
  case 5:
    puVar3[uVar1 - 5] = *(undefined4 *)((int)__src + (uVar1 - 5) * 4);
  case 4:
    puVar3[uVar1 - 4] = *(undefined4 *)((int)__src + (uVar1 - 4) * 4);
  case 3:
    puVar3[uVar1 - 3] = *(undefined4 *)((int)__src + (uVar1 - 3) * 4);
  case 2:
    puVar3[uVar1 - 2] = *(undefined4 *)((int)__src + (uVar1 - 2) * 4);
  case 1:
    puVar3[uVar1 - 1] = *(undefined4 *)((int)__src + (uVar1 - 1) * 4);
    __src = (void *)((int)__src + uVar1 * 4);
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_00165b25_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)__src;
    return __dest;
  case 2:
switchD_00165b25_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)__src;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)__src + 1);
    return __dest;
  case 3:
switchD_00165b25_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)__src;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)__src + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)__src + 2);
    return __dest;
  }
switchD_00165b25_caseD_0:
  return __dest;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


wchar_t * __cdecl _wcsncpy(wchar_t *__dest,wchar_t *__src,size_t __n)

{
  wchar_t wVar1;
  uint uVar2;
  uint uVar3;
  wchar_t *pwVar4;
  
  pwVar4 = __dest;
  if (__n != 0) {
    do {
      wVar1 = *__src;
      *pwVar4 = wVar1;
      pwVar4 = pwVar4 + 1;
      __src = __src + 1;
      if (wVar1 == L'\0') break;
      __n = __n - 1;
    } while (__n != 0);
    if ((__n != 0) && (uVar2 = __n - 1, uVar2 != 0)) {
      for (uVar3 = uVar2 >> 1; uVar3 != 0; uVar3 = uVar3 - 1) {
        pwVar4[0] = L'\0';
        pwVar4[1] = L'\0';
        pwVar4 = pwVar4 + 2;
      }
      for (uVar2 = (uint)((uVar2 & 1) != 0); uVar2 != 0; uVar2 = uVar2 - 1) {
        *pwVar4 = L'\0';
        pwVar4 = pwVar4 + 1;
      }
    }
  }
  return __dest;
}



// Library Function - Single Match
//  _strchr
// 
// Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release


char * __cdecl _strchr(char *__s,int __c)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)__s & 3) != 0) {
    uVar1 = *(uint *)__s;
    if ((char)uVar1 == (char)__c) {
      return (char *)(uint *)__s;
    }
    __s = (char *)((int)__s + 1);
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *(uint *)__s;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11((char)__c,(char)__c),CONCAT11((char)__c,(char)__c));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = (uint *)((int)__s + 4);
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      __s = (char *)puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (char *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (char *)0x0;
        }
      }
    }
    uVar1 = *(uint *)__s;
    if ((char)uVar1 == (char)__c) {
      return (char *)(uint *)__s;
    }
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == (char)__c) {
      return (char *)((int)__s + 1);
    }
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == (char)__c) {
      return (char *)((int)__s + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == (char)__c) {
      return (char *)((int)__s + 3);
    }
    __s = (char *)puVar5;
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}



// Library Function - Single Match
//  _atol
// 
// Library: Visual Studio 2003 Release


long __cdecl _atol(char *__nptr)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  
  while( true ) {
    iVar1 = FUN_00168883(*__nptr);
    if (iVar1 == 0) break;
    __nptr = __nptr + 1;
  }
  uVar2 = (uint)(byte)*__nptr;
  pbVar5 = (byte *)(__nptr + 1);
  if ((uVar2 == 0x2d) || (uVar3 = uVar2, uVar2 == 0x2b)) {
    uVar3 = (uint)*pbVar5;
    pbVar5 = (byte *)(__nptr + 2);
  }
  iVar1 = 0;
  while( true ) {
    if ((uVar3 < 0x30) || (0x39 < uVar3)) {
      iVar4 = -1;
    }
    else {
      iVar4 = uVar3 - 0x30;
    }
    if (iVar4 == -1) break;
    iVar1 = iVar4 + iVar1 * 10;
    uVar3 = (uint)*pbVar5;
    pbVar5 = pbVar5 + 1;
  }
  if (uVar2 == 0x2d) {
    iVar1 = -iVar1;
  }
  return iVar1;
}




long __cdecl _atol(char *__nptr)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  
  while( true ) {
    iVar1 = FUN_00168883(*__nptr);
    if (iVar1 == 0) break;
    __nptr = __nptr + 1;
  }
  uVar2 = (uint)(byte)*__nptr;
  pbVar5 = (byte *)(__nptr + 1);
  if ((uVar2 == 0x2d) || (uVar3 = uVar2, uVar2 == 0x2b)) {
    uVar3 = (uint)*pbVar5;
    pbVar5 = (byte *)(__nptr + 2);
  }
  iVar1 = 0;
  while( true ) {
    if ((uVar3 < 0x30) || (0x39 < uVar3)) {
      iVar4 = -1;
    }
    else {
      iVar4 = uVar3 - 0x30;
    }
    if (iVar4 == -1) break;
    iVar1 = iVar4 + iVar1 * 10;
    uVar3 = (uint)*pbVar5;
    pbVar5 = pbVar5 + 1;
  }
  if (uVar2 == 0x2d) {
    iVar1 = -iVar1;
  }
  return iVar1;
}




wchar_t * __cdecl _wcscat(wchar_t *__dest,wchar_t *__src)

{
  wchar_t wVar1;
  wchar_t *pwVar2;
  
  pwVar2 = __dest;
  wVar1 = *__dest;
  while (wVar1 != L'\0') {
    __dest = __dest + 1;
    wVar1 = *__dest;
  }
  do {
    wVar1 = *__src;
    *__dest = wVar1;
    __dest = __dest + 1;
    __src = __src + 1;
  } while (wVar1 != L'\0');
  return pwVar2;
}




int __cdecl _fclose(FILE *__stream)

{
  int local_20;
  
  local_20 = -1;
  if (((uint)__stream->_IO_read_base & 0x40) == 0) {
    __lock_file(__stream);
    local_20 = __fclose_lk(__stream);
    FUN_0016619a();
  }
  else {
    __stream->_IO_read_base = (char *)0x0;
  }
  return local_20;
}




int __cdecl _vsprintf(char *__s,char *__format,__gnuc_va_list __arg)

{
  int iVar1;
  char *local_24;
  int local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_20 = 0x7fffffff;
  local_18 = 0x42;
  local_1c = __s;
  local_24 = __s;
  iVar1 = FUN_00168fed(&local_24,__format,__arg);
  if (__s != (char *)0x0) {
    local_20 = local_20 + -1;
    if (local_20 < 0) {
      __flsbuf(0,&local_24);
    }
    else {
      *local_24 = '\0';
    }
  }
  return iVar1;
}



// Library Function - Single Match
//  _sprintf
// 
// Library: Visual Studio 2003 Release


int __cdecl _sprintf(char *__s,char *__format,...)

{
  int iVar1;
  char *local_24;
  int local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_20 = 0x7fffffff;
  local_18 = 0x42;
  local_1c = __s;
  local_24 = __s;
  iVar1 = FUN_00168fed(&local_24,__format,&stack0x0000000c);
  if (__s != (char *)0x0) {
    local_20 = local_20 + -1;
    if (local_20 < 0) {
      __flsbuf(0,&local_24);
    }
    else {
      *local_24 = '\0';
    }
  }
  return iVar1;
}



// Library Function - Single Match
//  __abstract_cw
// 
// Library: Visual Studio 2003 Release


int __cdecl _strncmp(char *__s1,char *__s2,size_t __n)

{
  size_t sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char cVar1;
  char cVar2;
  
  uVar5 = 0;
  sVar3 = __n;
  pcVar6 = __s1;
  if (__n != 0) {
    do {
      if (sVar3 == 0) break;
      sVar3 = sVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = __n - sVar3;
    do {
      pcVar6 = __s2;
      pcVar7 = __s1;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = __s1 + 1;
      pcVar6 = __s2 + 1;
      cVar2 = *__s1;
      cVar1 = *__s2;
      __s2 = pcVar6;
      __s1 = pcVar7;
    } while (cVar1 == cVar2);
    uVar5 = 0;
    if ((byte)pcVar6[-1] <= (byte)pcVar7[-1]) {
      if (pcVar6[-1] == pcVar7[-1]) {
        return 0;
      }
      uVar5 = 0xfffffffe;
    }
    uVar5 = ~uVar5;
  }
  return uVar5;
}



// Library Function - Single Match
//  __vsnprintf
// 
// Library: Visual Studio 2003 Release


char * __cdecl _strncat(char *__dest,char *__src,size_t __n)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  
  puVar5 = (uint *)__dest;
  if (__n == 0) {
    return __dest;
  }
  do {
    if (((uint)puVar5 & 3) == 0) goto LAB_001664cc;
    uVar4 = *puVar5;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_001664fd;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar6 = (uint *)((int)puVar6 + 2);
      goto LAB_0016650f;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_001664cc:
    do {
      puVar6 = puVar5;
      puVar5 = puVar6 + 1;
    } while (((*puVar6 ^ 0xffffffff ^ *puVar6 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar6;
    if ((char)uVar4 == '\0') goto LAB_0016650f;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar6 = (uint *)((int)puVar6 + 1);
      goto LAB_0016650f;
    }
  }
LAB_001664fd:
  puVar6 = (uint *)((int)puVar5 + -1);
LAB_0016650f:
  if (((uint)__src & 3) == 0) {
    uVar3 = __n >> 2;
  }
  else {
    do {
      bVar1 = (byte)*(uint *)__src;
      uVar4 = (uint)bVar1;
      __src = (char *)((int)__src + 1);
      if (bVar1 == 0) goto LAB_0016656a;
      *(byte *)puVar6 = bVar1;
      puVar6 = (uint *)((int)puVar6 + 1);
      __n = __n - 1;
      if (__n == 0) goto LAB_00166560;
    } while (((uint)__src & 3) != 0);
    uVar3 = __n >> 2;
  }
  do {
    if (uVar3 == 0) {
      for (uVar4 = __n & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        uVar3 = *(uint *)__src;
        __src = (char *)((int)__src + 1);
        *(byte *)puVar6 = (byte)uVar3;
        puVar6 = (uint *)((int)puVar6 + 1);
        if ((byte)uVar3 == 0) {
          return __dest;
        }
      }
LAB_00166560:
      *(byte *)puVar6 = 0;
      return __dest;
    }
    uVar2 = *(uint *)__src;
    uVar4 = *(uint *)__src;
    __src = (char *)((int)__src + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar4 == '\0') {
LAB_0016656a:
        *(byte *)puVar6 = (byte)uVar4;
        return __dest;
      }
      if ((char)(uVar4 >> 8) == '\0') {
        *(short *)puVar6 = (short)uVar4;
        return __dest;
      }
      if ((uVar4 & 0xff0000) == 0) {
        *(short *)puVar6 = (short)uVar4;
        *(byte *)((int)puVar6 + 2) = 0;
        return __dest;
      }
      if ((uVar4 & 0xff000000) == 0) {
        *puVar6 = uVar4;
        return __dest;
      }
    }
    *puVar6 = uVar4;
    puVar6 = puVar6 + 1;
    uVar3 = uVar3 - 1;
  } while( true );
}



// Library Function - Single Match
//  _strncpy
// 
// Library: Visual Studio


char * __cdecl _strncpy(char *__dest,char *__src,size_t __n)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (__n == 0) {
    return __dest;
  }
  puVar5 = (uint *)__dest;
  if (((uint)__src & 3) != 0) {
    while( true ) {
      uVar4 = *(uint *)__src;
      __src = (char *)((int)__src + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      __n = __n - 1;
      if (__n == 0) {
        return __dest;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)__src & 3) == 0) {
        uVar4 = __n >> 2;
        goto joined_r0x0016662c;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = __n >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_00166673;
        goto LAB_001666e9;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      __n = __n - 1;
    } while (__n != 0);
    return __dest;
  }
  uVar4 = __n >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *(uint *)__src;
      uVar2 = *(uint *)__src;
      __src = (char *)((int)__src + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x001666e5:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_001666e9:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          __n = __n & 3;
          if (__n != 0) goto LAB_00166673;
          return __dest;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x001666e5;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x001666e5;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x001666e5;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x0016662c:
    } while (uVar4 != 0);
    __n = __n & 3;
    if (__n == 0) {
      return __dest;
    }
  }
  do {
    cVar3 = (char)*(uint *)__src;
    __src = (char *)((int)__src + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (__n = __n - 1, __n != 0) {
LAB_00166673:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return __dest;
    }
    __n = __n - 1;
  } while (__n != 0);
  return __dest;
}



// Library Function - Single Match
//  _shortsort
// 
// Library: Visual Studio 2003 Release


void __cdecl _qsort(void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar)

{
  undefined1 uVar1;
  uint uVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  size_t sVar7;
  undefined1 *puVar8;
  undefined1 *local_100;
  undefined1 *local_fc;
  int local_f8;
  size_t sStack_f4;
  undefined4 auStack_f0 [30];
  undefined4 auStack_78 [30];
  
  if ((__nmemb < 2) || (__size == 0)) {
    return;
  }
  local_f8 = 0;
  local_100 = __base;
  local_fc = (undefined1 *)((__nmemb - 1) * __size + (int)__base);
LAB_001667c5:
  while (uVar2 = (uint)((int)local_fc - (int)local_100) / __size + 1, 8 < uVar2) {
    puVar3 = local_100 + (uVar2 >> 1) * __size;
    iVar4 = (*__compar)(local_100,puVar3);
    if ((0 < iVar4) && (local_100 != puVar3)) {
      puVar5 = puVar3;
      sVar7 = __size;
      do {
        uVar1 = puVar5[(int)local_100 - (int)puVar3];
        puVar5[(int)local_100 - (int)puVar3] = *puVar5;
        *puVar5 = uVar1;
        puVar5 = puVar5 + 1;
        sVar7 = sVar7 - 1;
      } while (sVar7 != 0);
    }
    iVar4 = (*__compar)(local_100,local_fc);
    if ((0 < iVar4) && (local_100 != local_fc)) {
      puVar5 = local_fc;
      sVar7 = __size;
      do {
        uVar1 = puVar5[(int)local_100 - (int)local_fc];
        puVar5[(int)local_100 - (int)local_fc] = *puVar5;
        *puVar5 = uVar1;
        puVar5 = puVar5 + 1;
        sVar7 = sVar7 - 1;
      } while (sVar7 != 0);
    }
    iVar4 = (*__compar)(puVar3,local_fc);
    puVar5 = local_100;
    puVar8 = local_fc;
    if ((0 < iVar4) && (puVar3 != local_fc)) {
      puVar6 = local_fc;
      sVar7 = __size;
      do {
        uVar1 = puVar6[(int)puVar3 - (int)local_fc];
        puVar6[(int)puVar3 - (int)local_fc] = *puVar6;
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
        sVar7 = sVar7 - 1;
      } while (sVar7 != 0);
    }
LAB_001668b0:
    if (puVar5 < puVar3) {
      do {
        puVar5 = puVar5 + __size;
        if (puVar3 <= puVar5) goto LAB_001668d0;
        iVar4 = (*__compar)(puVar5,puVar3);
      } while (iVar4 < 1);
      if (puVar3 <= puVar5) goto LAB_001668d0;
    }
    else {
LAB_001668d0:
      do {
        puVar5 = puVar5 + __size;
        if (local_fc < puVar5) break;
        iVar4 = (*__compar)(puVar5,puVar3);
      } while (iVar4 < 1);
    }
    do {
      puVar8 = puVar8 + -__size;
      if (puVar8 <= puVar3) break;
      iVar4 = (*__compar)(puVar8,puVar3);
    } while (0 < iVar4);
    if (puVar5 <= puVar8) {
      if (puVar5 != puVar8) {
        sStack_f4 = __size;
        puVar6 = puVar8;
        do {
          uVar1 = puVar6[(int)puVar5 - (int)puVar8];
          puVar6[(int)puVar5 - (int)puVar8] = *puVar6;
          *puVar6 = uVar1;
          puVar6 = puVar6 + 1;
          sStack_f4 = sStack_f4 - 1;
        } while (sStack_f4 != 0);
      }
      if (puVar3 == puVar8) {
        puVar3 = puVar5;
      }
      goto LAB_001668b0;
    }
    puVar8 = puVar8 + __size;
    if (puVar3 < puVar8) {
      do {
        puVar8 = puVar8 + -__size;
        if (puVar8 <= puVar3) goto LAB_00166970;
        iVar4 = (*__compar)(puVar8,puVar3);
      } while (iVar4 == 0);
      if (puVar8 <= puVar3) goto LAB_00166970;
    }
    else {
LAB_00166970:
      do {
        puVar8 = puVar8 + -__size;
        if (puVar8 <= local_100) break;
        iVar4 = (*__compar)(puVar8,puVar3);
      } while (iVar4 == 0);
    }
    if ((int)puVar8 - (int)local_100 < (int)local_fc - (int)puVar5) goto LAB_001669cb;
    if (local_100 < puVar8) {
      auStack_f0[local_f8] = local_100;
      auStack_78[local_f8] = puVar8;
      local_f8 = local_f8 + 1;
    }
    local_100 = puVar5;
    if (local_fc <= puVar5) goto LAB_001667e7;
  }
  _shortsort(local_100,__size,__compar);
  goto LAB_001667e7;
LAB_001669cb:
  if (puVar5 < local_fc) {
    auStack_f0[local_f8] = puVar5;
    auStack_78[local_f8] = local_fc;
    local_f8 = local_f8 + 1;
  }
  local_fc = puVar8;
  if (puVar8 <= local_100) {
LAB_001667e7:
    local_f8 = local_f8 + -1;
    if (local_f8 < 0) {
      return;
    }
    local_100 = (undefined1 *)auStack_f0[local_f8];
    local_fc = (undefined1 *)auStack_78[local_f8];
  }
  goto LAB_001667c5;
}



// Library Function - Single Match
//  _swprintf
// 
// Library: Visual Studio 2003 Release


int __cdecl _swprintf(wchar_t *__s,size_t __n,wchar_t *__format,...)

{
  int iVar1;
  wchar_t *local_24;
  int local_20;
  wchar_t *local_1c;
  undefined4 local_18;
  
  local_1c = __s;
  local_24 = __s;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = FUN_0016993d(&local_24,__n,&__format);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    __flsbuf(0,&local_24);
  }
  else {
    *(undefined1 *)local_24 = 0;
    local_24 = (wchar_t *)((int)local_24 + 1);
  }
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    __flsbuf(0,&local_24);
  }
  else {
    *(undefined1 *)local_24 = 0;
  }
  return iVar1;
}



// Library Function - Single Match
//  _swscanf
// 
// Library: Visual Studio 2003 Release


int __cdecl _swscanf(wchar_t *__s,wchar_t *__format,...)

{
  int iVar1;
  wchar_t *local_24;
  int local_20;
  wchar_t *local_1c;
  undefined4 local_18;
  
  local_18 = 0x49;
  local_1c = __s;
  local_24 = __s;
  local_20 = FUN_00166ecb(__s);
  local_20 = local_20 << 1;
  iVar1 = FUN_0016a17c(&local_24,__format,&stack0x0000000c);
  return iVar1;
}



// Library Function - Single Match
//  _strstr
// 
// Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release


char * __cdecl _strstr(char *__haystack,char *__needle)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  uint *puVar9;
  char *pcVar10;
  
  cVar3 = *__needle;
  if (cVar3 == '\0') {
    return __haystack;
  }
  if (__needle[1] == '\0') {
    while (((uint)__haystack & 3) != 0) {
      uVar4 = *(uint *)__haystack;
      if ((char)uVar4 == cVar3) {
        return (char *)(uint *)__haystack;
      }
      __haystack = (char *)((int)__haystack + 1);
      if ((char)uVar4 == '\0') {
        return (char *)0x0;
      }
    }
    while( true ) {
      while( true ) {
        uVar4 = *(uint *)__haystack;
        uVar7 = uVar4 ^ CONCAT22(CONCAT11(cVar3,cVar3),CONCAT11(cVar3,cVar3));
        uVar6 = uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff;
        puVar9 = (uint *)((int)__haystack + 4);
        if (((uVar7 ^ 0xffffffff ^ uVar7 + 0x7efefeff) & 0x81010100) != 0) break;
        __haystack = (char *)puVar9;
        if ((uVar6 & 0x81010100) != 0) {
          if ((uVar6 & 0x1010100) != 0) {
            return (char *)0x0;
          }
          if ((uVar4 + 0x7efefeff & 0x80000000) == 0) {
            return (char *)0x0;
          }
        }
      }
      uVar4 = *(uint *)__haystack;
      if ((char)uVar4 == cVar3) {
        return (char *)(uint *)__haystack;
      }
      if ((char)uVar4 == '\0') {
        return (char *)0x0;
      }
      cVar5 = (char)(uVar4 >> 8);
      if (cVar5 == cVar3) {
        return (char *)((int)__haystack + 1);
      }
      if (cVar5 == '\0') {
        return (char *)0x0;
      }
      cVar5 = (char)(uVar4 >> 0x10);
      if (cVar5 == cVar3) {
        return (char *)((int)__haystack + 2);
      }
      if (cVar5 == '\0') break;
      cVar5 = (char)(uVar4 >> 0x18);
      if (cVar5 == cVar3) {
        return (char *)((int)__haystack + 3);
      }
      __haystack = (char *)puVar9;
      if (cVar5 == '\0') {
        return (char *)0x0;
      }
    }
    return (char *)0x0;
  }
  do {
    cVar5 = *__haystack;
    do {
      while (__haystack = __haystack + 1, cVar5 != cVar3) {
        if (cVar5 == '\0') {
          return (char *)0x0;
        }
        cVar5 = *__haystack;
      }
      cVar5 = *__haystack;
      pcVar10 = __haystack + 1;
      pcVar8 = __needle;
    } while (cVar5 != __needle[1]);
    do {
      if (pcVar8[2] == '\0') {
LAB_00166b29:
        return __haystack + -1;
      }
      if (*pcVar10 != pcVar8[2]) break;
      pcVar1 = pcVar8 + 3;
      if (*pcVar1 == '\0') goto LAB_00166b29;
      pcVar2 = pcVar10 + 1;
      pcVar8 = pcVar8 + 2;
      pcVar10 = pcVar10 + 2;
    } while (*pcVar1 == *pcVar2);
  } while( true );
}




char * __cdecl _strrchr(char *__s,int __c)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = __s;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = __s + 1;
    cVar1 = *__s;
    __s = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while ((char)__c != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != (char)__c) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}




int __cdecl _isalpha(int param_1)

{
  int iVar1;
  
  if (1 < DAT_00338188) {
    iVar1 = FUN_0016ae1f(param_1,0x103);
    return iVar1;
  }
  return *(ushort *)(PTR_DAT_00338180 + param_1 * 2) & 0x103;
}



// Library Function - Single Match
//  _isdigit
// 
// Library: Visual Studio 2003 Release


int __cdecl _isdigit(int param_1)

{
  int iVar1;
  
  if (1 < DAT_00338188) {
    iVar1 = FUN_0016ae1f(param_1,4);
    return iVar1;
  }
  return (byte)PTR_DAT_00338180[param_1 * 2] & 4;
}



// Library Function - Single Match
//  _isspace
// 
// Library: Visual Studio 2003 Release


int __cdecl _isspace(int param_1)

{
  int iVar1;
  
  if (1 < DAT_00338188) {
    iVar1 = FUN_0016ae1f(param_1,8);
    return iVar1;
  }
  return (byte)PTR_DAT_00338180[param_1 * 2] & 8;
}



// Library Function - Single Match
//  _isalnum
// 
// Library: Visual Studio 2003 Release


int __cdecl _isalnum(int param_1)

{
  int iVar1;
  
  if (1 < DAT_00338188) {
    iVar1 = FUN_0016ae1f(param_1,0x107);
    return iVar1;
  }
  return *(ushort *)(PTR_DAT_00338180 + param_1 * 2) & 0x107;
}



// Library Function - Single Match
//  _wcsstr
// 
// Library: Visual Studio 2003 Release


wchar_t * __cdecl _wcsstr(wchar_t *__haystack,wchar_t *__needle)

{
  wchar_t wVar1;
  wchar_t *pwVar2;
  int iVar3;
  
  if (*__needle != L'\0') {
    wVar1 = *__haystack;
    if (wVar1 != L'\0') {
      iVar3 = (int)__haystack - (int)__needle;
      pwVar2 = __needle;
joined_r0x00166d1e:
      do {
        if (wVar1 != L'\0') {
          if (*pwVar2 == L'\0') {
            return __haystack;
          }
          if (*(wchar_t *)(iVar3 + (int)pwVar2) == *pwVar2) {
            wVar1 = *(wchar_t *)(iVar3 + (int)(pwVar2 + 1));
            pwVar2 = pwVar2 + 1;
            goto joined_r0x00166d1e;
          }
        }
        if (*pwVar2 == L'\0') {
          return __haystack;
        }
        __haystack = __haystack + 1;
        wVar1 = *__haystack;
        iVar3 = iVar3 + 2;
        pwVar2 = __needle;
      } while (wVar1 != L'\0');
    }
    __haystack = (wchar_t *)0x0;
  }
  return __haystack;
}



// WARNING: This is an inlined function
// WARNING: Unable to track spacebase fully for stack
// WARNING: Variable defined which should be unmapped: param_2
// Library Function - Single Match
//  __SEH_prolog
// 
// Library: Visual Studio

void __SEH_prolog(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  int *unaff_FS_OFFSET;
  undefined4 unaff_retaddr;
  undefined4 auStack_18 [4];
  undefined1 local_8 [8];
  
  iVar1 = -param_2;
  *(undefined4 *)((int)auStack_18 + iVar1 + 0xc) = param_3;
  *(undefined4 *)((int)auStack_18 + iVar1 + 8) = param_4;
  *(undefined4 *)((int)auStack_18 + iVar1 + 4) = param_5;
  *(undefined4 *)((int)auStack_18 + iVar1) = unaff_retaddr;
  *unaff_FS_OFFSET = (int)local_8;
  return;
}



// WARNING: This is an inlined function
// Library Function - Single Match
//  __SEH_epilog
// 
// Library: Visual Studio


int __cdecl _wcscmp(wchar_t *__s1,wchar_t *__s2)

{
  int iVar1;
  
  while( true ) {
    iVar1 = (uint)(ushort)*__s1 - (uint)(ushort)*__s2;
    if ((iVar1 != 0) || (*__s2 == L'\0')) break;
    __s1 = __s1 + 1;
    __s2 = __s2 + 1;
  }
  if (iVar1 < 0) {
    return -1;
  }
  if (0 < iVar1) {
    iVar1 = 1;
  }
  return iVar1;
}




int __cdecl _vswprintf(wchar_t *__s,size_t __n,wchar_t *__format,__gnuc_va_list __arg)

{
  int iVar1;
  wchar_t *local_24;
  int local_20;
  wchar_t *local_1c;
  undefined4 local_18;
  
  local_1c = __s;
  local_24 = __s;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = FUN_0016993d(&local_24,__n,__format);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    __flsbuf(0,&local_24);
  }
  else {
    *(undefined1 *)local_24 = 0;
    local_24 = (wchar_t *)((int)local_24 + 1);
  }
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    __flsbuf(0,&local_24);
  }
  else {
    *(undefined1 *)local_24 = 0;
  }
  return iVar1;
}



// Library Function - Single Match
//  __global_unwind2
// 
// Library: Visual Studio


int __cdecl _atexit(__func *__func)

{
  int iVar1;
  
  iVar1 = __onexit(__func);
  return (iVar1 != 0) - 1;
}




void * __cdecl _malloc(size_t __size)

{
  void *pvVar1;
  
  pvVar1 = (void *)__nh_malloc(__size,DAT_004dd2cc);
  return pvVar1;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


int __cdecl _iswspace(wint_t __wc)

{
  int iVar1;
  
  iVar1 = FUN_00166bf9(__wc,8);
  return iVar1;
}




int __cdecl _ungetc(int __c,FILE *__stream)

{
  int iVar1;
  
  __lock_file(__stream);
  iVar1 = __ungetc_lk(__c,__stream);
  FUN_0016f266();
  return iVar1;
}




void BigInitXBEFunction(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  FUN_001b0440(param_1,(int *)(&PTR_XBE_FILE_HEADER_002046a0 + param_4 * 0x40),(undefined1 *)param_1
               ,param_2,param_3);
  return;
}




undefined4 EnterCriticalSectionP(void)

{
  int unaff_FS_OFFSET;
  
  if (*(char *)(unaff_FS_OFFSET + 0x24) != '\0') {
    return 0;
  }
  RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  return 1;
}




_LIST_ENTRY * FUN_001c388c(PRTL_CRITICAL_SECTION param_1)

{
  LIST_ENTRY *pLVar1;
  _LIST_ENTRY *p_Var2;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  pLVar1 = &(param_1->Synchronization).Event.WaitListHead;
  pLVar1->Flink = (_LIST_ENTRY *)((int)&pLVar1->Flink->Flink + 1);
  p_Var2 = (param_1->Synchronization).Event.WaitListHead.Flink;
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return p_Var2;
}




undefined4 FUN_001c497a(PRTL_CRITICAL_SECTION param_1,_LIST_ENTRY *param_2,int param_3)

{
  _LIST_ENTRY **pp_Var1;
  _LIST_ENTRY *p_Var2;
  undefined4 uVar3;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  pp_Var1 = &param_1[0xc].Synchronization.Event.WaitListHead.Blink;
  p_Var2 = *pp_Var1;
  uVar3 = 0;
  param_1[2].Synchronization.RawEvent[3] = param_1[2].Synchronization.RawEvent[3] | 0x400000;
  param_1[4].RecursionCount = (LONG)param_2;
  for (; p_Var2 != (_LIST_ENTRY *)pp_Var1; p_Var2 = p_Var2->Flink) {
    p_Var2[-0x22].Flink = (_LIST_ENTRY *)((uint)p_Var2[-0x22].Flink | 0x400000);
    p_Var2[-0x1a].Flink = param_2;
  }
  if (param_3 == 0) {
    uVar3 = FUN_001c474b();
  }
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return uVar3;
}



undefined4

undefined4 __thiscall FUN_001c4bbf(PRTL_CRITICAL_SECTION param_1,_LIST_ENTRY *param_2,int param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  pbVar1 = (byte *)((int)&param_1[2].Synchronization + 0xe);
  *pbVar1 = *pbVar1 | 0x10;
  uVar2 = 0;
  param_1[4].Synchronization.Event.WaitListHead.Flink = param_2;
  if (param_3 == 0) {
    uVar2 = FUN_001c474b();
  }
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return uVar2;
}




undefined4 __thiscall FUN_001c4c48(PRTL_CRITICAL_SECTION param_1,_LIST_ENTRY *param_2,int param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  pbVar1 = (byte *)((int)&param_1[2].Synchronization + 0xe);
  *pbVar1 = *pbVar1 | 0x20;
  uVar2 = 0;
  param_1[4].Synchronization.Event.WaitListHead.Blink = param_2;
  if (param_3 == 0) {
    uVar2 = FUN_001c474b();
  }
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return uVar2;
}




FUN_001c4d5d(PRTL_CRITICAL_SECTION param_1,int param_2,_LIST_ENTRY *param_3,int param_4)

{
  byte *pbVar1;
  _LIST_ENTRY **pp_Var2;
  _LIST_ENTRY *p_Var3;
  float *pfVar4;
  undefined4 uVar5;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  uVar5 = 0;
  p_Var3 = (_LIST_ENTRY *)0x0;
  if (param_3 != (_LIST_ENTRY *)0x0) {
    pfVar4 = (float *)(param_1[10].Synchronization.RawEvent + 2);
    do {
      pp_Var2 = &p_Var3->Flink;
      p_Var3 = (_LIST_ENTRY *)((int)&p_Var3->Flink + 1);
      *pfVar4 = (float)*(byte *)((int)pp_Var2 + param_2) * 0.003921569;
      pfVar4 = pfVar4 + 1;
    } while (p_Var3 < param_3);
  }
  pbVar1 = (byte *)((int)&param_1[2].Synchronization + 0xf);
  *pbVar1 = *pbVar1 | 1;
  param_1[5].Synchronization.Event.WaitListHead.Flink =
       (_LIST_ENTRY *)((int)&param_1[10].Synchronization + 8);
  param_1[5].Synchronization.Event.WaitListHead.Blink = param_3;
  if (param_4 == 0) {
    uVar5 = FUN_001c474b();
  }
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return uVar5;
}



void FUN_001c4ddb(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,int param_7)

{
  DAT_001c5780 = DAT_001c5780 | 4;
  DAT_001c57a0 = param_1;
  DAT_001c57a4 = param_2;
  DAT_001c57a8 = param_3;
  DAT_001c57ac = param_4;
  DAT_001c57b0 = param_5;
  DAT_001c57b4 = param_6;
  if (param_7 == 0) {
    FUN_001c474b();
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 FUN_001c531e(PRTL_CRITICAL_SECTION param_1,_LIST_ENTRY *param_2,LONG param_3)

{
  undefined4 uVar1;
  
  FUN_001c3863((undefined1 *)((int)&param_1[4].Synchronization + 0xc));
  if (param_1[3].Synchronization.Event.WaitListHead.Flink == (_LIST_ENTRY *)0x2) {
    if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
      RtlLeaveCriticalSection(param_1);
    }
    uVar1 = 0;
  }
  else {
    FUN_001c52a7(0,0);
    (param_1->Synchronization).Event.WaitListHead.Flink = param_2;
    param_1->RecursionCount = param_3;
    uVar1 = FUN_001c5133();
    if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
      RtlLeaveCriticalSection(param_1);
    }
  }
  return uVar1;
}




