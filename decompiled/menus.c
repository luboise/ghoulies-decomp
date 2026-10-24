/* menus.c - Menus & UI (pause, replay, challenge menus) */
#include "menus.h"

void GetText(ushort target,ushort param_2,vec2 *scale,float *outFloat1,float *outFloat2,uint index)

{
  uint num_entries;
  int i;
  uint uVar1;
  int iVar2;
  bool bVar3;
  TextEntry *entries;
  
  if (((target != 0) && (param_2 != 0)) &&
     (num_entries = TextLookupTables[index].numValues, num_entries != 0)) {
    entries = TextLookupTables[index].entries;
    iVar2 = 0;
    uVar1 = num_entries;
    while (i = (int)num_entries / 2, iVar2 <= (int)uVar1) {
      bVar3 = target < entries[i].val;
      if ((target == entries[i].val) &&
         (bVar3 = param_2 < entries[i].val2, param_2 == entries[i].val2)) {
        if ((outFloat1 != (float *)0x0) && (entries[i].float1 != 0.0)) {
          *outFloat1 = scale->x * entries[i].float1 + *outFloat1;
        }
        if (outFloat2 == (float *)0x0) {
          return;
        }
        if (entries[i].float2 == 0.0) {
          return;
        }
        *outFloat2 = scale->y * entries[i].float2 + *outFloat2;
        return;
      }
      if (bVar3) {
        uVar1 = i - 1;
        num_entries = iVar2 + uVar1;
      }
      else {
        iVar2 = i + 1;
        num_entries = iVar2 + uVar1;
      }
    }
  }
  return;
}




short * RecomputeLoctextFString(float *x,float *y,float *scale,wchar_t *param_4)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  
  *scale = 1.0;
  *y = 0.0;
  *x = 0.0;
  if (*param_4 == L'¬') {
    _swscanf(param_4 + 1,L"%f %f %f",y,x,scale);
    wVar2 = *param_4;
    while (wVar2 != L'\0') {
      if (wVar2 == L'¬') goto LAB_000602ca;
      pwVar1 = param_4 + 1;
      param_4 = param_4 + 1;
      wVar2 = *pwVar1;
    }
    if (*param_4 == L'¬') {
LAB_000602ca:
      return param_4 + 1;
    }
  }
  return param_4;
}




void SetSaveNameMenu::alloc(void)

