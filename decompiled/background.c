/* background.c - Background rendering, collision things, GhoulyBox */
#include "background.h"

void background::getAllocDetails(ObjectAllocDetails *param_1)

{
  param_1->entitySize = 0x9e8;
  param_1->paramsSize = 0x334;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void background::getVTable(void)

{
  avatar::initVTable((AvatarVTable *)vtable);
  vtable[0] = getAllocDetails;
  vtable[1] = ctor;
  vtable[2] = dtor;
  vtable[3] = onMessage;
  vtable[4] = update;
  vtable[5] = draw;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 background::draw(avatar *param_1,undefined4 param_2,BOOL someFlag)

{
  undefined4 uVar1;
  
  if (Game::DialogState == NotInDialog) {
    uVar1 = avatar::draw(param_1,param_2,someFlag);
    return uVar1;
  }
  return 0;
}



void background::loadModelSomething
               (ndHeader *param_1,char param_2,undefined4 param_3,undefined4 param_4,
               ndHeader *param_5,undefined4 *param_6)

{
  ndHeader *pnVar1;
  int iVar2;
  ndHeader *pnVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  undefined1 uVar8;
  
LAB_00042c40:
  do {
    pcVar5 = param_1->subresName;
    iVar2 = 0xd;
    bVar7 = true;
    pcVar4 = pcVar5;
    pcVar6 = "ndPushBuffer";
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar7 = *pcVar4 == *pcVar6;
      pcVar4 = pcVar4 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    pnVar3 = param_5;
    if (bVar7) {
      *(undefined1 *)((int)&param_1[1].prev + 3) = 0;
    }
    else {
      iVar2 = 0xf;
      bVar7 = true;
      pcVar4 = pcVar5;
      pcVar6 = "ndBGPushBuffer";
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar7 = *pcVar4 == *pcVar6;
        pcVar4 = pcVar4 + 1;
        pcVar6 = pcVar6 + 1;
      } while (bVar7);
      if (bVar7) {
        if (param_2 != '\0') {
          param_1[2].field3_0x8 = (char *)((float)param_1[2].field3_0x8 - 70.0);
          param_1[2].varDataOffset = (void *)((float)param_1[2].varDataOffset - 70.0);
          param_1[2].callbackCtx = (BigBlockCallbackCtx *)((float)param_1[2].callbackCtx - 70.0);
          param_1[2].nextChild = (ndHeader *)((float)param_1[2].nextChild + 70.0);
          param_1[2].nextSibling = (ndHeader *)((float)param_1[2].nextSibling + 70.0);
          param_1[2].prev = (ndHeader *)((float)param_1[2].prev + 70.0);
        }
        *(undefined1 *)((int)&param_1[1].prev + 3) = 0;
        *param_6 = 1;
      }
      else {
        iVar2 = 0xf;
        bVar7 = true;
        pcVar4 = "ndShaderParam2";
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar7 = *pcVar5 == *pcVar4;
          pcVar5 = pcVar5 + 1;
          pcVar4 = pcVar4 + 1;
        } while (bVar7);
        if (bVar7) {
          param_1->field3_0x8 = (char *)0x0;
          pnVar3 = param_1;
        }
      }
    }
    if (param_2 == '\0') {
      bVar7 = true;
      pnVar1 = param_1->nextChild;
      iVar2 = 0xb;
      pcVar5 = param_1->subresName;
      pcVar4 = "ndMtxArray";
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar7 = *pcVar5 == *pcVar4;
        pcVar5 = pcVar5 + 1;
        pcVar4 = pcVar4 + 1;
      } while (bVar7);
      if (bVar7) {
        if (pnVar1 != (ndHeader *)0x0) {
          uVar8 = 1;
LAB_00042d7d:
          loadModelSomething(pnVar1,uVar8,param_3,param_4,pnVar3,param_6);
        }
      }
      else if (pnVar1 != (ndHeader *)0x0) {
        uVar8 = 0;
        goto LAB_00042d7d;
      }
      param_1 = param_1->nextSibling;
      if (param_1 == (ndHeader *)0x0) {
        return;
      }
      param_2 = '\0';
      goto LAB_00042c40;
    }
    if (param_1->nextChild != (ndHeader *)0x0) {
      loadModelSomething(param_1->nextChild,1,param_3,param_4,pnVar3,param_6);
    }
    param_1 = param_1->nextSibling;
    if (param_1 == (ndHeader *)0x0) {
      return;
    }
    param_2 = '\x01';
  } while( true );
}



// WARNING: Unable to use type for symbol piVar9
// WARNING: Unable to use type for symbol model_descriptor
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 background::ctor(background *bg,backgroundParams *params)

