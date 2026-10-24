/* input.c - Input handlers, gamepad/controller polling, virtual keyboard */
#include "input.h"

VirtualKeyboardContext * FUN_000110d0(void)

{
  VirtualKeyboardContext *pVVar1;
  
  pVVar1 = malloc_(300);
  if (pVVar1 != (VirtualKeyboardContext *)0x0) {
    pVVar1 = (VirtualKeyboardContext *)VirtualKeyboardContext::alloc(pVVar1);
    VirtualKeyboardContext::Initialise(pVVar1);
    return pVVar1;
  }
  VirtualKeyboardContext::Initialise((VirtualKeyboardContext *)0x0);
  return (VirtualKeyboardContext *)0x0;
}




void __fastcall DrawVirtualKeyboard(int param_1,int param_2,int *param_3)

{
  *param_3 = param_1;
  param_3[1] = param_2;
  param_3[2] = 0;
  if (param_1 < 0x10006) {
    if (param_1 == 0x10005) {
      if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
        param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0x16);
        return;
      }
    }
    else if (param_1 < 0x10003) {
      if (param_1 == 0x10002) {
        if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
          param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0x10);
          return;
        }
      }
      else if (param_1 == 0x20) {
        if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
          param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0xc);
          return;
        }
      }
      else {
        if (param_1 != 0x10000) {
          return;
        }
        if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
          param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0xe);
          return;
        }
      }
    }
    else if (param_1 == 0x10003) {
      if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
        param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0x12);
        return;
      }
    }
    else {
      if (param_1 != 0x10004) {
        return;
      }
      if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
        param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0x14);
        return;
      }
    }
  }
  else {
    switch(param_1) {
    case 0x10006:
      if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
        param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0x18);
        return;
      }
      break;
    case 0x10007:
      if (Input::CurrentVirtualKeyboardStr != (wchar_t *)0x0) {
        param_3[2] = *(int *)(Input::CurrentVirtualKeyboardStr + 0x1a);
        return;
      }
      break;
    case 0x10008:
      param_3[2] = (int)&DAT_0020a668;
      return;
    case 0x10009:
      param_3[2] = (int)&DAT_0020a65c;
      return;
    case 0x1000a:
      param_3[2] = (int)"H0D0Y0F0M0T0F0";
    default:
      return;
    }
  }
  param_3[2] = (int)&DAT_0020a4f4;
  return;
}




