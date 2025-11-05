#include "../../game.hpp"
#include "background.hpp"

namespace ghoulies::objects
{

Background::Background(const BackgroundParams& params)
    : Avatar(params)
{
  /*
char cVar1;
byte* pbVar2;
float fVar3;
ModelFooterEntry* pMVar4;
ColliderSetDescriptor* desc_00;
backgroundParams* pbVar5;
char* pcVar6;
BackgroundEntityNode* pBVar7;
Background* extraout_EAX;
uint uVar8;
int* piVar9;
backgroundInner* new_inners;
void* pvVar10;
BOOL BVar11;
int inner_i;
int* piVar12;
int i;
uint numInners;
int iVar13;
ModelDescriptor* desc;
*/

  GameContext& ctx {GameContext::Instance()};

  ctx.background_model_aid = params.model_aid;

  ctx.backgrounds.Register(&this->registry_entry_);

  /*
  // Sets current bg
  pBVar7->head = &bg->prevEntityNode;
  bg->prevEntityNode = pBVar7;
  bg->nextEntityNode = NULL;
  FUN_00043190(bg);
  FUN_000400d0(extraout_EAX);
  desc = (bg->avatar).modelRes;
  if (desc == NULL) {
    params = NULL;
  } else {
    params = (backgroundParams*)desc->footerEntries;
  }
  pbVar5 = params;
  numInners = (params->avatarParams).objParams.typeIndex;
  uVar8 = 0;
  if (numInners != 0) {
    piVar9 = *(int**)&(params->avatarParams).objParams;
    piVar12 = piVar9;
    do {
      if (*piVar12 == 0x14) {
        piVar9 = (int*)piVar9[uVar8 * 2 + 1];
        goto joined_r0x00042e38;
      }
      uVar8 = uVar8 + 1;
      piVar12 = piVar12 + 2;
    } while (uVar8 < numInners);
  }
  piVar9 = NULL;
joined_r0x00042e38:
  do {
    if (piVar9 == NULL) {
      break;
    }
    FUN_001198a0();
    if (*piVar9 == 0) {
      break;
    }
    piVar9 = (int*)((int)piVar9 + *piVar9);
  } while (true);
  numInners = (pbVar5->avatarParams).objParams.typeIndex;
  uVar8 = 0;
  if (numInners != 0) {
    piVar9 = *(int**)&(pbVar5->avatarParams).objParams;
    piVar12 = piVar9;
    do {
      if (*piVar12 == 8) {
        if (piVar9[uVar8 * 2 + 1] != 0) {
          uVar8 = 0;
          if (numInners != 0) {
            goto LAB_00042e85;
          }
          goto LAB_00042e94;
        }
        break;
      }
      uVar8 = uVar8 + 1;
      piVar12 = piVar12 + 2;
    } while (uVar8 < numInners);
  }
  goto LAB_00042e9b;
  while (true) {
    uVar8 = uVar8 + 1;
    piVar9 = piVar9 + 2;
    if (numInners <= uVar8) {
      break;
    }
  LAB_00042e85:
    if (*piVar9 == 8) {
      break;
    }
  }
LAB_00042e94:
  FUN_000fefd0();
LAB_00042e9b:
  desc = (bg->avatar).modelRes;
  if ((((desc != NULL) && (desc->footerEntries != NULL))
       && (pcVar6 = *(char**)(desc->footerEntries[2].subresourceType + 0x10),
           pcVar6 != NULL))
      && (*pcVar6 != '\0'))
  {
    if (((desc == NULL) || (desc->footerEntries == NULL))
        || (pbVar2 = *(byte**)(desc->footerEntries[2].subresourceType + 0x10),
            pbVar2 == NULL))
    {
      numInners = 0;
    } else {
      numInners = (uint)*pbVar2;
    }
    new_inners = (backgroundInner*)malloc ? (numInners * 0x9c);
    bg->inners = new_inners;
    for (uVar8 = numInners * 0x9c >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4*)new_inners = 0;
      new_inners = (backgroundInner*)&new_inners->field_0x4;
    }
    inner_i = 0;
    for (i = 0; i != 0; i = i + -1) {
      new_inners->field0_0x0 = 0;
      new_inners = (backgroundInner*)&new_inners->field_0x1;
    }
    if (numInners != 0) {
      iVar13 = 0;
      do {
        *(undefined4*)(&bg->inners->field0_0x0 + iVar13) = 0xffffffff;
        *(undefined4*)(&bg->inners->field_0x4 + iVar13) = 0;
        *(undefined4*)(&bg->inners->field_0x8 + iVar13) = 0;
        FUN_00045d70(bg, inner_i);
        inner_i = inner_i + 1;
        iVar13 = iVar13 + 0x9c;
      } while (inner_i < (int)numInners);
    }
    fVar3 = (params->avatarParams).pos.z;
    if ((*(int*)((int)fVar3 + 0x14) != 0) || (*(int*)((int)fVar3 + 0x2c) != 0))
    {
      pvVar10 =
          malloc ? ((uint) * (byte*)(*(int*)((int)fVar3 + 0x10) + 1) * 0x1e0);
      *(void**)&bg->field_0x950 = pvVar10;
      FUN_00044490();
    }
  }
  FUN_00043b40();
  FUN_000432b0(bg);
  desc = (bg->avatar).modelRes;
  if (((desc != NULL) && (pMVar4 = desc->footerEntries, pMVar4 != NULL))
      && (desc_00 = *(ColliderSetDescriptor**)(pMVar4[2].subresourceType + 4),
          desc_00 != NULL))
  {
    BVar11 = ColliderSetDescriptor::hasSomething(desc_00);
    numInners = -(uint)(BVar11 != 0) & (uint)desc_00;
    if (numInners != 0) {
      loadBackgroundResource(numInners, 0);
    }
  }
  Assets::GetResourceBytes(
      "aid_aidlist_ghoulies_background_disableframebufferclear", &params);
  pbVar5 = params;
  if (params == NULL) {
    System::ExitGame(2);
  }
  params = pbVar5;
  inner_i = IndexOfAssetInAIDList((ReplayChapterMenu**)&params,
                                  (bg->avatar).modelAID);
  Assets::DecrementResourceCounter(pbVar5);
  if (inner_i != -1) {
    DAT_004dea50 = 1;
    bg->aidFound = 1;
  }
  desc = (bg->avatar).modelRes;
  params = NULL;
  if ((desc != NULL) && (pMVar4 = desc->footerEntries, pMVar4 != NULL)) {
    FUN_00042c30(
        **(undefined4**)(*(int*)(pMVar4[2].subresourceType + 0x24) + 8),
        0,
        *(undefined4*)&bg->field_0x9d8,
        *(undefined4*)&bg->field_0x9dc,
        0,
        &params);
  }
  (bg->avatar).hasActor ? = true;
  *(backgroundParams**)&bg->field_0x9e0 = params;
  *(undefined4*)&bg->field_0x954 = 0xffffffff;
  ::actor::createOnDeathObjects(&bg->avatar, 0);
  return 1;
  */
}

}  // namespace ghoulies::objects
