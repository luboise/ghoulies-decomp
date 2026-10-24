/* audio.c - Audio: XACT, X3DAudio, DirectSound, cues, wavebanks, rumble */
#include "audio.h"

BOOL GetAmbienceAudio__(actor *param_1)

{
  int index;
  
  if ((param_1->actorType == Human) || ((param_1->node0x93c).prev != (actor_0x93c)0x0)) {
    index = 1;
  }
  else {
    index = 0;
  }
  if (ShouldntDroneBools[index] != 0) {
    return 0;
  }
                    // Ambience audio?
  return (uint)(byte)"\x01"[Game::CheckMoveOn];
}




void setPlaycamScript(char *playcamScriptBnlName,char *prevScriptBnlName)

{
  int err;
  char *pcVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  undefined4 uVar2;
  char bnl_name [80];
  
  uVar2 = 0;
  err = Assets::aidToBNLName(bnl_name,playcamScriptBnlName);
  if (err == 0) {
    pcVar1 = _strchr(bnl_name,L'\\');
    *pcVar1 = '\0';
    __snprintf(g_snprintf_out_buf,0x102,"%s%s%s",runtime::RootDirectory,"bundles\\",bnl_name);
    _DAT_004deb58 = 0x5c3a5a;
    XAPILIB::lstrcpynA(g_lstrcpynA_out_buf,g_snprintf_out_buf + 3,0x100);
    Assets::HashBNLName(pcVar1 + 1);
    err = Assets::aidToBNLName(bnl_name,prevScriptBnlName);
    if (err == 0) {
      pcVar1 = _strchr(bnl_name,L'\\');
      *pcVar1 = '\0';
      Assets::HashBNLName(pcVar1 + 1);
      uVar2 = extraout_EAX_00;
    }
    runtime::OpenOrDeleteFolder(&DAT_004deb58,extraout_EAX,uVar2);
    runtime::loadObjparamsFromBundle(playcamScriptBnlName);
    runtime::loadObjparamsFromBundle(prevScriptBnlName);
  }
  return;
}




int IndexOfAssetInAIDList(ReplayChapterMenu **param_1,asset_name_t param_2)

{
  char *pcVar1;
  BOOL BVar2;
  ReplayChapterMenu *name1;
  int i;
  
  name1 = *param_1;
  if (name1 == (ReplayChapterMenu *)0x0) {
    return -1;
  }
  i = 0;
  do {
    BVar2 = Assets::AssetNamesMatch((char *)name1,param_2);
    if (BVar2 != 0) {
      return i;
    }
    pcVar1 = name1->someAID;
    name1 = (ReplayChapterMenu *)name1->someAID;
    i = i + 1;
    if (*(int *)pcVar1 != 0x5f646961) {
      name1 = (ReplayChapterMenu *)0x0;
    }
  } while (name1 != (ReplayChapterMenu *)0x0);
  return -1;
}




int XSoundbankResource::GetResourceSize(XSoundbankResource *res)

{
  ResourceReader *pRVar1;
  int *piVar2;
  Asset *head;
  int iVar3;
  uint32_t uVar4;
  
  head = Assets::LoadedResources->head;
  while( true ) {
    if (Assets::LoadedResources->tail <= head) {
      return 0;
    }
    if ((head->description != (AssetDescription *)0x0) &&
       (*(XSoundbankResource **)
         ((int)&g_resourceReaders->head->fileOffset +
         (int)((int)&head->description[-1].totalAllocSize + 3) * (uint)g_resourceReaders->valueSize)
        == res)) break;
    head = (Asset *)(head->name + Assets::LoadedResources->valueSize);
  }
  pRVar1 = g_resourceReaders->head;
  iVar3 = (int)((int)&head->description[-1].totalAllocSize + 3) * (uint)g_resourceReaders->valueSize
  ;
  uVar4 = *(uint32_t *)((int)&pRVar1->useCount + iVar3);
  piVar2 = *(int **)((int)&pRVar1->resOffset + iVar3);
  if (piVar2 != (int *)0x0) {
    uVar4 = uVar4 + *piVar2;
  }
  return *(uint32_t *)((int)&pRVar1->resSize + iVar3) + uVar4;
}




void XSoundbankResource::UpdateOffsets(int param_1,undefined4 param_2,astruct_32 *param_3)

{
  uint uVar1;
  int iVar2;
  uint unaff_EBX;
  astruct_32 *paVar3;
  
  if (param_3->field8_0x14 != (void *)0x0) {
    free(param_3->field8_0x14);
    param_3->field8_0x14 = (void *)0x0;
  }
  if (param_1 == 0) {
    param_1 = param_3->field6_0xc;
  }
  paVar3 = param_3;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    paVar3->field0_0x0 = 0;
    paVar3 = (astruct_32 *)&paVar3->field_0x4;
  }
  param_3->field7_0x10 = param_2;
  param_3->field9_0x18 = 0xffffffff;
  param_3->field10_0x1c = 0xffffffff;
  uVar1 = 0;
  param_3->field6_0xc = param_1;
  param_3->field5_0x8 = unaff_EBX;
  if (unaff_EBX != 0) {
    iVar2 = 0;
    do {
      *(short *)(param_3->field6_0xc + 10 + iVar2) = (short)uVar1;
      uVar1 = uVar1 + 1;
      iVar2 = iVar2 + 0x14;
    } while (uVar1 < unaff_EBX);
  }
  param_3->field19_0x28 = 0;
  return;
}




void __fastcall UpdateGameVolumes(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 extraout_EDX;
  float in_XMM0_Da;
  float fVar2;
  float fVar3;
  
  fVar2 = in_XMM0_Da * 127.0;
  fVar1 = 127.0;
  if ((127.0 < fVar2) || (fVar3 = fVar2, fVar1 = 0.0, fVar2 < 0.0)) {
    fVar3 = fVar1;
  }
  SetCategoryVolume(param_2,(WORD)DAT_004219ec,(int)fVar3);
  fVar1 = 127.0;
  if ((127.0 < fVar2) || (fVar3 = fVar2, fVar1 = 0.0, fVar2 < 0.0)) {
    fVar3 = fVar1;
  }
  SetCategoryVolume((int)fVar3,(WORD)DAT_004219f4,(int)fVar3);
  fVar1 = 127.0;
  if ((127.0 < fVar2) || (fVar3 = fVar2, fVar1 = 0.0, fVar2 < 0.0)) {
    fVar3 = fVar1;
  }
  SetCategoryVolume(DAT_00421a0c,(WORD)DAT_00421a0c,(int)fVar3);
  fVar1 = 127.0;
  if ((127.0 < fVar2) || (fVar3 = fVar2, fVar1 = 0.0, fVar2 < 0.0)) {
    fVar3 = fVar1;
  }
  SetCategoryVolume(extraout_EDX,(WORD)DAT_00421a14,(int)fVar3);
  fVar1 = 127.0;
  if ((127.0 < fVar2) || (fVar1 = 0.0, fVar2 < 0.0)) {
    fVar2 = fVar1;
  }
  SetCategoryVolume((int)fVar2,(WORD)DAT_00421a1c,(int)fVar2);
  return;
}




void WriteInto0x9C(int flags,AudioPlayingContext *param_2,char *name)

{
  char cVar1;
  int iVar2;
  BOOL BVar3;
  
  param_2->playFlags = flags;
  param_2->field45_0x94 = 0;
  param_2->numReferences = 1;
  BVar3 = strcmp(name,"XACT_SILENCE");
  param_2->field43_0x8c = BVar3;
  param_2->field44_0x90 = 0;
  param_2->field46_0x98 = 0;
  iVar2 = 4 - (int)name;
  do {
    cVar1 = *name;
    name[(int)param_2 + iVar2] = cVar1;
    name = name + 1;
  } while (cVar1 != '\0');
  return;
}




void FUN_00038260(AudioPlayingContext *param_1)

{
  audio_struct_1 *paVar1;
  int local_4;
  
  if ((param_1->field46_0x98 == 0) && (param_1->field43_0x8c == 0)) {
    paVar1 = FUN_00038b30(&local_4,param_1->someString);
    if (local_4 != 0) {
      FUN_00038cc0((int)&paVar1[-0x8ea7].field_0x48 / 0x8c);
    }
  }
  return;
}




void FUN_000382c0(AudioPlayingContext *param_1)

{
  char soundBankIndex;
  undefined1 local_4 [4];
  
  param_1->field44_0x90 = 1;
  if (param_1->field43_0x8c == 0) {
    soundBankIndex = FUN_00038d10(local_4);
    param_1->indexInSoundbank = soundBankIndex;
    if (soundBankIndex != -1) {
      Audio::UpdateSoundbankByIndex(soundBankIndex);
    }
  }
  return;
}




void AudioPlayingContext::updateSomething(AudioPlayingContext *param_1)

{
  audio_struct_1 *paVar1;
  int local_4;
  
  param_1->field45_0x94 = 0;
  if ((param_1->field43_0x8c == 0) && (param_1->field46_0x98 == 0)) {
    paVar1 = FUN_00038b30(&local_4,param_1->someString);
    if (local_4 != 0) {
      Audio::UpdateSoundbankByIndex((char)((int)&paVar1[-0x8ea7].field_0x48 / 0x8c));
    }
  }
  return;
}




AudioPlayingContext * Prepare0x9c(uint flags,char *name)

{
  AudioPlayingContext *pAVar1;
  int i;
  
  i = 0;
  pAVar1 = Audio::PlayingContexts;
  do {
    if (pAVar1->playFlags == 0) {
      WriteInto0x9C(flags,Audio::PlayingContexts + i,name);
      return Audio::PlayingContexts + i;
    }
    pAVar1 = pAVar1 + 1;
    i = i + 1;
  } while ((int)pAVar1 < 0x4dffa0);
  return (AudioPlayingContext *)0x0;
}




AudioPlayingContext * Audio::NextPlayingCtx(AudioPlayingContext *param_1)

{
  int start_i;
  GlobalAudioContext *pGVar1;
  
  start_i = (int)&param_1[-0x7fec].field_0x60 / 0x9c;
  pGVar1 = (GlobalAudioContext *)(PlayingContexts + start_i);
  do {
    pGVar1 = (GlobalAudioContext *)(pGVar1->LoadedNames[1] + 0x1c);
    start_i = start_i + 1;
    if (pGVar1 == &LoadedNames) {
      return (AudioPlayingContext *)0x0;
    }
  } while (*(uint *)pGVar1->LoadedNames[0] == 0);
  return PlayingContexts + start_i;
}




AudioPlayingContext * Audio::GetPlayingContext(char *name)

{
  char cVar2;
  int i;
  AudioPlayingContext *ctx;
  char *pcVar5;
  char cVar6;
  char cVar1;
  
  i = 0;
  ctx = PlayingContexts;
  do {
                    // If a context is loaded in that slot
    if (ctx->playFlags != 0) {
      ctx = PlayingContexts + i;
      if (ctx == (AudioPlayingContext *)0x0) {
        return (AudioPlayingContext *)0x0;
      }
      cVar1 = *name;
      while( true ) {
        cVar6 = ctx->someString[0];
        pcVar5 = ctx->someString;
        cVar2 = cVar1;
        if (cVar6 == cVar1) {
                    // If the name matches, return it
          i = (int)name - (int)pcVar5;
          do {
            pcVar5 = pcVar5 + 1;
            if (cVar6 == '\0') {
              return ctx;
            }
            cVar6 = *pcVar5;
            cVar2 = pcVar5[i];
          } while (cVar6 == cVar2);
        }
                    // This shouldn't happen
        if (cVar6 == cVar2) break;
                    // Skip empty slots
        ctx = NextPlayingCtx(ctx);
        if (ctx == (AudioPlayingContext *)0x0) {
          return (AudioPlayingContext *)0x0;
        }
      }
      return ctx;
    }
    ctx = ctx + 1;
    i = i + 1;
  } while ((int)ctx < 0x4dffa0);
  return (AudioPlayingContext *)0x0;
}




AudioPlayingContext * FUN_000384f0(void)

{
  int iVar1;
  AudioPlayingContext *pAVar2;
  uint unaff_ESI;
  
  iVar1 = 0;
  pAVar2 = Audio::PlayingContexts;
  while (pAVar2->playFlags == 0) {
    pAVar2 = pAVar2 + 1;
    iVar1 = iVar1 + 1;
    if (0x4dff9f < (int)pAVar2) {
      return (AudioPlayingContext *)0x0;
    }
  }
  pAVar2 = Audio::PlayingContexts + iVar1;
  while( true ) {
    if (pAVar2 == (AudioPlayingContext *)0x0) {
      return (AudioPlayingContext *)0x0;
    }
    if (pAVar2->playFlags == unaff_ESI) break;
    pAVar2 = Audio::NextPlayingCtx(pAVar2);
  }
  return pAVar2;
}




AudioPlayingContext * Audio::GetSomePlayingThing(AudioPlayingContext *param_1)

{
  uint uVar1;
  int iVar2;
  AudioPlayingContext *pAVar3;
  AudioPlayingContext *pAVar4;
  
  pAVar4 = (AudioPlayingContext *)0x0;
  iVar2 = 0;
  pAVar3 = PlayingContexts;
  do {
    if (pAVar3->playFlags != 0) {
      pAVar3 = PlayingContexts + iVar2;
      if (pAVar3 == (AudioPlayingContext *)0x0) {
        return (AudioPlayingContext *)0x0;
      }
      do {
        if ((pAVar3 != param_1) && (uVar1 = pAVar3->playFlags, uVar1 != 0x12)) {
          if ((int)param_1->playFlags < (int)uVar1) {
            return (AudioPlayingContext *)0x0;
          }
          if ((pAVar4 == (AudioPlayingContext *)0x0) || ((int)pAVar4->playFlags < (int)uVar1)) {
            pAVar4 = pAVar3;
          }
        }
        pAVar3 = NextPlayingCtx(pAVar3);
      } while (pAVar3 != (AudioPlayingContext *)0x0);
      return pAVar4;
    }
    pAVar3 = pAVar3 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)pAVar3 < 0x4dffa0);
  return (AudioPlayingContext *)0x0;
}




void Audio::ClearAudioContext(void)

{
  GlobalAudioContext *name;
  GlobalAudioContext_ptr_792_uint_6_ gac;
  
  gac = (GlobalAudioContext_ptr_792_uint_6_)LoadedNames.ChannelIndices;
  name = &LoadedNames;
  do {
    name->LoadedNames[0][0] = '\0';
    ADJ(gac)->IsPlayingFlags[0] = 0;
    ADJ(gac)->ChannelIndices[0] = 0xffffffff;
    name = (GlobalAudioContext *)(name->LoadedNames + 1);
    gac = (GlobalAudioContext_ptr_792_uint_6_)(ADJ(gac)->ChannelIndices + 1);
  } while ((int)name < 0x4e02a0);
  Loading = 0;
  return;
}



// Updates cutscene music


void Audio::ResolveFightingAudioChannels(void)

{
  AudioPlayingContext *playing_ctx;
  BOOL BVar1;
  int iVar2;
  uint i;
  GlobalAudioContext *audio_name;
  float fVar3;
  
  i = 0;
  audio_name = &LoadedNames;
  do {
    if (audio_name->LoadedNames[0][0] != '\0') {
      if (LoadedNames.IsPlayingFlags[i] == Playing) {
        playing_ctx = GetPlayingContext((char *)audio_name);
        if (playing_ctx == (AudioPlayingContext *)0x0) {
                    // 1 = Failed to load
          iVar2 = 1;
        }
        else if (playing_ctx->field43_0x8c == 0) {
          if ((playing_ctx->field46_0x98 == 0) && (playing_ctx->indexInSoundbank != -1)) {
            BVar1 = ChannelNeedsUpdate(playing_ctx->indexInSoundbank);
                    // Forcing the jump prevents zombie music playback
                    // 
                    // Preventing the jump stops challenge audio from playing
                    // 
                    // Both are important for coordinating audio semantics
            if (BVar1 == 0) goto LAB_0003869e;
          }
          iVar2 = 2;
        }
        else {
LAB_0003869e:
          iVar2 = 3;
        }
        if (iVar2 == 2) {
                    // Plays the zombie music, but NOT level intro music
          ClearSlot(i);
        }
        else if (iVar2 == 3) {
          fVar3 = LoadedNames.PlaybackHeadsSec[i] + runtime::DeltaTime;
          goto LAB_000386f7;
        }
      }
      else {
                    // Skipping this prevents the challenge event sound from playing, which makes
                    // sense
        if (Loading == 0) {
          PlayOrChangeByName(LoadedNames.ChannelIndices[i],(char *)audio_name);
          fVar3 = 0.0;
          LoadedNames.IsPlayingFlags[i] = Playing;
LAB_000386f7:
          LoadedNames.PlaybackHeadsSec[i] = fVar3;
        }
      }
    }
    audio_name = (GlobalAudioContext *)(audio_name->LoadedNames + 1);
    i = i + 1;
    if (0x4e029f < (int)audio_name) {
      return;
    }
  } while( true );
}




void Audio::loadAudioIntoEmptySlot(uint channelIndex,char *param_2)

{
  char cVar1;
  int iVar2;
  GlobalAudioContext *pGVar3;
  int i;
  
  i = 0;
  pGVar3 = &LoadedNames;
  do {
                    // If the slot is empty
    if (pGVar3->LoadedNames[0][0] == '\0') {
      iVar2 = i * 0x80 - (int)param_2;
                    // Load the data into the slot
      do {
        cVar1 = *param_2;
        param_2[(int)&LoadedNames + iVar2] = cVar1;
        param_2 = param_2 + 1;
      } while (cVar1 != '\0');
      LoadedNames.IsPlayingFlags[i] = JustLoaded;
      LoadedNames.ChannelIndices[i] = channelIndex;
      return;
    }
    pGVar3 = (GlobalAudioContext *)(pGVar3->LoadedNames + 1);
    i = i + 1;
  } while ((int)pGVar3 < 0x4e02a0);
  return;
}




void Audio::PlayOneOff(char *soundName)

{
  char cVar1;
  char c2;
  GlobalAudioContext *pGVar2;
  char *pcVar3;
  int iVar4;
  uint i;
  char c1;
  
  c1 = *soundName;
  pGVar2 = &LoadedNames;
  i = 0;
  iVar4 = (int)&LoadedNames - (int)soundName;
  while( true ) {
    c2 = pGVar2->LoadedNames[0][0];
    pcVar3 = soundName;
    cVar1 = c1;
    if (c1 == c2) {
      do {
        pcVar3 = pcVar3 + 1;
        if (cVar1 == '\0') goto LAB_000387f1;
        cVar1 = *pcVar3;
        c2 = pcVar3[iVar4];
      } while (cVar1 == c2);
    }
    if (cVar1 == c2) break;
    i = i + 1;
    pGVar2 = (GlobalAudioContext *)(pGVar2->LoadedNames + 1);
    iVar4 = iVar4 + 0x80;
    if (0x4e029f < (int)pGVar2) {
      return;
    }
  }
LAB_000387f1:
                    // After loading it, calls this
  ClearSlot(i);
  return;
}




void Audio::ClearSlot(uint index)

{
  AudioPlayingContext *pAVar1;
  AudioPlayingContext *pAVar2;
  int iVar3;
  
  LoadedNames.ChannelIndices[index] = 0xffffffff;
  if (LoadedNames.IsPlayingFlags[index] == Playing) {
    pAVar1 = GetPlayingContext(LoadedNames.LoadedNames[index]);
    iVar3 = pAVar1->numReferences + -1;
    pAVar1->numReferences = iVar3;
    if (iVar3 < 1) {
      if ((pAVar1->playFlags != 0x12) &&
         (pAVar2 = GetSomePlayingThing(pAVar1), pAVar2 != (AudioPlayingContext *)0x0)) {
                    // Starts playing zombie music
                    // 
                    // Also resumes regular music
        AudioPlayingContext::updateSomething(pAVar2);
      }
      FUN_00038260(pAVar1);
      pAVar1->playFlags = 0;
    }
  }
  LoadedNames.LoadedNames[index][0] = '\0';
  return;
}




void Audio::PlayOrChangeByName(uint flags,char *param_2)

{
  AudioPlayingContext *music;
  AudioPlayingContext *some_song;
  int iVar1;
  
  music = GetPlayingContext(param_2);
  if (music != (AudioPlayingContext *)0x0) {
    music->numReferences = music->numReferences + 1;
    return;
  }
  some_song = (AudioPlayingContext *)Prepare0x9c(flags,param_2);
  if (some_song->playFlags == 0x12) {
    FUN_000382c0(some_song);
    return;
  }
  iVar1 = FUN_00038530();
  if (iVar1 != 0) {
    FUN_00038ad0();
    FUN_000382c0(some_song);
    return;
  }
  FUN_000382c0(some_song);
  FUN_00038300();
  return;
}




void PlayCutsceneMusic(char *param_1)

{
  AudioPlayingContext *pAVar1;
  AudioPlayingContext *pAVar2;
  int iVar3;
  
  pAVar1 = Audio::GetPlayingContext(param_1);
  iVar3 = pAVar1->numReferences + -1;
  pAVar1->numReferences = iVar3;
  if (iVar3 < 1) {
    if (pAVar1->playFlags != 0x12) {
      pAVar2 = Audio::GetSomePlayingThing(pAVar1);
      if (pAVar2 != (AudioPlayingContext *)0x0) {
        AudioPlayingContext::updateSomething(pAVar2);
      }
    }
    FUN_00038260(pAVar1);
    pAVar1->playFlags = 0;
  }
  return;
}




audio_struct_1 * FUN_00038b30(BOOL *outBool,char *param_2)

{
  audio_struct_1 *source;
  char cVar1;
  SoundSourceRegistrationDetails **ppSVar2;
  char cVar3;
  audio_struct_1 *paVar4;
  audio_struct_1 *paVar5;
  char *pcVar6;
  
  source = g_AudioSources;
  pcVar6 = param_2 + -0x4e030e;
  paVar4 = (audio_struct_1 *)0x0;
  do {
    paVar5 = source;
    if (source->parentIndex != 0xffff) {
      cVar1 = *(char *)&source->field1_0x2;
      cVar3 = *param_2;
      ppSVar2 = &source->field1_0x2;
      if (cVar1 == cVar3) {
        do {
          ppSVar2 = (SoundSourceRegistrationDetails **)((int)ppSVar2 + 1);
          if (cVar1 == '\0') goto LAB_00038b70;
          cVar1 = *(char *)ppSVar2;
          cVar3 = pcVar6[(int)ppSVar2];
        } while (cVar1 == cVar3);
      }
      paVar5 = paVar4;
      if (cVar1 == cVar3) {
LAB_00038b70:
        *outBool = 1;
        return source;
      }
    }
    source = source + 1;
    pcVar6 = pcVar6 + -0x8c;
    paVar4 = paVar5;
    if (0x4e0bcb < (int)source) {
      *outBool = 0;
      return paVar5;
    }
  } while( true );
}




void __fastcall FUN_00038bb0(AudioParentState param_1)

{
  short *unaff_ESI;
  
  *(undefined1 *)(unaff_ESI + 1) = 0;
  if (*unaff_ESI != -1) {
    AudioParent::UpdateState(0,Audio::SoundSources + *unaff_ESI,param_1);
    *unaff_ESI = -1;
    unaff_ESI[0x42] = 0;
    unaff_ESI[0x43] = 0;
  }
  unaff_ESI[0x44] = 0;
  unaff_ESI[0x45] = 0;
  return;
}




void __thiscall FUN_00038cc0(AudioParentState param_1,char param_2)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = (int)param_2;
  uVar1 = g_AudioSources[iVar2].parentIndex;
  *(undefined1 *)&g_AudioSources[iVar2].field1_0x2 = 0;
  if (uVar1 != 0xffff) {
    AudioParent::UpdateState(0,Audio::SoundSources + (short)uVar1,param_1);
    g_AudioSources[iVar2].parentIndex = 0xffff;
    g_AudioSources[iVar2].soundSourceState = 0;
  }
  g_AudioSources[iVar2].next_ = 0;
  return;
}




void Audio::UpdateSoundbankByIndex(char soundBankIndex)

{
  SoundSourceImpl *pSVar1;
  ushort uVar2;
  IXACT_Cue *cue;
  int bank_index;
  
  bank_index = (int)soundBankIndex;
  if (g_AudioSources[bank_index].soundSourceState == 1) {
    FindBySoundbankStrAndPlay
              ((char *)&g_AudioSources[bank_index].field1_0x2,g_AudioSources[bank_index].parentIndex
              );
  }
  else if ((g_AudioSources[bank_index].soundSourceState == 3) &&
          (uVar2 = g_AudioSources[bank_index].parentIndex, uVar2 != 0xffff)) {
    cue = SoundSources[(short)uVar2].cue;
    pSVar1 = SoundSources + (short)uVar2;
    if (cue != (IXACT_Cue *)0x0) {
      switch(pSVar1->state) {
      case ShouldGoTo4_2:
        g_AudioSources[bank_index].soundSourceState = 2;
        pSVar1->state = ShouldGoTo4_1;
        return;
      case ShouldPause1:
      case ShouldPause2:
      case ShouldPause3:
        pSVar1->state = ShouldPause2;
        audioSoundBankPauseCue(cue,0);
        g_AudioSources[bank_index].soundSourceState = 2;
        return;
      }
    }
  }
  g_AudioSources[bank_index].soundSourceState = 2;
  return;
}




void Audio::UpdateAudioSourceState(char index_char)

{
  SoundSourceImpl *pSVar1;
  IXACT_Cue *cue;
  int index;
  
  index = (int)index_char;
  if (g_AudioSources[index].soundSourceState != 1) {
    if (g_AudioSources[index].soundSourceState == 2) {
      cue = SoundSources[(short)g_AudioSources[index].parentIndex].cue;
      pSVar1 = SoundSources + (short)g_AudioSources[index].parentIndex;
      if (cue != (IXACT_Cue *)0x0) {
        switch(pSVar1->state) {
        case ShouldGoTo4_1:
          g_AudioSources[index].soundSourceState = 3;
          pSVar1->state = ShouldGoTo4_2;
          return;
        case ShouldPause1:
        case ShouldPause2:
        case ShouldPause3:
                    // State 5/6/7 all lead to pause
          pSVar1->state = ShouldPause3;
          audioSoundBankPauseCue(cue,1);
        }
      }
    }
    g_AudioSources[index].soundSourceState = 3;
  }
  return;
}




BOOL Audio::ChannelNeedsUpdate(char param_1)

{
  AudioParentState AVar1;
  
  if (g_AudioSources[param_1].soundSourceState == 3) {
    return 0;
  }
  if ((SoundSources[(short)g_AudioSources[param_1].parentIndex].cue != (IXACT_Cue *)0x0) &&
     ((((AVar1 = SoundSources[(short)g_AudioSources[param_1].parentIndex].state,
        AVar1 == ShouldGoTo4_1 || (AVar1 == ShouldGoTo4_2)) || (AVar1 == ShouldPause1)) ||
      ((AVar1 == ShouldPause2 || (AVar1 == ShouldPause3)))))) {
    return 0;
  }
  return 1;
}



BOOL Audio::FileReadCallback
               (HANDLE param_1,LPVOID param_2,DWORD param_3,LPDWORD param_4,LPOVERLAPPED param_5)

{
  BOOL BVar1;
  int unaff_FS_OFFSET;
  
  BVar1 = XAPILIB::ReadFile(param_1,param_2,param_3,param_4,param_5);
  if (BVar1 == 0) {
    XAPILIB::GetLastError(unaff_FS_OFFSET);
  }
  return BVar1;
}




BOOL Audio::WaitForIOCallback(HANDLE param_1,LPOVERLAPPED param_2,LPDWORD param_3,BOOL param_4)

{
  BOOL BVar1;
  char *exitCode;
  int unaff_FS_OFFSET;
  
  BVar1 = XAPILIB::GetOverlappedResult(param_1,param_2,param_3,param_4);
  if (BVar1 == 0) {
    exitCode = XAPILIB::GetLastError(unaff_FS_OFFSET);
    if (((int)exitCode < 0x3e4) || (0x3e5 < (int)exitCode)) {
      runtime::ExitGame((int)exitCode);
    }
  }
  return BVar1;
}




char * AddSoundbankLine(int *param_1,int param_2)

{
  char *pcVar1;
  int line;
  
  pcVar1 = Audio::CurrentSoundbankLine;
  if (AllocSize <= (uint)(DAT_004e0cd4 + param_2)) {
    AllocSize = AllocSize + 0x80 + param_2;
    Audio::CurrentSoundbankLine = AllocateMoreAStruct_33(AllocSize,Audio::CurrentSoundbankLine);
    if (pcVar1 != Audio::CurrentSoundbankLine) {
      line = (int)Audio::CurrentSoundbankLine - (int)pcVar1;
      if (param_1 != (int *)0x0) {
        *param_1 = *param_1 + line;
      }
      FUN_00038fe0(line);
    }
  }
  line = DAT_004e0cd4;
  DAT_004e0cd4 = DAT_004e0cd4 + param_2;
  return Audio::CurrentSoundbankLine + line;
}




void Audio::NewSoundbankFromLine(char *soundbankName)

{
  char cVar1;
  int iVar2;
  char *bankend;
  SoundbankNode *node;
  bool linked_list_exists;
  char *existing_line_start;
  SoundbankNode *list_end;
  SoundbankNode *list_tail;
  
  existing_line_start = CurrentSoundbankLine;
  bankend = soundbankName;
  do {
    cVar1 = *bankend;
    bankend = bankend + 1;
  } while (cVar1 != '\0');
  iVar2 = -(int)(soundbankName + 1) + 0xd;
  if (AllocSize <= bankend + (int)DAT_004e0cd4 + iVar2) {
    AllocSize = bankend + (int)(AllocSize + -(int)(soundbankName + 1) + 0x8d);
    CurrentSoundbankLine = AllocateMoreAStruct_33((uint)AllocSize,CurrentSoundbankLine);
    if (existing_line_start != CurrentSoundbankLine) {
      FUN_00038fe0((int)CurrentSoundbankLine - (int)existing_line_start);
    }
  }
  node = (SoundbankNode *)(CurrentSoundbankLine + (int)DAT_004e0cd4);
  DAT_004e0cd4 = bankend + (int)DAT_004e0cd4 + iVar2;
  iVar2 = 0xc - (int)soundbankName;
  do {
    cVar1 = *soundbankName;
    soundbankName[(int)node + iVar2] = cVar1;
    list_tail = XActSoundbankLookupTable;
    soundbankName = soundbankName + 1;
  } while (cVar1 != '\0');
  linked_list_exists = XActSoundbankLookupTable != (SoundbankNode *)0x0;
  node->next = (SoundbankNode *)0x0;
  node->entries = (SoundbankEntryNode *)0x0;
  if (linked_list_exists) {
    list_end = list_tail->next;
    while (list_end != (SoundbankNode *)0x0) {
      list_tail = list_tail->next;
      list_end = list_tail->next;
    }
    list_tail->next = node;
    return;
  }
  XActSoundbankLookupTable = node;
  return;
}




Audio::SearchSoundBankByName(char *audio_name,SoundbankNode *soundbank,uint *indexOut)

{
  byte bVar1;
  byte bVar2;
  char *pcVar3;
  int iVar4;
  uint i;
  SoundbankEntryNode *entry;
  
  entry = soundbank->entries;
  i = 0;
  while( true ) {
    if (entry == (SoundbankEntryNode *)0x0) {
      return (SoundbankEntryNode *)0x0;
    }
                    // eg. angry
    pcVar3 = entry->name;
    iVar4 = (int)audio_name - (int)pcVar3;
    while( true ) {
      bVar1 = *pcVar3;
      if (0x20 < bVar1) {
        bVar1 = bVar1 & 0xdf;
      }
      bVar2 = pcVar3[iVar4];
      if (0x20 < bVar2) {
        bVar2 = bVar2 & 0xdf;
      }
      if (bVar1 != bVar2) break;
      pcVar3 = pcVar3 + 1;
      if (bVar1 == 0) goto LAB_0003922a;
    }
    if (bVar1 == bVar2) break;
    entry = entry->next;
    i = i + 1;
  }
LAB_0003922a:
  *indexOut = i;
  return entry;
}



// eg. soundbankName = GENVIRONMENT


SoundbankNode * Audio::QuerySoundBankByName(char *soundbankName,uint *bankIndexOut)

{
  char c2;
  int mask;
  uint i;
  char *name;
  int offset;
  SoundbankNode *lut;
  char *pcVar1;
  
  i = 0;
  lut = XActSoundbankLookupTable;
  while( true ) {
    if (lut == (SoundbankNode *)0x0) {
      return (SoundbankNode *)0x0;
    }
    name = lut->name;
    mask = uVar3;
    offset = (int)soundbankName - (int)name;
    while( true ) {
      pcVar1 = name + offset;
      c2 = *name & 0b11011111;
      name = name + 1;
      if (c2 != (*pcVar1 & 0b11011111U)) break;
      if ((c2 == '\0') || (mask = mask + -1, mask == 0)) goto LAB_00039297;
    }
    if (c2 == (*pcVar1 & 0b11011111U)) break;
    lut = lut->next;
    i = i + 1;
  }
LAB_00039297:
  *bankIndexOut = i;
  return lut;
}




void Audio::LoadCueList(char *cueListAID)

