/* scripting.c - Script engine: parse, run, free scripts */
#include "scripting.h"

BOOL Scripting::GetSetupAIDFromChapter(char *scriptName,char *outAssetName)

{
  char cVar1;
  char cVar2;
  int i;
  char *pcVar3;
  char *pcVar4;
  int local_10c;
  char local_101 [128];
  char local_81 [128];
  
  i = _strncmp(scriptName,"aid_script_ghoulies_chapter",0x1b);
  if (i == 0) {
    local_101[1] = '\0';
    pcVar4 = local_101;
    do {
      pcVar3 = pcVar4 + 1;
      pcVar4 = pcVar4 + 1;
    } while (*pcVar3 != '\0');
    pcVar3 = "aid_script_ghoulies_chapter";
    for (i = 7; i != 0; i = i + -1) {
      *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar4 = pcVar4 + 4;
    }
    pcVar4 = scriptName + 0x1b;
    cVar1 = scriptName[0x1b];
    while ((cVar1 != '\0' && (cVar1 != '_'))) {
      pcVar3 = local_101 + 1;
      do {
        cVar2 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar2 != '\0');
      pcVar4 = pcVar4 + 1;
      (pcVar3 + (-0x109 - (int)&stack0xfffffef8))[(int)&stack0x00000000] = cVar1;
      (&stack0x00000001)[(int)(pcVar3 + (-0x109 - (int)&stack0xfffffef8))] = 0;
      cVar1 = *pcVar4;
    }
    pcVar4 = local_101;
    do {
      pcVar3 = pcVar4;
      pcVar4 = pcVar3 + 1;
    } while (pcVar3[1] != '\0');
    builtin_strncpy(pcVar3 + 1,"_setup",7);
    pcVar4 = local_101 + 1;
    i = (int)outAssetName - (int)pcVar4;
    do {
      cVar1 = *pcVar4;
      pcVar4[i] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    return 1;
  }
  return 0;
}




void __fastcall Scripting::RunSetupScriptFromScriptAID(char *aid)

{
  ScriptEntry *pSVar1;
  BOOL has_setup;
  ScriptResource *setup_script;
  char setup_script_aid [128];
  
  has_setup = GetSetupAIDFromChapter(aid,setup_script_aid);
  if ((has_setup != 0) && (setup_script_aid._0_4_ == 0x5f646961)) {
    Assets::GetResourceBytes(setup_script_aid,&setup_script);
    if (setup_script == (ScriptResource *)0x0) {
      runtime::ExitGame(2);
      return;
    }
    if (Scripts->tail == Scripts->end) {
      Scripts = (Buffer<> *)runtime::ExtendArray((Buffer *)Scripts);
    }
    pSVar1 = Scripts->tail;
    Scripts->tail = (ScriptEntry *)((int)&pSVar1->currentOp + (uint)Scripts->valueSize);
    pSVar1->currentOp = setup_script;
    pSVar1->resource = setup_script;
    has_setup = RunScripts();
    if (has_setup != 0) {
      Assets::DestroyAssetOrDecrement(setup_script);
    }
  }
  return;
}




BOOL ScriptInstance::seekToOp(Script *instance,ScriptOpcode op)

{
  ScriptOperation *pSVar1;
  uint uVar2;
  ScriptOpcode opcode;
  
  opcode = (instance->currentOp->header).opcode;
  while( true ) {
    if (opcode == op) {
      return 1;
    }
    pSVar1 = instance->currentOp;
    if ((pSVar1->header).opcode == EndScript) break;
    uVar2 = (pSVar1->header).opSize;
    instance->currentOp = (ScriptOperation *)(pSVar1->data + (uVar2 - 8));
    opcode = (((ScriptOperation *)(pSVar1->data + (uVar2 - 8)))->header).opcode;
  }
  return 0;
}



// current == EndScript
// next  == EndScript    => True
// 
// next != WaitForMoveOn => False
// 
// 
// nextnext == EndScript => True
// nextnext != EndScript => False
// 
// 
// 
// or for short
// 
// return
//  Current == EndScript   ||
//  Next == EndScript   ||
//  Next != WaitForMoveOn && NextNext == EndScript
// 
// tldr: "Is there nothing more to run here?"


BOOL ScriptOperation::nothingMoreToRun(ScriptOperation *param_1)

{
  ScriptOpcode SVar1;
  ScriptOperation *next_op;
  
  if ((param_1->header).opcode != EndScript) {
    next_op = (ScriptOperation *)(param_1->data + ((param_1->header).opSize - 8));
    SVar1 = (next_op->header).opcode;
    if (SVar1 != EndScript) {
      if (SVar1 != EndBookmark) {
        return 0;
      }
                    // Return next next opcode == 0
      return (uint)(*(int *)(next_op->data + ((next_op->header).opSize - 4)) == 0);
    }
  }
  return 1;
}




void __fastcall Scripting::AddGhoulySpawnToList(GhoulyBox *box,GhoulyBoxLLHead *list)

{
  GhoulyBox *pGVar1;
  
  if (box->head != (GhoulyBoxLLHead *)0x0) {
    box->head->next = box->next;
    if (box->next != (GhoulyBox *)0x0) {
      box->next->head = box->head;
    }
    box->head = (GhoulyBoxLLHead *)0x0;
    box->next = (GhoulyBox *)0x0;
  }
  if (list != (GhoulyBoxLLHead *)0x0) {
    pGVar1 = list->next;
    while (pGVar1 != (GhoulyBox *)0x0) {
      list = (GhoulyBoxLLHead *)((GhoulyBox *)list)->next;
      pGVar1 = ((GhoulyBox *)list)->next;
    }
    ((GhoulyBox *)list)->next = box;
    box->head = list;
    box->next = (GhoulyBox *)0x0;
  }
  return;
}




void Scripting::CreateScriptType1(InputHandlerType1 **script)

{
  InputHandlerType5 *script_00;
  InputHandlerType1 *puVar1;
  int iVar1;
  
  puVar1 = malloc_(0xb0);
  *script = puVar1;
  for (iVar1 = 0x2c; iVar1 != 0; iVar1 = iVar1 + -1) {
    (puVar1->base).type = 0;
    puVar1 = (InputHandlerType1 *)&(puVar1->base).active;
  }
  ((*script)->base).active = 0;
  ((*script)->base).type = TYPE_1;
  script_00 = (InputHandlerType5 *)*script;
  switch((script_00->header).type) {
  case TYPE_1:
    InputHandlerType1::init((InputHandlerType1 *)script_00);
    return;
  case TYPE_2:
    InputHandlerType1::init((InputHandlerType1 *)script_00);
    return;
  default:
    return;
  case TYPE_4_NESTED:
    InputHandlerType4::init((InputHandlerType4 *)script_00);
    return;
  case TYPE_5:
    InputHandlerType5::init(script_00);
    return;
  }
}




void Scripting::CreateScriptType4(ScriptType4 **scriptSet)

{
  InputHandlerType5 *pIVar1;
  ScriptType4 *s;
  int iVar2;
  InputHandlerType5 **curr_scr;
  
  s = malloc_(0x18);
  *scriptSet = s;
  (s->header).type = 0;
  (s->header).active = 0;
  s->s1 = (InputHandlerType5 *)0x0;
  s->s2 = (InputHandlerType5 *)0x0;
  s->s3 = (InputHandlerType5 *)0x0;
  s->s4 = (InputHandlerType5 *)0x0;
  ((*scriptSet)->header).active = 1;
  ((*scriptSet)->header).type = TYPE_4_NESTED;
  curr_scr = &(*scriptSet)->s1;
  iVar2 = 4;
  do {
    CreateScript(curr_scr,TYPE_5);
    pIVar1 = *curr_scr;
    curr_scr = curr_scr + 1;
    iVar2 = iVar2 + -1;
    pIVar1->parent = *scriptSet;
  } while (iVar2 != 0);
  return;
}




void Scripting::FreeScript4(ScriptType4 *script)

{
  InputHandlerBase *pIVar1;
  undefined4 uVar2;
  HeapTableEntry *pHVar3;
  int i;
  ScriptType4 *paVar4;
  
  (script->header).active = 0;
  paVar4 = (ScriptType4 *)&script->s1;
  i = 4;
  do {
    pIVar1 = (InputHandlerBase *)(paVar4->header).type;
    if (pIVar1 != (InputHandlerBase *)0x0) {
      FreeScriptInner(pIVar1);
      (paVar4->header).type = 0;
    }
    paVar4 = (ScriptType4 *)&(paVar4->header).active;
    i = i + -1;
  } while (i != 0);
  i = FindHeapOf(script);
  uVar2 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[i].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + i;
  }
  runtime::CurrentHeapToAllocateFrom = i;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,script);
  runtime::CurrentHeapToAllocateFrom = uVar2;
  return;
}




void Scripting::CreateScriptType5(InputHandlerType5 **script)

{
  InputHandlerType5 *s;
  int iVar1;
  InputHandlerType5 *ns;
  
  s = malloc_(0xbc);
  *script = s;
  for (iVar1 = 0x2f; iVar1 != 0; iVar1 = iVar1 + -1) {
    (s->header).type = 0;
    s = (InputHandlerType5 *)&(s->header).active;
  }
  ((*script)->header).active = 0;
  ((*script)->header).type = TYPE_5;
  ns = *script;
  ns->handle2_ = 0;
  ns->handle1_ = 0xffffffff;
  ns = *script;
  switch((ns->header).type) {
  case TYPE_1:
    InputHandlerType1::init((InputHandlerType1 *)ns);
    return;
  case TYPE_2:
    InputHandlerType1::init((InputHandlerType1 *)ns);
    return;
  default:
    return;
  case TYPE_4_NESTED:
    InputHandlerType4::init((InputHandlerType4 *)ns);
    return;
  case TYPE_5:
    InputHandlerType5::init(ns);
    return;
  }
}




void Scripting::FreeScript5(ScriptType4 *param_1)

{
  InputHandlerType5 *pIVar1;
  
  pIVar1 = param_1->s1;
  (param_1->header).active = 0;
  if (pIVar1 == (InputHandlerType5 *)0xffffffff) {
    free(param_1);
    return;
  }
  *(undefined4 *)&param_1->s2[0xc].field_0x90 = 0;
  FUN_00107a40(param_1[7].s3);
  return;
}




void Scripting::CreateScriptType2(InputHandlerType4 **script)

{
  InputHandlerType5 *script_00;
  InputHandlerType4 *pIVar1;
  int i;
  InputHandlerType4 *paVar1;
  
  pIVar1 = malloc_(0xb0);
  *script = pIVar1;
  for (i = 44; i != 0; i = i + -1) {
    (pIVar1->header).type = 0;
    pIVar1 = (InputHandlerType4 *)&(pIVar1->header).active;
  }
  ((*script)->header).active = 1;
  ((*script)->header).type = TYPE_2;
  script_00 = (InputHandlerType5 *)*script;
  switch((script_00->header).type) {
  case TYPE_1:
                    // If script type is 1 or 2, use the clear for those types
    InputHandlerType1::init((InputHandlerType1 *)script_00);
    return;
  case TYPE_2:
    InputHandlerType1::init((InputHandlerType1 *)script_00);
    return;
  default:
    return;
  case TYPE_4_NESTED:
                    // If the script is *4, that means its got multiple scripts on it. Load the
                    // inner scripts
    InputHandlerType4::init((InputHandlerType4 *)script_00);
    return;
  case TYPE_5:
                    // If the script type is 5, use a different init function (clashes with cases 1
                    // and 2)
    InputHandlerType5::init(script_00);
    return;
  }
}




void Scripting::FreeScript123(InputHandlerBase *param_1)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  param_1->active = 0;
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




void Scripting::CreateInputHandler3(InputHandlerType3 **script)

{
  InputHandlerType3 *s;
  InputHandlerType3 *ns;
  
  s = malloc_(8);
  *script = s;
  (s->header).type = 0;
  (s->header).active = 0;
  ((*script)->header).active = 1;
  ((*script)->header).type = TYPE_3;
  ns = *script;
  switch((ns->header).type) {
  case TYPE_1:
    InputHandlerType1::init((InputHandlerType1 *)ns);
    return;
  case TYPE_2:
    InputHandlerType1::init((InputHandlerType1 *)ns);
    return;
  default:
    return;
  case TYPE_4_NESTED:
    InputHandlerType4::init((InputHandlerType4 *)ns);
    return;
  case TYPE_5:
    InputHandlerType5::init((InputHandlerType5 *)ns);
    return;
  }
}




void Scripting::CreateScript(void **param_1,InputHandlerType scriptType)

{
  switch(scriptType) {
  case TYPE_1:
    CreateScriptType1(param_1);
    return;
  case TYPE_2:
    CreateScriptType2(param_1);
    return;
  case TYPE_3:
    CreateInputHandler3(param_1);
    return;
  case TYPE_4_NESTED:
    CreateScriptType4(param_1);
    return;
  case TYPE_5:
    CreateScriptType5(param_1);
  }
  return;
}




void Scripting::FreeScriptInner(InputHandlerBase *param_1)

{
  switch(param_1->type) {
  case TYPE_1:
    FreeScript123(param_1);
    return;
  case TYPE_2:
    FreeScript123(param_1);
    return;
  case TYPE_3:
    FreeScript123(param_1);
    return;
  case TYPE_4_NESTED:
    FreeScript4((ScriptType4 *)param_1);
    return;
  case TYPE_5:
    FreeScript5((ScriptType4 *)param_1);
    return;
  default:
    return;
  }
}




void ScriptType1::getControllerXY(InputHandlerType1 *param_1,vec2 *param_2)