VirtualKeyboardContext * VirtualKeyboardContext::alloc(VirtualKeyboardContext *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00170f1e;
  *unaff_FS_OFFSET = &uStack_c;
  param_1->field158_0xb0 = 0;
  param_1->field159_0xb4 = 0;
  param_1->field160_0xb8 = 0;
  local_4 = 0;
  param_1->field12_0xc = 0;
  param_1->field13_0x10 = 0;
  param_1->field14_0x14 = 1;
  param_1->field15_0x18 = 0;
  param_1->field153_0xa8 = 0;
  param_1->field161_0xbc = 0;
  param_1->field162_0xc0 = 0;
  param_1->field163_0xc4 = 0;
  param_1->field164_0xc8 = 0;
  param_1->field165_0xcc = 0;
  param_1->field173_0xe0 = 0;
  param_1->field174_0xe4 = 0;
  param_1->somePtr = &DAT_00434118;
  param_1->somefloat = 42.0;
  param_1->field177_0xf0 = 5;
  param_1->field190_0x118 = 0;
  param_1->field191_0x11c = 0;
  param_1->field192_0x120 = 0;
  param_1->field193_0x124 = 0;
  param_1->field194_0x128 = 0;
  param_1->field178_0xf4 = 0;
  param_1->field179_0xf8 = 0;
  param_1->field181_0x100 = 0;
  param_1->field180_0xfc = 0;
  param_1->field183_0x108 = 0;
  param_1->field182_0x104 = 0;
  param_1->field166_0xd0 = 0;
  param_1->field167_0xd4 = 0;
  param_1->field168_0xd8 = 0;
  param_1->field184_0x10c = 0;
  Scripting::CreateInputHandler3(&param_1->inputHandler);
  runtime::PushInputHandlerAndSetActive(&param_1->inputHandler->header,"virtualkeyboard");
  param_1->field16_0x1c = 0;
  param_1->somePtr = &DAT_00434118;
  Input::CurrentVirtualKeyboardStr = (wchar_t *)PTR_PTR_00434120;
  *unaff_FS_OFFSET = uStack_c;
  return param_1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 VirtualKeyboardContext::Initialise(VirtualKeyboardContext *param_1)

{
  undefined1 *lvCtx;
  int iVar1;
  entityAvatarMiscButtonBat *peVar2;
  uint uVar3;
  vec2 batPos;
  
  runtime::AllocateForLoctext_(0,1,(void *)0x400c0,(LoctextValueContext **)param_1);
  runtime::AllocateForLoctext_(0,1,(void *)0x400c0,(LoctextValueContext **)&param_1->field_0x4);
  lvCtx = &param_1->field_0x8;
  runtime::AllocateForLoctext_(0,1,(void *)0x400c0,(LoctextValueContext **)lvCtx);
  iVar1 = *(int *)param_1;
  *(float *)(iVar1 + 0x14) = 3.0;
  *(float *)(iVar1 + 0x18) = 0.7;
  *(undefined4 *)(iVar1 + 0x1c) = 3;
  switch(runtime::LanguageID) {
  case ENGLISH:
    param_1->field16_0x1c = 0;
    param_1->somePtr = &DAT_00434118;
    Input::CurrentVirtualKeyboardStr = (wchar_t *)PTR_PTR_00434120;
    break;
  case FRENCH:
    param_1->field16_0x1c = 4;
    param_1->somePtr = (undefined *)&UINT_00434148;
    Input::CurrentVirtualKeyboardStr = (wchar_t *)PTR_PTR_00434150;
    break;
  case GERMAN:
    param_1->field16_0x1c = 3;
    param_1->somePtr = (undefined *)&UINT_0043413c;
    Input::CurrentVirtualKeyboardStr = (wchar_t *)PTR_PTR_00434144;
    break;
  case SPANISH:
    param_1->field16_0x1c = 5;
    param_1->somePtr = (undefined *)&UINT_00434154;
    Input::CurrentVirtualKeyboardStr = (wchar_t *)PTR_PTR_0043415c;
    break;
  case ITALIAN:
    param_1->field16_0x1c = 6;
    param_1->somePtr = (undefined *)&UINT_00434160;
    Input::CurrentVirtualKeyboardStr = (wchar_t *)PTR_PTR_00434168;
    break;
  case KOREAN:
  case CHINESE:
  case JAPANESE:
    param_1->field16_0x1c = 7;
    param_1->somePtr = &DAT_0043416c;
    Input::CurrentVirtualKeyboardStr = (wchar_t *)PTR_PTR_00434174;
  }
  FUN_00014ab0((int)param_1);
  FUN_00011870(param_1);
  FUN_0005f970(*(undefined4 *)param_1);
  param_1->field161_0xbc = 0;
  FUN_00015c40(param_1);
  batPos.x = 0.0;
  batPos.y = 0.0;
  if (param_1->field178_0xf4 == 0) {
    peVar2 = entityAvatarMiscButtonBat::create(1.25,0.25,&batPos);
    param_1->field178_0xf4 = peVar2;
    param_1->field180_0xfc = 0;
    param_1->field181_0x100 = 0;
  }
  batPos.x = 0.0;
  batPos.y = 0.0;
  if (param_1->field179_0xf8 == 0) {
    peVar2 = entityAvatarMiscButtonBat::create(1.25,0.25,&batPos);
    param_1->field179_0xf8 = peVar2;
    param_1->field182_0x104 = 0;
    param_1->field183_0x108 = 0;
  }
  FUN_00016730();
  *(undefined4 *)(**(int **)lvCtx + 8) = *(undefined4 *)(**(int **)lvCtx + 4);
  uVar3 = CreateLoctext(*(LoctextValueContext **)lvCtx,(LPWSTR)&param_1->field_0x24,130.0,54.0,1.45,
                        1.45,1.0,0,0,1);
  *(uint *)&param_1->field_0xa4 = uVar3;
  if (param_1->field179_0xf8 != 0) {
    FUN_00015010();
    batPos.x = (float)param_1->field182_0x104;
    batPos.y = (float)param_1->field183_0x108;
    FUN_0006da00(0x3fa00000);
  }
  return 0;
}




undefined4 Input::DoBigUpdate(astruct_36 *param_1)

{
  int iVar1;
  
  if (Game::DialogState == NotInDialog) {
    if (((InputHandlerType4 *)param_1->field260_0x110 != (InputHandlerType4 *)0x0) &&
       (param_1->field259_0x10c != (Scene *)0x0)) {
      FUN_00109470((InputHandlerType4 *)param_1->field260_0x110);
      UpdateMenuInput((InputHandlerType3 *)param_1->field260_0x110,param_1->field259_0x10c);
    }
    iVar1 = UpdateInputsForKeyboard(param_1);
    if ((param_1->field25_0x1c == 1) && (param_1->field24_0x18 == 0)) {
      if (iVar1 != 4) {
        param_1->field265_0x118 = 0;
        FUN_00015220();
        return 0;
      }
    }
    else {
      FUN_00015090(iVar1);
    }
  }
  return 0;
}



// WARNING: Type propagation algorithm not settling


undefined4 Input::UpdateInputsForKeyboard(astruct_36 *param_1)

{
  InputHandlerType1 *pIVar1;
  BOOL BVar2;
  int iVar3;
  undefined4 uVar4;
  float fVar5;
  vec2 local_8;
  
  pIVar1 = GlobalInputHandler;
  uVar4 = 0;
  BVar2 = ContextHasButton(START,(InputHandlerType3 *)GlobalInputHandler);
  if (BVar2 != 0) {
    uVar4 = 2;
  }
  BVar2 = ContextHasButton(SELECT,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 4;
  }
  BVar2 = ContextHasButton(BUTTON_A,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 1;
  }
  BVar2 = ContextHasButton(BUTTON_B,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 3;
  }
  BVar2 = ContextHasButton(BUTTON_X,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 5;
  }
  BVar2 = ContextHasButton(BUTTON_Y,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 6;
  }
  BVar2 = ContextHasButton(BUTTON_BLACK,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 8;
  }
  BVar2 = ContextHasButton(BUTTON_WHITE,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 7;
  }
  BVar2 = ContextHasButton(TRIGGER_L,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 9;
  }
  BVar2 = ContextHasButton(TRIGGER_R,(InputHandlerType3 *)pIVar1);
  if (BVar2 != 0) {
    uVar4 = 10;
  }
  GetLSMovement_(pIVar1,&local_8);
  if (((((local_8.y <= 0.25) && (GetLSMovement_(GlobalInputHandler,&local_8), -0.25 <= local_8.y))
       && (GetLSMovement_(GlobalInputHandler,&local_8), -0.25 <= local_8.x)) &&
      ((iVar3 = isLSRight(), iVar3 == 0 &&
       (BVar2 = ContextHasButton(DPAD_LEFT,(InputHandlerType3 *)GlobalInputHandler), BVar2 == 0))))
     && ((iVar3 = dpadRight(), iVar3 == 0 &&
         ((iVar3 = hasDpadUp(), iVar3 == 0 && (iVar3 = hasDpadDown(), iVar3 == 0)))))) {
    param_1->directionalMovement = 0.0;
    return uVar4;
  }
  if (param_1->directionalMovement == 0.0) {
    GetLSMovement_(GlobalInputHandler,&local_8);
    pIVar1 = GlobalInputHandler;
    if ((0.25 < local_8.y) ||
       (BVar2 = ContextHasButton(DPAD_UP,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0)) {
      uVar4 = 0xb;
    }
    GetLSMovement_(pIVar1,&local_8);
    pIVar1 = GlobalInputHandler;
    if ((local_8.y < -0.25) ||
       (BVar2 = ContextHasButton(DPAD_DOWN,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0)) {
      uVar4 = 0xc;
    }
    GetLSMovement_(pIVar1,&local_8);
    pIVar1 = GlobalInputHandler;
    if ((local_8.x < -0.25) ||
       (BVar2 = ContextHasButton(DPAD_LEFT,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0)) {
      uVar4 = 0xd;
    }
    GetLSMovement_(pIVar1,&local_8);
    if ((0.25 < local_8.x) ||
       (BVar2 = ContextHasButton(DPAD_RIGHT,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0)) {
      uVar4 = 0xe;
    }
    param_1->directionalMovement = 0.333;
  }
  else {
    if (runtime::dx_timer <= 0.0) {
      fVar5 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar5 = 0.0;
    }
    if ((0.0 < param_1->directionalMovement) &&
       (fVar5 = param_1->directionalMovement - fVar5, param_1->directionalMovement = fVar5,
       fVar5 <= 0.0)) {
      param_1->directionalMovement = 0.0;
      GetLSMovement_(GlobalInputHandler,&local_8);
      pIVar1 = GlobalInputHandler;
      if ((0.25 < local_8.y) ||
         (BVar2 = ContextHasButton(DPAD_UP,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0)) {
        uVar4 = 0xb;
      }
      GetLSMovement_(pIVar1,&local_8);
      pIVar1 = GlobalInputHandler;
      if ((local_8.y < -0.25) ||
         (BVar2 = ContextHasButton(DPAD_DOWN,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0))
      {
        uVar4 = 0xc;
      }
      GetLSMovement_(pIVar1,&local_8);
      pIVar1 = GlobalInputHandler;
      if ((local_8.x < -0.25) ||
         (BVar2 = ContextHasButton(DPAD_LEFT,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0))
      {
        uVar4 = 0xd;
      }
      GetLSMovement_(pIVar1,&local_8);
      if ((0.25 < local_8.x) ||
         (BVar2 = ContextHasButton(DPAD_RIGHT,(InputHandlerType3 *)GlobalInputHandler), BVar2 != 0))
      {
        uVar4 = 0xe;
      }
      param_1->directionalMovement = 0.085;
      return uVar4;
    }
  }
  return uVar4;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


BOOL Scripting::Input::ResolveHandlers(void)

{
  InputHandlerType3 *pIVar1;
  uint uVar2;
  
  if (::Input::ResolvingInputs == 1) {
    if (DAT_004dea38 != 0) {
      DAT_004dea38 = 1;
      return 1;
    }
    if ((((((int)::Input::InputHandlers->tail - (int)::Input::InputHandlers->head) /
           (int)(uint)::Input::InputHandlers->valueSize != 0) &&
         (pIVar1 = *(InputHandlerType3 **)
                    (::Input::InputHandlers->head->handlerName +
                    (::Input::NumInputHandlers - 1) * (uint)::Input::InputHandlers->valueSize + -4),
         pIVar1 != (InputHandlerType3 *)0x0)) && ((pIVar1->header).active != 0)) &&
       (uVar2 = ::Input::ExecuteHandler(pIVar1), uVar2 == 0)) {
      DAT_004dea38 = 1;
      return 1;
    }
  }
  return 0;
}




void __fastcall runtime::UpdateNoControllerText(int *param_1)

{
  LoctextDescriptor *pLVar1;
  LPWSTR in_EAX;
  uint uVar2;
  LoctextDescriptor *local_4;
  
  local_4 = (LoctextDescriptor *)param_1;
  Assets::GetResourceBytes("aid_loctext_ghoulies_pause_nocontroller",&local_4);
  pLVar1 = local_4;
  if (local_4 == (LoctextDescriptor *)0x0) {
    ExitGame(2);
  }
  switch(*param_1) {
  default:
    uVar2 = 0;
    break;
  case 2:
    uVar2 = Player1PortBit;
    break;
  case 3:
    uVar2 = 0xffffffff;
    break;
  case 5:
    uVar2 = GetCurrentControllerPortBackup();
  }
  switch(uVar2) {
  case 1:
    createGameselectString("noControllerText","Port1",in_EAX,pLVar1);
    return;
  case 2:
    createGameselectString("noControllerText","Port2",in_EAX,pLVar1);
    return;
  case 4:
    createGameselectString("noControllerText","Port3",in_EAX,pLVar1);
    return;
  case 8:
    createGameselectString("noControllerText","Port4",in_EAX,pLVar1);
    break;
  case 0xffffffff:
    createGameselectString("noControllerText","PortAny",in_EAX,pLVar1);
    return;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void FUN_0007a420(InputHandlerType1 *param_1,float param_2)

{
  int in_EAX;
  float *unaff_ESI;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = 0.0;
  if (*(float *)(in_EAX + 0x930) <= 0.0) {
    fVar1 = *(float *)(in_EAX + 0x92c);
  }
  fVar1 = runtime::DeltaTime * runtime::TimeScale * fVar1;
  fVar2 = fVar1;
  fVar4 = modf(*unaff_ESI - param_2,360.0);
  if (fVar4 < -180.0) {
    fVar4 = fVar4 + 360.0;
  }
  fVar3 = 180.0;
  if (180.0 <= fVar4) {
    fVar4 = fVar4 - 360.0;
  }
  FUN_00108de0(param_1);
  if (fVar4 < 0.0) {
    fVar2 = 0.0 - fVar2;
  }
  fVar4 = fVar2 * 100.0 * fVar1 + fVar4;
  if ((fVar4 < -180.0) || (fVar3 < fVar4)) {
    fVar2 = modf(param_2 + fVar3,360.0);
    if (fVar2 < -180.0) {
      fVar2 = fVar2 + 360.0;
    }
    if (180.0 <= fVar2) {
      fVar2 = fVar2 - 360.0;
    }
    *unaff_ESI = fVar2;
    fVar2 = 0.0;
  }
  *unaff_ESI = fVar2 * 100.0 * fVar1 + *unaff_ESI;
  return;
}



// WARNING: Removing unreachable block (ram,0x0007a644)
// WARNING: Removing unreachable block (ram,0x0007a6b4)
// WARNING: Removing unreachable block (ram,0x0007a73f)
// WARNING: Removing unreachable block (ram,0x0007a742)


undefined4 FUN_0007b170(actorMind *param_1,InputHandlerBase *param_2)

{
  actor *paVar1;
  actorMind *paVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float in_XMM0_Da;
  float fVar6;
  float fVar7;
  float local_c;
  float local_8;
  float local_4;
  
  iVar3 = (int)param_2;
  paVar2 = param_1;
  paVar1 = param_1->actor;
  if ((paVar1->mind == (actorMind *)0x0) || (paVar1->mind->targetBody == (actorBody *)0x0)) {
    return 1;
  }
  param_2 = paVar1->input_handler_;
  FUN_0013a5b0();
  if (*(float *)(iVar3 + 0x28) <= in_XMM0_Da && in_XMM0_Da != *(float *)(iVar3 + 0x28)) {
    return 1;
  }
  if (runtime::dx_timer <= 0.0) {
    fVar6 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar6 = 0.0;
  }
  fVar7 = 0.0;
  if ((paVar1->avatar).movementFreezeTimer <= 0.0) {
    fVar7 = (paVar1->avatar).actionSpeed;
  }
  fVar6 = *(float *)(iVar3 + 0x30) - fVar7 * fVar6;
  *(float *)(iVar3 + 0x30) = fVar6;
  if (fVar6 <= 0.0) {
    *(float *)(iVar3 + 0x30) = fVar6 + 2.0;
    iVar4 = FUN_00135b60(paVar1,*(undefined4 *)(iVar3 + 0x2c),*(undefined4 *)(iVar3 + 0x10),
                         *(undefined4 *)(iVar3 + 0x14),&local_c);
    if (iVar4 == 0) goto LAB_0007b2d8;
    (paVar2->evasionPos).x = local_c;
    (paVar2->evasionPos).y = local_8;
    (paVar2->evasionPos).z = local_4;
  }
  local_c = (paVar2->evasionPos).x;
  local_8 = (paVar2->evasionPos).y;
  local_4 = (paVar2->evasionPos).z;
  FUN_00136030(&local_c,iVar3 + 0x2c);
  iVar4 = FUN_0007b490();
  iVar5 = FUN_00136b00(0xffffffff,param_1,param_2,&paVar2->evasionPos,2.5,0.0,
                       *(float *)(iVar3 + 0x20),0,&param_1);
  if (iVar4 != 0) {
    FUN_0007b510();
  }
  if (iVar5 != 1) {
    return 0;
  }
LAB_0007b2d8:
  *(undefined4 *)(iVar3 + 0x30) = 0;
  return 0;
}




undefined4 FUN_0007ba20(actorMind *param_1,InputHandlerType1 *param_2)

{
  actor *av;
  actorBody *body;
  float __x;
  int iVar1;
  InputHandlerType1 *pIVar2;
  byte bVar3;
  int iVar4;
  float10 extraout_ST0;
  float10 fVar5;
  float fVar6;
  float fVar7;
  vec3 local_1c;
  float local_10;
  float local_c;
  float local_4;
  
  iVar1 = (int)param_2;
  av = param_1->actor;
  param_2 = (InputHandlerType1 *)av->input_handler_;
  body = av->body;
  if (body->field13_0x30 != 0) {
    return 0;
  }
  if (body->someTimer2 != 0.0) {
    return 0;
  }
  if (body->someCount == 0) {
    bVar3 = body->movementIndex;
  }
  else {
    bVar3 = body->fallbackMovementIndex;
  }
  if ((body->movementFlags & 1 << (bVar3 & 0x1f)) == 0) {
    fVar7 = 1.0;
  }
  else {
    fVar7 = Game::FloorTypeMap[bVar3];
  }
  fVar6 = actorBody::getMovespeed(body);
  __x = *(float *)(iVar1 + 0x28);
  local_1c.x = fVar6 * fVar7 * *(float *)(iVar1 + 0x1c);
  local_10 = __x;
  sin(__x);
  local_c = (float)(extraout_ST0 * (float10)local_1c.x);
  fVar5 = (float10)cos(__x);
  local_4 = (float)(fVar5 * (float10)local_1c.x);
  avatar::getWorldPosition(&av->avatar,&local_1c);
  pIVar2 = param_2;
  fVar7 = *(float *)(iVar1 + 0x18) - *(float *)(iVar1 + 0xc);
  local_1c.x = fVar7 * local_c + local_1c.x;
  local_1c.y = fVar7 * 0.0 + local_1c.y;
  local_1c.z = fVar7 * local_4 + local_1c.z;
  if (*(int *)(iVar1 + 0x24) == 0) {
    iVar4 = FUN_00136b00(av->backgroundCollisionIndex,param_1,&param_2->base,&local_1c,0.0,30.0,1.0,
                         0,&param_1);
    if (iVar4 != 0) goto actorMind_onWalkToDestinationGoal;
    Input::GetLSMovement_(pIVar2,(vec2 *)&local_1c);
    FUN_00105dd0(*(undefined4 *)(iVar1 + 0x1c));
  }
  else {
    local_10 = *(float *)(iVar1 + 0x1c);
    local_1c.x = local_4;
    param_1 = (actorMind *)(local_4 * local_4 + local_c * local_c);
    local_1c.y = local_c;
    if ((float)param_1 != 0.0) {
      fVar5 = scaled_invsqrt((float)param_1);
      local_1c.x = (float)((float10)local_4 * ((float10)local_10 / fVar5));
      local_1c.y = (float)(((float10)local_10 / fVar5) * (float10)local_c);
    }
  }
  FUN_00108fc0();
actorMind_onWalkToDestinationGoal:
  if (*(float *)(iVar1 + 0xc) < *(float *)(iVar1 + 0x18)) {
    return 0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0007d210(InputHandlerType3 *param_1)

{
  int iVar1;
  actorBody *this;
  actorBodyStateId state;
  int iVar2;
  BOOL BVar3;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 0x134);
  this = *(actorBody **)(*(int *)(unaff_EDI + 8) + 0x95c);
  *(undefined4 *)(unaff_EDI + 0x134) = 0;
  if ((*(float *)(unaff_EDI + 0x15c) <= 0.0) && (iVar1 != 0)) {
    iVar2 = FUN_00027d40();
    if (iVar2 != 0) {
      BVar3 = Input::ContextHasButton(BUTTON_A,param_1);
      if (BVar3 != 0) {
        *(int *)(unaff_EDI + 0x18) = iVar1;
        state = (*this->vtable->getPickupState)(this);
        actorBody::setState(this,state);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0007ee40(InputHandlerType1 *param_1)

{
  int iVar1;
  int in_EAX;
  vec2 local_8;
  
  iVar1 = *(int *)(*(int *)(in_EAX + 8) + 0x95c);
  if (Game::PowerupParams[0x11].active != 0) {
    Input::GetLSMovement_(param_1,&local_8);
    local_8.x = 0.0 - local_8.x;
    local_8.y = 0.0 - local_8.y;
    FUN_00108fc0();
    ScriptType1::getControllerXY(param_1,&local_8);
    local_8.x = 0.0 - local_8.x;
    local_8.y = 0.0 - local_8.y;
    RunInputCallbacks(param_1);
  }
  if (*(char *)(iVar1 + 0x38) == '\x01') {
    Input::GetLSMovement_(param_1,&local_8);
    FUN_00140ae0();
    FUN_00108fc0();
  }
  if (*(char *)(iVar1 + 0x39) == '\x01') {
    ScriptType1::getControllerXY(param_1,&local_8);
    FUN_00140ae0();
    RunInputCallbacks(param_1);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 FUN_0007f980(float param_1,InputHandlerType1 *param_2)

{
  avatar *av;
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  vec3 local_24;
  float local_18;
  float local_14;
  float local_10;
  vec3 local_c;
  
  fVar1 = param_1;
  av = *(avatar **)((int)param_1 + 8);
  fVar3 = av[1].rotQuat.z;
  if ((*(short *)((int)fVar3 + 0x30) != 0) || (*(float *)((int)fVar3 + 0x34) != 0.0)) {
    return 0;
  }
  Input::GetLSMovement_(param_2,(vec2 *)&local_24);
  if (local_24.y * local_24.y + local_24.x * local_24.x <= 0.010000001) {
    avatar::getWorldPosition(av,&local_24);
    fVar3 = 0.0;
    if (*(int *)((int)fVar1 + 0x194) == 0) {
      param_1 = (av->rotEuler).y;
      fVar4 = param_1;
    }
    else {
      fVar4 = *(float *)((int)fVar1 + 400);
    }
    FUN_00100c70(fVar4);
    param_1 = fVar3;
    iVar2 = FUN_0013aa50(fVar3,*(undefined4 *)(av[1].model0x9s[0].audioID + 0x74),0x3e9c61aa,10,
                         0x41400000,0x41780000,0,0,&local_18,1,9,0);
    if (iVar2 != 0) {
      local_c.x = local_18 - local_24.x;
      local_c.y = local_14 - local_24.y;
      local_c.z = local_10 - local_24.z;
      vec3::getTurnAngle(&local_c,&param_1);
      FUN_001060a0(param_1,0x3f800000);
      local_24.x = local_c.z;
      local_24.y = local_c.x;
      FUN_00108fc0();
      *(float *)((int)fVar1 + 400) = param_1;
      *(undefined4 *)((int)fVar1 + 0x194) = 1;
      return 1;
    }
  }
  return 0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_000886b0(int param_1,InputHandlerType1 *param_2)

{
  float fVar1;
  actorBody *this;
  actor *paVar2;
  actor *av;
  KeyframeContext *pKVar3;
  AnimInstance *pAVar4;
  int iVar5;
  bool bVar6;
  undefined2 uVar7;
  bool bVar8;
  float fVar9;
  float fVar10;
  float local_30;
  vec2 local_2c;
  vec3 local_24;
  vec3 local_18;
  vec3 local_c;
  
  this = *(actorBody **)(param_1 + 8);
  paVar2 = this->actor;
  if (runtime::dx_timer <= 0.0) {
    fVar10 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar10 = 0.0;
  }
  fVar9 = 0.0;
  if ((paVar2->avatar).movementFreezeTimer <= 0.0) {
    fVar9 = (paVar2->avatar).actionSpeed;
  }
  *(float *)(param_1 + 0x10) = fVar9 * fVar10 + *(float *)(param_1 + 0x10);
  local_2c.x = (float)paVar2;
  if (((*(int *)(param_1 + 0x2c) == 0) || (paVar2->mind == (actorMind *)0x0)) ||
     (av = paVar2->mind->targetActor, av == (actor *)0x0)) {
    (this->rotation).z = 0.0;
    (this->rotation).x = 0.0;
  }
  else {
    avatar::getWorldPosition(&av->avatar,&local_24);
    avatar::getWorldPosition(&paVar2->avatar,&local_18);
    local_c.x = local_24.x - local_18.x;
    local_c.y = local_24.y - local_18.y;
    local_c.z = local_24.z - local_18.z;
    vec3::getTurnAngle(&local_c,&local_30);
    fVar10 = *(float *)(param_1 + 0x30);
    (this->rotation).x = 0.0;
    (this->rotation).y = fVar10 + local_30;
    (this->rotation).z = 0.0;
  }
  fVar10 = local_2c.x;
  if (*(int *)(param_1 + 0x3c) != 0) {
    actorBody::applyBodyDirectionToRotation(this);
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    paVar2 = this->actor;
    fVar9 = (paVar2->avatar).physicsPos.y;
    fVar1 = (paVar2->avatar).physicsPos.z;
    (this->velocity).x = (paVar2->avatar).physicsPos.x;
    (this->velocity).y = fVar9;
    (this->velocity).z = fVar1;
  }
  pKVar3 = ((avatar *)fVar10)->keyframeContext;
  if ((pKVar3 == (KeyframeContext *)0x0) ||
     (pAVar4 = pKVar3->kfcAnims->animInstance, pAVar4 == (AnimInstance *)0x0)) {
    fVar9 = 0.0;
  }
  else {
    fVar9 = pAVar4->t;
  }
  if ((fVar9 < *(float *)(param_1 + 0x34) || fVar9 == *(float *)(param_1 + 0x34)) ||
     (Input::GetLSMovement_(param_2,&local_2c),
     local_2c.y * local_2c.y + local_2c.x * local_2c.x <= 0.010000001)) {
    bVar6 = false;
  }
  else {
    bVar6 = true;
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    pKVar3 = ((avatar *)fVar10)->keyframeContext;
    if (pKVar3 == (KeyframeContext *)0x0) goto LAB_000888f5;
    pAVar4 = pKVar3->kfcAnims->animInstance;
    if (pAVar4 != (AnimInstance *)0x0) {
      bVar8 = false;
      if (pAVar4->loopMode != Mode1) goto LAB_000888ed;
      if (pAVar4->invDuration <= 0.0 && pAVar4->invDuration != 0.0) {
        bVar8 = 0.0 < pAVar4->t;
      }
      else {
        bVar8 = pAVar4->t < 1.0;
      }
      if (bVar8) goto LAB_00088944;
    }
LAB_000888e8:
    bVar8 = true;
  }
  else {
    iVar5 = *(int *)(*(int *)(param_1 + 8) + 8);
    if (runtime::dx_timer <= 0.0) {
      fVar10 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar10 = 0.0;
    }
    fVar9 = 0.0;
    if (*(float *)(iVar5 + 0x930) <= 0.0) {
      fVar9 = *(float *)(iVar5 + 0x92c);
    }
    if ((0.0 < *(float *)(param_1 + 0x20)) &&
       (fVar10 = *(float *)(param_1 + 0x20) - fVar9 * fVar10, *(float *)(param_1 + 0x20) = fVar10,
       fVar10 <= 0.0)) {
      *(undefined4 *)(param_1 + 0x20) = 0;
      goto LAB_000888e8;
    }
LAB_00088944:
    bVar8 = false;
  }
LAB_000888ed:
  if ((!bVar8) && (!bVar6)) {
    return;
  }
LAB_000888f5:
  if (*(short *)(param_1 + 0x18) == 0) {
    uVar7 = (**(code **)(**(int **)(param_1 + 8) + 0x20))(*(int **)(param_1 + 8));
    *(undefined2 *)(param_1 + 0xc) = uVar7;
    return;
  }
  *(short *)(param_1 + 0xc) = *(short *)(param_1 + 0x18);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0008a5f0(int param_1,InputHandlerType1 *param_2)

{
  int *piVar1;
  avatar *av;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  BOOL BVar5;
  bool bVar6;
  float fVar7;
  float fVar8;
  undefined4 uVar9;
  vec2 local_24;
  float local_1c;
  vec3 local_18;
  vec3 local_c;
  
  piVar1 = *(int **)(param_1 + 8);
  av = (avatar *)piVar1[2];
  if (runtime::dx_timer <= 0.0) {
    fVar8 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar8 = 0.0;
  }
  fVar7 = 0.0;
  if (av->movementFreezeTimer <= 0.0) {
    fVar7 = av->actionSpeed;
  }
  *(float *)(param_1 + 0x10) = fVar7 * fVar8 + *(float *)(param_1 + 0x10);
  piVar1[0x1cd] = 0;
  piVar1[0x1cb] = 0;
  piVar1[0xc6] = (int)Game::someGlobalPos.x;
  piVar1[199] = (int)Game::someGlobalPos.y;
  piVar1[200] = (int)Game::someGlobalPos.z;
  Input::GetLSMovement_(param_2,&local_24);
  FUN_00109810(1);
  avatar::getWorldPosition(av,&local_18);
  avatar::getWorldRotation(av,&local_c);
  if (*(avatar **)(param_1 + 0x29c) != (avatar *)0x0) {
    avatar::setPosition(*(avatar **)(param_1 + 0x29c),&local_18);
    local_24.x = *(float *)(param_1 + 0x29c);
    Maths::NormaliseAngles2PI(&local_c,(vec3 *)((int)local_24.x + 0x14));
    *(undefined4 *)((int)local_24.x + 0x2a8) = 0;
  }
  if (*(avatar **)(param_1 + 0x2a0) != (avatar *)0x0) {
    avatar::setPosition(*(avatar **)(param_1 + 0x2a0),&local_18);
    local_24.x = *(float *)(param_1 + 0x2a0);
    Maths::NormaliseAngles2PI(&local_c,(vec3 *)((int)local_24.x + 0x14));
    *(undefined4 *)((int)local_24.x + 0x2a8) = 0;
    iVar4 = *(int *)(param_1 + 0x2a0);
    if ((*(int *)(iVar4 + 0x50) != 0) &&
       (iVar2 = **(int **)(*(int *)(iVar4 + 0x50) + 0x58), iVar2 != 0)) {
      bVar6 = false;
      if (*(char *)(iVar2 + 0x2a) == '\x01') {
        if (*(float *)(iVar2 + 0x1c) <= 0.0 && *(float *)(iVar2 + 0x1c) != 0.0) {
          bVar6 = 0.0 < *(float *)(iVar2 + 0x14);
        }
        else {
          bVar6 = *(float *)(iVar2 + 0x14) < 1.0;
        }
        if (bVar6) {
          bVar6 = false;
        }
        else {
          bVar6 = true;
        }
      }
      if (!bVar6) goto LAB_0008a7df;
    }
    local_24.y = *(float *)(iVar4 + 0x34);
    local_24.x = *(float *)(iVar4 + 0x30) * 0.5;
    local_1c = *(float *)(iVar4 + 0x38) * 0.5;
    FUN_0013af80(0x3e4ccccd,0,0);
    avatar::destroy(*(avatar **)(param_1 + 0x2a0));
    *(undefined4 *)(param_1 + 0x2a0) = 0;
  }
LAB_0008a7df:
  switch(*(undefined4 *)(param_1 + 0x18)) {
  case 1:
    if ((*(actor **)(param_1 + 0x2a0) == (actor *)0x0) ||
       (iVar4 = CheckAnimKfcThreshold((void *)0x0,*(actor **)(param_1 + 0x2a0),0.9), iVar4 != 0)) {
      FUN_0008aad0();
      FUN_0008a950(2);
      return;
    }
    break;
  case 2:
    if (*(int *)(param_1 + 0x2b8) == 2) {
      uVar9 = 3;
LAB_0008a860:
      FUN_0008a950(uVar9);
    }
    goto LAB_0008a86a;
  case 3:
    iVar4 = CheckAnimKfcThreshold((void *)0x0,*(actor **)(param_1 + 0x29c),1.0);
    if ((iVar4 != 0) && (*(int *)(param_1 + 0x2b8) != 2)) {
      uVar9 = 2;
      goto LAB_0008a860;
    }
LAB_0008a86a:
    iVar4 = FUN_0008b140();
    if (iVar4 != 0) {
      FUN_0008a950(4);
      return;
    }
    break;
  case 4:
    BVar5 = avatar::updateKeyframes(av,0);
    if (BVar5 != 0) {
      if ((short)piVar1[0x25] == 0) {
        FUN_00133f50(param_1,0);
        return;
      }
      uVar3 = (**(code **)(*piVar1 + 0x20))(piVar1);
      *(undefined2 *)(param_1 + 0xc) = uVar3;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_0008cc40(float param_1,InputHandlerType1 *param_2)

{
  actorBody *this;
  actor *paVar1;
  KeyframeContext *pKVar2;
  AnimInstance *pAVar3;
  int iVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  Message local_8;
  
  iVar4 = (int)param_1;
  this = *(actorBody **)((int)param_1 + 8);
  if (runtime::dx_timer <= 0.0) {
    fVar8 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar8 = 0.0;
  }
  fVar6 = 0.0;
  if ((this->actor->avatar).movementFreezeTimer <= 0.0) {
    fVar6 = (this->actor->avatar).actionSpeed;
  }
  *(float *)((int)param_1 + 0x10) = fVar6 * fVar8 + *(float *)((int)param_1 + 0x10);
  paVar1 = this->actor;
  (this->rotation).z = 0.0;
  (this->rotation).x = 0.0;
  if (*(int *)((int)param_1 + 0x50) != 0) {
    actorBody::applyBodyDirectionToRotation(this);
  }
  fVar8 = 0.0;
  if (runtime::dx_timer <= 0.0) {
    fVar6 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar6 = 0.0;
  }
  if ((paVar1->avatar).movementFreezeTimer <= 0.0) {
    fVar8 = (paVar1->avatar).actionSpeed;
  }
  fVar8 = fVar8 * fVar6;
  if (*(int *)((int)param_1 + 0x48) != 0) {
    Input::GetLSMovement_(param_2,(vec2 *)&local_8);
    FUN_00109810(1);
    ScriptType1::getControllerXY(param_2,(vec2 *)&local_8);
    FUN_00109810(1);
    if ((*(int *)((int)param_1 + 0x2c) == 2) || (*(int *)((int)param_1 + 0x44) == 2)) {
      fVar8 = FLOAT_00428670 * fVar8;
    }
  }
  param_1 = fVar8;
  FUN_0008d0e0(iVar4,this);
  if ((0.0 < *(float *)(iVar4 + 0x58)) &&
     (param_1 = *(float *)(iVar4 + 0x58) - param_1, *(float *)(iVar4 + 0x58) = param_1,
     param_1 <= 0.0)) {
    *(undefined4 *)(iVar4 + 0x58) = 0;
  }
  pKVar2 = (paVar1->avatar).keyframeContext;
  bVar5 = false;
  if (((pKVar2 != (KeyframeContext *)0x0) &&
      (pAVar3 = pKVar2->kfcAnims->animInstance, pAVar3 != (AnimInstance *)0x0)) &&
     (fVar8 = pAVar3->t, fVar8 != pAVar3->defaultT)) {
    if (pAVar3->invDuration <= 0.0 && pAVar3->invDuration != 0.0) {
      fVar6 = pAVar3->defaultT;
      fVar7 = fVar8;
    }
    else {
      fVar7 = pAVar3->defaultT;
      fVar6 = fVar8;
    }
    if (fVar6 <= fVar7) {
      if ((1.0 < fVar7) && (fVar6 <= 1.0)) {
        bVar5 = false;
        goto LAB_0008ce2a;
      }
    }
    else if ((1.0 < fVar7) || (fVar6 <= 1.0)) {
      bVar5 = false;
      goto LAB_0008ce2a;
    }
    bVar5 = true;
  }
LAB_0008ce2a:
  if ((*(float *)(iVar4 + 0x58) == 0.0) && ((*(int *)(iVar4 + 0x4c) == 0 || (bVar5)))) {
    if (this->hitReactionRes == (HitReactionResource *)0x0) {
      bVar5 = true;
    }
    else {
      bVar5 = this->hitReactionRes->field_0x1a4 == '\0';
    }
    FUN_001346b0(bVar5);
    this->someTimer4 = this->knockdownThreshold;
    local_8.header.someActor = this->actor;
    local_8.header.msgId = Scene_ActorRecoveredFromStun;
    EventLoop::DispatchMessage((ObjMsgID *)&local_8);
    FUN_00134060(iVar4);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __thiscall FUN_000908d0(InputHandlerType1 *param_1,int param_2)

{
  float angle;
  int unaff_ESI;
  float10 fVar1;
  float10 extraout_ST0;
  float fVar2;
  vec2 local_c;
  
  if (((param_1 == (InputHandlerType1 *)0x0) || (*(short *)(unaff_ESI + 0x30) != 0)) ||
     (*(float *)(unaff_ESI + 0x34) != 0.0)) {
    local_c.y = 0.0;
    local_c.x = 0.0;
  }
  else {
    Input::GetLSMovement_(param_1,&local_c);
  }
  fVar1 = scaled_invsqrt(local_c.x * local_c.x + local_c.y * local_c.y);
  fVar2 = (float)fVar1;
  if ((float10)1.0 <= fVar1) {
    fVar2 = 1.0;
  }
  if ((local_c.x == 0.0) && (local_c.y == 0.0)) {
    local_c.x = 0.0;
  }
  else {
    fVar1 = atan2(local_c.x,local_c.y);
    local_c.x = (float)fVar1;
  }
  angle = local_c.x;
  if (fVar2 <= 0.0) {
    fVar2 = 0.0;
    local_c.x = 0.0;
  }
  else {
    fVar2 = fVar2 * *(float *)(param_2 + 0x20);
    sin(local_c.x);
    local_c.x = (float)(extraout_ST0 * (float10)fVar2);
    fVar1 = (float10)cos(angle);
    fVar2 = (float)(fVar1 * (float10)fVar2);
  }
  *(float *)(unaff_ESI + 0x318) = local_c.x;
  *(undefined4 *)(unaff_ESI + 0x31c) = 0;
  *(float *)(unaff_ESI + 800) = fVar2;
  *(undefined4 *)(unaff_ESI + 0x734) = 0;
  *(undefined4 *)(unaff_ESI + 0x72c) = 0;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00090be0(int param_1,InputHandlerType1 *param_2)

{
  int iVar1;
  bool bVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  vec2 local_10;
  vec2 local_8;
  
  fVar4 = 0.0;
  iVar1 = *(int *)(param_1 + 8);
  if (runtime::dx_timer <= 0.0) {
    fVar5 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar5 = 0.0;
  }
  if (*(float *)(*(int *)(iVar1 + 8) + 0x930) <= 0.0) {
    fVar4 = *(float *)(*(int *)(iVar1 + 8) + 0x92c);
  }
  fVar4 = fVar4 * fVar5 + *(float *)(param_1 + 0x10);
  *(float *)(param_1 + 0x10) = fVar4;
  Input::GetLSMovement_(param_2,&local_10);
  ScriptType1::getControllerXY(param_2,&local_8);
  fVar3 = scaled_invsqrt(local_10.y * local_10.y + local_10.x * local_10.x);
  if ((float10)0.0 == fVar3) {
    fVar3 = scaled_invsqrt(local_8.y * local_8.y + local_8.x * local_8.x);
    if ((float10)0.0 == fVar3) {
      bVar2 = false;
      goto LAB_00090cdc;
    }
  }
  bVar2 = true;
LAB_00090cdc:
  *(undefined4 *)(iVar1 + 0x734) = 0;
  *(undefined4 *)(iVar1 + 0x72c) = 0;
  if ((*(float *)(param_1 + 0x18) <= fVar4 && fVar4 != *(float *)(param_1 + 0x18)) || (bVar2)) {
    *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0x1c);
  }
  return;
}




void FUN_00094530(int param_1,InputHandlerType1 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  vec2 local_8;
  
  iVar1 = *(int *)(param_1 + 8);
  iVar2 = *(int *)(iVar1 + 8);
  if (runtime::dx_timer <= 0.0) {
    fVar9 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar9 = 0.0;
  }
  fVar6 = 0.0;
  if (*(float *)(iVar2 + 0x930) <= 0.0) {
    fVar6 = *(float *)(iVar2 + 0x92c);
  }
  *(float *)(param_1 + 0x10) = fVar6 * fVar9 + *(float *)(param_1 + 0x10);
  *(undefined4 *)(iVar1 + 0x734) = 0;
  *(undefined4 *)(iVar1 + 0x72c) = 0;
  if ((*(int *)(iVar2 + 0x50) != 0) &&
     (iVar3 = **(int **)(*(int *)(iVar2 + 0x50) + 0x58), iVar3 != 0)) {
    fVar9 = *(float *)(iVar3 + 0x14);
    bVar4 = false;
    if (fVar9 != *(float *)(iVar3 + 0x10c)) {
      if (*(float *)(iVar3 + 0x1c) <= 0.0 && *(float *)(iVar3 + 0x1c) != 0.0) {
        fVar6 = *(float *)(iVar3 + 0x10c);
        fVar7 = fVar9;
      }
      else {
        fVar7 = *(float *)(iVar3 + 0x10c);
        fVar6 = fVar9;
      }
      if (fVar6 <= fVar7) {
        if ((fVar7 <= 0.6) || (0.6 < fVar6)) goto LAB_00094609;
        bVar4 = false;
      }
      else if ((0.6 < fVar7) || (fVar6 <= 0.6)) {
        bVar4 = false;
      }
      else {
LAB_00094609:
        bVar4 = true;
      }
    }
    if (bVar4) {
      iVar3 = *(int *)(*(int *)(iVar1 + 0x15c) + 8);
      *(byte *)(iVar3 + 4) = *(byte *)(iVar3 + 4) & 0xdf;
    }
  }
  Input::GetLSMovement_(param_2,&local_8);
  if ((0.010000001 < local_8.y * local_8.y + local_8.x * local_8.x) ||
     (ScriptType1::getControllerXY(param_2,&local_8),
     0.010000001 < local_8.y * local_8.y + local_8.x * local_8.x)) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  fVar9 = *(float *)(param_1 + 0x18);
  if ((*(int *)(iVar2 + 0x50) == 0) ||
     (iVar3 = **(int **)(*(int *)(iVar2 + 0x50) + 0x58), iVar3 == 0)) goto LAB_0009471f;
  fVar6 = *(float *)(iVar3 + 0x14);
  bVar5 = false;
  if (fVar6 != *(float *)(iVar3 + 0x10c)) {
    if (*(float *)(iVar3 + 0x1c) <= 0.0 && *(float *)(iVar3 + 0x1c) != 0.0) {
      fVar7 = *(float *)(iVar3 + 0x10c);
      fVar8 = fVar6;
    }
    else {
      fVar8 = *(float *)(iVar3 + 0x10c);
      fVar7 = fVar6;
    }
    if (fVar7 <= fVar8) {
      if ((fVar8 <= fVar9) || (fVar9 < fVar7)) goto LAB_00094704;
      bVar5 = false;
    }
    else if ((fVar9 < fVar8) || (fVar7 <= fVar9)) {
      bVar5 = false;
    }
    else {
LAB_00094704:
      bVar5 = true;
    }
  }
  if ((bVar5) && (*(int *)(param_1 + 0x1c) != 0)) {
    *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + -1;
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
LAB_0009471f:
  if ((*(int *)(iVar2 + 0x50) != 0) &&
     (iVar1 = **(int **)(*(int *)(iVar2 + 0x50) + 0x58), iVar1 != 0)) {
    bVar5 = false;
    if (*(char *)(iVar1 + 0x2a) == '\x01') {
      if (*(float *)(iVar1 + 0x1c) <= 0.0 && *(float *)(iVar1 + 0x1c) != 0.0) {
        bVar5 = 0.0 < *(float *)(iVar1 + 0x14);
      }
      else {
        bVar5 = *(float *)(iVar1 + 0x14) < 1.0;
      }
      if (bVar5) {
        bVar5 = false;
      }
      else {
        bVar5 = true;
      }
    }
    if (!bVar5) {
      if (!bVar4) {
        return;
      }
      if (*(int *)(param_1 + 0x1c) != 0) {
        return;
      }
    }
  }
  FUN_00134060(param_1);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_00095940(int *param_1,InputHandlerType1 *param_2)

{
  float fVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  bool bVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_c;
  vec2 local_8;
  
  iVar5 = (int)param_1;
  iVar2 = *(int *)((int)param_1 + 8);
  if (runtime::dx_timer <= 0.0) {
    fVar13 = runtime::DeltaTime * runtime::TimeScale;
  }
  else {
    fVar13 = 0.0;
  }
  fVar11 = 0.0;
  if (*(float *)(*(int *)(iVar2 + 8) + 0x930) <= 0.0) {
    fVar11 = *(float *)(*(int *)(iVar2 + 8) + 0x92c);
  }
  *(float *)((int)param_1 + 0x10) = fVar11 * fVar13 + *(float *)((int)param_1 + 0x10);
  piVar3 = *(int **)(iVar2 + 8);
  piVar6 = piVar3;
  if (((*(int *)(iVar2 + 0x48) != 0) &&
      (iVar8 = *(int *)(*(int *)(iVar2 + 0x48) + 0x998), iVar8 != 0)) &&
     (*(int *)(iVar8 + 0x10) != 0)) {
    if ((runtime::Config::IsPal == 0) || (uVar7 = 0x32, runtime::Config::Use60Hz != 0)) {
      uVar7 = 0x3c;
    }
    iVar8 = (int)param_1 + 0x50;
    param_1 = piVar3;
    FUN_0013b030(0x3e4ccccd,iVar8,uVar7 / 2);
    piVar6 = param_1;
  }
  param_1 = piVar6;
  fVar13 = 0.0;
  if (((0.0 < *(float *)(iVar5 + 0x48)) && (iVar8 = FUN_0003ccb0(), iVar8 != 0)) &&
     ((*(int *)(iVar2 + 0x2c8) != 0 && (*(int *)(*(int *)(iVar2 + 0x2c8) + 0x10) != 0)))) {
    FUN_0013b1b0(*(undefined4 *)(iVar5 + 0x48),iVar5 + 0x4c);
    fVar13 = 0.0;
  }
  iVar8 = piVar3[0x14];
  local_c = fVar13;
  if ((iVar8 != 0) && (**(int **)(iVar8 + 0x58) != 0)) {
    local_c = *(float *)(**(int **)(iVar8 + 0x58) + 0x14);
  }
  uVar7 = *(uint *)(iVar5 + 0x6c);
  if (((uVar7 == 0) || (fVar11 = *(float *)(iVar5 + 0x68), iVar8 == 0)) ||
     (iVar8 = **(int **)(iVar8 + 0x58), iVar8 == 0)) goto LAB_00095aff;
  fVar1 = *(float *)(iVar8 + 0x14);
  bVar4 = false;
  if (fVar1 != *(float *)(iVar8 + 0x10c)) {
    if (*(float *)(iVar8 + 0x1c) <= fVar13 && fVar13 != *(float *)(iVar8 + 0x1c)) {
      fVar14 = *(float *)(iVar8 + 0x10c);
      fVar12 = fVar1;
    }
    else {
      fVar12 = *(float *)(iVar8 + 0x10c);
      fVar14 = fVar1;
    }
    if (fVar14 <= fVar12) {
      if ((fVar12 <= fVar11) || (fVar11 < fVar14)) goto LAB_00095ad9;
      bVar4 = false;
    }
    else if ((fVar11 < fVar12) || (fVar14 <= fVar11)) {
      bVar4 = false;
    }
    else {
LAB_00095ad9:
      bVar4 = true;
    }
  }
  if (bVar4) {
    pbVar9 = (byte *)((uVar7 >> 3) + *(int *)(*(int *)(iVar2 + 0x15c) + 8));
    *pbVar9 = *pbVar9 | '\x01' << ((byte)uVar7 & 7);
  }
LAB_00095aff:
  if ((*(int *)(iVar2 + 0x84) == 0) ||
     (fVar11 = *(float *)(*(int *)(iVar2 + 0x84) + 0x18), fVar11 == fVar13)) {
    fVar11 = 0.5;
  }
  if (fVar11 * 0.9 <= local_c) {
    EntityMoveContext::updateXY((EntityMoveContext *)(iVar5 + 0x18),&Game::someGlobalPos);
  }
  else if (*(int *)(iVar5 + 0x28) == 0) {
    FUN_00095f30();
  }
  FUN_00095ea0(iVar2);
  FUN_00096060();
  if ((*(int *)(iVar5 + 0x5c) == 0) || (*(int *)(iVar2 + 0x48) != 0)) {
    bVar4 = false;
  }
  else {
    bVar4 = true;
  }
  Input::GetLSMovement_(param_2,&local_8);
  piVar3 = param_1;
  if (((0.010000001 < local_8.y * local_8.y + local_8.x * local_8.x) && (0.75 < local_c)) &&
     (*(int *)(iVar5 + 0x30) == 0)) {
    FUN_00096390(1);
    return;
  }
  if ((param_1[0x14] != 0) && (iVar2 = **(int **)(param_1[0x14] + 0x58), iVar2 != 0)) {
    bVar10 = false;
    if (*(char *)(iVar2 + 0x2a) == '\x01') {
      if (*(float *)(iVar2 + 0x1c) <= 0.0 && *(float *)(iVar2 + 0x1c) != 0.0) {
        bVar10 = 0.0 < *(float *)(iVar2 + 0x14);
      }
      else {
        bVar10 = *(float *)(iVar2 + 0x14) < 1.0;
      }
      if (bVar10) {
        bVar10 = false;
      }
      else {
        bVar10 = true;
      }
    }
    if (!bVar10) {
      if (!bVar4) {
        return;
      }
      if (*(int *)(iVar5 + 0x30) != 0) {
        return;
      }
    }
  }
  if (*(int *)(iVar5 + 0x2c) == 0) {
    iVar2 = *param_1;
    param_1 = (int *)0x29;
    (**(code **)(iVar2 + 0xc))(piVar3,&param_1);
  }
  if (*(short *)(iVar5 + 100) == 0) {
    FUN_00134180(0);
    return;
  }
  *(short *)(iVar5 + 0xc) = *(short *)(iVar5 + 100);
  return;
}




void FUN_000a2eb0(InputHandlerType1 *param_1)

{
  int *piVar1;
  undefined2 uVar2;
  int unaff_EBX;
  vec2 local_8;
  
  piVar1 = *(int **)(unaff_EBX + 8);
  if (*(int *)(unaff_EBX + 0x1c) != 0) {
    if (((float)piVar1[0x94] * (float)piVar1[0x94] + (float)piVar1[0x93] * (float)piVar1[0x93] +
         (float)piVar1[0x92] * (float)piVar1[0x92] <= 0.0) ||
       ((**(byte **)(piVar1[0x57] + 8) & 2) == 0)) {
      uVar2 = 0;
    }
    else {
      uVar2 = (**(code **)(*piVar1 + 0x40))(piVar1);
    }
    *(undefined2 *)(unaff_EBX + 0xc) = uVar2;
  }
  if (((*(int *)(piVar1[2] + 0x958) == 0) || (*(char *)(*(int *)(piVar1[2] + 0x958) + 0x20) == '\0')
      ) && (*(short *)(unaff_EBX + 0x1a) != 0)) {
    *(short *)(unaff_EBX + 0xc) = *(short *)(unaff_EBX + 0x1a);
  }
  if (*(short *)(unaff_EBX + 0x18) != 0) {
    Input::GetLSMovement_(param_1,&local_8);
    if (0.010000001 < local_8.y * local_8.y + local_8.x * local_8.x) {
      *(undefined2 *)(unaff_EBX + 0xc) = *(undefined2 *)(unaff_EBX + 0x18);
    }
  }
  return;
}




BOOL Input::PlayerIsPressingAnything(actor *param_1)

{
  InputHandlerType1 *handler;
  BOOL noneOfThoseAreDown;
  avatar *paVar1;
  vec2 v2;
  
  handler = (InputHandlerType1 *)param_1->input_handler_;
  GetLSMovement_(handler,&v2);
  if (v2.y * v2.y + v2.x * v2.x <= 0.010000001) {
    ScriptType1::getControllerXY(handler,&v2);
    if (v2.y * v2.y + v2.x * v2.x <= 0.010000001) {
      noneOfThoseAreDown =
           ContextHasButton(BUTTON_Y|BUTTON_X|BUTTON_B|BUTTON_A,(InputHandlerType3 *)handler);
      if (noneOfThoseAreDown == 0) {
        paVar1 = FUN_00128df0(&param_1->avatar,0,100.0,&v2,FUN_00080241,(undefined *)0x0,(vec3 *)0x0
                             );
        return (uint)(paVar1 != (avatar *)0x0);
      }
    }
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void switchD_000d410b::caseD_1(void)

{
  if ((*DAT_00506560 == 1) && (Game::DialogState == NotInDialog)) {
    *DAT_00506560 = 2;
  }
  return;
}




void Input::Handlers::SelectMenuItem(void)

{
  code *pcVar1;
  undefined4 *puVar2;
  int extraout_EAX;
  uint uVar3;
  short sVar4;
  undefined2 in_SS;
  uint *puVar5;
  
  if (((g_globalFlagset & 0x80000) != 0) || (malloced100->field0_0x0 == 2)) {
    sVar4 = (short)&stack0x00000000 + -4;
    puVar5 = (uint *)CONCAT22((short)((uint)&stack0x00000000 >> 0x10),sVar4);
    puVar2 = (undefined4 *)segment(in_SS,sVar4);
    *puVar2 = 0xe4e5f;
    uVar3 = FUN_0037907d();
    *puVar5 = uVar3;
                    // (*(code*)malloced100->inputState->callback)(malloced100->inputState->callbackValue);
    pcVar1 = *(code **)(extraout_EAX + 0x218);
    puVar5[-1] = 0xe4e66;
    (*pcVar1)();
  }
  return;
}




void GamepadState::UpdateHoldValues(GamepadState *pad)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = pad->buttonsPressedMask;
  if ((uVar1 & 4) == 0) {
    pad->dpadLHold = 0;
  }
  else {
    iVar2 = pad->dpadLHold + 1;
    pad->dpadLHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->dpadLHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 8) == 0) {
    pad->dpadRHold = 0;
  }
  else {
    iVar2 = pad->dpadRHold + 1;
    pad->dpadRHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->dpadRHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 2) == 0) {
    pad->dpadDHold = 0;
  }
  else {
    iVar2 = pad->dpadDHold + 1;
    pad->dpadDHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->dpadDHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 1) == 0) {
    pad->dpadUHold = 0;
  }
  else {
    iVar2 = pad->dpadUHold + 1;
    pad->dpadUHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->dpadUHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 0x1000) == 0) {
    pad->btnBlackHold = 0;
  }
  else {
    iVar2 = pad->btnBlackHold + 1;
    pad->btnBlackHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->btnBlackHold = 0x7ffffffe;
    }
  }
  if ((short)uVar1 < 0) {
    iVar2 = pad->rTrigHold + 1;
    pad->rTrigHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->rTrigHold = 0x7ffffffe;
    }
  }
  else {
    pad->rTrigHold = 0;
  }
  if ((uVar1 & 0x4000) == 0) {
    pad->lTrigHold = 0;
  }
  else {
    iVar2 = pad->lTrigHold + 1;
    pad->lTrigHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->lTrigHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 0x100) == 0) {
    pad->btnAHold = 0;
  }
  else {
    iVar2 = pad->btnAHold + 1;
    pad->btnAHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->btnAHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 0x200) == 0) {
    pad->btnBHold = 0;
  }
  else {
    iVar2 = pad->btnBHold + 1;
    pad->btnBHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->btnBHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 0x400) == 0) {
    pad->btnXHold = 0;
  }
  else {
    iVar2 = pad->btnXHold + 1;
    pad->btnXHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->btnXHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 0x800) == 0) {
    pad->btnYHold = 0;
  }
  else {
    iVar2 = pad->btnYHold + 1;
    pad->btnYHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->btnYHold = 0x7ffffffe;
    }
  }
  if ((uVar1 & 0x10) == 0) {
    pad->btnStartHold = 0;
  }
  else {
    iVar2 = pad->btnStartHold + 1;
    pad->btnStartHold = iVar2;
    if (0x7ffffffe < iVar2) {
      pad->btnStartHold = 0x7ffffffe;
      return;
    }
  }
  return;
}




void Input::Initialise(void)

{
  float *pfVar1;
  
  InitialiseInner();
                    // Memset 0
  pfVar1 = &g_gamepadStates[0].field23_0x4c.y;
  do {
    *(undefined2 *)(pfVar1 + -6) = 0;
    pfVar1[-8] = 0.0;
    pfVar1[-7] = 0.0;
    pfVar1[-0x13] = 0.0;
    pfVar1[-20] = 0.0;
    pfVar1[-0x11] = 0.0;
    pfVar1[-0x12] = 0.0;
    pfVar1[-0xf] = 0.0;
    pfVar1[-0x10] = 0.0;
    pfVar1[-9] = 0.0;
    pfVar1[-10] = 0.0;
    pfVar1[-0xb] = 0.0;
    pfVar1[-0xc] = 0.0;
    pfVar1[-0xd] = 0.0;
    pfVar1[-0xe] = 0.0;
    *(undefined2 *)(pfVar1 + 9) = 0;
    pfVar1[7] = 0.0;
    pfVar1[8] = 0.0;
    pfVar1[-4] = 0.0;
    pfVar1[-5] = 0.0;
    pfVar1[-2] = 0.0;
    pfVar1[-3] = 0.0;
    *pfVar1 = 0.0;
    ((vec2 *)(pfVar1 + -1))->x = 0.0;
    pfVar1[6] = 0.0;
    pfVar1[5] = 0.0;
    pfVar1[4] = 0.0;
    pfVar1[3] = 0.0;
    pfVar1[2] = 0.0;
    pfVar1[1] = 0.0;
    pfVar1 = pfVar1 + 42;
  } while ((int)pfVar1 < 0x507ce8);
  ::Gamepad::CombinedState.buttonsPressedMask = 0;
  ::Gamepad::CombinedState.lt = 0.0;
  ::Gamepad::CombinedState.rt = 0.0;
  ::Gamepad::CombinedState.normLsy = 0.0;
  ::Gamepad::CombinedState.normLsx = 0.0;
  ::Gamepad::CombinedState.normRsy = 0.0;
  ::Gamepad::CombinedState.normRsx = 0.0;
  ::Gamepad::CombinedState.dpadY = 0.0;
  ::Gamepad::CombinedState.dpadX = 0.0;
  ::Gamepad::CombinedState.field11_0x2c = 0;
  ::Gamepad::CombinedState.field10_0x28 = 0;
  ::Gamepad::CombinedState.rsy2__ = 0.0;
  ::Gamepad::CombinedState.rsx2_ = 0.0;
  ::Gamepad::CombinedState.lsy2_ = 0.0;
  ::Gamepad::CombinedState.lsx2_ = 0.0;
  ::Gamepad::CombinedState.buttonsReleasedMask = 0;
  ::Gamepad::CombinedState.field30_0x6c = 0.0;
  ::Gamepad::CombinedState.field31_0x70 = 0.0;
  ::Gamepad::CombinedState.field18_0x40 = 0.0;
  ::Gamepad::CombinedState.field17_0x3c = 0.0;
  ::Gamepad::CombinedState.someBtnMask___ = 0;
  ::Gamepad::CombinedState.field22_0x4a = 0;
  ::Gamepad::CombinedState.field19_0x44 = 0;
  ::Gamepad::CombinedState.field20_0x46 = 0;
  ::Gamepad::CombinedState.field23_0x4c.y = 0.0;
  ::Gamepad::CombinedState.field23_0x4c.x = 0.0;
  ::Gamepad::CombinedState.field29_0x68 = 0.0;
  ::Gamepad::CombinedState.field28_0x64 = 0.0;
  ::Gamepad::CombinedState.field27_0x60 = 0.0;
  ::Gamepad::CombinedState.field26_0x5c = 0.0;
  ::Gamepad::CombinedState.field25_0x58 = 0.0;
  ::Gamepad::CombinedState.field24_0x54 = 0.0;
  return;
}




void Input::ProcessRawInputs(void)

{
  GamepadState *pad;
  CameraViewportDetails_ptr_20_float pfVar2;
  int slot;
  
  ReadAndUpdateXInput(runtime::DeltaTime);
  slot = 0;
                    // Clear gamepads every update
  pfVar2 = &g_gamepadStates[0].dpadY;
  do {
    pad = ADJ(pfVar2);
    FUN_000fa110(pad);
    ADJ(pfVar2)->buttonsPressedMask = 0;
    ADJ(pfVar2)->lt = 0.0;
    ADJ(pfVar2)->rt = 0.0;
    ADJ(pfVar2)->normLsy = 0.0;
    pad->normLsx = 0.0;
    ADJ(pfVar2)->normRsy = 0.0;
    ADJ(pfVar2)->normRsx = 0.0;
    ADJ(pfVar2)->dpadY = 0.0;
    ADJ(pfVar2)->dpadX = 0.0;
    ADJ(pfVar2)->field11_0x2c = 0;
    ADJ(pfVar2)->field10_0x28 = 0;
    ADJ(pfVar2)->rsy2__ = 0.0;
    ADJ(pfVar2)->rsx2_ = 0.0;
    ADJ(pfVar2)->lsy2_ = 0.0;
    ADJ(pfVar2)->lsx2_ = 0.0;
    GamepadState::updateBySlot(pad,slot);
    GamepadState::UpdateHoldValues(pad);
    pfVar2 = pfVar2 + 0x2a;
    slot = slot + 1;
  } while ((int)pfVar2 < 0x507cac);
  FUN_000fa110(&::Gamepad::CombinedState);
  ::Gamepad::CombinedState.buttonsPressedMask = 0;
  ::Gamepad::CombinedState.lt = 0.0;
  ::Gamepad::CombinedState.rt = 0.0;
  ::Gamepad::CombinedState.normLsy = 0.0;
  ::Gamepad::CombinedState.normLsx = 0.0;
  ::Gamepad::CombinedState.normRsy = 0.0;
  ::Gamepad::CombinedState.normRsx = 0.0;
  ::Gamepad::CombinedState.dpadY = 0.0;
  ::Gamepad::CombinedState.dpadX = 0.0;
  ::Gamepad::CombinedState.field11_0x2c = 0;
  ::Gamepad::CombinedState.field10_0x28 = 0;
  ::Gamepad::CombinedState.rsy2__ = 0.0;
  ::Gamepad::CombinedState.rsx2_ = 0.0;
  ::Gamepad::CombinedState.lsy2_ = 0.0;
  ::Gamepad::CombinedState.lsx2_ = 0.0;
  ::Gamepad::GetCombinedState(&::Gamepad::CombinedState);
  GamepadState::UpdateHoldValues(&::Gamepad::CombinedState);
  return;
}




void GamepadState::updateBySlot(GamepadState *param_1,uint slot)

{
  ushort uVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  byte local_a;
  byte local_9;
  int lsx;
  int lsy;
  
  Input::SetLSDeadzoneHandler(0);
  Input::SetRSDeadzoneHandler(0);
  Gamepad::GetPadRawLS(slot,&lsx,&lsy);
  if (lsx < 32701) {
    if (lsx < -32700) {
      fVar3 = -32700.0;
    }
    else {
      fVar3 = (float)lsx;
      if (0.0 <= fVar3) goto LAB_000fa56a;
    }
    fVar3 = (fVar3 - -9800.0) * -4.3668122e-05 * -1.0;
    if (-1.0 <= fVar3) {
      if (0.0 < fVar3) {
        fVar3 = 0.0;
      }
    }
    else {
      fVar3 = -1.0;
    }
  }
  else {
    fVar3 = 32700.0;
LAB_000fa56a:
    fVar3 = (fVar3 - 9800.0) * 4.3668122e-05;
    if (fVar3 <= 1.0) {
      if (fVar3 < 0.0) {
        fVar3 = 0.0;
      }
    }
    else {
      fVar3 = 1.0;
    }
  }
  param_1->normLsx = fVar3;
  if (lsy < 0x7fbd) {
    if (lsy < -0x7fbc) {
      fVar4 = -32700.0;
    }
    else {
      fVar4 = (float)lsy;
      if (0.0 <= fVar4) goto LAB_000fa608;
    }
    fVar4 = (fVar4 - -9800.0) * -4.3668122e-05 * -1.0;
    if (-1.0 <= fVar4) {
      bVar2 = fVar4 < 0.0;
      goto LAB_000fa62a;
    }
    fVar4 = -1.0;
  }
  else {
    fVar4 = 32700.0;
LAB_000fa608:
    fVar4 = (fVar4 - 9800.0) * 4.3668122e-05;
    if (fVar4 <= 1.0) {
      bVar2 = 0.0 < fVar4;
LAB_000fa62a:
      if (!bVar2 && fVar4 != 0.0) {
        fVar4 = 0.0;
      }
    }
    else {
      fVar4 = 1.0;
    }
  }
  param_1->normLsy = fVar4;
  param_1->lsx2_ = fVar3;
  param_1->lsy2_ = param_1->normLsy;
  Gamepad::GetRawRS(slot,&lsx,&lsy);
  if (lsx < 0x7fbd) {
    if (lsx < -0x7fbc) {
      fVar3 = -32700.0;
    }
    else {
      fVar3 = (float)lsx;
      if (0.0 <= fVar3) goto LAB_000fa6a8;
    }
    fVar3 = (fVar3 - -9800.0) * -4.3668122e-05 * -1.0;
    if (-1.0 <= fVar3) {
      if (0.0 < fVar3) {
        fVar3 = 0.0;
      }
    }
    else {
      fVar3 = -1.0;
    }
  }
  else {
    fVar3 = 32700.0;
LAB_000fa6a8:
    fVar3 = (fVar3 - 9800.0) * 4.3668122e-05;
    if (fVar3 <= 1.0) {
      if (fVar3 < 0.0) {
        fVar3 = 0.0;
      }
    }
    else {
      fVar3 = 1.0;
    }
  }
  param_1->normRsx = fVar3;
  if (lsy < 0x7fbd) {
    if (lsy < -0x7fbc) {
      fVar3 = -32700.0;
    }
    else {
      fVar3 = (float)lsy;
      if (0.0 <= fVar3) goto LAB_000fa744;
    }
    fVar3 = (fVar3 - -9800.0) * -4.3668122e-05 * -1.0;
    if (fVar3 < -1.0) {
      fVar3 = -1.0;
      goto LAB_000fa76b;
    }
    bVar2 = fVar3 < 0.0;
  }
  else {
    fVar3 = 32700.0;
LAB_000fa744:
    fVar3 = (fVar3 - 9800.0) * 4.3668122e-05;
    if (1.0 < fVar3) {
      fVar3 = 1.0;
      goto LAB_000fa76b;
    }
    bVar2 = 0.0 < fVar3;
  }
  if (!bVar2 && fVar3 != 0.0) {
    fVar3 = 0.0;
  }
LAB_000fa76b:
  param_1->normRsy = fVar3;
  param_1->rsx2_ = param_1->normRsx;
  param_1->rsy2__ = param_1->normRsy;
  Gamepad::GetTriggersRaw(slot,&local_a,&local_9);
  if (0x8c < local_a) {
    local_a = 0x8c;
  }
  param_1->lt = (float)local_a * 0.007142857;
  if (0x8c < local_9) {
    local_9 = 0x8c;
  }
  param_1->rt = (float)local_9 * 0.007142857;
  uVar1 = Gamepad::GetButtonsRaw(slot);
  param_1->buttonsPressedMask = uVar1;
  if ((uVar1 & 1) == 0) {
    if ((uVar1 & 2) != 0) {
      param_1->dpadX = 0.0;
      param_1->dpadY = -1.0;
      return;
    }
    if ((uVar1 & 8) == 0) {
      if ((uVar1 & 4) == 0) {
        return;
      }
      fVar3 = -1.0;
    }
    else {
      fVar3 = 1.0;
    }
    param_1->dpadX = fVar3;
    param_1->dpadY = 0.0;
    return;
  }
  param_1->dpadX = 0.0;
  param_1->dpadY = 1.0;
  return;
}




void Gamepad::GetCombinedState(GamepadState *state)

{
  ushort uVar1;
  byte rt;
  int tx;
  int ty;
  uint i;
  int iVar2;
  int lti;
  int bti;
  bool bVar3;
  float fx;
  float idky;
  float fy;
  byte lt;
  char local_a;
  char local_9;
  int lsx;
  int lsy;
  
  Input::SetLSDeadzoneHandler(0);
  Input::SetRSDeadzoneHandler(0);
  ty = 0;
  tx = 0;
  i = 0;
  do {
    GetPadRawLS(i,&lsx,&lsy);
    tx = tx + lsx;
    ty = ty + lsy;
    i = i + 1;
  } while ((int)i < 4);
                    // Convert input from [-32701,32700] to [-1.0, 1.0]
  if (tx < 32701) {
    if (tx < -32700) {
      fx = -32700.0;
    }
    else {
      fx = (float)tx;
      if (0.0 <= fx) goto LAB_000fa8d9;
    }
    fx = (fx - -9800.0) * -4.3668122e-05 * -1.0;
    if (-1.0 <= fx) {
      if (0.0 < fx) {
        fx = 0.0;
      }
    }
    else {
      fx = -1.0;
    }
  }
  else {
    fx = 32700.0;
LAB_000fa8d9:
    fx = (fx - 9800.0) * 4.3668122e-05;
    if (fx <= 1.0) {
      if (fx < 0.0) {
        fx = 0.0;
      }
    }
    else {
      fx = 1.0;
    }
  }
  state->normLsx = fx;
  if (ty < 0x7fbd) {
    if (ty < -0x7fbc) {
      idky = -32700.0;
    }
    else {
      idky = (float)ty;
      if (0.0 <= idky) goto LAB_000fa975;
    }
    fy = (idky - -9800.0) * -4.3668122e-05 * -1.0;
    if (-1.0 <= fy) {
      bVar3 = fy < 0.0;
      goto LAB_000fa997;
    }
    fy = -1.0;
  }
  else {
    idky = 32700.0;
LAB_000fa975:
    fy = (idky - 9800.0) * 4.3668122e-05;
    if (fy <= 1.0) {
      bVar3 = 0.0 < fy;
LAB_000fa997:
      if (!bVar3 && fy != 0.0) {
        fy = 0.0;
      }
    }
    else {
      fy = 1.0;
    }
  }
  state->normLsy = fy;
  state->lsx2_ = fx;
  ty = 0;
  tx = 0;
  state->lsy2_ = state->normLsy;
  iVar2 = 0;
  do {
    GetRawRS(iVar2,&lsy,&lsx);
    tx = tx + lsy;
    ty = ty + lsx;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  if (tx < 0x7fbd) {
    if (tx < -0x7fbc) {
      fx = -32700.0;
    }
    else {
      fx = (float)tx;
      if (0.0 <= fx) goto LAB_000faa2b;
    }
    fx = (fx - -9800.0) * -4.3668122e-05 * -1.0;
    if (-1.0 <= fx) {
      if (0.0 < fx) {
        fx = 0.0;
      }
    }
    else {
      fx = -1.0;
    }
  }
  else {
    fx = 32700.0;
LAB_000faa2b:
    fx = (fx - 9800.0) * 4.3668122e-05;
    if (fx <= 1.0) {
      if (fx < 0.0) {
        fx = 0.0;
      }
    }
    else {
      fx = 1.0;
    }
  }
  state->normRsx = fx;
  if (ty < 0x7fbd) {
    if (ty < -0x7fbc) {
      fx = -32700.0;
    }
    else {
      fx = (float)ty;
      if (0.0 <= fx) goto LAB_000faac5;
    }
    fx = (fx - -9800.0) * -4.3668122e-05 * -1.0;
    if (fx < -1.0) {
      fx = -1.0;
      goto LAB_000faaec;
    }
    bVar3 = fx < 0.0;
  }
  else {
    fx = 32700.0;
LAB_000faac5:
    fx = (fx - 9800.0) * 4.3668122e-05;
    if (1.0 < fx) {
      fx = 1.0;
      goto LAB_000faaec;
    }
    bVar3 = 0.0 < fx;
  }
  if (!bVar3 && fx != 0.0) {
    fx = 0.0;
  }
LAB_000faaec:
  state->normRsy = fx;
  state->rsx2_ = state->normRsx;
  rt = 0;
  state->rsy2__ = state->normRsy;
  lt = 0;
  lti = 0;
  do {
    GetTriggersRaw(lti,&local_a,&local_9);
    lt = lt + local_a;
    rt = rt + local_9;
    lti = lti + 1;
  } while (lti < 4);
  if (0x8c < lt) {
    lt = 0x8c;
  }
                    // div 140
  state->lt = (float)lt * 0.007142857;
  if (140 < rt) {
    rt = 140;
  }
  state->rt = (float)rt * 0.007142857;
  bti = 0;
  do {
    uVar1 = GetButtonsRaw(bti);
    state->buttonsPressedMask = state->buttonsPressedMask | uVar1;
    uVar1 = state->buttonsPressedMask;
    bti = bti + 1;
  } while (bti < 4);
  if ((uVar1 & XINPUT_GAMEPAD_DPAD_UP) == 0) {
    if ((uVar1 & XINPUT_GAMEPAD_DPAD_DOWN) != 0) {
      state->dpadX = 0.0;
      state->dpadY = -1.0;
      return;
    }
    if ((uVar1 & XINPUT_GAMEPAD_DPAD_RIGHT) == 0) {
      if ((uVar1 & XINPUT_GAMEPAD_DPAD_LEFT) == 0) {
        return;
      }
      fx = -1.0;
    }
    else {
      fx = 1.0;
    }
    state->dpadX = fx;
    state->dpadY = 0.0;
    return;
  }
  state->dpadX = 0.0;
  state->dpadY = 1.0;
  return;
}




GamepadState * Input::GamepadStateFromControllerMask(undefined4 controllerMask)

{
  int32_t iVar1;
  int iVar2;
  
  switch(controllerMask) {
  default:
    return (GamepadState *)0x0;
  case 1:
  case 2:
  case 4:
  case 8:
    iVar1 = PlayerNumberFromMask(controllerMask);
    return g_gamepadStates + iVar1;
  case 0x10:
  case 0x20:
  case 0x40:
  case 0x80:
    iVar2 = FUN_00109720();
    return g_gamepadStates + iVar2;
  case 0xffffffff:
    return &::Gamepad::CombinedState;
  }
}




int32_t Input::PlayerNumberFromMask(undefined4 controllerMask)

{
  switch(controllerMask) {
  case 1:
    return 0;
  case 2:
    return 1;
  default:
    return -1;
  case 4:
    return 2;
  case 8:
    return 3;
  }
}




void Input::UpdateRumbles(void)

{
  vec3 vals;
  RumbleContextPlus0xc f;
  uint i;
  
  i = 0;
  f = &RumbleContexts[0].uint0xc;
  do {
    if (ADJ(f)->uint0xc != 0) {
      vals.y = (float)ADJ(f)->field1_0x4 * 0.01;
      vals.x = (float)ADJ(f).field0_0x0 * 0.01;
      vals.z = 0.0;
      SetRumble(i,vals);
    }
    f = f + 4;
    i = i + 1;
  } while ((int)f < 0x507d8c);
  return;
}




void ClearScriptType1(InputHandlerType1 *param_1)

{
  FUN_000fa110((GamepadState *)&param_1->field1_0x8);
  param_1->field15_0x40 = 0;
  param_1->field13_0x38 = 0;
  param_1->field14_0x3c = 0;
  param_1->field2_0xc = 0;
  param_1->field1_0x8 = (GamepadState *)0x0;
  param_1->field4_0x14 = 0;
  param_1->field3_0x10 = 0;
  param_1->field6_0x1c = 0;
  param_1->field5_0x18 = 0;
  param_1->field12_0x34 = 0;
  param_1->field11_0x30 = 0;
  param_1->field10_0x2c = 0;
  param_1->field9_0x28 = 0;
  param_1->field8_0x24 = 0;
  param_1->field7_0x20 = 0;
  return;
}




int InputHandlerType4::init(InputHandlerType4 *param_1)

{
  undefined4 uVar1;
  HeapTableEntry *pHVar2;
  int extraout_ECX;
  int i;
  InputHandlerBase **ppIVar3;
  
  ppIVar3 = param_1->subHandlers;
  i = 4;
  do {
    if (*ppIVar3 != (InputHandlerBase *)0x0) {
      InputHandlerBase::init(*ppIVar3);
    }
    ppIVar3 = ppIVar3 + 1;
    i = i + -1;
  } while (i != 0);
  i = FindHeapOf(param_1);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[i].heapHandle == (HANDLE)0x0) {
    pHVar2 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar2 = g_HeapTableBase + i;
  }
  runtime::CurrentHeapToAllocateFrom = i;
  XAPILIB::HeapFree(pHVar2->heapHandle,0,param_1);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return extraout_ECX;
}




int InputHandlerType5::init(InputHandlerType5 *param_1)

{
  param_1->field15_0x40 = 0;
  param_1->field16_0x44 = 0;
  param_1->field4_0x14 = 0;
  param_1->field3_0x10 = 0;
  param_1->field17_0x48 = 0;
  param_1->field6_0x1c = 0;
  param_1->field5_0x18 = 0;
  param_1->field8_0x24 = 0;
  param_1->field7_0x20 = 0;
  param_1->field14_0x3c = 0;
  param_1->field13_0x38 = 0;
  param_1->field12_0x34 = 0;
  param_1->field11_0x30 = 0;
  param_1->field10_0x2c = 0;
  param_1->field9_0x28 = 0;
  param_1->field34_0x84 = 0;
  param_1->field32_0x7c = 0;
  param_1->field33_0x80 = 0;
  param_1->field21_0x50 = 0;
  param_1->field20_0x4c = 0;
  param_1->field23_0x58 = 0;
  param_1->field22_0x54 = 0;
  param_1->field25_0x60 = 0;
  param_1->field24_0x5c = 0;
  param_1->field31_0x78 = 0;
  param_1->field30_0x74 = 0;
  param_1->field29_0x70 = 0;
  param_1->field28_0x6c = 0;
  param_1->field27_0x68 = 0;
  param_1->field26_0x64 = 0;
  return 0;
}




uint GetCurrentControllerPortBackup(void)

{
  int in_EAX;
  int iVar1;
  
  switch(*(undefined4 *)(in_EAX + 8)) {
  case 0:
    iVar1 = FUN_00107ff0(0x10);
    return (&runtime::Player1PortBit)[iVar1];
  case 1:
    iVar1 = FUN_00107ff0(0x20);
    return (&runtime::Player1PortBit)[iVar1];
  case 2:
    iVar1 = FUN_00107ff0(0x40);
    return (&runtime::Player1PortBit)[iVar1];
  case 3:
    iVar1 = FUN_00107ff0(0x80);
    return (&runtime::Player1PortBit)[iVar1];
  default:
    iVar1 = FUN_00107ff0(0);
    return (&runtime::Player1PortBit)[iVar1];
  }
}




uint InputCheckSet::check(InputCheckSet *param_1)

{
  uint uVar1;
  
  switch(param_1->field5_0x8) {
  case 0:
    uVar1 = GetGamepadHandle(0);
    return uVar1 & 0x10;
  case 1:
    uVar1 = GetGamepadHandle(0);
    return uVar1 & 0x20;
  case 2:
    uVar1 = GetGamepadHandle(0);
    return uVar1 & 0x40;
  case 3:
    uVar1 = GetGamepadHandle(0);
    return uVar1 & 0x80;
  default:
    GetGamepadHandle(0);
    return 0;
  }
}




int InputHandlerType1::init(InputHandlerType1 *script)

{
  script->field13_0x38 = 0;
  script->field14_0x3c = 0;
  script->field2_0xc = 0;
  script->field1_0x8 = (GamepadState *)0x0;
  script->field15_0x40 = 0;
  script->field4_0x14 = 0;
  script->field3_0x10 = 0;
  script->field6_0x1c = 0;
  script->field5_0x18 = 0;
  script->field12_0x34 = 0;
  script->field11_0x30 = 0;
  script->field10_0x2c = 0;
  script->field9_0x28 = 0;
  script->field8_0x24 = 0;
  script->field7_0x20 = 0;
  script->field32_0x7c = 0;
  script->field30_0x74 = 0;
  script->field31_0x78 = 0;
  script->field19_0x48 = 0;
  script->field18_0x44 = 0;
  script->field21_0x50 = 0;
  script->field20_0x4c = 0;
  script->field23_0x58 = 0;
  script->field22_0x54 = 0;
  script->field29_0x70 = 0;
  script->field28_0x6c = 0;
  script->field27_0x68 = 0;
  script->field26_0x64 = 0;
  script->field25_0x60 = 0;
  script->field24_0x5c = 0;
  return 0;
}




void FUN_00107ec0(InputHandlerType4 *param_1)

{
  FUN_000fa110((GamepadState *)param_1->subHandlers);
  Input::GamepadStateFromControllerMask(runtime::Player1PortBit);
  FUN_000fa190();
  return;
}




int Input::FirstPlayerPressed(XInputButton buttonMask)

{
  undefined4 controllerMask;
  GamepadState *state;
  uint i;
  int extraout_EDX;
  uint uVar1;
  
  if (buttonMask ==
      ~(TRIGGER_R|TRIGGER_L|BUTTON_WHITE|BUTTON_BLACK|BUTTON_Y|BUTTON_X|BUTTON_B|BUTTON_A|BUTTON_RS|
        BUTTON_LS|SELECT|START|DPAD_RIGHT|DPAD_LEFT|DPAD_DOWN|DPAD_UP)) {
    return -1;
  }
  uVar1 = 1;
  do {
    if ((uVar1 & buttonMask) != 0) {
      i = 0;
      do {
        switch(i) {
        case 0:
          controllerMask = 1;
          break;
        case 1:
          controllerMask = 2;
          break;
        case 2:
          controllerMask = 4;
          break;
        case 3:
          controllerMask = 8;
          break;
        default:
          controllerMask = 0;
        }
        state = GamepadStateFromControllerMask(controllerMask);
        if (((state->buttonsPressedMask & (ushort)uVar1) != 0) &&
           ((state->buttonsReleasedMask & (ushort)uVar1) == 0)) {
          return extraout_EDX;
        }
        i = extraout_EDX + 1;
      } while (i < 4);
    }
    uVar1 = uVar1 * 2;
    if (0x8000 < uVar1) {
      return -1;
    }
  } while( true );
}




void InputHandlerBase::init(InputHandlerBase *param_1)

{
  switch(param_1->type) {
  case TYPE_1:
    InputHandlerType1::init((InputHandlerType1 *)param_1);
    return;
  case TYPE_2:
    InputHandlerType1::init((InputHandlerType1 *)param_1);
    return;
  default:
    return;
  case TYPE_4_NESTED:
    InputHandlerType4::init((InputHandlerType4 *)param_1);
    return;
  case TYPE_5:
    InputHandlerType5::init((InputHandlerType5 *)param_1);
    return;
  }
}




uint Input::ExecuteHandler(InputHandlerType3 *param_1)

{
  uint uVar1;
  uint uVar2;
  InputCheckSet **check_sets;
  int iVar3;
  InputCheckSet *ics;
  
  uVar2 = runtime::Player1PortBit;
  switch((param_1->header).type) {
  default:
    return 0;
  case TYPE_2:
    uVar1 = GetGamepadHandle(0);
    return uVar1 & uVar2;
  case TYPE_3:
    uVar2 = GetGamepadHandle(0);
    return uVar2;
  case TYPE_4_NESTED:
    iVar3 = 0;
    check_sets = param_1->inputCheckSets;
    break;
  case TYPE_5:
    uVar2 = InputCheckSet::check((InputCheckSet *)param_1);
    return uVar2;
  }
  while (((ics = *check_sets, ics == (InputCheckSet *)0x0 || (ics->someBool == 0)) ||
         (uVar2 = InputCheckSet::check(ics), uVar2 != 0))) {
    iVar3 = iVar3 + 1;
    check_sets = check_sets + 1;
    if (3 < iVar3) {
      return 1;
    }
  }
  return 0;
}




BOOL IsButtonDown(int param_1,ushort btn)

{
  undefined4 *puVar1;
  BOOL BVar2;
  GamepadState *state;
  int *piVar3;
  int iVar4;
  
  switch(*(int *)param_1 + -1) {
  case 0:
  case 1:
  case 2:
  case 4:
                    // WARNING: Could not recover jumptable at 0x00108313. Too many branches
                    // WARNING: Treating indirect jump as call
    BVar2 = (*(code *)(&PTR_IsButtonDownBig__001083c8)[*(int *)param_1 + -1])();
    return BVar2;
  case 3:
    iVar4 = 0;
    piVar3 = (int *)(param_1 + 8);
    break;
  default:
    return 0;
  }
  do {
    puVar1 = (undefined4 *)*piVar3;
    state = (GamepadState *)(puVar1 + 2);
    if (puVar1[2] != -1) {
      switch(*puVar1) {
      case 1:
      case 2:
        break;
      case 3:
        state = &Gamepad::CombinedState;
        break;
      default:
        state = (GamepadState *)0x0;
        break;
      case 5:
        state = (GamepadState *)(puVar1 + 4);
      }
      if ((state->buttonsPressedMask & btn) != 0) {
        return 1;
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
    if (3 < iVar4) {
      return 0;
    }
  } while( true );
}




bool Input::IsButtonDownBig_(void *param_1,ushort param_2)

{
  return (*(ushort *)((int)param_1 + 0x40) & param_2) != 0;
}




bool Input::IsButtonDown(ushort param_1)

{
  return (::Gamepad::CombinedState.buttonsPressedMask & param_1) != 0;
}




bool Input::Param2InSomeMask(GamepadState *param_1,ushort param_2)

{
  return (param_1->someBtnMask___ & param_2) != 0;
}




bool Input::IsStartBackOrDpadRight_(ushort param_1)

{
  return (uRam00000038 & param_1) != 0;
}




BOOL Input::ContextHasButton(XInputButton button,InputHandlerType3 *handler)

{
  InputCheckSet *pIVar1;
  BOOL BVar2;
  GamepadState *state;
  uint uVar3;
  uint isDown;
  InputCheckSet **ppIVar4;
  int command;
  
  command = (handler->header).type - TYPE_1;
  switch(command) {
  case 0:
  case 1:
  case 2:
  case 4:
    BVar2 = (*(code *)(&PTR_Callback1_001084cc)[command])();
    return BVar2;
  case 3:
    isDown = 0;
    ppIVar4 = handler->inputCheckSets;
    command = 4;
    break;
  default:
    return 0;
  }
  do {
    pIVar1 = *ppIVar4;
    state = (GamepadState *)&pIVar1->field5_0x8;
    if (pIVar1->field5_0x8 != -1) {
      switch(*(undefined4 *)pIVar1) {
      case 1:
      case 2:
        break;
      case 3:
        state = &::Gamepad::CombinedState;
        break;
      default:
        state = (GamepadState *)0x0;
        break;
      case 5:
        state = (GamepadState *)&pIVar1[1].someBool;
      }
      if (((state->buttonsPressedMask & button) ==
           ~(TRIGGER_R|TRIGGER_L|BUTTON_WHITE|BUTTON_BLACK|BUTTON_Y|BUTTON_X|BUTTON_B|BUTTON_A|
             BUTTON_RS|BUTTON_LS|SELECT|START|DPAD_RIGHT|DPAD_LEFT|DPAD_DOWN|DPAD_UP)) ||
         ((state->buttonsReleasedMask & button) !=
          ~(TRIGGER_R|TRIGGER_L|BUTTON_WHITE|BUTTON_BLACK|BUTTON_Y|BUTTON_X|BUTTON_B|BUTTON_A|
            BUTTON_RS|BUTTON_LS|SELECT|START|DPAD_RIGHT|DPAD_LEFT|DPAD_DOWN|DPAD_UP))) {
        uVar3 = 0;
      }
      else {
        uVar3 = 1;
      }
      isDown = isDown | uVar3;
    }
    ppIVar4 = ppIVar4 + 1;
    command = command + -1;
  } while (command != 0);
  return isDown;
}




undefined4 Input::ButtonCheckCallbacks::Callback1(InputHandlerType1 *param_1)

{
  ushort unaff_BP;
  
  if (((param_1->field15_0x40 & unaff_BP) != 0) && ((param_1->field32_0x7c & unaff_BP) == 0)) {
    return 1;
  }
  return 0;
}




undefined4 Input::ButtonCheckCallbacks::CheckCombinedMask(void)

{
  ushort unaff_BP;
  
  if (((::Gamepad::CombinedState.buttonsPressedMask & unaff_BP) != 0) &&
     ((::Gamepad::CombinedState.buttonsReleasedMask & unaff_BP) == 0)) {
    return 1;
  }
  return 0;
}




undefined4 switchD_00108408::caseD_4(InputHandlerType1 *param_1)

{
  ushort unaff_BP;
  
  if (((*(ushort *)&param_1->field19_0x48 & unaff_BP) != 0) &&
     ((*(ushort *)&param_1->field_0x84 & unaff_BP) == 0)) {
    return 1;
  }
  return 0;
}




undefined4 Input::ButtonCheckCallbacks::Callback3(void)

{
  ushort unaff_BP;
  
  if (((uRam00000038 & unaff_BP) != 0) && ((uRam00000074 & unaff_BP) == 0)) {
    return 1;
  }
  return 0;
}




void Input::GetLSMovement_(InputHandlerType1 *param_1,vec2 *param_2)

{
  GamepadState *pGVar1;
  GamepadState *pGVar2;
  int index;
  GamepadState **ppGVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  
  index = (param_1->base).type - TYPE_1;
  switch(index) {
  case 0:
  case 1:
  case 2:
  case 4:
                    // WARNING: Could not recover jumptable at 0x00108603. Too many branches
                    // WARNING: Treating indirect jump as call
                    // If 1, 2, 3, or 5
    (*(code *)(&g_inputCallbacks)[index])();
    return;
  case 3:
    ppGVar3 = &param_1->field1_0x8;
    index = 4;
    break;
  default:
    param_2->y = 0.0;
    param_2->x = 0.0;
    return;
  }
  do {
    pGVar1 = *ppGVar3;
    pGVar2 = (GamepadState *)&pGVar1->normRsx;
    fVar5 = 0.0;
    fVar6 = 0.0;
    if (pGVar1->normRsx == -NAN) {
LAB_001086e3:
      if (0.0 <= fVar6) goto LAB_001086e8;
LAB_001086c5:
      fVar6 = (fVar6 - -9800.0) * -4.3668122e-05 * -1.0;
      if (-1.0 <= fVar6) {
        bVar4 = fVar6 < 0.0;
        goto LAB_00108706;
      }
      fVar6 = -1.0;
    }
    else {
      switch(pGVar1->normLsx) {
      case 1.4013e-45:
      case 2.8026e-45:
        break;
      case 4.2039e-45:
        pGVar2 = &::Gamepad::CombinedState;
        break;
      default:
        pGVar2 = (GamepadState *)0x0;
        break;
      case 7.00649e-45:
        pGVar2 = (GamepadState *)&pGVar1->dpadX;
      }
      fVar6 = pGVar2->normLsy;
      fVar5 = pGVar2->normLsx;
      if (fVar6 <= 32700.0) {
        if (-32700.0 <= fVar6) goto LAB_001086e3;
        fVar6 = -32700.0;
        goto LAB_001086c5;
      }
      fVar6 = 32700.0;
LAB_001086e8:
      fVar6 = (fVar6 - 9800.0) * 4.3668122e-05;
      if (fVar6 <= 1.0) {
        bVar4 = 0.0 < fVar6;
LAB_00108706:
        if (!bVar4 && fVar6 != 0.0) {
          fVar6 = 0.0;
        }
      }
      else {
        fVar6 = 1.0;
      }
    }
    if (fVar5 <= 32700.0) {
      if (-32700.0 <= fVar5) {
        if (0.0 <= fVar5) goto LAB_00108748;
      }
      else {
        fVar5 = -32700.0;
      }
      fVar5 = (fVar5 - -9800.0) * -4.3668122e-05 * -1.0;
      if (-1.0 <= fVar5) {
        bVar4 = fVar5 < 0.0;
        goto LAB_00108766;
      }
      fVar5 = -1.0;
    }
    else {
      fVar5 = 32700.0;
LAB_00108748:
      fVar5 = (fVar5 - 9800.0) * 4.3668122e-05;
      if (fVar5 <= 1.0) {
        bVar4 = 0.0 < fVar5;
LAB_00108766:
        if (!bVar4 && fVar5 != 0.0) {
          fVar5 = 0.0;
        }
      }
      else {
        fVar5 = 1.0;
      }
    }
    ppGVar3 = ppGVar3 + 1;
    index = index + -1;
    param_2->x = fVar5;
    param_2->y = fVar6;
    if (index == 0) {
      return;
    }
  } while( true );
}




void FUN_00108de0(InputHandlerType1 *param_1)

{
  int iVar1;
  GamepadState **ppGVar2;
  
  iVar1 = (param_1->base).type - TYPE_1;
  switch(iVar1) {
  case 0:
  case 1:
  case 2:
  case 4:
                    // WARNING: Could not recover jumptable at 0x00108df3. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)(&PTR_LAB_00108ea8)[iVar1])();
    return;
  case 3:
    ppGVar2 = &param_1->field1_0x8;
    iVar1 = 4;
    break;
  default:
    return;
  }
  do {
    if ((*ppGVar2)->normRsx != -NAN) {
      switch((*ppGVar2)->normLsx) {
      case 1.4013e-45:
      case 2.8026e-45:
        break;
      case 4.2039e-45:
        break;
      default:
        break;
      case 7.00649e-45:
      }
    }
    ppGVar2 = ppGVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}




void RunInputCallbacks(InputHandlerType1 *param_1)

{
  GamepadState *pGVar1;
  GamepadState *pGVar2;
  int iVar3;
  float *unaff_EBX;
  GamepadState **ppGVar4;
  
  iVar3 = (param_1->base).type - TYPE_1;
  switch(iVar3) {
  case 0:
  case 1:
  case 2:
  case 4:
                    // WARNING: Could not recover jumptable at 0x001090b3. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)(&PTR_FUN_00109154)[iVar3])();
    return;
  case 3:
    ppGVar4 = &param_1->field1_0x8;
    iVar3 = 4;
    do {
      pGVar1 = *ppGVar4;
      pGVar2 = (GamepadState *)&pGVar1->normRsx;
      if (pGVar1->normRsx != -NAN) {
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
        pGVar2->normRsx = *unaff_EBX;
        pGVar2->normRsy = unaff_EBX[1];
      }
      ppGVar4 = ppGVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}




void FUN_00109180(InputHandlerType4 *list,vec2 *param_2)

{
  undefined4 *puVar1;
  GamepadState *pGVar2;
  int status;
  void *ppAVar3;
  
  status = (list->header).type - TYPE_1;
  switch(status) {
  case 0:
  case 1:
  case 2:
  case 4:
                    // WARNING: Could not recover jumptable at 0x00109193. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)(&PTR_FUN_00109234)[status])();
    return;
  case 3:
    ppAVar3 = list->subHandlers;
    status = 4;
    do {
      puVar1 = *(undefined4 **)ppAVar3;
      pGVar2 = (GamepadState *)(puVar1 + 2);
      if (puVar1[2] != -1) {
        switch(*puVar1) {
        case 1:
        case 2:
          break;
        case 3:
          pGVar2 = &Gamepad::CombinedState;
          break;
        default:
          pGVar2 = (GamepadState *)0x0;
          break;
        case 5:
          pGVar2 = (GamepadState *)(puVar1 + 4);
        }
        pGVar2->lt = param_2->x;
        pGVar2->rt = param_2->y;
      }
      ppAVar3 = (void *)((int)ppAVar3 + 4);
      status = status + -1;
    } while (status != 0);
  }
  return;
}




void FUN_00109260(InputHandlerType4 *param_1,float *param_2)

{
  InputHandlerBase *pIVar1;
  GamepadState *pGVar2;
  int iVar3;
  InputHandlerBase **ppIVar4;
  
  iVar3 = (param_1->header).type - TYPE_1;
  switch(iVar3) {
  case 0:
  case 1:
  case 2:
  case 4:
                    // WARNING: Could not recover jumptable at 0x00109273. Too many branches
                    // WARNING: Treating indirect jump as call
                    // If non-nested
    (*(code *)InputHandlersCallbackGroup[iVar3])();
    return;
  case 3:
                    // If nested
    ppIVar4 = param_1->subHandlers;
    iVar3 = 4;
    do {
      pIVar1 = *ppIVar4;
      pGVar2 = (GamepadState *)(pIVar1 + 1);
      if (pIVar1[1].type != 0xffffffff) {
        switch(pIVar1->type) {
        case TYPE_1:
        case TYPE_2:
          break;
        case TYPE_3:
          pGVar2 = &Gamepad::CombinedState;
          break;
        default:
          pGVar2 = (GamepadState *)0x0;
          break;
        case TYPE_5:
          pGVar2 = (GamepadState *)(pIVar1 + 2);
        }
        pGVar2->dpadX = *param_2;
        pGVar2->dpadY = param_2[1];
      }
      ppIVar4 = ppIVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}




void runtime::PushInputHandlerAndSetActive(InputHandlerBase *handler,char *handlerName)

{
  char *name;
  char c;
  Script2TypeNode *tail;
  
  if (Input::NumInputHandlers != 0) {
    name = Input::InputHandlers->head->handlerName +
           (Input::NumInputHandlers - 1) * (uint)Input::InputHandlers->valueSize + 0x44;
    name[0] = '\0';
    name[1] = '\0';
    name[2] = '\0';
    name[3] = '\0';
  }
  if (Input::InputHandlers->tail == Input::InputHandlers->end) {
    Input::InputHandlers = (Buffer<> *)ExtendArray((Buffer *)Input::InputHandlers);
  }
  tail = Input::InputHandlers->tail;
                    // Update the tail
  Input::InputHandlers->tail =
       (Script2TypeNode *)(tail->handlerName + (Input::InputHandlers->valueSize - 4));
  tail->next = (InputHandlerType4 *)handler;
  tail->isCurrent = 0;
  tail->field3_0x4c = 0;
  name = handlerName;
  do {
    c = *name;
    name[(int)tail + (4 - (int)handlerName)] = c;
    name = name + 1;
  } while (c != '\0');
  Input::NumInputHandlers = Input::NumInputHandlers + 1;
  SetCurrentInputHandler(handlerName);
  return;
}




void FUN_00109470(InputHandlerType4 *param_1)

{
  int iVar1;
  uint uVar2;
  InputHandlerType4 *pIVar3;
  Script2TypeNode *pSVar4;
  InputHandlerType4 *pIVar5;
  
  uVar2 = Events::EventCount1;
  iVar1 = (param_1->header).type - TYPE_1;
  switch(iVar1) {
  case 0:
  case 1:
  case 2:
  case 3:
    pIVar5 = param_1;
    break;
  case 4:
    pIVar5 = (InputHandlerType4 *)param_1[7].subHandlers[2];
    break;
  default:
    pIVar5 = (InputHandlerType4 *)0x0;
  }
  for (pSVar4 = Input::InputHandlers->head; pSVar4 < Input::InputHandlers->tail; pSVar4 = pSVar4 + 1
      ) {
    if (pSVar4->next == pIVar5) goto LAB_001094bd;
  }
  pSVar4 = (Script2TypeNode *)0x0;
LAB_001094bd:
  switch(iVar1) {
  default:
    pIVar3 = (InputHandlerType4 *)0x0;
    break;
  case 1:
  case 2:
  case 4:
    pIVar3 = param_1;
  }
  if ((pIVar3 != pIVar5) || (pSVar4->field3_0x4c != Events::EventCount1)) {
    if (pSVar4->isCurrent == 0) {
      switch(iVar1) {
      case 0:
        InputHandlerType1::init((InputHandlerType1 *)param_1);
        pSVar4->field3_0x4c = uVar2;
        return;
      case 1:
        InputHandlerType1::init((InputHandlerType1 *)param_1);
        pSVar4->field3_0x4c = uVar2;
        return;
      case 3:
        InputHandlerType4::init(param_1);
        break;
      case 4:
        InputHandlerType5::init((InputHandlerType5 *)param_1);
        pSVar4->field3_0x4c = uVar2;
        return;
      }
    }
    else {
      switch(iVar1) {
      case 0:
        ClearScriptType1((InputHandlerType1 *)param_1);
        pSVar4->field3_0x4c = uVar2;
        return;
      case 1:
        FUN_00107ec0(param_1);
        pSVar4->field3_0x4c = uVar2;
        return;
      case 4:
        FUN_00107c30();
        pSVar4->field3_0x4c = uVar2;
        return;
      }
    }
    pSVar4->field3_0x4c = uVar2;
  }
  return;
}




BOOL runtime::SetCurrentInputHandler(char *name)

{
  Script2TypeNode *found;
  Script2TypeNode *node;
  Script2TypeNode *tail;
  
  found = GetInputHandlerByName(name);
  found->isCurrent = 1;
  tail = Input::InputHandlers->tail;
  for (node = Input::InputHandlers->head; node < tail; node = node + 1) {
    if (node != found) {
      node->isCurrent = 0;
    }
  }
  return 1;
}




void Input::BindControllerToPlayer_(int32_t player,undefined4 param_2)

{
  int iVar1;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  uint extraout_ECX_03;
  
  switch(player) {
  case 0:
    iVar1 = FUN_00107ff0(param_2);
    (&runtime::Player1PortBit)[iVar1] = extraout_ECX;
    return;
  case 1:
    iVar1 = FUN_00107ff0(param_2);
    (&runtime::Player1PortBit)[iVar1] = extraout_ECX_00;
    return;
  case 2:
    iVar1 = FUN_00107ff0(param_2);
    (&runtime::Player1PortBit)[iVar1] = extraout_ECX_01;
    return;
  case 3:
    iVar1 = FUN_00107ff0(param_2);
    (&runtime::Player1PortBit)[iVar1] = extraout_ECX_02;
    return;
  default:
    iVar1 = FUN_00107ff0(param_2);
    (&runtime::Player1PortBit)[iVar1] = extraout_ECX_03;
    return;
  }
}




void LeadsToReadInput1(void)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = FUN_00131c50(0,&BaronDraw_00545994);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    if ((g_UIElement10 != (Scene *)0x0) || (FUN_0012d540(), g_UIElement10 != (Scene *)0x0)) {
      Input::UpdateMenuInput((InputHandlerType3 *)0x0,g_UIElement10);
    }
    FUN_0012ef60(FLOAT_ARRAY_005459a8,&g_someVec3);
    return;
  }
  if (g_UIElement10 == (Scene *)0x0) {
    return;
  }
  Scene::free(g_UIElement10);
  g_UIElement10 = (Scene *)0x0;
  return;
}




int FUN_00136620(InputHandlerBase *param_1)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  actorMind *unaff_EBX;
  undefined4 local_4;
  
  iVar1 = FUN_00136b00(0xffffffff,unaff_EBX,param_1,(vec3 *)(in_EAX + 0x10),
                       *(float *)(in_EAX + 0x24) + 2.5,*(float *)(in_EAX + 0x28),
                       *(float *)(in_EAX + 0x2c),0,&local_4);
  if ((iVar1 == 0) && (iVar2 = FUN_001373f0(unaff_EBX,(vec3 *)(in_EAX + 0x10)), iVar2 != 0)) {
    return 1;
  }
  return iVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Input::UpdateMenuInput(InputHandlerType3 *script3,Scene *scene)

{
  int *piVar1;
  code *pcVar2;
  BOOL mask_matches;
  int index;
  int iVar3;
  float fVar4;
  float fVar5;
  float fStack_8;
  float fStack_4;
  int maskIndex;
  uint scene_state;
  
  if (script3 != (InputHandlerType3 *)0x0) {
    Scripting::Input::ResolveHandlers();
  }
  piVar1 = scene->field3815_0x1024;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x10))(piVar1);
  }
  scene_state = scene->sceneState;
  if (scene_state == 1) {
    if (runtime::dx_timer <= 0.0) {
      fVar5 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar5 = 0.0;
    }
    if ((0.0 < scene->someTimer) &&
       (fVar5 = scene->someTimer - fVar5, scene->someTimer = fVar5, fVar5 <= 0.0)) {
      scene->someTimer = 0.0;
    }
    fVar5 = scene->originalTimerValue;
    fVar4 = scene->field2227_0x9d8;
    if (fVar5 != 0.0) {
      fVar5 = ((scene->someTimer - fVar5) / (0.0 - fVar5)) * fVar4;
      if (fVar4 <= 0.0) {
        if ((fVar4 <= fVar5) && (fVar4 = fVar5, 0.0 < fVar5)) {
          fVar4 = 0.0;
        }
      }
      else if ((fVar5 <= fVar4) && (fVar4 = fVar5, fVar5 < 0.0)) {
        fVar4 = 0.0;
      }
    }
    scene->field3_0xc = (int)fVar4;
    if ((scene->someTimer <= 0.001 && scene->someTimer != 0.001) &&
       (scene->field3_0xc = (int)scene->field2227_0x9d8, scene->sceneState != 2)) {
      scene->sceneState = 2;
    }
  }
  else if (scene_state == 2) {
    if ((script3 != (InputHandlerType3 *)0x0) && (index = 0, 0 < scene->numInputCallbacks)) {
      iVar3 = 0;
      do {
        maskIndex = *(int *)((int)scene->inputContextStart->callbacks + iVar3 + -0x44);
        switch(maskIndex) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
                    // Digital cases
          mask_matches = ContextHasButton(ButtonMasks[maskIndex],script3);
          if (mask_matches != 0) {
            if (scene->hasAudio_ != 0) {
              Audio::PlaySoundWithFlags(scene->selectAudio,1);
            }
LAB_001425d5:
            pcVar2 = scene->inputContextStart->callbacks[index].callback;
            if (pcVar2 != (code *)0x0) {
                    // Reacts to input
                    // 
                    // Ignores buttons that aren't bound (eg. y in menus that dont use y)
              (*pcVar2)();
            }
            return 1;
          }
          break;
        case 6:
        case 7:
                    // Directional cases
          FUN_001429e0((int)&fStack_8,script3);
          if ((fStack_8 != 0.0) || (fStack_4 != 0.0)) goto LAB_001425d5;
        }
        index = index + 1;
        iVar3 = iVar3 + 0x48;
        if (scene->numInputCallbacks <= index) {
          return 0;
        }
      } while( true );
    }
  }
  else if (scene_state == 3) {
    if (runtime::dx_timer <= 0.0) {
      fVar5 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar5 = 0.0;
    }
    if ((0.0 < scene->someTimer) &&
       (fVar5 = scene->someTimer - fVar5, scene->someTimer = fVar5, fVar5 <= 0.0)) {
      scene->someTimer = 0.0;
    }
    fVar5 = scene->field2227_0x9d8;
    if (scene->originalTimerValue != 0.0) {
      fVar4 = (scene->someTimer / scene->originalTimerValue) * fVar5;
      if (fVar5 <= 0.0) {
        if ((fVar5 <= fVar4) && (fVar5 = fVar4, 0.0 < fVar4)) {
          fVar5 = 0.0;
        }
      }
      else if ((fVar4 <= fVar5) && (fVar5 = fVar4, fVar4 < 0.0)) {
        fVar5 = 0.0;
      }
    }
    scene->field3_0xc = (int)fVar5;
    if ((fVar5 < 0.001) &&
       (*(uint *)(*(int *)scene->field3814_0x1020 + 8) <=
        *(uint *)(*(int *)scene->field3814_0x1020 + 4))) {
      FUN_00142c20(1,scene);
      return 0;
    }
  }
  return 0;
}




void DrawXboxButtons_(int param_1)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  float fVar4;
  int *local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  if ((((*(GlobalFlagset *)(in_EAX + 0x10b4) & g_globalFlagset) == 0) &&
      (*(int *)(in_EAX + 0x94c) != 0)) &&
     (0.001 < *(float *)(in_EAX + 0xc) || *(float *)(in_EAX + 0xc) == 0.001)) {
    local_10 = *(undefined4 *)(in_EAX + 0xc);
    iVar2 = 0;
    local_c = local_10;
    if (0 < *(int *)(in_EAX + 0x954)) {
      local_14 = (int *)(in_EAX + 0x9a8);
      iVar3 = in_EAX + 0x958;
      do {
        iVar1 = *local_14;
        if (iVar1 != 0) {
          if (param_1 == 0) {
            FUN_001221b0(iVar1,*(TextDrawData **)(in_EAX + 0x9dc),0xff);
          }
          else {
            DrawMalloced100Value
                      (iVar1,iVar3,&local_10,0,*(TextDrawData **)(in_EAX + 0x9dc),0xffffffff);
          }
        }
        iVar2 = iVar2 + 1;
        local_14 = local_14 + 1;
        iVar3 = iVar3 + 8;
      } while (iVar2 < *(int *)(in_EAX + 0x954));
    }
    iVar2 = *(int *)(in_EAX + 0x1024);
    if (iVar2 != 0) {
      fVar4 = *(float *)(in_EAX + 0x102c) * *(float *)(in_EAX + 0xc);
      if (*(float *)(iVar2 + 0x200) != fVar4) {
        *(float *)(iVar2 + 0x200) = fVar4;
        *(undefined4 *)(iVar2 + 0x2a8) = 0;
      }
      (**(code **)(**(int **)(in_EAX + 0x1024) + 0x14))
                (*(int **)(in_EAX + 0x1024),
                 (int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,3);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void FUN_001429e0(int param_1,InputHandlerType3 *param_2)

{
  BOOL BVar1;
  float fVar2;
  float fVar3;
  
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)param_1 = 0;
  Input::GetLSMovement_((InputHandlerType1 *)param_2,(vec2 *)param_1);
  if ((*(float *)param_1 <= 0.2 && *(float *)param_1 != 0.2) && (-0.2 < *(float *)param_1)) {
    *(undefined4 *)param_1 = 0;
  }
  if ((*(float *)(param_1 + 4) <= 0.2 && *(float *)(param_1 + 4) != 0.2) &&
     (-0.2 < *(float *)(param_1 + 4))) {
    *(undefined4 *)(param_1 + 4) = 0;
  }
  BVar1 = IsButtonDown((int)param_2,4);
  fVar2 = -1.0;
  fVar3 = 1.0;
  if (BVar1 == 0) {
    BVar1 = IsButtonDown((int)param_2,8);
    if (BVar1 != 0) {
      *(float *)param_1 = fVar3;
    }
  }
  else {
    *(float *)param_1 = -1.0;
  }
  BVar1 = IsButtonDown((int)param_2,2);
  if (BVar1 != 0) {
    *(float *)(param_1 + 4) = fVar2;
    return;
  }
  BVar1 = IsButtonDown((int)param_2,1);
  if (BVar1 != 0) {
    *(float *)(param_1 + 4) = fVar3;
  }
  return;
}




void FUN_00142f00(int *param_1,InputHandlerType3 *param_2)

{
  bool bVar1;
  int iVar2;
  BOOL BVar3;
  int iVar4;
  int *piVar5;
  
  if (*param_1 == 2) {
    bVar1 = true;
    iVar4 = 0;
    piVar5 = param_1 + 0x17;
    do {
      if (!bVar1) {
        return;
      }
      if ((*piVar5 != 0) && (BVar3 = IsButtonDown((int)param_2,(ushort)*piVar5), BVar3 == 0)) {
        bVar1 = false;
      }
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar4 < 2);
    if (!bVar1) {
      return;
    }
    *param_1 = 3;
    param_1[1] = 0;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
    return;
  }
  if (*param_1 != 3) {
    return;
  }
  if (param_1[0x17] != 0) {
    iVar4 = 0;
    do {
      iVar2 = FUN_00108500();
      if (iVar2 != 0) {
        *param_1 = 2;
        param_1[1] = 0;
        param_1[0x1a] = 0;
        param_1[0x1b] = 0;
        break;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
  }
  if (param_1[0x1a] == 0) {
    BVar3 = Input::ContextHasButton(*(XInputButton *)(param_1 + param_1[1] + 2),param_2);
    if (BVar3 != 0) {
      param_1[0x1a] = 1;
      goto LAB_00142fe5;
    }
    BVar3 = Input::ContextHasButton
                      (TRIGGER_R|TRIGGER_L|BUTTON_WHITE|BUTTON_BLACK|BUTTON_Y|BUTTON_X|BUTTON_B|
                       BUTTON_A|BUTTON_RS|BUTTON_LS|SELECT|START|DPAD_RIGHT|DPAD_LEFT|DPAD_DOWN|
                       DPAD_UP,param_2);
    if (BVar3 == 0) goto LAB_00142fe5;
    param_1[1] = 0;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
  }
  else {
    if (param_1[0x1b] != 0) goto LAB_00142fe5;
    iVar4 = FUN_00108500();
    if (iVar4 != 0) {
      param_1[0x1b] = 1;
      goto LAB_00142fe5;
    }
    BVar3 = Input::ContextHasButton
                      (TRIGGER_R|TRIGGER_L|BUTTON_WHITE|BUTTON_BLACK|BUTTON_Y|BUTTON_X|BUTTON_B|
                       BUTTON_A|BUTTON_RS|BUTTON_LS|SELECT|START|DPAD_RIGHT|DPAD_LEFT|DPAD_DOWN|
                       DPAD_UP,param_2);
    if (BVar3 == 0) goto LAB_00142fe5;
    param_1[1] = 0;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
  }
  *param_1 = 3;
LAB_00142fe5:
  if ((param_1[0x1a] != 0) && (param_1[0x1b] != 0)) {
    iVar4 = param_1[1];
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
    param_1[1] = iVar4 + 1;
    if (param_1[0x16] < iVar4 + 1) {
      *param_1 = 4;
      return;
    }
  }
  return;
}




bool Input::AnyPlayerPressedAOrStart(void)

{
  InputHandlerType1 *handler;
  BOOL BVar1;
  BOOL BVar2;
  
  handler = GlobalInputHandler;
  BVar1 = ContextHasButton(BUTTON_A,(InputHandlerType3 *)GlobalInputHandler);
  BVar2 = ContextHasButton(START,(InputHandlerType3 *)handler);
  if (BVar1 == 0) {
    if (BVar2 == 0) {
      return false;
    }
    switch((handler->base).type) {
    case TYPE_3:
    case TYPE_4_NESTED:
      _DAT_004340e8 = FirstPlayerPressed(START);
      return _DAT_004340e8 != -1;
    }
  }
  else {
    if (BVar2 != 0) {
      return false;
    }
    switch((handler->base).type) {
    case TYPE_3:
    case TYPE_4_NESTED:
      _DAT_004340e8 = FirstPlayerPressed(BUTTON_A);
      return _DAT_004340e8 != -1;
    }
  }
  _DAT_004340e8 = 0;
  return true;
}




bool dpadRight(void)

{
  BOOL BVar1;
  
  BVar1 = Input::ContextHasButton(DPAD_RIGHT,(InputHandlerType3 *)Input::GlobalInputHandler);
  return BVar1 != 0;
}




bool hasDpadUp(void)

{
  BOOL BVar1;
  
  BVar1 = Input::ContextHasButton(DPAD_UP,(InputHandlerType3 *)Input::GlobalInputHandler);
  return BVar1 != 0;
}




bool hasDpadDown(void)

{
  BOOL BVar1;
  
  BVar1 = Input::ContextHasButton(DPAD_DOWN,(InputHandlerType3 *)Input::GlobalInputHandler);
  return BVar1 != 0;
}




undefined4 isLSRight(void)

{
  vec2 local_8;
  
  Input::GetLSMovement_(Input::GlobalInputHandler,&local_8);
  if (0.25 < local_8.x) {
    return 1;
  }
  return 0;
}



TextInstance *
TextInstance::ctor(LPCWSTR str,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,void *param_6,undefined4 param_7)

{
  TextInstance *puVar1;
  
  puVar1 = malloc_(0x23c);
  puVar1->field0_0x0 = 0;
  puVar1->field1_0x4 = 0;
  XAPILIB::lstrcpynW(puVar1->textContent,str,0xff);
  puVar1->field6_0x20c = param_3;
  puVar1->field5_0x208 = param_2;
  puVar1->field7_0x210 = param_4;
  puVar1->demoCallback = param_6;
  puVar1->field8_0x214 = param_5;
  puVar1->field10_0x21c = param_7;
  puVar1->field12_0x224 = 0;
  puVar1->field13_0x228 = 0;
  puVar1->field11_0x220 = 0;
  puVar1->field14_0x22c = 0;
  puVar1->field23_0x238 = 0;
  return puVar1;
}



undefined4 *
FUN_001433c0(LPCWSTR param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            float *param_9,undefined4 param_10)

{
  char *in_EAX;
  undefined4 *puVar1;
  void *pvVar2;
  float local_8;
  float local_4;
  
  puVar1 = malloc_(0x23c);
  *puVar1 = 0;
  puVar1[1] = 0;
  XAPILIB::lstrcpynW((LPWSTR)(puVar1 + 2),param_1,0xff);
  puVar1[0x82] = param_2;
  puVar1[0x83] = param_3;
  puVar1[0x84] = param_4;
  puVar1[0x85] = param_5;
  puVar1[0x86] = param_6;
  puVar1[0x87] = param_7;
  puVar1[0x89] = 0;
  puVar1[0x8a] = 0;
  puVar1[0x88] = 0;
  puVar1[0x8b] = 0;
  if (in_EAX != (char *)0x0) {
    local_8 = *param_9 + (float)puVar1[0x89];
    local_4 = (float)puVar1[0x8a] + param_9[1];
    pvVar2 = malloc_(0x2c);
    FUN_00144780(in_EAX,param_8,pvVar2,&local_8,param_10);
    puVar1[0x8e] = pvVar2;
    puVar1[0x8c] = *param_9;
    puVar1[0x8d] = param_9[1];
    return puVar1;
  }
  puVar1[0x8e] = 0;
  return puVar1;
}




void XcSHAUpdate(PUCHAR pbSHAContext,PUCHAR pbInput,ULONG dwInputLength)

{
                    // WARNING: Could not recover jumptable at 0x00152752. Too many branches
                    // WARNING: Treating indirect jump as call
  XcSHAUpdate(pbSHAContext,pbInput,dwInputLength);
  return;
}




void XcSHAUpdate(PUCHAR pbSHAContext,PUCHAR pbInput,ULONG dwInputLength)

{
                    // WARNING: Could not recover jumptable at 0x00152752. Too many branches
                    // WARNING: Treating indirect jump as call
  XcSHAUpdate(pbSHAContext,pbInput,dwInputLength);
  return;
}




Input::Gamepad::SetBitIfGreaterThan(int slot,uint bitToSet,byte value,byte threshold)

{
  ControllerAnalogsBitfield CVar1;
  
  if (threshold <= value) {
                    // If it previously wasn't down,
                    // Set it as changed
                    // Otherwise
                    // Set it as unchanged
    if ((bitToSet & ProcessedGamepads[slot].changedButtonsDown) == 0) {
      ProcessedGamepads[slot].changed =
           (ControllerAnalogsBitfield)((uint)ProcessedGamepads[slot].changed | bitToSet);
    }
    else {
      ProcessedGamepads[slot].changed =
           (ControllerAnalogsBitfield)((uint)ProcessedGamepads[slot].changed & ~bitToSet);
    }
    ProcessedGamepads[slot].buttonsDown = ProcessedGamepads[slot].buttonsDown | bitToSet;
    ProcessedGamepads[slot].buttonsUp = ProcessedGamepads[slot].buttonsUp & ~bitToSet;
    return;
  }
  if ((bitToSet & ProcessedGamepads[slot].changedButtonsDown) == 0) {
    ProcessedGamepads[slot].buttonsUp = ProcessedGamepads[slot].buttonsUp & ~bitToSet;
  }
  else {
    ProcessedGamepads[slot].buttonsUp = ProcessedGamepads[slot].buttonsUp | bitToSet;
  }
  CVar1 = ProcessedGamepads[slot].changed;
  ProcessedGamepads[slot].buttonsDown = ProcessedGamepads[slot].buttonsDown & ~bitToSet;
  ProcessedGamepads[slot].changed = (ControllerAnalogsBitfield)((uint)CVar1 & ~bitToSet);
  return;
}




void Input::Gamepad::DebouncePads(float delta)

{
  int i;
  ProcessedGamepad_0x94 pfVar5;
  uint32_t bit;
  int num_bits;
  float new_value;
  float debounce_max;
  float debounce_min;
  float prevValue;
  uint *puVar1;
  
  debounce_max = Debounce2;
  debounce_min = Debounce1;
  i = 0;
  do {
    bit = 0b00000001;
    pfVar5 = (ProcessedGamepad_0x94)((int)ProcessedGamepads[0].repeatAccumulators + i);
    num_bits = 32;
    do {
                    // If the input isn't pressed at all, reset
      if ((*(uint *)((int)ProcessedGamepads[0].pressLengths + i + -0x14) & bit) == 0) {
        ADJ(pfVar5)->pressLengths[0] = 0.0;
LAB_00154c29:
                    // Turn off the bit in inactiveTimeMask (@ 0x10)
        *(uint *)((int)ProcessedGamepads[0].pressLengths + i + -4) =
             *(uint *)((int)ProcessedGamepads[0].pressLengths + i + -4) & ~bit;
      }
      else {
        prevValue = ADJ(pfVar5)->pressLengths[0];
        new_value = delta + prevValue;
        ADJ(pfVar5)->pressLengths[0] = new_value;
                    // debounce1 is typically 0
        if (debounce_min <= new_value) {
          if (debounce_min <= prevValue) {
            prevValue = ADJ(pfVar5)->repeatAccumulators[0] + delta;
            ADJ(pfVar5)->repeatAccumulators[0] = prevValue;
                    // Reset if less than debounce max and above debounce min
            if (prevValue < debounce_max) goto LAB_00154c29;
            puVar1 = (uint *)((int)ProcessedGamepads[0].pressLengths + i + -4);
            *puVar1 = *puVar1 | bit;
            ADJ(pfVar5)->repeatAccumulators[0] = ADJ(pfVar5)->repeatAccumulators[0] - debounce_min;
          }
          else {
            puVar1 = (uint *)((int)ProcessedGamepads[0].pressLengths + i + -4);
            *puVar1 = *puVar1 | bit;
            ADJ(pfVar5)->repeatAccumulators[0] = 0.0;
          }
        }
      }
      pfVar5 = (ProcessedGamepad_0x94)(ADJ(pfVar5)->repeatAccumulators + 1);
      bit = bit << 1;
      num_bits = num_bits + -1;
    } while (num_bits != 0);
    *(undefined4 *)((int)ProcessedGamepads[0].pressLengths + i + -0x10) =
         *(undefined4 *)((int)ProcessedGamepads[0].pressLengths + i + -0x14);
                    // Go to next gamepad
    i = i + 316;
    if (1263 < i) {
      return;
    }
  } while( true );
}




void Input::SetLSDeadzoneHandler(deadzone_handler_t *param_1)

{
  PTR_LSDeadzoneHandler = param_1;
  return;
}




void Input::SetRSDeadzoneHandler(deadzone_handler_t *param_1)

{
  PTR_RSDeadzoneHandler = param_1;
  return;
}




void Input::Gamepad::HandleLS(int slot,int lx,int ly)

{
  float fVar1;
  
  if (PTR_LSDeadzoneHandler != (deadzone_handler_t *)0x0) {
                    // Jumps to 0x00155360
    (*PTR_LSDeadzoneHandler)(slot,&lx,&ly);
  }
  fVar1 = (float)lx * 0.013513514;
  ProcessedGamepads[slot].lsx = lx;
  ProcessedGamepads[slot].lsy = ly;
  if (-1.0 <= fVar1) {
    if (1.0 < fVar1) {
      fVar1 = 1.0;
    }
  }
  else {
    fVar1 = -1.0;
  }
  ProcessedGamepads[slot].field11_0x124 = (int)fVar1;
  fVar1 = (float)ly * 0.013513514;
  if (fVar1 < -1.0) {
    ProcessedGamepads[slot].field12_0x128 = (int)-1.0;
    return;
  }
  if (1.0 < fVar1) {
    fVar1 = 1.0;
  }
  ProcessedGamepads[slot].field12_0x128 = (int)fVar1;
  return;
}




void Gamepad::GetPadRawLS(uint slot,int *lsx,int *lsy)

{
  *lsx = Input::Gamepad::ProcessedGamepads[slot].lsx;
  *lsy = Input::Gamepad::ProcessedGamepads[slot].lsy;
  return;
}




void Input::Gamepad::HandleRS(int slot,int rx,int ry)

{
  float fVar1;
  
  if (PTR_RSDeadzoneHandler != (deadzone_handler_t *)0x0) {
    (*PTR_RSDeadzoneHandler)(slot,&rx,&ry);
  }
  fVar1 = (float)rx * 0.016949153;
  ProcessedGamepads[slot].rsx = rx;
  ProcessedGamepads[slot].rsy = ry;
  if (-1.0 <= fVar1) {
    if (1.0 < fVar1) {
      fVar1 = 1.0;
    }
  }
  else {
    fVar1 = -1.0;
  }
  ProcessedGamepads[slot].field13_0x12c = (int)fVar1;
  fVar1 = (float)ry * 0.016949153;
  if (fVar1 < -1.0) {
    ProcessedGamepads[slot].field14_0x130 = (int)-1.0;
    return;
  }
  if (1.0 < fVar1) {
    fVar1 = 1.0;
  }
  ProcessedGamepads[slot].field14_0x130 = (int)fVar1;
  return;
}




void Gamepad::GetRawRS(int param_1,int *param_2,int *param_3)

{
  *param_2 = Input::Gamepad::ProcessedGamepads[param_1].rsx;
  *param_3 = Input::Gamepad::ProcessedGamepads[param_1].rsy;
  return;
}




void Input::Gamepad::UpdateTriggersForSlot(int slot,byte param_2,byte param_3)

{
  byte value;
  
  if (PTR_GamepadCallback3 != (void *)0x0) {
    (*PTR_GamepadCallback3)(slot,0xc000,&param_2,&param_3);
  }
  value = param_3;
  ProcessedGamepads[slot].lt = param_2;
  ProcessedGamepads[slot].rt = param_3;
  SetBitIfGreaterThan(slot,0x4000,param_2,0x1e);
  SetBitIfGreaterThan(slot,0x8000,value,0x1e);
  return;
}




void Gamepad::GetTriggersRaw(int param_1,uchar *param_2,uchar *param_3)

{
  *param_2 = Input::Gamepad::ProcessedGamepads[param_1].lt;
  *param_3 = Input::Gamepad::ProcessedGamepads[param_1].rt;
  return;
}



// WARNING: Unable to use type for symbol bVar1


void Input::Gamepad::UpdateRSBoolsForSLot(int slot,undefined1 param_2,undefined1 param_3)

{
  bool bVar1;
  
                    // Goes to 0x155400
                    // 
                    // Applies deadzones and restricts analog input to [0, 40...190]
  if (PTR_GamepadCallback3 != (void *)0x0) {
    (*PTR_GamepadCallback3)(slot,0b0000001100000000,&param_2,&param_3);
  }
  bVar1 = (bool)param_3;
  ProcessedGamepads[slot].lsxMoved = (bool)param_2;
  ProcessedGamepads[slot].lsyMoved = (bool)param_3;
  SetBitIfGreaterThan(slot,0x100,param_2,0x1e);
  SetBitIfGreaterThan(slot,0x200,bVar1,0x1e);
  return;
}




void Input::Gamepad::UpdateAnalog2(int slot,undefined1 param_2,undefined1 param_3)

{
  bool value;
  
  if (PTR_GamepadCallback3 != (void *)0x0) {
    (*PTR_GamepadCallback3)(slot,0b0000110000000000,&param_2,&param_3);
  }
  value = (bool)param_3;
  ProcessedGamepads[slot].xIsDown = (bool)param_2;
  ProcessedGamepads[slot].yIsDown = (bool)param_3;
  SetBitIfGreaterThan(slot,0x400,param_2,0x1e);
  SetBitIfGreaterThan(slot,0x800,value,0x1e);
  return;
}




void Input::Gamepad::UpdateAnalog3(int param_1,undefined1 param_2,undefined1 param_3)

{
  bool value;
  
  if (PTR_GamepadCallback3 != (void *)0x0) {
    (*PTR_GamepadCallback3)(param_1,0x3000,&param_2,&param_3);
  }
  value = (bool)param_3;
  ProcessedGamepads[param_1].blackIsDown = (bool)param_2;
  ProcessedGamepads[param_1].whiteIsDown = (bool)param_3;
  SetBitIfGreaterThan(param_1,0x1000,param_2,0x1e);
  SetBitIfGreaterThan(param_1,0x2000,value,0x1e);
  return;
}




int Gamepad::GetButtonsRaw(int param_1)

{
  return Input::Gamepad::ProcessedGamepads[param_1].buttonsDown;
}




void Input::Gamepad::UpdateButtonsForSlot(int slot,uint buttonsUpdated,uint buttonsDown)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0b00000001;
  iVar2 = 0x20;
  do {
    uVar1 = uVar3 & 0b1111111111111111;
                    // If the button is down
    if ((buttonsDown & uVar1) != 0) {
                    // If the button was updated
      if ((buttonsUpdated & uVar1) == 0) {
                    // Disable the bit
        ProcessedGamepads[slot].changed =
             (ControllerAnalogsBitfield)((uint)ProcessedGamepads[slot].changed & ~uVar1);
      }
      else {
        ProcessedGamepads[slot].changed =
             (ControllerAnalogsBitfield)((uint)ProcessedGamepads[slot].changed | uVar1);
        ProcessedGamepads[slot].buttonsDown = ProcessedGamepads[slot].buttonsDown | uVar1;
        ProcessedGamepads[slot].buttonsUp = ProcessedGamepads[slot].buttonsUp & ~uVar1;
      }
    }
    uVar3 = uVar3 << 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  uVar3 = ProcessedGamepads[slot].buttonsDown;
                    // button a
  ProcessedGamepads[slot].lsxMoved = (bool)-((uVar3 & 0x100) != 0);
                    // Button b
  ProcessedGamepads[slot].lsyMoved = (bool)-((uVar3 & 0x200) != 0);
                    // Button x
  ProcessedGamepads[slot].xIsDown = (bool)-((uVar3 & 0x400) != 0);
                    // Button y
  ProcessedGamepads[slot].yIsDown = (bool)-((uVar3 & 0x800) != 0);
                    // Black
  ProcessedGamepads[slot].blackIsDown = (bool)-((uVar3 & 0x1000) != 0);
                    // White
  ProcessedGamepads[slot].whiteIsDown = (bool)-((uVar3 & 0x2000) != 0);
  return;
}




void Input::Gamepad::UpdateLSBoolsForSlot(int slot,uint buttonsUpdated,uint buttonsDown)

{
  uint uVar3;
  int iVar1;
  
  uVar3 = 0b00000001;
  iVar1 = 0x20;
  do {
    if ((buttonsDown & uVar3) != 0) {
      if ((buttonsUpdated & uVar3) == 0) {
        ProcessedGamepads[slot].buttonsUp = ProcessedGamepads[slot].buttonsUp & ~uVar3;
      }
      else {
        ProcessedGamepads[slot].buttonsUp = ProcessedGamepads[slot].buttonsUp | uVar3;
        ProcessedGamepads[slot].buttonsDown = ProcessedGamepads[slot].buttonsDown & ~uVar3;
        ProcessedGamepads[slot].changed =
             (ControllerAnalogsBitfield)((uint)ProcessedGamepads[slot].changed & ~uVar3);
      }
    }
    uVar3 = uVar3 << 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  uVar3 = ProcessedGamepads[slot].buttonsDown;
  ProcessedGamepads[slot].lsxMoved = (bool)-((uVar3 & 0x100) != 0);
  ProcessedGamepads[slot].lsyMoved = (bool)-((uVar3 & 0x200) != 0);
  ProcessedGamepads[slot].xIsDown = (bool)-((uVar3 & 0x400) != 0);
  ProcessedGamepads[slot].yIsDown = (bool)-((uVar3 & 0x800) != 0);
  ProcessedGamepads[slot].blackIsDown = (bool)-((uVar3 & 0x1000) != 0);
  ProcessedGamepads[slot].whiteIsDown = (bool)-((uVar3 & 0x2000) != 0);
  return;
}



void Input::ApplyDeadzones
               (int *xPtr,int *yPtr,int innerRadius,int outerRadius,int interpolationStrength)

{
  int iVar1;
  int lx;
  int iVar2;
  int ly;
  bool bVar3;
  int lx_sign;
  int ly_sign;
  
  lx = *xPtr;
  ly = *yPtr;
  if (lx < 0) {
    lx_sign = -1;
    lx = -lx;
  }
  else {
    lx_sign = 1;
  }
  if (ly < 0) {
    ly_sign = -1;
    ly = -ly;
  }
  else {
    ly_sign = 1;
  }
  if (innerRadius < lx) {
    lx = lx - innerRadius;
  }
  else {
    lx = 0;
  }
  if (innerRadius < ly) {
    ly = ly - innerRadius;
  }
  else {
    ly = 0;
  }
  if ((lx == 0) && (ly == 0)) {
    *yPtr = 0;
    *xPtr = 0;
    return;
  }
  iVar1 = ly * interpolationStrength;
  iVar2 = lx * interpolationStrength;
  if (iVar1 - iVar2 == 0 || iVar1 < iVar2) {
    iVar2 = (outerRadius - interpolationStrength) * ly + iVar2;
    bVar3 = SBORROW4(outerRadius * interpolationStrength,iVar2);
    iVar1 = outerRadius * interpolationStrength - iVar2;
  }
  else {
    iVar2 = (outerRadius - interpolationStrength) * lx + iVar1;
    bVar3 = SBORROW4(outerRadius * interpolationStrength,iVar2);
    iVar1 = outerRadius * interpolationStrength - iVar2;
  }
  if (bVar3 != iVar1 < 0) {
    lx = (lx * outerRadius * interpolationStrength) / iVar2;
                    // LARP square to circle
    ly = (ly * outerRadius * interpolationStrength) / iVar2;
  }
  *xPtr = lx_sign * lx;
  *yPtr = ly_sign * ly;
  return;
}




void Input::Gamepad::initialise(int slot)

{
  ProcessedGamepads[slot].buttonsDown = 0;
  ProcessedGamepads[slot].changedButtonsDown = 0;
  ProcessedGamepads[slot].changed = (ControllerAnalogsBitfield)0x0;
  ProcessedGamepads[slot].buttonsUp = 0;
  ProcessedGamepads[slot].inactiveTimeMask = 0;
  ProcessedGamepads[slot].lsx = 0;
  ProcessedGamepads[slot].lsy = 0;
  ProcessedGamepads[slot].rsx = 0;
  ProcessedGamepads[slot].rsy = 0;
  ProcessedGamepads[slot].lsxMoved = false;
  ProcessedGamepads[slot].lsyMoved = false;
  ProcessedGamepads[slot].yIsDown = false;
  ProcessedGamepads[slot].xIsDown = false;
  ProcessedGamepads[slot].blackIsDown = false;
  ProcessedGamepads[slot].whiteIsDown = false;
  ProcessedGamepads[slot].lt = '\0';
  ProcessedGamepads[slot].rt = '\0';
  ProcessedGamepads[slot].field11_0x124 = 0;
  ProcessedGamepads[slot].field12_0x128 = 0;
  ProcessedGamepads[slot].field13_0x12c = 0;
  ProcessedGamepads[slot].field14_0x130 = 0;
  ProcessedGamepads[slot].pressLengths[0] = 1.0;
  ProcessedGamepads[slot].pressLengths[1] = 1.0;
  ProcessedGamepads[slot].pressLengths[2] = 1.0;
  ProcessedGamepads[slot].pressLengths[3] = 1.0;
  ProcessedGamepads[slot].pressLengths[4] = 1.0;
  ProcessedGamepads[slot].pressLengths[5] = 1.0;
  ProcessedGamepads[slot].pressLengths[6] = 1.0;
  ProcessedGamepads[slot].pressLengths[7] = 1.0;
  ProcessedGamepads[slot].pressLengths[8] = 1.0;
  ProcessedGamepads[slot].pressLengths[9] = 1.0;
  ProcessedGamepads[slot].pressLengths[10] = 1.0;
  ProcessedGamepads[slot].pressLengths[0xb] = 1.0;
  ProcessedGamepads[slot].pressLengths[0xc] = 1.0;
  ProcessedGamepads[slot].pressLengths[0xd] = 1.0;
  ProcessedGamepads[slot].pressLengths[0xe] = 1.0;
  ProcessedGamepads[slot].pressLengths[0xf] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x10] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x11] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x12] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x13] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x14] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x15] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x16] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x17] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x18] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x19] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x1a] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x1b] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x1c] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x1d] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x1e] = 1.0;
  ProcessedGamepads[slot].pressLengths[0x1f] = 1.0;
  return;
}




void Input::DefaultLSDeadzoneHandler(int param_1,int *stickX,int *stickY)

{
                    // Normalise lx/ly
  *stickX = (int)((float)*stickX * 0.0033569336);
  *stickY = (int)((float)*stickY * 0.0033569336);
  ApplyDeadzones(stickX,stickY,15,72,40);
  return;
}




void Input::DefaultLSDeadzoneHandler(undefined4 param_1,int *param_2,int *param_3)

{
  *param_2 = (int)((float)*param_2 * 0.0030212402);
  *param_3 = (int)((float)*param_3 * 0.0030212402);
  ApplyDeadzones(param_2,param_3,0xf,0x3b,0x1f);
  return;
}




void Input::Gamepad::ApplyAnalogDeadzone(undefined4 slot,undefined4 mask,byte *inX,byte *inY)

{
  uint64_t uVar1;
  
                    // Reduce inputs to 217/255 (85%)
  uVar1 = float10::to_uint64_t((float10)*inX * (float10)0.8509804);
  *inX = (byte)uVar1;
  uVar1 = float10::to_uint64_t((float10)*inY * (float10)0.8509804);
  *inY = (byte)uVar1;
  if (*inX < 0x28) {
    *inX = 0;
  }
  else {
    if (190 < *inX) {
      *inX = 190;
    }
    *inX = *inX - 40;
  }
  if (*inY < 40) {
    *inY = 0;
    return;
  }
  if (190 < *inY) {
    *inY = 190;
  }
  *inY = *inY - 40;
  return;
}




void Input::ClearGamepadStructsAndSetCallbacks(void)

{
  int i;
  int *pGVar2;
  
  Debounce1 = 1.0;
                    // Clear structdetails
  i = 316;
  pGVar2 = &Gamepad::ProcessedGamepads[0].buttonsDown;
  for (; i != 0; i = i + -1) {
    *pGVar2 = 0;
    pGVar2 = pGVar2 + 1;
  }
  PTR_LSDeadzoneHandler = DefaultLSDeadzoneHandler;
  PTR_RSDeadzoneHandler = DefaultLSDeadzoneHandler;
  PTR_GamepadCallback3 = Gamepad::ApplyAnalogDeadzone;
  Debounce2 = 0.0;
  return;
}




ControllerBitfield GetGamepadHandle(int gamepadIndex)

{
  return (&Input::Gamepad::ConnectedControllers)[gamepadIndex * 2];
}




void Input::OpenGamepadHandles(XPP_DEVICE_TYPE *handles,uint openMask,uint closeMask)

{
  HANDLE pvVar1;
  DWORD i;
  uint uVar2;
  
  if (handles == GamePads) {
    i = 0;
    do {
      uVar2 = 1 << ((byte)i & 0b00011111);
      if (((closeMask & uVar2) != 0) && (Gamepad::Handles[i] != (HANDLE)0x0)) {
        XAPILIB::XInputClose(Gamepad::Handles[i]);
        Gamepad::Handles[i] = (HANDLE)0x0;
      }
      if ((openMask & uVar2) != 0) {
        pvVar1 = XAPILIB::XInputOpen(GamePads,i,0,(PXINPUT_POLLING_PARAMETERS)0x0);
        Gamepad::Handles[i] = pvVar1;
      }
      i = i + 1;
    } while ((int)i < 4);
  }
  return;
}




void Input::InitialiseInner(void)

{
  XPP_DEVICE_TYPE *local_8;
  int local_4;
  
  local_8 = GamePads;
  local_4 = 4;
  XAPILIB::XInitDevices(1,(PXDEVICE_PREALLOC_TYPE)&stack0xfffffff8);
  Gamepad::Handles[0] = (HANDLE)0x0;
  Gamepad::Handles[1] = (HANDLE)0x0;
  Gamepad::Handles[2] = (HANDLE)0x0;
  Gamepad::Handles[3] = (HANDLE)0x0;
  Gamepad::ConnectedControllers = (ControllerBitfield)XAPILIB::XGetDevices(GamePads);
  OpenGamepadHandles(GamePads,Gamepad::ConnectedControllers,0);
  ClearGamepadStructsAndSetCallbacks();
  InitialiseFlagFloats();
  Gamepad::initialised_ = true;
  return;
}



// WARNING: Inlined function: FALSE


void Input::ReadAndUpdateXInput(float deltaTime)

{
  bool cVar2;
  BOOL err;
  ControllerBitfield inserted;
  XINPUT_STATE *pad_state;
  XINPUT_GAMEPAD *pad;
  XINPUT_FEEDBACK *feedback;
  int slot;
  HANDLE *ppvVar6;
  DWORD removals;
  DWORD insertions;
  WORD wButtons [4];
  HANDLE ptr;
  uint ignore_mask;
  
                    // Update which controllers are plugged in
  err = XAPILIB::XGetDeviceChanges(GamePads,&insertions,&removals);
  if (err != 0) {
    OpenGamepadHandles(GamePads,insertions,removals);
    Gamepad::ConnectedControllers =
         (ControllerBitfield)(~removals & (uint)Gamepad::ConnectedControllers | insertions);
  }
  pad_state = Gamepad::GamepadStates;
  slot = 0;
  inserted = Gamepad::ConnectedControllers;
  do {
    ptr = *(HANDLE *)((int)Gamepad::Handles + slot);
    if (ptr != (HANDLE)0x0) {
      *(uint *)((int)wButtons + slot) =
           (uint)(((PXINPUT_STATE)pad_state)->field1_0x4).Gamepad.wButtons;
      XAPILIB::XInputGetState(ptr,(PXINPUT_STATE)pad_state);
      inserted = Gamepad::ConnectedControllers;
    }
    pad_state = (XINPUT_STATE *)&((PXINPUT_STATE)pad_state)->field_0x16;
    slot = slot + 4;
  } while ((int)pad_state < 0x434908);
  slot = 0;
  pad = &Gamepad::GamepadStates[0].Gamepad;
  do {
    if (((uint)inserted & 1 << ((byte)slot & 0x1f)) == 0) {
      Gamepad::initialise(slot);
    }
    else {
      Gamepad::HandleLS(slot,(int)pad->sThumbLX,(int)pad->sThumbLY);
      Gamepad::HandleRS(slot,(int)pad->sThumbRX,(int)pad->sThumbRY);
      ignore_mask = *(uint *)(wButtons + slot * 2);
      Gamepad::UpdateButtonsForSlot
                (slot,(pad->wButtons ^ ignore_mask) & (uint)pad->wButtons,0b11111111);
      Gamepad::UpdateLSBoolsForSlot(slot,(pad->wButtons ^ ignore_mask) & ignore_mask,0xff);
      Gamepad::UpdateRSBoolsForSLot(slot,pad->bAnalogButtons[0],pad->bAnalogButtons[1]);
      Gamepad::UpdateAnalog2(slot,pad->bAnalogButtons[2],pad->bAnalogButtons[3]);
      Gamepad::UpdateAnalog3(slot,pad->bAnalogButtons[4],pad->bAnalogButtons[5]);
      Gamepad::UpdateTriggersForSlot(slot,pad->bAnalogButtons[6],pad->bAnalogButtons[7]);
    }
    pad = (XINPUT_GAMEPAD *)((int)(pad + 1) + 4);
    slot = slot + 1;
    inserted = Gamepad::ConnectedControllers;
  } while ((int)pad < 0x43490c);
  Gamepad::DebouncePads(deltaTime);
  UpdateRumbleValues(Gamepad::XInputFeedbacks,deltaTime);
  if (Config::RumbleSupported != false) {
    ppvVar6 = Gamepad::Handles;
    feedback = Gamepad::XInputFeedbacks;
    do {
      if (*ppvVar6 != (HANDLE)0x0) {
        XAPILIB::XInputSetState(*ppvVar6,(PXINPUT_FEEDBACK)feedback);
      }
      feedback = feedback + 1;
      ppvVar6 = ppvVar6 + 1;
    } while ((int)feedback < 0x4348a0);
  }
  return;
}




void Input::InitialiseFlagFloats(void)

{
  bool *pbVar1;
  
  pbVar1 = &Gamepad::rumbleFloats_[0].flag2;
  do {
    ((GamepadFlagFloats *)(pbVar1 + -1))->rumbleEnabled = true;
    *pbVar1 = true;
    pbVar1[2] = false;
    pbVar1 = pbVar1 + 0x14;
  } while ((int)pbVar1 < 0x434961);
  return;
}




void Input::UpdateRumbleValues(XINPUT_FEEDBACK *feedback,float delta)

{
  XINPUT_RUMBLE *puVar2;
  void *puVar3;
  uint64_t uVar1;
  
  if ((Gamepad::rumbleFloats_[0].duration_ != 0.0) &&
     (Gamepad::rumbleFloats_[0].duration_ = Gamepad::rumbleFloats_[0].duration_ - delta,
     Gamepad::rumbleFloats_[0].duration_ <= 0.0)) {
    Gamepad::rumbleFloats_[0].rumbling = false;
    Gamepad::rumbleFloats_[0].xRumble = 0.0;
    Gamepad::rumbleFloats_[0].yRumble = 0.0;
  }
  if ((Gamepad::rumbleFloats_[1].duration_ != 0.0) &&
     (Gamepad::rumbleFloats_[1].duration_ = Gamepad::rumbleFloats_[1].duration_ - delta,
     Gamepad::rumbleFloats_[1].duration_ <= 0.0)) {
    Gamepad::rumbleFloats_[1].rumbling = false;
    Gamepad::rumbleFloats_[1].xRumble = 0.0;
    Gamepad::rumbleFloats_[1].yRumble = 0.0;
  }
  if ((Gamepad::rumbleFloats_[2].duration_ != 0.0) &&
     (Gamepad::rumbleFloats_[2].duration_ = Gamepad::rumbleFloats_[2].duration_ - delta,
     Gamepad::rumbleFloats_[2].duration_ <= 0.0)) {
    Gamepad::rumbleFloats_[2].rumbling = false;
    Gamepad::rumbleFloats_[2].xRumble = 0.0;
    Gamepad::rumbleFloats_[2].yRumble = 0.0;
  }
  if ((Gamepad::rumbleFloats_[3].duration_ != 0.0) &&
     (Gamepad::rumbleFloats_[3].duration_ = Gamepad::rumbleFloats_[3].duration_ - delta,
     Gamepad::rumbleFloats_[3].duration_ <= 0.0)) {
    Gamepad::rumbleFloats_[3].rumbling = false;
    Gamepad::rumbleFloats_[3].xRumble = 0.0;
    Gamepad::rumbleFloats_[3].yRumble = 0.0;
  }
  puVar3 = &Gamepad::rumbleFloats_[0].yRumble;
  puVar2 = &feedback->Rumble;
  do {
    *(undefined4 *)&puVar2[-0x11].wRightMotorSpeed = 0;
    *(undefined4 *)&puVar2[-0x10].wRightMotorSpeed = 0;
    uVar1 = float10::to_uint64_t((float10)*(float *)((int)puVar3 + -4) * (float10)65535.0);
    puVar2->wLeftMotorSpeed = (WORD)uVar1;
    uVar1 = float10::to_uint64_t((float10)*(float *)puVar3 * (float10)65535.0);
    puVar2->wRightMotorSpeed = (WORD)uVar1;
    puVar3 = (void *)((int)puVar3 + 0x14);
    puVar2 = (XINPUT_RUMBLE *)&puVar2[0x11].wRightMotorSpeed;
  } while ((int)puVar3 < 0x43496c);
  return;
}




void Input::SetRumble(uint pad,vec3 vals)

{
  if (Gamepad::rumbleFloats_[pad].rumbleEnabled == false) {
    return;
  }
  if ((vals.x == 0.0) && (vals.y == 0.0)) {
    Gamepad::rumbleFloats_[pad].rumbling = false;
    Gamepad::rumbleFloats_[pad].physicalPad_ = SUB41(pad,0);
    Gamepad::rumbleFloats_[pad].xRumble = vals.x;
    Gamepad::rumbleFloats_[pad].yRumble = vals.y;
    Gamepad::rumbleFloats_[pad].duration_ = vals.z;
  }
  else {
    Gamepad::rumbleFloats_[pad].xRumble = vals.x;
    Gamepad::rumbleFloats_[pad].rumbling = true;
    Gamepad::rumbleFloats_[pad].physicalPad_ = SUB41(pad,0);
    Gamepad::rumbleFloats_[pad].yRumble = vals.y;
    Gamepad::rumbleFloats_[pad].duration_ = vals.z;
    if (vals.z != 0.0) {
      Gamepad::rumbleFloats_[pad].durationStillGoing = false;
      return;
    }
  }
  Gamepad::rumbleFloats_[pad].durationStillGoing = true;
  return;
}



// WARNING: Inlined function: GetBigBlock
// WARNING: Inlined function: GetDisplayMatrices


