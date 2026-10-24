/* xgraphics_d3d.c - Xbox XGRAPHICS / D3D8 / D3DX8 driver wrappers */
#include "xgraphics_d3d.h"

void D3D8::D3D_AllocContiguousMemory(SIZE_T size,ULONG_PTR ptr)

{
  XAPILIB::XPhysicalAlloc(size,0xffffffff,ptr,0x404);
  return;
}




void D3D8::D3D_SetPushBufferSize(DWORD PushBufferSize,DWORD KickOffSize)

{
  g_D3D_PUSH_BUFFER_SIZE = PushBufferSize;
  g_D3D_KICK_OFF_SIZE = KickOffSize;
  return;
}




void D3D8::D3DDevice_SetRenderState_PSTextureModes(DWORD Value)

{
  D3D_g_pDevice->field1875_0x78c = Value;
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x4000;
  D3DRS_PSTextureModes = Value;
  return;
}




void __fastcall D3D8::D3DDevice_SetRenderState_Simple(SimpleRenderState_Encoded Method,DWORD Value)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  while( true ) {
    puVar1 = D3D::D3D__Device.State;
    if (D3D::D3D__Device.State + 2 < D3D::D3D__Device.field1_0x4) break;
    D3DDevice_MakeSpace();
  }
  puVar2 = D3D::D3D__Device.State + 2;
  *D3D::D3D__Device.State = Method;
  D3D::D3D__Device.State = puVar2;
  puVar1[1] = Value;
  return;
}




void D3D8::D3DDevice_SetRenderStateNotInline(int param_1,DWORD param_2)

{
  if (param_1 < 0x5c) {
    D3DDevice_SetRenderState_Simple
              (*(SimpleRenderState_Encoded *)(&DAT_0020a368 + param_1 * 4),param_2);
    (&D3D_g_RenderState)[param_1] = param_2;
    return;
  }
  if (param_1 < 0x88) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | (uint)(&PTR_FUN_0020a148)[param_1];
    (&D3D_g_RenderState)[param_1] = param_2;
    return;
  }
  (**(code **)(param_1 * 4 + 0x17f798))(param_2);
  return;
}




void D3D8::D3DDevice_GetViewportOffsetAndScale(D3DXVECTOR4 *pOffset,D3DXVECTOR4 *pScale)

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
  
  fVar6 = (float)(int)D3D_g_pDevice->field2640_0xed0;
  if ((int)D3D_g_pDevice->field2640_0xed0 < 0) {
    fVar6 = fVar6 + 4.2949673e+09;
  }
  fVar6 = fVar6 * (float)D3D_g_pDevice->field2290_0x958 + (float)D3D_g_pDevice->field2646_0xee8;
  fVar7 = (float)(int)D3D_g_pDevice->field2641_0xed4;
  if ((int)D3D_g_pDevice->field2641_0xed4 < 0) {
    fVar7 = fVar7 + 4.2949673e+09;
  }
  fVar7 = fVar7 * (float)D3D_g_pDevice->field2291_0x95c + (float)D3D_g_pDevice->field2647_0xeec;
  if (((char)(D3D_g_pDevice->bitField1 >> 8) < '\0') && (D3DRS_MultiSampleAntiAlias != 0)) {
    fVar6 = fVar6 - 0.5;
    fVar7 = fVar7 - 0.5;
  }
  fVar8 = (float)(int)D3D_g_pDevice->field2642_0xed8;
  if ((int)D3D_g_pDevice->field2642_0xed8 < 0) {
    fVar8 = fVar8 + 4.2949673e+09;
  }
  fVar8 = fVar8 * (float)D3D_g_pDevice->field2290_0x958 * 0.5;
  fVar1 = (float)(int)D3D_g_pDevice->field2643_0xedc;
  if ((int)D3D_g_pDevice->field2643_0xedc < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  fVar9 = fVar1 * (float)D3D_g_pDevice->field2291_0x95c * -0.5;
  fVar1 = (float)D3D_g_pDevice->field2645_0xee4;
  fVar2 = (float)D3D_g_pDevice->field2644_0xee0;
  fVar3 = *(float *)&D3D_g_pDevice->field_0x944;
  fVar4 = (float)D3D_g_pDevice->field2644_0xee0;
  fVar5 = *(float *)&D3D_g_pDevice->field_0x944;
  pOffset->w = 0.0;
  pOffset->z = fVar4 * fVar5;
  pOffset->x = fVar8 + fVar6;
  pOffset->y = -fVar9 + fVar7;
  pScale->y = fVar9;
  pScale->z = (fVar1 - fVar2) * fVar3;
  pScale->w = 0.0;
  pScale->x = fVar8;
  return;
}




void D3D8::D3D_UpdateProjectionViewportTransform(void)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50 [5];
  float local_3c;
  float local_28;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  fVar1 = (float)(int)D3D_g_pDevice->field2642_0xed8;
  if ((int)D3D_g_pDevice->field2642_0xed8 < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  local_5c = fVar1 * (float)D3D_g_pDevice->field2290_0x958 * 0.5;
  fVar1 = (float)(int)D3D_g_pDevice->field2643_0xedc;
  if ((int)D3D_g_pDevice->field2643_0xedc < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  local_3c = fVar1 * (float)D3D_g_pDevice->field2291_0x95c * -0.5;
  local_58 = -local_3c;
  local_60 = ((float)D3D_g_pDevice->field2645_0xee4 - (float)D3D_g_pDevice->field2644_0xee0) *
             *(float *)&D3D_g_pDevice->field_0x944;
  local_54 = *(float *)&D3D_g_pDevice->field_0x944 * (float)D3D_g_pDevice->field2644_0xee0;
  if (DAT_00181dac == 2) {
    local_14 = *(float *)&D3D_g_pDevice->field_0x940 * *(float *)&D3D_g_pDevice->field_0x944;
    local_3c = local_3c * local_14;
    local_60 = local_14 * local_60;
    local_5c = local_14 * local_5c;
    local_58 = local_14 * local_58;
    local_54 = local_14 * local_54;
  }
  else {
    local_14 = 1.0;
  }
  pfVar3 = local_50;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = 0.0;
    pfVar3 = pfVar3 + 1;
  }
  local_28 = local_60;
  local_20 = local_5c;
  local_1c = local_58;
  local_18 = local_54;
  local_50[0] = local_5c;
  FUN_00177af0(&D3D_g_pDevice->field2296_0x970,&D3D_g_pDevice->field2496_0xc90,local_50);
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x200;
  return;
}