{
  int size;
  char *line;
  uint uVar1;
  undefined4 extraout_EAX;
  char *entry;
  CueListResource *res;
  CueListResource *cue_list_res;
  char c;
  char *next_char;
  char *soundbank_name;
  
  if (*(int *)cueListAID == 0x5f646961) {
    Assets::GetResourceBytes(cueListAID,&cue_list_res);
    res = cue_list_res;
    if (cue_list_res == (CueListResource *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    res = (CueListResource *)0x0;
  }
  size = XSoundbankResource::GetResourceSize((XSoundbankResource *)res);
  cue_list_res = res;
  line = GetNextNonEmptyLine((char **)&cue_list_res,(int)res,size);
  CurrentGroup = (char *)0x0;
  soundbank_name = CurrentGroup;
  while (CurrentGroup = soundbank_name, line != (char *)0x0) {
    c = *line;
    entry = line;
    while (c != '\t') {
      next_char = entry + 1;
      entry = entry + 1;
      c = *next_char;
    }
                    // Replace tab with \x00
    *entry = '\0';
                    // If CurrentSoundBankName is bad, or different
                    // 
                    // When we go from Gpirate to Gboy, update it
    if ((soundbank_name == (char *)0x0) || (uVar1 = strcasecmp(line,soundbank_name), uVar1 != 0)) {
      NewSoundbankFromLine(line);
      CurrentGroup = line;
      SoundbankEntries = extraout_EAX;
    }
    addEntryToLinkedList(SoundbankEntries,entry + 1);
                    // Get next cue???
    line = GetNextNonEmptyLine((char **)&cue_list_res,(int)res,size);
    soundbank_name = CurrentGroup;
  }
  Assets::DestroyAssetOrDecrement(res);
                    // Load the soundbank?
  FUN_00035c60(res);
  soundbank_name = CurrentSoundbankLine;
  if (DAT_004e0cd4 < AllocSize) {
    CurrentSoundbankLine = AllocateMoreAStruct_33(DAT_004e0cd4,CurrentSoundbankLine);
    AllocSize = DAT_004e0cd4;
    if (soundbank_name != CurrentSoundbankLine) {
      FUN_00038fe0((int)CurrentSoundbankLine - (int)soundbank_name);
    }
  }
  return;
}




BOOL Audio::QueryAudioByXACTName(char *audioStr,uint *bankIndexOut,uint *cueIndexOut)

{
  char *pcVar1;
  char *search_ptr;
  SoundbankNode *bank_node;
  SoundbankEntryNode *entry_node;
  char *id1;
  char *str2;
  uint bank_index;
  uint entry_index;
  char c;
  
                    // Start at       \/ HERE
                    // XACT_SOUNDBANK_
  search_ptr = audioStr + 0xf;
  id1 = CurrentAudioId;
  str2 = g_CurrentAudioName;
  c = audioStr[0xf];
  while (c != '_') {
    *id1 = c;
    pcVar1 = search_ptr + 1;
    id1 = id1 + 1;
    search_ptr = search_ptr + 1;
    c = *pcVar1;
  }
  search_ptr = search_ptr + 1;
  *id1 = '\0';
  c = *search_ptr;
  while (c != '\0') {
    *str2 = c;
    id1 = search_ptr + 1;
    str2 = str2 + 1;
    search_ptr = search_ptr + 1;
    c = *id1;
  }
  *str2 = '\0';
  bank_node = QuerySoundBankByName(CurrentAudioId,&bank_index);
  if ((bank_node != (SoundbankNode *)0x0) &&
     (entry_node = SearchSoundBankByName(g_CurrentAudioName,bank_node,&entry_index),
     entry_node != (SoundbankEntryNode *)0x0)) {
    if (bankIndexOut != (uint *)0x0) {
      *bankIndexOut = bank_index;
    }
    if (cueIndexOut != (uint *)0x0) {
      *cueIndexOut = entry_index;
    }
    return 1;
  }
  return 0;
}




ushort Audio::Play(char *audioStr,uint flags,uint param_3,float f1)

{
  ushort parentIndex;
  
  if (f1 == 0.0) {
    f1 = 5.0;
  }
  parentIndex = CreateSoundSourceAndReturnIndex(AudioType1);
  if (parentIndex != 0xffff) {
    SoundSources[(short)parentIndex].flags = flags;
    AudioParent::SetPositionWithScale(parentIndex,f1);
    FindBySoundbankStrAndPlay(audioStr,parentIndex);
  }
  return parentIndex;
}




undefined4 Audio::PlaySoundWithFlags(char *param_1,uint flags)

{
  i16 soundSourceIndex;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar1;
  
  soundSourceIndex = CreateSoundSourceAndReturnIndex(AudioType0);
  uVar1 = extraout_var;
  if (soundSourceIndex != -1) {
    SoundSources[soundSourceIndex].flags = flags;
    FindBySoundbankStrAndPlay(param_1,soundSourceIndex);
    uVar1 = extraout_var_00;
  }
  return CONCAT22(uVar1,soundSourceIndex);
}



// WARNING: Inlined function: setI3DL2


void Audio::Seti3dl2forSoundSource(soundSource *player)

{
  float fVar1;
  long lVar2;
  long lVar3;
  float fVar4;
  
  fVar4 = BaseLevelRatio[0].ratio;
  lVar3 = BaseLevelRatio[0].level;
  fVar1 = BaseLevelRatio[GlobalObstructionOffset].ratio;
  lVar2 = BaseLevelRatio[GlobalObstructionOffset].level;
  (player->params->dsi3dl2).lDirect = 0;
  (player->params->dsi3dl2).lDirectHF = 0;
  (player->params->dsi3dl2).lRoom = 0;
  (player->params->dsi3dl2).lRoomHF = 0;
  (player->params->dsi3dl2).flRoomRolloffFactor = 0.0;
  (player->params->dsi3dl2).Obstruction.lHFLevel = lVar2;
  (player->params->dsi3dl2).Obstruction.flLFRatio = fVar1;
  (player->params->dsi3dl2).Occlusion.lHFLevel = lVar3;
  (player->params->dsi3dl2).Occlusion.flLFRatio = fVar4;
  XACT::IXACTSoundSource_SetI3DL2Source
            (player->xactSoundSource,&player->params->dsi3dl2,deferSettings_);
  player->params->field_0x24 = 1;
  return;
}




void AudioPlayerParent::free(SoundSourceImpl *param_1)

{
  if ((param_1->state != Free) &&
     ((param_1->soundSource == (soundSource *)0x0 ||
      (AudioPlayerContext::free(&param_1->soundSource), param_1->soundSource == (soundSource *)0x0))
     )) {
    param_1->state = Free;
  }
  return;
}




int AudioParent::UpdateState(BOOL param_1,SoundSourceImpl *src,AudioParentState param_3)

{
  int iVar1;
  
  if (src->cue == (IXACT_Cue *)0x0) {
    src->state = Finished;
  }
  else {
    param_3 = src->state - ShouldGoTo4_1;
    switch(param_3) {
    case Free:
    case Loaded:
      src->state = State4;
      return param_3;
    case ShouldGoTo4_2:
    case State4:
    case ShouldPause1:
      src->state = Paused;
      iVar1 = IXACT_Cue::stop(src->cue,param_1);
      return iVar1;
    }
  }
  return param_3;
}



// WARNING: Inlined function: setI3DL2


void Audio::UpdatePlayerContexts(void)

{
  float fVar1;
  long lVar2;
  soundSource *psVar3;
  long lVar4;
  float fVar5;
  AudioPlayerParent_ptr_28_AudioPlayerContext__ ppAVar3;
  vec3 local_c;
  AudioParentState state;
  
                    // Update context positions
  ppAVar3 = &SoundSources[0].soundSource;
  do {
    state = ADJ(ppAVar3).state;
    if (state == ShouldPause2) {
      if (ADJ(ppAVar3)->sourceType == AudioType1) {
        SetSoundConeOrientation(ADJ(ppAVar3)->soundSource,&SoundConeOrientation);
        fVar5 = BaseLevelRatio[0].ratio;
        lVar4 = BaseLevelRatio[0].level;
        fVar1 = BaseLevelRatio[GlobalObstructionOffset].ratio;
        lVar2 = BaseLevelRatio[GlobalObstructionOffset].level;
        psVar3 = ADJ(ppAVar3)->soundSource;
        (psVar3->params->dsi3dl2).lDirect = 0;
        (psVar3->params->dsi3dl2).lDirectHF = 0;
        (psVar3->params->dsi3dl2).lRoom = 0;
        (psVar3->params->dsi3dl2).lRoomHF = 0;
        (psVar3->params->dsi3dl2).flRoomRolloffFactor = 0.0;
        (psVar3->params->dsi3dl2).Obstruction.lHFLevel = lVar2;
        (psVar3->params->dsi3dl2).Obstruction.flLFRatio = fVar1;
        (psVar3->params->dsi3dl2).Occlusion.lHFLevel = lVar4;
        (psVar3->params->dsi3dl2).Occlusion.flLFRatio = fVar5;
        XACT::IXACTSoundSource_SetI3DL2Source
                  (psVar3->xactSoundSource,&psVar3->params->dsi3dl2,deferSettings_);
        psVar3->params->field_0x24 = 1;
        if (ADJ(ppAVar3)->someu32 != 0) {
          fVar1 = *(float *)&ADJ(ppAVar3)->field_0x14;
          local_c.x = (Graphics::CurrentCameraStruct->forwards).x * fVar1 +
                      (Graphics::CurrentCameraStruct->pos).x;
          local_c.y = (Graphics::CurrentCameraStruct->forwards).y * fVar1 +
                      (Graphics::CurrentCameraStruct->pos).y;
          local_c.z = (Graphics::CurrentCameraStruct->forwards).z * fVar1 +
                      (Graphics::CurrentCameraStruct->pos).z;
          SetSoundSourcePosition(ADJ(ppAVar3)->soundSource,&local_c);
        }
      }
    }
    else if (state == State8) {
      if (ADJ(ppAVar3)->flags != 0) goto LAB_00039718;
    }
    else {
                    // Free the bad ones
      if (state == Finished) {
LAB_00039718:
        if ((state != Free) &&
           ((ADJ(ppAVar3)->soundSource == (soundSource *)0x0 ||
            (AudioPlayerContext::free(ppAVar3), ADJ(ppAVar3)->soundSource == (soundSource *)0x0))))
        {
          ADJ(ppAVar3).state = Free;
        }
      }
    }
    ppAVar3 = ppAVar3 + 9;
    if (0x4e13c3 < (int)ppAVar3) {
      return;
    }
  } while( true );
}




i16 Audio::CreateSoundSourceAndReturnIndex(AudioSourceType sourceType)

{
  SoundSourceImpl *parent;
  undefined1 *puVar1;
  soundSource **piVar1;
  soundSource **source;
  
  parent = SoundSources;
  do {
                    // Find the first free sound source
    if (parent->state == Free) {
      source = &parent->soundSource;
      parent->state = Free;
      parent->flags = 0;
      parent->someu32 = 0;
      soundSource::ctor(sourceType,source);
      if (*source == (soundSource *)0x0) {
        AudioPlayerParent::free(parent);
        return -1;
      }
      parent->sourceType = sourceType;
      if (sourceType == AudioType1) {
        SetSoundSourcePosition(*source,&Game::someGlobalPos);
        SetSoundSourceVelocity(*source,&Game::someGlobalPos);
        SetSoundConeOrientation(*source,&SoundConeOrientation);
        Seti3dl2forSoundSource(*source);
      }
      parent->state = Loaded;
      puVar1 = &parent[-0x22b07].field_0x14;
      return ((short)((int)puVar1 / 0x24) + (short)((int)puVar1 >> 0x1f)) -
             (short)((longlong)(int)puVar1 * 0x38e38e39 >> 0x3f);
    }
    parent = parent + 1;
  } while ((int)parent < 0x4e13a8);
  return -1;
}




void __fastcall UpdatePlayStatus(SoundSourceImpl *src,int param_2)

{
  SoundSourceImpl *pSVar1;
  AudioParentState AVar2;
  IXACT_Cue *cue;
  short sVar3;
  AudioParentState extraout_ECX;
  undefined1 *puVar4;
  
  if (param_2 == 0) {
    src->state = ShouldPause2;
  }
  else if (param_2 == 1) {
    if (src->cue != (IXACT_Cue *)0x0) {
      IXACT_Cue::free(&src->cue);
    }
    switch(src->state) {
    case ShouldGoTo4_1:
    case ShouldGoTo4_2:
    case ShouldPause1:
    case ShouldPause2:
    case ShouldPause3:
      src->state = State8;
      return;
    case Paused:
      src->state = Finished;
      return;
    }
  }
  else if (param_2 == 3) {
    PlayCue(src->cue);
    AVar2 = src->state;
    src->state = ShouldPause1;
    if (AVar2 == ShouldGoTo4_2) {
      puVar4 = &src[-0x22b07].field_0x14;
      sVar3 = ((short)((int)puVar4 / 0x24) + (short)((int)puVar4 >> 0x1f)) -
              (short)((longlong)(int)puVar4 * 0x38e38e39 >> 0x3f);
      cue = Audio::SoundSources[sVar3].cue;
      pSVar1 = Audio::SoundSources + sVar3;
      if (cue != (IXACT_Cue *)0x0) {
        switch(pSVar1->state) {
        case ShouldGoTo4_1:
          pSVar1->state = ShouldGoTo4_2;
          return;
        case ShouldPause1:
        case ShouldPause2:
        case ShouldPause3:
          pSVar1->state = ShouldPause3;
          audioSoundBankPauseCue(cue,1);
          return;
        }
      }
    }
    else if (AVar2 == State4) {
      AudioParent::UpdateState(1,src,extraout_ECX);
      return;
    }
  }
  return;
}




undefined4 Audio::CuePlaybackCallback(IXACT_Cue *cue,u32 param_2)

{
  SoundSourceImpl *src;
  
  src = (SoundSourceImpl *)audioCue::get0x14(cue);
  UpdatePlayStatus(src,param_2);
  return 0;
}



// WARNING: Inlined function: SetMallocStructInner
// This might actually be setting an asset based on the global sound banks?


bool Audio::FindBySoundbankStrAndPlay(char *audioStr,short soundSourceIndex)

{
  int sourceIndex;
  BOOL found;
  uint sourceSourceImpl;
  uint soundBank;
  IXACT_Cue *cue;
  SoundSourceImpl *inner;
  IXACT_Cue **pp_ixact_cue;
  SoundSourceImpl *source;
  
  sourceIndex = (int)soundSourceIndex;
  source = SoundSources + sourceIndex;
  found = QueryAudioByXACTName(audioStr,&soundBank,&sourceSourceImpl);
  if (found != 0) {
    pp_ixact_cue = &SoundSources[sourceIndex].cue;
    audioSoundBankGetCue
              (Soundbanks[soundBank],sourceSourceImpl,SoundSources[sourceIndex].soundSource,
               pp_ixact_cue,CuePlaybackCallback,pp_ixact_cue);
    if (*pp_ixact_cue != (IXACT_Cue *)0x0) {
      (*pp_ixact_cue)->soundSourceImpl = source;
      source->state = ShouldGoTo4_1;
      return true;
    }
    source->state = State8;
  }
  return false;
}




void AudioParent::SetPositionWithScale(ushort parentIndex,float audioScale)

{
  soundSource *source;
  vec3 local_c;
  
  source = Audio::SoundSources[(short)parentIndex].soundSource;
  if (source != (soundSource *)0x0) {
    *(float *)&Audio::SoundSources[(short)parentIndex].field_0x14 = audioScale;
    Audio::SoundSources[(short)parentIndex].someu32 = 1;
    local_c.x = (Graphics::CurrentCameraStruct->forwards).x * audioScale +
                (Graphics::CurrentCameraStruct->pos).x;
    local_c.y = (Graphics::CurrentCameraStruct->forwards).y * audioScale +
                (Graphics::CurrentCameraStruct->pos).y;
    local_c.z = (Graphics::CurrentCameraStruct->forwards).z * audioScale +
                (Graphics::CurrentCameraStruct->pos).z;
    Audio::SetSoundSourcePosition(source,&local_c);
  }
  return;
}




void Audio::LoadWavebanks(char *param_1,char *param_2)

{
  BOOL has_flag;
  uint err;
  char *error;
  uint hashed;
  int puVar1;
  int iVar1;
  char *name_start;
  WavebankDrive *resMeta;
  int unaff_FS_OFFSET;
  asset_name name;
  asset_name filepath;
  byte c;
  
  puVar1 = (int)&g_someCacheContextPtr;
  resMeta = WavebankDrives;
  iVar1 = 0xc;
  do {
    Utils::SprintfToUpper(name,"aid_xwavebank_%s_%s","ghoulies",resMeta->name,param_2,param_1);
    hashed = 0;
    name_start = name + 4;
    c = name[4];
    while (c != 0) {
      hashed = (c & 0xdf) + hashed * 0x10;
      name_start = name_start + 1;
      has_flag = hashed & 0xf0000000;
      if (has_flag != 0) {
        hashed = hashed ^ ((uint)has_flag >> 24 | has_flag);
      }
      c = *name_start;
    }
    _sprintf(filepath,"%s%s%08x",runtime::RootDirectory,"xwavebank\\",hashed);
    err = QueryFile(filepath);
    if (err == 0xffffffff) {
      error = XAPILIB::GetLastError(unaff_FS_OFFSET);
    }
    else {
      error = (char *)(-(uint)((err & 0x10) != 0) & 267);
    }
    if (error == (char *)0x0) {
      if (resMeta->loadType == 1) {
        LoadWavebanksInner(resMeta,filepath,(CacheContext *)puVar1);
      }
      else if (resMeta->loadType == 2) {
        CreateStreamedWaveBankAtFileOffset
                  (filepath,0,(HANDLE)0x0,0,(XACTSoundbank *)0x2,
                   &((CacheContext *)puVar1)->nextCache,resMeta->field1_0x4,resMeta->field2_0x8,
                   (undefined *)0x0,(HANDLE)0x0);
      }
    }
    resMeta = resMeta + 1;
    puVar1 = (int)&((CacheContext *)puVar1)->cache2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}




void Audio::RunTestAudio(void)

{
  int iVar1;
  XSoundbankResource *res;
  undefined4 uVar2;
  undefined4 uVar3;
  XSoundbankResource *local_4;
  
  if (asset_name_00421bf0._0_4_ == 0x5f646961) {
    Assets::GetResourceBytes(asset_name_00421bf0,&local_4);
    res = local_4;
    if (local_4 == (XSoundbankResource *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    res = (XSoundbankResource *)0x0;
  }
  uVar3 = 1;
  uVar2 = 0;
  iVar1 = XSoundbankResource::GetResourceSize(res);
  FUN_0015d090(res,iVar1,uVar2,uVar3);
  Assets::DestroyAssetOrDecrement(res);
  FUN_00035c60(res);
  return;
}




void Audio::LoadSoundbanks(char *soundBankGroup)

{
  char cVar1;
  int size;
  char cVar2;
  SoundbankNode *lut;
  SoundbankNode *soundbank;
  XSoundbankResource *res;
  char audio_aid [128];
  XSoundbankResource *ress;
  char *filePath;
  audioSoundBankPreLoaded **preloaded;
  
  lut = (SoundbankNode *)0x0;
  do {
    while( true ) {
      do {
        soundbank = XActSoundbankLookupTable;
        if (((lut != (SoundbankNode *)0x0) &&
            (soundbank = *(SoundbankNode **)(lut[-1].name + 0x7c),
            *(SoundbankNode **)(lut[-1].name + 0x7c) == (SoundbankNode *)0x0)) ||
           (lut = (SoundbankNode *)soundbank->name, lut == (SoundbankNode *)0x0)) {
          return;
        }
        cVar2 = *(char *)lut;
        if (('@' < cVar2) && (cVar2 < '[')) {
          cVar2 = cVar2 + ' ';
        }
        cVar1 = *soundBankGroup;
        if (('@' < cVar1) && (cVar1 < '[')) {
          cVar1 = cVar1 + ' ';
        }
      } while (cVar2 != cVar1);
      _sprintf(&TempAIDBuffer,"aid_xsoundbank_%s_%s",soundBankGroup,soundbank->name + 1);
      size = 0;
      do {
        cVar2 = (&TempAIDBuffer)[size];
        audio_aid[size] = cVar2;
        size = size + 1;
      } while (cVar2 != '\0');
      preloaded = Soundbanks + NumSoundbanks;
      if (audio_aid._0_4_ == 0x5f646961) break;
LAB_0003a02b:
      NumSoundbanks = NumSoundbanks + 1;
    }
    Assets::GetResourceBytes(audio_aid,&res);
    ress = res;
    if (res != (XSoundbankResource *)0x0) {
      filePath = (char *)lut;
      size = XSoundbankResource::GetResourceSize(res);
      PreloadSoundbank(ress,size,filePath,preloaded);
      goto LAB_0003a02b;
    }
    runtime::ExitGame(2);
    NumSoundbanks = NumSoundbanks + 1;
  } while( true );
}




void Audio::UpdateListener(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  X3DAUDIO_VECTOR pos;
  X3DAUDIO_VECTOR orient_top;
  X3DAUDIO_VECTOR orient_front;
  float local_10;
  
  pos.x = (Graphics::CurrentCameraStruct->pos).x;
  pos.y = (Graphics::CurrentCameraStruct->pos).y;
  pos.z = (Graphics::CurrentCameraStruct->pos).z;
  orient_front.x = (Graphics::CurrentCameraStruct->forwards).x;
  orient_front.y = (Graphics::CurrentCameraStruct->forwards).y;
  orient_front.z = (Graphics::CurrentCameraStruct->forwards).z;
  local_10 = (Graphics::CurrentCameraStruct->rotQuat).x;
  fVar1 = (Graphics::CurrentCameraStruct->rotQuat).z;
  fVar2 = (Graphics::CurrentCameraStruct->rotQuat).y;
  fVar3 = (Graphics::CurrentCameraStruct->rotQuat).w;
  fVar4 = (fVar3 * 0.0 - fVar1 * -1.0) + fVar2 * 0.0;
  fVar6 = (fVar3 * 0.0 - fVar2 * 0.0) + local_10 * -1.0;
  fVar5 = (fVar3 * -1.0 - local_10 * 0.0) + fVar1 * 0.0;
  fVar7 = fVar2 * -1.0 + fVar1 * 0.0 + local_10 * 0.0;
  orient_top.x = (fVar2 * fVar6 + fVar7 * local_10 + fVar3 * fVar4) - fVar1 * fVar5;
  orient_top.y = (fVar3 * fVar5 + fVar2 * fVar7 + fVar1 * fVar4) - fVar6 * local_10;
  orient_top.z = (fVar3 * fVar6 + fVar1 * fVar7 + fVar5 * local_10) - fVar2 * fVar4;
  SetListenerPosition(&pos);
  SetVelocity(&g_X3D_Velocity);
  SetOrientation(&orient_front,&orient_top);
  return;
}




void Audio::LoadReverbSettings(int param_1)

{
  int iVar1;
  astruct_17 *puVar2;
  void *pvVar2;
  void *local_4;
  
  if (RevertSettings._0_4_ == 0x5f646961) {
    Assets::GetResourceBytes(RevertSettings,&local_4);
    pvVar2 = local_4;
    if (local_4 == (void *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    pvVar2 = (void *)0x0;
  }
  iVar1 = param_1 * 0x30;
  puVar2 = (astruct_17 *)(iVar1 + (int)pvVar2);
  FUN_0015c1e0(puVar2->field0_0x0,puVar2->field1_0x4,puVar2->field2_0x8,puVar2->field3_0xc,
               puVar2->field4_0x10,puVar2->field5_0x14,puVar2->field6_0x18,puVar2->field7_0x1c,
               puVar2->field8_0x20,puVar2->field9_0x24,*(undefined4 *)(iVar1 + 0x28 + (int)pvVar2),
               *(undefined4 *)(iVar1 + 0x2c + (int)pvVar2));
  Assets::DestroyAssetOrDecrement(pvVar2);
  DAT_004e14f4 = param_1;
  return;
}



// WARNING: Inlined function: SetFormatStringFunctions


void Audio::Initialise(void)

{
  uint *puVar1;
  undefined4 extraout_EDX;
  undefined4 uVar2;
  undefined4 extraout_EDX_00;
  uint uVar3;
  
  MallocFn = malloc2electricboogaloo;
  FreeFn = free2electricboogaloo;
  SetFileIOCallbacks(FileReadCallback,WaitForIOCallback);
  InitialiseXACTEngine();
  RunTestAudio();
  uVar2 = runtime::CurrentHeapToAllocateFrom;
  runtime::CurrentHeapToAllocateFrom = 1;
  CurrentSoundbankLine = malloc_(0x100);
  DAT_004e0cd4 = 0;
  AllocSize = 0x100;
  runtime::CurrentHeapToAllocateFrom = uVar2;
  LoadCueList("aid_xcuelist_ghoulies_default");
  LoadSoundbanks("ghoulies");
  LoadWavebanks(uVar2,0);
  LoadReverbSettings(0x18);
  puVar1 = &SoundSources[0].someu32;
  do {
    ((SoundSourceImpl *)(puVar1 + -3))->state = Free;
    puVar1[-2] = 0;
    *puVar1 = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1 = puVar1 + 9;
  } while ((int)puVar1 < 0x4e13b4);
  uVar3 = 0;
  uVar2 = extraout_EDX;
  do {
    SetCategoryVolume(uVar2,(WORD)*(undefined4 *)((int)&DAT_00421c7c + uVar3),
                      *(int *)((int)&DAT_00421c80 + uVar3));
    uVar3 = uVar3 + 8;
    uVar2 = extraout_EDX_00;
  } while (uVar3 < 0x18);
  return;
}




void Audio::Audio__RunCallbacks(void)

{
  Update(runtime::DeltaTime);
  UpdateListener();
  UpdatePlayerContexts();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_00047370(AudioParentState param_1)

{
  AudioParentState extraout_ECX;
  int unaff_ESI;
  
  if (*(int *)(unaff_ESI + 0xcc) == 1) {
    *(undefined4 *)(unaff_ESI + 0xcc) = 2;
    if (*(int *)(unaff_ESI + 0x114) != 0) {
      FUN_0005f970(*(int *)(unaff_ESI + 0x114));
      param_1 = extraout_ECX;
    }
    if (*(short *)(unaff_ESI + 0x168) != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + *(short *)(unaff_ESI + 0x168),param_1);
      *(undefined2 *)(unaff_ESI + 0x168) = 0xffff;
    }
  }
  return;
}




void FromPlayToPause(GamePauseContext *param_1)

{
  undefined4 uVar1;
  HeapTableEntry *pHVar2;
  int iVar3;
  GamePausePage *pGVar4;
  int local_4;
  
  FUN_000473d0();
  Camera::setActiveCamera(&param_1->cameraCfg);
  if (param_1 == PTR_005462a0) {
    PTR_005462a0 = (GamePauseContext *)0x0;
  }
  if (param_1->cutsceneBuffer != (Cutscene *)0x0) {
    Cutscene::dtor(param_1->cutsceneBuffer);
  }
  pGVar4 = &param_1->field18_0x8c;
  iVar3 = 4;
  do {
    if (pGVar4->field0_0x0 != 0) {
      FUN_000f85d0();
    }
    pGVar4 = pGVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (param_1->asset != (Asset *)0x0) {
    Assets::DestroyAssetOrDecrement(param_1->asset);
    FUN_00036210(&local_4);
    if (local_4 == 0) {
      FUN_00035c60(param_1->asset);
    }
  }
  iVar3 = FindHeapOf(param_1);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
    pHVar2 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar2 = g_HeapTableBase + iVar3;
  }
  runtime::CurrentHeapToAllocateFrom = iVar3;
  XAPILIB::HeapFree(pHVar2->heapHandle,0,param_1);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}




void __fastcall FUN_0004c4a0(AudioParentState param_1)

{
  short sVar1;
  int in_EAX;
  int unaff_ESI;
  
  if (in_EAX == 0) {
    FUN_0004c3b0();
  }
  else if ((in_EAX == 1) &&
          (sVar1 = *(short *)(unaff_ESI + *(int *)(param_1 + 0x10) * 2), sVar1 != -1)) {
    AudioParent::UpdateState(0,Audio::SoundSources + sVar1,param_1);
    *(undefined2 *)(unaff_ESI + *(int *)(param_1 + 0x10) * 2) = 0xffff;
    return;
  }
  return;
}




int someaudioshit(void)

{
  short sVar1;
  int iVar2;
  int unaff_EBX;
  int iVar3;
  
  iVar3 = 1;
  sVar1 = *(short *)(unaff_EBX + 2);
  while (((sVar1 != 0 && (sVar1 != 0x20)) && (sVar1 != 0x7d))) {
    iVar2 = iVar3 * 2;
    iVar3 = iVar3 + 1;
    sVar1 = *(short *)(unaff_EBX + 2 + iVar2);
  }
  iVar2 = FUN_00056f10((short *)(unaff_EBX + 2));
  if (iVar2 != 0x5c) {
    FUN_00056f80(iVar2);
  }
  sVar1 = *(short *)(unaff_EBX + iVar3 * 2);
  while ((sVar1 != 0 && (sVar1 != 0x7d))) {
    iVar2 = iVar3 * 2;
    iVar3 = iVar3 + 1;
    sVar1 = *(short *)(unaff_EBX + 2 + iVar2);
  }
  return unaff_EBX + iVar3 * 2;
}




void PlayDialogAudio(void)

{
  i16 soundSourceIndex;
  
  soundSourceIndex = Audio::CreateSoundSourceAndReturnIndex(AudioType0);
  if (soundSourceIndex != -1) {
    Audio::SoundSources[soundSourceIndex].flags = 1;
    Audio::FindBySoundbankStrAndPlay(UnspecifiedAudio,soundSourceIndex);
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


BOOL CreateDialog(LPCWSTR param_1,undefined1 param_2)

{
  undefined4 extraout_EDX;
  
  if (8 < NumDialogsAgain__ + 1) {
    return 0;
  }
  XAPILIB::lstrcpyW(DialogTexts[NumDialogs].dialog,param_1);
  DialogTexts[NumDialogs].nullchar_ = param_2;
  NumDialogs = NumDialogs + 1;
  if (7 < NumDialogs) {
    NumDialogs = 0;
  }
  NumDialogsAgain__ = NumDialogsAgain__ + 1;
  if (Game::DialogState == NotInDialog) {
    Events::SetDialogState(TextIncoming);
  }
  if (((undefined1)g_globalFlagset & Paused) == 0) {
    SetCategoryVolume(DAT_00421a1c,(WORD)DAT_00421a1c,0);
    SetCategoryVolume(extraout_EDX,(WORD)DAT_00421a24,0x3f);
  }
  DAT_004ee2ac = DAT_004e14f4;
  Audio::LoadReverbSettings(1);
  return 1;
}




void updateDialogSound(void)

{
  short sVar1;
  bool bVar2;
  short *in_EAX;
  undefined4 *unaff_EDI;
  
  bVar2 = false;
  sVar1 = *in_EAX;
  while ((sVar1 != 0 && (!bVar2))) {
    bVar2 = false;
    switch(*in_EAX) {
    case 9:
    case 10:
    case 0xd:
    case 0x20:
      break;
    case 0x7b:
      in_EAX = (short *)someaudioshit();
      break;
    case 0x7e:
      in_EAX = in_EAX + 1;
    default:
      *unaff_EDI = in_EAX;
      bVar2 = true;
    }
    in_EAX = in_EAX + 1;
    sVar1 = *in_EAX;
  }
  FUN_00059880();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint FUN_000663b0(Buffer<AudioSmth> *linkedList,undefined *param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = linkedList->head;
  if (uVar2 < linkedList->tail) {
    do {
      iVar1 = (*(code *)param_2)(uVar2);
      if (iVar1 != 0) {
        return uVar2;
      }
      uVar2 = uVar2 + linkedList->valueSize;
    } while (uVar2 < linkedList->tail);
  }
  return 0;
}




void __fastcall resolveSoupEnding(entityBodyPlayer *body,Message *update)

{
  actor *act;
  astruct_23 *paVar1;
  
  act = (body->human).body.actor;
  if ((update->header).someActor == act) {
    switch(update[1].header.msgId) {
    case General_Open:
      if (((body->human).body.health != 0) && (body->storedHealth != 0)) {
        (body->human).body.health = (ushort)body->storedHealth;
      }
      body->storedHealth = 0;
      body->energySapped_ = 0;
      return;
    case General_Close:
    case Avatar_AddToIgnoreList:
    case Avatar_AnimationEvent:
    case Avatar_CutScene_SetAnim:
    case Avatar_CutScene_SetPos:
    case Avatar_CutScene_SetRot:
      break;
    case Avatar_BreakableHit:
      FUN_0013b810((int)&body->someU32,act);
      return;
    case Avatar_CutScene_Begin:
      (act->avatar).field_0x197 = (act->avatar).field_0x197 + -1;
      actor::executeCallout(act,0,InvisibilityEnd);
      FUN_0003eeb0();
      paVar1 = (act->avatar).as23ptr;
      if (paVar1 != (astruct_23 *)0x0) {
        paVar1->field_0x18 = paVar1->field_0x18 + -1;
        return;
      }
      break;
    case Avatar_CutScene_End:
      actorBody::disableFlagByIndex(7,(actorBody *)body);
      return;
    case Avatar_Deflected:
    case Avatar_DeflectedByActor:
      (act->avatar).actionSpeed = 1.0;
      break;
    default:
      goto switchD_00075df6_default;
    }
  }
switchD_00075df6_default:
  return;
}




void FUN_0007dbe0(entityMindPlayer *param_1,void *this,int param_3)

{
  actor *av;
  int iVar1;
  vec3 local_c;
  
  if (this != (void *)0x0) {
    av = (param_1->actorMind).actor;
    if (av->input_handler_->active != 0) {
      iVar1 = FUN_00109620();
      if (iVar1 != 0) {
        avatar::getWorldPosition(&av->avatar,&local_c);
        FUN_0013ad60(av,0x2a,&local_c);
      }
    }
    return;
  }
  RegisterAssetEventFromMap__(param_1,(param_3 != 0) + 1);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0007dcc0(entityMindPlayer *param_1)

{
  int in_EAX;
  
  if (*(int *)(in_EAX + 0x1c) != 0) {
    RegisterAssetEventFromMap__(param_1,(*(int *)(in_EAX + 0x10) != 0) + 1);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 useCowerAttack(actorBody *param_1,entityMindPlayer *param_2)

{
  AttackEntry *attackEntry;
  
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  attackEntry = AttackDataResource::getAttackByStateId
                          ((AttackDataResource *)param_1->attackDataRes,
                           *(actorBodyStateId *)
                            (&DAT_002ffee4 +
                            (int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * -6.0) *
                            -2));
  if (attackEntry != (AttackEntry *)0x0) {
    (param_2->actorMind).currentAttackTarget = (actorBody *)0x0;
    actorBody::useAttack(param_1,attackEntry,0);
    return 1;
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void RegisterAssetEventFromMap__(entityMindPlayer *mind,uint index)

{
  actor *av;
  int iVar1;
  vec3 local_c;
  
  av = (mind->actorMind).actor;
  if (av->input_handler_->active != 0) {
    iVar1 = FUN_00109620();
    if (iVar1 != 0) {
      avatar::getWorldPosition(&av->avatar,&local_c);
      FUN_0013ad60(av,(uint)*(ushort *)
                             ((int)&PTR_AnimMapping_girl_60__animAID_102__002ffeee + index * 2),
                   &local_c);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall DisplayHealth(entityMindPlayer *mindPlayer,actorBody *param_2)

{
  actorBody *extraout_ECX;
  actorBody *pGVar1;
  
  pGVar1 = ((mindPlayer->actorMind).actor)->body;
  if (((((mindPlayer->actorMind).field_0x20 != '\0') ||
       (param_2 = (actorBody *)pGVar1->flagSet, ((param_2->actor->avatar).field_0x5 & 1) != 0)) ||
      (Game::PowerupParams[10].active != 0)) || (pGVar1->health < 0xb)) {
    BaronDraw_00433c10.scalar = 2.0;
    UI::LoadHealthTextures(param_2);
    param_2 = extraout_ECX;
  }
  if (0.0 < (mindPlayer->interactiveVals).attackTimer) {
    FUN_00130710((GameState *)param_2,1,(uint)pGVar1->health);
    return;
  }
  FUN_00130710((GameState *)param_2,0,(uint)pGVar1->health);
  return;
}




undefined4 onReplayLevel(entitySceneControlGameSelect *param_1)

{
  byte *pbVar3;
  byte bVar4;
  int iVar1;
  astruct_15 *paVar2;
  
  paVar2 = SomeAS15;
  iVar1 = param_1->field9_0x11c;
  if (iVar1 == 1) {
    pbVar3 = SomeAS15->flags;
    bVar4 = *pbVar3 | 2;
LAB_00083d53:
    *pbVar3 = bVar4;
    pbVar3 = paVar2->flags;
    bVar4 = *pbVar3 | 4;
  }
  else {
    if (iVar1 == 2) {
      pbVar3 = SomeAS15->flags;
      bVar4 = *pbVar3 & 0xfd;
      goto LAB_00083d53;
    }
    if (iVar1 != 3) goto LAB_00083d5f;
    *SomeAS15->flags = *SomeAS15->flags & 0xfd;
    pbVar3 = paVar2->flags;
    bVar4 = *pbVar3 & 0xfb;
  }
  *pbVar3 = bVar4;
LAB_00083d5f:
  XAPILIB::lstrcpyW(game::oldNextPlaycamScriptWide,game::nextPlaycamScriptWide);
  runtime::SaveTheGame_();
  setNextPlaycamScriptAID(1,param_1->nextPlaycamAID);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_000a73a0(XSoundbankResource *param_1,int param_2)

{
  char cVar1;
  int in_EAX;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  XSoundbankResource *res;
  int *name;
  int *piVar5;
  XSoundbankResource *pXStack_4;
  
  pcVar2 = (char *)(in_EAX + 0x18);
  iVar4 = param_2 - (int)pcVar2;
  do {
    cVar1 = *pcVar2;
    pcVar2[iVar4 + 100] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  piVar5 = (int *)(param_2 + 0xf4);
  name = (int *)(in_EAX + 0x98);
  iVar4 = 3;
  pXStack_4 = param_1;
  do {
    if (*name == 0x5f646961) {
      Assets::GetResourceBytes((char *)name,&pXStack_4);
      res = pXStack_4;
      if (pXStack_4 == (XSoundbankResource *)0x0) {
        runtime::ExitGame(2);
      }
    }
    else {
      res = (XSoundbankResource *)0x0;
    }
    piVar5[-1] = (int)res;
    if (res != (XSoundbankResource *)0x0) {
      uVar3 = XSoundbankResource::GetResourceSize(res);
      *piVar5 = (int)(res->name + ((uVar3 & 0xfffffff8) - 0x28));
    }
    name = name + 0x20;
    piVar5 = piVar5 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(undefined4 *)(param_2 + 0xec) = *(undefined4 *)(param_2 + 0xf0);
  return;
}




void FUN_000af920(XSoundbankResource *param_1,int param_2)

{
  int iVar1;
  avatar *act;
  XSoundbankResource *pXVar2;
  AnimEventMapping *pAVar3;
  uint uVar4;
  XSoundbankResource *res;
  char *someFlag;
  
  pXVar2 = param_1;
  iVar1 = *(int *)(*(int *)(param_1->wavebankArray + 0x95c) + 0x48);
  if (((iVar1 == 0) || (someFlag = (char *)(iVar1 + 0xdb0), someFlag == (char *)0x0)) ||
     (*someFlag == '\0')) {
    someFlag = (char *)0x0;
  }
  act = *(avatar **)(*(int *)(param_1->wavebankArray + 0x95c) + 8);
  pAVar3 = avatar::getAnimEventByName(act,"knobattack_overlay",(BOOL)someFlag);
  if ((pAVar3 == (AnimEventMapping *)0x0) && (someFlag != (char *)0x0)) {
    pAVar3 = avatar::getAnimEventByName(act,"knobattack_overlay",0);
  }
  pXVar2[1].SDBK = (uint32_t)pAVar3;
  if (*(int *)(param_2 + 0x18) == 0x5f646961) {
    Assets::GetResourceBytes((char *)(param_2 + 0x18),&param_1);
    res = param_1;
    if (param_1 == (XSoundbankResource *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    res = (XSoundbankResource *)0x0;
  }
  pXVar2[1]._dParams = (u32)res;
  if (res != (XSoundbankResource *)0x0) {
    uVar4 = XSoundbankResource::GetResourceSize(res);
    pXVar2[1].fileSize = (u32)(res->name + ((uVar4 & 0xfffffffc) - 0x28));
    *(XSoundbankResource **)&pXVar2[1].flags = res;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000c7a50(AudioParentState param_1)

{
  AudioParentState extraout_ECX;
  weapon *unaff_ESI;
  
  if (unaff_ESI->field100_0x998 != 0) {
    FUN_0013f660();
    (*((unaff_ESI->avatar).vtable)->onMessage)();
    param_1 = extraout_ECX;
  }
  unaff_ESI->field9_0x93c = 0;
  if (unaff_ESI->field_0xd08 != '\0') {
    unaff_ESI->field_0xd08 = 0;
    if (unaff_ESI->field1044_0xd88 != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + (short)unaff_ESI->field1044_0xd88,param_1);
      unaff_ESI->field1044_0xd88 = 0xffff;
    }
  }
  (unaff_ESI->avatar).has0x4CollisionFlag = 0;
  avatar::updateMorphTargetsOrSomething(&unaff_ESI->avatar);
  weapon::onDestroy(unaff_ESI);
  return;
}




void __fastcall FUN_000cae00(AudioParentState param_1)

{
  int *unaff_ESI;
  
  *(undefined1 *)(unaff_ESI + 0x24f) = 0;
  if ((char)unaff_ESI[0x342] != '\0') {
    *(undefined1 *)(unaff_ESI + 0x342) = 0;
    if ((short)unaff_ESI[0x362] != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + (short)unaff_ESI[0x362],param_1);
      *(undefined2 *)(unaff_ESI + 0x362) = 0xffff;
    }
  }
  unaff_ESI[0x3b6] = 0;
  unaff_ESI[0x395] = 0;
  unaff_ESI[0x3b7] = 0x40a00000;
  if (*(code **)(*unaff_ESI + 0x50) != (code *)0x0) {
    (**(code **)(*unaff_ESI + 0x50))();
  }
  return;
}




void __fastcall FUN_000cb200(AudioParentState param_1)

{
  bool bVar1;
  actor *in_EAX;
  BOOL BVar2;
  AudioParentState extraout_ECX;
  int unaff_ESI;
  float fVar3;
  float fVar4;
  
  fVar4 = 0.0;
  if ((in_EAX == (actor *)0x0) ||
     (BVar2 = GetAmbienceAudio__(in_EAX), param_1 = extraout_ECX, BVar2 != 0)) {
    fVar3 = fVar4;
    if (runtime::dx_timer <= fVar4) {
      fVar3 = runtime::DeltaTime * runtime::TimeScale;
    }
    if ((fVar4 < *(float *)(unaff_ESI + 0xedc)) &&
       (fVar3 = *(float *)(unaff_ESI + 0xedc) - fVar3, *(float *)(unaff_ESI + 0xedc) = fVar3,
       fVar3 <= fVar4)) {
      *(float *)(unaff_ESI + 0xedc) = fVar4;
    }
    if (*(float *)(unaff_ESI + 0xedc) == fVar4) {
      fVar3 = fVar4;
      if (runtime::dx_timer <= fVar4) {
        fVar3 = runtime::DeltaTime * runtime::TimeScale;
      }
      fVar3 = *(float *)(unaff_ESI + 0xee0) * fVar3 + *(float *)(unaff_ESI + 0xed8);
      *(float *)(unaff_ESI + 0xed8) = fVar3;
      if (1.0 < fVar3) {
        *(float *)(unaff_ESI + 0xed8) = 1.0;
      }
    }
  }
  bVar1 = fVar4 < *(float *)(unaff_ESI + 0xed8);
  *(bool *)(unaff_ESI + 0x93c) = bVar1;
  if ((!bVar1) && (*(char *)(unaff_ESI + 0xd08) != '\0')) {
    *(undefined1 *)(unaff_ESI + 0xd08) = 0;
    if (*(short *)(unaff_ESI + 0xd88) != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + *(short *)(unaff_ESI + 0xd88),param_1);
      *(undefined2 *)(unaff_ESI + 0xd88) = 0xffff;
    }
  }
  return;
}




void __fastcall FUN_000cc430(AudioParentState param_1)

{
  int iVar1;
  int *unaff_ESI;
  
  *(undefined1 *)(unaff_ESI + 0x24f) = 0;
  if ((char)unaff_ESI[0x342] != '\0') {
    *(undefined1 *)(unaff_ESI + 0x342) = 0;
    if ((short)unaff_ESI[0x362] != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + (short)unaff_ESI[0x362],param_1);
      *(undefined2 *)(unaff_ESI + 0x362) = 0xffff;
    }
  }
  iVar1 = unaff_ESI[0x3d2];
  *(undefined2 *)((int)unaff_ESI + 0xc0e) = 0;
  (**(code **)(*unaff_ESI + 0x40))();
  *(ushort *)(unaff_ESI + 0x303) = (-(ushort)(iVar1 != 0) & 0xfffb) + 9;
  unaff_ESI[0x305] = 0;
  (**(code **)(*unaff_ESI + 0x3c))();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000cd2a0(AudioParentState param_1)

{
  int iVar1;
  int *unaff_ESI;
  
  *(undefined1 *)(unaff_ESI + 0x24f) = 0;
  if ((char)unaff_ESI[0x342] != '\0') {
    *(undefined1 *)(unaff_ESI + 0x342) = 0;
    if ((short)unaff_ESI[0x362] != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + (short)unaff_ESI[0x362],param_1);
      *(undefined2 *)(unaff_ESI + 0x362) = 0xffff;
    }
  }
  iVar1 = unaff_ESI[0x3a5];
  *(undefined2 *)((int)unaff_ESI + 0xc0e) = 0;
  (**(code **)(*unaff_ESI + 0x40))();
  *(ushort *)(unaff_ESI + 0x303) = (-(ushort)(iVar1 != 0) & 0xfffb) + 9;
  unaff_ESI[0x305] = 0;
  (**(code **)(*unaff_ESI + 0x3c))();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_000cf670(AudioParentState param_1)

{
  WeaponProjectilesContext *pWVar1;
  AudioParentState extraout_ECX;
  weapon *unaff_ESI;
  
  if (unaff_ESI->field100_0x998 != 0) {
    FUN_0013f660();
    (*((unaff_ESI->avatar).vtable)->onMessage)();
    param_1 = extraout_ECX;
  }
  unaff_ESI->field9_0x93c = 0;
  if (unaff_ESI->field_0xd08 != '\0') {
    unaff_ESI->field_0xd08 = 0;
    if (unaff_ESI->field1044_0xd88 != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + (short)unaff_ESI->field1044_0xd88,param_1);
      unaff_ESI->field1044_0xd88 = 0xffff;
    }
  }
  (unaff_ESI->avatar).has0x4CollisionFlag = 0;
  avatar::updateMorphTargetsOrSomething(&unaff_ESI->avatar);
  pWVar1 = unaff_ESI->projectilesCtx;
  if ((pWVar1 != (WeaponProjectilesContext *)0x0) &&
     ((*(short *)&pWVar1[1].field_0x37c == 2 || (*(int *)&pWVar1->field_0x93c != 0)))) {
    unaff_ESI->weaponState = 1;
    weapon::onDestroy(unaff_ESI);
    return;
  }
  unaff_ESI->weaponState = 0;
  weapon::onDestroy(unaff_ESI);
  return;
}




void __fastcall FUN_000d1fc0(AudioParentState param_1)

{
  LPWSTR lpString1;
  float scaleX;
  int *piVar1;
  undefined4 *puVar2;
  undefined2 uVar3;
  int in_EAX;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  char *pcVar4;
  int iVar5;
  int extraout_EAX_04;
  int *unaff_ESI;
  undefined4 uVar6;
  WCHAR local_30 [24];
  
  piVar1 = DAT_00506554;
  if (*DAT_00506554 == 3) {
    unaff_ESI = DAT_00506554 + 0x9e2;
    if ((short)DAT_00506554[0x9e2] != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + (short)DAT_00506554[0x9e2],param_1);
    }
    *(undefined2 *)unaff_ESI = 0xffff;
  }
  *piVar1 = in_EAX;
  puVar2 = DAT_00506568;
  switch(in_EAX) {
  case 2:
    FUN_000d2730();
    if ((short)piVar1[(piVar1[0x8d5] + 1) * 0x213] == -1) {
      uVar3 = FUN_000d27d0(*(undefined4 *)(piVar1[0x8d5] * 0x388 + 0x180 + DAT_00506558));
      *(undefined2 *)(piVar1 + (piVar1[0x8d5] + 1) * 0x213) = uVar3;
      return;
    }
    break;
  case 3:
    iVar5 = piVar1[0x8d5];
    LoctextValueContext::Initialise
              ((LoctextValueContext *)piVar1[0x8d3],(LPWSTR)(piVar1 + iVar5 * 0x213 + 1),
               (float)piVar1[iVar5 * 0x213 + 0x81],(float)piVar1[iVar5 * 0x213 + 0x82],
               FLOAT_00428a88,FLOAT_00428a88,1.0,1,0);
    piVar1[piVar1[0x8d5] * 0x213 + 0x83] = extraout_EAX;
    Audio::PlaySoundWithFlags("XACT_SOUNDBANK_GPICKUPDITTIES_EVENTREQICON",1);
    if ((short)piVar1[0x9e2] == -1) {
      uVar3 = FUN_000d27d0("XACT_SOUNDBANK_GPROPS_SNAREROLL");
      *(undefined2 *)(piVar1 + 0x9e2) = uVar3;
    }
    piVar1[0x8d4] = DAT_00428ae0;
    return;
  case 4:
    iVar5 = piVar1[0x8d5];
    LoctextValueContext::Initialise
              ((LoctextValueContext *)piVar1[0x8d3],(LPWSTR)(piVar1 + iVar5 * 0x213 + 0x8a),
               (float)piVar1[iVar5 * 0x213 + 0x10a],(float)piVar1[iVar5 * 0x213 + 0x10b],
               FLOAT_00428a88,FLOAT_00428a88,1.0,1,0);
    piVar1[piVar1[0x8d5] * 0x213 + 0x10c] = extraout_EAX_00;
    Audio::PlaySoundWithFlags("XACT_SOUNDBANK_GSTREAMSDITTIES_SCOREFANFARE",1);
    piVar1[0x8d4] = DAT_00428ae4;
    return;
  case 5:
    iVar5 = piVar1[0x8d5];
    LoctextValueContext::Initialise
              ((LoctextValueContext *)piVar1[0x8d3],(LPWSTR)(piVar1 + iVar5 * 0x213 + 0x10d),
               (float)piVar1[iVar5 * 0x213 + 0x18d],(float)piVar1[iVar5 * 0x213 + 0x18e],
               FLOAT_00428a8c,FLOAT_00428a8c,1.0,1,1);
    piVar1[piVar1[0x8d5] * 0x213 + 399] = extraout_EAX_01;
    LoctextValueContext::Initialise
              ((LoctextValueContext *)piVar1[0x8d3],(LPWSTR)(piVar1 + 0x8dc),(float)piVar1[0x95c],
               (float)piVar1[0x95d],FLOAT_00428a8c,FLOAT_00428a8c,1.0,1,1);
    scaleX = FLOAT_00428a8c;
    piVar1[0x95e] = extraout_EAX_02;
    iVar5 = piVar1[0x8d5];
    LoctextValueContext::Initialise
              ((LoctextValueContext *)piVar1[0x8d3],(LPWSTR)(piVar1 + iVar5 * 0x213 + 400),
               (float)piVar1[iVar5 * 0x213 + 0x210],(float)piVar1[iVar5 * 0x213 + 0x211],scaleX,
               scaleX,1.0,1,1);
    piVar1[piVar1[0x8d5] * 0x213 + 0x212] = extraout_EAX_03;
    Audio::PlaySoundWithFlags("XACT_SOUNDBANK_GPICKUPDITTIES_KEYAPPEAR",1);
    piVar1[0x8d4] = DAT_00428ae8;
    return;
  case 6:
    iVar5 = piVar1[0x8d5] * 0x388;
    uVar6 = 1;
    pcVar4 = GetFinalScoreSound(0,CONCAT22((short)((uint)iVar5 >> 0x10),
                                           *(undefined2 *)(DAT_00506558 + iVar5 + 0x186)),
                                CONCAT22((short)((uint)unaff_ESI >> 0x10),
                                         *(undefined2 *)(DAT_00506558 + 0x184 + iVar5)));
    Audio::PlaySoundWithFlags(pcVar4,uVar6);
    piVar1[0x8d4] = DAT_00428aec;
    return;
  case 7:
    lpString1 = (LPWSTR)(piVar1 + 0x95f);
    *lpString1 = L'\0';
    createGameselectString("finalscore","score",lpString1,(LoctextDescriptor *)*puVar2);
    iVar5 = DAT_00506558;
    piVar1[0x9df] = (int)g_DXContext.field28_0x48;
    piVar1[0x9e0] = (int)g_DXContext.__0;
    piVar1[0x9e0] = DAT_00428ac4;
    iVar5 = piVar1[0x8db] + (uint)*(ushort *)(piVar1[0x8d5] * 0x388 + 0x184 + iVar5);
    piVar1[0x8db] = iVar5;
    FUN_00166b36(iVar5,local_30,10);
    XAPILIB::lstrcatW(lpString1,local_30);
    LoctextValueContext::Initialise
              ((LoctextValueContext *)piVar1[0x8d3],lpString1,(float)piVar1[0x9df],
               (float)piVar1[0x9e0],FLOAT_00428a90,FLOAT_00428a90,1.0,1,1);
    piVar1[0x9e1] = extraout_EAX_04;
    Audio::PlaySoundWithFlags("XACT_SOUNDBANK_GPICKUPDITTIES_REAPERICON",1);
    piVar1[0x8d4] = DAT_00428af0;
    return;
  case 8:
    FUN_0005f970(piVar1[0x8d3]);
    piVar1[0x9e1] = 0;
    piVar1[0x95e] = 0;
    piVar1[piVar1[0x8d5] * 0x213 + 0x212] = 0;
    piVar1[piVar1[0x8d5] * 0x213 + 399] = 0;
    piVar1[piVar1[0x8d5] * 0x213 + 0x10c] = 0;
    iVar5 = DAT_00428af4;
    piVar1[piVar1[0x8d5] * 0x213 + 0x83] = 0;
    piVar1[0x8d4] = iVar5;
    FUN_000d2810();
    *(undefined2 *)(piVar1 + (piVar1[0x8d5] + 1) * 0x213) = 0xffff;
    return;
  case 9:
    FUN_0013b9d0();
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void __fastcall FUN_000d2810(AudioParentState param_1)

{
  short in_AX;
  
  if (in_AX != -1) {
    AudioParent::UpdateState(0,Audio::SoundSources + in_AX,param_1);
  }
  return;
}




char * GetFinalScoreSound(uint min,uint max,uint score)

{
  uint minn;
  float fVar1;
  float fVar2;
  float minnn;
  
  minn = min & 0xffff;
                    // If max, return max
  if ((float)(int)((score & 0xffff) - minn) / (float)(int)((max & 0xffff) - minn) == 1.0) {
    return "XACT_SOUNDBANK_GBOY_21TO25";
  }
  fVar1 = (float)(max & 0xffff);
  minnn = (float)minn;
  if (fVar1 == minnn) {
    fVar1 = 4.0;
  }
  else {
    fVar2 = 4.0;
    fVar1 = (((float)(score & 0xffff) - minnn) / (fVar1 - minnn)) * 4.0;
    if ((4.0 < fVar1) || (fVar2 = 0.0, fVar1 < 0.0)) {
      return "XACT_SOUNDBANK_GBOY_0TO6" + (int)fVar2 * 0x80;
    }
  }
  return "XACT_SOUNDBANK_GBOY_0TO6" + (int)fVar1 * 0x80;
}




BOOL CheckPlaycamLoaded__(void)

{
  int iVar1;
  int i;
  asset_name_t in_EDX;
  char *pcVar2;
  char *pcVar3;
  undefined4 *puVar4;
  ReplayChapterMenu *local_10c;
  char local_108 [45];
  undefined4 local_db;
  char local_88 [46];
  undefined4 local_5a [21];
  
  pcVar2 = "aid_script_ghoulies_chapter5_scene1_1playcam";
  pcVar3 = local_108;
  for (i = 0xb; i != 0; i = i + -1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar3 = pcVar3 + 4;
  }
  *pcVar3 = *pcVar2;
  puVar4 = &local_db;
  for (i = 0x14; i != 0; i = i + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined2 *)puVar4 = 0;
  *(undefined1 *)((int)puVar4 + 2) = 0;
  pcVar2 = "aid_script_ghoulies_chapter5_scene13_2playcam";
  pcVar3 = local_88;
  for (i = 0xb; i != 0; i = i + -1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar3 = pcVar3 + 4;
  }
  *(undefined2 *)pcVar3 = *(undefined2 *)pcVar2;
  puVar4 = local_5a;
  for (i = 0x14; i != 0; i = i + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined2 *)puVar4 = 0;
  local_10c = (ReplayChapterMenu *)Assets::SceneOrderAHandle.sceneOrder;
  i = IndexOfAssetInAIDList(&local_10c,in_EDX);
  iVar1 = IndexOfAssetInAIDList(&local_10c,local_108);
  if (iVar1 <= i) {
    iVar1 = IndexOfAssetInAIDList(&local_10c,local_88);
    if (i <= iVar1) {
      return 0;
    }
  }
  return 1;
}




void SetRumblesAndMaybeOthers(void)

{
  int iVar1;
  
  FUN_001558f0(1);
  iVar1 = 0;
  do {
    FUN_00155930();
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  Input::RumbleContexts[0].uint0x8 = 0;
  Input::RumbleContexts[0].uint0xc = 0;
  Input::RumbleContexts[1].uint0x8 = 0;
  Input::RumbleContexts[1].uint0xc = 0;
  Input::RumbleContexts[2].uint0x8 = 0;
  Input::RumbleContexts[2].uint0xc = 0;
  Input::RumbleContexts[3].uint0x8 = 0;
  Input::RumbleContexts[3].uint0xc = 0;
  return;
}




void UpdateRumblesOrAudio_(void)

{
  uint *intArray;
  RumbleContextPlus0xc rumble;
  
  SomeGlobalAudioBuffer = malloc_(0x2b0);
  SomeGlobalAudioBuffer->head = SomeGlobalAudioBuffer->values;
  SomeGlobalAudioBuffer->tail = SomeGlobalAudioBuffer->values;
  SomeGlobalAudioBuffer->end = (Audio0x54 *)(SomeGlobalAudioBuffer + 1);
  SomeGlobalAudioBuffer->valueSize = 0x54;
  SomeGlobalAudioBuffer->capacity = 8;
  DAT_00507df4 = 0;
  rumble = &Input::RumbleContexts[0].uint0xc;
  intArray = g_AudioContext_[0].g_INT_ARRAY;
  do {
    intArray[1] = 1;
    *intArray = 1;
    ADJ(rumble)->uint0x8 = 1;
    ADJ(rumble)->uint0xc = 1;
    intArray = intArray + 7;
                    // +4 since its a pointer, ignore this (its correctly +16)
    rumble = rumble + 4;
  } while ((int)intArray < 0x507e00);
  return;
}




void Audio::ProcessSamples(void)

{
  Audio0x54 **ppAVar1;
  float fVar2;
  float fVar3;
  vec3_ptr_8_float adjusted_pointer;
  BOOL BVar4;
  uint *__dest;
  float *pfVar5;
  uint uVar6;
  PhysicsStruct *idk;
  RumbleContext *pRVar7;
  int iVar8;
  Audio0x54 *pAVar9;
  Buffer<Audio0x54> *pBVar10;
  float fVar11;
  float local_4;
  
  if (runtime::dx_timer <= 0.0) {
    local_4 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    local_4 = 0.0;
  }
  fVar11 = (Graphics::CurrentCameraStruct->pos).x;
  fVar2 = (Graphics::CurrentCameraStruct->pos).y;
  fVar3 = (Graphics::CurrentCameraStruct->pos).z;
                    // Update vec3 at a weird offset
  adjusted_pointer = (vec3_ptr_8_float)&g_AudioContext_[0].field2_0x8;
  do {
    ADJ(adjusted_pointer).x = fVar11;
    ADJ(adjusted_pointer)->y = fVar2;
    ADJ(adjusted_pointer)->z = fVar3;
    adjusted_pointer = adjusted_pointer + 7;
  } while ((int)adjusted_pointer < 0x507dfc);
  if ((DAT_00507df4 == 0) && (SomeGlobalAudioBuffer != (Buffer<Audio0x54> *)0x0)) {
    uVar6 = (uint)(ushort)SomeGlobalAudioBuffer->valueSize;
    pAVar9 = SomeGlobalAudioBuffer->head;
    iVar8 = 0;
    pBVar10 = SomeGlobalAudioBuffer;
    if (0 < ((int)SomeGlobalAudioBuffer->tail - (int)pAVar9) / (int)uVar6) {
      do {
        idk = (PhysicsStruct *)((int)&pAVar9->field0_0x0 + uVar6 * iVar8);
        if (idk[2].count != 0) {
          BVar4 = Physics::CalculateInterpolations(idk,local_4);
          if (BVar4 == 0) {
            FUN_000fb650(idk,fVar11);
            pBVar10 = SomeGlobalAudioBuffer;
          }
          else {
            Assets::DestroyAssetOrDecrement((void *)idk[2].count);
            pBVar10 = SomeGlobalAudioBuffer;
            uVar6 = (uint)(ushort)SomeGlobalAudioBuffer->valueSize;
            __dest = (uint *)((int)&SomeGlobalAudioBuffer->head->field0_0x0 + uVar6 * iVar8);
            ppAVar1 = &SomeGlobalAudioBuffer->tail;
            if (__dest < (undefined1 *)((int)*ppAVar1 - uVar6)) {
              _memmove(__dest,(void *)((int)__dest + uVar6),
                       (int)((int)*ppAVar1 - uVar6) - (int)__dest);
            }
            *ppAVar1 = (Audio0x54 *)((int)*ppAVar1 - (uint)(ushort)pBVar10->valueSize);
            pBVar10 = SomeGlobalAudioBuffer;
          }
        }
        pAVar9 = pBVar10->head;
        uVar6 = (uint)(ushort)pBVar10->valueSize;
        iVar8 = iVar8 + 1;
      } while (iVar8 < ((int)pBVar10->tail - (int)pAVar9) / (int)uVar6);
    }
  }
  pfVar5 = (float *)&g_AudioContext_[0].field_0x14;
  pRVar7 = Input::RumbleContexts;
  do {
    if (pfVar5[-1] != 0.0) {
      if (DAT_00507df4 == 0) {
        fVar11 = pfVar5[1];
        if ((pRVar7->uint0x8 == 0) || (*pfVar5 < 5.0)) {
          pRVar7->field0_0x0 = 0;
        }
        else {
          pRVar7->field0_0x0 = (uint)*pfVar5;
        }
        if ((pRVar7->uint0x8 != 0) && (5.0 <= fVar11)) {
          pRVar7->field1_0x4 = (uint)fVar11;
          goto LAB_000fb0ca;
        }
      }
      else {
        pRVar7->field0_0x0 = 0;
      }
      pRVar7->field1_0x4 = 0;
    }
LAB_000fb0ca:
    *pfVar5 = 0.0;
    pfVar5[1] = 0.0;
    pRVar7 = pRVar7 + 1;
    pfVar5 = pfVar5 + 7;
    if (0x507d7f < (int)pRVar7) {
      return;
    }
  } while( true );
}




Audio0x54 * FUN_000fb7c0(void)

{
  Audio0x54 *pAVar1;
  
  if (SomeGlobalAudioBuffer == (Buffer<Audio0x54> *)0x0) {
    return (Audio0x54 *)0x0;
  }
  if (0xf < (uint)(((int)SomeGlobalAudioBuffer->tail - (int)SomeGlobalAudioBuffer->head) /
                  (int)(uint)(ushort)SomeGlobalAudioBuffer->valueSize)) {
    return (Audio0x54 *)0x0;
  }
  if (SomeGlobalAudioBuffer->tail == SomeGlobalAudioBuffer->end) {
    SomeGlobalAudioBuffer =
         (Buffer<Audio0x54> *)runtime::ExtendArray((Buffer *)SomeGlobalAudioBuffer);
  }
  pAVar1 = SomeGlobalAudioBuffer->tail;
  SomeGlobalAudioBuffer->tail =
       (Audio0x54 *)((int)&pAVar1->field0_0x0 + (uint)(ushort)SomeGlobalAudioBuffer->valueSize);
  return pAVar1;
}




void SetPlayerExitedBox(vec3 *param_1,vec3 *param_2)

{
  PlayerSpawnPos_.x = param_2->x;
  PlayerSpawnPos_.y = param_2->y;
  PlayerSpawnPos_.z = param_2->z;
  PlayerOOBPos_.x = param_1->x;
  PlayerOOBPos_.y = param_1->y;
  PlayerOOBPos_.z = param_1->z;
  PlayerExitedBox = 1;
  return;
}




void __thiscall FUN_00117880(AudioParentState param_1,undefined4 param_2)

{
  short sVar1;
  int in_EAX;
  vec3 *unaff_EBX;
  short *unaff_EDI;
  float in_XMM0_Da;
  
  sVar1 = *unaff_EDI;
  if ((in_XMM0_Da <= 0.0) || (in_EAX != 0)) {
    if (sVar1 != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + sVar1,param_1);
      *unaff_EDI = -1;
      return;
    }
  }
  else {
    if (sVar1 == -1) {
      sVar1 = FUN_00039580(param_2,0);
      if (sVar1 == -1) goto LAB_001178cd;
    }
    if (Audio::SoundSources[sVar1].soundSource != (soundSource *)0x0) {
      Audio::SetSoundSourcePosition(Audio::SoundSources[sVar1].soundSource,unaff_EBX);
    }
  }
LAB_001178cd:
  *unaff_EDI = sVar1;
  return;
}




void __fastcall FUN_00117980(AudioParentState param_1)

{
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  DAT_0050e7ac = ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * DAT_0050e7b0;
  DAT_0050e7a8 = 0;
  DAT_0050e7b8 = 0;
  DAT_0050e7c4 = 0;
  DAT_0050e7bc = 0;
  DAT_0050e7c0 = 0;
  DAT_0050e7c8 = 0;
  if (DAT_0050e7d8 != -1) {
    param_1 = AudioParent::UpdateState(0,Audio::SoundSources + DAT_0050e7d8,param_1);
    DAT_0050e7d8 = -1;
  }
  if (DAT_0050e7d4 != -1) {
    AudioParent::UpdateState(0,Audio::SoundSources + DAT_0050e7d4,param_1);
    DAT_0050e7d4 = -1;
  }
  return;
}



// WARNING: Type propagation algorithm not settling
// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void InitPlaycamScriptAndGlobals(void)

{
  undefined4 unaff_EDI;
  
  FLOAT_00509b2c = 1.0;
  vec3_00509b20.x = 1.0;
  vec3_00509b20.y = 1.0;
  vec3_00509b20.z = 1.0;
  FLOAT_00509b4c = 1.0;
                    // Starts at pi/9 (20deg)
  UnknownAngle1 = 0.34906587;
  DAT_005462fc = 1;
                    // Starts at pi/4.5 (40deg)
  UnknownAngle2 = 0.69813174;
  DAT_00509b58 = 1;
  DAT_00509b70 = 0;
  Game::UseMovementSmoothing = 1;
  AllocateGlobalShorts();
  DAT_00545d1c = 0;
  DAT_00545cc8 = 0;
  FUN_0013cbd0();
  ResetStateVariables();
  InitPlaycamStuff(unaff_EDI);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void reuse_old_playcam_id(void)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  
  uVar2 = SomeAS15->field1_0x4;
  pbVar3 = SomeAS15->flags;
  for (uVar1 = uVar2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    pbVar3[0] = 0;
    pbVar3[1] = 0;
    pbVar3[2] = 0;
    pbVar3[3] = 0;
    pbVar3 = pbVar3 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pbVar3 = 0;
    pbVar3 = pbVar3 + 1;
  }
  game::oldNextPlaycamScriptWide[0] = L'\0';
  Game::Save.timeSeconds = 0;
  Game::Save.numKills = 0;
  Game::Save.numDeaths = 0;
  Game::Save.numPrisoners = 0;
  Game::Save.field4_0x10 = 0;
  Game::DeathsInCurrentRoom = 0;
  setNextPlaycamScriptAID(1,Assets::SceneOrderAHandle.sceneOrder);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void setNextPlaycamScriptAID(int newChapterState,char *newPlaycamId)

{
  int i;
  char c;
  
  if (Game::GameState.newSceneScriptAID._0_4_ == L'\x5f646961') {
    Game::GameState.newSceneScriptAID[0] = '\0';
    Game::GameState.newSceneScriptAID[1] = 'i';
    Game::GameState.newSceneScriptAID[2] = 'd';
    Game::GameState.newSceneScriptAID[3] = '_';
                    // replace with aid\0
  }
  i = 0x510ed8 - (int)newPlaycamId;
  do {
    c = *newPlaycamId;
    newPlaycamId[i] = c;
    newPlaycamId = newPlaycamId + 1;
  } while (c != '\0');
  PlayerObjectParamsId = 0;
  g_finishedLoading_ = 0;
  Game::Something0x7 = 0;
  Game::PlayerObjParamsAID[0] = '\0';
  if (DAT_00430d94 == 0) {
    Game::DeathsInCurrentRoom = 0;
  }
  DAT_00430d94 = 0;
  DAT_00430d98 = 0;
  Game::GameState.newLoadState2___ = newChapterState;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


char * GetPlayerActorObjParams(void)

{
  PlayerModel challengeFlags;
  
  challengeFlags = GetChallengeHeader();
  if (challengeFlags == INVALID) {
    if (((*SomeAS15->flags & 0b00001000) == 0) && ((g_globalFlagset & 0x200000) == 0)) {
      challengeFlags = COOPER;
    }
    else {
      challengeFlags = AMBER;
    }
  }
  if (challengeFlags != COOPER) {
    if (challengeFlags == AMBER) {
      return "aid_objparams_ghoulies_actor_player_girl";
    }
    if (challengeFlags == COOK) {
      return "aid_objparams_ghoulies_actor_cookplayable";
    }
  }
  return "aid_objparams_ghoulies_actor_player_boy";
}




void InitPlaycamStuff(undefined4 param_1)

{
  asset_name *newScript;
  BOOL regular;
  char *player_objparams_aid;
  
                    // Get the new playcam script (or the first one if we fail to find it)
  newScript = Assets::GetEntryAfterInTable
                        ((asset_name **)&Assets::SceneOrderAHandle,
                         Game::GameState.currentSceneScript,1);
  BundleContext::bnlNameFromScriptAID(Game::GameState.currentSceneScript);
  regular = Assets::AIDIsRegularScript(Game::GameState.currentSceneScript);
                    // If we aren't in a weird script where the player isnt used
  if (regular != 0) {
                    // Ensure the bundle context exists
    player_objparams_aid = GetPlayerActorObjParams();
    BundleContext::bnlNameFromScriptAID(player_objparams_aid);
                    // Then actually read it once we know it exists
    player_objparams_aid = GetPlayerActorObjParams();
    runtime::loadObjparamsFromBundle(player_objparams_aid);
  }
  Events::loadBnlFromScriptAid();
  setPlaycamScript(Game::GameState.currentSceneScript,*newScript);
  runtime::CacheContext.utilityDriveError = 1;
  return;
}




void SpawnThePlayerFromMarker(void)

{
  uint uVar1;
  ushort uVar2;
  Marker *pMVar3;
  uint uVar4;
  
  uVar1 = (Game::GameState.markerInstance)->numMarkers;
  uVar4 = 0;
  pMVar3 = (Game::GameState.markerInstance)->marker;
  if (uVar1 != 0) {
    while( true ) {
      uVar2 = Marker::nextIdOfNextMarkerOfType(Player,1,0);
      if (pMVar3->id == uVar2) break;
      uVar4 = uVar4 + 1;
      pMVar3 = (Marker *)((int)&pMVar3->size + pMVar3->size);
      if (uVar1 <= uVar4) {
        return;
      }
    }
                    // LoadPlayerSpawner
    if ((pMVar3 != (Marker *)0x0) && ((code *)Marker::Handlers[pMVar3->markerType] != (code *)0x0))
    {
      (*(code *)Marker::Handlers[pMVar3->markerType])(pMVar3);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


actor * getThePlayer(void)

{
  if (Game::SceneInfo.playerActors.prev != (actor_0x93c_conflict5)0x0) {
    return (actor *)ADJ(Game::SceneInfo.playerActors.prev);
  }
  return (actor *)0x0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void UpdateAvatarAudio(void)

{
  SomeAudioStruct *pSVar1;
  
  pSVar1 = &SomeAudioStruct_00512520;
  do {
    FUN_0012a510(pSVar1);
    FUN_0012a6e0(pSVar1);
    FUN_0012a7d0(pSVar1);
    pSVar1 = pSVar1 + 1;
  } while ((int)pSVar1 < 0x512548);
  return;
}




void FUN_0012a510(SomeAudioStruct *param_1)

{
  SoundSourceImpl *pSVar1;
  int *piVar2;
  AudioParentState AVar3;
  int *piVar4;
  IXACT_Cue *cue;
  int *piVar5;
  undefined4 local_20;
  int *local_1c;
  undefined4 local_18;
  int *local_14;
  undefined4 uStack_10;
  int *piStack_c;
  
  piVar5 = param_1->field2_0x8;
  while (piVar5 != (int *)0x0) {
    piVar2 = (int *)piVar5[1];
    if ((Audio::SoundSources[(short)piVar5[2]].cue == (IXACT_Cue *)0x0) ||
       ((((AVar3 = Audio::SoundSources[(short)piVar5[2]].state, AVar3 != ShouldGoTo4_1 &&
          (AVar3 != ShouldGoTo4_2)) && (AVar3 != ShouldPause1)) &&
        ((AVar3 != ShouldPause2 && (AVar3 != ShouldPause3)))))) {
      piVar4 = (int *)piVar5[3];
      if (piVar4 != (int *)0x0) {
        local_20 = 0x8a;
        local_1c = piVar5;
        (**(code **)(*piVar4 + 0xc))(piVar4,&local_20);
      }
      cue = Audio::SoundSources[(short)piVar5[2]].cue;
      pSVar1 = Audio::SoundSources + (short)piVar5[2];
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
      *(undefined2 *)(piVar5 + 2) = 0xffff;
      *(undefined1 *)((int)piVar5 + 0x92) = 1;
      if (*piVar5 != 0) {
        *(int *)(*piVar5 + 4) = piVar5[1];
      }
      if ((int *)piVar5[1] != (int *)0x0) {
        *(int *)piVar5[1] = *piVar5;
      }
      *piVar5 = 0;
      piVar5[1] = 0;
      piVar5 = piVar2;
    }
    else {
      piVar4 = (int *)piVar5[3];
      if (piVar4 != (int *)0x0) {
        local_18 = 0x8b;
        local_14 = piVar5;
        (**(code **)(*piVar4 + 0xc))(piVar4,&local_18);
      }
      if (Audio::SoundSources[(short)piVar5[2]].soundSource != (soundSource *)0x0) {
        Audio::SetSoundSourcePosition
                  (Audio::SoundSources[(short)piVar5[2]].soundSource,(vec3 *)(piVar5 + 0x25));
      }
      piVar4 = (int *)piVar5[3];
      if (piVar4 != (int *)0x0) {
        uStack_10 = 0x8c;
        piStack_c = piVar5;
        (**(code **)(*piVar4 + 0xc))(piVar4,&uStack_10);
      }
      if (Audio::SoundSources[(short)piVar5[2]].soundSource != (soundSource *)0x0) {
        Audio::SetSoundConeOrientation
                  (Audio::SoundSources[(short)piVar5[2]].soundSource,(vec3 *)(piVar5 + 0x28));
      }
      *(undefined1 *)((int)piVar5 + 0x92) = 0;
      piVar5 = piVar2;
    }
  }
  return;
}




void FUN_0012a6e0(SomeAudioStruct *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *extraout_ECX;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar5 = (Graphics::CurrentCameraStruct->pos).x;
  fVar6 = (Graphics::CurrentCameraStruct->pos).y;
  fVar7 = (Graphics::CurrentCameraStruct->pos).z;
  piVar1 = param_1->field4_0x10;
  if (piVar1 != (int *)0x0) {
    piVar1[0x2b] = (int)((fVar7 - (float)piVar1[0x27]) * (fVar7 - (float)piVar1[0x27]) +
                         (fVar6 - (float)piVar1[0x26]) * (fVar6 - (float)piVar1[0x26]) +
                        (fVar5 - (float)piVar1[0x25]) * (fVar5 - (float)piVar1[0x25]));
    puVar2 = (undefined4 *)piVar1[1];
    while (puVar4 = puVar2, puVar4 != (undefined4 *)0x0) {
      piVar1 = (int *)*puVar4;
      puVar2 = (undefined4 *)puVar4[1];
      puVar4[0x2b] = (fVar7 - (float)puVar4[0x27]) * (fVar7 - (float)puVar4[0x27]) +
                     (fVar6 - (float)puVar4[0x26]) * (fVar6 - (float)puVar4[0x26]) +
                     (fVar5 - (float)puVar4[0x25]) * (fVar5 - (float)puVar4[0x25]);
      iVar3 = *piVar1;
      while ((iVar3 != 0 && ((float)puVar4[0x2b] < (float)piVar1[0x2b]))) {
        piVar1 = (int *)*piVar1;
        FUN_0002cc30();
        iVar3 = *piVar1;
        puVar4 = extraout_ECX;
      }
    }
  }
  return;
}




void FUN_0012a7d0(SomeAudioStruct *param_1)

{
  int *piVar1;
  int *piVar2;
  int **ppiVar3;
  int **ppiVar4;
  undefined4 **ppuVar5;
  undefined4 **ppuVar6;
  bool bVar7;
  int **ppiVar8;
  undefined4 **ppuVar9;
  i16 soundSourceIndex;
  int iVar10;
  int local_c;
  undefined4 local_8;
  int *local_4;
  
  ppiVar8 = (int **)param_1->field1_0x4;
  ppiVar3 = &param_1->field1_0x4;
  while (ppiVar4 = ppiVar8, ppiVar4 != (int **)0x0) {
    ppiVar3 = ppiVar4;
    ppiVar8 = (int **)*ppiVar4;
  }
  local_c = 0;
  for (piVar1 = ppiVar3[1]; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
    local_c = local_c + 1;
  }
  ppuVar9 = (undefined4 **)param_1->field3_0xc;
  ppuVar6 = &param_1->field3_0xc;
  while (ppuVar5 = ppuVar9, ppuVar5 != (undefined4 **)0x0) {
    ppuVar6 = ppuVar5;
    ppuVar9 = (undefined4 **)*ppuVar5;
  }
  iVar10 = 0;
  for (piVar1 = ppuVar6[1]; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
    iVar10 = iVar10 + 1;
  }
  local_c = param_1->field0_0x0 - local_c;
  if (iVar10 <= local_c) {
    local_c = iVar10;
  }
  bVar7 = false;
  if (0 < local_c) {
    do {
      piVar1 = param_1->field4_0x10;
      if (*piVar1 != 0) {
        *(int *)(*piVar1 + 4) = piVar1[1];
      }
      if ((int *)piVar1[1] != (int *)0x0) {
        *(int *)piVar1[1] = *piVar1;
      }
      *piVar1 = 0;
      piVar1[1] = 0;
      soundSourceIndex = Audio::CreateSoundSourceAndReturnIndex(AudioType1);
      if (soundSourceIndex != -1) {
        Audio::SoundSources[soundSourceIndex].flags = 0;
        if (Audio::SoundSources[soundSourceIndex].soundSource != (soundSource *)0x0) {
          Audio::SetSoundSourcePosition
                    (Audio::SoundSources[soundSourceIndex].soundSource,(vec3 *)(piVar1 + 0x25));
        }
        if (Audio::SoundSources[soundSourceIndex].soundSource != (soundSource *)0x0) {
          Audio::SetSoundConeOrientation
                    (Audio::SoundSources[soundSourceIndex].soundSource,(vec3 *)(piVar1 + 0x28));
        }
        Audio::FindBySoundbankStrAndPlay((char *)(piVar1 + 4),soundSourceIndex);
      }
      *(i16 *)(piVar1 + 2) = soundSourceIndex;
      if (soundSourceIndex != -1) {
        ppiVar3 = &param_1->field1_0x4;
        piVar2 = param_1->field1_0x4;
        while (piVar2 != (int *)0x0) {
          ppiVar3 = (int **)*ppiVar3;
          piVar2 = *ppiVar3;
        }
        piVar2 = ppiVar3[1];
        ppiVar3[1] = piVar1;
        *piVar1 = (int)ppiVar3;
        piVar1[1] = (int)piVar2;
        if (piVar2 != (int *)0x0) {
          *piVar2 = (int)piVar1;
        }
        if (piVar1[3] != 0) {
          if (!bVar7) {
            local_8 = 0x89;
            bVar7 = true;
          }
          local_4 = piVar1;
          (**(code **)(*(int *)piVar1[3] + 0xc))((int *)piVar1[3],&local_8);
        }
      }
      local_c = local_c + -1;
    } while (local_c != 0);
  }
  while (piVar1 = param_1->field4_0x10, piVar1 != (int *)0x0) {
    if (*piVar1 != 0) {
      *(int *)(*piVar1 + 4) = piVar1[1];
    }
    if ((int *)piVar1[1] != (int *)0x0) {
      *(int *)piVar1[1] = *piVar1;
    }
    *piVar1 = 0;
    piVar1[1] = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_0012e840(AudioParentState param_1)

{
  if (DAT_00433b9c != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(DAT_00433b9c);
    DAT_00433b9c = (void *)0x0;
  }
  if (DAT_00433ba0 != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(DAT_00433ba0);
    DAT_00433ba0 = (void *)0x0;
  }
  if (DAT_00433ba4 != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(DAT_00433ba4);
    DAT_00433ba4 = (void *)0x0;
  }
  BaronDraw_00433b88.stateScalar = 0.0;
  BaronDraw_00433b88.scalar = 0.0;
  BaronDraw_00433b88.type = New_Name;
  BaronDraw_00433b88.field3_0xc = 0;
  BaronDraw_00433b88.field4_0x10 = 0;
  DAT_00433b80 = 1.0;
  DAT_00433bcc = 0;
  DAT_00433bd0 = 0;
  if ((short)PTR_DAT_00433b84 != -1) {
    AudioParent::UpdateState(0,Audio::SoundSources + (short)PTR_DAT_00433b84,param_1);
    PTR_DAT_00433b84._0_2_ = -1;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void __thiscall playBuzzer(AudioParentState param_1,char *param_2)

{
  i16 soundSourceIndex;
  
  if ((short)PTR_DAT_00433b84 != -1) {
    AudioParent::UpdateState(0,Audio::SoundSources + (short)PTR_DAT_00433b84,param_1);
    PTR_DAT_00433b84._0_2_ = -1;
  }
  soundSourceIndex = Audio::CreateSoundSourceAndReturnIndex(AudioType0);
  if (soundSourceIndex != -1) {
    Audio::SoundSources[soundSourceIndex].flags = 0;
    Audio::FindBySoundbankStrAndPlay(param_2,soundSourceIndex);
  }
  PTR_DAT_00433b84._0_2_ = soundSourceIndex;
  return;
}




void __fastcall FUN_00130080(AudioParentState param_1)

{
  if (g_LoadedHeartAsset != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(g_LoadedHeartAsset);
    g_LoadedHeartAsset = (void *)0x0;
  }
  if (g_BrokenHeartAsset != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(g_BrokenHeartAsset);
    g_BrokenHeartAsset = (void *)0x0;
  }
  if (g_InvulnerableHeartAsset != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(g_InvulnerableHeartAsset);
    g_InvulnerableHeartAsset = (void *)0x0;
  }
  if (g_ImpHeadGlowAsset != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(g_ImpHeadGlowAsset);
    g_ImpHeadGlowAsset = (void *)0x0;
  }
  if (g_BaronUIAsset != (void *)0x0) {
    param_1 = Assets::DestroyAssetOrDecrement(g_BaronUIAsset);
    g_BaronUIAsset = (void *)0x0;
  }
  if ((short)PTR_DAT_00433be4 != -1) {
    param_1 = AudioParent::UpdateState(0,Audio::SoundSources + (short)PTR_DAT_00433be4,param_1);
    PTR_DAT_00433be4._0_2_ = -1;
  }
  if (Audio::RandomiserSoundSourceIndex != 0xffff) {
    AudioParent::UpdateState
              (0,Audio::SoundSources + (short)Audio::RandomiserSoundSourceIndex,param_1);
    Audio::RandomiserSoundSourceIndex = 0xffff;
  }
  BaronDraw_00433c10.type = New_Name;
  BaronDraw_00433c10.field3_0xc = 0;
  BaronDraw_00433c10.field4_0x10 = 0;
  g_BaronTexture_.type = New_Name;
  g_BaronTexture_.field3_0xc = 0;
  g_BaronTexture_.field4_0x10 = 0;
  DAT_00433be8 = 0;
  Audio::RandomiserBankIndex = 0;
  BaronDraw_00433c10.stateScalar = 0.0;
  BaronDraw_00433c10.scalar = 0.0;
  g_BaronTexture_.stateScalar = 0.0;
  g_BaronTexture_.scalar = 0.0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_00130830(AudioParentState param_1,char *param_2)

{
  i16 soundSourceIndex;
  
  if ((short)PTR_DAT_00433be4 != -1) {
    AudioParent::UpdateState(0,Audio::SoundSources + (short)PTR_DAT_00433be4,param_1);
    PTR_DAT_00433be4._0_2_ = -1;
  }
  soundSourceIndex = Audio::CreateSoundSourceAndReturnIndex(AudioType0);
  if (soundSourceIndex != -1) {
    Audio::SoundSources[soundSourceIndex].flags = 0;
    Audio::FindBySoundbankStrAndPlay(param_2,soundSourceIndex);
  }
  PTR_DAT_00433be4._0_2_ = soundSourceIndex;
  return;
}




void Audio::LoadRandomiserSounds(char *param_1,undefined4 param_2)

{
  ushort soundSourceIndex;
  
  soundSourceIndex = RandomiserSoundSourceIndex;
                    // If not playing
  if ((RandomiserSoundSourceIndex == 0xffff) &&
     (soundSourceIndex = CreateSoundSourceAndReturnIndex(AudioType0), soundSourceIndex != 0xffff)) {
    SoundSources[(short)soundSourceIndex].flags = 0;
    FindBySoundbankStrAndPlay(param_1,soundSourceIndex);
  }
  RandomiserSoundSourceIndex = soundSourceIndex;
  return;
}




void Audio::PlaySound(char *param_1,AudioParentState parentState)

{
  ushort soundSourceIndex;
  
  if (RandomiserSoundSourceIndex != 0xffff) {
    AudioParent::UpdateState(0,SoundSources + (short)RandomiserSoundSourceIndex,parentState);
    RandomiserSoundSourceIndex = 0xffff;
  }
  soundSourceIndex = CreateSoundSourceAndReturnIndex(AudioType0);
  if (soundSourceIndex != 0xffff) {
    SoundSources[(short)soundSourceIndex].flags = 0;
    FindBySoundbankStrAndPlay(param_1,soundSourceIndex);
  }
  RandomiserSoundSourceIndex = soundSourceIndex;
  return;
}




AudioParentState FUN_001309c0(void)

{
  AudioParentState in_ECX;
  
  if (Audio::RandomiserSoundSourceIndex != 0xffff) {
    in_ECX = AudioParent::UpdateState
                       (0,Audio::SoundSources + (short)Audio::RandomiserSoundSourceIndex,in_ECX);
    Audio::RandomiserSoundSourceIndex = 0xffff;
  }
  return in_ECX;
}




actor * spawnPlayerAtLocationAndRotation(vec3 *rotEuler,char *assetName,vec3 *pos)

{
  char cVar1;
  int iVar2;
  char *player_obj_params;
  actorParams *params;
  actor *paVar3;
  
  if ((assetName == (char *)0x0) || (*(int *)assetName != 0x5f646961)) {
    assetName = Game::PlayerObjParamsAID;
  }
  player_obj_params = GetPlayerActorObjParams();
  if (*(int *)player_obj_params != 0x5f646961) {
    return (actor *)0x0;
  }
  params = (actorParams *)Assets::GetObjParams(player_obj_params);
  paVar3 = (actor *)0x0;
  if (params != (actorParams *)0x0) {
    (params->avatarParams).pos.x = pos->x;
    (params->avatarParams).pos.y = pos->y;
    (params->avatarParams).pos.z = pos->z;
    (params->avatarParams).rotEuler.x = rotEuler->x;
    (params->avatarParams).rotEuler.y = rotEuler->y;
    (params->avatarParams).rotEuler.z = rotEuler->z;
    (params->avatarParams).scale = 1.0;
    *(undefined2 *)((int)&(params->avatarParams).impactId + 2) = 0;
    (params->avatarParams).ghoulyboxId2 = 0;
    if (assetName != (char *)0x0) {
      iVar2 = 0x4ba - (int)assetName;
      do {
        cVar1 = *assetName;
        assetName[(int)params + iVar2] = cVar1;
        assetName = assetName + 1;
      } while (cVar1 != '\0');
    }
    paVar3 = (actor *)Assets::CreateEntityFromParams((objParams *)params);
    free(params);
  }
  return paVar3;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

actor * __fastcall
FUN_001349e0(char *param_1,char *param_2,vec3 *param_3,vec3 *param_4,float param_5,char *param_6,
            char *param_7,actor *param_8,actorDroneTriggerId param_9,vec3 *someVec3,
            vec3 *someOtherVec3,undefined4 *param_12,undefined4 param_13,short param_14)

{
  actor *object;
  Message msg;
  
  object = spawnActor(param_3,param_4,param_6,param_5,(char *)0x0,(char *)0x0,param_7,param_2,
                      param_1,param_14);
  if ((object != (actor *)0x0) && (param_8 != (actor *)0x0)) {
    object->droneTriggerId = param_9;
    if (param_12 != (undefined4 *)0x0) {
      FUN_000280d0(param_12,(int)&object->field_0x998);
    }
    msg.header.msgId = Actor_SetDroneAction;
    msg.header.someActor = param_8;
                    // Calls actor::func3
    (*((object->avatar).vtable)->onMessage)(object,&msg);
  }
  return object;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00137140(undefined4 param_1,float param_2,entityMindPlayer *param_3)

{
  float fVar1;
  actor *paVar2;
  actorBody *paVar3;
  actor *paVar4;
  int extraout_EDX;
  int iVar5;
  float10 fVar6;
  float fVar7;
  vec2 local_c;
  
  paVar2 = (param_3->actorMind).actor;
  paVar3 = paVar2->body;
  if ((paVar3->field13_0x30 == 0) && (paVar3->someTimer2 == 0.0)) {
    if (*(int *)&(param_3->actorMind).field_0x3c == 0) {
      FUN_000251d0();
      iVar5 = *(int *)&(param_3->actorMind).field_0x30;
      if ((iVar5 == 0) || ((param_3->actorMind).minF <= (param_3->actorMind).t)) {
        paVar4 = (param_3->actorMind).targetActor;
        if (((param_3->actorMind).field_0x20 == '\0') || (paVar4 == (actor *)0x0)) {
          FUN_0011bed0(paVar2,param_1,param_2);
        }
        else {
          FUN_0011bff0(paVar4);
        }
        FUN_0002a130();
        iVar5 = extraout_EDX;
      }
      if (iVar5 != 0) {
        (paVar3->camPos).x = *(float *)(iVar5 + 0x28);
        (paVar3->camPos).y = *(float *)(iVar5 + 0x2c);
        (paVar3->camPos).z = *(float *)(iVar5 + 0x30);
        paVar3->field_0x308 = 1;
        return;
      }
      ScriptType1::getControllerXY((InputHandlerType1 *)paVar2->input_handler_,&local_c);
      if ((local_c.x != 0.0) || (local_c.y != 0.0)) {
        fVar1 = (paVar2->avatar).rotEuler.y;
        fVar6 = (float10)FUN_00105d90();
        fVar7 = (float)fVar6;
        local_c.x = fVar7;
        FUN_00100e40(fVar1);
        FUN_00025250(fVar7);
      }
      return;
    }
    fVar7 = (param_3->actorMind).v3.y;
    fVar1 = (param_3->actorMind).v3.z;
    (paVar3->camPos).x = (param_3->actorMind).v3.x;
    (paVar3->camPos).y = fVar7;
    (paVar3->camPos).z = fVar1;
    paVar3->field_0x308 = 1;
  }
  *(undefined4 *)&(param_3->actorMind).field_0x3c = 0;
  return;
}




void __fastcall FUN_0013b7c0(actor *param_1,entityBodyPlayer_0x924 param_2)

{
  CalloutDescriptor **ppCVar1;
  
  ppCVar1 = &(param_1->avatar).callout;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    actor::executeCalloutInDescriptor(*ppCVar1,ProjectileTrail,CalloutCallback1,0,param_1,param_2);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall FUN_0013b7e0(actor *act,entityBodyPlayer_0x924 param_2,avatarCalloutId param_3)

{
  CalloutDescriptor **ppCVar1;
  
  ppCVar1 = &(act->avatar).callout;
  if (ppCVar1 != (CalloutDescriptor **)0x0) {
    actor::executeCalloutInDescriptor(*ppCVar1,param_3,CalloutCallback1,0,act,param_2);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 PlayGhoulLaugh(void)

{
  i16 soundSourceIndex;
  uint uVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar2;
  
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  uVar1 = runtime::rand & 0x7fffff;
  soundSourceIndex = Audio::CreateSoundSourceAndReturnIndex(AudioType0);
  uVar2 = extraout_var;
  if (soundSourceIndex != -1) {
    Audio::SoundSources[soundSourceIndex].flags = 1;
    Audio::FindBySoundbankStrAndPlay
              (audio_asset_name_ARRAY_00314768[-(int)(((float)(uVar1 | 0x3f800000) - 1.0) * -11.0)],
               soundSourceIndex);
    uVar2 = extraout_var_00;
  }
  return CONCAT22(uVar2,soundSourceIndex);
}




undefined4 Audio::PlayRandomBaronLaugh(void)

{
  i16 soundSourceIndex;
  uint uVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar2;
  
  runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
  uVar1 = runtime::rand & 0x7fffff;
  soundSourceIndex = CreateSoundSourceAndReturnIndex(AudioType0);
  uVar2 = extraout_var;
  if (soundSourceIndex != -1) {
    SoundSources[soundSourceIndex].flags = 1;
    FindBySoundbankStrAndPlay
              ("XACT_SOUNDBANK_GBARON_STARTBUTTONLAUGH" +
               (int)(((float)(uVar1 | 0x3f800000) - 1.0) * 0.0) * -0x80,soundSourceIndex);
    uVar2 = extraout_var_00;
  }
  return CONCAT22(uVar2,soundSourceIndex);
}




void __fastcall FUN_00146230(AudioParentState param_1)

{
  int in_EAX;
  int unaff_ESI;
  
  *(char *)(unaff_ESI + 0x93c) = (char)in_EAX;
  if ((in_EAX == 0) && (*(char *)(unaff_ESI + 0xd08) != '\0')) {
    *(undefined1 *)(unaff_ESI + 0xd08) = 0;
    if (*(short *)(unaff_ESI + 0xd88) != -1) {
      AudioParent::UpdateState(0,Audio::SoundSources + *(short *)(unaff_ESI + 0xd88),param_1);
      *(undefined2 *)(unaff_ESI + 0xd88) = 0xffff;
    }
  }
  return;
}




void IXACT_Cue::removeFromInternalLinkedList(IXACT_Cue *param_1)

{
  IXACT_Cue *head;
  IXACT_Cue *prev;
  
  prev = param_1->prev;
  for (head = prev; head != (IXACT_Cue *)0x0; head = head->prev) {
  }
  head = param_1->next;
  prev->next = head;
  if (head != (IXACT_Cue *)0x0) {
    head->prev = prev;
  }
  return;
}




void Audio::SetFormatStringFunctions(MallocFn *param_1,FreeFn *param_2)

{
  MallocFn = param_1;
  FreeFn = param_2;
  return;
}




void Audio::SetFileIOCallbacks(AudioFileReadCallback *callback1,WaitForIOCallback *callback2)

{
  AudioFileReadCallback *local_8;
  WaitForIOCallback *local_4;
  
  local_8 = callback1;
  local_4 = callback2;
  XACT::XACTEngineSetFileIOCallbacks(&local_8);
  return;
}




void Audio::Update(void)

{
  g_TICK_COUNT = XAPILIB::GetTickCount();
  if (deferSettings_ == 1) {
    XACT::IXACTEngine_CommitDeferredSettings(xactEngine_);
  }
  ParseXACTNotifications();
  XACTENG::XACTEngineDoWork();
  return;
}



BOOL XAPILIB::GetFileTime
               (HANDLE hFile,LPFILETIME lpCreationTime,LPFILETIME lpLastAccessTime,
               LPFILETIME lpLastWriteTime)

{
  code *pcVar1;
  BOOL BVar2;
  
  pcVar1 = (code *)swi(3);
  BVar2 = (*pcVar1)();
  return BVar2;
}




void SetVelocity(X3DAUDIO_VECTOR *param_1)

{
  XACT::IXACTEngine_SetListenerVelocity
            (Audio::xactEngine_,param_1->x,param_1->y,param_1->z,Audio::deferSettings_);
  _DAT_004d982c = param_1->x;
  _DAT_004d9830 = param_1->y;
  _DAT_004d9834 = param_1->z;
  return;
}




void SetOrientation(X3DAUDIO_VECTOR *front,X3DAUDIO_VECTOR *top)

{
  X3DAUDIO_VECTOR *pXVar1;
  X3DAUDIO_VECTOR *pXVar2;
  
  pXVar2 = front;
  if (front == (X3DAUDIO_VECTOR *)0x0) {
    pXVar2 = (X3DAUDIO_VECTOR *)&g_XACT_Orient_Front_x;
  }
  pXVar1 = top;
  if (top == (X3DAUDIO_VECTOR *)0x0) {
    pXVar1 = (X3DAUDIO_VECTOR *)&g_XACT_Orient_Top_x;
  }
  XACT::IXACTEngine_SetListenerOrientation
            (Audio::xactEngine_,pXVar2->x,pXVar2->y,pXVar2->z,pXVar1->x,pXVar1->y,pXVar1->z,
             Audio::deferSettings_);
  if (front != (X3DAUDIO_VECTOR *)0x0) {
    g_XACT_Orient_Front_x = front->x;
    g_XACT_Orient_Front_y = front->y;
    g_XACT_Orient_Front_z = front->z;
  }
  if (top != (X3DAUDIO_VECTOR *)0x0) {
    g_XACT_Orient_Top_x = top->x;
    g_XACT_Orient_Top_y = top->y;
    g_XACT_Orient_Top_z = top->z;
  }
  return;
}




void Audio::InitialiseXACTEngine(void)

{
  uint audio_flags;
  XACT_RUNTIME_PARAMETERS xact_params;
  
  maxConcurrentStreams_ = 0x3c;
  xact_params.dwMaxConcurrentStreams = 0x3c;
  xact_params.dwInteractiveAudioLookaheadTime = 0xfa;
  max2DHardwareVoices_ = 0x5a;
  max3DHardwareVoices_ = 0x40;
  xact_params.dwMax2DHwVoices = 0x5a;
  xact_params.dwMax3DHwVoices = 0x40;
  xact_params.dwMaxNotifications = 800;
  XACTENG::XACTEngineCreate(&xact_params,&xactEngine_);
  List::Init((uint *)&List<audioSoundbankPreLoaded>_004d97d4);
  List::Init((uint *)&PreLoadedSoundBanks);
  List::Init((uint *)&SoundSourceList2);
  List::Init((uint *)&SoundSources);
  audio_flags = XAPILIB::XGetAudioFlags();
  if ((audio_flags & 0b1111111111111111) == 1) {
    SpeakerSetup = Mono;
  }
  else {
    SpeakerSetup = ((audio_flags & 0b1111111111111111) != 0) + Stereo;
  }
  UseAC3 = audio_flags >> 0x10 & 1;
  UseDTS = audio_flags >> 0x11 & 1;
  deferSettings_ = (uint)(DAT_00336140 != 0);
  GlobalPositionMultiplier = 1.0;
  DSOUND::DirectSoundUseFullHRTF();
  _DAT_004d97c8 = 1;
  DAT_004d9778 = 1;
  g_TICK_COUNT = XAPILIB::GetTickCount();
  g_TICK_COUNT = XAPILIB::GetTickCount();
  if (deferSettings_ == 1) {
    XACT::IXACTEngine_CommitDeferredSettings(xactEngine_);
  }
  ParseXACTNotifications();
  XACTENG::XACTEngineDoWork();
  return;
}




void SetListenerPosition(X3DAUDIO_VECTOR *position)

{
  XACT::IXACTEngine_SetListenerPosition
            (Audio::xactEngine_,Audio::GlobalPositionMultiplier * position->x,
             Audio::GlobalPositionMultiplier * position->y,
             Audio::GlobalPositionMultiplier * position->z,Audio::deferSettings_);
  g_AudioListenerPosition.x = position->x;
  g_AudioListenerPosition.y = position->y;
  g_AudioListenerPosition.z = position->z;
  return;
}



// WARNING: Unable to use type for symbol ptr

void * Audio::AllocAudioMemory
                 (uint size,char *inStr,undefined4 strSize,char *param_4,undefined4 param_5,
                 undefined4 param_6)

{
  char cVar1;
  audioSoundBankPreLoaded *new_memory;
  char *pcVar2;
  char *new_str;
  uint uVar3;
  audioSoundBankPreLoaded *ptr;
  char *param_2_length;
  
  if (LoggingCallbackFn != (code *)0x0) {
    (*LoggingCallbackFn)(0,size,".\\audiocore.c",param_4,param_5,param_6);
  }
  new_memory = (*MallocFn)(size);
  ptr = new_memory;
                    // memset to 0
  for (uVar3 = size >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    ptr->prev = (audioSoundBankPreLoaded *)0x0;
    ptr = (audioSoundBankPreLoaded *)&ptr->next;
  }
  for (uVar3 = size & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)&ptr->prev = 0;
    ptr = (audioSoundBankPreLoaded *)((int)&ptr->prev + 1);
  }
                    // Find end of string
  pcVar2 = inStr;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  param_2_length = pcVar2 + (1 - (int)(inStr + 1));
  if (LoggingCallbackFn != (code *)0x0) {
    (*LoggingCallbackFn)(0,param_2_length,".\\audiocore.c",param_4,param_5,param_6);
  }
  new_str = (*MallocFn)((uint)param_2_length);
  pcVar2 = new_str;
  for (uVar3 = (uint)param_2_length >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = (uint)param_2_length & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = '\0';
    pcVar2 = pcVar2 + 1;
  }
  new_memory->str = new_str;
  _sprintf(new_str,"%s",inStr);
  new_memory->initialised = 1;
  new_memory->strSize = strSize;
  return new_memory;
}




void AudioPlayerContext::SetMixBins(soundSource *param_1,int param_2)

{
  int iVar1;
  DWORD *pDVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  DWORD num_mixbins;
  _XDSMIXBINS mixbins;
  char acStack_1a0 [32];
  int local_180 [32];
  _XDSMIXBINS bins [32];
  DWORD i;
  DWORD numBins;
  
  piVar5 = local_180;
  local_180[0] = 0;
  for (iVar3 = 0x1f; piVar5 = piVar5 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = 0;
  }
  numBins = *(DWORD *)&param_1->field_0x2c;
  iVar3 = 0;
  num_mixbins = 0;
  if (0 < (int)numBins) {
    pDVar2 = (DWORD *)&param_1->field_0x30;
    do {
      i = *pDVar2;
      bins[i].dwCount = i;
      bins[i].lpMixBinVolumePairs = (LPDSMIXBINVOLUMEPAIR)pDVar2[1];
      iVar1 = iVar3 + 0x70;
      iVar3 = iVar3 + 1;
      pDVar2 = pDVar2 + 2;
      acStack_1a0[i] = param_1->SDBK[iVar1];
      local_180[i] = 1;
      num_mixbins = numBins;
    } while (iVar3 < (int)numBins);
  }
  if (param_2 != 0x1c) {
    puVar4 = &param_2;
    iVar3 = param_2;
    do {
      switch(*(undefined4 *)&param_1->field_0x24) {
      case 1:
      case 3:
      case 4:
        numBins = *(DWORD *)(&DAT_00336270 + iVar3 * 4);
        break;
      default:
        numBins = 0x1c;
        break;
      case 5:
      case 6:
      case 7:
      case 8:
        numBins = *(DWORD *)(&DAT_00336200 + iVar3 * 4);
      }
      if (local_180[numBins] == 0) {
        iVar3 = *(int *)&param_1->field_0x2c;
        local_180[numBins] = 1;
        num_mixbins = num_mixbins + 1;
        bins[numBins].dwCount = numBins;
        bins[numBins].lpMixBinVolumePairs = (LPDSMIXBINVOLUMEPAIR)0x0;
        acStack_1a0[numBins] = '\x7f';
        *(int *)&param_1->field_0x2c = iVar3 + 1;
      }
      iVar3 = puVar4[1];
      puVar4 = puVar4 + 1;
    } while (iVar3 != 0x1c);
  }
  mixbins.lpMixBinVolumePairs = (LPDSMIXBINVOLUMEPAIR)&param_1->field_0x30;
  iVar3 = 0;
  piVar5 = &DAT_003362e4;
  pDVar2 = (DWORD *)mixbins.lpMixBinVolumePairs;
  do {
    iVar1 = piVar5[-1];
    if (local_180[iVar1] != 0) {
      *pDVar2 = bins[iVar1].dwCount;
      pDVar2[1] = (DWORD)bins[iVar1].lpMixBinVolumePairs;
      param_1->SDBK[iVar3 + 0x70] = acStack_1a0[iVar1];
      iVar3 = iVar3 + 1;
      pDVar2 = pDVar2 + 2;
    }
    iVar1 = *piVar5;
    if (local_180[iVar1] != 0) {
      *pDVar2 = bins[iVar1].dwCount;
      pDVar2[1] = (DWORD)bins[iVar1].lpMixBinVolumePairs;
      param_1->SDBK[iVar3 + 0x70] = acStack_1a0[iVar1];
      iVar3 = iVar3 + 1;
      pDVar2 = pDVar2 + 2;
    }
    iVar1 = piVar5[1];
    if (local_180[iVar1] != 0) {
      *pDVar2 = bins[iVar1].dwCount;
      pDVar2[1] = (DWORD)bins[iVar1].lpMixBinVolumePairs;
      param_1->SDBK[iVar3 + 0x70] = acStack_1a0[iVar1];
      iVar3 = iVar3 + 1;
      pDVar2 = pDVar2 + 2;
    }
    iVar1 = piVar5[2];
    if (local_180[iVar1] != 0) {
      *pDVar2 = bins[iVar1].dwCount;
      pDVar2[1] = (DWORD)bins[iVar1].lpMixBinVolumePairs;
      param_1->SDBK[iVar3 + 0x70] = acStack_1a0[iVar1];
      iVar3 = iVar3 + 1;
      pDVar2 = pDVar2 + 2;
    }
    piVar5 = piVar5 + 4;
  } while ((int)piVar5 < 0x336364);
  *(DWORD *)&param_1->field_0x2c = num_mixbins;
  mixbins.dwCount = num_mixbins;
  XACT::IXACTSoundSource_SetMixBins(param_1->xactSoundSource,&mixbins);
  return;
}




void FUN_0015c170(soundSource *param_1,int param_2)

{
  *(uint *)&param_1->field_0x78 = (uint)(param_2 != 0);
  if ((param_2 != 0) != 0) {
    AudioPlayerContext::SetMixBins(param_1,5);
    FUN_0015c0c0(param_1,5,0);
    return;
  }
  FUN_0015c000(param_1,5,0x1c);
  FUN_0015c0c0(param_1,5,0xffffe700);
  return;
}




void __fastcall SetCategoryVolume(undefined4 param_1,WORD param_2,int param_3)

{
  ulonglong uVar1;
  
  uVar1 = FUN_0015b8f0(param_1,param_3);
  XACT::IXACTEngine_SetMasterVolume(Audio::xactEngine_,param_2,(LONG)uVar1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_0015c1e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12)

{
  _DAT_004d97a0 = param_3;
  _DAT_004d97a4 = param_4;
  _DAT_004d97a8 = param_5;
  _DAT_004d97b0 = param_7;
  _DAT_004d979c = param_2;
  _DAT_004d97b8 = param_9;
  _DAT_004d97bc = param_10;
  _DAT_004d97ac = param_6;
  _DAT_004d9798 = param_1;
  _DAT_004d97c0 = param_11;
  _DAT_004d97b4 = param_8;
  _DAT_004d97c4 = param_12;
  XACT::IXACTEngine_SetI3dl2Listener(Audio::xactEngine_,&DAT_004d9798,Audio::deferSettings_);
  return;
}



// WARNING: This is an inlined function

void soundSource::setI3DL2
               (soundSource *source,long direct,long directHF,long room,long roomHF,
               float roomRollOffFactor,long obstLevel,float obstRatio,long occlLevel,float occlRatio
               )

{
  (source->params->dsi3dl2).lDirect = direct;
  (source->params->dsi3dl2).lDirectHF = directHF;
  (source->params->dsi3dl2).lRoom = room;
  (source->params->dsi3dl2).lRoomHF = roomHF;
  (source->params->dsi3dl2).flRoomRolloffFactor = roomRollOffFactor;
  (source->params->dsi3dl2).Obstruction.lHFLevel = obstLevel;
  (source->params->dsi3dl2).Obstruction.flLFRatio = obstRatio;
  (source->params->dsi3dl2).Occlusion.lHFLevel = occlLevel;
  (source->params->dsi3dl2).Occlusion.flLFRatio = occlRatio;
  XACT::IXACTSoundSource_SetI3DL2Source
            (source->xactSoundSource,&source->params->dsi3dl2,Audio::deferSettings_);
  source->params->field_0x24 = 1;
  return;
}




void Audio::soundSource::ctor(AudioSourceType soundType,soundSource **param_2)

{
  HRESULT HVar1;
  soundSourceParams *settings;
  Node<> *root;
  soundSource *newSrc;
  
  newSrc = AllocAudioMemory(0x7c,"soundSource",3,"audioSoundSourceCreate",0x41,0);
  switch(soundType) {
  case AudioType0:
    *(undefined4 *)&newSrc->field_0x24 = 0;
    newSrc->xactSoundSource = (XACTSoundSource *)0x0;
    List::PushGlobal((Node *)&SoundSources,(Node *)&newSrc->next);
    settings = (soundSourceParams *)ExecuteAudioCommand(1,4,"audioSoundSourceCreate",0x59,0);
    newSrc->params = settings;
    break;
  case AudioType1:
  case AudioType3:
  case AudioType4:
    *(AudioSourceType *)&newSrc->field_0x24 = soundType;
    HVar1 = XACTENG::IXACTEngine_CreateSoundSource(xactEngine_,2,&newSrc->xactSoundSource);
    if (HVar1 < 0) {
      FUN_0015baa0(&newSrc,"audioSoundSourceCreate",0x121,0);
      *param_2 = (soundSource *)0x0;
      return;
    }
    List::PushGlobal((Node *)&SoundSources,(Node *)&newSrc->next);
    settings = (soundSourceParams *)ExecuteAudioCommand(1,0x50,"audioSoundSourceCreate",299,0);
    newSrc->params = settings;
    (newSrc->params->pos).x = 0.0;
    (newSrc->params->pos).y = 0.0;
    (newSrc->params->pos).z = 0.0;
    (newSrc->params->velocity).x = 0.0;
    (newSrc->params->velocity).y = 0.0;
    (newSrc->params->velocity).z = 0.0;
    (newSrc->params->coneOrientation).x = 0.0;
    (newSrc->params->coneOrientation).y = 0.0;
    (newSrc->params->coneOrientation).z = 0.0;
    if (soundType == AudioType1) {
      AudioPlayerContext::SetMixBins(newSrc,4);
      newSrc->params[1].pos.x = 0.0;
    }
    else if (soundType == AudioType3) {
      AudioPlayerContext::SetMixBins(newSrc,4);
    }
    else if (soundType == AudioType4) {
      AudioPlayerContext::SetMixBins(newSrc,4);
    }
    FUN_0015c170(newSrc,1);
    break;
  case AudioType5:
    *(undefined4 *)&newSrc->field_0x24 = 5;
    HVar1 = XACTENG::IXACTEngine_CreateSoundSource(xactEngine_,1,&newSrc->xactSoundSource);
    if (HVar1 < 0) {
      FUN_0015baa0(&newSrc,"audioSoundSourceCreate",0x71,0);
      *param_2 = (soundSource *)0x0;
      return;
    }
    List::PushGlobal((Node *)&SoundSources,(Node *)&newSrc->next);
    settings = (soundSourceParams *)ExecuteAudioCommand(1,4,"audioSoundSourceCreate",0x7b,0);
    newSrc->params = settings;
    (settings->pos).x = 0.0;
    AudioPlayerContext::SetMixBins(newSrc,0);
    break;
  case AudioType6:
    *(undefined4 *)&newSrc->field_0x24 = 6;
    HVar1 = XACTENG::IXACTEngine_CreateSoundSource(xactEngine_,1,&newSrc->xactSoundSource);
    if (HVar1 < 0) {
      FUN_0015baa0(&newSrc,"audioSoundSourceCreate",0x99,0);
      *param_2 = (soundSource *)0x0;
      return;
    }
    List::PushGlobal((Node *)&SoundSources,(Node *)&newSrc->next);
    settings = (soundSourceParams *)ExecuteAudioCommand(1,8,"audioSoundSourceCreate",0xa3,0);
    newSrc->params = settings;
    *(undefined1 *)&(settings->pos).x = 0x40;
    (settings->pos).y = 0.0;
    AudioPlayerContext::SetMixBins(newSrc,0);
    break;
  case AudioType7:
    *(undefined4 *)&newSrc->field_0x24 = 7;
    HVar1 = XACTENG::IXACTEngine_CreateSoundSource(xactEngine_,1,&newSrc->xactSoundSource);
    if (HVar1 < 0) {
      FUN_0015baa0(&newSrc,"audioSoundSourceCreate",0xc3,0);
      *param_2 = (soundSource *)0x0;
      return;
    }
    List::PushGlobal((Node *)&SoundSources,(Node *)&newSrc->next);
    settings = (soundSourceParams *)ExecuteAudioCommand(1,8,"audioSoundSourceCreate",0xcd,0);
    newSrc->params = settings;
    *(undefined1 *)&(settings->pos).x = 0x40;
    *(undefined1 *)((int)&(settings->pos).x + 1) = 0;
    (settings->pos).y = 0.0;
    AudioPlayerContext::SetMixBins(newSrc,0);
    break;
  case AudioType8:
    *(undefined4 *)&newSrc->field_0x24 = 8;
    HVar1 = XACTENG::IXACTEngine_CreateSoundSource(xactEngine_,1,&newSrc->xactSoundSource);
    if (HVar1 < 0) {
      FUN_0015baa0(&newSrc,"audioSoundSourceCreate",0xf0,0);
      *param_2 = (soundSource *)0x0;
      return;
    }
    List::PushGlobal((Node *)&SoundSources,(Node *)&newSrc->next);
    settings = (soundSourceParams *)ExecuteAudioCommand(1,0x10,"audioSoundSourceCreate",0xfa,0);
    newSrc->params = settings;
    *(undefined1 *)&(settings->pos).x = 0x40;
    *(undefined1 *)((int)&(settings->pos).x + 1) = 0;
    (settings->pos).y = 0.0;
    AudioPlayerContext::SetMixBins(newSrc,0);
  }
  root = _MostRecentSoundSource;
  if (SoundSourceList2.next == (sourceSource_0x18)0x0) {
    root = &SoundSourceList2;
  }
  List::PushGlobal((Node *)root,(Node *)newSrc);
  _MostRecentSoundSource = (Node<> *)newSrc;
  newSrc->isInitialised_ = 1;
  *param_2 = newSrc;
  return;
}




BOOL audioSoundSource::isValid(soundSource *param_1)

{
  BOOL BVar1;
  soundSource *psVar2;
  
  psVar2 = (soundSource *)Audio::SoundSourceList2.next;
  BVar1 = XAPILIB::IsBadCodePtr((FARPROC)param_1);
  if (BVar1 == 0) {
    if (param_1->xactSoundSource != (XACTSoundSource *)0x0) {
      BVar1 = XAPILIB::IsBadCodePtr((FARPROC)param_1->xactSoundSource);
      if (BVar1 != 0) {
        FUN_0015b920("audioSoundSourceCheckValid : XACTSoundSource : %X Invalid!\n",
                     param_1->xactSoundSource);
        return 0;
      }
    }
    if (psVar2 != (soundSource *)0x0) {
      do {
        if (psVar2 == param_1) {
          return 1;
        }
        psVar2 = *(soundSource **)&psVar2->field_0x4;
      } while (psVar2 != (soundSource *)0x0);
      return 0;
    }
  }
  else {
    FUN_0015b920("audioSoundSourceCheckValid : %X Invalid!\n",param_1);
  }
  return 0;
}




void Audio::SetSoundSourcePosition(soundSource *source,vec3 *pos)

{
  BOOL valid;
  
  valid = audioSoundSource::isValid(source);
  if (valid == 0) {
    FUN_0015b920("audioSoundSourceDestroy : soundSource : %X is no longer valid!\n",source);
    return;
  }
  XACT::IXACTSoundSource_SetPosition
            (source->xactSoundSource,GlobalPositionMultiplier * pos->x,
             GlobalPositionMultiplier * pos->y,GlobalPositionMultiplier * pos->z,deferSettings_);
  (source->params->pos).x = pos->x;
  (source->params->pos).y = pos->y;
  (source->params->pos).z = pos->z;
  return;
}




void Audio::SetSoundSourceVelocity(soundSource *param_1,vec3 *param_2)

{
  BOOL BVar1;
  
  BVar1 = audioSoundSource::isValid(param_1);
  if (BVar1 == 0) {
    FUN_0015b920("audioSoundSourceDestroy : soundSource : %X is no longer valid!\n",param_1);
    return;
  }
  XACT::IXACTSoundSource_SetVelocity
            (param_1->xactSoundSource,GlobalPositionMultiplier * param_2->x,
             GlobalPositionMultiplier * param_2->y,GlobalPositionMultiplier * param_2->z,
             deferSettings_);
  (param_1->params->velocity).x = param_2->x;
  (param_1->params->velocity).y = param_2->y;
  (param_1->params->velocity).z = param_2->z;
  return;
}




void Audio::SetSoundConeOrientation(soundSource *param_1,vec3 *param_2)

{
  BOOL BVar1;
  
  BVar1 = audioSoundSource::isValid(param_1);
  if (BVar1 == 0) {
    FUN_0015b920("audioSoundSourceDestroy : soundSource : %X is no longer valid!\n",param_1);
    return;
  }
  XACT::IXACTSoundSource_SetConeOrientation
            (param_1->xactSoundSource,param_2->x,param_2->y,param_2->z,deferSettings_);
  (param_1->params->coneOrientation).x = param_2->x;
  (param_1->params->coneOrientation).y = param_2->y;
  (param_1->params->coneOrientation).z = param_2->z;
  return;
}




bool FUN_0015c990(soundSource *param_1)

{
  BOOL BVar1;
  int local_4;
  
  BVar1 = audioSoundSource::isValid(param_1);
  if (BVar1 == 0) {
    FUN_0015b920("audioSoundSourceDestroy : soundSource : %X is no longer valid!\n",param_1);
    return true;
  }
  XACT::IXACTSoundSource_GetStatus(param_1->xactSoundSource,&local_4);
  return local_4 == 1;
}




void AudioPlayerContext::free(soundSource **param_1)

{
  soundSource *psVar1;
  BOOL BVar2;
  int iVar3;
  undefined4 uVar4;
  
  BVar2 = audioSoundSource::isValid(*param_1);
  if (BVar2 == 0) {
    FUN_0015b920("audioSoundSourceDestroy : soundSource : %X is no longer valid!\n",param_1);
    return;
  }
  if ((*param_1)->xactSoundSource != (XACTSoundSource *)0x0) {
    iVar3 = FUN_0015c990(*param_1);
    if (iVar3 != 0) {
      return;
    }
    XACT::IXACTSoundSource_Release((*param_1)->xactSoundSource);
    (*param_1)->xactSoundSource = (XACTSoundSource *)0x0;
  }
  psVar1 = *param_1;
  switch(*(undefined4 *)&psVar1->field_0x24) {
  case 0:
    uVar4 = 0x1b6;
    break;
  case 1:
    uVar4 = 0x1cf;
    goto LAB_0015ca96;
  default:
    goto switchD_0015ca3b_caseD_2;
  case 5:
    uVar4 = 0x1bb;
    goto LAB_0015ca7b;
  case 6:
    uVar4 = 0x1c0;
LAB_0015ca96:
    FUN_0015b7b0(psVar1->params,"audioSoundSourceDestroy",uVar4,0);
    (*param_1)->params = (soundSourceParams *)0x0;
    goto switchD_0015ca3b_caseD_2;
  case 7:
    uVar4 = 0x1c5;
    break;
  case 8:
    uVar4 = 0x1ca;
LAB_0015ca7b:
    FUN_0015b7b0(psVar1->params,"audioSoundSourceDestroy",uVar4,0);
    (*param_1)->params = (soundSourceParams *)0x0;
    goto switchD_0015ca3b_caseD_2;
  }
  FUN_0015b7b0(psVar1->params,"audioSoundSourceDestroy",uVar4,0);
  (*param_1)->params = (soundSourceParams *)0x0;
switchD_0015ca3b_caseD_2:
  if ((soundSource *)Audio::_MostRecentSoundSource == *param_1) {
    Audio::_MostRecentSoundSource = *(Node<> **)(*param_1)->SDBK;
  }
  IXACT_Cue::removeFromInternalLinkedList((IXACT_Cue *)*param_1);
  IXACT_Cue::removeFromInternalLinkedList((IXACT_Cue *)&(*param_1)->next);
  FUN_0015baa0(param_1,"audioSoundSourceDestroy",0x1e3,0);
  *param_1 = (soundSource *)0x0;
  return;
}



void Audio::PreloadSoundbank
               (XSoundbankResource *soundbank,DWORD soundbankSize,char *filePath,
               audioSoundBankPreLoaded **outStruct)

{
  audioSoundBankPreLoaded *newSource;
  DWORD size;
  XSoundbankResource *local_4;
  
  size = 0;
  local_4 = (XSoundbankResource *)0x0;
  newSource = AllocAudioMemory(0xa4,filePath,1,"audioSoundBankPreLoadedCreate",99,0);
  if ((soundbank == (XSoundbankResource *)0x0) || (soundbankSize == 0)) {
    FUN_0015bb30(filePath,&local_4,&size);
    newSource->soundbank = local_4;
  }
  else {
    newSource->soundbank = soundbank;
    size = soundbankSize;
    newSource->flags1[0] = '\x01';
  }
  List::PushGlobal((Node *)&PreLoadedSoundBanks,(Node *)newSource);
  XACTENG::IXACTEngine_CreateSoundBank
            (xactEngine_,newSource->soundbank,size,&newSource->xactSoundbank);
  DispatchRegisterNotification(newSource,0);
  DispatchRegisterNotification(newSource,1);
  DispatchRegisterNotification(newSource,2);
  DispatchRegisterNotification(newSource,3);
  newSource->initialised = 1;
  NumSoundbanks = NumSoundbanks + 1;
  List::Init((uint *)&newSource->cursorPos);
  *outStruct = newSource;
  return;
}



undefined4
Audio::audioSoundBankGetCue
          (audioSoundBankPreLoaded *preloaded,uint entryIndex,soundSource *soundSource,
          IXACT_Cue **outAudioCue,void *callback,IXACT_Cue **newCue)

{
  IXACT_Cue *cue;
  HRESULT iVar1;
  undefined4 extraout_ECX;
  int unaff_FS_OFFSET;
  u32 local_10 [4];
  
  cue = AllocAudioMemory(76,"Cue",4,"audioSoundBankGetCue",0x16c,0);
  audioSoundSource::isValid(soundSource);
  cue->entryIndex = entryIndex;
  cue->preloaded = preloaded;
  cue->soundSource = soundSource;
  cue->callback = callback;
  cue->field19_0x28 = 4;
  if (callback != (void *)0x0) {
    (*callback)(cue,4);
  }
  local_10[0] = 8;
  local_10[1] = cue->entryIndex;
  local_10[2] = 0;
  local_10[3] = 0;
  iVar1 = XACT::IXACTSoundBank_PrepareEx
                    ((int)cue->preloaded->xactSoundbank,local_10,(LONG)&cue->someCue,newCue);
  if (iVar1 < 0) {
    runtime::GetLastError(unaff_FS_OFFSET);
    *outAudioCue = (IXACT_Cue *)0x0;
    return extraout_ECX;
  }
  List::PushGlobal((Node *)&preloaded->cursorPos,(Node *)cue);
  *outAudioCue = cue;
  return outAudioCue;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 PlayCue(IXACT_Cue *cue)

{
  int iVar1;
  int unaff_FS_OFFSET;
  undefined4 local_10;
  undefined4 local_c;
  XACTSoundSource *local_8;
  undefined4 local_4;
  
  if ((cue->playbackFlags & 1) != 0) {
    runtime::GetLastError(unaff_FS_OFFSET);
    return 1;
  }
  if ((cue->playbackFlags & 2) != 0) {
    runtime::GetLastError(unaff_FS_OFFSET);
    return 1;
  }
  audioSoundSource::isValid(cue->soundSource);
  local_10 = 4;
  local_c = 0xffffffff;
  local_8 = cue->soundSource->xactSoundSource;
  local_4 = 0;
  iVar1 = XACTENG::IXACTSoundBank_PlayEx(cue->preloaded->xactSoundbank,&local_10,&cue->someCue);
  if (iVar1 < 0) {
    runtime::GetLastError(unaff_FS_OFFSET);
    return 1;
  }
  cue->playbackFlags = cue->playbackFlags | 1;
  _DAT_004d9b70 = _DAT_004d9b70 + 1;
  return 0;
}




audioSoundBankPreLoaded * audioSoundbankPreLoaded::getByXACTSoundbank(XACTSoundbank *param_1)

{
  audioSoundBankPreLoaded *preLoaded;
  
  preLoaded = Audio::PreLoadedSoundBanks.next;
  while( true ) {
    if (preLoaded == (audioSoundBankPreLoaded *)0x0) {
      return (audioSoundBankPreLoaded *)0x0;
    }
    if (preLoaded->xactSoundbank == param_1) break;
    preLoaded = preLoaded->next;
  }
  return preLoaded;
}




void Audio::SetMallocStructInner(IXACT_Cue *param_1,SoundSourceImpl *param_2)

{
  param_1->soundSourceImpl = param_2;
  return;
}




u32 audioCue::get0x14(IXACT_Cue *audio)

{
  return (u32)audio->soundSourceImpl;
}




void audioSoundBankPauseCue(IXACT_Cue *cue,BOOL pause)

{
  int err;
  int unaff_FS_OFFSET;
  
  if ((cue->playbackFlags >> 2 & 1) != pause) {
    err = XACT::IXACTSoundBank_PauseSoundCue
                    (cue->preloaded->xactSoundbank,cue->someCue,(uint)(pause != 0));
    if (err < 0) {
      runtime::GetLastError(unaff_FS_OFFSET);
      return;
    }
                    // Bit 2 of flags becomes bit 0 of param_2
    cue->playbackFlags = cue->playbackFlags ^ ((pause & uVar1) << 2 ^ cue->playbackFlags) & 4;
  }
  return;
}




uint IXACT_Cue::stop(IXACT_Cue *cue,BOOL paused)

{
  uint uVar1;
  uint uVar2;
  uint extraout_ECX;
  
  uVar1 = cue->playbackFlags;
  uVar2 = uVar1;
                    // If not paused
  if ((uVar1 & 2) == 0) {
    uVar2 = uVar1 | 2;
                    // Pause it, and pause the CUE if it has one
    cue->playbackFlags = uVar2;
    if (cue->someCue != (IXACT_Cue *)0x0) {
      if ((uVar1 & 4) != 0) {
        audioSoundBankPauseCue(cue,0);
        paused = 1;
      }
      XACT::IXACTSoundBank_Stop
                (cue->preloaded->xactSoundbank,0xffffffff,-(uint)(paused != 0) & 2,cue->someCue);
      uVar2 = extraout_ECX;
    }
    Audio::SoundbanksStopped_ = Audio::SoundbanksStopped_ + 1;
  }
  return uVar2;
}




void IXACT_Cue::free(IXACT_Cue **cue)

{
  if ((*cue)->someCue != (IXACT_Cue *)0x0) {
    stop(*cue,0);
  }
  removeFromInternalLinkedList(*cue);
  FUN_0015baa0(cue,"audioSoundBankFreeCue",0x26d,0);
  *cue = (IXACT_Cue *)0x0;
  return;
}



void Audio::CreateStreamedWaveBankAtFileOffset
               (char *param_1,DWORD fileOffset,HANDLE param_3,DWORD param_4,
               XACTSoundbank *xactSoundbank,undefined4 *param_6,DWORD packetSizeMs,
               undefined4 param_8,undefined *param_9,HANDLE fileHandle)

{
  audioSoundBankPreLoaded *newNode;
  HANDLE pvVar1;
  DWORD local_14;
  XACT_WAVEBANK_STREAMING_PARAMETERS streamingParams;
  undefined4 local_4;
  
  local_14 = 0;
  newNode = AllocAudioMemory(0x58,param_1,0,"audioWaveBankExpertCreate",0xec,0);
  if (xactSoundbank == (XACTSoundbank *)0x0) {
    if ((param_3 == (HANDLE)0x0) || (param_4 == 0)) {
      FUN_0015bb30(param_1,&newNode->someCallback,&local_14);
    }
    else {
      newNode->someCallback = param_3;
      local_14 = param_4;
      *(undefined1 *)((int)&newNode->soundbank + 1) = 1;
    }
    XACTENG::IXACTEngine_RegisterWaveBank
              (xactEngine_,newNode->someCallback,local_14,(XACTWaveBank **)newNode->flags1);
  }
  else {
    if ((xactSoundbank != (XACTSoundbank *)0x1) && (xactSoundbank != (XACTSoundbank *)0x2))
    goto LAB_0015cfd7;
    streamingParams.dwOffset = 0;
    streamingParams.dwPacketSizeInMilliSecs = 0;
    streamingParams.hFile = (HANDLE)0x0;
    local_4 = 0;
    if (fileHandle == (HANDLE)0x0) {
      pvVar1 = CreateFileForHandle(param_1,0x80000000,1,(char *)0x0,3,0x60000000);
      newNode->someCallback = pvVar1;
    }
    else {
      newNode->someCallback = fileHandle;
      *(undefined1 *)&newNode->soundbank = 1;
    }
    streamingParams.hFile = newNode->someCallback;
    streamingParams.dwOffset = fileOffset;
    streamingParams.dwPacketSizeInMilliSecs = packetSizeMs;
    local_4 = param_8;
    XACTENG::IXACTEngine_RegisterStreamedWaveBank
              (xactEngine_,&streamingParams,(XACTWaveBank **)newNode->flags1);
  }
  List::PushGlobal((Node *)&List<audioSoundbankPreLoaded>_004d97f4,(Node *)&newNode->cursorPos);
LAB_0015cfd7:
  newNode->xactSoundbank = xactSoundbank;
  List::PushGlobal((Node *)&List<audioSoundbankPreLoaded>_004d97d4,(Node *)newNode);
  FUN_0015d180(newNode,3);
  *(undefined4 *)&newNode->field_0x34 = 6;
  newNode->flags2 = newNode->flags2 | 0x40;
  *(undefined **)&newNode->field_0x38 = param_9;
  if (param_9 != (undefined *)0x0) {
    (*(code *)param_9)(newNode,6);
    *param_6 = newNode;
    return;
  }
  *param_6 = newNode;
  return;
}




audioSoundBankPreLoaded * FUN_0015d040(int param_1)

{
  audioSoundBankPreLoaded *paVar1;
  
  paVar1 = List<audioSoundbankPreLoaded>_004d97d4.next;
  while( true ) {
    if (paVar1 == (audioSoundBankPreLoaded *)0x0) {
      return (audioSoundBankPreLoaded *)0x0;
    }
    if (*(int *)paVar1->flags1 == param_1) break;
    paVar1 = paVar1->next;
  }
  return paVar1;
}



// WARNING: This is an inlined function

void FUN_0015d060(char *param_1,XACTSoundbank *xactSoundbank,undefined4 *param_3,DWORD param_4,
                 undefined4 param_5,undefined *callback)

{
  Audio::CreateStreamedWaveBankAtFileOffset
            (param_1,0,(HANDLE)0x0,0,xactSoundbank,param_3,param_4,param_5,callback,(HANDLE)0x0);
  return;
}




undefined4 DispatchRegisterNotification(audioSoundBankPreLoaded *param_1,int param_2)

{
  byte *pbVar1;
  PCXACT_NOTIFICATION_DESCRIPTION pNotificationDesc;
  
  pNotificationDesc = (PCXACT_NOTIFICATION_DESCRIPTION)(param_1->flags1 + param_2 * 0x18 + 0xc);
  pNotificationDesc->wType = 0;
  pNotificationDesc->wFlags = 0;
  pNotificationDesc->pSoundBank = (XACTSoundbank *)0x0;
  pNotificationDesc->pWaveBank = (XACTWaveBank *)0x0;
  pNotificationDesc->dwSoundCueIndex = 0;
  pNotificationDesc->pSoundCue = (IXACT_Cue *)0x0;
  pNotificationDesc->pvContext = (PVOID)0x0;
  switch(param_2) {
  case 0:
    pNotificationDesc->wType = 0;
    break;
  case 1:
    pNotificationDesc->wType = 1;
    break;
  case 2:
    pNotificationDesc->wType = 2;
    break;
  case 3:
    pNotificationDesc->wType = 3;
  }
  pNotificationDesc->wFlags = 0x8002;
  pNotificationDesc->pSoundBank = param_1->xactSoundbank;
  pNotificationDesc->pWaveBank = (XACTWaveBank *)0xffffffff;
  pNotificationDesc->pvContext = (PVOID)0x0;
  XACTENG::IXACTEngine_RegisterNotification(Audio::xactEngine_,pNotificationDesc);
  pbVar1 = (byte *)((int)&pNotificationDesc->wFlags + 1);
  *pbVar1 = *pbVar1 & 0x7f;
  Audio::NumRegisteredNotifications = Audio::NumRegisteredNotifications + 1;
  return 0;
}




undefined4 FUN_0015d180(audioSoundBankPreLoaded *inner,int param_2)

{
  undefined1 *pNotificationDesc;
  
  pNotificationDesc = &inner->field_0x3c;
  *(undefined4 *)pNotificationDesc = 0;
  inner->wavebankptr2 = (XACTWaveBank *)0x0;
  *(undefined4 *)&inner->field_0x44 = 0;
  *(undefined4 *)&inner->field_0x48 = 0;
  *(undefined4 *)&inner->field_0x4c = 0;
  *(undefined4 *)&inner->field_0x50 = 0;
  if (param_2 == 3) {
    *(undefined2 *)pNotificationDesc = 3;
  }
  *(undefined2 *)&inner->field_0x3e = 1;
  inner->wavebankptr2 = *(XACTWaveBank **)inner->flags1;
  *(undefined4 *)&inner->field_0x44 = 0xffffffff;
  *(undefined4 *)&inner->field_0x50 = 0;
  XACTENG::IXACTEngine_RegisterNotification
            (Audio::xactEngine_,(PCXACT_NOTIFICATION_DESCRIPTION)pNotificationDesc);
  Audio::NumRegisteredNotifications = Audio::NumRegisteredNotifications + 1;
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 Audio::ParseXACTNotifications(void)

{
  uint uVar1;
  IXACT_Cue *pSoundCue;
  XACTSoundbank *pXVar2;
  DWORD DVar3;
  int iVar4;
  audioSoundBankPreLoaded *preLoaded;
  code *pcVar5;
  int iVar6;
  undefined4 uVar7;
  XACT_NOTIFICATION_DESCRIPTION notif;
  
  iVar4 = XACTENG::IXACTEngine_GetNotification
                    (xactEngine_,(PCXACT_NOTIFICATION_DESCRIPTION)0x0,&notif);
  pXVar2 = notif.pSoundBank;
  DVar3 = notif.dwSoundCueIndex;
  do {
    if (iVar4 != 0) {
      return 0;
    }
    iVar6 = 0;
    notif.pSoundBank = pXVar2;
    notif.dwSoundCueIndex = DVar3;
    preLoaded = audioSoundbankPreLoaded::getByXACTSoundbank(pXVar2);
    iVar4 = FUN_0015d040(pXVar2);
    if ((preLoaded != (audioSoundBankPreLoaded *)0x0) &&
       ((iVar6 = FUN_0015cd90(preLoaded,DVar3), iVar6 == 0 ||
        (((*(byte *)(iVar6 + 0x34) & 2) != 0 && (notif.wType != 1)))))) goto LAB_0015d341;
    switch(notif.wType) {
    case 0:
      if ((*(uint *)(iVar6 + 0x38) & 1) != 0) goto LAB_0015d341;
      *(undefined4 *)(iVar6 + 0x28) = 0;
      *(uint *)(iVar6 + 0x38) = *(uint *)(iVar6 + 0x38) | 1;
      break;
    case 1:
      uVar1 = *(uint *)(iVar6 + 0x34);
      pSoundCue = *(IXACT_Cue **)(iVar6 + 0x24);
      if ((*(uint *)(iVar6 + 0x38) & 2) != 0) goto LAB_0015d341;
      *(undefined4 *)(iVar6 + 0x28) = 1;
      *(uint *)(iVar6 + 0x34) = uVar1 | 2;
      *(uint *)(iVar6 + 0x38) = *(uint *)(iVar6 + 0x38) | 2;
      *(undefined4 *)(iVar6 + 0x24) = 0;
      if ((pSoundCue != (IXACT_Cue *)0x0) && ((uVar1 >> 1 & 1) == 0)) {
        XACT::IXACTSoundBank_Stop(preLoaded->xactSoundbank,0xffffffff,2,pSoundCue);
        _DAT_004d9b70 = _DAT_004d9b70 + -1;
      }
      break;
    case 2:
      if ((*(uint *)(iVar6 + 0x38) & 4) != 0) goto LAB_0015d341;
      *(undefined4 *)(iVar6 + 0x28) = 2;
      *(HANDLE *)(iVar6 + 0x30) = notif.hEvent;
      *(uint *)(iVar6 + 0x38) = *(uint *)(iVar6 + 0x38) | 4;
      break;
    case 3:
      if (iVar6 == 0) {
        if ((char)*(uint *)(iVar4 + 0x54) < '\0') goto LAB_0015d341;
        *(undefined4 *)(iVar4 + 0x34) = 7;
        *(uint *)(iVar4 + 0x54) = *(uint *)(iVar4 + 0x54) | 0x80;
        goto LAB_0015d32c;
      }
      if ((*(uint *)(iVar6 + 0x38) & 8) == 0) {
        *(undefined4 *)(iVar6 + 0x28) = 3;
        *(uint *)(iVar6 + 0x38) = *(uint *)(iVar6 + 0x38) | 8;
        break;
      }
      goto LAB_0015d341;
    }
    if ((iVar6 == 0) || (pcVar5 = *(code **)(iVar6 + 0x2c), pcVar5 == (code *)0x0)) {
LAB_0015d32c:
      if ((iVar4 != 0) && (pcVar5 = *(code **)(iVar4 + 0x38), pcVar5 != (code *)0x0)) {
        uVar7 = *(undefined4 *)(iVar4 + 0x34);
        goto LAB_0015d33c;
      }
    }
    else {
      uVar7 = *(undefined4 *)(iVar6 + 0x28);
      iVar4 = iVar6;
LAB_0015d33c:
      (*pcVar5)(iVar4,uVar7);
    }
LAB_0015d341:
    iVar4 = XACTENG::IXACTEngine_GetNotification
                      (xactEngine_,(PCXACT_NOTIFICATION_DESCRIPTION)0x0,&notif);
    pXVar2 = notif.pSoundBank;
    DVar3 = notif.dwSoundCueIndex;
  } while( true );
}




undefined1 * FUN_001aa4a0(LPDIRECTSOUND8 param_1)

{
  int iVar1;
  
  if (DAT_0055334c != (LPDIRECTSOUND8)0xffffffff) {
    if (DAT_0055334c == param_1) goto LAB_001aa4c8;
    if (DAT_00553354 != 0) {
      return (undefined1 *)0x0;
    }
  }
  DAT_0055334c = param_1;
LAB_001aa4c8:
  if (DAT_0055334c == (LPDIRECTSOUND8)0x0) {
    DAT_0055335c = DSOUND::DirectSoundCreate;
  }
  else {
    _DAT_00553358 = 0;
  }
  DAT_00553350 = (uint)(DAT_0055334c == (LPDIRECTSOUND8)0x0);
  iVar1 = FUN_001aa170();
  if (iVar1 == 0) {
    return (undefined1 *)0x0;
  }
  DAT_0055336c = DAT_0055336c + -1;
  if ((((DAT_0055336c == 0) && (DAT_00553350 != 0)) && (DAT_0055334c != (LPDIRECTSOUND8)0x0)) &&
     (DAT_0055334c != (LPDIRECTSOUND8)0xffffffff)) {
    DSOUND::IDirectSound_Release(DAT_0055334c);
    DAT_0055334c = (LPDIRECTSOUND8)0xffffffff;
  }
  return &LAB_001aa230;
}



void __thiscall

int XACTENG::XACT_CEngine_RegisterStreamedWaveBank(int param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  int *piVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  *param_3 = 0;
  pvVar3 = XAPILIB::XMemAlloc(0x80,0x6484a004);
  if (pvVar3 != (void *)0x0) {
    iVar4 = FUN_001bc983();
  }
  iVar5 = (-(uint)(iVar4 != 0) & 0x7ff8fff2) + 0x8007000e;
  if ((-1 < iVar5) && (iVar5 = FUN_001bcf05(param_2), -1 < iVar5)) {
    piVar1 = (int *)(iVar4 + 0x58);
    *piVar1 = param_1 + 0x44;
    piVar2 = *(int **)(param_1 + 0x48);
    *(int **)(iVar4 + 0x5c) = piVar2;
    *piVar2 = (int)piVar1;
    *(int **)(*piVar1 + 4) = piVar1;
    *param_3 = iVar4;
    return iVar5;
  }
  if (iVar4 != 0) {
    FUN_001bd33d(iVar4);
  }
  return iVar5;
}




undefined4 XACTENG::XACT_CEngine_RegisterNotification(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = EnterCriticalSectionP();
  uVar2 = FUN_001bba3f(param_2,1);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return uVar2;
}




undefined4 XACTENG::XACT_CEngine_GetNotification(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  KIRQL local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_c = 0;
  FUN_001babbe(local_10);
  piVar4 = (int *)(param_1 + 0x6c);
  piVar3 = (int *)*piVar4;
  if (piVar3 != piVar4) {
    do {
      piVar2 = piVar3 + -10;
      piVar3 = (int *)*piVar3;
      iVar1 = FUN_001bb498(param_2,piVar2);
      if (iVar1 != 0) break;
      piVar2 = (int *)0x0;
    } while (piVar3 != piVar4);
    if (piVar2 != (int *)0x0) {
      piVar3 = piVar2 + 10;
      *(int *)(*piVar3 + 4) = piVar2[0xb];
      *(int *)piVar2[0xb] = *piVar3;
      piVar2[0xb] = (int)piVar3;
      *piVar3 = (int)piVar3;
      piVar3 = piVar2;
      for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *param_3 = *piVar3;
        piVar3 = piVar3 + 1;
        param_3 = param_3 + 1;
      }
      if ((int)(*piVar2 & -0x80000000) == 0) {
        FUN_001bbac0(param_1,piVar2);
      }
      FUN_001bb413(piVar2);
      goto LAB_001bbb77;
    }
  }
  local_8 = 0x80004005;
LAB_001bbb77:
  FUN_001babe0();
  return local_8;
}




void XACT::XACTEngineSetFileIOCallbacks(undefined4 param_1)

{
  int extraout_EDX;
  
  EnterCriticalSectionP();
  FUN_001bb21c(param_1);
  if (extraout_EDX != 0) {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return;
}




void XACTENG::XACT_CEngine_CreateSoundSource(undefined4 param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = FUN_001bbe2d(param_2 | 0x20000000,1,&param_2);
  uVar1 = param_2;
  if ((-1 < iVar2) && (iVar2 = FUN_001c470a(), -1 < iVar2)) {
    *param_3 = uVar1;
  }
  return;
}




void XACTENG::XACTEngineDoWork(void)

{
  char cVar1;
  
  cVar1 = EnterCriticalSectionP();
  if (DAT_001c54f0 != 0) {
    DSOUND::DirectSoundDoWork();
    FUN_001bc362();
  }
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return;
}




HRESULT XACTENG::XACTEngineCreate(XACT_RUNTIME_PARAMETERS *pParams,XACTEngine **ppEngine)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  cVar1 = EnterCriticalSectionP();
  if (DAT_001c54f0 == 0) {
    pvVar2 = XAPILIB::XMemAlloc(0x168,0x6484a000);
    if (pvVar2 == (void *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = FUN_001babf7();
    }
    iVar4 = (-(uint)(iVar3 != 0) & 0x7ff8fff2) + 0x8007000e;
    if ((iVar4 < 0) || (iVar4 = FUN_001bacf6(pParams), iVar4 < 0)) {
      if (iVar3 != 0) {
        FUN_001bc333(iVar3);
      }
    }
    else {
      *ppEngine = (XACTEngine *)(-(uint)(iVar3 != 0) & iVar3 + 8U);
    }
  }
  else {
    *ppEngine = (XACTEngine *)(DAT_001c54f0 + 8);
    FUN_001bacce(DAT_001c54f0);
  }
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return iVar4;
}



HRESULT XACTENG::IXACTEngine_DownloadEffectsImage
                  (XACTEngine *pThis,PVOID pvData,DWORD dwSize,LPVOID pEffectLoc,LPVOID *ppImageDesc
                  )

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = XACT_CEngine_DownloadEffectsImage
                    (-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),pvData,dwSize,
                     pEffectLoc,ppImageDesc);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}



HRESULT XACTENG::IXACTEngine_CreateSoundSource
                  (XACTEngine *pThis,DWORD dwFlags,XACTSoundSource **ppSoundSource)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = XACT_CEngine_CreateSoundSource
                    (-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),dwFlags,ppSoundSource)
  ;
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}



HRESULT XACTENG::IXACTEngine_CreateSoundBank
                  (XACTEngine *pThis,XSoundbankResource *pvData,DWORD dwSize,
                  XACTSoundbank **ppSoundBank)

{
  char cVar1;
  int iVar2;
  
  cVar1 = EnterCriticalSectionP();
  iVar2 = XACT_CEngine_CreateSoundBank
                    (-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),pvData,dwSize,
                     ppSoundBank);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return iVar2;
}



HRESULT XACTENG::IXACTEngine_RegisterWaveBank
                  (XACTEngine *pThis,LPVOID pvData,DWORD dwSize,XACTWaveBank **ppWaveBank)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = XACT_CEngine_RegisterWaveBank
                    (-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),pvData,dwSize,
                     ppWaveBank);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}



HRESULT XACTENG::IXACTEngine_RegisterStreamedWaveBank
                  (XACTEngine *pThis,XACT_WAVEBANK_STREAMING_PARAMETERS *pParams,
                  XACTWaveBank **ppWaveBank)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = XACT_CEngine_RegisterStreamedWaveBank
                    (-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),pParams,ppWaveBank);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}




HRESULT XACT::IXACTEngine_SetMasterVolume(XACTEngine *pThis,WORD wCategory,LONG lVolume)

{
  char cVar1;
  HRESULT HVar2;
  undefined2 in_stack_0000000a;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = FUN_001bb8c8(-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),_wCategory,lVolume);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}




void XACT::IXACTEngine_SetI3dl2Listener(int param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_001bb92c(-(uint)(param_1 != 0) & param_1 - 8U,param_2,param_3);
  return;
}



HRESULT XACT::IXACTEngine_SetListenerOrientation
                  (XACTEngine *pThis,float xFront,float yFront,float zFront,float xTop,float yTop,
                  float zTop,DWORD dwApply)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = FUN_001bb95b(-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),xFront,yFront,zFront
                       ,xTop,yTop,zTop,dwApply);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}



HRESULT XACT::IXACTEngine_SetListenerPosition
                  (XACTEngine *pThis,float x,float y,float z,DWORD dwApply)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = FUN_001bb9b5(-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),x,y,z,dwApply);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}



HRESULT XACT::IXACTEngine_SetListenerVelocity
                  (XACTEngine *pThis,float x,float y,float z,DWORD dwApply)

{
  HRESULT HVar1;
  
  HVar1 = FUN_001bb9fa(-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),x,y,z,dwApply);
  return HVar1;
}



HRESULT XACTENG::IXACTEngine_RegisterNotification
                  (XACTEngine *pThis,PCXACT_NOTIFICATION_DESCRIPTION pNotificationDesc)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = XACT_CEngine_RegisterNotification
                    (-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),pNotificationDesc);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}



HRESULT XACTENG::IXACTEngine_GetNotification
                  (XACTEngine *pThis,PCXACT_NOTIFICATION_DESCRIPTION pNotificationDesc,
                  LPVOID pNotification)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = XACT_CEngine_GetNotification
                    (-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8),pNotificationDesc,
                     pNotification);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}




HRESULT XACT::IXACTEngine_CommitDeferredSettings(XACTEngine *pThis)

{
  HRESULT HVar1;
  
  HVar1 = FUN_001bbbf3(-(uint)(pThis != (XACTEngine *)0x0) & (uint)(pThis + -8));
  return HVar1;
}



HRESULT XACT::IXACTSoundBank_PrepareEx
                  (int cueIndex,DWORD *dwFlags,LONG timeOffset,IXACT_Cue **ppCue)

{
  char cVar1;
  int iVar2;
  
  cVar1 = EnterCriticalSectionP();
  iVar2 = FUN_001c3835(cueIndex,(PrepareExParams *)dwFlags,(int *)timeOffset);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return iVar2;
}



undefined4

XACTENG::IXACTSoundBank_PlayEx(XACTSoundbank *param_1,undefined4 param_2,IXACT_Cue **param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = EnterCriticalSectionP();
  uVar2 = XACT_CSoundBank_Play(param_1,param_2,param_3);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return uVar2;
}



HRESULT XACT::IXACTSoundBank_Stop
                  (XACTSoundbank *pThis,DWORD dwSoundCueIndex,DWORD dwFlags,IXACT_Cue *pSoundCue)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = EnterCriticalSectionP();
  HVar2 = FUN_001c3712(pThis,dwSoundCueIndex,dwFlags,pSoundCue);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return HVar2;
}



undefined4

XACT::IXACTSoundBank_PauseSoundCue(XACTSoundbank *param_1,undefined4 param_2,uint param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = EnterCriticalSectionP();
  uVar2 = FUN_001c2d98(param_1,param_2,param_3);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return uVar2;
}




int XACT::IXACTSoundSource_Release(int param_1)

{
  PRTL_CRITICAL_SECTION CriticalSection;
  int iVar1;
  
  CriticalSection = (PRTL_CRITICAL_SECTION)(param_1 + 0x24);
  RtlEnterCriticalSection(CriticalSection);
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x40) = 0;
    RtlLeaveCriticalSection(CriticalSection);
    if ((*(byte *)(param_1 + 0x17) & 0x20) != 0) {
      FUN_001baf67(param_1);
    }
    FUN_001c435f(1);
    iVar1 = 0;
  }
  else if ((iVar1 == 1) && ((*(byte *)(param_1 + 0x17) & 0x20) == 0)) {
    *(undefined4 *)(param_1 + 0x40) = 0;
    FUN_001c3a94(0);
    RtlLeaveCriticalSection(CriticalSection);
    FUN_001baf67(param_1);
  }
  else {
    RtlLeaveCriticalSection(CriticalSection);
  }
  return iVar1;
}



HRESULT XACT::IXACTSoundSource_SetPosition
                  (XACTSoundSource *pThis,FLOAT x,FLOAT y,FLOAT z,DWORD dwApply)

{
  HRESULT HVar1;
  
  HVar1 = FUN_001c48fa(pThis,x,y,z,dwApply);
  return HVar1;
}



void XACT::IXACTSoundSource_SetConeOrientation
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  FUN_001c49e3(param_1,param_2,param_3,param_4,param_5);
  return;
}




HRESULT XACT::IXACTSoundSource_SetI3DL2Source(void *pBuffer,DSI3DL2BUFFER *pds3db,DWORD dwApply)

{
  float fVar1;
  HRESULT HVar2;
  
  FUN_001c3863((int)pBuffer + 0x24);
  *(long *)((int)pBuffer + 0xc4) = pds3db->lDirect;
  *(long *)((int)pBuffer + 200) = pds3db->lDirectHF;
  *(long *)((int)pBuffer + 0xcc) = pds3db->lRoom;
  *(long *)((int)pBuffer + 0xd0) = pds3db->lRoomHF;
  *(float *)((int)pBuffer + 0xd4) = pds3db->flRoomRolloffFactor;
  *(long *)((int)pBuffer + 0xd8) = (pds3db->Obstruction).lHFLevel;
  *(float *)((int)pBuffer + 0xdc) = (pds3db->Obstruction).flLFRatio;
  *(long *)((int)pBuffer + 0xe0) = (pds3db->Occlusion).lHFLevel;
  fVar1 = (pds3db->Occlusion).flLFRatio;
  *(byte *)((int)pBuffer + 0xc2) = *(byte *)((int)pBuffer + 0xc2) | 0x7f;
  HVar2 = 0;
  *(float *)((int)pBuffer + 0xe4) = fVar1;
  if (dwApply == 0) {
    HVar2 = FUN_001c474b();
  }
  if (pBuffer != (void *)0x0) {
    RtlLeaveCriticalSection(pBuffer);
  }
  return HVar2;
}



HRESULT XACT::IXACTSoundSource_SetVelocity
                  (XACTSoundSource *pThis,FLOAT x,FLOAT y,FLOAT z,DWORD dwApply)

{
  HRESULT HVar1;
  
  HVar1 = FUN_001c4af6(pThis,x,y,z,dwApply);
  return HVar1;
}




HRESULT XACT::IXACTSoundSource_SetMixBins(PRTL_CRITICAL_SECTION param_1,LPDSMIXBINS param_2)

{
  HRESULT HVar1;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  if ((CDirectSoundBuffer *)param_1[1].Synchronization.RawEvent[0] == (CDirectSoundBuffer *)0x0) {
    HVar1 = DSOUND::IDirectSoundStream_SetMixBins
                      ((CDirectSoundStream *)param_1[1].Synchronization.Event.SignalState,param_2);
  }
  else {
    HVar1 = DSOUND::IDirectSoundBuffer_SetMixBins
                      ((CDirectSoundBuffer *)param_1[1].Synchronization.RawEvent[0],param_2);
  }
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return HVar1;
}




HRESULT XACT::IXACTSoundSource_SetMixBinVolumes(PRTL_CRITICAL_SECTION param_1,LPDSMIXBINS param_2)

{
  HRESULT HVar1;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  if ((CDirectSoundBuffer *)param_1[1].Synchronization.RawEvent[0] == (CDirectSoundBuffer *)0x0) {
    HVar1 = DSOUND::IDirectSoundStream_SetMixBinVolumes_8
                      ((CDirectSoundStream *)param_1[1].Synchronization.Event.SignalState,param_2);
  }
  else {
    HVar1 = DSOUND::IDirectSoundBuffer_SetMixBinVolumes_8
                      ((CDirectSoundBuffer *)param_1[1].Synchronization.RawEvent[0],param_2);
  }
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return HVar1;
}




undefined4 XACT::IXACTSoundSource_GetStatus(PRTL_CRITICAL_SECTION param_1,uint *param_2)

{
  int iVar1;
  
  FUN_001c3863((undefined1 *)((int)&param_1[1].Synchronization + 8));
  *param_2 = 0;
  if ((param_1->Synchronization).Event.WaitListHead.Flink < (_LIST_ENTRY *)0x2) {
    iVar1 = FUN_001c3a03();
    if (iVar1 == 0) goto LAB_001c3b23;
  }
  *param_2 = *param_2 | 1;
LAB_001c3b23:
  if (param_1 != (PRTL_CRITICAL_SECTION)0x0) {
    RtlLeaveCriticalSection(param_1);
  }
  return 0;
}




undefined4 * __fastcall FUN_001c28de(XACTSoundbank *param_1)

{
  undefined1 *puVar1;
  
  puVar1 = &param_1->field_0x14;
  param_1->cueIndex = (i32)puVar1;
  *(undefined1 **)puVar1 = puVar1;
  puVar1 = &param_1->field_0xc;
  *(undefined1 **)&param_1->field_0x10 = puVar1;
  *(undefined1 **)puVar1 = puVar1;
  puVar1 = &param_1->field_0x1c;
  *(undefined1 **)&param_1->field_0x20 = puVar1;
  *(undefined1 **)puVar1 = puVar1;
  puVar1 = &param_1->field_0x24;
  *(undefined1 **)&param_1->field_0x28 = puVar1;
  *(undefined1 **)puVar1 = puVar1;
  param_1->numUsages = 1;
  FUN_001bacce(DAT_001c54f0);
  return &param_1->numUsages;
}




void __fastcall IXACTSoundbankHolder::parseCurrentSoundbank(XACTSoundbank *this)

{
  int *piVar1;
  void *pvVar2;
  uint uVar3;
  int *piVar4;
  uint i;
  int cue_i;
  
  pvVar2 = XAPILIB::XMemAlloc((uint)this->soundbank->numSomething << 3,0x6484800b);
  this->cuesAlloc = pvVar2;
  if (-1 < (int)((-(uint)(pvVar2 != (void *)0x0) & 0x7ff8fff2) + 0x8007000e)) {
    uVar3 = 0;
    if (this->soundbank->numSomething != 0) {
      do {
        *(undefined4 *)((int)this->cuesAlloc + uVar3 * 8 + 4) = 0xffffffff;
        uVar3 = uVar3 + 1;
      } while (uVar3 < this->soundbank->numSomething);
    }
    i = 0;
    if (this->soundbank->numCues != 0) {
      cue_i = 0;
      do {
        piVar4 = (int *)((int)this->cuesAlloc +
                        (uint)*(ushort *)((int)&this->soundbank->cues[0].b + cue_i + 2) * 8);
        if (piVar4[1] == -1) {
          piVar4[1] = i;
        }
        else {
          do {
            piVar1 = (int *)*piVar4;
            if (piVar1 == (int *)0x0) break;
            piVar4 = piVar1;
          } while (piVar1 != (int *)0x0);
          pvVar2 = XAPILIB::XMemAlloc(8,0x6484800b);
          *piVar4 = (int)pvVar2;
          if ((int)((-(uint)(pvVar2 != (void *)0x0) & 0x7ff8fff2) + 0x8007000e) < 0) {
            return;
          }
          *(uint *)((int)pvVar2 + 4) = i;
        }
        i = i + 1;
        cue_i = cue_i + 0x14;
      } while (i < this->soundbank->numCues);
    }
  }
  return;
}




undefined4 FUN_001c2d98(XACTSoundbank *param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  
  cVar1 = EnterCriticalSectionP();
  puVar3 = (undefined4 *)(param_2 + 0x28);
  iVar2 = 3;
  do {
    if ((void *)*puVar3 != (void *)0x0) {
      FUN_001c0bda((void *)*puVar3,param_3);
    }
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return 0;
}




void __fastcall FUN_001c3392(XACTSoundbank *param_1)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  puVar5 = *(undefined4 **)&param_1->field_0x14;
  while (puVar5 != (undefined4 *)&param_1->field_0x14) {
    puVar2 = (undefined4 *)*puVar5;
    FUN_001c2f06(puVar5);
    puVar5 = puVar2;
  }
  while (iVar3 = FUN_001baeff(param_1), iVar3 != 0) {
    FUN_001bade1(param_1);
    FUN_001bc362();
  }
  puVar1 = &param_1->field_0xc;
  *(undefined4 *)(*(int *)puVar1 + 4) = *(undefined4 *)&param_1->field_0x10;
  **(undefined4 **)&param_1->field_0x10 = *(undefined4 *)puVar1;
  *(undefined1 **)&param_1->field_0x10 = puVar1;
  *(undefined1 **)puVar1 = puVar1;
  puVar5 = *(undefined4 **)&param_1->field_0x1c;
  while (puVar5 != (undefined4 *)&param_1->field_0x1c) {
    puVar2 = puVar5 + -0x19;
    puVar5 = (undefined4 *)*puVar5;
    FUN_001c53e3(puVar2);
  }
  puVar5 = *(undefined4 **)&param_1->field_0x24;
  while (puVar5 != (undefined4 *)&param_1->field_0x24) {
    puVar2 = puVar5 + -10;
    puVar5 = (undefined4 *)*puVar5;
    FUN_001bbb89(DAT_001c54f0,puVar2);
    FUN_001bbac0(DAT_001c54f0,puVar2);
  }
  FUN_001bc333(DAT_001c54f0);
  if (param_1->wavebankArrayAlloc != (void *)0x0) {
    XAPILIB::XMemFree(param_1->wavebankArrayAlloc,0x64848011);
  }
  uVar4 = 0;
  if (param_1->cuesAlloc != (void *)0x0) {
    if (param_1->soundbank->numSomething != 0) {
      do {
        puVar5 = *(undefined4 **)((int)param_1->cuesAlloc + uVar4 * 8);
        while (puVar5 != (undefined4 *)0x0) {
          puVar2 = (undefined4 *)*puVar5;
          XAPILIB::XMemFree(puVar5,0x6484800b);
          puVar5 = puVar2;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < param_1->soundbank->numSomething);
    }
    XAPILIB::XMemFree(param_1->cuesAlloc,0x6484800b);
    param_1->cuesAlloc = (void *)0x0;
  }
  return;
}




void * __thiscall XACTSoundbank::dtor(void *this,byte param_1)

{
  FUN_001c3392(this);
  if ((param_1 & 1) != 0) {
    XAPILIB::XMemFree(this,0x6484a000);
  }
  return this;
}




int XACTSoundbank::fromResource(XACTSoundbank *this,XSoundbankResource *res,u32 dwSize)

{
  int iVar1;
  void *pvVar2;
  int extraout_EAX;
  
  this->soundbankSize = dwSize;
  this->soundbank = res;
  iVar1 = 0;
  if (res->lenWavebankArray != 0) {
    pvVar2 = XAPILIB::XMemAlloc((uint)res->lenWavebankArray << 2,0x64848011);
    this->wavebankArrayAlloc = pvVar2;
    iVar1 = (-(uint)(pvVar2 != (void *)0x0) & 0x7ff8fff2) + 0x8007000e;
    if (iVar1 < 0) {
      return iVar1;
    }
  }
                    // if it has cue names
  if ((this->soundbank->flags & XSB_FLAGS_NO_CUE_NAMES) == 0) {
    IXACTSoundbankHolder::parseCurrentSoundbank(this);
    iVar1 = extraout_EAX;
  }
  return iVar1;
}



// WARNING: This is an inlined function


int FUN_001c34cb(XACTSoundbank *this,PrepareExParams *param_2,int param_3,int *param_4)

{
  undefined4 uVar1;
  PrepareExParams *pPVar2;
  int iVar3;
  char cVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  int local_10;
  XSoundbankCue *cue;
  undefined4 *local_8;
  
  pPVar2 = param_2;
  uVar7 = 0;
  local_8 = (undefined4 *)0x0;
  local_10 = 0;
  cVar4 = EnterCriticalSectionP();
  cue = this->soundbank->cues + param_2->cueIndex;
  puVar5 = param_2->field6_0xc;
  if ((puVar5 != (uint *)0x0) && (*puVar5 != 0)) {
    param_2 = (PrepareExParams *)0x0;
    do {
      if ((*(short *)(&param_2->field_0x0 + puVar5[1]) == 1) &&
         (iVar6 = _strncmp(s__SoundVariation_001c54e0,
                           *(char **)((int)(&param_2->field_0x0 + puVar5[1]) + 0x14),0x10),
         iVar6 == 0)) {
        local_8 = (undefined4 *)(pPVar2->field6_0xc[1] + 0xc + uVar7 * 0x18);
        break;
      }
      puVar5 = pPVar2->field6_0xc;
      param_2 = (PrepareExParams *)&param_2[1].field5_0x8;
      uVar7 = uVar7 + 1;
    } while (uVar7 < *puVar5);
  }
  if ((cue->flags & 8) == 0) {
    if (local_8 == (undefined4 *)0x0) {
      uVar1 = 0x3f800000;
    }
    else {
      uVar1 = *local_8;
    }
    FUN_001c2dfc(*(undefined4 *)pPVar2,cue,uVar1);
    if (cue->soundIndex == 0xffff) {
      iVar6 = -0x7fffbffb;
      goto LAB_001c35ee;
    }
  }
  iVar6 = FUN_001c2d1c(pPVar2->cueIndex,pPVar2->field5_0x8,&local_10);
  iVar3 = local_10;
  if (-1 < iVar6) {
    if ((pPVar2->field1_0x1 & 1) != 0) {
      FUN_001be74b(param_3);
      *(int *)(param_3 + 0xc) = iVar3;
    }
    if (pPVar2->field6_0xc != (uint *)0x0) {
      iVar6 = FUN_001bc0c6(DAT_001c54f0,pPVar2->field6_0xc,iVar3);
    }
    if ((-1 < iVar6) && (iVar6 = FUN_001bf748(*(undefined4 *)pPVar2), -1 < iVar6)) {
      *param_4 = iVar3;
      goto LAB_001c35ee;
    }
  }
  if (iVar3 != 0) {
    FUN_001bf824(3);
  }
LAB_001c35ee:
  if (cVar4 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return iVar6;
}



// WARNING: Inlined function: FUN_001c34cb


undefined4 XACTENG::XACT_CSoundBank_Play(XACTSoundbank *param_1,uint *param_2,IXACT_Cue **cue)

{
  uint uVar1;
  XACTSoundbank *pXVar2;
  uint *puVar3;
  char cVar4;
  uint *puVar5;
  int iVar6;
  undefined4 uVar7;
  IXACT_Cue **cuee;
  undefined1 *puVar8;
  uint uVar9;
  IXACT_Cue *pIVar10;
  XACTSoundbank *pXStack_48;
  XSoundbankCue *pXStack_44;
  undefined4 *puStack_40;
  undefined1 *puStack_3c;
  undefined4 uStack_38;
  uint *puStack_34;
  uint uStack_30;
  IXACT_Cue *pIStack_2c;
  uint local_1c;
  uint local_18;
  undefined4 local_14;
  uint local_10;
  uint local_c;
  undefined4 local_8;
  
  puVar5 = param_2;
  puVar8 = &stack0xfffffffc;
  local_8 = 0;
  uVar1 = param_2[1];
  local_c = param_2[2];
  uVar9 = *param_2;
  uStack_30 = 0x1c362f;
  param_2 = (uint *)uVar9;
  pIStack_2c = (IXACT_Cue *)uVar1;
  iVar6 = FUN_001c2cfc();
  cuee = cue;
  pXVar2 = param_1;
  if ((iVar6 != 0) && (((uint)param_2 & 0x100) == 0)) {
    uStack_30 = local_c;
    uStack_38 = 0x1c3643;
    puStack_34 = (uint *)iVar6;
    pIStack_2c = (IXACT_Cue *)uVar9;
    uVar7 = FUN_001c531e();
    return uVar7;
  }
  if (((uint)param_2 & 4) == 0) {
    local_10 = puVar5[3];
    local_14 = 0;
    pIStack_2c = (IXACT_Cue *)&param_1;
    puStack_34 = &local_1c;
    local_1c = uVar9 | 8;
    uStack_38 = 0x1c3690;
    uVar9 = 0;
    puStack_40 = (undefined4 *)0x0;
    pXStack_48 = (XACTSoundbank *)0x0;
    puStack_3c = &stack0xfffffffc;
    uStack_30 = iVar6;
    local_18 = uVar1;
    cVar4 = EnterCriticalSectionP(local_1c,puVar5,uVar1);
    puVar3 = puStack_34;
    pXStack_44 = pXVar2->soundbank->cues + puStack_34[1];
    puVar5 = (uint *)puStack_34[3];
    if ((puVar5 != (uint *)0x0) && (*puVar5 != 0)) {
      puStack_34 = (uint *)0x0;
      do {
        if ((*(short *)(puVar5[1] + (int)puStack_34) == 1) &&
           (iVar6 = _strncmp(s__SoundVariation_001c54e0,
                             *(char **)((short *)(puVar5[1] + (int)puStack_34) + 10),0x10),
           iVar6 == 0)) {
          puStack_40 = (undefined4 *)(*(int *)(puVar3[3] + 4) + 0xc + uVar9 * 0x18);
          break;
        }
        puVar5 = (uint *)puVar3[3];
        puStack_34 = puStack_34 + 6;
        uVar9 = uVar9 + 1;
      } while (uVar9 < *puVar5);
    }
    if ((pXStack_44->flags & 8) == 0) {
      if (puStack_40 == (undefined4 *)0x0) {
        uVar7 = 0x3f800000;
      }
      else {
        uVar7 = *puStack_40;
      }
      FUN_001c2dfc(*puVar3,pXStack_44,uVar7);
      if (pXStack_44->soundIndex != 0xffff) goto LAB_001c3581;
      iVar6 = -0x7fffbffb;
    }
    else {
LAB_001c3581:
      iVar6 = FUN_001c2d1c(puVar3[1],puVar3[2],&pXStack_48);
      pXVar2 = pXStack_48;
      if (-1 < iVar6) {
        if ((*puVar3 & 0x100) != 0) {
          FUN_001be74b(uStack_30);
          *(XACTSoundbank **)(uStack_30 + 0xc) = pXVar2;
        }
        if (puVar3[3] != 0) {
          iVar6 = FUN_001bc0c6(DAT_001c54f0,puVar3[3],pXVar2);
        }
        if ((-1 < iVar6) && (iVar6 = FUN_001bf748(*puVar3), -1 < iVar6)) {
          *(XACTSoundbank **)pIStack_2c = pXVar2;
          goto LAB_001c35ee;
        }
      }
      if (pXVar2 != (XACTSoundbank *)0x0) {
        FUN_001bf824(3);
      }
    }
LAB_001c35ee:
    if (cVar4 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
    }
    *(int *)(puStack_3c + -4) = iVar6;
    puVar8 = puStack_3c;
    if (iVar6 < 0) goto LAB_001c3708;
    pIVar10 = *(IXACT_Cue **)(puStack_3c + 8);
    cuee = *(IXACT_Cue ***)(puStack_3c + 0x10);
LAB_001c369d:
    if (-1 < *(int *)(puVar8 + -4)) goto LAB_001c36a3;
  }
  else {
    uStack_30 = puVar5[3];
    pIVar10 = *cue;
    if (uStack_30 != 0) {
      puStack_34 = DAT_001c54f0;
      uStack_38 = 0x1c3667;
      pIStack_2c = pIVar10;
      local_8 = FUN_001bc0c6();
      puVar8 = &stack0xfffffffc;
      goto LAB_001c369d;
    }
LAB_001c36a3:
    if (*(int *)(puVar8 + -8) != 0) {
      pIStack_2c = *(IXACT_Cue **)(puVar8 + -8);
      uStack_30 = 0x1c36b3;
      FUN_001be773();
    }
    pIStack_2c = (IXACT_Cue *)(puVar8 + 0xc);
    uStack_30 = 0x1c36be;
    FUN_001bea70();
    pIStack_2c = *(IXACT_Cue **)(puVar8 + 0xc);
    uStack_30 = 0x1c36c8;
    FUN_001be97c();
    if (*(int *)(puVar8 + -8) != 0) {
      pIStack_2c = (IXACT_Cue *)0x0;
      uStack_30 = 0x1c36d7;
      FUN_001be9b5();
    }
    if ((puVar8[0xc] & 0x80) == 0) {
      pIStack_2c = (IXACT_Cue *)0x1c36eb;
      uVar7 = FUN_001bf04c();
      *(undefined4 *)(puVar8 + -4) = uVar7;
    }
    else {
      pIStack_2c = (IXACT_Cue *)0x1c36e4;
      FUN_001beae3();
    }
    if (-1 < *(int *)(puVar8 + -4)) {
      if (cuee != (IXACT_Cue **)0x0) {
        *cuee = pIVar10;
      }
      goto LAB_001c3708;
    }
  }
  if (pIVar10 != (IXACT_Cue *)0x0) {
    pIStack_2c = (IXACT_Cue *)0x3;
    uStack_30 = 0x1c3700;
    FUN_001bf824();
  }
LAB_001c3708:
  return *(undefined4 *)(puVar8 + -4);
}




u32 XACTSoundbank::decrementUsages(XACTSoundbank *param_1)

{
  u32 uVar1;
  
  param_1->numUsages = param_1->numUsages - 1;
  uVar1 = param_1->numUsages;
  if (param_1->numUsages == 0) {
    dtor(param_1,1);
  }
  return uVar1;
}



// WARNING: Inlined function: FUN_001c34cb


int FUN_001c3835(int cueIndex,PrepareExParams *param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  char cVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  int iStack_20;
  byte *pbStack_1c;
  undefined4 *puStack_18;
  int iStack_c;
  
  uVar6 = 0;
  puStack_18 = (undefined4 *)0x0;
  iStack_20 = 0;
  cVar3 = EnterCriticalSectionP();
  pbStack_1c = (byte *)(*(int *)(cueIndex + 4) + 0x38 + param_2->cueIndex * 0x14);
  puVar4 = param_2->field6_0xc;
  if ((puVar4 != (uint *)0x0) && (*puVar4 != 0)) {
    iStack_c = 0;
    do {
      if ((*(short *)(puVar4[1] + iStack_c) == 1) &&
         (iVar5 = _strncmp(s__SoundVariation_001c54e0,
                           *(char **)((short *)(puVar4[1] + iStack_c) + 10),0x10), iVar5 == 0)) {
        puStack_18 = (undefined4 *)(param_2->field6_0xc[1] + 0xc + uVar6 * 0x18);
        break;
      }
      puVar4 = param_2->field6_0xc;
      iStack_c = iStack_c + 0x18;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *puVar4);
  }
  if ((*pbStack_1c & 8) == 0) {
    if (puStack_18 == (undefined4 *)0x0) {
      uVar1 = 0x3f800000;
    }
    else {
      uVar1 = *puStack_18;
    }
    FUN_001c2dfc(*(undefined4 *)param_2,pbStack_1c,uVar1);
    if (*(short *)(pbStack_1c + 2) == -1) {
      iVar5 = -0x7fffbffb;
      goto LAB_001c35ee;
    }
  }
  iVar5 = FUN_001c2d1c(param_2->cueIndex,param_2->field5_0x8,&iStack_20);
  iVar2 = iStack_20;
  if (-1 < iVar5) {
    if ((param_2->field1_0x1 & 1) != 0) {
      FUN_001be74b(0);
      iRam0000000c = iVar2;
    }
    if (param_2->field6_0xc != (uint *)0x0) {
      iVar5 = FUN_001bc0c6(DAT_001c54f0,param_2->field6_0xc,iVar2);
    }
    if ((-1 < iVar5) && (iVar5 = FUN_001bf748(*(undefined4 *)param_2), -1 < iVar5)) {
      *param_3 = iVar2;
      goto LAB_001c35ee;
    }
  }
  if (iVar2 != 0) {
    FUN_001bf824(3);
  }
LAB_001c35ee:
  if (cVar3 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&RTL_CRITICAL_SECTION_001c5504);
  }
  return iVar5;
}




HRESULT FUN_001c48fa(LPDIRECTSOUNDBUFFER pBuffer,float x,float y,float z,DWORD dwApply)

{
  undefined4 *puVar1;
  HRESULT local_8;
  
  FUN_001c3863((int)pBuffer + 0x24);
  local_8 = 0;
  *(float *)((int)pBuffer + 0x4c) = x;
  *(float *)((int)pBuffer + 0x50) = y;
  *(float *)((int)pBuffer + 0x54) = z;
  puVar1 = *(undefined4 **)((int)pBuffer + 0x15c);
  *(uint *)((int)pBuffer + 0x44) = *(uint *)((int)pBuffer + 0x44) | 0x10000;
  for (; puVar1 != (undefined4 *)((int)pBuffer + 0x15c); puVar1 = (undefined4 *)*puVar1) {
    puVar1[-0x42] = *(float *)((int)pBuffer + 0x4c);
    puVar1[-0x41] = *(undefined4 *)((int)pBuffer + 0x50);
    puVar1[-0x40] = *(undefined4 *)((int)pBuffer + 0x54);
    puVar1[-0x44] = puVar1[-0x44] | 0x10000;
  }
  if (dwApply == 0) {
    local_8 = FUN_001c474b();
  }
  if (pBuffer != (LPDIRECTSOUNDBUFFER)0x0) {
    RtlLeaveCriticalSection(pBuffer);
  }
  return local_8;
}




void FUN_001c4e2b(DSI3DL2LISTENER *param_1,DWORD param_2)

{
  HRESULT HVar1;
  
  _DAT_001c5544 = param_1->lRoom;
  _DAT_001c5548 = param_1->lRoomHF;
  _DAT_001c554c = param_1->flRoomRolloffFactor;
  _DAT_001c5550 = param_1->flDecayTime;
  _DAT_001c5554 = param_1->flDecayHFRatio;
  _DAT_001c5558 = param_1->lReflections;
  _DAT_001c555c = param_1->flReflectionsDelay;
  _DAT_001c5560 = param_1->lReverb;
  _DAT_001c5564 = param_1->flReverbDelay;
  _DAT_001c5568 = param_1->flDiffusion;
  _DAT_001c556c = param_1->flDensity;
  _DAT_001c5570 = param_1->flHFReference;
  _DAT_001c5540 = _DAT_001c5540 | 0xfff;
  HVar1 = DSOUND::IDirectSound_SetI3DL2Listener
                    (*(LPDIRECTSOUND8 *)(DAT_001c54f0 + 0x10),param_1,param_2);
  if ((-1 < HVar1) && (param_2 == 0)) {
    FUN_001c474b();
  }
  return;
}




int DSOUND::DSound_CRefCount_Release(int *param_1)

{
  int iVar1;
  
  if ((param_1[1] == 0) || (iVar1 = param_1[1] + -1, param_1[1] = iVar1, iVar1 != 0)) {
    iVar1 = param_1[1];
  }
  else {
    (**(code **)(*param_1 + 0xc))(param_1);
    iVar1 = 0;
  }
  return iVar1;
}




undefined4 DSOUND::DirectSoundEnterCriticalSection(void)

{
  int unaff_FS_OFFSET;
  
  if (*(char *)(unaff_FS_OFFSET + 0x24) != '\0') {
    return 0;
  }
  RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
  return 1;
}




ULONG DSOUND::IDirectSound_Release(LPDIRECTSOUND8 pThis)

{
  int *piVar1;
  ULONG UVar2;
  
  piVar1 = (int *)(-(uint)(pThis != (LPDIRECTSOUND8)0x0) & (int)pThis - 8U);
  UVar2 = (**(code **)(*piVar1 + 8))(piVar1);
  return UVar2;
}



HRESULT DSOUND::IDirectSoundBuffer_Unlock
                  (CDirectSoundBuffer *pThis,LPVOID ppvAudioPtr1,DWORD pdwAudioBytes1,
                  LPVOID ppvAudioPtr2,DWORD pdwAudioBytes2)

{
  return 0;
}




ULONG DSOUND::IDirectSoundBuffer_Release(CDirectSoundBuffer *pThis)

{
  int *piVar1;
  ULONG UVar2;
  
  piVar1 = (int *)(-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                  (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume);
  UVar2 = (**(code **)(*piVar1 + 8))(piVar1);
  return UVar2;
}




void DSOUND::DirectSoundUseFullHRTF(void)

{
  char cVar1;
  
  cVar1 = DirectSoundEnterCriticalSection();
  CHRTFSource_SetFullHRTF5Channel();
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
  }
  return;
}




undefined4 DSOUND::XAudioCalculatePitch(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  
  FUN_001c5849();
  if (param_1 == 48000) {
    uVar2 = 0;
  }
  else {
    fVar1 = (float)param_1;
    if (param_1 < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    uVar2 = FUN_001cb40d(fVar1 * 2.0833333e-05);
  }
  FUN_001c586e();
  return uVar2;
}




void DSOUND::XAudioCreatePcmFormat(ushort param_1,int param_2,ushort param_3,undefined2 *param_4)

{
  uint uVar1;
  
  param_4[1] = param_1;
  param_4[7] = param_3;
  uVar1 = (int)((uint)param_1 * (uint)param_3) / 8;
  param_4[8] = 0;
  *(int *)(param_4 + 2) = param_2;
  *param_4 = 1;
  param_4[6] = (short)uVar1;
  *(uint *)(param_4 + 4) = (uVar1 & 0xffff) * param_2;
  return;
}




void DSOUND::XAudioCreateAdpcmFormat(WORD nChannels,DWORD nSamplesPerSec,LPXBOXADPCMWAVEFORMAT pwfx)

{
  *(DWORD *)&pwfx->wSamplesPerBlock = nSamplesPerSec;
  *(WORD *)((int)&pwfx->wfx + 2) = nChannels;
  *(undefined2 *)&pwfx->wfx = 0x69;
  *(undefined2 *)&pwfx[1].field_0x6 = 4;
  pwfx[1].wSamplesPerBlock = nChannels * 0x24;
  pwfx[1].wfx = (WAVEFORMATEX)((nSamplesPerSec >> 6) * 0x24);
  *(undefined2 *)&pwfx[2].wfx = 2;
  *(undefined2 *)((int)&pwfx[2].wfx + 2) = 0x40;
  return;
}




undefined4 DSOUND::CDirectSound_SetMixBinHeadroom(int param_1,int param_2,undefined1 param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    *(undefined1 *)(*(int *)(param_1 + 8) + 0x10 + param_2) = param_3;
    uVar2 = CMcpxAPU_SetMixBinHeadroom(param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




void DSOUND::CDirectSound_DoWork(void)

{
  char cVar1;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    CMcpxAPU_ServiceDeferredCommandsLow();
  }
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
  }
  return;
}




void __thiscall DSOUND::CDirectSoundVoiceSettings_SetMixBinVolumes(int param_1,uint *param_2)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*param_2 != 0) {
    do {
      piVar1 = (int *)(param_2[1] + uVar2 * 8);
      uVar2 = uVar2 + 1;
      *(int *)(param_1 + 0x30 + *piVar1 * 4) = piVar1[1];
    } while (uVar2 < *param_2);
  }
  return;
}




void DSOUND::CDirectSoundVoice_SetPitch(int param_1,undefined4 param_2)

{
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x18) = param_2;
  CMcpxVoiceClient_SetPitch();
  return;
}




void DSOUND::CDirectSoundVoice_SetVolume(int param_1,int param_2)

{
  *(int *)(*(int *)(param_1 + 0x10) + 0x1c) = param_2 - *(int *)(*(int *)(param_1 + 0x10) + 0x20);
  CMcpxVoiceClient_SetVolume();
  return;
}




void DSOUND::CDirectSoundVoice_SetLFO(undefined4 param_1,undefined4 param_2)

{
  CMcpxVoiceClient_SetLFO(param_2);
  return;
}




void DSOUND::CDirectSoundVoice_SetEG(undefined4 param_1,undefined4 param_2)

{
  CMcpxVoiceClient_SetEG(param_2);
  return;
}




void DSOUND::CDirectSoundVoice_SetFilter(undefined4 param_1,undefined4 param_2)

{
  CMcpxVoiceClient_SetFilter(param_2);
  return;
}




void DSOUND::CDirectSoundVoice_SetHeadroom(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *(int *)(iVar1 + 0x1c) = *(int *)(iVar1 + 0x1c) + (*(int *)(iVar1 + 0x20) - param_2);
  *(int *)(iVar1 + 0x20) = param_2;
  CMcpxVoiceClient_SetVolume();
  return;
}




void DSOUND::CDirectSoundVoice_SetMixBinVolumes(undefined4 param_1,undefined4 param_2)

{
  CDirectSoundVoiceSettings_SetMixBinVolumes(param_2);
  CMcpxVoiceClient_SetVolume();
  return;
}




undefined4 DSOUND::CDirectSoundVoice_CommitDeferredSettings(void)

{
  CMcpxVoiceClient_Commit3dSettings();
  return 0;
}




void DSOUND::CDirectSoundVoice_GetVoiceProperties(undefined4 param_1,undefined4 param_2)

{
  CMcpxVoiceClient_GetVoiceProperties(param_2);
  return;
}




undefined4 DSOUND::CDirectSoundVoice_Set3DVoiceData(int param_1,byte *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(*(int *)(param_1 + 0x10) + 0xb8);
  if ((puVar1 == (undefined4 *)0x0) || ((char)*(undefined4 *)param_2 == '\0')) {
    if ((*param_2 & 0x40) != 0) {
      FUN_001cc50a(0,param_2);
    }
  }
  else {
    *puVar1 = *(undefined4 *)param_2;
    if ((*param_2 & 1) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 4) = *(undefined4 *)(param_2 + 4);
    }
    if ((*param_2 & 2) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 8) = *(undefined4 *)(param_2 + 8);
    }
    if ((*param_2 & 4) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0xc) =
           *(undefined4 *)(param_2 + 0xc);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x10) =
           *(undefined4 *)(param_2 + 0x10);
    }
    if ((*param_2 & 8) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x14) =
           *(undefined4 *)(param_2 + 0x14);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x18) =
           *(undefined4 *)(param_2 + 0x18);
    }
    if ((*param_2 & 0x10) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x1c) =
           *(undefined4 *)(param_2 + 0x1c);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x20) =
           *(undefined4 *)(param_2 + 0x20);
    }
    if ((*param_2 & 0x20) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x24) =
           *(undefined4 *)(param_2 + 0x24);
    }
    if ((*param_2 & 0x40) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x28) =
           *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x2c) =
           *(undefined4 *)(param_2 + 0x2c);
    }
    if ((*param_2 & 0x80) != 0) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x30) =
           *(undefined4 *)(param_2 + 0x30);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0xb8) + 0x34) =
           *(undefined4 *)(param_2 + 0x34);
    }
    FUN_001cd054();
  }
  return 0;
}




undefined4 DSOUND::CDirectSoundVoice_Use3DVoiceData(int param_1,int param_2)

{
  byte *pbVar1;
  
  if (param_2 == 0) {
    pbVar1 = (byte *)(*(int *)(param_1 + 0x10) + 0xb);
    *pbVar1 = *pbVar1 & 0xfe;
  }
  else {
    pbVar1 = (byte *)(*(int *)(param_1 + 0x10) + 0xb);
    *pbVar1 = *pbVar1 | 1;
  }
  return 0;
}




undefined4 DSOUND::CDirectSoundBuffer_Play(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000010;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CMcpxBuffer_Play(in_stack_00000010);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_Stop(void)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CMcpxBuffer_Stop(0);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}



undefined4
DSOUND::CDirectSoundBuffer_StopEx
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CMcpxBuffer_Stop_Ex(param_2,param_3,param_4);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_GetStatus(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CMcpxBuffer_GetStatus(param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetLoopRegion(int param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  
  cVar2 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 != 0) {
    if (cVar2 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    return 0x80004005;
  }
  iVar1 = *(int *)(param_1 + 0x1c);
  if (param_3 == 0) {
    param_3 = *(int *)(iVar1 + 200) - param_2;
  }
  else if (*(uint *)(iVar1 + 200) < (uint)(param_2 + param_3)) {
    uVar3 = 0x88780032;
    goto LAB_001c6303;
  }
  *(int *)(iVar1 + 0xcc) = param_2;
  *(int *)(iVar1 + 0xd0) = param_3;
  uVar3 = FUN_001ce043();
LAB_001c6303:
  if (cVar2 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
  }
  return uVar3;
}



undefined4
DSOUND::CDirectSoundBuffer_GetCurrentPosition
          (undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CMcpxBuffer_GetCurrentPosition(param_2,param_3);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}



int DSOUND::CDirectSoundBuffer_Lock
              (int param_1,int param_2,uint param_3,int *param_4,uint *param_5,undefined4 *param_6,
              int *param_7,byte param_8)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int local_8;
  
  local_8 = 0;
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    if (((param_8 & 1) == 0) ||
       (local_8 = CDirectSoundBuffer_GetCurrentPosition(param_1,0,&param_2), -1 < local_8)) {
      uVar2 = param_3;
      if ((param_8 & 2) != 0) {
        uVar2 = *(uint *)(*(int *)(param_1 + 0x1c) + 0xc0);
      }
      *param_4 = *(int *)(*(int *)(param_1 + 0x1c) + 0xbc) + param_2;
      uVar3 = uVar2;
      if ((uint)(*(int *)(*(int *)(param_1 + 0x1c) + 0xc0) - param_2) <= uVar2) {
        uVar3 = *(int *)(*(int *)(param_1 + 0x1c) + 0xc0) - param_2;
      }
      *param_5 = uVar3;
      if ((param_6 != (undefined4 *)0x0) && (param_7 != (int *)0x0)) {
        if (uVar3 < uVar2) {
          *param_6 = *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xbc);
          *param_7 = uVar2 - *param_5;
        }
        else {
          *param_6 = 0;
          *param_7 = 0;
        }
      }
    }
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    local_8 = -0x7fffbffb;
  }
  return local_8;
}