{
  GamepadState *pGVar1;
  GamepadState *pGVar2;
  int iVar3;
  GamepadState **ppGVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  
  iVar3 = (param_1->base).type - TYPE_1;
  switch(iVar3) {
  case 0:
  case 1:
  case 2:
  case 4:
                    // WARNING: Could not recover jumptable at 0x001088e3. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)(&PTR_LAB_00108a88)[iVar3])();
    return;
  case 3:
    ppGVar4 = &param_1->field1_0x8;
    iVar3 = 4;
    break;
  default:
    param_2->y = 0.0;
    param_2->x = 0.0;
    return;
  }
  do {
    pGVar1 = *ppGVar4;
    pGVar2 = (GamepadState *)&pGVar1->normRsx;
    fVar6 = 0.0;
    fVar7 = 0.0;
    if (pGVar1->normRsx == -NAN) {
LAB_001089c6:
      if (0.0 <= fVar7) goto LAB_001089cb;
LAB_001089a8:
      fVar7 = (fVar7 - -9800.0) * -4.3668122e-05 * -1.0;
      if (-1.0 <= fVar7) {
        bVar5 = fVar7 < 0.0;
        goto LAB_001089e9;
      }
      fVar7 = -1.0;
    }
    else {
      switch(pGVar1->normLsx) {
      case 1.4013e-45:
      case 2.8026e-45:
        break;
      case 4.2039e-45:
        pGVar2 = &Gamepad::CombinedState;
        break;
      default:
        pGVar2 = (GamepadState *)0x0;
        break;
      case 7.00649e-45:
        pGVar2 = (GamepadState *)&pGVar1->dpadX;
      }
      fVar7 = pGVar2->normRsy;
      fVar6 = pGVar2->normRsx;
      if (fVar7 <= 32700.0) {
        if (-32700.0 <= fVar7) goto LAB_001089c6;
        fVar7 = -32700.0;
        goto LAB_001089a8;
      }
      fVar7 = 32700.0;
LAB_001089cb:
      fVar7 = (fVar7 - 9800.0) * 4.3668122e-05;
      if (fVar7 <= 1.0) {
        bVar5 = 0.0 < fVar7;
LAB_001089e9:
        if (!bVar5 && fVar7 != 0.0) {
          fVar7 = 0.0;
        }
      }
      else {
        fVar7 = 1.0;
      }
    }
    if (fVar6 <= 32700.0) {
      if (-32700.0 <= fVar6) {
        if (0.0 <= fVar6) goto LAB_00108a2b;
      }
      else {
        fVar6 = -32700.0;
      }
      fVar6 = (fVar6 - -9800.0) * -4.3668122e-05 * -1.0;
      if (-1.0 <= fVar6) {
        bVar5 = fVar6 < 0.0;
        goto LAB_00108a49;
      }
      fVar6 = -1.0;
    }
    else {
      fVar6 = 32700.0;
LAB_00108a2b:
      fVar6 = (fVar6 - 9800.0) * 4.3668122e-05;
      if (fVar6 <= 1.0) {
        bVar5 = 0.0 < fVar6;
LAB_00108a49:
        if (!bVar5 && fVar6 != 0.0) {
          fVar6 = 0.0;
        }
      }
      else {
        fVar6 = 1.0;
      }
    }
    ppGVar4 = ppGVar4 + 1;
    iVar3 = iVar3 + -1;
    param_2->x = fVar6;
    param_2->y = fVar7;
    if (iVar3 == 0) {
      return;
    }
  } while( true );
}




void Scripting::PopInputHandler(void)

{
  Script2TypeNode **ppSVar1;
  InputHandlerType1 *pIVar2;
  Buffer<> *pBVar3;
  char *__dest;
  uint uVar4;
  Script2TypeNode *prev;
  
  pBVar3 = ::Input::InputHandlers;
  uVar4 = (uint)::Input::InputHandlers->valueSize;
  __dest = ::Input::InputHandlers->head->handlerName + (::Input::NumInputHandlers - 1) * uVar4 + -4;
  ppSVar1 = &::Input::InputHandlers->tail;
  if (__dest < (undefined1 *)((int)*ppSVar1 - uVar4)) {
    _memmove(__dest,__dest + uVar4,(int)((int)*ppSVar1 - uVar4) - (int)__dest);
  }
  *ppSVar1 = (Script2TypeNode *)((int)*ppSVar1 - (uint)pBVar3->valueSize);
  uVar4 = ::Input::NumInputHandlers - 1;
  if (((int)::Input::InputHandlers->tail - (int)::Input::InputHandlers->head) /
      (int)(uint)::Input::InputHandlers->valueSize != 0) {
    prev = (Script2TypeNode *)
           (::Input::InputHandlers->head->handlerName +
           (::Input::NumInputHandlers - 2) * (uint)::Input::InputHandlers->valueSize + -4);
    ::Input::NumInputHandlers = ::Input::NumInputHandlers - 1;
    runtime::SetCurrentInputHandler(prev->handlerName);
    pIVar2 = (InputHandlerType1 *)prev->next;
    uVar4 = ::Input::NumInputHandlers;
    switch((pIVar2->base).type) {
    case TYPE_1:
      ClearScriptType1(pIVar2);
      return;
    case TYPE_2:
      FUN_00107ec0((InputHandlerType4 *)pIVar2);
      return;
    case TYPE_5:
      FUN_00107c30();
      uVar4 = ::Input::NumInputHandlers;
    }
  }
  ::Input::NumInputHandlers = uVar4;
  return;
}




Script2TypeNode * runtime::GetInputHandlerByName(char *param_1)

{
  Script2TypeNode *node;
  byte bVar2;
  byte bVar3;
  char *iVar4;
  char *node_name;
  
  node = Input::InputHandlers->head;
                    // If size > 0
  if (node < Input::InputHandlers->tail) {
    iVar4 = param_1 + (-4 - (int)node);
    do {
      node_name = node->handlerName;
      while( true ) {
        bVar2 = *node_name;
                    // To uppercase
                    // 
        if (0x20 < bVar2) {
          bVar2 = bVar2 & 0b11011111;
        }
        bVar3 = node_name[(int)iVar4];
        if (0x20 < bVar3) {
          bVar3 = bVar3 & 0xdf;
        }
        if (bVar2 != bVar3) break;
        node_name = node_name + 1;
        if (bVar2 == 0) {
          return node;
        }
      }
      if (bVar2 == bVar3) {
        return node;
      }
      node = node + 1;
      iVar4 = iVar4 + -0x50;
    } while (node < Input::InputHandlers->tail);
  }
  return (Script2TypeNode *)0x0;
}




int Scripting::ScriptHeaderIndexFromAID(char *name)

{
  char cVar1;
  int i;
  BOOL BVar2;
  uint uVar3;
  AssetScriptHeader *name1;
  asset_name asset_namee;
  
  if (OverrideScriptHeader._0_4_ == 0x5f646961) {
    i = 0;
    do {
      cVar1 = OverrideScriptHeader[i];
      asset_namee[i] = cVar1;
      i = i + 1;
    } while (cVar1 != '\0');
    OverrideScriptHeader[0] = '\0';
    OverrideScriptHeader[1] = 'i';
    OverrideScriptHeader[2] = 'd';
    OverrideScriptHeader[3] = '_';
  }
  else {
    i = -(int)name;
    do {
      cVar1 = *name;
      name[(int)(asset_namee + i)] = cVar1;
      name = name + 1;
    } while (cVar1 != '\0');
  }
  i = 0;
  name1 = g_scriptHeaders;
  uVar3 = 0;
  do {
    BVar2 = Assets::AssetNamesMatch(name1->aid,asset_namee);
    if (BVar2 != 0) {
      return i;
    }
    uVar3 = uVar3 + 0x90;
    i = i + 1;
    name1 = name1 + 1;
  } while (uVar3 < 0x5e80);
  return 0;
}




void Scripting::SetCurrentPlaycamScript(void)

{
  int index;
  
  index = ScriptHeaderIndexFromAID(Game::GameState.currentSceneScript);
  g_currentPlaycamScriptHeader = g_scriptHeaders + index;
  return;
}




void Events::Scripting::RunScriptConditionsCallback2(void)

{
  Something0x20 *pSVar1;
  Something0x20 *i;
  
  FUN_00140e30();
  if (::Scripting::ScriptConditions != (Buffer<> *)0x0) {
    pSVar1 = ::Scripting::ScriptConditions->tail;
    for (i = ::Scripting::ScriptConditions->head; i < pSVar1; i = i + 1) {
      (*(code *)::Scripting::ScriptConditionCallbacks[*(int *)i].callback2)(i);
    }
  }
  ::Scripting::updateLevelScript();
  return;
}



// WARNING: Unable to use type for symbol pNVar3
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Scripting::updateLevelScript(void)