void D3D8::D3DDevice_SetRenderState_EdgeAntiAlias(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x80320;
  puVar2[1] = Value;
  puVar2[2] = Value;
  pDVar1->State = puVar2 + 3;
  DAT_00181dcc = Value;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void D3D8::D3DDevice_SetRenderState_ShadowFunc(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x41e6c;
  puVar2[1] = Value - 0x200;
  pDVar1->State = puVar2 + 2;
  _DAT_00181de0 = Value;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void D3D8::D3DDevice_SetRenderState_FogColor(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x402a8;
  puVar2[1] = Value >> 0x10 & 0xff | (Value & 0xff) << 0x10 | Value & 0xff00ff00;
  pDVar1->State = puVar2 + 2;
  _DAT_00181d98 = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_CullMode(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  bool bVar3;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x40308;
  if (Value == 0) {
    puVar2[1] = 0;
    pDVar1->State = puVar2 + 2;
    D3DRS_CullMode = Value;
    return;
  }
  puVar2[1] = 1;
  bVar3 = Value != D3DRS_FrontFace;
  puVar2[2] = 0x4039c;
  puVar2[3] = bVar3 + 0x404;
  pDVar1->State = puVar2 + 4;
  D3DRS_CullMode = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_FrontFace(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x403a0;
  puVar2[1] = Value;
  pDVar1->State = puVar2 + 2;
  D3DRS_FrontFace = Value;
  D3DDevice_SetRenderState_CullMode(D3DRS_CullMode);
  return;
}




void D3D8::D3DDevice_SetRenderState_NormalizeNormals(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x403a4;
  puVar2[1] = Value;
  pDVar1->State = puVar2 + 2;
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x200;
  DAT_00181da8 = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_TextureFactor(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  DWORD *pDVar3;
  int iVar4;
  
  pDVar1 = D3D_g_pDevice;
  if (D3D_g_pDevice->field1872_0x780 == 0) {
    puVar2 = D3D_g_pDevice->State;
    if (D3D_g_pDevice->field1_0x4 <= puVar2) {
      D3DDevice_MakeSpace();
      puVar2 = extraout_EAX;
    }
    *puVar2 = &DAT_00400a60;
    pDVar3 = puVar2 + 1;
    iVar4 = 0x10;
    do {
      *pDVar3 = Value;
      pDVar3 = pDVar3 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    pDVar1->State = pDVar3;
    DAT_00181dc0 = Value;
    return;
  }
  DAT_00181dc0 = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_LineWidth(DWORD Value)

{
  D3D__Device *pDVar1;
  uint uVar2;
  undefined4 *extraout_EAX;
  undefined4 *puVar3;
  
  pDVar1 = D3D_g_pDevice;
  uVar2 = FUN_001782c0((float)Value * (float)D3D_g_pDevice->field2292_0x960 * 8.0 + 0.5);
  if (0x1ff < uVar2) {
    uVar2 = 0x1ff;
  }
  puVar3 = pDVar1->State;
  if (pDVar1->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX;
  }
  *puVar3 = 0x40380;
  puVar3[1] = uVar2;
  pDVar1->State = puVar3 + 2;
  DAT_00181de4 = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_Dxt1NoiseEnable(DWORD Value)

{
  undefined4 **ppuVar1;
  D3D__Device *pDVar2;
  undefined4 *extraout_EAX;
  undefined4 *puVar3;
  uint uVar4;
  
  pDVar2 = D3D_g_pDevice;
  uVar4 = 0;
  if (((&DAT_0017f958)[*(byte *)(D3D_g_pDevice->field3353_0x19f4 + 0xd)] & 0x3c) == 0x20) {
    uVar4 = Value;
  }
  if (uVar4 != (D3D_g_pDevice->bitField1 & 1)) {
    ppuVar1 = &D3D_g_pDevice->field1_0x4;
    D3D_g_pDevice->bitField1 = D3D_g_pDevice->bitField1 ^ 1;
    puVar3 = pDVar2->State;
    if (*ppuVar1 <= puVar3) {
      D3DDevice_MakeSpace();
      puVar3 = extraout_EAX;
    }
    *puVar3 = &LAB_0004010e_2;
    puVar3[1] = 0;
    puVar3[2] = 0x40100;
    puVar3[3] = uVar4 << 5 | 8;
    pDVar2->State = puVar3 + 4;
  }
  D3DRS_Dxt1NoiseEnable = Value;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void D3D8::D3DDevice_SetRenderState_ZBias(DWORD Value)

{
  float fVar1;
  bool bVar2;
  
  bVar2 = Value != 0;
  fVar1 = (float)(int)Value;
  if ((int)Value < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  D3DDevice_SetRenderStateNotInline(0x4d,-fVar1 * 0.25);
  D3DDevice_SetRenderStateNotInline(0x4e,-fVar1);
  D3DDevice_SetRenderStateNotInline(0x4f,bVar2);
  D3DDevice_SetRenderStateNotInline(0x50,bVar2);
  D3DDevice_SetRenderStateNotInline(0x51,bVar2);
  _D3DRS_ZBias = Value;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void D3D8::D3DDevice_SetRenderState_LogicOp(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  if (Value == 0) {
    *puVar2 = 0x417bc;
    puVar2[1] = 0;
    pDVar1->State = puVar2 + 2;
    _D3DRS_LogicOp = Value;
    return;
  }
  *puVar2 = 0x817bc;
  puVar2[1] = 1;
  puVar2[2] = Value;
  pDVar1->State = puVar2 + 3;
  _D3DRS_LogicOp = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_FillMode(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  DWORD DVar3;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  DVar3 = D3DRS_BackFillMode;
  if (D3DRS_TwoSidedLighting == 0) {
    DVar3 = Value;
  }
  *puVar2 = &DAT_0008038c;
  puVar2[1] = Value;
  puVar2[2] = DVar3;
  pDVar1->State = puVar2 + 3;
  D3DRS_FillMode = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_BackFillMode(DWORD Value)

{
  DWORD DVar1;
  D3D__Device *pDVar2;
  undefined4 *extraout_EAX;
  undefined4 *puVar3;
  DWORD DVar4;
  
  pDVar2 = D3D_g_pDevice;
  DVar1 = D3DRS_FillMode;
  D3DRS_BackFillMode = Value;
  puVar3 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX;
  }
  DVar4 = D3DRS_BackFillMode;
  if (D3DRS_TwoSidedLighting == 0) {
    DVar4 = DVar1;
  }
  *puVar3 = &DAT_0008038c;
  puVar3[1] = DVar1;
  puVar3[2] = DVar4;
  pDVar2->State = puVar3 + 3;
  D3DRS_FillMode = DVar1;
  return;
}




void D3D8::D3DDevice_SetRenderState_TwoSidedLighting(DWORD Value)

{
  undefined4 uVar1;
  D3D__Device *pDVar2;
  undefined4 *extraout_EAX;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  pDVar2 = D3D_g_pDevice;
  puVar3 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX;
  }
  *puVar3 = 0x417c4;
  puVar3[1] = Value;
  pDVar2->State = puVar3 + 2;
  pDVar2 = D3D_g_pDevice;
  uVar1 = D3DRS_FillMode;
  if (Value != 0) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x9000;
  }
  D3DRS_TwoSidedLighting = Value;
  puVar3 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX_00;
  }
  uVar4 = D3DRS_BackFillMode;
  if (D3DRS_TwoSidedLighting == 0) {
    uVar4 = uVar1;
  }
  *puVar3 = &DAT_0008038c;
  puVar3[1] = uVar1;
  puVar3[2] = uVar4;
  pDVar2->State = puVar3 + 3;
  D3DRS_FillMode = uVar1;
  return;
}




void D3D8::D3DDevice_SetRenderState_VertexBlend(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x200;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x40328;
  puVar2[1] = Value;
  pDVar1->State = puVar2 + 2;
  DAT_00181d94 = Value;
  return;
}




void D3D8::D3DDevice_SetTextureState_TexCoordIndex(DWORD Stage,DWORD Value)

{
  D3D__Device *pDVar1;
  int *extraout_EAX;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  pDVar1 = D3D_g_pDevice;
  (&DAT_001819e0)[Stage * 0x20] = Value;
  piVar2 = pDVar1->State;
  iVar5 = 0;
  if (pDVar1->field1_0x4 <= piVar2) {
    D3DDevice_MakeSpace();
    piVar2 = extraout_EAX;
  }
  iVar3 = 0;
  uVar4 = Value & 0xffff0000;
  if (uVar4 != 0) {
    *piVar2 = Stage * 4 + 0x41964;
    piVar2[1] = -0x1000000;
    piVar2 = piVar2 + 2;
    Value = Stage;
    if (uVar4 < 0x30001) {
      if (uVar4 == 0x30000) {
        iVar5 = 0x8512;
        iVar3 = 1;
      }
      else if (uVar4 == 0x10000) {
        iVar5 = 0x8511;
        iVar3 = 1;
      }
      else {
        iVar5 = 0x2400;
      }
    }
    else {
      iVar5 = 0x2401;
    }
  }
  (&DAT_0032cf41)[Stage] = (char)Value + '\t';
  *piVar2 = (Stage + 0xc03c) * 0x10;
  piVar2[1] = iVar5;
  piVar2[2] = iVar5;
  piVar2[3] = iVar5;
  pDVar1->State = piVar2 + 4;
  if ((pDVar1->field2287_0x94c == 0) && (iVar3 != 0)) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x200;
  }
  pDVar1->field2287_0x94c =
       ~(1 << ((byte)Stage & 0x1f)) & pDVar1->field2287_0x94c | iVar3 << ((byte)Stage & 0x1f);
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x47f;
  return;
}




void D3D8::D3DDevice_SetTextureState_BumpEnv(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value)

{
  D3D__Device *pDVar1;
  int *extraout_EAX;
  int *piVar2;
  uint uVar3;
  
  pDVar1 = D3D_g_pDevice;
  uVar3 = Stage;
  if (D3D_g_pDevice->field1872_0x780 == 0) {
    uVar3 = Stage + 1;
  }
  if ((uVar3 & 3) != 0) {
    piVar2 = D3D_g_pDevice->State;
    if (D3D_g_pDevice->field1_0x4 <= piVar2) {
      D3DDevice_MakeSpace();
      piVar2 = extraout_EAX;
    }
    *piVar2 = (uVar3 * 0x10 + Type) * 4 + 0x41ad0;
    piVar2[1] = Value;
    pDVar1->State = piVar2 + 2;
  }
  *(DWORD *)((int)&D3D_g_DeferredTextureState + (Stage * 0x20 + Type) * 4) = Value;
  return;
}




void D3D8::D3DDevice_SetTextureState_BorderColor(DWORD Stage,DWORD Value)

{
  D3D__Device *pDVar1;
  int *extraout_EAX;
  int *piVar2;
  
  pDVar1 = D3D_g_pDevice;
  piVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= piVar2) {
    D3DDevice_MakeSpace();
    piVar2 = extraout_EAX;
  }
  *piVar2 = Stage * 0x40 + 0x41b24;
  piVar2[1] = Value;
  pDVar1->State = piVar2 + 2;
  *(DWORD *)(&DAT_001819e4 + Stage * 0x80) = Value;
  return;
}




void D3D8::D3DDevice_SetTextureState_ColorKeyColor(DWORD Stage,DWORD Value)

{
  D3D__Device *pDVar1;
  int *extraout_EAX;
  int *piVar2;
  
  pDVar1 = D3D_g_pDevice;
  piVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= piVar2) {
    D3DDevice_MakeSpace();
    piVar2 = extraout_EAX;
  }
  *piVar2 = Stage * 4 + 0x40ae0;
  piVar2[1] = Value;
  pDVar1->State = piVar2 + 2;
  *(DWORD *)(&DAT_001819e8 + Stage * 0x80) = Value;
  return;
}



void D3D8::D3DDevice_SetTextureStageStateNotInline
               (DWORD param_1,D3DTEXTURESTAGESTATETYPE param_2,uint param_3)

{
  if ((int)param_2 < 0xc) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 1 << ((byte)param_1 & 0x1f);
    *(uint *)((int)&D3D_g_DeferredTextureState + (param_1 * 0x20 + param_2) * 4) = param_3;
  }
  else {
    if (param_2 == 0xc) {
      Graphics::GraphicsFlags =
           Graphics::GraphicsFlags | (-(uint)(param_3 < 0x19) & 0xffffbff1) + 0x480f;
      (&DAT_001819a0)[param_1 * 0x20] = param_3;
      return;
    }
    if ((int)param_2 < 0x16) {
      Graphics::GraphicsFlags = Graphics::GraphicsFlags | *(uint *)(&DAT_0020a260 + param_2 * 4);
      *(uint *)((int)&D3D_g_DeferredTextureState + (param_1 * 0x20 + param_2) * 4) = param_3;
      return;
    }
    if (param_2 == 0x1c) {
      D3DDevice_SetTextureState_TexCoordIndex(param_1,param_3);
      return;
    }
    if (param_2 == 0x1d) {
      D3DDevice_SetTextureState_BorderColor(param_1,param_3);
      return;
    }
    if (param_2 == 0x1e) {
      D3DDevice_SetTextureState_ColorKeyColor(param_1,param_3);
      return;
    }
    if ((int)param_2 < 0x1c) {
      D3DDevice_SetTextureState_BumpEnv(param_1,param_2,param_3);
      return;
    }
  }
  return;
}




void D3D8::D3D_CommonSetDebugRegisters(void)

{
  undefined4 uVar1;
  D3D__Device *pDVar2;
  undefined4 *extraout_EAX;
  undefined4 *puVar3;
  uint uVar4;
  
  pDVar2 = D3D_g_pDevice;
  uVar4 = D3D_g_pDevice->field4002_0x2418 & 0xfffffff7;
  D3D_g_pDevice->field4002_0x2418 = uVar4;
  if (D3DRS_DoNotCullUncompressed != 0) {
    pDVar2->field4002_0x2418 = uVar4 | 8;
  }
  uVar4 = pDVar2->field4003_0x241c & 0xe7efffff;
  pDVar2->field4003_0x241c = uVar4;
  if (D3DRS_RopZCmpAlwaysRead != 0) {
    pDVar2->field4003_0x241c = uVar4 | 0x100000;
  }
  if (D3DRS_RopZRead != 0) {
    pDVar2->field4003_0x241c = pDVar2->field4003_0x241c | 0x8000000;
  }
  puVar3 = pDVar2->State;
  if (pDVar2->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX;
  }
  *puVar3 = &LAB_0004010e_2;
  puVar3[1] = 0;
  uVar1 = pDVar2->field4002_0x2418;
  puVar3[2] = 0x81d8c;
  puVar3[3] = &DAT_00400094;
  puVar3[4] = uVar1;
  puVar3[5] = 0x40100;
  puVar3[6] = 9;
  uVar1 = pDVar2->field4003_0x241c;
  puVar3[7] = 0x81d8c;
  puVar3[8] = &DAT_00400b80;
  puVar3[9] = uVar1;
  puVar3[10] = 0x40100;
  puVar3[0xb] = 9;
  pDVar2->State = puVar3 + 0xc;
  return;
}



void __fastcall

D3D8::D3D_CommonSetMultiSampleModeAndScale(undefined4 *param_1,D3DVIEWPORT8 *param_2)

{
  float fVar1;
  uint uVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *extraout_EAX;
  undefined4 *puVar7;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar8;
  uint uVar9;
  int iVar10;
  float local_10;
  
  iVar10 = D3DRS_MultiSampleMode;
  iVar4 = param_1[0x67d];
  if (iVar4 == param_1[0x681]) {
    fVar1 = (float)param_1[0x25b];
    local_10 = (float)param_1[0x25a];
    uVar6 = *(uint *)(param_1[0x682] + 0x10);
    if (uVar6 == 0) {
      iVar4 = 1 << ((byte)(*(uint *)(param_1[0x682] + 0xc) >> 0x14) & 0xf);
    }
    else {
      iVar4 = (uVar6 & 0xfff) + 1;
    }
    fVar3 = (float)iVar4;
    if (iVar4 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    uVar5 = FUN_001782c0(fVar3 * local_10 + 0.5);
    uVar6 = *(uint *)(param_1[0x682] + 0x10);
    if (uVar6 == 0) {
      iVar4 = 1 << (*(byte *)(param_1[0x682] + 0xf) & 0xf);
    }
    else {
      iVar4 = (uVar6 >> 0xc & 0xfff) + 1;
    }
    fVar3 = (float)iVar4;
    if (iVar4 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    uVar6 = FUN_001782c0(fVar3 * fVar1 + 0.5);
    iVar4 = param_1[0x681];
    if (*(uint *)(iVar4 + 0x10) == 0) {
      uVar9 = 1 << ((byte)(*(uint *)(iVar4 + 0xc) >> 0x14) & 0xf);
    }
    else {
      uVar9 = (*(uint *)(iVar4 + 0x10) & 0xfff) + 1;
    }
    if (uVar9 <= uVar5) {
      if (*(uint *)(iVar4 + 0x10) == 0) {
        uVar5 = 1 << ((byte)(*(uint *)(iVar4 + 0xc) >> 0x14) & 0xf);
      }
      else {
        uVar5 = (*(uint *)(iVar4 + 0x10) & 0xfff) + 1;
      }
    }
    if (*(uint *)(iVar4 + 0x10) == 0) {
      uVar9 = 1 << (*(byte *)(iVar4 + 0xf) & 0xf);
    }
    else {
      uVar9 = (*(uint *)(iVar4 + 0x10) >> 0xc & 0xfff) + 1;
    }
    if (uVar6 < uVar9) goto LAB_001720fe;
    uVar6 = *(uint *)(iVar4 + 0x10);
    if (uVar6 == 0) {
      uVar6 = 1 << (*(byte *)(iVar4 + 0xf) & 0xf);
      goto LAB_001720fe;
    }
  }
  else {
    uVar6 = *(uint *)(iVar4 + 0x10);
    fVar1 = 1.0;
    local_10 = 1.0;
    iVar10 = D3DRS_MultiSampleRenderTargetMode;
    if (uVar6 == 0) {
      uVar5 = 1 << ((byte)(*(uint *)(iVar4 + 0xc) >> 0x14) & 0xf);
      uVar6 = 1 << (*(byte *)(iVar4 + 0xf) & 0xf);
      goto LAB_001720fe;
    }
    uVar5 = (uVar6 & 0xfff) + 1;
  }
  uVar6 = (uVar6 >> 0xc & 0xfff) + 1;
LAB_001720fe:
  uVar9 = param_1[0x67f];
  uVar2 = param_1[2];
  param_1[2] = uVar2 & 0xffff7fff;
  if ((iVar10 != 0) && ((uVar9 & 0x200) == 0)) {
    local_10 = local_10 * 0.5;
    uVar5 = uVar5 + 1 >> 1;
    param_1[2] = uVar2 & 0xffff7fff | 0x8000;
    if (iVar10 == 2) {
      fVar1 = fVar1 * 0.5;
      uVar6 = uVar6 + 1 >> 1;
      uVar9 = uVar9 | 0x2000;
    }
    else {
      uVar9 = uVar9 | 0x1000;
    }
  }
  param_1[599] = fVar1;
  param_1[0x256] = local_10;
  param_1[0x254] = uVar5;
  param_1[0x255] = uVar6;
  if (local_10 < fVar1) {
    fVar1 = local_10;
  }
  local_10 = fVar1;
  puVar7 = (undefined4 *)*param_1;
  if ((undefined4 *)param_1[1] <= puVar7) {
    D3DDevice_MakeSpace();
    puVar7 = extraout_EAX;
  }
  *puVar7 = 0x40208;
  puVar7[1] = uVar9;
  puVar8 = puVar7 + 2;
  if ((float)param_1[600] != local_10) {
    param_1[600] = local_10;
    iVar4 = FUN_001782c0(local_10 + local_10 + 0.5);
    param_1[0x259] = *(undefined4 *)(&LAB_0017f99c + iVar4 * 4);
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x10f;
    uVar6 = FUN_001782c0(DAT_00181de4 * local_10 * 8.0 + 0.5);
    if (0x1ff < uVar6) {
      uVar6 = 0x1ff;
    }
    *puVar8 = 0x40380;
    puVar7[3] = uVar6;
    puVar8 = puVar7 + 4;
  }
  *param_1 = puVar8;
  uVar6 = D3DRS_MultiSampleMask << 0x10 | D3DRS_SampleAlpha;
  if (((char)((uint)param_1[2] >> 8) < '\0') && (D3DRS_MultiSampleAntiAlias != 0)) {
    uVar6 = uVar6 | 1;
  }
  if ((undefined4 *)param_1[1] <= puVar8) {
    D3DDevice_MakeSpace();
    puVar8 = extraout_EAX_00;
  }
  *puVar8 = 0x41d7c;
  puVar8[1] = uVar6;
  *param_1 = puVar8 + 2;
  if ((*(byte *)(param_1[0x1e4] + 4) & 2) != 0) {
    FUN_00173900();
  }
  D3DDevice_SetViewport(param_2);
  return;
}




void D3D8::D3DDevice_SetRenderState_ZEnable(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  undefined4 uVar3;
  bool bVar4;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  if ((Value == 0) || (pDVar1->field3354_0x19f8 == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  *puVar2 = 0x4030c;
  puVar2[1] = uVar3;
  uVar3 = DAT_00181cb8;
  puVar2[2] = 0x41d78;
  puVar2[3] = uVar3;
  pDVar1->State = puVar2 + 4;
  bVar4 = DAT_00181dac == 2;
  DAT_00181dac = Value;
  if ((bVar4) || (Value == 2)) {
    D3D_UpdateProjectionViewportTransform();
    FUN_00173900();
    if (pDVar1->field1_0x4 <= pDVar1->State) {
      D3DDevice_MakeSpace();
    }
    FUN_00171e10();
    puVar2 = (undefined4 *)FUN_00171c20();
    pDVar1->State = puVar2;
  }
  return;
}




void D3D8::D3DDevice_SetRenderState_StencilEnable(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  uVar3 = 0;
  if (D3DRS_StencilCullEnable != 0) {
    uVar3 = 2;
  }
  if ((D3DRS_OcclusionCullEnable != 0) &&
     ((D3DRS_StencilEnable == 0 || (D3DRS_StencilFail == 0x1e00)))) {
    uVar3 = uVar3 | 1;
  }
  *puVar2 = &DAT_00041d84;
  puVar2[1] = uVar3;
  if ((Value == 0) || (pDVar1->field3354_0x19f8 == 0)) {
    uVar4 = 0;
  }
  else {
    uVar4 = 1;
  }
  puVar2[2] = 0x4032c;
  puVar2[3] = uVar4;
  pDVar1->State = puVar2 + 4;
  D3DRS_StencilEnable = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_StencilFail(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  uint uVar3;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  uVar3 = 0;
  if (D3DRS_StencilCullEnable != 0) {
    uVar3 = 2;
  }
  if ((D3DRS_OcclusionCullEnable != 0) &&
     ((D3DRS_StencilEnable == 0 || (D3DRS_StencilFail == 0x1e00)))) {
    uVar3 = uVar3 | 1;
  }
  *puVar2 = &DAT_00041d84;
  puVar2[1] = uVar3;
  puVar2[2] = 0x40370;
  puVar2[3] = Value;
  pDVar1->State = puVar2 + 4;
  D3DRS_StencilFail = Value;
  return;
}




void D3D8::D3DDevice_SetRenderState_YuvEnable(undefined4 param_1)

{
  D3D__Device *pDVar1;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  D3DRS_YuvEnable = param_1;
  if (D3D_g_pDevice->field1_0x4 <= D3D_g_pDevice->State) {
    D3DDevice_MakeSpace();
  }
  puVar2 = (undefined4 *)FUN_00171e10();
  pDVar1->State = puVar2;
  return;
}




void D3D8::D3DDevice_SetRenderState_OcclusionCullEnable(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  uint uVar3;
  
  pDVar1 = D3D_g_pDevice;
  D3DRS_OcclusionCullEnable = Value;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  uVar3 = 0;
  if (D3DRS_StencilCullEnable != 0) {
    uVar3 = 2;
  }
  if ((D3DRS_OcclusionCullEnable != 0) &&
     ((D3DRS_StencilEnable == 0 || (D3DRS_StencilFail == 0x1e00)))) {
    uVar3 = uVar3 | 1;
  }
  *puVar2 = &DAT_00041d84;
  puVar2[1] = uVar3;
  pDVar1->State = puVar2 + 2;
  return;
}




void D3D8::D3DDevice_SetRenderState_StencilCullEnable(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  uint uVar3;
  
  pDVar1 = D3D_g_pDevice;
  D3DRS_StencilCullEnable = Value;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  uVar3 = 0;
  if (D3DRS_StencilCullEnable != 0) {
    uVar3 = 2;
  }
  if ((D3DRS_OcclusionCullEnable != 0) &&
     ((D3DRS_StencilEnable == 0 || (D3DRS_StencilFail == 0x1e00)))) {
    uVar3 = uVar3 | 1;
  }
  *puVar2 = &DAT_00041d84;
  puVar2[1] = uVar3;
  pDVar1->State = puVar2 + 2;
  return;
}




void D3D8::D3DDevice_SetRenderState_RopZCmpAlwaysRead(DWORD Value)

{
  D3DRS_RopZCmpAlwaysRead = Value;
  D3D_CommonSetDebugRegisters();
  return;
}




void D3D8::D3DDevice_SetRenderState_RopZRead(DWORD Value)

{
  D3DRS_RopZRead = Value;
  D3D_CommonSetDebugRegisters();
  return;
}




void D3D8::D3DDevice_SetRenderState_DoNotCullUncompressed(DWORD Value)

{
  D3DRS_DoNotCullUncompressed = Value;
  D3D_CommonSetDebugRegisters();
  return;
}




void D3D8::D3DDevice_SetRenderState_MultiSampleMode(DWORD Value)

{
  D3DRS_MultiSampleMode = Value;
  if (D3D_g_pDevice->field3353_0x19f4 == D3D_g_pDevice->field3357_0x1a04) {
    D3D_CommonSetMultiSampleModeAndScale();
  }
  return;
}




void D3D8::D3DDevice_SetRenderState_MultiSampleRenderTargetMode(DWORD Value)

{
  D3DRS_MultiSampleRenderTargetMode = Value;
  if (D3D_g_pDevice->field3353_0x19f4 != D3D_g_pDevice->field3357_0x1a04) {
    D3D_CommonSetMultiSampleModeAndScale();
  }
  return;
}




void D3D8::D3DDevice_SetRenderState_MultiSampleAntiAlias(DWORD Value)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  uint uVar3;
  
  pDVar1 = D3D_g_pDevice;
  D3DRS_MultiSampleAntiAlias = Value;
  FUN_00173900();
  uVar3 = D3DRS_MultiSampleMask << 0x10 | D3DRS_SampleAlpha;
  if (((char)(pDVar1->bitField1 >> 8) < '\0') && (D3DRS_MultiSampleAntiAlias != 0)) {
    uVar3 = uVar3 | 1;
  }
  puVar2 = pDVar1->State;
  if (pDVar1->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x41d7c;
  puVar2[1] = uVar3;
  pDVar1->State = puVar2 + 2;
  if (pDVar1->field1_0x4 <= puVar2 + 2) {
    D3DDevice_MakeSpace();
  }
  puVar2 = (undefined4 *)FUN_00171c20();
  pDVar1->State = puVar2;
  return;
}




void D3D8::D3DDevice_SetRenderState_MultiSampleMask(DWORD Value)

{
  D3D__Device *pDVar1;
  uint uVar2;
  undefined4 *extraout_EAX;
  undefined4 *puVar3;
  
  pDVar1 = D3D_g_pDevice;
  D3DRS_MultiSampleMask = Value;
  uVar2 = Value << 0x10 | D3DRS_SampleAlpha;
  if (((char)(D3D_g_pDevice->bitField1 >> 8) < '\0') && (D3DRS_MultiSampleAntiAlias != 0)) {
    uVar2 = uVar2 | 1;
  }
  puVar3 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX;
  }
  *puVar3 = 0x41d7c;
  puVar3[1] = uVar2;
  pDVar1->State = puVar3 + 2;
  return;
}




HRESULT D3D8::D3DDevice_SetRenderState_SampleAlpha(DWORD dwSampleAlpha)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  uint uVar3;
  
  pDVar1 = D3D_g_pDevice;
  uVar3 = D3DRS_MultiSampleMask << 0x10 | dwSampleAlpha;
  D3DRS_SampleAlpha = dwSampleAlpha;
  if (((char)(D3D_g_pDevice->bitField1 >> 8) < '\0') && (D3DRS_MultiSampleAntiAlias != 0)) {
    uVar3 = uVar3 | 1;
  }
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x41d7c;
  puVar2[1] = uVar3;
  pDVar1->State = puVar2 + 2;
  return (HRESULT)(puVar2 + 2);
}




void D3D8::D3DDevice_DrawVertices(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT VertexCount)

{
  D3D__Device *pDVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  pDVar1 = D3D_g_pDevice;
  CDevice_SetStateVB(0);
  uVar4 = VertexCount - 1 >> 8;
  puVar2 = (undefined4 *)D3DDevice_BeginStateBig(uVar4 + 6);
  *puVar2 = 0x417fc;
  puVar2[1] = PrimitiveType;
  puVar2[2] = (uVar4 + 1) * 0x40000 + 0x40001810;
  if (0x100 < VertexCount) {
    iVar3 = (VertexCount - 0x101 >> 8) + 1;
    do {
      puVar2[3] = StartVertex | 0xff000000;
      puVar2 = puVar2 + 1;
      StartVertex = StartVertex + 0x100;
      VertexCount = VertexCount - 0x100;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  puVar2[3] = (VertexCount - 1) * 0x1000000 | StartVertex;
  puVar2[4] = 0x417fc;
  puVar2[5] = 0;
  pDVar1->State = puVar2 + 6;
  return;
}



void D3D8::D3DDevice_DrawIndexedVertices
               (D3DPRIMITIVETYPE PrimitiveType,UINT VertexCount,PWORD pIndexData)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  ushort uVar8;
  undefined8 *puVar9;
  D3D__Device *pDVar10;
  undefined4 *puVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int *piVar16;
  PWORD pWVar17;
  int local_8;
  
  pDVar10 = D3D_g_pDevice;
  CDevice_SetStateVB(*(undefined4 *)&D3D_g_pDevice->field_0x1c);
  pDVar10->bitField1 = pDVar10->bitField1 | 0x800;
  puVar11 = (undefined4 *)D3DDevice_BeginStateBig(0x209);
  *puVar11 = 0x417fc;
  puVar11[1] = PrimitiveType;
  PrimitiveType = (D3DPRIMITIVETYPE)(puVar11 + 2);
  uVar12 = -PrimitiveType >> 2 & 7;
  if (uVar12 * 2 + 0x3e <= VertexCount) {
    if (uVar12 != 0) {
      iVar13 = uVar12 - 1;
      *(int *)PrimitiveType = iVar13 * 0x40000 + 0x40001800;
      pWVar17 = pIndexData;
      for (iVar15 = iVar13; PrimitiveType = PrimitiveType + 4, iVar15 != 0; iVar15 = iVar15 + -1) {
        *(int *)PrimitiveType = *(int *)pWVar17;
        pWVar17 = pWVar17 + 2;
      }
      pIndexData = pIndexData + iVar13 * 2;
      PrimitiveType = (D3DPRIMITIVETYPE)(puVar11 + uVar12 + 2);
      VertexCount = VertexCount + iVar13 * -2;
    }
    if (VertexCount % 0x3fe < 0x3e) {
      local_8 = 0x1ff;
    }
    else {
      local_8 = ((VertexCount % 0x3fe >> 1) + 1 & 0xfffffff0) - 1;
    }
    do {
      *(int *)PrimitiveType = local_8 * 0x40000 + 0x40001800;
      uVar12 = local_8 - 0xfU >> 4;
      uVar1 = *(undefined8 *)(pIndexData + 2);
      uVar2 = *(undefined8 *)(pIndexData + 6);
      uVar3 = *(undefined8 *)(pIndexData + 10);
      uVar4 = *(undefined8 *)(pIndexData + 0xe);
      uVar5 = *(undefined8 *)(pIndexData + 0x12);
      uVar6 = *(undefined8 *)(pIndexData + 0x16);
      uVar7 = *(undefined8 *)(pIndexData + 0x1a);
      *(undefined4 *)(PrimitiveType + D3DPT_LINESTRIP) = *(undefined4 *)pIndexData;
      *(undefined8 *)(PrimitiveType + D3DPT_QUADLIST) = uVar1;
      *(undefined8 *)(PrimitiveType + 0x10) = uVar2;
      *(undefined8 *)(PrimitiveType + 0x18) = uVar3;
      *(undefined8 *)(PrimitiveType + 0x20) = uVar4;
      *(undefined8 *)(PrimitiveType + 0x28) = uVar5;
      *(undefined8 *)(PrimitiveType + 0x30) = uVar6;
      *(undefined8 *)(PrimitiveType + 0x38) = uVar7;
      pWVar17 = pIndexData + 0x1e;
      puVar9 = (undefined8 *)PrimitiveType;
      do {
        uVar1 = *(undefined8 *)(pWVar17 + 4);
        uVar2 = *(undefined8 *)(pWVar17 + 8);
        uVar3 = *(undefined8 *)(pWVar17 + 0xc);
        uVar4 = *(undefined8 *)(pWVar17 + 0x10);
        uVar5 = *(undefined8 *)(pWVar17 + 0x14);
        uVar6 = *(undefined8 *)(pWVar17 + 0x18);
        uVar7 = *(undefined8 *)(pWVar17 + 0x1c);
        puVar9[8] = *(undefined8 *)pWVar17;
        puVar9[9] = uVar1;
        puVar9[10] = uVar2;
        puVar9[0xb] = uVar3;
        puVar9[0xc] = uVar4;
        puVar9[0xd] = uVar5;
        puVar9[0xe] = uVar6;
        puVar9[0xf] = uVar7;
        pWVar17 = pWVar17 + 0x20;
        uVar12 = uVar12 - 1;
        puVar9 = puVar9 + 8;
      } while (uVar12 != 0);
      pIndexData = pIndexData + local_8 * 2;
      VertexCount = VertexCount + local_8 * -2;
      pDVar10->State = (undefined4 *)(local_8 * 4 + 4 + PrimitiveType);
      PrimitiveType = D3DDevice_BeginStateBig(0x204);
      local_8 = 0x1ff;
    } while (0x3fd < VertexCount);
  }
  uVar14 = VertexCount >> 1;
  *(uint *)PrimitiveType = uVar14 * 0x40000 + 0x40001800;
  pWVar17 = pIndexData;
  piVar16 = (int *)PrimitiveType;
  for (uVar12 = uVar14; piVar16 = piVar16 + 1, uVar12 != 0; uVar12 = uVar12 - 1) {
    *piVar16 = *(int *)pWVar17;
    pWVar17 = pWVar17 + 2;
  }
  piVar16 = (int *)(PrimitiveType + (uVar14 + 1) * 4);
  if ((VertexCount & 1) != 0) {
    uVar8 = pIndexData[uVar14 * 2];
    *piVar16 = 0x41808;
    piVar16[1] = (uint)uVar8;
    piVar16 = piVar16 + 2;
  }
  *piVar16 = 0x417fc;
  piVar16[1] = 0;
  uVar12 = pDVar10->bitField1;
  pDVar10->State = piVar16 + 2;
  pDVar10->bitField1 = uVar12 & 0xffffe7ff;
  if ((uVar12 & 0x1000) != 0) {
    D3D_SetFence(1);
  }
  return;
}




void D3D8::D3DDevice_SetVertexData2f(int Register,FLOAT a,FLOAT b)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  puVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = &LAB_00081880 + Register * 8;
  puVar2[1] = a;
  puVar2[2] = b;
  pDVar1->State = puVar2 + 3;
  return;
}




void D3D8::D3DDevice_SetVertexData4f(int Register,FLOAT a,FLOAT b,FLOAT c,FLOAT d)

{
  D3D__Device *pDVar1;
  int *extraout_EAX;
  int *piVar2;
  int iVar3;
  
  pDVar1 = D3D_g_pDevice;
  piVar2 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= piVar2) {
    D3DDevice_MakeSpace();
    piVar2 = extraout_EAX;
  }
  if (Register == -1) {
    iVar3 = 0x1518;
  }
  else {
    iVar3 = (Register + 0x1a0) * 0x10;
  }
  *piVar2 = iVar3 + 0x100000;
  piVar2[1] = (int)a;
  piVar2[2] = (int)b;
  piVar2[3] = (int)c;
  piVar2[4] = (int)d;
  pDVar1->State = piVar2 + 5;
  return;
}



// Colour is ARGB


void D3D8::D3DDevice_SetVertexDataColor(int Register,D3DCOLOR Color)

{
  int *piVar2;
  int *piVar1;
  D3D__Device *pDVar1;
  
  pDVar1 = D3D_g_pDevice;
  piVar1 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= piVar1) {
    D3DDevice_MakeSpace();
    piVar1 = piVar2;
  }
  *piVar1 = Register * 4 + 0x41940;
  piVar1[1] = Color >> 0x10 & 0xff | (Color & 0xff) << 0x10 | Color & 0xff00ff00;
  pDVar1->State = piVar1 + 2;
  return;
}




void D3D8::D3DDevice_Begin(D3DPRIMITIVETYPE PrimitiveType)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  FUN_001799a0();
  puVar2 = pDVar1->State;
  if (pDVar1->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = extraout_EAX;
  }
  *puVar2 = 0x417fc;
  puVar2[1] = PrimitiveType;
  pDVar1->State = puVar2 + 2;
  pDVar1->bitField1 = pDVar1->bitField1 | 0x800;
  return;
}




void D3D8::D3DDevice_End(void)

{
  uint uVar1;
  D3D__Device *pDVar2;
  undefined4 *extraout_EAX;
  undefined4 *puVar3;
  
  pDVar2 = D3D_g_pDevice;
  puVar3 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX;
  }
  *puVar3 = 0x417fc;
  puVar3[1] = 0;
  pDVar2->State = puVar3 + 2;
  uVar1 = pDVar2->bitField1;
  pDVar2->bitField1 = uVar1 & 0xffffe7ff;
  if ((uVar1 & 0x1000) != 0) {
    D3D_SetFence(1);
  }
  return;
}




D3D8::D3DDevice_SetVertexShaderConstant1(INT Register,DirectXShaderConstant *pConstantData)

{
  float fVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  while( true ) {
    puVar2 = D3D::D3D__Device.State;
    if (D3D::D3D__Device.State + 7 < D3D::D3D__Device.field1_0x4) break;
    D3DDevice_MakeSpace();
  }
  puVar3 = D3D::D3D__Device.State + 7;
  *D3D::D3D__Device.State = 0x41ea4;
  D3D::D3D__Device.State = puVar3;
  puVar2[1] = Register;
  puVar2[2] = FUN_00100b80;
  fVar1 = pConstantData->c1;
  puVar2[3] = fVar1;
  DirectX::VertexShaderRegisters[Register].c1 = fVar1;
  fVar1 = pConstantData->c2;
  puVar2[4] = fVar1;
  DirectX::VertexShaderRegisters[Register].c2 = fVar1;
  fVar1 = pConstantData->c3;
  puVar2[5] = fVar1;
  DirectX::VertexShaderRegisters[Register].c3 = fVar1;
  fVar1 = pConstantData->c4;
  puVar2[6] = fVar1;
  DirectX::VertexShaderRegisters[Register].c4 = fVar1;
  return;
}



// 0x40 bytes (one vertex shader constant is 0x10)

void __fastcall

D3D8::D3DDevice_SetVertexShaderConstant4(INT Register,DirectXShaderConstant *pConstantData)

{
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  double uVar1;
  
  while( true ) {
    puVar9 = D3D::D3D__Device.State;
    if (D3D::D3D__Device.State + 0x13 < D3D::D3D__Device.field1_0x4) break;
    D3DDevice_MakeSpace();
  }
  uVar1 = *(double *)pConstantData;
  uVar2._0_4_ = pConstantData->c3;
  uVar2._4_4_ = pConstantData->c4;
  uVar3._0_4_ = pConstantData[1].c1;
  uVar3._4_4_ = pConstantData[1].c2;
  uVar4._0_4_ = pConstantData[1].c3;
  uVar4._4_4_ = pConstantData[1].c4;
  uVar5._0_4_ = pConstantData[2].c1;
  uVar5._4_4_ = pConstantData[2].c2;
  uVar6._0_4_ = pConstantData[2].c3;
  uVar6._4_4_ = pConstantData[2].c4;
  uVar7._0_4_ = pConstantData[3].c1;
  uVar7._4_4_ = pConstantData[3].c2;
  uVar8._0_4_ = pConstantData[3].c3;
  uVar8._4_4_ = pConstantData[3].c4;
  puVar10 = D3D::D3D__Device.State + 0x13;
  *D3D::D3D__Device.State = 0x41ea4;
  D3D::D3D__Device.State = puVar10;
  puVar9[1] = Register;
  puVar9[2] = &DAT_00400b80;
  *(double *)(puVar9 + 3) = uVar1;
  *(double *)(DirectX::VertexShaderRegisters + Register) = uVar1;
  *(undefined8 *)(puVar9 + 5) = uVar2;
  DirectX::VertexShaderRegisters[Register].c3 = (float)(undefined4)uVar2;
  DirectX::VertexShaderRegisters[Register].c4 = (float)uVar2._4_4_;
  *(undefined8 *)(puVar9 + 7) = uVar3;
  DirectX::VertexShaderRegisters[Register + 1].c1 = (float)(undefined4)uVar3;
  DirectX::VertexShaderRegisters[Register + 1].c2 = (float)uVar3._4_4_;
  *(undefined8 *)(puVar9 + 9) = uVar4;
  DirectX::VertexShaderRegisters[Register + 1].c3 = (float)(undefined4)uVar4;
  DirectX::VertexShaderRegisters[Register + 1].c4 = (float)uVar4._4_4_;
  *(undefined8 *)(puVar9 + 0xb) = uVar5;
  DirectX::VertexShaderRegisters[Register + 2].c1 = (float)(undefined4)uVar5;
  DirectX::VertexShaderRegisters[Register + 2].c2 = (float)uVar5._4_4_;
  *(undefined8 *)(puVar9 + 0xd) = uVar6;
  DirectX::VertexShaderRegisters[Register + 2].c3 = (float)(undefined4)uVar6;
  DirectX::VertexShaderRegisters[Register + 2].c4 = (float)uVar6._4_4_;
  *(undefined8 *)(puVar9 + 0xf) = uVar7;
  DirectX::VertexShaderRegisters[Register + 3].c1 = (float)(undefined4)uVar7;
  DirectX::VertexShaderRegisters[Register + 3].c2 = (float)uVar7._4_4_;
  *(undefined8 *)(puVar9 + 0x11) = uVar8;
  DirectX::VertexShaderRegisters[Register + 3].c3 = (float)(undefined4)uVar8;
  DirectX::VertexShaderRegisters[Register + 3].c4 = (float)uVar8._4_4_;
  return;
}



void __fastcall
D3D8::D3DDevice_SetVertexShaderConstantNotInlineFast
          (INT Register,PVOID pConstantData,DWORD ConstantCount)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  uint *extraout_EAX;
  undefined4 *extraout_EAX_00;
  
  if (D3D::D3D__Device.field1_0x4 <= D3D::D3D__Device.State) {
    D3DDevice_MakeSpace();
    D3D::D3D__Device.State = extraout_EAX_00;
  }
  *D3D::D3D__Device.State = 0x41ea4;
  D3D::D3D__Device.State[1] = Register;
  D3D::D3D__Device.State = D3D::D3D__Device.State + 2;
  if (ConstantCount < 0x10) {
LAB_0017351b:
    *D3D::D3D__Device.State = ConstantCount << 0x12 | 0xb80;
    for (; D3D::D3D__Device.State = D3D::D3D__Device.State + 1, ConstantCount != 0;
        ConstantCount = ConstantCount - 1) {
      *D3D::D3D__Device.State = *(uint *)pConstantData;
      pConstantData = (uint *)((int)pConstantData + 4);
    }
  }
  else {
    while( true ) {
      uVar1 = *(undefined8 *)pConstantData;
      uVar2 = *(undefined8 *)((int)pConstantData + 8);
      uVar3 = *(undefined8 *)((int)pConstantData + 0x10);
      uVar4 = *(undefined8 *)((int)pConstantData + 0x18);
      uVar5 = *(undefined8 *)((int)pConstantData + 0x20);
      uVar6 = *(undefined8 *)((int)pConstantData + 0x28);
      uVar7 = *(undefined8 *)((int)pConstantData + 0x30);
      uVar8 = *(undefined8 *)((int)pConstantData + 0x38);
      *D3D::D3D__Device.State = &DAT_00400b80;
      *(undefined8 *)(D3D::D3D__Device.State + 1) = uVar1;
      *(undefined8 *)(D3D::D3D__Device.State + 3) = uVar2;
      *(undefined8 *)(D3D::D3D__Device.State + 5) = uVar3;
      *(undefined8 *)(D3D::D3D__Device.State + 7) = uVar4;
      *(undefined8 *)(D3D::D3D__Device.State + 9) = uVar5;
      *(undefined8 *)(D3D::D3D__Device.State + 0xb) = uVar6;
      *(undefined8 *)(D3D::D3D__Device.State + 0xd) = uVar7;
      *(undefined8 *)(D3D::D3D__Device.State + 0xf) = uVar8;
      D3D::D3D__Device.State = D3D::D3D__Device.State + 0x11;
      ConstantCount = ConstantCount - 0x10;
      if (ConstantCount == 0) break;
      pConstantData = (PVOID)((int)pConstantData + 0x40);
      if (ConstantCount < 0x10) goto LAB_0017351b;
      if (D3D::D3D__Device.field1_0x4 <= D3D::D3D__Device.State) {
        D3DDevice_MakeSpace();
        D3D::D3D__Device.State = extraout_EAX;
      }
    }
  }
  return;
}



void __fastcall
D3D8::D3DDevice_SetVertexShaderConstantNotInline
          (INT Register,PVOID pConstantData,DWORD ConstantCount)

{
  DWORD DVar1;
  float *pfVar2;
  DirectXShaderConstant *pDVar3;
  
  if (((byte)D3D::D3D__Device.bitField1 & 0x10) == 0) {
    pfVar2 = pConstantData;
    pDVar3 = DirectX::VertexShaderRegisters + Register;
    for (DVar1 = ConstantCount; DVar1 != 0; DVar1 = DVar1 - 1) {
      pDVar3->c1 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pDVar3 = (DirectXShaderConstant *)&pDVar3->c2;
    }
  }
  D3DDevice_SetVertexShaderConstantNotInlineFast(Register,pConstantData,ConstantCount);
  return;
}




void D3D8::D3DDevice_SetStreamSource(UINT StreamNumber,D3DVertexBuffer *pStreamData,UINT Stride)

{
  D3DResource *pResource;
  UINT UVar1;
  D3D__Device *pDVar2;
  uint uVar3;
  
  pDVar2 = D3D_g_pDevice;
  if (pStreamData != (D3DVertexBuffer *)0x0) {
    (pStreamData->resource).Common = (pStreamData->resource).Common + 0x80000;
  }
  if ((&D3D::D3D__Device.field4034_0x2498)[StreamNumber * 3] != 0) {
    *(undefined4 *)((&D3D::D3D__Device.field4034_0x2498)[StreamNumber * 3] + 8) =
         *(undefined4 *)&pDVar2->field_0x2c;
    pResource = (D3DResource *)(&D3D::D3D__Device.field4034_0x2498)[StreamNumber * 3];
    uVar3 = pResource->Common - 0x80000;
    pResource->Common = uVar3;
    if ((uVar3 & 0x78ffff) == 0) {
      D3D_DestroyResource(pResource);
    }
  }
  UVar1 = (&D3D::D3D__Device.field4032_0x2490)[StreamNumber * 3];
  (&D3D::D3D__Device.field4032_0x2490)[StreamNumber * 3] = Stride;
  (&D3D::D3D__Device.field4034_0x2498)[StreamNumber * 3] = pStreamData;
  if (Stride == UVar1) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x40;
    return;
  }
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x70;
  return;
}




void D3D8::D3DDevice_LoadVertexShader(DWORD Handle,DWORD Address)

{
  int iVar1;
  D3D__Device *pDVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  pDVar2 = D3D_g_pDevice;
  if ((D3D_g_pDevice->bitField1 & 0x10) == 0) {
    FUN_00172ee0(Handle - 1,Address);
  }
  iVar4 = *(int *)(Handle + 0xb);
  iVar1 = iVar4 + 2;
  puVar3 = (undefined4 *)D3DDevice_BeginStateBig(iVar1);
  *puVar3 = 0x41e9c;
  puVar3[1] = Address;
  puVar5 = (undefined4 *)(Handle + 0x113);
  puVar6 = puVar3 + 2;
  for (; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  pDVar2->State = puVar3 + iVar1;
  return;
}




void D3D8::D3DDevice_SelectVertexShader(DWORD Handle,DWORD Address)

{
  uint uVar1;
  UINT UVar2;
  D3D__Device *pDVar3;
  undefined4 *puVar4;
  undefined4 *extraout_EAX;
  
  pDVar3 = D3D_g_pDevice;
  if (Handle != 0) {
    uVar1 = *(uint *)(D3D_g_pDevice->field1876_0x790 + 4);
    D3D_g_pDevice->field1876_0x790 = (undefined *)(Handle - 1);
    *(DWORD *)&pDVar3->field_0x794 = Handle;
    UVar2 = Graphics::GraphicsFlags;
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x70;
    if (((*(uint *)(Handle + 3) ^ uVar1) & 0x13) != 0) {
      Graphics::GraphicsFlags = UVar2 | 0x1070;
      if (pDVar3->field1_0x4 <= pDVar3->State) {
        D3DDevice_MakeSpace();
      }
      puVar4 = (undefined4 *)FUN_00171c20();
      uVar1 = *(uint *)(Handle + 3);
      *puVar4 = &LAB_00081e8e_6;
      puVar4[1] = 6;
      puVar4[2] = uVar1 & 1;
      pDVar3->State = puVar4 + 3;
    }
  }
  puVar4 = pDVar3->State;
  if (pDVar3->field1_0x4 <= puVar4) {
    D3DDevice_MakeSpace();
    puVar4 = extraout_EAX;
  }
  *puVar4 = 0x41ea0;
  puVar4[1] = Address;
  pDVar3->State = puVar4 + 2;
  *(DWORD *)&pDVar3->field_0x798 = Address;
  return;
}




void D3D8::D3DDevice_SetShaderConstantMode(VERTEXSHADERCONSTANTMODE Mode)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  pDVar1 = D3D_g_pDevice;
  if ((Mode & 0x10) == 0) {
    uVar3 = D3D_g_pDevice->bitField1 & 0xfffffdff;
  }
  else {
    uVar3 = D3D_g_pDevice->bitField1 | 0x200;
  }
  D3D_g_pDevice->bitField1 = uVar3;
  pDVar1->field3298_0x1918 = Mode & 0xffffffef;
  if ((Mode & 0xffffffef) == 0) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x1600;
    puVar2 = pDVar1->State;
    if (pDVar1->field1_0x4 <= puVar2) {
      D3DDevice_MakeSpace();
      puVar2 = extraout_EAX;
    }
    *puVar2 = 0x41ea4;
    puVar2[1] = 0x3c;
    puVar2[2] = 0x300b80;
    puVar5 = &DAT_0017fa88;
    puVar6 = puVar2 + 3;
    for (iVar4 = 0xc; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    FUN_00176f10(puVar2 + 0xf,s_XACT_SOUNDBANK_GVAMPIRECHICKEN_B_00400838 + 8,&DirectX::Transform);
    FUN_00176f10(puVar2 + 0x20,&DAT_00400880,&DirectX::Transform);
    FUN_00176f10(puVar2 + 0x31,&DAT_004008c0,&DirectX::Transform);
    FUN_00176f10(puVar2 + 0x42,&DAT_00400900,&DirectX::Transform);
    puVar2[0x53] = 0x1009d0;
    puVar2[0x54] = 0;
    puVar2[0x55] = 0;
    puVar2[0x57] = 0;
    puVar2[0x56] = 0x3f800000;
    puVar2[0x58] = 0x100a50;
    puVar2[0x59] = 0;
    puVar2[0x5a] = 0;
    puVar2[0x5b] = 0;
    puVar2[0x5c] = 0x3f800000;
    pDVar1->State = puVar2 + 0x5d;
  }
  return;
}




void D3D8::D3DDevice_SetVertexShader(DWORD Handle)

{
  uint uVar1;
  int iVar2;
  D3D__Device *pDVar3;
  uint uVar4;
  undefined4 *extraout_EAX;
  undefined4 *puVar5;
  undefined *puVar6;
  
  pDVar3 = D3D_g_pDevice;
  uVar1 = *(uint *)(D3D_g_pDevice->field1876_0x790 + 4);
  iVar2 = *(int *)(D3D_g_pDevice->field1876_0x790 + 0x10);
  if ((Handle & 1) == 0) {
    puVar6 = &DAT_00184478;
    FUN_00172da0(&DAT_00184478,Handle);
  }
  else {
    puVar6 = (undefined *)(Handle - 1);
    if ((*(byte *)(Handle + 3) & 0x10) != 0) {
      D3DDevice_LoadVertexShader(Handle,0);
      D3DDevice_SelectVertexShader(Handle,0);
      return;
    }
  }
  uVar4 = Graphics::GraphicsFlags | 0x70;
  if (iVar2 != *(int *)(puVar6 + 0x10)) {
    uVar4 = Graphics::GraphicsFlags | 0x470;
  }
  Graphics::GraphicsFlags = uVar4;
  if (uVar1 != *(uint *)(puVar6 + 4)) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x1600;
  }
  puVar5 = pDVar3->State;
  pDVar3->field1876_0x790 = puVar6;
  *(DWORD *)&pDVar3->field_0x794 = Handle;
  *(undefined4 *)&pDVar3->field_0x798 = 0;
  if (pDVar3->field1_0x4 <= puVar5) {
    D3DDevice_MakeSpace();
    puVar5 = extraout_EAX;
  }
  if ((*(uint *)(puVar6 + 4) & 0x400) == 0) {
    *puVar5 = 0x4194c;
    puVar5[1] = 0xffffffff;
    puVar5 = puVar5 + 2;
  }
  if ((*(uint *)(puVar6 + 4) & 0x800) == 0) {
    *puVar5 = 0x41950;
    puVar5[1] = 0;
    puVar5 = puVar5 + 2;
  }
  if ((*(uint *)(puVar6 + 4) & 0x1000) == 0) {
    *puVar5 = 0x4195c;
    puVar5[1] = 0xffffffff;
    puVar5 = puVar5 + 2;
  }
  if ((*(uint *)(puVar6 + 4) & 0x2000) == 0) {
    *puVar5 = 0x41960;
    puVar5[1] = 0;
    puVar5 = puVar5 + 2;
  }
  if ((*(uint *)(puVar6 + 4) & 2) != 0) {
    puVar5 = (undefined4 *)FUN_00171c20();
    *puVar5 = 0x41ea0;
    puVar5[1] = 0;
    puVar5[2] = &LAB_00081e8e_6;
    puVar5[3] = 6;
    puVar5[4] = 0;
    pDVar3->State = puVar5 + 5;
    FUN_00173900();
    return;
  }
  if (((*(uint *)(puVar6 + 4) ^ uVar1) & 0x12) != 0) {
    *puVar5 = 0x41e94;
    puVar5[1] = 4;
    puVar5 = (undefined4 *)FUN_00171c20();
  }
  pDVar3->State = puVar5;
  return;
}




void D3D8::D3DDevice_SetVertexShaderInput(DWORD Handle,UINT StreamCount,STREAMINPUT *pStreamInputs)

{
  D3DResource *pDVar1;
  UINT UVar2;
  D3D__Device *pDVar3;
  int *extraout_EAX;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  undefined4 *puVar8;
  STREAMINPUT *pSVar9;
  int *piVar10;
  uint uVar11;
  int local_40 [16];
  
  pDVar3 = D3D_g_pDevice;
  UVar2 = StreamCount;
  pSVar9 = pStreamInputs;
  if (Handle != 0) {
    for (; UVar2 != 0; UVar2 = UVar2 - 1) {
      (pSVar9->VertexBuffer->resource).Common = (pSVar9->VertexBuffer->resource).Common + 0x80000;
      pSVar9 = pSVar9 + 1;
    }
    uVar11 = 0;
    if (pDVar3->field2393_0xaf4 != 0) {
      puVar8 = &pDVar3->field2394_0xaf8;
      do {
        pDVar1 = (D3DResource *)*puVar8;
        pDVar1->Lock = *(DWORD *)&pDVar3->field_0x2c;
        uVar7 = pDVar1->Common - 0x80000;
        pDVar1->Common = uVar7;
        if ((uVar7 & 0x78ffff) == 0) {
          D3D_DestroyResource(pDVar1);
        }
        uVar11 = uVar11 + 1;
        puVar8 = puVar8 + 3;
      } while (uVar11 < (uint)pDVar3->field2393_0xaf4);
    }
    Graphics::GraphicsFlags = Graphics::GraphicsFlags & 0xffffff8f | 0x40000000;
    pDVar3->field2392_0xaf0 = Handle;
    pDVar3->field2393_0xaf4 = StreamCount;
    pSVar9 = pStreamInputs;
    puVar8 = &pDVar3->field2394_0xaf8;
    for (uVar11 = StreamCount * 3 & 0x3fffffff; uVar11 != 0; uVar11 = uVar11 - 1) {
      *puVar8 = pSVar9->VertexBuffer;
      pSVar9 = (STREAMINPUT *)&pSVar9->Stride;
      puVar8 = puVar8 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar8 = *(undefined1 *)&pSVar9->VertexBuffer;
      pSVar9 = (STREAMINPUT *)((int)&pSVar9->VertexBuffer + 1);
      puVar8 = (undefined4 *)((int)puVar8 + 1);
    }
    piVar4 = pDVar3->State;
    if (pDVar3->field1_0x4 <= piVar4) {
      D3DDevice_MakeSpace();
      piVar4 = extraout_EAX;
    }
    uVar11 = 0;
    *piVar4 = (int)&DAT_00401720;
    piVar6 = (int *)(Handle + 0x1b);
    piVar10 = piVar4;
    do {
      piVar10 = piVar10 + 1;
      pSVar9 = pStreamInputs + piVar6[-2];
      *piVar10 = piVar6[-1] + (pSVar9->VertexBuffer->resource).Data + pSVar9->Offset;
      local_40[uVar11] = pSVar9->Stride * 0x100 + *piVar6;
      uVar11 = uVar11 + 1;
      piVar6 = piVar6 + 4;
    } while (uVar11 < 0x10);
    piVar4[0x11] = (int)&DAT_00401760;
    piVar10 = local_40;
    piVar6 = piVar4 + 0x12;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar6 = *piVar10;
      piVar10 = piVar10 + 1;
      piVar6 = piVar6 + 1;
    }
    pDVar3->State = piVar4 + 0x22;
    return;
  }
  Graphics::GraphicsFlags = Graphics::GraphicsFlags & 0xbfffffff | 0x70;
  uVar11 = 0;
  if (D3D_g_pDevice->field2393_0xaf4 != 0) {
    puVar8 = &D3D_g_pDevice->field2394_0xaf8;
    do {
      pDVar1 = (D3DResource *)*puVar8;
      uVar7 = pDVar1->Common - 0x80000;
      pDVar1->Lock = *(DWORD *)&pDVar3->field_0x2c;
      pDVar1->Common = uVar7;
      if ((uVar7 & 0x78ffff) == 0) {
        D3D_DestroyResource(pDVar1);
      }
      uVar11 = uVar11 + 1;
      puVar8 = puVar8 + 3;
    } while (uVar11 < (uint)pDVar3->field2393_0xaf4);
  }
  pDVar3->field2393_0xaf4 = 0;
  return;
}