undefined4 DSOUND::CDirectSoundBuffer_SetCurrentPosition(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CMcpxBuffer_SetCurrentPosition(param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




ULONG DSOUND::CDirectSoundStream_AddRef(CDirectSoundStream *pThis)

{
  char cVar1;
  ULONG UVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    *(int *)(pThis + 8) = *(int *)(pThis + 8) + 1;
    UVar2 = *(ULONG *)(pThis + 8);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    UVar2 = 0x80004005;
  }
  return UVar2;
}




ULONG DSOUND::CDirectSoundStream_Release(CDirectSoundStream *pThis)

{
  char cVar1;
  ULONG UVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    UVar2 = DSound_CRefCount_Release(pThis + 4);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    UVar2 = 0x80004005;
  }
  return UVar2;
}




HRESULT DSOUND::CDirectSoundStream_GetInfo(CDirectSoundStream *pThis,LPXMEDIAINFO pInfo)

{
  char cVar1;
  HRESULT HVar2;
  DWORD DVar3;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    pInfo->dwFlags = 5;
    DVar3 = FUN_001c5a62();
    pInfo->dwMaxLookahead = DVar3;
    DVar3 = *(DWORD *)(*(int *)(pThis + 0x20) + 0x14);
    pInfo->dwOutputSize = 0;
    pInfo->dwInputSize = DVar3;
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = 0;
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_Discontinuity(CDirectSoundStream *pThis)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CMcpxStream_Discontinuity();
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_Flush(CDirectSoundStream *pThis)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    CMcpxStream_Flush(0);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = 0;
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}