{
  char cVar1;
  ModelFooterEntry *pMVar2;
  Subresource0x11 *pSVar3;
  float fVar4;
  ModelDescriptor *pMVar5;
  backgroundParams *pbVar6;
  char *pcVar7;
  background_0x934 pEVar8;
  uint uVar9;
  ModelSubresource0x14 *model_subres_0x14;
  Subresource0x8 *subres;
  backgroundInner *new_inners;
  void *pvVar10;
  BOOL BVar11;
  ColliderSetDescriptor *pCVar12;
  int inner_i;
  int *piVar13;
  int i;
  ModelFooterEntry *pMVar14;
  ModelFooterEntry *footer_entry;
  char *model_aid;
  uint numInners;
  int iVar15;
  int *piVar9;
  backgroundParams *model_descriptor;
  ModelDescriptor *pvVar7;
  Model *model_instance;
  Model *desc;
  
  model_aid = (params->avatarParams).modelAID;
  pcVar7 = model_aid;
  do {
    cVar1 = *pcVar7;
    pcVar7[(int)g_backgroundModelName - (int)model_aid] = cVar1;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  pEVar8 = (background_0x934)0x511b1c;
  if (Game::SceneInfo.backgrounds.head != (background_0x934_conflict3)0x0) {
    pEVar8 = (background_0x934)&Game::SceneInfo.backgrounds;
    do {
      pEVar8 = pEVar8->next;
    } while (pEVar8->next != (background_0x934)0x0);
  }
                    // Sets current bg
  pEVar8->next = &bg->background_0x934;
  (bg->background_0x934).prev = pEVar8;
  (bg->background_0x934).next = (background_0x934)0x0;
  calculateAABB(bg);
  avatar::loadTransforms(&bg->avatar);
  model_instance = (bg->avatar).model;
  if (model_instance == (Model *)0x0) {
    params = (backgroundParams *)0x0;
  }
  else {
    params = (backgroundParams *)model_instance->descriptor;
  }
  model_descriptor = params;
  numInners._0_2_ = (params->avatarParams).objParams.typeIndex;
  numInners._2_2_ = (params->avatarParams).objParams.field3_0x6;
  uVar9 = 0;
  if (numInners != 0) {
    piVar9 = *(int **)&(params->avatarParams).objParams;
    piVar13 = piVar9;
    do {
      if (*piVar13 == 0x14) {
        model_subres_0x14 = (ModelSubresource0x14 *)piVar9[uVar9 * 2 + 1];
        goto joined_r0x00042e38;
      }
      uVar9 = uVar9 + 1;
      piVar13 = piVar13 + 2;
    } while (uVar9 < numInners);
  }
  model_subres_0x14 = (ModelSubresource0x14 *)0x0;
joined_r0x00042e38:
  do {
    if (model_subres_0x14 == (ModelSubresource0x14 *)0x0) break;
    Game::AddSubres0x14(model_subres_0x14);
    if (model_subres_0x14->size == 0) break;
    model_subres_0x14 =
         (ModelSubresource0x14 *)((int)&model_subres_0x14->size + model_subres_0x14->size);
  } while( true );
  uVar9._0_2_ = (model_descriptor->avatarParams).objParams.typeIndex;
  uVar9._2_2_ = (model_descriptor->avatarParams).objParams.field3_0x6;
  numInners = 0;
  if (uVar9 != 0) {
    pMVar2 = *(ModelFooterEntry **)&(model_descriptor->avatarParams).objParams;
    pMVar14 = pMVar2;
    do {
      if (pMVar14->subresourceType == Subresource0x8) {
        if (pMVar2[numInners].offset != 0) {
          numInners = 0;
          footer_entry = pMVar2;
          if (uVar9 != 0) goto LAB_00042e85;
          goto LAB_00042e92;
        }
        break;
      }
      numInners = numInners + 1;
      pMVar14 = pMVar14 + 1;
    } while (numInners < uVar9);
  }
  goto LAB_00042e9b;
  while( true ) {
    numInners = numInners + 1;
    footer_entry = footer_entry + 1;
    if (uVar9 <= numInners) break;
LAB_00042e85:
    if (footer_entry->subresourceType == Subresource0x8) {
      subres = (Subresource0x8 *)pMVar2[numInners].offset;
      goto LAB_00042e94;
    }
  }
LAB_00042e92:
  subres = (Subresource0x8 *)0x0;
LAB_00042e94:
  FUN_000fefd0(model_aid,subres);
LAB_00042e9b:
  desc = (bg->avatar).model;
  if ((((desc != (Model *)0x0) && (desc->descriptor != (ModelDescriptor *)0x0)) &&
      (pSVar3 = desc->descriptor->runtimeCtx->subres0x11, pSVar3 != (Subresource0x11 *)0x0)) &&
     (pSVar3->otherCount != '\0')) {
    if (((desc == (Model *)0x0) || (desc->descriptor == (ModelDescriptor *)0x0)) ||
       (pSVar3 = desc->descriptor->runtimeCtx->subres0x11, pSVar3 == (Subresource0x11 *)0x0)) {
      numInners = 0;
    }
    else {
      numInners = (uint)pSVar3->otherCount;
    }
    new_inners = malloc_(numInners * 0x9c);
    bg->breakables = new_inners;
    for (uVar9 = numInners * 0x9c >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)new_inners = 0;
      new_inners = (backgroundInner *)&new_inners->field_0x4;
    }
    inner_i = 0;
    for (i = 0; i != 0; i = i + -1) {
      new_inners->field0_0x0 = 0;
      new_inners = (backgroundInner *)&new_inners->field_0x1;
    }
    if (numInners != 0) {
      iVar15 = 0;
      do {
        *(undefined4 *)(&bg->breakables->field0_0x0 + iVar15) = 0xffffffff;
        *(undefined4 *)(&bg->breakables->field_0x4 + iVar15) = 0;
        *(undefined4 *)((int)&bg->breakables->someTimer + iVar15) = 0;
        FUN_00045d70(bg,inner_i);
        inner_i = inner_i + 1;
        iVar15 = iVar15 + 0x9c;
      } while (inner_i < (int)numInners);
    }
    fVar4 = (params->avatarParams).pos.z;
    if ((*(int *)((int)fVar4 + 0x14) != 0) || (*(int *)((int)fVar4 + 0x2c) != 0)) {
      pvVar10 = malloc_((uint)*(byte *)(*(int *)((int)fVar4 + 0x10) + 1) * 0x1e0);
      bg->somePtr = (float)pvVar10;
      FUN_00044490();
    }
  }
  loalModelSubres0xf(bg);
  loadModelSubres0x2(bg);
  desc = (bg->avatar).model;
  if (((desc != (Model *)0x0) && (pMVar5 = desc->descriptor, pMVar5 != (ModelDescriptor *)0x0)) &&
     (pCVar12 = pMVar5->runtimeCtx->colliders, pCVar12 != (ColliderSetDescriptor *)0x0)) {
    BVar11 = ColliderSetDescriptor::hasCollision0x1235_(pCVar12);
    pCVar12 = (ColliderSetDescriptor *)(-(uint)(BVar11 != 0) & (uint)pCVar12);
    if (pCVar12 != (ColliderSetDescriptor *)0x0) {
      runCallbackOnColliders(pCVar12,0,0,0,Background::RegisterColliderCallback,bg);
    }
  }
  Assets::GetResourceBytes("aid_aidlist_ghoulies_background_disableframebufferclear",&params);
  pbVar6 = params;
  if (params == (backgroundParams *)0x0) {
    runtime::ExitGame(2);
  }
  params = pbVar6;
  inner_i = IndexOfAssetInAIDList((ReplayChapterMenu **)&params,(bg->avatar).modelAID);
  Assets::DestroyAssetOrDecrement(pbVar6);
  if (inner_i != -1) {
    DAT_004dea50 = 1;
    bg->aidFound = 1;
  }
  desc = (bg->avatar).model;
  params = (backgroundParams *)0x0;
  if ((desc != (Model *)0x0) && (pMVar5 = desc->descriptor, pMVar5 != (ModelDescriptor *)0x0)) {
    loadModelSomething(*pMVar5->runtimeCtx->modelSubresource->rootNodes,0,
                       *(undefined4 *)&bg->field_0x9d8,*(undefined4 *)&bg->field_0x9dc,0,&params);
  }
  (bg->avatar).hasActor_ = true;
  *(backgroundParams **)&bg->field_0x9e0 = params;
  *(undefined4 *)&bg->field_0x954 = 0xffffffff;
  ::actor::createOnDeathObjects(&bg->avatar,0);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void background::dtor(background *bg)

{
  background_0x934 pEVar1;
  
  FUN_00043d50();
  if (*(void **)&bg->field_0x9d8 != (void *)0x0) {
    free(*(void **)&bg->field_0x9d8);
    *(undefined4 *)&bg->field_0x9d8 = 0;
  }
  if (*(void **)&bg->field_0x9dc != (void *)0x0) {
    free(*(void **)&bg->field_0x9dc);
    *(undefined4 *)&bg->field_0x9dc = 0;
  }
  *(undefined4 *)&bg->field_0x9e0 = 0;
  if (bg->somePtr2 != (astruct_46 *)0x0) {
    FUN_000ed2e0();
    bg->somePtr2 = (astruct_46 *)0x0;
  }
  if (bg->breakables != (backgroundInner *)0x0) {
    free(bg->breakables);
    bg->breakables = (backgroundInner *)0x0;
  }
  if (bg->somePtr != 0.0) {
    FUN_00044620();
    free((void *)bg->somePtr);
    bg->somePtr = 0.0;
  }
  pEVar1 = (bg->background_0x934).prev;
  if (pEVar1 != (background_0x934)0x0) {
                    // Destroyed scene tree
    pEVar1->next = (bg->background_0x934).next;
  }
  pEVar1 = (bg->background_0x934).next;
  if (pEVar1 != (background_0x934)0x0) {
    pEVar1->prev = (bg->background_0x934).prev;
  }
  (bg->background_0x934).prev = (background_0x934)0x0;
  (bg->background_0x934).next = (background_0x934)0x0;
  if (bg->aidFound != 0) {
    DAT_004dea50 = 0;
    bg->aidFound = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


int background::calculateAABB(background *bg)

{
  ModelDescriptor *pMVar1;
  Model *extraout_EAX;
  BOOL BVar2;
  ColliderSetDescriptor *col_set;
  Model *model;
  vec3 *pvVar3;
  vec3 pos;
  vec3 v;
  AABBFat aabb;
  ColliderSetDescriptor *collider_set;
  Model *instance;
  
  model = (bg->avatar).model;
  if ((model != (Model *)0x0) && (model->descriptor != (ModelDescriptor *)0x0)) {
    avatar::pos1FromMatrix(&bg->avatar,&v);
    pvVar3 = avatar::pos2FromMatrix(&bg->avatar,&pos);
    Game::SetBackgroundPositions(&v,pvVar3);
    instance = (bg->avatar).model;
    model = extraout_EAX;
    if (instance != (Model *)0x0) {
      pMVar1 = instance->descriptor;
      model = (Model *)0x0;
      if (pMVar1 != (ModelDescriptor *)0x0) {
        model = (Model *)pMVar1->runtimeCtx;
        collider_set = (ColliderSetDescriptor *)model->field1_0x4;
        if (collider_set != (ColliderSetDescriptor *)0x0) {
          BVar2 = ColliderSetDescriptor::hasCollision0x1235_(collider_set);
          col_set = (ColliderSetDescriptor *)(-(uint)(BVar2 != 0) & (uint)collider_set);
          model = (Model *)0x0;
                    // If it has collision
          if (col_set != (ColliderSetDescriptor *)0x0) {
            aabb.matrixPtr = (uint)col_set->matrixPtr;
            aabb.aabb.maxZ = 0;
            aabb.aabb.maxY = 0;
            aabb.aabb.maxX = 0;
            aabb.aabb.minZ = 0;
            aabb.aabb.minY = 0;
            aabb.aabb.minX = 0;
                    // 0xffffffff = load all colliders
            model = (Model *)runCallbackOnColliders
                                       (col_set,0xffffffff,0,0,ColliderPairValue::calculateAABB,
                                        &aabb);
            Game::BackgroundAABB.aabb.maxX = aabb.aabb.maxX;
            Game::BackgroundAABB.aabb.maxY = aabb.aabb.maxY;
            Game::BackgroundAABB.aabb.maxZ = aabb.aabb.maxZ;
            Game::BackgroundAABB.aabb.minX = aabb.aabb.minX;
            Game::BackgroundAABB.aabb.minY = aabb.aabb.minY;
            Game::BackgroundHasCollision = true;
            Game::BackgroundAABB.aabb.minZ = aabb.aabb.minZ;
          }
        }
      }
    }
  }
  return (int)model;
}



// WARNING: Type propagation algorithm not settling
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void background::loadModelSubres0x2(background *bg)

{
  AffineTransform *pAVar1;
  short sVar2;
  Model *pMVar3;
  ModelDescriptor *pMVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  AffineTransform *pAVar8;
  ModelFooterEntry *pMVar9;
  int *piVar10;
  Skeleton *pSVar11;
  int *piVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  
  piVar12 = (int *)0x0;
  while ((iVar6 = DAT_0050e930, pMVar3 = (bg->avatar).model, pMVar3 != (Model *)0x0 &&
         (pMVar4 = pMVar3->descriptor, pMVar4 != (ModelDescriptor *)0x0))) {
    uVar7 = 0;
    if (pMVar4->numFooterEntries == 0) break;
    pMVar9 = pMVar4->footerEntries;
    while (pMVar9->subresourceType != BoneAffines) {
      uVar7 = uVar7 + 1;
      pMVar9 = pMVar9 + 1;
      if (pMVar4->numFooterEntries <= uVar7) goto LAB_000432f1;
    }
    piVar10 = (int *)pMVar4->footerEntries[uVar7].offset;
    if (piVar10 == (int *)0x0) break;
    if (piVar12 == (int *)0x0) {
      piVar12 = piVar10 + 1;
      piVar10 = piVar12 + *piVar10 * 0xd;
    }
    else {
      piVar12 = piVar12 + 0xd;
      piVar10 = piVar10 + *piVar10 * 0xd + 1;
    }
    while( true ) {
      if (piVar10 <= piVar12) goto LAB_000432f1;
      if ((short)*piVar12 == 8) break;
      piVar12 = piVar12 + 0xd;
    }
    pMVar3 = (bg->avatar).model;
    if (pMVar3 == (Model *)0x0) {
      pSVar11 = (Skeleton *)0x0;
    }
    else {
      pSVar11 = pMVar3->skeleton;
      if (pSVar11 == (Skeleton *)0x0) {
        pSVar11 = pMVar3->skeleton2;
      }
    }
    fVar13 = (float)piVar12[4];
    fVar16 = (float)piVar12[8];
    fVar14 = (float)piVar12[0xc];
    sVar2 = *(short *)((int)piVar12 + 2);
    pAVar1 = &(bg->avatar).drawAffine;
    fVar17 = fVar13;
    fVar15 = fVar16;
    if (-1 < sVar2) {
      if (pSVar11->ignoresGlobalBone == 0) {
        ::skeleton::gotten_affine.m[0][0] = pSVar11[sVar2].boneAffines[0].m[0][0];
        ::skeleton::gotten_affine.m[0][1] = pSVar11[sVar2].boneAffines[0].m[1][0];
        ::skeleton::gotten_affine.m[0][2] = pSVar11[sVar2].boneAffines[0].m[2][0];
        ::skeleton::gotten_affine.m[0][3] = (float)pSVar11[sVar2 + 1].numBones;
        ::skeleton::gotten_affine.m[1][0] = pSVar11[sVar2].boneAffines[0].m[0][1];
        ::skeleton::gotten_affine.m[1][1] = pSVar11[sVar2].boneAffines[0].m[1][1];
        ::skeleton::gotten_affine.m[1][2] = pSVar11[sVar2].boneAffines[0].m[2][1];
        ::skeleton::gotten_affine.m[1][3] = (float)pSVar11[sVar2 + 1].ignoresGlobalBone;
        ::skeleton::gotten_affine.m[2][0] = pSVar11[sVar2].boneAffines[0].m[0][2];
        ::skeleton::gotten_affine.m[2][1] = pSVar11[sVar2].boneAffines[0].m[1][2];
        ::skeleton::gotten_affine.m[2][2] = pSVar11[sVar2].boneAffines[0].m[2][2];
        ::skeleton::gotten_affine.m[2][3] = *(float *)&pSVar11[sVar2 + 1].field_0x8;
        pAVar8 = &::skeleton::gotten_affine;
      }
      else {
        pAVar8 = pSVar11->boneAffines + sVar2;
      }
      fVar17 = pAVar8->m[0][1] * fVar16 + pAVar8->m[0][2] * fVar14 + pAVar8->m[0][0] * fVar13 +
               pAVar8->m[0][3];
      fVar15 = pAVar8->m[1][1] * fVar16 + pAVar8->m[1][2] * fVar14 + pAVar8->m[1][0] * fVar13 +
               pAVar8->m[1][3];
      fVar14 = pAVar8->m[2][1] * fVar16 + pAVar8->m[2][2] * fVar14 + pAVar8->m[2][0] * fVar13 +
               pAVar8->m[2][3];
    }
    fVar13 = fVar17;
    fVar16 = fVar15;
    if (pAVar1 != (AffineTransform *)0x0) {
      fVar13 = (bg->avatar).drawAffine.m[0][1] * fVar15 + (bg->avatar).drawAffine.m[0][2] * fVar14 +
               fVar17 * pAVar1->m[0][0] + (bg->avatar).drawAffine.m[0][3];
      fVar16 = (bg->avatar).drawAffine.m[1][1] * fVar15 + (bg->avatar).drawAffine.m[1][2] * fVar14 +
               (bg->avatar).drawAffine.m[1][0] * fVar17 + (bg->avatar).drawAffine.m[1][3];
      fVar14 = (bg->avatar).drawAffine.m[2][1] * fVar15 + (bg->avatar).drawAffine.m[2][2] * fVar14 +
               (bg->avatar).drawAffine.m[2][0] * fVar17 + (bg->avatar).drawAffine.m[2][3];
    }
    iVar5 = DAT_0050e930 * 3;
    DAT_0050e930 = DAT_0050e930 + 1;
    (&DAT_0050e834)[iVar5] = fVar13;
    (&DAT_0050e838)[iVar6 * 3] = fVar16;
    (&DAT_0050e83c)[iVar6 * 3] = fVar14;
  }
LAB_000432f1:
  piVar12 = (int *)0x0;
  while ((pMVar3 = (bg->avatar).model, pMVar3 != (Model *)0x0 &&
         (pMVar4 = pMVar3->descriptor, pMVar4 != (ModelDescriptor *)0x0))) {
    uVar7 = 0;
    if (pMVar4->numFooterEntries == 0) break;
    pMVar9 = pMVar4->footerEntries;
    while (pMVar9->subresourceType != BoneAffines) {
      uVar7 = uVar7 + 1;
      pMVar9 = pMVar9 + 1;
      if (pMVar4->numFooterEntries <= uVar7) goto LAB_00043341;
    }
    piVar10 = (int *)pMVar4->footerEntries[uVar7].offset;
    if (piVar10 == (int *)0x0) break;
    if (piVar12 == (int *)0x0) {
      piVar12 = piVar10 + 1;
      piVar10 = piVar12 + *piVar10 * 0xd;
    }
    else {
      piVar12 = piVar12 + 0xd;
      piVar10 = piVar10 + *piVar10 * 0xd + 1;
    }
    while( true ) {
      if (piVar10 <= piVar12) goto LAB_00043341;
      if ((short)*piVar12 == 9) break;
      piVar12 = piVar12 + 0xd;
    }
    pMVar3 = (bg->avatar).model;
    if (pMVar3 == (Model *)0x0) {
      pSVar11 = (Skeleton *)0x0;
    }
    else {
      pSVar11 = pMVar3->skeleton;
      if (pSVar11 == (Skeleton *)0x0) {
        pSVar11 = pMVar3->skeleton2;
      }
    }
    fVar13 = (float)piVar12[4];
    fVar16 = (float)piVar12[8];
    _DAT_0050e940 = (float)piVar12[0xc];
    sVar2 = *(short *)((int)piVar12 + 2);
    pAVar1 = &(bg->avatar).drawAffine;
    fVar14 = fVar13;
    fVar17 = fVar16;
    if (-1 < sVar2) {
      if (pSVar11->ignoresGlobalBone == 0) {
        ::skeleton::gotten_affine.m[0][0] = pSVar11[sVar2].boneAffines[0].m[0][0];
        ::skeleton::gotten_affine.m[0][1] = pSVar11[sVar2].boneAffines[0].m[1][0];
        ::skeleton::gotten_affine.m[0][2] = pSVar11[sVar2].boneAffines[0].m[2][0];
        ::skeleton::gotten_affine.m[0][3] = (float)pSVar11[sVar2 + 1].numBones;
        ::skeleton::gotten_affine.m[1][0] = pSVar11[sVar2].boneAffines[0].m[0][1];
        ::skeleton::gotten_affine.m[1][1] = pSVar11[sVar2].boneAffines[0].m[1][1];
        ::skeleton::gotten_affine.m[1][2] = pSVar11[sVar2].boneAffines[0].m[2][1];
        ::skeleton::gotten_affine.m[1][3] = (float)pSVar11[sVar2 + 1].ignoresGlobalBone;
        ::skeleton::gotten_affine.m[2][0] = pSVar11[sVar2].boneAffines[0].m[0][2];
        ::skeleton::gotten_affine.m[2][1] = pSVar11[sVar2].boneAffines[0].m[1][2];
        ::skeleton::gotten_affine.m[2][2] = pSVar11[sVar2].boneAffines[0].m[2][2];
        ::skeleton::gotten_affine.m[2][3] = *(float *)&pSVar11[sVar2 + 1].field_0x8;
        pAVar8 = &::skeleton::gotten_affine;
      }
      else {
        pAVar8 = pSVar11->boneAffines + sVar2;
      }
      fVar14 = pAVar8->m[0][2] * _DAT_0050e940 + pAVar8->m[0][1] * fVar16 + pAVar8->m[0][0] * fVar13
               + pAVar8->m[0][3];
      fVar17 = pAVar8->m[1][2] * _DAT_0050e940 + pAVar8->m[1][1] * fVar16 + pAVar8->m[1][0] * fVar13
               + pAVar8->m[1][3];
      _DAT_0050e940 =
           pAVar8->m[2][2] * _DAT_0050e940 + pAVar8->m[2][1] * fVar16 + pAVar8->m[2][0] * fVar13 +
           pAVar8->m[2][3];
    }
    _DAT_0050e938 = fVar14;
    _DAT_0050e93c = fVar17;
    if (pAVar1 != (AffineTransform *)0x0) {
      _DAT_0050e938 =
           (bg->avatar).drawAffine.m[0][2] * _DAT_0050e940 +
           (bg->avatar).drawAffine.m[0][1] * fVar17 + pAVar1->m[0][0] * fVar14 +
           (bg->avatar).drawAffine.m[0][3];
      _DAT_0050e93c =
           (bg->avatar).drawAffine.m[1][2] * _DAT_0050e940 +
           (bg->avatar).drawAffine.m[1][1] * fVar17 + (bg->avatar).drawAffine.m[1][0] * fVar14 +
           (bg->avatar).drawAffine.m[1][3];
      _DAT_0050e940 =
           (bg->avatar).drawAffine.m[2][2] * _DAT_0050e940 +
           (bg->avatar).drawAffine.m[2][1] * fVar17 + (bg->avatar).drawAffine.m[2][0] * fVar14 +
           (bg->avatar).drawAffine.m[2][3];
    }
    runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
    Graphics::SetShaderConstant.c1 =
         ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) * 0.3 + 0.7;
    DAT_0050e944 = 1;
    Graphics::SetShaderConstant.c4 = 1.0;
    Graphics::SetShaderConstant.c2 = Graphics::SetShaderConstant.c1;
    Graphics::SetShaderConstant.c3 = Graphics::SetShaderConstant.c1;
    DAT_0050e948 = Graphics::SetShaderConstant.c1;
  }
LAB_00043341:
  piVar12 = (int *)0x0;
  while( true ) {
    pMVar3 = (bg->avatar).model;
    if ((pMVar3 == (Model *)0x0) || (pMVar4 = pMVar3->descriptor, pMVar4 == (ModelDescriptor *)0x0))
    {
      return;
    }
    uVar7 = 0;
    if (pMVar4->numFooterEntries == 0) {
      return;
    }
    pMVar9 = pMVar4->footerEntries;
    while (pMVar9->subresourceType != BoneAffines) {
      uVar7 = uVar7 + 1;
      pMVar9 = pMVar9 + 1;
      if (pMVar4->numFooterEntries <= uVar7) {
        return;
      }
    }
    piVar10 = (int *)pMVar4->footerEntries[uVar7].offset;
    if (piVar10 == (int *)0x0) break;
    if (piVar12 == (int *)0x0) {
      piVar12 = piVar10 + 1;
      piVar10 = piVar12 + *piVar10 * 0xd;
    }
    else {
      piVar12 = piVar12 + 0xd;
      piVar10 = piVar10 + *piVar10 * 0xd + 1;
    }
    if (piVar10 <= piVar12) {
      return;
    }
    while ((short)*piVar12 != 0x1f) {
      piVar12 = piVar12 + 0xd;
      if (piVar10 <= piVar12) {
        return;
      }
    }
    pMVar3 = (bg->avatar).model;
    if (pMVar3 == (Model *)0x0) {
      pSVar11 = (Skeleton *)0x0;
    }
    else {
      pSVar11 = pMVar3->skeleton;
      if (pSVar11 == (Skeleton *)0x0) {
        pSVar11 = pMVar3->skeleton2;
      }
    }
    fVar13 = (float)piVar12[4];
    fVar16 = (float)piVar12[8];
    _DAT_0050e960 = (float)piVar12[0xc];
    sVar2 = *(short *)((int)piVar12 + 2);
    pAVar1 = &(bg->avatar).drawAffine;
    fVar14 = fVar13;
    fVar17 = fVar16;
    if (-1 < sVar2) {
      if (pSVar11->ignoresGlobalBone == 0) {
        ::skeleton::gotten_affine.m[0][0] = pSVar11[sVar2].boneAffines[0].m[0][0];
        ::skeleton::gotten_affine.m[0][1] = pSVar11[sVar2].boneAffines[0].m[1][0];
        ::skeleton::gotten_affine.m[0][2] = pSVar11[sVar2].boneAffines[0].m[2][0];
        ::skeleton::gotten_affine.m[0][3] = (float)pSVar11[sVar2 + 1].numBones;
        ::skeleton::gotten_affine.m[1][0] = pSVar11[sVar2].boneAffines[0].m[0][1];
        ::skeleton::gotten_affine.m[1][1] = pSVar11[sVar2].boneAffines[0].m[1][1];
        ::skeleton::gotten_affine.m[1][2] = pSVar11[sVar2].boneAffines[0].m[2][1];
        ::skeleton::gotten_affine.m[1][3] = (float)pSVar11[sVar2 + 1].ignoresGlobalBone;
        ::skeleton::gotten_affine.m[2][0] = pSVar11[sVar2].boneAffines[0].m[0][2];
        ::skeleton::gotten_affine.m[2][1] = pSVar11[sVar2].boneAffines[0].m[1][2];
        ::skeleton::gotten_affine.m[2][2] = pSVar11[sVar2].boneAffines[0].m[2][2];
        ::skeleton::gotten_affine.m[2][3] = *(float *)&pSVar11[sVar2 + 1].field_0x8;
        pAVar8 = &::skeleton::gotten_affine;
      }
      else {
        pAVar8 = pSVar11->boneAffines + sVar2;
      }
      fVar14 = pAVar8->m[0][2] * _DAT_0050e960 + pAVar8->m[0][1] * fVar16 + fVar13 * pAVar8->m[0][0]
               + pAVar8->m[0][3];
      fVar17 = pAVar8->m[1][2] * _DAT_0050e960 + pAVar8->m[1][1] * fVar16 + pAVar8->m[1][0] * fVar13
               + pAVar8->m[1][3];
      _DAT_0050e960 =
           pAVar8->m[2][2] * _DAT_0050e960 + pAVar8->m[2][1] * fVar16 + pAVar8->m[2][0] * fVar13 +
           pAVar8->m[2][3];
    }
    _DAT_0050e958 = fVar14;
    _DAT_0050e95c = fVar17;
    if (pAVar1 != (AffineTransform *)0x0) {
      _DAT_0050e958 =
           (bg->avatar).drawAffine.m[0][2] * _DAT_0050e960 +
           (bg->avatar).drawAffine.m[0][1] * fVar17 + pAVar1->m[0][0] * fVar14 +
           (bg->avatar).drawAffine.m[0][3];
      _DAT_0050e95c =
           (bg->avatar).drawAffine.m[1][2] * _DAT_0050e960 +
           (bg->avatar).drawAffine.m[1][1] * fVar17 + (bg->avatar).drawAffine.m[1][0] * fVar14 +
           (bg->avatar).drawAffine.m[1][3];
      _DAT_0050e960 =
           (bg->avatar).drawAffine.m[2][2] * _DAT_0050e960 +
           (bg->avatar).drawAffine.m[2][1] * fVar17 + (bg->avatar).drawAffine.m[2][0] * fVar14 +
           (bg->avatar).drawAffine.m[2][3];
    }
    DAT_0050e950 = 1;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void background::loalModelSubres0xf(background *bg)

{
  Model *pMVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  ModelFooterEntry *pMVar6;
  int iVar7;
  int iVar8;
  ModelDescriptor *pMVar9;
  
  pMVar1 = (bg->avatar).model;
  if (pMVar1 == (Model *)0x0) {
    pMVar9 = (ModelDescriptor *)0x0;
  }
  else {
    pMVar9 = pMVar1->descriptor;
  }
  iVar8 = 0;
  iVar7 = 0;
  do {
    uVar2 = pMVar9->numFooterEntries;
    uVar4 = 0;
    if (uVar2 != 0) {
      pMVar6 = pMVar9->footerEntries;
      do {
        if (pMVar6->subresourceType == (Unknown0xc|SomeType0x3)) {
          piVar3 = (int *)pMVar9->footerEntries[uVar4].offset;
          if (piVar3 != (int *)0x0) {
            iVar5 = *piVar3;
            goto LAB_00043b83;
          }
          break;
        }
        uVar4 = uVar4 + 1;
        pMVar6 = pMVar6 + 1;
      } while (uVar4 < uVar2);
    }
    iVar5 = 0;
LAB_00043b83:
    if (iVar5 <= iVar8) {
      return;
    }
    uVar4 = 0;
    if (uVar2 != 0) {
      pMVar6 = pMVar9->footerEntries;
      do {
        if (pMVar6->subresourceType == (Unknown0xc|SomeType0x3)) {
          uVar2 = pMVar9->footerEntries[uVar4].offset;
          if (uVar2 != 0) {
            iVar5 = iVar7 + 4 + uVar2;
            goto LAB_00043ba8;
          }
          break;
        }
        uVar4 = uVar4 + 1;
        pMVar6 = pMVar6 + 1;
      } while (uVar4 < uVar2);
    }
    iVar5 = 0;
LAB_00043ba8:
    FUN_0005b2d0(*(undefined4 *)(iVar5 + 0x24),*(undefined2 *)(iVar5 + 0x28));
    iVar8 = iVar8 + 1;
    iVar7 = iVar7 + 0x2c;
  } while( true );
}




undefined4 Background::RegisterColliderCallback(Collider *collider,background *bg)

{
  ColliderInstance *pCVar1;
  Buffer<> *puVar2;
  Buffer<> *buf;
  
  if ((collider->field13_0x10 != '\0') && ((collider->collisionMask & 0xc) != 0)) {
    if (bg->colliderList == (Buffer<> *)0x0) {
      puVar2 = malloc_(0x60);
      puVar2->head = puVar2->values;
      puVar2->tail = puVar2->values;
      puVar2->valueSize = 8;
      puVar2->capacity = 10;
      puVar2->end = (ColliderInstance *)(puVar2 + 1);
      bg->colliderList = puVar2;
    }
    buf = bg->colliderList;
    if (buf->tail == buf->end) {
      buf = (Buffer<> *)runtime::ExtendArray((Buffer *)buf);
      bg->colliderList = buf;
    }
    pCVar1 = buf->tail;
    buf->tail = (ColliderInstance *)((int)&pCVar1->collider + (uint)buf->valueSize);
    pCVar1->collider = collider;
    pCVar1->collisionMask = collider->collisionMask;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void background::onMessage(background *bg,Avatar_HitByActorMessage *msg)

{
  actor *paVar1;
  int *piVar2;
  bool bVar3;
  background *av;
  Avatar_HitByActorMessage *pAVar4;
  actor *breakables;
  BOOL BVar5;
  float fVar6;
  int iVar7;
  undefined4 extraout_ECX;
  actor *hitter_00;
  background **ppbVar8;
  MessageHeader local_8;
  actor *hitter;
  
  pAVar4 = msg;
  av = bg;
  switch((msg->field0_0x0).msgId) {
  case Avatar_BreakableHit:
    breakables = (actor *)(msg->v1).y;
    hitter_00 = (actor *)0x0;
    bVar3 = false;
    if ((breakables != (actor *)0x0) && (BVar5 = actorIsHumanOrNoPrevLL(breakables), BVar5 == 0)) {
      paVar1 = *(actor **)&breakables->body->field_0x270;
      msg = *(Avatar_HitByActorMessage **)&breakables->body->field_0x274;
      if ((paVar1 == (actor *)0x0) || (BVar5 = actorIsHumanOrNoPrevLL(paVar1), BVar5 == 0)) {
        if ((msg == (Avatar_HitByActorMessage *)0x0) ||
           (BVar5 = actorIsHumanOrNoPrevLL((actor *)msg), BVar5 == 0)) goto LAB_00043ed6;
        hitter_00 = (actor *)0x3;
      }
      else {
        hitter_00 = (actor *)0x2;
      }
      bVar3 = true;
    }
LAB_00043ed6:
    if (((pAVar4->v1).x == 0.0) || (!bVar3)) {
      BVar5 = 0;
    }
    else {
      BVar5 = 1;
    }
    breakables = (actor *)getBreakablesFromBackground
                                    (pAVar4->hitter,bg,BVar5,hitter_00,breakables,&bg);
    (pAVar4->field0_0x0).someActor = breakables;
    if ((breakables != (actor *)0x0) && (piVar2 = (int *)(pAVar4->v1).y, piVar2 != (int *)0x0)) {
      local_8.someActor = (actor *)0x0;
      local_8.msgId = Actor_SmashedBreakables;
      local_8.someActor = (actor *)FUN_00046470();
      (**(code **)(*piVar2 + 0xc))(piVar2,&local_8);
      return;
    }
    break;
  default:
    avatar::onMessage(&bg->avatar,(Message *)msg);
    break;
  case Avatar_HitByActor:
    breakables = msg->hitter;
    ppbVar8 = &bg;
    hitter = (actor *)0x1;
    BVar5 = actorIsHumanOrNoPrevLL(breakables);
    breakables = (actor *)getBreakablesFromBackground
                                    (pAVar4->someU32,bg,BVar5,hitter,breakables,ppbVar8);
    (pAVar4->field0_0x0).someActor = breakables;
    if (breakables != (actor *)0x0) {
      local_8.someActor = (actor *)0x0;
      local_8.msgId = Actor_SmashedBreakables;
      local_8.someActor = (actor *)FUN_00046470();
      (*((pAVar4->hitter->avatar).vtable)->onMessage)(pAVar4->hitter,&local_8);
      return;
    }
    break;
  case Avatar_HitByProjectile:
    fVar6 = (msg->v2).x;
    breakables = *(actor **)((int)fVar6 + 0xd8c);
    if (breakables == (actor *)0x0) {
      BVar5 = 0;
    }
    else {
      BVar5 = actorIsHumanOrNoPrevLL(breakables);
    }
    fVar6 = (float)getBreakablesFromBackground
                             (*(undefined4 *)&pAVar4->field_0x2c,bg,BVar5,(actor *)&DAT_00000005,
                              fVar6,&bg);
    (pAVar4->v1).y = fVar6;
    pAVar4->someU32 = 0;
    if (breakables == (actor *)0x0) {
      return;
    }
    goto joined_r0x00044036;
  case Avatar_HitByWeapon:
    fVar6 = (msg->v1).z;
    breakables = *(actor **)((int)fVar6 + 0xd8c);
    if (breakables == (actor *)0x0) {
      BVar5 = 0;
    }
    else {
      BVar5 = actorIsHumanOrNoPrevLL(breakables);
    }
    fVar6 = (float)getBreakablesFromBackground((pAVar4->v2).z,bg,BVar5,(actor *)0x4,fVar6,&bg);
    (pAVar4->v1).y = fVar6;
joined_r0x00044036:
    if (fVar6 != 0.0) {
      local_8.someActor = (actor *)0x0;
      local_8.msgId = Actor_SmashedBreakables;
      local_8.someActor = (actor *)FUN_00046470();
      (*((breakables->avatar).vtable)->onMessage)(breakables,&local_8);
      return;
    }
    break;
  case Avatar_SceneInsert:
    avatar::onMessage(&bg->avatar,(Message *)msg);
    avatar::onDrawListAdd(&av->avatar);
    iVar7 = FUN_00040be0();
    if (iVar7 != 0) {
      FUN_0002cbf0();
    }
    entityAvatarFxBurnup::checkCollision0x4((entityAvatarFxBurnup *)av);
    FUN_0002cd00(extraout_ECX,(SceneTreeNode *)&(av->avatar).node0x918);
    return;
  case Background_PostAStarInit:
    FUN_00045ec0();
    return;
  case Background_ReregisterDoor:
    FUN_00044300(bg,(Message *)msg);
    return;
  case Scene_Sfx_UpdatePos:
    break;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

int getBreakablesFromBackground
              (int param_1,background *param_2,BOOL param_3,actor *hitter,undefined4 param_5,
              int *param_6)

{
  Breakabl *pBVar1;
  int iVar2;
  int iVar3;
  Breakabl *pBVar4;
  
  pBVar1 = *(Breakabl **)(param_1 + 8);
  iVar3 = 0;
  for (pBVar4 = *(Breakabl **)(param_1 + 4); pBVar4 < pBVar1; pBVar4 = pBVar4 + 3) {
    iVar2 = FUN_000441f0(param_2,pBVar4,param_3,param_5);
    if (iVar2 != 0) {
      iVar3 = iVar3 + 1;
      *param_6 = pBVar4->index;
    }
  }
  return iVar3;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void LoadBackgroundPartTables(void)

{
  Asset *res;
  uint uVar1;
  Asset *local_4;
  
  Assets::GetResourceBytes("aid_misc_ghoulies_background_parttable",&local_4);
  res = local_4;
  if (local_4 == (Asset *)0x0) {
    runtime::ExitGame(2);
  }
  Assets::MiscGhouliesBackgroundPartTable = res;
  uVar1 = XSoundbankResource::GetResourceSize((XSoundbankResource *)res);
  DAT_00546298 = uVar1 / 0x22c;
  Assets::GetResourceBytes("aid_loctext_ghoulies_background_backgroundparttable",&local_4);
  if (local_4 == (Asset *)0x0) {
    runtime::ExitGame(2);
  }
  Assets::LoctextGhouliesBackgroundPartTable = local_4;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void background::doBigUpdate(background *bg)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  byte bVar5;
  byte *pbVar6;
  ModelDescriptor *pMVar7;
  astruct_46 *paVar8;
  AvatarMatrix *pAVar9;
  D3DXMATRIX DVar10;
  float *pfVar11;
  uint uVar12;
  float *pfVar13;
  int iVar14;
  background_conflict8 *pbVar15;
  int iVar16;
  undefined4 unaff_EBX;
  undefined4 uVar17;
  ModelDescriptor *model_desc;
  undefined4 unaff_EBP;
  int iVar18;
  float *pfVar19;
  undefined4 unaff_ESI;
  undefined4 uVar20;
  char *pcVar21;
  float speed;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar26;
  background_conflict8 *pbVar27;
  uint uVar28;
  uint uVar29;
  float fVar30;
  D3DXMATRIX someMat4;
  float fVar25;
  Model *model_instance;
  
  if (bg->somePtr == 0.0) {
    if (bg->somePtr2 != (astruct_46 *)0x0) {
      someMat4.m[2][0] = 0.0;
      if (runtime::dx_timer <= 0.0) {
        someMat4.m[2][0] = runtime::DeltaTime * runtime::TimeScale;
      }
      someMat4.m[1][3] = 3.99946e-40;
      someMat4.m[3][1] = someMat4.m[2][0];
      FUN_000ef2d0(someMat4.m[2][0],bg->somePtr2);
      model_instance = (bg->avatar).model;
      if ((model_instance == (Model *)0x0) ||
         (pMVar7 = model_instance->descriptor, pMVar7 == (ModelDescriptor *)0x0)) {
        someMat4.m[2][3] = 0.0;
      }
      else {
        someMat4.m[2][3] = (float)pMVar7->runtimeCtx->subres0x11;
      }
      someMat4.m[3][1] = (float)bg->breakables;
      someMat4.m[3][0] = 0.0;
      uVar20 = (int)someMat4.m[3][1] + *(int *)&bg->field_0x944 * 0x9c;
      uVar17 = someMat4.m[2][3];
      someMat4._60_4_ = uVar20;
      if ((uint)someMat4.m[3][1] < (uint)uVar20) {
        do {
          if (runtime::dx_timer <= 0.0) {
            fVar26 = runtime::DeltaTime * runtime::TimeScale;
          }
          else {
            fVar26 = 0.0;
          }
          if ((0.0 < ((backgroundInner *)someMat4.m[3][1])->someTimer) &&
             (fVar26 = ((backgroundInner *)someMat4.m[3][1])->someTimer - fVar26,
             ((backgroundInner *)someMat4.m[3][1])->someTimer = fVar26, fVar26 <= 0.0)) {
            ((backgroundInner *)someMat4.m[3][1])->someTimer = 0.0;
          }
          iVar16 = uVar17 + *(int *)someMat4.m[3][1] * 0xc;
          someMat4.m[3][2] = (float)((uint)*(ushort *)(iVar16 + 0x14) + uVar17);
          iVar18 = 0;
          if (*(char *)(iVar16 + 0x16) != '\0') {
            do {
              iVar16 = (int)(short)someMat4._48_2_;
              paVar8 = bg->somePtr2;
              fVar26 = *(float *)(&paVar8[1].field12_0x18 + iVar16 * 0xa8);
              fVar24 = (&paVar8[1].v)[iVar16 * 0x1c].x;
              speed = (&paVar8[1].v)[iVar16 * 0x1c].y;
              fVar30 = (&paVar8[1].v)[iVar16 * 0x1c].z;
              fVar22 = (&paVar8[1].field16_0x28)[iVar16 * 0x54];
              bVar5 = *(byte *)((int)someMat4.m[3][2] + iVar18);
              pAVar9 = (bg->avatar).transforms;
              pAVar9[bVar5].pos.x = (float)(&paVar8[1].field11_0x14)[iVar16 * 0x54];
              pAVar9[bVar5].pos.y = fVar26;
              pAVar9[bVar5].pos.z = fVar24;
              (bg->avatar).field234_0x29c = 0;
              (bg->avatar).field235_0x2a0 = 0;
              pAVar9[bVar5].field9_0x44 = 1.4013e-45;
              bVar5 = *(byte *)((int)someMat4.m[3][2] + iVar18);
              pAVar9 = (bg->avatar).transforms;
              pAVar9[bVar5].rotEuler.x = speed;
              pAVar9[bVar5].rotEuler.y = fVar30;
              pAVar9[bVar5].rotEuler.z = fVar22;
              someMat4.m[1][3] = 4.00452e-40;
              Math::WrapAnglesRad(&pAVar9[bVar5].rotEuler);
              iVar18 = iVar18 + 1;
              someMat4.m[3][0] = (float)((int)someMat4.m[3][0] + 1);
              pAVar9[bVar5].field9_0x44 = 1.4013e-45;
              uVar17 = someMat4.m[2][3];
              uVar20 = someMat4.m[3][3];
            } while (iVar18 < (int)(uint)*(byte *)((int)someMat4.m[2][3] + 0x16 +
                                                  *(int *)someMat4.m[3][1] * 0xc));
          }
          someMat4.m[3][1] = (float)((int)someMat4.m[3][1] + 0x9c);
        } while ((uint)someMat4.m[3][1] < (uint)uVar20);
      }
    }
    return;
  }
  model_instance = ADJ(Game::SceneInfo.backgrounds.head).avatar.modelInstance;
  pbVar15 = ADJ(Game::SceneInfo.backgrounds.head);
  if (model_instance == (Model *)0x0) {
    model_desc = (ModelDescriptor *)0x0;
  }
  else {
    model_desc = model_instance->descriptor;
  }
  fVar25 = ADJ(Game::SceneInfo.backgrounds.head)->somePtr;
  uVar12 = (uint)model_desc->runtimeCtx->subres0x11->count;
  pbVar6 = (byte *)model_desc->runtimeCtx->subres0x18;
  if (pbVar6 == (byte *)0x0) {
    if (uVar12 != 0) {
      pfVar19 = (float *)((int)fVar25 + 0x1d0);
      do {
        if (*(char *)((int)pfVar19 + 5) != '\0') {
          pfVar11 = pfVar19 + -0x74;
          FUN_0010cfe0(pfVar11,model_desc);
          FUN_0010c8d0();
          fVar26 = 0.0;
          if (runtime::dx_timer <= 0.0) {
            fVar24 = runtime::DeltaTime * runtime::TimeScale;
          }
          else {
            fVar24 = 0.0;
          }
          speed = 0.0;
          if ((pbVar15->avatar).movementFreezeTimer <= 0.0) {
            speed = (pbVar15->avatar).actionSpeed;
          }
          fVar24 = speed * fVar24 + *pfVar19;
          *pfVar19 = fVar24;
          if (*pfVar11 == 0.0) {
LAB_00044a56:
            if (fVar24 <= 1.0) goto LAB_00044a5f;
          }
          else {
            pfVar13 = (float *)pfVar19[-0x73];
            speed = *pfVar11;
            pfVar11 = pfVar13 + 5;
            do {
              pfVar1 = pfVar11 + -3;
              fVar30 = *pfVar11;
              fVar22 = *pfVar13;
              pfVar2 = pfVar11 + -2;
              pfVar3 = pfVar11 + -4;
              pfVar4 = pfVar11 + -1;
              pfVar13 = pfVar13 + 0xc;
              pfVar11 = pfVar11 + 0xc;
              speed = (float)((int)speed + -1);
              fVar26 = (*pfVar1 - fVar30) * (*pfVar1 - fVar30) +
                       (fVar22 - *pfVar2) * (fVar22 - *pfVar2) +
                       (*pfVar3 - *pfVar4) * (*pfVar3 - *pfVar4) + fVar26;
            } while (speed != 0.0);
            if (fVar26 < 0.0003) goto LAB_00044a56;
LAB_00044a5f:
            if (fVar24 <= 4.0) goto LAB_00044a6c;
          }
          *(undefined1 *)((int)pfVar19 + 5) = 0;
        }
LAB_00044a6c:
        pfVar19 = pfVar19 + 0x78;
        uVar12 = uVar12 - 1;
      } while (uVar12 != 0);
    }
    FUN_00044430();
  }
  else {
    uVar12 = 0;
    uVar28 = 0;
    fVar26 = runtime::DeltaTime;
    pbVar27 = pbVar15;
    fVar24 = fVar25;
    if (*pbVar6 != 0) {
      do {
        iVar16 = 0;
        if (*(char *)(*(int *)(pbVar6 + 8) + uVar28 * 8) != '\0') {
          pcVar21 = (char *)(uVar12 * 0x1e0 + 0x1d5 + (int)fVar25);
          uVar29 = uVar28;
          fVar25 = fVar24;
          do {
            fVar24 = 0.0;
            if (*pcVar21 != '\0') {
              speed = fVar24;
              if (runtime::dx_timer <= 0.0) {
                speed = fVar26 * runtime::TimeScale;
              }
              if ((pbVar15->avatar).movementFreezeTimer <= 0.0) {
                fVar24 = (pbVar15->avatar).actionSpeed;
              }
              fVar26 = fVar24 * speed + *(float *)(pcVar21 + -5);
              *(float *)(pcVar21 + -5) = fVar26;
              iVar18 = (int)(*(float *)(pbVar6 + 4) * fVar26);
              if (iVar18 < (int)(uint)*(ushort *)
                                       (*(int *)(*(int *)(pbVar6 + 8) + 4 + uVar28 * 8) + iVar16 * 4
                                       )) {
                iVar14 = ((uint)*(ushort *)
                                 (*(int *)(*(int *)(pbVar6 + 8) + 4 + uVar28 * 8) + 2 + iVar16 * 4)
                         + iVar18) * 0xe;
                iVar18 = *(int *)(pbVar6 + 0x1c) + iVar14;
                fVar22 = (float)(int)*(short *)(*(int *)(pbVar6 + 0x1c) + iVar14) * 3.125e-05;
                fVar26 = (float)(int)*(short *)(iVar18 + 4) * 3.125e-05;
                iVar14 = (int)*(short *)(iVar18 + 0xc);
                fVar23 = (float)(int)*(short *)(iVar18 + 2) * 3.125e-05;
                fVar24 = (float)(int)*(short *)(iVar18 + 8) * 0.0625;
                speed = (float)(int)*(short *)(iVar18 + 10) * 0.0625;
                fVar30 = (float)iVar14 * 0.0625;
                FUN_00153be0(&someMat4,*(undefined4 *)(pbVar6 + 0x10),*(undefined4 *)(pbVar6 + 0x14)
                             ,*(undefined4 *)(pbVar6 + 0x18),fVar22,fVar23,fVar26,
                             (float)(int)*(short *)(iVar18 + 6) * 3.125e-05,fVar24,speed,fVar30);
                D3DX8::D3DXMatrixMultiply
                          ((D3DXMATRIX *)(pcVar21 + -0x125),(D3DXMATRIX *)(pcVar21 + -0x1a5),
                           &someMat4);
                DVar10.m[0][1] = (float)bg;
                DVar10.m[0][0] = (float)(pcVar21 + -0x125);
                DVar10.m[0][2] = (float)unaff_ESI;
                DVar10.m[0][3] = (float)unaff_EBP;
                DVar10.m[1][0] = (float)unaff_EBX;
                DVar10._20_4_ = uVar12;
                DVar10._24_4_ = pbVar27;
                DVar10._28_4_ = uVar29;
                DVar10._32_4_ = iVar14;
                DVar10.m[2][1] = fVar25;
                DVar10.m[2][2] = fVar24;
                DVar10.m[2][3] = speed;
                DVar10.m[3][0] = fVar30;
                DVar10.m[3][1] = fVar22;
                DVar10.m[3][2] = fVar23;
                DVar10.m[3][3] = fVar26;
                pbVar15 = pbVar27;
                uVar28 = uVar29;
                FUN_00156010((astruct_24 *)(pbVar27->avatar).ndMtxArray,
                             *(undefined4 *)&(pbVar27->avatar).field_0x294,uVar12,DVar10);
                fVar26 = runtime::DeltaTime;
                pbVar27 = pbVar15;
                uVar29 = uVar28;
              }
              else {
                *pcVar21 = '\0';
                fVar26 = runtime::DeltaTime;
              }
            }
            uVar12 = uVar12 + 1;
            pcVar21 = pcVar21 + 0x1e0;
            iVar16 = iVar16 + 1;
            fVar24 = fVar25;
          } while (iVar16 < (int)(uint)*(byte *)(*(int *)(pbVar6 + 8) + uVar28 * 8));
        }
        uVar28 = uVar28 + 1;
      } while (uVar28 < *pbVar6);
      return;
    }
  }
  return;
}




void background::update(background *bg)

{
  ModelSubresource *pMVar1;
  Model *instance;
  
  doBigUpdate(bg);
  instance = (bg->avatar).model;
  if ((instance != (Model *)0x0) &&
     (pMVar1 = instance->modelPassedToBG, pMVar1 != (ModelSubresource *)0x0)) {
    updateModelChildren_(pMVar1,1.0);
  }
  return;
}




void GhoulyBox::loadFromDescriptor(GhoulyBox *this,GhoulyBoxDescriptor *res)

{
  float fVar1;
  uint *curr_ptr;
  char *objparams;
  GhoulyBoxOpcode opcode;
  
  opcode = res->opcode;
  while (opcode != New_Name) {
    switch(opcode) {
    case New_Name_(1):
      FUN_000f3ab0(this,(float)(int)res->someFloat * 0.01,res->field128_0x108 + 4,
                   res->field129_0x188 + 4,res->field131_0x20c,res->objparamsAID,&res->field_0x8c);
      break;
    case New_Name_(2):
      FUN_000f3b60();
      break;
    case Set0xc:
      this->field3_0xc = *(uint *)res->objparamsAID;
      break;
    case New_Name_(4):
      runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
      this->field3_0xc =
           (int)((float)((*(int *)(res->objparamsAID + 4) - *(int *)res->objparamsAID) + 1) *
                 ((float)(runtime::rand & 0x7fffff | 0x3f800000) - 1.0) +
                (float)*(int *)res->objparamsAID);
      break;
    case New_Name_(5):
      this->field3_0xc = 0xffffffff;
      break;
    case New_Name_(6):
      this->field5_0x14 = *(int *)res->objparamsAID;
      break;
    case New_Name_(7):
      fVar1 = *(float *)res->objparamsAID;
      *(undefined4 *)&this->field7_0x1c = *(undefined4 *)(res->objparamsAID + 4);
      this->f2 = fVar1;
      this->f1 = 0.001;
      break;
    case New_Name_(8):
      FUN_000f3bd0();
    }
    curr_ptr = &res->operationSize;
    objparams = res->objparamsAID;
                    // Go to next operation
    res = (GhoulyBoxDescriptor *)(res->objparamsAID + (*curr_ptr - 8));
    opcode = *(GhoulyBoxOpcode *)(objparams + (*curr_ptr - 4));
  }
  return;
}




void __fastcall FocusOnDoors_(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0xb8) != param_2) {
    *(int *)(param_1 + 0xb8) = param_2;
    if (param_2 == 0) {
      if (DAT_004ee320 != 0) {
        Game::NotAllowedToPause = Game::NotAllowedToPause + -1;
        GlobalCounter2 = GlobalCounter2 + -1;
        g_globalFlagset = g_globalFlagset & ~DoorCutscene;
        DAT_004ee320 = 0;
      }
    }
    else if ((DAT_004ee31c == 0) && (*(int *)(param_1 + 0x144) != 0)) {
      if (DAT_004ee320 == 0) {
        Game::NotAllowedToPause = Game::NotAllowedToPause + 1;
        GlobalCounter2 = GlobalCounter2 + 1;
        g_globalFlagset = g_globalFlagset | DoorCutscene;
        DAT_004ee320 = 1;
      }
      Camera::ctor(&g_doorsProjectionSet,"doors",(ProjectionSetBitField)0x0);
      Camera::AppendAndSelect(&g_doorsProjectionSet,0);
      Camera::SetActiveCameraConfig(0,"doors");
      DAT_004ee31c = 1;
      return;
    }
  }
  return;
}




void background::bigCollisionCheck2(undefined4 param_1)

{
  short *psVar1;
  short *in_EAX;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int local_18;
  int local_14;
  uint local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar4 = 0;
  if (0 < in_EAX[1]) {
    uVar2 = 0;
    do {
      psVar1 = in_EAX + uVar2 * 0xa8 + 0x1c8;
      if (in_EAX[uVar2 * 0xa8 + 0x1f5] == -2) {
        iVar3 = FUN_000f18e0(param_1,&local_14);
        if (iVar3 == 0) {
          psVar1[0x2d] = in_EAX[3];
          iVar3 = (int)psVar1 + (-0x390 - (int)in_EAX);
          *in_EAX = *in_EAX + -1;
          in_EAX[3] = ((short)(iVar3 / 0x150) + (short)(iVar3 >> 0x1f)) -
                      (short)((longlong)iVar3 * 0x30c30c31 >> 0x3f);
        }
        else if ((local_18 != 0) && (local_14 == 1)) {
          local_c = *(undefined4 *)psVar1;
          local_8 = *(undefined4 *)(psVar1 + 2);
          runtime::rand = runtime::rand * 0x19660d + 0x3c6ef35f;
          local_4 = *(undefined4 *)(psVar1 + 4);
          local_10 = runtime::rand & 0x7fffff | 0x3f800000;
          FUN_000ee560();
        }
      }
      uVar4 = uVar4 + 1;
      uVar2 = uVar4 & 0xffff;
    } while ((int)uVar2 < (int)in_EAX[1]);
  }
  return;
}




void background::bigCollisionCheck1(undefined4 param_1)

{
  short *in_EAX;
  int iVar1;
  int iVar2;
  undefined1 local_8 [8];
  
  iVar1 = FUN_000efe30();
  if (iVar1 != 0) {
    FUN_000eed50();
    iVar2 = FUN_000f18e0(param_1,local_8);
    if (iVar2 == 0) {
      *(short *)(iVar1 + 0x5a) = in_EAX[3];
      iVar1 = (iVar1 - (int)in_EAX) + -0x390;
      *in_EAX = *in_EAX + -1;
      in_EAX[3] = ((short)(iVar1 / 0x150) + (short)(iVar1 >> 0x1f)) -
                  (short)((longlong)iVar1 * 0x30c30c31 >> 0x3f);
    }
  }
  return;
}




GhoulyBox * GhoulyBox::fromAID(char *ghoulyBoxAID)

{
  GhoulyBox *extraout_EAX;
  GhoulyBox *this;
  uint uVar1;
  GhoulyBox *ddc;
  GhoulyBoxDescriptor *res;
  
                    // Load ECX with new space
  uVar1 = RandRange();
  do {
    Assets::GetResourceBytes(AllGhoulyBoxNames[uVar1],&res);
    if (res != (GhoulyBoxDescriptor *)0x0) {
      this = (GhoulyBox *)DeathDropContext::ctor();
      this->field3_0xc = 1;
      loadFromDescriptor(this,res);
      Assets::DestroyAssetOrDecrement(res);
      return this;
    }
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  runtime::ExitGame(2);
  return extraout_EAX;
}




void GhoulyBox::dtor(void *param_1)

{
  void *mem;
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  if (*(int *)param_1 != 0) {
    *(undefined4 *)(*(int *)param_1 + 4) = *(undefined4 *)((int)param_1 + 4);
    if (*(undefined4 **)((int)param_1 + 4) != (undefined4 *)0x0) {
      **(undefined4 **)((int)param_1 + 4) = *(undefined4 *)param_1;
    }
    *(undefined4 *)param_1 = 0;
    *(undefined4 *)((int)param_1 + 4) = 0;
  }
  mem = *(void **)((int)param_1 + 8);
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
  runtime::CurrentHeapToAllocateFrom = uVar1;
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
  SpawnReaperDefault();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields

void FUN_000f3ab0(GhoulyBox *ddc,undefined4 param_2,char *someAID,char *param_4,undefined4 param_5,
                 char *objParamsAID,char *param_7)

{
  char cVar1;
  GhoulyBoxInner *pGVar2;
  Buffer<> *buf;
  int iVar3;
  
  buf = ddc->inners;
  if (buf->tail == buf->end) {
    buf = (Buffer<> *)runtime::ExtendArray((Buffer *)buf);
    ddc->inners = buf;
  }
  pGVar2 = buf->tail;
  buf->tail = (GhoulyBoxInner *)((int)&pGVar2->field0_0x0 + (uint)buf->valueSize);
  iVar3 = (int)pGVar2 - (int)objParamsAID;
  do {
    cVar1 = *objParamsAID;
    objParamsAID[iVar3] = cVar1;
    objParamsAID = objParamsAID + 1;
  } while (cVar1 != '\0');
  iVar3 = 0x80 - (int)param_7;
  do {
    cVar1 = *param_7;
    param_7[(int)pGVar2 + iVar3] = cVar1;
    param_7 = param_7 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)&pGVar2->field_0x100 = param_2;
  iVar3 = 0x104 - (int)someAID;
  do {
    cVar1 = *someAID;
    someAID[(int)pGVar2 + iVar3] = cVar1;
    someAID = someAID + 1;
  } while (cVar1 != '\0');
  iVar3 = 0x184 - (int)param_4;
  do {
    cVar1 = *param_4;
    param_4[(int)pGVar2 + iVar3] = cVar1;
    param_4 = param_4 + 1;
  } while (cVar1 != '\0');
  pGVar2->field_0x204 = 0;
  *(undefined4 *)&pGVar2->field_0x284 = param_5;
  ddc->innersInitialised_ = 1;
  return;
}




int Background::isCollisionThings(int index,vec3 *param_2)

{
  int iVar1;
  int iVar2;
  BackgroundCollisionThing *thing;
  
  thing = BackgroundCollisionThings[index];
  if (thing == (BackgroundCollisionThing *)0x0) {
    return -1;
  }
  iVar1 = ((int)param_2->x - (int)vec3_0050e264.x) / (int)thing->someF;
  iVar2 = ((int)param_2->z - (int)vec3_0050e264.z) / (int)thing->someF;
  if ((((-1 < iVar1) && (iVar1 < *(int *)thing)) && (-1 < iVar2)) &&
     (iVar2 < (int)thing->maxFloatVal)) {
    return *(int *)thing * iVar2 + iVar1;
  }
  return -1;
}




void LoadBackgroundTiles(void)

{
  vec3 *pvVar1;
  vec3 *pvVar2;
  undefined4 *puVar3;
  VertexList *pVVar4;
  int iVar5;
  vec3 *pvVar6;
  void *pvVar7;
  int iVar8;
  BYTE *mem;
  uint *puVar9;
  undefined4 uVar10;
  BYTE *pBVar11;
  uint uVar13;
  ModelFooterEntry *pMVar14;
  int *piVar15;
  int iVar16;
  HeapTableEntry *pHVar17;
  float *pfVar18;
  uint uVar19;
  ModelDescriptor *descriptor;
  ModelFooterEntry *pMVar20;
  uint size;
  float *pfVar21;
  BYTE *pBVar22;
  uint8_t *buf;
  float10 fVar23;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  uint64_t uVar30;
  uint64_t uVar31;
  uint64_t uVar32;
  uint local_70;
  int local_68;
  uint *local_64;
  vec3 **local_60;
  int local_58;
  float local_3c;
  float local_38;
  float local_30;
  float local_2c;
  TilesSubresource *subres0x12;
  Subresource0x11 *uVar12;
  Model *model;
  
  if (Game::SceneInfo.backgrounds.head != (background_0x934_conflict3)0x0) {
    model = ADJ(Game::SceneInfo.backgrounds.head).avatar.modelInstance;
    currentBg = (background *)ADJ(Game::SceneInfo.backgrounds.head);
    if (model == (Model *)0x0) {
      descriptor = (ModelDescriptor *)0x0;
    }
    else {
      descriptor = model->descriptor;
    }
    subres0x12 = descriptor->runtimeCtx->subres0x12;
    if (subres0x12 != (TilesSubresource *)0x0) {
      size = subres0x12->size1 * subres0x12->size2 * subres0x12->size3;
      currentBgVertexBuffer = malloc_(size);
      uVar13 = size >> 2;
      buf = currentBgVertexBuffer;
      while (uVar13 != 0) {
        uVar13 = uVar13 - 1;
        builtin_memcpy(buf,"\x01\x01\x01\x01",4);
        buf = buf + 4;
      }
      for (size = size & 3; size != 0; size = size - 1) {
        *buf = '\x01';
        buf = buf + 1;
      }
    }
    uVar13 = 0;
    if (descriptor->numFooterEntries != 0) {
      pMVar14 = descriptor->footerEntries;
      while (pMVar14->subresourceType != Subresource0x11) {
        uVar13 = uVar13 + 1;
        pMVar14 = pMVar14 + 1;
        if (descriptor->numFooterEntries <= uVar13) {
          return;
        }
      }
      uVar12 = (Subresource0x11 *)descriptor->footerEntries[uVar13].offset;
      if (((uVar12 != (Subresource0x11 *)0x0) &&
          (pVVar4 = uVar12->vertexLists, pVVar4 != (VertexList *)0x0)) &&
         (iVar8 = FUN_00053030(descriptor), iVar8 != 0)) {
        DAT_0050e384 = (uint)descriptor->runtimeCtx->subres0x11->count;
        uint32_t_0050e37c = (uint32_t)malloc_(DAT_0050e384 * 4);
        DAT_0050e380 = malloc_(DAT_0050e384 * 4);
        local_70 = 0;
        if (DAT_0050e384 != 0) {
          local_60 = &pVVar4->vertices;
          do {
            uVar13 = 0;
            if (descriptor->numFooterEntries != 0) {
              pMVar14 = descriptor->footerEntries;
              do {
                if (pMVar14->subresourceType == Subresource0x11) {
                  uVar13 = descriptor->footerEntries[uVar13].offset;
                  if (uVar13 != 0) {
                    iVar8 = *(int *)(uVar13 + 0xc);
                    goto LAB_00112ea4;
                  }
                  break;
                }
                uVar13 = uVar13 + 1;
                pMVar14 = pMVar14 + 1;
              } while (uVar13 < descriptor->numFooterEntries);
            }
            iVar8 = 0;
LAB_00112ea4:
            iVar5 = *(int *)(iVar8 + local_70 * 8);
            uVar13 = iVar5 * 0x30;
            mem = malloc_(uVar13);
            if (0 < iVar5) {
              local_64 = (uint *)(mem + 0xc);
              local_68 = 0;
              pfVar21 = (float *)(mem + 8);
              local_58 = iVar5;
LAB_00112ef2:
              iVar16 = *(int *)(iVar8 + 4 + local_70 * 8);
              piVar15 = (int *)(iVar16 + local_68);
              pvVar6 = *local_60;
              pvVar1 = pvVar6 + *piVar15;
              pvVar2 = pvVar6 + *(int *)(iVar16 + 4 + local_68);
              pvVar6 = pvVar6 + piVar15[2];
              pfVar21[-2] = pvVar1->x;
              pfVar21[-1] = pvVar1->y;
              *pfVar21 = pvVar1->z;
              pfVar21[2] = pvVar2->x;
              pfVar21[3] = pvVar2->y;
              pfVar21[4] = pvVar2->z;
              pfVar21[6] = pvVar6->x;
              pfVar21[7] = pvVar6->y;
              pfVar21[8] = pvVar6->z;
              size = descriptor->numFooterEntries;
              uVar19 = 0;
              if (size != 0) {
                pMVar14 = descriptor->footerEntries;
                pMVar20 = pMVar14;
                do {
                  if (pMVar20->subresourceType == Subresource0x11) {
                    if ((pMVar14[uVar19].offset != 0) &&
                       (*(int *)(pMVar14[uVar19].offset + 0x10) != 0)) {
                      uVar19 = 0;
                      pMVar20 = pMVar14;
                      if (size != 0) goto LAB_001130a4;
                      goto LAB_001130b6;
                    }
                    break;
                  }
                  uVar19 = uVar19 + 1;
                  pMVar20 = pMVar20 + 1;
                } while (uVar19 < size);
              }
              fVar25 = pvVar6->y - pvVar1->y;
              fVar27 = pvVar6->z - pvVar1->z;
              fVar24 = pvVar2->z - pvVar1->z;
              fVar29 = pvVar6->x - pvVar1->x;
              fVar28 = pvVar2->x - pvVar1->x;
              fVar26 = pvVar2->y - pvVar1->y;
              local_2c = fVar24 * fVar29 - fVar27 * fVar28;
              fVar28 = fVar25 * fVar28 - fVar26 * fVar29;
              local_30 = fVar27 * fVar26 - fVar25 * fVar24;
              fVar24 = local_30 * local_30 + local_2c * local_2c + fVar28 * fVar28;
              if (fVar24 != 0.0) {
                fVar23 = (float10)invsqrt(fVar24);
                local_30 = (float)((float10)local_30 * fVar23);
                local_2c = (float)((float10)local_2c * fVar23);
              }
              uVar30 = float10::to_uint64_t((float10)local_2c * (float10)1023.0);
              uVar31 = float10::to_uint64_t(extraout_ST0_00 * (float10)511.0);
              uVar32 = float10::to_uint64_t((float10)local_30 * (float10)1023.0);
              iVar16 = 3;
              puVar9 = local_64;
              do {
                *puVar9 = ((uint)uVar30 & 0x7ff | (int)uVar31 << 0xb) << 0xb | (uint)uVar32 & 0x7ff;
                puVar9 = puVar9 + 4;
                iVar16 = iVar16 + -1;
              } while (iVar16 != 0);
              goto LAB_0011326c;
            }
LAB_0011329c:
            puVar3 = (undefined4 *)(uint32_t_0050e37c + local_70 * 4);
            uVar10 = D3D8::D3DDevice_CreateVertexBuffer2(uVar13);
            pvVar7 = DAT_0050e380;
            *puVar3 = uVar10;
            *(int *)((int)pvVar7 + local_70 * 4) = iVar5 * 3;
            pBVar11 = D3D8::D3DVertexBuffer_Lock2
                                (*(D3DVertexBuffer **)(uint32_t_0050e37c + local_70 * 4),0);
            pBVar22 = mem;
            for (uVar13 = uVar13 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
              *(undefined4 *)pBVar11 = *(undefined4 *)pBVar22;
              pBVar22 = pBVar22 + 4;
              pBVar11 = pBVar11 + 4;
            }
            for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
              *pBVar11 = *pBVar22;
              pBVar22 = pBVar22 + 1;
              pBVar11 = pBVar11 + 1;
            }
            iVar8 = FindHeapOf(mem);
            uVar10 = runtime::CurrentHeapToAllocateFrom;
            if (g_HeapTableBase[iVar8].heapHandle == (HANDLE)0x0) {
              pHVar17 = (HeapTableEntry *)0x0;
            }
            else {
              pHVar17 = g_HeapTableBase + iVar8;
            }
            runtime::CurrentHeapToAllocateFrom = iVar8;
            XAPILIB::HeapFree(pHVar17->heapHandle,0,mem);
            local_70 = local_70 + 1;
            local_60 = local_60 + 2;
            runtime::CurrentHeapToAllocateFrom = uVar10;
          } while (local_70 < DAT_0050e384);
        }
      }
    }
  }
  return;
  while( true ) {
    uVar19 = uVar19 + 1;
    pMVar20 = pMVar20 + 1;
    if (size <= uVar19) break;
LAB_001130a4:
    if (pMVar20->subresourceType == Subresource0x11) {
      if (pMVar14[uVar19].offset != 0) {
        iVar16 = *(int *)(pMVar14[uVar19].offset + 0x10);
        goto LAB_001130b8;
      }
      break;
    }
  }
LAB_001130b6:
  iVar16 = 0;
LAB_001130b8:
  pfVar18 = (float *)(*(int *)(iVar16 + local_70 * 4) + local_68);
  pfVar21[1] = *pfVar18;
  fVar24 = *pfVar18;
  pfVar21[5] = pfVar18[1];
  fVar25 = pfVar18[1];
  pfVar21[9] = pfVar18[2];
  if ((pfVar18[2] == 0.0) || (fVar25 == 0.0 || fVar24 == 0.0)) {
    fVar25 = pvVar6->y - pvVar1->y;
    fVar27 = pvVar6->z - pvVar1->z;
    fVar24 = pvVar2->z - pvVar1->z;
    fVar29 = pvVar6->x - pvVar1->x;
    fVar28 = pvVar2->x - pvVar1->x;
    fVar26 = pvVar2->y - pvVar1->y;
    local_38 = fVar24 * fVar29 - fVar27 * fVar28;
    fVar28 = fVar25 * fVar28 - fVar26 * fVar29;
    local_3c = fVar27 * fVar26 - fVar25 * fVar24;
    fVar24 = local_3c * local_3c + local_38 * local_38 + fVar28 * fVar28;
    if (fVar24 != 0.0) {
      fVar23 = (float10)invsqrt(fVar24);
      local_3c = (float)((float10)local_3c * fVar23);
      local_38 = (float)((float10)local_38 * fVar23);
    }
    uVar30 = float10::to_uint64_t((float10)local_38 * (float10)1023.0);
    uVar31 = float10::to_uint64_t(extraout_ST0 * (float10)511.0);
    uVar32 = float10::to_uint64_t((float10)local_3c * (float10)1023.0);
    iVar16 = 3;
    puVar9 = local_64;
    do {
      *puVar9 = ((uint)uVar30 & 0x7ff | (int)uVar31 << 0xb) << 0xb | (uint)uVar32 & 0x7ff;
      puVar9 = puVar9 + 4;
      iVar16 = iVar16 + -1;
    } while (iVar16 != 0);
  }
LAB_0011326c:
  local_68 = local_68 + 0xc;
  local_64 = local_64 + 0xc;
  pfVar21 = pfVar21 + 0xc;
  local_58 = local_58 + -1;
  if (local_58 == 0) goto LAB_0011329c;
  goto LAB_00112ef2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Background::updateViews(void)

{
  background_conflict8 *avatar;
  background_0x934_conflict3 pEVar1;
  background_conflict8 *pbVar2;
  
  pEVar1 = Game::SceneInfo.backgrounds.head;
  while (pEVar1 != (background_0x934_conflict3)0x0) {
    pbVar2 = ADJ(pEVar1);
    avatar = ADJ(pEVar1);
    pEVar1 = pEVar1->next;
    if (*(int *)&(pbVar2->avatar).field_0x908 == 0) {
      (*((avatar->avatar).object.vtable)->update)(avatar);
      ::avatar::updateBaseTransform((avatar *)avatar);
      ::avatar::getMaxScaleFromBasis((avatar *)avatar);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields
// Updates
// - Physics
// 
// - Not timers


void SetupBackgroundEntries(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  uint entryIndex;
  GlobalBackgroundEntry *local_c;
  int i;
  background_0x934_conflict3 entry;
  Model *instance;
  
  i = 0;
  if (0 < Game::BackgroundEntriesToSetUp) {
    local_c = GlobalBackgroundEntry_ARRAY_00512350;
    entry = Game::SceneInfo.backgrounds.head;
    do {
      for (; entry != (background_0x934_conflict3)0x0; entry = entry->next) {
        instance = ADJ(entry).avatar.modelInstance;
        bVar1 = local_c->shadowIndex;
        bVar3 = local_c->entryIndex;
        if (instance != (Model *)0x0) {
          entryIndex = (uint)bVar3;
          iVar4 = (int)(entryIndex * 2) >> 3;
          bVar2 = (byte)(entryIndex * 2) & 7;
          if (ModelInstance::Subres1Flags[entryIndex] != (uint)bVar1) {
            ModelInstance::Subres1Flags[entryIndex] = (uint)bVar1;
          }
          *(byte *)((int)(instance->varData).matrixLists + iVar4 + -0x10) =
               ~('\x03' << bVar2) & *(byte *)((int)(instance->varData).matrixLists + iVar4 + -0x10)
               | bVar1 << bVar2;
        }
        instance = ADJ(entry).avatar.shadowModel;
        if (instance != (Model *)0x0) {
          entryIndex = (uint)bVar3;
          iVar4 = (int)(entryIndex * 2) >> 3;
          bVar3 = (byte)(entryIndex * 2) & 7;
          if (ModelInstance::Subres1Flags[entryIndex] != (uint)bVar1) {
            ModelInstance::Subres1Flags[entryIndex] = (uint)bVar1;
          }
          *(byte *)((int)(instance->varData).matrixLists + iVar4 + -0x10) =
               ~('\x03' << bVar3) & *(byte *)((int)(instance->varData).matrixLists + iVar4 + -0x10)
               | bVar1 << bVar3;
        }
      }
      i = i + 1;
      local_c = local_c + 1;
      entry = Game::SceneInfo.backgrounds.head;
    } while (i < Game::BackgroundEntriesToSetUp);
  }
  Game::BackgroundEntriesToSetUp = 0;
  return;
}




void background::updateModelChildren_(int *param_1,float param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int local_4;
  
  local_4 = 0;
  if (0 < *param_1) {
    do {
      piVar1 = *(int **)(param_1[1] + local_4 * 4);
      iVar3 = 0;
      if (0 < *piVar1) {
        iVar2 = 0;
        do {
          FUN_001658b0(piVar1[1] + iVar2,param_2);
          iVar3 = iVar3 + 1;
          iVar2 = iVar2 + 0x2c;
        } while (iVar3 < *piVar1);
      }
      local_4 = local_4 + 1;
    } while (local_4 < *param_1);
  }
  return;
}