{
  malloc_(0x498);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL BnousChallengesMenu::ctor(entitySceneControlGameSelect *param_1,BonusChallengesMenu *param_2)

{
  entitySceneControlGameSelect **ppeVar1;
  undefined4 *puVar2;
  int *piVar3;
  ushort uVar4;
  LoctextValueContext *pLVar5;
  int iVar6;
  astruct_16 *paVar7;
  astruct_15 *paVar8;
  BonusChallengesMenu *this;
  char cVar9;
  void *pvVar10;
  byte *pbVar11;
  BOOL BVar12;
  entitySceneControlGameSelect *peVar13;
  BonusChallengesMenu *pBVar14;
  int i;
  byte bVar15;
  AudioPlayingContext *play_ctx;
  char *pcVar16;
  uint uVar17;
  char *pcVar18;
  byte *pbVar19;
  char *pcVar20;
  char *name2;
  int next_i;
  bool bad_id;
  LoctextDescriptor *local_24;
  int local_20;
  entitySceneControlGameSelect *local_1c;
  void *local_18;
  char *local_14;
  char *local_10;
  char *local_c;
  int len;
  int local_4;
  char *aidlist;
  BonusChallengesMenu *puVar12;
  BonusChallengesMenu *puVar13;
  TextureDescriptor *paVar12;
  BonusChallengesMenu *paVar11;
  
  this = param_2;
  param_2->nextPlaycamWide[0] = L'\0';
  XAPILIB::lstrcpyW(param_2->nextPlaycamWide,game::nextPlaycamScriptWide);
  FUN_000f3020();
  paVar8 = SomeAS15;
  *SomeAS15->flags = *SomeAS15->flags | 2;
  *paVar8->flags = *paVar8->flags | 4;
  runtime::SaveTheGame_();
  this->field20_0x14c = 0;
  this->state = 0;
  this->sceneControlGameSelect = param_1;
  this->field10_0x124 = 0.0;
  this->field11_0x128 = 0.0;
  _DAT_00506574 = this;
  this->field12_0x12c = 0;
  runtime::AllocateForLoctext_(0,1,(void *)0xc0,&this->field19_0x148);
  pLVar5 = this->field19_0x148;
  (pLVar5->somePos).x = 3.0;
  (pLVar5->somePos).y = 0.7;
  pLVar5->maybeState = 3;
  Assets::GetResourceBytes("aid_loctext_ghoulies_script_scenenames",&local_24);
  if (local_24 == (LoctextDescriptor *)0x0) {
    runtime::ExitGame(2);
  }
  Assets::GetResourceBytes("aid_aidlist_ghoulies_challenges_challengeorder",&local_18);
  if (local_18 == (void *)0x0) {
    runtime::ExitGame(2);
  }
  pvVar10 = malloc_(0x5cdc);
  paVar7 = PTR_00506c54;
  this->field4_0x10c = pvVar10;
  this->field5_0x110 = 0;
  this->field6_0x114 = 0;
  this->field7_0x118 = 0;
  this->field8_0x11c = 0;
  this->field9_0x120 = 0;
  pbVar11 = (byte *)paVar7->field2_0x8;
  pbVar19 = pbVar11 + paVar7->copySize;
  local_1c = (entitySceneControlGameSelect *)0x0;
  for (; pbVar11 < pbVar19; pbVar11 = pbVar11 + 1) {
    i = 0;
    for (bVar15 = *pbVar11; bVar15 != 0; bVar15 = bVar15 & bVar15 - 1) {
      i = i + 1;
    }
    local_1c = (entitySceneControlGameSelect *)((local_1c->maybeVertex).name + i + -0x58);
  }
  if ((DAT_00506578 == 0x14) && ((PTR_00506c6c->field2_0x8[4] & 0x20) == 0)) {
    DAT_0050657c = 0x14;
    DAT_00506578 = 0;
  }
  local_20 = 0;
  do {
    i = local_20;
    if (*(int *)(local_20 * 0x80 + (int)local_18) == 0x5f646961) {
      Assets::GetResourceBytes((char *)(local_20 * 0x80 + (int)local_18),&local_10);
      pcVar18 = local_10;
      if (local_10 == (char *)0x0) {
        runtime::ExitGame(2);
      }
    }
    else {
      pcVar18 = (char *)0x0;
    }
    param_2 = (BonusChallengesMenu *)(i * 0x46c);
    *(int *)((int)this->field4_0x10c + (int)(param_2->nextPlaycamWide + -4)) = i;
    if (i == 20) {
      *(undefined4 *)((int)this->field4_0x10c + 0x5cd8) = 1;
    }
    else {
      *(uint *)((int)this->field4_0x10c + (int)(param_2[1].nextPlaycamWide + -4)) =
           (uint)(i * 5 + 5 <= (int)local_1c);
    }
    *(undefined4 *)((int)this->field4_0x10c + (int)&param_2->field_0x45c) = 0;
    *(int32_t *)((int)this->field4_0x10c + (int)&param_2->field_0x460) = -1;
    *(undefined4 *)((int)this->field4_0x10c + (int)&param_2->field_0x464) = 0x80069764;
    *(undefined4 *)((int)this->field4_0x10c + (int)(param_2->nextPlaycamWide + 0x18)) = 2;
    pvVar10 = (void *)((int)this->field4_0x10c + (int)param_2);
    if (*(int *)((int)this->field4_0x10c + (int)(param_2[1].nextPlaycamWide + -4)) == 0) {
      pcVar16 = "aid_texture_ghoulies_gameselect_challenges_locked";
      pcVar20 = (char *)((int)pvVar10 + 0x248);
      do {
        cVar9 = *pcVar16;
        *pcVar20 = cVar9;
        pcVar20 = pcVar20 + 1;
        pcVar16 = pcVar16 + 1;
      } while (cVar9 != '\0');
      *(undefined1 *)((int)this->field4_0x10c + (int)&param_2->field_0x2c8) = 0;
      createGameselectString("scenenames","locked",u__00507e78,local_24);
      pcVar20 = (char *)((int)this->field4_0x10c + (int)&param_2->field_0x348);
      pcVar16 = "challengelocked";
      do {
        cVar9 = *pcVar16;
        *pcVar20 = cVar9;
        pcVar20 = pcVar20 + 1;
        pcVar16 = pcVar16 + 1;
      } while (cVar9 != '\0');
    }
    else {
      pcVar20 = pcVar18 + 0xc0;
      pcVar16 = (char *)((int)pvVar10 + 0x248);
      do {
        cVar9 = *pcVar20;
        *pcVar16 = cVar9;
        next_i = DAT_004e1740;
        pcVar16 = pcVar16 + 1;
        pcVar20 = pcVar20 + 1;
      } while (cVar9 != '\0');
      if (i == 20) {
        local_4 = DAT_004e1740;
        Assets::GetResourceBytes("aid_aidlist_ghoulies_sceneorder_challenge21",&local_c);
        aidlist = local_c;
        if (local_c == (char *)0x0) {
          runtime::ExitGame(2);
        }
        local_14 = aidlist;
        len = AIDListResource::getLength((asset_name *)&local_14);
        pcVar20 = (char *)0x0;
        pcVar16 = aidlist;
        name2 = aidlist;
        if (0 < next_i) {
          do {
            pcVar16 = name2;
            if (len <= (int)pcVar20) break;
            local_14 = pcVar20 + 1;
            if (aidlist == (char *)0x0) {
LAB_000d5bad:
              pcVar16 = (char *)0x0;
            }
            else {
              pcVar20 = aidlist;
              pcVar16 = aidlist;
              if (name2 != (asset_name_t)0x0) {
                do {
                  BVar12 = Assets::AssetNamesMatch(pcVar20,name2);
                  if (BVar12 != 0) {
                    if ((pcVar20 != (char *)0x0) &&
                       (pcVar16 = pcVar20 + 0x80, *(int *)(pcVar20 + 0x80) == 0x5f646961))
                    goto LAB_000d5baf;
                    break;
                  }
                  pcVar16 = pcVar20 + 0x80;
                  if (*(int *)(pcVar20 + 0x80) != 0x5f646961) {
                    pcVar16 = (char *)0x0;
                  }
                  pcVar20 = pcVar16;
                } while (pcVar16 != (char *)0x0);
                goto LAB_000d5bad;
              }
            }
LAB_000d5baf:
            pcVar20 = local_14;
            name2 = pcVar16;
          } while ((int)local_14 < local_4);
        }
        pcVar20 = (char *)((int)this->field4_0x10c + 0x5b38);
        do {
          cVar9 = *pcVar16;
          *pcVar20 = cVar9;
          pcVar20 = pcVar20 + 1;
          pcVar16 = pcVar16 + 1;
        } while (cVar9 != '\0');
      }
      else {
        pcVar20 = pcVar18 + 0x40;
        pcVar16 = (char *)((int)this->field4_0x10c + (int)&param_2->field_0x2c8);
        do {
          cVar9 = *pcVar20;
          *pcVar16 = cVar9;
          pcVar16 = pcVar16 + 1;
          pcVar20 = pcVar20 + 1;
        } while (cVar9 != '\0');
      }
      createGameselectString("scenenames",pcVar18,u__00507e78,local_24);
      pcVar20 = (char *)((int)this->field4_0x10c + (int)&param_2->field_0x348);
      pcVar16 = pcVar18;
      do {
        cVar9 = *pcVar16;
        *pcVar20 = cVar9;
        pcVar20 = pcVar20 + 1;
        pcVar16 = pcVar16 + 1;
      } while (cVar9 != '\0');
    }
    pBVar14 = param_2;
    XAPILIB::lstrcpyW((LPWSTR)((int)this->field4_0x10c + (int)(param_2->nextPlaycamWide + 0x1a)),
                      u__00507e78);
    pvVar10 = this->field4_0x10c;
    *(float *)((int)pvVar10 + (int)&pBVar14->field_0x23c) = g_DXContext.field28_0x48;
    *(float *)((int)pvVar10 + (int)&pBVar14->field_0x240) = g_DXContext.__0;
    *(undefined4 *)((int)this->field4_0x10c + (int)&pBVar14->field_0x448) =
         *(undefined4 *)(pcVar18 + 0x140);
    *(undefined4 *)((int)this->field4_0x10c + (int)&pBVar14->field_0x44c) =
         *(undefined4 *)(pcVar18 + 0x144);
    *(undefined4 *)((int)this->field4_0x10c + (int)&pBVar14->field_0x450) =
         *(undefined4 *)(pcVar18 + 0x148);
    *(undefined4 *)((int)this->field4_0x10c + (int)&pBVar14->field_0x454) =
         *(undefined4 *)(pcVar18 + 0x14c);
    *(undefined4 *)((int)this->field4_0x10c + (int)&pBVar14->field_0x458) =
         (&DAT_004e194c)[*(int *)((int)this->field4_0x10c + (int)pBVar14)];
    puVar2 = (undefined4 *)((int)this->field4_0x10c + (int)(pBVar14->nextPlaycamWide + -2));
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2[10] = 0;
    puVar2[0xb] = FLOAT_00428c10;
    puVar2[0xc] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = 0;
    puVar2[8] = 0;
    puVar2[9] = 0;
    next_i = local_20 + 1;
    piVar3 = (int *)((int)this->field4_0x10c + (int)(pBVar14->nextPlaycamWide + -2));
    i = next_i;
    if (next_i < 0) {
      i = 0;
    }
    piVar3[1] = i;
    *piVar3 = i;
    FUN_0012f990(&FLOAT_00428c10,piVar3);
    Assets::DestroyAssetOrDecrement(pcVar18);
    local_20 = next_i;
  } while (next_i < 21);
  this->numFuckers = (byte)PTR_00506c6c->field2_0x8[4] >> 5 & 1 | 0b00010100;
  ppeVar1 = &this->field48_0x1a4;
  *ppeVar1 = (entitySceneControlGameSelect *)0x0;
  this->field49_0x1a8 = (entitySceneControlGameSelect *)0x0;
  this->field58_0x1cc = 0;
  this->field59_0x1d0 = FLOAT_00428c10;
  this->field60_0x1d4 = 0;
  this->field50_0x1ac = 0;
  this->field51_0x1b0 = 0;
  this->field52_0x1b4 = 0;
  this->field53_0x1b8 = 0;
  this->field54_0x1bc = 0;
  this->field55_0x1c0 = 0;
  this->field56_0x1c4 = 0;
  this->field57_0x1c8 = 0;
  peVar13 = local_1c;
  if ((int)local_1c < 0) {
    peVar13 = (entitySceneControlGameSelect *)0x0;
  }
  this->field49_0x1a8 = peVar13;
  *ppeVar1 = peVar13;
  FUN_0012f990(&FLOAT_00428c10,(int *)ppeVar1);
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_pauseicons_bonusbooks",&param_2);
  paVar11 = param_2;
  if (param_2 == (BonusChallengesMenu *)0x0) {
    runtime::ExitGame(2);
  }
  i = DAT_00506578 * 0x46c;
  this->field61_0x1d8 = (undefined *)paVar11;
  piVar3 = (int *)(i + 0x248 + (int)this->field4_0x10c);
  this->field62_0x1dc = (float)(ushort)paVar11->nextPlaycamWide[0] * 0.5;
  if (*piVar3 == 0x5f646961) {
    Assets::GetResourceBytes((char *)piVar3,&param_2);
    pBVar14 = param_2;
    if (param_2 == (BonusChallengesMenu *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    pBVar14 = (BonusChallengesMenu *)0x0;
  }
  this->field21_0x150 = (undefined *)pBVar14;
  *(int32_t *)&this->field_0x15c = -1;
  this->field22_0x154 = 320.0;
  this->field23_0x158 = 240.0;
  uVar4 = *(ushort *)(this->field21_0x150 + 8);
  uVar17 = (uint)g_DXContext.backBufferWidth;
  this->field29_0x164 =
       (float)g_DXContext.backBufferHeight / (float)*(ushort *)(this->field21_0x150 + 10);
  this->field28_0x160 = (float)uVar17 / (float)uVar4;
  this->field30_0x168 = 0;
  *(int32_t *)&this->field_0x174 = -1;
  this->field31_0x16c = 0x43a00000;
  this->field32_0x170 = 0x43700000;
  this->field37_0x178 = this->field28_0x160;
  this->field38_0x17c = this->field29_0x164;
  this->field39_0x180 = 0.0;
  this->field40_0x184 = 1.0;
  this->someTimer = 0.0;
  this->field42_0x18c = 0.0;
  this->field43_0x190 = 1.0;
  this->field44_0x194 = 1;
  this->field45_0x198 = Game::GameState.currentChapter;
  this->field46_0x19c = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_challenge_unplayed",&param_2);
  pBVar14 = param_2;
  if (param_2 == (BonusChallengesMenu *)0x0) {
    runtime::ExitGame(2);
  }
  this->field13_0x130 = (undefined *)pBVar14;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_challenge_bronzetrophy",&param_2);
  pBVar14 = param_2;
  if (param_2 == (BonusChallengesMenu *)0x0) {
    runtime::ExitGame(2);
  }
  this->field14_0x134 = (undefined *)pBVar14;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_challenge_silvertrophy",&param_2);
  pBVar14 = param_2;
  if (param_2 == (BonusChallengesMenu *)0x0) {
    runtime::ExitGame(2);
  }
  this->field15_0x138 = (undefined *)pBVar14;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_challenge_goldtrophy",&param_2);
  puVar12 = param_2;
  if (param_2 == (BonusChallengesMenu *)0x0) {
    runtime::ExitGame(2);
  }
  this->field16_0x13c = (undefined *)puVar12;
  Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_challenge_platinumtrophy",&param_2);
  puVar13 = param_2;
  if (param_2 == (BonusChallengesMenu *)0x0) {
    runtime::ExitGame(2);
  }
  i = DAT_00506578;
  this->field17_0x140 = (undefined *)puVar13;
  this->field18_0x144 = (float)*(ushort *)(this->field14_0x134 + 10) * 0.5;
  this->field47_0x1a0 = (Scene *)0x0;
  FUN_000d7640(i,this,0);
  BonusChallengesMenu::setState(this,1);
  Assets::DestroyAssetOrDecrement(local_24);
                    // Success if able to play pause music
  if (Audio::PauseMusicPlaying != 0) {
    return 1;
  }
  play_ctx = Audio::GetPlayingContext(g_pauseMusicXACTID);
  bVar15 = g_pauseMusicXACTID[0];
  if (play_ctx != (AudioPlayingContext *)0x0) {
    play_ctx->numReferences = play_ctx->numReferences + 1;
    Audio::PauseMusicPlaying = 1;
    return 1;
  }
  i = 0;
                    // From here down 
                    // Load the pause music
                    // ////////////////////////
  play_ctx = Audio::PlayingContexts;
  do {
    if (play_ctx->playFlags == 0) {
      play_ctx = Audio::PlayingContexts + i;
      uVar17 = 0x58;
      bad_id = g_pauseMusicXACTID[0] != 'X';
      play_ctx->playFlags = 1;
      Audio::PlayingContexts[i].field45_0x94 = 0;
      Audio::PlayingContexts[i].numReferences = 1;
      if (bad_id) goto LAB_000d61d9;
      bVar15 = 0x58;
      next_i = 0;
      goto LAB_000d61c4;
    }
    play_ctx = play_ctx + 1;
    i = i + 1;
  } while ((int)play_ctx < 0x4dffa0);
  play_ctx = (AudioPlayingContext *)0x0;
  goto LAB_000d6148;
  while( true ) {
    bVar15 = g_pauseMusicXACTID[next_i + 1];
    iVar6 = next_i + 1;
    uVar17 = (uint)(byte)"XACT_SILENCE"[iVar6];
    next_i = next_i + 1;
    if (bVar15 != "XACT_SILENCE"[iVar6]) break;
LAB_000d61c4:
    if (bVar15 == 0) {
      next_i = 0;
      goto LAB_000d61e1;
    }
  }
LAB_000d61d9:
  next_i = bVar15 - uVar17;
LAB_000d61e1:
  pcVar18 = g_pauseMusicXACTID;
  Audio::PlayingContexts[i].field44_0x90 = 0;
  Audio::PlayingContexts[i].field46_0x98 = 0;
                    // copy into play_ctx+0x4 (name)
  Audio::PlayingContexts[i].field43_0x8c = (uint)(next_i == 0);
  do {
    cVar9 = *pcVar18;
    pcVar18[(int)(&UNK_000b583c + i * 0x9c)] = cVar9;
    pcVar18 = pcVar18 + 1;
  } while (cVar9 != '\0');
LAB_000d6148:
  if (play_ctx->playFlags == 0x12) {
    i = play_ctx->field43_0x8c;
    play_ctx->field44_0x90 = 1;
  }
  else {
    i = FUN_00038530();
    if (i == 0) {
      play_ctx->field44_0x90 = 1;
      if (play_ctx->field43_0x8c == 0) {
        cVar9 = FUN_00038d10(&param_2);
        play_ctx->indexInSoundbank = cVar9;
        if (cVar9 != -1) {
          Audio::UpdateSoundbankByIndex(cVar9);
        }
      }
      FUN_00038300();
      Audio::PauseMusicPlaying = 1;
      return 1;
    }
    FUN_00038ad0();
    i = play_ctx->field43_0x8c;
    play_ctx->field44_0x90 = 1;
  }
  if (i == 0) {
    cVar9 = FUN_00038d10(&param_2);
    play_ctx->indexInSoundbank = cVar9;
    if (cVar9 != -1) {
      Audio::UpdateSoundbankByIndex(cVar9);
      Audio::PauseMusicPlaying = 1;
      return 1;
    }
  }
  Audio::PauseMusicPlaying = 1;
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void BonusChallengesMenu::update(BonusChallengesMenu *this)

{
  void *pvVar1;
  InputHandlerType3 *script3;
  int iVar2;
  undefined4 uVar3;
  float *extraout_ECX;
  int iVar4;
  float10 extraout_ST0;
  BonusChallengesMenu *pBVar5;
  uint64_t uVar6;
  float fVar7;
  undefined4 local_8;
  undefined4 local_4;
  BonusChallengesMenu *thiss;
  
  thiss = this;
  fVar7 = modf(Events::EventDelta,1.0);
  sin(fVar7 * 6.2831855);
  abs_float((float)extraout_ST0);
  if ((Game::DialogState == NotInDialog) && (this->field47_0x1a0 != (Scene *)0x0)) {
    switch(this->state) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
      script3 = (InputHandlerType3 *)0x0;
      break;
    case 2:
      script3 = Input::MenuInputHandler;
      break;
    default:
      goto switchD_000d646f_default;
    }
    Input::UpdateMenuInput(script3,this->field47_0x1a0);
  }
switchD_000d646f_default:
  switch(this->state) {
  case 1:
    if (this->field44_0x194 != 0) {
      Timer::reduce(&this->field43_0x190);
      pBVar5 = (BonusChallengesMenu *)((*extraout_ECX - 1.0) * -1.0);
      if ((float)pBVar5 <= 1.0) {
        this = (BonusChallengesMenu *)0x0;
        if (0.0 <= (float)pBVar5) {
          this = pBVar5;
        }
      }
      else {
        this = (BonusChallengesMenu *)1.0;
      }
      uVar6 = float10::to_uint64_t((float10)(float)this * (float10)255.0);
      local_8 = CONCAT13((char)uVar6,0xffffff);
      uVar6 = float10::to_uint64_t((float10)(float)this * (float10)128.0);
      local_4 = CONCAT13((char)uVar6,0x69764);
      iVar4 = 0;
      if (0 < thiss->numFuckers) {
        iVar2 = 0;
        do {
          *(undefined4 *)((int)thiss->field4_0x10c + iVar2 + 0x460) = local_8;
          *(undefined4 *)((int)thiss->field4_0x10c + iVar2 + 0x464) = local_4;
          iVar4 = iVar4 + 1;
          iVar2 = iVar2 + 0x46c;
        } while (iVar4 < thiss->numFuckers);
      }
      iVar4 = DAT_00506578 * 0x46c;
      *(undefined4 *)((int)thiss->field4_0x10c + iVar4 + 0x464) = 0xc43ef7b6;
      uVar6 = float10::to_uint64_t((float10)(float)this * (float10)196.0);
      *(char *)((int)thiss->field4_0x10c + iVar4 + 0x467) = (char)uVar6;
    }
    if ((thiss->field43_0x190 <= 0.001 && thiss->field43_0x190 != 0.001) &&
       (iVar4 = entitySceneControlGameSelect::isStatus2Or3(thiss->sceneControlGameSelect),
       iVar4 == 0)) {
      setState(thiss,2);
      return;
    }
    break;
  case 3:
    pvVar1 = this->field4_0x10c;
    iVar4 = DAT_00506578 * 0x46c;
    if (runtime::dx_timer <= 0.0) {
      fVar7 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar7 = 0.0;
    }
    if ((0.0 < this->field39_0x180) &&
       (fVar7 = this->field39_0x180 - fVar7, this->field39_0x180 = fVar7, fVar7 <= 0.0)) {
      this->field39_0x180 = 0.0;
    }
    fVar7 = *(float *)(this->field12_0x12c + 0x93c);
    if (fVar7 == 0.0) {
      fVar7 = 1.0;
    }
    else {
      fVar7 = (this->field39_0x180 - fVar7) / (0.0 - fVar7);
      if (fVar7 <= 1.0) {
        if (fVar7 < 0.0) {
          fVar7 = 0.0;
        }
      }
      else {
        fVar7 = 1.0;
      }
    }
    this->field40_0x184 = fVar7;
    if ((undefined *)this->field30_0x168 != this->field21_0x150) {
      uVar6 = float10::to_uint64_t((float10)fVar7 * (float10)255.0);
      this->field27_0x15f = (char)uVar6;
      this->field36_0x177 = -1 - (char)uVar6;
    }
    uVar3 = FUN_00101730(-763.8705,-6.05322e-40,fVar7);
    *(undefined4 *)((int)pvVar1 + iVar4 + 0x464) = uVar3;
    if (1.0 <= this->field40_0x184) {
      setState(this,2);
      return;
    }
    break;
  case 4:
    if (Game::DialogState == NotInDialog) {
      setState(this,2);
      return;
    }
    break;
  case 5:
    if (runtime::dx_timer <= 0.0) {
      fVar7 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar7 = 0.0;
    }
    if ((0.0 < this->someTimer) &&
       (fVar7 = this->someTimer - fVar7, this->someTimer = fVar7, fVar7 <= 0.0)) {
      this->someTimer = 0.0;
    }
    fVar7 = (this->someTimer - 0.75) * -1.3333334;
    if (fVar7 <= 1.0) {
      if (fVar7 < 0.0) {
        fVar7 = 0.0;
      }
    }
    else {
      fVar7 = 1.0;
    }
    this->field42_0x18c = fVar7;
    if (1.0 <= fVar7) {
      setState(this,6);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void BonusChallengesMenu::draw(BonusChallengesMenu *param_1)

{
  DXTextureInstance *pDVar1;
  undefined4 uVar2;
  BonusChallengesMenu *pBVar3;
  int iVar4;
  BonusChallengesMenu *pBVar5;
  uint64_t uVar6;
  undefined4 local_4;
  
  pBVar3 = param_1;
  if ((param_1->field21_0x150 != (undefined *)0x0) && (param_1->field27_0x15f != '\0')) {
    DrawMalloced100Value
              (param_1->field21_0x150,&param_1->field22_0x154,&param_1->field28_0x160,0,
               *(TextDrawData **)&param_1->field_0x15c,0);
  }
  if ((param_1->field30_0x168 != 0) && (param_1->field36_0x177 != '\0')) {
    DrawMalloced100Value
              (param_1->field30_0x168,&param_1->field31_0x16c,&param_1->field37_0x178,0,
               *(TextDrawData **)&param_1->field_0x174,0);
  }
  uVar2 = DAT_00428c20;
  pDVar1 = (DXTextureInstance *)param_1->field61_0x1d8;
  if (pDVar1 != (DXTextureInstance *)0x0) {
    local_4 = DAT_00428c20;
    if ((param_1->field44_0x194 != 0) &&
       (param_1->field40_0x184 <= 1.0 && param_1->field40_0x184 != 1.0)) {
      pBVar5 = (BonusChallengesMenu *)(param_1->field40_0x184 * 255.0);
      if ((float)pBVar5 <= 255.0) {
        param_1 = (BonusChallengesMenu *)0x0;
        if (0.0 <= (float)pBVar5) {
          param_1 = pBVar5;
        }
      }
      else {
        param_1 = (BonusChallengesMenu *)255.0;
      }
      uVar6 = float10::to_uint64_t((float10)(float)param_1);
      local_4 = CONCAT13((char)uVar6,(int3)uVar2);
    }
    Graphics::ReconfigureRenderer();
    Graphics::DrawTexture(0,0,pDVar1,(vec2 *)&DAT_00305cc8,0,0.0,local_4,(vec2 *)&DAT_00305cc0);
    Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
    if (Graphics::UseDefaultPixelC0 == 0) {
      DAT_00509b00 = 0;
    }
    FUN_0012f000(1);
  }
  iVar4 = 0;
  do {
    if (iVar4 != 2) {
      FUN_000d6a30();
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 5);
  FUN_000d6a30();
  if (((Game::DialogState == NotInDialog) && (pBVar3->field44_0x194 == 0)) &&
     (iVar4 = pBVar3->field12_0x12c, iVar4 != 0)) {
    if (*(float *)(iVar4 + 0x200) != 2.0) {
      *(float *)(iVar4 + 0x200) = 2.0;
      *(undefined4 *)(iVar4 + 0x2a8) = 0;
    }
    (**(code **)(*(int *)pBVar3->field12_0x12c + 0x14))
              ((int *)pBVar3->field12_0x12c,
               (int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,3);
  }
  if (pBVar3->field47_0x1a0 != (Scene *)0x0) {
    DrawXboxButtons_(1);
  }
  return;
}




void BonusChallengesMenu::setState(BonusChallengesMenu *param_1,int state)

{
  char cVar1;
  void *pvVar2;
  Scene *scene;
  int iVar3;
  GamePauseContext *pGVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  undefined4 uVar11;
  float fVar12;
  float local_120 [3];
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  float local_108;
  undefined4 local_104;
  char local_100 [256];
  
  iVar3 = param_1->state;
  if (iVar3 == 1) {
    if (param_1->field44_0x194 != 0) {
      param_1->field44_0x194 = 0;
      FUN_000d6ef0();
    }
    local_108 = g_DXContext.field32_0x58 + 16.0;
    local_104 = g_DXContext.field35_0x64 - 16.0;
    local_110 = 0;
    local_10c = 0xc2000000;
    local_120[0] = 20.0;
    uVar11 = 0xc1800000;
    local_120[1] = -16.0;
    createGameselectLoctext
              ((GameselectLoctext *)"challengeMenu_basic",1.0,0.75,"gameselect",
               "aid_loctext_ghoulies_gameselect_gameselecttext");
    local_114 = 0;
    local_120[2] = (float)uVar11;
    TransitionAndLoadScene
              (1,"challengeMenu_basic",&local_108,&local_110,local_120,local_120 + 2,0x3f800000,
               &DAT_3f400000,"gameselect","aid_loctext_ghoulies_gameselect_gameselecttext",0x400c0);
    iVar3 = param_1->field47_0x1a0->field3814_0x1020;
    iVar8 = DAT_00506578 * 0x46c;
    *(float *)(iVar3 + 0x14) = 3.0;
    *(float *)(iVar3 + 0x18) = 0.7;
    *(undefined4 *)(iVar3 + 0x1c) = 3;
    pvVar2 = param_1->field4_0x10c;
    local_120[2] = *(float *)((int)pvVar2 + iVar8 + 0x240);
    local_120[0] = *(float *)((int)pvVar2 + iVar8 + 0x23c);
    uVar5 = CreateLoctext(param_1->field19_0x148,(LPWSTR)((int)pvVar2 + iVar8 + 0x3c),local_120[0],
                          local_120[2],1.35,1.35,1.0,1,0,1);
    *(uint *)(DAT_00506578 * 0x46c + 0x244 + (int)param_1->field4_0x10c) = uVar5;
    CreateLoctext(param_1->field19_0x148,param_1->nextPlaycamWide,
                  (float)g_DXContext.backBufferWidth * 0.5,35.0,1.35,1.35,1.0,1,0,1);
    FUN_000d6f40();
    iVar8 = DAT_00506578;
  }
  else if (iVar3 == 3) {
    pvVar2 = param_1->field4_0x10c;
    iVar3 = DAT_00506578 * 0x46c;
    local_120[0] = *(float *)(iVar3 + 0x240 + (int)pvVar2);
    local_120[2] = *(float *)((int)pvVar2 + iVar3 + 0x23c);
    uVar5 = CreateLoctext(param_1->field19_0x148,(LPWSTR)((int)pvVar2 + iVar3 + 0x3c),local_120[2],
                          local_120[0],1.35,1.35,1.0,1,0,1);
    iVar8 = DAT_00506578;
    *(uint *)(DAT_00506578 * 0x46c + 0x244 + (int)param_1->field4_0x10c) = uVar5;
  }
  else {
    iVar8 = DAT_00506578;
    if (iVar3 == 5) {
      iVar3 = FUN_00116170();
      *(undefined4 *)(iVar3 + 0x94) = 3;
      *(undefined4 *)(iVar3 + 0x124) = 2;
      pGVar4 = GamePauseContext::ctor(0,1,(char *)0x0);
      *(GamePauseContext **)(iVar3 + 0x120) = pGVar4;
      iVar8 = DAT_00506578;
    }
  }
  param_1->state = state;
  switch(state) {
  case 3:
    iVar3 = 0;
    if (0 < param_1->numFuckers) {
      iVar8 = 0;
      do {
        *(undefined4 *)(iVar8 + 0x464 + (int)param_1->field4_0x10c) = 0x80069764;
        iVar3 = iVar3 + 1;
        iVar8 = iVar8 + 0x46c;
      } while (iVar3 < param_1->numFuckers);
    }
    param_1->field10_0x124 = 320.0;
    param_1->field11_0x128 = 140.0;
    if (param_1->field12_0x12c != 0) {
      FUN_0006da00(0x40000000);
    }
    FUN_000d6fe0();
    iVar3 = 0;
    do {
      FUN_0005f7e0(param_1->field19_0x148);
      iVar3 = iVar3 + 0x46c;
    } while (iVar3 < 0x5cdc);
    return;
  case 4:
    pcVar6 = PTR_s_challengeintros__00428c0c;
    do {
      cVar1 = *pcVar6;
      pcVar6[(int)(local_100 + -(int)PTR_s_challengeintros__00428c0c)] = cVar1;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    pcVar6 = (char *)(iVar8 * 0x46c + 0x348 + (int)param_1->field4_0x10c);
    pcVar7 = pcVar6;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    pcVar10 = (char *)((int)&local_104 + 3);
    do {
      pcVar9 = pcVar10 + 1;
      pcVar10 = pcVar10 + 1;
    } while (*pcVar9 != '\0');
    pcVar9 = pcVar6;
    for (uVar5 = (uint)((int)pcVar7 - (int)pcVar6) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar5 = (int)pcVar7 - (int)pcVar6 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar10 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      pcVar10 = pcVar10 + 1;
    }
    Events::BeginDialogSequence(0);
    return;
  case 5:
    param_1->someTimer = 0.75;
    param_1->field42_0x18c = 0.0;
    FUN_0005f970(param_1->field19_0x148);
    scene = param_1->field47_0x1a0;
    scene->field2160_0x950 = 0;
    FUN_00142c20(3,scene);
    fVar12 = -50.0;
    if (640.0 - param_1->field10_0x124 <= 320.0) {
      param_1->field10_0x124 = -50.0;
    }
    else {
      param_1->field10_0x124 = 690.0;
    }
    if (240.0 < 480.0 - param_1->field11_0x128) {
      fVar12 = 530.0;
    }
    param_1->field11_0x128 = fVar12;
    if (param_1->field12_0x12c != 0) {
      FUN_0006da00(0x40000000);
      return;
    }
    break;
  case 6:
                    // Set playcam script
    if ((param_1->field20_0x14c != 0) &&
       (*(int *)((int)param_1->field4_0x10c + iVar8 * 0x46c + 0x468) != 0)) {
      FUN_0004a3d0();
      FUN_0004a3b0();
      FUN_000d5860();
      if (DAT_00506578 == 0x14) {
        FUN_00049b60();
      }
      XAPILIB::lstrcpyW(g_someWString,param_1->nextPlaycamWide);
      entitySceneControlGameSelect::setPlaycamScript
                (param_1->sceneControlGameSelect,3,
                 DAT_00506578 * 0x46c + 0x2c8 + (int)param_1->field4_0x10c);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 SetSaveNameMenu::ctor(entitySceneControlGameSelect *control,MenuSceneResource *res)

{
  char cVar1;
  byte *pbVar2;
  Camera *pCVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  astruct_15 *paVar10;
  void *lp;
  CameraLLNode *pCVar11;
  Cutscene *cutscene;
  BOOL BVar12;
  int iVar13;
  undefined4 unaff_ESI;
  char *pcVar14;
  Camera *mv;
  undefined4 unaff_EDI;
  char *pcVar15;
  undefined4 *puVar16;
  vec2 local_1a4;
  Camera *local_19c;
  undefined1 local_198 [4];
  float local_194;
  float local_190;
  int local_18c;
  char local_188 [35];
  undefined4 local_165 [23];
  char local_108 [39];
  undefined4 local_e1 [22];
  char cutscene_name [42];
  undefined4 local_5e [22];
  
  paVar10 = SomeAS15;
  pcVar14 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  pcVar15 = cutscene_name;
  for (iVar13 = 10; iVar13 != 0; iVar13 = iVar13 + -1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar14;
    pcVar14 = pcVar14 + 4;
    pcVar15 = pcVar15 + 4;
  }
  *(undefined2 *)pcVar15 = *(undefined2 *)pcVar14;
  puVar16 = local_5e;
  for (iVar13 = 0x15; iVar13 != 0; iVar13 = iVar13 + -1) {
    *puVar16 = 0;
    puVar16 = puVar16 + 1;
  }
  *(undefined2 *)puVar16 = 0;
  res->gameselectControl = control;
  res->field973_0x48c = game::nextPlaycamScriptWide;
  res->field0_0x0 = 0;
  (res->field975_0x494).scene = (Scene *)0x0;
  pbVar2 = paVar10->flags;
  *pbVar2 = *pbVar2 | 2;
  pbVar2 = paVar10->flags;
  DAT_00506588 = res;
  *pbVar2 = *pbVar2 | 4;
  runtime::SaveTheGame_();
  FUN_000f3020();
  mv = &res->field970_0x424;
  local_19c = mv;
  Camera::ctor(mv,"features",(ProjectionSetBitField)0x8);
  (res->field970_0x424).aspectRatioType = 0;
  Camera::ComputeTangents
            ((res->field970_0x424).fov,&local_18c,&local_194,&local_190,
             &(res->field970_0x424).aspectRatio,&(res->field970_0x424).cotangentOffset,0,local_198,
             &local_1a4);
  pCVar11 = Camera::AvailableConfigs;
  pCVar3 = Camera::AvailableConfigs[0].head;
  while (pCVar3 != (Camera *)0x0) {
    pCVar11 = (CameraLLNode *)((Camera *)pCVar11)->next;
    pCVar3 = ((Camera *)pCVar11)->next;
  }
  pCVar3 = ((Camera *)pCVar11)->prev;
  ((Camera *)pCVar11)->prev = mv;
  mv->next = (Camera *)pCVar11;
  (res->field970_0x424).prev = pCVar3;
  if (pCVar3 != (Camera *)0x0) {
    pCVar3->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(res->field970_0x424).name);
  }
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
    pcVar14 = "aid_model_ghoulies_actor_dialogbat";
    pcVar15 = local_188;
    for (iVar13 = 8; iVar13 != 0; iVar13 = iVar13 + -1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar14;
      pcVar14 = pcVar14 + 4;
      pcVar15 = pcVar15 + 4;
    }
    *(undefined2 *)pcVar15 = *(undefined2 *)pcVar14;
    pcVar15[2] = pcVar14[2];
    puVar16 = local_165;
    for (iVar13 = 0x17; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar16 = 0;
      puVar16 = puVar16 + 1;
    }
    *(undefined1 *)puVar16 = 0;
    pcVar14 = "aid_model_ghoulies_actor_dialogbatgold";
    pcVar15 = local_108;
    for (iVar13 = 9; iVar13 != 0; iVar13 = iVar13 + -1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar14;
      pcVar14 = pcVar14 + 4;
      pcVar15 = pcVar15 + 4;
    }
    *(undefined2 *)pcVar15 = *(undefined2 *)pcVar14;
    pcVar15[2] = pcVar14[2];
    puVar16 = local_e1;
    for (iVar13 = 0x16; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar16 = 0;
      puVar16 = puVar16 + 1;
    }
    *(undefined1 *)puVar16 = 0;
    iVar13 = 0;
    do {
      cVar1 = local_188[iVar13];
      g_assetName[iVar13] = cVar1;
      iVar13 = iVar13 + 1;
    } while (cVar1 != '\0');
    iVar13 = 0;
    do {
      cVar1 = local_108[iVar13];
      *(char *)((int)g_someWString + iVar13 + 0x8c) = cVar1;
      iVar13 = iVar13 + 1;
      mv = local_19c;
    } while (cVar1 != '\0');
  }
  cutscene = Assets::LoadCutscene(cutscene_name,6,mv);
  res->csBuffer = cutscene;
  Cutscene::update(cutscene,g_cutsceneDelta,0.0,0);
  Camera::SetActiveCameraConfig(0,"features");
  res->field971_0x484 = Game::GameState.currentChapter;
  res->field972_0x488 = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x400c0,(LoctextValueContext **)&res->field968_0x41c);
  puVar16 = res->field968_0x41c;
  puVar16[5] = FLOAT_00428c58;
  puVar16[6] = FLOAT_00428c5c;
  puVar16[7] = 3;
  XAPILIB::lstrcpyW(res->wStr,res->field973_0x48c);
  lp = PTR_005462c4;
  res->field450_0x204 = FLOAT_00428c38;
  res->field451_0x208 = FLOAT_00428c3c;
  res->field452_0x20c = 0;
  BVar12 = XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar12 == 0) {
    createGameselectString("gameselect","features_featuresbanner",(LPWSTR)&res->field_0x210,lp);
  }
  fVar9 = DAT_00428c7c;
  fVar8 = DAT_00428c78;
  uVar7 = DAT_00428c74;
  fVar6 = DAT_00428c70;
  fVar5 = DAT_00428c6c;
  res->field965_0x410 = FLOAT_00428c30;
  uVar4 = DAT_00428c68;
  res->field966_0x414 = FLOAT_00428c34;
  res->field967_0x418 = 0;
  local_1a4.x = g_DXContext.field28_0x48 + _DAT_00428c60;
  local_1a4.y = g_DXContext.__0 + _DAT_00428c64;
  InitMalloced100(uVar4,fVar5,fVar6,0,fVar8,fVar9,3,uVar7,1,1,&local_1a4);
  if (Audio::PauseMusicPlaying == 0) {
    Audio::PlayOrChangeByName(1,g_pauseMusicXACTID);
    Audio::PauseMusicPlaying = 1;
  }
  FUN_000d8840(res,1);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void SetSaveNameMenu::func3(int param_1)

{
  destroyGlobalMalloced100();
  DAT_00506588 = 0;
  UnregisterScript__(*(int *)(param_1 + 0x41c));
  *(undefined4 *)(param_1 + 0x41c) = 0;
  if (*(Scene **)(param_1 + 0x494) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0x494));
    *(undefined4 *)(param_1 + 0x494) = 0;
  }
  g_cutsceneDelta =
       *(float *)(*(int *)(param_1 + 0x420) + 0x2c) / *(float *)(*(int *)(param_1 + 0x420) + 0x34);
  Cutscene::dtor(*(Cutscene **)(param_1 + 0x420));
  *(undefined4 *)(param_1 + 0x420) = 0;
  Camera::setActiveCamera(param_1 + 0x424);
  Game::GameState.currentChapter = *(int *)(param_1 + 0x484);
  Game::GameState.currentScene = *(int *)(param_1 + 0x488);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void SetSaveNameMenu::func4(int *param_1)

{
  Cutscene *cutscene;
  entityAvatarMiscButtonBat *peVar1;
  uint uVar2;
  Buffer<> *pBVar3;
  MenuBatState MVar4;
  Malloced100 *pMVar5;
  InputHandlerType3 *script3;
  int iVar6;
  undefined1 *puVar7;
  undefined4 unaff_EDI;
  float delta;
  
  if ((Game::DialogState == NotInDialog) &&
     (cutscene = (Cutscene *)param_1[0x108], cutscene != (Cutscene *)0x0)) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,(Cutscene *)param_1[0x108],(Camera *)(param_1 + 0x109));
  }
  if ((Scene *)param_1[0x125] != (Scene *)0x0) {
    switch(*param_1) {
    case 0:
    case 1:
    case 3:
    case 4:
      script3 = (InputHandlerType3 *)0x0;
LAB_000d7edd:
      Input::UpdateMenuInput(script3,(Scene *)param_1[0x125]);
      break;
    case 2:
      script3 = Input::MenuInputHandler;
      if (Game::DialogState == NotInDialog) goto LAB_000d7edd;
    }
  }
  if (*param_1 == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar6 = *(int *)(param_1[0x124] + 0x124), iVar6 < 2 || (3 < iVar6)) ||
        (*(int *)(param_1[0x124] + 0x120) == 0)))) {
      FUN_000d8840(param_1,2);
    }
  }
  else if (((*param_1 == 3) && (TransitionData.discReadEnum == 0)) &&
          ((iVar6 = *(int *)(param_1[0x124] + 0x124), iVar6 < 2 ||
           ((3 < iVar6 || (*(int *)(param_1[0x124] + 0x120) == 0)))))) {
    FUN_000d8840(param_1,4);
    FUN_00143790();
    return;
  }
  if ((g_paused_ != 0) &&
     (peVar1 = malloced100->buttonBat, peVar1 != (entityAvatarMiscButtonBat *)0x0)) {
    (*((peVar1->avatar).vtable)->update)(peVar1,unaff_EDI);
  }
  pMVar5 = malloced100;
  uVar2 = malloced100->field0_0x0;
  if (uVar2 != 1) {
    if (uVar2 != 3) {
      if ((uVar2 == 4) &&
         (pBVar3 = malloced100->loctextValueCtx->buffer, pBVar3->tail <= pBVar3->head)) {
        malloced100->field0_0x0 = 0;
      }
      goto LAB_001437fc;
    }
    MVar4 = malloced100->buttonBat->state;
    if ((MVar4 != Idle) && (MVar4 != Hopping)) goto LAB_001437fc;
  }
  iVar6 = FUN_00144030();
  if (iVar6 != 0) {
    pMVar5->field0_0x0 = 2;
  }
LAB_001437fc:
  if (pMVar5->field0_0x0 != 0) {
    puVar7 = (undefined1 *)&pMVar5->field21_0x5c;
    while (puVar7 = *(undefined1 **)(puVar7 + 4), (undefined4 *)puVar7 != (undefined4 *)0x0) {
      if (*(float **)(puVar7 + 0x238) != (float *)0x0) {
        FUN_00144880(*(float **)(puVar7 + 0x238));
      }
    }
  }
  if (pMVar5->value != (Malloced100Value *)0x0) {
    FUN_00144880((float *)pMVar5->value);
  }
  if (pMVar5->value2 == (Malloced100Value *)0x0) {
    return;
  }
  FUN_00144880((float *)pMVar5->value2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void SetSaveNameMenu::func5(int param_1)

{
  float fVar1;
  int iVar2;
  float *extraout_ECX;
  float *extraout_EDX;
  
  iVar2 = FUN_000489e0(param_1 + 0x424);
  if (iVar2 != 0) {
    Graphics::RecalculateWorldAndViews();
    FUN_0013c490((float *)(param_1 + 0x450),(float *)(param_1 + 0x44c),
                 &Graphics::CurrentCameraStruct->affineT);
    fVar1 = *extraout_ECX;
    Graphics::CurrentCameraStruct->near = *extraout_EDX;
    Graphics::CurrentCameraStruct->far = fVar1;
    Graphics::UpdatePerspectiveProj();
    Graphics::UpdateViewport2();
  }
  if (((Game::DialogState == NotInDialog) && ((g_globalFlagset & 0x40040) == 0)) &&
     (*(Cutscene **)(param_1 + 0x420) != (Cutscene *)0x0)) {
    FUN_0004dbd0(*(Cutscene **)(param_1 + 0x420));
  }
  if ((*(int *)(param_1 + 0x494) != 0) && (Game::DialogState == NotInDialog)) {
    DrawXboxButtons_(0);
  }
  FUN_00143840();
  return;
}




void MainMenu::alloc(void)

{
  malloc_(0xf34);
  return;
}




undefined4 MainMenu::func2(undefined4 param_1,undefined4 *param_2)

{
  float fVar1;
  ushort uVar2;
  LoctextValueContext *pLVar3;
  int iVar4;
  astruct_14 *paVar5;
  void *pvVar6;
  undefined4 *puVar7;
  char cVar8;
  int *piVar9;
  undefined4 uVar10;
  BOOL BVar11;
  undefined4 *puVar12;
  char *pcVar13;
  undefined4 *puVar14;
  AudioPlayingContext *pAVar15;
  byte bVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  char *pcVar20;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float *pfVar21;
  bool bVar22;
  
  puVar7 = param_2;
  uVar10 = DAT_005462c8;
  param_2[0x3ca] = param_1;
  paVar5 = PTR_00506c6c;
  param_2[0x3c8] = game::nextPlaycamScriptWide;
  *param_2 = 0;
  param_2[0x3c9] = 0;
  param_2[0x336] = -1;
  param_2[0x334] = 0;
  param_2[0x335] = 0;
  param_2[0x337] = 0;
  param_2[0x338] = 0;
  param_2[0x333] = 0;
  param_2[0x332] = 0;
  param_2[0x339] = 0;
  param_2[0x215] = 0;
  param_2[0x216] = 0;
  param_2[0x217] = uVar10;
  param_2[0x218] = 0xbadbadba;
  param_2[0x219] = 0;
  param_2[0x3cc] = 0;
  DAT_005462cc = param_2;
  if ((paVar5->field2_0x8[7] & 0x20) == 0) {
    iVar17 = 0;
    piVar9 = &DAT_004e1950;
    do {
      if (piVar9[-1] == 6) {
        iVar17 = iVar17 + 1;
      }
      if (*piVar9 == 6) {
        iVar17 = iVar17 + 1;
      }
      if (piVar9[1] == 6) {
        iVar17 = iVar17 + 1;
      }
      piVar9 = piVar9 + 3;
    } while ((int)piVar9 < 0x4e19a4);
    if (iVar17 < 0x14) {
      malloc_(0x70);
      uVar10 = FUN_00142e50();
      puVar7[0x3cc] = uVar10;
    }
  }
  if (puVar7[0x3cc] != 0) {
    FUN_000db1a0();
  }
  runtime::AllocateForLoctext_(0,1,(void *)0xc0,(LoctextValueContext **)(puVar7 + 0x29d));
  pLVar3 = (LoctextValueContext *)puVar7[0x29d];
  (pLVar3->somePos).x = 3.0;
  (pLVar3->somePos).y = 0.7;
  pLVar3->maybeState = 3;
  *(undefined2 *)(puVar7 + 0x21a) = 0x62;
  *(undefined2 *)((int)puVar7 + 0x86a) = 0x6c;
  *(undefined2 *)(puVar7 + 0x21b) = 0x61;
  *(undefined2 *)((int)puVar7 + 0x86e) = 0x6e;
  *(undefined2 *)(puVar7 + 0x21c) = 0x6b;
  *(undefined2 *)((int)puVar7 + 0x872) = 0;
  puVar7[0x29c] = 0;
  puVar7[0x29a] = g_DXContext.field28_0x48;
  fVar1 = g_DXContext.__0;
  puVar7[0x29b] = g_DXContext.__0;
  puVar7[0x29b] = fVar1 - 185.0;
  runtime::AllocateForLoctext_(0,1,(void *)0xc0,(LoctextValueContext **)(puVar7 + 0x321));
  iVar17 = 0;
  do {
    *(short *)((int)puVar7 + iVar17 * 2 + 0xa78) = (short)"Progress not set"[iVar17];
    iVar17 = iVar17 + 1;
  } while (iVar17 < 0x10);
  *(undefined2 *)(puVar7 + 0x2a6) = 0;
  puVar7[0x31e] = g_DXContext.field28_0x48;
  fVar1 = g_DXContext.__0;
  puVar7[799] = g_DXContext.__0;
  puVar7[799] = fVar1 + 90.0;
  puVar7[800] = 0;
  runtime::AllocateForLoctext_(0,1,(void *)0xc0,(LoctextValueContext **)(puVar7 + 0x214));
  runtime::AllocateForLoctext_(0,1,(void *)0x400c0,(LoctextValueContext **)(puVar7 + 0x3bd));
  pvVar6 = PTR_005462c4;
  BVar11 = XAPILIB::IsBadReadPtr(PTR_005462c4,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar11 == 0) {
    createGameselectString
              ("gameselect","gameslotcontents_completed",(LPWSTR)(puVar7 + 0x33a),pvVar6);
  }
  puVar7[0x3ba] = g_DXContext.field28_0x48;
  fVar1 = g_DXContext.__0;
  puVar7[0x3bb] = g_DXContext.__0;
  puVar7[0x3bb] = fVar1 + 58.0;
  pfVar21 = (float *)&DAT_003069a4;
  pcVar20 = s_aid_movie_ghoulies_gameselect_ho_00428d04;
  puVar14 = puVar7 + 2;
  do {
    *(undefined2 *)(puVar14 + -1) = 0x65;
    *(undefined2 *)((int)puVar14 + 2) = 0x6f;
    *(undefined2 *)((int)puVar14 + -2) = 0x72;
    *(undefined2 *)puVar14 = 0x72;
    *(undefined2 *)(puVar14 + 1) = 0x72;
    *(undefined2 *)((int)puVar14 + 6) = 0;
    puVar14[0x7f] = g_DXContext.field28_0x48;
    fVar1 = g_DXContext.__0;
    puVar14[0x80] = g_DXContext.__0;
    puVar14[0x80] = fVar1 + 38.0;
    puVar14[0x81] = 0;
    puVar14[0x84] = pfVar21[-4];
    puVar14[0x85] = pfVar21[-3];
    puVar14[0x87] = *pfVar21;
    puVar14[0x88] = pfVar21[1];
    puVar14[0x83] = 0;
    puVar12 = (undefined4 *)0x0;
    if ((*(int *)(pcVar20 + -0x80) == 0x5f646961) &&
       (Assets::GetResourceBytes(pcVar20 + -0x80,&param_2), puVar12 = param_2,
       param_2 == (undefined4 *)0x0)) {
      runtime::ExitGame(2);
      puVar12 = param_2;
    }
    puVar14[0x83] = puVar12;
    puVar14[0x86] = -1;
    uVar2 = *(ushort *)((int)puVar12 + 10);
    uVar19 = (uint)g_DXContext.backBufferHeight;
    fVar1 = pfVar21[1];
    puVar14[0x87] =
         ((float)g_DXContext.backBufferWidth * *pfVar21) / (float)*(ushort *)(puVar12 + 2);
    puVar14[0x88] = ((float)uVar19 * fVar1) / (float)uVar2;
    pcVar13 = pcVar20;
    do {
      cVar8 = *pcVar13;
      pcVar13[(int)puVar14 + (0x224 - (int)pcVar20)] = cVar8;
      pcVar13 = pcVar13 + 1;
    } while (cVar8 != '\0');
    puVar14[0xad] = 0x80069764;
    puVar14[0xae] = *pfVar21 * 640.0 + 12.0;
    puVar14[0xaf] = pfVar21[1] * 480.0 + 12.0;
    puVar14[0xac] = 0;
    uVar10 = LoadMovie((char *)(puVar14 + 0x89),0x14);
    puVar14[0xa9] = uVar10;
    puVar14[0xaa] = 0;
    puVar14[0xab] = 0;
    pcVar20 = pcVar20 + 0x104;
    pfVar21 = pfVar21 + 7;
    puVar14 = puVar14 + 0xb1;
  } while ((int)pcVar20 < 0x429010);
  uVar10 = 0;
  puVar7[0x3c3] = -1;
  puVar7[0x3c1] = 0;
  puVar7[0x3c2] = 0;
  puVar7[0x3c4] = 0;
  puVar7[0x3c5] = 0;
  puVar7[0x3c0] = 0;
  iVar17 = FUN_0004a470();
  if (iVar17 != 0) {
    Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_challenge_unplayed",&param_2);
    puVar14 = param_2;
    if (param_2 == (undefined4 *)0x0) {
      runtime::ExitGame(2);
    }
    uVar10 = 0;
    puVar7[0x3c0] = puVar14;
    puVar7[0x3c1] = puVar7[0x1e8];
    puVar7[0x3c2] = puVar7[0x1e9];
  }
  puVar7[0x322] = 0;
  if (*(int *)(s_aid_texture_ghoulies_gameselect__00428c84 + puVar7[0x217] * 0x104) == 0x5f646961) {
    Assets::GetResourceBytes
              (s_aid_texture_ghoulies_gameselect__00428c84 + puVar7[0x217] * 0x104,&param_2);
    puVar14 = param_2;
    if (param_2 == (undefined4 *)0x0) {
      runtime::ExitGame(2);
    }
    uVar10 = 0;
  }
  else {
    puVar14 = (undefined4 *)0x0;
  }
  puVar7[0x322] = puVar14;
  puVar7[0x325] = -1;
  puVar7[0x323] = g_DXContext.field28_0x48;
  puVar7[0x324] = g_DXContext.__0;
  uVar2 = *(ushort *)(puVar7[0x322] + 8);
  uVar19 = (uint)g_DXContext.backBufferWidth;
  puVar7[0x327] = (float)g_DXContext.backBufferHeight / (float)*(ushort *)(puVar7[0x322] + 10);
  puVar7[0x326] = (float)uVar19 / (float)uVar2;
  puVar7[0x329] = g_DXContext.field28_0x48;
  puVar7[0x32a] = g_DXContext.__0;
  puVar7[0x32c] = puVar7[0x326];
  puVar7[0x32d] = puVar7[0x327];
  puVar7[0x328] = 0;
  puVar7[0x32b] = -1;
  puVar7[0x32e] = uVar10;
  puVar7[0x32f] = uVar10;
  puVar7[0x330] = 2.0;
  puVar7[0x331] = 1;
  puVar7[0x3cb] = 0;
  puVar7[0x3c6] = Game::GameState.currentChapter;
  puVar7[0x3c7] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  FUN_000d9c20(puVar7);
  XAPILIB::lstrcpyW((LPWSTR)(puVar7 + 0x21a),(LPCWSTR)puVar7[0x3c8]);
  FUN_000da040(puVar7);
  if (Audio::PauseMusicPlaying != 0) goto LAB_000d92e4;
  pAVar15 = Audio::GetPlayingContext(g_pauseMusicXACTID);
  bVar16 = g_pauseMusicXACTID[0];
  if (pAVar15 == (AudioPlayingContext *)0x0) {
    iVar17 = 0;
    pAVar15 = Audio::PlayingContexts;
    do {
      if (pAVar15->playFlags == 0) {
        pAVar15 = Audio::PlayingContexts + iVar17;
        uVar19 = 0x58;
        bVar22 = g_pauseMusicXACTID[0] != 'X';
        pAVar15->playFlags = 1;
        Audio::PlayingContexts[iVar17].field45_0x94 = 0;
        Audio::PlayingContexts[iVar17].numReferences = 1;
        if (bVar22) goto LAB_000d922a;
        bVar16 = 0x58;
        iVar18 = 0;
        goto LAB_000d9215;
      }
      pAVar15 = pAVar15 + 1;
      iVar17 = iVar17 + 1;
    } while ((int)pAVar15 < 0x4dffa0);
    pAVar15 = (AudioPlayingContext *)0x0;
    goto LAB_000d91a6;
  }
  pAVar15->numReferences = pAVar15->numReferences + 1;
  goto LAB_000d92de;
  while( true ) {
    bVar16 = g_pauseMusicXACTID[iVar18 + 1];
    iVar4 = iVar18 + 1;
    uVar19 = (uint)(byte)"XACT_SILENCE"[iVar4];
    iVar18 = iVar18 + 1;
    if (bVar16 != "XACT_SILENCE"[iVar4]) break;
LAB_000d9215:
    if (bVar16 == 0) {
      iVar18 = 0;
      goto LAB_000d9232;
    }
  }
LAB_000d922a:
  iVar18 = bVar16 - uVar19;
LAB_000d9232:
  pcVar20 = g_pauseMusicXACTID;
  Audio::PlayingContexts[iVar17].field44_0x90 = 0;
  Audio::PlayingContexts[iVar17].field46_0x98 = 0;
  Audio::PlayingContexts[iVar17].field43_0x8c = (uint)(iVar18 == 0);
  do {
    cVar8 = *pcVar20;
    pcVar20[(int)(&UNK_000b583c + iVar17 * 0x9c)] = cVar8;
    pcVar20 = pcVar20 + 1;
  } while (cVar8 != '\0');
LAB_000d91a6:
  if (pAVar15->playFlags == 0x12) {
    iVar17 = pAVar15->field43_0x8c;
    pAVar15->field44_0x90 = 1;
  }
  else {
    iVar17 = FUN_00038530();
    if (iVar17 == 0) {
      pAVar15->field44_0x90 = 1;
      if (pAVar15->field43_0x8c == 0) {
        cVar8 = FUN_00038d10(&param_2);
        pAVar15->indexInSoundbank = cVar8;
        if (cVar8 != -1) {
          Audio::UpdateSoundbankByIndex(cVar8);
        }
      }
      FUN_00038300();
      goto LAB_000d92de;
    }
    FUN_00038ad0();
    iVar17 = pAVar15->field43_0x8c;
    pAVar15->field44_0x90 = 1;
  }
  if (iVar17 == 0) {
    cVar8 = FUN_00038d10(&param_2);
    pAVar15->indexInSoundbank = cVar8;
    if (cVar8 != -1) {
      Audio::UpdateSoundbankByIndex(cVar8);
    }
  }
LAB_000d92de:
  Audio::PauseMusicPlaying = 1;
LAB_000d92e4:
  FUN_000da580(1);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void MainMenu::func3(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  if (*(int *)(param_1 + 0xf30) != 0) {
    FUN_00142eb0();
  }
  UnregisterScript__(*(int *)(param_1 + 0xa74));
  *(undefined4 *)(param_1 + 0xa74) = 0;
  UnregisterScript__(*(int *)(param_1 + 0x850));
  *(undefined4 *)(param_1 + 0x850) = 0;
  UnregisterScript__(*(int *)(param_1 + 0xc84));
  *(undefined4 *)(param_1 + 0xc84) = 0;
  UnregisterScript__(*(int *)(param_1 + 0xef4));
  *(undefined4 *)(param_1 + 0xef4) = 0;
  FUN_000da1b0();
  if (*(void **)(param_1 + 0xf00) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xf00));
    *(undefined4 *)(param_1 + 0xf00) = 0;
  }
  iVar2 = DAT_005462cc;
  if (*(void **)(DAT_005462cc + 0xccc) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(DAT_005462cc + 0xccc));
    *(undefined4 *)(iVar2 + 0xccc) = 0;
  }
  if (*(avatar **)(param_1 + 0x864) != (avatar *)0x0) {
    avatar::destroy(*(avatar **)(param_1 + 0x864));
    *(undefined4 *)(param_1 + 0x864) = 0;
  }
  if (*(void **)(param_1 + 0xc88) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xc88));
    *(undefined4 *)(param_1 + 0xc88) = 0;
    *(undefined4 *)(param_1 + 0xc94) = 0xff0000ff;
  }
  if (*(void **)(param_1 + 0xca0) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xca0));
    *(undefined4 *)(param_1 + 0xca0) = 0;
    *(undefined4 *)(param_1 + 0xcac) = 0xff0000ff;
  }
  Game::GameState.currentChapter = *(int *)(param_1 + 0xf18);
  Game::GameState.currentScene = *(int *)(param_1 + 0xf1c);
  piVar3 = (int *)(param_1 + 0x2ac);
  iVar2 = 3;
  do {
    if (*piVar3 != 0) {
      if (0 < piVar3[3]) {
        piVar1 = (int *)(*piVar3 + 0x18);
        *piVar1 = *piVar1 + -1;
        piVar3[3] = piVar3[3] + -1;
      }
      FUN_001072b0();
      *piVar3 = 0;
    }
    piVar3 = piVar3 + 0xb1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (*(Scene **)(param_1 + 0xf2c) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0xf2c));
    *(undefined4 *)(param_1 + 0xf2c) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void MainMenu::update(MainMenu *menu)