HRESULT DSOUND::CDirectSoundStream_Process
                  (CDirectSoundStream *pThis,PXMEDIAPACKET pInputBuffer,PXMEDIAPACKET pOutputBuffer)

{
  char cVar1;
  HRESULT HVar2;
  uint local_8;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CMcpxStream_GetStatus(&local_8);
    if (-1 < HVar2) {
      if ((local_8 & 1) == 0) {
        HVar2 = -0x7787ffce;
      }
      if (-1 < HVar2) {
        HVar2 = FUN_001cb1c2(pInputBuffer);
      }
    }
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_Pause(CDirectSoundStream *pThis,DWORD dwPause)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CMcpxStream_Pause(dwPause);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}



HRESULT DSOUND::CDirectSoundStream_FlushEx
                  (CDirectSoundStream *pThis,REFERENCE_TIME rtTimeStamp,DWORD dwFlags)

{
  char cVar1;
  HRESULT HVar2;
  undefined4 in_stack_00000008;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    if (rtTimeStamp._4_4_ == 0) {
      CMcpxStream_Flush(0);
      HVar2 = 0;
    }
    else {
      HVar2 = CMcpxStream_Stop_Ex(in_stack_00000008,rtTimeStamp);
    }
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




void DSOUND::CDirectSound3DCalculator_GetVoiceData(DWORD a1,DWORD a2,DWORD a3,DWORD a4,DWORD a5)

{
  uint uVar1;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  int local_c;
  int local_8;
  
  FUN_001c5849();
  uVar1 = *(uint *)a1 | *(uint *)a2;
  if ((uVar1 & 0x400000) != 0) {
    uVar1 = uVar1 | 0xffff0000;
  }
  if ((uVar1 & 0x15200010) != 0) {
    if (*(int *)(a2 + 0x40) == 2) {
      local_38 = 0;
    }
    else {
      FUN_001c5941(*(float *)(a1 + 0x3c) * *(float *)(a2 + 0x48),*(undefined4 *)(a2 + 0x38),
                   *(undefined4 *)(a2 + 0x3c),*(undefined4 *)(a2 + 0x50),*(undefined4 *)(a2 + 0x54),
                   *(undefined4 *)(a2 + 0x68),*(uint *)(a2 + 0x58) >> 2 & 1,&local_38);
    }
    if (local_38 != *(int *)(a5 + 4)) {
      *(uint *)a5 = *(uint *)a5 | 1;
      *(int *)(a5 + 4) = local_38;
    }
  }
  if ((uVar1 & 0x40140000) != 0) {
    if (*(int *)(a2 + 0x40) == 2) {
      local_34 = 0;
    }
    else {
      FUN_001c5978(*(undefined4 *)(a2 + 0x20),*(undefined4 *)(a2 + 0x24),*(undefined4 *)(a2 + 0x34),
                   *(undefined4 *)(a2 + 0x70),&local_34);
    }
    if (local_34 != *(int *)(a5 + 8)) {
      *(uint *)a5 = *(uint *)a5 | 2;
      *(int *)(a5 + 8) = local_34;
    }
  }
  if ((uVar1 & 0x34800008) != 0) {
    if (*(int *)(a2 + 0x40) == 2) {
      local_30 = 0;
      local_2c = 0;
    }
    else {
      FUN_001c5998(*(float *)(a1 + 0x38) * *(float *)(a2 + 0x44),*(undefined4 *)(a2 + 0x68),
                   *(undefined4 *)(a2 + 0x74),*(undefined4 *)(a2 + 0x78),*(uint *)(a2 + 0x58) & 1,
                   &local_30,&local_2c);
    }
    if ((local_30 != *(int *)(a5 + 0xc)) || (local_2c != *(int *)(a5 + 0x10))) {
      *(uint *)a5 = *(uint *)a5 | 4;
      *(int *)(a5 + 0xc) = local_30;
      *(int *)(a5 + 0x10) = local_2c;
    }
  }
  if ((uVar1 & 0x24000000) != 0) {
    if ((*(int *)(a2 + 0x40) == 2) || ((*(byte *)(a2 + 0x58) & 2) == 0)) {
      local_28 = 0;
      local_24 = 0;
    }
    else {
      FUN_001c59cc(*(undefined4 *)(a2 + 0x74),*(undefined4 *)(a2 + 0x78),&local_28,&local_24);
    }
    if ((local_28 != *(int *)(a5 + 0x14)) || (local_24 != *(int *)(a5 + 0x18))) {
      *(uint *)a5 = *(uint *)a5 | 8;
      *(int *)(a5 + 0x14) = local_28;
      *(int *)(a5 + 0x18) = local_24;
    }
  }
  if ((uVar1 & 0x82800028) != 0) {
    if (*(int *)(a2 + 0x40) == 2) {
      local_18 = 0;
    }
    else {
      FUN_001c59ee(*(float *)(a1 + 0x38) * *(float *)(a2 + 0x44),
                   *(float *)(a1 + 0x40) * *(float *)(a2 + 0x4c),*(undefined4 *)(a2 + 0x6c),
                   &local_18);
    }
    if (local_18 != *(int *)(a5 + 0x24)) {
      *(uint *)a5 = *(uint *)a5 | 0x20;
      *(int *)(a5 + 0x24) = local_18;
    }
  }
  if ((uVar1 & 0x20000000) != 0) {
    if (*(int *)(a2 + 0x40) == 2) {
      local_14 = 0.0;
      local_10 = 0.0;
    }
    else {
      local_14 = *(float *)(a2 + 0x74);
      local_10 = *(float *)(a2 + 0x78);
    }
    if ((local_14 != *(float *)(a5 + 0x28)) || (local_10 != *(float *)(a5 + 0x2c))) {
      *(float *)(a5 + 0x28) = local_14;
      *(uint *)a5 = *(uint *)a5 | 0x40;
      *(float *)(a5 + 0x2c) = local_10;
    }
  }
  if (((a3 != 0) && (a4 != 0)) &&
     (((uVar1 & 0x14000000) != 0 || (((*(uint *)a3 | *(uint *)a4) & 0x7f0804) != 0)))) {
    if (*(int *)(a2 + 0x40) == 2) {
      local_20 = 0;
      local_1c = 0;
      local_c = 0;
      local_8 = 0;
    }
    else {
      FUN_001ce923(*(undefined4 *)(a2 + 0x68),*(undefined4 *)(a3 + 0xc),*(undefined4 *)(a3 + 0x30),
                   a4,&local_20,&local_1c,&local_c,&local_8);
      if ((*(byte *)(a2 + 0x58) & 2) != 0) {
        local_8 = local_c;
      }
    }
    if ((local_20 != *(int *)(a5 + 0x1c)) || (local_1c != *(int *)(a5 + 0x20))) {
      *(uint *)a5 = *(uint *)a5 | 0x10;
      *(int *)(a5 + 0x1c) = local_20;
      *(int *)(a5 + 0x20) = local_1c;
    }
    if ((local_c != *(int *)(a5 + 0x30)) || (local_8 != *(int *)(a5 + 0x34))) {
      *(byte *)a5 = *(byte *)a5 | 0x80;
      *(int *)(a5 + 0x30) = local_c;
      *(int *)(a5 + 0x34) = local_8;
    }
  }
  FUN_001c586e();
  return;
}




undefined4 DSOUND::CDirectSoundBuffer_SetVolume(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetVolume(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetPitch(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetPitch(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetLFO(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetLFO(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetEG(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetEG(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetFilter(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetFilter(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetHeadroom(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetHeadroom(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetMixBinVolumes(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetMixBinVolumes(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_GetVoiceProperties(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_GetVoiceProperties(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_Set3DVoiceData(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_Set3DVoiceData(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_Use3DVoiceData(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int extraout_ECX;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_Use3DVoiceData(param_1,param_2);
    if (extraout_ECX != 0) {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetPitch(CDirectSoundStream *pThis,LONG lPitch)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetPitch(pThis + 4,lPitch);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetVolume(CDirectSoundStream *pStream,LONG lVolume)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetVolume(pStream + 4,lVolume);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetLFO(CDirectSoundStream *pThis,LPCDSLFODESC pLFODesc)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetLFO(pThis + 4,pLFODesc);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetEG(CDirectSoundStream *pThis,DSENVOLOPEDESC *pEnvelopeDesc)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetEG(pThis + 4,pEnvelopeDesc);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetFilter(CDirectSoundStream *pThis,DSFILTERDESC *pFilterDesc)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetFilter(pThis + 4,pFilterDesc);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetHeadroom(CDirectSoundStream *pThis,DWORD dwHeadroom)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetHeadroom(pThis + 4,dwHeadroom);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}



HRESULT DSOUND::CDirectSoundStream_SetMixBinVolumes_8
                  (CDirectSoundStream *pThis,LPDSMIXBINS pMixBins)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetMixBinVolumes(pThis + 4,pMixBins);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}



HRESULT DSOUND::CDirectSoundStream_GetVoiceProperties
                  (CDirectSoundStream *pThis,DSVOICEPROPS *pVoiceProps)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_GetVoiceProperties(pThis + 4,pVoiceProps);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




undefined4 DSOUND::CDirectSoundStream_Set3DVoiceData(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_Set3DVoiceData(param_1 + 4,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundStream_Use3DVoiceData(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int extraout_ECX;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_Use3DVoiceData(param_1 + 4,param_2);
    if (extraout_ECX != 0) {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}



HRESULT DSOUND::IDirectSound_DownloadEffectsImage
                  (LPDIRECTSOUND8 pThis,LPCVOID pvImageBuffer,DWORD dwImageSize,PVOID pImageLoc,
                  PVOID *ppImageDesc)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSound_DownloadEffectsImage
                    (-(uint)(pThis != (LPDIRECTSOUND8)0x0) & (int)pThis - 8U,pvImageBuffer,
                     dwImageSize,pImageLoc,ppImageDesc);
  return HVar1;
}



HRESULT DSOUND::IDirectSound_SetMixBinHeadroom
                  (LPDIRECTSOUND8 pThis,DWORD dwMixBinMask,DWORD dwHeadroom)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSound_SetMixBinHeadroom
                    (-(uint)(pThis != (LPDIRECTSOUND8)0x0) & (int)pThis - 8U,dwMixBinMask,dwHeadroom
                    );
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetVolume(CDirectSoundBuffer *pThis,LONG lVolume)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetVolume
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,lVolume);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetPitch(CDirectSoundBuffer *pThis,LONG lPitch)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetPitch
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,lPitch);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetLFO(LPDIRECTSOUNDBUFFER8 pThis,LPCDSLFODESC pLFODesc)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetLFO
                    (-(uint)(pThis != (LPDIRECTSOUNDBUFFER8)0x0) & (int)pThis - 0x1cU,pLFODesc);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetEG(CDirectSoundBuffer *pThis,DSENVOLOPEDESC *pEnvelopeDesc)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetEG
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pEnvelopeDesc);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetFilter(LPVOID pThis,DSFILTERDESC *pFilterDesc)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetFilter
                    (-(uint)(pThis != (LPVOID)0x0) & (int)pThis - 0x1cU,pFilterDesc);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetHeadroom(CDirectSoundBuffer *pThis,DWORD dwHeadroom)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetHeadroom
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,dwHeadroom);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_SetMixBinVolumes_8
                  (CDirectSoundBuffer *pThis,LPDSMIXBINS pMixBins)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetMixBinVolumes
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pMixBins);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_Play
                  (CDirectSoundBuffer *pThis,DWORD dwReserved1,DWORD dwReserved2,DWORD dwFlags)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_Play
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,dwReserved1,dwReserved2,
                     dwFlags);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_Stop(CDirectSoundBuffer *pThis)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_Stop
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_StopEx
                  (CDirectSoundBuffer *pBuffer,REFERENCE_TIME rtTimeStamp,DWORD dwFlags)

{
  HRESULT HVar1;
  undefined4 in_stack_00000008;
  
  HVar1 = CDirectSoundBuffer_StopEx
                    (-(uint)(pBuffer != (CDirectSoundBuffer *)0x0) &
                     (uint)&pBuffer[-1].Xb_VoiceProperties.l3DDistanceVolume,in_stack_00000008,
                     rtTimeStamp);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_SetLoopRegion
                  (CDirectSoundBuffer *pThis,DWORD dwLoopStart,DWORD dwLoopLength)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetLoopRegion
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,dwLoopStart,dwLoopLength)
  ;
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_GetStatus(CDirectSoundBuffer *pThis,LPDWORD pdwStatus)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_GetStatus
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pdwStatus);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_GetCurrentPosition
                  (CDirectSoundBuffer *pThis,PDWORD pdwCurrentPlayCursor,
                  PDWORD pdwCurrentWriteCursor)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_GetCurrentPosition
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pdwCurrentPlayCursor,
                     pdwCurrentWriteCursor);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetCurrentPosition(CDirectSoundBuffer *pThis,DWORD dwNewPosition)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetCurrentPosition
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,dwNewPosition);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_Lock
                  (CDirectSoundBuffer *pThis,DWORD dwOffset,DWORD dwBytes,LPVOID *ppvAudioPtr1,
                  LPDWORD pdwAudioBytes1,LPVOID *ppvAudioPtr2,LPDWORD pdwAudioBytes2,DWORD dwFlags)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_Lock
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,dwOffset,dwBytes,
                     ppvAudioPtr1,pdwAudioBytes1,ppvAudioPtr2,pdwAudioBytes2,dwFlags);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_GetVoiceProperties
                  (CDirectSoundBuffer *pThis,DSVOICEPROPS *pVoiceProps)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_GetVoiceProperties
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pVoiceProps);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_Set3DVoiceData(CDirectSoundBuffer *pThis,DWORD a2)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_Set3DVoiceData
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,a2);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_Use3DVoiceData(LPVOID pThis,LPUNKNOWN pUnknown)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_Use3DVoiceData
                    (-(uint)(pThis != (LPVOID)0x0) & (int)pThis - 0x1cU,pUnknown);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundStream_SetVolume(CDirectSoundStream *pStream,LONG lVolume)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetVolume(pStream + 4,lVolume);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundStream_SetPitch(CDirectSoundStream *pThis,LONG lPitch)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetPitch(pThis + 4,lPitch);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundStream_SetLFO(CDirectSoundStream *pThis,LPCDSLFODESC pLFODesc)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetLFO(pThis + 4,pLFODesc);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundStream_SetEG(CDirectSoundStream *pThis,DSENVOLOPEDESC *pEnvelopeDesc)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetEG(pThis + 4,pEnvelopeDesc);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundStream_SetFilter(CDirectSoundStream *pThis,DSFILTERDESC *pFilterDesc)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetFilter(pThis + 4,pFilterDesc);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundStream_SetHeadroom(CDirectSoundStream *pThis,DWORD dwHeadroom)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetHeadroom(pThis + 4,dwHeadroom);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}



HRESULT DSOUND::IDirectSoundStream_SetMixBinVolumes_8
                  (CDirectSoundStream *pThis,LPDSMIXBINS pMixBins)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetMixBinVolumes(pThis + 4,pMixBins);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundStream_Pause(CDirectSoundStream *pThis,DWORD dwPause)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CMcpxStream_Pause(dwPause);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}



void DSOUND::IDirectSoundStream_FlushEx
               (CDirectSoundStream *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
               )

{
  DWORD unaff_retaddr;
  
  CDirectSoundStream_FlushEx(param_1,CONCAT44(param_4,param_3),unaff_retaddr);
  return;
}



HRESULT DSOUND::IDirectSoundStream_GetVoiceProperties
                  (CDirectSoundStream *pThis,DSVOICEPROPS *pVoiceProps)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_GetVoiceProperties(pThis + 4,pVoiceProps);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




undefined4 DSOUND::IDirectSoundStream_Set3DVoiceData(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_Set3DVoiceData(param_1 + 4,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::IDirectSoundStream_Use3DVoiceData(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int extraout_ECX;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_Use3DVoiceData(param_1 + 4,param_2);
    if (extraout_ECX != 0) {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}



void DSOUND::IDirectSound3DCalculator_GetVoiceData
               (DWORD param_1,DWORD param_2,DWORD param_3,DWORD param_4,DWORD param_5)

{
  CDirectSound3DCalculator_GetVoiceData(param_1,param_2,param_3,param_4,param_5);
  return;
}




void DSOUND::DirectSoundDoWork(void)

{
  char cVar1;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e3b38 != 0) {
    CDirectSound_DoWork(DAT_001e3b38);
  }
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
  }
  return;
}




void DSOUND::CDirectSoundVoice_SetFrequency(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    param_2 = *(int *)(*(int *)(param_1 + 0x10) + 0x10);
  }
  uVar1 = XAudioCalculatePitch(param_2);
  CDirectSoundVoice_SetPitch(param_1,uVar1);
  return;
}




int DSOUND::CDirectSoundVoice_SetOutputBuffer(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = -(uint)(param_2 != 0) & param_2 - 0x1cU;
  uVar1 = *(uint *)(*(int *)(param_1 + 0x10) + 0xb0);
  iVar2 = 0;
  if (uVar3 != uVar1) {
    if ((uVar1 != 0) && (iVar2 = FUN_001cd3ee(), iVar2 < 0)) {
      return iVar2;
    }
    FUN_001c755e(uVar3);
    if (uVar3 != 0) {
      iVar2 = FUN_001cd2e1();
    }
  }
  return iVar2;
}




void DSOUND::CDirectSoundVoice_SetMixBins(undefined4 param_1,undefined4 param_2)

{
  FUN_001c7493(param_2);
  CMcpxVoiceClient_SetMixBins();
  return;
}




undefined4 DSOUND::CDirectSoundBuffer_SetPlayRegion(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 != 0) {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    return 0x80004005;
  }
  if (param_3 == 0) {
    param_3 = *(int *)(*(int *)(param_1 + 0x1c) + 0xc0) - param_2;
  }
  else if (*(uint *)(*(int *)(param_1 + 0x1c) + 0xc0) < (uint)(param_2 + param_3)) {
    uVar2 = 0x88780032;
    goto LAB_001c7862;
  }
  FUN_001c77a2(param_2,param_3);
  uVar2 = FUN_001cdff8();
LAB_001c7862:
  if (cVar1 != '\0') {
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetFrequency(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetFrequency(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetOutputBuffer(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetOutputBuffer(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 DSOUND::CDirectSoundBuffer_SetMixBins(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetMixBins(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}



HRESULT DSOUND::CDirectSoundStream_SetOutputBuffer
                  (CDirectSoundStream *pThis,CDirectSoundBuffer *pOutputBuffer)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetOutputBuffer(pThis + 4,pOutputBuffer);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetMixBins(CDirectSoundStream *pThis,LPDSMIXBINS pMixBins)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetMixBins(pThis + 4,pMixBins);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundBuffer_SetFrequency(CDirectSoundBuffer *pThis,DWORD dwFrequency)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetFrequency
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,dwFrequency);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_SetOutputBuffer
                  (CDirectSoundBuffer *pThis,CDirectSoundBuffer *pOutputBuffer)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetOutputBuffer
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pOutputBuffer);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundBuffer_SetMixBins(CDirectSoundBuffer *pThis,LPDSMIXBINS pMixBins)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetMixBins
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pMixBins);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_SetPlayRegion
                  (CDirectSoundBuffer *pThis,DWORD dwPlayStart,DWORD dwPlayLength)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetPlayRegion
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,dwPlayStart,dwPlayLength)
  ;
  return HVar1;
}



HRESULT DSOUND::IDirectSoundStream_SetOutputBuffer
                  (CDirectSoundStream *pThis,CDirectSoundBuffer *pOutputBuffer)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetOutputBuffer(pThis + 4,pOutputBuffer);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundStream_SetMixBins(CDirectSoundStream *pThis,LPDSMIXBINS pMixBins)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetMixBins(pThis + 4,pMixBins);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




void DSOUND::CDirectSoundVoice_SetFormat(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_001c7bb6(param_2,1);
  if (iVar1 == 0) {
    FUN_001c7493(0);
  }
  iVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x14))();
  if (-1 < iVar1) {
    iVar1 = CMcpxVoiceClient_SetMixBins();
    if (-1 < iVar1) {
      CMcpxVoiceClient_SetPitch();
    }
  }
  return;
}




int __thiscall DSOUND::CDirectSoundBufferSettings_SetBufferData(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  if ((*(uint *)(param_1 + 8) & 0x80000000) == 0) {
    if (*(int *)(param_1 + 0xbc) == 0) goto LAB_001c7cae;
    FUN_001c8bab(*(int *)(param_1 + 0xbc));
  }
  *(undefined4 *)(param_1 + 0xbc) = 0;
LAB_001c7cae:
  *(int *)(param_1 + 0xc0) = param_3;
  if (param_3 != 0) {
    if (param_2 == 0) {
      *(byte *)(param_1 + 0xb) = *(byte *)(param_1 + 0xb) & 0x7f;
      iVar1 = FUN_001c8b43(0x61645344,param_3,0);
      *(int *)(param_1 + 0xbc) = iVar1;
      local_8 = (-(uint)(iVar1 != 0) & 0x7ff8fff2) + 0x8007000e;
    }
    else {
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x80000000;
      *(int *)(param_1 + 0xbc) = param_2;
    }
  }
  FUN_001c77a2(0,*(undefined4 *)(param_1 + 0xc0));
  return local_8;
}




int DSOUND::CDirectSoundBuffer_SetBufferData(int param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  int iVar3;
  
  iVar1 = param_2;
  iVar3 = 0;
  if ((param_2 != 0) || (param_2 = 0, param_3 != 0)) {
    param_2 = 1;
  }
  cVar2 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    if ((((iVar1 != *(int *)(*(int *)(param_1 + 0x1c) + 0xbc)) ||
         (param_3 != *(int *)(*(int *)(param_1 + 0x1c) + 0xc0))) &&
        (iVar3 = FUN_001ce35b(param_2), -1 < iVar3)) &&
       ((iVar3 = CDirectSoundBufferSettings_SetBufferData(iVar1,param_3), -1 < iVar3 &&
        (param_2 != 0)))) {
      iVar3 = CMcpxBuffer_SetBufferData();
    }
    if (cVar2 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar2 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    iVar3 = -0x7fffbffb;
  }
  return iVar3;
}



undefined4 * __thiscall

DSOUND::CDirectSoundStream_Constructor(undefined4 *param_1,undefined4 param_2)

{
  FUN_001c7631(param_2);
  param_1[1] = &PTR_LAB_0020a028;
  *param_1 = &PTR_CDirectSoundStream_AddRef_0020a038;
  return param_1;
}




void DSOUND::CDirectSound3DCalculator_Calculate3D(DWORD a1,DWORD a2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  int local_94 [26];
  int local_2c [3];
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  uint local_c;
  uint local_8;
  
  FUN_001c5849();
  local_8 = *(uint *)a1;
  local_c = *(uint *)(a1 + 4);
  if (a2 != 0) {
    local_8 = local_8 | *(uint *)a2;
    local_c = local_c | *(uint *)(a2 + 4);
  }
  if (((local_8 & 4) != 0) || ((local_c & 0x40) == 0)) {
    FUN_001c8e05(a1 + 0x20,a1 + 0x2c,local_94);
    iVar2 = 3;
    bVar5 = true;
    piVar3 = local_94;
    piVar4 = (int *)(a1 + 0x44);
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar5 = *piVar3 == *piVar4;
      piVar3 = piVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (bVar5);
    if (!bVar5) {
      local_8 = local_8 | 0x40;
      *(int *)(a1 + 0x44) = local_94[0];
      *(int *)(a1 + 0x48) = local_94[1];
      *(int *)(a1 + 0x4c) = local_94[2];
    }
    local_c = local_c | 0x40;
  }
  uVar1 = local_8;
  if (((local_8 & 0x400000) != 0) && (uVar1 = local_8 & 0x400000, *(int *)(a2 + 0x40) != 2)) {
    local_8 = local_8 | 0x7ff0000;
    uVar1 = local_8;
  }
  local_8 = uVar1;
  if ((a2 != 0) && (*(int *)(a2 + 0x40) != 2)) {
    if (((local_8 & 0x410001) != 0) || ((local_c & 0x18000000) != 0x18000000)) {
      (*DAT_001e3b64)(*(int *)(a2 + 0x40),a1 + 8,a2 + 8,local_2c,&local_20);
      iVar2 = 3;
      bVar5 = true;
      piVar3 = local_2c;
      piVar4 = (int *)(a2 + 0x5c);
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar5 = *piVar3 == *piVar4;
        piVar3 = piVar3 + 1;
        piVar4 = piVar4 + 1;
      } while (bVar5);
      if (!bVar5) {
        local_8 = local_8 | 0x8000000;
        *(int *)(a2 + 0x5c) = local_2c[0];
        *(int *)(a2 + 0x60) = local_2c[1];
        *(int *)(a2 + 100) = local_2c[2];
      }
      if (local_20 != *(float *)(a2 + 0x68)) {
        local_8 = local_8 | 0x10000000;
        *(float *)(a2 + 0x68) = local_20;
      }
      local_c = local_c | 0x18000000;
    }
    if (((local_8 & 0x18400044) != 0) || ((local_c & 0x20000000) == 0)) {
      FUN_001c5918(*(undefined4 *)(a2 + 0x40),a1 + 0x20,a1 + 0x2c,a1 + 0x44,a2 + 0x5c,
                   *(undefined4 *)(a2 + 0x68),&local_14,&local_10);
      if ((local_14 != *(float *)(a2 + 0x74)) || (local_10 != *(float *)(a2 + 0x78))) {
        local_8 = local_8 | 0x20000000;
        *(float *)(a2 + 0x74) = local_14;
        *(float *)(a2 + 0x78) = local_10;
      }
      local_c = local_c | 0x20000000;
    }
    if (((local_8 & 0x8080000) != 0) || ((local_c & 0x40000000) == 0)) {
      (*DAT_001e3b6c)(a2 + 0x28,a2 + 0x5c,&local_18);
      if (local_18 != *(float *)(a2 + 0x70)) {
        local_8 = local_8 | 0x40000000;
        *(float *)(a2 + 0x70) = local_18;
      }
      local_c = local_c | 0x40000000;
    }
    if (((local_8 & 0x8420002) != 0) || ((local_c & 0x80000000) != 0x80000000)) {
      (*DAT_001e3b70)(*(undefined4 *)(a2 + 0x40),a1 + 0x14,a2 + 0x14,a2 + 0x5c,&local_1c);
      if (local_1c != *(float *)(a2 + 0x6c)) {
        local_8 = local_8 | 0x80000000;
        *(float *)(a2 + 0x6c) = local_1c;
      }
      local_c = local_c | 0x80000000;
    }
  }
  if ((local_8 & 0x7f) != 0) {
    *(uint *)a1 = local_8 & 0x7f;
  }
  if ((local_c & 0x7f) != 0) {
    *(uint *)(a1 + 4) = local_c & 0x7f;
  }
  if ((local_8 & 0xffff0000) != 0) {
    *(uint *)a2 = local_8 & 0xffff0000;
  }
  if ((local_c & 0xffff0000) != 0) {
    *(uint *)(a2 + 4) = local_c & 0xffff0000;
  }
  FUN_001c586e();
  return;
}




undefined4 DSOUND::CDirectSoundBuffer_SetFormat(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    uVar2 = CDirectSoundVoice_SetFormat(param_1,param_2);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




HRESULT DSOUND::CDirectSoundStream_SetFormat(CDirectSoundStream *pThis,LPCWAVEFORMATEX pwfxFormat)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetFormat(pThis + 4,pwfxFormat);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSoundBuffer_SetFormat(CDirectSoundBuffer *pBuffer,LPCWAVEFORMATEX pwfxFormat)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetFormat
                    (-(uint)(pBuffer != (CDirectSoundBuffer *)0x0) &
                     (uint)&pBuffer[-1].Xb_VoiceProperties.l3DDistanceVolume,pwfxFormat);
  return HVar1;
}



HRESULT DSOUND::IDirectSoundBuffer_SetBufferData
                  (CDirectSoundBuffer *pThis,LPVOID pvBufferData,DWORD dwBufferBytes)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSoundBuffer_SetBufferData
                    (-(uint)(pThis != (CDirectSoundBuffer *)0x0) &
                     (uint)&pThis[-1].Xb_VoiceProperties.l3DDistanceVolume,pvBufferData,
                     dwBufferBytes);
  return HVar1;
}




HRESULT DSOUND::IDirectSoundStream_SetFormat(CDirectSoundStream *pThis,LPCWAVEFORMATEX pwfxFormat)

{
  char cVar1;
  HRESULT HVar2;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    HVar2 = CDirectSoundVoice_SetFormat(pThis + 4,pwfxFormat);
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




void DSOUND::IDirectSound3DCalculator_Calculate3D(DWORD a1,DWORD a2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  int aiStack_94 [26];
  int aiStack_2c [3];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  uint uStack_c;
  uint uStack_8;
  
  FUN_001c5849();
  uStack_8 = *(uint *)a1;
  uStack_c = *(uint *)(a1 + 4);
  if (a2 != 0) {
    uStack_8 = uStack_8 | *(uint *)a2;
    uStack_c = uStack_c | *(uint *)(a2 + 4);
  }
  if (((uStack_8 & 4) != 0) || ((uStack_c & 0x40) == 0)) {
    FUN_001c8e05(a1 + 0x20,a1 + 0x2c,aiStack_94);
    iVar2 = 3;
    bVar5 = true;
    piVar3 = aiStack_94;
    piVar4 = (int *)(a1 + 0x44);
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar5 = *piVar3 == *piVar4;
      piVar3 = piVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (bVar5);
    if (!bVar5) {
      uStack_8 = uStack_8 | 0x40;
      *(int *)(a1 + 0x44) = aiStack_94[0];
      *(int *)(a1 + 0x48) = aiStack_94[1];
      *(int *)(a1 + 0x4c) = aiStack_94[2];
    }
    uStack_c = uStack_c | 0x40;
  }
  uVar1 = uStack_8;
  if (((uStack_8 & 0x400000) != 0) && (uVar1 = uStack_8 & 0x400000, *(int *)(a2 + 0x40) != 2)) {
    uStack_8 = uStack_8 | 0x7ff0000;
    uVar1 = uStack_8;
  }
  uStack_8 = uVar1;
  if ((a2 != 0) && (*(int *)(a2 + 0x40) != 2)) {
    if (((uStack_8 & 0x410001) != 0) || ((uStack_c & 0x18000000) != 0x18000000)) {
      (*DAT_001e3b64)(*(int *)(a2 + 0x40),a1 + 8,a2 + 8,aiStack_2c,&fStack_20);
      iVar2 = 3;
      bVar5 = true;
      piVar3 = aiStack_2c;
      piVar4 = (int *)(a2 + 0x5c);
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar5 = *piVar3 == *piVar4;
        piVar3 = piVar3 + 1;
        piVar4 = piVar4 + 1;
      } while (bVar5);
      if (!bVar5) {
        uStack_8 = uStack_8 | 0x8000000;
        *(int *)(a2 + 0x5c) = aiStack_2c[0];
        *(int *)(a2 + 0x60) = aiStack_2c[1];
        *(int *)(a2 + 100) = aiStack_2c[2];
      }
      if (fStack_20 != *(float *)(a2 + 0x68)) {
        uStack_8 = uStack_8 | 0x10000000;
        *(float *)(a2 + 0x68) = fStack_20;
      }
      uStack_c = uStack_c | 0x18000000;
    }
    if (((uStack_8 & 0x18400044) != 0) || ((uStack_c & 0x20000000) == 0)) {
      FUN_001c5918(*(undefined4 *)(a2 + 0x40),a1 + 0x20,a1 + 0x2c,a1 + 0x44,a2 + 0x5c,
                   *(undefined4 *)(a2 + 0x68),&fStack_14,&fStack_10);
      if ((fStack_14 != *(float *)(a2 + 0x74)) || (fStack_10 != *(float *)(a2 + 0x78))) {
        uStack_8 = uStack_8 | 0x20000000;
        *(float *)(a2 + 0x74) = fStack_14;
        *(float *)(a2 + 0x78) = fStack_10;
      }
      uStack_c = uStack_c | 0x20000000;
    }
    if (((uStack_8 & 0x8080000) != 0) || ((uStack_c & 0x40000000) == 0)) {
      (*DAT_001e3b6c)(a2 + 0x28,a2 + 0x5c,&fStack_18);
      if (fStack_18 != *(float *)(a2 + 0x70)) {
        uStack_8 = uStack_8 | 0x40000000;
        *(float *)(a2 + 0x70) = fStack_18;
      }
      uStack_c = uStack_c | 0x40000000;
    }
    if (((uStack_8 & 0x8420002) != 0) || ((uStack_c & 0x80000000) != 0x80000000)) {
      (*DAT_001e3b70)(*(undefined4 *)(a2 + 0x40),a1 + 0x14,a2 + 0x14,a2 + 0x5c,&fStack_1c);
      if (fStack_1c != *(float *)(a2 + 0x6c)) {
        uStack_8 = uStack_8 | 0x80000000;
        *(float *)(a2 + 0x6c) = fStack_1c;
      }
      uStack_c = uStack_c | 0x80000000;
    }
  }
  if ((uStack_8 & 0x7f) != 0) {
    *(uint *)a1 = uStack_8 & 0x7f;
  }
  if ((uStack_c & 0x7f) != 0) {
    *(uint *)(a1 + 4) = uStack_c & 0x7f;
  }
  if ((uStack_8 & 0xffff0000) != 0) {
    *(uint *)a2 = uStack_8 & 0xffff0000;
  }
  if ((uStack_c & 0xffff0000) != 0) {
    *(uint *)(a2 + 4) = uStack_c & 0xffff0000;
  }
  FUN_001c586e();
  return;
}




HRESULT DSOUND::CDirectSound_CommitDeferredSettings(CDirectSound *pThis)

{
  char cVar1;
  HRESULT HVar2;
  CDirectSound *pCVar3;
  
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    FUN_001c5849();
    CDirectSound3DCalculator_Calculate3D(*(int *)(pThis + 8) + 0x30,0);
    FUN_001ca09a();
    for (pCVar3 = *(CDirectSound **)(pThis + 0x10); pCVar3 != pThis + 0x10;
        pCVar3 = *(CDirectSound **)pCVar3) {
      CDirectSoundVoice_CommitDeferredSettings(pCVar3 + -0x14);
    }
    *(undefined4 *)(*(int *)(pThis + 8) + 0x30) = 0;
    *(undefined4 *)(*(int *)(pThis + 8) + 0x80) = 0;
    FUN_001c586e();
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = 0;
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    HVar2 = -0x7fffbffb;
  }
  return HVar2;
}




HRESULT DSOUND::IDirectSound_CommitDeferredSettings(CDirectSound *pThis)

{
  HRESULT HVar1;
  
  HVar1 = CDirectSound_CommitDeferredSettings
                    ((CDirectSound *)(-(uint)(pThis != (CDirectSound *)0x0) & (uint)(pThis + -8)));
  return HVar1;
}




int DSOUND::CDirectSound_CreateSoundBuffer(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  cVar1 = DirectSoundEnterCriticalSection();
  piVar3 = (int *)0x0;
  if (DAT_001e34b4 == 0) {
    iVar2 = FUN_001c57ff(0x24);
    if (iVar2 != 0) {
      piVar3 = (int *)FUN_001c77c6(param_1);
    }
    iVar2 = (-(uint)(piVar3 != (int *)0x0) & 0x7ff8fff2) + 0x8007000e;
    if ((iVar2 < 0) || (iVar2 = FUN_001c83d5(piVar3,param_2), iVar2 < 0)) {
      if (piVar3 != (int *)0x0) {
        (**(code **)(*piVar3 + 8))(piVar3);
      }
    }
    else {
      *param_3 = -(uint)(piVar3 != (int *)0x0) & (uint)(piVar3 + 7);
    }
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    iVar2 = -0x7fffbffb;
  }
  return iVar2;
}



int DSOUND::CDirectSound_CreateSoundStream
              (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  cVar1 = DirectSoundEnterCriticalSection();
  piVar3 = (int *)0x0;
  if (DAT_001e34b4 == 0) {
    iVar2 = FUN_001c57ff(0x28);
    if (iVar2 != 0) {
      piVar3 = (int *)CDirectSoundStream_Constructor(param_1);
    }
    iVar2 = (-(uint)(piVar3 != (int *)0x0) & 0x7ff8fff2) + 0x8007000e;
    if ((iVar2 < 0) || (iVar2 = FUN_001c8516(piVar3,param_2), iVar2 < 0)) {
      if (piVar3 != (int *)0x0) {
        (**(code **)(*piVar3 + 4))(piVar3);
      }
    }
    else {
      *param_3 = piVar3;
    }
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    iVar2 = -0x7fffbffb;
  }
  return iVar2;
}



undefined4

DSOUND::CDirectSound_SetI3DL2Listener(CDirectSound *param_1,undefined4 *param_2,byte param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  cVar1 = DirectSoundEnterCriticalSection();
  if (DAT_001e34b4 == 0) {
    if (*(int *)(*(int *)(param_1 + 8) + 8) == -1) {
      uVar2 = 0x88780032;
    }
    else {
      *(undefined4 *)(*(int *)(param_1 + 8) + 0x84) = *param_2;
      *(undefined4 *)(*(int *)(param_1 + 8) + 0x88) = param_2[1];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0x8c) = param_2[2];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0x90) = param_2[3];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0x94) = param_2[4];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0x98) = param_2[5];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0x9c) = param_2[6];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0xa0) = param_2[7];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0xa4) = param_2[8];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0xa8) = param_2[9];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0xac) = param_2[10];
      *(undefined4 *)(*(int *)(param_1 + 8) + 0xb0) = param_2[0xb];
      *(ushort *)(*(int *)(param_1 + 8) + 0x80) = *(ushort *)(*(int *)(param_1 + 8) + 0x80) | 0xfff;
      if ((param_3 & 1) == 0) {
        CDirectSound_CommitDeferredSettings(param_1);
      }
    }
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
  }
  else {
    if (cVar1 != '\0') {
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)&DAT_001e34c0);
    }
    uVar2 = 0x80004005;
  }
  return uVar2;
}