void D3D8::D3DDevice_SetGammaRamp(DWORD dwFlags,D3DGAMMARAMP *pRamp)

{
  undefined4 *puVar1;
  D3D__Device *pDVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  D3DGAMMARAMP *pDVar6;
  undefined4 *puVar7;
  bool bVar8;
  
  pDVar2 = D3D_g_pDevice;
  uVar3 = D3D_g_pDevice->field4022_0x2468 & 1;
  iVar4 = 0xc0;
  bVar8 = true;
  piVar5 = &D3D_g_pDevice->field3609_0x1df4 + D3D_g_pDevice->field3995_0x23fc * 0xc0;
  pDVar6 = pRamp;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar8 = *piVar5 == *(int *)pDVar6->red;
    piVar5 = piVar5 + 1;
    pDVar6 = (D3DGAMMARAMP *)(pDVar6->red + 4);
  } while (bVar8);
  if (!bVar8) {
    puVar1 = &D3D_g_pDevice->field3609_0x1df4;
    puVar7 = puVar1 + uVar3 * 0xc0;
    for (iVar4 = 0xc0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = *(undefined4 *)pRamp->red;
      pRamp = (D3DGAMMARAMP *)(pRamp->red + 4);
      puVar7 = puVar7 + 1;
    }
    pDVar2->field3995_0x23fc = uVar3;
    if ((dwFlags & 2) != 0) {
      FUN_00179d80(puVar1 + uVar3 * 0xc0);
      return;
    }
    (&pDVar2->field3993_0x23f4)[uVar3] = 1;
  }
  return;
}




void D3D8::D3DDevice_SetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX *pMatrix)