{
  actor_conflict5 *paVar1;
  BOOL stillHaveScripts;
  asset_name *nextPlaycam;
  float fVar2;
  undefined4 newChapterState;
  Message local_24;
  actor_0x93c_conflict5 pNVar3;
  weapon_conflict7 *weapon;
  
  if (GoToNextLevelScript == 0) {
    if (Bookmark != 0) {
      SeekScriptToBookmark(LoadedResource,BookmarkGroup,Bookmark);
      Bookmark = 0;
    }
    if (numScriptConditions == 0) {
      CheckScriptConditions();
      stillHaveScripts = RunScripts();
      if (stillHaveScripts != 0) {
        CheckLevelExits = 1;
        goto LAB_001171a7;
      }
    }
    if (CheckLevelExits != 0) {
LAB_001171a7:
      nextPlaycam = Assets::GetEntryAfterInTable
                              ((asset_name **)&Assets::SceneOrderAHandle,
                               Game::GameState.currentSceneScript,1);
      pNVar3 = Game::SceneInfo.playerActors.prev;
      if (nextPlaycam != (asset_name *)0x0) {
        if (PlayerExitedBox == 0) {
          setNextPlaycamScriptAID(1,*nextPlaycam);
          g_timeStandingInExit = 0.0;
        }
        else {
          if ((Game::SceneInfo.playerActors.prev != (actor_0x93c_conflict5)0x0) &&
             (paVar1 = ADJ(Game::SceneInfo.playerActors.prev), paVar1 != (actor_conflict5 *)0x0)) {
            weapon = ADJ(Game::SceneInfo.playerActors.prev)->body->weapon;
            if (weapon != (weapon_conflict7 *)0x0) {
              weapon->skipDestroyMsg = 1;
                    // Destroy the players weapon
              FUN_0001b6b0((actorBody *)ADJ(pNVar3)->body);
            }
            CreateSetDroneActionMessage((Actor_SetDroneActionMessage *)&local_24);
            local_24.header.someActor = (actor *)0x8;
            (*((paVar1->avatar).object.vtable)->onMessage)(paVar1,&local_24);
          }
          g_timeStandingInExit = 1.0;
        }
      }
      GoToNextLevelScript = 1;
      numScriptConditions = numScriptConditions + 1;
      return;
    }
  }
  else {
    if (runtime::dx_timer <= 0.0) {
      fVar2 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar2 = 0.0;
    }
    if ((0.0 < g_timeStandingInExit) &&
       (g_timeStandingInExit = g_timeStandingInExit - fVar2, g_timeStandingInExit <= 0.0)) {
      newChapterState = 1;
      g_timeStandingInExit = 0.0;
      nextPlaycam = Assets::GetEntryAfterInTable
                              ((asset_name **)&Assets::SceneOrderAHandle,
                               Game::GameState.currentSceneScript,1);
      setNextPlaycamScriptAID(newChapterState,*nextPlaycam);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Scripting::SetBackground(char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (int)BackgroundAID - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Scripting::SetPlayerObjParams(uint32_t param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  PlayerObjectParamsId = param_1;
  if (param_2 != (char *)0x0) {
    iVar2 = (int)Game::PlayerObjParamsAID - (int)param_2;
    do {
      cVar1 = *param_2;
      param_2[iVar2] = cVar1;
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
    return;
  }
  Game::PlayerObjParamsAID[0] = '\0';
  return;
}




void Scripting::CheckScriptConditions(void)

{
  Something0x20 **ppSVar1;
  ScriptResource *pSVar2;
  ScriptEntry *pSVar3;
  Buffer<> *pBVar4;
  int success;
  Something0x20 *str;
  Something0x20 *pSVar5;
  ScriptCondition *dst;
  
  if (ScriptConditions != (Buffer<> *)0x0) {
    pSVar5 = ScriptConditions->tail;
    dst = (ScriptCondition *)ScriptConditions->head;
    if (dst < pSVar5) {
      do {
        success = (*(code *)ScriptConditionCallbacks[*(int *)dst].runCheck)(dst);
        if (success != 0) {
          pSVar2 = *(ScriptResource **)&((Something0x20 *)dst)->field_0x4;
          if (Scripts->tail == Scripts->end) {
            Scripts = (Buffer<> *)runtime::ExtendArray((Buffer *)Scripts);
          }
          pSVar3 = Scripts->tail;
          Scripts->tail = (ScriptEntry *)((int)&pSVar3->currentOp + (uint)Scripts->valueSize);
          pSVar3->currentOp = pSVar2;
          pSVar3->resource = pSVar2;
          pBVar4 = ScriptConditions;
          if (success == 1) {
            ppSVar1 = &ScriptConditions->tail;
            str = (Something0x20 *)((int)ScriptConditions->tail - (uint)ScriptConditions->valueSize)
            ;
            if (dst < str) {
              memcpy(dst,str,(uint)ScriptConditions->valueSize);
            }
            dst = (ScriptCondition *)((int)dst + -0x20);
            *ppSVar1 = (Something0x20 *)((int)*ppSVar1 - (uint)pBVar4->valueSize);
            pSVar5 = pSVar5 + -1;
          }
        }
        dst = dst + 4;
      } while (dst < pSVar5);
    }
  }
  return;
}




ScriptCondition * Scripting::newScriptCondition(ScriptCondition *cond)

{
  Something0x20 *dst;
  
  if (ScriptConditions->tail == *(Something0x20 **)ScriptConditions->values) {
    ScriptConditions = (Buffer<> *)runtime::ExtendArray((Buffer *)ScriptConditions);
  }
  dst = ScriptConditions->tail;
  ScriptConditions->tail =
       (Something0x20 *)((int)&dst->field_0x0 + (uint)ScriptConditions->valueSize);
  memcpy(dst,cond,ScriptConditionParams_ARRAY_00314258[cond->id].size);
  return cond;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ScriptReturnCode Scripting::Handler::handler2(Script *instance)

{
  actor_0x934_conflict5 *ppNVar1;
  actor_conflict5 *paVar2;
  undefined1 index;
  undefined1 valueToSearch;
  ScriptOperation *pSVar3;
  Model *pMVar4;
  uint uVar5;
  objTag oVar6;
  actor_0x934_conflict5 pNVar7;
  ScriptOpcode stype;
  
  pSVar3 = instance->currentOp;
  stype = (pSVar3->header).opcode;
  if (stype == U0x12) {
    Events::UpdateActionBeginEnds(0xff,(uint)(*(int *)pSVar3->data != 0));
  }
  else if (stype == U0x90) {
    uVar5 = Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,pSVar3->data);
    if (uVar5 == 0xffffffff) {
      oVar6 = Null;
    }
    else {
      oVar6 = (short)uVar5 + Actor;
    }
    pNVar7 = Game::SceneInfo.actors_0x934.head;
    if (Game::SceneInfo.actors_0x934.head != (actor_0x934_conflict5)0x0) {
      do {
        paVar2 = ADJ(pNVar7);
        if ((ADJ(pNVar7).avatar.object.tag == oVar6) &&
           (pickup::DetachFromActor
                      ((entityStatePickup *)ADJ(pNVar7).avatar.statePickUp,(actor *)paVar2),
           *(int *)&ADJ(pNVar7).avatar.field_0x908 == 0)) {
          instance = (Script *)0x80;
          (*((paVar2->avatar).object.vtable)->onMessage)(paVar2,&instance);
          if (*(int *)&ADJ(pNVar7).avatar.field_0x908 == 0) {
            removeavatarfromsomelistsshit(paVar2);
          }
        }
        ppNVar1 = &pNVar7->next;
        pNVar7 = *ppNVar1;
      } while (*ppNVar1 != (actor_0x934_conflict5)0x0);
      return Continue;
    }
  }
  else {
    if (stype != U0x9f) {
      return SkipHandler;
    }
    uVar5 = Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,pSVar3->data);
    if (uVar5 == 0xffffffff) {
      instance = (Script *)0x0;
    }
    else {
      instance = (Script *)(uVar5 + 1);
    }
    pNVar7 = Game::SceneInfo.actors_0x934.head;
    if (Game::SceneInfo.actors_0x934.head != (actor_0x934_conflict5)0x0) {
      do {
        if (ADJ(pNVar7).avatar.object.tag == (objTag)instance) {
          index = pSVar3->data[0x40];
          valueToSearch = pSVar3->data[0x44];
          pMVar4 = ADJ(pNVar7).avatar.modelInstance;
          if (pMVar4 != (Model *)0x0) {
            ModelInstance::searchForValueWithFlags(valueToSearch,pMVar4,index);
          }
          pMVar4 = ADJ(pNVar7).avatar.shadowModel;
          if (pMVar4 != (Model *)0x0) {
            ModelInstance::searchForValueWithFlags(valueToSearch,pMVar4,index);
          }
        }
        ppNVar1 = &pNVar7->next;
        pNVar7 = *ppNVar1;
      } while (*ppNVar1 != (actor_0x934_conflict5)0x0);
      return Continue;
    }
  }
  return Continue;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


ScriptReturnCode Scripting::Handler::handle_0x32_0x38(Script *param_1)

{
  ScriptOperation *pSVar1;
  ushort uVar2;
  
  pSVar1 = param_1->currentOp;
  switch((pSVar1->header).opcode) {
  case Group1_0x32:
    DAT_0050e568 = *(undefined4 *)pSVar1->data;
    return Continue;
  case Group1_0x33:
    DAT_0050e56c = *(undefined4 *)pSVar1->data;
    return Continue;
  case Group1_0x34:
    uVar2 = GetActorTagIndex(pSVar1->data + 4);
    (&DAT_0050e570)[uVar2] = *(undefined4 *)pSVar1->data;
    return Continue;
  case Group1_0x35:
    DAT_0050e570 = *(undefined4 *)pSVar1->data;
    return Continue;
  case Group1_0x36:
    uVar2 = GetActorTagIndex(pSVar1->data + 4);
    *(undefined4 *)(&DAT_0050e660 + (uint)uVar2 * 4) = *(undefined4 *)pSVar1->data;
    return Continue;
  case Group1_0x37:
    _DAT_0050e754 = *(float *)pSVar1->data * 0.01;
    return Continue;
  case Group1_0x38:
    _DAT_0050e758 = *(undefined4 *)pSVar1->data;
    return Continue;
  default:
    return SkipHandler;
  }
}




ScriptReturnCode Scripting::Handler::handle_0x5d_0x71(int *param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  iVar1 = *param_1;
  if (*(int *)(iVar1 + 4) == 0x5d) {
    param_1 = (int *)0x1;
    uVar3 = Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,(char *)(iVar1 + 8));
    if (uVar3 == 0xffffffff) {
      FUN_00122ca0();
      return Continue;
    }
    FUN_00122ca0();
  }
  else {
    if (*(int *)(iVar1 + 4) != 0x71) {
      return SkipHandler;
    }
    piVar2 = (int *)Game::OnSceneBegin(*(short *)(iVar1 + 8));
    if (piVar2 != (int *)0x0) {
      param_1 = (int *)0x13;
      (**(code **)(*piVar2 + 0xc))(piVar2,&param_1);
      return Continue;
    }
  }
  return Continue;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Scripting::Handler::handler0x98(Script *instance,BOOL flag)

{
  GlobalBackgroundEntry *pGVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  ScriptOperation *pSVar4;
  undefined4 uVar5;
  Model *pMVar6;
  background_0x934_conflict3 pEVar7;
  undefined1 uVar8;
  
  pSVar4 = instance->currentOp;
  if ((pSVar4->header).opcode != (U0x90|UpdateSomethingByTag0x8)) {
    return 3;
  }
  pEVar7 = Game::SceneInfo.backgrounds.head;
  if (flag != 0) {
    for (; pEVar7 != (background_0x934_conflict3)0x0; pEVar7 = pEVar7->next) {
      uVar2 = pSVar4->data[0];
      pMVar6 = ADJ(pEVar7).avatar.modelInstance;
      uVar3 = pSVar4->data[4];
      if (pMVar6 != (Model *)0x0) {
        ModelInstance::searchForValueWithFlags(uVar3,pMVar6,uVar2);
      }
      pMVar6 = ADJ(pEVar7).avatar.shadowModel;
      if (pMVar6 != (Model *)0x0) {
        ModelInstance::searchForValueWithFlags(uVar3,pMVar6,uVar2);
      }
    }
    return 2;
  }
  uVar2 = pSVar4->data[1];
  uVar3 = pSVar4->data[2];
  uVar8 = pSVar4->data[3];
  pGVar1 = GlobalBackgroundEntry_ARRAY_00512350 + Game::BackgroundEntriesToSetUp;
  pGVar1->entryIndex = pSVar4->data[0];
  pGVar1->field1_0x1 = uVar2;
  pGVar1->field2_0x2 = uVar3;
  pGVar1->field3_0x3 = uVar8;
  uVar5 = *(undefined4 *)(pSVar4->data + 4);
  pGVar1 = GlobalBackgroundEntry_ARRAY_00512350 + Game::BackgroundEntriesToSetUp;
  pGVar1->shadowIndex = (char)uVar5;
  pGVar1->field5_0x5 = (char)((uint)uVar5 >> 8);
  pGVar1->field6_0x6 = (char)((uint)uVar5 >> 0x10);
  pGVar1->field7_0x7 = (char)((uint)uVar5 >> 0x18);
  Game::BackgroundEntriesToSetUp = Game::BackgroundEntriesToSetUp + 1;
  return 2;
}



// WARNING: Removing unreachable block (ram,0x001250e8)
// WARNING: Removing unreachable block (ram,0x00125155)
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Scripting::Handler::CheckChallengeLogic0x7a_0x86(Script *instance)

{
  ScriptOperation *pSVar1;
  ushort uVar3;
  challengeId uVar2;
  undefined4 local_10 [2];
  undefined4 local_8;
  undefined4 local_4;
  
  pSVar1 = instance->currentOp;
  switch((pSVar1->header).opcode) {
  case SetChallengeId:
    uVar2 = Events::GetIndexOfStringInTable(9,EventLoop::ChallengeIDNames,pSVar1->data);
    FUN_0004a100(uVar2);
    return 2;
  case Group20x7b:
    FUN_0004a240();
    return 2;
  case Group20x7c:
    local_10[0] = 0x10;
    local_8 = 0;
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x7d:
    local_8 = *(undefined4 *)pSVar1->data;
    local_10[0] = 0x11;
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x7e:
    local_10[0] = 5;
    break;
  case Group20x7f:
    uVar3 = GetActorTagIndex(pSVar1->data);
    if (uVar3 == 0) {
      return 2;
    }
    local_10[0] = 9;
    uVar3 = GetActorTagIndex(pSVar1->data);
    local_8 = CONCAT22(local_8._2_2_,uVar3);
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x80:
    local_10[0] = 10;
    uVar3 = GetActorTagIndex(pSVar1->data);
    local_4 = *(undefined4 *)(pSVar1->data + 0x40);
    local_8 = CONCAT22(local_8._2_2_,uVar3);
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x81:
    local_10[0] = 0x12;
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x82:
    local_10[0] = 4;
    break;
  case Group20x83:
    local_8 = *(undefined4 *)pSVar1->data;
    local_10[0] = 0xb;
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x84:
    local_10[0] = 0xc;
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x85:
    local_10[0] = 0;
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  case Group20x86:
    local_10[0] = 3;
    EventLoop::SolidifyNewChallengeFromId(local_10);
    return 2;
  default:
    return 3;
  }
  uVar3 = GetActorTagIndex(pSVar1->data);
  local_8 = CONCAT22(local_8._2_2_,uVar3);
  EventLoop::SolidifyNewChallengeFromId(local_10);
  return 2;
}




ScriptReturnCode Scripting::Handler::addCondition(Script *instance)

{
  uint uVar1;
  ushort uVar2;
  ScriptCondition cond_type;
  uint local_18;
  uint local_14;
  uint local_10;
  undefined4 local_c;
  PlayerEntersRegionOperation *op;
  
  op = (PlayerEntersRegionOperation *)instance->currentOp;
  switch((op->header).opcode) {
  case EndCondition:
    return End;
  case TimeoutCondition:
    local_18 = (uint)(float)(int)op->field1_0x8;
    local_14 = *(uint *)&op->field_0xc;
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = TimeOut;
    break;
  case NumberGhouliesAliveCondition:
    local_18 = op->field1_0x8;
    local_14 = *(uint *)&op->field_0xc;
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = NumberGhouliesAlive;
    break;
  case ScareSourceProximityCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = ScareSourceProximity;
    break;
  case ObjectPickedUpCondition:
    cond_type.id = ObjectPickedUp;
    goto LAB_001257ae;
  case NumberGhouliesKilledCondition:
    local_14 = *(uint *)&op->field_0xc;
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    local_18 = op->field1_0x8;
    local_10 = 0;
    local_c = 0;
    cond_type.id = NumberGhouliesKilled;
    break;
  case NumberOfKnockdownsCondition:
    cond_type.id = NumberOfKnockdowns;
    goto LAB_00125623;
  case PlayerApproachesDoorCondition:
    local_14 = *(uint *)&op->field_0xc;
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = PlayerApproachesDoor;
    local_18 = (uint)(ushort)op->field1_0x8;
    break;
  case HauntedObjectActivatedCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    local_18 = 0;
    cond_type.id = HauntedObjectActivated;
    uVar2 = GetActorTagIndex(&op->field1_0x8);
    local_18 = CONCAT22(local_18._2_2_,uVar2);
    break;
  default:
    return SkipHandler;
  case PlayerEntersRegionCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    local_18 = op->field1_0x8;
    cond_type.id = PlayerEntersRegion;
    break;
  case PlayerLeavesRegionCondition:
    local_18 = op->field1_0x8;
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = PlayerLeavesRegion;
    break;
  case SpecificGhouliesAliveCondition:
    uVar1 = (op->header).opSize;
    local_18 = op->field1_0x8;
    cond_type.id = SpecificGhouliesAlive;
    goto LAB_00125640;
  case SpecificGhouliesKilledCondition:
    cond_type.id = SpecificGhouliesKilled;
LAB_00125623:
    uVar1 = (op->header).opSize;
    local_18 = op->field1_0x8;
LAB_00125640:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + uVar1);
    local_10 = 0;
    local_14 = 0;
    uVar2 = GetActorTagIndex(&op->field_0xc);
    local_10 = *(uint *)&op[4].field_0xc;
    local_14 = CONCAT22(local_14._2_2_,uVar2);
    break;
  case ObjectByMarkerRemovedCondition:
    local_14 = *(uint *)&op->field_0xc;
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    local_18 = op->field1_0x8;
    cond_type.id = ObjectByMarkerRemoved;
    break;
  case PlayerDeflectionContactCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = PlayerDeflectionContact;
    goto LAB_001257bc;
  case PlayerHitGhoulyCondition:
    cond_type.id = PlayerHitGhouly;
    goto LAB_001257ae;
  case GhoulyTriggeredCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    cond_type.id = GhoulyTriggered;
    uVar2 = GetActorTagIndex(&op->field1_0x8);
    local_14 = op[4].field1_0x8;
    local_10 = *(uint *)&op[4].field_0xc;
    local_18 = CONCAT22(local_18._2_2_,uVar2);
    break;
  case GhoulyExistsInSceneCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = GhoulyExistsInScene;
    goto LAB_001257bc;
  case ObjectByMarkerBrokenCondition:
    FUN_001253f0((int)&(op->header).opSize + (op->header).opSize,&cond_type);
    local_18 = op->field1_0x8;
    local_10 = op[1].header.opSize;
    local_14 = *(uint *)&op->field_0xc;
    break;
  case ActorHasNoEnergyCondition:
    cond_type.id = ActorHasNoEnergy;
LAB_001257ae:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
LAB_001257bc:
    local_14 = 0;
    local_18 = 0;
    uVar2 = GetActorTagIndex(&op->field1_0x8);
    local_14 = op[4].field1_0x8;
    local_18 = CONCAT22(local_18._2_2_,uVar2);
    break;
  case EveryNthKillCondition:
    FUN_00125420((int)&(op->header).opSize + (op->header).opSize);
    local_18 = op->field1_0x8;
    uVar2 = GetActorTagIndex(&op->field_0xc);
    local_10 = *(uint *)&op[4].field_0xc;
    local_14 = CONCAT22(local_14._2_2_,uVar2);
    break;
  case NoGhoulySpawnsActiveCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = NoGhoulySpawnsActive;
    break;
  case Challenge21ActiveCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = IsChallenge21Active;
    break;
  case Challenge21NotActiveCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = IsChallenge21NotActive;
    break;
  case GhoulyEntersRegionCondition:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    local_18 = 0;
    local_14 = 0;
    cond_type.id = GhoulyEntersRegion;
    uVar2 = GetActorTagIndex(&op->field1_0x8);
    local_18 = CONCAT22(local_18._2_2_,uVar2);
    local_14 = op[4].field1_0x8;
    break;
  case GhoulyEntersRegionCondition|SetBackground:
    cond_type.id = GhoulyHasEnergyLEQ;
    goto LAB_00125873;
  case GhoulySignalCondition:
    cond_type.id = GhoulySignal;
LAB_00125873:
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    local_18 = 0;
    local_14 = 0;
    uVar2 = GetActorTagIndex(&op->field1_0x8);
    local_14 = op[4].field1_0x8;
    local_18 = CONCAT22(local_18._2_2_,uVar2);
    break;
  case ObjectByMarkerNotBrokenCondition:
    local_18 = op->field1_0x8;
    cond_type.opToRun = (ScriptOperation *)((int)&(op->header).opSize + (op->header).opSize);
    cond_type.id = ObjectByMarkerNotBroken;
  }
  newScriptCondition(&cond_type);
  ScriptInstance::seekToOp(instance,EndCondition);
  return Continue;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ScriptReturnCode Scripting::Handler::updateRoom(Script *instance,BOOL flag1,BOOL flag2)

{
  ScriptOpcode SVar1;
  Script *pSVar2;
  BOOL nothingToRun;
  int door_i;
  UpdateDoorOperation *op;
  UpdateDoorOperation *pSVar1;
  
  pSVar1 = (UpdateDoorOperation *)instance->currentOp;
  SVar1 = (pSVar1->header).opcode;
  if (SVar1 != UpdateDoor) {
    if (SVar1 == U0x4f) {
      if (flag1 == 0) {
        (&DAT_005123b0)[g_someIndex * 4] = pSVar1->doorId;
        (&DAT_005123b4)[g_someIndex * 2] = *(undefined4 *)&pSVar1->isClosed;
        g_someIndex = g_someIndex + 1;
        return Continue;
      }
      FUN_001117e0(pSVar1->doorId);
      return Continue;
    }
    if (SVar1 == U0x56) {
      FUN_00122f70();
      return Continue;
    }
    return SkipHandler;
  }
                    // Handle Op 0x29
  if ((flag1 != 0) && (flag2 == 0)) {
    if (CheckIfMoreToRun == 0) {
      nothingToRun = ScriptOperation::nothingMoreToRun((ScriptOperation *)pSVar1);
      UpdateDoor(pSVar1->doorId,pSVar1->isClosed,pSVar1->field8_0x14,nothingToRun);
      if (pSVar1->field7_0x10 == 0) {
        return Continue;
      }
      Events::UpdateActionBeginEnds(0xff,0);
      CheckIfMoreToRun = 1;
    }
    else {
      door_i = FUN_0005b780(&instance);
      pSVar2 = (Script *)0x8;
      if (door_i != 0) {
        pSVar2 = instance;
      }
      if (((uint)pSVar2 & 0xffff) == *(uint *)&pSVar1->isClosed) {
        Events::UpdateActionBeginEnds(0xff,1);
        CheckIfMoreToRun = 0;
        return Continue;
      }
    }
    return Halt;
  }
  door_i = 0;
                    // Find door where id matches first value in data
  if (0 < Game::NumDoors) {
    do {
      if ((uint)Game::Doors[door_i].id == *(uint *)&pSVar1->doorId) break;
      door_i = door_i + 1;
    } while (door_i < Game::NumDoors);
  }
  Game::Doors[door_i].id = pSVar1->doorId;
  Game::Doors[door_i].isShut = pSVar1->isClosed;
  if (Game::NumDoors <= door_i) {
    Game::NumDoors = Game::NumDoors + 1;
  }
  return Continue;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ScriptReturnCode Scripting::Handler::newChallenge(Script *instance,BOOL b1,BOOL b2)

{
  ChallengeType CVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  ChallengeDetails challenge_details;
  TimeLimitChallenge TStack_c8;
  ChallengeType CStack_ac;
  TimeLimitChallenge TStack_a8;
  undefined4 uStack_8c;
  TimeLimitChallenge aTStack_88 [2];
  byte local_3c;
  ScriptOperation *op;
  ScriptOpcode opcode;
  
  op = instance->currentOp;
  opcode = (op->header).opcode;
                    // Requires opcode < 0x88
  if (0x71 < opcode - PlayEventIntro) {
switchD_00126164_caseD_24:
    return SkipHandler;
  }
  uVar4 = (uint)*(byte *)((int)&PTR_caseD_50_001268b4 + opcode + SetBackground);
  switch(opcode) {
  case PlayEventIntro:
    if (b2 == 0) {
      if (*(int *)(op->data + 8) != 0) {
        ExitChallenge_();
      }
      EventLoop::CreateNewChallengeList(*(ushort *)op->data,*(uint *)(op->data + 4),op->data + 0xc);
      return Continue;
    }
    break;
  case EndDescribingChallenge:
    if (DAT_00512414 == 0) {
      StartEventsSequence();
      DAT_00512414 = 1;
    }
    else if (g_pauseMenuState_ == Paused) {
      DAT_00512414 = 0;
      return Continue;
    }
    break;
  case CreateKillAllChallenge:
    FUN_00125c80(uVar4,&challenge_details);
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case CreateTimeLimitChallenge:
    Challenge::GetChallengeDetails(&challenge_details,0);
    challenge_details.data = *(uint *)op->data;
    if (((undefined1)g_globalFlagset & GrimReaperAlive) != 0) {
      return Continue;
    }
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case CreateXChallenge:
    FUN_00125cc0(uVar4,&challenge_details.index);
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case CreateKillAllByTagChallenge:
    FUN_00125d00();
    uVar2 = GetActorTagIndex(op->data);
    TStack_c8.length = (float)CONCAT22(TStack_c8.length._2_2_,uVar2);
    CStack_ac = (ChallengeType)(*(int *)(op->data + 0x40) == 0);
    CreateNewChallenge(&TStack_c8);
    return Continue;
  case CreateKillNByTagChallenge:
    FUN_00125d40();
    TStack_c8.length = (float)FUN_0001bb60();
    uVar2 = GetActorTagIndex(op->data + 8);
    CStack_ac = CONCAT22(CStack_ac._2_2_,uVar2);
    CreateNewChallenge(&TStack_c8);
    return Continue;
  case CreateKillAllByTagChallenge|AddSceneControl:
    FUN_00125dc0();
    challenge_details.data = *(uint *)op->data;
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case CreateFindTheGhoulieKeyChallenge:
    FUN_00126040();
    CreateNewChallenge(aTStack_88);
    return Continue;
  case 0x20:
    FUN_00125e00();
    TStack_c8.length = (float)(uint)*(ushort *)op->data;
    CreateNewChallenge(&TStack_c8);
    return Continue;
  case CreateDontKillByTagChallenge:
    FUN_00125e40();
    uVar2 = GetActorTagIndex(op->data);
    TStack_c8.length = (float)CONCAT22(TStack_c8.length._2_2_,uVar2);
    CStack_ac = 0xffffffff;
    CreateNewChallenge(&TStack_c8);
    return Continue;
  case 0x22:
    FUN_00125f00();
    challenge_details.data = 0xffffffff;
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case CreateWeaponsOnlyChallenge:
    FUN_00125ec0();
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  default:
    goto switchD_00126164_caseD_24;
  case CreateNextOneDifferentChallenge:
    FUN_00125e80();
    aTStack_88[0].length._0_2_ = 0;
    if (*(int *)(op->data + 0x40) != 0) {
      uVar2 = GetActorTagIndex(op->data);
      *(ushort *)((int)&aTStack_88[0].length + (uint)local_3c * 2 + 2) = uVar2;
      local_3c = local_3c + 1;
    }
    if (*(int *)(op->data + 0x84) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x44);
      *(ushort *)((int)&aTStack_88[0].length + (uint)local_3c * 2 + 2) = uVar2;
      local_3c = local_3c + 1;
    }
    if (*(int *)(op->data + 200) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x88);
      *(ushort *)((int)&aTStack_88[0].length + (uint)local_3c * 2 + 2) = uVar2;
      local_3c = local_3c + 1;
    }
    if (*(int *)(op->data + 0x10c) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0xcc);
      *(ushort *)((int)&aTStack_88[0].length + (uint)local_3c * 2 + 2) = uVar2;
      local_3c = local_3c + 1;
    }
    if (*(int *)(op->data + 0x150) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x110);
      *(ushort *)((int)&aTStack_88[0].length + (uint)local_3c * 2 + 2) = uVar2;
      local_3c = local_3c + 1;
    }
    CreateNewChallenge(aTStack_88);
    return Continue;
  case 0x26:
    FUN_00125f40();
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case CreateFindTheKeyChallenge:
    FUN_00126080();
    challenge_details.data = *(uint *)op->data;
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case CreateNoBreakHouseChallenge:
    FUN_00125f80();
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case 0x50:
    FUN_00125fc0();
    bVar5 = *(int *)(op->data + 0x40) != 0;
    if (bVar5) {
      challenge_details.index._0_2_ = GetActorTagIndex(op->data);
    }
    uVar4 = (uint)bVar5;
    if (*(int *)(op->data + 0x84) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x44);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
      uVar4 = uVar4 + 1;
    }
    if (*(int *)(op->data + 200) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x88);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
      uVar4 = uVar4 + 1;
    }
    if (*(int *)(op->data + 0x10c) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0xcc);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
      uVar4 = uVar4 + 1;
    }
    if (*(int *)(op->data + 0x150) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x110);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
    }
    iVar3 = FUN_0001bb60();
    TStack_a8.length._0_2_ = *(undefined2 *)((int)&challenge_details.index + iVar3 * 2);
    if (*(int *)(op->data + 0x154) != 0) {
      FUN_00126940(0);
    }
    uStack_8c = 0;
    CreateNewChallenge(&TStack_a8);
    FUN_00116c50();
    return Continue;
  case ObjectPickedUpCondition|ShowDialogByName:
    ChallengeFloats.field4_0x10 = *(float *)(op->data + 0x10);
    ChallengeFloats.reaperFloat1 = *(float *)op->data;
    ChallengeFloats.reaperFloat2 = *(float *)(op->data + 4);
    ChallengeFloats.field2_0x8 = *(float *)(op->data + 8);
    ChallengeFloats.field3_0xc = *(float *)(op->data + 0xc);
    return Continue;
  case Unknown0x5c|AddSceneControl|SetBackground:
    FUN_00126000();
    challenge_details.data = FUN_0001bb60();
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case Group20x86|SetBackground:
    FUN_001260c0();
    CreateNewChallenge((TimeLimitChallenge *)&challenge_details);
    return Continue;
  case Group20x80|UpdateSomethingByTag0x8:
    FUN_00126100();
    bVar5 = *(int *)(op->data + 0x44) != 0;
    if (bVar5) {
      challenge_details.index._0_2_ = GetActorTagIndex(op->data);
      TStack_a8.challengeType = *(ChallengeType *)(op->data + 0x40);
    }
    uVar4 = (uint)bVar5;
    if (*(int *)(op->data + 0x8c) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x48);
      CVar1 = *(ChallengeType *)(op->data + 0x88);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
      (&TStack_a8.challengeType)[uVar4] = CVar1;
      uVar4 = uVar4 + 1;
    }
    if (*(int *)(op->data + 0xd4) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x90);
      CVar1 = *(ChallengeType *)(op->data + 0xd0);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
      (&TStack_a8.challengeType)[uVar4] = CVar1;
      uVar4 = uVar4 + 1;
    }
    if (*(int *)(op->data + 0x11c) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0xd8);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
      (&TStack_a8.challengeType)[uVar4] = *(ChallengeType *)(op->data + 0x118);
      uVar4 = uVar4 + 1;
    }
    if (*(int *)(op->data + 0x164) != 0) {
      uVar2 = GetActorTagIndex(op->data + 0x120);
      CVar1 = *(ChallengeType *)(op->data + 0x160);
      *(ushort *)((int)&challenge_details.index + uVar4 * 2) = uVar2;
      (&TStack_a8.challengeType)[uVar4] = CVar1;
    }
    iVar3 = FUN_0001bb60();
    CStack_ac = (&TStack_a8.challengeType)[iVar3];
    TStack_c8.length =
         (float)CONCAT22(TStack_c8.length._2_2_,
                         *(undefined2 *)((int)&challenge_details.index + iVar3 * 2));
    if (*(int *)(op->data + 0x168) != 0) {
      FUN_00126940(0);
    }
    CreateNewChallenge(&TStack_c8);
    FUN_00116c50();
    return Continue;
  }
  return Halt;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Scripting::Handler::SetGlobalFlag(Script *param_1)