undefined4 * DSOUND::DSound_CMemoryManager_PoolAlloc(ULONG param_1,SIZE_T param_2,int param_3)

{
  undefined4 *PoolBlock;
  ULONG UVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  PoolBlock = ExAllocatePoolWithTag(param_2,param_1);
  if (PoolBlock != (undefined4 *)0x0) {
    UVar1 = ExQueryPoolBlockSize(PoolBlock);
    *DAT_001e3b60 = *DAT_001e3b60 + UVar1;
    if (param_3 != 0) {
      puVar3 = PoolBlock;
      for (uVar2 = UVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      for (uVar2 = UVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar3 = 0;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
    }
  }
  return PoolBlock;
}




void DSOUND::XAudioCreatePcmFormat(ushort param_1,int param_2,ushort param_3,undefined2 *param_4)

{
  uint uVar1;
  
  param_4[1] = param_1;
  param_4[7] = param_3;
  uVar1 = (int)((uint)param_1 * (uint)param_3) / 8;
  param_4[8] = 0;
  *(int *)(param_4 + 2) = param_2;
  *param_4 = 1;
  param_4[6] = (short)uVar1;
  *(uint *)(param_4 + 4) = (uVar1 & 0xffff) * param_2;
  return;
}




void DSOUND::XAudioCreateAdpcmFormat(WORD nChannels,DWORD nSamplesPerSec,LPXBOXADPCMWAVEFORMAT pwfx)

{
  *(DWORD *)&pwfx->wSamplesPerBlock = nSamplesPerSec;
  *(WORD *)((int)&pwfx->wfx + 2) = nChannels;
  *(undefined2 *)&pwfx->wfx = 0x69;
  *(undefined2 *)&pwfx[1].field_0x6 = 4;
  pwfx[1].wSamplesPerBlock = nChannels * 0x24;
  pwfx[1].wfx = (WAVEFORMATEX)((nSamplesPerSec >> 6) * 0x24);
  *(undefined2 *)&pwfx[2].wfx = 2;
  *(undefined2 *)((int)&pwfx[2].wfx + 2) = 0x40;
  return;
}




void DSOUND::CHRTFSource_SetFullHRTF5Channel(void)

{
  DAT_001e3b64 = FUN_001c8e42;
  DAT_001e3b68 = FUN_001c8e8b;
  DAT_001e3b6c = FUN_001c8fee;
  DAT_001e3b70 = FUN_001c9084;
  DAT_001e3b74 = FUN_001c90cf;
  DAT_001e3b78 = FUN_001c91e0;
  DAT_001e3b7c = FUN_001c9270;
  DAT_001e3b80 = CFullHRTFSource_GetCenterVolume;
  DAT_001e3b84 = FUN_001c93e1;
  DAT_001e3b88 = FUN_001c945a;
  _DAT_001e3b8c = 3;
  return;
}




void __fastcall DSOUND::CMcpxAPU_ServiceDeferredCommandsLow(int param_1)

{
  undefined4 ****ppppuVar1;
  undefined4 ****ppppuVar2;
  undefined4 *****pppppuVar3;
  undefined4 ****local_c;
  undefined4 ****local_8;
  
  local_c = &local_c;
  local_8 = local_c;
  FUN_001c5810();
  ppppuVar1 = (undefined4 ****)(param_1 + 0x4b0);
  while ((undefined4 ****)*ppppuVar1 != ppppuVar1) {
    FUN_001c9a62(&local_c,*ppppuVar1);
  }
  while (pppppuVar3 = (undefined4 *****)FUN_001c57e0(local_c), pppppuVar3 != &local_c) {
    if (((uint)pppppuVar3[2] & 4) == 0) {
      pppppuVar3[2] = (undefined4 ****)((uint)pppppuVar3[2] & 0xfffffffd);
    }
    else {
      *pppppuVar3 = ppppuVar1;
      ppppuVar2 = *(undefined4 *****)(param_1 + 0x4b4);
      pppppuVar3[1] = ppppuVar2;
      *ppppuVar2 = pppppuVar3;
      (*pppppuVar3)[1] = pppppuVar3;
    }
    FUN_001c5832();
    (*(code *)(*pppppuVar3[3])[9])(pppppuVar3[4],pppppuVar3[5]);
    FUN_001c5810();
  }
  FUN_001c5832();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 __thiscall DSOUND::CMcpxAPU_SetMixBinHeadroom(int param_1,int param_2)

{
  FUN_001c5810();
  do {
  } while ((_DAT_fe820010 & 0xfffffffc) < 4);
  *(uint *)(param_2 * 4 + -0x17dfe00) = *(byte *)(*(int *)(param_1 + 0xc) + 0x10 + param_2) & 7;
  FUN_001c5832();
  return 0;
}




undefined4 __thiscall DSOUND::CMcpxStream_Stop(int *param_1,byte param_2)

{
  FUN_001c5810();
  if ((*(byte *)((int)param_1 + 0x12) & 3) == 3) {
    if ((param_2 & 6) == 0) {
      FUN_001cd122(0);
    }
    else {
      if ((param_2 & 4) == 0) {
        *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) & 0xefff;
      }
      else {
        *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) | 0x1000;
      }
      FUN_001cc34c();
    }
    if ((param_2 & 4) == 0) {
      (**(code **)(*param_1 + 0x1c))(3,0,0,0);
    }
  }
  FUN_001c5832();
  return 0;
}




undefined4 __thiscall DSOUND::CMcpxStream_GetStatus(int param_1,uint *param_2)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 0x12);
  *param_2 = (uint)(*(int **)(param_1 + 0xb0) != (int *)(param_1 + 0xb0));
  if ((uVar1 & 0x2000) != 0) {
    *(byte *)((int)param_2 + 2) = *(byte *)((int)param_2 + 2) | 8;
  }
  if (((byte)uVar1 & 3) == 3) {
    if ((uVar1 & 0x444) != 0) {
      *(byte *)((int)param_2 + 2) = *(byte *)((int)param_2 + 2) | 2;
      if ((uVar1 & 0x400) == 0) {
        return 0;
      }
      *param_2 = *param_2 | 0x40000;
      return 0;
    }
  }
  else if ((uVar1 & 0x8001) != 0x8001) {
    return 0;
  }
  *(byte *)((int)param_2 + 2) = *(byte *)((int)param_2 + 2) | 1;
  return 0;
}