{
  D3D__Device *pDVar1;
  uint uVar2;
  int iVar3;
  D3DMATRIX *pDVar4;
  float *pfVar5;
  
  pDVar1 = D3D_g_pDevice;
  pDVar4 = pMatrix;
  pfVar5 = (float *)(&D3D_g_pDevice->field2480_0xc50 + State * 0x10);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar5 = (pDVar4->DUMMYUNIONNAME).DUMMYSTRUCTNAME._11;
    pDVar4 = (D3DMATRIX *)((int)&pDVar4->DUMMYUNIONNAME + 4);
    pfVar5 = pfVar5 + 1;
  }
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | *(uint *)(&DAT_0017fd90 + State * 4);
  if (State == D3DTS_PROJECTION) {
    if (((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._33 ==
         (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._34) ||
       ((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._33 == 0.0)) {
      *(undefined4 *)&pDVar1->field_0x938 = 0;
      *(undefined4 *)&pDVar1->field_0x93c = 0x3f800000;
    }
    else {
      *(float *)&pDVar1->field_0x938 =
           (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._44 -
           ((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._43 /
           (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._33) *
           (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._34;
      *(float *)&pDVar1->field_0x93c =
           (((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._44 -
            (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._43) /
           ((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._33 -
           (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._34)) *
           (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._34 +
           (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._44;
    }
    uVar2 = pDVar1->bitField1 & 0xfffffffd;
    pDVar1->bitField1 = uVar2;
    *(float *)&pDVar1->field_0x940 = 1.0 / *(float *)&pDVar1->field_0x93c;
    if (((((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._14 == 0.0) &&
         ((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._24 == 0.0)) &&
        ((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._34 == 0.0)) &&
       ((pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._44 == 1.0)) {
      pDVar1->bitField1 = uVar2 | 2;
    }
    D3D_UpdateProjectionViewportTransform();
    FUN_00173900();
  }
  return;
}




void D3D8::D3DDevice_GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX *pMatrix)

{
  int iVar1;
  float *pfVar2;
  
  pfVar2 = (float *)(&D3D_g_pDevice->field2480_0xc50 + State * 0x10);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    (pMatrix->DUMMYUNIONNAME).DUMMYSTRUCTNAME._11 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pMatrix = (D3DMATRIX *)((int)&pMatrix->DUMMYUNIONNAME + 4);
  }
  return;
}




ULONG D3D8::D3DDevice_Release(void)

{
  ULONG UVar1;
  int iVar2;
  D3D__Device *pDVar3;
  
  pDVar3 = D3D_g_pDevice;
  if (D3D_g_pDevice->flag1 == 1) {
    FUN_0017ac50(D3D_g_pDevice);
    D3D_g_pDevice = (D3D__Device *)0x0;
    for (iVar2 = 0x924; iVar2 != 0; iVar2 = iVar2 + -1) {
      pDVar3->State = (undefined4 *)0x0;
      pDVar3 = (D3D__Device *)&pDVar3->field1_0x4;
    }
    return 0;
  }
  UVar1 = D3D_g_pDevice->flag1 - 1;
  D3D_g_pDevice->flag1 = UVar1;
  return UVar1;
}




void D3D8::D3D_KickOffAndWaitForIdle(void)

{
  D3D_BlockOnTime(*(DWORD *)&D3D_g_pDevice->field_0x2c,2);
  return;
}




void D3D8::D3DDevice_BlockOnFence(DWORD Fence)

{
  D3D_BlockOnTime(Fence,4);
  return;
}




void D3D8::D3DDevice_SetVerticalBlankCallback(D3DVBLANKCALLBACK pCallback)

{
  D3D_g_pDevice->field3590_0x1da8 = pCallback;
  return;
}




void D3D8::D3DDevice_BlockUntilVerticalBlank(void)

{
  D3D__Device *pDVar1;
  
  pDVar1 = D3D_g_pDevice;
  D3D_g_pDevice->field3592_0x1db0 = 0;
  KeWaitForSingleObject(&pDVar1->field3591_0x1dac,UserRequest,'\x01','\0',(PLARGE_INTEGER)0x0);
  return;
}




void D3D8::D3DDevice_GetProjectionViewportMatrix(D3DMATRIX *pProjectionViewport)

{
  int iVar1;
  float *pfVar2;
  
  pfVar2 = (float *)&D3D_g_pDevice->field2296_0x970;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    (pProjectionViewport->DUMMYUNIONNAME).DUMMYSTRUCTNAME._11 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pProjectionViewport = (D3DMATRIX *)((int)&pProjectionViewport->DUMMYUNIONNAME + 4);
  }
  return;
}




void D3D8::D3DDevice_SetFlickerFilter(DWORD Filter)

{
  if ((DAT_001845a0 == 0) || (DAT_00184598 != Filter)) {
    AvSendTVEncoderOption((PVOID)D3D_g_pDevice->field3490_0x1c18,0xb,Filter,(PULONG)0x0);
    DAT_001845a0 = 1;
    DAT_00184598 = Filter;
  }
  return;
}




void D3D8::D3DDevice_SetSoftDisplayFilter(BOOL Enable)

{
  if ((DAT_0018459c == 0) || (DAT_00184594 != (Enable != 0))) {
    AvSendTVEncoderOption((PVOID)D3D_g_pDevice->field3490_0x1c18,0xe,Enable,(PULONG)0x0);
    DAT_00184594 = (uint)(Enable != 0);
    DAT_0018459c = 1;
  }
  return;
}




DWORD D3D8::D3DDevice_InsertFence(void)

{
  DWORD DVar1;
  
  DVar1 = D3D_SetFence(0);
  return DVar1;
}




void D3D8::D3DDevice_SetRenderTarget(D3DSurface *pRenderTarget,D3DSurface *pNewZStencil)

{
  byte bVar1;
  DWORD DVar2;
  D3D__Device *pDVar3;
  undefined4 uVar4;
  undefined4 *extraout_EAX;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  DWORD DStack_c;
  int iStack_8;
  
  pDVar3 = D3D_g_pDevice;
  if (pRenderTarget == (D3DSurface *)0x0) {
    pRenderTarget = (D3DSurface *)D3D_g_pDevice->field3353_0x19f4;
  }
  FUN_00175970(pRenderTarget);
  iVar5 = pDVar3->field3353_0x19f4;
  if (iVar5 != 0) {
    if (*(int *)(iVar5 + 0x14) != 0) {
      iVar5 = *(int *)(iVar5 + 0x14);
    }
    *(undefined4 *)(iVar5 + 8) = *(undefined4 *)&pDVar3->field_0x2c;
    FUN_00175b90(pDVar3->field3353_0x19f4);
  }
  iVar5 = pDVar3->field3354_0x19f8;
  pDVar3->field3353_0x19f4 = pRenderTarget;
  if (iVar5 != 0) {
    if (*(int *)(iVar5 + 0x14) != 0) {
      iVar5 = *(int *)(iVar5 + 0x14);
    }
    *(undefined4 *)(iVar5 + 8) = *(undefined4 *)&pDVar3->field_0x2c;
    FUN_00175b90(pDVar3->field3354_0x19f8);
  }
  pDVar3->field3354_0x19f8 = pNewZStencil;
  if (pNewZStencil != (D3DSurface *)0x0) {
    FUN_00175970(pNewZStencil);
    FUN_0017b080(pNewZStencil,&pDVar3->field_0x944);
    uVar4 = FUN_00174080(pNewZStencil);
    pDVar3->field2286_0x948 = uVar4;
  }
  puVar6 = pDVar3->State;
  if (pDVar3->field1_0x4 <= puVar6) {
    D3DDevice_MakeSpace();
    puVar6 = extraout_EAX;
  }
  DVar2 = (pRenderTarget->super).resource.Data;
  if (pNewZStencil == (D3DSurface *)0x0) {
    DStack_c = 0;
  }
  else {
    DStack_c = (pNewZStencil->super).resource.Data;
  }
  iStack_8 = 2;
  do {
    *puVar6 = 0x40100;
    puVar6[1] = 0;
    if ((pRenderTarget->super).Size == 0) {
      iVar5 = 1 << ((byte)((pRenderTarget->super).Format >> 0x14) & 0xf);
      bVar1 = *(byte *)((int)&(pRenderTarget->super).Format + 1);
      if (bVar1 == 0xc) {
        uVar8 = iVar5 * 2;
      }
      else if ((bVar1 < 0xe) || (0xf < bVar1)) {
        uVar8 = ((byte)(&DAT_0017f958)[*(byte *)((int)&(pRenderTarget->super).Format + 1)] & 0x3c) *
                iVar5 >> 3;
      }
      else {
        uVar8 = iVar5 * 4;
      }
    }
    else {
      uVar8 = (*(byte *)((int)&(pRenderTarget->super).Size + 3) + 1) * 0x40;
    }
    iVar5 = pDVar3->field2286_0x948;
    puVar6[2] = 0x4020c;
    puVar6[3] = iVar5 << 0x10 | uVar8 & 0xffff;
    puVar6[4] = 0x40100;
    puVar6[5] = 0;
    puVar6[6] = &LAB_0004010e_2;
    puVar6[7] = 0;
    puVar6[8] = 0x40100;
    puVar6[9] = 0;
    puVar6[10] = 0x40210;
    puVar6[0xb] = DVar2;
    puVar6[0xc] = 0x40100;
    puVar6[0xd] = 0;
    puVar6[0xe] = &LAB_0004010e_2;
    puVar6[0xf] = 0;
    puVar6[0x10] = 0x40100;
    puVar6[0x11] = 0;
    puVar6[0x12] = 0x40214;
    puVar6[0x13] = DStack_c;
    puVar6[0x14] = 0x40100;
    puVar6[0x15] = 0;
    puVar6[0x16] = &LAB_0004010e_2;
    puVar6[0x17] = 0;
    puVar6 = puVar6 + 0x18;
    iStack_8 = iStack_8 + -1;
  } while (iStack_8 != 0);
  puVar6 = (undefined4 *)FUN_00171e10();
  if ((DAT_00181dac == 0) || (pDVar3->field3354_0x19f8 == 0)) {
    uVar4 = 0;
  }
  else {
    uVar4 = 1;
  }
  *puVar6 = 0x4030c;
  puVar6[1] = uVar4;
  if ((D3DRS_StencilEnable == 0) || (pDVar3->field3354_0x19f8 == 0)) {
    uVar4 = 0;
  }
  else {
    uVar4 = 1;
  }
  puVar6[2] = 0x4032c;
  puVar6[3] = uVar4;
  puVar7 = puVar6 + 4;
  if (((pDVar3->bitField1 & 0x100) != 0) &&
     (pRenderTarget == (D3DSurface *)pDVar3->field3357_0x1a04)) {
    pDVar3->bitField1 = pDVar3->bitField1 & 0xfffffeff;
    *puVar7 = &LAB_0004012d_3;
    puVar6[5] = 0;
    puVar7 = puVar6 + 6;
  }
  pDVar3->State = puVar7;
  uVar4 = FUN_0017af60(pRenderTarget,pNewZStencil);
  pDVar3->field3355_0x19fc = uVar4;
  D3D_CommonSetMultiSampleModeAndScale();
  D3DDevice_SetRenderState_Dxt1NoiseEnable(D3DRS_Dxt1NoiseEnable);
  return;
}




D3DSurface * D3D8::D3DDevice_GetBackBuffer2(INT BackBuffer)

{
  D3DSurface *pDVar1;
  
  if (BackBuffer == -1) {
    pDVar1 = (D3DSurface *)D3D_g_pDevice->field3358_0x1a08;
    D3DResource_AddRef((D3DResource *)pDVar1);
    return pDVar1;
  }
  pDVar1 = (D3DSurface *)(&D3D_g_pDevice->field3357_0x1a04)[-(uint)(BackBuffer != 0) & 2];
  D3DResource_AddRef((D3DResource *)pDVar1);
  return pDVar1;
}



void D3D8::D3DDevice_CopyRects
               (D3DSurface *pSourceSurface,RECT *pSourceRectsArray,UINT cRects,
               D3DSurface *pDestinationSurface,POINT *pDestPointsArray)

{
  byte bVar1;
  DWORD DVar2;
  DWORD DVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  D3D__Device *pDVar8;
  D3D__Device *pDVar9;
  char cVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *extraout_EAX;
  LONG *pLVar13;
  undefined4 *extraout_EAX_00;
  undefined4 *puVar14;
  uint uVar15;
  RECT *pRVar16;
  uint uVar17;
  int iVar18;
  POINT *pPVar19;
  RECT *pRVar20;
  uint local_34;
  uint local_28;
  uint local_24;
  POINT local_18;
  RECT local_10;
  
  uVar17 = (uint)*(byte *)((int)&(pSourceSurface->super).Format + 1);
  bVar1 = (&DAT_0017f958)[uVar17];
  uVar15 = (bVar1 & 0x38) >> 3;
  uVar11 = FUN_00174080(pSourceSurface);
  uVar12 = FUN_00174080(pDestinationSurface);
  if ((bVar1 & 1) == 0) {
    cVar10 = FUN_0017aed0(uVar17);
    bVar7 = false;
    if (cVar10 != '\0') goto LAB_0017448e;
  }
  else {
LAB_0017448e:
    bVar7 = true;
  }
  pDVar8 = D3D_g_pDevice;
  iVar18 = D3D_g_pDevice->field3299_0x191c;
  if (cRects == 0) {
    cRects = 1;
  }
  if (bVar7) {
    local_34 = FUN_001740f0(pSourceSurface);
    if (local_34 < 0x1fc1) {
      uVar11 = local_34 + 0x3f & 0xffffffc0;
      local_28 = 1;
    }
    else {
      uVar11 = 0x1000;
      local_28 = local_34 >> 0xc;
      local_34 = 0x1000;
    }
    uVar12 = uVar11;
    if (iVar18 != 0) {
      local_34 = local_34 / uVar15;
      goto LAB_00174510;
    }
    uVar15 = 1;
  }
  else {
LAB_00174510:
    if (iVar18 != 0) goto LAB_00174531;
  }
  if (uVar15 == 1) {
    iVar18 = 1;
  }
  else if (uVar15 == 2) {
    iVar18 = 4;
  }
  else {
    iVar18 = 10;
  }
LAB_00174531:
  puVar14 = pDVar8->State;
  if (pDVar8->field1_0x4 <= puVar14) {
    D3DDevice_MakeSpace();
    puVar14 = extraout_EAX;
  }
  DVar2 = (pDestinationSurface->super).resource.Data;
  DVar3 = (pSourceSurface->super).resource.Data;
  *puVar14 = &LAB_00086308;
  puVar14[1] = DVar3;
  puVar14[2] = DVar2;
  puVar14[3] = 0x86300;
  puVar14[4] = iVar18;
  puVar14[5] = uVar12 << 0x10 | uVar11 & 0xffff;
  pDVar8->State = puVar14 + 6;
  do {
    pDVar9 = D3D_g_pDevice;
    local_24 = cRects;
    if (1 < cRects) {
      local_24 = 1;
    }
    cRects = cRects - local_24;
    if (pSourceRectsArray == (RECT *)0x0) {
      pRVar20 = &local_10;
      if (local_24 != 0) {
        uVar12 = (pSourceSurface->super).Size;
        pLVar13 = &local_10.y2;
        uVar11 = local_24;
        do {
          pLVar13[-2] = 0;
          if (uVar12 == 0) {
            iVar18 = 1 << (*(byte *)((int)&(pSourceSurface->super).Format + 3) & 0xf);
          }
          else {
            iVar18 = (uVar12 >> 0xc & 0xfff) + 1;
          }
          *pLVar13 = iVar18;
          ((RECT *)(pLVar13 + -3))->x1 = 0;
          if (uVar12 == 0) {
            iVar18 = 1 << ((byte)((pSourceSurface->super).Format >> 0x14) & 0xf);
          }
          else {
            iVar18 = (uVar12 & 0xfff) + 1;
          }
          pLVar13[-1] = iVar18;
          pLVar13 = pLVar13 + 4;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
    }
    else {
      pRVar20 = pSourceRectsArray;
      pSourceRectsArray = pSourceRectsArray + 1;
    }
    if (pDestPointsArray == (POINT *)0x0) {
      uVar12 = 0;
      pPVar19 = &local_18;
      pRVar16 = pRVar20;
      if (local_24 != 0) {
        do {
          (&local_18)[uVar12].x1 = pRVar16->x1;
          (&local_18)[uVar12].y1 = pRVar16->y1;
          uVar12 = uVar12 + 1;
          pRVar16 = pRVar16 + 1;
        } while (uVar12 < local_24);
      }
    }
    else {
      pPVar19 = pDestPointsArray;
      pDestPointsArray = pDestPointsArray + 1;
    }
    if ((bVar7) && (local_24 != 0)) {
      pLVar13 = &pRVar20->x2;
      uVar12 = local_24;
      do {
        ((RECT *)(pLVar13 + -2))->x1 = 0;
        pLVar13[-1] = 0;
        *pLVar13 = local_34;
        pLVar13[1] = local_28;
        pLVar13 = pLVar13 + 4;
        uVar12 = uVar12 - 1;
      } while (uVar12 != 0);
    }
    if (local_24 != 0) {
      pLVar13 = &pRVar20->y1;
      do {
        puVar14 = pDVar9->State;
        if (pDVar9->field1_0x4 <= puVar14) {
          D3DDevice_MakeSpace();
          puVar14 = extraout_EAX_00;
        }
        iVar18 = *pLVar13;
        uVar12 = ((RECT *)(pLVar13 + -1))->x1;
        iVar4 = pPVar19->y1;
        uVar11 = pPVar19->x1;
        iVar5 = pLVar13[2];
        iVar6 = pLVar13[1];
        *puVar14 = FUN_000c4300;
        puVar14[1] = iVar18 << 0x10 | uVar12 & 0xffff;
        puVar14[2] = iVar4 << 0x10 | uVar11 & 0xffff;
        puVar14[3] = (iVar5 - iVar18) * 0x10000 ^ iVar6 - uVar12 & 0xffff;
        pDVar9->State = puVar14 + 4;
        pPVar19 = pPVar19 + 1;
        pLVar13 = pLVar13 + 4;
        local_24 = local_24 - 1;
      } while (local_24 != 0);
    }
  } while (cRects != 0);
  if ((D3DSurface *)pSourceSurface->Parent != (D3DSurface *)0x0) {
    pSourceSurface = (D3DSurface *)pSourceSurface->Parent;
  }
  (pSourceSurface->super).resource.Lock = *(DWORD *)&pDVar8->field_0x2c;
  if (pDestinationSurface->Parent == (D3DBaseTexture *)0x0) {
    (pDestinationSurface->super).resource.Lock = *(DWORD *)&pDVar8->field_0x2c;
    return;
  }
  (pDestinationSurface->Parent->super).resource.Lock = *(DWORD *)&pDVar8->field_0x2c;
  return;
}




D3DSurface * D3D8::D3DDevice_GetRenderTarget2(void)

{
  D3DSurface *pThis;
  
  pThis = (D3DSurface *)D3D_g_pDevice->field3353_0x19f4;
  if (pThis != (D3DSurface *)0x0) {
    D3DResource_AddRef((D3DResource *)pThis);
  }
  return pThis;
}




D3DSurface * D3D8::D3DDevice_GetDepthStencilSurface2(void)

{
  D3DSurface *pThis;
  
  pThis = (D3DSurface *)D3D_g_pDevice->field3354_0x19f8;
  if (pThis == (D3DSurface *)0x0) {
    return (D3DSurface *)0x0;
  }
  D3DResource_AddRef((D3DResource *)pThis);
  return pThis;
}




void D3D8::D3DDevice_SetViewport(D3DVIEWPORT8 *pViewport)

{
  uint uVar1;
  D3D__Device *pDVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *uVar6;
  int iVar3;
  uint uVar7;
  uint uVar8;
  float fVar1;
  
  pDVar2 = D3D_g_pDevice;
  if (pViewport != (D3DVIEWPORT8 *)0x0) {
    iVar3 = D3D_g_pDevice->field3353_0x19f4;
    if (iVar3 == D3D_g_pDevice->field3357_0x1a04) {
      iVar3 = D3D_g_pDevice->field3358_0x1a08;
    }
    uVar7 = pViewport->X;
    uVar3 = -(uint)(uVar7 != 0) & uVar7;
    uVar8 = pViewport->Y;
    uVar4 = -(uint)(uVar8 != 0) & uVar8;
    uVar1 = *(uint *)(iVar3 + 0x10);
    if (uVar1 == 0) {
      uVar5 = 1 << ((byte)(*(uint *)(iVar3 + 0xc) >> 0x14) & 0xf);
    }
    else {
      uVar5 = (uVar1 & 0xfff) + 1;
    }
    uVar7 = uVar7 + pViewport->Width;
    if (uVar5 <= uVar7) {
      if (uVar1 == 0) {
        uVar7 = 1 << ((byte)(*(uint *)(iVar3 + 0xc) >> 0x14) & 0xf);
      }
      else {
        uVar7 = (uVar1 & 0xfff) + 1;
      }
    }
    if (uVar1 == 0) {
      uVar5 = 1 << (*(byte *)(iVar3 + 0xf) & 0xf);
    }
    else {
      uVar5 = (uVar1 >> 0xc & 0xfff) + 1;
    }
    uVar8 = uVar8 + pViewport->Height;
    if (uVar5 <= uVar8) {
      if (uVar1 == 0) {
        uVar8 = 1 << (*(byte *)(iVar3 + 0xf) & 0xf);
      }
      else {
        uVar8 = (uVar1 >> 0xc & 0xfff) + 1;
      }
    }
    fVar1 = (float)(int)uVar7;
    if ((int)uVar7 < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    uVar1 = D3D_g_pDevice->field2288_0x950;
    uVar5 = FUN_001782c0(fVar1 * (float)D3D_g_pDevice->field2290_0x958 + 0.5);
    if (uVar1 < uVar5) {
      fVar1 = (float)(int)uVar1;
      if ((int)uVar1 < 0) {
        fVar1 = fVar1 + 4.2949673e+09;
      }
      uVar7 = FUN_001782c0(fVar1 / (float)pDVar2->field2290_0x958);
    }
    fVar1 = (float)(int)uVar8;
    if ((int)uVar8 < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    uVar1 = pDVar2->field2289_0x954;
    uVar5 = FUN_001782c0(fVar1 * (float)pDVar2->field2291_0x95c + 0.5);
    if (uVar1 < uVar5) {
      fVar1 = (float)(int)uVar1;
      if ((int)uVar1 < 0) {
        fVar1 = fVar1 + 4.2949673e+09;
      }
      uVar8 = FUN_001782c0(fVar1 / (float)pDVar2->field2291_0x95c);
    }
    pDVar2->field2640_0xed0 = uVar3;
    pDVar2->field2643_0xedc = uVar8 - uVar4;
    pDVar2->field2641_0xed4 = uVar4;
    pDVar2->field2642_0xed8 = uVar7 - uVar3;
    pDVar2->field2644_0xee0 = pViewport->MinZ;
    pDVar2->field2645_0xee4 = pViewport->MaxZ;
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x100;
  }
  D3DDevice_SetScissors(0,0,(D3DRECT *)0x0);
  D3D_UpdateProjectionViewportTransform();
  if (pDVar2->field1_0x4 <= pDVar2->State) {
    D3DDevice_MakeSpace();
  }
  uVar6 = (undefined4 *)FUN_00171c20();
  pDVar2->State = uVar6;
  return;
}




void D3D8::D3DDevice_SetTexture(DWORD Stage,D3DBaseTexture *pTexture)

{
  byte bVar1;
  D3DResource *pResource;
  DWORD DVar2;
  DWORD DVar3;
  int iVar4;
  D3D__Device *pDVar5;
  int *extraout_EAX;
  int *piVar6;
  int *extraout_EAX_00;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  
  pDVar5 = D3D_g_pDevice;
  pResource = (D3DResource *)(&D3D_g_pDevice->textureSlots)[Stage];
  if (pResource != (D3DResource *)0x0) {
    uVar8 = pResource->Common - 0x80000;
    pResource->Lock = *(DWORD *)&D3D_g_pDevice->field_0x2c;
    pResource->Common = uVar8;
    if ((uVar8 & 0x78ffff) == 0) {
      D3D_DestroyResource(pResource);
    }
  }
  (&pDVar5->textureSlots)[Stage] = (uint *)pTexture;
  if (pTexture == (D3DBaseTexture *)0x0) {
    piVar6 = pDVar5->State;
    if (pDVar5->field1_0x4 <= piVar6) {
      D3DDevice_MakeSpace();
      piVar6 = extraout_EAX;
    }
    *piVar6 = Stage * 0x40 + 0x41b0c;
    piVar6[1] = 0;
    pDVar5->State = piVar6 + 2;
    *(undefined4 *)(&pDVar5->field_0xc + Stage * 4) = 0x80000000;
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x4800;
    return;
  }
  (pTexture->super).resource.Common = (pTexture->super).resource.Common + 0x80000;
  piVar6 = pDVar5->State;
  if (pDVar5->field1_0x4 <= piVar6) {
    D3DDevice_MakeSpace();
    piVar6 = extraout_EAX_00;
  }
  DVar2 = (pTexture->super).Format;
  DVar3 = (pTexture->super).resource.Data;
  *piVar6 = (Stage + 0x206c) * 0x40;
  piVar6[1] = DVar3;
  piVar6[2] = DVar2;
  uVar8 = (pTexture->super).Size;
  piVar9 = piVar6 + 3;
  if (uVar8 != 0) {
    bVar1 = *(byte *)((int)&(pTexture->super).Size + 3);
    *piVar9 = Stage * 0x40 + 0x41b10;
    piVar6[4] = (bVar1 + 1) * 0x400000;
    piVar6[5] = Stage * 0x40 + 0x41b1c;
    piVar6[6] = ((uVar8 & 0xfff) + 1) * 0x10000 | (uVar8 >> 0xc & 0xfff) + 1;
    piVar9 = piVar6 + 7;
  }
  uVar8 = (pTexture->super).Format;
  uVar7 = uVar8 & 0x20f4;
  if (*(uint *)(&pDVar5->field_0xc + Stage * 4) != uVar7) {
    if ((char)(uVar7 >> 8) != '\0') {
      uVar7 = uVar8 & 0xf4;
      if ((0x29ff < (uVar8 & 0xff00)) && ((uVar8 & 0xff00) < 0x3101)) {
        uVar7 = uVar7 | 0x40000000;
      }
    }
    *(uint *)(&pDVar5->field_0xc + Stage * 4) = uVar7;
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x4000;
    if (pResource == (D3DResource *)0x0) {
      iVar4 = *(int *)(&pDVar5->field_0x770 + Stage * 4);
      *piVar9 = Stage * 0x40 + 0x41b0c;
      piVar9[1] = iVar4;
      piVar9 = piVar9 + 2;
      Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x800;
    }
  }
  pDVar5->State = piVar9;
  return;
}




BOOL D3D8::D3DDevice_IsBusy(void)

{
  int iVar1;
  
  iVar1 = D3D_g_pDevice->field2268_0x930;
  if (*(int *)(iVar1 + 0x3240) != *(int *)(iVar1 + 0x3244)) {
    return 1;
  }
  return (uint)(*(int *)(&DAT_00400700 + iVar1) != 0);
}



void D3D8::D3DDevice_SetModelView
               (D3DMATRIX *pModelView,D3DMATRIX *pInverseModelView,D3DMATRIX *pComposite)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  D3DMATRIX *pDVar5;
  float *pfVar6;
  
  pDVar1 = D3D_g_pDevice;
  if (pComposite == (D3DMATRIX *)0x0) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags & 0x7ffffdff | 0x200;
    return;
  }
  Graphics::GraphicsFlags = Graphics::GraphicsFlags & 0xfffffdff | 0x80000000;
  puVar4 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar4) {
    D3DDevice_MakeSpace();
    puVar4 = extraout_EAX;
  }
  iVar3 = 0x10;
  if ((pDVar1->bitField1 & 0x10) == 0) {
    pDVar5 = pModelView;
    pfVar6 = (float *)&pDVar1->field2312_0x9b0;
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar6 = (pDVar5->DUMMYUNIONNAME).DUMMYSTRUCTNAME._11;
      pDVar5 = (D3DMATRIX *)((int)&pDVar5->DUMMYUNIONNAME + 4);
      pfVar6 = pfVar6 + 1;
    }
  }
  FUN_00176f10(puVar4,&DAT_00400480,pModelView);
  FUN_00176f10(puVar4 + 0x11,&DAT_00400680,pComposite);
  puVar2 = puVar4 + 0x22;
  if (pInverseModelView != (D3DMATRIX *)0x0) {
    *puVar2 = 0x300580;
    pfVar6 = (float *)(puVar4 + 0x23);
    for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar6 = (pInverseModelView->DUMMYUNIONNAME).DUMMYSTRUCTNAME._11;
      pInverseModelView = (D3DMATRIX *)((int)&pInverseModelView->DUMMYUNIONNAME + 4);
      pfVar6 = pfVar6 + 1;
    }
    puVar2 = puVar4 + 0x2f;
  }
  pDVar1->State = puVar2;
  return;
}




void D3D8::D3D_SetTileNoWait(int param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  D3D__Device *pDVar6;
  int iVar7;
  int iVar8;
  
  pDVar6 = D3D_g_pDevice;
  if ((param_2 != (int *)0x0) && (uVar2 = param_2[1], uVar2 != 0)) {
    iVar3 = param_2[2];
    iVar4 = *param_2;
    iVar5 = param_2[3];
    iVar8 = param_2[4];
    iVar7 = param_2[5];
    if (-1 < iVar4) {
      iVar7 = 0;
      iVar8 = 0;
    }
    piVar1 = &D3D_g_pDevice->field3400_0x1ab0 + param_1 * 6;
    *piVar1 = iVar4;
    piVar1[1] = uVar2;
    piVar1[2] = iVar3;
    piVar1[3] = iVar5;
    piVar1[4] = iVar8;
    piVar1[5] = iVar7;
    FUN_0017ccc6(param_1,uVar2 & 0xfffffff,iVar3,iVar5,iVar4,iVar8,iVar7);
    return;
  }
  FUN_0017ceb4(param_1,(&D3D_g_pDevice->field3405_0x1ac4)[param_1 * 6]);
  (&pDVar6->field3400_0x1ab0)[param_1 * 6] = 0;
  (&pDVar6->field3401_0x1ab4)[param_1 * 6] = 0;
  (&pDVar6->field3402_0x1ab8)[param_1 * 6] = 0;
  (&pDVar6->field3403_0x1abc)[param_1 * 6] = 0;
  (&pDVar6->field3404_0x1ac0)[param_1 * 6] = 0;
  (&pDVar6->field3405_0x1ac4)[param_1 * 6] = 0;
  return;
}




void D3D8::D3DDevice_SetScissors(DWORD Count,BOOL Exclusive,D3DRECT *pRects)

{
  float fVar1;
  float fVar2;
  float fVar3;
  D3D__Device *pDVar4;
  undefined4 *extraout_EAX;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  int *piVar11;
  LONG *pLVar12;
  uint local_c;
  
  pDVar4 = D3D_g_pDevice;
  fVar1 = (float)D3D_g_pDevice->field2290_0x958;
  fVar2 = (float)D3D_g_pDevice->field2291_0x95c;
  puVar10 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar10) {
    D3DDevice_MakeSpace();
    puVar10 = extraout_EAX;
  }
  if (Count == 0) {
    fVar3 = (float)(int)pDVar4->field2640_0xed0;
    if ((int)pDVar4->field2640_0xed0 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    uVar5 = FUN_001782c0(fVar3 * fVar1 + 0.5);
    fVar3 = (float)(int)pDVar4->field2641_0xed4;
    if ((int)pDVar4->field2641_0xed4 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    local_c = FUN_001782c0(fVar3 * fVar2 + 0.5);
    fVar3 = (float)(int)pDVar4->field2642_0xed8;
    if ((int)pDVar4->field2642_0xed8 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    iVar6 = FUN_001782c0(fVar3 * fVar1 + 0.5);
    fVar1 = (float)(int)pDVar4->field2643_0xedc;
    if ((int)pDVar4->field2643_0xedc < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    iVar7 = FUN_001782c0(fVar1 * fVar2 + 0.5);
  }
  else {
    if ((Count != 1) || (Exclusive != 0)) {
      iVar6 = pDVar4->field2288_0x950;
      iVar7 = pDVar4->field2289_0x954;
      *puVar10 = &DAT_00080200;
      puVar10[1] = iVar6 << 0x10;
      puVar10[2] = iVar7 << 0x10;
      puVar10[3] = 0x402b4;
      puVar10[4] = Exclusive;
      piVar9 = puVar10 + 5;
      if (Count != 0) {
        iVar6 = 0x402e0;
        piVar11 = (int *)((int)piVar9 + (-0x10 - (int)puVar10) + (int)pRects);
        local_c = Count;
        do {
          iVar7 = piVar11[-1];
          iVar8 = FUN_001782c0((float)piVar11[1] * fVar1 + 0.5);
          uVar5 = FUN_001782c0((float)iVar7 * fVar1 + 0.5);
          *piVar9 = iVar6 + -0x20;
          piVar9[1] = uVar5 | (iVar8 + -1) * 0x10000;
          iVar7 = *piVar11;
          iVar8 = FUN_001782c0((float)piVar11[2] * fVar2 + 0.5);
          uVar5 = FUN_001782c0((float)iVar7 * fVar2 + 0.5);
          piVar9[2] = iVar6;
          piVar9[3] = uVar5 | (iVar8 + -1) * 0x10000;
          piVar9 = piVar9 + 4;
          piVar11 = piVar11 + 4;
          iVar6 = iVar6 + 4;
          local_c = local_c - 1;
        } while (local_c != 0);
      }
      goto LAB_00175022;
    }
    uVar5 = FUN_001782c0((float)pRects->x1 * fVar1 + 0.5);
    local_c = FUN_001782c0((float)pRects->y1 * fVar2 + 0.5);
    iVar6 = FUN_001782c0((float)pRects->x2 * fVar1 + 0.5);
    iVar6 = iVar6 - uVar5;
    iVar7 = FUN_001782c0((float)pRects->y2 * fVar2 + 0.5);
    iVar7 = iVar7 - local_c;
  }
  *puVar10 = &DAT_00080200;
  puVar10[1] = iVar6 << 0x10 | uVar5;
  puVar10[2] = iVar7 << 0x10 | local_c;
  puVar10[3] = 0x402b4;
  puVar10[4] = 0;
  iVar6 = pDVar4->field2288_0x950;
  puVar10[5] = 0x402c0;
  puVar10[6] = iVar6 << 0x10;
  iVar6 = pDVar4->field2289_0x954;
  puVar10[7] = 0x402e0;
  puVar10[8] = iVar6 << 0x10;
  piVar9 = puVar10 + 9;
LAB_00175022:
  pDVar4->State = piVar9;
  pLVar12 = &pDVar4->field3448_0x1b70;
  for (iVar6 = (Count & 0xfffffff) << 2; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pLVar12 = pRects->x1;
    pRects = (D3DRECT *)&pRects->y1;
    pLVar12 = pLVar12 + 1;
  }
  for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
    *(char *)pLVar12 = (char)pRects->x1;
    pRects = (D3DRECT *)((int)&pRects->x1 + 1);
    pLVar12 = (LONG *)((int)pLVar12 + 1);
  }
  pDVar4->field3480_0x1bf0 = Count;
  pDVar4->field3481_0x1bf4 = Exclusive;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void D3D8::D3DDevice_SetScreenSpaceOffset(FLOAT x,FLOAT y)

{
  D3D__Device *pDVar1;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  D3D_g_pDevice->field2646_0xee8 = x + _DAT_0017fd10;
  pDVar1->field2647_0xeec = y + _DAT_0017fd10;
  FUN_00173900();
  if (pDVar1->field1_0x4 <= pDVar1->State) {
    D3DDevice_MakeSpace();
  }
  puVar2 = (undefined4 *)FUN_00171c20();
  pDVar1->State = puVar2;
  return;
}




HRESULT D3D8::D3DDevice_CreatePixelShader(D3DPIXELSHADERDEF *pPSDef,DWORD *pHandle)

{
  undefined4 *puVar1;
  int iVar2;
  DWORD *puVar3;
  
  puVar1 = XAPILIB::XMemAlloc(0xfc,0x24800000);
  if (puVar1 == (undefined4 *)0x0) {
    return -0x7ff8fff2;
  }
  puVar1[2] = puVar1 + 3;
  *puVar1 = 1;
  puVar1[1] = 1;
  puVar3 = puVar1 + 3;
  for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = pPSDef->PSAlphaInputs[0];
    pPSDef = (D3DPIXELSHADERDEF *)(pPSDef->PSAlphaInputs + 1);
    puVar3 = puVar3 + 1;
  }
  *pHandle = (DWORD)puVar1;
  return 0;
}




void D3D8::D3DDevice_DeletePixelShader(DWORD Handle)

{
  *(int *)Handle = *(int *)Handle + -1;
  if ((*(int *)Handle == 0) && (*(int *)(Handle + 4) != 0)) {
    XAPILIB::XMemFree(Handle,0x24800000);
  }
  return;
}




void D3D8::D3DDevice_SetPixelShader(DWORD Handle)

{
  DWORD DVar1;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar2;
  uint uVar5;
  int iVar6;
  undefined4 *puVar8;
  undefined4 *puVar9;
  D3D__Device *pDVar2;
  undefined4 uVar1;
  
  pDVar2 = D3D_g_pDevice;
  DVar1 = D3D_g_pDevice->field1872_0x780;
  D3D_g_pDevice->field1872_0x780 = Handle;
  if (Handle == 0) {
    uVar5 = Graphics::GraphicsFlags | 0x4800;
    if (pDVar2->field1873_0x784 != 0) {
      uVar5 = Graphics::GraphicsFlags | 0x6800;
    }
    Graphics::GraphicsFlags = uVar5;
    D3DDevice_SetRenderState_TextureFactor(DAT_00181dc0);
    if (pDVar2->field1_0x4 <= pDVar2->State) {
      D3DDevice_MakeSpace();
    }
    puVar3 = (undefined4 *)FUN_00171bb0();
    *puVar3 = 0x41e78;
    puVar3[1] = &INT_00210000;
    pDVar2->State = puVar3 + 2;
    return;
  }
  uVar5 = *(uint *)(*(int *)(Handle + 8) + 0x24) | *(uint *)(*(int *)(Handle + 8) + 0x20);
  if ((uVar5 == 0) && (pDVar2->field1873_0x784 != 0)) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x2000;
  }
  pDVar2->field1873_0x784 = uVar5;
  pDVar2->field1874_0x788 = *(uint *)(*(int *)(Handle + 8) + 0xec) & 0x100;
  puVar3 = *(undefined4 **)(Handle + 8);
  pDVar2->field1875_0x78c = puVar3[0x36];
  Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0x4000;
  puVar2 = pDVar2->State;
  if (pDVar2->field1_0x4 <= puVar2) {
    D3DDevice_MakeSpace();
    puVar2 = puVar4;
  }
  if ((pDVar2->bitField1 & 0x10) == 0) {
    puVar9 = puVar3;
    puVar8 = &D3D_g_RenderState;
    for (iVar6 = 0x39; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar8 = puVar8 + 1;
    }
    D3DRS_PSTextureModes = puVar3[0x36];
  }
  if (DVar1 == 0) {
    puVar2 = (undefined4 *)FUN_00171bb0();
  }
  *puVar2 = 0x200260;
  puVar8 = puVar3;
  puVar9 = puVar2;
  for (iVar6 = 8; puVar9 = puVar9 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
  }
  puVar2[9] = 0x800a60;
  puVar9 = puVar3 + 10;
  puVar8 = puVar2 + 10;
  for (iVar6 = 0x20; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar8 = puVar8 + 1;
  }
  uVar1 = puVar3[0x2a];
  puVar2[0x2a] = 0x417f8;
  puVar2[0x2b] = uVar1;
  puVar2[0x2c] = &LAB_00081e1f_1;
  puVar2[0x2d] = puVar3[0x2b];
  puVar2[0x2e] = puVar3[0x2c];
  puVar2[0x2f] = 0x241e40;
  puVar9 = puVar3 + 0x2d;
  puVar8 = puVar2 + 0x30;
  for (iVar6 = 9; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar2[0x39] = 0x81e74;
  puVar2[0x3a] = puVar3[0x37];
  puVar2[0x3b] = puVar3[0x38];
  if (pDVar2->field1873_0x784 != 0) {
    puVar2[0x3c] = 0x80288;
    puVar2[0x3d] = puVar3[8];
    puVar2[0x3e] = puVar3[9];
    pDVar2->State = puVar2 + 0x3f;
    return;
  }
  pDVar2->State = puVar2 + 0x3c;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void D3D8::D3DDevice_SetPixelShaderConstant
               (DWORD Register,DirectXShaderConstant *pConstantData,DWORD ConstantCount)

{
  int iVar1;
  D3D__Device *pDVar2;
  uint uVar3;
  undefined4 *extraout_EAX;
  undefined4 *puVar4;
  uint uVar5;
  undefined1 auVar6 [16];
  
  pDVar2 = D3D_g_pDevice;
  iVar1 = *(int *)(D3D_g_pDevice->field1872_0x780 + 8);
  for (; ConstantCount != 0; ConstantCount = ConstantCount - 1) {
    auVar6 = minps((undefined1  [16])*pConstantData,_DAT_0032cf60);
    auVar6 = maxps(auVar6,_DAT_00434240);
    uVar3 = (int)ROUND(auVar6._0_4_ * _DAT_0032cf70) << 0x10 |
            (int)ROUND(auVar6._4_4_ * fRam0032cf74) << 8 | (int)ROUND(auVar6._8_4_ * fRam0032cf78) |
            (int)ROUND(auVar6._12_4_ * _DAT_0032cf7c) << 0x18;
    *(uint *)(&pDVar2->field_0x8e0 + Register * 4) = uVar3;
    puVar4 = pDVar2->State;
    if (pDVar2->field1_0x4 <= puVar4) {
      D3DDevice_MakeSpace();
      puVar4 = extraout_EAX;
    }
    uVar5 = *(uint *)(&DAT_0032cf80 + Register * 4) ^ *(uint *)(iVar1 + 0xe4);
    if ((uVar5 & 0xf) == 0) {
      _DAT_00181b98 = uVar3;
      *puVar4 = FUN_00040a60;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf0) == 0) {
      _DAT_00181b9c = uVar3;
      *puVar4 = 0x40a64;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf00) == 0) {
      _DAT_00181ba0 = uVar3;
      *puVar4 = 0x40a68;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf000) == 0) {
      _DAT_00181ba4 = uVar3;
      *puVar4 = 0x40a6c;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf0000) == 0) {
      _DAT_00181ba8 = uVar3;
      *puVar4 = 0x40a70;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf00000) == 0) {
      _DAT_00181bac = uVar3;
      *puVar4 = 0x40a74;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf000000) == 0) {
      _DAT_00181bb0 = uVar3;
      *puVar4 = 0x40a78;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf0000000) == 0) {
      _DAT_00181bb4 = uVar3;
      *puVar4 = 0x40a7c;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    uVar5 = *(uint *)(&DAT_0032cf80 + Register * 4) ^ *(uint *)(iVar1 + 0xe8);
    if ((uVar5 & 0xf) == 0) {
      _DAT_00181bb8 = uVar3;
      *puVar4 = 0x40a80;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf0) == 0) {
      _DAT_00181bbc = uVar3;
      *puVar4 = 0x40a84;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf00) == 0) {
      _DAT_00181bc0 = uVar3;
      *puVar4 = 0x40a88;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf000) == 0) {
      _DAT_00181bc4 = uVar3;
      *puVar4 = 0x40a8c;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf0000) == 0) {
      _DAT_00181bc8 = uVar3;
      *puVar4 = 0x40a90;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf00000) == 0) {
      _DAT_00181bcc = uVar3;
      *puVar4 = 0x40a94;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf000000) == 0) {
      _DAT_00181bd0 = uVar3;
      *puVar4 = &DAT_00040a98;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf0000000) == 0) {
      _DAT_00181bd4 = uVar3;
      *puVar4 = &DAT_00040a9c;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    uVar5 = *(uint *)(&DAT_0032cf80 + Register * 4) ^ *(uint *)(iVar1 + 0xec);
    if ((uVar5 & 0xf) == 0) {
      _DAT_00181c1c = uVar3;
      *puVar4 = 0x41e20;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if ((uVar5 & 0xf0) == 0) {
      _DAT_00181c20 = uVar3;
      *puVar4 = 0x41e24;
      puVar4[1] = uVar3;
      puVar4 = puVar4 + 2;
    }
    if (Register == 0) {
      *puVar4 = 0xc181c;
      puVar4[1] = pConstantData->c1;
      puVar4[2] = pConstantData->c2;
      puVar4[3] = pConstantData->c3;
      puVar4 = puVar4 + 4;
    }
    pDVar2->State = puVar4;
    pConstantData = pConstantData + 1;
    Register = Register + 1;
  }
  return;
}




void D3D8::D3D_DestroyResource(D3DResource *pResource)

{
  uint uVar1;
  
  uVar1 = pResource->Common & 0x70000;
  if ((uVar1 != 0x50000) || ((int)pResource->Common < 0)) {
    D3D_BlockOnResource(pResource);
  }
  FUN_00175840(pResource);
  if (uVar1 == 0x50000) {
    if (-1 < (int)pResource->Common) goto LAB_00175911;
    uVar1 = pResource->Data | 0x80000000;
  }
  else if (uVar1 == 0x20000) {
    if ((int)pResource->Common < 0) goto LAB_00175911;
    uVar1 = pResource->Data;
  }
  else {
    if ((uVar1 == 0x10000) || (uVar1 == 0x60000)) goto LAB_00175911;
    uVar1 = pResource->Data | 0x80000000;
  }
  XAPILIB::XMemFree(uVar1,0xa1800000);
LAB_00175911:
  XAPILIB::XMemFree(pResource,0x24800000);
  return;
}




ULONG D3D8::D3DResource_AddRef(D3DResource *pThis)

{
  uint uVar1;
  
  if ((((pThis->Common & 0xffff) == 0) && ((pThis->Common & 0x70000) == 0x50000)) &&
     ((D3DResource *)pThis[1].Lock != (D3DResource *)0x0)) {
    D3DResource_AddRef((D3DResource *)pThis[1].Lock);
  }
  uVar1 = pThis->Common + 1;
  pThis->Common = uVar1;
  return uVar1 & 0xffff;
}




ULONG D3D8::D3DResource_Release(D3DResource *pThis)

{
  uint uVar1;
  
  uVar1 = pThis->Common;
  if ((uVar1 & 0xffff) == 1) {
    if (((uVar1 & 0x70000) == 0x50000) && ((D3DResource *)pThis[1].Lock != (D3DResource *)0x0)) {
      D3DResource_Release((D3DResource *)pThis[1].Lock);
    }
    uVar1 = pThis->Common;
    if ((uVar1 & 0x780000) == 0) {
      D3D_DestroyResource(pThis);
      return 0;
    }
  }
  pThis->Common = uVar1 - 1;
  return uVar1 - 1 & 0xffff;
}




char D3D8::D3DResource_GetType(uint *param_1)

{
  uint uVar1;
  
  uVar1 = *param_1 & 0x70000;
  if (0x30000 < uVar1) {
    if (uVar1 == 0x40000) {
      if ((param_1[3] & 4) != 0) {
        return '\x05';
      }
      return (0x20 < (param_1[3] & 0xf0)) + '\x03';
    }
    if (uVar1 != 0x50000) {
      return '\n';
    }
    return (0x20 < (param_1[3] & 0xf0)) + '\x01';
  }
  if (uVar1 == 0x30000) {
    return '\t';
  }
  if (uVar1 != 0) {
    return (uVar1 != 0x10000) + '\a';
  }
  return '\x06';
}




BOOL D3D8::D3DResource_IsBusy(D3DResource *pThis)

{
  D3DResource *pDVar1;
  
  if (((((pThis->Common & 0x70000) != 0x50000) ||
       (pDVar1 = (D3DResource *)pThis[1].Lock, pDVar1 == (D3DResource *)0x0)) ||
      (((pThis->Common & 0x780000) == 0 &&
       ((pThis = pDVar1, pDVar1 == (D3DResource *)0x0 || ((pDVar1->Common & 0x780000) == 0)))))) &&
     (((pThis->Common & 0x780000) == 0 &&
      (((((pThis->Common & 0x70000) != 0x50000 || ((uint *)pThis[1].Lock == (uint *)0x0)) ||
        ((*(uint *)pThis[1].Lock & 0x780000) == 0)) &&
       ((pThis->Lock == 0 ||
        ((uint)(*(int *)&D3D_g_pDevice->field_0x2c - *(int *)D3D_g_pDevice->inner1Ptr) <=
         *(int *)&D3D_g_pDevice->field_0x2c - pThis->Lock)))))))) {
    pThis->Lock = 0;
    return 0;
  }
  return 1;
}




void D3D8::D3DResource_Register(D3DResource *pThis,PVOID pBase)

{
  uint uVar1;
  
  uVar1 = pThis->Data + (int)pBase;
  if ((pThis->Common & 0x70000) != 0x20000) {
    uVar1 = uVar1 & 0xfffffff;
  }
  pThis->Data = uVar1;
  return;
}




void D3D8::D3DSurface_GetDesc(undefined4 param_1,undefined4 param_2)

{
  Get2DSurfaceDesc(param_1,0,param_2);
  return;
}




void D3D8::D3DSurface_LockRect(void *pThis,void *pLockedRect,void *pRect,DWORD Flags)

{
  Lock2DSurface(pThis,D3DCUBEMAP_FACE_POSITIVE_X,0,pLockedRect,pRect,Flags);
  return;
}




DWORD D3D8::D3DDevice_Swap(DWORD Flags)

{
  D3D__Device *pDVar1;
  
  pDVar1 = D3D_g_pDevice;
  if ((*(int *)&D3D_g_pDevice->field_0x8d0 != 0) || (*(int *)&D3D_g_pDevice->field_0x8d4 != 0)) {
    FUN_0017d190();
  }
  if (Flags == 0) {
    Flags = 5;
  }
  if ((pDVar1->bitField1 & 0x4000) == 0) {
    if ((Flags & 4) == 0) goto LAB_00176872;
    D3D_SetFence(0);
    if ((&pDVar1->field3317_0x1964)[pDVar1->field4022_0x2468 - 1 & 1] != 0) {
      D3D_BlockOnTime((&pDVar1->field3317_0x1964)[pDVar1->field4022_0x2468 - 1 & 1],1);
    }
    pDVar1->field4022_0x2468 = pDVar1->field4022_0x2468 + 1;
    FUN_00176670();
  }
  else {
    if ((Flags & 3) != 0) {
      D3D_SetFence(0);
      if ((&pDVar1->field3317_0x1964)[pDVar1->field4022_0x2468 - 1 & 1] != 0) {
        D3D_BlockOnTime((&pDVar1->field3317_0x1964)[pDVar1->field4022_0x2468 - 1 & 1],1);
      }
      pDVar1->field4022_0x2468 = pDVar1->field4022_0x2468 + 1;
    }
    FUN_00176480(Flags);
    if ((Flags & 4) == 0) goto LAB_00176872;
  }
  FUN_00176780();
LAB_00176872:
  if (((Flags & 4) != 0) &&
     ((Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0xff1000,
      *(int *)&pDVar1->field_0x8d0 != 0 || (*(int *)&pDVar1->field_0x8d4 != 0)))) {
    FUN_0017d5c0();
  }
  return pDVar1->field4022_0x2468;
}




void D3D::D3DPushBuffer_SetTexture(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = DAT_001845a8;
  piVar3 = (int *)(*(int *)(param_1 + 4) + param_2);
  if (DAT_001845a8 != 0) {
    piVar3 = (int *)(*(int *)(DAT_001845a8 + 4) + *(int *)(DAT_001845a8 + 0x10));
    iVar4 = ((uint)(*(int *)(param_4 + 0x10) != 0) * 4 + 3) * 4;
    uVar5 = *(int *)(DAT_001845a8 + 0x10) + iVar4 + 8;
    *(uint *)(DAT_001845a8 + 0x10) = uVar5;
    if (*(uint *)(iVar2 + 0x14) < uVar5) {
      return;
    }
    *piVar3 = iVar4;
    piVar3[1] = param_2;
    piVar3 = piVar3 + 2;
  }
  if (piVar3 != (int *)0x0) {
    iVar2 = *(int *)(param_4 + 0xc);
    iVar4 = *(int *)(param_4 + 4);
    *piVar3 = (param_3 + 0x206c) * 0x40;
    piVar3[1] = iVar4;
    piVar3[2] = iVar2;
    uVar5 = *(uint *)(param_4 + 0x10);
    if (uVar5 != 0) {
      bVar1 = *(byte *)(param_4 + 0x13);
      piVar3[3] = param_3 * 0x40 + 0x41b10;
      piVar3[4] = (bVar1 + 1) * 0x400000;
      piVar3[5] = param_3 * 0x40 + 0x41b1c;
      piVar3[6] = ((uVar5 & 0xfff) + 1) * 0x10000 | (uVar5 >> 0xc & 0xfff) + 1;
    }
  }
  return;
}




DWORD * D3D8::D3DDevice_BeginPush_4(DWORD Count)

{
  DWORD *pDVar1;
  
  CDevice_SetStateVB(0);
  pDVar1 = (DWORD *)D3DDevice_BeginStateBig(Count + 1);
  return pDVar1;
}




void D3D8::D3DDevice_EndPush(DWORD *pPush)

{
  D3D_g_pDevice->State = pPush;
  return;
}




void __fastcall D3D8::CDevice_KickOff(uint *param_1)

{
  int iVar1;
  BOOL BVar2;
  uint uVar3;
  
  if ((param_1[2] & 4) == 0) {
    uVar3 = *param_1;
  }
  else {
    uVar3 = param_1[0x1db];
  }
  if ((param_1[2] & 0x2000) == 0) {
    iVar1 = D3D_g_pDevice->field3490_0x1c18;
    *(uint *)(iVar1 + 0x100410) = *(uint *)(iVar1 + 0x100410) | 0x10000;
    do {
    } while ((*(uint *)(iVar1 + 0x100410) & 0x10000) != 0);
    *(uint *)(param_1[0x704] + 0x40) = uVar3 & 0xfffffff;
    if (D3D::D3D__NullHardware != 0) {
      do {
        BVar2 = D3DDevice_IsBusy();
      } while (BVar2 != 0);
      param_1[2] = param_1[2] | 0x2000;
      return;
    }
  }
  else {
    param_1[0x704] = 0x181910;
    DAT_00181950 = *param_1 & 0xfffffff;
    *(uint *)(param_1[0x704] + 0x44) = DAT_00181950;
    *(uint *)param_1[0xc] = param_1[0xb] - 2;
    param_1[0x775] = param_1[0x91a];
  }
  return;
}




uint D3D8::D3D_SetFence(byte param_1)

{
  uint uVar1;
  D3D__Device *pDVar2;
  undefined4 *extraout_EAX;
  undefined4 *puVar3;
  uint uVar4;
  
  pDVar2 = D3D_g_pDevice;
  puVar3 = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 <= puVar3) {
    D3DDevice_MakeSpace();
    puVar3 = extraout_EAX;
  }
  uVar1 = *(uint *)&pDVar2->field_0x2c;
  *puVar3 = FUN_0004a310;
  puVar3[1] = (int)puVar3 << 5 | uVar1 & 0x1f;
  puVar3[2] = 0x41d70;
  puVar3[3] = uVar1;
  puVar3[4] = FUN_00041d90;
  puVar3[5] = 0;
  puVar3[6] = FUN_00041d90;
  puVar3[7] = 0;
  pDVar2->State = puVar3 + 8;
  uVar4 = uVar1 >> 1 & 0x3f;
  *(uint *)(&pDVar2->field_0x60 + uVar4 * 8) = uVar1;
  *(undefined4 **)(&pDVar2->field_0x64 + uVar4 * 8) = puVar3;
  if ((param_1 & 1) != 0) {
    uVar4 = *(int *)&pDVar2->field_0x34 + 1U & *(uint *)&pDVar2->field_0x38;
    *(uint *)&pDVar2->field_0x34 = uVar4;
    *(uint *)(*(int *)&pDVar2->field_0x44 + uVar4 * 8) = uVar1;
    *(undefined4 **)(*(int *)&pDVar2->field_0x44 + 4 + uVar4 * 8) = puVar3;
  }
  *(undefined4 *)&pDVar2->field_0x3c = 0;
  *(int *)&pDVar2->field_0x2c = *(int *)&pDVar2->field_0x2c + 2;
  if ((param_1 & 2) == 0) {
    CDevice_KickOff();
  }
  return uVar1;
}




void D3D8::D3D_BlockOnTime(DWORD Unknown1,int Unknown2)

{
  DWORD DVar1;
  D3D__Device *pDVar2;
  DWORD *pDVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  uint uVar6;
  NTSTATUS NVar7;
  undefined4 *puVar8;
  
  pDVar2 = D3D_g_pDevice;
  DVar1 = *(DWORD *)&D3D_g_pDevice->field_0x2c;
  if (DVar1 - *(int *)D3D_g_pDevice->inner1Ptr <= DVar1 - Unknown1) {
    return;
  }
  if (Unknown1 == DVar1) {
    D3D_SetFence(0);
  }
  pDVar3 = (DWORD *)FUN_001770a0();
  if (pDVar3 == (DWORD *)0x0) {
    return;
  }
  puVar4 = (undefined4 *)FUN_001771a0(pDVar2,0);
  if (puVar4 <= pDVar2->State) {
    puVar4 = (undefined4 *)((int)puVar4 + *(int *)&pDVar2->field_0x40);
  }
  puVar8 = (undefined4 *)pDVar3[1];
  if (puVar8 <= pDVar2->State) {
    puVar8 = (undefined4 *)((int)puVar8 + *(int *)&pDVar2->field_0x40);
  }
  if ((-1 < (int)puVar8 - (int)puVar4) && (0x23ff < (uint)((int)puVar8 - (int)puVar4))) {
    if (pDVar2->field3351_0x19ec != 0) {
      pDVar2->field3352_0x19f0 = Unknown1;
      (*(code *)pDVar2->field3351_0x19ec)(Unknown2);
      uVar5 = FUN_001771a0(pDVar2,0);
      uVar6 = FUN_00176ee0(uVar5);
      if (uVar6 < 0x2000) goto LAB_0017755b;
    }
    DVar1 = pDVar3[1];
    pDVar2->field3596_0x1dc0 = 0;
    if ((Unknown2 & 8U) == 0) {
      *(undefined1 **)(DVar1 + 0x10) = &LAB_0004010e_2;
      *(undefined4 *)(DVar1 + 0x14) = 0;
    }
    *(undefined4 *)(DVar1 + 0x18) = 0x40100;
    *(undefined4 *)(DVar1 + 0x1c) = 5;
    FUN_00177220();
    uVar5 = FUN_001771a0(pDVar2,1);
    uVar6 = FUN_00176ee0(uVar5);
    if (0x1fff < uVar6) {
      do {
        NVar7 = KeWaitForSingleObject
                          (&pDVar2->field3595_0x1dbc,UserRequest,'\x01','\0',(PLARGE_INTEGER)0x0);
      } while (NVar7 != 0);
      return;
    }
    *(undefined4 *)(DVar1 + 0x10) = 0x40100;
    *(undefined4 *)(DVar1 + 0x14) = 0;
    *(undefined4 *)(DVar1 + 0x18) = 0x40100;
    *(undefined4 *)(DVar1 + 0x1c) = 0;
    FUN_00177220();
    Unknown1 = *pDVar3;
  }
LAB_0017755b:
  if (pDVar2->field3351_0x19ec != 0) {
    pDVar2->field3352_0x19f0 = Unknown1;
    (*(code *)pDVar2->field3351_0x19ec)(Unknown2 | 0x80000000);
  }
  do {
  } while (*(int *)&pDVar2->field_0x2c - Unknown1 <
           (uint)(*(int *)&pDVar2->field_0x2c - *(int *)pDVar2->inner1Ptr));
  return;
}




undefined4 * D3D8::D3D_MakeRequestedSpace_8(uint param_1,uint param_2)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  D3D__Device *pDVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
  
  pDVar5 = D3D_g_pDevice;
  if ((D3D_g_pDevice->bitField1 & 4) != 0) {
    puVar1 = &D3D_g_pDevice->field_0x760;
    *(int *)&D3D_g_pDevice->field_0x764 =
         (int)D3D_g_pDevice->State +
         (*(int *)&D3D_g_pDevice->field_0x764 - *(int *)(*(int *)puVar1 + 4));
    puVar7 = *(undefined4 **)(*(int *)puVar1 + 4);
    pDVar5->State = puVar7;
    return puVar7;
  }
  puVar9 = D3D_g_pDevice->State;
  uVar3 = *(uint *)D3D_g_pDevice->inner1Ptr;
  puVar7 = (undefined4 *)FUN_00176f80();
  uVar8 = *(uint *)&pDVar5->field_0x28;
  uVar6 = (int)puVar9 + param_2;
  if ((uVar8 <= (int)puVar9 + param_2 + 0x4000) && (uVar6 = uVar8, uVar8 < param_1 + (int)puVar9)) {
    *(uint *)&pDVar5->field_0x40 = (int)pDVar5->State - pDVar5->field27_0x24;
    *pDVar5->State = (pDVar5->field27_0x24 & 0xfffffff) + 1;
    if (pDVar5->State < puVar7) {
      puVar7 = (undefined4 *)(pDVar5->field27_0x24 + 4);
    }
    puVar9 = (undefined4 *)pDVar5->field27_0x24;
    if (puVar7 == puVar9) {
      puVar7 = puVar9 + 1;
    }
    pDVar5->State = puVar9;
    uVar6 = (int)puVar9 + param_2;
  }
  param_2 = uVar6;
  if ((puVar9 < puVar7) && (puVar7 <= param_2)) {
    uVar8 = *(uint *)&pDVar5->field_0x34;
    iVar4 = *(int *)&pDVar5->field_0x44;
    do {
      iVar2 = uVar8 * 8;
      uVar8 = uVar8 - 1 & *(uint *)&pDVar5->field_0x38;
      puVar7 = *(undefined4 **)(iVar4 + 4 + uVar8 * 8);
      if (puVar7 < puVar9) {
        puVar7 = (undefined4 *)((int)puVar7 + *(int *)&pDVar5->field_0x40);
      }
    } while ((((undefined4 *)((Graphics::DXPushBufferSize >> 1) + (int)puVar9) < puVar7) &&
             (uVar8 != *(uint *)&pDVar5->field_0x34)) && (uVar3 < *(uint *)(iVar4 + uVar8 * 8)));
    D3D_BlockOnTime(*(DWORD *)(iVar4 + iVar2),8);
  }
  pDVar5->field1_0x4 = (undefined4 *)(param_2 - 0x204);
  if ((pDVar5->bitField1 & 0x800) == 0) {
    D3D_SetFence(3);
    CDevice_KickOff();
    return pDVar5->State;
  }
  pDVar5->bitField1 = pDVar5->bitField1 | 0x1000;
  CDevice_KickOff();
  return pDVar5->State;
}




void D3D8::D3DDevice_MakeSpace(void)

{
  D3D_MakeRequestedSpace_8(Graphics::DXPushBufferSize >> 1,Graphics::DXPushBufferSize);
  return;
}




int D3D8::D3DDevice_BeginStateBig(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 *space;
  uint uVar3;
  
  space = D3D_g_pDevice->State;
  if (D3D_g_pDevice->field1_0x4 + 0x80 <= space + param_1) {
    uVar1 = param_1 * 4 + 0x204;
    uVar2 = Graphics::DXPushBufferSize >> 1;
    if (Graphics::DXPushBufferSize >> 1 < uVar1) {
      uVar2 = uVar1;
    }
    uVar3 = Graphics::DXPushBufferSize;
    if (Graphics::DXPushBufferSize < uVar1) {
      uVar3 = uVar1;
    }
    space = (undefined4 *)D3D_MakeRequestedSpace_8(uVar2,uVar3);
  }
  return (int)space;
}




void D3D8::D3D_KickOffAndWaitForIdle(void)

{
  D3D_BlockOnTime(*(DWORD *)&D3D_g_pDevice->field_0x2c,2);
  return;
}




void D3D8::D3D_BlockOnResource(D3DResource *pResource)

{
  D3DResource *pDVar1;
  DWORD Unknown1;
  int iVar2;
  
  if (D3D_g_pDevice != (D3D__Device *)0x0) {
    if ((((pResource->Common & 0x70000) == 0x50000) &&
        (pDVar1 = (D3DResource *)pResource[1].Lock, pDVar1 != (D3DResource *)0x0)) &&
       (iVar2 = FUN_00175930(pResource), pResource = pDVar1, iVar2 != 0)) {
      D3D_BlockOnTime(*(DWORD *)&D3D_g_pDevice->field_0x2c,2);
      return;
    }
    Unknown1 = pResource->Lock;
    iVar2 = FUN_00175930(pResource);
    if (iVar2 != 0) {
      D3D_BlockOnTime(*(DWORD *)&D3D_g_pDevice->field_0x2c,2);
      return;
    }
    if (Unknown1 != 0) {
      D3D_BlockOnTime(Unknown1,0x10);
    }
  }
  return;
}




void D3D::D3DTexture_GetLevelDesc(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  undefined1 auStack_8 [4];
  undefined1 auStack_4 [4];
  
  puVar2 = param_3;
  uVar1 = param_1;
  *param_3 = (uint)*(byte *)(param_1 + 0xd);
  uVar3 = D3D8::D3DResource_GetType(param_1);
  puVar2[1] = uVar3;
  puVar2[2] = 0;
  if (param_2 == 0) {
    if ((char)(&DAT_0017f958)[*(byte *)(uVar1 + 0xd)] < '\0') {
      puVar2[2] = 1;
    }
    else if (((&DAT_0017f958)[*(byte *)(uVar1 + 0xd)] & 0x40) != 0) {
      puVar2[2] = 2;
    }
  }
  if (*(int *)(uVar1 + 4) == *(int *)(D3D8::D3D_g_pDevice->field3357_0x1a04 + 4)) {
    puVar2[4] = D3D8::D3D_g_pDevice->field3315_0x195c;
  }
  else {
    puVar2[4] = 0x11;
  }
  FUN_0017b0f0(uVar1,param_2,&param_1,&param_3,auStack_4,auStack_8,&param_2);
  puVar2[5] = param_1;
  puVar2[6] = (uint)param_3;
  puVar2[3] = param_2;
  return;
}




D3DSurface * D3D8::D3DTexture_GetSurfaceLevel2(D3DTexture *param_1,undefined4 param_2)

{
  D3DTexture *pDVar1;
  D3DSurface *pDVar2;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  pDVar1 = param_1;
  FUN_0017b300(param_1,0,param_2,&param_2,local_4,local_8,&local_c,&param_1);
  pDVar2 = (D3DSurface *)FUN_00175c00(local_c,param_1,pDVar1,param_2);
  return pDVar2;
}



void D3D8::D3DTexture_LockRect
               (D3DPixelContainer *param_1,UINT param_2,D3DLOCKED_RECT *param_3,RECT *param_4,
               DWORD param_5)

{
  Lock2DSurface(param_1,D3DCUBEMAP_FACE_POSITIVE_X,param_2,param_3,param_4,param_5);
  return;
}




void D3D::D3D_AllocContiguousMemory(uint param_1,uint param_2)

{
  int iVar1;
  
  if (param_2 < 0x1001) {
    XAPILIB::XMemAlloc(param_1,0xbc800000);
    return;
  }
  iVar1 = 0;
  if (param_2 != 0) {
    for (; (param_2 >> iVar1 & 1) == 0; iVar1 = iVar1 + 1) {
    }
  }
  XAPILIB::XMemAlloc(param_1,iVar1 << 0x18 | 0xb0800000);
  return;
}




undefined4 * D3D8::D3DDevice_CreateVertexBuffer2(uint param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  
  puVar1 = XAPILIB::XMemAlloc(0xc,0x64800000);
  if (puVar1 != (undefined4 *)0x0) {
    pvVar2 = XAPILIB::XMemAlloc(param_1,0xb2800000);
    if (pvVar2 != (void *)0x0) {
      puVar1[1] = (uint)pvVar2 & 0xfffffff;
      *puVar1 = 0x1000001;
      return puVar1;
    }
    XAPILIB::XMemFree(puVar1,0x24800000);
  }
  return (undefined4 *)0x0;
}




BYTE * D3D8::D3DVertexBuffer_Lock2(D3DVertexBuffer *pVertexBuffer,DWORD Flags)

{
  D3D__Device *pDVar1;
  undefined4 *extraout_EAX;
  undefined4 *puVar2;
  
  pDVar1 = D3D_g_pDevice;
  if ((Flags & 0x10) == 0) {
    puVar2 = D3D_g_pDevice->State;
    if (D3D_g_pDevice->field1_0x4 <= puVar2) {
      D3DDevice_MakeSpace();
      puVar2 = extraout_EAX;
    }
    *puVar2 = 0x41710;
    puVar2[1] = 0;
    pDVar1->State = puVar2 + 2;
  }
  if ((Flags & 0xa0) == 0) {
    FUN_00177800(pVertexBuffer);
  }
  return (BYTE *)((pVertexBuffer->resource).Data | 0x80000000);
}




D3DCOLOR * D3D8::D3DPalette_Lock2(D3DPalette *pThis,DWORD Flags)

{
  if ((Flags & 0xa0) == 0) {
    FUN_00177800(pThis);
  }
  return (D3DCOLOR *)((pThis->resource).Data | 0x80000000);
}




uint D3D::D3DPalette_GetSize(uint *param_1)

{
  return *param_1 >> 0x1e;
}




void D3D8::D3D_LazySetPointParams(void *Device)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 *extraout_EAX;
  undefined4 *puVar10;
  uint uVar11;
  undefined4 *puVar12;
  
  puVar10 = *(undefined4 **)Device;
  if (*(undefined4 **)((int)Device + 4) <= puVar10) {
    D3DDevice_MakeSpace();
    puVar10 = extraout_EAX;
  }
  fVar9 = DAT_00181d58;
  fVar8 = DAT_00181d54;
  fVar7 = DAT_00181d50;
  iVar6 = DAT_00181d4c;
  fVar4 = DAT_00181d44;
  fVar2 = DAT_00181d40;
  if (DAT_00181d4c == 0) {
    fVar2 = DAT_00181d40 * *(float *)((int)Device + 0x960);
    if (fVar2 < DAT_00181d44) {
      fVar2 = DAT_00181d44;
    }
    if (DAT_00181d5c < fVar2) {
      fVar2 = DAT_00181d5c;
    }
    puVar12 = puVar10;
    if (_DAT_00180140 < fVar2) {
      fVar2 = _DAT_00180140;
    }
  }
  else {
    fVar1 = DAT_00181d5c - DAT_00181d44;
    fVar3 = (float)*(int *)((int)Device + 0xedc);
    if (*(int *)((int)Device + 0xedc) < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    fVar3 = fVar3 * DAT_00181d40;
    *puVar10 = &DAT_00200a30;
    fVar3 = fVar1 / fVar3;
    puVar10[4] = fVar1;
    puVar10[5] = fVar1;
    puVar10[6] = fVar1;
    puVar10[8] = fVar4;
    puVar12 = puVar10 + 9;
    fVar3 = fVar3 * fVar3;
    puVar10[1] = fVar7 * fVar3;
    puVar10[2] = fVar8 * fVar3;
    puVar10[3] = fVar3 * fVar9;
    puVar10[7] = -(fVar4 / fVar1);
  }
  uVar5 = DAT_00181d48;
  *puVar12 = &LAB_00080318;
  puVar12[1] = iVar6;
  puVar12[2] = uVar5;
  uVar11 = FUN_001782c0(fVar2 * 8.0 + 0.5);
  if (0x1ff < uVar11) {
    uVar11 = 0x1ff;
  }
  puVar12[3] = 0x4043c;
  puVar12[4] = uVar11;
  *(undefined4 **)Device = puVar12 + 5;
  return;
}




void __thiscall D3D8::CDevice_SetStateVB(undefined4 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  UINT UVar4;
  uint uVar5;
  uint *extraout_EAX;
  uint *puVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int local_8;
  
  UVar4 = Graphics::GraphicsFlags;
  uVar5 = Graphics::GraphicsFlags & 0xffffffaf;
  uVar9 = Graphics::GraphicsFlags & 0x3fffff8f;
  Graphics::GraphicsFlags = uVar5;
  if (uVar9 != 0) {
    FUN_001799a0();
  }
  if (((UVar4 & 0x40000000) == 0) && (((UVar4 & 0x40) != 0 || (param_1[8] != param_2)))) {
    iVar1 = param_1[0x1e4];
    param_1[8] = param_2;
    uVar9 = *(uint *)(iVar1 + 4) & 0x10;
    puVar6 = (uint *)*param_1;
    if ((uint *)param_1[1] <= puVar6) {
      D3DDevice_MakeSpace();
      puVar6 = extraout_EAX;
    }
    if ((UVar4 & 0x10) != 0) {
      *puVar6 = (uint)&DAT_00401760;
      puVar6 = puVar6 + 1;
      uVar5 = 0;
      do {
        iVar7 = (uint)*(byte *)((int)&DAT_0032cf38 + uVar5 + uVar9) * 0x10;
        *puVar6 = (&D3D::D3D__Device.field4032_0x2490)[*(int *)(iVar7 + iVar1 + 0x14) * 3] * 0x100 +
                  *(int *)(iVar7 + 0x1c + iVar1);
        puVar6 = puVar6 + 1;
        uVar5 = uVar5 + 1;
      } while (uVar5 < 0x10);
    }
    if (param_2 == 0) {
      uVar5 = 0x41720;
      iVar7 = 0;
      do {
        iVar8 = iVar1 + (uint)*(byte *)((int)&DAT_0032cf38 + iVar7 + uVar9) * 0x10;
        if (*(int *)(iVar8 + 0x1c) != 2) {
          if ((&D3D::D3D__Device.field4034_0x2498)[*(int *)(iVar8 + 0x14) * 3] != 0) {
            iVar2 = *(int *)((&D3D::D3D__Device.field4034_0x2498)[*(int *)(iVar8 + 0x14) * 3] + 4);
            iVar3 = *(int *)(iVar8 + 0x18);
            iVar8 = (&D3D::D3D__Device.field4033_0x2494)[*(int *)(iVar8 + 0x14) * 3];
            *puVar6 = uVar5;
            puVar6[1] = iVar2 + iVar3 + iVar8;
            puVar6 = puVar6 + 2;
          }
        }
        uVar5 = uVar5 + 4;
        iVar7 = iVar7 + 1;
      } while (uVar5 < 0x41760);
      *param_1 = puVar6;
      return;
    }
    local_8 = 0;
    uVar5 = 0x41720;
    do {
      iVar7 = (uint)*(byte *)((int)&DAT_0032cf38 + local_8 + uVar9) * 0x10 + iVar1;
      if (*(int *)(iVar7 + 0x1c) != 2) {
        iVar8 = *(int *)(iVar7 + 0x14);
        if ((&D3D::D3D__Device.field4034_0x2498)[iVar8 * 3] != 0) {
          iVar2 = (&D3D::D3D__Device.field4032_0x2490)[iVar8 * 3];
          iVar3 = *(int *)((&D3D::D3D__Device.field4034_0x2498)[iVar8 * 3] + 4);
          iVar7 = *(int *)(iVar7 + 0x18);
          iVar8 = (&D3D::D3D__Device.field4033_0x2494)[iVar8 * 3];
          *puVar6 = uVar5;
          puVar6[1] = iVar2 * param_2 + iVar3 + iVar7 + iVar8;
          puVar6 = puVar6 + 2;
        }
      }
      local_8 = local_8 + 1;
      uVar5 = uVar5 + 4;
    } while (uVar5 < 0x41760);
    *param_1 = puVar6;
  }
  return;
}




void __fastcall D3D8::CDevice_SetStateUP(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *extraout_EAX;
  undefined4 *puVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  uint local_14;
  int local_10;
  int local_c;
  int local_4;
  
  if ((Graphics::GraphicsFlags & 0x3fffff8f) != 0) {
    FUN_001799a0();
  }
  if ((Graphics::GraphicsFlags & 0x20) != 0) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags & 0xffffffdf | 0x50;
    iVar2 = param_1[0x1e4];
    uVar3 = *(uint *)(iVar2 + 4);
    puVar4 = (undefined4 *)*param_1;
    iVar7 = 0;
    local_10 = 0;
    local_c = 0;
    if ((undefined4 *)param_1[1] <= puVar4) {
      D3DDevice_MakeSpace();
      puVar4 = extraout_EAX;
    }
    *puVar4 = &DAT_00401760;
    puVar6 = puVar4 + 1;
    local_14 = 0;
    do {
      iVar1 = (uint)*(byte *)((int)&DAT_0032cf38 + local_14 + (uVar3 & 0x10)) * 0x10 + iVar2;
      uVar5 = *(uint *)(iVar1 + 0x1c);
      *puVar6 = uVar5;
      puVar6 = puVar6 + 1;
      if (uVar5 != 2) {
        iVar1 = *(int *)(iVar1 + 0x18);
        uVar5 = (uint)(byte)(&DAT_0017fa3c)[uVar5 >> 4 & 0xf] *
                (uint)(byte)(&DAT_0017fa34)[uVar5 & 0xf] + 3 >> 2;
        if (iVar7 == 0) {
          param_1[0x2f1] = uVar5;
          iVar7 = 1;
          local_4 = iVar1;
        }
        else if (iVar1 - local_c == 0) {
          param_1[iVar7 * 2 + 0x2ef] = param_1[iVar7 * 2 + 0x2ef] + uVar5;
        }
        else {
          param_1[iVar7 * 2 + 0x2f0] = iVar1 - local_c;
          param_1[iVar7 * 2 + 0x2f1] = uVar5;
          iVar7 = iVar7 + 1;
        }
        local_10 = local_10 + uVar5;
        local_c = iVar1 + uVar5 * 4;
      }
      local_14 = local_14 + 1;
    } while (local_14 < 0x10);
    param_1[0x2ee] = local_10;
    param_1[0x311] = iVar7;
    *param_1 = puVar6;
    param_1[0x2ef] = local_4;
    param_1[0x2f0] = local_4 - local_c;
  }
  return;
}




void __fastcall D3D8::CDevice_FreeFrameBuffers(int param_1)

{
  PVOID pvVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  pvVar1 = AvGetSavedDataAddress();
  if (pvVar1 == (PVOID)0x0) {
    AvSendTVEncoderOption(*(PVOID *)(param_1 + 0x1c18),9,1,(PULONG)0x0);
  }
  iVar2 = *(int *)(param_1 + 0x19f4);
  if (iVar2 != 0) {
    if (*(int *)(iVar2 + 0x14) != 0) {
      iVar2 = *(int *)(iVar2 + 0x14);
    }
    *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(param_1 + 0x2c);
    FUN_00175b90(*(undefined4 *)(param_1 + 0x19f4));
    *(undefined4 *)(param_1 + 0x19f4) = 0;
  }
  iVar2 = *(int *)(param_1 + 0x19f8);
  if (iVar2 != 0) {
    if (*(int *)(iVar2 + 0x14) != 0) {
      iVar2 = *(int *)(iVar2 + 0x14);
    }
    *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(param_1 + 0x2c);
    FUN_00175b90(*(undefined4 *)(param_1 + 0x19f8));
    *(undefined4 *)(param_1 + 0x19f8) = 0;
  }
  uVar3 = 0;
  if (*(int *)(param_1 + 0x1a00) != 0) {
    puVar4 = (undefined4 *)(param_1 + 0x1a04);
    do {
      if ((D3DResource *)*puVar4 != (D3DResource *)0x0) {
        D3DResource_Release((D3DResource *)*puVar4);
        *puVar4 = 0;
      }
      uVar3 = uVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0x1a00));
  }
  if (*(D3DResource **)(param_1 + 0x1a10) != (D3DResource *)0x0) {
    D3DResource_Release(*(D3DResource **)(param_1 + 0x1a10));
    *(undefined4 *)(param_1 + 0x1a10) = 0;
  }
  if (*(int *)(param_1 + 0x1a7c) != 0) {
    D3D_SetTileNoWait(1,0);
    XAPILIB::XMemFree(*(undefined4 *)(param_1 + 0x1a7c),0xa1800000);
    *(undefined4 *)(param_1 + 0x1a7c) = 0;
  }
  if (*(int *)(param_1 + 0x1a74) != 0) {
    D3D_SetTileNoWait(0,0);
    XAPILIB::XMemFree(*(undefined4 *)(param_1 + 0x1a74),0xa1800000);
    *(undefined4 *)(param_1 + 0x1a74) = 0;
  }
  if (*(int *)(param_1 + 0x1a78) != 0) {
    XAPILIB::XMemFree(*(int *)(param_1 + 0x1a78),0xa1800000);
    *(undefined4 *)(param_1 + 0x1a78) = 0;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x0017a2a3)
// WARNING: Removing unreachable block (ram,0x0017a2bb)


undefined4 __thiscall D3D8::CDevice_InitializeFrameBuffers(undefined4 *param_1,int *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  void *pvVar5;
  int iVar6;
  undefined4 *extraout_EAX;
  undefined4 *puVar7;
  int *piVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  uint local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  uint local_20;
  int local_1c;
  undefined4 local_18;
  void *local_14;
  uint local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  piVar2 = param_2;
  local_44 = 1;
  if (param_2[3] != 0) {
    local_44 = param_2[3];
  }
  local_2c = FUN_0017ae10(param_2[2]);
  local_1c = FUN_0017ae10(param_2[9]);
  local_24 = *param_2;
  DAT_00181d6c = param_2[0xc];
  local_28 = param_2[1];
  param_1[0x658] = param_2[5];
  uVar9 = param_1[2];
  local_34 = local_44 + 1;
  param_1[0x680] = local_34;
  param_1[2] = uVar9 & 0xffffbfff;
  D3DRS_MultiSampleMode = 0;
  local_3c = 0;
  if (((param_2[4] & 0x3000U) != 0) || (param_2[5] == 3)) {
    local_3c = 1;
    param_1[2] = uVar9 & 0xffffbfff | 0x4000;
  }
  uVar9 = param_2[4];
  if (uVar9 == 0) {
    uVar9 = 0x11;
  }
  uVar3 = uVar9 >> 4 & 0xf;
  local_20 = uVar9 & 0xf;
  param_1[0x657] = uVar9;
  param_1[0x25a] = (float)uVar3;
  param_1[0x25b] = (float)local_20;
  if (((uVar9 & 0x1000) != 0) && (D3DRS_MultiSampleMode = 2, (char)uVar9 == '!')) {
    D3DRS_MultiSampleMode = 1;
  }
  DAT_00181d68 = 2;
  if ((uVar9 & 0x100) == 0) {
    if ((uVar9 & 0x200) != 0) {
      DAT_00181d68 = 5;
    }
  }
  else {
    DAT_00181d68 = 4;
  }
  piVar8 = param_2 + 0xd;
  if (*piVar8 == 0) {
    local_50 = (undefined4 *)local_2c;
    uVar9 = param_2[4] & 0xf0000;
    if (uVar9 < 0x30001) {
      if (uVar9 == 0x30000) {
        local_50 = (undefined4 *)0x1e;
      }
      else if (uVar9 == 0x10000) {
        local_50 = (undefined4 *)0x1c;
      }
      else if (uVar9 == 0x20000) {
        local_50 = (undefined4 *)0x11;
      }
    }
    else if (uVar9 == 0x40000) {
      local_50 = (undefined4 *)0x12;
    }
    iVar4 = uVar3 * local_24;
    local_20 = local_20 * local_28;
    local_40 = iVar4;
    uVar9 = FUN_0017af20(iVar4,local_50);
    local_38 = FUN_0017b5d0(iVar4,local_20,1,1,local_50,uVar9,0,0,&local_48,&local_4c);
    if (local_3c == 0) {
      local_50 = (undefined4 *)local_34;
    }
    else {
      local_50 = (undefined4 *)0x1;
    }
    for (local_30 = (((int)local_50 * local_38 + -1 + uVar9) / uVar9) * uVar9;
        (local_30 & 0x3fff) != 0; local_30 = local_30 + uVar9) {
    }
    pvVar5 = XAPILIB::XMemAlloc(local_30,0xbe800000);
    if (pvVar5 == (void *)0x0) {
      return 0x8007000e;
    }
    param_1[0x69d] = pvVar5;
    if (local_50 != (undefined4 *)0x0) {
      puVar7 = param_1 + 0x685;
      local_34 = (int)local_50;
      local_50 = param_1 + 0x681;
      do {
        *local_50 = puVar7;
        FUN_00175c60(puVar7,local_48,local_4c,pvVar5);
        pvVar5 = (void *)((int)pvVar5 + local_38);
        local_50 = local_50 + 1;
        puVar7 = puVar7 + 6;
        local_34 = local_34 + -1;
      } while (local_34 != 0);
    }
    if (local_40 != 0x780) {
      local_14 = (void *)param_1[0x69d];
      local_18 = 0;
      local_c = 0;
      local_8 = 0;
      local_4 = 0;
      local_10 = local_30;
      local_c = FUN_00174080(param_1[0x681]);
      D3D_SetTileNoWait(0,&local_18);
    }
    if (local_3c != 0) {
      local_38 = FUN_0017b5d0(local_24,local_28,1,1,local_2c,0,0,0,&local_48,&local_4c);
      iVar4 = local_44;
      pvVar5 = XAPILIB::XMemAlloc(local_38 * local_44,0xbe800000);
      if (pvVar5 == (void *)0x0) {
        return 0x8007000e;
      }
      param_1[0x69e] = pvVar5;
      if (iVar4 != 0) {
        puVar7 = param_1 + 0x682;
        puVar10 = param_1 + 0x68b;
        local_24 = local_44;
        do {
          *puVar7 = puVar10;
          FUN_00175c60(puVar10,local_48,local_4c,pvVar5);
          pvVar5 = (void *)((int)pvVar5 + local_38);
          puVar7 = puVar7 + 1;
          puVar10 = puVar10 + 6;
          local_24 = local_24 + -1;
        } while (local_24 != 0);
        local_24 = 0;
      }
    }
    iVar4 = local_1c;
    if (param_2[8] != 0) {
      uVar3 = FUN_0017af20(local_40,local_1c);
      iVar6 = FUN_0017b5d0(local_40,local_20,1,1,iVar4,uVar3,0,0,&local_48,&local_4c);
      for (uVar9 = ((iVar6 + -1 + uVar3) / uVar3) * uVar3; (uVar9 & 0x3fff) != 0;
          uVar9 = uVar9 + uVar3) {
      }
      pvVar5 = XAPILIB::XMemAlloc(uVar9,0xbe800000);
      if (pvVar5 == (void *)0x0) {
        return 0x8007000e;
      }
      param_1[0x69f] = pvVar5;
      param_1[0x684] = param_1 + 0x697;
      FUN_00175c60(param_1 + 0x697,local_48,local_4c,pvVar5);
      if (local_40 != 0x780) {
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        local_18 = 0x80000001;
        local_14 = pvVar5;
        local_10 = uVar9;
        local_c = FUN_00174080(param_1[0x684]);
        if (((&DAT_0017f958)[iVar4] & 0x3c) == 0x20) {
          local_18 = 0x84000001;
        }
        D3D_SetTileNoWait(1,&local_18);
      }
    }
  }
  else {
    if (local_34 != 0) {
      param_2 = param_1 + 0x681;
      puVar7 = param_1 + 0x685;
      local_38 = local_34;
      do {
        puVar10 = (undefined4 *)*piVar8;
        *puVar7 = *puVar10;
        puVar7[1] = puVar10[1];
        puVar7[2] = puVar10[2];
        puVar7[3] = puVar10[3];
        puVar7[4] = puVar10[4];
        puVar7[5] = puVar10[5];
        *param_2 = (int)puVar7;
        param_2 = param_2 + 1;
        piVar8 = piVar8 + 1;
        puVar7 = puVar7 + 6;
        local_38 = local_38 + -1;
      } while (local_38 != 0);
    }
    puVar7 = (undefined4 *)piVar2[0x10];
    if (puVar7 != (undefined4 *)0x0) {
      param_1[0x697] = *puVar7;
      param_1[0x698] = puVar7[1];
      param_1[0x699] = puVar7[2];
      param_1[0x69a] = puVar7[3];
      param_1[0x69b] = puVar7[4];
      param_1[0x69c] = puVar7[5];
      param_1[0x684] = param_1 + 0x697;
    }
  }
  uVar9 = 0;
  if (param_1[0x680] != 0) {
    puVar7 = param_1 + 0x681;
    do {
      D3DResource_AddRef((D3DResource *)*puVar7);
      uVar9 = uVar9 + 1;
      puVar7 = puVar7 + 1;
    } while (uVar9 < (uint)param_1[0x680]);
  }
  if ((D3DResource *)param_1[0x684] != (D3DResource *)0x0) {
    D3DResource_AddRef((D3DResource *)param_1[0x684]);
  }
  puVar7 = (undefined4 *)*param_1;
  if ((undefined4 *)param_1[1] <= puVar7) {
    D3DDevice_MakeSpace();
    puVar7 = extraout_EAX;
  }
  uVar1 = param_1[0x680];
  *puVar7 = &LAB_000c0120;
  puVar7[1] = 0;
  puVar7[2] = 1;
  puVar7[3] = uVar1;
  *param_1 = puVar7 + 4;
  return 0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


int __thiscall D3D__Device::D3D__Device(D3D__Device *this,undefined4 *param_1)

{
  undefined4 *this_00;
  D3DDeviceInner1 *inner1;
  undefined4 uVar2;
  BOOL BVar1;
  int i;
  uint uVar4;
  int *puVar5;
  undefined4 *puVar6;
  int unaff_FS_OFFSET;
  undefined4 local_164;
  undefined1 local_160 [12];
  undefined4 local_154;
  undefined1 local_150 [16];
  undefined1 local_140 [12];
  undefined4 local_134;
  undefined1 local_130 [12];
  undefined4 local_124;
  undefined1 local_120 [16];
  undefined1 local_110 [16];
  undefined1 local_100 [16];
  undefined1 local_f0 [16];
  undefined1 local_e0 [16];
  undefined1 local_d0 [16];
  undefined1 local_c0 [16];
  undefined1 local_b0 [16];
  undefined1 local_a0 [16];
  undefined1 local_90 [16];
  undefined1 local_80 [16];
  undefined1 local_70 [16];
  undefined1 local_60 [16];
  undefined1 local_50 [16];
  undefined1 local_40 [16];
  undefined1 local_30 [16];
  undefined1 local_20 [16];
  undefined1 local_10 [16];
  
  inner1 = XAPILIB::XMemAlloc(96,0xac800000);
  this->field4026_0x2478 = inner1;
  if (inner1 == (D3DDeviceInner1 *)0x0) {
    return -0x7ff8fff2;
  }
  this->inner1Ptr = inner1;
  this->inner1Ptr_intArray8_2 = inner1->intArray8_2;
  this->inner1Ptr_intArray8_1 = inner1->intArray8_1;
  puVar5 = inner1->intArray8_1;
  for (i = 0x10; i != 0; i = i + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  uVar4 = AutoClass2__FUN_00176fd0(this);
  if (-1 < (int)uVar4) {
    Graphics::GraphicsFlags = Graphics::GraphicsFlags | 0xff7f7f;
    this_00 = &this->field3490_0x1c18;
    this->field2286_0x948 = 0x40;
    CMiniport_InitHardware((D3D__Device *)this_00);
    D3D8::CMiniport_CreateCtxDmaObject(3,0x3d,0,134197247,local_120);
    D3D8::CMiniport_CreateCtxDmaObject(5,2,0,0x7ffafff,local_f0);
    D3D8::CMiniport_CreateCtxDmaObject(4,3,0,0x7ffafff,local_d0);
    D3D8::CMiniport_CreateCtxDmaObject(9,0x3d,0,0x7ffafff,local_130);
    this->field4023_0x246c = local_124;
    D3D8::CMiniport_CreateCtxDmaObject(10,0x3d,0,0x7ffafff,local_140);
    this->field4024_0x2470 = local_134;
    D3D8::CMiniport_CreateCtxDmaObject(11,0x3d,0,0x7ffafff,local_160);
    this->field4025_0x2474 = local_154;
    D3D8::CMiniport_CreateCtxDmaObject(2,3,this->inner1Ptr_intArray8_1,0x1f,local_c0);
    D3D8::CMiniport_CreateCtxDmaObject(7,0x3d,this->inner1Ptr_intArray8_2,0x1f,local_110);
    D3D8::CMiniport_CreateCtxDmaObject(12,0x3d,0x80000000,0x10000000,local_e0);
    D3D8::CMiniport_CreateCtxDmaObject(8,0x3d,this->inner1Ptr,0x20,local_100);
    D3D8::CMiniport_CreateCtxDmaObject(6,2,0,0x7ffafff,local_150);
    FUN_0017c5da(0x206e,0,local_150,0,&local_164);
    FUN_0017c63d(local_150);
    FUN_0017c63d(local_e0);
    FUN_0017c63d(local_c0);
    FUN_0017c63d(local_110);
    FUN_0017c63d(local_d0);
    FUN_0017c63d(local_f0);
    FUN_0017c63d(local_120);
    FUN_0017c63d(local_130);
    FUN_0017c63d(local_140);
    FUN_0017c63d(local_160);
    FUN_0017c63d(local_100);
    FUN_0017c921(0xd,0x97,local_60);
    FUN_0017c921(0xe,0x39,local_b0);
    FUN_0017c921(0x10,0x9f,local_10);
    FUN_0017c921(0x11,0x62,local_90);
    FUN_0017c921(0x12,0x44,local_40);
    FUN_0017c921(0x13,0x57,local_a0);
    FUN_0017c921(0x14,0x43,local_20);
    FUN_0017c921(0x15,0x12,local_30);
    FUN_0017c921(0x16,0x72,local_50);
    FUN_0017c921(0x18,0x19,local_70);
    FUN_0017c921(0x19,0x30,local_80);
    _DAT_0018195c = *this_00;
    this->field2268_0x930 = _DAT_0018195c;
    this->field3488_0x1c10 = local_164;
    _DAT_80000000 = (this->field27_0x24 & 0xfffffff) + 1;
    D3D8::CDevice_KickOff();
    uVar4 = (uint)this->State ^ *(uint *)(this->field3488_0x1c10 + 0x44);
    while ((uVar4 & 0xfffffff) != 0) {
      FUN_00176ec0();
      uVar4 = (uint)this->State ^ *(uint *)(this->field3488_0x1c10 + 0x44);
    }
    _DAT_80000000 = 0xdeadbeef;
    FUN_00179ed0();
    uVar4 = D3D8::CDevice_InitializeFrameBuffers(param_1);
    if (-1 < (int)uVar4) {
      uVar2 = FUN_00174080(this->field3358_0x1a08);
      uVar4 = FUN_0017b85d(*param_1,param_1[1],param_1[0xb],param_1[10],param_1[2],param_1[0xc],
                           uVar2);
      if (-1 < (int)uVar4) {
        D3D8::D3D_SetFence(0);
        do {
          BVar1 = D3D8::D3DDevice_IsBusy();
        } while (BVar1 != 0);
        this->field1876_0x790 = &DAT_00184478;
        D3D8::D3DDevice_SetVertexShader(4);
        D3D8::D3DDevice_SetVertexShader(2);
        puVar6 = &D3D::D3D__Device.field4080_0x2550;
        for (i = 0x46; i != 0; i = i + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        D3D::D3D__Device.field4081_0x2554 = 0x10;
        D3D8::D3DDevice_SetRenderTarget
                  ((D3DSurface *)this->field3357_0x1a04,(D3DSurface *)this->field3360_0x1a10);
        FUN_00179fe0();
        D3D8::D3DDevice_Clear(0,(D3DRECT *)0x0,3,0,1.0,0);
        i = *(int *)(*(int *)(unaff_FS_OFFSET + 0x20) + 0x250);
        if ((i != 0) && (puVar5 = *(int **)(i + 0x20), puVar5 != (int *)0x0)) {
          puVar5[1] = (int)&this->field4022_0x2468;
          *puVar5 = (int)&this->field3601_0x1dd4;
          puVar5[2] = this->field3358_0x1a08;
          puVar5[3] = (int)this_00;
          puVar5[5] = (int)&this->field_0x8d0;
          puVar5[6] = (int)&this->field_0x8d8;
          puVar5[7] = (int)&LAB_001750b0;
          puVar5[8] = -0x54321100;
        }
        D3D8::D3DDevice_SetFlickerFilter(5);
        D3D8::D3DDevice_SetSoftDisplayFilter(0);
        uVar4 = 0;
      }
    }
  }
  return uVar4;
}




void D3D8::Get2DSurfaceDesc(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  puVar2 = param_3;
  uVar1 = param_1;
  *param_3 = (uint)*(byte *)(param_1 + 0xd);
  uVar3 = D3DResource_GetType(param_1);
  puVar2[1] = uVar3;
  puVar2[2] = 0;
  if (param_2 == 0) {
    if ((char)(&DAT_0017f958)[*(byte *)(uVar1 + 0xd)] < '\0') {
      puVar2[2] = 1;
    }
    else if (((&DAT_0017f958)[*(byte *)(uVar1 + 0xd)] & 0x40) != 0) {
      puVar2[2] = 2;
    }
  }
  if (*(int *)(uVar1 + 4) == *(int *)(D3D_g_pDevice->field3357_0x1a04 + 4)) {
    puVar2[4] = D3D_g_pDevice->field3315_0x195c;
  }
  else {
    puVar2[4] = 0x11;
  }
  FUN_0017b0f0(uVar1,param_2,&param_1,&param_3,local_4,local_8,&param_2);
  puVar2[5] = param_1;
  puVar2[6] = (uint)param_3;
  puVar2[3] = param_2;
  return;
}



void FUN_0017b300(int param_1,int param_2,int param_3,uint *param_4,uint *param_5,uint *param_6,
                 uint *param_7,undefined4 *param_8)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint local_18;
  uint local_14;
  uint local_c;
  uint local_4;
  
  iVar2 = param_1;
  uVar4 = *(uint *)(param_1 + 0x10);
  local_14 = *(uint *)(param_1 + 4) | 0x80000000;
  uVar3 = (byte)(&DAT_0017f958)[*(byte *)(param_1 + 0xd)] & 0x3c;
  if (uVar4 == 0) {
    uVar4 = *(uint *)(param_1 + 0xc);
    bVar1 = *(byte *)(param_1 + 0xd);
    uVar9 = uVar4 >> 0x14 & 0xf;
    uVar12 = uVar4 >> 0x18 & 0xf;
    uVar4 = uVar4 >> 0x1c;
    bVar5 = 0;
    if ((bVar1 == 0xc) || ((0xd < bVar1 && (bVar1 < 0x10)))) {
      bVar5 = 1;
    }
    uVar6 = -(uint)bVar5 & 2;
    if (param_2 != 0) {
      iVar10 = 0;
      local_4 = *(byte *)(param_1 + 0xe) & 0xf;
      uVar11 = uVar9;
      local_18 = uVar12;
      local_c = uVar4;
      if ((*(byte *)(param_1 + 0xe) & 0xf) != 0) {
        do {
          uVar8 = uVar6;
          if (uVar6 < uVar11) {
            uVar8 = uVar11;
          }
          uVar7 = uVar6;
          if (uVar6 < local_18) {
            uVar7 = local_18;
          }
          iVar10 = iVar10 + ((1 << ((char)uVar7 + (char)uVar8 & 0x1fU)) * uVar3 >> 3);
          if (uVar11 != 0) {
            uVar11 = uVar11 - 1;
          }
          if (local_18 != 0) {
            local_18 = local_18 - 1;
          }
          if (local_c != 0) {
            local_c = local_c - 1;
          }
          local_4 = local_4 - 1;
        } while (local_4 != 0);
      }
      local_14 = local_14 + (iVar10 + 0x7fU & 0xffffff80) * param_2;
    }
    if (param_3 != 0) {
      param_1 = param_3;
      do {
        uVar11 = uVar9;
        if (uVar9 <= uVar6) {
          uVar11 = uVar6;
        }
        uVar8 = uVar12;
        if (uVar12 <= uVar6) {
          uVar8 = uVar6;
        }
        local_14 = local_14 +
                   ((1 << ((char)uVar8 + (char)uVar11 + (char)uVar4 & 0x1fU)) * uVar3 >> 3);
        if (uVar9 != 0) {
          uVar9 = uVar9 - 1;
        }
        if (uVar12 != 0) {
          uVar12 = uVar12 - 1;
        }
        if (uVar4 != 0) {
          uVar4 = uVar4 - 1;
        }
        param_1 = param_1 + -1;
      } while (param_1 != 0);
    }
    uVar11 = uVar9;
    if (uVar9 <= uVar6) {
      uVar11 = uVar6;
    }
    uVar8 = uVar12;
    if (uVar12 <= uVar6) {
      uVar8 = uVar6;
    }
    bVar1 = *(byte *)(iVar2 + 0xd);
    bVar5 = (byte)uVar11;
    if (bVar1 == 0xc) {
      uVar6 = (1 << (bVar5 & 0x1f)) << 1;
    }
    else if ((bVar1 < 0xe) || (0xf < bVar1)) {
      uVar6 = (1 << (bVar5 & 0x1f)) * uVar3 >> 3;
    }
    else {
      uVar6 = (1 << (bVar5 & 0x1f)) << 2;
    }
    *param_7 = ((uVar4 << 4 | uVar12) << 4 | uVar9) << 0x14 | *(uint *)(iVar2 + 0xc) & 0xfffff;
    *param_8 = *(undefined4 *)(iVar2 + 0x10);
    uVar4 = (1 << ((char)uVar8 + bVar5 & 0x1f)) * uVar3 >> 3;
  }
  else {
    *param_7 = *(uint *)(param_1 + 0xc);
    uVar6 = ((uVar4 >> 0x18) + 1) * 0x40;
    uVar4 = ((uVar4 >> 0xc & 0xfff) + 1) * uVar6;
    *param_8 = *(undefined4 *)(param_1 + 0x10);
  }
  *param_4 = local_14;
  *param_5 = uVar6;
  *param_6 = uVar4;
  return;
}



void D3D8::Lock2DSurface(D3DPixelContainer *pPixelContainer,D3DCUBEMAP_FACES FaceType,UINT Level,
                        D3DLOCKED_RECT *pLockedRect,RECT *pRect,DWORD Flags)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  D3DPixelContainer *pDVar4;
  DWORD DVar5;
  undefined1 local_4 [4];
  
  DVar5 = Flags;
  pDVar4 = pPixelContainer;
  if ((Flags & 0x20) == 0) {
    D3D_BlockOnResource(&pPixelContainer->resource);
  }
  FUN_0017b300(pDVar4,FaceType,Level,&Flags,&pPixelContainer,local_4,&FaceType,&Level);
  if ((DVar5 & 0x40) != 0) {
    Flags = Flags | 0xf0000000;
  }
  if (pRect != (RECT *)0x0) {
    bVar1 = (&DAT_0017f958)[*(byte *)((int)&pDVar4->Format + 1)];
    iVar2 = pRect->y1;
    iVar3 = pRect->x1;
    pLockedRect->Pitch = (INT)pPixelContainer;
    pLockedRect->pBits =
         (void *)(Flags + ((bVar1 & 0x3c) * iVar3 >> 3) + iVar2 * (int)pPixelContainer);
    return;
  }
  pLockedRect->Pitch = (INT)pPixelContainer;
  pLockedRect->pBits = (void *)Flags;
  return;
}



int FUN_0017b5d0(int param_1,int param_2,undefined4 param_3,uint param_4,uint param_5,uint param_6,
                int param_7,int param_8,uint *param_9,uint *param_10)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined8 uVar11;
  int local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  local_14 = 0;
  uVar3 = (byte)(&DAT_0017f958)[param_5] & 0x3c;
  if (((((&DAT_0017f958)[param_5] & 1) == 0) && (param_5 != 0xc)) &&
     (((int)param_5 < 0xe || (0xf < (int)param_5)))) {
    uVar2 = 0;
    local_10 = 0;
    local_c = 0;
    if (param_4 == 0) {
      param_4 = 1;
    }
    if (param_6 == 0) {
      param_6 = (uVar3 * param_1 >> 3) + 0x3f & 0xffffffc0;
    }
    local_8 = param_2;
    local_14 = param_2 * param_6;
  }
  else {
    local_c = FUN_0017ae00();
    local_10 = FUN_0017ae00();
    uVar11 = FUN_0017ae00();
    uVar10 = (uint)((ulonglong)uVar11 >> 0x20);
    uVar2 = (uint)uVar11;
    bVar1 = 0;
    local_8 = 0;
    if ((param_5 == 0xc) || ((0xd < (int)param_5 && ((int)param_5 < 0x10)))) {
      bVar1 = 1;
    }
    uVar4 = -(uint)bVar1 & 2;
    uVar9 = local_c;
    uVar5 = param_4;
    if (param_4 == 0) {
      uVar7 = uVar10;
      if (uVar10 <= uVar2) {
        uVar7 = uVar2;
      }
      uVar5 = local_c;
      if ((local_c <= uVar7) && (uVar5 = uVar10, uVar10 <= uVar2)) {
        uVar5 = uVar2;
      }
      uVar5 = uVar5 + 1;
      param_4 = uVar5;
    }
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
      uVar7 = (uint)((ulonglong)uVar11 >> 0x20);
      iVar8 = (int)uVar11;
      uVar10 = uVar4;
      if (uVar4 < uVar9) {
        uVar10 = uVar9;
      }
      uVar6 = uVar4;
      if (uVar4 < uVar7) {
        uVar6 = uVar7;
      }
      local_14 = local_14 +
                 ((1 << ((char)uVar6 + (char)uVar10 + (char)uVar11 & 0x1fU)) * uVar3 >> 3);
      if (uVar9 != 0) {
        uVar9 = uVar9 - 1;
      }
      if (uVar7 != 0) {
        uVar7 = uVar7 - 1;
      }
      if (iVar8 != 0) {
        iVar8 = iVar8 + -1;
      }
      uVar11 = CONCAT44(uVar7,iVar8);
    }
    param_1 = 0;
    if (param_7 != 0) {
      local_14 = (local_14 + 0x7fU & 0xffffff80) * 6;
    }
  }
  *param_9 = (((((uVar2 << 4 | local_10) << 4 | local_c) << 4 | param_4) << 8 | param_5) << 4 |
             (param_8 != 0) + 2) << 4 | -(uint)(param_7 != 0) & 4 | 9;
  if (param_1 == 0) {
    *param_10 = 0;
    return local_14;
  }
  *param_10 = (((param_6 >> 6) - 1) * 0x1000 | local_8 - 1U) << 0xc | param_1 - 1U;
  return local_14;
}