{
  int iVar1;
  undefined4 uVar2;
  
  if (menu->scenePtr != (Scene *)0x0) {
    switch(menu->state) {
    case New_Name:
    case New_Name_(1):
    case BatInMotion:
    case New_Name_(7):
    case New_Name_(8):
      Input::UpdateMenuInput((InputHandlerType3 *)0x0,menu->scenePtr);
      break;
    case New_Name_(2):
    case HoveringMainGame:
    case HoveringBonusChallenges:
    case HoveringFeatures:
      if (Game::DialogState == NotInDialog) {
        if ((menu->field3843_0xf30 != (int *)0x0) &&
           (FUN_00142f00(menu->field3843_0xf30,Input::MenuInputHandler), *menu->field3843_0xf30 == 4
           )) {
          FUN_000db380();
          FUN_00142eb0();
        }
        Input::UpdateMenuInput(Input::MenuInputHandler,menu->scenePtr);
      }
    }
  }
  switch(menu->state) {
  case New_Name_(1):
    if (menu->field3247_0xcc4 != 0) {
      FUN_000da3b0();
    }
    iVar1 = entitySceneControlGameSelect::isStatus2Or3
                      (*(entitySceneControlGameSelect **)&menu->field_0xf28);
    if (iVar1 != 0) goto switchD_000d94d6_caseD_2;
    uVar2 = 6;
    break;
  default:
    goto switchD_000d94d6_caseD_2;
  case BatInMotion:
    FUN_000d9d10();
    goto switchD_000d94d6_caseD_2;
  case New_Name_(7):
    iVar1 = entitySceneControlGameSelect::isStatus2Or3
                      (*(entitySceneControlGameSelect **)&menu->field_0xf28);
    if (iVar1 != 0) goto switchD_000d94d6_caseD_2;
    uVar2 = 8;
  }
  FUN_000da580(uVar2);
switchD_000d94d6_caseD_2:
  FUN_000daf10();
  if (menu->field3816_0xf00 != 0) {
    menu->field3817_0xf04 = (float)menu->field1946_0x7a0;
    menu->field3818_0xf08 = menu->field1947_0x7a4;
    iVar1 = menu->field1945_0x79c;
    menu->field3817_0xf04 =
         (float)*(ushort *)(iVar1 + 8) * menu->field1949_0x7ac * 0.5 +
         menu->field1949_0x7ac * 6.25 * 5.0 + menu->field3817_0xf04;
    menu->field3820_0xf10 =
         ((float)*(ushort *)(iVar1 + 10) * menu->field1950_0x7b0 * 0.75) /
         (float)*(ushort *)(menu->field3816_0xf00 + 8);
    menu->field3821_0xf14 =
         ((float)*(ushort *)(iVar1 + 10) * menu->field1950_0x7b0 * 0.75) /
         (float)*(ushort *)(menu->field3816_0xf00 + 10);
    menu->field3819_0xf0c = menu->field1948_0x7a8;
  }
  return;
}