DSOUND::CMcpxStream_Stop_Ex(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_2 != 0 || param_3 != 0) &&
     (iVar1 = (**(code **)(*param_1 + 0x1c))(4,param_2,param_3,param_4), iVar1 != 0)) {
    return 0;
  }
  uVar2 = CMcpxStream_Stop(param_4);
  return uVar2;
}




undefined4 DSOUND::CMcpxStream_Discontinuity(void)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_001ca67c();
  if (iVar1 == 0) {
    uVar2 = CMcpxStream_Stop(1);
  }
  else {
    FUN_001ca61f();
  }
  return uVar2;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void __thiscall DSOUND::CMcpxStream_Flush(int *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  int unaff_FS_OFFSET;
  int local_c;
  
  cVar1 = *(char *)(unaff_FS_OFFSET + 0x24);
  uVar2 = 0;
  if ((*(byte *)((int)param_1 + 0x12) & 1) == 0) goto LAB_001caee8;
  FUN_001c5810();
  do {
    (**(code **)(*param_1 + 0x20))(uVar2);
    uVar2 = uVar2 + 1;
  } while (uVar2 < 6);
  uVar2 = param_1[100];
  local_c = 2;
  do {
    FUN_001cad57(uVar2,0x80004004);
    uVar2 = uVar2 - 1 & 1;
    local_c = local_c + -1;
  } while (local_c != 0);
  param_1[100] = 0;
  FUN_001cd122(0);
  FUN_001c5832();
  FUN_001cd038();
  FUN_001cac8c(param_1 + 0x2a,0x80004004);
  if ((*(byte *)(param_1[0x20] + 10) & 4) == 0) {
LAB_001caecd:
    if (cVar1 != '\0') {
      (**(code **)(*param_1 + 0x1c))(2,0,0,0);
      goto LAB_001caee8;
    }
  }
  else {
    if (cVar1 != '\0') {
      (**(code **)(*param_1 + 0x1c))(1,0,0,0);
      goto LAB_001caecd;
    }
    FUN_001caab8();
  }
  FUN_001cad02();
LAB_001caee8:
  if (param_2 == 0) {
    *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) & 0xcfff;
  }
  return;
}