int D3D8::CMiniport_GetDisplayCapabilities(void)

{
  if (DAT_00181958 == 0) {
    AvSendTVEncoderOption((PVOID)0x0,6,0,(PULONG)&DAT_00181958);
  }
  return DAT_00181958;
}




undefined4 __fastcall D3D8::CMiniport_IsFlipPending(int param_1)

{
  return *(undefined4 *)(param_1 + ((*(uint *)(param_1 + 0x1bc) & 1) * 3 + 0x5d) * 4);
}




bool __thiscall D3D__Device::CMiniport_InitHardware(D3D__Device *this)

{
  int *piVar1;
  BOOLEAN BVar2;
  undefined1 uVar3;
  int iVar4;
  ULONG Vector;
  uint uVar5;
  BOOL BVar6;
  undefined1 *puVar7;
  KIRQL local_14 [4];
  int local_10;
  undefined1 local_c [3];
  byte local_9;
  undefined1 *local_8;
  
  KeInitializeDpc((KDPC *)&this->field_0x84,FUN_0017c4b0,this);
  piVar1 = &this->field386_0x1ac;
  this->field387_0x1b0 = (int)piVar1;
  *piVar1 = (int)piVar1;
  piVar1 = &this->field379_0x19c;
  this->field381_0x1a4 = 0;
  this->field383_0x1a6 = 4;
  this->field385_0x1a8 = 1;
  this->field374_0x194 = 0;
  this->field376_0x196 = 4;
  this->field378_0x198 = 1;
  this->field380_0x1a0 = (int)piVar1;
  *piVar1 = (int)piVar1;
  iVar4 = FUN_0017c671();
  if ((iVar4 != 0) && (iVar4 = FUN_0017c69c(), iVar4 != 0)) {
    Vector = HalGetInterruptVector(3,local_14);
    KeInitializeInterrupt
              ((PKINTERRUPT)&this->field_0x14,FUN_0017bb00,this,Vector,local_14[0],LevelSensitive,
               '\x01');
    BVar2 = KeConnectInterrupt((PKINTERRUPT)&this->field_0x14);
    if (BVar2 != '\0') {
      this->field333_0x168 = 0;
      this->field332_0x164 = &LAB_0017bf40;
      HalRegisterShutdownNotification((PHAL_SHUTDOWN_REGISTRATION)&this->field332_0x164,'\x01');
      iVar4 = FUN_0017c6dd();
      if (iVar4 != 0) {
        local_8 = &this->field_0x2dc;
        local_10 = 2;
        do {
          uVar5 = 0;
          do {
            puVar7 = local_8 + uVar5;
            uVar3 = (undefined1)uVar5;
            puVar7[-0x100] = uVar3;
            *puVar7 = uVar3;
            puVar7[0x100] = uVar3;
            uVar5 = uVar5 + 1;
          } while (uVar5 < 0x100);
          local_8 = local_8 + 0x300;
          local_10 = local_10 + -1;
        } while (local_10 != 0);
        out(0x80c0,1);
        HalReadWritePCISpace(1,0,0x4c,local_c,4,'\0');
        local_9 = local_9 | 0x1f;
        HalReadWritePCISpace(1,0,0x4c,local_c,4,'\x01');
        this->field145_0xa0 = 1;
        BVar6 = FUN_0017c760(this);
        return BVar6 != 0;
      }
    }
  }
  return false;
}



