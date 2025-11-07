#include <iostream>

#include "../../game.hpp"
#include "background.hpp"
#include "graphics/model.hpp"

using graphics::DrawContext;

namespace ghoulies::objects
{

Background::Background(const BackgroundParams& params)
    : Avatar(params)
{
  GameContext& ctx {GameContext::Instance()};

  ctx.background_model_aid = params.model_aid;

  if (params.model_aid.empty()) {
    throw std::runtime_error("No model available for background.");
  }

  ctx.backgrounds.Register(&this->registry_entry_);

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

void Avatar::OnMessage(events::Message& msg)
{
  std::cout << "Avatar::OnMessage" << "\n";
};

void Avatar::Update() {};

bool Avatar::Draw(DrawContext& ctx)
{
  /*
ModelFooterEntry* pMVar1;
uint uVar2;
int iVar3;
ModelDescriptor* model_res;

if (param_1->field_0x197 != '\0') {
return 0;
}
update0x1d8s(param_1);
model_res = param_1->modelRes;
if (model_res == NULL) {
return 0;
}
if (someFlag == 0) {
if ((model_res->footerEntries[1].subresourceType & 0x10) == Model) {
return 0;
}
} else if ((someFlag == 2)
       && ((model_res->footerEntries[1].subresourceType & 8) == Model))
{
return 0;
}
if (param_1->hasActor? == false) {
::actor::createOnDeathObjects(param_1, 0);
}
iVar3 = FUN_00101930(*(undefined4*)&param_1->field_0x19c, 0xff000000);
if (iVar3 == 0) {
pMVar1 = *(ModelFooterEntry**)&param_1->field_0x19c;
uVar2 = *(uint*)&param_1->field_0x198;
model_res[0x12].runtimeCtx = (ModelRuntimeContext*)0x1;
model_res[0x12].field5_0x14 = uVar2;
model_res[0x13].footerEntries = pMVar1;
} else {
model_res[0x12].runtimeCtx = NULL;
}
if (*(code**)&param_1->field_0x1a0 != NULL) {
(**(code**)&param_1->field_0x1a0)(
  param_1, someFlag, *(undefined4*)&param_1->field_0x1a8);
}

// Draw the model with the actors affine matrix
  */

  if (this->model_ == nullptr) {
    return false;
  }

  // this->model_->DrawBasic(ctx.render_pass);
  this->model_->DrawWithTransform(
      ctx,
      ::graphics::Transform {
          .position = pos_, .rotation = rot_euler_, .scale = scale_});

  return true;
}

void Avatar::SetModel(std::string_view model_aid)
{
  auto& game_context {GameContext::Instance()};

  try {
    const auto* raw_asset {game_context.GetAsset(model_aid)};

    auto model_asset_exp {ModelAsset::FromAsset(*raw_asset)};

    if (!model_asset_exp.has_value()) {
      throw std::runtime_error(std::format(
          "Failed to create Avatar: No model exists with asset ID {}.",
          model_aid));
    }

    this->model_ = std::make_shared<::graphics::Model>(
        game_context.sdl_device, std::move(model_asset_exp).value());
  } catch (std::runtime_error& e) {
    throw std::runtime_error(
        std::format("Failed to create Avatar: {}", e.what()));
  }
}

Avatar::Avatar(const AvatarParams& params)
    : Object(params)
    , pos_(params.pos)
    , rot_euler_(params.rot_euler)
{
  this->scale_ = params.scale * glm::vec3 {1, 1, 1};

  if (!params.model_aid.empty()) {
    this->SetModel(params.model_aid);
  }
}

}  // namespace ghoulies::objects