undefined4 __thiscall DSOUND::CMcpxStream_Pause(int param_1,int param_2)

{
  ushort *puVar1;
  ushort uVar2;
  undefined4 uVar3;
  
  if (param_2 == 0) {
    puVar1 = (ushort *)(param_1 + 0x12);
    if ((*(byte *)puVar1 & 0x20) != 0) {
      *puVar1 = *puVar1 & 0xffdf;
      FUN_001caf0a();
    }
    uVar3 = FUN_001cc424(*puVar1 & 0xffbb);
    return uVar3;
  }
  if (param_2 == 1) {
    uVar2 = *(ushort *)(param_1 + 0x12) & 0xffbf | 4;
  }
  else if (param_2 == 2) {
    uVar2 = *(ushort *)(param_1 + 0x12) & 0xfffb | 0x40;
  }
  else {
    if (param_2 != 3) {
      return 0x80004005;
    }
    if ((*(byte *)(param_1 + 0x12) & 3) != 3) {
      *(ushort *)(param_1 + 0x12) = *(ushort *)(param_1 + 0x12) | 0x20;
      return 0;
    }
    uVar2 = *(ushort *)(param_1 + 0x12) & 0xffbb;
  }
  uVar3 = FUN_001cc424(uVar2);
  return uVar3;
}




undefined4 __thiscall DSOUND::CMcpxVoiceClient_SetLFO(int param_1,int *param_2)