undefined4 __thiscall
FUN_0017ccc6(int *param_1,uint param_2,uint param_3,int param_4,undefined4 param_5,uint param_6,
            uint param_7,uint param_8)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  undefined4 local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  int local_14;
  uint local_10;
  int *local_c;
  int local_8;
  
  iVar1 = *param_1;
  local_c = param_1;
  FUN_0017c9b1(&local_24);
  local_18 = param_6 & 1;
  local_10 = param_2 * 4 + 0x10 & 0x1ffc | 0xea0000;
  local_1c = param_2 * 4 + 0x30 & 0x1ffc | 0xea0000;
  local_14 = (param_3 - 1) + param_4;
  puVar2 = (uint *)((param_2 + 0x10024) * 0x10 + iVar1);
  puVar3 = (uint *)((param_2 + 0x40090) * 0x10 + iVar1);
  local_20 = param_2 * 4 + 0x50 & 0x1ffc | 0xea0000;
  local_8 = param_2 * 0x10 + iVar1;
  do {
    FUN_0017e5ce();
    *(int *)(local_8 + 0x100244) = local_14;
    *(undefined4 *)(local_8 + 0x100248) = param_5;
    *(int *)(&DAT_00400904 + local_8) = local_14;
    *(undefined4 *)(&DAT_00400908 + local_8) = param_5;
    if (local_18 == 0) {
      uVar4 = param_3 | 1;
    }
    else {
      uVar4 = param_3 | 3;
    }
    *puVar3 = uVar4;
    *puVar2 = uVar4;
    *(uint *)(&DAT_00400750 + iVar1) = local_10;
    *(uint *)(&DAT_00400754 + iVar1) = uVar4;
    *(uint *)(&DAT_00400750 + iVar1) = local_1c;
    *(int *)(&DAT_00400754 + iVar1) = local_14;
    *(uint *)(&DAT_00400750 + iVar1) = local_20;
    *(undefined4 *)(&DAT_00400754 + iVar1) = param_5;
  } while (((*puVar2 != *puVar3) ||
           (*(int *)(local_8 + 0x100248) != *(int *)(&DAT_00400908 + local_8))) ||
          (((*(uint *)(&DAT_00400904 + local_8) ^ *(uint *)(local_8 + 0x100244)) & 0xffffc000) != 0)
          );
  if ((param_6 & 0x80000000) != 0) {
    param_3 = param_7 >> 2 | 0x80000000;
    if ((param_6 & 0x4000000) != 0) {
      param_3 = param_7 >> 2 | 0x84000000;
    }
    puVar2 = (uint *)(iVar1 + 0x100300 + param_2 * 4);
    do {
      FUN_0017e5ce();
      *puVar2 = param_3;
      *(uint *)(&DAT_00400980 + param_2 * 4 + iVar1) = param_3;
      *(uint *)(&DAT_00400750 + iVar1) = param_2 * 4 + 0x90 & 0x1ffc | 0xea0000;
      *(uint *)(&DAT_00400754 + iVar1) = param_3;
    } while (*puVar2 != *(uint *)(&DAT_00400980 + param_2 * 4 + iVar1));
    if (param_8 != 0) {
      uVar4 = param_2 | param_8 | 0x80000000;
      do {
        FUN_0017e5ce();
        *(uint *)(iVar1 + 0x100324) = uVar4;
        *(uint *)(&DAT_004009a0 + iVar1) = uVar4;
      } while (*(uint *)(iVar1 + 0x100324) != *(uint *)(&DAT_004009a0 + iVar1));
    }
  }
  *(undefined4 *)(iVar1 + 0x3220) = local_24;
  return 1;
}