void MainMenu::draw(float *param_1)

{
  int *piVar1;
  undefined1 *puVar2;
  vec2 *otherPos;
  float fVar3;
  DXTextureInstance *pDVar4;
  undefined4 uVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  float fVar10;
  uint64_t uVar11;
  undefined4 local_1c;
  vec2 local_18;
  DXTextureInstance *local_10;
  undefined4 uStack_c;
  float afStack_8 [2];
  
  pfVar7 = param_1;
  fVar10 = *param_1;
  fVar3 = param_1[0x217];
  if ((((fVar10 == 2.8026e-45) || (fVar10 == 4.2039e-45)) || (fVar10 == 7.00649e-45)) ||
     (fVar10 == 5.60519e-45)) {
    if (param_1[(int)fVar3 * 0xb1 + 0xab] != 0.0) {
      if ((char)(undefined1)g_globalFlagset < '\0') {
        if (0 < (int)param_1[(int)fVar3 * 0xb1 + 0xae]) {
          FUN_000dace0();
        }
      }
      else if ((int)param_1[(int)fVar3 * 0xb1 + 0xae] < 1) {
        piVar1 = (int *)((int)param_1[(int)fVar3 * 0xb1 + 0xab] + 0x18);
        *piVar1 = *piVar1 + 1;
        param_1[(int)fVar3 * 0xb1 + 0xae] = (float)((int)param_1[(int)fVar3 * 0xb1 + 0xae] + 1);
      }
    }
  }
  if (*param_1 != 1.4013e-45) {
    pfVar8 = param_1 + (int)fVar3 * 0xb1;
    if (6 < (int)param_1[(int)fVar3 * 0xb1 + 0xac]) {
      if (pfVar8[0xab] != 0.0) {
        local_18.x = *(float *)((int)param_1[0x3ca] + 0x84);
        iVar9 = FUN_00107360();
        if ((pfVar8[0xad] == 0.0) && (iVar9 != 0)) {
          pfVar8[0xad] = 1.4013e-45;
        }
      }
      goto LAB_000d972a;
    }
  }
  local_18.x = param_1[(int)fVar3 * 0xb1 + 0x85];
  pfVar8 = param_1 + (int)fVar3 * 0xb1;
LAB_000d972a:
  param_1 = pfVar8;
  pfVar8 = param_1;
  if ((pfVar7[0x322] != 0.0) && (*(char *)((int)pfVar7 + 0xc97) != '\0')) {
    DrawMalloced100Value
              (pfVar7[0x322],pfVar7 + 0x323,pfVar7 + 0x326,0,(TextDrawData *)pfVar7[0x325],0);
  }
  if ((pfVar7[0x328] != 0.0) && (*(char *)((int)pfVar7 + 0xcaf) != '\0')) {
    DrawMalloced100Value
              (pfVar7[0x328],pfVar7 + 0x329,pfVar7 + 0x32c,0,(TextDrawData *)pfVar7[0x32b],0);
  }
  pDVar4 = *(DXTextureInstance **)(DAT_005462cc + 0xccc);
  if (pDVar4 != (DXTextureInstance *)0x0) {
    uVar5 = *(undefined4 *)(DAT_005462cc + 0xcd8);
    otherPos = (vec2 *)(DAT_005462cc + 0xcdc);
    local_10 = (DXTextureInstance *)(DAT_005462cc + 0xcd0);
    Graphics::ReconfigureRenderer();
    Graphics::DrawTexture(0,0,pDVar4,otherPos,0,0.0,uVar5,(vec2 *)local_10);
    Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
    if (Graphics::UseDefaultPixelC0 == 0) {
      DAT_00509b00 = 0;
    }
  }
  local_1c = 0.0;
  pfVar6 = pfVar7;
  do {
    if ((local_1c != pfVar7[0x217]) && (pfVar6[0x85] != 0.0)) {
      FUN_00061360((float)((int)pfVar6[0x86] - (int)pfVar6[0xb0] / 2),
                   (float)((int)pfVar6[0x87] - (int)pfVar6[0xb1] / 2),(float)(int)pfVar6[0xb0],
                   0x3dcccccd,pfVar6[0xaf]);
      local_10 = (DXTextureInstance *)pfVar6[0x85];
      fVar10 = pfVar6[0x88];
      Graphics::ReconfigureRenderer();
      Graphics::DrawTexture
                (0,0,local_10,(vec2 *)(pfVar6 + 0x89),0,0.0,fVar10,(vec2 *)(pfVar6 + 0x86));
      Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
      if (Graphics::UseDefaultPixelC0 == 0) {
        DAT_00509b00 = 0;
      }
    }
    local_1c = (float)((int)local_1c + 1);
    pfVar6 = pfVar6 + 0xb1;
  } while ((int)local_1c < 3);
  fVar10 = pfVar7[0x217];
  if (pfVar7[(int)fVar10 * 0xb1 + 0x85] != 0.0) {
    FUN_00061360((float)((int)pfVar7[(int)fVar10 * 0xb1 + 0x86] -
                        (int)pfVar7[(int)fVar10 * 0xb1 + 0xb0] / 2),
                 (float)((int)pfVar7[(int)fVar10 * 0xb1 + 0x87] -
                        (int)pfVar7[(int)fVar10 * 0xb1 + 0xb1] / 2),
                 (float)(int)pfVar7[(int)fVar10 * 0xb1 + 0xb0],0x3dcccccd,
                 pfVar7[(int)fVar10 * 0xb1 + 0xaf]);
    local_10 = (DXTextureInstance *)pfVar7[(int)fVar10 * 0xb1 + 0x85];
    fVar3 = pfVar7[(int)fVar10 * 0xb1 + 0x88];
    Graphics::ReconfigureRenderer();
    Graphics::DrawTexture
              (0,0,local_10,(vec2 *)(pfVar7 + (int)fVar10 * 0xb1 + 0x89),0,0.0,fVar3,
               (vec2 *)(pfVar7 + (int)fVar10 * 0xb1 + 0x86));
    Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
    if (Graphics::UseDefaultPixelC0 == 0) {
      DAT_00509b00 = 0;
    }
  }
  if ((param_1[0xab] != 0.0) && (*(int *)((int)param_1[0xab] + 8) != 0)) {
    if (param_1[0xad] != 0.0) {
      afStack_8[0] = 16.0;
      afStack_8[1] = 4.0;
      local_10 = (DXTextureInstance *)0x431f0000;
      uStack_c = 0x42ee0000;
      fVar10 = ((float)(int)param_1[0xac] - 7.0) * 0.05 * 255.0;
      if (fVar10 <= 255.0) {
        param_1 = (float *)0x0;
        if (0.0 <= fVar10) {
          param_1 = (float *)fVar10;
        }
      }
      else {
        param_1 = (float *)255.0;
      }
      uVar11 = float10::to_uint64_t((float10)(float)param_1);
      fVar10 = local_18.x;
      local_1c = (float)CONCAT13((char)uVar11,0xffffff);
      puVar2 = (undefined1 *)((int)local_18.x + 10);
      local_18.x = ((float)*(ushort *)((int)pfVar8[0x85] + 8) * pfVar8[0x89]) /
                   (float)*(ushort *)((int)local_18.x + 8);
      local_18.y = ((float)*(ushort *)((int)pfVar8[0x85] + 10) * pfVar8[0x8a]) /
                   (float)*(ushort *)puVar2;
      Graphics::ReconfigureRenderer();
      Graphics::DrawTexture
                (0,(int)afStack_8,(DXTextureInstance *)fVar10,&local_18,&local_10,0.0,local_1c,
                 (vec2 *)(pfVar8 + 0x86));
      Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
      if (Graphics::UseDefaultPixelC0 == 0) {
        DAT_00509b00 = 0;
      }
    }
    if ((*pfVar7 != 1.4013e-45) && ((int)pfVar8[0xac] < 100)) {
      pfVar8[0xac] = (float)((int)pfVar8[0xac] + 1);
    }
  }
  pDVar4 = (DXTextureInstance *)pfVar7[0x3c0];
  if (pDVar4 != (DXTextureInstance *)0x0) {
    fVar10 = pfVar7[0x3c3];
    Graphics::ReconfigureRenderer();
    Graphics::DrawTexture
              (-1,0,pDVar4,(vec2 *)(pfVar7 + 0x3c4),0,0.0,fVar10,(vec2 *)(pfVar7 + 0x3c1));
    Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
    if (Graphics::UseDefaultPixelC0 == 0) {
      DAT_00509b00 = 0;
    }
  }
  if (((Game::DialogState == NotInDialog) && (pfVar7[0x331] == 0.0)) &&
     (fVar10 = pfVar7[0x219], fVar10 != 0.0)) {
    if (*(float *)((int)fVar10 + 0x200) != 2.0) {
      *(float *)((int)fVar10 + 0x200) = 2.0;
      *(undefined4 *)((int)fVar10 + 0x2a8) = 0;
    }
    (**(code **)(*(int *)pfVar7[0x219] + 0x14))
              ((int *)pfVar7[0x219],
               (int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,3);
  }
  if ((pfVar7[0x3cb] != 0.0) && (Game::DialogState == NotInDialog)) {
    DrawXboxButtons_(0);
  }
  return;
}




void ReplayChapterMenu::alloc(void)

{
  malloc_(0x49c);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 ReplayChapterMenu::ctor(entitySceneControlGameSelect *gameSelect,ReplayChapterMenu *menu)

{
  char cVar1;
  byte *pbVar2;
  Camera *pCVar3;
  LoctextValueContext *pLVar4;
  float fVar5;
  float fVar6;
  uint32_t uVar7;
  astruct_15 *paVar8;
  void *lp;
  CameraLLNode *pCVar9;
  Cutscene *cutscene;
  BOOL BVar10;
  uint uVar11;
  int iVar12;
  undefined4 unaff_ESI;
  char *pcVar13;
  Camera *mv;
  undefined4 unaff_EDI;
  char *c_ptr;
  undefined4 *puVar14;
  vec2 local_224;
  Camera *local_21c;
  undefined1 local_218 [4];
  float local_214;
  int local_210;
  float local_20c;
  char local_208 [35];
  undefined4 local_1e5 [23];
  char dialogPage1AID [42];
  undefined4 auStack_15e [21];
  char local_108 [39];
  undefined4 local_e1 [22];
  char local_88 [132];
  
  paVar8 = SomeAS15;
  pcVar13 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  c_ptr = dialogPage1AID;
  for (iVar12 = 10; iVar12 != 0; iVar12 = iVar12 + -1) {
    *(undefined4 *)c_ptr = *(undefined4 *)pcVar13;
    pcVar13 = pcVar13 + 4;
    c_ptr = c_ptr + 4;
  }
  *(undefined2 *)c_ptr = *(undefined2 *)pcVar13;
  puVar14 = auStack_15e;
  for (iVar12 = 0x15; iVar12 != 0; iVar12 = iVar12 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined2 *)puVar14 = 0;
  menu->entitySceneControl = gameSelect;
  *(wchar_t **)&menu->field_0x48c = game::nextPlaycamScriptWide;
  menu->field0_0x0 = 0;
  menu->scene = (Scene *)0x0;
  pbVar2 = paVar8->flags;
  *pbVar2 = *pbVar2 | 2;
  pbVar2 = paVar8->flags;
  DAT_005065d0 = menu;
  *pbVar2 = *pbVar2 | 4;
  runtime::SaveTheGame_();
  FUN_000f3020();
  mv = &menu->cameraConfig;
  local_21c = mv;
  Camera::ctor(mv,"replaychapter",(ProjectionSetBitField)0x8);
  (menu->cameraConfig).aspectRatioType = 0;
  Camera::ComputeTangents
            ((menu->cameraConfig).fov,&local_210,&local_20c,&local_214,
             &(menu->cameraConfig).aspectRatio,&(menu->cameraConfig).cotangentOffset,0,local_218,
             &local_224);
  pCVar9 = Camera::AvailableConfigs;
  pCVar3 = Camera::AvailableConfigs[0].head;
  while (pCVar3 != (Camera *)0x0) {
    pCVar9 = (CameraLLNode *)((Camera *)pCVar9)->next;
    pCVar3 = ((Camera *)pCVar9)->next;
  }
  pCVar3 = ((Camera *)pCVar9)->prev;
  ((Camera *)pCVar9)->prev = mv;
  mv->next = (Camera *)pCVar9;
  (menu->cameraConfig).prev = pCVar3;
  if (pCVar3 != (Camera *)0x0) {
    pCVar3->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(menu->cameraConfig).name);
  }
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
    pcVar13 = "aid_model_ghoulies_actor_dialogbat";
    c_ptr = local_208;
    for (iVar12 = 8; iVar12 != 0; iVar12 = iVar12 + -1) {
      *(undefined4 *)c_ptr = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      c_ptr = c_ptr + 4;
    }
    *(undefined2 *)c_ptr = *(undefined2 *)pcVar13;
    c_ptr[2] = pcVar13[2];
    puVar14 = local_1e5;
    for (iVar12 = 0x17; iVar12 != 0; iVar12 = iVar12 + -1) {
      *puVar14 = 0;
      puVar14 = puVar14 + 1;
    }
    *(undefined1 *)puVar14 = 0;
    pcVar13 = "aid_model_ghoulies_actor_dialogbatgold";
    c_ptr = local_108;
    for (iVar12 = 9; iVar12 != 0; iVar12 = iVar12 + -1) {
      *(undefined4 *)c_ptr = *(undefined4 *)pcVar13;
      pcVar13 = pcVar13 + 4;
      c_ptr = c_ptr + 4;
    }
    *(undefined2 *)c_ptr = *(undefined2 *)pcVar13;
    c_ptr[2] = pcVar13[2];
    puVar14 = local_e1;
    for (iVar12 = 0x16; iVar12 != 0; iVar12 = iVar12 + -1) {
      *puVar14 = 0;
      puVar14 = puVar14 + 1;
    }
    *(undefined1 *)puVar14 = 0;
    iVar12 = 0;
    do {
      cVar1 = local_208[iVar12];
      g_assetName[iVar12] = cVar1;
      iVar12 = iVar12 + 1;
    } while (cVar1 != '\0');
    iVar12 = 0;
    do {
      cVar1 = local_108[iVar12];
      *(char *)((int)g_someWString + iVar12 + 0x8c) = cVar1;
      iVar12 = iVar12 + 1;
      mv = local_21c;
    } while (cVar1 != '\0');
  }
  cutscene = Assets::LoadCutscene(dialogPage1AID,6,mv);
  menu->cutscene = cutscene;
  Cutscene::update(cutscene,g_cutsceneDelta,0.0,0);
  Camera::SetActiveCameraConfig(0,"replaychapter");
  menu->currentChapter = Game::GameState.currentChapter;
  menu->currentScene = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x80,&menu->loctextValueCtx);
  pLVar4 = menu->loctextValueCtx;
  (pLVar4->somePos).x = vec2_004299e8.x;
  (pLVar4->somePos).y = vec2_004299e8.y;
  pLVar4->maybeState = 3;
  XAPILIB::lstrcpyW((LPWSTR)&menu->field1_0x4,*(LPCWSTR *)&menu->field_0x48c);
  lp = PTR_005462c4;
  (menu->some_v2_1).x = FLOAT_004299c8;
  (menu->some_v2_1).y = FLOAT_004299cc;
  *(undefined4 *)&menu->field_0x20c = 0;
  BVar10 = XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar10 == 0) {
    createGameselectString
              ("gameselect","replaychapter_replaychapterbanner",(LPWSTR)&menu->field_0x210,lp);
  }
  (menu->some_v2_2).x = game::replay_chapter_vec2.x;
  (menu->some_v2_2).y = game::replay_chapter_vec2.y;
  *(undefined4 *)&menu->field_0x418 = 0;
  runtime::GetLatestLoadableScript(local_88,*(LPCWSTR *)&menu->field_0x48c);
  uVar11 = Assets::GetChapterIndexFromAID(local_88);
  uVar7 = uint32_t_00429a04;
  fVar6 = vec2_004299fc.y;
  fVar5 = vec2_004299fc.x;
  menu->trueChapterId = Game::ChapterIndexToTrueIndex[uVar11];
  local_224.x = g_DXContext.field28_0x48 + _DAT_004299f0;
  local_224.y = g_DXContext.__0 + _DAT_004299f4;
  InitMalloced100(uint32_t_004299f8,fVar5,fVar6,0,2.0,0.5,3,uVar7,1,1,&local_224);
  if (Audio::PauseMusicPlaying == 0) {
    Audio::PlayOrChangeByName(1,g_pauseMusicXACTID);
    Audio::PauseMusicPlaying = 1;
  }
  load_text(menu,1);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void ReplayChapterMenu::dtor(ReplayChapterMenu *param_1)