{
  ushort *puVar1;
  uint uVar2;
  
  FUN_001c5810();
  if (*param_2 == 0) {
    *(uint *)(param_1 + 0x18) =
         *(uint *)(param_1 + 0x18) ^
         ((uint)(param_2[1] != 0) << 0xe ^ *(uint *)(param_1 + 0x18)) & 0x4000;
    *(uint *)(param_1 + 0x2c) =
         *(uint *)(param_1 + 0x2c) ^ (param_2[1] ^ *(uint *)(param_1 + 0x2c)) & 0x7fff;
    *(uint *)(param_1 + 0x30) =
         *(uint *)(param_1 + 0x30) ^ (param_2[2] << 0xc ^ *(uint *)(param_1 + 0x30)) & 0x3ff000;
    *(char *)(param_1 + 0x34) = (char)param_2[5];
    *(char *)(param_1 + 0x35) = (char)param_2[3];
    *(char *)(param_1 + 0x36) = (char)param_2[4];
  }
  else if (*param_2 == 1) {
    *(uint *)(param_1 + 0x18) =
         *(uint *)(param_1 + 0x18) ^
         ((uint)(param_2[1] != 0) << 0xf ^ *(uint *)(param_1 + 0x18)) & 0x8000;
    *(uint *)(param_1 + 0x2c) =
         *(uint *)(param_1 + 0x2c) ^ (param_2[1] << 0x10 ^ *(uint *)(param_1 + 0x2c)) & 0x7fff0000;
    *(uint *)(param_1 + 0x30) = param_2[2] << 0x16 | *(uint *)(param_1 + 0x30) & 0x3fffff;
    *(char *)(param_1 + 0x37) = (char)param_2[3];
  }
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    do {
    } while (_DAT_fe820010 >> 2 < (uint)*(byte *)(param_1 + 100) * 7);
    uVar2 = 0;
    if (*(byte *)(param_1 + 100) != 0) {
      puVar1 = (ushort *)(param_1 + 0xc);
      do {
        _DAT_fe8202f8 = (uint)*puVar1;
        _DAT_fe820318 = *(undefined4 *)(param_1 + 0x18);
        _DAT_fe820350 = *(undefined4 *)(param_1 + 0x2c);
        _DAT_fe82036c = *(undefined4 *)(param_1 + 0x30);
        _DAT_fe820370 = *(undefined4 *)(param_1 + 0x34);
        _DAT_fe8202fc = 0;
        uVar2 = uVar2 + 1;
        puVar1 = puVar1 + 1;
      } while (uVar2 < *(byte *)(param_1 + 100));
    }
  }
  FUN_001c5832();
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 __thiscall DSOUND::CMcpxVoiceClient_SetEG(int param_1,int *param_2)

{
  ushort *puVar1;
  uint uVar2;
  
  FUN_001c5810();
  if (*param_2 == 0) {
    *(uint *)(param_1 + 0x40) =
         *(uint *)(param_1 + 0x40) ^ (param_2[1] << 0x18 ^ *(uint *)(param_1 + 0x40)) & 0xf000000;
    *(uint *)(param_1 + 0x18) =
         *(uint *)(param_1 + 0x18) ^ (param_2[6] ^ *(uint *)(param_1 + 0x18)) & 0xfff;
    *(char *)(param_1 + 0x1f) = (char)param_2[8];
    *(uint *)(param_1 + 0x24) =
         *(uint *)(param_1 + 0x24) ^ (param_2[3] ^ *(uint *)(param_1 + 0x24)) & 0xfff;
    *(uint *)(param_1 + 0x24) =
         (param_2[2] << 0xc ^ *(uint *)(param_1 + 0x24)) & 0xfff000 ^ *(uint *)(param_1 + 0x24);
    *(char *)(param_1 + 0x27) = (char)param_2[9];
    *(uint *)(param_1 + 0x28) =
         *(uint *)(param_1 + 0x28) ^ (param_2[5] ^ *(uint *)(param_1 + 0x28)) & 0xfff;
    *(uint *)(param_1 + 0x28) =
         (param_2[4] << 0xc ^ *(uint *)(param_1 + 0x28)) & 0xfff000 ^ *(uint *)(param_1 + 0x28);
    *(char *)(param_1 + 0x2b) = (char)param_2[7];
  }
  else if (*param_2 == 1) {
    *(uint *)(param_1 + 0x40) = param_2[1] << 0x1c | *(uint *)(param_1 + 0x40) & 0xfffffff;
    *(uint *)(param_1 + 0x30) =
         *(uint *)(param_1 + 0x30) ^ (param_2[6] ^ *(uint *)(param_1 + 0x30)) & 0xfff;
    *(uint *)(param_1 + 0x1c) =
         *(uint *)(param_1 + 0x1c) ^ (param_2[3] ^ *(uint *)(param_1 + 0x1c)) & 0xfff;
    *(uint *)(param_1 + 0x1c) =
         (param_2[2] << 0xc ^ *(uint *)(param_1 + 0x1c)) & 0xfff000 ^ *(uint *)(param_1 + 0x1c);
    *(uint *)(param_1 + 0x20) =
         *(uint *)(param_1 + 0x20) ^ (param_2[5] ^ *(uint *)(param_1 + 0x20)) & 0xfff;
    *(uint *)(param_1 + 0x20) =
         (param_2[4] << 0xc ^ *(uint *)(param_1 + 0x20)) & 0xfff000 ^ *(uint *)(param_1 + 0x20);
    *(char *)(param_1 + 0x23) = (char)param_2[7];
  }
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    do {
    } while (_DAT_fe820010 >> 2 < (uint)*(byte *)(param_1 + 100) * 9);
    uVar2 = 0;
    if (*(byte *)(param_1 + 100) != 0) {
      puVar1 = (ushort *)(param_1 + 0xc);
      do {
        _DAT_fe8202f8 = (uint)*puVar1;
        _DAT_fe820318 = *(undefined4 *)(param_1 + 0x18);
        _DAT_fe820308 = *(undefined4 *)(param_1 + 0x1c);
        _DAT_fe82030c = *(undefined4 *)(param_1 + 0x20);
        _DAT_fe820310 = *(undefined4 *)(param_1 + 0x24);
        _DAT_fe820314 = *(undefined4 *)(param_1 + 0x28);
        _DAT_fe82036c = *(undefined4 *)(param_1 + 0x30);
        _DAT_fe8202fc = 0;
        uVar2 = uVar2 + 1;
        puVar1 = puVar1 + 1;
      } while (uVar2 < *(byte *)(param_1 + 100));
    }
  }
  FUN_001c5832();
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 __thiscall DSOUND::CMcpxVoiceClient_SetFilter(int param_1,uint *param_2)

{
  int *piVar1;
  ushort *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint local_24 [4];
  uint local_14;
  uint local_10;
  undefined4 local_8;
  
  local_8 = 0;
  FUN_001c5810();
  if (param_2 == (uint *)0x0) {
    local_24[3] = (uint)*(ushort *)(param_1 + 0x3a);
    local_24[2] = *(uint *)(param_1 + 0x38) & 0xffff;
    local_24[0] = *(byte *)(param_1 + 0x1a) & 3;
    local_24[1] = *(uint *)(param_1 + 0x18) >> 0x12 & 7;
    local_14 = *(uint *)(param_1 + 0x3c) & 0xffff;
    local_10 = (uint)*(ushort *)(param_1 + 0x3e);
  }
  else {
    puVar6 = local_24;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar6 = *param_2;
      param_2 = param_2 + 1;
      puVar6 = puVar6 + 1;
    }
  }
  uVar5 = local_24[0];
  if (((*(uint *)(*(int *)(param_1 + 0x70) + 8) & 0x200010) != 0) && (local_24[0] == 0)) {
    uVar5 = 3;
  }
  *(uint *)(param_1 + 0x18) =
       ((local_24[1] & 7) << 2 | uVar5 & 3) << 0x10 | *(uint *)(param_1 + 0x18) & 0xffe0ffff;
  piVar1 = (int *)(*(int *)(param_1 + 0x70) + 0xb8);
  *(uint *)(param_1 + 0x38) = local_24[3] << 0x10 | local_24[2] & 0xffff;
  if ((*piVar1 == 0) || ((*(byte *)(*(int *)(param_1 + 0x70) + 0xb) & 1) == 0)) {
    uVar4 = local_14 & 0xffff;
    uVar5 = local_10;
  }
  else {
    uVar4 = *(uint *)(*piVar1 + 0x30) & 0xffff;
    *(uint *)(param_1 + 0x3c) = uVar4;
    uVar5 = *(uint *)(*piVar1 + 0x34);
  }
  *(uint *)(param_1 + 0x3c) = uVar5 << 0x10 | uVar4;
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    do {
    } while (_DAT_fe820010 >> 2 < (uint)*(byte *)(param_1 + 100) * 6);
    uVar5 = 0;
    if (*(byte *)(param_1 + 100) != 0) {
      puVar2 = (ushort *)(param_1 + 0xc);
      do {
        _DAT_fe8202f8 = (uint)*puVar2;
        _DAT_fe820318 = *(undefined4 *)(param_1 + 0x18);
        _DAT_fe820374 = *(undefined4 *)(param_1 + 0x38);
        _DAT_fe820378 = *(undefined4 *)(param_1 + 0x3c);
        _DAT_fe8202fc = 0;
        uVar5 = uVar5 + 1;
        puVar2 = puVar2 + 1;
      } while (uVar5 < *(byte *)(param_1 + 100));
    }
  }
  FUN_001c5832();
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 __thiscall DSOUND::CMcpxVoiceClient_GetVoiceProperties(int param_1,int *param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  uint local_2c [4];
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  if ((*(byte *)(param_1 + 0x12) & 1) == 0) {
    return 0x88780032;
  }
  iVar4 = DAT_001e3c40 + (uint)*(ushort *)(param_1 + 0xc) * 0x80;
  uVar3 = *(uint *)(iVar4 + 0x28);
  uVar5 = *(uint *)(iVar4 + 0x2c);
  uVar2 = *(uint *)(iVar4 + 0x30);
  local_c = *(undefined4 *)(iVar4 + 0x7c);
  local_2c[0] = uVar3 >> 4 & 0xfff;
  local_2c[1] = uVar3 >> 0x14;
  local_2c[2] = uVar5 >> 4 & 0xfff;
  local_2c[3] = uVar5 >> 0x14;
  local_18 = uVar2 >> 0x14;
  local_1c = uVar2 >> 4 & 0xfff;
  uVar5 = (uVar5 & 0xf) << 4;
  local_14 = uVar3 & 0xf | uVar5 | (uVar2 & 0xf) << 8;
  local_10 = uVar3 >> 0x10 & 0xf | uVar5 | uVar2 >> 8 & 0xf00;
  uVar3 = 0;
  do {
    puVar1 = local_2c + uVar3;
    uVar3 = uVar3 + 1;
    *puVar1 = *puVar1 * 100 >> 6;
  } while (uVar3 < 8);
  *param_2 = *(int *)(*(int *)(param_1 + 0x70) + 0x24);
  iVar4 = *(int *)(param_1 + 0x70);
  uVar3 = 0;
  piVar6 = param_2;
  if (*(int *)(iVar4 + 0x24) != 0) {
    do {
      piVar6[1] = (uint)*(byte *)(iVar4 + 0x28 + uVar3);
      piVar6[2] = -local_2c[uVar3];
      iVar4 = *(int *)(param_1 + 0x70);
      uVar3 = uVar3 + 1;
      piVar6 = piVar6 + 2;
    } while (uVar3 < *(uint *)(iVar4 + 0x24));
    if (7 < uVar3) goto LAB_001ccc1c;
  }
  piVar6 = param_2 + uVar3 * 2 + 2;
  iVar4 = 8 - uVar3;
  do {
    piVar6[-1] = -1;
    *piVar6 = -10000;
    piVar6 = piVar6 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
LAB_001ccc1c:
  param_2[0x11] = (int)(short)((uint)local_c >> 0x10);
  iVar4 = *(int *)(param_1 + 0x70);
  if ((*(int *)(iVar4 + 0xb8) == 0) || ((*(byte *)(iVar4 + 0xb) & 1) == 0)) {
    param_2[0x12] = 0;
    param_2[0x13] = 0;
    param_2[0x14] = 0;
    param_2[0x15] = 0;
    param_2[0x16] = 0;
  }
  else {
    param_2[0x12] = *(int *)(*(int *)(iVar4 + 0xb8) + 4);
    param_2[0x13] = *(int *)(*(int *)(*(int *)(param_1 + 0x70) + 0xb8) + 8);
    param_2[0x14] = *(int *)(*(int *)(*(int *)(param_1 + 0x70) + 0xb8) + 0x24);
    param_2[0x15] = *(int *)(*(int *)(*(int *)(param_1 + 0x70) + 0xb8) + 0x1c);
    param_2[0x16] = *(int *)(*(int *)(*(int *)(param_1 + 0x70) + 0xb8) + 0x20);
  }
  return local_8;
}




undefined4 __fastcall DSOUND::CMcpxVoiceClient_SetMixBins(int param_1)

{
  uint uVar1;
  ushort *puVar2;
  undefined4 local_34 [10];
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  FUN_001c5810();
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    FUN_001cbd10(&local_8,(uint *)(param_1 + 0x14));
    FUN_001cbdc1(local_34);
    do {
    } while (_DAT_fe820010 >> 2 < (uint)*(byte *)(param_1 + 100) << 3);
    uVar1 = 0;
    if (*(byte *)(param_1 + 100) != 0) {
      puVar2 = (ushort *)(param_1 + 0xc);
      do {
        _DAT_fe8202f8 = (uint)*puVar2;
        _DAT_fe820300 = local_8;
        _DAT_fe820304 = *(uint *)(param_1 + 0x14);
        if (uVar1 != 0) {
          _DAT_fe820304 = _DAT_fe820304 | 0x400000;
        }
        _DAT_fe820360 = local_34[uVar1];
        _DAT_fe820364 = local_34[uVar1 + 3];
        _DAT_fe820368 = local_34[uVar1 + 6];
        _DAT_fe8202fc = 0;
        uVar1 = uVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (uVar1 < *(byte *)(param_1 + 100));
    }
  }
  FUN_001c5832();
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 __fastcall DSOUND::CMcpxVoiceClient_SetVolume(int param_1)

{
  uint uVar1;
  ushort *puVar2;
  undefined4 local_30 [10];
  undefined4 local_8;
  
  local_8 = 0;
  FUN_001c5810();
  if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
    FUN_001cbdc1(local_30);
    do {
    } while (_DAT_fe820010 >> 2 < (uint)*(byte *)(param_1 + 100) * 6);
    uVar1 = 0;
    if (*(byte *)(param_1 + 100) != 0) {
      puVar2 = (ushort *)(param_1 + 0xc);
      do {
        _DAT_fe8202f8 = (uint)*puVar2;
        _DAT_fe820360 = local_30[uVar1];
        _DAT_fe820364 = local_30[uVar1 + 3];
        _DAT_fe820368 = local_30[uVar1 + 6];
        _DAT_fe8202fc = 0;
        uVar1 = uVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (uVar1 < *(byte *)(param_1 + 100));
    }
  }
  FUN_001c5832();
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


undefined4 __fastcall DSOUND::CMcpxVoiceClient_SetPitch(int param_1)

{
  ushort *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 local_8;
  
  FUN_001c5810();
  if ((*(uint *)(*(int *)(param_1 + 0x70) + 8) & 0x182000) == 0) {
    if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
      FUN_001cc015(&local_8);
      do {
      } while (_DAT_fe820010 >> 2 < (uint)*(byte *)(param_1 + 100) * 2);
      uVar2 = 0;
      if (*(byte *)(param_1 + 100) != 0) {
        puVar1 = (ushort *)(param_1 + 0xc);
        do {
          _DAT_fe8202f8 = (uint)*puVar1;
          _DAT_fe82037c = local_8;
          uVar2 = uVar2 + 1;
          puVar1 = puVar1 + 1;
        } while (uVar2 < *(byte *)(param_1 + 100));
      }
    }
  }
  else {
    for (puVar3 = *(undefined4 **)(param_1 + 0x44); puVar3 != (undefined4 *)(param_1 + 0x44);
        puVar3 = (undefined4 *)*puVar3) {
      CMcpxVoiceClient_SetPitch();
    }
  }
  FUN_001c5832();
  return 0;
}




void __fastcall DSOUND::CMcpxVoiceClient_Commit3dSettings(int param_1)

{
  DWORD a2;
  int iVar1;
  
  FUN_001c5849();
  if ((*(byte *)(param_1 + 0x12) & 3) == 3) {
    CDirectSound3DCalculator_Calculate3D
              (*(int *)(*(int *)(param_1 + 8) + 0xc) + 0x30,
               *(DWORD *)(*(int *)(param_1 + 0x70) + 0xb4));
    a2 = *(DWORD *)(*(int *)(param_1 + 0x70) + 0xb4);
    iVar1 = *(int *)(*(int *)(param_1 + 8) + 0xc);
    CDirectSound3DCalculator_GetVoiceData
              (iVar1 + 0x30,a2,iVar1 + 0x80,a2 + 0x7c,*(DWORD *)(*(int *)(param_1 + 0x70) + 0xb8));
    **(undefined4 **)(*(int *)(param_1 + 0x70) + 0xb4) = 0;
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x70) + 0xb4) + 0x7c) = 0;
    FUN_001cd054();
  }
  FUN_001c586e();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


int __thiscall DSOUND::CMcpxBuffer_Pause(int param_1,int param_2)

{
  ushort uVar1;
  
  FUN_001c5810();
  if ((*(byte *)(param_1 + 0x12) & 3) == 3) {
    if (param_2 == 0) {
      uVar1 = *(ushort *)(param_1 + 0x12) & 0xffbb;
    }
    else if (param_2 == 1) {
      uVar1 = *(ushort *)(param_1 + 0x12) & 0xffbf | 4;
    }
    else {
      if (param_2 != 2) {
        param_2 = -0x7fffbffb;
        goto LAB_001cdaed;
      }
      uVar1 = *(ushort *)(param_1 + 0x12) & 0xfffb | 0x40;
    }
    param_2 = FUN_001cc424(uVar1);
  }
LAB_001cdaed:
  FUN_001c5832();
  return param_2;
}




undefined4 __thiscall DSOUND::CMcpxBuffer_GetStatus(int param_1,uint *param_2)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(param_1 + 0x12);
  if (((byte)uVar1 & 3) == 3) {
    *param_2 = ((uVar1 & 0x444) != 0) + 1;
    if ((uVar1 & 0x200) != 0) {
      *param_2 = *param_2 | 4;
    }
  }
  else {
    *param_2 = (uint)((uVar1 & 0x8001) == 0x8001);
  }
  return 0;
}



undefined4 __thiscall

DSOUND::CMcpxBuffer_GetCurrentPosition(int param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  FUN_001c5810();
  if ((*(byte *)(param_1 + 0x12) & 3) == 3) {
    uVar3 = FUN_001cca84();
    if (param_2 != (uint *)0x0) {
      *param_2 = uVar3;
    }
    if (param_3 != (uint *)0x0) {
      uVar4 = FUN_001ca65a(0x20);
      uVar1 = *(uint *)(*(int *)(param_1 + 0x80) + 0x14);
      if (uVar4 < uVar1) {
        uVar4 = uVar1;
      }
      uVar4 = uVar4 + uVar3;
      *param_3 = uVar4;
      if ((((*(ushort *)(param_1 + 0x12) & 0x200) == 0) ||
          (iVar2 = *(int *)(param_1 + 0x80), uVar3 < *(uint *)(iVar2 + 0xcc))) ||
         ((uint)(*(int *)(iVar2 + 0xd0) + *(int *)(iVar2 + 0xcc)) <= uVar3)) {
        *param_3 = uVar4 % *(uint *)(*(int *)(param_1 + 0x80) + 0xc0);
      }
      else {
        uVar4 = uVar4 % *(uint *)(iVar2 + 0xd0);
        *param_3 = uVar4;
        *param_3 = *(int *)(*(int *)(param_1 + 0x80) + 0xcc) + uVar4;
      }
    }
  }
  else {
    if (param_2 != (uint *)0x0) {
      *param_2 = *(uint *)(param_1 + 0x148);
    }
    if (param_3 != (uint *)0x0) {
      *param_3 = *(uint *)(param_1 + 0x148);
    }
  }
  FUN_001c5832();
  return 0;
}




int __thiscall DSOUND::CMcpxBuffer_Play(int *param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  if ((*(uint *)(param_1[0x20] + 8) & 0x182000) != 0) {
    param_2 = 1;
  }
  iVar1 = FUN_001cdefa();
  if (-1 < iVar1) {
    if (((param_2 & 4) != 0) && ((*(byte *)((int)param_1 + 0x12) & 0x42) == 0)) {
      iVar1 = FUN_001cc424(0x40);
    }
    if (-1 < iVar1) {
      if ((*(byte *)(param_1[0x20] + 9) & 0x20) == 0) {
        if (((param_2 & 2) == 0) && ((*(ushort *)((int)param_1 + 0x12) & 0x446) == 0)) {
          iVar2 = param_1[0x52];
        }
        else {
          iVar2 = 0;
        }
        param_1[0x52] = 0;
        if (iVar2 == 0) {
          FUN_001cd7c9(param_2);
        }
        else {
          FUN_001cd90a(iVar2,param_2);
        }
        if (*(int *)(param_1[0x20] + 0xdc) != 0) {
          (**(code **)(*param_1 + 0x1c))(2,0,0,0);
        }
      }
      else {
        FUN_001cd52d();
      }
    }
  }
  return iVar1;
}




int __thiscall DSOUND::CMcpxBuffer_Stop(int *param_1,byte param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if ((*(byte *)((int)param_1 + 0x12) & 3) == 3) {
    if ((param_2 & 1) == 0) {
      if ((*(uint *)(param_1[0x20] + 8) & 0x182000) == 0) {
        CMcpxBuffer_GetCurrentPosition(param_1 + 0x52,0);
      }
      FUN_001cd122(0);
      FUN_001cde5b();
      if ((*(byte *)(param_1[0x20] + 10) & 4) != 0) {
        (**(code **)(*param_1 + 0x1c))(1,0,0,0);
      }
    }
    else {
      if ((((param_2 & 2) != 0) && ((*(ushort *)((int)param_1 + 0x12) & 0x203) == 0x203)) &&
         (iVar1 = CMcpxBuffer_Play(0), iVar1 < 0)) {
        return iVar1;
      }
      FUN_001cc34c();
    }
  }
  return iVar1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


int __thiscall DSOUND::CMcpxBuffer_SetCurrentPosition(int param_1,uint param_2)

{
  undefined4 uVar1;
  ushort *puVar2;
  uint uVar3;
  int local_8;
  
  local_8 = 0;
  if ((*(byte *)(param_1 + 0x12) & 3) == 3) {
    do {
    } while ((*(uint *)((uint)*(ushort *)(param_1 + 10 + (uint)*(byte *)(param_1 + 100) * 2) * 0x80
                        + 0x54 + DAT_001e3c40) & 0x100000) != 0);
    if (((*(ushort *)(param_1 + 0x12) & 0x203) == 0x203) &&
       ((uint)(*(int *)(*(int *)(param_1 + 0x80) + 0xd0) + *(int *)(*(int *)(param_1 + 0x80) + 0xcc)
              ) <= param_2)) {
      local_8 = CMcpxBuffer_Play(0);
      if (local_8 < 0) goto LAB_001ce1d8;
    }
    uVar1 = FUN_001ca641(param_2);
    FUN_001c5810();
    do {
    } while (_DAT_fe820010 >> 2 < (uint)*(byte *)(param_1 + 100) << 2);
    uVar3 = 0;
    if (*(byte *)(param_1 + 100) != 0) {
      puVar2 = (ushort *)(param_1 + 0xc);
      do {
        _DAT_fe8202f8 = (uint)*puVar2;
        _DAT_fe8202fc = 0;
        uVar3 = uVar3 + 1;
        puVar2 = puVar2 + 1;
        _DAT_fe8203d8 = uVar1;
      } while (uVar3 < *(byte *)(param_1 + 100));
    }
    FUN_001c5832();
  }
  else {
    *(uint *)(param_1 + 0x148) = param_2;
  }
LAB_001ce1d8:
  FUN_001cde5b();
  return local_8;
}




void __fastcall DSOUND::CMcpxBuffer_SetBufferData(int param_1)

{
  *(undefined4 *)(param_1 + 0x148) = 0;
  if ((*(byte *)(*(int *)(param_1 + 0x80) + 10) & 4) == 0) {
    FUN_001cdefa();
    return;
  }
  return;
}




DSOUND::CMcpxBuffer_Stop_Ex(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_2 != 0 || param_3 != 0) &&
     (iVar1 = (**(code **)(*param_1 + 0x1c))(4,param_2,param_3,param_4), iVar1 != 0)) {
    return 0;
  }
  uVar2 = CMcpxBuffer_Stop(param_4);
  return uVar2;
}




HRESULT DSOUND::CDirectSoundStream_Pause(CDirectSoundStream *pThis,DWORD dwPause)

{
  code *pcVar1;
  uint uVar2;
  byte bVar3;
  undefined4 in_EAX;
  uint uVar4;
  uint *in_ECX;
  uint *puVar5;
  int unaff_EBX;
  char *unaff_EDI;
  byte in_AF;
  
                    // WARNING: Read-only address (ram,0x0019292c) is written
  bRam0019292c = (byte)((uint)in_ECX >> 8) ^ 0xf6;
  puVar5 = (uint *)CONCAT31((int3)((int)in_ECX + *in_ECX >> 8),
                            (char)((int)in_ECX + *in_ECX) + *unaff_EDI +
                            CARRY4((uint)in_ECX,*in_ECX));
  *puVar5 = *puVar5 | (uint)puVar5;
  uVar4 = CONCAT31((int3)((uint)in_EAX >> 8),(char)in_EAX + '\x12') | 0x21375148;
  *(uint *)(uVar4 * 3) = *(uint *)(uVar4 * 3) ^ (uint)unaff_EDI;
  bVar3 = (byte)uVar4;
  uVar2 = *puVar5;
  DAT_2e353b2e = DAT_2e353b2e + (char)uVar2;
  *puVar5 = *puVar5 - unaff_EBX;
  *(int *)((int)(unaff_EDI + 2) * 2) =
       *(int *)((int)(unaff_EDI + 2) * 2) +
       CONCAT31((int3)((uint)(CONCAT31((int3)(uVar4 >> 8),
                                       bVar3 + (9 < (bVar3 & 0xf) | in_AF) * '\x06' +
                                       (0x99 < bVar3) * '`') + -0x4e6cd4c7) >> 8),
                (char)uVar2 + -0x2b);
                    // WARNING: Does not return
  pcVar1 = (code *)invalidInstructionException();
  (*pcVar1)();
}



// WARNING: Unable to track spacebase fully for stack
// WARNING: Globals starting with '_' overlap smaller symbols at the same address


HRESULT DSOUND::CDirectSoundStream_SetEG(CDirectSoundStream *pThis,DSENVOLOPEDESC *pEnvelopeDesc)

{
  undefined4 *puVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  uint *puVar5;
  undefined6 uVar6;
  code *pcVar7;
  byte bVar8;
  uint uVar9;
  int *piVar10;
  char cVar11;
  uint *in_ECX;
  uint *puVar12;
  uint uVar13;
  byte *in_EDX;
  undefined4 unaff_EBX;
  byte *pbVar14;
  char *unaff_ESI;
  undefined4 *unaff_EDI;
  undefined2 in_SS;
  
  puVar12 = (uint *)((uint)in_ECX | *in_ECX);
  bVar8 = *in_EDX;
  uVar6 = *(undefined6 *)((int)unaff_EDI + 0x3685064e);
  *unaff_EDI = (int)uVar6;
  pcVar2 = unaff_ESI + 0x2400a60f + (int)puVar12;
  puVar5 = (uint *)(CONCAT31((int3)((uint)in_EDX >> 8),(byte)in_EDX | bVar8) +
                   *(int *)((int)puVar12 + 0x40340003));
  *(byte *)puVar12 = (byte)*puVar12 & (byte)((uint)puVar12 >> 8);
  uVar9 = CONCAT31((int3)((uint6)uVar6 >> 8),(byte)uVar6 - 0x27) + -0x7c7ddfe0 +
          (uint)((byte)uVar6 < 0x27);
  *(undefined2 *)(pcVar2 + -4) = in_SS;
  pbVar14 = (byte *)(CONCAT31((int3)((uint)unaff_EBX >> 8),0xa6) & *puVar12);
  *(uint *)((int)puVar12 + uVar9) = *(uint *)((int)puVar12 + uVar9) | uVar9;
  cVar11 = (byte)puVar12 + (byte)*puVar12;
  *unaff_ESI = *unaff_ESI + cVar11 + CARRY1((byte)puVar12,(byte)*puVar12);
  uVar13 = CONCAT31((int3)((uint)puVar12 >> 8),cVar11) | *puVar5;
  uVar9 = (uVar9 | 0x11) ^ 10;
  _DAT_c1049d45 = uVar9;
  *(char *)(unaff_EDI + 1) = (char)uVar9;
  piVar10 = (int *)(uVar9 & 0xb6a83782);
  *(undefined4 *)((int)puVar5 + -0x5c79524d) = *(undefined4 *)(pcVar2 + -4);
  iVar4 = *(int *)pbVar14;
  DAT_90132083 = SUB41(piVar10,0);
  *piVar10 = *piVar10 + 0x232b4038;
  cVar11 = *unaff_ESI;
  piVar10 = (int *)(uVar9 & 0x84202100);
  *piVar10 = *piVar10 + -0x25;
  *(undefined2 *)(pcVar2 + -4) = in_SS;
  LOCK();
  puVar1 = (undefined4 *)((int)puVar5 + iVar4 + 0x1830105);
  uVar3 = *puVar1;
  *puVar1 = piVar10;
  UNLOCK();
  bVar8 = (byte)uVar3;
  *pbVar14 = *pbVar14 | bVar8;
  pbVar14[CONCAT22((short)(uVar13 >> 0x10),CONCAT11((char)(uVar13 >> 8) - cVar11,(char)uVar13))] =
       pbVar14[CONCAT22((short)(uVar13 >> 0x10),CONCAT11((char)(uVar13 >> 8) - cVar11,(char)uVar13))
              ] + bVar8;
                    // WARNING: Does not return
  pcVar7 = (code *)invalidInstructionException();
  (*pcVar7)();
}



// WARNING: Unable to track spacebase fully for stack
// WARNING: Globals starting with '_' overlap smaller symbols at the same address


HRESULT DSOUND::CDirectSoundStream_SetHeadroom(CDirectSoundStream *pThis,DWORD dwHeadroom)

{
  ushort *puVar1;
  byte *pbVar2;
  int iVar3;
  short sVar4;
  undefined8 uVar5;
  byte in_AL;
  uint *puVar6;
  uint in_ECX;
  byte *pbVar7;
  uint unaff_EBP;
  uint uVar8;
  uint *unaff_ESI;
  undefined2 in_ES;
  undefined2 in_CS;
  undefined2 auStack_4 [2];
  
  uVar8 = unaff_EBP & _DAT_1f0b262f;
  *(byte *)(in_ECX + 0x83868204) = in_AL & *(byte *)(uVar8 + 0x17251984);
  *unaff_ESI = *unaff_ESI | in_ECX;
  uVar5 = rdmsr(in_ECX);
  pbVar7 = (byte *)((ulonglong)uVar5 >> 0x20);
  puVar1 = (ushort *)(uVar8 + 0x27);
  sVar4 = ((ushort)in_ECX & 3) - (*puVar1 & 3);
  *puVar1 = *puVar1 + (ushort)(0 < sVar4) * sVar4;
  pbVar2 = (byte *)((int)uVar5 + 0x3d);
  *pbVar2 = *pbVar2 << 2 | *pbVar2 >> 6;
  iVar3 = *(int *)(in_ECX + 0x8683169e);
  puVar6 = (uint *)CONCAT31((int3)((ulonglong)uVar5 >> 8),((byte)uVar5 ^ 0x96) + 0x11);
  *puVar6 = *puVar6 & (uint)unaff_ESI;
  *pbVar7 = *pbVar7 | 0xa4;
  *(undefined2 *)((int)auStack_4 + iVar3) = in_ES;
  LOCK();
  pbVar7[-0x7bfcfb79] = (byte)in_ECX;
  UNLOCK();
  *pbVar7 = *pbVar7 | 0x13;
  *(undefined2 *)(&stack0x00000000 + (iVar3 - _DAT_b4af1df4)) = in_CS;
  return -0x4b50e25c;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


HRESULT DSOUND::CDirectSoundStream_SetFormat(CDirectSoundStream *pThis,LPCWAVEFORMATEX pwfxFormat)

{
  char *pcVar1;
  uint uVar2;
  uint uVar3;
  byte *in_EAX;
  byte *pbVar4;
  uint uVar5;
  byte *in_ECX;
  uint *puVar6;
  uint *in_EDX;
  byte unaff_BL;
  uint unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  in_ECX[0xc89879b] = in_ECX[0xc89879b] ^ 0x1d;
  *(byte *)(in_EDX + 0x12510080) = (char)in_EDX[0x12510080] + unaff_BL;
  *in_EAX = *in_EAX & unaff_BL;
  pbVar4 = (byte *)CONCAT22((short)((uint)in_EAX >> 0x10),
                            CONCAT11((byte)((uint)in_EAX >> 8) ^ *in_ECX,(char)in_EAX));
  *pbVar4 = *pbVar4 & 0x11;
  uVar2 = *in_EDX;
  *in_EDX = *in_EDX - 0x96112b;
  puVar6 = (uint *)((int)in_ECX * 5);
  uVar5 = *puVar6;
  uVar3 = *puVar6;
  *puVar6 = (uint)(pbVar4 + uVar3 + (uVar2 < 0x96112b));
  *(byte **)(in_ECX + 0xa008788) = pbVar4;
  *(int *)(unaff_EDI + 4) =
       (int)(pbVar4 + (uint)(CARRY4(uVar5,(uint)pbVar4) ||
                            CARRY4((uint)(pbVar4 + uVar3),(uint)(uVar2 < 0x96112b))) +
                      *(int *)(unaff_EDI + 4));
  pbVar4 = pbVar4 + 0x54630809;
  puVar6 = (uint *)((uint)in_ECX | (uint)pbVar4);
  _DAT_2615283c = pbVar4;
  *(char *)(unaff_ESI + 0x24afaf07) = *(char *)(unaff_ESI + 0x24afaf07) + (char)puVar6;
  uVar5 = (uint)pbVar4 | 0x8586a2b1;
  uVar2 = *puVar6;
  pcVar1 = (char *)(uVar5 + 0xd000299 + unaff_EDI + 5);
  *pcVar1 = *pcVar1 + (char)in_EDX + (0xf2fffd66 < uVar5);
  _DAT_ab0d2186 = _DAT_ab0d2186 ^ CONCAT31(0x9d1436,(byte)uVar2 | 0x38) - 1U;
  *puVar6 = *puVar6 + uVar5 + 0xd000299 + (uint)CARRY4(unaff_EBP,_DAT_019a0d2b);
  *(uint **)(uVar5 + 0xd888d1a) = puVar6;
  *puVar6 = *puVar6 | (uint)in_EDX;
  return uVar5 + 0x70070a9c;
}



HRESULT DSOUND::IDirectSound_SetI3DL2Listener
                  (LPDIRECTSOUND8 pThis,DSI3DL2LISTENER *pds3dl,DWORD dwApply)

{
  uint uVar1;
  uint uVar2;
  undefined4 in_EAX;
  uint uVar3;
  int iVar4;
  uint *in_ECX;
  int in_EDX;
  uint unaff_EBX;
  int *unaff_ESI;
  byte in_CF;
  
  *(char *)(unaff_EBX + 0x3027008e) =
       *(char *)(unaff_EBX + 0x3027008e) + (char)in_EDX + (0x42 < in_CF);
  uVar1 = *in_ECX;
  uVar3 = CONCAT31((int3)((uint)in_EAX >> 8),in_CF + 0xbd) & 0x20202020;
  uVar2 = *in_ECX;
  *(int *)(uVar3 * 2) = *(int *)(uVar3 * 2) + uVar3 + (uint)(unaff_EBX < *in_ECX);
  *unaff_ESI = *unaff_ESI + uVar3;
  iVar4 = uVar3 + *(int *)(unaff_EBX - uVar2);
  return CONCAT31((int3)((uint)iVar4 >> 8),(char)iVar4 + *(char *)(in_EDX + uVar1 + 0x1a020181));
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

HRESULT DSOUND::DirectSoundCreate
                  (LPVOID pguidDeviceId,LPDIRECTSOUND8 *ppDirectSound,LPUNKNOWN pUnknown)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  char cVar6;
  char *in_EAX;
  undefined3 uVar7;
  uint uVar4;
  byte *pbVar5;
  byte bVar8;
  char *in_ECX;
  byte bVar9;
  undefined4 in_EDX;
  byte *unaff_EBX;
  int unaff_EBP;
  int iVar10;
  char *unaff_EDI;
  undefined2 in_CS;
  
  LOCK();
  cVar3 = *in_EAX;
  *in_EAX = (char)in_EAX;
  uVar7 = (undefined3)((uint)in_EAX >> 8);
  UNLOCK();
  bVar9 = (byte)((uint)in_EDX >> 8);
  DAT_312e2b31 = DAT_312e2b31 - bVar9;
  bVar8 = (byte)((uint)in_ECX >> 8);
  *unaff_EBX = *unaff_EBX ^ bVar8;
  bVar2 = *unaff_EBX;
  *unaff_EBX = *unaff_EBX - bVar8;
  *in_ECX = (*in_ECX - (char)unaff_EBX) - (bVar2 < bVar8);
  *(uint *)(in_ECX + -0x7bfffe7e) = *(uint *)(in_ECX + -0x7bfffe7e) | CONCAT31(uVar7,cVar3);
  bVar2 = cVar3 + 8;
  iVar10 = _DAT_4f9d16cb * -0x76;
  *(undefined2 *)(in_ECX + -0x6b) = in_CS;
  uVar4 = CONCAT31(uVar7,bVar2 + (9 < (bVar2 & 0xf) || ((uint)in_EAX & 0x1000) != 0) * -6 +
                         (0x99 < bVar2 || ((uint)in_EAX & 0x100) != 0) * -0x60) | 0x18;
  DAT_82978ca2 = (char)uVar4;
  *(int *)(uVar4 + 0xe9593ac) = *(int *)(uVar4 + 0xe9593ac) + unaff_EBP;
  cVar3 = in_ECX[uVar4 * 4];
  cVar6 = (char)((uint)in_EAX >> 8);
  *unaff_EDI = *unaff_EDI + cVar6;
  pbVar5 = (byte *)(CONCAT31(uVar7,(char)uVar4 + cVar3) ^ 0x31);
  *pbVar5 = *pbVar5 ^ bVar9;
  iVar1 = (CONCAT31((int3)(CONCAT22((short)((uint)in_EAX >> 0x10),
                                    CONCAT11(cVar6 - *pbVar5,(char)pbVar5)) >> 8),(char)pbVar5) |
          0xf) + 0xfefcf8eb;
  unaff_EBX[iVar1 * 4 + -0x76787c7e] = unaff_EBX[iVar1 * 4 + -0x76787c7e] + 0x83;
  uVar7 = (undefined3)((uint)iVar1 >> 8);
  cVar3 = (char)iVar1 + '\x03';
  return CONCAT31(uVar7,cVar3 + *(char *)(iVar10 + CONCAT31(uVar7,cVar3)));
}




int DSOUND::XWmaDecoderCreateMediaObject(undefined4 param_1,undefined4 *param_2)

{
  void *pvVar1;
  int *piVar2;
  int iVar3;
  
  pvVar1 = XAPILIB::XMemAlloc(0x94,0x6482a000);
  if (pvVar1 == (void *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = (int *)FUN_001e4583();
  }
  if (piVar2 == (int *)0x0) {
    iVar3 = -0x7ff8fff2;
  }
  else {
    iVar3 = FUN_001e3e10(param_1);
    if (-1 < iVar3) {
      *param_2 = piVar2;
      return iVar3;
    }
  }
  *param_2 = 0;
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 4))(piVar2);
  }
  return iVar3;
}