void D3D::Direct3D_SetPushBufferSize(DWORD PushBufferSize,DWORD KickOffSize)

{
  Graphics::DXPushBufferSize = PushBufferSize;
  Graphics::DXPushBufferSize = KickOffSize;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

HRESULT D3D8::Direct3D_CreateDevice
                  (UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,
                  D3DPRESENT_PARAMETERS *pPresentationParameters,
                  IDirect3DDevice8 **ppReturnedDeviceInterface)

{
  int iVar1;
  int i;
  void *pDVar2;
  
  if (Graphics::DXPushBufferSize == 0) {
    Graphics::DXPushBufferSize = 0x80000;
  }
  if (Graphics::DXPushBufferSize == 0) {
    Graphics::DXPushBufferSize = 0x8000;
  }
  D3D::D3D__Device.bitField1 = D3D::D3D__Device.bitField1 | BehaviorFlags & 0b00010000;
  D3D_g_pDevice = &D3D::D3D__Device;
  D3D::D3D__Device.flag1 = 1;
  iVar1 = D3D__Device::D3D__Device(&D3D::D3D__Device,&pPresentationParameters->BackBufferWidth);
  if (iVar1 < 0) {
    FUN_0017ac50(&D3D::D3D__Device);
    if (ppReturnedDeviceInterface != (IDirect3DDevice8 **)0x0) {
      *ppReturnedDeviceInterface = (IDirect3DDevice8 *)0x0;
    }
    pDVar2 = &D3D::D3D__Device;
    for (i = 0x924; i != 0; i = i + -1) {
      *(undefined4 *)pDVar2 = 0;
      pDVar2 = (void *)((int)pDVar2 + 4);
    }
    D3D_g_pDevice = (D3D__Device *)0x0;
    return iVar1;
  }
  if (ppReturnedDeviceInterface != (IDirect3DDevice8 **)0x0) {
    *ppReturnedDeviceInterface = (IDirect3DDevice8 *)&D3D::D3D__Device;
  }
  return 0;
}




D3DXVECTOR3 * D3DX8::D3DXVec3TransformNormal(D3DXVECTOR3 *pOut,D3DXVECTOR3 *pV,D3DXVECTOR3 *pM)

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
  
  fVar1 = pV->x;
  fVar2 = pM->y;
  fVar3 = pV->x;
  fVar4 = pM->z;
  fVar5 = pV->y;
  fVar6 = pM[1].z;
  fVar7 = pV->y;
  fVar8 = pM[2].x;
  fVar9 = pV->z;
  fVar10 = pM[3].x;
  fVar11 = pV->z;
  fVar12 = pM[3].y;
  pOut->x = pV->z * pM[2].z + pV->y * pM[1].y + pV->x * pM->x;
  pOut->y = fVar9 * fVar10 + fVar5 * fVar6 + fVar1 * fVar2;
  pOut->z = fVar11 * fVar12 + fVar7 * fVar8 + fVar3 * fVar4;
  return pOut;
}




