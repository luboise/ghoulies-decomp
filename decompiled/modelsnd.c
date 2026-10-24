/* modelsnd.c - Models & nd-tree: mesh, skeleton, nd shaders, subresources */
#include "modelsnd.h"

void ModelInstance::setBlendTargetWeights(Model *instance,BlendTargetWeights *param_2)

{
  BlendTarget **ppBVar1;
  float *pfVar2;
  int iVar3;
  
  pfVar2 = param_2->weights + 2;
  ppBVar1 = instance->blendTargets + 1;
  iVar3 = 6;
  do {
    if (ppBVar1[-1] != (BlendTarget *)0x0) {
      ppBVar1[-1]->blendWeight = ((BlendTargetWeights *)(pfVar2 + -2))->weights[0];
    }
    if (*ppBVar1 != (BlendTarget *)0x0) {
      (*ppBVar1)->blendWeight = pfVar2[-1];
    }
    if (ppBVar1[1] != (BlendTarget *)0x0) {
      ppBVar1[1]->blendWeight = *pfVar2;
    }
    if (ppBVar1[2] != (BlendTarget *)0x0) {
      ppBVar1[2]->blendWeight = pfVar2[1];
    }
    if (ppBVar1[3] != (BlendTarget *)0x0) {
      ppBVar1[3]->blendWeight = pfVar2[2];
    }
    if (ppBVar1[4] != (BlendTarget *)0x0) {
      ppBVar1[4]->blendWeight = pfVar2[3];
    }
    if (ppBVar1[5] != (BlendTarget *)0x0) {
      ppBVar1[5]->blendWeight = pfVar2[4];
    }
    if (ppBVar1[6] != (BlendTarget *)0x0) {
      ppBVar1[6]->blendWeight = pfVar2[5];
    }
    ppBVar1 = ppBVar1 + 8;
    pfVar2 = pfVar2 + 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void ModelInstance::clearBlendTargets(Model *param_1)

{
  BlendTarget **ppBVar1;
  int blendTargetSets;
  
  ppBVar1 = param_1->blendTargets + 1;
  blendTargetSets = 6;
  do {
                    // Update blend targets in sets of 8
    if (ppBVar1[-1] != (BlendTarget *)0x0) {
      ppBVar1[-1]->blendWeight = 0.0;
    }
    if (*ppBVar1 != (BlendTarget *)0x0) {
      (*ppBVar1)->blendWeight = 0.0;
    }
    if (ppBVar1[1] != (BlendTarget *)0x0) {
      ppBVar1[1]->blendWeight = 0.0;
    }
    if (ppBVar1[2] != (BlendTarget *)0x0) {
      ppBVar1[2]->blendWeight = 0.0;
    }
    if (ppBVar1[3] != (BlendTarget *)0x0) {
      ppBVar1[3]->blendWeight = 0.0;
    }
    if (ppBVar1[4] != (BlendTarget *)0x0) {
      ppBVar1[4]->blendWeight = 0.0;
    }
    if (ppBVar1[5] != (BlendTarget *)0x0) {
      ppBVar1[5]->blendWeight = 0.0;
    }
    if (ppBVar1[6] != (BlendTarget *)0x0) {
      ppBVar1[6]->blendWeight = 0.0;
    }
    ppBVar1 = ppBVar1 + 8;
    blendTargetSets = blendTargetSets + -1;
  } while (blendTargetSets != 0);
  return;
}



void CombinedAnimChannel::combineABintoC
               (CombinedAnimChannel *channel1,CombinedAnimChannel *channel2,
               CombinedAnimChannel *outChannel,float param_4,uint numChannelsToCombine)

{
  KFTransform *pKVar1;
  KfTransform_0x18 pfVar1;
  KfTransform_0x20 pfVar2;
  KfTransform_0x24 pfVar3;
  float fVar1;
  
  fVar1 = 1.0 - param_4;
  pKVar1 = outChannel->boneTransforms;
  if ((short)numChannelsToCombine != 0) {
    pfVar1 = &channel1->boneTransforms[0].pos.z;
    numChannelsToCombine = numChannelsToCombine & 0xffff;
    pfVar2 = &channel2->boneTransforms[0].scale.y;
    do {
      pfVar3 = &outChannel->boneTransforms[0].scale.z;
      Quaternion::SLERP(&ADJ(pfVar1).rotQuat,&ADJ(pfVar2).rotQuat,
                        &outChannel->boneTransforms[0].rotQuat,param_4);
      outChannel->boneTransforms[0].scale.x =
           (ADJ(pfVar2)->scale).x * param_4 + (ADJ(pfVar1)->scale).x * fVar1;
      *(float *)((int)pfVar2 + ((int)pKVar1 - (int)channel2->boneTransforms)) =
           *(float *)((int)channel1 + (4 - (int)channel2->boneTransforms) + (int)pfVar2) * fVar1 +
           (ADJ(pfVar2)->scale).y * param_4;
      (ADJ(pfVar3)->scale).z =
           *(float *)((int)channel1 + (4 - (int)pKVar1) + (int)pfVar3) * fVar1 +
           (ADJ(pfVar2)->scale).z * param_4;
      outChannel->boneTransforms[0].pos.x =
           (ADJ(pfVar2)->pos).x * param_4 + (ADJ(pfVar1)->pos).x * fVar1;
      outChannel->boneTransforms[0].pos.y =
           (ADJ(pfVar2)->pos).y * param_4 + (ADJ(pfVar1)->pos).y * fVar1;
      outChannel->boneTransforms[0].pos.z =
           (ADJ(pfVar2)->pos).z * param_4 + (ADJ(pfVar1)->pos).z * fVar1;
      pfVar2 = pfVar2 + 10;
      pfVar1 = pfVar1 + 10;
      numChannelsToCombine = numChannelsToCombine - 1;
      outChannel = (CombinedAnimChannel *)pfVar3;
    } while (numChannelsToCombine != 0);
  }
  return;
}



void __fastcall

void ModelInstance::setAllBoneAffines(AffineTransform *newAffine,Model *param_2)

{
  ndSkeleton *pnVar1;
  int i;
  Skeleton *pSVar2;
  AffineTransform *bone;
  
  pSVar2 = param_2->skeleton;
  pnVar1 = param_2->ndSkeleton;
  if (pSVar2 == (Skeleton *)0x0) {
    pSVar2 = param_2->skeleton2;
  }
  bone = pSVar2->boneAffines;
  i = 0;
  if (0 < (int)pnVar1->numBones) {
    do {
      bone->m[0][0] = newAffine->m[0][0];
      bone->m[0][1] = newAffine->m[0][1];
      bone->m[0][2] = newAffine->m[0][2];
      bone->m[0][3] = newAffine->m[0][3];
      bone->m[1][0] = newAffine->m[1][0];
      bone->m[1][1] = newAffine->m[1][1];
      bone->m[1][2] = newAffine->m[1][2];
      bone->m[1][3] = newAffine->m[1][3];
      bone->m[2][0] = newAffine->m[2][0];
      bone->m[2][1] = newAffine->m[2][1];
      bone->m[2][2] = newAffine->m[2][2];
      bone->m[2][3] = newAffine->m[2][3];
      bone = bone + 1;
      i = i + 1;
    } while (i < (int)pnVar1->numBones);
  }
  pSVar2->ignoresGlobalBone = 1;
  return;
}



void UpdateBoneAffines(AnimInstance *anim,float delta,BoneList *boneList,ndSkeletonBone *ndBones,
                      int num_bones,AffineTransform *boneAffines)

{
  uint16_t *puVar1;
  void **callback;
  
                    // If we aren't applying it globally to all instances of the skeleton?
  if (boneList != (BoneList *)0x0) {
    if (boneList->numBones == 0) {
      callback = (void **)0x0;
      puVar1 = (ushort *)0x0;
    }
    else {
      callback = (void **)boneList->boneParentCallbacks->head;
      puVar1 = boneList->ids->head;
    }
    if (callback != (void **)0x0) {
      ApplyAnimToBones(anim,callback,puVar1,boneList,boneAffines,num_bones,ndBones,delta);
      return;
    }
  }
                    // If no parents, handle the bone alone
  handleRootBoneAffines(anim,boneAffines,num_bones,ndBones);
  return;
}



void KeyframeContext::CombineAnimChannels
               (AnimInstance *param_1,KFCAnimation *kfChannel,undefined4 param_3,
               float playbackSpeedXProgress,CombinedAnimChannel *outChannel,uint32_t someId,
               KeyframeHeader *param_7,KeyframeHeader *param_8)

{
  if (someId == 0x21) {
    FUN_00031fc0(param_7,param_3,param_1,param_8,kfChannel,playbackSpeedXProgress,outChannel);
  }
  else {
    if (someId == 0x22) {
      FUN_00032020(param_8,param_3,playbackSpeedXProgress,outChannel);
      return;
    }
    if (someId == 0x23) {
      FUN_0002d1a0(&kfChannel->animEventsRes->events[0].animEventType,playbackSpeedXProgress,
                   param_1->animRes->numBones);
      FUN_00031950(playbackSpeedXProgress,&LAB_0002d740);
      return;
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


Skeleton * SkeletonInstance::resetBoneAffines(Skeleton *instance)

{
  AffineTransform *affine;
  int i;
  
  i = 0;
  instance->ignoresGlobalBone = 1;
  affine = instance->boneAffines;
  if (0 < instance->numBones) {
    do {
      affine->m[0][0] = 1.0;
      affine->m[0][1] = 0.0;
      affine->m[0][2] = 0.0;
      affine->m[0][3] = 0.0;
      affine->m[1][0] = 0.0;
      affine->m[1][1] = 1.0;
      affine->m[1][2] = 0.0;
      affine->m[1][3] = 0.0;
      affine->m[2][0] = 0.0;
      affine->m[2][1] = 0.0;
      affine->m[2][2] = 1.0;
      affine->m[2][3] = 0.0;
      affine = affine + 1;
      i = i + 1;
    } while (i < instance->numBones);
  }
  return instance;
}




AffineTransform * Skeleton::getBoneAffineIntoGlobal(Skeleton *skeleton,uint index)

{
  if (skeleton->ignoresGlobalBone != 0) {
    return skeleton->boneAffines + index;
  }
  ::skeleton::gotten_affine.m[0][0] = skeleton[index].boneAffines[0].m[0][0];
  ::skeleton::gotten_affine.m[0][1] = skeleton[index].boneAffines[0].m[1][0];
  ::skeleton::gotten_affine.m[0][2] = skeleton[index].boneAffines[0].m[2][0];
  ::skeleton::gotten_affine.m[0][3] = (float)skeleton[index + 1].numBones;
  ::skeleton::gotten_affine.m[1][0] = skeleton[index].boneAffines[0].m[0][1];
  ::skeleton::gotten_affine.m[1][1] = skeleton[index].boneAffines[0].m[1][1];
  ::skeleton::gotten_affine.m[1][2] = skeleton[index].boneAffines[0].m[2][1];
  ::skeleton::gotten_affine.m[1][3] = (float)skeleton[index + 1].ignoresGlobalBone;
  ::skeleton::gotten_affine.m[2][0] = skeleton[index].boneAffines[0].m[0][2];
  ::skeleton::gotten_affine.m[2][1] = skeleton[index].boneAffines[0].m[1][2];
  ::skeleton::gotten_affine.m[2][2] = skeleton[index].boneAffines[0].m[2][2];
  ::skeleton::gotten_affine.m[2][3] = *(float *)&skeleton[index + 1].field_0x8;
  return &::skeleton::gotten_affine;
}




void Assets::ModelResource::LoadTilesSubresource(TilesSubresource *tiles,int base,DataViewList *dvl)

{
  uint32_t uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint32_t *puVar5;
  int local_c;
  uint i;
  uint resPointer;
  
  if (tiles->somePtr != (void *)0x0) {
    tiles->somePtr = (void *)((int)tiles->somePtr + base);
  }
  if (tiles->somePtr2 != (void *)0x0) {
    tiles->somePtr2 = (void *)((int)tiles->somePtr2 + base);
  }
  if (tiles->tiles != (ModelTile *)0x0) {
    tiles->tiles = (ModelTile *)((int)&tiles->tiles->field0_0x0 + base);
    i = 0;
    if (tiles->product != 0) {
      local_c = 0;
      do {
        resPointer = *(uint *)((int)&tiles->tiles->resPtr + local_c);
        if (resPointer != 0) {
          uVar4 = 0;
          if (dvl->numItems != 0) {
            puVar5 = &dvl->items[0].size;
            uVar2 = 0;
            do {
              uVar1 = *puVar5;
              if (resPointer < uVar2 + uVar1) {
                iVar3 = (dvl->items[uVar4].offset - uVar2) + resPointer;
                goto LAB_0004f58b;
              }
              uVar4 = uVar4 + 1;
              puVar5 = puVar5 + 2;
              uVar2 = uVar2 + uVar1;
            } while (uVar4 < dvl->numItems);
          }
          iVar3 = 0;
LAB_0004f58b:
          *(int *)((int)&tiles->tiles->resPtr + local_c) = iVar3;
          XGRAPHC::XGSetVertexBufferHeader
                    (*(UINT *)((int)&tiles->tiles->resSize + local_c),8,0,D3DPOOL_DEFAULT,
                     (void *)((int)&tiles->tiles->bufferHeader + local_c),0);
          D3D8::D3DResource_Register
                    ((D3DResource *)((int)&tiles->tiles->bufferHeader + local_c),
                     *(PVOID *)((int)&tiles->tiles->resPtr + local_c));
        }
        i = i + 1;
        local_c = local_c + 0x1c;
      } while (i < tiles->product);
    }
  }
  if (*(int *)(tiles + 1) != 0) {
    *(int *)(tiles + 1) = *(int *)(tiles + 1) + base;
  }
  return;
}




uint32_t ModelSubresource0x2::getSubres0x2IndexById(ModelSubresource0x2 *subres,short id)

{
  uint32_t i;
  ModelSubresource0x2Entry *entry;
  void *next;
  
  i = 0;
  entry = (ModelSubresource0x2Entry *)0x0;
  do {
    if (entry == (ModelSubresource0x2Entry *)0x0) {
      entry = subres->entries;
      next = entry + subres->numEntries;
    }
    else {
      entry = entry + 1;
      next = subres->entries + subres->numEntries;
    }
    while( true ) {
      if (next <= entry) {
        return i;
      }
      if (entry->id == id) break;
      entry = entry + 1;
    }
    i = i + 1;
  } while( true );
}




void ModelSubresource0x8::runCallback(undefined *fn,Subresource0x8 *subres)

{
  uint height;
  int index;
  int i;
  int j;
  vec3 local_c;
  
  if (subres->numX != 0) {
    height = (uint)subres->numZ;
    i = 0;
    do {
      j = 0;
      if (height != 0) {
        do {
          local_c.x = (float)i * subres->scaleX + subres->minX;
          index = (uint)subres->numX * j + i;
          local_c.y = 0.0;
          local_c.z = (float)j * subres->scaleZ + subres->minZ;
          (*(code *)fn)(subres,&local_c,subres->entries + index,&subres->entries[index].field1_0x1,
                        &subres->entries[index].field2_0x2);
          height = (uint)subres->numZ;
          j = j + 1;
        } while (j < (int)height);
      }
      i = i + 1;
    } while (i < (int)(uint)subres->numX);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void TexturesSubresource::updatePointers(TexturesSubresource *param_1,int base,DataViewList *dvl)

{
  TextureDescriptor *pTVar1;
  uint32_t uVar2;
  PVOID pvVar3;
  uint uVar4;
  uint32_t *puVar5;
  uint local_4;
  
  param_1->textures = (TextureDescriptor **)((int)param_1->textures + base);
  local_4 = 0;
  if (param_1->numTextures != 0) {
    do {
      param_1->textures[local_4] =
           (TextureDescriptor *)((int)&param_1->textures[local_4]->format + base);
      pTVar1 = param_1->textures[local_4];
      uVar4 = 0;
      if (pTVar1->dataSize == 0) {
        pTVar1->dataOffset = (PVOID)0x0;
      }
      else {
        if (dvl->numItems != 0) {
          puVar5 = &dvl->items[0].size;
          pvVar3 = (PVOID)0x0;
          do {
            uVar2 = *puVar5;
            if (pTVar1->dataOffset < (PVOID)((int)pvVar3 + uVar2)) {
              pTVar1->dataOffset =
                   (PVOID)((dvl->items[uVar4].offset - (int)pvVar3) + (int)pTVar1->dataOffset);
              goto LAB_000527ab;
            }
            uVar4 = uVar4 + 1;
            puVar5 = puVar5 + 2;
            pvVar3 = (PVOID)((int)pvVar3 + uVar2);
          } while (uVar4 < dvl->numItems);
        }
        pTVar1->dataOffset = (PVOID)0x0;
      }
LAB_000527ab:
      local_4 = local_4 + 1;
    } while (local_4 < param_1->numTextures);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


TextureDescriptor * ModelDescriptor::getTextureByIndex(ModelDescriptor *param_1,uint indexInList)

{
  ModelFooterEntry *subresPtr;
  uint i;
  int iVar1;
  
  i = 0;
  if (param_1->numFooterEntries != 0) {
    subresPtr = param_1->footerEntries;
    do {
      if (subresPtr->subresourceType == Textures) {
        i = param_1->footerEntries[i].offset;
        goto LAB_000528e1;
      }
      i = i + 1;
      subresPtr = subresPtr + 1;
    } while (i < param_1->numFooterEntries);
  }
  i = 0;
LAB_000528e1:
  iVar1 = *(int *)(*(int *)(i + 4) + indexInList * 4);
  return (TextureDescriptor *)(*(int *)(iVar1 + 4) + (uint)*(byte *)(iVar1 + 0x12) * 0x14 + iVar1);
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void ModelDescriptor::processDescriptor(ModelDescriptor *desc,uint i,DataViewList *dvl)

{
  int iVar1;
  int *piVar2;
  uint descriptorBase;
  ModelSubresource *res;
  uint offset;
  char *basePtr;
  ModelFooterEntry *footer_entry;
  ModelFooterEntry *sub_main_desc;
  
  descriptorBase = i;
  desc->footerEntries = (ModelFooterEntry *)((int)&desc->footerEntries->subresourceType + i);
  i = 0;
  if (desc->numFooterEntries != 0) {
    do {
      footer_entry = desc->footerEntries + i;
      switch(desc->footerEntries[i].subresourceType) {
      case Model:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        sub_main_desc = (ModelFooterEntry *)desc->footerEntries[i].offset;
        res = (ModelSubresource *)(sub_main_desc->subresourceType + descriptorBase);
        sub_main_desc->subresourceType = (ModelSubresourceType)res;
        if (dvl != (DataViewList *)0x0) {
          offset = DataViewList::GetResourceByAddress(dvl,(void *)sub_main_desc->offset);
          sub_main_desc->offset = offset;
        }
        ModelSubresource::process(res,(int)res,(void *)sub_main_desc->offset);
        break;
      case BoneAffines:
      case SomeType0x3:
      case AnimColliders:
      case ModelMatrix:
      case Subresource0x8:
      case RigidBoneIndices:
      case Subresource0x8|BoneAffines:
      case Unknown0xc|SomeType0x3:
      case 0x14:
      case 0x15:
        offset = footer_entry->offset;
LAB_00052af2:
        footer_entry->offset = offset + descriptorBase;
        break;
      case Colliders:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        ColliderSet::processDescriptor
                  ((ColliderSetDescriptor *)desc->footerEntries[i].offset,descriptorBase);
        break;
      case Textures:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        TexturesSubresource::updatePointers
                  ((TexturesSubresource *)desc->footerEntries[i].offset,descriptorBase,dvl);
        break;
      case Subresource0x8|SomeType0x3:
      case 0x17:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        offset = desc->footerEntries[i].offset;
        iVar1 = *(int *)(offset + 0xc);
        if (iVar1 != 0) {
          *(uint *)(offset + 0xc) = iVar1 + descriptorBase;
        }
        break;
      case Unknown0xc:
      case Unknown0xd:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        offset = desc->footerEntries[i].offset;
        if (*(int *)(offset + 4) != 0) {
          *(uint *)(offset + 4) = *(int *)(offset + 4) + descriptorBase;
        }
        TexturesSubresource::updatePointers((TexturesSubresource *)(offset + 8),descriptorBase,dvl);
        break;
      case Unknown0xc|BoneAffines:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        ModelSubresource0xe::processDescriptor
                  ((ModelSubresource0xe *)desc->footerEntries[i].offset,(void *)descriptorBase);
        break;
      case 0x10:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        offset = desc->footerEntries[i].offset;
        if (*(int *)(offset + 4) != 0) {
          *(uint *)(offset + 4) = *(int *)(offset + 4) + descriptorBase;
        }
        if (*(int *)(offset + 0xc) != 0) {
          *(uint *)(offset + 0xc) = *(int *)(offset + 0xc) + descriptorBase;
        }
        if (*(int *)(offset + 8) != 0) {
          *(uint *)(offset + 8) = *(int *)(offset + 8) + descriptorBase;
        }
        break;
      case Subresource0x11:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        Subresource0x11::process
                  ((void *)descriptorBase,(Subresource0x11 *)desc->footerEntries[i].offset);
        break;
      case Tiles:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        Assets::ModelResource::LoadTilesSubresource
                  ((TilesSubresource *)desc->footerEntries[i].offset,descriptorBase,dvl);
        break;
      case Tiles|ModelFlags:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        piVar2 = (int *)desc->footerEntries[i].offset;
        if (piVar2[1] != 0) {
          piVar2[1] = piVar2[1] + descriptorBase;
        }
        if (*piVar2 != 0) {
          *piVar2 = *piVar2 + descriptorBase;
        }
        break;
      case 0x16:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        FUN_00051f60(desc->footerEntries[i].offset,descriptorBase);
        break;
      case 0x18:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        FUN_00053270();
        break;
      case 0x19:
      case 0x1a:
        footer_entry->offset = footer_entry->offset + descriptorBase;
        footer_entry = (ModelFooterEntry *)desc->footerEntries[i].offset;
        offset = footer_entry->offset;
        if (offset != 0) goto LAB_00052af2;
      }
      i = i + 1;
    } while (i < desc->numFooterEntries);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void ModelDescriptor::ctor(ModelDescriptor *descriptor)

{
  ModelRuntimeContext *ctx;
  uint i;
  TilesSubresource *pTVar1;
  Subresource0xd *pSVar2;
  Subresource0x11 *pSVar3;
  ColliderSetDescriptor *colSet;
  int *piVar5;
  undefined4 *puVar6;
  TexturesSubresource *pTVar7;
  ModelFooterEntry *entries;
  ModelFooterEntry *piVar4;
  
  ctx = malloc_(0x30);
  i = 0;
  descriptor->runtimeCtx = ctx;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == Tiles) {
        pTVar1 = (TilesSubresource *)descriptor->footerEntries[i].offset;
        goto LAB_00052ba7;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  pTVar1 = (TilesSubresource *)0x0;
LAB_00052ba7:
  ctx->subres0x12 = pTVar1;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == (Subresource0x8|BoneAffines)) {
        i = descriptor->footerEntries[i].offset;
        goto LAB_00052bcc;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  i = 0;
LAB_00052bcc:
  ctx->type10Index = i;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == Unknown0xd) {
        pSVar2 = (Subresource0xd *)descriptor->footerEntries[i].offset;
        goto LAB_00052bf6;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  pSVar2 = (Subresource0xd *)0x0;
LAB_00052bf6:
  ctx->subresource0xd = pSVar2;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == 0x15) {
        i = descriptor->footerEntries[i].offset;
        goto LAB_00052c1c;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  i = 0;
LAB_00052c1c:
  ctx->type0x15Index = i;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == 0x10) {
        i = descriptor->footerEntries[i].offset;
        goto LAB_00052c46;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  i = 0;
LAB_00052c46:
  ctx->type0x10Index = i;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == Subresource0x11) {
        pSVar3 = (Subresource0x11 *)descriptor->footerEntries[i].offset;
        goto LAB_00052c6c;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  pSVar3 = (Subresource0x11 *)0x0;
LAB_00052c6c:
  ctx->subres0x11 = pSVar3;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == (Unknown0xc|BoneAffines)) {
        i = descriptor->footerEntries[i].offset;
        goto LAB_00052c96;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  i = 0;
LAB_00052c96:
  ctx->type0xeIndex = i;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == Colliders) {
        colSet = (ColliderSetDescriptor *)descriptor->footerEntries[i].offset;
        goto LAB_00052cbc;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  colSet = (ColliderSetDescriptor *)0x0;
LAB_00052cbc:
  ctx->colliders = colSet;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == Unknown0xc) {
        piVar5 = (int *)descriptor->footerEntries[i].offset;
        goto LAB_00052ce6;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  piVar5 = (int *)0x0;
LAB_00052ce6:
  ctx->type0xcIndex = piVar5;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == Model) {
        puVar6 = (undefined4 *)descriptor->footerEntries[i].offset;
        goto LAB_00052d0c;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  puVar6 = (undefined4 *)0x0;
LAB_00052d0c:
  ctx->modelSubresource = (ModelSubresource *)*puVar6;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    piVar4 = descriptor->footerEntries;
    do {
      if (piVar4->subresourceType == Textures) {
        pTVar7 = (TexturesSubresource *)descriptor->footerEntries[i].offset;
        goto LAB_00052d36;
      }
      i = i + 1;
      piVar4 = piVar4 + 1;
    } while (i < descriptor->numFooterEntries);
  }
  pTVar7 = (TexturesSubresource *)0x0;
LAB_00052d36:
  ctx->textureSubresource = pTVar7;
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == 0x18) {
        piVar5 = (int *)descriptor->footerEntries[i].offset;
        goto LAB_00052d5c;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  piVar5 = (int *)0x0;
LAB_00052d5c:
  ctx->subres0x18 = piVar5;
  ModelResource::loadModelMain(descriptor->runtimeCtx->modelSubresource);
  i = 0;
  if (descriptor->numFooterEntries != 0) {
    entries = descriptor->footerEntries;
    do {
      if (entries->subresourceType == Textures) {
        pTVar7 = (TexturesSubresource *)descriptor->footerEntries[i].offset;
        if (pTVar7 != (TexturesSubresource *)0x0) {
          CreateTexturesForModel(pTVar7,descriptor);
        }
        break;
      }
      i = i + 1;
      entries = entries + 1;
    } while (i < descriptor->numFooterEntries);
  }
  piVar5 = descriptor->runtimeCtx->type0xcIndex;
  if (piVar5 != (int *)0x0) {
    CreateTexturesForModel((TexturesSubresource *)(piVar5 + 2),descriptor);
  }
  pSVar2 = descriptor->runtimeCtx->subresource0xd;
  if (pSVar2 != (Subresource0xd *)0x0) {
    CreateTexturesForModel((TexturesSubresource *)&pSVar2->numTextures,descriptor);
  }
  return;
}




void ModelDescriptor::dtor(int *param_1)

{
  void *mem;
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  HeapTableEntry *pHVar5;
  
  FUN_00156870(*(undefined4 *)(param_1[4] + 0x24));
  uVar2 = 0;
  if (param_1[1] != 0) {
    piVar4 = (int *)*param_1;
    do {
      if (*piVar4 == 7) {
        iVar3 = ((int *)*param_1)[uVar2 * 2 + 1];
        if (iVar3 != 0) {
          FUN_00052850(iVar3);
        }
        break;
      }
      uVar2 = uVar2 + 1;
      piVar4 = piVar4 + 2;
    } while (uVar2 < (uint)param_1[1]);
  }
  if (*(int *)(param_1[4] + 8) != 0) {
    FUN_00052850(*(int *)(param_1[4] + 8) + 8);
  }
  if (*(int *)(param_1[4] + 0xc) != 0) {
    FUN_00052850(*(int *)(param_1[4] + 0xc) + 8);
  }
  mem = (void *)param_1[4];
  iVar3 = FindHeapOf(mem);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar3].heapHandle == (HANDLE)0x0) {
    pHVar5 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar5 = g_HeapTableBase + iVar3;
  }
  runtime::CurrentHeapToAllocateFrom = iVar3;
  XAPILIB::HeapFree(pHVar5->heapHandle,0,mem);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void ModelDescriptor::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_00052f17;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_00052f17:
  pRVar2->typeStr = "model";
  pRVar2->processDescriptor = processDescriptor;
  pRVar2->ctor = ctor;
  pRVar2->dtor = dtor;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


uint ModelDescriptor::get0x3SubresSize(ModelDescriptor *param_1)

{
  uint i;
  ModelFooterEntry *pMVar1;
  ModelSubres0x3Descriptor *piVar1;
  
  i = 0;
  if (param_1->numFooterEntries != 0) {
    pMVar1 = param_1->footerEntries;
    do {
      if (pMVar1->subresourceType == SomeType0x3) {
        piVar1 = (ModelSubres0x3Descriptor *)param_1->footerEntries[i].offset;
        if (piVar1 == (ModelSubres0x3Descriptor *)0x0) {
          return 0;
        }
        return piVar1->numValues * 0x98 + 4;
      }
      i = i + 1;
      pMVar1 = pMVar1 + 1;
    } while (i < param_1->numFooterEntries);
  }
  return 0;
}




uint8_t ModelDescriptor::getBoneIdxFromRigid(ModelDescriptor *modelRes,short index)

{
  uint i;
  ModelFooterEntry *footer_entry;
  ModelSubresource0x9 *subres9;
  
  i = 0;
  if (modelRes->numFooterEntries != 0) {
    footer_entry = modelRes->footerEntries;
    do {
      if (footer_entry->subresourceType == RigidBoneIndices) {
        subres9 = (ModelSubresource0x9 *)modelRes->footerEntries[i].offset;
        if (subres9 == (ModelSubresource0x9 *)0x0) {
          return 0xff;
        }
        return subres9->indices[index];
      }
      i = i + 1;
      footer_entry = footer_entry + 1;
    } while (i < modelRes->numFooterEntries);
  }
  return 0xff;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Subresource0x11::process(void *descriptorBase,Subresource0x11 *param_2)

{
  int iVar1;
  int i;
  
  if (param_2->vertexLists != (VertexList *)0x0) {
    param_2->vertexLists =
         (VertexList *)((int)&param_2->vertexLists->numVertices + (int)descriptorBase);
    i = 0;
    if (param_2->count != 0) {
      do {
        param_2->vertexLists[i].vertices =
             (vec3 *)((int)&(param_2->vertexLists[i].vertices)->x + (int)descriptorBase);
        i = i + 1;
      } while (i < (int)(uint)param_2->count);
    }
  }
  if ((param_2->drawLists != (TriangleDrawList *)0x0) &&
     (param_2->drawLists =
           (TriangleDrawList *)((int)&param_2->drawLists->numTriangleDraws + (int)descriptorBase),
     param_2->count != 0)) {
    i = 0;
    do {
      param_2->drawLists[i].triangleDraws =
           (TriangleDraw *)
           ((int)&(param_2->drawLists[i].triangleDraws)->index0 + (int)descriptorBase);
      i = i + 1;
    } while (i < (int)(uint)param_2->count);
  }
  if (param_2->somePtr3 != 0) {
    param_2->somePtr3 = param_2->somePtr3 + (int)descriptorBase;
    i = 0;
    if (param_2->count != 0) {
      do {
        iVar1 = *(int *)(param_2->somePtr3 + i * 4);
        if (iVar1 != 0) {
          *(int *)(param_2->somePtr3 + i * 4) = iVar1 + (int)descriptorBase;
        }
        i = i + 1;
      } while (i < (int)(uint)param_2->count);
    }
  }
  return;
}




void ModelSubresource0xe::processDescriptor(ModelSubresource0xe *subres,void *descriptorBase)

{
  uint32_t **ppuVar1;
  uint i;
  
  if (subres->somePtr1 != (uint32_t *)0x0) {
    subres->somePtr1 = (uint32_t *)((int)subres->somePtr1 + (int)descriptorBase);
    subres->somePtr2 = (uint32_t *)((int)subres->somePtr2 + (int)descriptorBase);
    if (subres->numSamplerAssignments != 0) {
      subres->samplerAssignments =
           (PixelShaderSamplerAssignment *)
           ((int)&subres->samplerAssignments->numAssignments + (int)descriptorBase);
      i = 0;
      if (subres->numSamplerAssignments != 0) {
        do {
          if (subres->samplerAssignments[i].numAssignments != 0) {
            ppuVar1 = &subres->samplerAssignments[i].assignments;
            *ppuVar1 = (uint32_t *)((int)*ppuVar1 + (int)descriptorBase);
          }
          i = i + 1;
        } while (i < subres->numSamplerAssignments);
      }
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Assets::TextureDescriptor::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_00053377;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_00053377:
  pRVar2->typeStr = "texture";
  pRVar2->processDescriptor = processMetadata;
  pRVar2->ctor = ctor;
  pRVar2->dtor = switchD_000d4179::EmptyFunction;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

TextureHeader *
Graphics::CreateTextureHeader
          (ushort width,ushort height,uint8_t mipMapLevels,D3DFORMAT format,void *memory)

{
  TextureHeader *d3d;
  SIZE_T size;
  allocatedTex *new_memory;
  int _clear_size;
  int *_clear_ptr;
  
  d3d = malloc_(0x30);
  _clear_size = 0xc;
  _clear_ptr = &d3d->format;
                    // memset 0
  for (; _clear_size != 0; _clear_size = _clear_size + -1) {
    *_clear_ptr = 0;
    _clear_ptr = _clear_ptr + 1;
  }
  d3d->mipMapLevels = mipMapLevels;
  d3d->height = height;
  d3d->width = width;
  d3d->d3dResourceOffset = 0x1c;
  d3d->format = format;
  d3d->flag1 = false;
  d3d->textureMemory = (allocatedTex *)0x0;
  d3d->texSize = 0;
  d3d->flag2 = false;
  d3d->flag3 = false;
  XGRAPHC::XGSetTextureHeader
            ((uint)width,(uint)height,(uint)mipMapLevels,D3DUSAGE_BORDERSOURCE_COLOR,format,
             D3DPOOL_DEFAULT,&d3d->texture,0,0);
  d3d->texSize = size;
  if (memory == (void *)0x0) {
    new_memory = (allocatedTex *)XAPILIB::XPhysicalAlloc(size,0xffffffff,0x80,0x404);
    d3d->textureMemory = new_memory;
  }
  else {
    d3d->textureMemory = memory;
  }
  D3D8::D3DResource_Register
            ((D3DResource *)((int)&d3d->format + d3d->d3dResourceOffset),d3d->textureMemory);
  return d3d;
}




void Assets::TextureDescriptor::ctor(TextureDescriptor *tex)

{
  int i_ptr;
  int i;
  PVOID pBase;
  
  pBase = tex->dataOffset;
  tex->field_0x12 = 0;
  tex->isMultiTexture = (bool)-(1 < tex->texCount);
  if ((pBase != (PVOID)0x0) && (i = 0, tex->texCount != 0)) {
    i_ptr = 0;
    do {
      XGRAPHC::XGSetTextureHeader
                ((uint)tex->width,(uint)tex->height,(uint)(byte)tex->mipLevels,
                 D3DUSAGE_BORDERSOURCE_COLOR,tex->format,D3DPOOL_DEFAULT,
                 (D3DTexture *)((int)&tex->format + tex->headerSize + i_ptr),0,0);
      D3D8::D3DResource_Register((D3DResource *)((int)&tex->format + tex->headerSize + i_ptr),pBase)
      ;
      pBase = (PVOID)((int)pBase + tex->dataSize);
      i = i + 1;
      i_ptr = i_ptr + 0x14;
    } while (i < (int)(uint)tex->texCount);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names

void Assets::TextureDescriptor::processMetadata
               (TextureDescriptor *texParams,char *metaStart,DataViewList *resBytes)

{
  PVOID offset;
  
  if (texParams->dataSize != 0) {
    offset = (PVOID)DataViewList::GetResourceByAddress(resBytes,texParams->dataOffset);
    texParams->dataOffset = offset;
    return;
  }
  texParams->dataOffset = (PVOID)0x0;
  return;
}




Model * Model::init(Model *model)

{
  ModelVariableData *varData;
  Skeleton *str;
  int *piVar1;
  uint uVar2;
  Model *header_instance;
  ndMtxArray *pnVar3;
  ndMtxArray *pnVar4;
  Skeleton *dst;
  uint uVar3;
  int iVar4;
  ModelFooterEntry *pMVar5;
  ModelVariableData *pMVar6;
  Model *pMVar7;
  ModelDescriptor *mesh_header;
  ModelSubresource *subres;
  
  mesh_header = model->descriptor;
  subres = mesh_header->runtimeCtx->modelSubresource;
  uVar2 = 0;
  if (mesh_header->numFooterEntries != 0) {
    pMVar5 = mesh_header->footerEntries;
    do {
      if (pMVar5->subresourceType == SomeType0x3) {
        piVar1 = (int *)mesh_header->footerEntries[uVar2].offset;
        if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
          uVar2 = ModelDescriptor::get0x3SubresSize(mesh_header);
          header_instance = malloc_(uVar2 + 0x2a0 + subres->varSize);
          uVar2 = ModelDescriptor::get0x3SubresSize(mesh_header);
          memcpy(header_instance,model,uVar2 + 0x2a0 + subres->varSize);
          header_instance->ptrToSubres0x3 =
               (ModelSubres0x3Descriptor *)
               ((int)(header_instance->varData).matrixLists + (subres->varSize - 4));
          MeshHeaderInstance::registerSubres0x3s(header_instance);
          goto LAB_000f8825;
        }
        break;
      }
      uVar2 = uVar2 + 1;
      pMVar5 = pMVar5 + 1;
    } while (uVar2 < mesh_header->numFooterEntries);
  }
  header_instance = malloc_(subres->varSize + 0x2a0);
  memcpy(header_instance,model,subres->varSize + 0x2a0);
LAB_000f8825:
  uVar2 = subres->varSize;
  varData = &header_instance->varData;
  pMVar6 = varData;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    pMVar6->headerData = 0;
    pMVar6 = (ModelVariableData *)pMVar6->matrixLists;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)&pMVar6->headerData = 0;
    pMVar6 = (ModelVariableData *)((int)&pMVar6->headerData + 1);
  }
  MeshHeader::initialiseRootNodeMatrices(subres,varData);
                    // if runtime ctx and root ctx out of date then copy the matrices across?
  pnVar3 = (ndMtxArray *)MeshHeader::getFirstDescendantByType(subres,0,"ndMtxArray");
  pnVar4 = (ndMtxArray *)
           MeshHeader::getFirstDescendantByType
                     (header_instance->descriptor->runtimeCtx->modelSubresource,0,"ndMtxArray");
  if ((pnVar3 != (ndMtxArray *)0x0) && (pnVar4 != (ndMtxArray *)0x0)) {
    FUN_001560a0(pnVar3,&model->varData,pnVar4,varData);
  }
  FUN_00035ba0();
  header_instance->boneIndices[0] = 0xffffffff;
  header_instance->boneIndices[1] = 0xffffffff;
  header_instance->boneIndices[2] = 0xffffffff;
  header_instance->boneIndices[3] = 0xffffffff;
  header_instance->boneIndices[4] = 0xffffffff;
  header_instance->boneIndices[5] = 0xffffffff;
  header_instance->boneIndices[6] = 0xffffffff;
  header_instance->boneIndices[7] = 0xffffffff;
  header_instance->boneIndices[8] = 0xffffffff;
  header_instance->boneIndices[9] = 0xffffffff;
  header_instance->boneIndices[10] = 0xffffffff;
  header_instance->boneIndices[0xb] = 0xffffffff;
  header_instance->boneIndices[0xc] = 0xffffffff;
  header_instance->boneIndices[0xd] = 0xffffffff;
  header_instance->boneIndices[0xe] = 0xffffffff;
  header_instance->boneIndices[0xf] = 0xffffffff;
  header_instance->boneIndices[0x10] = 0xffffffff;
  header_instance->boneIndices[0x11] = 0xffffffff;
  header_instance->boneIndices[0x12] = 0xffffffff;
  header_instance->boneIndices[0x13] = 0xffffffff;
  str = model->skeleton2;
  if (str == (Skeleton *)0x0) {
    header_instance->skeleton2 = (Skeleton *)0x0;
  }
  else {
    uVar2 = str->numBones * 0x40 + 0x10;
    dst = malloc_(uVar2);
    memcpy(dst,str,uVar2);
    header_instance->skeleton2 = dst;
  }
  header_instance->skeleton = (Skeleton *)0x0;
  MeshHeaderInstance::loadMorphTargets(header_instance);
  FUN_000f8b80();
  pMVar7 = header_instance;
  for (iVar4 = 0x56; pMVar7 = (Model *)&pMVar7->field1_0x4, iVar4 != 0; iVar4 = iVar4 + -1) {
    *(ModelSubresource **)pMVar7 = (ModelSubresource *)0x0;
  }
  header_instance->modelPassedToBG = (ModelSubresource *)0x0;
  ModelSubresource::loadShaders(&header_instance->modelPassedToBG,subres,&header_instance->varData);
  return header_instance;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


Model * Model::copyWithPoseFrom(char *someAID,Model *existing)

{
  Model *pMVar2;
  int iVar3;
  BOOL BVar4;
  Skeleton *pSVar5;
  char *keyName;
  Skeleton *pSVar6;
  uint iVar7;
  ModelDescriptor *pMVar8;
  Model *pMVar9;
  ModelDescriptor *local_1c;
  ModelDescriptor *local_18;
  char *local_14;
  uint *local_10;
  AffineTransform *local_c;
  AffineTransform *local_8;
  void *local_4;
  ModelSubresource *pMVar1;
  
  if (*(int *)someAID == 0x5f646961) {
    Assets::GetResourceBytes(someAID,&local_1c);
    pMVar8 = local_1c;
                    // load or exit
    if (local_1c != (ModelDescriptor *)0x0) {
      pMVar2 = ctor(local_1c,1,1);
      local_18 = existing->descriptor;
      iVar7 = 0;
      while( true ) {
        if (existing->ndSkeleton == (ndSkeleton *)0x0) {
          iVar3 = 0;
        }
        else {
          iVar3 = ndSkeleton::getNumBones(existing->ndSkeleton);
        }
        if (iVar3 <= (int)iVar7) break;
        pMVar1 = local_18->runtimeCtx->modelSubresource;
        if (pMVar1 == (ModelSubresource *)0x0) {
          keyName = (char *)0x0;
        }
        else {
          MeshHeader::getMapEntryByIndex(pMVar1,iVar7,&local_14,&local_4);
          keyName = local_14;
        }
        pMVar1 = pMVar8->runtimeCtx->modelSubresource;
        if (pMVar1 != (ModelSubresource *)0x0) {
          BVar4 = ModelSubresource::getMapValue(pMVar1,keyName,&local_10);
          if ((BVar4 != 0) && (local_10 != (uint *)0x0)) {
            pSVar5 = pMVar2->skeleton;
            if (pSVar5 == (Skeleton *)0x0) {
              pSVar5 = pMVar2->skeleton2;
            }
            pSVar6 = existing->skeleton;
            if (pSVar6 == (Skeleton *)0x0) {
              pSVar6 = existing->skeleton2;
            }
            local_c = Skeleton::getBoneAffineIntoGlobal(pSVar5,*local_10);
            local_8 = Skeleton::getBoneAffineIntoGlobal(pSVar6,iVar7);
            local_c->m[0][0] = local_8->m[0][0];
            local_c->m[0][1] = local_8->m[0][1];
            local_c->m[0][2] = local_8->m[0][2];
            local_c->m[0][3] = local_8->m[0][3];
            local_c->m[1][0] = local_8->m[1][0];
            local_c->m[1][1] = local_8->m[1][1];
            local_c->m[1][2] = local_8->m[1][2];
            local_c->m[1][3] = local_8->m[1][3];
            local_c->m[2][0] = local_8->m[2][0];
            local_c->m[2][1] = local_8->m[2][1];
            local_c->m[2][2] = local_8->m[2][2];
            local_c->m[2][3] = local_8->m[2][3];
            pMVar8 = local_1c;
          }
        }
        iVar7 = iVar7 + 1;
      }
      pSVar5 = pMVar2->skeleton;
      pSVar6 = pSVar5;
      if (pSVar5 == (Skeleton *)0x0) {
        pSVar6 = pMVar2->skeleton2;
      }
      if (pSVar6 != (Skeleton *)0x0) {
        if (pSVar5 == (Skeleton *)0x0) {
          pSVar5 = pMVar2->skeleton2;
        }
        pSVar5->ignoresGlobalBone = 1;
      }
      pMVar9 = pMVar2;
      for (iVar3 = 0x56; pMVar9 = (Model *)&pMVar9->field1_0x4, iVar3 != 0; iVar3 = iVar3 + -1) {
        *(ModelSubresource **)pMVar9 = (ModelSubresource *)0x0;
      }
      return pMVar2;
    }
    runtime::ExitGame(2);
  }
  return (Model *)0x0;
}




undefined4 ModelResource::dropResource(Asset *param_1)

{
  Asset *pAVar1;
  
  if (g_NewAssetBuffer_->tail == g_NewAssetBuffer_->end) {
    g_NewAssetBuffer_ = (Buffer<> *)runtime::ExtendArray((Buffer *)g_NewAssetBuffer_);
  }
  pAVar1 = g_NewAssetBuffer_->tail;
  g_NewAssetBuffer_->tail = (Asset *)(pAVar1->name + g_NewAssetBuffer_->valueSize);
  *(Asset **)pAVar1->name = param_1;
  *(undefined4 *)(pAVar1->name + 4) = DAT_005079dc;
  if (*(int *)(param_1[4].name + 0x6c) != 0) {
    FUN_00165a60(*(int *)(param_1[4].name + 0x6c));
    param_1[4].name[0x6c] = '\0';
    param_1[4].name[0x6d] = '\0';
    param_1[4].name[0x6e] = '\0';
    param_1[4].name[0x6f] = '\0';
  }
  FUN_000fdfc0();
  FUN_00035ba0();
  return *(undefined4 *)param_1->name;
}




void ModelInstance::draw(Model *instance,AffineTransform *affine,undefined4 param_3)

{
  vec3 translation;
  
  translation.x = affine->m[0][3];
  translation.y = affine->m[1][3];
  translation.z = affine->m[2][3];
                    // If it has Model subres 0x3
  if ((~(instance->descriptor->flags >> 1) & 1) != 0) {
    Graphics::SetModelSubres0x3Values(&translation);
    Model::activateTextures(instance);
    Model::drawIt(instance,affine,param_3);
    return;
  }
                    // RGBA
  Graphics::SetRoomLighting(0x3f800000,0x3f800000,0x3f800000,0x3f800000);
  ClearBinaryEntry();
                    // Disable for chrome effect
  Graphics::UpdateMatrices(&translation,false);
  Model::activateTextures(instance);
  Model::drawIt(instance,affine,param_3);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Model::drawIt(Model *model,AffineTransform *affine,uint param_3)

{
  Skeleton *skeleton_instance;
  
  Graphics::SomeModelContext = param_3;
  Graphics::SetSomePtr1(&model->globalUintsFlags);
  skeleton_instance = model->skeleton;
  if (skeleton_instance == (Skeleton *)0x0) {
    skeleton_instance = model->skeleton2;
  }
  Skeleton::bindFromModelInstance(model,skeleton_instance);
  g_avatarTransform.m[0][0] = affine->m[0][0];
  g_avatarTransform.m[0][1] = affine->m[1][0];
  g_avatarTransform.m[0][2] = affine->m[2][0];
  g_avatarTransform.m[1][0] = affine->m[0][1];
  g_avatarTransform.m[1][1] = affine->m[1][1];
  g_avatarTransform.m[1][2] = affine->m[2][1];
  g_avatarTransform.m[2][0] = affine->m[0][2];
  g_avatarTransform.m[2][1] = affine->m[1][2];
  g_avatarTransform.m[2][2] = affine->m[2][2];
  g_avatarTransform.m[3][0] = affine->m[0][3];
  g_avatarTransform.m[3][1] = affine->m[1][3];
  g_avatarTransform.m[3][2] = affine->m[2][3];
  g_avatarTransform.m[2][3] = 0.0;
  g_avatarTransform.m[1][3] = 0.0;
  g_avatarTransform.m[0][3] = 0.0;
  g_avatarTransform.m[3][3] = 1.0;
  Graphics::GetWorldTransform(&g_avatarTransform);
  Graphics::CurrentModelBeingDrawn = model;
  Graphics::DrawModelWithBones
            (model->descriptor->runtimeCtx->modelSubresource,0,param_3,&model->varData);
  DAT_005079e4 = 0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Model::activateTextures(Model *param_1)

{
  uint i;
  ModelFooterEntry *piVar4;
  ModelTextureList *list;
  TextureDescriptor *iVar1;
  ModelDescriptor *footerEntries;
  
  footerEntries = param_1->descriptor;
  i = 0;
  if (footerEntries->numFooterEntries != 0) {
    piVar4 = footerEntries->footerEntries;
    while (piVar4->subresourceType != Textures) {
      i = i + 1;
      piVar4 = piVar4 + 1;
      if (footerEntries->numFooterEntries <= i) {
        return;
      }
    }
    list = (ModelTextureList *)footerEntries->footerEntries[i].offset;
    if ((list != (ModelTextureList *)0x0) && (i = list->numDescriptors, i != 0)) {
      iVar1 = (TextureDescriptor *)footerEntries->runtimeCtx->textureSubresource;
      if (iVar1 != (TextureDescriptor *)0x0) {
        BigBlock::SetTextures(iVar1->headerSize,i);
        return;
      }
      BigBlock::SetTextures(0,i);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Skeleton::bindFromModelInstance(Model *instance,Skeleton *skeleton)

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
  void *pvVar12;
  AffineTransform *pOut;
  D3DXMATRIX *affine;
  int num_bones;
  int i;
  void *pcVar2;
  AffineTransform *affines;
  
  if (instance->ndSkeleton != (ndSkeleton *)0x0) {
    pvVar12 = (instance->ndSkeleton->header).varDataOffset;
    if (skeleton == (Skeleton *)0x0) {
      *(undefined4 *)((int)pvVar12 + (int)(instance->varData).matrixLists) = 0;
    }
    else {
      affines = skeleton->boneAffines;
      *(AffineTransform **)((int)pvVar12 + (int)(instance->varData).matrixLists) = affines;
      if (skeleton->ignoresGlobalBone != 0) {
        num_bones = skeleton->numBones;
        affine = (D3DXMATRIX *)(affines + num_bones + -1);
        pOut = (AffineTransform *)(num_bones * 0x40 + -0x40 + (int)affines);
        if (3 < num_bones) {
          i = num_bones + -3;
                    // num_bones = 3
          num_bones = num_bones - i;
          do {
            D3DX8::D3DXMatrixTranspose((D3DMATRIX *)pOut,affine);
            pOut->m[2][3] = 0.0;
            pOut->m[1][3] = 0.0;
            pOut->m[0][3] = 0.0;
            pOut[1].m[0][3] = 1.0;
            affine = (D3DXMATRIX *)((int)affine + -0x30);
            pOut = (AffineTransform *)(pOut[-2].m + 2);
            i = i + -1;
          } while (i != 0);
        }
        for (; num_bones != 0; num_bones = num_bones + -1) {
          fVar1 = affine->m[0][1];
          fVar2 = affine->m[0][2];
          fVar3 = affine->m[0][3];
          fVar4 = affine->m[1][0];
          fVar5 = affine->m[1][1];
          fVar6 = affine->m[1][2];
          fVar7 = affine->m[1][3];
          fVar8 = affine->m[2][0];
          fVar9 = affine->m[2][1];
          fVar10 = affine->m[2][2];
          fVar11 = affine->m[2][3];
          (*(float (*) [4])pOut)[0] = affine->m[0][0];
          (*(float (*) [4])pOut)[1] = fVar4;
          (*(float (*) [4])pOut)[2] = fVar8;
          *(float *)((int)pOut + 0x10) = fVar1;
          *(float *)((int)pOut + 0x10 + 4) = fVar5;
          *(float *)((int)pOut + 0x10 + 8) = fVar9;
          *(float *)((int)pOut + 0x20) = fVar2;
          *(float *)((int)pOut + 0x20 + 4) = fVar6;
          *(float *)((int)pOut + 0x20 + 8) = fVar10;
          *(float *)((int)pOut + 0x30) = fVar3;
          *(float *)((int)pOut + 0x30 + 4) = fVar7;
          *(float *)((int)pOut + 0x30 + 8) = fVar11;
          *(undefined4 *)((int)pOut + 0x20 + 0xc) = 0;
          *(undefined4 *)((int)pOut + 0x10 + 0xc) = 0;
          (*(float (*) [4])pOut)[3] = 0.0;
          *(float *)((int)pOut + 0x30 + 0xc) = 1.0;
          affine = (D3DXMATRIX *)((int)affine + -0x30);
          pOut = (AffineTransform *)((int)pOut + -0x40);
        }
        skeleton->ignoresGlobalBone = 0;
        return;
      }
    }
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x000f9713)
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void ModelInstance::searchForValueWithFlags(byte valueToSearch,Model *instance,byte index)

{
  byte indexTimes2Bottom3Bits;
  int indexTimes2Top5Bits;
  uint uVar1;
  
  uVar1 = (uint)index;
  indexTimes2Top5Bits = (int)(uVar1 * 2) >> 3;
  indexTimes2Bottom3Bits = (byte)(uVar1 * 2) & 7;
  if (Subres1Flags[uVar1] != (uint)valueToSearch) {
    Subres1Flags[uVar1] = (uint)valueToSearch;
  }
  *(byte *)((int)(instance->varData).matrixLists + indexTimes2Top5Bits + -0x10) =
       ~(0b00000011 << indexTimes2Bottom3Bits) &
       *(byte *)((int)(instance->varData).matrixLists + indexTimes2Top5Bits + -0x10) |
       valueToSearch << indexTimes2Bottom3Bits;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


uint ModelInstance::numBones(Model *param_1)

{
  uint numBones;
  
  if (param_1->ndSkeleton != (ndSkeleton *)0x0) {
    numBones = ndSkeleton::getNumBones(param_1->ndSkeleton);
    return numBones;
  }
  return 0;
}




Model * Model::ctor(ModelDescriptor *descriptor,BOOL hasSkeleton,BOOL hasOx3)

{
  ModelSubres0x3Descriptor *dst;
  Model *instance;
  ndSkeleton *nd_skeleton;
  int someSize;
  uint copy_size;
  ModelFooterEntry *entry;
  Skeleton *skel_instance;
  ModelSubres0x3Descriptor *desc_0x3;
  ModelVariableData *pMVar1;
  Model *pMVar2;
  ModelSubresource *header;
  ModelSubres0x3Descriptor *descc_0x3;
  ModelSubresource **as24;
  uint num_bones;
  uint variable_size;
  ModelVariableData *var_data;
  
  header = descriptor->runtimeCtx->modelSubresource;
  MeshHeader::getFirstDescendantByType(header,0,"ndMtxArray");
  if (hasOx3 != 0) {
    copy_size = 0;
    if (descriptor->numFooterEntries != 0) {
      entry = descriptor->footerEntries;
      do {
        if (entry->subresourceType == SomeType0x3) {
          descc_0x3 = (ModelSubres0x3Descriptor *)descriptor->footerEntries[copy_size].offset;
          if ((descc_0x3 != (ModelSubres0x3Descriptor *)0x0) && (descc_0x3->numValues != 0)) {
            someSize = MeshHeader::getSomeSize(header);
            copy_size = ModelDescriptor::get0x3SubresSize(descriptor);
            instance = malloc_(someSize + 0x2a0 + copy_size);
            someSize = MeshHeader::getSomeSize(header);
            dst = (ModelSubres0x3Descriptor *)((int)(instance->varData).matrixLists + someSize + -4)
            ;
            instance->ptrToSubres0x3 = dst;
            copy_size = 0;
            if (descriptor->numFooterEntries == 0) goto LAB_000f9a10;
            entry = descriptor->footerEntries;
            goto LAB_000f9a03;
          }
          break;
        }
        copy_size = copy_size + 1;
        entry = entry + 1;
      } while (copy_size < descriptor->numFooterEntries);
    }
  }
  someSize = MeshHeader::getSomeSize(header);
  instance = malloc_(someSize + 0x2a0);
  instance->ptrToSubres0x3 = (ModelSubres0x3Descriptor *)0x0;
  goto LAB_000f98a2;
  while( true ) {
    copy_size = copy_size + 1;
    entry = entry + 1;
    if (descriptor->numFooterEntries <= copy_size) break;
LAB_000f9a03:
    if (entry->subresourceType == SomeType0x3) {
      desc_0x3 = (ModelSubres0x3Descriptor *)descriptor->footerEntries[copy_size].offset;
      goto LAB_000f9a12;
    }
  }
LAB_000f9a10:
  desc_0x3 = (ModelSubres0x3Descriptor *)0x0;
LAB_000f9a12:
  copy_size = ModelDescriptor::get0x3SubresSize(descriptor);
  memcpy(dst,desc_0x3,copy_size);
  MeshHeaderInstance::registerSubres0x3s(instance);
LAB_000f98a2:
  instance->descriptor = descriptor;
  nd_skeleton = (ndSkeleton *)MeshHeader::getFirstDescendantByType(header,0,"ndSkeleton");
  instance->ndSkeleton = nd_skeleton;
  instance->globalUintsFlags = 0;
  instance->field361_0x298 = (ModelSubresource *)0x0;
  instance->boneIndices[0] = 0xffffffff;
  instance->boneIndices[1] = 0xffffffff;
  instance->boneIndices[2] = 0xffffffff;
  instance->boneIndices[3] = 0xffffffff;
  instance->boneIndices[4] = 0xffffffff;
  instance->boneIndices[5] = 0xffffffff;
  instance->boneIndices[6] = 0xffffffff;
  instance->boneIndices[7] = 0xffffffff;
  instance->boneIndices[8] = 0xffffffff;
  instance->boneIndices[9] = 0xffffffff;
  instance->boneIndices[10] = 0xffffffff;
  instance->boneIndices[0xb] = 0xffffffff;
  instance->boneIndices[0xc] = 0xffffffff;
  instance->boneIndices[0xd] = 0xffffffff;
  instance->boneIndices[0xe] = 0xffffffff;
  instance->boneIndices[0xf] = 0xffffffff;
  instance->boneIndices[0x10] = 0xffffffff;
  instance->boneIndices[0x11] = 0xffffffff;
  instance->boneIndices[0x12] = 0xffffffff;
  instance->boneIndices[0x13] = 0xffffffff;
  variable_size = header->varSize;
  var_data = &instance->varData;
  pMVar1 = var_data;
                    // Zero out the data
  for (copy_size = variable_size >> 2; copy_size != 0; copy_size = copy_size - 1) {
    pMVar1->headerData = 0;
    pMVar1 = (ModelVariableData *)pMVar1->matrixLists;
  }
  for (copy_size = variable_size & 3; copy_size != 0; copy_size = copy_size - 1) {
    *(undefined1 *)&pMVar1->headerData = 0;
    pMVar1 = (ModelVariableData *)((int)&pMVar1->headerData + 1);
  }
  MeshHeader::initialiseRootNodeMatrices(header,var_data);
  if ((hasSkeleton == 0) || (instance->ndSkeleton == (ndSkeleton *)0x0)) {
    instance->skeleton2 = (Skeleton *)0x0;
  }
  else {
    num_bones = instance->ndSkeleton->numBones;
    skel_instance = malloc_(num_bones * 0x40 + 0x10);
    skel_instance->numBones = num_bones;
    skel_instance = SkeletonInstance::resetBoneAffines(skel_instance);
    instance->skeleton2 = skel_instance;
  }
  instance->skeleton = (Skeleton *)0x0;
  MeshHeaderInstance::loadMorphTargets(instance);
  instance->initialised = 0;
  instance->field352_0x1c4 = -1;
  instance->field351_0x1c0 = 0;
  pMVar2 = instance;
  for (someSize = 0x56; pMVar2 = (Model *)&pMVar2->field1_0x4, someSize != 0;
      someSize = someSize + -1) {
    *(ModelSubresource **)pMVar2 = (ModelSubresource *)0x0;
  }
  instance->field342_0x15c = (ModelSubresource *)0x0;
  instance->modelPassedToBG = (ModelSubresource *)0x0;
  ModelSubresource::loadShaders(&instance->modelPassedToBG,header,var_data);
  return instance;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void MeshHeaderInstance::loadMorphTargets(Model *instance)

{
  BOOL was_found;
  BlendTarget *pBVar1;
  char **morph_target_name;
  BlendTarget **bt;
  int *offset;
  
  morph_target_name = Graphics::BlendTargetNames;
  bt = instance->blendTargets;
  do {
    was_found = ModelSubresource::getMapValue
                          (instance->descriptor->runtimeCtx->modelSubresource,*morph_target_name,
                           &offset);
    if (was_found == 0) {
      pBVar1 = (BlendTarget *)0x0;
    }
    else {
      pBVar1 = (BlendTarget *)((int)(instance->varData).matrixLists + *offset + -4);
    }
    *bt = pBVar1;
    morph_target_name = morph_target_name + 1;
    bt = bt + 1;
  } while ((int)morph_target_name < 0x339ac8);
  return;
}




void MeshHeaderInstance::registerSubres0x3s(Model *param_1)

{
  Subres0x3Val *value;
  byte cVar2;
  uint i;
  ModelSubres0x3Descriptor *subres;
  
  subres = param_1->ptrToSubres0x3;
  if ((subres != (ModelSubres0x3Descriptor *)0x0) && (i = subres->numValues, 0 < (int)i)) {
    value = subres->values;
    do {
      cVar2 = 0;
      do {
        if (Model::Subres0x3Values[(char)cVar2] == (Subres0x3Val *)0x0) goto LAB_000fdf9a;
        cVar2 = cVar2 + 1;
      } while ((char)cVar2 < '(');
      cVar2 = 0xff;
LAB_000fdf9a:
      value->field102_0x66 = value->field102_0x66 | 1;
      Model::Subres0x3Values[(char)cVar2] = value;
      Model::NumSubres0x3s = Model::NumSubres0x3s + 1;
      value = value + 1;
      i = i - 1;
    } while (i != 0);
  }
  return;
}




void D3DXMATRIX::getInverse(D3DXMATRIX *inv,float *det,D3DXMATRIX *param_3)

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
  
  fVar3 = param_3->m[1][0];
  fVar1 = param_3->m[0][0];
  fVar2 = param_3->m[0][1];
  fVar4 = param_3->m[1][1];
  fVar5 = param_3->m[2][0];
  fVar6 = param_3->m[2][1];
  fVar7 = param_3->m[3][0];
  fVar19 = fVar4 * fVar1 - fVar3 * fVar2;
  fVar8 = param_3->m[3][1];
  fVar9 = param_3->m[3][2];
  fVar10 = param_3->m[3][3];
  fVar18 = fVar6 * fVar1 - fVar5 * fVar2;
  fVar17 = fVar8 * fVar1 - fVar7 * fVar2;
  fVar20 = fVar6 * fVar3 - fVar5 * fVar4;
  fVar21 = fVar8 * fVar3 - fVar7 * fVar4;
  fVar22 = fVar8 * fVar5 - fVar7 * fVar6;
  fVar1 = param_3->m[0][2];
  fVar2 = param_3->m[0][3];
  fVar3 = param_3->m[1][2];
  fVar4 = param_3->m[1][3];
  fVar5 = param_3->m[2][2];
  fVar6 = param_3->m[2][3];
  fVar31 = fVar1 * fVar4 - fVar3 * fVar2;
  fVar30 = fVar1 * fVar6 - fVar5 * fVar2;
  fVar23 = fVar1 * fVar10 - fVar9 * fVar2;
  fVar11 = param_3->m[0][0];
  fVar12 = param_3->m[1][0];
  fVar13 = param_3->m[2][0];
  fVar28 = fVar3 * fVar6 - fVar5 * fVar4;
  fVar14 = param_3->m[2][1];
  fVar29 = fVar3 * fVar10 - fVar9 * fVar4;
  fVar15 = param_3->m[3][0];
  fVar26 = fVar5 * fVar10 - fVar9 * fVar6;
  fVar7 = param_3->m[0][1];
  fVar8 = param_3->m[1][1];
  fVar16 = param_3->m[3][1];
  fVar27 = (fVar30 * fVar8 - fVar31 * fVar14) - fVar28 * fVar7;
  fVar24 = fVar31 * fVar16 + (fVar29 * fVar7 - fVar23 * fVar8);
  fVar25 = (fVar23 * fVar14 - fVar30 * fVar16) - fVar26 * fVar7;
  fVar7 = fVar28 * fVar16 + (fVar26 * fVar8 - fVar29 * fVar14);
  fVar8 = fVar7 * fVar11 + fVar25 * fVar12 + fVar24 * fVar13 + fVar27 * fVar15;
  if (det != (float *)0x0) {
    *det = fVar8;
  }
  fVar8 = 1.0 / fVar8;
  iVar32 = FUN_0016744d((double)fVar8);
  if (iVar32 != 0) {
    inv->m[0][0] = fVar7 * fVar8;
    inv->m[0][1] = fVar25 * fVar8;
    inv->m[0][2] = fVar24 * fVar8;
    inv->m[0][3] = fVar27 * fVar8;
    inv->m[1][0] = ((fVar29 * fVar13 - fVar28 * fVar15) - fVar26 * fVar12) * fVar8;
    inv->m[1][1] = (fVar30 * fVar15 + (fVar11 * fVar26 - fVar23 * fVar13)) * fVar8;
    inv->m[1][2] = ((fVar23 * fVar12 - fVar31 * fVar15) - fVar29 * fVar11) * fVar8;
    inv->m[1][3] = (fVar31 * fVar13 + (fVar28 * fVar11 - fVar30 * fVar12)) * fVar8;
    inv->m[2][0] = (fVar20 * fVar10 + (fVar22 * fVar4 - fVar21 * fVar6)) * fVar8;
    inv->m[2][1] = ((fVar17 * fVar6 - fVar18 * fVar10) - fVar22 * fVar2) * fVar8;
    inv->m[2][2] = (fVar19 * fVar10 + (fVar21 * fVar2 - fVar17 * fVar4)) * fVar8;
    inv->m[2][3] = ((fVar18 * fVar4 - fVar19 * fVar6) - fVar20 * fVar2) * fVar8;
    inv->m[3][0] = ((fVar5 * fVar21 - fVar9 * fVar20) - fVar3 * fVar22) * fVar8;
    inv->m[3][1] = (fVar9 * fVar18 + (fVar1 * fVar22 - fVar5 * fVar17)) * fVar8;
    inv->m[3][2] = ((fVar3 * fVar17 - fVar9 * fVar19) - fVar1 * fVar21) * fVar8;
    inv->m[3][3] = (fVar5 * fVar19 + (fVar1 * fVar20 - fVar3 * fVar18)) * fVar8;
  }
  return;
}




void D3DXMATRIX::MultiplyByVec3(D3DXMATRIX *inMatrix,D3DXMATRIX *outMatrix,vec3 rowMultiplier)

{
  outMatrix->m[0][0] = inMatrix->m[0][0] * rowMultiplier.x;
  outMatrix->m[0][1] = inMatrix->m[0][1] * rowMultiplier.x;
  outMatrix->m[0][2] = inMatrix->m[0][2] * rowMultiplier.x;
  outMatrix->m[0][3] = inMatrix->m[0][3] * rowMultiplier.x;
  outMatrix->m[1][0] = inMatrix->m[1][0] * rowMultiplier.y;
  outMatrix->m[1][1] = inMatrix->m[1][1] * rowMultiplier.y;
  outMatrix->m[1][2] = inMatrix->m[1][2] * rowMultiplier.y;
  outMatrix->m[1][3] = inMatrix->m[1][3] * rowMultiplier.y;
  outMatrix->m[2][0] = inMatrix->m[2][0] * rowMultiplier.z;
  outMatrix->m[2][1] = inMatrix->m[2][1] * rowMultiplier.z;
  outMatrix->m[2][2] = inMatrix->m[2][2] * rowMultiplier.z;
  outMatrix->m[2][3] = inMatrix->m[2][3] * rowMultiplier.z;
  if (outMatrix != inMatrix) {
    outMatrix->m[3][0] = inMatrix->m[3][0];
    outMatrix->m[3][1] = inMatrix->m[3][1];
    outMatrix->m[3][2] = inMatrix->m[3][2];
    outMatrix->m[3][3] = inMatrix->m[3][3];
  }
  return;
}



void FUN_001538a0(float *param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7)

{
  float fVar1;
  
  fVar1 = 1.0 / (param_5 - param_4);
  *param_1 = fVar1 * 2.0;
  param_1[4] = 0.0;
  param_1[8] = 0.0;
  param_1[0xc] = 0.0 - (param_4 + param_5) * fVar1;
  fVar1 = 1.0 / (param_2 - param_3);
  param_1[1] = 0.0;
  param_1[5] = fVar1 * 2.0;
  param_1[9] = 0.0;
  param_1[0xd] = 0.0 - (param_2 + param_3) * fVar1;
  param_1[2] = 0.0;
  param_1[6] = 0.0;
  fVar1 = 1.0 / (param_7 - param_6);
  param_1[10] = 0.0 - fVar1;
  param_1[0xe] = 0.0 - ((param_6 + param_7) * fVar1 - 1.0) * 0.5;
  param_1[3] = 0.0;
  param_1[7] = 0.0;
  param_1[0xb] = 0.0;
  param_1[0xf] = 1.0;
  return;
}



void FUN_00153a00(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16,
                 undefined4 param_17)

{
  *param_1 = param_2;
  param_1[4] = param_3;
  param_1[8] = param_4;
  param_1[0xc] = param_5;
  param_1[1] = param_6;
  param_1[5] = param_7;
  param_1[9] = param_8;
  param_1[0xd] = param_9;
  param_1[2] = param_10;
  param_1[6] = param_11;
  param_1[10] = param_12;
  param_1[0xe] = param_13;
  param_1[3] = param_14;
  param_1[7] = param_15;
  param_1[0xb] = param_16;
  param_1[0xf] = param_17;
  return;
}




void ndMtxArray::ctor(ndMtxArray *this,void *descriptorStart,void *resStart)

{
  D3DXMATRIX *matrix;
  
  ndHeader::updateOffsets(&this->header,(int)descriptorStart);
  matrix = (D3DXMATRIX *)((int)this->runtimeMatrices + (int)descriptorStart);
  this->entries = (ndMtxArraySomething *)((int)&this->entries->bone_i + (int)descriptorStart);
  this->runtimeMatrices = matrix;
  if ((matrix != (D3DXMATRIX *)0x0) && (this->numMatrices != 0)) {
    this->calc1 = (short)matrix - (short)this;
  }
  return;
}




void ndMtxArray::ctor(ndMtxArray *mtxArray)

{
  D3DXMATRIX *pDVar1;
  int i;
  D3DXMATRIX *pDVar2;
  D3DXMATRIX *pDVar3;
  
  if ((mtxArray->numMatrices != 0) && (mtxArray->runtimeMatrices != (D3DXMATRIX *)0x0)) {
                    // Num matrices * 64
    pDVar1 = malloc_(mtxArray->numMatrices << 6);
    pDVar2 = mtxArray->runtimeMatrices;
    pDVar3 = pDVar1;
    for (i = (mtxArray->numMatrices & 0x3ffffffU) << 4; i != 0; i = i + -1) {
      pDVar3->m[0][0] = pDVar2->m[0][0];
      pDVar2 = (D3DXMATRIX *)(pDVar2->m[0] + 1);
      pDVar3 = (D3DXMATRIX *)(pDVar3->m[0] + 1);
    }
    for (i = 0; i != 0; i = i + -1) {
      *(undefined1 *)pDVar3 = *(undefined1 *)pDVar2;
      pDVar2 = (D3DXMATRIX *)((int)pDVar2->m[0] + 1);
      pDVar3 = (D3DXMATRIX *)((int)pDVar3->m[0] + 1);
    }
    mtxArray->runtimeMatrices = pDVar1;
    *(undefined1 *)((int)&mtxArray->field3_0x28 + 1) = 1;
    return;
  }
  *(undefined1 *)((int)&mtxArray->field3_0x28 + 1) = 0;
  return;
}




void ndMtxArray::dtor(ndMtxArray *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1->numMatrices;
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      *(undefined1 *)(iVar1 * 0x40 + iVar2 + param_2 + 4 + (int)(param_1->header).varDataOffset) = 0
      ;
      iVar1 = param_1->numMatrices;
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  ndSkeleton::dtor((ndSkeleton *)param_1,param_2);
  return;
}



// WARNING: Inlined function: GetBigBlock

void ndMtxArray::writeMatrices
               (ndMtxArray *this,D3DXMATRIX *boneTransforms,D3DXMATRIX *projMatrix,
               D3DXMATRIX *viewMatrix,void *varData,D3DXMATRIX *outMatrices)

{
  void *pvVar1;
  D3DXMATRIX *listOffset;
  D3DXMATRIX *bones;
  D3DXMATRIX *outMatrix;
  int i;
  D3DXMATRIX *matrices;
  ndMtxArraySomething *entry;
  D3DXMATRIX *mat;
  
  i = 0;
  outMatrix = outMatrices;
  if (0 < this->count) {
    do {
      entry = this->entries + i;
      mat = projMatrix;
      if ((entry->flagField & 1) == 0) {
        if ((entry->flagField & 2) != 0) {
          listOffset = (D3DXMATRIX *)((uint)entry->bone_i << 6);
          bones = boneTransforms;
          goto LAB_00155f39;
        }
        matrices = (this->header).varDataOffset;
        if ((*(byte *)((int)matrices + this->numMatrices * 0x40 + (uint)entry->matrixIndex + 4 +
                      (int)varData) & 1) == 0) {
          Maths::MultiplyMat4s(outMatrix,boneTransforms + entry->bone_i,projMatrix);
          listOffset = (D3DXMATRIX *)((uint)this->entries[i].matrixIndex << 6);
          mat = outMatrix;
          goto LAB_00155f36;
        }
        D3DX8::D3DXMatrixMultiply
                  (outMatrix,
                   (D3DXMATRIX *)
                   ((int)matrices + (uint)entry->matrixIndex * 0x40 + 4 + (int)varData),viewMatrix);
      }
      else {
        pvVar1 = (this->header).varDataOffset;
        listOffset = (D3DXMATRIX *)((uint)entry->matrixIndex * 0x40);
        if ((*(byte *)((int)pvVar1 + this->numMatrices * 0x40 + (uint)entry->matrixIndex + 4 +
                      (int)varData) & 1) == 0) {
LAB_00155f36:
          bones = this->runtimeMatrices;
LAB_00155f39:
          Maths::MultiplyMat4s(outMatrix,(D3DXMATRIX *)((int)listOffset + (int)bones),mat);
        }
        else {
          D3DX8::D3DXMatrixMultiply
                    (outMatrix,
                     (D3DXMATRIX *)((int)((int)listOffset + (int)pvVar1) + 4 + (int)varData),
                     viewMatrix);
        }
      }
      outMatrix = outMatrix + 1;
      i = i + 1;
    } while (i < this->count);
  }
  BigBlock_004370a0.mtxArrayBoneMatrices = outMatrices;
  return;
}



// WARNING: Inlined function: GetDisplayMatrices
// WARNING: Inlined function: GetBigBlock


void ndMtxArray::update(ndMtxArray *this,ModelVariableData *param_2)

{
  DisplayMatrices *local_8;
  
  writeMatrices(this,BigBlock_004370a0.boneTransforms,
                &(&Graphics::DisplayMatrices)[Graphics::DisplayMatrixIndex].projMatrix,
                (&Graphics::DisplayMatrices)[Graphics::DisplayMatrixIndex].viewMatrix,param_2,
                Graphics::SomeMatrices->matrices);
  ndHeader::update(&this->header);
  return;
}




void ndMtxArray::update(ndMtxArray *this,ModelVariableData *param_2)

{
  update(this,param_2);
  return;
}




uint32_t ndMtxArray::getNumMatrices(ndMtxArray *nd)

{
  return nd->numMatrices;
}




uint ndMtxArray::getSomeFlagValue(ndMtxArray *param_1,uint index)

{
  ndMtxArraySomething *pnVar1;
  int i;
  uint8_t *puVar2;
  
  i = 0;
  if (0 < param_1->count) {
    pnVar1 = param_1->entries;
    puVar2 = &pnVar1->matrixIndex;
    do {
      if (index == *puVar2) {
        if ((pnVar1[i].flagField & 1) != 0) {
          return 0xffffffff;
        }
        return (uint)pnVar1[i].bone_i;
      }
      i = i + 1;
      puVar2 = puVar2 + 8;
    } while (i < param_1->count);
  }
  return 0xffffffff;
}




void ndHeader::instantiate(ndHeader *nd,ModelVariableData *param_2)

{
  for (; nd != (ndHeader *)0x0; nd = nd->nextSibling) {
                    // clear matrices?
    destroyNode(nd->callbackCtx,nd,param_2);
    if (nd->nextChild != (ndHeader *)0x0) {
      instantiate(nd->nextChild,param_2);
    }
  }
  return;
}



// WARNING: Inlined function: EmptyFunction


uint MeshHeader::getSomeSize(ModelSubresource *param_1)

{
  return param_1->varSize;
}




void MeshHeader::initialiseRootNodeMatrices(ModelSubresource *header,ModelVariableData *varData)

{
  uint i;
  
  i = 0;
  if (header->numRootNodes != 0) {
    do {
      ndHeader::instantiate(header->rootNodes[i],varData);
      i = i + 1;
    } while (i < header->numRootNodes);
  }
  return;
}




ndHeader * ndHeader::findFirstNodeByType(ndHeader *param_1,NdType ndType)

{
  ndHeader *found;
  
  while( true ) {
    if (param_1 == (ndHeader *)0x0) {
      return (ndHeader *)0x0;
    }
    if (param_1->nd_type == ndType) break;
    if ((param_1->nextChild != (ndHeader *)0x0) &&
       (found = findFirstNodeByType(param_1->nextChild,ndType), found != (ndHeader *)0x0)) {
      return found;
    }
    param_1 = param_1->nextSibling;
  }
  return param_1;
}



// WARNING: Inlined function: GetBigBlock

ndHeader *
MeshHeader::getFirstDescendantByType
          (ModelSubresource *param_1,ushort rootNodeIndex,char *ndNameString)

{
  int nd_type;
  ndHeader *item;
  
  nd_type = IndexOfKeyInTable(BigBlock_004370a0.callbackTable,ndNameString);
  item = ndHeader::findFirstNodeByType(param_1->rootNodes[rootNodeIndex],(NdType)nd_type);
  return item;
}



// WARNING: Inlined function: GetBigBlock


void ModelResource::loadNdTree(ndHeader *param_1)

{
  ndHeader *pnVar1;
  int STR_LEN;
  char *size;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  bool valid;
  char *STR;
  
  do {
    if ((ndMtxArray *)param_1 == (ndMtxArray *)0x0) {
      return;
    }
    pcVar3 = (((ndMtxArray *)param_1)->header).subresName;
    STR_LEN = 0xf;
    valid = true;
    pcVar2 = pcVar3;
    STR = "ndVertexBuffer";
    do {
      if (STR_LEN == 0) break;
      STR_LEN = STR_LEN + -1;
      valid = *pcVar2 == *STR;
      pcVar2 = pcVar2 + 1;
      STR = STR + 1;
    } while (valid);
    if (!valid) {
      STR_LEN = 0xd;
      valid = true;
      pcVar2 = pcVar3;
      STR = "ndPushBuffer";
      do {
        size = pcVar2;
        pcVar4 = STR;
        if (STR_LEN == 0) break;
        STR_LEN = STR_LEN + -1;
        pcVar4 = STR + 1;
        size = pcVar2 + 1;
        valid = *pcVar2 == *STR;
        pcVar2 = size;
        STR = pcVar4;
      } while (valid);
      if (valid) {
        ndPushBuffer::ctor((ndPushBuffer *)param_1,size,pcVar4);
      }
      else {
        STR_LEN = 10;
        valid = true;
        pcVar2 = pcVar3;
        STR = "ndShader2";
        do {
          if (STR_LEN == 0) break;
          STR_LEN = STR_LEN + -1;
          valid = *pcVar2 == *STR;
          pcVar2 = pcVar2 + 1;
          STR = STR + 1;
        } while (valid);
        if (valid) {
          ndShader2::ctor((ndShader2 *)param_1);
        }
        else {
          STR_LEN = 0xd;
          valid = true;
          pcVar2 = pcVar3;
          STR = "ndBlendShape";
          do {
            if (STR_LEN == 0) break;
            STR_LEN = STR_LEN + -1;
            valid = *pcVar2 == *STR;
            pcVar2 = pcVar2 + 1;
            STR = STR + 1;
          } while (valid);
          if (!valid) {
            STR_LEN = 0xb;
            valid = true;
            pcVar2 = "ndMtxArray";
            do {
              if (STR_LEN == 0) break;
              STR_LEN = STR_LEN + -1;
              valid = *pcVar3 == *pcVar2;
              pcVar3 = pcVar3 + 1;
              pcVar2 = pcVar2 + 1;
            } while (valid);
            if (valid) {
              ndMtxArray::ctor((ndMtxArray *)param_1);
            }
          }
        }
      }
    }
    pnVar1 = (((ndMtxArray *)param_1)->header).nextChild;
    if (pnVar1 != (ndHeader *)0x0) {
      loadNdTree(pnVar1);
    }
    param_1 = (((ndMtxArray *)param_1)->header).nextSibling;
  } while( true );
}




void ModelSubresource::process(ModelSubresource *this,int base,void *resBytes)

{
  ModelSection1 *dataStart;
  ModelMap2 *pMVar1;
  uint i;
  
  if (this->keyValuesMap != (KeyValueMap *)0x0) {
    dataStart = (ModelSection1 *)((int)&this->keyValuesMap->numEntries + base);
    this->keyValuesMap = (KeyValueMap *)dataStart;
                    // If value at +0x10, load it
    updateKeyValueTableOffsets(dataStart,base);
  }
  if (this->somePtr2 != (void *)0x0) {
    pMVar1 = (ModelMap2 *)((int)this->somePtr2 + base);
    this->somePtr2 = pMVar1;
    ModelMap2::ctor(pMVar1,(void *)base);
  }
  i = 0;
                    // Update +0x8
  this->rootNodes = (ndHeader **)((int)this->rootNodes + base);
  if (this->numRootNodes != 0) {
    do {
      this->rootNodes[i] = (ndHeader *)((int)&this->rootNodes[i]->subresName + base);
      ModelResource::LoadModelMesh
                (this->rootNodes[i],(ModelSubresource *)base,resBytes,
                 BigBlock_004370a0.callbackTable);
      i = i + 1;
    } while (i < this->numRootNodes);
  }
  if (this->nextPtrMaybe != (int *)0x0) {
    pMVar1 = (ModelMap2 *)((int)this->nextPtrMaybe + base);
    this->nextPtrMaybe = (int *)pMVar1;
    ModelMap2::ctor(pMVar1,(void *)base);
  }
  return;
}




void ModelResource::loadModelMain(ModelSubresource *params)

{
  uint i;
  
  i = 0;
  if (params->numRootNodes != 0) {
    do {
      loadNdTree(params->rootNodes[i]);
      i = i + 1;
    } while (i < params->numRootNodes);
  }
  return;
}




BOOL ModelSubresource::getMapValue(ModelSubresource *subres,char *keyName,void **outValue)

{
  byte bVar1;
  KeyValueMap *pKVar2;
  byte *pbVar3;
  int iVar4;
  uint i;
  byte *pbVar5;
  KeyValue *entry;
  bool someBool;
  
  pKVar2 = subres->keyValuesMap;
  if (pKVar2 == (KeyValueMap *)0x0) {
    return 0;
  }
  i = 0;
  if (pKVar2->numEntries != 0) {
    entry = pKVar2->entries;
    do {
      pbVar3 = (byte *)entry->key;
      pbVar5 = (byte *)keyName;
      do {
        bVar1 = *pbVar3;
        someBool = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_0015692b:
          iVar4 = (1 - (uint)someBool) - (uint)(someBool != 0);
          goto LAB_00156930;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        someBool = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_0015692b;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00156930:
      if (iVar4 == 0) {
        *outValue = pKVar2->entries[i].value;
        return 1;
      }
      i = i + 1;
      entry = entry + 1;
    } while (i < pKVar2->numEntries);
  }
  return 0;
}




int32_t MeshHeader::getNumAttribMapEntries(ModelSubresource *param_1)

{
  if (param_1->keyValuesMap == (KeyValueMap *)0x0) {
    return 0;
  }
  return param_1->keyValuesMap->numEntries;
}




void MeshHeader::getMapEntryByIndex(ModelSubresource *param_1,int index,char **key,void **value)

{
  KeyValueMap *pKVar1;
  
  pKVar1 = param_1->keyValuesMap;
  *key = pKVar1->entries[index].key;
  *value = pKVar1->entries[index].value;
  return;
}




void ndSkeleton::ctor(ndSkeleton *param_1,int modelBase)

{
  ndHeader::updateOffsets(&param_1->header,modelBase);
  param_1->bonesStart = (ndSkeletonBone *)((int)&param_1->bonesStart->parentBone + modelBase);
  return;
}



// WARNING: Inlined function: GetBigBlock


void ndSkeleton::update(ndSkeleton *param_1,ModelVariableData *param_2)

{
  D3DXMATRIX *ndHeaderSomePtr;
  ndSkeleton *ndskelly;
  
  BigBlock_004370a0.boneTransforms =
       *(D3DXMATRIX **)((int)(param_1->header).varDataOffset + (int)param_2 + 4);
  BigBlock_004370a0.bones = param_1->bonesStart;
                    // BonesStart
  BigBlock_004370a0.numBones = param_1->numBones;
                    // NumBones
  ndHeader::update(&param_1->header);
  return;
}




uint ndSkeleton::getNumBones(ndSkeleton *param_1)

{
  return param_1->numBones;
}




undefined4 ndShaderParam2::UpdatePayload2(ndShaderParam2 *param)

{
  void *pvVar1;
  undefined4 local_8;
  BigBlock *big_block;
  
  big_block = &BigBlock_004370a0;
  local_8 = 0;
  pvVar1 = param->payload1->ptr0x20;
  if (pvVar1 != (void *)0x0) {
    FUN_00158bb0((int)pvVar1 + 1,1,&local_8);
  }
  FUN_00158bb0(&big_block->field60_0x46,2,&local_8);
  return local_8;
}



// WARNING: Inlined function: GetBigBlock
// WARNING: Inlined function: GetDisplayMatrices
// WARNING: Inlined function: SetParam2Value


void ndShaderParam2::update(ndShaderParam2 *param,DisplayMatrices *displayType)

{
  void *pvVar1;
  uint uVar2;
  DisplayMatrices *pDVar3;
  ndShaderParam2 *param2;
  
  uVar2 = Graphics::DisplayMatrixIndex;
  pvVar1 = (param->header).varDataOffset;
  pDVar3 = &Graphics::DisplayMatrices + Graphics::DisplayMatrixIndex;
  if (BigBlock_004370a0.numTextures != 0) {
    Graphics::SetSomeTextureVar(BigBlock_004370a0.texture1);
  }
  Graphics::SetViewMatrix((&Graphics::DisplayMatrices)[uVar2].viewMatrix);
  Graphics::SetFromDisplayType(pDVar3);
  Graphics::SetSomeVec3(&BigBlock_004370a0.someVec3);
  if (param->payload2 != (ndShaderParam2Payload *)0x0) {
    Graphics::Param2Value = UpdatePayload2(param);
  }
  setTextures(param->payload1,
              *(ndShader2Param2TextureAssignment **)((int)pvVar1 + (int)displayType + 4));
  D3D8::D3DDevice_SetPixelShaderConstant(6,BigBlock_004370a0.pixelShaderConstantValues,2);
  ndHeader::update(&param->header);
  return;
}




void ndShaderParam2::ctor(ndShaderParam2 *param_1,void *modelBase,void *resourceBase)

{
  ndShaderParam2Payload *pnVar1;
  
  pnVar1 = (ndShaderParam2Payload *)((int)&param_1->payload1->colours + (int)modelBase);
  param_1->payload1 = pnVar1;
  ndShaderParam2Payload::updatePayload(pnVar1,(int)modelBase);
  if (param_1->payload2 != (ndShaderParam2Payload *)0x0) {
    pnVar1 = (ndShaderParam2Payload *)((int)&param_1->payload2->colours + (int)modelBase);
    param_1->payload2 = pnVar1;
    ndShaderParam2Payload::updatePayload(pnVar1,(int)modelBase);
  }
  ndHeader::updateOffsets(&param_1->header,(int)modelBase);
  return;
}




void ndShaderParam2::dtor(int param_1,int param_2)

{
  int iVar1;
  
  param_2 = *(int *)(param_1 + 0xc) + param_2;
  iVar1 = FUN_0015b260(*(undefined4 *)(param_1 + 0x20));
  if (iVar1 == 0) {
    *(undefined4 *)(param_2 + 4) = 0;
  }
  else {
    *(int *)(param_2 + 4) = param_2 + 0xc;
    FUN_0015b040(*(undefined4 *)(param_1 + 0x20),param_2 + 0xc);
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    iVar1 = FUN_0015b260(*(int *)(param_1 + 0x24));
    if (iVar1 != 0) {
      iVar1 = FUN_0015b260(*(undefined4 *)(param_1 + 0x20));
      iVar1 = iVar1 + *(int *)(param_2 + 4);
      *(int *)(param_2 + 8) = iVar1;
      FUN_0015b040(*(undefined4 *)(param_1 + 0x24),iVar1);
      return;
    }
    *(undefined4 *)(param_2 + 8) = 0;
  }
  return;
}




void ndBlendShape::ctor(ndBlendShape *shape,int resBase,int param_3)

{
  int *piVar1;
  ndVertexBuffer *pnVar2;
  ndVertexBufferResView *pnVar3;
  VBResViewType *pVVar4;
  uint uVar5;
  uint i;
  int iVar6;
  
  ndHeader::updateOffsets(&shape->header,resBase);
  i = 0;
  shape->vertexBuffers = (ndVertexBuffer **)((int)shape->vertexBuffers + resBase);
  if ((short)shape->numVertexBuffers != 0) {
    do {
      shape->vertexBuffers[i] =
           (ndVertexBuffer *)((int)&(shape->vertexBuffers[i]->header).subresName + resBase);
      pnVar2 = shape->vertexBuffers[i];
      if (pnVar2->numResViews != 0) {
        pnVar2->resViews = (ndVertexBufferResView *)(&pnVar2->resViews->stride + resBase);
      }
      uVar5 = 0;
      if (pnVar2->numResViews != 0) {
        iVar6 = 0;
        do {
          piVar1 = (int *)((int)&pnVar2->resViews->resourceHeap + iVar6);
          *piVar1 = *piVar1 + param_3;
          uVar5 = uVar5 + 1;
          iVar6 = iVar6 + 0x18;
        } while (uVar5 < pnVar2->numResViews);
      }
      i = i + 1;
    } while (i < (ushort)shape->numVertexBuffers);
  }
  i = 0;
  if ((short)(*shape->vertexBuffers)->numResViews != 0) {
    iVar6 = 0;
    do {
      pnVar3 = (*shape->vertexBuffers)->resViews;
      D3D8::D3DResource_Register
                ((D3DResource *)((int)&pnVar3->d3dResPtr + iVar6),
                 *(PVOID *)((int)&pnVar3->resourceHeap + iVar6));
      i = i + 1;
      iVar6 = iVar6 + 0x18;
    } while (i < (ushort)(*shape->vertexBuffers)->numResViews);
  }
  if (1 < (ushort)shape->numVertexBuffers) {
    i = 1;
    do {
      iVar6 = 0;
      if (shape->vertexBuffers[i]->resViews->resType != Vertex) {
        pVVar4 = &shape->vertexBuffers[i]->resViews->resType;
        do {
          pVVar4 = pVVar4 + 0x18;
          iVar6 = iVar6 + 1;
        } while (*pVVar4 != Vertex);
      }
      pnVar3 = shape->vertexBuffers[i]->resViews;
      D3D8::D3DResource_Register((D3DResource *)&pnVar3[iVar6].d3dResPtr,pnVar3[iVar6].resourceHeap)
      ;
      i = i + 1;
    } while (i < (ushort)shape->numVertexBuffers);
  }
  return;
}




void ndBlendShape::update(ndBlendShape *blend,int param_2)

{
  if (*(char *)((int)&blend->numVertexBuffers + 2) != '\0') {
    FUN_00157650(blend,(int)(blend->header).varDataOffset + param_2);
    ndHeader::update(&blend->header);
    return;
  }
  FUN_00157880(blend);
  ndHeader::update(&blend->header);
  return;
}




void ndRigidSkinIdx::update(ndRigidSkinIdx *rigidSkin)

{
  int Register;
  uint i;
  D3DMATRIX local_40;
  
  D3D8::D3DDevice_SetVertexShaderConstant4
            (0x74,(DirectXShaderConstant *)
                  &(&Graphics::DisplayMatrices)[Graphics::DisplayMatrixIndex].projectionMat);
  i = 0;
  if (rigidSkin->numIndices != 0) {
                    // 0x78-0x7a - affine 1
                    // 0x7b-0x7d - affine 2
                    // 0x7e-0x80 - affine 3
                    // 0x81-0x83 - affine 4
                    // etc
    Register = 0x78;
    do {
      D3DX8::D3DXMatrixTranspose
                (&local_40,BigBlock_004370a0.mtxArrayBoneMatrices + rigidSkin->mtxIndices[i]);
                    // Sets 12 floats (ie, 3 registers, an affine transform)
      D3D8::D3DDevice_SetVertexShaderConstantNotInline(Register,&local_40,0xc);
      i = i + 1;
      Register = Register + 3;
    } while (i < rigidSkin->numIndices);
  }
  ndHeader::update(&rigidSkin->base);
  return;
}




void ndRigidSkinIdx::update(ndRigidSkinIdx *rigidSkin)

{
  update(rigidSkin);
  return;
}




void ndRigidSkinIdx::ctor(ndRigidSkinIdx *param_1,int param_2)

{
  param_1->mtxIndices = param_1->mtxIndices + param_2;
  ndHeader::updateOffsets(&param_1->base,param_2);
  return;
}




void ndShader2::ctor(ndShader2 *params,void *base,void *resBase)

{
  ndShader *pnVar1;
  
  pnVar1 = (ndShader *)((int)&params->pixelShader1->pixelPipelineIndex + (int)base);
  params->pixelShader1 = pnVar1;
  ndShader2Payload::UpdateOffsets(pnVar1,base);
  if (params->pixelShader2 != (ndShader *)0x0) {
    pnVar1 = (ndShader *)((int)&params->pixelShader2->pixelPipelineIndex + (int)base);
    params->pixelShader2 = pnVar1;
    ndShader2Payload::UpdateOffsets(pnVar1,base);
  }
  ndHeader::updateOffsets(&params->header,(int)base);
  return;
}




void ndShader2::ctor(ndShader2 *param_1)

{
  FUN_0015b360((ndShader2Payload *)param_1->pixelShader1);
  if (param_1->pixelShader2 != (ndShader *)0x0) {
    FUN_0015b360((ndShader2Payload *)param_1->pixelShader2);
    return;
  }
  return;
}




void ndShader2::update(ndShader2 *shader)

{
  ndShader::use(shader->pixelShader1);
  ndHeader::update(&shader->header);
  return;
}




void nd2D::update(ndHeader *param_1,undefined4 param_2)

{
  uint uVar1;
  DisplayMatrices *pDVar2;
  int iVar3;
  D3DXMATRIX *pDVar4;
  DisplayMatrices *pDVar5;
  
  stackPushProjMatrix();
  FUN_00157f10(param_1,param_2);
  uVar1 = Graphics::DisplayMatrixIndex;
  pDVar2 = &Graphics::DisplayMatrices + Graphics::DisplayMatrixIndex;
  pDVar4 = &(&Graphics::DisplayMatrices)[Graphics::DisplayMatrixIndex].worldMat;
  pDVar5 = pDVar2;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    (pDVar5->projMatrix).m[0][0] = pDVar4->m[0][0];
    pDVar4 = (D3DXMATRIX *)((int)pDVar4 + 4);
    pDVar5 = (DisplayMatrices *)((int)&pDVar5->projMatrix + 4);
  }
  pDVar4 = (&Graphics::DisplayMatrices)[uVar1].viewMatrix;
  (&Graphics::DisplayMatrices)[uVar1].projMatrix.m[3][0] =
       *(float *)((int)pDVar4 + 0x20) * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][2] +
       *(float *)((int)pDVar4 + 0x10) * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][1] +
       (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][0] * pDVar4->m[0][0] +
       *(float *)((int)pDVar4 + 0x30);
  pDVar4 = (&Graphics::DisplayMatrices)[uVar1].viewMatrix;
  (&Graphics::DisplayMatrices)[uVar1].projMatrix.m[3][1] =
       pDVar4->m[2][1] * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][2] +
       pDVar4->m[1][1] * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][1] +
       pDVar4->m[0][1] * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][0] + pDVar4->m[3][1];
  pDVar4 = (&Graphics::DisplayMatrices)[uVar1].viewMatrix;
  (&Graphics::DisplayMatrices)[uVar1].projMatrix.m[3][2] =
       pDVar4->m[2][2] * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][2] +
       pDVar4->m[1][2] * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][1] +
       pDVar4->m[0][2] * (&Graphics::DisplayMatrices)[uVar1].worldMat.m[3][0] + pDVar4->m[3][2];
  FUN_00156540(pDVar2);
  if (param_1->nextSibling != (ndHeader *)0x0) {
    Graphics::PushNdNode(*param_1->nextSibling->callbackCtx->callbacks,param_1->nextSibling);
  }
  Graphics::PushNdNode(&LAB_00157d30,param_1);
  if (param_1->nextChild != (ndHeader *)0x0) {
    Graphics::PushNdNode(*param_1->nextChild->callbackCtx->callbacks,param_1->nextChild);
  }
  return;
}




void nd2D::ctor(ndHeader *param_1,int param_2)

{
  D3DX8::D3DXMatrixTranspose((D3DMATRIX *)&param_1[1].nd_type,&param_1[1].nd_type);
  ndHeader::updateOffsets(param_1,param_2);
  return;
}



// WARNING: Inlined function: GetDisplayMatrices
// WARNING: Inlined function: GetBigBlock


void ndPixelShaderParam::update(ndHeader *group)

{
  ndHeader::update(group);
  return;
}




void ndBGPushBuffer::ctor(ndBGPushBuffer *buf,void *modelStart,void *resStart)

{
  buf->somePtr2 = buf->somePtr2 + (int)modelStart;
  buf->somePtr1 = buf->somePtr1 + (int)modelStart;
  ndPushBuffer::ctor(&buf->pushBuffer,modelStart,resStart);
  return;
}




void ndBGPushBuffer::dtor(ndSkeleton *param_1,int param_2)

{
  *(undefined4 *)((int)(param_1->header).varDataOffset + param_2 + 4) = 0xffffffff;
  ndSkeleton::dtor(param_1,param_2);
  return;
}



// WARNING: Inlined function: GetBigBlock


void ndBGPushBuffer::update(ndBGPushBuffer *buf,int param_2)

{
  int iVar1;
  ndBGPushBuffer *buff;
  
  Graphics::ndBGPushBuffersUpdated = Graphics::ndBGPushBuffersUpdated + 1;
  iVar1 = *(int *)((int)(buf->pushBuffer).subres.varDataOffset + param_2 + 4);
  if ((iVar1 != -1) && (iVar1 != BigBlock_004370a0.field315_0x18c)) {
    DAT_00546304 = DAT_00546304 + 1;
    ndHeader::update((ndHeader *)buf);
    return;
  }
  if ((buf->pushBuffer).field_0x3f == '\0') {
    ndPushBuffer::update(&buf->pushBuffer);
    return;
  }
  DAT_00546304 = DAT_00546304 + 1;
  updateSiblings(buf);
  return;
}




void ndPushBuffer::ctor(ndPushBuffer *param_1,ModelSubresource *params,char *resBytes)

{
  uint i;
  
  ndHeader::updateOffsets(&param_1->subres,(int)params);
  if (param_1->d3dResourcePtr != (D3DResource *)0x0) {
    param_1->d3dResourcePtr =
         (D3DResource *)((int)&params->varSize + (int)&param_1->d3dResourcePtr->Common);
    param_1->pushBufStart = (int)&params->varSize + param_1->pushBufStart;
    return;
  }
  param_1->pushDataPtrs = (WORD **)((int)param_1->pushDataPtrs + (int)params);
  param_1->vertexCounts = (UINT *)((int)param_1->vertexCounts + (int)params);
  i = 0;
  param_1->primitiveTypes = (D3DPRIMITIVETYPE *)((int)param_1->primitiveTypes + (int)params);
  if (param_1->numDraws != 0) {
    do {
      param_1->pushDataPtrs[i] = (WORD *)((int)param_1->pushDataPtrs[i] + (int)params);
      i = i + 1;
    } while (i < param_1->numDraws);
  }
  return;
}




void ndPushBuffer::ctor(ndPushBuffer *param_1,undefined4 size,undefined4 param_3)

{
  D3DPushBuffer pPushBuffer;
  code *hardware_malloc;
  undefined4 *pushbuffer_mem;
  uint uVar1;
  uint uVar2;
  ULONG unaff_EBX;
  undefined4 *puVar3;
  undefined4 *puVar4;
  UINT unaff_retaddr;
  
  if (param_1->d3dResourcePtr != (D3DResource *)0x0) {
    hardware_malloc =
         (code *)FUN_00155d00(param_1->field4_0x2c,0x80,".\\nodes\\geometry\\pushbuffer.c",0xf4);
    pushbuffer_mem = (undefined4 *)(*hardware_malloc)();
    uVar2 = param_1->field4_0x2c;
    puVar3 = (undefined4 *)param_1->pushBufStart;
    puVar4 = pushbuffer_mem;
    for (uVar1 = uVar2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    param_1->pushBufStart = (uint)pushbuffer_mem;
    pPushBuffer.resource.Data = 0;
    pPushBuffer.resource.Common = (DWORD)param_1->d3dResourcePtr;
    pPushBuffer.resource.Lock = param_3;
    pPushBuffer.Size = size;
    pPushBuffer.AllocationSize = unaff_EBX;
    XGRAPHICS::XGSetPushBufferHeader(param_1->field4_0x2c,0,pPushBuffer,unaff_retaddr);
    D3D8::D3DResource_Register(param_1->d3dResourcePtr,(PVOID)param_1->pushBufStart);
  }
  return;
}



// WARNING: Inlined function: GetBigBlock


BOOL ndPushBuffer::shouldDraw(ndPushBuffer *param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1->valueToCheck == 0xff) {
    return 1;
  }
  uVar1 = (char)param_1->valueToCheck * 2;
  uVar2 = uVar1 & 0x80000007;
  if ((int)uVar2 < 0) {
    uVar2 = (uVar2 - 1 | 0xfffffff8) + 1;
  }
  return (uint)((*(byte *)(((int)(uVar1 + ((int)uVar1 >> 0x1f & 7U)) >> 3) +
                          (int)BigBlock_004370a0.modelSomePtr1) >> ((byte)uVar2 & 0x1f) & 3) ==
               param_1->checkValue);
}




void ndPushBuffer::update(ndPushBuffer *param_1)

{
  BOOL BVar1;
  uint i;
  
  BVar1 = shouldDraw(param_1);
  if (BVar1 != 0) {
    if (param_1->doNotCull != false) {
      D3D8::D3DDevice_SetRenderState_CullMode(D3DCULL_NONE);
    }
    i = 0;
    if (param_1->numDraws != 0) {
      do {
        D3D8::D3DDevice_DrawIndexedVertices
                  (param_1->primitiveTypes[i],param_1->vertexCounts[i],param_1->pushDataPtrs[i]);
        i = i + 1;
      } while (i < param_1->numDraws);
    }
    if (param_1->doNotCull != false) {
                    // Cull Clockwise
      D3D8::D3DDevice_SetRenderState_CullMode(CULL_CW);
    }
  }
                    // Update children (or maybe siblings)
  ndHeader::update(&param_1->subres);
  return;
}




void ndVertexBuffer::ctor(ndVertexBuffer *vb,int base,void *resStart)

{
  uint res_i;
  ndVertexBufferResView *view_ptr;
  
  ndHeader::updateOffsets(&vb->header,base);
  res_i = 0;
  vb->resViews = (ndVertexBufferResView *)(&vb->resViews->stride + base);
  if (vb->numResViews != 0) {
    view_ptr = (ndVertexBufferResView *)0x0;
    do {
      *(int *)((int)&vb->resViews->resourceHeap + (int)view_ptr) =
           *(int *)((int)&vb->resViews->resourceHeap + (int)view_ptr) + (int)resStart;
                    // Fixup resource pointer using runtime one
      D3D8::D3DResource_Register
                ((D3DResource *)((int)&view_ptr->d3dResPtr + (int)&vb->resViews->stride),
                 *(PVOID *)((int)&vb->resViews->resourceHeap + (int)view_ptr));
      res_i = res_i + 1;
      view_ptr = view_ptr + 1;
    } while (res_i < vb->numResViews);
  }
  return;
}



// WARNING: Inlined function: GetBigBlock


void ndVertexBuffer::bindResources(ndVertexBuffer *param_1)

{
  int iVar1;
  int iVar2;
  uint i;
  
  i = 0;
  if (param_1->numResViews != 0) {
    iVar2 = 0;
    iVar1 = 0x78;
    do {
      *(uint8_t **)((int)BigBlock_004370a0.streamSources + iVar1 + -0x78) =
           &param_1->resViews->stride + iVar2;
      i = i + 1;
      iVar1 = iVar1 + 4;
      iVar2 = iVar2 + 0x18;
    } while (i < param_1->numResViews);
  }
  return;
}




void ndVertexBuffer::update(ndVertexBuffer *param_1)

{
  bindResources(param_1);
  ndHeader::update(&param_1->header);
  return;
}




void ndVertexShader::ctor(ndVertexShader *this,void *base,void *resBase)

{
  int iVar1;
  VertexShader *shaderPtr;
  char *otherStream;
  
  otherStream = this->otherStreamUntil0xff;
  this->otherStreamUntil0xff = otherStream + (int)base;
  shaderPtr = (VertexShader *)((int)base + (int)(this->shader->shader + -1));
  this->strides = this->strides + (int)base;
  this->streamSourceIndices = (uint32_t *)((int)this->streamSourceIndices + (int)base);
  this->shader = shaderPtr;
  iVar1 = LoadVertexShaderAndGetIndex
                    (shaderPtr,(uint *)(otherStream + (int)base),this->id3,(uint)(this->id1 != -1),
                     (uint)(this->id2 != -1));
  this->runtimeIndex = iVar1;
  ndHeader::updateOffsets(&this->header,(int)base);
  return;
}



// WARNING: Inlined function: GetBigBlock
// WARNING: Inlined function: GetDisplayMatrices
// WARNING: Inlined function: GetBinaryEntriesCount


void ndVertexShader::update(ndVertexShader *this,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  DWORD Handle;
  uint vertexShaderId;
  UINT i;
  BigBlock *big_block;
  float m [4] [4];
  DisplayMatrices *pM;
  
  uVar1 = Graphics::DisplayMatrixIndex;
  iVar2 = Graphics::DisplayMatrixIndex * 0xc4;
  pM = &Graphics::DisplayMatrices + Graphics::DisplayMatrixIndex;
  vertexShaderId = Game::GraphicsFlags;
  if (this->id1 == -1) {
    vertexShaderId = Game::GraphicsFlags & 0x80000000;
  }
  i = 0;
  if (this->numStreamSources != 0) {
    do {
                    // Set Input Data Streams
      D3D8::D3DDevice_SetStreamSource
                (i,(D3DVertexBuffer *)
                   (BigBlock_004370a0.streamSources[this->streamSourceIndices[i]] + 1),
                 (uint)this->strides[i]);
      i = i + 1;
    } while (i < this->numStreamSources);
  }
  Handle = GetCachedVertexShader(this->runtimeIndex,vertexShaderId);
  D3D8::D3DDevice_SetVertexShader(Handle);
  if (this->constant1Index < 0x60) {
    BigBlock_004370a0.projMatrixIndex = (ushort)this->constant1Index;
    BigBlock_004370a0.vsConstantIndex2 = this->constant2Index;
    D3DX8::D3DXMatrixTranspose((D3DMATRIX *)m,iVar2 + 0x439334);
    D3D8::D3DDevice_SetVertexShaderConstant4
              (BigBlock_004370a0.projMatrixIndex + 0x60,(DirectXShaderConstant *)m);
    if (BigBlock_004370a0.vsConstantIndex2 < 0x60) {
      D3DX8::D3DXMatrixTranspose((D3DMATRIX *)m,pM);
      D3D8::D3DDevice_SetVertexShaderConstantNotInline
                (BigBlock_004370a0.vsConstantIndex2 + 0x60,m,0xc);
    }
  }
  if (this->viewMatrixIndex < 0x60) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline
              (this->viewMatrixIndex + 0x60,(&Graphics::DisplayMatrices)[uVar1].viewMatrix,0xc);
  }
  D3D8::D3DDevice_SetVertexShaderConstant1(this->idk3 + 0x60,&BigBlock_004370a0.vsConstant);
  if (this->field16_0x4c < 0x60) {
    D3D8::D3DDevice_SetVertexShaderConstantNotInline
              (this->field16_0x4c + 0x60,&BigBlock_004370a0.field_0x1b0,8);
  }
  ndHeader::update(&this->header);
  return;
}




void ndSkeleton::dtor(ndSkeleton *param_1,undefined4 param_2)

{
  dtor(param_1,param_2);
  return;
}




void ndPixelShader::ctor(ndHeader *param_1,int param_2)

{
  XGBuffer *local_4;
  
  XGRAPHICS::XGAssembleShader
            ("",s_xps_1_1_mov_r0_v0_0032e4b8,0x12,4,(XGBuffer **)0x0,&local_4,(XGBuffer **)0x0,
             (XGBuffer **)0x0,(SASM_ResolverCallback *)0x0,(LPVOID)0x0,(LPDWORD)0x0);
  D3D8::D3DDevice_CreatePixelShader(local_4->pData,&DAT_0054d948);
  ndHeader::updateOffsets(param_1,param_2);
  return;
}




void ndPixelShader::update(ndHeader *param_1)

{
  D3D8::D3DDevice_SetPixelShader(DAT_0054d948);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ZFUNC,0x203);
  Graphics::RenderState.zCmpFunc = D3DCMP_LESSEQUAL;
  D3D8::D3DDevice_SetRenderState_ZEnable(1);
  D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHABLENDENABLE,0);
  Graphics::RenderState.alphaBlendingEnabled = 0;
  ndHeader::update(param_1);
  return;
}




void ndHeader::updateOffsets(ndHeader *param_1,int param_2)

{
  updateOffsets(param_1,param_2);
  return;
}




void ndHeader::updateOffsets(ndHeader *param_1,int param_2)

{
  if (param_1->nextChild != (ndHeader *)0x0) {
    param_1->nextChild = (ndHeader *)((int)&param_1->nextChild->subresName + param_2);
  }
  if (param_1->nextSibling != (ndHeader *)0x0) {
    param_1->nextSibling = (ndHeader *)((int)&param_1->nextSibling->subresName + param_2);
  }
  if (param_1->prev != (ndHeader *)0x0) {
    param_1->prev = (ndHeader *)((int)&param_1->prev->subresName + param_2);
  }
  return;
}




void ndSkeleton::dtor(ndSkeleton *param_1,int param_2)

{
  *(undefined4 *)(param_2 + (int)(param_1->header).varDataOffset) = 0;
  return;
}



// WARNING: Inlined function: getCallbackTable


void ndHeader::update(ndHeader *group)

{
  if (group->nextSibling != (ndHeader *)0x0) {
    Graphics::PushNdNode(*group->nextSibling->callbackCtx->callbacks,group->nextSibling);
  }
  if (group->nextChild != (ndHeader *)0x0) {
    Graphics::PushNdNode(*group->nextChild->callbackCtx->callbacks,group->nextChild);
  }
  return;
}



// WARNING: Inlined function: getCallbackTable


void ndBGPushBuffer::updateSiblings(ndBGPushBuffer *param_1)

{
  ndHeader *pnVar1;
  
  pnVar1 = (param_1->pushBuffer).subres.nextSibling;
  if (pnVar1 != (ndHeader *)0x0) {
    Graphics::PushNdNode(*pnVar1->callbackCtx->callbacks,(param_1->pushBuffer).subres.nextSibling);
  }
  return;
}



// WARNING: Inlined function: getCallbackTable


void ModelMap2::ctor(ModelMap2 *param_1,void *modelBase)

{
  int *piVar1;
  int iVar2;
  void *piVar3;
  uint uVar3;
  ModelMap2Entry *entry_i;
  uint uVar4;
  ModelMap2Entry *entry;
  
  uVar4 = 0;
  param_1->entries = (ModelMap2Entry *)((int)&param_1->entries->field0_0x0 + (int)modelBase);
  if (param_1->numEntries != 0) {
    entry_i = (ModelMap2Entry *)0x0;
    do {
      entry = param_1->entries;
      iVar2 = *(int *)((int)&entry->field2_0x8 + (int)entry_i);
      piVar3 = (void *)((int)&entry_i->field0_0x0 + (int)&entry->field0_0x0);
      *(int *)piVar3 =
           *(int *)((int)&entry_i->field0_0x0 + (int)&entry->field0_0x0) + (int)modelBase;
      *(int *)((int)piVar3 + 8) = iVar2 + (int)modelBase;
      uVar3 = 0;
      if (*(int *)((int)piVar3 + 4) != 0) {
        do {
          piVar1 = (int *)(*(int *)((int)piVar3 + 8) + uVar3 * 4);
          *piVar1 = *piVar1 + (int)modelBase;
          uVar3 = uVar3 + 1;
        } while (uVar3 < *(uint *)((int)piVar3 + 4));
      }
      uVar4 = uVar4 + 1;
      entry_i = entry_i + 1;
    } while (uVar4 < param_1->numEntries);
  }
  return;
}




void ReflectionData::setField0x8(ReflectionData *param_1,uint param_2)

{
  param_1->field8_0x8 = param_2;
  return;
}




void ModelInstance::ClearBinaryEntry(void)

{
  List::Init((uint *)&BinaryEntry);
  Game::GraphicsFlags = Game::GraphicsFlags & 0x80000000;
  return;
}




void ModelInstance::BinaryEntry::getPtr(int param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 4);
  return;
}




void ndShaderParam2Payload::updatePayload(ndShaderParam2Payload *this,int modelBase)

{
  uint i;
  ndShaderParam2Assignment *ass_ptr;
  
  if (this->textureAssignments != (ndShader2Param2TextureAssignment *)0x0) {
    this->textureAssignments =
         (ndShader2Param2TextureAssignment *)
         ((int)&this->textureAssignments->textureInstanceIndex + modelBase);
  }
  if (this->colours != (ndShader2Param2Colour *)0x0) {
    this->colours = (ndShader2Param2Colour *)(&this->colours->r + modelBase);
  }
  if (this->vsConstants != 0) {
    this->vsConstants = this->vsConstants + modelBase;
  }
  if (this->ptr0x20 != (void *)0x0) {
    this->ptr0x20 = (void *)((int)this->ptr0x20 + modelBase);
  }
  if (this->assignmentsStart != (ndShaderParam2Assignment *)0x0) {
    this->assignmentsStart =
         (ndShaderParam2Assignment *)((int)&this->assignmentsStart->keyName + modelBase);
    i = 0;
    if (this->numAssignments != 0) {
      ass_ptr = (ndShaderParam2Assignment *)0x0;
      do {
        *(int *)((int)&ass_ptr->keyName + (int)&this->assignmentsStart->keyName) =
             *(int *)((int)&ass_ptr->keyName + (int)&this->assignmentsStart->keyName) + modelBase;
        i = i + 1;
        ass_ptr = ass_ptr + 1;
      } while (i < this->numAssignments);
    }
  }
  return;
}



void ndShaderParam2::setTextures
               (ndShaderParam2Payload *payload,ndShader2Param2TextureAssignment *param_2)

{
  ndShader2Param2Colour *pnVar1;
  int iVar2;
  uint uVar3;
  DXTextureInstance *tex_instance;
  int iVar4;
  uint uVar5;
  ShaderConstant *pConstantData;
  SomethingInner_ptr_4_undefined4 somethingInner;
  int tex_i;
  DWORD i;
  int iVar6;
  D3DBaseTexture *base_tex;
  vec4 local_10;
  ndShader2Param2TextureAssignment *tex_ass;
  byte alphaRef;
  
  i = 0;
                    // Set constants [0,n) to *field0x00
  if (payload->numColours != 0) {
    do {
      pnVar1 = payload->colours;
      local_10.x = (float)pnVar1[i].r * 0.003921569;
      local_10.y = (float)pnVar1[i].g * 0.003921569;
      local_10.z = (float)pnVar1[i].b * 0.003921569;
      local_10.w = (float)pnVar1[i].w * 0.003921569;
      D3D8::D3DDevice_SetPixelShaderConstant(i,(DirectXShaderConstant *)&local_10,1);
      i = i + 1;
    } while (i < payload->numColours);
  }
  i = 0;
  if (payload->numTextureAssignments != 0) {
    tex_i = 0;
    somethingInner = &D3D8::D3D_g_DeferredTextureState.count2;
    do {
      ADJ(somethingInner).count1 = (uint)(&payload->textureAssignments->flag1)[tex_i];
      uVar3 = 1 << ((byte)i & 0b00011111);
      Graphics::GraphicsFlags = Graphics::GraphicsFlags | uVar3;
      ADJ(somethingInner)->count2 = (uint)(&payload->textureAssignments->flag2)[tex_i];
      Graphics::GraphicsFlags = Graphics::GraphicsFlags | uVar3;
      ADJ(somethingInner)->count3 = (uint)(&payload->textureAssignments->flag3)[tex_i];
      ADJ(somethingInner)->field7_0x1c = 0;
      ADJ(somethingInner)->field4_0x10 = 2;
      ADJ(somethingInner)->field5_0x14 = 2;
      uVar5 = Graphics::GraphicsFlags | uVar3;
      Graphics::GraphicsFlags = uVar5;
      ADJ(somethingInner)->field3_0xc = 2;
      if (*(short *)((int)&payload->textureAssignments->field5_0x8 + tex_i + 2) == 0) {
        Graphics::GraphicsFlags = Graphics::GraphicsFlags | uVar3;
        ADJ(somethingInner)->field10_0x28 = 0;
        if (-1 < *(short *)((int)&payload->textureAssignments->field5_0x8 + tex_i)) {
          D3D8::D3DDevice_SetTextureState_BumpEnv
                    (i,0x16,*(DWORD *)((int)&payload->textureAssignments->field6_0xc + tex_i));
          D3D8::D3DDevice_SetTextureState_BumpEnv
                    (i,0x17,*(DWORD *)((int)&payload->textureAssignments->field7_0x10 + tex_i));
          D3D8::D3DDevice_SetTextureState_BumpEnv
                    (i,0x19,*(DWORD *)((int)&payload->textureAssignments->field8_0x14 + tex_i));
          D3D8::D3DDevice_SetTextureState_BumpEnv
                    (i,0x18,*(DWORD *)((int)&payload->textureAssignments->field9_0x18 + tex_i));
        }
      }
      else {
        Graphics::GraphicsFlags = uVar5 | uVar3;
        ADJ(somethingInner)->field10_0x28 = 0xf0000000;
      }
      tex_ass = (ndShader2Param2TextureAssignment *)
                ((int)&payload->textureAssignments->textureInstanceIndex + tex_i);
      if (tex_ass->flag4 == '\0') {
                    // If it has a regular colour rather than a diffuse texture ????
        if (((payload->weirdTexIndex == i) && (payload->numWeirdTextures != '\0')) &&
           (Graphics::SomeTexturePtr != (undefined *)0x0)) {
          D3D8::D3DDevice_SetTexture(i,(D3DBaseTexture *)Graphics::SomeTexturePtr);
          D3D8::D3DDevice_SetVertexShaderConstant1
                    (payload->field19_0x34 + 0x60,
                     (DirectXShaderConstant *)&Graphics::VSConstants::Green);
        }
        else if (tex_ass->textureInstanceIndex != 0xffffffff) {
          tex_instance = *(DXTextureInstance **)(*(int *)&param_2->flag1 + i * 4);
          if (tex_instance == (DXTextureInstance *)0x0) {
            tex_instance = Graphics::TextureInstanceList[tex_ass->textureInstanceIndex];
          }
                    // Stage second, texture first
          (*DAT_004d9754)(tex_instance,i);
        }
      }
      else {
        Graphics::GetFallbackTexture(Graphics::Param2Value,&base_tex);
        D3D8::D3DDevice_SetTexture(i,base_tex);
      }
      i = i + 1;
      somethingInner = somethingInner + 0x20;
      tex_i = tex_i + 0x1c;
    } while (i < payload->numTextureAssignments);
  }
  uVar3 = 0;
  if (payload->numVertexShaderConstants != 0) {
    iVar6 = 0;
    tex_i = 0;
    do {
      if ((param_2 == (ndShader2Param2TextureAssignment *)0x0) ||
         (pConstantData = (ShaderConstant *)(tex_i + param_2->textureInstanceIndex),
         *(char *)(tex_i + 0x40 + param_2->textureInstanceIndex) == '\0')) {
        iVar4 = iVar6 + payload->vsConstants;
        iVar2 = *(int *)(iVar4 + 0x44);
        if (iVar2 == 1) {
          pConstantData = Graphics::Graphics::Matrix1;
        }
        else {
          if (iVar2 != 2) {
            iVar4 = *(int *)(payload->vsConstants + 0x40 + iVar6);
            pConstantData = (ShaderConstant *)(payload->vsConstants + iVar6);
            goto LAB_0015afa8;
          }
          pConstantData = Graphics::Matrix2;
        }
        iVar4 = *(int *)(iVar4 + 0x40);
      }
      else {
        iVar4 = *(int *)(iVar6 + 0x40 + payload->vsConstants);
      }
LAB_0015afa8:
      D3D8::D3DDevice_SetVertexShaderConstant4(iVar4 + 0x60,(DirectXShaderConstant *)pConstantData);
      uVar3 = uVar3 + 1;
      tex_i = tex_i + 0x44;
      iVar6 = iVar6 + 0x48;
    } while (uVar3 < payload->numVertexShaderConstants);
  }
  if (payload->alphaReference == '\0') {
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,0);
    Graphics::RenderState.alphaTestingEnabled = 0;
  }
  else {
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHATESTENABLE,1);
    Graphics::RenderState.alphaTestingEnabled = 1;
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
    Graphics::RenderState.alphaCmpFunction = D3DCMP_GREATER;
    alphaRef = payload->alphaReference;
    D3D8::D3DDevice_SetRenderState_Simple(D3DRS_ALPHAREF,(uint)alphaRef);
    Graphics::RenderState.alphaRef = (uint)alphaRef;
  }
  if (Graphics::PostParam2TextureBindCallback != (code *)0x0) {
    (*Graphics::PostParam2TextureBindCallback)(payload);
  }
  return;
}




void ndShader::use(ndShader *this)

{
  switch(this->pixelPipelineIndex) {
  case 0:
    ndShader2Payload::useType0();
    break;
  case 1:
    ndShader2Payload::useType1();
    break;
  case 2:
    ndShader2Payload::useType2();
    break;
  case 3:
    ndShader2Payload::useType3();
  }
  D3D8::D3DDevice_SetPixelShader(this->pixelPipelineHandle);
  if (Graphics::callback4 != (undefined *)0x0) {
                    // 0x000f9b40
    (*(code *)Graphics::callback4)(this);
  }
  return;
}




void ModelSubresource::loadShaders(int *param_1,ModelSubresource *param_2,int param_3)

{
  uint *puVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint local_4;
  
  local_4 = 0;
  MeshHeader::loadShadersFromAttribMapInner(param_2,&local_4,param_3,0x4dbdf8);
  uVar3 = local_4;
  if (local_4 != 0) {
    puVar1 = (uint *)(*graphics::alloc)(8);
    *param_1 = (int)puVar1;
    *puVar1 = uVar3;
    uVar2 = (*graphics::alloc)(uVar3 << 2);
    *(undefined4 *)(*param_1 + 4) = uVar2;
    puVar5 = &DAT_004dbdf8;
    puVar6 = *(undefined4 **)(*param_1 + 4);
    for (uVar3 = uVar3 & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    return;
  }
  *param_1 = 0;
  return;
}