{
  destroyGlobalMalloced100();
  DAT_005065d0 = 0;
  UnregisterScript__((int)param_1->loctextValueCtx);
  param_1->loctextValueCtx = (LoctextValueContext *)0x0;
  if (param_1->scene != (Scene *)0x0) {
    Scene::free(param_1->scene);
    param_1->scene = (Scene *)0x0;
  }
  g_cutsceneDelta = param_1->cutscene->t / param_1->cutscene->length;
  Cutscene::dtor(param_1->cutscene);
  param_1->cutscene = (Cutscene *)0x0;
  Camera::setActiveCamera(&param_1->cameraConfig);
  Game::GameState.currentChapter = param_1->currentChapter;
  Game::GameState.currentScene = param_1->currentScene;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void ReplayChapterMenu::update(ReplayChapterMenu *param_1)

{
  Cutscene *cutscene;
  int iVar1;
  InputHandlerType3 *script3;
  float delta;
  
  cutscene = param_1->cutscene;
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,param_1->cutscene,&param_1->cameraConfig);
  }
  if (param_1->scene != (Scene *)0x0) {
    switch(param_1->field0_0x0) {
    case 0:
    case 1:
    case 3:
    case 4:
      script3 = (InputHandlerType3 *)0x0;
      break;
    case 2:
      script3 = Input::MenuInputHandler;
      break;
    default:
      goto switchD_000e22aa_default;
    }
    Input::UpdateMenuInput(script3,param_1->scene);
  }
switchD_000e22aa_default:
  if (param_1->field0_0x0 == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar1 = param_1->entitySceneControl->status, iVar1 < 2 || (3 < iVar1)) ||
        (param_1->entitySceneControl->gamePauseCtx == (GamePauseContext *)0x0)))) {
      load_text(param_1,2);
    }
  }
  else if (((param_1->field0_0x0 == 3) && (TransitionData.discReadEnum == 0)) &&
          ((iVar1 = param_1->entitySceneControl->status, iVar1 < 2 ||
           ((3 < iVar1 || (param_1->entitySceneControl->gamePauseCtx == (GamePauseContext *)0x0)))))
          ) {
    load_text(param_1,4);
    FUN_00143790();
    return;
  }
  FUN_00143790();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


Malloced100 * ReplayChapterMenu::loadChapterNames(void)