float * D3DX8::D3DXVec4Transform(float *param_1,float *param_2,float *param_3)

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
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  
  fVar1 = *param_2;
  fVar2 = param_3[2];
  fVar3 = *param_2;
  fVar4 = param_3[1];
  fVar5 = *param_2;
  fVar6 = param_3[3];
  fVar7 = param_2[1];
  fVar8 = param_3[6];
  fVar9 = param_2[1];
  fVar10 = param_3[5];
  fVar11 = param_2[1];
  fVar12 = param_3[7];
  fVar13 = param_2[2];
  fVar14 = param_3[10];
  fVar15 = param_2[2];
  fVar16 = param_3[9];
  fVar17 = param_2[2];
  fVar18 = param_3[0xb];
  fVar19 = param_2[3];
  fVar20 = param_3[0xe];
  fVar21 = param_2[3];
  fVar22 = param_3[0xd];
  fVar23 = param_2[3];
  fVar24 = param_3[0xf];
  *param_1 = param_2[3] * param_3[0xc] +
             param_2[2] * param_3[8] + param_2[1] * param_3[4] + *param_2 * *param_3;
  param_1[1] = fVar21 * fVar22 + fVar15 * fVar16 + fVar9 * fVar10 + fVar3 * fVar4;
  param_1[2] = fVar19 * fVar20 + fVar13 * fVar14 + fVar7 * fVar8 + fVar1 * fVar2;
  param_1[3] = fVar23 * fVar24 + fVar17 * fVar18 + fVar11 * fVar12 + fVar5 * fVar6;
  return param_1;
}




void D3DX8::D3DXMatrixTranspose(D3DMATRIX *pOut,D3DMATRIX *pM)

{
  float fVar1;
  
  fVar1 = pM->m[0][1];
  pOut->m[0][1] = pM->m[1][0];
  pOut->m[1][0] = fVar1;
  fVar1 = pM->m[0][2];
  pOut->m[0][2] = pM->m[2][0];
  pOut->m[2][0] = fVar1;
  fVar1 = pM->m[0][3];
  pOut->m[0][3] = pM->m[3][0];
  pOut->m[3][0] = fVar1;
  fVar1 = pM->m[1][2];
  pOut->m[1][2] = pM->m[2][1];
  pOut->m[2][1] = fVar1;
  fVar1 = pM->m[1][3];
  pOut->m[1][3] = pM->m[3][1];
  pOut->m[3][1] = fVar1;
  fVar1 = pM->m[2][3];
  pOut->m[2][3] = pM->m[3][2];
  pOut->m[3][2] = fVar1;
  if (pOut != pM) {
    pOut->m[0][0] = pM->m[0][0];
    pOut->m[1][1] = pM->m[1][1];
    pOut->m[2][2] = pM->m[2][2];
    pOut->m[3][3] = pM->m[3][3];
  }
  return;
}




void D3DX8::D3DXMatrixInverse(float *param_1,float *param_2,float *param_3)

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
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  int iVar32;
  
  fVar3 = param_3[4];
  fVar1 = *param_3;
  fVar2 = param_3[1];
  fVar4 = param_3[5];
  fVar5 = param_3[8];
  fVar6 = param_3[9];
  fVar7 = param_3[0xc];
  fVar19 = fVar4 * fVar1 - fVar3 * fVar2;
  fVar8 = param_3[0xd];
  fVar9 = param_3[0xe];
  fVar10 = param_3[0xf];
  fVar18 = fVar6 * fVar1 - fVar5 * fVar2;
  fVar17 = fVar8 * fVar1 - fVar7 * fVar2;
  fVar20 = fVar6 * fVar3 - fVar5 * fVar4;
  fVar21 = fVar8 * fVar3 - fVar7 * fVar4;
  fVar22 = fVar8 * fVar5 - fVar7 * fVar6;
  fVar1 = param_3[2];
  fVar2 = param_3[3];
  fVar3 = param_3[6];
  fVar4 = param_3[7];
  fVar5 = param_3[10];
  fVar6 = param_3[0xb];
  fVar31 = fVar1 * fVar4 - fVar3 * fVar2;
  fVar30 = fVar1 * fVar6 - fVar5 * fVar2;
  fVar23 = fVar1 * fVar10 - fVar9 * fVar2;
  fVar11 = *param_3;
  fVar12 = param_3[4];
  fVar13 = param_3[8];
  fVar28 = fVar3 * fVar6 - fVar5 * fVar4;
  fVar14 = param_3[9];
  fVar29 = fVar3 * fVar10 - fVar9 * fVar4;
  fVar15 = param_3[0xc];
  fVar26 = fVar5 * fVar10 - fVar9 * fVar6;
  fVar7 = param_3[1];
  fVar8 = param_3[5];
  fVar16 = param_3[0xd];
  fVar27 = (fVar30 * fVar8 - fVar31 * fVar14) - fVar28 * fVar7;
  fVar24 = fVar31 * fVar16 + (fVar29 * fVar7 - fVar23 * fVar8);
  fVar25 = (fVar23 * fVar14 - fVar30 * fVar16) - fVar26 * fVar7;
  fVar7 = fVar28 * fVar16 + (fVar26 * fVar8 - fVar29 * fVar14);
  fVar8 = fVar7 * fVar11 + fVar25 * fVar12 + fVar24 * fVar13 + fVar27 * fVar15;
  if (param_2 != (float *)0x0) {
    *param_2 = fVar8;
  }
  fVar8 = 1.0 / fVar8;
  iVar32 = FUN_0016744d((double)fVar8);
  if (iVar32 != 0) {
    *param_1 = fVar7 * fVar8;
    param_1[1] = fVar25 * fVar8;
    param_1[2] = fVar24 * fVar8;
    param_1[3] = fVar27 * fVar8;
    param_1[4] = ((fVar29 * fVar13 - fVar28 * fVar15) - fVar26 * fVar12) * fVar8;
    param_1[5] = (fVar30 * fVar15 + (fVar11 * fVar26 - fVar23 * fVar13)) * fVar8;
    param_1[6] = ((fVar23 * fVar12 - fVar31 * fVar15) - fVar29 * fVar11) * fVar8;
    param_1[7] = (fVar31 * fVar13 + (fVar28 * fVar11 - fVar30 * fVar12)) * fVar8;
    param_1[8] = (fVar20 * fVar10 + (fVar22 * fVar4 - fVar21 * fVar6)) * fVar8;
    param_1[9] = ((fVar17 * fVar6 - fVar18 * fVar10) - fVar22 * fVar2) * fVar8;
    param_1[10] = (fVar19 * fVar10 + (fVar21 * fVar2 - fVar17 * fVar4)) * fVar8;
    param_1[0xb] = ((fVar18 * fVar4 - fVar19 * fVar6) - fVar20 * fVar2) * fVar8;
    param_1[0xc] = ((fVar5 * fVar21 - fVar9 * fVar20) - fVar3 * fVar22) * fVar8;
    param_1[0xd] = (fVar9 * fVar18 + (fVar1 * fVar22 - fVar5 * fVar17)) * fVar8;
    param_1[0xe] = ((fVar3 * fVar17 - fVar9 * fVar19) - fVar1 * fVar21) * fVar8;
    param_1[0xf] = (fVar5 * fVar19 + (fVar1 * fVar20 - fVar3 * fVar18)) * fVar8;
  }
  return;
}




void D3DX8::D3DXMatrixScaling(D3DXMATRIX *param_1,float x,float y,float z)

{
  param_1->m[3][2] = 0.0;
  param_1->m[0][0] = x;
  param_1->m[3][1] = 0.0;
  param_1->m[1][1] = y;
  param_1->m[3][0] = 0.0;
  param_1->m[2][2] = z;
  param_1->m[2][3] = 0.0;
  param_1->m[2][1] = 0.0;
  param_1->m[2][0] = 0.0;
  param_1->m[1][3] = 0.0;
  param_1->m[1][2] = 0.0;
  param_1->m[1][0] = 0.0;
  param_1->m[0][3] = 0.0;
  param_1->m[0][2] = 0.0;
  param_1->m[0][1] = 0.0;
  param_1->m[3][3] = 1.0;
  return;
}




void D3DX8::D3DXMatrixTranslation(D3DXMATRIX *param_1,float x,float y,float z)

{
  param_1->m[2][3] = 0.0;
  param_1->m[3][0] = x;
  param_1->m[2][1] = 0.0;
  param_1->m[3][1] = y;
  param_1->m[2][0] = 0.0;
  param_1->m[3][2] = z;
  param_1->m[1][3] = 0.0;
  param_1->m[1][2] = 0.0;
  param_1->m[1][0] = 0.0;
  param_1->m[0][3] = 0.0;
  param_1->m[0][2] = 0.0;
  param_1->m[0][1] = 0.0;
  param_1->m[3][3] = 1.0;
  param_1->m[2][2] = 1.0;
  param_1->m[1][1] = 1.0;
  param_1->m[0][0] = 1.0;
  return;
}




void D3DX8::D3DXMatrixRotationX(D3DXMATRIX *matrix,float angle)

{
  float10 fVar2;
  float10 fVar1;
  
  fVar1 = (float10)fcos((float10)angle);
  fVar2 = (float10)fsin((float10)angle);
  matrix->m[0][0] = 1.0;
  matrix->m[0][1] = 0.0;
  matrix->m[1][2] = (float)fVar2;
  matrix->m[0][2] = 0.0;
  matrix->m[0][3] = 0.0;
  matrix->m[1][0] = 0.0;
  matrix->m[1][1] = (float)fVar1;
  matrix->m[1][3] = 0.0;
  matrix->m[2][0] = 0.0;
  matrix->m[2][1] = -(float)fVar2;
  matrix->m[2][2] = (float)fVar1;
  matrix->m[2][3] = 0.0;
  matrix->m[3][0] = 0.0;
  matrix->m[3][1] = 0.0;
  matrix->m[3][2] = 0.0;
  matrix->m[3][3] = 1.0;
  return;
}




void D3DX8::D3DXMatrixRotationY(float *param_1,float param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_2);
  fVar2 = (float10)fsin((float10)param_2);
  *param_1 = (float)fVar1;
  param_1[1] = 0.0;
  param_1[2] = -(float)fVar2;
  param_1[3] = 0.0;
  param_1[4] = 0.0;
  param_1[5] = 1.0;
  param_1[6] = 0.0;
  param_1[7] = 0.0;
  param_1[8] = (float)fVar2;
  param_1[9] = 0.0;
  param_1[10] = (float)fVar1;
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[0xf] = 1.0;
  return;
}




void D3DX8::D3DXMatrixRotationZ(float *param_1,float param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)param_2);
  fVar2 = (float10)fsin((float10)param_2);
  *param_1 = (float)fVar1;
  param_1[1] = (float)fVar2;
  param_1[2] = 0.0;
  param_1[3] = 0.0;
  param_1[4] = -(float)fVar2;
  param_1[5] = (float)fVar1;
  param_1[6] = 0.0;
  param_1[7] = 0.0;
  param_1[8] = 0.0;
  param_1[9] = 0.0;
  param_1[10] = 1.0;
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[0xf] = 1.0;
  return;
}




void D3DX8::D3DXMatrixRotationQuaternion(float *param_1,float *param_2)

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
  
  fVar1 = *param_2;
  fVar10 = param_2[1] * 2.0;
  fVar11 = param_2[2] * 2.0;
  fVar12 = fVar1 * 2.0 * param_2[3];
  fVar2 = param_2[3];
  fVar3 = param_2[3];
  fVar4 = *param_2;
  fVar5 = *param_2;
  fVar6 = *param_2;
  fVar7 = param_2[1];
  fVar8 = param_2[1];
  fVar9 = param_2[2];
  *param_1 = (1.0 - fVar10 * fVar7) - fVar11 * fVar9;
  param_1[1] = fVar10 * fVar5 + fVar11 * fVar3;
  param_1[2] = fVar11 * fVar6 - fVar10 * fVar2;
  param_1[3] = 0.0;
  param_1[4] = fVar10 * fVar5 - fVar11 * fVar3;
  fVar1 = 1.0 - fVar1 * 2.0 * fVar4;
  param_1[5] = fVar1 - fVar11 * fVar9;
  param_1[6] = fVar11 * fVar8 + fVar12;
  param_1[7] = 0.0;
  param_1[8] = fVar11 * fVar6 + fVar10 * fVar2;
  param_1[9] = fVar11 * fVar8 - fVar12;
  param_1[10] = fVar1 - fVar10 * fVar7;
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[0xf] = 1.0;
  return;
}




void D3DX8::D3DXMatrixPerspectiveFovLH(D3DXMATRIX *pOut,float fovy,float Aspect,float zn,float zf)

{
  float10 fVar1;
  float fVar2;
  float10 fVar3;
  
  fVar1 = (float10)fcos((float10)(fovy * 0.5));
  fVar3 = (float10)fsin((float10)(fovy * 0.5));
  pOut->m[0][0] = ((float)fVar1 / (float)fVar3) / Aspect;
  pOut->m[0][1] = 0.0;
  pOut->m[0][2] = 0.0;
  pOut->m[0][3] = 0.0;
  pOut->m[1][0] = 0.0;
  pOut->m[1][1] = (float)fVar1 / (float)fVar3;
  pOut->m[1][2] = 0.0;
  pOut->m[1][3] = 0.0;
  pOut->m[2][0] = 0.0;
  pOut->m[2][1] = 0.0;
  fVar2 = zf / (zf - zn);
  pOut->m[2][2] = fVar2;
  pOut->m[2][3] = 1.0;
  pOut->m[3][0] = 0.0;
  pOut->m[3][1] = 0.0;
  pOut->m[3][2] = -(fVar2 * zn);
  pOut->m[3][3] = 0.0;
  return;
}




void D3DX8::D3DXVec3Normalize(vec3 *outNorm,vec3 *v)

{
  float fVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_10 [12];
  
  fVar3 = (float10)FUN_00184f05(v);
  fVar1 = (float)fVar3;
  iVar2 = FUN_00184600(fVar1,0x3f800000);
  if (iVar2 == 0) {
    if (fVar1 <= 9.9999994e-11) {
      outNorm->x = 0.0;
      outNorm->y = 0.0;
      outNorm->z = 0.0;
      return;
    }
    v = (vec3 *)FUN_00184edd(local_10,SQRT(fVar1));
  }
  else if (outNorm == v) {
    return;
  }
  outNorm->x = v->x;
  outNorm->y = v->y;
  outNorm->z = v->z;
  return;
}



// Transform ignoring the w component


D3DXVECTOR3 * D3DX8::D3DXVec3TransformCoord(D3DXVECTOR3 *pOut,D3DXVECTOR3 *pV,D3DXVECTOR3 *pM)

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
  int iVar16;
  
  fVar1 = pV->x;
  fVar2 = pM->z;
  fVar3 = pV->x;
  fVar4 = pM->y;
  fVar5 = pV->y;
  fVar6 = pM[2].x;
  fVar7 = pV->y;
  fVar8 = pM[1].z;
  fVar9 = pV->z;
  fVar10 = pM[3].y;
  fVar11 = pV->z;
  fVar12 = pM[3].x;
  fVar13 = pM[4].y;
  fVar14 = pM[4].z;
  fVar15 = pM[5].x + pV->z * pM[3].z + pV->y * pM[2].y + pV->x * pM[1].x;
  pOut->x = pM[4].x + pV->z * pM[2].z + pV->y * pM[1].y + pV->x * pM->x;
  pOut->y = fVar13 + fVar11 * fVar12 + fVar7 * fVar8 + fVar3 * fVar4;
  pOut->z = fVar14 + fVar9 * fVar10 + fVar5 * fVar6 + fVar1 * fVar2;
  iVar16 = FUN_00184600(fVar15,0x3f800000);
  if (iVar16 == 0) {
    FUN_00184ebe(fVar15);
  }
  return pOut;
}




D3DXMATRIX * D3DX8::D3DXMatrixMultiply(D3DXMATRIX *pOut,D3DXMATRIX *pM1,D3DXMATRIX *pM2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  D3DXMATRIX *pDVar5;
  int iVar6;
  int iVar7;
  D3DXMATRIX *pDVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  D3DXMATRIX local_44;
  
  pDVar5 = pOut;
  if (pM2 == pOut) {
    if (pM1 != pOut) {
      iVar7 = -4;
      do {
        iVar6 = -0x10;
        fVar9 = (float10)*(float *)((int)pM2 + iVar7 * 4 + 0x10);
        fVar10 = (float10)*(float *)((int)pM2 + iVar7 * 4 + 0x20);
        fVar11 = (float10)*(float *)((int)pM2 + iVar7 * 4 + 0x30);
        fVar12 = (float10)*(float *)((int)pM2 + iVar7 * 4 + 0x40);
        do {
          *(float *)((int)pOut + iVar6 * 4 + 0x40) =
               (float)(fVar12 * (float10)*(float *)((int)pM1 + iVar6 * 4 + 0x4c) +
                       fVar10 * (float10)*(float *)((int)pM1 + iVar6 * 4 + 0x44) +
                      fVar9 * (float10)*(float *)((int)pM1 + iVar6 * 4 + 0x40) +
                      fVar11 * (float10)*(float *)((int)pM1 + iVar6 * 4 + 0x48));
          iVar6 = iVar6 + 4;
        } while (iVar6 != 0);
        ffree(fVar9);
        ffree(fVar10);
        ffree(fVar11);
        ffree(fVar12);
        pOut = (D3DXMATRIX *)(pOut->m[0] + 1);
        iVar7 = iVar7 + 1;
      } while (iVar7 != 0);
      return pDVar5;
    }
    pDVar8 = &local_44;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pDVar8->m[0][0] = pM2->m[0][0];
      pM2 = (D3DXMATRIX *)(pM2->m[0] + 1);
      pDVar8 = (D3DXMATRIX *)((int)pDVar8 + 4);
    }
    pM2 = &local_44;
  }
  iVar7 = -4;
  do {
    iVar6 = -4;
    fVar1 = pM1->m[0][0];
    fVar2 = pM1->m[0][1];
    fVar3 = pM1->m[0][2];
    fVar4 = pM1->m[0][3];
    do {
      *(float *)((int)pOut + iVar6 * 4 + 0x10) =
           (float)((float10)fVar4 * (float10)*(float *)((int)pM2 + iVar6 * 4 + 0x40) +
                   (float10)fVar2 * (float10)*(float *)((int)pM2 + iVar6 * 4 + 0x20) +
                  (float10)fVar1 * (float10)*(float *)((int)pM2 + iVar6 * 4 + 0x10) +
                  (float10)fVar3 * (float10)*(float *)((int)pM2 + iVar6 * 4 + 0x30));
      iVar6 = iVar6 + 1;
    } while (iVar6 != 0);
    ffree((float10)fVar1);
    ffree((float10)fVar2);
    ffree((float10)fVar3);
    ffree((float10)fVar4);
    pM1 = (D3DXMATRIX *)(pM1->m + 1);
    pOut = (D3DXMATRIX *)(pOut->m + 1);
    iVar7 = iVar7 + 1;
  } while (iVar7 != 0);
  return pDVar5;
}




void D3DX8::D3DXMatrixLookAtLH(D3DXMATRIX *pOut,D3DXVECTOR3 *pEye,undefined4 pAt,undefined4 pUp)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float local_28;
  float local_24;
  float local_20;
  vec3 local_1c;
  vec3 local_10;
  
  FUN_00184f74(&local_10,pAt,pEye);
  D3DXVec3Normalize(&local_10,&local_10);
  FUN_00184f28(&local_1c,pUp,&local_10);
  D3DXVec3Normalize(&local_1c,&local_1c);
  FUN_00184f28(&local_28,&local_10,&local_1c);
  pOut->m[0][0] = local_1c.x;
  pOut->m[1][0] = local_1c.y;
  pOut->m[2][0] = local_1c.z;
  fVar1 = pEye->x;
  fVar2 = pEye->z;
  fVar3 = pEye->y;
  pOut->m[0][1] = local_28;
  pOut->m[1][1] = local_24;
  pOut->m[2][1] = local_20;
  pOut->m[3][0] = -(local_1c.y * fVar3 + local_1c.z * fVar2 + local_1c.x * fVar1);
  fVar1 = pEye->x;
  fVar2 = pEye->z;
  fVar3 = pEye->y;
  pOut->m[0][2] = local_10.x;
  pOut->m[1][2] = local_10.y;
  pOut->m[2][2] = local_10.z;
  pOut->m[3][1] = -(local_24 * fVar3 + local_20 * fVar2 + local_28 * fVar1);
  pOut->m[3][2] = -(local_10.y * pEye->y + local_10.z * pEye->z + local_10.x * pEye->x);
  pOut->m[0][3] = 0.0;
  pOut->m[1][3] = 0.0;
  pOut->m[2][3] = 0.0;
  pOut->m[3][3] = 1.0;
  return;
}




void D3DX8::D3DXPlaneNormalize(float *param_1,float *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = param_2[2] * param_2[2] + param_2[1] * param_2[1] + *param_2 * *param_2;
  iVar2 = FUN_00184600(fVar1,0x3f800000);
  if (iVar2 == 0) {
    if (fVar1 <= 9.9999994e-11) {
      *param_1 = 0.0;
      param_1[1] = 0.0;
      param_1[2] = 0.0;
      fVar1 = 0.0;
    }
    else {
      fVar1 = 1.0 / SQRT(fVar1);
      *param_1 = fVar1 * *param_2;
      param_1[1] = fVar1 * param_2[1];
      param_1[2] = fVar1 * param_2[2];
      fVar1 = fVar1 * param_2[3];
    }
    param_1[3] = fVar1;
  }
  else if (param_1 != param_2) {
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
    param_1[3] = param_2[3];
  }
  return;
}



D3DXPlane *

D3DX8::D3DXPlaneFromPointNormal(D3DXPlane *pOut,D3DXVECTOR3 *pPoint,D3DXVECTOR3 *pNormal)

{
  (pOut->normal).x = pNormal->x;
  (pOut->normal).y = pNormal->y;
  (pOut->normal).z = pNormal->z;
  pOut->c = -(pPoint->x * pNormal->x + pPoint->z * pNormal->z + pPoint->y * pNormal->y);
  return pOut;
}




D3DXMATRIX * D3DX8::D3DXMatrixReflect(D3DXMATRIX *pOut,D3DXPlane *pPlane)

{
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float fVar1;
  float fVar2;
  float fVar3;
  
  D3DXPlaneNormalize(&local_14,pPlane);
  fVar1 = local_14 * -2.0;
  fVar3 = local_10 * -2.0;
  fVar2 = local_c * -2.0;
  pOut->m[0][0] = local_14 * fVar1 + 1.0;
  pOut->m[0][1] = fVar3 * local_14;
  pOut->m[0][2] = fVar2 * local_14;
  pOut->m[0][3] = 0.0;
  pOut->m[1][0] = local_10 * fVar1;
  pOut->m[1][1] = local_10 * fVar3 + 1.0;
  pOut->m[1][2] = fVar2 * local_10;
  pOut->m[1][3] = 0.0;
  pOut->m[2][0] = local_c * fVar1;
  pOut->m[2][1] = local_c * fVar3;
  pOut->m[2][2] = local_c * fVar2 + 1.0;
  pOut->m[2][3] = 0.0;
  pOut->m[3][0] = local_8 * fVar1;
  pOut->m[3][1] = local_8 * fVar3;
  pOut->m[3][2] = local_8 * fVar2;
  pOut->m[3][3] = 1.0;
  return pOut;
}




int XGRAPHICS::XGBuffer_AddRef(int *param_1)

{
  *param_1 = *param_1 + 1;
  return *param_1;
}




LPVOID XGRAPHICS::XGBuffer_GetBufferPointer(XGBuffer *pThis)

{
  return pThis->pData;
}




undefined4 XGRAPHICS::XGBuffer_GetBufferSize(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}




void D3D8::D3D_KickOffAndWaitForIdle(void)

{
  uint3 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int in_stack_00000004;
  int in_stack_00000008;
  
  if (in_stack_00000008 == 0) {
    uVar4 = *(uint *)(in_stack_00000004 + 8);
  }
  else {
    if (in_stack_00000008 == 1) {
      uVar4 = *(uint *)(in_stack_00000004 + 4);
      uVar1 = (uint3)(uVar4 >> 8);
      uVar3 = CONCAT31(uVar1 >> 0x13,(char)(uVar4 >> 0x13));
      uVar2 = CONCAT31(uVar1 >> 0x15,(char)(uVar4 >> 0x15));
      uVar5 = uVar4 >> 0x17;
      uVar4 = uVar4 >> 0x19;
      goto LAB_001877c0;
    }
    if (in_stack_00000008 != 2) {
      return;
    }
    uVar4 = *(uint *)(in_stack_00000004 + 4);
  }
  uVar1 = (uint3)(uVar4 >> 8);
  uVar3 = CONCAT31(uVar1 >> 4,(char)(uVar4 >> 4));
  uVar2 = CONCAT31(uVar1 >> 6,(char)(uVar4 >> 6));
  uVar5 = uVar4 >> 8;
  uVar4 = uVar4 >> 10;
LAB_001877c0:
  FUN_00187718(uVar4 & 0xffffff03,uVar5 & 0xffffff03,uVar2 & 0xffffff03,uVar3 & 0xffffff03);
  return;
}




char XGRAPHICS::XGSUCode_GetVertexShaderType(short *param_1)

{
  short sVar1;
  char cVar2;
  
  sVar1 = *param_1;
  if (sVar1 == 0x2078) {
    cVar2 = '\x01';
  }
  else if (sVar1 == 0x7378) {
    cVar2 = '\x03';
  }
  else {
    cVar2 = ((sVar1 == 0x7778) - 1U & 0xfd) + 2;
  }
  return cVar2;
}




DWORD XGRAPHICS::XGBuffer_Release(XGBuffer *pThis)

{
  DWORD DVar1;
  DWORD DVar2;
  
  DVar2 = pThis->refCount;
  DVar1 = DVar2 - 1;
  pThis->refCount = DVar1;
  if (DVar2 == 1) {
    if (pThis->pData != (LPVOID)0x0) {
      XAPILIB::XMemFree(pThis->pData,0x24870000);
    }
    XAPILIB::XMemFree(pThis,0x24870000);
  }
  return DVar1;
}




HRESULT XGRAPHICS::XGBufferCreate(DWORD numBytes,XGBuffer **param_2)

{
  XGBuffer *puVar1;
  void *iVar2;
  
  puVar1 = XAPILIB::XMemAlloc(0xc,0x24870000);
  if (puVar1 == (XGBuffer *)0x0) {
    puVar1 = (XGBuffer *)0x0;
  }
  else {
    puVar1->refCount = 0;
    puVar1->pData = (LPVOID)0x0;
    puVar1->size = 0;
  }
  if (puVar1 != (XGBuffer *)0x0) {
    puVar1->refCount = 1;
    iVar2 = XAPILIB::XMemAlloc(numBytes,0x24870000);
    puVar1->pData = iVar2;
    puVar1->size = numBytes;
    if (iVar2 != (void *)0x0) {
      *param_2 = puVar1;
      return 0;
    }
    XAPILIB::XMemFree(puVar1,0x24870000);
  }
  return E_OUTOFMEMORY;
}