{
  ScriptOperation *pSVar1;
  ScriptOpcode SVar2;
  
  pSVar1 = param_1->currentOp;
  SVar2 = (pSVar1->header).opcode;
  if (SVar2 == SetGlobalFlag1) {
    g_globalFlagset = g_globalFlagset | *(GlobalFlagset *)pSVar1->data;
    return 2;
  }
  if (SVar2 != SetGlobalFlag2) {
    return 3;
  }
  g_globalFlagset = g_globalFlagset & ~*(uint *)pSVar1->data;
  return 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ScriptReturnCode Scripting::Handler::SpawnGhoulieWithBox(Script *instance)

{
  actor_0x934_conflict5 *ppNVar1;
  actor_0x944 *ppNVar2;
  actor *av;
  ScriptOperation *pSVar3;
  actorMind *paVar4;
  objTag oVar5;
  ushort uVar6;
  BOOL success;
  uint uVar7;
  Script *pSVar8;
  uint32_t uVar9;
  undefined2 extraout_var_00;
  actor_0x934_conflict5 pNVar10;
  actor_0x944 pNVar11;
  undefined4 uVar12;
  undefined4 local_2c;
  undefined4 local_28;
  Message local_24;
  vec3 local_1c;
  vec3 local_10;
  undefined4 local_4;
  ScriptOperation *opp;
  undefined2 extraout_var;
  ScriptOpcode opcode;
  
  pSVar3 = instance->currentOp;
  opcode = (pSVar3->header).opcode;
  if (0x6d < opcode - SpawnGhoulyWithBox) {
switchD_00126a33_caseD_2c:
    return SkipHandler;
  }
  switch(opcode) {
  case SpawnGhoulyWithBox:
    if (WaitForGhoulyBoxToOpen == 0) {
      Assets::OpenBoxFromAid
                ((uint)*(byte *)((int)&switchD_00126a33::switchdataD_00126d68 +
                                opcode + AddSceneControl),pSVar3->data,
                 *(uint *)(pSVar3->data + 0x80),pSVar3->data + 0x84);
      if (*(int *)(pSVar3->data + 0x104) == 0) {
        return Continue;
      }
                    // Check it next frame
      WaitForGhoulyBoxToOpen = 1;
    }
    else {
                    // When door is broken it goes here
      success = Game::AllGhoulyBoxesFinishedOpening();
      if (success != 0) {
        WaitForGhoulyBoxToOpen = 0;
        return Continue;
      }
    }
    return Halt;
  case ExecuteGhoulyspawn:
    game::execute_ghouly_spawn(pSVar3->data);
    return Continue;
  default:
    goto switchD_00126a33_caseD_2c;
  case ObjectPickedUpCondition|MoveOn:
    instance = (Script *)0x1;
    oVar5 = GetActorTagIndex(pSVar3->data);
    pNVar10 = Game::SceneInfo.actors_0x934.head;
    if (Game::SceneInfo.actors_0x934.head != (actor_0x934_conflict5)0x0) {
      do {
        if ((ADJ(pNVar10).avatar.object.tag == oVar5) &&
           ((*(uint *)(pSVar3->data + 0x40) == 0 ||
            (*(uint *)(pSVar3->data + 0x40) == (uint)ADJ(pNVar10).avatar.field237_0x1fc)))) {
          (*(ADJ(pNVar10).avatar.object.vtable)->onMessage)(ADJ(pNVar10),&instance);
        }
        ppNVar1 = &pNVar10->next;
        pNVar10 = *ppNVar1;
      } while (*ppNVar1 != (actor_0x934_conflict5)0x0);
      return Continue;
    }
    break;
  case ObjectPickedUpCondition|EndDescribingChallenge:
    local_28 = 0;
    local_2c = 0x65;
    uVar7 = FUN_0002b710((int)(pSVar3->data + 0x40));
    local_28 = CONCAT22(local_28._2_2_,(short)uVar7);
    GetActorTagIndex(pSVar3->data);
    FUN_00122d40();
    return Continue;
  case Unknown0x5c:
    instance = (Script *)0x36;
    GetActorTagIndex(pSVar3->data);
    FUN_00122d40();
    return Continue;
  case Unknown0x5c|AddSceneControl:
    uVar12 = *(undefined4 *)(pSVar3->data + 0x44);
    uVar6 = GetActorTagIndex(pSVar3->data);
    FUN_000f4930(uVar6,uVar12);
    return Continue;
  case GhoulyTriggeredCondition|SetBackground:
    uVar6 = GetActorTagIndex(pSVar3->data);
    pSVar8 = (Script *)CONCAT22(extraout_var,uVar6);
    pNVar11 = Game::SceneInfo.enemies;
    instance = pSVar8;
    if (Game::SceneInfo.enemies != (actor_0x944)0x0) {
      do {
        if (((objTag)pSVar8 < Actor_Baron) || (ADJ(pNVar11).avatar.tag == (objTag)pSVar8)) {
          ADJ(pNVar11)->randTraitoristicCombat = pSVar3->data[0x40];
          paVar4 = ADJ(pNVar11)->mind;
          if ((paVar4 != (actorMind *)0x0) &&
             ((paVar4->targetBody != (actorBody *)0x0 &&
              (uVar9 = actorMind::doTraitorStuffOrFight(paVar4,paVar4->targetBody,1), uVar9 == 0))))
          {
            paVar4 = ADJ(pNVar11)->mind;
            if (paVar4->targetBody != (actorBody *)0x0) {
              local_2c = 100;
              local_28 = 0;
              (*((paVar4->actor->avatar).vtable)->onMessage)(paVar4->actor,&local_2c);
            }
            paVar4->targetBody = (actorBody *)0x0;
            pSVar8 = instance;
          }
        }
        ppNVar2 = &pNVar11->next;
        pNVar11 = *ppNVar2;
      } while (*ppNVar2 != (actor_0x944)0x0);
      return Continue;
    }
    break;
  case ObjectPickedUpCondition|Signal0x30:
    GetActorTagIndex(pSVar3->data);
    FUN_0010f6c0();
    return Continue;
  case ObjectPickedUpCondition|Group1_0x38:
    oVar5 = GetActorTagIndex(pSVar3->data);
    pNVar11 = Game::SceneInfo.enemies;
    if (Game::SceneInfo.enemies != (actor_0x944)0x0) {
      do {
        if ((oVar5 < Actor_Baron) || (ADJ(pNVar11).avatar.tag == oVar5)) {
          FUN_00019660(*(undefined4 *)(pSVar3->data + 0x40));
        }
        ppNVar2 = &pNVar11->next;
        pNVar11 = *ppNVar2;
      } while (*ppNVar2 != (actor_0x944)0x0);
      return Continue;
    }
    break;
  case GhoulyEntersRegionCondition|AddSceneControl|SetBackground:
    uVar6 = GetActorTagIndex(pSVar3->data);
    pSVar8 = (Script *)CONCAT22(extraout_var_00,uVar6);
    instance = pSVar8;
    for (pNVar11 = Game::SceneInfo.enemies; pNVar11 != (actor_0x944)0x0; pNVar11 = pNVar11->next) {
      av = ADJ(pNVar11);
      if (((objTag)pSVar8 < Actor_Baron) || (ADJ(pNVar11).avatar.tag == (objTag)pSVar8)) {
        ::actor::drone(av);
        ADJ(pNVar11)->droneTriggerId = Null;
        local_1c.x = 0.0;
        local_1c.y = 0.0;
        local_1c.z = 0.0;
        local_10.x = 0.0;
        local_10.y = 0.0;
        local_10.z = 0.0;
        local_4 = 0;
        local_24.header.msgId = Actor_SetDroneAction;
        local_24.header.someActor = *(actor **)(pSVar3->data + 0x40);
        avatar::getWorldPosition(&av->avatar,&local_1c);
        avatar::getWorldRotation(&av->avatar,&local_10);
        (*((av->avatar).vtable)->onMessage)(av,&local_24);
        pSVar8 = instance;
      }
    }
  }
  return Continue;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Scripting::Handler::SetPositions_(Script *param_1,BOOL param_2)

{
  Marker *pMVar1;
  ScriptOperation *pSVar2;
  uint uVar3;
  ushort uVar4;
  ushort markerId;
  BOOL BVar5;
  avatar *paVar6;
  int iVar7;
  undefined4 uVar8;
  Marker *pMVar9;
  uint uVar10;
  vec3 local_18;
  vec3 local_c;
  
  pSVar2 = param_1->currentOp;
  switch((pSVar2->header).opcode) {
  case U0x4c|SetBackground:
    paVar6 = (avatar *)Game::OnSceneBegin(*(short *)pSVar2->data);
    if (paVar6 != (avatar *)0x0) {
      avatar::getWorldRotation(paVar6,&local_18);
      avatar::getWorldPosition(paVar6,&local_c);
      local_18.y = *(float *)(pSVar2->data + 0x84) * 0.017453292 + local_18.y;
      FUN_00112c50((paVar6->scale).z);
      avatar::destroy(paVar6);
      return 2;
    }
    break;
  case U0x4c|AddSceneControl:
    BVar5 = Random::thresholdCheck(&runtime::rand,*(float *)(pSVar2->data + 8) * 0.01);
    if (BVar5 != 0) {
      FUN_001400a0(*(undefined2 *)(pSVar2->data + 4));
      return 2;
    }
    break;
  default:
    return 3;
  case 0x60:
    paVar6 = (avatar *)Game::OnSceneBegin(*(short *)pSVar2->data);
    if (paVar6 != (avatar *)0x0) {
      avatar::destroy(paVar6);
      return 2;
    }
    break;
  case 0x62:
    uVar4 = Marker::nextIdOfNextMarkerOfType(0x13,1,0);
    if (uVar4 != 0) {
      uVar3 = (Game::GameState.markerInstance)->numMarkers;
      iVar7 = *(int *)pSVar2->data;
      pMVar1 = (Game::GameState.markerInstance)->marker;
      markerId = uVar4;
      do {
        uVar10 = 0;
        pMVar9 = pMVar1;
        if (uVar3 != 0) {
          do {
            if (pMVar9->id == markerId) goto LAB_00126f9f;
            uVar10 = uVar10 + 1;
            pMVar9 = (Marker *)((int)&pMVar9->size + pMVar9->size);
          } while (uVar10 < uVar3);
        }
        pMVar9 = (Marker *)0x0;
LAB_00126f9f:
        if (*(int *)(pMVar9 + 1) == iVar7) {
          local_18.x = 0.0 - (pMVar9->eulerRot).x;
          local_18.y = (pMVar9->eulerRot).y + 3.1415927;
          local_18.z = (pMVar9->eulerRot).z;
          FUN_0013d250(&pMVar9->pos,&local_18);
          return 2;
        }
        markerId = Marker::nextIdOfNextMarkerOfType(0x13,0,markerId);
        if (markerId == uVar4) {
          return 2;
        }
        if (markerId == 0) {
          return 2;
        }
      } while( true );
    }
    break;
  case PlayerDeflectionContactCondition|SetBackground:
    if (param_2 == 0) {
      GameColliderSetupBitfield_ARRAY_00512420[Game::SomeThingsToSetUp].field0_0x0 = pSVar2->data[0]
      ;
      GameColliderSetupBitfield_ARRAY_00512420[Game::SomeThingsToSetUp].field2_0x2 =
           *(uint16_t *)(pSVar2->data + 4);
      Game::SomeThingsToSetUp = Game::SomeThingsToSetUp + 1;
      return 2;
    }
    if (*(int *)(pSVar2->data + 4) == 0) {
      Collision::RunColliderCallbackOnAllAvatars(pSVar2->data[0],Collider::removeFlags,4);
      return 2;
    }
    Collision::RunColliderCallbackOnAllAvatars(pSVar2->data[0],Collider::addFlags,4);
    FUN_00122ce0();
    return 2;
  case GhoulyExistsInSceneCondition|AddSceneControl:
    FUN_001249b0();
    return 2;
  case ObjectByMarkerBrokenCondition|SetBackground:
    FUN_001400d0(*(undefined2 *)(pSVar2->data + 4),*(undefined2 *)(pSVar2->data + 8),
                 *(undefined2 *)(pSVar2->data + 0xc),*(undefined2 *)(pSVar2->data + 0x10),
                 *(undefined2 *)(pSVar2->data + 0x14),*(undefined2 *)(pSVar2->data + 0x18),
                 *(undefined2 *)(pSVar2->data + 0x1c),*(undefined2 *)(pSVar2->data + 0x20),
                 *(undefined2 *)(pSVar2->data + 0x24));
    return 2;
  case ObjectPickedUpCondition|Group1_0x34:
    FUN_00115f40();
    return 2;
  case NoGhoulySpawnsActiveCondition|AddSceneControl:
    FUN_001189d0(*(undefined4 *)(pSVar2->data + 8),*(undefined4 *)(pSVar2->data + 0xc),
                 *(undefined4 *)(pSVar2->data + 0x10));
    return 2;
  case U0x90|U0xc|SetBackground:
    iVar7 = FUN_00049d10();
    if ((iVar7 == 0) && (iVar7 = FUN_000f2a20(), iVar7 != 0)) {
      Game::Save.numPrisoners = Game::Save.numPrisoners + 1;
      FUN_0012d7e0(Game::Save.numPrisoners);
      return 2;
    }
    break;
  case U0x90|Bookmark:
    if (*(int *)(pSVar2->data + 8) != 0) {
      (&DAT_00512448)[DAT_00512444] = *(undefined4 *)pSVar2->data;
      uVar8 = FUN_000f29a0();
      (&DAT_0051245c)[DAT_00512444] = uVar8;
      DAT_00512444 = DAT_00512444 + 1;
    }
    if (*(int *)(pSVar2->data + 4) != 0) {
      FUN_000f29d0();
      return 2;
    }
    FUN_000f29f0();
  }
  return 2;
}




undefined4 Scripting::Handler::AudioHandlers(Script *param_1)

{
  ScriptOperation *pSVar1;
  AudioPlayingContext *pAVar2;
  AudioPlayingContext *pAVar3;
  int iVar4;
  
  pSVar1 = param_1->currentOp;
  switch((pSVar1->header).opcode) {
  case Group1_0x38|AddSceneControl:
    FUN_00116d20(3);
    return 2;
  case Signal0x3b:
    if (Audio::SomeGlobalPlayingContext[0] != '\0') {
      pAVar2 = Audio::GetPlayingContext(Audio::SomeGlobalPlayingContext);
      iVar4 = pAVar2->numReferences + -1;
      pAVar2->numReferences = iVar4;
      if (iVar4 < 1) {
        if ((pAVar2->playFlags != 0b00010010) &&
           (pAVar3 = Audio::GetSomePlayingThing(pAVar2), pAVar3 != (AudioPlayingContext *)0x0)) {
          AudioPlayingContext::updateSomething(pAVar3);
        }
        FUN_00038260(pAVar2);
        pAVar2->playFlags = 0;
      }
      Audio::SomeGlobalPlayingContext[0] = '\0';
      return 2;
    }
    break;
  default:
    return 3;
  case Signal0x45:
    if (DAT_0050e560 == 0) {
      FUN_00116c90();
      DAT_0050e560 = 1;
      return 2;
    }
    break;
  case PlayMusicByActorTag :
    GetActorTagIndex(pSVar1->data);
    FUN_00116c50();
    return 2;
  case U0x56|SetBackground:
    FUN_00116d20(2);
    return 2;
  case PlaySound:
    Audio::loadAudioIntoEmptySlot(6,pSVar1->data);
  }
  return 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

ScriptReturnCode

Scripting::Handler::runCutscenes(Script *instance,undefined4 param_2,int inACutscene_)

{
  GlobalFlagset GVar1;
  ushort uVar2;
  ushort marker_id;
  BOOL in_ctsc;
  BOOL done;
  int iVar3;
  undefined4 uVar4;
  Cutscene *csb;
  uint uVar5;
  objParams *params;
  char *pcVar6;
  char *pcVar7;
  undefined4 *puVar8;
  byte bVar9;
  vec3 eulers;
  vec3 pos;
  undefined4 local_108 [7];
  undefined4 local_ea [24];
  char local_88 [29];
  undefined4 local_6b;
  PlayCutsceneOperation *op;
  
  op = (PlayCutsceneOperation *)instance->currentOp;
  switch((op->header).opcode) {
  case PlayCutscene:
    if (inACutscene_ == 0) {
      if (InACutscene_ == 0) {
        iVar3 = FUN_00087830();
        if (iVar3 == 2) {
          pcVar6 = "aid_model_ghoulies_actor_boy";
          pcVar7 = local_88;
          for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
            *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar7 = pcVar7 + 4;
          }
          *pcVar7 = *pcVar6;
          puVar8 = &local_6b;
          for (iVar3 = 0x18; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar8 = 0;
            puVar8 = puVar8 + 1;
          }
          *(undefined2 *)puVar8 = 0;
          *(undefined1 *)((int)puVar8 + 2) = 0;
          pcVar6 = "aid_model_ghoulies_actor_girl";
          puVar8 = local_108;
          for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar8 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            puVar8 = puVar8 + 1;
          }
          *(undefined2 *)puVar8 = *(undefined2 *)pcVar6;
          puVar8 = local_ea;
          for (iVar3 = 0x18; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar8 = 0;
            puVar8 = puVar8 + 1;
          }
          *(undefined2 *)puVar8 = 0;
          FUN_0004e610();
        }
                    // Where cutscene load begins in a level
                    // 
                    // Also runs zombie cutscene in scullery
        Cutscene::LoadFromLevel
                  (op->cutsceneAID,(uint)(Game::CheckMoveOn == 3),(uint)(Game::CheckMoveOn == 3));
        if (op->someFlag != 0) {
          InACutscene_ = 1;
          if (op[1].header.opSize == 0) {
            bVar9 = 0xff;
          }
          else {
            bVar9 = 2;
          }
          Events::UpdateActionBeginEnds(bVar9,0);
          iVar3 = FUN_000f2bb0();
          if ((iVar3 == 0) || (iVar3 = FUN_00049d10(), iVar3 != 0)) {
            LoadCutsceneSkip();
          }
          return Halt;
        }
      }
      else {
        in_ctsc = Cutscene::InACutscene();
        if (in_ctsc == 0) {
          if (g_successfullyLoadedCutsceneSkip == 0) {
            return Halt;
          }
          iVar3 = FUN_00127b10();
          if (iVar3 == 0) {
            return Halt;
          }
        }
        done = ScriptOperation::nothingMoreToRun(instance->currentOp);
        if (done == 0) {
          InACutscene_ = done;
          Cutscene::SetCutsceneCam();
          if (op[1].header.opSize == 0) {
            bVar9 = 0xff;
          }
          else {
            bVar9 = 2;
          }
          Events::UpdateActionBeginEnds(bVar9,1);
          if (Game::DialogState != NotInDialog) {
            FUN_000583a0();
          }
          if (g_successfullyLoadedCutsceneSkip != 0) {
            FreeScript();
            return Continue;
          }
        }
      }
    }
    break;
  case ShowDialogByName:
    if (inACutscene_ != 0) {
      return Continue;
    }
    if (DAT_00512474 != 0) {
      if (Game::DialogState != NotInDialog) {
        return Halt;
      }
      Events::UpdateActionBeginEnds(0xff,1);
      DAT_00512474 = 0;
      return Continue;
    }
    uVar2 = GetActorTagIndex(op->cutsceneAID);
    if ((1 < uVar2) && (iVar3 = FUN_001291a0(uVar2,0), iVar3 == 0)) {
      return Continue;
    }
    if ((op[1].header.opSize != 0) && (iVar3 = FUN_00049d10(), iVar3 != 0)) {
      return Continue;
    }
    if (op[1].header.opcode != EndScript) {
      if (*(int *)op[1].cutsceneAID == 0) {
        GVar1 = g_globalFlagset & 0x8000000;
      }
      else {
        if (*(int *)op[1].cutsceneAID != 1) goto LAB_0012770d;
        GVar1 = g_globalFlagset & 0x10000000;
      }
      if (GVar1 != 0) {
        return Continue;
      }
    }
LAB_0012770d:
    iVar3 = FUN_000fbf90();
    if (iVar3 != 0) {
      if (op->someFlag != 0) {
        uVar4 = FUN_0001bb60();
        _sprintf(&TempAIDBuffer,"%s%d",op->cutsceneAID + 0x40,uVar4);
      }
      iVar3 = Events::BeginDialogSequence(0);
      if (iVar3 != 0) {
        Events::UpdateActionBeginEnds(0xff,0);
        DAT_00512474 = 1;
        if (op[1].header.opcode != EndScript) {
          if (*(int *)op[1].cutsceneAID == 0) {
            g_globalFlagset = g_globalFlagset | 0x8000000;
          }
          else if (*(int *)op[1].cutsceneAID == 1) {
            g_globalFlagset = g_globalFlagset | 0x10000000;
            return Halt;
          }
        }
      }
      return Halt;
    }
    break;
  case ShowDialogByName|SetBackground:
    FUN_00106d50((char)op->someFlag,op[1].header.opSize,1);
    FUN_00106dd0();
    return Continue;
  case ShowDialogByName|AddSceneControl:
    if (inACutscene_ == 0) {
      if (InACutscene_ != 0) {
        in_ctsc = Cutscene::InACutscene();
        if (in_ctsc == 0) {
          return Halt;
        }
        InACutscene_ = 0;
        Cutscene::SetCutsceneCam();
        return Continue;
      }
      if (op[1].header.opSize != 0) {
        InACutscene_ = 1;
        return Halt;
      }
    }
    break;
  default:
    return SkipHandler;
  case PlayWalkinCutscene:
    if (inACutscene_ == 0) {
      if (InACutscene_ == 0) {
        csb = (Cutscene *)Cutscene::LoadFromLevel(op->cutsceneAID,0,1);
        uVar5 = Cutscene::getEventIdFromModelName(csb,"aid_model_ghoulies_cutscene_reliccandle");
        if (uVar5 == 0) {
          SceneControl_Candle = (sceneControlObj *)0x0;
        }
        else {
          params = Assets::GetObjParams("aid_objparams_ghoulies_scenecontrol_candle");
          params[1].paramsSize = (short)uVar5;
          params[1].objInitValue = (short)(uVar5 >> 0x10);
          SceneControl_Candle = (sceneControlObj *)Assets::CreateEntityFromParams(params);
          free(params);
        }
        marker_id = Marker::nextIdOfNextMarkerOfType(StartingPosition,1,0);
        if (marker_id != BAD_MARKER) {
          Marker::GetPosByIndex(marker_id,&pos);
          Marker::getEulersByIndex(marker_id,&eulers);
          Math::AddAnglesUnwrapped(3.1415927,eulers.y);
          FUN_0004ef20(&pos);
          Cutscene::RerenderFromEulerAngles(&eulers);
        }
        InACutscene_ = 1;
      }
      else {
        in_ctsc = Cutscene::InACutscene();
        if (in_ctsc != 0) {
          in_ctsc = ScriptOperation::nothingMoreToRun((ScriptOperation *)op);
          if (in_ctsc != 0) {
            return Continue;
          }
          InACutscene_ = 0;
          Cutscene::SetCutsceneCam();
                    // Spawn player at the end of a cutscene
          SpawnThePlayerFromMarker();
          if (SceneControl_Candle == (sceneControlObj *)0x0) {
            return Continue;
          }
          FUN_00116140();
          SceneControl_Candle = (sceneControlObj *)0x0;
          return Continue;
        }
      }
      return Halt;
    }
    break;
  case U0x90|U0xb:
    if ((Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) ||
       (ADJ(Game::SceneInfo.playerActors.prev) == (actor_conflict5 *)0x0)) {
      eulers.z = 0.0;
      eulers.y = 0.0;
      eulers.x = 0.0;
    }
    else {
      avatar::getWorldPosition((avatar *)ADJ(Game::SceneInfo.playerActors.prev),&eulers);
    }
    FUN_000fb120(&eulers,1.0,op->cutsceneAID);
    return Continue;
  case U0x90|U0xc:
    if ((Game::SceneInfo.playerActors.prev == (actor_0x93c_conflict5)0x0) ||
       (ADJ(Game::SceneInfo.playerActors.prev) == (actor_conflict5 *)0x0)) {
      eulers.z = 0.0;
      eulers.y = 0.0;
      eulers.x = 0.0;
    }
    else {
      avatar::getWorldPosition((avatar *)ADJ(Game::SceneInfo.playerActors.prev),&eulers);
    }
    FUN_000493d0();
  }
  return Continue;
}




void Scripting::FreeScript(void)

{
  if (g_successfullyLoadedCutsceneSkip != 0) {
    PopInputHandler();
    switch((g_someScriptType2->header).type) {
    case TYPE_1:
      FreeScript123(&g_someScriptType2->header);
      break;
    case TYPE_2:
      FreeScript123(&g_someScriptType2->header);
      break;
    case TYPE_3:
      FreeScript123(&g_someScriptType2->header);
      break;
    case TYPE_4_NESTED:
      FreeScript4((ScriptType4 *)g_someScriptType2);
      break;
    case TYPE_5:
      FreeScript5((ScriptType4 *)g_someScriptType2);
    }
    g_someScriptType2 = (InputHandlerType4 *)0x0;
    g_successfullyLoadedCutsceneSkip = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Scripting::Handler::UpdatePlayer_(Script *param_1,int param_2,int param_3)

{
  ScriptOperation *pSVar1;
  uint uVar2;
  actorDroneActionId aVar3;
  ushort markerId;
  actor *paVar4;
  int iVar5;
  actor *iVar3;
  avatar *player;
  avatar *av;
  ObjMsgID local_34;
  vec3 local_30;
  Actor_SetDroneActionMessage local_24 [4];
  
  pSVar1 = param_1->currentOp;
  switch((pSVar1->header).opcode) {
  case ProbablySpawnSomething1:
    if ((param_3 == 0) && (iVar3 = getThePlayer(), iVar3 != (actor *)0x0)) {
      FUN_0001b810(iVar3->body,0,0);
      avatar::destroy(&iVar3->avatar);
      return 2;
    }
    break;
  case SpawnPlayer:
    if (param_3 == 0) {
      SpawnThePlayerFromMarker();
      return 2;
    }
    break;
  case ProbablySpawnSomething2:
    paVar4 = getThePlayer();
    if (paVar4 != (actor *)0x0) {
      if (*(int *)pSVar1->data == 0) {
        FUN_00042090(paVar4);
        return 2;
      }
      ::actor::decrementAS23(paVar4);
      return 2;
    }
    break;
  case SetPlayerWorried:
    paVar4 = getThePlayer();
    if (paVar4 != (actor *)0x0) {
      CreateSetDroneActionMessage(local_24);
      local_24[0].droneAction = StandNervously;
      local_24[0].someShort = 0;
      (*((paVar4->avatar).vtable)->onMessage)(paVar4,local_24);
      return 2;
    }
    break;
  case Signal0x30:
    paVar4 = getThePlayer();
    if (paVar4 == (actor *)0x0) {
      return 2;
    }
    local_30.x = 0.0;
    local_34 = Actor_EndDroneAction;
    goto LAB_00127d92;
  case Signal0x30|SetBackground:
    if (param_2 == 0) {
      SetPlayerObjParams(0,pSVar1->data);
      return 2;
    }
    paVar4 = getThePlayer();
    if (paVar4 != (actor *)0x0) {
      ::actor::handleWeaponSetup(paVar4,1,pSVar1->data);
      return 2;
    }
    break;
  default:
    return 3;
  case HauntedObjectActivatedCondition|AddSceneControl:
    if (param_2 == 0) {
      PlayerObjectParamsId = 0;
      Game::PlayerObjParamsAID[0] = '\0';
      return 2;
    }
    paVar4 = getThePlayer();
    if (paVar4 != (actor *)0x0) {
      ::actor::setupScriptedCollisions(paVar4);
      FUN_0012ecc0();
      return 2;
    }
    break;
  case GhoulyExistsInSceneCondition|AddSceneControl|SetBackground:
    paVar4 = getThePlayer();
    if ((paVar4 == (actor *)0x0) ||
       ((aVar3 = ::actor::getNextDroneAction(paVar4), aVar3 != Null && (paVar4->isDroning == 0)))) {
      return 0;
    }
    break;
  case ObjectPickedUpCondition|Group1_0x36:
    paVar4 = getThePlayer();
    if (paVar4 == (actor *)0x0) {
      return 2;
    }
    local_34 = Actor_IgnoreInputs;
    local_30.x = 1.4013e-45;
    goto LAB_00127d92;
  case ObjectPickedUpCondition|Group1_0x37:
    paVar4 = getThePlayer();
    if (paVar4 == (actor *)0x0) {
      return 2;
    }
    local_34 = Actor_IgnoreInputs;
    local_30.x = 0.0;
LAB_00127d92:
    (*((paVar4->avatar).vtable)->onMessage)(paVar4,&local_34);
    break;
  case FrightenPlayer:
    player = &getThePlayer()->avatar;
    if (player != (avatar *)0x0) {
      local_30.x = 0.0;
      local_30.y = 0.0;
      local_30.z = 0.0;
      local_34 = Actor_Fright;
      av = FUN_00128df0(player,0,0.0,(vec2 *)&param_1,0x4240,(undefined *)0x0,(vec3 *)0x0);
      if (av != (avatar *)0x0) {
        avatar::getWorldPosition(av,&local_30);
      }
      (*player->vtable->onMessage)(player,&local_34);
      return 2;
    }
    break;
  case GhoulyEntersRegionCondition|AddSceneControl:
                    // Spawn from marker
    paVar4 = getThePlayer();
    if ((paVar4 != (actor *)0x0) &&
       (markerId = Marker::nextIdOfNextMarkerOfType(Player,1,0), markerId != 0)) {
      uVar2 = *(uint *)pSVar1->data;
      while (iVar5 = Marker::getMarkerById(markerId), *(ushort *)(iVar5 + 0x28) != uVar2) {
        markerId = Marker::nextIdOfNextMarkerOfType(Player,0,markerId);
        if (markerId == 0) {
          return 2;
        }
      }
      ::actor::setPosition(paVar4,(vec3 *)(iVar5 + 0xc));
      ::actor::setRotation(paVar4,(vec3 *)(iVar5 + 0x18));
    }
    return 2;
  case 0xa0:
    paVar4 = getThePlayer();
    if (paVar4 != (actor *)0x0) {
      param_1 = (Script *)0x2c;
      (*((paVar4->avatar).vtable)->onMessage)(paVar4,&param_1);
      return 2;
    }
    break;
  case 0xa6:
    if (param_2 == 0) {
      PlayerObjectParamsId = 0;
      Game::PlayerObjParamsAID[0] = '\0';
      return 2;
    }
    paVar4 = getThePlayer();
    if ((paVar4 != (actor *)0x0) && (iVar5 = FUN_0013a860(paVar4), iVar5 != 0)) {
      FUN_0012ecc0();
      return 2;
    }
  }
  return 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ScriptReturnCode Scripting::Handler::Setup(Script *instance,BOOL param_2,BOOL gameIsLoading)

{
  ScriptOperation *pSVar2;
  LoctextValueContext *pLVar3;
  objTag oVar4;
  ushort uVar5;
  objParams *params;
  actor_0x944 pNVar6;
  BOOL success;
  uint uVar7;
  undefined4 uVar8;
  float in_XMM0_Da;
  float fVar9;
  float scaleX;
  float scaleY;
  float length;
  vec3 local_3c;
  AffineTransform local_30;
  U0x61Operation *pSVar1;
  
  pSVar2 = instance->currentOp;
  switch((pSVar2->header).opcode) {
  case SetBackground:
    SetBackground(pSVar2->data);
    return Continue;
  case AddSceneControl:
    if (param_2 == 0) {
      Game::AddSceneControl(pSVar2->data);
      return Continue;
    }
    params = Assets::GetObjParams(pSVar2->data);
    if (params != (objParams *)0x0) {
      Assets::CreateEntityFromParams(params);
      free(params);
      return Continue;
    }
    break;
  default:
    return SkipHandler;
  case SetSomething0x4:
    DAT_0050ea98 = *(undefined4 *)pSVar2->data;
    return Continue;
  case U0x5:
  case U0xc:
    break;
  case SetNumSuperScaryInputs:
    Game::NumSuperScaryInputs = *(uint *)pSVar2->data;
    return Continue;
  case SetSomething0x7:
    Game::Something0x7 = *(int *)pSVar2->data;
    return Continue;
  case UpdateSomethingByTag0x8:
    oVar4 = GetActorTagIndex(pSVar2->data);
    FUN_0010f690(*(undefined4 *)(pSVar2->data + 0x40));
    pNVar6 = Game::SceneInfo.enemies;
    if (Game::SceneInfo.enemies != (actor_0x944)0x0) {
      do {
        if ((ADJ(pNVar6).avatar.tag == oVar4) && (ADJ(pNVar6)->mind != (actorMind *)0x0)) {
          ADJ(pNVar6)->mind->floatFromTagList = *(undefined4 *)(pSVar2->data + 0x40);
        }
        pNVar6 = pNVar6->next;
      } while (pNVar6 != (actor_0x944)0x0);
      return Continue;
    }
    break;
  case SetNoAttackTimer:
    uVar5 = GetActorTagIndex(pSVar2->data);
    Game::AddNoAttackTimer(uVar5,*(float *)(pSVar2->data + 0x40));
    local_3c.y = *(float *)(pSVar2->data + 0x40);
    local_3c.x = 1.09301e-43;
    FUN_00122d40();
    return Continue;
  case SetSceneName:
    if (pSVar2->data != (undefined *)0x0) {
      u__00507e78[0] = L'\0';
      success = loctext::get_text("aid_loctext_ghoulies_script_scenenames","scenenames",pSVar2->data
                                  ,u__00507e78);
      if ((success != 0) && (success = IsValidString((LPWSTR)u__00507e78), success == 0)) {
        if ((*(int *)(pSVar2->data + 0x40) != 0) && (gameIsLoading == 0)) {
          if (Game::WalkinLoctext == (LoctextValueContext *)0x0) {
            runtime::AllocateForLoctext_(0,0,(void *)0x5e4,&Game::WalkinLoctext);
            pLVar3 = Game::WalkinLoctext;
            uVar7 = runtime::rand * 0x19660d + 0x3c6ef35f;
            runtime::rand = uVar7;
            (Game::WalkinLoctext->somePos).x = 2.5;
            in_XMM0_Da = 0.5;
            (pLVar3->somePos).y = 0.5;
            pLVar3->maybeState = uVar7;
          }
          uVar8 = FUN_0005f550(*(undefined4 *)(pSVar2->data + 0x44));
          length = *(float *)(pSVar2->data + 0x48);
          fVar9 = (float)Graphics::BackbufferHeight;
          success = 0;
          scaleY = 1.5;
          scaleX = 1.5;
          Font::GetTextHeight(2.0,uVar8,0);
          LoctextValueContext::Initialise
                    (Game::WalkinLoctext,u__00507e78,(float)Graphics::BackbufferWidth * 0.5,
                     (fVar9 - in_XMM0_Da) * 0.5,scaleX,scaleY,length,success,1);
        }
        FUN_0011dcf0();
        return Continue;
      }
    }
    break;
  case U0xb:
    SetPlayerObjParams((uint)(byte)pSVar2->data[0],pSVar2->data + 1);
    return Continue;
  case U0x4b:
    FUN_000fd780();
    return Continue;
  case U0x4c:
    Audio::LoadReverbSettings(*(undefined4 *)pSVar2->data);
    return Continue;
  case U0x52:
    FUN_0012aa50(pSVar2->data);
    return Continue;
  case SetCameraProperties:
    Game::CurrentPlayerCameraIndex = *(int *)pSVar2->data;
    Game::CameraVal1 = Game::SceneFloats1[Game::CurrentPlayerCameraIndex];
    DAT_00545af0 = *(int *)(pSVar2->data + 4);
    Game::CameraVal2 = Game::SceneFloats2[Game::CurrentPlayerCameraIndex];
    DAT_00545af4 = *(int *)(pSVar2->data + 8);
    DAT_0043402c = (&FLOAT_00314e28)[*(int *)(pSVar2->data + 8)];
    DAT_00545af8 = *(int *)(pSVar2->data + 0xc);
    uint32_t_00434010 = Game::SomeFloats4[*(int *)(pSVar2->data + 4)];
    DAT_00434030 = Game::SomeFloats6[*(int *)(pSVar2->data + 0xc)];
    return Continue;
  case 100:
    local_3c.x = (float)CONCAT13(pSVar2->data[0x10],
                                 CONCAT12(pSVar2->data[0xc],
                                          CONCAT11(pSVar2->data[8],pSVar2->data[4])));
    instance = (Script *)
               (uint)CONCAT12(pSVar2->data[0x28],CONCAT11(pSVar2->data[0x24],pSVar2->data[0x20]));
    DAT_00512134 = instance;
    DAT_00512138 = (uint)(*(int *)pSVar2->data != 0);
    DAT_00512104 = *(undefined4 *)pSVar2->data;
    FUN_001236d0(local_3c.x,local_3c.x,*(undefined4 *)(pSVar2->data + 0x14),
                 *(undefined4 *)(pSVar2->data + 0x18),*(undefined4 *)(pSVar2->data + 0x1c));
    return Continue;
  case AddGhoulyByTag:
    uVar5 = GetActorTagIndex(pSVar2->data);
    g_AssetBodySearchList[Assets::NumSomethingBodies] = uVar5;
    Assets::NumSomethingBodies = Assets::NumSomethingBodies + 1;
    return Continue;
  case ObjectPickedUpCondition|U0x39:
    FUN_00114050();
    return Continue;
  case Group20x80|SetNoAttackTimer:
    DAT_00506c60 = *(float *)pSVar2->data * 60.0 + 0.99;
    FUN_000f27c0();
    return Continue;
  case Group20x80|SetSceneName:
    if (*(int *)pSVar2->data != 0) {
      Game::UseMovementSmoothing = 0;
      DAT_00509b70 = 1;
      return Continue;
    }
    Game::UseMovementSmoothing = 1;
    DAT_00509b70 = 0;
    break;
  case RotateSomethingByNDegrees:
    local_3c.x = 0.0;
    local_3c.z = 0.0;
    local_3c.y = 1.0;
    Math::GetRotationMatrix(&local_3c,*(float *)pSVar2->data * 0.0055555557 * 3.1415927,&local_30);
    local_3c.x = (local_30.m[0][0] * 0.0 - local_30.m[0][2] * 1.0) + local_30.m[0][3] +
                 local_30.m[0][1];
    local_3c.y = (local_30.m[1][0] * 0.0 - local_30.m[1][2] * 1.0) + local_30.m[1][3] +
                 local_30.m[1][1];
    local_3c.z = (local_30.m[2][0] * 0.0 - local_30.m[2][2] * 1.0) + local_30.m[2][3] +
                 local_30.m[2][1];
    Game::SetSomeVec3(&local_3c);
    return Continue;
  case U0x90|SetSceneName:
    FUN_000f2740();
    return Continue;
  case Group20x80|CreateDontKillByTagChallenge:
    FUN_000fea90();
    return Continue;
  case 0xa2:
    Game::GameState.field95_0x25c = (uint)(*(int *)pSVar2->data == 0);
    return Continue;
  case 0xa4:
    DAT_0050ef1c = (uint)(*(int *)pSVar2->data != 0);
    return Continue;
  case Group20x80|CreateNextOneDifferentChallenge:
    DAT_00510650 = (uint)(*(int *)pSVar2->data != 0);
    return Continue;
  }
  return Continue;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Scripting::Handler::finalHandler(Script *instance)

{
  ScriptOpcode SVar1;
  uint actor_tag;
  
  SVar1 = (instance->currentOp->header).opcode;
  if (SVar1 == U0x39) {
    FUN_0012d050();
    return 2;
  }
  if (SVar1 != U0x59) {
    return 3;
  }
  actor_tag = Events::GetIndexOfStringInTable(0xe9,ActorTagTable + 1,instance->currentOp->data);
  if (actor_tag == 0xffffffff) {
    deliverMessageToParam1(0);
    return 2;
  }
  deliverMessageToParam1((short)actor_tag + 1);
  return 2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL Scripting::RunScripts(void)

{
  ScriptEntry **ppSVar1;
  Buffer<> *pBVar2;
  BOOL fallthrough;
  ScriptEntry *pSVar3;
  ScriptEntry *end;
  ScriptEntry *pGVar2;
  ScriptEntry *head;
  ushort size;
  ScriptEntry *tail;
  
  if (Scripts != (Buffer<> *)0x0) {
    head = Scripts->head;
    tail = Scripts->tail;
    size = Scripts->valueSize;
    if ((Game::WalkinLoctext != (LoctextValueContext *)0x0) &&
       (Game::WalkinLoctext->buffer->tail <= Game::WalkinLoctext->buffer->head)) {
      UnregisterScript__((int)Game::WalkinLoctext);
      Game::WalkinLoctext = (LoctextValueContext *)0x0;
    }
    pGVar2 = Scripts->head;
    end = Scripts->tail + -1;
                    // Execute all scripts, starting from the tail then going inwards
    if (pGVar2 <= end) {
      while (fallthrough = Script::update((Script *)end), pBVar2 = Scripts, fallthrough != 0) {
        ppSVar1 = &Scripts->tail;
        pSVar3 = (ScriptEntry *)((int)*ppSVar1 - (uint)Scripts->valueSize);
        if (end < pSVar3) {
          _memmove(end,(void *)((int)&end->currentOp + (uint)Scripts->valueSize),
                   (int)pSVar3 - (int)end);
        }
        *ppSVar1 = (ScriptEntry *)((int)*ppSVar1 - (uint)pBVar2->valueSize);
        if ((Bookmark != 0) || (end = end + -1, end < pGVar2)) break;
      }
    }
    if ((((int)tail - (int)head) / (int)(uint)size != 0) &&
       (((int)Scripts->tail - (int)Scripts->head) / (int)(uint)Scripts->valueSize == 0)) {
      return 1;
    }
  }
  return 0;
}




BOOL Script::update(Script *this)

{
  void *pvVar1;
  int iVar2;
  ScriptReturnCode ret;
  uint j;
  BOOL inACutscene;
  
  pvVar1 = g_scriptRelatedLinkedList_;
  do {
    if (pvVar1 == (void *)0x0) {
      iVar2 = 0;
LAB_00128a24:
      if ((iVar2 != 0) ||
         (((inACutscene = 1, g_finishedLoading_ != 1 && ((*SomeAS15->flags & 8) == 0)) &&
          ((g_globalFlagset & 0x200000) == 0)))) {
        inACutscene = 0;
      }
LAB_RerunAllScripts:
      do {
                    // Execute all ops in the script
        j = 0;
        do {
          ret = (**(code **)((int)Scripting::ScriptHandlers + j))(this,iVar2 != 0,inACutscene);
                    // If we aren't skipping this handler
          if (ret != SkipHandler) {
                    // And we didn't handle it
            if (ret != Continue) {
                    // The script should have ended?
              return (uint)(ret == End);
            }
                    // Continue
            this->currentOp =
                 (ScriptOperation *)(this->currentOp->data + ((this->currentOp->header).opSize - 8))
            ;
            goto LAB_RerunAllScripts;
          }
          j = j + 4;
                    // Run all 17 handlers
        } while (j < 0x44);
        this->currentOp =
             (ScriptOperation *)(this->currentOp->data + ((this->currentOp->header).opSize - 8));
      } while( true );
    }
    if (*(int *)((int)pvVar1 + 8) == 0x7d) {
      iVar2 = (int)pvVar1 + 8;
      goto LAB_00128a24;
    }
    pvVar1 = *(void **)((int)pvVar1 + 4);
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


ScriptReturnCode Scripting::Handler::ScriptPosHandlers(Script *instance,BOOL param_2,BOOL param_3)

{
  BOOL canBookmark;
  int iVar1;
  SetPlayStateOperation *op;
  
  op = (SetPlayStateOperation *)instance->currentOp;
  switch((op->header).opcode) {
  case EndScript:
    return End;
  default:
    return SkipHandler;
  case U0xc|SetBackground:
    spawnFxAndAID(&op->skipToNext,0);
    break;
  case Bookmark:
    canBookmark = EventLoop::IsPlayStateSomething();
    if ((((op->someEnum == 1) && (canBookmark != 0)) || ((op->someEnum == 2 && (canBookmark == 0))))
       || ((op->someFlag != 0 && (iVar1 = FUN_00049d10(), iVar1 != 0)))) {
      ScriptInstance::seekToOp(instance,EndBookmark);
      return Continue;
    }
    EventLoop::SetAggressions(op->skipToNext,op->someUint2,op->eventStr);
    if ((param_3 != 0) && (op->skipToNext == 0)) {
      return Halt;
    }
    if ((param_2 == 0) && (param_3 == 0)) {
      return Halt;
    }
    break;
  case EndBookmark:
    Game::WaitingForChallenge = 0;
                    // NOT HANDLED
    if (Game::CheckedMoveOn != 0) {
      if (Game::MoveOn == 0) {
        Game::WaitingForChallenge = 1;
        return Halt;
      }
LAB_00128c9e:
      Game::MoveOn = Game::MoveOn + -1;
      return Continue;
    }
    break;
  case 0x10:
    if (param_3 == 0) {
      if (Game::MoveOn == 0) {
        return Halt;
      }
      goto LAB_00128c9e;
    }
    break;
  case MoveOn:
    if (param_3 == 0) {
      Game::MoveOn = Game::MoveOn + 1;
      return Continue;
    }
    break;
  case GoToBookmark:
    Bookmark = op->someUint2;
    BookmarkGroup = op->skipToNext;
    return Continue;
  }
  return Continue;
}




void Scripting::SeekScriptToBookmark(ScriptResource *res,int preBookmark,int bookmark)

{
  uint uVar1;
  ScriptEntry *script;
  ScriptOpcode opcode;
  
  for (script = Scripts->head; script < Scripts->tail;
      script = (ScriptEntry *)((int)&script->currentOp + (uint)Scripts->valueSize)) {
    if (script->resource == res) goto LAB_00128db2;
  }
  script = (ScriptEntry *)0x0;
LAB_00128db2:
  opcode = res->operations[0].header.opcode;
  if (opcode != EndScript) {
                    // While we aren't at a bookmark,
                    // 
                    // 
                    // (!opcode == bookmark || pre != prebook) || bookmark doesn't match
                    // 
                    // OR the bookmark we are at doesn't match the pre-bookmark 
                    // OR the bookmark doesn't match the bookmark
    while (((opcode != Bookmark || (*(int *)res->operations[0].data != preBookmark)) ||
           (*(int *)(res->operations[0].data + 4) != bookmark))) {
      uVar1 = res->operations[0].header.opSize;
      opcode = *(ScriptOpcode *)(res->operations[0].data + (uVar1 - 4));
      res = (ScriptResource *)(res->operations[0].data + (uVar1 - 8));
      if (opcode == EndScript) {
        return;
      }
    }
    script->currentOp = res;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

avatar * FUN_00128df0(avatar *param_1,short param_2,float param_3,vec2 *param_4,undefined4 param_5,
                     undefined *param_6,vec3 *param_7)

{
  int iVar1;
  actor_conflict5 *paVar2;
  actor_conflict5 *av;
  float10 fVar3;
  float fVar4;
  actor_conflict5 *local_24;
  actor_0x934_conflict5 local_20;
  vec3 local_18;
  vec3 local_c;
  
  paVar2 = (actor_conflict5 *)0x0;
  local_24 = (actor_conflict5 *)0x0;
  if (param_7 == (vec3 *)0x0) {
    avatar::getWorldPosition(param_1,&local_18);
  }
  else {
    local_18.x = param_7->x;
    local_18.y = param_7->y;
    local_18.z = param_7->z;
  }
  fVar4 = param_3 * param_3;
  if (param_3 <= 0.0) {
    fVar4 = 3.4028235e+38;
  }
  local_20 = Game::SceneInfo.actors_0x934.head;
  param_3 = fVar4;
  if (Game::SceneInfo.actors_0x934.head != (actor_0x934_conflict5)0x0) {
    do {
      av = ADJ(local_20);
      if (((param_2 == 0) || (ADJ(local_20).avatar.object.tag == param_2)) &&
         (iVar1 = FUN_00129420(param_1), paVar2 = local_24, iVar1 != 0)) {
        avatar::getWorldPosition((avatar *)av,&local_c);
        fVar4 = (local_18.z - local_c.z) * (local_18.z - local_c.z) +
                (local_18.y - local_c.y) * (local_18.y - local_c.y) +
                (local_18.x - local_c.x) * (local_18.x - local_c.x);
        if (((fVar4 < param_3) && (iVar1 = FUN_001295e0(), iVar1 != 0)) &&
           ((param_6 == (undefined *)0x0 || (iVar1 = (*(code *)param_6)(param_1,av), iVar1 != 0))))
        {
          paVar2 = av;
          param_3 = fVar4;
          local_24 = av;
        }
      }
      local_20 = local_20->next;
    } while (local_20 != (actor_0x934_conflict5)0x0);
    if ((paVar2 != (actor_conflict5 *)0x0) && (param_4 != (vec2 *)0x0)) {
      fVar3 = scaled_invsqrt(param_3);
      param_4->x = (float)fVar3;
    }
  }
  return (avatar *)paVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

actor_conflict5 *
FUN_00128f70(avatar *param_1,float param_2,float param_3,float param_4,float *param_5,float *param_6
            ,undefined4 param_7,code *param_8)

{
  int iVar1;
  actor_conflict5 *paVar2;
  float10 fVar3;
  float fVar4;
  actor_0x934_conflict5 local_3c;
  float local_38;
  float local_30;
  actor_conflict5 *local_2c;
  float local_28;
  vec3 local_24;
  vec3 local_18;
  vec3 local_c;
  
  local_2c = (actor_conflict5 *)0x0;
  avatar::getWorldPosition(param_1,&local_24);
  if (param_4 <= 0.0) {
    param_4 = 100000.0;
  }
  local_38 = param_4 * param_4;
  local_28 = param_2 + 3.1415927;
  local_3c = Game::SceneInfo.actors_0x934.head;
  if (Game::SceneInfo.actors_0x934.head == (actor_0x934_conflict5)0x0) {
    return (actor_conflict5 *)0x0;
  }
  do {
    paVar2 = ADJ(local_3c);
    iVar1 = FUN_00129420(param_1);
    if (iVar1 != 0) {
      avatar::getWorldPosition((avatar *)paVar2,&local_18);
      local_c.y = local_18.y - local_24.y;
      local_c.x = local_18.x - local_24.x;
      fVar4 = (local_24.z - local_18.z) * (local_24.z - local_18.z) +
              (local_24.y - local_18.y) * (local_24.y - local_18.y) +
              (local_24.x - local_18.x) * (local_24.x - local_18.x);
      local_c.z = local_18.z - local_24.z;
      vec3::getTurnAngle(&local_c,&local_30);
      param_4 = modf(local_30 - param_2,6.2831855);
      if (param_4 < -3.1415927) {
        param_4 = param_4 + 6.2831855;
      }
      if (3.1415927 <= param_4) {
        param_4 = param_4 - 6.2831855;
      }
      fVar3 = abs_float(param_4);
      if ((fVar4 < local_38) && ((float)fVar3 < param_3)) {
        iVar1 = FUN_001295e0();
        if (iVar1 != 0) {
          if (param_8 != (code *)0x0) {
            iVar1 = (*param_8)(param_1,paVar2);
            if (iVar1 == 0) goto LAB_00129143;
          }
          local_28 = local_30;
          local_38 = fVar4;
          local_2c = paVar2;
        }
      }
    }
LAB_00129143:
    paVar2 = local_2c;
    local_3c = local_3c->next;
    if (local_3c == (actor_0x934_conflict5)0x0) {
      if (local_2c != (actor_conflict5 *)0x0) {
        if (param_5 != (float *)0x0) {
          *param_5 = local_28;
        }
        if (param_6 != (float *)0x0) {
          fVar3 = scaled_invsqrt(local_38);
          *param_6 = (float)fVar3;
        }
      }
      return paVar2;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 ScriptConditionCallback::checkPlayerApproachesDoor(PlayerApproachesDoorCondition *cond)

{
  BOOL success;
  float distance;
  vec3 local_18;
  vec3 local_c;
  PlayerApproachesDoorCondition *pPVar1;
  
  if (((Game::SceneInfo.playerActors.prev != (actor_0x93c_conflict5)0x0) &&
      (ADJ(Game::SceneInfo.playerActors.prev) != (actor_conflict5 *)0x0)) &&
     (ADJ(Game::SceneInfo.playerActors.prev)->body->health != 0)) {
    avatar::getWorldPosition((avatar *)ADJ(Game::SceneInfo.playerActors.prev),&local_18);
    pPVar1 = cond;
                    // Get the player's distance to the door
    success = game::get_nearest_door_to_pos(&local_c,cond->doorId,&local_18,(float *)&cond);
    if (success != 0) {
      distance = pPVar1->minDistance;
      if (distance <= 0.0) {
        distance = 50.0;
      }
      if ((float)cond < distance) {
        return 1;
      }
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