{
  undefined2 *puVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  TextInstance *text;
  Malloced100 *extraout_EDX;
  Malloced100 *pMVar5;
  HeapTableEntry *pHVar6;
  int num_chapters;
  float in_XMM0_Da;
  char chapter_num2 [256];
  char chapter_num [256];
  wchar_t local_200 [255];
  
  uVar2 = Save::getHighestCompletedChapter(*(undefined4 *)(DAT_005065d0 + 0x48c));
  pMVar5 = extraout_EDX;
  if (uVar2 == 0) {
    num_chapters = *(int *)(DAT_005065d0 + 0x490) + -1;
  }
  else {
    num_chapters = 5;
  }
  for (; 0 < num_chapters; num_chapters = num_chapters + -1) {
    if (g_HeapTableBase[runtime::CurrentHeapToAllocateFrom].heapHandle == (HANDLE)0x0) {
      pHVar6 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar6 = g_HeapTableBase + runtime::CurrentHeapToAllocateFrom;
    }
    piVar3 = (int *)runtime::AllocateOnHeap(pHVar6->heapHandle,0,8);
    if (piVar3 != (int *)0x0) {
      iVar4 = FUN_0014ded0(pHVar6->heapHandle,0,piVar3);
      puVar1 = (undefined2 *)(iVar4 + -4 + (int)piVar3);
      *puVar1 = 0x1234;
      *(undefined1 *)(puVar1 + 1) = *(undefined1 *)&pHVar6->field32_0x20;
    }
    _sprintf(chapter_num,"%d",num_chapters);
    u__00507e78[0] = L'\0';
    loctext::get_text("aid_loctext_ghoulies_chapterheadings","chapternumber",chapter_num,u__00507e78
                     );
    XAPILIB::lstrcpyW(local_200,u__00507e78);
    _sprintf(chapter_num2,"%d",num_chapters);
    u__00507e78[0] = L'\0';
    loctext::get_text("aid_loctext_ghoulies_chapterheadings","chaptername",chapter_num2,u__00507e78)
    ;
    XAPILIB::wsprintfW(local_200,L"%s : %s",local_200,u__00507e78);
    *piVar3 = num_chapters;
    text = (TextInstance *)TextInstance::ctor(local_200,0,0,0,0,FUN_000e23b0,piVar3);
    pMVar5 = (Malloced100 *)FUN_001439c0(text,in_XMM0_Da);
  }
  return pMVar5;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void ReplayChapterMenu::load_text(ReplayChapterMenu *menu,int param_2)

{
  Scene **ctx;
  Scene *pSVar1;
  float scaleX;
  void *pvVar2;
  uint uVar3;
  BOOL BVar4;
  int iVar5;
  undefined4 unaff_ESI;
  char *pcVar6;
  undefined4 unaff_EDI;
  char *pcVar7;
  float fVar8;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  char local_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  char aid [128];
  
  pcVar6 = "aid_loctext_ghoulies_gameselect_gameselecttext";
  pcVar7 = aid;
  for (iVar5 = 0xb; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  *(undefined2 *)pcVar7 = *(undefined2 *)pcVar6;
  pcVar7[2] = pcVar6[2];
  pcVar6 = aid + 0x2f;
  for (iVar5 = 0x14; iVar5 != 0; iVar5 = iVar5 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  *pcVar6 = '\0';
  if (menu->field0_0x0 == 1) {
    _local_90 = (Scene *)(g_DXContext.field32_0x58 + FLOAT_004299d0);
    fStack_8c = g_DXContext.field35_0x64 - FLOAT_004299d4;
    local_98 = FLOAT_004299e0 * 0.0;
    fVar8 = FLOAT_004299d8 * 0.5 * FLOAT_004299e0;
    local_a0 = fVar8 + FLOAT_004299dc;
    local_94 = 0.0 - FLOAT_004299e0 * FLOAT_004299d8;
    local_9c = 0.0 - fVar8;
    fStack_84 = 0.0;
    createGameselectLoctext(&eventEntries,FLOAT_004299e0,FLOAT_004299e4,"gameselect",aid);
    fStack_88 = fVar8;
    uVar3 = CreateLoctext(menu->loctextValueCtx,(LPWSTR)&menu->field1_0x4,(menu->some_v2_1).x,
                          (menu->some_v2_1).y,FLOAT_004299b8,FLOAT_004299b8,1.0,1,0,1);
    scaleX = FLOAT_004299bc;
    fVar8 = (menu->some_v2_2).y;
    *(uint *)&menu->field_0x20c = uVar3;
    uVar3 = CreateLoctext(menu->loctextValueCtx,(LPWSTR)&menu->field_0x210,(menu->some_v2_2).x,fVar8
                          ,scaleX,scaleX,1.0,1,0,1);
    *(uint *)&menu->field_0x20c = uVar3;
    pvVar2 = PTR_005462c4;
    BVar4 = XAPILIB::IsBadReadPtr(PTR_005462c4,CONCAT44(unaff_ESI,unaff_EDI));
    if (BVar4 != 0) {
      return;
    }
    ctx = &menu->scene;
    LoadScene_(1,(char *)&eventEntries,(SceneLoadContext *)&local_90,&local_98,&local_a0,&fStack_88,
               FLOAT_004299e0,FLOAT_004299e4,"gameselect",pvVar2,0x400c0,(SceneLoadContext *)ctx);
    pSVar1 = *ctx;
    pSVar1->originalTimerValue = 0.2;
    if (0.2 < pSVar1->someTimer) {
      pSVar1->someTimer = 0.2;
    }
    *(undefined4 *)(pSVar1->field3814_0x1020 + 0x20) = 0x3e4ccccd;
    iVar5 = (*ctx)->field3814_0x1020;
    *(float *)(iVar5 + 0x14) = vec2_004299e8.x;
    *(float *)(iVar5 + 0x18) = vec2_004299e8.y;
    *(undefined4 *)(iVar5 + 0x1c) = 3;
    loadChapterNames();
    FUN_00143b10();
  }
  else if (menu->field0_0x0 == 2) {
    FUN_00143b80();
  }
  menu->field0_0x0 = param_2;
  if (param_2 == 3) {
    FUN_0005f970(menu->loctextValueCtx);
    pSVar1 = menu->scene;
    if (pSVar1 != (Scene *)0x0) {
      pSVar1->field2160_0x950 = 0;
      FUN_00142c20(3,pSVar1);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 ReplaySceneMenu::ctor(entitySceneControlGameSelect *control,ReplaySceneMenu *menu)

{
  char cVar1;
  byte *pbVar2;
  Camera *pCVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  astruct_15 *paVar7;
  void *lp;
  CameraLLNode *pCVar8;
  Cutscene *csb;
  BOOL BVar9;
  uint chapter_index;
  int i;
  undefined4 unaff_ESI;
  char *pcVar10;
  Camera *mv;
  undefined4 unaff_EDI;
  char *pcVar11;
  undefined4 *puVar12;
  vec2 local_224;
  Camera *local_21c;
  undefined1 local_218 [4];
  float local_214;
  int local_210;
  float local_20c;
  char local_208 [35];
  undefined4 local_1e5 [23];
  asset_name cutscene_aid;
  char local_108 [39];
  undefined4 local_e1 [22];
  char latest_script [132];
  LoctextValueContext *locval_ctx;
  float someFloat2;
  
  paVar7 = SomeAS15;
  pcVar10 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  pcVar11 = cutscene_aid;
  for (i = 10; i != 0; i = i + -1) {
    *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar11 = pcVar11 + 4;
  }
  *(undefined2 *)pcVar11 = *(undefined2 *)pcVar10;
  pcVar10 = cutscene_aid + 0x2a;
  for (i = 0x15; i != 0; i = i + -1) {
    pcVar10[0] = '\0';
    pcVar10[1] = '\0';
    pcVar10[2] = '\0';
    pcVar10[3] = '\0';
    pcVar10 = pcVar10 + 4;
  }
  pcVar10[0] = '\0';
  pcVar10[1] = '\0';
  menu->gameselectControl = control;
  menu->someWideString = game::nextPlaycamScriptWide;
  menu->menuState = MenuState0;
  (menu->sceneLoadContext).scene = (Scene *)0x0;
  pbVar2 = paVar7->flags;
  *pbVar2 = *pbVar2 | 2;
  pbVar2 = paVar7->flags;
  ReplaySceneMenu = menu;
  *pbVar2 = *pbVar2 | 4;
  runtime::SaveTheGame_();
  FUN_000f3020();
  mv = &menu->field520_0x424;
  local_21c = mv;
  Camera::ctor(mv,"replayscene",(ProjectionSetBitField)0x8);
  (menu->field520_0x424).aspectRatioType = 0;
  Camera::ComputeTangents
            ((menu->field520_0x424).fov,&local_210,&local_20c,&local_214,
             &(menu->field520_0x424).aspectRatio,&(menu->field520_0x424).cotangentOffset,0,local_218
             ,&local_224);
  pCVar8 = Camera::AvailableConfigs;
  pCVar3 = Camera::AvailableConfigs[0].head;
  while (pCVar3 != (Camera *)0x0) {
    pCVar8 = (CameraLLNode *)((Camera *)pCVar8)->next;
    pCVar3 = ((Camera *)pCVar8)->next;
  }
  pCVar3 = ((Camera *)pCVar8)->prev;
  ((Camera *)pCVar8)->prev = mv;
  mv->next = (Camera *)pCVar8;
  (menu->field520_0x424).prev = pCVar3;
  if (pCVar3 != (Camera *)0x0) {
    pCVar3->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(menu->field520_0x424).name);
  }
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
    pcVar10 = "aid_model_ghoulies_actor_dialogbat";
    pcVar11 = local_208;
    for (i = 8; i != 0; i = i + -1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    *(undefined2 *)pcVar11 = *(undefined2 *)pcVar10;
    pcVar11[2] = pcVar10[2];
    puVar12 = local_1e5;
    for (i = 0x17; i != 0; i = i + -1) {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
    }
    *(undefined1 *)puVar12 = 0;
    pcVar10 = "aid_model_ghoulies_actor_dialogbatgold";
    pcVar11 = local_108;
    for (i = 9; i != 0; i = i + -1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    *(undefined2 *)pcVar11 = *(undefined2 *)pcVar10;
    pcVar11[2] = pcVar10[2];
    puVar12 = local_e1;
    for (i = 0x16; i != 0; i = i + -1) {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
    }
    *(undefined1 *)puVar12 = 0;
    i = 0;
    do {
      cVar1 = local_208[i];
      g_assetName[i] = cVar1;
      i = i + 1;
    } while (cVar1 != '\0');
    i = 0;
    do {
      cVar1 = local_108[i];
      *(char *)((int)g_someWString + i + 0x8c) = cVar1;
      i = i + 1;
      mv = local_21c;
    } while (cVar1 != '\0');
  }
  csb = Assets::LoadCutscene(cutscene_aid,6,mv);
  menu->cutsceneBuffer = csb;
  Cutscene::update(csb,g_cutsceneDelta,0.0,0);
  Camera::SetActiveCameraConfig(0,"replayscene");
  menu->currentChapter = Game::GameState.currentChapter;
  menu->currentScene = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x80,&menu->loctextValueCtx);
  locval_ctx = menu->loctextValueCtx;
  (locval_ctx->somePos).x = Params.somePos.x;
  (locval_ctx->somePos).y = Params.somePos.y;
  locval_ctx->maybeState = 3;
  XAPILIB::lstrcpyW((LPWSTR)&menu->field_0x4,menu->someWideString);
  lp = PTR_005462c4;
  (menu->someVec_1).x = Params.someVec2_2.x;
  (menu->someVec_1).y = Params.someVec2_2.y;
  menu->loctextIndex = 0;
  BVar9 = XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar9 == 0) {
    createGameselectString("gameselect","replayscene_replayscenebanner",menu->someWString,lp);
  }
  (menu->someVec2_2).x = Params.someVec2_1.x;
  (menu->someVec2_2).y = Params.someVec2_1.y;
  menu->field517_0x418 = 0;
  runtime::GetLatestLoadableScript(latest_script,menu->someWideString);
  chapter_index = Assets::GetChapterIndexFromAID(latest_script);
  someFloat2 = Params.wobbleSpeed;
  uVar6 = Params.field15_0x4c;
  fVar5 = Params.rowScale;
  fVar4 = Params.rowSpacing;
  menu->trueChapterIndex = Game::ChapterIndexToTrueIndex[chapter_index];
  local_224.x = g_DXContext.field28_0x48 + Params.someVec2_3.x;
  local_224.y = g_DXContext.__0 + Params.someVec2_3.y;
                    // Init stuff and make bat
  InitMalloced100(Params.rowsPerPage,fVar4,fVar5,0,Params.wobbleHeight,someFloat2,3,uVar6,1,1,
                  &local_224);
  if (Audio::PauseMusicPlaying == 0) {
    Audio::PlayOrChangeByName(1,g_pauseMusicXACTID);
    Audio::PauseMusicPlaying = 1;
  }
  setState(menu,1);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void ReplaySceneMenu::func3(ReplaySceneMenu *menu)

{
  Scene *scene;
  
  destroyGlobalMalloced100();
  ReplaySceneMenu = 0;
  UnregisterScript__((int)menu->loctextValueCtx);
  scene = (menu->sceneLoadContext).scene;
  menu->loctextValueCtx = (LoctextValueContext *)0x0;
  if (scene != (Scene *)0x0) {
    Scene::free(scene);
    (menu->sceneLoadContext).scene = (Scene *)0x0;
  }
  g_cutsceneDelta = menu->cutsceneBuffer->t / menu->cutsceneBuffer->length;
  Cutscene::dtor(menu->cutsceneBuffer);
  menu->cutsceneBuffer = (Cutscene *)0x0;
  Camera::setActiveCamera(&menu->field520_0x424);
  Game::GameState.currentChapter = menu->currentChapter;
  Game::GameState.currentScene = menu->currentScene;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void ReplaySceneMenu::update(ReplaySceneMenu *menu)

{
  Cutscene *cutscene;
  Scene *scene;
  entityAvatarMiscButtonBat *peVar1;
  uint uVar2;
  Buffer<> *pBVar3;
  MenuBatState MVar4;
  Malloced100 *pMVar5;
  InputHandlerType3 *handler;
  int iVar6;
  undefined1 *puVar7;
  undefined4 unaff_EDI;
  float delta;
  
  cutscene = menu->cutsceneBuffer;
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,menu->cutsceneBuffer,&menu->field520_0x424);
  }
  scene = (menu->sceneLoadContext).scene;
  if (scene != (Scene *)0x0) {
    switch(menu->menuState) {
    case MenuState0:
    case MenuState1:
    case MenuState3:
    case MenuState4:
      handler = (InputHandlerType3 *)0x0;
      break;
    case AwaitingInput:
      handler = Input::MenuInputHandler;
      break;
    default:
      goto switchD_000e302a_default;
    }
                    // Read menu input
    Input::UpdateMenuInput(handler,scene);
  }
switchD_000e302a_default:
  if (menu->menuState == MenuState1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar6 = menu->gameselectControl->status, iVar6 < 2 || (3 < iVar6)) ||
        (menu->gameselectControl->gamePauseCtx == (GamePauseContext *)0x0)))) {
                    // Breaks initialisation of replay scene menu
      setState(menu,2);
    }
  }
  else if (((menu->menuState == MenuState3) && (TransitionData.discReadEnum == 0)) &&
          ((iVar6 = menu->gameselectControl->status, iVar6 < 2 ||
           ((3 < iVar6 || (menu->gameselectControl->gamePauseCtx == (GamePauseContext *)0x0)))))) {
    setState(menu,4);
    FUN_00143790();
    return;
  }
  if ((g_paused_ != 0) &&
     (peVar1 = malloced100->buttonBat, peVar1 != (entityAvatarMiscButtonBat *)0x0)) {
    (*((peVar1->avatar).vtable)->update)(peVar1,unaff_EDI);
  }
  pMVar5 = malloced100;
  uVar2 = malloced100->field0_0x0;
  if (uVar2 != 1) {
    if (uVar2 != 3) {
      if ((uVar2 == 4) &&
         (pBVar3 = malloced100->loctextValueCtx->buffer, pBVar3->tail <= pBVar3->head)) {
        malloced100->field0_0x0 = 0;
      }
      goto LAB_001437fc;
    }
    MVar4 = malloced100->buttonBat->state;
    if ((MVar4 != Idle) && (MVar4 != Hopping)) goto LAB_001437fc;
  }
  iVar6 = FUN_00144030();
  if (iVar6 != 0) {
    pMVar5->field0_0x0 = 2;
  }
LAB_001437fc:
  if (pMVar5->field0_0x0 != 0) {
    puVar7 = (undefined1 *)&pMVar5->field21_0x5c;
    while (puVar7 = *(undefined1 **)(puVar7 + 4), (undefined4 *)puVar7 != (undefined4 *)0x0) {
      if (*(float **)(puVar7 + 0x238) != (float *)0x0) {
        FUN_00144880(*(float **)(puVar7 + 0x238));
      }
    }
  }
  if (pMVar5->value != (Malloced100Value *)0x0) {
    FUN_00144880((float *)pMVar5->value);
  }
  if (pMVar5->value2 == (Malloced100Value *)0x0) {
    return;
  }
  FUN_00144880((float *)pMVar5->value2);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void ReplaySceneMenu::setState(ReplaySceneMenu *menu,MenuState newState)

{
  Scene *pSVar1;
  float scaleX;
  void *pvVar2;
  uint index;
  BOOL BVar3;
  int iVar4;
  undefined4 unaff_ESI;
  char *pcVar5;
  undefined4 unaff_EDI;
  char *pcVar6;
  float fVar7;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  void *local_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  char loctext_aid [128];
  SceneLoadContext *loadCtx;
  
  pcVar5 = "aid_loctext_ghoulies_gameselect_gameselecttext";
  pcVar6 = loctext_aid;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
  pcVar6[2] = pcVar5[2];
  pcVar5 = loctext_aid + 0x2f;
  for (iVar4 = 0x14; iVar4 != 0; iVar4 = iVar4 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
  }
  *pcVar5 = '\0';
  if (menu->menuState == MenuState1) {
    local_90 = (void *)(g_DXContext.field32_0x58 + Params.field4_0x18);
    fStack_8c = g_DXContext.field35_0x64 - Params.field5_0x1c;
    local_98 = Params.field8_0x28 * 0.0;
    fVar7 = Params.field6_0x20 * 0.5 * Params.field8_0x28;
    local_a0 = fVar7 + Params.field7_0x24;
    local_94 = 0.0 - Params.field8_0x28 * Params.field6_0x20;
    local_9c = 0.0 - fVar7;
    fStack_84 = 0.0;
    createGameselectLoctext
              ((GameselectLoctext *)"ReplayChapterMenu",Params.field8_0x28,Params.field9_0x2c,
               "gameselect",loctext_aid);
    fStack_88 = fVar7;
    index = CreateLoctext(menu->loctextValueCtx,(LPWSTR)&menu->field_0x4,(menu->someVec_1).x,
                          (menu->someVec_1).y,Params.field0_0x0,Params.field0_0x0,1.0,1,0,1);
    scaleX = Params.field1_0x4;
    fVar7 = (menu->someVec2_2).y;
    menu->loctextIndex = index;
    index = CreateLoctext(menu->loctextValueCtx,menu->someWString,(menu->someVec2_2).x,fVar7,scaleX,
                          scaleX,1.0,1,0,1);
    menu->loctextIndex = index;
    pvVar2 = PTR_005462c4;
    BVar3 = XAPILIB::IsBadReadPtr(PTR_005462c4,CONCAT44(unaff_ESI,unaff_EDI));
    if (BVar3 != 0) {
      return;
    }
    loadCtx = &menu->sceneLoadContext;
    LoadScene_(1,"ReplayChapterMenu",(SceneLoadContext *)&local_90,&local_98,&local_a0,&fStack_88,
               Params.field8_0x28,Params.field9_0x2c,"gameselect",pvVar2,0x400c0,loadCtx);
    pSVar1 = loadCtx->scene;
    pSVar1->originalTimerValue = 0.2;
    if (0.2 < pSVar1->someTimer) {
      pSVar1->someTimer = 0.2;
    }
    *(undefined4 *)(pSVar1->field3814_0x1020 + 0x20) = 0x3e4ccccd;
    iVar4 = loadCtx->scene->field3814_0x1020;
    *(float *)(iVar4 + 0x14) = Params.somePos.x;
    *(float *)(iVar4 + 0x18) = Params.somePos.y;
    *(undefined4 *)(iVar4 + 0x1c) = 3;
    FUN_000e3560();
    FUN_00143b10();
  }
  else if (menu->menuState == AwaitingInput) {
    FUN_00143b80();
  }
  menu->menuState = newState;
  if (newState == MenuState3) {
    FUN_0005f970(menu->loctextValueCtx);
    pSVar1 = (menu->sceneLoadContext).scene;
    if (pSVar1 != (Scene *)0x0) {
      pSVar1->field2160_0x950 = 0;
      FUN_00142c20(3,pSVar1);
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void ReplayChapterMenu::draw(ReplaySceneMenu *menu)

{
  float fVar1;
  int iVar2;
  float *extraout_ECX;
  float *extraout_EDX;
  
  iVar2 = FUN_000489e0(&menu->field520_0x424);
  if (iVar2 != 0) {
    Graphics::RecalculateWorldAndViews();
    FUN_0013c490(&(menu->field520_0x424).float5,&(menu->field520_0x424).field5_0x28,
                 &Graphics::CurrentCameraStruct->affineT);
    fVar1 = *extraout_ECX;
    Graphics::CurrentCameraStruct->near = *extraout_EDX;
    Graphics::CurrentCameraStruct->far = fVar1;
    Graphics::UpdatePerspectiveProj();
    Graphics::UpdateViewport2();
  }
                    // Draw background image
  if (menu->cutsceneBuffer != (Cutscene *)0x0) {
    FUN_0004dbd0(menu->cutsceneBuffer);
  }
  if ((menu->sceneLoadContext).scene != (Scene *)0x0) {
    DrawXboxButtons_(0);
  }
  FUN_00143840();
  return;
}



// WARNING: Unable to track spacebase fully for stack
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Menu12::alloc(void)

{
  malloc_(0xae0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Menu12::ctor(undefined4 param_1,astruct_18 *param_2)

{
  char cVar1;
  ushort uVar2;
  astruct_13 *paVar3;
  float fVar4;
  int i;
  BOOL BVar5;
  void *pvVar6;
  char *pcVar7;
  undefined4 uVar8;
  char *pcVar9;
  undefined4 unaff_ESI;
  undefined4 *puVar10;
  int unaff_EDI;
  void *gameselect_tex;
  char tex_name [128];
  astruct_34 *bruh;
  
  i = 0;
  do {
    cVar1 = "aid_texture_ghoulies_gameselect_house"[i];
    tex_name[i] = cVar1;
    i = i + 1;
  } while (cVar1 != '\0');
  param_2->houseTexture = param_1;
  param_2->field0_0x0 = 0;
  param_2->field2581_0xadc = 0;
  param_2->field2566_0xaac = 0.0;
  param_2->field2573_0xac8 = 0xff;
  param_2->field2570_0xabc = (float)-1;
  param_2->field2568_0xab4 = 0;
  param_2->field2569_0xab8 = 0;
  param_2->field2571_0xac0 = 0;
  param_2->field2572_0xac4 = 0;
  param_2->field2567_0xab0 = (astruct_34 *)0x0;
  bruh = *(astruct_34 **)(param_2->houseTexture + 0x84);
  param_2->field2567_0xab0 = bruh;
  DAT_005065e0 = param_2;
  FUN_000629d0((D3DTexture *)(bruh->textureImportsStart + (uint)bruh->index * 0x14 + (int)bruh),
               (D3DTexture *)0x0);
  D3D8::D3DDevice_Clear(0,(D3DRECT *)0x0,0xf0,0,1.0,0);
  FUN_00062a90();
  param_2->field2577_0xacc = 0;
  param_2->field2030_0x848 = 0;
  param_2->field2031_0x84c = 0;
  param_2->field2032_0x850 = 1;
  param_2->field2033_0x854 = 0xbadbadba;
  param_2->field2034_0x858 = 0;
  runtime::AllocateForLoctext_(0,1,(void *)0xc0,(LoctextValueContext **)&param_2->field2549_0xa68);
  puVar10 = param_2->field2549_0xa68;
  puVar10[5] = 3.0;
  puVar10[6] = 0.7;
  puVar10[7] = 3;
  pvVar6 = PTR_005462c4;
  param_2->field2548_0xa64 = 0;
  param_2->field2546_0xa5c = 0.0;
  param_2->field2547_0xa60 = 0.0;
  param_2->field2035_0x85c = L'\0';
  BVar5 = XAPILIB::IsBadReadPtr(pvVar6,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar5 == 0) {
    createGameselectString("gameselect","xselldemo_titlebanner",&param_2->field2035_0x85c,pvVar6);
  }
  param_2->field2548_0xa64 = 0;
  param_2->field2546_0xa5c = g_DXContext.field28_0x48;
  param_2->field2547_0xa60 = g_DXContext.__0;
  param_2->field2547_0xa60 = g_DXContext.field33_0x5c;
  runtime::AllocateForLoctext_(0,1,(void *)0xc0,(LoctextValueContext **)&param_2->field2029_0x844);
  puVar10 = &param_2->field513_0x21c;
  i = 0;
  do {
    puVar10[-4] = 0;
    puVar10[-6] = 0;
    puVar10[-5] = 0;
    *(undefined2 *)(puVar10 + -0x86) = 0;
    *(undefined2 *)(puVar10 + -0x86) = 0x65;
    *(undefined2 *)((int)puVar10 + -0x212) = 0x6f;
    *(undefined2 *)((int)puVar10 + -0x216) = 0x72;
    *(undefined2 *)(puVar10 + -0x85) = 0x72;
    *(undefined2 *)(puVar10 + -0x84) = 0x72;
    *(undefined2 *)((int)puVar10 + -0x20e) = 0;
    puVar10[-6] = g_DXContext.field28_0x48;
    fVar4 = g_DXContext.__0;
    puVar10[-5] = g_DXContext.__0;
    puVar10[-5] = fVar4 + 36.0;
    puVar10[-4] = 0;
    puVar10[1] = -1;
    puVar10[-1] = 0;
    *puVar10 = 0;
    puVar10[2] = 0;
    puVar10[3] = 0;
    puVar10[-2] = 0;
    if (tex_name._0_4_ == 0x5f646961) {
      Assets::GetResourceBytes(tex_name,&gameselect_tex);
      pvVar6 = gameselect_tex;
      if (gameselect_tex == (void *)0x0) {
        runtime::ExitGame(2);
        pvVar6 = gameselect_tex;
      }
    }
    else {
      pvVar6 = (void *)0x0;
    }
    puVar10[-2] = pvVar6;
    puVar10[-1] = *(undefined4 *)((int)&FLOAT_0042a128 + i);
    *puVar10 = *(undefined4 *)((int)&FLOAT_0042a12c + i);
    puVar10[2] = *(undefined4 *)((int)&FLOAT_0042a138 + i);
    puVar10[3] = *(undefined4 *)((int)&FLOAT_0042a13c + i);
    puVar10[1] = -1;
    pcVar7 = "aid_loctext_ghoulies_gameselect_gameselecttext" +
             *(int *)((int)&XSellDemoParams_0042a0d0.field2_0x8 + i) * 0x80;
    pcVar9 = (char *)(puVar10 + 4);
    do {
      cVar1 = *pcVar7;
      *pcVar9 = cVar1;
      pcVar9 = pcVar9 + 1;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    puVar10[0x27] = -6.05322e-40;
    puVar10[0x28] = *(float *)((int)&FLOAT_0042a138 + i) * 640.0 + 12.0;
    puVar10[0x29] = *(float *)((int)&FLOAT_0042a13c + i) * 480.0 + 12.0;
    puVar10[0x26] = 0;
    uVar8 = LoadMovie((char *)(puVar10 + 4),0x14);
    puVar10[0x24] = uVar8;
    puVar10[0x25] = 0;
    i = i + 0x1c;
    puVar10 = puVar10 + 0xb0;
  } while (i < 0x54);
  param_2->field2553_0xa78 = (float)-1;
  param_2->field2551_0xa70 = 0;
  param_2->field2552_0xa74 = 0;
  param_2->field2554_0xa7c = 0.0;
  param_2->field2555_0xa80 = 0.0;
  param_2->field2550_0xa6c = (void *)0x0;
  if (tex_name._0_4_ == 0x5f646961) {
    Assets::GetResourceBytes(tex_name,&gameselect_tex);
    if (gameselect_tex == (void *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    gameselect_tex = (void *)0x0;
  }
  param_2->field2550_0xa6c = gameselect_tex;
  param_2->field2553_0xa78 = (float)-1;
  param_2->field2551_0xa70 = 0x43a00000;
  param_2->field2552_0xa74 = 0x43700000;
  i = Graphics::CurrentCameraStruct->calculatedWidth_;
  uVar2 = *(ushort *)((int)param_2->field2550_0xa6c + 8);
  param_2->field2555_0xa80 =
       (float)(int)Graphics::CurrentCameraStruct->calculatedHeight__unused /
       (float)*(ushort *)((int)param_2->field2550_0xa6c + 10);
  param_2->field2554_0xa7c = (float)i / (float)uVar2;
  param_2->field2559_0xa90 = (float)-1;
  param_2->field2557_0xa88 = 0;
  param_2->field2558_0xa8c = 0;
  param_2->field2560_0xa94 = 0;
  param_2->field2561_0xa98 = 0;
  param_2->field2556_0xa84 = 0;
  param_2->field2559_0xa90 = (float)-1;
  param_2->field2557_0xa88 = 0x43a00000;
  param_2->field2558_0xa8c = 0x43700000;
  param_2->field2560_0xa94 = param_2->field2554_0xa7c;
  param_2->field2561_0xa98 = param_2->field2555_0xa80;
  paVar3 = PTR_00506c70;
  param_2->field2562_0xa9c = 0;
  param_2->field2563_0xaa0 = 0;
  param_2->field2564_0xaa4 = 2.0;
  param_2->field2565_0xaa8 = 1;
  param_2->field2578_0xad0 = Game::GameState.currentChapter;
  param_2->field2579_0xad4 = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  *(byte *)paVar3->head = *(byte *)paVar3->head | 4;
  FUN_000e67b0(&param_2->field0_0x0,1,unaff_EDI);
  resource::next_menu_id = 0xc;
  XAPILIB::lstrcpyW(g_wString,L"");
  FUN_000e70e0((Menu12 *)param_2,1);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Menu12::dtor(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  UnregisterScript__(*(int *)(param_1 + 0xa68));
  *(undefined4 *)(param_1 + 0xa68) = 0;
  UnregisterScript__(*(int *)(param_1 + 0x844));
  *(undefined4 *)(param_1 + 0x844) = 0;
  FUN_000e6ce0();
  if (*(avatar **)(param_1 + 0x858) != (avatar *)0x0) {
    avatar::destroy(*(avatar **)(param_1 + 0x858));
    *(undefined4 *)(param_1 + 0x858) = 0;
  }
  if (*(void **)(param_1 + 0xa6c) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xa6c));
    *(undefined4 *)(param_1 + 0xa6c) = 0;
    *(undefined4 *)(param_1 + 0xa78) = 0xff0000ff;
  }
  if (*(void **)(param_1 + 0xa84) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xa84));
    *(undefined4 *)(param_1 + 0xa84) = 0;
    *(undefined4 *)(param_1 + 0xa90) = 0xff0000ff;
  }
  Game::GameState.currentChapter = *(int *)(param_1 + 0xad0);
  Game::GameState.currentScene = *(int *)(param_1 + 0xad4);
  piVar3 = (int *)(param_1 + 0x2ac);
  iVar2 = 3;
  do {
    if (*piVar3 != 0) {
      if (0 < piVar3[2]) {
        piVar1 = (int *)(*piVar3 + 0x18);
        *piVar1 = *piVar1 + -1;
        piVar3[2] = piVar3[2] + -1;
      }
      FUN_001072b0();
      *piVar3 = 0;
    }
    piVar3 = piVar3 + 0xb0;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (*(Scene **)(param_1 + 0xadc) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0xadc));
    *(undefined4 *)(param_1 + 0xadc) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Menu12::update(Menu12 *param_1)

{
  InputHandlerType3 *script3;
  int iVar1;
  
  if (param_1->field2702_0xadc != (Scene *)0x0) {
    switch(param_1->state) {
    case 0:
    case 1:
    case 5:
    case 6:
    case 7:
    case 8:
      script3 = (InputHandlerType3 *)0x0;
      break;
    case 2:
    case 3:
    case 4:
      script3 = Input::MenuInputHandler;
      if (Game::DialogState != NotInDialog) goto switchD_000e622e_default;
      break;
    default:
      goto switchD_000e622e_default;
    }
    Input::UpdateMenuInput(script3,param_1->field2702_0xadc);
  }
switchD_000e622e_default:
  switch(param_1->state) {
  case 1:
    if (param_1->field2659_0xaa8 != 0) {
      FUN_000e6f10(param_1);
    }
    iVar1 = entitySceneControlGameSelect::isStatus2Or3(param_1->field2701_0xad8);
    if (iVar1 == 0) {
                    // Crashes the game in demo mode
      FUN_000e70e0(param_1,5);
      return;
    }
    break;
  case 5:
    FUN_000e6890();
    return;
  case 6:
    FUN_000e6a30();
    return;
  case 7:
    iVar1 = entitySceneControlGameSelect::isStatus2Or3(param_1->field2701_0xad8);
    if (iVar1 == 0) {
      FUN_000e70e0(param_1,8);
    }
  }
  return;
}




void Menu12::draw(float *param_1)

{
  int *piVar1;
  float fVar2;
  DXTextureInstance *pDVar3;
  float *pfVar4;
  float *pfVar5;
  undefined1 uVar6;
  float *pfVar7;
  float fVar8;
  uint64_t uVar9;
  undefined4 uStack_8;
  
  pfVar5 = param_1;
  fVar8 = *param_1;
  fVar2 = param_1[0x214];
  if (((fVar8 == 2.8026e-45) || (fVar8 == 4.2039e-45)) || (fVar8 == 5.60519e-45)) {
    if (param_1[(int)fVar2 * 0xb0 + 0xab] != 0.0) {
      if ((char)(undefined1)g_globalFlagset < '\0') {
        if (0 < (int)param_1[(int)fVar2 * 0xb0 + 0xad]) {
          FUN_000e7650();
        }
      }
      else if ((int)param_1[(int)fVar2 * 0xb0 + 0xad] < 1) {
        piVar1 = (int *)((int)param_1[(int)fVar2 * 0xb0 + 0xab] + 0x18);
        *piVar1 = *piVar1 + 1;
        param_1[(int)fVar2 * 0xb0 + 0xad] = (float)((int)param_1[(int)fVar2 * 0xb0 + 0xad] + 1);
      }
    }
  }
  if ((*param_1 == 1.4013e-45) ||
     (pfVar7 = param_1 + (int)fVar2 * 0xb0, (int)param_1[(int)fVar2 * 0xb0 + 0xac] < 1)) {
    pfVar7 = param_1 + (int)fVar2 * 0xb0;
    param_1[0x2ac] = param_1[(int)fVar2 * 0xb0 + 0x85];
  }
  else if (pfVar7[0xab] != 0.0) {
    param_1[0x2ac] = *(float *)((int)param_1[0x2b6] + 0x84);
    FUN_00107360();
  }
  if ((param_1[0x29b] != 0.0) && (*(char *)((int)param_1 + 0xa7b) != '\0')) {
    DrawMalloced100Value
              (param_1[0x29b],param_1 + 0x29c,param_1 + 0x29f,0,(TextDrawData *)param_1[0x29e],0);
  }
  if ((param_1[0x2a1] != 0.0) && (*(char *)((int)param_1 + 0xa93) != '\0')) {
    DrawMalloced100Value
              (param_1[0x2a1],param_1 + 0x2a2,param_1 + 0x2a5,0,(TextDrawData *)param_1[0x2a4],0);
  }
  param_1 = (float *)0x0;
  pfVar4 = pfVar5;
  do {
    if ((param_1 != (float *)pfVar5[0x214]) && (pfVar4[0x85] != 0.0)) {
      FUN_00061360((float)((int)pfVar4[0x86] - (int)pfVar4[0xaf] / 2),
                   (float)((int)pfVar4[0x87] - (int)pfVar4[0xb0] / 2),(float)(int)pfVar4[0xaf],
                   0x3dcccccd,pfVar4[0xae]);
      fVar8 = pfVar4[0x88];
      pDVar3 = (DXTextureInstance *)pfVar4[0x85];
      Graphics::ReconfigureRenderer();
      Graphics::DrawTexture(0,0,pDVar3,(vec2 *)(pfVar4 + 0x89),0,0.0,fVar8,(vec2 *)(pfVar4 + 0x86));
      Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
      if (Graphics::UseDefaultPixelC0 == 0) {
        DAT_00509b00 = 0;
      }
    }
    param_1 = (float *)((int)param_1 + 1);
    pfVar4 = pfVar4 + 0xb0;
  } while ((int)param_1 < 3);
  if (pfVar7[0x85] != 0.0) {
    FUN_00061360((float)((int)pfVar7[0x86] - (int)pfVar7[0xaf] / 2),
                 (float)((int)pfVar7[0x87] - (int)pfVar7[0xb0] / 2),(float)(int)pfVar7[0xaf],
                 0x3dcccccd,pfVar7[0xae]);
    pDVar3 = (DXTextureInstance *)pfVar7[0x85];
    fVar8 = pfVar7[0x88];
    Graphics::ReconfigureRenderer();
    Graphics::DrawTexture(0,0,pDVar3,(vec2 *)(pfVar7 + 0x89),0,0.0,fVar8,(vec2 *)(pfVar7 + 0x86));
    Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
    if (Graphics::UseDefaultPixelC0 == 0) {
      DAT_00509b00 = 0;
    }
  }
  if ((pfVar7[0xab] != 0.0) && (*(int *)((int)pfVar7[0xab] + 8) != 0)) {
    if (1 < (int)pfVar7[0xac]) {
      fVar8 = ((float)(int)pfVar7[0xac] - 1.0) * 0.05 * 255.0;
      if (fVar8 <= 255.0) {
        param_1 = (float *)0x0;
        if (0.0 <= fVar8) {
          param_1 = (float *)fVar8;
        }
      }
      else {
        param_1 = (float *)255.0;
      }
      uVar9 = float10::to_uint64_t((float10)(float)param_1);
      uVar6 = (undefined1)uVar9;
      fVar8 = *pfVar5;
      if (((fVar8 == 8.40779e-45) || (fVar8 == 9.80909e-45)) || (fVar8 == 1.12104e-44)) {
        uVar6 = *(undefined1 *)(pfVar5 + 0x2b2);
      }
      uStack_8 = CONCAT13(uVar6,0xffffff);
      fVar8 = pfVar5[0x214];
      pDVar3 = (DXTextureInstance *)pfVar5[0x2ac];
      Graphics::ReconfigureRenderer();
      Graphics::DrawTexture
                (0,(int)fVar8 * 0x1c + 0x42a0dc,pDVar3,(vec2 *)(pfVar5 + (int)fVar8 * 0xb0 + 0x89),
                 (int)fVar8 * 0x1c + 0x42a0e4,0.0,uStack_8,
                 (vec2 *)(pfVar5 + (int)fVar8 * 0xb0 + 0x86));
      Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
      if (Graphics::UseDefaultPixelC0 == 0) {
        DAT_00509b00 = 0;
      }
    }
    if ((*pfVar5 != 1.4013e-45) && ((int)pfVar7[0xac] < 100)) {
      pfVar7[0xac] = (float)((int)pfVar7[0xac] + 1);
    }
  }
  if (Game::DialogState == NotInDialog) {
    if ((pfVar5[0x2aa] == 0.0) && (fVar8 = pfVar5[0x216], fVar8 != 0.0)) {
      if (*(float *)((int)fVar8 + 0x200) != 2.0) {
        *(float *)((int)fVar8 + 0x200) = 2.0;
        *(undefined4 *)((int)fVar8 + 0x2a8) = 0;
      }
      (**(code **)(*(int *)pfVar5[0x216] + 0x14))
                ((int *)pfVar5[0x216],
                 (int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,3);
    }
    if (pfVar5[0x2b7] != 0.0) {
      DrawXboxButtons_(0);
    }
  }
  return;
}




void FUN_000e6f10(Menu12 *menu)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  float fVar4;
  uint64_t uVar5;
  float local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (runtime::dx_timer <= 0.0) {
    fVar4 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar4 = 0.0;
  }
  if ((0.0 < *(float *)&menu->field_0xaa4) &&
     (fVar4 = *(float *)&menu->field_0xaa4 - fVar4, *(float *)&menu->field_0xaa4 = fVar4,
     fVar4 <= 0.0)) {
    *(undefined4 *)&menu->field_0xaa4 = 0;
  }
  fVar4 = (*(float *)&menu->field_0xaa4 - 2.0) * -0.5;
  if (fVar4 <= 1.0) {
    local_c = 0.0;
    if (0.0 <= fVar4) {
      local_c = fVar4;
    }
  }
  else {
    local_c = 1.0;
  }
  uVar5 = float10::to_uint64_t((float10)local_c * (float10)255.0);
  local_8 = CONCAT13((char)uVar5,0xffffff);
  uVar5 = float10::to_uint64_t((float10)local_c * (float10)128.0);
  local_4 = (float)CONCAT13((char)uVar5,0x69764);
  pfVar2 = &menu->field687_0x2b8;
  iVar3 = 3;
  pfVar1 = pfVar2;
  do {
    pfVar1[-0x26] = (float)local_8;
    *pfVar1 = local_4;
    pfVar1 = pfVar1 + 0xb0;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  (&menu->field687_0x2b8)[menu->field2077_0x850 * 0xb0] = -763.8705;
  uVar5 = float10::to_uint64_t((float10)local_c * (float10)196.0);
  *(char *)((int)&menu->field687_0x2b8 + menu->field2077_0x850 * 0x2c0 + 3) = (char)uVar5;
  if (1.0 <= local_c) {
    menu->field2659_0xaa8 = 0;
    iVar3 = 3;
    do {
      pfVar2[-0x26] = (float)-1;
      *pfVar2 = -6.05322e-40;
      pfVar2 = pfVar2 + 0xb0;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    (&menu->field687_0x2b8)[menu->field2077_0x850 * 0xb0] = -763.8705;
  }
  return;
}




void FUN_000e70e0(Menu12 *menu,uint param_2)

{
  Scene *pSVar1;
  asset_name *newPlaycamScript;
  uint uVar2;
  entityAvatarMiscButtonBat *peVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  float fVar7;
  undefined4 uVar8;
  float local_ac;
  vec2 local_a8;
  float local_a0 [3];
  float local_94;
  undefined4 local_90;
  undefined4 local_8c;
  char local_88 [128];
  
  if (menu->state == 1) {
    if (menu->field2659_0xaa8 != 0) {
      menu->field2659_0xaa8 = 0;
      FUN_000e7090();
    }
    local_a8.x = menu->field2595_0xa5c;
    uVar2 = CreateLoctext(menu->field2598_0xa68,(LPWSTR)&menu->field_0x85c,local_a8.x,
                          menu->field2596_0xa60,1.35,1.35,1.0,1,0,1);
    menu->field2597_0xa64 = uVar2;
    local_a8.x = 0.0;
    local_a8.y = 0.0;
    if (menu->field2082_0x858 == (entityAvatarMiscButtonBat *)0x0) {
      peVar3 = entityAvatarMiscButtonBat::create(2.0,0.4,&local_a8);
      menu->field2082_0x858 = peVar3;
    }
    pcVar5 = "aid_loctext_ghoulies_gameselect_gameselecttext";
    pcVar6 = local_88;
    for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar6 = pcVar6 + 4;
    }
    *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
    pcVar6[2] = pcVar5[2];
    local_a0[2] = g_DXContext.field32_0x58 + 16.0;
    pcVar5 = local_88 + 0x2f;
    for (iVar4 = 0x14; iVar4 != 0; iVar4 = iVar4 + -1) {
      pcVar5[0] = '\0';
      pcVar5[1] = '\0';
      pcVar5[2] = '\0';
      pcVar5[3] = '\0';
      pcVar5 = pcVar5 + 4;
    }
    local_94 = g_DXContext.field35_0x64 - 16.0;
    local_8c = 0xc2000000;
    *pcVar5 = '\0';
    local_a0[0] = 20.0;
    fVar7 = -16.0;
    local_ac = 0.0;
    local_90 = 0;
    local_a0[1] = -16.0;
    createGameselectLoctext
              ((GameselectLoctext *)"frontendGameSlotPlay",1.0,0.75,"gameselect",local_88);
    if (0.0 < fVar7) {
      local_ac = fVar7;
    }
    createGameselectLoctext
              ((GameselectLoctext *)"frontendGameSlotChallenges",1.0,0.75,"gameselect",local_88);
    if (local_ac < fVar7) {
      local_ac = fVar7;
    }
    createGameselectLoctext
              ((GameselectLoctext *)"frontendGameSlotFeatures",1.0,0.75,"gameselect",local_88);
    if (local_ac < fVar7) {
      local_ac = fVar7;
    }
    local_a8.x = local_ac;
    local_a8.y = 0.0;
    TransitionAndLoadScene
              (1,0,local_a0 + 2,&local_90,local_a0,&local_a8,0x3f800000,&DAT_3f400000,"gameselect",
               local_88,0x400c0);
    pSVar1 = menu->field2702_0xadc;
    pSVar1->originalTimerValue = 0.2;
    if (0.2 < pSVar1->someTimer) {
      pSVar1->someTimer = 0.2;
    }
    *(undefined4 *)(pSVar1->field3814_0x1020 + 0x20) = 0x3e4ccccd;
    iVar4 = menu->field2702_0xadc->field3814_0x1020;
    *(float *)(iVar4 + 0x14) = 3.0;
    *(float *)(iVar4 + 0x18) = 0.7;
    *(undefined4 *)(iVar4 + 0x1c) = 3;
  }
  else if (menu->state == 6) {
    uVar8 = 3;
    newPlaycamScript =
         Assets::GetEntryAfterInTable
                   ((asset_name **)&Assets::SceneOrderAHandle,Game::GameState.currentSceneScript,1);
    entitySceneControlGameSelect::setPlaycamScript(menu->field2701_0xad8,uVar8,newPlaycamScript);
  }
  menu->state = param_2;
  switch(param_2) {
  case 5:
    menu->field545_0x224 = FLOAT_0042a138;
    menu->field546_0x228 = FLOAT_0042a13c;
    menu->field688_0x2bc = FLOAT_0042a138 * 640.0 + 12.0;
    menu->field689_0x2c0 = FLOAT_0042a13c * 480.0 + 12.0;
    menu->field687_0x2b8 = -6.05322e-40;
    menu->field1234_0x4e4 = FLOAT_0042a154;
    menu->field1235_0x4e8 = FLOAT_0042a158;
    menu->field1377_0x57c = FLOAT_0042a154 * 640.0 + 12.0;
    menu->field1378_0x580 = FLOAT_0042a158 * 480.0 + 12.0;
    menu->field1376_0x578 = -6.05322e-40;
    menu->field1923_0x7a4 = FLOAT_0042a170;
    menu->field1924_0x7a8 = FLOAT_0042a174;
    menu->field2066_0x83c = FLOAT_0042a170 * 640.0 + 12.0;
    menu->field2067_0x840 = FLOAT_0042a174 * 480.0 + 12.0;
    menu->field2065_0x838 = -6.05322e-40;
    FUN_000e6bd0(menu);
    FUN_000e6db0();
    if (menu->field2702_0xadc != (Scene *)0x0) {
      iVar4 = menu->field2077_0x850;
      if (iVar4 == 0) {
        FUN_00142180();
        return;
      }
      if (iVar4 == 1) {
        FUN_00142180();
        return;
      }
      if (iVar4 == 2) {
        FUN_00142180();
        return;
      }
    }
    break;
  case 6:
    if (0 < *(int *)(&menu->field_0x2b4 + menu->field2077_0x850 * 0x2c0)) {
      FUN_000e7650();
    }
    FUN_0013b9d0();
    pSVar1 = menu->field2702_0xadc;
    pSVar1->field2160_0x950 = 0;
    FUN_00142c20(3,pSVar1);
    menu->field2660_0xaac = 0.75;
    FUN_0005f7e0(menu->field2598_0xa68);
    FUN_0005f7e0(menu->field2068_0x844);
    return;
  case 7:
    if (0 < *(int *)(&menu->field_0x2b4 + menu->field2077_0x850 * 0x2c0)) {
      FUN_000e7650();
    }
    FUN_0013b9d0();
    return;
  case 8:
    FUN_0005f7e0(menu->field2598_0xa68);
    FUN_0005f7e0(menu->field2068_0x844);
    pSVar1 = menu->field2702_0xadc;
    if (pSVar1 != (Scene *)0x0) {
      pSVar1->field2160_0x950 = 0;
      FUN_00142c20(3,pSVar1);
    }
  }
  return;
}




void UI::EnterPauseUI(void)

{
  Game::SetPauseState(EnteringPause);
  Audio::PlayOrChangeByName(0x10,"XACT_SOUNDBANK_GSTREAMSDITTIES_PAUSE");
  UpdateGameVolumes();
  g_gameStateStack = g_gameStateStack + 1;
  return;
}




void runtime::UpdatePauseScreen(void)

{
  int *piVar1;
  int iVar2;
  InputHandlerType3 *script3;
  BOOL BVar3;
  uint uVar4;
  int i;
  char *pcVar5;
  char *pcVar6;
  undefined4 *puVar7;
  bool bVar8;
  bool bVar9;
  float fVar10;
  char new_aid [42];
  undefined4 local_56 [21];
  
  if ((1 < (int)Game::g_pauseState) && ((int)Game::g_pauseState < 10)) {
    Events::UpdateDialogState();
  }
  if (g_pausePadScript != (InputHandlerType3 *)0x0) {
    FUN_00109470((InputHandlerType4 *)g_pausePadScript);
  }
                    // Old state
  switch(Game::g_pauseState) {
  case Playing:
    if ((DAT_00510e30 != (Scene *)0x0) &&
       (DAT_00510e30->inputContextStart == (SceneInputContext *)0x0)) {
      Scene::free(DAT_00510e30);
      DAT_00510e30 = (Scene *)0x0;
    }
    if ((DAT_00510cf8 != (int *)0x0) &&
       (*(uint *)(*DAT_00510cf8 + 8) <= *(uint *)(*DAT_00510cf8 + 4))) {
      UnregisterScript__((int)DAT_00510cf8);
      DAT_00510cf8 = (int *)0x0;
    }
    break;
  case EnteringPause:
    if (DAT_00510e24 != (int *)0x0) {
      fVar10 = *(float *)(DAT_00510e24[9] + 0x2c) / *(float *)(DAT_00510e24[9] + 0x34);
      bVar9 = fVar10 == 0.123;
      bVar8 = fVar10 < 0.123;
LAB_0011d011:
      if (bVar8 || bVar9) break;
    }
    goto LAB_0011d017;
  case Paused:
  case 8:
    break;
  case New_Name_(2):
  case ChallengeRules:
    if ((Game::DialogState != NotInDialog) || (Game::g_pauseState == Paused)) break;
    goto LAB_0011d020;
  case ExitingPause:
    if ((DAT_00510e24 == (int *)0x0) || (DAT_00510e24[4] != 0)) {
      pcVar5 = "aid_script_ghoulies_gameselect_gameselect";
      pcVar6 = new_aid;
      for (i = 10; i != 0; i = i + -1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar6 = (char *)((int)pcVar6 + 4);
      }
      *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
      puVar7 = local_56;
      for (i = 0x15; i != 0; i = i + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      *(undefined2 *)puVar7 = 0;
      switch(game::return_menu_state) {
      case ReturnToScene:
        Game::SetPauseState(Playing);
        break;
      case ReturnToMainMenu:
        game::reset_scene_vars_on_leave();
        if (game::oldNextPlaycamScriptWide[0] == L'\0') {
          reuse_old_playcam_id();
        }
        else {
          resource::next_menu_id = MainMenu;
          XAPILIB::lstrcpyW(g_wString,g_someWString);
          setNextPlaycamScriptAID(1,new_aid);
        }
        break;
      case RestartScene:
        FUN_0004a310();
        game::reset_scene_vars_on_leave();
        break;
      case ReturnToBonusChallenges:
        game::reset_scene_vars_on_leave();
        resource::next_menu_id = BonusChallenges;
        XAPILIB::lstrcpyW(g_wString,g_someWString);
        setNextPlaycamScriptAID(1,new_aid);
        break;
      case ReturnToReplayScene:
        resource::next_menu_id = ReplayScene;
        XAPILIB::lstrcpyW(g_wString,g_someWString);
        setNextPlaycamScriptAID(1,new_aid);
        break;
      case ReturnToBonusBookLevelSelect:
        resource::next_menu_id = BonusBooksLevelSelect;
        XAPILIB::lstrcpyW(g_wString,g_someWString);
        setNextPlaycamScriptAID(1,new_aid);
        break;
      case ReturnToReplayChapter:
        game::reset_scene_vars_on_leave();
        resource::next_menu_id = ReplayChapter;
        XAPILIB::lstrcpyW(g_wString,g_someWString);
        setNextPlaycamScriptAID(1,new_aid);
      }
    }
    break;
  case MapScreen:
    if (((DAT_00510e24 == (int *)0x0) || (DAT_00510e24[4] != 0)) && (Game::g_pauseState != 8)) {
      Game::g_pauseState = 8;
      FUN_0011dd10();
      g_globalFlagset = g_globalFlagset | 0x2200;
    }
    break;
  case 9:
    if (DAT_00510e24 != (int *)0x0) {
      fVar10 = *(float *)(DAT_00510e24[9] + 0x2c) / *(float *)(DAT_00510e24[9] + 0x34);
      bVar9 = fVar10 == 0.815;
      bVar8 = fVar10 < 0.815;
      goto LAB_0011d011;
    }
LAB_0011d017:
    if (Game::g_pauseState != Paused) {
LAB_0011d020:
      Game::g_pauseState = Paused;
      FUN_00048940(0.123);
      piVar1 = DAT_00510e24 + 2;
      if (DAT_00510e24[2] == 0) {
        CloseDoorAndUpdateState(1,(Cutscene *)DAT_00510e24[9]);
        *piVar1 = 1;
      }
    }
    break;
  default:
    goto switchD_0011cfec_default;
  }
switchD_0011cfec_default:
  switch(Game::g_pauseState) {
  case Playing:
  case EnteringPause:
  case ExitingPause:
  case MapScreen:
  case 9:
    if (DAT_00510e30 != (Scene *)0x0) {
LAB_0011d2b8:
      script3 = (InputHandlerType3 *)0x0;
LAB_0011d2ba:
      Input::UpdateMenuInput(script3,DAT_00510e30);
    }
    break;
  case Paused:
    if (g_pausePadScript == (InputHandlerType3 *)0x0) goto LAB_0011d2b8;
    i = Input::UpdateMenuInput(g_pausePadScript,DAT_00510e30);
    if (((i == 0) && (i = FUN_0011dea0(), i != 0)) &&
       (BVar3 = Input::ContextHasButton(START,g_pausePadScript), BVar3 != 0)) {
      FUN_0011dee0();
    }
    break;
  case 8:
    script3 = g_pausePadScript;
    if (DAT_00510e30 != (Scene *)0x0) goto LAB_0011d2ba;
  }
  if ((int)Game::g_pauseState < 2) {
    return;
  }
  if ((7 < (int)Game::g_pauseState) && (Game::g_pauseState != 9)) {
    return;
  }
  if (DAT_00510e24 == (int *)0x0) {
    return;
  }
  i = *DAT_00510e24;
  iVar2 = DAT_00510e24[9];
  fVar10 = *(float *)(iVar2 + 0x2c) / *(float *)(iVar2 + 0x34);
  if (fVar10 < Cutscene::PauseCutsceneLookupTable[i].tToDoLoad ||
      fVar10 == Cutscene::PauseCutsceneLookupTable[i].tToDoLoad) {
    uVar4 = Cutscene::PauseCutsceneLookupTable[i].field5_0x10c;
  }
  else {
    fVar10 = *(float *)(iVar2 + 0x2c) / *(float *)(iVar2 + 0x34);
    if (fVar10 < Cutscene::PauseCutsceneLookupTable[i].tToSwapBuffers ||
        fVar10 == Cutscene::PauseCutsceneLookupTable[i].tToSwapBuffers) goto LAB_0011d39f;
    uVar4 = Cutscene::PauseCutsceneLookupTable[i].field6_0x110;
  }
  if (uVar4 != 0xffffffff) {
    DAT_00510e24[uVar4 * 4 + 0x25] = 1;
  }
LAB_0011d39f:
  FUN_000483e0(DAT_00510e24);
  return;
}




void UI::UnloadSomeElements2_(void)

{
  if (g_UIElement12 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(g_UIElement12);
    g_UIElement12 = (void *)0x0;
  }
  if (g_UIElement13 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(g_UIElement13);
    g_UIElement13 = (void *)0x0;
  }
  if (g_UIElement14 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(g_UIElement14);
    g_UIElement14 = (void *)0x0;
  }
  BaronDraw_00545994.type = New_Name;
  BaronDraw_00545994.stateScalar = 0.0;
  BaronDraw_00545994.scalar = 0.0;
  BaronDraw_00545994.field3_0xc = 0;
  BaronDraw_00545994.field4_0x10 = 0;
  DAT_00545990 = 0;
  if (g_UIElement10 != (Scene *)0x0) {
    Scene::free(g_UIElement10);
    g_UIElement10 = (Scene *)0x0;
  }
  return;
}




void UI::UnloadSomeElements_(void)

{
  if (g_UIElement9 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(g_UIElement9);
    g_UIElement9 = (void *)0x0;
  }
  if (g_UIElement8 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(g_UIElement8);
    g_UIElement8 = (void *)0x0;
  }
  BaronDraw_0043268c.type = New_Name;
  BaronDraw_0043268c.field3_0xc = 0;
  BaronDraw_0043268c.field4_0x10 = 0;
  BaronDraw_0043268c.stateScalar = 0.0;
  BaronDraw_0043268c.scalar = 0.0;
  DAT_00432688 = 0xffffffff;
  return;
}




void __fastcall UI::LoadHealthTextures(actorBody *inAsset)

{
  actorBody *asset;
  char *asset_name;
  actorBody *pAVar1;
  
  asset = inAsset;
  if (g_LoadedHeartAsset == (actorBody *)0x0) {
    if ((PTR_00506c6c->field2_0x8[4] & 0x40) == 0) {
      asset_name = "aid_texture_ghoulies_scoreboard_energy_heart";
    }
    else {
      asset_name = "aid_texture_ghoulies_scoreboard_energy_heartgold";
    }
    Assets::GetResourceBytes(asset_name,&asset);
    pAVar1 = asset;
    if (asset == (actorBody *)0x0) {
      runtime::ExitGame(2);
    }
    g_LoadedHeartAsset = pAVar1;
    _DAT_00433c90 = (uint)*(ushort *)&pAVar1->actor;
  }
  if (g_BrokenHeartAsset == (actorBody *)0x0) {
    if ((PTR_00506c6c->field2_0x8[4] & 0x40) == 0) {
      asset_name = "aid_texture_ghoulies_scoreboard_energy_heartbroken";
    }
    else {
      asset_name = "aid_texture_ghoulies_scoreboard_energy_heartgoldbroken";
    }
    Assets::GetResourceBytes(asset_name,&asset);
    pAVar1 = asset;
    if (asset == (actorBody *)0x0) {
      runtime::ExitGame(2);
    }
    g_BrokenHeartAsset = pAVar1;
    _DAT_00433c94 = (uint)*(ushort *)&pAVar1->actor;
  }
  if (g_InvulnerableHeartAsset == (actorBody *)0x0) {
    Assets::GetResourceBytes("aid_texture_ghoulies_powerups_invunerability",&asset);
    pAVar1 = asset;
    if (asset == (actorBody *)0x0) {
      runtime::ExitGame(2);
    }
    g_InvulnerableHeartAsset = pAVar1;
    _DAT_00433c98 = (uint)*(ushort *)&pAVar1->actor;
  }
  if (g_ImpHeadGlowAsset == (actorBody *)0x0) {
    Assets::GetResourceBytes("aid_texture_particles_impheadglow",&asset);
    pAVar1 = asset;
    if (asset == (actorBody *)0x0) {
      runtime::ExitGame(2);
    }
    g_ImpHeadGlowAsset = pAVar1;
    Game::HealthMetadata[0]._0_4_ = ZEXT24(*(ushort *)&pAVar1->actor);
  }
  if (g_BaronUIAsset == (actorBody *)0x0) {
    Assets::GetResourceBytes("aid_texture_ghoulies_scoreboard_dialogheads_baron",&asset);
    pAVar1 = asset;
    if (asset == (actorBody *)0x0) {
      runtime::ExitGame(2);
    }
    g_BaronUIAsset = pAVar1;
    Game::HealthMetadata[0].minHealth = (float)(uint)*(ushort *)&pAVar1->actor;
  }
  return;
}




void UI::InitialiseVariables(void)

{
  DAT_00433bf4 = 1.0;
  INT_00433bf8 = (int)1.0;
  FLOAT_00433c04 = 0.1;
  FLOAT_00433bfc = 0.05;
  FLOAT_00433c0c = 1.2;
  FLOAT_00433c00 = 0.0;
  FLOAT_00433c08 = 0.0;
  INT_00433be0 = 0;
  INT_00433c70 = 0;
  Audio::RandomiserBankIndex = 0;
  BaronDraw_00433c10.type = New_Name;
  BaronDraw_00433c10.stateScalar = 0.0;
  BaronDraw_00433c10.scalar = 0.0;
  BaronDraw_00433c10.field3_0xc = 0;
  BaronDraw_00433c10.field4_0x10 = 0;
  g_BaronTexture_.type = New_Name;
  g_BaronTexture_.stateScalar = 0.0;
  g_BaronTexture_.scalar = 0.0;
  g_BaronTexture_.field3_0xc = 0;
  g_BaronTexture_.field4_0x10 = 0;
  INT_00433c38 = 0;
  PlayerHealth = 0;
  RandomBaronHealth = 0;
  FLOAT_00433c64 = 0.4;
  FLOAT_00433c68 = 0.0;
  INT_00433c40 = 0;
  INT_00433c44 = 0;
  INT_00433c48 = 0;
  INT_00433c4c = 0;
  INT_00433c50 = 0;
  INT_00433c54 = 0;
  INT_00433c58 = 0;
  INT_00433c5c = 0;
  return;
}




void __fastcall UI::DrawRandomiser(void)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  actorBody *in_ECX;
  actorBody *extraout_ECX;
  actorBody *parentState;
  undefined4 extraout_ECX_00;
  actorBody *inAsset;
  vec3 *pvVar3;
  float fVar4;
  float local_4;
  char *sound;
  bool update_fake_health;
  
  update_fake_health = false;
  if (DAT_00433be8 == 1) {
    if (Audio::RandomiserBankIndex == 0) {
      inAsset = (actorBody *)FUN_001309c0();
    }
    else {
      Audio::LoadRandomiserSounds("XACT_SOUNDBANK_GPROPS_RANDOMIZER",Audio::RandomiserBankIndex);
      update_fake_health = true;
      if ((BaronDraw_00433c10.type == New_Name_(2)) ||
         (inAsset = parentState, BaronDraw_00433c10.type == New_Name_(3))) {
        if (runtime::dx_timer <= 0.0) {
          fVar4 = runtime::DeltaTime * runtime::TimeScale;
        }
        else {
          fVar4 = 0.0;
        }
        inAsset = parentState;
        if ((0.0 < g_UITimeRelatedFloat) &&
           (g_UITimeRelatedFloat = g_UITimeRelatedFloat - fVar4, inAsset = parentState,
           g_UITimeRelatedFloat <= 0.0)) {
          g_UITimeRelatedFloat = 0.0;
          DAT_00433be8 = 2;
          if (PlayerHealth < 11) {
            sound = "XACT_SOUNDBANK_GBARON_COMING_2";
          }
          else if (PlayerHealth < 21) {
            sound = "XACT_SOUNDBANK_GBARON_EVILLAUGH_2";
          }
          else {
            sound = "XACT_SOUNDBANK_GBARON_WHAT_2";
          }
          Audio::PlaySound(sound,parentState);
          inAsset = (actorBody *)
                    (CONCAT31((int3)((uint)extraout_ECX_00 >> 8),*PTR_00506c6c->field2_0x8) | 0x40);
          *PTR_00506c6c->field2_0x8 = (char)inAsset;
        }
      }
    }
  }
  else {
    inAsset = in_ECX;
    if ((DAT_00433be8 == 2) && (iVar2 = FUN_001309f0(), inAsset = extraout_ECX, iVar2 != 0)) {
      DAT_00433be8 = 0;
    }
  }
  if (INT_00433c70 == 0) {
    if (INT_00433be0 != 0) {
      if (((g_globalFlagset & 0x4020) == 0) && (!update_fake_health)) goto LAB_001302e4;
      goto LAB_001302b8;
    }
  }
  else {
LAB_001302b8:
    BaronDraw_00433c10.scalar = 2.0;
    LoadHealthTextures(inAsset);
  }
  if (update_fake_health) {
    g_BaronTexture_.scalar = 2.0;
  }
LAB_001302e4:
  local_4 = 0.0;
                    // Draw baron
  FUN_00131c50(0,&g_BaronTexture_);
                    // Instant crash when disabled????
  bVar1 = FUN_00131c50(0,&BaronDraw_00433c10);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    FUN_00130a50();
    INT_00433bf8 = (int)in_ECX->actor;
    FLOAT_00433c04 = 0.1;
    FLOAT_00433c0c = *(float *)&in_ECX->field_0x4;
    if (0 < INT_00433c38) {
      if (runtime::dx_timer <= local_4) {
        local_4 = runtime::DeltaTime * runtime::TimeScale;
      }
      FUN_00104df0(local_4);
    }
    pvVar3 = (vec3 *)&LAB_00313a2c;
    if (INT_00433c70 == 0) {
      pvVar3 = (vec3 *)&LAB_00313a18;
    }
    FUN_0012ef60((float *)&INT_00433c38,pvVar3);
                    // Update fake UI value
    if (update_fake_health) {
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      RandomBaronHealth =
           (int)(((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 89.0 + 10.0);
    }
    Audio::RandomiserBankIndex = 0;
    return;
  }
  FUN_001308a0();
  Audio::RandomiserBankIndex = 0;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void UI::UnloadElement(int *param_1)

{
  void *__dest;
  ushort *puVar1;
  undefined4 uVar2;
  int *mem;
  void *pvVar3;
  int iVar4;
  HeapTableEntry *pHVar5;
  
  mem = param_1;
  pvVar3 = *(void **)(*param_1 + 8);
  __dest = *(void **)(*param_1 + 4);
  if (__dest < pvVar3) {
    param_1 = (int *)((uint)((int)pvVar3 + (-1 - (int)__dest)) / 0x94 + 1);
    do {
      Assets::DestroyAssetOrDecrement(*(void **)((int)__dest + 0x88));
      *(undefined4 *)((int)__dest + 0x88) = 0;
      puVar1 = (ushort *)*mem;
      pvVar3 = (void *)(*(int *)(puVar1 + 4) - (uint)*puVar1);
      if (__dest < pvVar3) {
        _memmove(__dest,(void *)((uint)*puVar1 + (int)__dest),(int)pvVar3 - (int)__dest);
      }
      param_1 = (int *)((int)param_1 + -1);
      *(uint *)(puVar1 + 4) = *(int *)(puVar1 + 4) - (uint)*puVar1;
    } while (param_1 != (int *)0x0);
  }
  if ((void *)mem[2] != (void *)0x0) {
    Assets::DestroyAssetOrDecrement((void *)mem[2]);
    mem[2] = 0;
  }
  if ((void *)mem[3] != (void *)0x0) {
    Assets::DestroyAssetOrDecrement((void *)mem[3]);
    mem[3] = 0;
  }
  pvVar3 = (void *)*mem;
  if (pvVar3 != (void *)0x0) {
    iVar4 = FindHeapOf(pvVar3);
    uVar2 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar4].heapHandle == (HANDLE)0x0) {
      pHVar5 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar5 = g_HeapTableBase + iVar4;
    }
    runtime::CurrentHeapToAllocateFrom = iVar4;
    XAPILIB::HeapFree(pHVar5->heapHandle,0,pvVar3);
    runtime::CurrentHeapToAllocateFrom = uVar2;
    *mem = 0;
  }
  iVar4 = FindHeapOf(mem);
  uVar2 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar4].heapHandle == (HANDLE)0x0) {
    pHVar5 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar5 = g_HeapTableBase + iVar4;
  }
  runtime::CurrentHeapToAllocateFrom = iVar4;
  XAPILIB::HeapFree(pHVar5->heapHandle,0,mem);
  runtime::CurrentHeapToAllocateFrom = uVar2;
  return;
}



// Game locks up when level goals show up and this is disabled


void UI::Draw2DElements(int *param_1)

{
  int iVar1;
  ushort *puVar2;
  bool bVar3;
  undefined3 extraout_var;
  void *pvVar4;
  void *__dest;
  void *local_8;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    __dest = *(void **)(iVar1 + 4);
    local_8 = *(void **)(iVar1 + 8);
    if (__dest < local_8) {
      do {
        if (((*(int *)((int)__dest + 8) == 2) && (g_paused_ != 0)) ||
           (bVar3 = FUN_00131c50(param_1[0x14],(BaronDraw *)((int)__dest + 8)),
           CONCAT31(extraout_var,bVar3) != 0)) {
          DAT_00545ab4 = param_1;
          FUN_00104df0(g_totalTimeSpentThisSession);
          DAT_00545ab4 = (int *)0x0;
          FUN_0012ef60((float *)((int)__dest + 0x3c),(vec3 *)&LAB_00314170);
        }
        else if (*(int *)((int)__dest + 0x1c) != 0) {
          Assets::DestroyAssetOrDecrement(*(void **)((int)__dest + 0x88));
          *(undefined4 *)((int)__dest + 0x88) = 0;
          puVar2 = (ushort *)*param_1;
          pvVar4 = (void *)(*(int *)(puVar2 + 4) - (uint)*puVar2);
          if (__dest < pvVar4) {
            _memmove(__dest,(void *)((uint)*puVar2 + (int)__dest),(int)pvVar4 - (int)__dest);
          }
          __dest = (void *)((int)__dest + -0x94);
          local_8 = (void *)((int)local_8 - 0x94);
          *(uint *)(puVar2 + 4) = *(int *)(puVar2 + 4) - (uint)*puVar2;
        }
        __dest = (void *)((int)__dest + 0x94);
      } while (__dest < local_8);
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x00131272)


void UI::UnloadManyElements_(void)

{
  UnloadSomeElements2_();
  if (g_UIElement7 != 0) {
    UnloadElement(g_UIElement7);
    g_UIElement7 = 0;
  }
  DAT_005459fc = 0;
  _DAT_00545a04 = 0;
  _DAT_00545a0c = 0;
  DAT_00545a00 = 0;
  DAT_00545a08 = 0;
  DAT_00545a10 = 0;
  UnloadSomeElements_();
  if (g_UIElement5 != 0) {
    UnregisterScript__(g_UIElement5);
    g_UIElement5 = 0;
  }
  g_globalFlagset = g_globalFlagset & 0xfffeffff;
  PTR_00545a20 = (actor *)0x0;
  DAT_00545a18 = 0;
  DAT_00545a24 = 0;
  if (DAT_00545a1c != 0) {
    DAT_00545a1c = 0;
    DAT_00433b7c = -1;
  }
  if (g_UIElement6 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(g_UIElement6);
    g_UIElement6 = (void *)0x0;
  }
  FUN_0012e840();
  if (g_UIElement1 != 0) {
    UnloadElement(g_UIElement1);
    g_UIElement1 = 0;
  }
  FUN_00130080();
  if (PowerupUI != 0) {
    UnloadElement(PowerupUI);
    PowerupUI = 0;
  }
  if (g_UIElement3 != 0) {
    UnregisterScript__(g_UIElement3);
    g_UIElement3 = 0;
  }
  FUN_0012ef10();
  g_UIElement4 = 0;
  return;
}




void __fastcall HandleUIUpdate(void)

{
  if (g_UIElement4 != 0) {
    if ((Game::DialogState == NotInDialog) && ((g_globalFlagset & HealthAltered?) == 0)) {
      UI::DrawRandomiser();
                    // Handle level goals
      if (g_UIElement1 != 0) {
        UI::Draw2DElements(g_UIElement1);
      }
                    // UI::ImportantFunction is called inside this function again
      FUN_001323e0();
      FUN_0012d690();
    }
    if ((((g_UIElement4 != 0) && (Game::DialogState == NotInDialog)) &&
        (0x7fffffff < (uint)Cutscene::CurrentCutsceneIndex)) &&
       (((g_globalFlagset & 0x400) == 0 && ((g_globalFlagset & HealthAltered?) == 0)))) {
      LeadsToReadInput1();
      FUN_0012da10();
      FUN_0012e070();
      FUN_0012e900();
      return;
    }
  }
  return;
}




