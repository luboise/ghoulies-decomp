/* assets.c - Asset loading: BNL/bundle assets, objParams, AID tables */
#include "assets.h"

int Assets::aidToBNLName(char *bnlOut,char *name)

{
  BOOL match;
  char *underscore_ptr;
  char *pcVar2;
  int i;
  char cVar1;
  
  if (name != (char *)0x0) {
    match = AssetNamesMatch(g_GlobalAssetName,name);
    if (match == 0) {
                    // Copy name into param_1
      i = (int)bnlOut - (int)name;
      do {
        cVar1 = *name;
        name[i] = cVar1;
        name = name + 1;
      } while (cVar1 != '\0');
                    // Find the final _
      i = 2;
      pcVar2 = bnlOut;
      do {
        underscore_ptr = _strchr(pcVar2,L'_');
        i = i + -1;
        pcVar2 = underscore_ptr + 1;
      } while (i != 0);
      *underscore_ptr = '\\';
      pcVar2 = bnlOut + -1;
      do {
        underscore_ptr = pcVar2;
        pcVar2 = underscore_ptr + 1;
      } while (underscore_ptr[1] != '\0');
      builtin_strncpy(underscore_ptr + 1,".bnl",5);
      return 0;
    }
  }
  *bnlOut = '\0';
  return 2;
}




void __fastcall Assets::HashBNLName(char *param_1)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = 0;
  bVar1 = *param_1;
  while (bVar1 != 0) {
    uVar2 = (bVar1 & 0xdf) + uVar2 * 0x10;
    param_1 = param_1 + 1;
    if ((uVar2 & 0xf0000000) != 0) {
      uVar2 = uVar2 ^ (uVar2 & 0xf0000000) >> 0x18;
    }
    bVar1 = *param_1;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void someResource::dtor(undefined4 param_1,undefined4 param_2)

{
  AssetDescription *local_8;
  BundleContext *local_4;
  
  Assets::BundleContext::getAssetDescriptionByName(param_2,&local_4,&local_8);
  local_8->useCount = local_8->useCount - 1;
  return;
}




void Assets::StateTableAsset::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  InitialiseAssetGroup("objparams",0x35c,0,objParams::AssetHeaders);
  InitialiseAssetGroup("statetable",0x29,1,Statetable::AssetHeaders);
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_00034c06;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_00034c06:
  pRVar2->typeStr = "statetable";
  pRVar2->processDescriptor = (void *)0x0;
  pRVar2->ctor = switchD_000d4179::EmptyFunction;
  pRVar2->dtor = switchD_000d4179::EmptyFunction;
  return;
}




void Assets::InitAssetGroups(void)

{
  createDirectoryResolver(FindAssetHeaderInBinary,AssetDescription::getSomeValues,(void *)0x0,4,0);
  AnimTableResource::InitLoader();
  InitialiseAssetGroup("attackdata",0x1d,1,AttackData::AssetHeaders);
  InitialiseAssetGroup("hitreaction",0x27,1,HitReactionResource::AssetHeaders);
  InitialiseAssetGroup("objparams",0x1f1,0,actorParams::AssetHeaders);
  InitialiseAssetGroup("scripttable",0x23,0,ScriptTable::AssetHeaders);
  StateTableAsset::InitLoader();
  return;
}



AssetHeader *

Assets::FindAssetHeaderInGroup(asset_name_t assetName,uint typeHash,AssetHeader *start,int count)

{
  BOOL same;
  int i;
  AssetHeader *header;
  
  i = 0;
  header = start;
  if (0 < count) {
    do {
      if ((typeHash == header->assetTypeHash) &&
         (same = AssetNamesMatch(header->name,assetName), same != 0)) {
        return start + i;
      }
      i = i + 1;
      header = header + 1;
    } while (i < count);
  }
  return (AssetHeader *)0x0;
}




AssetHeader * Assets::FindAssetHeader(char *assetName,BOOL fullSearch)

{
  AssetHeaderGroup *pAVar1;
  int iVar2;
  byte c;
  byte bVar3;
  uint32_t asset_type_hash;
  int i;
  AssetHeader *header;
  char *asset_type;
  AssetHeaderGroup *end;
  AssetHeaderGroup_ptr_4_AssetHeader__ cur_group;
  char copy_c;
  
  asset_type_hash = GetNameHash(assetName);
  end = g_assetHeaderGroups + g_parsedHeaderGroupsCount;
                    // If count > 0
  if (g_assetHeaderGroups < end) {
    cur_group = &g_assetHeaderGroups[0].headers;
    do {
      if ((fullSearch != 0) || (ADJ(cur_group)->importantAssetBool != 0)) {
        i = 0;
        copy_c = assetName[4];
        while (copy_c != '_') {
          LoadingAssetType[i] = copy_c;
          iVar2 = i + 5;
          i = i + 1;
          copy_c = assetName[iVar2];
        }
                    // Gets objparams
        LoadingAssetType[i] = '\0';
        asset_type = LoadingAssetType;
        do {
          c = *asset_type;
                    // To uppercase
          if (0x20 < c) {
            c = c & 0b11011111;
          }
          bVar3 = asset_type[(int)(cur_group + -0x137c87)];
          if (0x20 < bVar3) {
            bVar3 = bVar3 & 0b11011111;
          }
          if (c != bVar3) {
            if (c != bVar3) goto LAB_00034de2;
            break;
          }
          asset_type = asset_type + 1;
        } while (c != 0);
                    // If the group was found, go find the header in the group
        header = FindAssetHeaderInGroup
                           (assetName,asset_type_hash,ADJ(cur_group)->headers,ADJ(cur_group).count);
        if (header != (AssetHeader *)0x0) {
          return header;
        }
      }
LAB_00034de2:
                    // Go to next header group
      pAVar1 = (AssetHeaderGroup *)(cur_group + 10);
      cur_group = cur_group + 0xb;
    } while (pAVar1 < end);
  }
  return (AssetHeader *)0x0;
}



AssetHeaderGroup * __fastcall

Assets::InitialiseAssetGroup(char *groupName,uint count,BOOL param_3,AssetHeader *param_4)

{
  char cVar1;
  byte bVar2;
  int offset;
  AssetHeaderGroup *group;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar4;
  char c;
  
  uVar4 = g_parsedHeaderGroupsCount;
  offset = g_parsedHeaderGroupsCount * 0x2c;
  group = g_assetHeaderGroups + g_parsedHeaderGroupsCount;
  g_parsedHeaderGroupsCount = g_parsedHeaderGroupsCount + 1;
  group->count = count;
  g_assetHeaderGroups[uVar4].headers = param_4;
                    // Copy groupName into the group
  offset = (offset + 0x4dedb8) - (int)groupName;
  do {
    cVar1 = *groupName;
    groupName[offset] = cVar1;
    groupName = groupName + 1;
  } while (cVar1 != '\0');
  g_assetHeaderGroups[uVar4].importantAssetBool = param_3;
  if (count != 0) {
    pcVar4 = param_4->name + 4;
    do {
      bVar2 = *pcVar4;
      group = (AssetHeaderGroup *)(uint)bVar2;
      uVar4 = 0;
      pcVar5 = pcVar4;
                    // Hash the name of the first asset header, skipping aid_
      while (bVar2 != 0) {
                    // To uppercase
        uVar4 = ((uint)group & 0b11011111) + uVar4 * 0x10;
        pcVar5 = pcVar5 + 1;
        uVar3 = uVar4 & 0xf0000000;
        if (uVar3 != 0) {
          uVar4 = uVar4 ^ (uVar3 >> 0x18 | uVar3);
        }
        bVar2 = *pcVar5;
        group = (AssetHeaderGroup *)CONCAT31((int3)(uVar3 >> 8),bVar2);
      }
                    // Write the hash into the header
      *(uint *)(pcVar4 + 0x84) = uVar4;
      pcVar4 = pcVar4 + 0x8c;
      count = count - 1;
    } while (count != 0);
  }
  return group;
}




ResourceLoadStatus FindAssetHeaderInBinary(undefined4 param_1,char *name,AssetHeader **param_3)

{
  AssetHeader *header;
  
  header = Assets::FindAssetHeader(name,0);
  if (header != (AssetHeader *)0x0) {
    *param_3 = header;
    return IN_BINARY?;
  }
  return ERROR;
}



BOOL AssetDescription::getSomeValues
               (uint loaderId,AssetDescription *description,AssetType *assetType,uint32_t *hash1,
               undefined4 *resOffset,undefined4 *resSize)

{
  *hash1 = description->hash1;
  *assetType = description->assetType;
  *resOffset = 0;
  *resSize = 0;
  return 1;
}




char * Assets::LoctextPathFromHash(undefined4 param_1,char *param_2)

{
  int loctext;
  uint32_t uVar1;
  
  loctext = _strncmp(param_2,"aid_loctext_",12);
  if (loctext == 0) {
    uVar1 = GetNameHash(param_2);
    _sprintf(g_demandPathSprintfOut,"%s%s%08x",runtime::RootDirectory,asset_name_0042a690,uVar1);
    return g_demandPathSprintfOut;
  }
  return (char *)0x0;
}




char * Assets::FontPathFromHash(undefined4 param_1,char *param_2)

{
  int iVar1;
  uint32_t uVar2;
  
  iVar1 = _strncmp(param_2,"aid_font_",9);
  if (iVar1 == 0) {
    uVar2 = GetNameHash(param_2);
    _sprintf(g_demandPathSprintfOut,"%s%s%08x",runtime::RootDirectory,"font\\",uVar2);
    return g_demandPathSprintfOut;
  }
  return (char *)0x0;
}




char * Assets::DemandPathFromHash(undefined4 param_1,char *param_2)

{
  uint32_t uVar1;
  uint file_attribs;
  char *pcVar2;
  int unaff_FS_OFFSET;
  
  uVar1 = GetNameHash(param_2);
  _sprintf(g_demandPathSprintfOut,"%s%s%08x",runtime::RootDirectory,"demand\\",uVar1);
  file_attribs = QueryFile(g_demandPathSprintfOut);
  if (file_attribs == 0xffffffff) {
    pcVar2 = XAPILIB::GetLastError(unaff_FS_OFFSET);
    return (char *)((pcVar2 != (char *)0x0) - 1 & 0x4def98);
  }
  return (char *)(((-(uint)((file_attribs & FILE_ATTRIBUTE_DIRECTORY) != 0) & 0x10b) != 0) - 1 &
                 0x4def98);
}




undefined4 Assets::useLoaderToGetAssetHeader_(int loaderId,char *param_2,AssetDescription **param_3)

{
  uint uVar1;
  LoaderCallbacks *loader;
  int success;
  int iVar1;
  
  iVar1 = 0;
  uVar1 = 0;
  do {
    if (*(int *)((int)&directoryResolver[0].loaderId + uVar1) == loaderId) {
      loader = directoryResolver + iVar1;
      goto LAB_000350c5;
    }
    uVar1 = uVar1 + 0x18;
    iVar1 = iVar1 + 1;
  } while (uVar1 < 0x180);
  loader = (LoaderCallbacks *)0x0;
LAB_000350c5:
                    // Goes to 0x00034f00 (LoctextPathFromHash)
  success = (**loader->resolveDirectoryFn)(loaderId,param_2);
  if (success != 0) {
    *param_3 = (AssetDescription *)param_2;
    return 2;
  }
  return 0;
}



undefined4
loadDemandAsset(int loaderId,asset_name *assetName,uint32_t *descriptor_ptr,uint32_t *param_4,
               uint32_t *param_5,undefined4 *param_6)

{
  uint uVar1;
  LoaderCallbacks *pLVar2;
  char *filename;
  DWORD DVar3;
  int iVar4;
  int extraout_ECX;
  int extraout_ECX_00;
  DemandFileContext dfc;
  char acStack_104 [259];
  
  iVar4 = 0;
  uVar1 = 0;
  do {
    if (*(int *)((int)&Assets::directoryResolver[0].loaderId + uVar1) == loaderId) {
      pLVar2 = Assets::directoryResolver + iVar4;
      goto LAB_0003512a;
    }
    uVar1 = uVar1 + 0x18;
    iVar4 = iVar4 + 1;
  } while (uVar1 < 0x180);
  pLVar2 = (LoaderCallbacks *)0x0;
LAB_0003512a:
  filename = (char *)(**pLVar2->resolveDirectoryFn)(loaderId,assetName);
  builtin_strncpy(acStack_104,"Z:\\",4);
  XAPILIB::lstrcpynA(acStack_104 + 3,filename + 3,0x100);
  DVar3 = runtime::DoFileConsistencyCheck();
  iVar4 = extraout_ECX;
  if (DVar3 == 0) {
                    // If the file on the Z drive matches the one on the disc, delete the one on the
                    // Z drive
    uVar1 = CreateFilePointer(acStack_104,&dfc,(int)acStack_104);
    if (uVar1 == 0) goto LAB_000351d3;
    runtime::MarkForDeletion(acStack_104);
    iVar4 = extraout_ECX_00;
  }
  uVar1 = CreateFilePointer(filename,&dfc,iVar4);
  if (uVar1 != 0) {
    runtime::ExitGame(uVar1);
  }
  iVar4 = _strncmp(filename + 3,"font\\",5);
                    // If it is NOT a font
  if (iVar4 != 0) {
    runtime::ReadBNLFile(filename,acStack_104,(astruct_20 **)0x0,0,0);
  }
  if (uVar1 != 0) {
    return 0;
  }
LAB_000351d3:
  *descriptor_ptr = dfc.field26_0x20.descriptorPtr;
  *param_4 = dfc.field26_0x20.chunkCount;
  *param_5 = dfc.field26_0x20.totalAllocSize;
  *param_6 = dfc.field26_0x20.dataViewListPtr;
  if (*descriptor_ptr == 0) {
    *descriptor_ptr = *param_5;
  }
                    // Processes and advances file pointer forward (the first 32 bytes of the demand
                    // have been processed by now)
  Events::TriggerAssetTypeCallback1(assetName,(void *)*descriptor_ptr,(void *)*param_5);
  return 1;
}




ResourceReader * Assets::GetNewResourceHandle(void)

{
  ResourceReader *res;
  
  for (res = g_resourceReaders->head; res < g_resourceReaders->tail;
      res = (ResourceReader *)((int)&res->loaderId + (uint)g_resourceReaders->valueSize)) {
    if (res->loaderId == 0) goto LAB_0003574a;
  }
  if (g_resourceReaders->tail == g_resourceReaders->end) {
    g_resourceReaders = (Buffer<> *)runtime::ExtendArray((Buffer *)g_resourceReaders);
  }
  res = g_resourceReaders->tail;
  g_resourceReaders->tail =
       (ResourceReader *)((int)&res->loaderId + (uint)g_resourceReaders->valueSize);
LAB_0003574a:
  res->loaderId = 0;
  res->loadStatus = ERROR;
  res->fileOffset = 0;
  res->resOffset = 0;
  res->useCount = 0;
  res->resSize = 0;
  return res;
}




BOOL Assets::AssetNamesMatch(char *name1,asset_name_t name2)

{
  char c1;
  char *c2;
  int diff;
  char local_res0 [4];
  
  if (*(int *)name2 == 0x5f646961) {
    if (*(int *)name1 == L'\x5f646961') {
                    // If they both start with aid_
      c2 = name2 + 4;
      c1 = name2[4] & 0b11011111;
      if (c1 == (name1[4] & 0b11011111U)) {
        diff = (int)(name1 + 4) - (int)c2;
        do {
          c2 = c2 + 1;
          if (c1 == 0) {
            return 1;
          }
          c1 = *c2 & 0b11011111;
        } while (c1 == (c2[diff] & 0xdfU));
      }
    }
  }
  else if (*(int *)name1 != L'\x5f646961') {
    return 1;
  }
  return 0;
}



void Utils::SprintfToUpper
               (char *outStr,char *fmt,char *args,char *param_4,char *param_5,char *param_6)

{
  char *pcVar1;
  char c;
  
  __vsnprintf(outStr,128,fmt,(va_list)&args);
  c = *outStr;
  while (c != '\0') {
    c = *outStr;
    if (('@' < c) && (c < '[')) {
      *outStr = c + 32;
    }
    pcVar1 = outStr + 1;
    outStr = outStr + 1;
    c = *pcVar1;
  }
  return;
}




bool __fastcall Assets::AssetInGroup(undefined4 param_1,int param_2,char *param_3)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = 0;
  cVar2 = *(char *)(param_2 + 4);
  while (cVar2 != '_') {
    LoadingAssetType[iVar3] = cVar2;
    pcVar1 = (char *)(param_2 + 5 + iVar3);
    iVar3 = iVar3 + 1;
    cVar2 = *pcVar1;
  }
  LoadingAssetType[iVar3] = '\0';
  uVar4 = strcasecmp(LoadingAssetType,param_3);
  return (bool)('\x01' - (uVar4 != 0));
}




uint32_t Assets::GetNameHash(char *assetName)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  uchar bVar1;
  
  pbVar3 = (byte *)(assetName + 4);
  uVar1 = 0;
  bVar1 = *pbVar3;
  while (bVar1 != 0) {
    uVar1 = (bVar1 & 0b11011111) + uVar1 * 0x10;
    pbVar3 = pbVar3 + 1;
    uVar2 = uVar1 & 0xf0000000;
    if (uVar2 != 0) {
      uVar1 = uVar1 ^ (uVar2 >> 0x18 | uVar2);
    }
    bVar1 = *pbVar3;
  }
  return uVar1;
}




void AssetHandle::Unload(LoadedAssetHandle *param_1)

{
  Assets::DestroyAssetOrDecrement(param_1->sceneOrder);
  param_1->sceneOrder = (char *)0x0;
  return;
}



asset_name *

Assets::GetEntryAfterInTable(asset_name **assetTable,asset_name_t name,BOOL canFallbackToFirst)

{
  BOOL same;
  asset_name *asset;
  asset_name *asset_it;
  asset_name *first;
  
  first = *assetTable;
  if (first == (asset_name *)0x0) {
    return (asset_name *)0x0;
  }
  asset_it = first;
  if (name == (asset_name_t)0x0) {
    return first;
  }
                    // While we haven't found the asset
  while (same = AssetNamesMatch(*asset_it,name), same == 0) {
                    // If the next string in memory isn't an asset name, return NULL
                    // If we are no longer in the asset table, return NULL
    asset = asset_it + 1;
                    // If next next is bad, give up
    if (*(int *)asset_it[1] != L'\x5f646961') {
      asset = (asset_name *)0x0;
    }
    asset_it = asset;
    if (asset == (asset_name *)0x0) {
      return (asset_name *)0x0;
    }
  }
  if (asset_it == (asset_name *)0x0) {
    return (asset_name *)0x0;
  }
  if (*(int *)asset_it[1] != 0x5f646961) {
    if (canFallbackToFirst == 0) {
      return (asset_name *)0x0;
    }
    return first;
  }
  return asset_it + 1;
}




int AIDListResource::getLength(asset_name *param_1)

{
  int *piVar1;
  char *pcVar2;
  BOOL BVar3;
  char *name1;
  int i;
  char *name2;
  
  pcVar2 = *(char **)*param_1;
  i = 0;
  name2 = pcVar2;
  if (pcVar2 == (char *)0x0) {
    return 0;
  }
  do {
    i = i + 1;
    name1 = pcVar2;
    while (BVar3 = Assets::AssetNamesMatch(name1,name2), BVar3 == 0) {
      piVar1 = (int *)(name1 + 0x80);
      name1 = name1 + 0x80;
      if (*piVar1 != 0x5f646961) {
        name1 = (char *)0x0;
      }
      if (name1 == (char *)0x0) {
        return i;
      }
    }
    if ((name1 == (char *)0x0) || (name2 = name1 + 0x80, *(int *)(name1 + 0x80) != 0x5f646961)) {
      return i;
    }
  } while( true );
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Assets::InitGlobalBuffersAndLoaderCallbackTables(void)

{
  InitBigBlock((BigBlock *)D3D8::D3D_AllocContiguousMemory,(NamedCallbackTable *)FreePhysical);
  AnimResource::InitLoader();
  TextureDescriptor::InitLoader();
  ModelDescriptor::InitLoader();
  CutsceneResource::InitLoader();
  CameraResource::InitLoader();
  FontResource::InitLoader();
  LoctextResource::InitLoader();
  CalloutResource::InitLoader();
  LoadedResources = malloc_(4496);
  LoadedResources->head = LoadedResources->values;
  LoadedResources->tail = LoadedResources->values;
  LoadedResources->valueSize = 140;
  LoadedResources->capacity = 32;
  LoadedResources->end = (Asset *)(LoadedResources + 1);
  SmallAssetBuffer1 = malloc_(296);
  SmallAssetBuffer1->head = SmallAssetBuffer1->values;
  SmallAssetBuffer1->tail = SmallAssetBuffer1->values;
  SmallAssetBuffer1->valueSize = 140;
  SmallAssetBuffer1->capacity = 2;
  SmallAssetBuffer1->end = SmallAssetBuffer1->values + 2;
  SmallAssetBuffer2 = malloc_(296);
  SmallAssetBuffer2->head = SmallAssetBuffer2->values;
  SmallAssetBuffer2->tail = SmallAssetBuffer2->values;
  SmallAssetBuffer2->valueSize = 140;
  SmallAssetBuffer2->capacity = 2;
  SmallAssetBuffer2->end = SmallAssetBuffer2->values + 2;
  PTR_SmallAssetBuffer1 = (AssetBuffer<2> **)&SmallAssetBuffer1;
  return;
}




void * Assets::GetResourceBytesOrExit(int *someAID)

{
  void *local_4;
  
  if (*someAID != 0x5f646961) {
    return (void *)0x0;
  }
  GetResourceBytes((char *)someAID,&local_4);
  if (local_4 == (void *)0x0) {
    runtime::ExitGame(2);
  }
  return local_4;
}




int Assets::DestroyAssetOrDecrement(void *param_1)

{
  Asset *asset;
  int iVar1;
  
  for (asset = LoadedResources->head; asset < LoadedResources->tail;
      asset = (Asset *)(asset->name + LoadedResources->valueSize)) {
    if ((asset->description != (AssetDescription *)0x0) &&
       (*(void **)((int)&g_resourceReaders->head->fileOffset +
                  (int)((int)&asset->description[-1].totalAllocSize + 3) *
                  (uint)g_resourceReaders->valueSize) == param_1)) goto LAB_00035c45;
  }
  asset = (Asset *)0x0;
LAB_00035c45:
  iVar1 = asset->numUsages + -1;
  asset->numUsages = iVar1;
  return iVar1;
}




Asset * Assets::GetNewAssetInstance(char *inStr)

{
  char *char_i;
  uint32_t hash;
  Asset *instance;
  char c;
  
  for (instance = LoadedResources->head; instance < LoadedResources->tail;
      instance = (Asset *)(instance->name + LoadedResources->valueSize)) {
    if (instance->description == (AssetDescription *)0x0) goto LAB_00035e4d;
  }
  if (LoadedResources->tail == LoadedResources->end) {
    LoadedResources = (Buffer<> *)runtime::ExtendArray((Buffer *)LoadedResources);
  }
  instance = LoadedResources->tail;
                    // Push tail back by one element
  LoadedResources->tail = (Asset *)(instance->name + LoadedResources->valueSize);
LAB_00035e4d:
                    // If we find an empty spot, copy the name into it
  char_i = inStr;
  do {
    c = *char_i;
    char_i[(int)instance - (int)inStr] = c;
    char_i = char_i + 1;
  } while (c != '\0');
  instance->description = (AssetDescription *)0x0;
  instance->numUsages = 0;
  hash = GetNameHash(inStr);
  instance->nameHash = hash;
  return instance;
}




void Assets::GetResourceBytes(char *name,void **handle)

{
  Asset *res;
  Asset *search1;
  void *str;
  Asset *local_ECX_116;
  void *str_00;
  BOOL success;
  Buffer<> *buf1;
  Asset **tail1;
  
  success = 0;
  res = newAssetInstance(LoadedResources,name);
                    // If we can't find the asset, allocate for a new one
  if (res == (Asset *)0x0) {
    res = GetNewAssetInstance(name);
    search1 = newAssetInstance(SmallAssetBuffer1,name);
    str = newAssetInstance(SmallAssetBuffer2,name);
    if (search1 != (Asset *)0x0) {
      memcpy(res,search1,140);
      buf1 = SmallAssetBuffer1;
      tail1 = &SmallAssetBuffer1->tail;
                    // If weird copy, fix buffer
      local_ECX_116 = (Asset *)((int)SmallAssetBuffer1->tail - (uint)SmallAssetBuffer1->valueSize);
      if (search1 < local_ECX_116) {
        memcpy(search1,local_ECX_116,(uint)SmallAssetBuffer1->valueSize);
      }
      *tail1 = (Asset *)((int)*tail1 - (uint)buf1->valueSize);
    }
    if (str != (void *)0x0) {
      memcpy(res,str,140);
      buf1 = SmallAssetBuffer2;
      tail1 = &SmallAssetBuffer2->tail;
      str_00 = (void *)((int)SmallAssetBuffer2->tail - (uint)SmallAssetBuffer2->valueSize);
      if (str < str_00) {
        memcpy(str,str_00,(uint)SmallAssetBuffer2->valueSize);
      }
      *tail1 = (Asset *)((int)*tail1 - (uint)buf1->valueSize);
    }
    if (res == (Asset *)0x0) {
      res = GetNewAssetInstance(name);
    }
  }
                    // If the asset we found has been loaded 0 times, then load it
  if (res->numUsages == 0) {
    success = LoadResourceAttributes_(res,(uint32_t *)&res->description,&res->description);
  }
                    // If the load failed/the asset is in an invalid state, just return null
  if (res->description == (AssetDescription *)0x0) {
    *handle = (void *)0x0;
    return;
  }
  *handle = *(void **)((int)&g_resourceReaders->head->fileOffset +
                      (int)((int)&res->description[-1].totalAllocSize + 3) *
                      (uint)g_resourceReaders->valueSize);
  res->numUsages = res->numUsages + 1;
  if (success != 0) {
    createResourceFromName(res->name);
  }
  return;
}




void * Assets::newAssetInstance(Buffer<> *buf,char *name)

{
  uint32_t name_hash;
  Asset *head;
  Asset *tail;
  
  tail = buf->tail;
  head = buf->head;
  while( true ) {
    if (tail <= head) {
      return (void *)0x0;
    }
    name_hash = GetNameHash(name);
    if (head->nameHash == name_hash) break;
    head = (Asset *)(head->name + buf->valueSize);
  }
  return head;
}




ResourceLoaderStub * GetResourceLoaderStub(char *assetType)

{
  uint uVar1;
  ResourceLoaderStub *pAVar2;
  uint offset;
  
  offset = 0;
  pAVar2 = g_majorResourceLoaders;
  do {
    if (pAVar2->typeStr != (char *)0x0) {
      uVar1 = strcasecmp(pAVar2->typeStr,assetType);
      if (uVar1 == 0) {
        return g_majorResourceLoaders + offset;
      }
    }
    offset = offset + 1;
    pAVar2 = pAVar2 + 1;
  } while (offset < uVar2);
  return (ResourceLoaderStub *)0x0;
}




uint Assets::GetChapterIndexFromAID(char *assetName)

{
  char *pcVar2;
  int iVar3;
  uint uVar1;
  char *__s1;
  char cVar1;
  
  iVar3 = _strncmp("aid_script_ghoulies_chapter",assetName,0x1b);
                    // If string starts with "aid_script_ghoulies_chapter"
  if (iVar3 == 0) {
    uVar1 = 1;
    do {
      __s1 = g_chapterStrings[uVar1];
      pcVar2 = __s1;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      iVar3 = _strncmp(__s1,assetName + 0x1b,(int)pcVar2 - (int)(__s1 + 1));
      if (iVar3 == 0) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
    } while ((int)uVar1 < 10);
  }
  return 0;
}




Cutscene * Assets::LoadCutscene(char *cutsceneName,uint cutsceneFlags,Camera *camConfig)

{
  Cutscene *cutscene;
  CutsceneDescriptor *resource;
  uint cs_flags;
  byte num_animss;
  
  cs_flags = cutsceneFlags;
                    // cutsceneName: "aid_cutscene_ghoulies_dialogs_dialogpage1"
  if (*(int *)cutsceneName == 0x5f646961) {
    GetResourceBytes(cutsceneName,(void **)&cutsceneFlags);
    resource = (CutsceneDescriptor *)cutsceneFlags;
    if (cutsceneFlags == 0) {
      runtime::ExitGame(2);
    }
  }
  else {
    resource = (CutsceneDescriptor *)0x0;
  }
  cutsceneFlags = (uint)resource->length;
  num_animss = resource->numAnimResources;
  cutscene = Cutscene::ctor((float)cutsceneFlags,cs_flags,(uint)num_animss,resource);
  Cutscene::loadAnimations(cutscene,resource,cs_flags & 2,cs_flags & 4);
  Cutscene::loadEvents(cutscene,cutsceneName,(uint)num_animss);
  if ((resource->numCameras != '\0') && (camConfig != (Camera *)0x0)) {
    Cutscene::updateCameraFromCutscene(cutscene,camConfig);
  }
  g_assetName[0] = '\0';
  g_someWString[0x46]._0_1_ = 0;
  return cutscene;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Assets::LoadCutsceneSimple(char *cutsceneName,BOOL someFlag)

{
  sceneControlObj **ppsVar1;
  sceneControlObj **ppsVar2;
  sceneControlObj_0x8 puVar3;
  uint cutsceneFlags;
  Cutscene *pCVar4;
  Message local_8;
  
  Cutscene::CurrentCutsceneIndex = Cutscene::CurrentCutsceneIndex + 1;
  cutsceneFlags = (uint)(Cutscene::CurrentCutsceneIndex == 0);
  if (someFlag != 0) {
    cutsceneFlags = cutsceneFlags | 0x20;
  }
                    // Executes room walk in?
  pCVar4 = LoadCutscene(cutsceneName,cutsceneFlags,&Cutscene::CutsceneCam);
  Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex] = pCVar4;
  local_8.header.someActor = (actor *)Cutscene::LoadedCutscenes[Cutscene::CurrentCutsceneIndex];
  local_8.header.msgId = Scene_CutsceneAlloc;
  EventLoop::DispatchMessage((ObjMsgID *)&local_8);
  puVar3 = Game::SceneControls.next;
  while (puVar3 != (sceneControlObj_0x8)0x0) {
    ppsVar1 = (sceneControlObj **)(puVar3 + -8);
    ppsVar2 = (sceneControlObj **)(puVar3 + -8);
    puVar3 = *(sceneControlObj_0x8 *)(puVar3 + 4);
                    // Goes to 0x00115ee0 (entitySceneControl::update)
    (*(code *)((*ppsVar1)->obj_0x8).next)(ppsVar2,&local_8);
  }
  g_stateStack = g_stateStack + 1;
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Assets::CalloutResource::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_0004f627;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_0004f627:
  pRVar2->typeStr = "callout";
  pRVar2->processDescriptor = (void *)0x0;
  pRVar2->ctor = ctor;
  pRVar2->dtor = dtor;
  return;
}




void Assets::CalloutResource::ctor(ushort *param_1)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  
  uVar1 = param_1[2];
  puVar3 = param_1;
  while (uVar1 != 0) {
    puVar3 = (ushort *)((int)puVar3 + (uint)*puVar3);
    uVar1 = puVar3[2];
  }
  if (*(int *)(puVar3 + 0x24) != 0x5f646961) {
    puVar3[100] = 0;
    puVar3[0x65] = 0;
    return;
  }
  GetResourceBytes((char *)(puVar3 + 0x24),&param_1);
  puVar2 = param_1;
  if (param_1 == (ushort *)0x0) {
    runtime::ExitGame(2);
  }
  *(ushort **)(puVar3 + 100) = puVar2;
  return;
}




void Assets::CalloutResource::dtor(ushort *param_1)

{
  ushort uVar1;
  
  uVar1 = param_1[2];
  while (uVar1 != 0) {
    param_1 = (ushort *)((int)param_1 + (uint)*param_1);
    uVar1 = param_1[2];
  }
  if (*(void **)(param_1 + 100) != (void *)0x0) {
    DestroyAssetOrDecrement(*(void **)(param_1 + 100));
    param_1[100] = 0;
    param_1[0x65] = 0;
  }
  return;
}




void Assets::CameraResource::processMetadata(CameraDescriptor *resOffset,int fileOffset)

{
  float **ppfVar1;
  float *pfVar2;
  
  ppfVar1 = &(resOffset->posXValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  ppfVar1 = &(resOffset->posYValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  ppfVar1 = &(resOffset->posZValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  ppfVar1 = &(resOffset->rotXValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  ppfVar1 = &(resOffset->rotYValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  ppfVar1 = &(resOffset->rotZValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  ppfVar1 = &(resOffset->rotWValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  ppfVar1 = &(resOffset->zoomValues).floats;
  *ppfVar1 = (float *)((int)*ppfVar1 + fileOffset);
  pfVar2 = (resOffset->aspectRatioValues).floats;
  if (pfVar2 != (float *)0x0) {
    (resOffset->aspectRatioValues).floats = (float *)((int)pfVar2 + fileOffset);
  }
  return;
}




void Assets::CameraResource::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_0004f74f;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_0004f74f:
  pRVar2->typeStr = "camera";
  pRVar2->processDescriptor = processMetadata;
  pRVar2->ctor = (AfterLoadFn *)0x0;
  pRVar2->dtor = (void *)0x0;
  return;
}




void Assets::FontResource::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_00051627;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_00051627:
  pRVar2->typeStr = "font";
  pRVar2->processDescriptor = processMetadata;
  pRVar2->ctor = fromDescriptor;
  pRVar2->dtor = switchD_000d4179::EmptyFunction;
  Font::NullCharResource = (FontDescriptor *)0x0;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void Assets::FontResource::fromDescriptor(FontDescriptor *desc)

{
  int glyphCount;
  int i_ptr;
  
  glyphCount = (desc->endGlyph - desc->startGlyph) + 1;
  if (0 < glyphCount) {
    i_ptr = 0;
    do {
      if (0 < *(int *)((int)&desc->dataStart->field1_0x4 + i_ptr)) {
        TextureDescriptor::ctor(*(TextureDescriptor **)((int)&desc->dataStart->texHeaders + i_ptr));
      }
      i_ptr = i_ptr + 0x18;
      glyphCount = glyphCount + -1;
    } while (glyphCount != 0);
  }
  return;
}




void Assets::FontResource::processMetadata(void *param_1,uint resOffset,uint fileOffset)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int local_8;
  int local_4;
  
  *(int *)((int)param_1 + 0x14) = (int)param_1 + 0x18;
  local_4 = (*(int *)((int)param_1 + 4) - *(int *)param_1) + 1;
  if (0 < local_4) {
    local_8 = 0;
    do {
      piVar5 = (int *)(*(int *)((int)param_1 + 0x14) + local_8);
      if (0 < piVar5[1]) {
        *piVar5 = *piVar5 + (int)param_1;
        iVar1 = *(int *)(local_8 + *(int *)((int)param_1 + 0x14));
        if (*(int *)(iVar1 + 0x18) == 0) {
          *(undefined4 *)(iVar1 + 0x14) = 0;
        }
        else {
          uVar4 = 0;
          if (*(uint *)(fileOffset + 4) != 0) {
            piVar5 = (int *)(fileOffset + 0xc);
            uVar3 = 0;
            do {
              iVar2 = *piVar5;
              if (*(uint *)(iVar1 + 0x14) < uVar3 + iVar2) {
                *(uint *)(iVar1 + 0x14) =
                     (*(int *)(fileOffset + 8 + uVar4 * 8) - uVar3) + *(uint *)(iVar1 + 0x14);
                goto LAB_00051740;
              }
              uVar4 = uVar4 + 1;
              piVar5 = piVar5 + 2;
              uVar3 = uVar3 + iVar2;
            } while (uVar4 < *(uint *)(fileOffset + 4));
          }
          *(undefined4 *)(iVar1 + 0x14) = 0;
        }
      }
LAB_00051740:
      local_8 = local_8 + 0x18;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


int FontDescriptor::getSomeMeasurementByIndex(FontDescriptor *param_1,ushort param_2)

{
  uint uVar1;
  int index;
  
  if (param_2 != 0) {
    uVar1 = (uint)param_2;
    if (((int)param_1->startGlyph <= (int)uVar1) && ((int)uVar1 <= (int)param_1->endGlyph)) {
      index = uVar1 - param_1->startGlyph;
      if ((param_1->dataStart[index].texHeaders != (TextureDescriptor *)0x0) &&
         ((ushort)param_1->dataStart[index].field1_0x4 != 0xffffffff)) {
        return param_1->dataStart[index].field4_0x10 - param_1->dataStart[index].field2_0x8;
      }
    }
  }
  return param_1->xOffset_;
}




void Assets::LoctextResource::InitLoader(void)

{
  uint uVar1;
  ResourceLoaderStub *pRVar2;
  
  uVar1 = 0;
  pRVar2 = g_majorResourceLoaders;
  do {
    if (pRVar2->typeStr == (char *)0x0) {
      pRVar2 = g_majorResourceLoaders + uVar1;
      goto LAB_00051ec7;
    }
    uVar1 = uVar1 + 1;
    pRVar2 = pRVar2 + 1;
  } while (uVar1 < 0x10);
  pRVar2 = (ResourceLoaderStub *)0x0;
LAB_00051ec7:
  pRVar2->typeStr = "loctext";
  pRVar2->processDescriptor = processMetadata;
  pRVar2->ctor = switchD_000d4179::EmptyFunction;
  pRVar2->dtor = switchD_000d4179::EmptyFunction;
  return;
}



void __thiscall

Assets::LoctextResource::processMetadata(undefined4 param_1_00,LoctextDescriptor *param_1)

{
                    // Called for loctext
  FUN_001628c0(param_1,(int)param_1);
  return;
}



// WARNING: This is an inlined function
// WARNING: Inlined function: EmptyFunction


BOOL Font::GetTextHeight(float param_1,undefined4 param_2,int fontIndex)

{
  if (param_1 != 0.0) {
    return (BOOL)(&runtime::GloopyFontResource.gloopy)[fontIndex];
  }
  return CONCAT22((short)((uint)param_2 >> 0x10),
                  CONCAT11((param_1 == 0.0) << 6 | NAN(param_1) << 2 | 2U | param_1 < 0.0,
                           (char)param_2));
}




float Font::GetGlyph(int fontTableIndex,float param_2)

{
  FontDescriptor *pFVar1;
  uint uVar2;
  int iVar3;
  
  pFVar1 = (&runtime::GloopyFontResource.gloopy)[fontTableIndex];
  uVar2 = pFVar1->startGlyph;
  if (param_2 == 0.0) {
    if (((int)uVar2 < 0x6d) && (0x6b < (int)pFVar1->endGlyph)) {
      iVar3 = 0x6c - uVar2;
      if ((pFVar1->dataStart[iVar3].texHeaders != (TextureDescriptor *)0x0) &&
         ((ushort)pFVar1->dataStart[0x6c - uVar2].field1_0x4 != 0xffffffff)) {
        return (float)(int)(pFVar1->dataStart[iVar3].field4_0x10 -
                           pFVar1->dataStart[iVar3].field2_0x8) * DefaultFontScale.x;
      }
    }
    return (float)(int)pFVar1->xOffset_ * DefaultFontScale.x;
  }
  if (((int)uVar2 < 0x6d) && (0x6b < (int)pFVar1->endGlyph)) {
    iVar3 = 0x6c - uVar2;
    if ((pFVar1->dataStart[iVar3].texHeaders != (TextureDescriptor *)0x0) &&
       ((ushort)pFVar1->dataStart[0x6c - uVar2].field1_0x4 != 0xffffffff)) {
      return (float)(int)(pFVar1->dataStart[iVar3].field4_0x10 - pFVar1->dataStart[iVar3].field2_0x8
                         ) * param_2;
    }
  }
  return (float)(int)pFVar1->xOffset_ * param_2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void resource19::func5(void)

{
  func5();
  return;
}




void LoadAssetDatabase_(void)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  short sVar4;
  int unaff_ESI;
  float fVar5;
  float fVar6;
  
  iVar2 = *(int *)(*(int *)(unaff_ESI + 8) + 8);
  piVar3 = *(int **)(iVar2 + 0x95c);
  if ((*(int *)(unaff_ESI + 0x34) == 0) && (*(int *)(unaff_ESI + 0x1a4) != 0)) {
    uVar1 = *(ushort *)(iVar2 + 0xcf4);
    fVar5 = Game::HealthMetadata[0x11].maxHealth;
    if (uVar1 != 0) {
      fVar6 = (float)Game::HealthMetadata[0x11].minHealthU8;
      if ((float)Game::HealthMetadata[0x11].maxHealthU8 != fVar6) {
        fVar6 = (((float)(byte)Assets::GhouliesStatsheet[uVar1 - 1].healthStart - fVar6) /
                ((float)Game::HealthMetadata[0x11].maxHealthU8 - fVar6)) *
                (Game::HealthMetadata[0x11].maxHealth - Game::HealthMetadata[0x11].minHealth) +
                Game::HealthMetadata[0x11].minHealth;
        if (Game::HealthMetadata[0x11].maxHealth <= Game::HealthMetadata[0x11].minHealth) {
          if ((Game::HealthMetadata[0x11].maxHealth <= fVar6) &&
             (fVar5 = fVar6, Game::HealthMetadata[0x11].minHealth < fVar6)) {
            fVar5 = Game::HealthMetadata[0x11].minHealth;
          }
        }
        else if ((fVar6 <= Game::HealthMetadata[0x11].maxHealth) &&
                (fVar5 = fVar6, fVar6 < Game::HealthMetadata[0x11].minHealth)) {
          fVar5 = Game::HealthMetadata[0x11].minHealth;
        }
      }
    }
    piVar3[0x8f] = (int)(fVar5 * 0.5);
    sVar4 = (**(code **)(*piVar3 + 0x34))(piVar3);
  }
  else {
    sVar4 = *(short *)(unaff_ESI + 0x1a8);
    if (sVar4 == 0) {
      sVar4 = (**(code **)(*piVar3 + 0x20))(piVar3);
    }
  }
  *(short *)(unaff_ESI + 0xc) = sVar4;
  *(undefined4 *)(unaff_ESI + 0x1c) = 0;
  FUN_00089700();
  if (*(int *)(unaff_ESI + 0x80) != 0) {
    FUN_0001f830(*(undefined2 *)(unaff_ESI + 0x78));
    *(undefined4 *)(unaff_ESI + 0x80) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource19::func5(void)

{
  DXTextureInstance *pDVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  DialogState extraout_ECX;
  DialogState DVar5;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 *puVar6;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  int iVar7;
  
  iVar7 = DAT_00506568;
  DVar5 = Game::DialogState;
  if ((Game::DialogState == NotInDialog) &&
     (DVar5 = NotInDialog, *(int *)(DAT_00506568 + 0x104) != 0)) {
    puVar6 = (undefined4 *)(DAT_00506568 + 0x108);
    DVar5 = NotInDialog;
    if (*(int *)(DAT_00506568 + 0x108) != 0) {
      FUN_00048bc0();
      FUN_0004dbd0((Cutscene *)*puVar6);
      DVar5 = extraout_ECX;
    }
  }
  iVar4 = DAT_0050656c;
  iVar3 = DAT_00506554;
  switch(*(undefined4 *)(iVar7 + 0x16c)) {
  case 1:
    return;
  case 2:
    FUN_00061360((float)((int)*(float *)(DAT_00506554 + 0x2358) -
                        (int)(*(float *)(DAT_00506554 + 0x2360) * 0.5)),
                 (float)((int)*(float *)(DAT_00506554 + 0x235c) -
                        (int)(*(float *)(DAT_00506554 + 0x2364) * 0.5)),
                 (float)(int)*(float *)(DAT_00506554 + 0x2360),DAT_00428aac,
                 *(undefined4 *)(DAT_00506554 + 0x2368),unaff_EDI,unaff_ESI,unaff_EBP,DVar5);
    puVar6 = (undefined4 *)(iVar3 + 0x210);
    iVar7 = 4;
    break;
  case 3:
    if ((*(int *)(DAT_0050656c + 0x634) != 0) && (Game::DialogState == NotInDialog)) {
      DrawXboxButtons_(0,unaff_ESI);
    }
    iVar7 = *(int *)(iVar4 + 0x424);
    if (((iVar7 != 0) && (*(int *)(iVar7 + 4) != 0)) &&
       ((*(float *)(iVar7 + 0x14) != 0.0 || (*(float *)(iVar7 + 0x18) != 0.0)))) {
      DrawMalloced100Value
                (*(int *)(iVar7 + 4),iVar7 + 8,iVar7 + 0x14,0,*(TextDrawData **)(iVar7 + 0x10),
                 0xffffffff);
    }
    return;
  case 4:
    if (*(int *)(DAT_0050655c + 0x21c) != 0) {
      FUN_001221b0(*(int *)(DAT_0050655c + 0x21c),*(undefined4 *)(DAT_0050655c + 0x228),0,unaff_ESI)
      ;
    }
    return;
  case 5:
    FUN_00061360((float)((int)*(float *)(DAT_00506564 + 0x12d4) -
                        (int)(*(float *)(DAT_00506564 + 0x12dc) * 0.5)),
                 (float)((int)*(float *)(DAT_00506564 + 0x12d8) -
                        (int)(*(float *)(DAT_00506564 + 0x12e0) * 0.5)),
                 (float)(int)*(float *)(DAT_00506564 + 0x12dc),DAT_00428b8c,
                 *(undefined4 *)(DAT_00506564 + 0x12e4));
    FUN_000d3d80();
    return;
  default:
    return;
  }
  do {
    pDVar1 = (DXTextureInstance *)*puVar6;
    if (pDVar1 != (DXTextureInstance *)0x0) {
      Graphics::ReconfigureRenderer(unaff_EBX);
      Graphics::DrawTexture(-1,0,pDVar1,(vec2 *)(puVar6 + 4),0,0.0,-1,(vec2 *)(puVar6 + 1));
      Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
      if (Graphics::UseDefaultPixelC0 == 0) {
        DAT_00509b00 = 0;
      }
    }
    puVar6 = puVar6 + 0x213;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  piVar2 = *(int **)(iVar3 + 0x2134);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x14))
              (piVar2,(int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,3);
  }
  return;
}




undefined4 resource7::func2(undefined4 param_1,undefined4 *param_2)

{
  Camera *mv;
  char cVar1;
  Camera *pCVar2;
  LoctextValueContext *pLVar3;
  void *lp;
  CameraLLNode *pCVar4;
  Cutscene *pCVar5;
  BOOL BVar6;
  int iVar7;
  undefined4 unaff_ESI;
  char *pcVar8;
  undefined4 unaff_EDI;
  char *pcVar9;
  undefined4 *puVar10;
  vec2 local_120;
  int local_118;
  float local_114;
  float local_110;
  undefined1 local_10c [4];
  char local_108 [35];
  undefined4 local_e5 [23];
  char local_88 [39];
  undefined4 local_61 [23];
  
  mv = (Camera *)(param_2 + 0x10b);
  *param_2 = param_1;
  _DAT_00506570 = param_2;
  param_2[1] = 0;
  param_2[2] = game::nextPlaycamScriptWide;
  param_2[0x125] = 0;
  Camera::ctor(mv,"bonusbookcollection",(ProjectionSetBitField)0x8);
  param_2[0x117] = 0;
  Camera::ComputeTangents
            ((float)param_2[0x114],&local_118,&local_114,&local_110,(float *)(param_2 + 0x121),
             (float *)(param_2 + 0x122),0,local_10c,&local_120);
  pCVar4 = Camera::AvailableConfigs;
  pCVar2 = Camera::AvailableConfigs[0].head;
  while (pCVar2 != (Camera *)0x0) {
    pCVar4 = (CameraLLNode *)((Camera *)pCVar4)->next;
    pCVar2 = ((Camera *)pCVar4)->next;
  }
  pCVar2 = ((Camera *)pCVar4)->prev;
  ((Camera *)pCVar4)->prev = mv;
  mv->next = (Camera *)pCVar4;
  param_2[0x10c] = pCVar2;
  if (pCVar2 != (Camera *)0x0) {
    pCVar2->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(char *)(param_2 + 0x118));
  }
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
    pcVar8 = "aid_model_ghoulies_actor_dialogbat";
    pcVar9 = local_108;
    for (iVar7 = 8; iVar7 != 0; iVar7 = iVar7 + -1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    *(undefined2 *)pcVar9 = *(undefined2 *)pcVar8;
    pcVar9[2] = pcVar8[2];
    puVar10 = local_e5;
    for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    *(undefined1 *)puVar10 = 0;
    pcVar8 = "aid_model_ghoulies_actor_dialogbatgold";
    pcVar9 = local_88;
    for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar9 = pcVar9 + 4;
    }
    *(undefined2 *)pcVar9 = *(undefined2 *)pcVar8;
    pcVar9[2] = pcVar8[2];
    puVar10 = local_61;
    for (iVar7 = 0x16; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    *(undefined1 *)puVar10 = 0;
    iVar7 = 0;
    do {
      cVar1 = local_108[iVar7];
      g_assetName[iVar7] = cVar1;
      iVar7 = iVar7 + 1;
    } while (cVar1 != '\0');
    iVar7 = 0;
    do {
      cVar1 = local_88[iVar7];
      *(char *)((int)g_someWString + iVar7 + 0x8c) = cVar1;
      iVar7 = iVar7 + 1;
    } while (cVar1 != '\0');
  }
  pCVar5 = Assets::LoadCutscene("aid_cutscene_ghoulies_dialogs_dialogpage1",6,mv);
  param_2[0x10a] = pCVar5;
  Camera::SetActiveCameraConfig(0,"bonusbookcollection");
  param_2[0x123] = Game::GameState.currentChapter;
  param_2[0x124] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x80,(LoctextValueContext **)(param_2 + 0x109));
  pLVar3 = (LoctextValueContext *)param_2[0x109];
  (pLVar3->somePos).x = 3.0;
  (pLVar3->somePos).y = 0.7;
  pLVar3->maybeState = 3;
  XAPILIB::lstrcpyW((LPWSTR)(param_2 + 3),(LPCWSTR)param_2[2]);
  lp = PTR_005462c4;
  param_2[0x83] = 0x43a00000;
  param_2[0x84] = 0x420c0000;
  param_2[0x85] = 0;
  BVar6 = XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar6 == 0) {
    createGameselectString("gameselect","bonusbookcollection_banner",(LPWSTR)(param_2 + 0x86),lp);
  }
  param_2[0x106] = 0x43a00000;
  param_2[0x107] = 0x42700000;
  param_2[0x108] = 0;
  local_120.x = g_DXContext.field28_0x48;
  local_120.y = g_DXContext.__0 - 10.0;
  InitMalloced100(10,8.0,0.65,0,2.0,0.5,3,1,1,0,&local_120);
  FUN_000d55f0(1);
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource7::func3(int param_1)

{
  destroyGlobalMalloced100();
  _DAT_00506570 = 0;
  UnregisterScript__(*(int *)(param_1 + 0x424));
  *(undefined4 *)(param_1 + 0x424) = 0;
  if (*(Scene **)(param_1 + 0x494) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0x494));
    *(undefined4 *)(param_1 + 0x494) = 0;
  }
  Cutscene::dtor(*(Cutscene **)(param_1 + 0x428));
  *(undefined4 *)(param_1 + 0x428) = 0;
  Camera::setActiveCamera(param_1 + 0x42c);
  Game::GameState.currentChapter = *(int *)(param_1 + 0x48c);
  Game::GameState.currentScene = *(int *)(param_1 + 0x490);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource7::resource7::func5(int *param_1)

{
  Cutscene *cutscene;
  int iVar1;
  InputHandlerType3 *script3;
  float delta;
  
  cutscene = (Cutscene *)param_1[0x10a];
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,(Cutscene *)param_1[0x10a],(Camera *)(param_1 + 0x10b));
  }
  if ((Scene *)param_1[0x125] != (Scene *)0x0) {
    switch(param_1[1]) {
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
      goto switchD_000d525b_default;
    }
    Input::UpdateMenuInput(script3,(Scene *)param_1[0x125]);
  }
switchD_000d525b_default:
  if (param_1[1] == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar1 = *(int *)(*param_1 + 0x124), iVar1 < 2 || (3 < iVar1)) ||
        (*(int *)(*param_1 + 0x120) == 0)))) {
      FUN_000d55f0(2);
    }
  }
  else if (((param_1[1] == 3) && (TransitionData.discReadEnum == 0)) &&
          ((iVar1 = *(int *)(*param_1 + 0x124), iVar1 < 2 ||
           ((3 < iVar1 || (*(int *)(*param_1 + 0x120) == 0)))))) {
    FUN_000d55f0(4);
    FUN_00143790();
    return;
  }
  FUN_00143790();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource6::alloc(void)

{
  malloc_(0x1e0);
  return;
}




void resource6::func3(BonusChallengesMenu *param_1)

{
  void *mem;
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  _DAT_00506574 = 0;
  UnregisterScript__((int)param_1->field19_0x148);
  param_1->field19_0x148 = (LoctextValueContext *)0x0;
  FUN_000d6f90(param_1);
  if ((avatar *)param_1->field12_0x12c != (avatar *)0x0) {
    avatar::destroy((avatar *)param_1->field12_0x12c);
    param_1->field12_0x12c = 0;
  }
  if (param_1->field21_0x150 != (undefined *)0x0) {
    Assets::DestroyAssetOrDecrement(param_1->field21_0x150);
    param_1->field21_0x150 = (undefined *)0x0;
    *(undefined4 *)&param_1->field_0x15c = 0xff0000ff;
  }
  if ((void *)param_1->field30_0x168 != (void *)0x0) {
    Assets::DestroyAssetOrDecrement((void *)param_1->field30_0x168);
    param_1->field30_0x168 = 0;
    *(undefined4 *)&param_1->field_0x174 = 0xff0000ff;
  }
  FUN_000d6f90(param_1);
  Assets::DestroyAssetOrDecrement(param_1->field61_0x1d8);
  param_1->field61_0x1d8 = (undefined *)0x0;
  Assets::DestroyAssetOrDecrement(param_1->field13_0x130);
  Assets::DestroyAssetOrDecrement(param_1->field14_0x134);
  Assets::DestroyAssetOrDecrement(param_1->field15_0x138);
  Assets::DestroyAssetOrDecrement(param_1->field16_0x13c);
  Assets::DestroyAssetOrDecrement(param_1->field17_0x140);
  param_1->field13_0x130 = (undefined *)0x0;
  param_1->field14_0x134 = (undefined *)0x0;
  param_1->field15_0x138 = (undefined *)0x0;
  param_1->field16_0x13c = (undefined *)0x0;
  param_1->field17_0x140 = (undefined *)0x0;
  if (param_1->field47_0x1a0 != (Scene *)0x0) {
    Scene::free(param_1->field47_0x1a0);
    param_1->field47_0x1a0 = (Scene *)0x0;
  }
  Game::GameState.currentChapter = param_1->field45_0x198;
  Game::GameState.currentScene = param_1->field46_0x19c;
  mem = param_1->field4_0x10c;
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
  param_1->field4_0x10c = (void *)0x0;
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource19::alloc(void)

{
  malloc_(8);
  return;
}




undefined4 resource19::func2(undefined4 param_1,undefined4 *param_2)

{
  DAT_00506584 = param_2;
  *param_2 = 0;
  param_2[1] = param_1;
  FUN_000d3e30();
  *param_2 = 1;
  FUN_000d4230();
  return 1;
}




void resource19::func3(void)

{
  FUN_000d3fb0();
  DAT_00506584 = 0;
  return;
}




void resource19::func4(int *param_1)

{
  int iVar1;
  
  if (*param_1 == 1) {
    FUN_000d4070();
    iVar1 = FUN_000d4bc0();
    if (iVar1 != 0) {
      iVar1 = FUN_00116170();
      *(undefined4 *)(iVar1 + 0x94) = 3;
      *(undefined4 *)(iVar1 + 0x124) = 1;
      if (*(int *)(iVar1 + 0x120) != 0) {
        FromPlayToPause(*(int *)(iVar1 + 0x120));
        *(undefined4 *)(iVar1 + 0x120) = 0;
      }
      *DAT_00506584 = 2;
    }
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource::genericDealloc(void *param_1)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
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



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource2::alloc(void)

{
  malloc_(0x594);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource2::func2(undefined4 param_1,undefined4 *param_2)

{
  Camera *mv;
  Camera *pCVar1;
  LoctextValueContext *pLVar2;
  void *lp;
  CameraLLNode *pCVar3;
  Cutscene *cutscene;
  BOOL BVar4;
  int iVar5;
  undefined4 unaff_ESI;
  char *pcVar6;
  undefined4 unaff_EDI;
  char *pcVar7;
  undefined4 *puVar8;
  int local_94;
  undefined1 local_90 [4];
  float local_8c;
  undefined1 local_88 [4];
  float local_84;
  char local_80 [42];
  undefined4 local_56 [21];
  
  pcVar6 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  pcVar7 = local_80;
  for (iVar5 = 10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  *(undefined2 *)pcVar7 = *(undefined2 *)pcVar6;
  puVar8 = local_56;
  for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  *(undefined2 *)puVar8 = 0;
  param_2[0x163] = param_1;
  DAT_0050658c = param_2;
  *param_2 = 0;
  param_2[0x164] = 0;
  XAPILIB::lstrcpyW((LPWSTR)(param_2 + 0x123),game::nextPlaycamScriptWide);
  mv = (Camera *)(param_2 + 0x109);
  Camera::ctor(mv,"gameslotdeletion",(ProjectionSetBitField)0x8);
  param_2[0x115] = 0;
  Camera::ComputeTangents
            ((float)param_2[0x112],&local_94,&local_8c,&local_84,(float *)(param_2 + 0x11f),
             (float *)(param_2 + 0x120),0,local_90,local_88);
  pCVar3 = Camera::AvailableConfigs;
  pCVar1 = Camera::AvailableConfigs[0].head;
  while (pCVar1 != (Camera *)0x0) {
    pCVar3 = (CameraLLNode *)((Camera *)pCVar3)->next;
    pCVar1 = ((Camera *)pCVar3)->next;
  }
  pCVar1 = ((Camera *)pCVar3)->prev;
  ((Camera *)pCVar3)->prev = mv;
  mv->next = (Camera *)pCVar3;
  param_2[0x10a] = pCVar1;
  if (pCVar1 != (Camera *)0x0) {
    pCVar1->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(char *)(param_2 + 0x116));
  }
  cutscene = Assets::LoadCutscene(local_80,6,mv);
  param_2[0x108] = cutscene;
  Cutscene::update(cutscene,g_cutsceneDelta,0.0,0);
  Camera::SetActiveCameraConfig(0,"gameslotdeletion");
  param_2[0x121] = Game::GameState.currentChapter;
  param_2[0x122] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x40080,(LoctextValueContext **)(param_2 + 0x107));
  pLVar2 = (LoctextValueContext *)param_2[0x107];
  (pLVar2->somePos).x = 3.0;
  (pLVar2->somePos).y = 0.7;
  pLVar2->maybeState = 3;
  XAPILIB::lstrcpyW((LPWSTR)(param_2 + 1),(LPCWSTR)(param_2 + 0x123));
  lp = PTR_005462c4;
  param_2[0x81] = 0x43a00000;
  param_2[0x82] = 100.0;
  param_2[0x83] = 0;
  BVar4 = XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar4 == 0) {
    createGameselectString("gameselect","gameslotdeletion_deleteprompt",(LPWSTR)(param_2 + 0x84),lp)
    ;
  }
  param_2[0x104] = 0x43a00000;
  param_2[0x105] = 0x43700000;
  param_2[0x106] = 0;
  FUN_000dbdc0(param_2);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource2::func3(int param_1)

{
  DAT_0050658c = 0;
  UnregisterScript__(*(int *)(param_1 + 0x41c));
  *(undefined4 *)(param_1 + 0x41c) = 0;
  if (*(Scene **)(param_1 + 0x590) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0x590));
    *(undefined4 *)(param_1 + 0x590) = 0;
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


void resource2::func4(int *param_1)

{
  Cutscene *cutscene;
  InputHandlerType3 *script3;
  int iVar1;
  float delta;
  
  cutscene = (Cutscene *)param_1[0x108];
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,(Cutscene *)param_1[0x108],(Camera *)(param_1 + 0x109));
  }
  if ((Scene *)param_1[0x164] != (Scene *)0x0) {
    switch(*param_1) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
      script3 = (InputHandlerType3 *)0x0;
      break;
    case 2:
      script3 = Input::MenuInputHandler;
      break;
    default:
      goto switchD_000dba5a_default;
    }
    Input::UpdateMenuInput(script3,(Scene *)param_1[0x164]);
  }
switchD_000dba5a_default:
  iVar1 = *param_1;
  if (iVar1 == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar1 = *(int *)(param_1[0x163] + 0x124), iVar1 < 2 || (3 < iVar1)) ||
        (*(int *)(param_1[0x163] + 0x120) == 0)))) {
      FUN_000dbdc0(param_1);
    }
  }
  else if (iVar1 == 3) {
    iVar1 = FUN_0010f530(param_1 + 0x123);
    if (iVar1 == 0) {
      XAPILIB::lstrcpyW(game::nextPlaycamScriptWide,L"");
      iVar1 = FUN_00116170();
      *(undefined4 *)(iVar1 + 0x94) = 1;
      *(undefined4 *)(iVar1 + 0x124) = 1;
      if (*(int *)(iVar1 + 0x120) != 0) {
        FromPlayToPause(*(int *)(iVar1 + 0x120));
        *(undefined4 *)(iVar1 + 0x120) = 0;
      }
      FUN_000dbdc0(param_1);
      return;
    }
  }
  else if (((iVar1 == 4) && (TransitionData.discReadEnum == 0)) &&
          ((iVar1 = *(int *)(param_1[0x163] + 0x124), iVar1 < 2 ||
           ((3 < iVar1 || (*(int *)(param_1[0x163] + 0x120) == 0)))))) {
    FUN_000dbdc0(param_1);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource2::func5(int param_1)

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
  if (((g_globalFlagset & 0x40040) == 0) && (*(Cutscene **)(param_1 + 0x420) != (Cutscene *)0x0)) {
    FUN_0004dbd0(*(Cutscene **)(param_1 + 0x420));
  }
  if (*(int *)(param_1 + 0x590) == 0) {
    return;
  }
  DrawXboxButtons_();
  return;
}




void resource5::alloc(void)

{
  malloc_(0xf50);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource5::func2(int param_1,int *param_2)

{
  char cVar1;
  Camera *pCVar2;
  Camera *pCVar3;
  LoctextValueContext *pLVar4;
  Buffer<SaveEntry> *pBVar5;
  LPCWSTR pWVar6;
  void *lp;
  CameraLLNode *pCVar7;
  Cutscene *pCVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  undefined4 unaff_ESI;
  char *pcVar12;
  SaveEntry *pSVar13;
  LPWSTR pWVar14;
  undefined4 unaff_EDI;
  char *pcVar15;
  undefined4 *puVar16;
  LPCWSTR local_194;
  undefined1 local_190 [4];
  undefined1 local_18c [4];
  float local_188;
  int local_184;
  char local_180 [35];
  undefined4 local_15d [23];
  char local_100 [39];
  undefined4 local_d9 [22];
  char local_80 [42];
  undefined4 local_56 [21];
  
  pcVar12 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  pcVar15 = local_80;
  for (iVar11 = 10; iVar11 != 0; iVar11 = iVar11 + -1) {
    *(undefined4 *)pcVar15 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar15 = pcVar15 + 4;
  }
  *(undefined2 *)pcVar15 = *(undefined2 *)pcVar12;
  puVar16 = local_56;
  for (iVar11 = 0x15; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar16 = 0;
    puVar16 = puVar16 + 1;
  }
  *(undefined2 *)puVar16 = 0;
  param_2[0x3d2] = param_1;
  _DAT_00506590 = param_2;
  *param_2 = 0;
  param_2[0x3d1] = (int)game::nextPlaycamScriptWide;
  param_2[0x3d3] = 0;
  Camera::ctor((Camera *)(param_2 + 0x3b7),"gameslotinfo",(ProjectionSetBitField)0x8);
  param_2[0x3c3] = 0;
  Camera::ComputeTangents
            ((float)param_2[0x3c0],&local_184,&local_188,(float *)&local_194,
             (float *)(param_2 + 0x3cd),(float *)(param_2 + 0x3ce),0,local_190,local_18c);
  pCVar7 = Camera::AvailableConfigs;
  pCVar2 = Camera::AvailableConfigs[0].head;
  while (pCVar2 != (Camera *)0x0) {
    pCVar7 = (CameraLLNode *)((Camera *)pCVar7)->next;
    pCVar2 = ((Camera *)pCVar7)->next;
  }
  pCVar3 = ((Camera *)pCVar7)->prev;
  pCVar2 = (Camera *)(param_2 + 0x3b7);
  ((Camera *)pCVar7)->prev = pCVar2;
  pCVar2->next = (Camera *)pCVar7;
  param_2[0x3b8] = (int)pCVar3;
  if (pCVar3 != (Camera *)0x0) {
    pCVar3->next = pCVar2;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(char *)(param_2 + 0x3c4));
  }
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
    pcVar12 = "aid_model_ghoulies_actor_dialogbat";
    pcVar15 = local_180;
    for (iVar11 = 8; iVar11 != 0; iVar11 = iVar11 + -1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar12;
      pcVar12 = pcVar12 + 4;
      pcVar15 = pcVar15 + 4;
    }
    *(undefined2 *)pcVar15 = *(undefined2 *)pcVar12;
    pcVar15[2] = pcVar12[2];
    puVar16 = local_15d;
    for (iVar11 = 0x17; iVar11 != 0; iVar11 = iVar11 + -1) {
      *puVar16 = 0;
      puVar16 = puVar16 + 1;
    }
    *(undefined1 *)puVar16 = 0;
    pcVar12 = "aid_model_ghoulies_actor_dialogbatgold";
    pcVar15 = local_100;
    for (iVar11 = 9; iVar11 != 0; iVar11 = iVar11 + -1) {
      *(undefined4 *)pcVar15 = *(undefined4 *)pcVar12;
      pcVar12 = pcVar12 + 4;
      pcVar15 = pcVar15 + 4;
    }
    *(undefined2 *)pcVar15 = *(undefined2 *)pcVar12;
    pcVar15[2] = pcVar12[2];
    puVar16 = local_d9;
    for (iVar11 = 0x16; iVar11 != 0; iVar11 = iVar11 + -1) {
      *puVar16 = 0;
      puVar16 = puVar16 + 1;
    }
    *(undefined1 *)puVar16 = 0;
    iVar11 = 0;
    do {
      cVar1 = local_180[iVar11];
      g_assetName[iVar11] = cVar1;
      iVar11 = iVar11 + 1;
    } while (cVar1 != '\0');
    iVar11 = 0;
    do {
      cVar1 = local_100[iVar11];
      *(char *)((int)g_someWString + iVar11 + 0x8c) = cVar1;
      iVar11 = iVar11 + 1;
    } while (cVar1 != '\0');
  }
  pCVar8 = Assets::LoadCutscene(local_80,6,(Camera *)(param_2 + 0x3b7));
  param_2[0x3b6] = (int)pCVar8;
  Camera::SetActiveCameraConfig(0,"gameslotinfo");
  param_2[0x3cf] = Game::GameState.currentChapter;
  param_2[0x3d0] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x80,(LoctextValueContext **)(param_2 + 1));
  pLVar4 = (LoctextValueContext *)param_2[1];
  (pLVar4->somePos).x = 1.5;
  (pLVar4->somePos).y = 0.7;
  pLVar4->maybeState = 3;
  XAPILIB::lstrcpyW((LPWSTR)(param_2 + 2),(LPCWSTR)param_2[0x3d1]);
  lp = PTR_005462c4;
  param_2[0x82] = (int)g_DXContext.field28_0x48;
  param_2[0x83] = (int)g_DXContext.__0;
  param_2[0x83] = 0x42dc0000;
  param_2[0x84] = 0;
  XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  createGameselectString("gameselect","gameslotinfo_banner",(LPWSTR)(param_2 + 0x85),lp);
  param_2[0x105] = (int)g_DXContext.field28_0x48;
  param_2[0x106] = (int)g_DXContext.__0;
  param_2[0x106] = (int)50.0;
  param_2[0x107] = 0;
  iVar11 = 5;
  piVar9 = param_2 + 0x108;
  do {
    *(undefined2 *)piVar9 = 0;
    piVar9 = piVar9 + 0x83;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  pBVar5 = runtime::Saves->save1;
  pSVar13 = pBVar5->head;
  local_194 = (LPCWSTR)param_2[0x3d1];
  if (pSVar13 < pBVar5->tail) {
    do {
      iVar11 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar13->entries->field1_0x2,local_194);
      if (iVar11 == 0) {
        uVar10 = pSVar13->entries[1].field3_0xa;
        goto LAB_000dc3b3;
      }
      pSVar13 = (SaveEntry *)((int)&pSVar13->val1 + (uint)pBVar5->valueSize);
    } while (pSVar13 < pBVar5->tail);
  }
  uVar10 = 0;
LAB_000dc3b3:
  FUN_000fbb20(param_2 + 0x108,(float)(int)uVar10,1);
  pBVar5 = runtime::Saves->save1;
  pSVar13 = pBVar5->head;
  pWVar6 = (LPCWSTR)param_2[0x3d1];
  if (pSVar13 < pBVar5->tail) {
    do {
      iVar11 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar13->entries->field1_0x2,pWVar6);
      if (iVar11 == 0) {
        uVar10 = pSVar13->entries[1].field4_0xe;
        goto LAB_000dc40a;
      }
      pSVar13 = (SaveEntry *)((int)&pSVar13->val1 + (uint)pBVar5->valueSize);
    } while (pSVar13 < pBVar5->tail);
  }
  uVar10 = 0;
LAB_000dc40a:
  pWVar14 = (LPWSTR)(param_2 + 0x18b);
  if (uVar10 == 0) {
    iVar11 = XAPILIB::lstrlenW(pWVar14);
    pWVar14[iVar11] = L'0';
    (pWVar14 + iVar11)[1] = L'\0';
  }
  else {
    u__00507e78[0x810] = L'\0';
    XAPILIB::wsprintfW(u__00507e78 + 0x810,L"%d",uVar10);
    XAPILIB::lstrcatW(pWVar14,u__00507e78 + 0x810);
  }
  pBVar5 = runtime::Saves->save1;
  pSVar13 = pBVar5->head;
  pWVar6 = (LPCWSTR)param_2[0x3d1];
  if (pSVar13 < pBVar5->tail) {
    do {
      iVar11 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar13->entries->field1_0x2,pWVar6);
      if (iVar11 == 0) {
        uVar10 = pSVar13->entries[1].field5_0x12;
        goto LAB_000dc48e;
      }
      pSVar13 = (SaveEntry *)((int)&pSVar13->val1 + (uint)pBVar5->valueSize);
    } while (pSVar13 < pBVar5->tail);
  }
  uVar10 = 0;
LAB_000dc48e:
  pWVar14 = (LPWSTR)(param_2 + 0x20e);
  if (uVar10 == 0) {
    iVar11 = XAPILIB::lstrlenW(pWVar14);
    pWVar14[iVar11] = L'0';
    (pWVar14 + iVar11)[1] = L'\0';
  }
  else {
    u__00507e78[0x810] = L'\0';
    XAPILIB::wsprintfW(u__00507e78 + 0x810,L"%d",uVar10);
    XAPILIB::lstrcatW(pWVar14,u__00507e78 + 0x810);
  }
  pBVar5 = runtime::Saves->save1;
  pSVar13 = pBVar5->head;
  pWVar6 = (LPCWSTR)param_2[0x3d1];
  if (pSVar13 < pBVar5->tail) {
    do {
      iVar11 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar13->entries->field1_0x2,pWVar6);
      if (iVar11 == 0) {
        uVar10 = pSVar13->entries[1].field6_0x16;
        goto LAB_000dc518;
      }
      pSVar13 = (SaveEntry *)((int)&pSVar13->val1 + (uint)pBVar5->valueSize);
    } while (pSVar13 < pBVar5->tail);
  }
  uVar10 = 0;
LAB_000dc518:
  pWVar14 = (LPWSTR)(param_2 + 0x291);
  if (uVar10 == 0) {
    iVar11 = XAPILIB::lstrlenW(pWVar14);
    pWVar14[iVar11] = L'0';
    (pWVar14 + iVar11)[1] = L'\0';
  }
  else {
    u__00507e78[0x810] = L'\0';
    XAPILIB::wsprintfW(u__00507e78 + 0x810,L"%d",uVar10);
    XAPILIB::lstrcatW(pWVar14,u__00507e78 + 0x810);
  }
  pBVar5 = runtime::Saves->save1;
  pSVar13 = pBVar5->head;
  pWVar6 = (LPCWSTR)param_2[0x3d1];
  if (pSVar13 < pBVar5->tail) {
    do {
      iVar11 = XAPILIB::lstrcmpW((LPCWSTR)&pSVar13->entries->field1_0x2,pWVar6);
      if (iVar11 == 0) {
        uVar10 = pSVar13->entries[1].field7_0x1a;
        goto LAB_000dc5a1;
      }
      pSVar13 = (SaveEntry *)((int)&pSVar13->val1 + (uint)pBVar5->valueSize);
    } while (pSVar13 < pBVar5->tail);
  }
  uVar10 = 0;
LAB_000dc5a1:
  pWVar14 = (LPWSTR)(param_2 + 0x397);
  if (uVar10 == 0) {
    iVar11 = XAPILIB::lstrlenW(pWVar14);
    pWVar14[iVar11] = L'0';
    (pWVar14 + iVar11)[1] = L'\0';
  }
  else {
    u__00507e78[0x810] = L'\0';
    XAPILIB::wsprintfW(u__00507e78 + 0x810,L"%d",uVar10);
    XAPILIB::lstrcatW(pWVar14,u__00507e78 + 0x810);
  }
  iVar11 = 5;
  do {
    pWVar14[0] = L'\0';
    pWVar14[1] = L'\0';
    pWVar14 = pWVar14 + 0xc;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  param_2[0x3b5] = 0;
  if (*param_2 == 2) {
    param_2[0x3b5] = (int)0.5;
  }
  param_2[0x3d3] = 0;
  *param_2 = 1;
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource5::func3(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar1 = param_1;
  _DAT_00506590 = 0;
  UnregisterScript__(*(int *)(param_1 + 4));
  *(undefined4 *)(param_1 + 4) = 0;
  puVar2 = (undefined2 *)(param_1 + 0x420);
  iVar3 = 5;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 0x106;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (*(Scene **)(param_1 + 0xf4c) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0xf4c));
    *(undefined4 *)(param_1 + 0xf4c) = 0;
  }
  Cutscene::dtor(*(Cutscene **)(param_1 + 0xed8));
  *(undefined4 *)(param_1 + 0xed8) = 0;
  Camera::setActiveCamera(param_1 + 0xedc);
  puVar4 = (undefined4 *)(param_1 + 0xe5c);
  param_1 = 5;
  do {
    if ((void *)*puVar4 != (void *)0x0) {
      Assets::DestroyAssetOrDecrement((void *)*puVar4);
      *puVar4 = 0;
    }
    puVar4 = puVar4 + 6;
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  Game::GameState.currentChapter = *(int *)(iVar1 + 0xf3c);
  Game::GameState.currentScene = *(int *)(iVar1 + 0xf40);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource5::func4(int *param_1)

{
  Cutscene *cutscene;
  int iVar1;
  InputHandlerType3 *script3;
  float *pfVar2;
  float *pfVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  
  cutscene = (Cutscene *)param_1[0x3b6];
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    fVar5 = 0.0;
    if (runtime::dx_timer <= 0.0) {
      fVar5 = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(fVar5,(Cutscene *)param_1[0x3b6],(Camera *)(param_1 + 0x3b7));
  }
  if ((Scene *)param_1[0x3d3] != (Scene *)0x0) {
    switch(*param_1) {
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
      goto switchD_000dc76a_default;
    }
    Input::UpdateMenuInput(script3,(Scene *)param_1[0x3d3]);
  }
switchD_000dc76a_default:
  iVar1 = *param_1;
  if (iVar1 == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar1 = *(int *)(param_1[0x3d2] + 0x124), iVar1 < 2 || (3 < iVar1)) ||
        (*(int *)(param_1[0x3d2] + 0x120) == 0)))) {
      FUN_000dcb20();
      return;
    }
  }
  else {
    if (iVar1 == 2) {
      if (runtime::dx_timer <= 0.0) {
        fVar5 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar5 = 0.0;
      }
      if ((0.0 < (float)param_1[0x3b5]) &&
         (fVar5 = (float)param_1[0x3b5] - fVar5, param_1[0x3b5] = (int)fVar5, fVar5 <= 0.0)) {
        param_1[0x3b5] = 0;
      }
      pfVar3 = (float *)&DAT_00308050;
      pfVar2 = (float *)(param_1 + 0x39b);
      do {
        fVar5 = *pfVar3;
        fVar6 = ((float)param_1[0x3b5] - 0.5) * -2.0 * (fVar5 - 0.01) + 0.01;
        if (fVar5 <= 0.01) {
          if (fVar5 <= fVar6) {
            bVar4 = fVar6 < 0.01;
            goto LAB_000dc925;
          }
        }
        else if (fVar6 <= fVar5) {
          bVar4 = 0.01 < fVar6;
LAB_000dc925:
          fVar5 = fVar6;
          if (!bVar4 && fVar6 != 0.01) {
            fVar5 = 0.01;
          }
        }
        *pfVar2 = fVar5;
        pfVar2[1] = fVar5;
        pfVar3 = pfVar3 + 1;
        pfVar2 = pfVar2 + 6;
        if (0x308063 < (int)pfVar3) {
          return;
        }
      } while( true );
    }
    if (iVar1 == 3) {
      if (runtime::dx_timer <= 0.0) {
        fVar5 = runtime::DeltaTime * runtime::TimeScale;
      }
      else {
        fVar5 = 0.0;
      }
      if ((0.0 < (float)param_1[0x3b5]) &&
         (fVar5 = (float)param_1[0x3b5] - fVar5, param_1[0x3b5] = (int)fVar5, fVar5 <= 0.0)) {
        param_1[0x3b5] = 0;
      }
      pfVar3 = (float *)&DAT_00308050;
      pfVar2 = (float *)(param_1 + 0x39b);
      do {
        fVar5 = *pfVar3;
        fVar6 = ((float)param_1[0x3b5] - 0.5) * -2.0 * (0.01 - fVar5) + fVar5;
        if (0.01 <= fVar5) {
          if (0.01 <= fVar6) {
            bVar4 = fVar6 < fVar5;
            goto LAB_000dc854;
          }
          fVar6 = 0.01;
        }
        else if (fVar6 <= 0.01) {
          bVar4 = fVar5 < fVar6;
LAB_000dc854:
          if (!bVar4 && fVar5 != fVar6) {
            fVar6 = fVar5;
          }
        }
        else {
          fVar6 = 0.01;
        }
        *pfVar2 = fVar6;
        pfVar2[1] = fVar6;
        pfVar3 = pfVar3 + 1;
        pfVar2 = pfVar2 + 6;
      } while ((int)pfVar3 < 0x308064);
    }
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource5::func5(int param_1)

{
  float fVar1;
  DXTextureInstance *pDVar2;
  undefined4 uVar3;
  int iVar4;
  float *extraout_ECX;
  float *extraout_EDX;
  undefined4 *puVar5;
  
  iVar4 = FUN_000489e0(param_1 + 0xedc);
  if (iVar4 != 0) {
    Graphics::RecalculateWorldAndViews();
    FUN_0013c490((float *)(param_1 + 0xf08),(float *)(param_1 + 0xf04),
                 &Graphics::CurrentCameraStruct->affineT);
    fVar1 = *extraout_ECX;
    Graphics::CurrentCameraStruct->near = *extraout_EDX;
    Graphics::CurrentCameraStruct->far = fVar1;
    Graphics::UpdatePerspectiveProj();
    Graphics::UpdateViewport2();
  }
  if (*(Cutscene **)(param_1 + 0xed8) != (Cutscene *)0x0) {
    FUN_0004dbd0(*(Cutscene **)(param_1 + 0xed8));
  }
  puVar5 = (undefined4 *)(param_1 + 0xe5c);
  iVar4 = 5;
  do {
    pDVar2 = (DXTextureInstance *)*puVar5;
    if (pDVar2 != (DXTextureInstance *)0x0) {
      uVar3 = puVar5[3];
      Graphics::ReconfigureRenderer();
      Graphics::DrawTexture(-1,0,pDVar2,(vec2 *)(puVar5 + 4),0,0.0,uVar3,(vec2 *)(puVar5 + 1));
      Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
      if (Graphics::UseDefaultPixelC0 == 0) {
        DAT_00509b00 = 0;
      }
    }
    puVar5 = puVar5 + 6;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if (*(int *)(param_1 + 0xf4c) != 0) {
    DrawXboxButtons_();
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names


void resource4::alloc(void)

{
  malloc_(0x178);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource4::func2(undefined4 param_1,undefined4 *param_2)

{
  Camera *mv;
  Camera *pCVar1;
  CameraLLNode *pCVar2;
  Cutscene *cutscene;
  BOOL BVar3;
  int iVar4;
  char *pcVar5;
  wchar_t *lpString2;
  char *pcVar6;
  undefined4 *puVar7;
  int local_94;
  undefined1 local_90 [4];
  float local_8c;
  undefined1 local_88 [4];
  float local_84;
  char local_80 [42];
  undefined4 local_56 [21];
  
  pcVar5 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  pcVar6 = local_80;
  for (iVar4 = 10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
  puVar7 = local_56;
  for (iVar4 = 0x15; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  *(undefined2 *)puVar7 = 0;
  param_2[0x5d] = param_1;
  mv = (Camera *)(param_2 + 2);
  DAT_00506594 = param_2;
  *param_2 = 0;
  param_2[0x1a] = 0;
  *(undefined2 *)(param_2 + 0x1d) = 0;
  Camera::ctor(mv,"gameslotnaming",(ProjectionSetBitField)0x8);
  param_2[0xe] = 0;
  Camera::ComputeTangents
            ((float)param_2[0xb],&local_94,&local_8c,&local_84,(float *)(param_2 + 0x18),
             (float *)(param_2 + 0x19),0,local_90,local_88);
  pCVar2 = Camera::AvailableConfigs;
  pCVar1 = Camera::AvailableConfigs[0].head;
  while (pCVar1 != (Camera *)0x0) {
    pCVar2 = (CameraLLNode *)((Camera *)pCVar2)->next;
    pCVar1 = ((Camera *)pCVar2)->next;
  }
  pCVar1 = ((Camera *)pCVar2)->prev;
  ((Camera *)pCVar2)->prev = mv;
  mv->next = (Camera *)pCVar2;
  param_2[3] = pCVar1;
  if (pCVar1 != (Camera *)0x0) {
    pCVar1->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(char *)(param_2 + 0xf));
  }
  cutscene = Assets::LoadCutscene(local_80,6,mv);
  param_2[1] = cutscene;
  Cutscene::update(cutscene,g_cutsceneDelta,0.0,0);
  Camera::SetActiveCameraConfig(0,"gameslotnaming");
  lpString2 = u__00507e78;
  param_2[0x1b] = Game::GameState.currentChapter;
  param_2[0x1c] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  BVar3 = loctext::get_text("aid_loctext_ghoulies_savedgame","supportsavedgame","defaultnewgamename"
                            ,u__00507e78);
  if (BVar3 == 0) {
    lpString2 = L"ERROR";
  }
  XAPILIB::lstrcpyW((LPWSTR)(param_2 + 0x1d),lpString2);
  *param_2 = 1;
  FUN_00143070();
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource4::func3(int param_1)

{
  void *ptr;
  
  g_cutsceneDelta =
       *(float *)(*(int *)(param_1 + 4) + 0x2c) / *(float *)(*(int *)(param_1 + 4) + 0x34);
  DAT_00506594 = 0;
  Cutscene::dtor(*(Cutscene **)(param_1 + 4));
  *(undefined4 *)(param_1 + 4) = 0;
  Camera::setActiveCamera(param_1 + 8);
  ptr = *(void **)(param_1 + 0x68);
  if (ptr != (void *)0x0) {
    FUN_000113c0(ptr);
    free(ptr);
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  Game::GameState.currentChapter = *(int *)(param_1 + 0x6c);
  Game::GameState.currentScene = *(int *)(param_1 + 0x70);
  FUN_001430e0();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource4::func4(resource4 *param_1)

{
  Cutscene *cutscene;
  int iVar1;
  astruct_36 *paVar2;
  float delta;
  
  FUN_00109470((InputHandlerType4 *)Input::GlobalInputHandler);
  cutscene = param_1->csb;
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,param_1->csb,&param_1->camera);
  }
  iVar1 = param_1->field0_0x0;
  if (iVar1 == 1) {
    if (((TransitionData.discReadEnum == 0) &&
        (((iVar1 = *(int *)(param_1->field265_0x174 + 0x124), iVar1 < 2 || (3 < iVar1)) ||
         (*(int *)(param_1->field265_0x174 + 0x120) == 0)))) &&
       (param_1->field0_0x0 = 2, param_1->as36 == (astruct_36 *)0x0)) {
      paVar2 = (astruct_36 *)FUN_000110d0(&param_1->field12_0x74);
      param_1->as36 = paVar2;
    }
  }
  else if (((iVar1 == 2) || (iVar1 == 3)) && (param_1->as36 != (astruct_36 *)0x0)) {
    Input::DoBigUpdate(param_1->as36);
    return;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource4::func5(int *param_1)

{
  float fVar1;
  int iVar2;
  float *extraout_ECX;
  float *extraout_EDX;
  
  iVar2 = FUN_000489e0(param_1 + 2);
  if (iVar2 != 0) {
    Graphics::RecalculateWorldAndViews();
    FUN_0013c490((float *)(param_1 + 0xd),(float *)(param_1 + 0xc),
                 &Graphics::CurrentCameraStruct->affineT);
    fVar1 = *extraout_ECX;
    Graphics::CurrentCameraStruct->near = *extraout_EDX;
    Graphics::CurrentCameraStruct->far = fVar1;
    Graphics::UpdatePerspectiveProj();
    Graphics::UpdateViewport2();
  }
  if (((Game::DialogState == NotInDialog) && ((g_globalFlagset & 0x40040) == 0)) &&
     ((Cutscene *)param_1[1] != (Cutscene *)0x0)) {
    FUN_0004dbd0((Cutscene *)param_1[1]);
  }
  if ((((g_globalFlagset & DoRenderLoop?) == 0) && (*param_1 != 4)) && (param_1[0x1a] != 0)) {
    FUN_00011110();
  }
  return;
}




void resource1::alloc(void)

{
  malloc_(0xeac);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource1::func2(undefined4 param_1,undefined4 *param_2)

{
  float fVar1;
  char cVar2;
  ushort uVar3;
  LoctextValueContext *pLVar4;
  astruct_13 *paVar5;
  LoctextValueContext **ppLVar6;
  undefined4 *puVar7;
  void *pvVar8;
  char *pcVar9;
  int i;
  uint uVar10;
  uint uVar11;
  int *piVar12;
  char *name;
  int *piVar13;
  void *local_90;
  char *local_8c;
  void *local_88;
  LoctextValueContext **local_84;
  int local_80 [13];
  undefined4 local_4c [19];
  
  piVar12 = (int *)"aid_texture_ghoulies_gameselect_emptyslotbackground";
  piVar13 = local_80;
  for (i = 0xd; i != 0; i = i + -1) {
    *piVar13 = *piVar12;
    piVar12 = piVar12 + 1;
    piVar13 = piVar13 + 1;
  }
  puVar7 = local_4c;
  for (i = 0x13; i != 0; i = i + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  DAT_005065b8 = param_2;
  LoadFileSelectMovies();
  param_2[0x3a9] = param_1;
  *param_2 = 0;
  param_2[0x3a7] = 0;
  param_2[0x3a8] = 0;
  param_2[0x2e4] = 0;
  param_2[0x84] = 0;
  param_2[0x2cf] = 0;
  local_84 = (LoctextValueContext **)(param_2 + 0x2cf);
  param_2[0x83] = 0;
  param_2[0x81] = 0;
  param_2[0x82] = 0;
  *(undefined2 *)(param_2 + 1) = 0;
  DAT_0042a0c8 = 0;
  DAT_0042a0c4 = 0;
  resource::next_menu_id = 1;
  XAPILIB::lstrcpyW(g_wString,L"");
  uVar11 = PTR_00506c6c->field1_0x4;
  puVar7 = (undefined4 *)PTR_00506c6c->field2_0x8;
  for (uVar10 = uVar11 >> 2; paVar5 = PTR_00506c70, uVar10 != 0; uVar10 = uVar10 - 1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined1 *)puVar7 = 0;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  uVar11 = paVar5->capacity;
  puVar7 = paVar5->head;
  for (uVar10 = uVar11 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined1 *)puVar7 = 0;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  param_2[0x2e0] = 0;
  param_2[0x2e1] = 0;
  param_2[0x2e2] = 0;
  param_2[0x2e3] = 0;
  param_2[0x2c8] = 0;
  param_2[0x2c9] = 0;
  param_2[0x2ca] = DAT_00428f9c;
  param_2[0x2cb] = DAT_00428fa0;
  param_2[0x2cc] = 0xbadbadba;
  param_2[0x2cd] = 0xbadbadba;
  param_2[0x2ce] = 0;
  puVar7 = param_2 + 0x2e7;
  i = 3;
  do {
    *(undefined2 *)puVar7 = 0;
    puVar7 = puVar7 + 0x40;
    i = i + -1;
  } while (i != 0);
  param_2[0x2d0] = 0;
  if (local_80[0] == 0x5f646961) {
    Assets::GetResourceBytes((char *)local_80,&local_90);
    pvVar8 = local_90;
    if (local_90 == (void *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    pvVar8 = (void *)0x0;
  }
  param_2[0x2d0] = pvVar8;
  param_2[0x2d3] = -1;
  param_2[0x2d1] = g_DXContext.field28_0x48;
  param_2[0x2d2] = g_DXContext.__0;
  uVar3 = *(ushort *)(param_2[0x2d0] + 8);
  uVar11 = (uint)g_DXContext.backBufferWidth;
  param_2[0x2d5] = (float)g_DXContext.backBufferHeight / (float)*(ushort *)(param_2[0x2d0] + 10);
  param_2[0x2d4] = (float)uVar11 / (float)uVar3;
  param_2[0x2d6] = 0;
  param_2[0x2d9] = -1;
  param_2[0x2d7] = g_DXContext.field28_0x48;
  param_2[0x2d8] = g_DXContext.__0;
  param_2[0x2da] = param_2[0x2d4];
  param_2[0x2db] = param_2[0x2d5];
  param_2[0x2dc] = 0;
  param_2[0x2dd] = 0;
  local_8c = asset_name_0042941c;
  name = s_aid_texture_ghoulies_gameselect__00429048;
  puVar7 = param_2 + 0x11a;
  do {
    puVar7[-0x95] = 0;
    *(undefined2 *)(puVar7 + -0x94) = 0x65;
    *(undefined2 *)((int)puVar7 + -0x24a) = 0x6f;
    *(undefined2 *)((int)puVar7 + -0x24e) = 0x72;
    *(undefined2 *)(puVar7 + -0x93) = 0x72;
    *(undefined2 *)(puVar7 + -0x92) = 0x72;
    *(undefined2 *)((int)puVar7 + -0x246) = 0;
    puVar7[-0x14] = g_DXContext.field28_0x48;
    puVar7[-0x13] = g_DXContext.__0;
    puVar7[-0x14] = (float)puVar7[-0x14] + _DAT_00428fa8;
    puVar7[-0x13] = (float)puVar7[-0x13] + _DAT_00428fac;
    puVar7[-0x11] = 0;
    if (*(int *)name == 0x5f646961) {
      Assets::GetResourceBytes(name,&local_88);
      pvVar8 = local_88;
      if (local_88 == (void *)0x0) {
        runtime::ExitGame(2);
        pvVar8 = local_88;
      }
    }
    else {
      pvVar8 = (void *)0x0;
    }
    puVar7[-0x11] = pvVar8;
    puVar7[-0x10] = *(int *)((int)name + -0x1c);
    puVar7[-0xf] = *(int *)((int)name + -0x18);
    uVar11 = (uint)g_DXContext.backBufferHeight;
    uVar3 = *(ushort *)(puVar7[-0x11] + 10);
    fVar1 = *(float *)((int)name + -8);
    puVar7[-0xd] = ((float)g_DXContext.backBufferWidth * *(float *)((int)name + -0xc)) /
                   (float)*(ushort *)(puVar7[-0x11] + 8);
    puVar7[-0xc] = ((float)uVar11 * fVar1) / (float)uVar3;
    puVar7[-0xe] = -1;
    puVar7[-0xb] = 0;
    Assets::GetResourceBytes("aid_texture_ghoulies_gameselect_disc_discspin",&local_90);
    if (local_90 == (void *)0x0) {
      runtime::ExitGame(2);
    }
    puVar7[-0xb] = local_90;
    puVar7[-10] = *(int *)((int)name + -0x1c);
    puVar7[-9] = *(int *)((int)name + -0x18);
    puVar7[-10] = (float)puVar7[-10] + _DAT_00428fd0;
    puVar7[-9] = (float)puVar7[-9] + _DAT_00428fd4;
    puVar7[-7] = FLOAT_00428fc8;
    puVar7[-6] = FLOAT_00428fcc;
    puVar7[-8] = -1;
    puVar7[-2] = -1;
    puVar7[-4] = 0;
    puVar7[-3] = 0;
    puVar7[-1] = 0;
    *puVar7 = 0;
    puVar7[-5] = 0;
    puVar7[4] = -1;
    puVar7[2] = 0;
    puVar7[3] = 0;
    puVar7[5] = 0;
    puVar7[6] = 0;
    puVar7[1] = 0;
    pcVar9 = local_8c;
    do {
      cVar2 = *pcVar9;
      pcVar9[(int)puVar7 + (0x1c - (int)local_8c)] = cVar2;
      pcVar9 = pcVar9 + 1;
    } while (cVar2 != '\0');
    puVar7[0x27] = *(undefined4 *)(local_8c + 0x80);
    puVar7[0x28] = *(undefined4 *)(local_8c + 0x84);
    puVar7[0x29] = 0x80069764;
    puVar7[0x2a] = *(float *)((int)name + -0xc) * 640.0 + FLOAT_00428fbc;
    local_8c = local_8c + 0x10c;
    puVar7[0x2b] = *(float *)((int)name + -8) * 480.0 + FLOAT_00428fbc;
    name = (char *)((int)name + 0x124);
    puVar7 = puVar7 + 0xc1;
  } while ((int)local_8c < 0x429740);
  param_2[0x2e5] = Game::GameState.currentChapter;
  param_2[0x2e6] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  param_2[0x3aa] = 0;
  FUN_000df9a0(param_2,4);
  ppLVar6 = local_84;
  runtime::AllocateForLoctext_(0,1,(void *)0x80,local_84);
  fVar1 = DAT_00429010;
  pLVar4 = *ppLVar6;
  (pLVar4->somePos).x = DAT_0042900c;
  (pLVar4->somePos).y = fVar1;
  pLVar4->maybeState = 3;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource1::func3(int param_1)

{
  AllocatedMovie **ppAVar1;
  
  FUN_000df080();
  FUN_000df0b0();
  FUN_000df110();
  FUN_000df0e0();
  if (*(avatar **)(param_1 + 0xb38) != (avatar *)0x0) {
    avatar::destroy(*(avatar **)(param_1 + 0xb38));
    *(undefined4 *)(param_1 + 0xb38) = 0;
  }
  if (*(void **)(param_1 + 0xb40) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xb40));
    *(undefined4 *)(param_1 + 0xb40) = 0;
    *(undefined4 *)(param_1 + 0xb4c) = 0xff0000ff;
  }
  if (*(void **)(param_1 + 0xb58) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0xb58));
    *(undefined4 *)(param_1 + 0xb58) = 0;
    *(undefined4 *)(param_1 + 0xb64) = 0xff0000ff;
  }
  Game::GameState.currentChapter = *(int *)(param_1 + 0xb94);
  Game::GameState.currentScene = *(int *)(param_1 + 0xb98);
  ppAVar1 = PTR_ARRAY_00506598;
  do {
    if (*ppAVar1 != (AllocatedMovie *)0x0) {
      FUN_001072b0();
      *ppAVar1 = (AllocatedMovie *)0x0;
    }
    ppAVar1 = ppAVar1 + 1;
  } while ((int)ppAVar1 < 0x5065b8);
  if (*(int *)(param_1 + 0xb3c) != 0) {
    UnregisterScript__(*(int *)(param_1 + 0xb3c));
    *(undefined4 *)(param_1 + 0xb3c) = 0;
  }
  if (*(int *)(param_1 + 0x210) != 0) {
    UnregisterScript__(*(int *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0;
  }
  if (*(Scene **)(param_1 + 0xea8) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0xea8));
    *(undefined4 *)(param_1 + 0xea8) = 0;
  }
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource1::func4(undefined4 *param_1)

{
  float *pfVar1;
  InputHandlerType3 *script3;
  BOOL BVar2;
  undefined1 *puVar3;
  int iVar4;
  Scene *scene;
  uint64_t uVar5;
  
  switch(*param_1) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 6:
  case 7:
  case 8:
    scene = (Scene *)param_1[0x3aa];
    if (scene == (Scene *)0x0) goto switchD_000ddd94_default;
    script3 = (InputHandlerType3 *)0x0;
    break;
  case 5:
    scene = (Scene *)param_1[0x3aa];
    script3 = Input::MenuInputHandler;
    if (scene == (Scene *)0x0) goto switchD_000ddd94_default;
    break;
  default:
    goto switchD_000ddd94_default;
  }
  Input::UpdateMenuInput(script3,scene);
switchD_000ddd94_default:
  switch(*param_1) {
  case 1:
    if (param_1[0x3a7] == 0) {
      if (2 < (int)param_1[0x3a8]) {
        FUN_000df9a0(param_1,2);
        return;
      }
      FUN_000df650();
      return;
    }
    break;
  case 2:
    pfVar1 = (float *)(param_1 + 0x2e4);
    BVar2 = Timer::reduce(pfVar1);
    if (BVar2 == 0) {
      puVar3 = (undefined1 *)((int)param_1 + 1099);
      iVar4 = 3;
      do {
        if ((DAT_00429028 == 0.0) ||
           (param_1 = (undefined4 *)
                      (255.0 - ((*pfVar1 - DAT_00429028) / (0.0 - DAT_00429028)) * 255.0),
           (float)param_1 < 0.0)) {
          param_1 = (undefined4 *)0x0;
        }
        else if (255.0 < (float)param_1) {
          param_1 = (undefined4 *)255.0;
        }
        uVar5 = float10::to_uint64_t((float10)(float)param_1);
        *puVar3 = (char)uVar5;
        puVar3 = puVar3 + 0x304;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      return;
    }
    FUN_000df9a0(param_1,3);
    break;
  case 4:
    if (param_1[0x2df] == 0) {
      iVar4 = entitySceneControlGameSelect::isStatus2Or3
                        ((entitySceneControlGameSelect *)param_1[0x3a9]);
      if (iVar4 == 0) {
        FUN_000df9a0(param_1,1);
      }
    }
    else {
      FUN_000df3e0();
    }
    puVar3 = (undefined1 *)((int)param_1 + 1099);
    iVar4 = 3;
    do {
      *puVar3 = puVar3[-0x18];
      puVar3 = puVar3 + 0x304;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    return;
  case 6:
    FUN_000de540();
    return;
  case 7:
    FUN_000de7b0();
    return;
  }
  return;
}




void resource1::func5(int *param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  DXTextureInstance *pDVar4;
  int *piVar5;
  float *pfVar6;
  int *piVar7;
  float fVar8;
  undefined8 uVar9;
  uint64_t uVar10;
  undefined4 local_14;
  vec2 local_10;
  float local_8 [2];
  
  piVar5 = param_1;
  iVar2 = param_1[0x2cb];
  if ((g_globalFlagset & DoRenderLoop?) == 0) {
    iVar3 = param_1[0x2e0];
    if (iVar3 != 0) {
      if ((char)g_globalFlagset < '\0') {
        if (param_1[0x2e2] != 0) {
          *(int *)(iVar3 + 0x18) = *(int *)(iVar3 + 0x18) + -1;
          param_1[0x2e2] = 0;
        }
      }
      else if (param_1[0x2e2] == 0) {
        *(int *)(iVar3 + 0x18) = *(int *)(iVar3 + 0x18) + 1;
        param_1[0x2e2] = 1;
      }
    }
    local_10.x = *(float *)(param_1[0x3a9] + 0x84);
    if ((param_1[0x2e0] != 0) && (DAT_00429000 <= param_1[0x2e1])) {
      FUN_00107360();
    }
    iVar3 = param_1[0x2d0];
    if ((iVar3 != 0) && (*(int *)(iVar3 + 4) + (uint)*(byte *)(iVar3 + 0x12) * 0x14 + iVar3 != 0)) {
      uVar9 = FUN_00053680();
      if (((int)uVar9 != 0) && (*(char *)((int)param_1 + 0xb4f) != '\0')) {
        DrawMalloced100Value
                  ((int)((ulonglong)uVar9 >> 0x20),param_1 + 0x2d1,param_1 + 0x2d4,0,
                   (TextDrawData *)param_1[0x2d3],0);
      }
    }
    iVar3 = param_1[0x2d6];
    if ((iVar3 != 0) && (*(int *)(iVar3 + 4) + (uint)*(byte *)(iVar3 + 0x12) * 0x14 + iVar3 != 0)) {
      uVar9 = FUN_00053680();
      if (((int)uVar9 != 0) && (*(char *)((int)param_1 + 0xb67) != '\0')) {
        DrawMalloced100Value
                  ((int)((ulonglong)uVar9 >> 0x20),param_1 + 0x2d7,param_1 + 0x2da,0,
                   (TextDrawData *)param_1[0x2d9],0);
      }
    }
    param_1 = (int *)0x0;
    pfVar6 = (float *)(piVar5 + 0x145);
    do {
      if ((param_1 != (int *)piVar5[0x2cb]) && (pfVar6[-0x3c] != 0.0)) {
        FUN_00061360((float)((int)pfVar6[-0x3b] - (int)pfVar6[-1] / 2),
                     (float)((int)pfVar6[-0x3a] - (int)*pfVar6 / 2),(float)(int)pfVar6[-1],
                     DAT_00428f98,pfVar6[-2]);
        pDVar4 = (DXTextureInstance *)pfVar6[-0x3c];
        fVar8 = pfVar6[-0x39];
        Graphics::ReconfigureRenderer();
        Graphics::DrawTexture
                  (0,0,pDVar4,(vec2 *)(pfVar6 + -0x38),0,0.0,fVar8,(vec2 *)(pfVar6 + -0x3b));
        Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
        if (Graphics::UseDefaultPixelC0 == 0) {
          DAT_00509b00 = 0;
        }
      }
      param_1 = (int *)((int)param_1 + 1);
      pfVar6 = pfVar6 + 0xc1;
    } while ((int)param_1 < 3);
    if (piVar5[piVar5[0x2cb] * 0xc1 + 0x109] != 0) {
      FUN_00061360((float)((int)(float)piVar5[iVar2 * 0xc1 + 0x10a] -
                          (int)(float)piVar5[iVar2 * 0xc1 + 0x144] / 2),
                   (float)((int)(float)piVar5[iVar2 * 0xc1 + 0x10b] -
                          (int)(float)piVar5[iVar2 * 0xc1 + 0x145] / 2),
                   (float)(int)(float)piVar5[iVar2 * 0xc1 + 0x144],DAT_00428f98,
                   piVar5[iVar2 * 0xc1 + 0x143]);
      pDVar4 = (DXTextureInstance *)piVar5[iVar2 * 0xc1 + 0x109];
      iVar3 = piVar5[iVar2 * 0xc1 + 0x10c];
      Graphics::ReconfigureRenderer();
      Graphics::DrawTexture
                (0,0,pDVar4,(vec2 *)(piVar5 + iVar2 * 0xc1 + 0x10d),0,0.0,iVar3,
                 (vec2 *)(piVar5 + iVar2 * 0xc1 + 0x10a));
      Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
      if (Graphics::UseDefaultPixelC0 == 0) {
        DAT_00509b00 = 0;
      }
    }
    iVar3 = *piVar5;
    if ((0 < iVar3) && ((iVar3 < 3 || (iVar3 == 4)))) {
      piVar7 = piVar5 + 0x10f;
      param_1 = (int *)0x3;
      do {
        pDVar4 = (DXTextureInstance *)*piVar7;
        if (pDVar4 != (DXTextureInstance *)0x0) {
          iVar3 = piVar7[3];
          Graphics::ReconfigureRenderer();
          Graphics::DrawTexture(-1,0,pDVar4,(vec2 *)(piVar7 + 4),0,0.0,iVar3,(vec2 *)(piVar7 + 1));
          Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
          if (Graphics::UseDefaultPixelC0 == 0) {
            DAT_00509b00 = 0;
          }
        }
        piVar7 = piVar7 + 0xc1;
        param_1 = (int *)((int)param_1 + -1);
      } while (param_1 != (int *)0x0);
    }
    if ((piVar5[0x2e0] != 0) && (*(int *)(piVar5[0x2e0] + 8) != 0)) {
      if (DAT_00429000 < piVar5[0x2e1]) {
        fVar8 = (float)DAT_00429000;
        local_8[0] = 16.0;
        local_8[1] = 4.0;
        if ((float)(DAT_00429004 + DAT_00429000) == fVar8) {
          param_1 = (int *)255.0;
        }
        else {
          param_1 = (int *)((((float)piVar5[0x2e1] - fVar8) /
                            ((float)(DAT_00429004 + DAT_00429000) - fVar8)) * 255.0);
          if ((float)param_1 <= 255.0) {
            if ((float)param_1 < 0.0) {
              param_1 = (int *)0x0;
            }
          }
          else {
            param_1 = (int *)255.0;
          }
        }
        uVar10 = float10::to_uint64_t((float10)(float)param_1);
        fVar8 = local_10.x;
        local_14 = CONCAT13((char)uVar10,0xffffff);
        puVar1 = (undefined1 *)((int)local_10.x + 10);
        local_10.x = ((float)*(ushort *)(piVar5[iVar2 * 0xc1 + 0x109] + 8) *
                     (float)piVar5[piVar5[0x2cb] * 0xc1 + 0x10d]) /
                     (float)*(ushort *)((int)local_10.x + 8);
        local_10.y = ((float)*(ushort *)(piVar5[iVar2 * 0xc1 + 0x109] + 10) *
                     (float)piVar5[piVar5[0x2cb] * 0xc1 + 0x10e]) / (float)*(ushort *)puVar1;
        Graphics::ReconfigureRenderer();
        Graphics::DrawTexture
                  (0,(int)local_8,(DXTextureInstance *)fVar8,&local_10,piVar5 + iVar2 * 0xc1 + 0x141
                   ,0.0,local_14,(vec2 *)(piVar5 + iVar2 * 0xc1 + 0x10a));
        Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
        if (Graphics::UseDefaultPixelC0 == 0) {
          DAT_00509b00 = 0;
        }
      }
      piVar5[0x2e1] = piVar5[0x2e1] + 1;
    }
    piVar7 = piVar5 + 0x11b;
    param_1 = (int *)0x3;
    do {
      pDVar4 = (DXTextureInstance *)*piVar7;
      if (pDVar4 != (DXTextureInstance *)0x0) {
        iVar2 = piVar7[3];
        Graphics::ReconfigureRenderer();
        Graphics::DrawTexture(0,0,pDVar4,(vec2 *)(piVar7 + 4),0,0.0,iVar2,(vec2 *)(piVar7 + 1));
        Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
        if (Graphics::UseDefaultPixelC0 == 0) {
          DAT_00509b00 = 0;
        }
      }
      pDVar4 = (DXTextureInstance *)piVar7[-6];
      if (pDVar4 != (DXTextureInstance *)0x0) {
        iVar2 = piVar7[-3];
        Graphics::ReconfigureRenderer();
        Graphics::DrawTexture(0,0,pDVar4,(vec2 *)(piVar7 + -2),0,0.0,iVar2,(vec2 *)(piVar7 + -5));
        Graphics::UseDefaultPixelC0 = Graphics::UseDefaultPixelC0 + -1;
        if (Graphics::UseDefaultPixelC0 == 0) {
          DAT_00509b00 = 0;
        }
      }
      piVar7 = piVar7 + 0xc1;
      param_1 = (int *)((int)param_1 + -1);
    } while (param_1 != (int *)0x0);
    if ((piVar5[0x2df] == 0) && (iVar2 = piVar5[0x2ce], iVar2 != 0)) {
      if (*(float *)(iVar2 + 0x200) != DAT_00428f90) {
        *(float *)(iVar2 + 0x200) = DAT_00428f90;
        *(undefined4 *)(iVar2 + 0x2a8) = 0;
      }
      (**(code **)(*(int *)piVar5[0x2ce] + 0x14))
                ((int *)piVar5[0x2ce],
                 (int)&Graphics::CurrentCameraStruct[-0x2a8c].transformMat / 0x1e4,3);
    }
    if (piVar5[0x3aa] != 0) {
      DrawXboxButtons_(0);
    }
  }
  return;
}




undefined4 resource18::func2(undefined4 param_1,undefined4 *param_2)

{
  LPWSTR pWVar1;
  LoctextValueContext *pLVar2;
  void *pvVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  BOOL BVar6;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  
  puVar4 = param_2;
  param_2[0x90] = DAT_005065bc;
  param_2[0x92] = g_someDiskFloat;
  param_2[0x91] = DAT_005065c0;
  *param_2 = 0;
  param_2[0x8f] = param_1;
  param_2[0x89] = 0;
  pWVar1 = (LPWSTR)(param_2 + 7);
  param_2[0x87] = 0;
  param_2[0x88] = 0;
  *pWVar1 = L'\0';
  DAT_005065c8 = param_2;
  DAT_005065bc = 0;
  DAT_005065c0 = 0;
  g_someDiskFloat = 0.0;
  param_2[0x8b] = 0;
  param_2[0x8c] = 0;
  param_2[0x93] = 0;
  param_2[1] = 0;
  Assets::GetResourceBytes("aid_texture_ghoulies_gameselect_loading",&param_2);
  puVar5 = param_2;
  if (param_2 == (undefined4 *)0x0) {
    runtime::ExitGame(2);
  }
  puVar4[1] = puVar5;
  puVar4[4] = -1;
  puVar4[2] = g_DXContext.field28_0x48;
  puVar4[3] = g_DXContext.__0;
  puVar4[5] = 1.0;
  puVar4[6] = 1.0;
  runtime::AllocateForLoctext_(0,1,(void *)0x1c0,(LoctextValueContext **)(puVar4 + 0x8a));
  pLVar2 = (LoctextValueContext *)puVar4[0x8a];
  (pLVar2->somePos).x = 3.0;
  (pLVar2->somePos).y = 0.7;
  pLVar2->maybeState = 3;
  pvVar3 = PTR_005462c4;
  BVar6 = XAPILIB::IsBadReadPtr(PTR_005462c4,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar6 == 0) {
    createGameselectString("gameselect","loading",pWVar1,pvVar3);
  }
  puVar4[0x89] = 0;
  puVar4[0x87] = g_DXContext.field28_0x48;
  puVar4[0x88] = g_DXContext.__0;
  puVar4[0x88] = g_DXContext.field35_0x64 * 0.75;
  puVar4[0x8d] = Game::GameState.currentChapter;
  puVar4[0x8e] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  FUN_000e5b70();
  GlobalCounter2 = GlobalCounter2 + 1;
  FUN_000e0ad0();
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource18::func3(int param_1)

{
  GlobalCounter2 = GlobalCounter2 + -1;
  if ((*(int *)(param_1 + 0x240) != 0) && (Audio::PauseMusicPlaying == 0)) {
    Audio::PlayOrChangeByName(1,g_pauseMusicXACTID);
    Audio::PauseMusicPlaying = 1;
  }
  DAT_005065c8 = 0;
  UnregisterScript__(*(int *)(param_1 + 0x228));
  *(undefined4 *)(param_1 + 0x228) = 0;
  if (*(void **)(param_1 + 4) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  DAT_005065bc = 0;
  DAT_005065c0 = 0;
  Game::GameState.currentChapter = *(int *)(param_1 + 0x234);
  Game::GameState.currentScene = *(int *)(param_1 + 0x238);
  return;
}




void resource18::func4(int *param_1)

{
  uint uVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  if (*param_1 == 1) {
    fVar4 = 0.0;
    if (runtime::dx_timer <= 0.0) {
      fVar3 = runtime::DeltaTime * runtime::TimeScale;
    }
    else {
      fVar3 = 0.0;
    }
    if ((0.0 < (float)param_1[0x8b]) &&
       (fVar3 = (float)param_1[0x8b] - fVar3, param_1[0x8b] = (int)fVar3, fVar3 <= 0.0)) {
      param_1[0x8b] = 0;
      if (param_1[0x8c] == 0) {
        uVar1 = CreateLoctext((LoctextValueContext *)param_1[0x8a],(LPWSTR)(param_1 + 7),
                              (float)param_1[0x87],(float)param_1[0x88],1.5,1.5,1.0,1,0,1);
        fVar4 = 0.0;
        param_1[0x89] = uVar1;
        param_1[0x8c] = 1;
      }
      else {
        FUN_0005f7e0((LoctextValueContext *)param_1[0x8a]);
        param_1[0x8c] = 0;
      }
      param_1[0x8b] = (int)1.0;
    }
    iVar2 = DAT_005065c8;
    if (fVar4 == *(float *)(DAT_005065c8 + 0x248)) {
      iVar2 = runtime::GetSpaceUsedByDiskType(HARDDISK_0,(uint *)0x0,(uint *)0x0);
      if (iVar2 == 0) {
        FUN_000e0aa0();
        return;
      }
    }
    else {
      fVar3 = fVar4;
      if (runtime::dx_timer <= fVar4) {
        fVar3 = runtime::DeltaTime * runtime::TimeScale;
      }
      if ((fVar4 < *(float *)(DAT_005065c8 + 0x24c)) &&
         (fVar3 = *(float *)(DAT_005065c8 + 0x24c) - fVar3, *(float *)(DAT_005065c8 + 0x24c) = fVar3
         , fVar3 <= fVar4)) {
        *(float *)(iVar2 + 0x24c) = fVar4;
        FUN_000e0a60();
        return;
      }
    }
  }
  return;
}




void resource18::func5(int *param_1)

{
  if (((-1 < *param_1) && (*param_1 < 3)) && (param_1[1] != 0)) {
    DrawMalloced100Value(param_1[1],param_1 + 2,param_1 + 5,0,(TextDrawData *)param_1[4],0);
  }
  return;
}




void resource17::alloc(void)

{
  malloc_(0xac8);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource17::func2(undefined4 param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  Camera *pCVar3;
  LoctextValueContext *pLVar4;
  void *lp;
  undefined4 *puVar5;
  char *pcVar6;
  CameraLLNode *pCVar7;
  Cutscene *cutscene;
  BOOL BVar8;
  int iVar9;
  undefined4 unaff_ESI;
  Camera *camConfig;
  undefined4 unaff_EDI;
  char *pcVar10;
  vec2 local_1a4;
  float local_19c;
  float local_198;
  float local_194;
  Camera *local_190;
  int local_18c;
  char local_188 [35];
  undefined4 local_165 [23];
  char local_108 [39];
  undefined4 local_e1 [22];
  char local_88 [42];
  undefined4 local_5e [22];
  
  pcVar6 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  pcVar10 = local_88;
  for (iVar9 = 10; iVar9 != 0; iVar9 = iVar9 + -1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar10 = pcVar10 + 4;
  }
  *(undefined2 *)pcVar10 = *(undefined2 *)pcVar6;
  puVar5 = local_5e;
  for (iVar9 = 0x15; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = 0;
  param_2[0x124] = param_1;
  DAT_005065cc = param_2;
  *param_2 = 0;
  param_2[0x123] = game::nextPlaycamScriptWide;
  param_2[0x125] = 0;
  puVar5 = param_2 + 0x126;
  iVar9 = 3;
  do {
    *puVar5 = 0;
    puVar5[0x83] = 0;
    puVar5[0x81] = 0;
    puVar5[0x82] = 0;
    *(undefined2 *)(puVar5 + 1) = 0;
    puVar5 = puVar5 + 0x84;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  camConfig = (Camera *)(param_2 + 0x109);
  param_2[0x10d] = 0;
  param_2[0x10c] = 0;
  param_2[0x10b] = 0;
  *(undefined1 *)((int)param_2 + 0x479) = 8;
  param_2[0x10e] = 0.0;
  param_2[0x10f] = 0.0;
  param_2[0x110] = 0.0;
  param_2[0x111] = 1.0;
  pcVar6 = "options";
  param_2[0x112] = -1.0;
  param_2[0x115] = 3;
  param_2[0x113] = 0x4e6e6b28;
  param_2[0x114] = 0;
  do {
    cVar1 = *pcVar6;
    *(char *)((int)(param_2 + -0xc9351) + (int)pcVar6) = cVar1;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  fVar2 = (float)param_2[0x112];
  camConfig->next = (Camera *)0x0;
  param_2[0x10a] = 0;
  local_190 = camConfig;
  Camera::ComputeTangents
            (fVar2,&local_18c,&local_194,&local_198,(float *)(param_2 + 0x11f),
             (float *)(param_2 + 0x120),param_2[0x115],&local_19c,&local_1a4);
  param_2[0x115] = 0;
  Camera::ComputeTangents
            ((float)param_2[0x112],&local_18c,&local_19c,&local_1a4.x,(float *)(param_2 + 0x11f),
             (float *)(param_2 + 0x120),0,&local_194,&local_198);
  pCVar7 = Camera::AvailableConfigs;
  pCVar3 = Camera::AvailableConfigs[0].head;
  while (pCVar3 != (Camera *)0x0) {
    pCVar7 = (CameraLLNode *)((Camera *)pCVar7)->next;
    pCVar3 = ((Camera *)pCVar7)->next;
  }
  pCVar3 = ((Camera *)pCVar7)->prev;
  ((Camera *)pCVar7)->prev = camConfig;
  camConfig->next = (Camera *)pCVar7;
  param_2[0x10a] = pCVar3;
  if (pCVar3 != (Camera *)0x0) {
    pCVar3->next = camConfig;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(char *)(param_2 + 0x116));
  }
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
    pcVar6 = "aid_model_ghoulies_actor_dialogbat";
    pcVar10 = local_188;
    for (iVar9 = 8; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar10 = pcVar10 + 4;
    }
    *(undefined2 *)pcVar10 = *(undefined2 *)pcVar6;
    pcVar10[2] = pcVar6[2];
    puVar5 = local_165;
    for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined1 *)puVar5 = 0;
    pcVar6 = "aid_model_ghoulies_actor_dialogbatgold";
    pcVar10 = local_108;
    for (iVar9 = 9; iVar9 != 0; iVar9 = iVar9 + -1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar10 = pcVar10 + 4;
    }
    *(undefined2 *)pcVar10 = *(undefined2 *)pcVar6;
    pcVar10[2] = pcVar6[2];
    puVar5 = local_e1;
    for (iVar9 = 0x16; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined1 *)puVar5 = 0;
    iVar9 = 0;
    do {
      cVar1 = local_188[iVar9];
      g_assetName[iVar9] = cVar1;
      iVar9 = iVar9 + 1;
    } while (cVar1 != '\0');
    iVar9 = 0;
    do {
      cVar1 = local_108[iVar9];
      *(char *)((int)g_someWString + iVar9 + 0x8c) = cVar1;
      iVar9 = iVar9 + 1;
      camConfig = local_190;
    } while (cVar1 != '\0');
  }
  cutscene = Assets::LoadCutscene(local_88,6,camConfig);
  param_2[0x108] = cutscene;
  Cutscene::update(cutscene,g_cutsceneDelta,0.0,0);
  Camera::SetActiveCameraConfig(0,"options");
  param_2[0x121] = Game::GameState.currentChapter;
  param_2[0x122] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x400c0,(LoctextValueContext **)(param_2 + 0x107));
  fVar2 = FLOAT_0042998c;
  pLVar4 = (LoctextValueContext *)param_2[0x107];
  (pLVar4->somePos).x = FLOAT_00429988;
  (pLVar4->somePos).y = fVar2;
  pLVar4->maybeState = 3;
  XAPILIB::lstrcpyW((LPWSTR)(param_2 + 1),(LPCWSTR)param_2[0x123]);
  lp = PTR_005462c4;
  fVar2 = FLOAT_0042996c;
  param_2[0x81] = FLOAT_00429968;
  param_2[0x82] = fVar2;
  param_2[0x83] = 0;
  BVar8 = XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar8 == 0) {
    createGameselectString("gameselect","options_optionsbanner",(LPWSTR)(param_2 + 0x84),lp);
  }
  fVar2 = FLOAT_00429964;
  param_2[0x104] = FLOAT_00429960;
  param_2[0x105] = fVar2;
  param_2[0x106] = 0;
  local_1a4.x = g_DXContext.field28_0x48 + FLOAT_00429990;
  local_1a4.y = g_DXContext.__0 + FLOAT_00429994;
  InitMalloced100(UINT_00429998,FLOAT_0042999c,FLOAT_004299a0,0,FLOAT_004299a8,FLOAT_004299ac,3,
                  DAT_004299a4,0,1,&local_1a4);
  FUN_000e1a80(1);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource17::func3(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + 0x498);
  iVar1 = 3;
  do {
    FUN_001434e0();
    *puVar2 = 0;
    puVar2 = puVar2 + 0x84;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  destroyGlobalMalloced100();
  DAT_005065cc = 0;
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


void resource17::func4(int *param_1)

{
  Cutscene *cutscene;
  int iVar1;
  InputHandlerType3 *script3;
  float delta;
  
  cutscene = (Cutscene *)param_1[0x108];
  if (cutscene != (Cutscene *)0x0) {
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
      break;
    case 2:
      script3 = Input::MenuInputHandler;
      if (Game::DialogState != NotInDialog) goto switchD_000e107a_default;
      break;
    default:
      goto switchD_000e107a_default;
    }
    Input::UpdateMenuInput(script3,(Scene *)param_1[0x125]);
  }
switchD_000e107a_default:
  if (*param_1 == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar1 = *(int *)(param_1[0x124] + 0x124), iVar1 < 2 || (3 < iVar1)) ||
        (*(int *)(param_1[0x124] + 0x120) == 0)))) {
      FUN_000e1a80(2);
    }
  }
  else if (((*param_1 == 3) && (TransitionData.discReadEnum == 0)) &&
          ((iVar1 = *(int *)(param_1[0x124] + 0x124), iVar1 < 2 ||
           ((3 < iVar1 || (*(int *)(param_1[0x124] + 0x120) == 0)))))) {
    FUN_000e1a80(4);
    FUN_00143790();
    return;
  }
  FUN_00143790();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource17::func5(int param_1)

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
  if (((g_globalFlagset & 0x40040) == 0) && (*(Cutscene **)(param_1 + 0x420) != (Cutscene *)0x0)) {
    FUN_0004dbd0(*(Cutscene **)(param_1 + 0x420));
  }
  if ((*(int *)(param_1 + 0x494) != 0) && (Game::DialogState == NotInDialog)) {
    DrawXboxButtons_(0);
  }
  FUN_00143840();
  return;
}




undefined4 resource16::ctor(undefined4 param_1,undefined4 *param_2)

{
  char cVar1;
  byte *pbVar2;
  Camera *pCVar3;
  LoctextValueContext *pLVar4;
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
  uint uVar14;
  undefined4 unaff_ESI;
  char *pcVar15;
  Camera *mv;
  undefined4 unaff_EDI;
  char *pcVar16;
  undefined4 *puVar17;
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
  char local_88 [42];
  undefined4 local_5e [22];
  
  paVar10 = SomeAS15;
  pcVar15 = "aid_cutscene_ghoulies_dialogs_dialogpage1";
  pcVar16 = local_88;
  for (iVar13 = 10; iVar13 != 0; iVar13 = iVar13 + -1) {
    *(undefined4 *)pcVar16 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar16 = pcVar16 + 4;
  }
  *(undefined2 *)pcVar16 = *(undefined2 *)pcVar15;
  puVar17 = local_5e;
  for (iVar13 = 0x15; iVar13 != 0; iVar13 = iVar13 + -1) {
    *puVar17 = 0;
    puVar17 = puVar17 + 1;
  }
  *(undefined2 *)puVar17 = 0;
  param_2[0x125] = param_1;
  param_2[0x123] = game::nextPlaycamScriptWide;
  *param_2 = 0;
  param_2[0x126] = 0;
  pbVar2 = paVar10->flags;
  *pbVar2 = *pbVar2 | 2;
  pbVar2 = paVar10->flags;
  DAT_005065dc = param_2;
  *pbVar2 = *pbVar2 | 4;
  runtime::SaveTheGame_();
  FUN_000f3020();
  mv = (Camera *)(param_2 + 0x109);
  local_19c = mv;
  Camera::ctor(mv,"replaystorybook",(ProjectionSetBitField)0x8);
  param_2[0x115] = 0;
  Camera::ComputeTangents
            ((float)param_2[0x112],&local_18c,&local_194,&local_190,(float *)(param_2 + 0x11f),
             (float *)(param_2 + 0x120),0,local_198,&local_1a4);
  pCVar11 = Camera::AvailableConfigs;
  pCVar3 = Camera::AvailableConfigs[0].head;
  while (pCVar3 != (Camera *)0x0) {
    pCVar11 = (CameraLLNode *)((Camera *)pCVar11)->next;
    pCVar3 = ((Camera *)pCVar11)->next;
  }
  pCVar3 = ((Camera *)pCVar11)->prev;
  ((Camera *)pCVar11)->prev = mv;
  mv->next = (Camera *)pCVar11;
  param_2[0x10a] = pCVar3;
  if (pCVar3 != (Camera *)0x0) {
    pCVar3->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(char *)(param_2 + 0x116));
  }
  if ((PTR_00506c6c->field2_0x8[4] & 0x40) != 0) {
    pcVar15 = "aid_model_ghoulies_actor_dialogbat";
    pcVar16 = local_188;
    for (iVar13 = 8; iVar13 != 0; iVar13 = iVar13 + -1) {
      *(undefined4 *)pcVar16 = *(undefined4 *)pcVar15;
      pcVar15 = pcVar15 + 4;
      pcVar16 = pcVar16 + 4;
    }
    *(undefined2 *)pcVar16 = *(undefined2 *)pcVar15;
    pcVar16[2] = pcVar15[2];
    puVar17 = local_165;
    for (iVar13 = 0x17; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar17 = 0;
      puVar17 = puVar17 + 1;
    }
    *(undefined1 *)puVar17 = 0;
    pcVar15 = "aid_model_ghoulies_actor_dialogbatgold";
    pcVar16 = local_108;
    for (iVar13 = 9; iVar13 != 0; iVar13 = iVar13 + -1) {
      *(undefined4 *)pcVar16 = *(undefined4 *)pcVar15;
      pcVar15 = pcVar15 + 4;
      pcVar16 = pcVar16 + 4;
    }
    *(undefined2 *)pcVar16 = *(undefined2 *)pcVar15;
    pcVar16[2] = pcVar15[2];
    puVar17 = local_e1;
    for (iVar13 = 0x16; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar17 = 0;
      puVar17 = puVar17 + 1;
    }
    *(undefined1 *)puVar17 = 0;
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
  cutscene = Assets::LoadCutscene(local_88,6,mv);
  param_2[0x108] = cutscene;
  Cutscene::update(cutscene,g_cutsceneDelta,0.0,0);
  Camera::SetActiveCameraConfig(0,"replaystorybook");
  param_2[0x121] = Game::GameState.currentChapter;
  param_2[0x122] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0x80,(LoctextValueContext **)(param_2 + 0x107));
  pLVar4 = (LoctextValueContext *)param_2[0x107];
  (pLVar4->somePos).x = FLOAT_00429b10;
  (pLVar4->somePos).y = FLOAT_00429b14;
  pLVar4->maybeState = 3;
  XAPILIB::lstrcpyW((LPWSTR)(param_2 + 1),(LPCWSTR)param_2[0x123]);
  lp = PTR_005462c4;
  param_2[0x81] = FLOAT_00429af0;
  param_2[0x82] = FLOAT_00429af4;
  param_2[0x83] = 0;
  BVar12 = XAPILIB::IsBadReadPtr(lp,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar12 == 0) {
    createGameselectString("gameselect","replaystorybook_banner",(LPWSTR)(param_2 + 0x84),lp);
  }
  fVar9 = FLOAT_00429b34;
  fVar8 = FLOAT_00429b30;
  uVar7 = DAT_00429b2c;
  fVar6 = FLOAT_00429b28;
  fVar5 = FLOAT_00429b24;
  param_2[0x104] = FLOAT_00429ae8;
  uVar14 = (uint)DAT_00429b20;
  param_2[0x105] = FLOAT_00429aec;
  param_2[0x106] = 0;
  local_1a4.x = g_DXContext.field28_0x48 + _DAT_00429b18;
  local_1a4.y = g_DXContext.__0 + _DAT_00429b1c;
  InitMalloced100(uVar14,fVar5,fVar6,0,fVar8,fVar9,3,uVar7,1,1,&local_1a4);
  if (Audio::PauseMusicPlaying == 0) {
    Audio::PlayOrChangeByName(1,g_pauseMusicXACTID);
    Audio::PauseMusicPlaying = 1;
  }
  FUN_000e57f0(param_2,1);
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource16::func3(int param_1)

{
  destroyGlobalMalloced100();
  DAT_005065dc = 0;
  UnregisterScript__(*(int *)(param_1 + 0x41c));
  *(undefined4 *)(param_1 + 0x41c) = 0;
  if (*(Scene **)(param_1 + 0x498) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0x498));
    *(undefined4 *)(param_1 + 0x498) = 0;
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


void resource16::func4(int *param_1)

{
  Cutscene *cutscene;
  int iVar1;
  InputHandlerType3 *script3;
  float delta;
  
  cutscene = (Cutscene *)param_1[0x108];
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,(Cutscene *)param_1[0x108],(Camera *)(param_1 + 0x109));
  }
  if ((Scene *)param_1[0x126] != (Scene *)0x0) {
    switch(*param_1) {
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
      goto switchD_000e4cfa_default;
    }
    Input::UpdateMenuInput(script3,(Scene *)param_1[0x126]);
  }
switchD_000e4cfa_default:
  if (*param_1 == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar1 = *(int *)(param_1[0x125] + 0x124), iVar1 < 2 || (3 < iVar1)) ||
        (*(int *)(param_1[0x125] + 0x120) == 0)))) {
      FUN_000e57f0(param_1,2);
    }
  }
  else if (((*param_1 == 3) && (TransitionData.discReadEnum == 0)) &&
          ((iVar1 = *(int *)(param_1[0x125] + 0x124), iVar1 < 2 ||
           ((3 < iVar1 || (*(int *)(param_1[0x125] + 0x120) == 0)))))) {
    FUN_000e57f0(param_1,4);
    FUN_00143790();
    return;
  }
  FUN_00143790();
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource14::alloc(void)

{
  malloc_(0x2c);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource14::func2(undefined4 param_1,undefined4 *param_2)

{
  SceneLoadContext *ctx;
  Scene *pSVar1;
  int iVar2;
  void *pvVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  BOOL BVar6;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 uVar7;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18 [4];
  Scene *local_8;
  float local_4;
  
  puVar4 = param_2;
  ctx = (SceneLoadContext *)(param_2 + 10);
  _DAT_005065e4 = param_2;
  *param_2 = 0;
  param_2[9] = param_1;
  ctx->scene = (Scene *)0x0;
  param_2[1] = 0;
  Assets::GetResourceBytes("aid_texture_ghoulies_misc_controllerpage",&param_2);
  puVar5 = param_2;
  if (param_2 == (undefined4 *)0x0) {
    runtime::ExitGame(2);
  }
  puVar4[1] = puVar5;
  puVar4[4] = -1;
  puVar4[2] = g_DXContext.field28_0x48;
  puVar4[3] = g_DXContext.__0;
  puVar4[5] = 1.0;
  puVar4[6] = 1.0;
  puVar4[7] = Game::GameState.currentChapter;
  puVar4[8] = Game::GameState.currentScene;
  local_8 = (Scene *)(g_DXContext.field32_0x58 + 35.0);
  local_4 = g_DXContext.field35_0x64 - 16.0;
  local_18[3] = -32.0;
  uVar7 = 0;
  local_18[0] = 20.0;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  local_18[2] = 0.0;
  local_18[1] = -16.0;
  local_1c = 0;
  createGameselectLoctext
            ((GameselectLoctext *)"XSellDemoMoviesPlayingMenu",1.0,0.75,"gameselect",
             "aid_loctext_ghoulies_gameselect_gameselecttext");
  pvVar3 = PTR_005462c4;
  local_20 = uVar7;
  BVar6 = XAPILIB::IsBadReadPtr(PTR_005462c4,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar6 != 0) {
    return 0;
  }
  LoadScene_(1,(char *)0x0,(SceneLoadContext *)&local_8,local_18 + 2,local_18,&local_20,0x3f800000,
             &DAT_3f400000,"gameselect",pvVar3,0x400c0,ctx);
  pSVar1 = ctx->scene;
  pSVar1->originalTimerValue = 0.2;
  if (0.2 < pSVar1->someTimer) {
    pSVar1->someTimer = 0.2;
  }
  *(undefined4 *)(pSVar1->field3814_0x1020 + 0x20) = 0x3e4ccccd;
  iVar2 = ctx->scene->field3814_0x1020;
  *(float *)(iVar2 + 0x14) = 3.0;
  *(float *)(iVar2 + 0x18) = 0.7;
  *(undefined4 *)(iVar2 + 0x1c) = 3;
  FUN_000e7d60(1);
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource14::func3(int param_1)

{
  _DAT_005065e4 = 0;
  if (*(Scene **)(param_1 + 0x28) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0x28));
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  if (*(void **)(param_1 + 4) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
    Game::GameState.currentChapter = *(int *)(param_1 + 0x1c);
    Game::GameState.currentScene = *(int *)(param_1 + 0x20);
    return;
  }
  Game::GameState.currentChapter = *(int *)(param_1 + 0x1c);
  Game::GameState.currentScene = *(int *)(param_1 + 0x20);
  return;
}




void resource14::func4(int *param_1)

{
  Scene *scene;
  int iVar1;
  
  scene = (Scene *)param_1[10];
  if (scene != (Scene *)0x0) {
    iVar1 = *param_1;
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        Input::UpdateMenuInput(Input::MenuInputHandler,scene);
        return;
      }
      if (iVar1 != 2) {
        return;
      }
    }
    Input::UpdateMenuInput((InputHandlerType3 *)0x0,scene);
  }
  return;
}




void resource14::func5(int *param_1)

{
  if (((-1 < *param_1) && (*param_1 < 3)) && (param_1[1] != 0)) {
    DrawMalloced100Value(param_1[1],param_1 + 2,param_1 + 5,0,(TextDrawData *)param_1[4],0);
  }
  if ((param_1[10] != 0) && (Game::DialogState == NotInDialog)) {
    DrawXboxButtons_();
    return;
  }
  return;
}




void resource13::alloc(void)

{
  malloc_(0x2ac);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource13::func2(float param_1,int *param_2)

{
  int *piVar1;
  Camera *mv;
  SceneLoadContext *ctx;
  Camera *pCVar2;
  LoctextValueContext *pLVar3;
  Scene *pSVar4;
  int iVar5;
  void *pvVar6;
  int *piVar7;
  CameraLLNode *pCVar8;
  Cutscene *pCVar9;
  BOOL bad;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float fVar10;
  int local_20 [2];
  float local_18 [2];
  vec2 local_10;
  Scene *local_8;
  float local_4;
  
  piVar7 = param_2;
  param_2[0xa0] = (int)param_1;
  *param_2 = 0;
  param_2[0xa1] = 0;
  param_2[0xa2] = 0;
  param_2[0xa3] = 3;
  param_2[0xa4] = 0;
  param_2[0xa8] = -1;
  param_2[0xa6] = 0;
  param_2[0xa7] = 0;
  param_2[0xa9] = 0;
  param_2[0xaa] = 0;
  param_2[0xa5] = 0;
  param_2[0xa5] = *(int *)(param_2[0xa0] + 0x84);
  mv = (Camera *)(param_2 + 0x86);
  DAT_005065e8 = param_2;
  Camera::ctor(mv,"options",(ProjectionSetBitField)0x8);
  piVar7[0x92] = 0;
  Camera::ComputeTangents
            ((float)piVar7[0x8f],local_20,&param_1,(float *)&param_2,(float *)(piVar7 + 0x9c),
             (float *)(piVar7 + 0x9d),0,local_18,&local_10);
  pCVar8 = Camera::AvailableConfigs;
  pCVar2 = Camera::AvailableConfigs[0].head;
  while (pCVar2 != (Camera *)0x0) {
    pCVar8 = (CameraLLNode *)((Camera *)pCVar8)->next;
    pCVar2 = ((Camera *)pCVar8)->next;
  }
  pCVar2 = ((Camera *)pCVar8)->prev;
  ((Camera *)pCVar8)->prev = mv;
  mv->next = (Camera *)pCVar8;
  piVar7[0x87] = (int)pCVar2;
  if (pCVar2 != (Camera *)0x0) {
    pCVar2->next = mv;
  }
  if (Camera::ActiveConfigs[0] == (Camera *)0x0) {
    Camera::SetActiveCameraConfig(0,(char *)(piVar7 + 0x93));
  }
  pCVar9 = Assets::LoadCutscene("aid_cutscene_ghoulies_dialogs_dialogpage1",6,mv);
  piVar7[0x85] = (int)pCVar9;
  Camera::SetActiveCameraConfig(0,"options");
  piVar7[0x9e] = Game::GameState.currentChapter;
  piVar7[0x9f] = Game::GameState.currentScene;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  runtime::AllocateForLoctext_(0,1,(void *)0xc0,(LoctextValueContext **)(piVar7 + 0x84));
  pLVar3 = (LoctextValueContext *)piVar7[0x84];
  (pLVar3->somePos).x = 3.0;
  (pLVar3->somePos).y = 0.7;
  pLVar3->maybeState = 3;
  pvVar6 = PTR_005462c4;
  bad = XAPILIB::IsBadReadPtr(PTR_005462c4,CONCAT44(unaff_ESI,unaff_EDI));
  if (bad == 0) {
    createGameselectString("gameselect","xselldemomovies_titlebanner",(LPWSTR)(piVar7 + 1),pvVar6);
  }
  piVar7[0x81] = 0x43a00000;
  piVar7[0x82] = 0x42700000;
  piVar7[0x83] = 0;
  local_10.x = g_DXContext.field28_0x48;
  local_10.y = g_DXContext.__0 - 20.0;
  InitMalloced100(2,30.0,0.9,0,2.0,0.5,3,0,0,0,&local_10);
  FUN_000e86c0();
  local_8 = (Scene *)(g_DXContext.field32_0x58 + 75.0);
  local_4 = g_DXContext.field35_0x64 - 16.0;
  local_20[1] = 0xc2000000;
  fVar10 = 0.0;
  local_18[0] = 20.0;
  local_20[0] = 0;
  local_18[1] = -16.0;
  local_10.y = 0.0;
  createGameselectLoctext
            ((GameselectLoctext *)"XSellDemoMoviesMainMenu",1.0,0.75,"gameselect",
             "aid_loctext_ghoulies_gameselect_gameselecttext");
  pvVar6 = PTR_005462c4;
  local_10.x = fVar10;
  bad = XAPILIB::IsBadReadPtr(PTR_005462c4,CONCAT44(unaff_ESI,unaff_EDI));
  if (bad != 0) {
    return 0;
  }
  ctx = (SceneLoadContext *)(piVar7 + 0xa1);
  LoadScene_(1,(char *)0x0,(SceneLoadContext *)&local_8,local_20,local_18,&local_10,0x3f800000,
             &DAT_3f400000,"gameselect",pvVar6,0x400c0,ctx);
  pSVar4 = ctx->scene;
  pSVar4->originalTimerValue = 0.2;
  if (0.2 < pSVar4->someTimer) {
    pSVar4->someTimer = 0.2;
  }
  *(undefined4 *)(pSVar4->field3814_0x1020 + 0x20) = 0x3e4ccccd;
  iVar5 = ctx->scene->field3814_0x1020;
  *(float *)(iVar5 + 0x14) = 3.0;
  *(float *)(iVar5 + 0x18) = 0.7;
  *(undefined4 *)(iVar5 + 0x1c) = 3;
  if (*piVar7 == 2) {
    FUN_00143b80();
    FUN_0005f970(piVar7[0x84]);
  }
  else if (*piVar7 == 3) {
    if (piVar7[0xa2] != 0) {
      if (piVar7[0xa4] != 0) {
        piVar1 = (int *)(piVar7[0xa2] + 0x18);
        *piVar1 = *piVar1 + -1;
        piVar7[0xa4] = 0;
      }
      FUN_001072b0();
      piVar7[0xa2] = 0;
    }
    if (Audio::PauseMusicPlaying == 0) {
      Audio::PlayOrChangeByName(1,g_pauseMusicXACTID);
      Audio::PauseMusicPlaying = 1;
      *piVar7 = 1;
      return 1;
    }
  }
  *piVar7 = 1;
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource13::func3(int param_1)

{
  destroyGlobalMalloced100();
  DAT_005065e8 = 0;
  UnregisterScript__(*(int *)(param_1 + 0x210));
  *(undefined4 *)(param_1 + 0x210) = 0;
  if (*(Scene **)(param_1 + 0x284) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0x284));
    *(undefined4 *)(param_1 + 0x284) = 0;
  }
  Cutscene::dtor(*(Cutscene **)(param_1 + 0x214));
  *(undefined4 *)(param_1 + 0x214) = 0;
  Camera::setActiveCamera(param_1 + 0x218);
  Game::GameState.currentChapter = *(int *)(param_1 + 0x278);
  Game::GameState.currentScene = *(int *)(param_1 + 0x27c);
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource13::func4(int *param_1)

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
  
  cutscene = (Cutscene *)param_1[0x85];
  if (cutscene != (Cutscene *)0x0) {
    if (cutscene->length <= cutscene->t) {
      Cutscene::update(cutscene,0.0,0.0,0);
    }
    delta = 0.0;
    if (runtime::dx_timer <= 0.0) {
      delta = runtime::DeltaTime * runtime::TimeScale;
    }
    RuncutsceneAndShouldEnd(delta,(Cutscene *)param_1[0x85],(Camera *)(param_1 + 0x86));
  }
  if ((Scene *)param_1[0xa1] == (Scene *)0x0) goto switchD_000e82ea_default;
  switch(*param_1) {
  case 0:
  case 1:
  case 4:
  case 5:
    script3 = (InputHandlerType3 *)0x0;
    goto LAB_000e8303;
  case 2:
    if (Game::DialogState == NotInDialog) goto switchD_000e82ea_caseD_3;
    break;
  case 3:
switchD_000e82ea_caseD_3:
    script3 = Input::MenuInputHandler;
LAB_000e8303:
    Input::UpdateMenuInput(script3,(Scene *)param_1[0xa1]);
  }
switchD_000e82ea_default:
  if (*param_1 == 1) {
    if ((TransitionData.discReadEnum == 0) &&
       (((iVar6 = *(int *)(param_1[0xa0] + 0x124), iVar6 < 2 || (3 < iVar6)) ||
        (*(int *)(param_1[0xa0] + 0x120) == 0)))) {
      FUN_000e87f0(param_1,2);
    }
  }
  else if (((*param_1 == 4) && (TransitionData.discReadEnum == 0)) &&
          ((iVar6 = *(int *)(param_1[0xa0] + 0x124), iVar6 < 2 ||
           ((3 < iVar6 || (*(int *)(param_1[0xa0] + 0x120) == 0)))))) {
    *param_1 = 5;
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


void resource15::alloc(void)

{
  malloc_(0x23c);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 resource15::func2(undefined4 param_1,char *param_2)

{
  SceneLoadContext *ctx;
  Scene *pSVar1;
  int iVar2;
  LoctextValueContext *pLVar3;
  char *pcVar4;
  void *pvVar5;
  char *pcVar6;
  BOOL BVar7;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float local_18 [4];
  Scene *local_8;
  float local_4;
  
  pcVar4 = param_2;
  ctx = (SceneLoadContext *)(param_2 + 0x238);
  _DAT_005065ec = param_2;
  pcVar4[0] = '\0';
  pcVar4[1] = '\0';
  pcVar4[2] = '\0';
  pcVar4[3] = '\0';
  *(undefined4 *)(param_2 + 0x234) = param_1;
  ctx->scene = (Scene *)0x0;
  pcVar4[0x214] = '\0';
  pcVar4[0x215] = '\0';
  pcVar4[0x216] = '\0';
  pcVar4[0x217] = '\0';
  Assets::GetResourceBytes("aid_texture_ghoulies_gameselect_zombieclapframe",&param_2);
  pcVar6 = param_2;
  if (param_2 == (char *)0x0) {
    runtime::ExitGame(2);
  }
  *(char **)(pcVar4 + 0x214) = pcVar6;
  *(int32_t *)(pcVar4 + 0x220) = -1;
  *(float *)(pcVar4 + 0x218) = g_DXContext.field28_0x48;
  *(float *)(pcVar4 + 0x21c) = g_DXContext.__0;
  *(float *)(pcVar4 + 0x224) = 1.0;
  *(float *)(pcVar4 + 0x228) = 1.0;
  *(int *)(pcVar4 + 0x22c) = Game::GameState.currentChapter;
  pvVar5 = PTR_005462c4;
  *(int *)(pcVar4 + 0x230) = Game::GameState.currentScene;
  local_8 = (Scene *)(g_DXContext.field32_0x58 + 35.0);
  local_4 = g_DXContext.field35_0x64 - 16.0;
  local_18[2] = 0.0;
  local_18[3] = -32.0;
  local_18[0] = 20.0;
  Game::GameState.currentChapter = 1;
  Game::GameState.currentScene = 1;
  local_18[1] = -16.0;
  BVar7 = XAPILIB::IsBadReadPtr(pvVar5,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar7 != 0) {
    return 0;
  }
  LoadScene_(0,(char *)0x0,(SceneLoadContext *)&local_8,local_18 + 2,local_18,0,0x3f800000,
             &DAT_3f400000,"gameselect",pvVar5,0x400c0,ctx);
  pSVar1 = ctx->scene;
  pSVar1->originalTimerValue = 0.2;
  if (0.2 < pSVar1->someTimer) {
    pSVar1->someTimer = 0.2;
  }
  *(undefined4 *)(pSVar1->field3814_0x1020 + 0x20) = 0x3e4ccccd;
  iVar2 = ctx->scene->field3814_0x1020;
  *(float *)(iVar2 + 0x14) = 3.0;
  *(float *)(iVar2 + 0x18) = 0.7;
  *(undefined4 *)(iVar2 + 0x1c) = 3;
  runtime::AllocateForLoctext_(0,1,(void *)0x80,(LoctextValueContext **)(pcVar4 + 0x210));
  pLVar3 = *(LoctextValueContext **)(pcVar4 + 0x210);
  (pLVar3->somePos).x = 3.0;
  pLVar3->maybeState = 3;
  (pLVar3->somePos).y = 0.7;
  pvVar5 = PTR_005462c4;
  pcVar4[0x20c] = '\0';
  pcVar4[0x20d] = '\0';
  pcVar4[0x20e] = '\0';
  pcVar4[0x20f] = '\0';
  pcVar4[0x204] = '\0';
  pcVar4[0x205] = '\0';
  pcVar4[0x206] = '\0';
  pcVar4[0x207] = '\0';
  pcVar4[0x208] = '\0';
  pcVar4[0x209] = '\0';
  pcVar4[0x20a] = '\0';
  pcVar4[0x20b] = '\0';
  *(WCHAR *)(pcVar4 + 4) = L'\0';
  BVar7 = XAPILIB::IsBadReadPtr(pvVar5,CONCAT44(unaff_ESI,unaff_EDI));
  if (BVar7 == 0) {
    createGameselectString("gameselect","xselldemoquit_prompt",(LPWSTR)(pcVar4 + 4),pvVar5);
  }
  *(float *)(pcVar4 + 0x204) = g_DXContext.field28_0x48;
  *(float *)(pcVar4 + 0x208) = g_DXContext.__0;
  pcVar4[0x20c] = '\0';
  pcVar4[0x20d] = '\0';
  pcVar4[0x20e] = '\0';
  pcVar4[0x20f] = '\0';
  FUN_000e8e50();
  return 1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void resource15::func3(int param_1)

{
  _DAT_005065ec = 0;
  UnregisterScript__(*(int *)(param_1 + 0x210));
  *(undefined4 *)(param_1 + 0x210) = 0;
  if (*(Scene **)(param_1 + 0x238) != (Scene *)0x0) {
    Scene::free(*(Scene **)(param_1 + 0x238));
    *(undefined4 *)(param_1 + 0x238) = 0;
  }
  if (*(void **)(param_1 + 0x214) != (void *)0x0) {
    Assets::DestroyAssetOrDecrement(*(void **)(param_1 + 0x214));
    *(undefined4 *)(param_1 + 0x214) = 0;
    Game::GameState.currentChapter = *(int *)(param_1 + 0x22c);
    Game::GameState.currentScene = *(int *)(param_1 + 0x230);
    return;
  }
  Game::GameState.currentChapter = *(int *)(param_1 + 0x22c);
  Game::GameState.currentScene = *(int *)(param_1 + 0x230);
  return;
}




void resource15::func4(int *param_1)

{
  Scene *scene;
  int iVar1;
  
  scene = (Scene *)param_1[0x8e];
  if (scene != (Scene *)0x0) {
    iVar1 = *param_1;
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        Input::UpdateMenuInput(Input::MenuInputHandler,scene);
        return;
      }
      if (iVar1 != 2) {
        return;
      }
    }
    Input::UpdateMenuInput((InputHandlerType3 *)0x0,scene);
  }
  return;
}




void resource15::func5(int *param_1)

{
  if (((-1 < *param_1) && (*param_1 < 3)) && (param_1[0x85] != 0)) {
    DrawMalloced100Value
              (param_1[0x85],param_1 + 0x86,param_1 + 0x89,0,(TextDrawData *)param_1[0x88],0);
  }
  if (param_1[0x8e] != 0) {
    DrawXboxButtons_();
    return;
  }
  return;
}




Assets::CreateFxParticleImpactFlash(char *assetName,uint count,vec3 *soundPos_,vec3 *updatedAngles_)

{
  vec3 *pvVar1;
  fxParticleImpactFlash *puVar2;
  int iVar2;
  uint size;
  char *paVar3;
  
  pvVar1 = soundPos_;
  size = (count & 0xffff) * 0x150 + 0x4e0;
  puVar2 = malloc_(size);
  paVar3 = (char *)puVar2;
                    // memset(0)
  for (size = size >> 2; size != 0; size = size - 1) {
    ((fxParticleImpactFlash *)paVar3)->field0_0x0 = 0;
    ((fxParticleImpactFlash *)paVar3)->field_0x1 = 0;
    ((fxParticleImpactFlash *)paVar3)->field2_0x2 = 0;
    paVar3 = &((fxParticleImpactFlash *)paVar3)->field_0x4;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *paVar3 = '\0';
    paVar3 = paVar3 + 1;
  }
                    // end memset
  puVar2->field7_0x8 = -3.0;
  puVar2->field2_0x2 = (ushort)count;
  puVar2->field12_0x10 = -1.0;
  puVar2->field124_0xb8 = 1.0;
  puVar2->field117_0x98 = 1.0;
  puVar2->maybeOtherFlags_ = 0;
  puVar2->field125_0xbc = -1.0;
  FUN_000ed170();
  (puVar2->soundPos_).x = pvVar1->x;
  (puVar2->soundPos_).y = pvVar1->y;
  (puVar2->soundPos_).z = pvVar1->z;
  (puVar2->updatedAngles).x = updatedAngles_->x;
  (puVar2->updatedAngles).y = updatedAngles_->y;
  (puVar2->updatedAngles).z = updatedAngles_->z;
  puVar2->fxCustomType = 0;
  puVar2->field184_0x13c = 3;
  if (puVar2->fxParticlesImpactFlash != (void *)0x0) {
    DestroyAssetOrDecrement(puVar2->fxParticlesImpactFlash);
  }
  if ((assetName != (char *)0x0) && (*(int *)assetName == 0x5f646961)) {
    GetResourceBytes(assetName,(void **)&count);
    size = count;
    if (count == 0) {
      runtime::ExitGame(2);
    }
    puVar2->fxParticlesImpactFlash = (void *)size;
  }
  puVar2->field599_0x2e4 = 0xffff;
  puVar2->field736_0x36e = 1;
  return puVar2;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


undefined4 Assets::LoadAndExecuteScript(fxParticleImpactFlash *target,uint *param_2,char *param_3)

{
  undefined4 uVar1;
  void *pAVar2;
  void *script;
  
  if (*(int *)param_3 == 0x5f646961) {
    GetResourceBytes(param_3,&script);
    pAVar2 = script;
    if (script == (void *)0x0) {
      runtime::ExitGame(2);
    }
  }
  else {
    pAVar2 = (void *)0x0;
  }
  script = pAVar2;
  uVar1 = ExecuteScript(target,&script,param_2);
  DestroyAssetOrDecrement(pAVar2);
  return uVar1;
}




MarkerInstance * Assets::GetMarkerFromAID(char *markerName)

{
  MarkerInstance *pMVar1;
  uint uVar2;
  uint *size;
  char *marker_bytes;
  short ptr;
  
  uVar2 = 8;
  pMVar1 = malloc_(8);
  pMVar1->numMarkers = 0;
  if (*(int *)markerName == 0x5f646961) {
    GetResourceBytes(markerName,&marker_bytes);
    if (marker_bytes == (char *)0x0) {
      runtime::ExitGame(2);
      pMVar1->end = 8;
      return pMVar1;
    }
    ptr = *(short *)(marker_bytes + 4);
    size = (uint *)marker_bytes;
    while (ptr != 0) {
      pMVar1 = (MarkerInstance *)AllocateMoreAStruct_33(*size + uVar2,pMVar1);
      memcpy((void *)((int)pMVar1->marker + (uVar2 - 8)),size,*size);
      uVar2 = uVar2 + *size;
      pMVar1->numMarkers = pMVar1->numMarkers + 1;
      size = (uint *)((int)size + *size);
      ptr = (short)size[1];
    }
    DestroyAssetOrDecrement(marker_bytes);
  }
  pMVar1->end = uVar2;
  return pMVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


obj * Assets::CreateEntityFromParams(objParams *params)

{
  ObjectFullVTable *vtable;
  Object *entity;
  BOOL success;
  uint i;
  undefined4 unaff_EBX;
  Object *temp_ptr;
  ObjectAllocDetails alloc_details;
  ushort type;
  
  type = params->typeIndex;
                    // Can call 0x00109db4
                    // Can call 0xcef70
  vtable = (ObjectFullVTable *)(*(code *)(&VTableTable)[(uint)type * 3])();
  alloc_details.paramsSize = 0;
  alloc_details.entitySize = 0;
  (*vtable->getAllocDetails)(&alloc_details);
  entity = malloc_(alloc_details.entitySize);
  if (entity != (Object *)0x0) {
    temp_ptr = entity;
    for (i = alloc_details.entitySize >> 2; i != 0; i = i - 1) {
      temp_ptr->vtable = (ObjectFullVTable *)0x0;
      temp_ptr = (Object *)&temp_ptr->typeIndex;
    }
    for (i = alloc_details.entitySize & 3; i != 0; i = i - 1) {
      *(undefined1 *)&temp_ptr->vtable = 0;
      temp_ptr = (Object *)((int)&temp_ptr->vtable + 1);
    }
    entity->vtable = vtable;
    entity->typeIndex = type;
    success = BuildNewEntity((obj *)entity,CONCAT22((short)((uint)unaff_EBX >> 0x10),type),params);
    if (success != 0) {
      Entity::Count = Entity::Count + 1;
      return (obj *)entity;
    }
    free(entity);
  }
  return (obj *)0x0;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Assets::DeleteResource_(void *param_1)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  obj::destroy(param_1,*(ushort *)((int)param_1 + 4),0);
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
  Entity::Count = Entity::Count + -1;
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


BOOL Assets::BuildNewEntity(obj *res,uint type,void *params)

{
  BOOL parent_success;
  ObjectFullVTable *parent_vtable;
  ObjectFullVTable *our_vtable;
  int constructed_successfully;
  code *parent_ctor;
  code *our_ctor;
  ushort parent_id;
  
  parent_id = *(ushort *)(&PreConstructorTable + (type & 0xffff) * 0xc);
  if (parent_id == 0) {
    parent_ctor = (code *)0x0;
  }
  else {
                    // Build the parent resource first
    parent_success = BuildNewEntity(res,(uint)parent_id,params);
    if (parent_success == 0) {
      return 0;
    }
                    // Doesn't actually run anything, just gets the parent's ctor
    parent_vtable = (ObjectFullVTable *)(*(code *)(&VTableTable)[(uint)parent_id * 3])();
    parent_ctor = parent_vtable->ctor;
  }
                    // Goes to 0x1074f0, presumably loads the vtable
  our_vtable = (ObjectFullVTable *)(*(code *)(&VTableTable)[(type & 0xffff) * 3])();
  our_ctor = our_vtable->ctor;
                    // Calls
                    // 0x0003e940
                    // 0x000878d0 (options menu)
                    // 
                    // CALLS THIS TO CREATE GRIM REAPER
                    // 0x000ad400
                    // Goes to
                    // 0x00024c50
                    // 0x0002b600
                    // 0x000cffd0
                    // 0x000a2590
                    // If we have a constructor, and our parent has a different constructor, run our
                    // constructor. If there's an error running our constructor, clean up the
                    // resource and return 0.
                    // 
  if (((our_ctor != (code *)0x0) && (parent_ctor != our_ctor)) &&
     (constructed_successfully = (*our_ctor)(res,params), constructed_successfully == 0)) {
                    // Runs 0x00107700 after going to the table above
    obj::destroy((Object *)res,(ushort)type,0);
    return 0;
  }
  return 1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


objParams * Assets::GetObjParams(char *assetName)

{
  ushort *str;
  AssetHeader *header;
  objParams *inners_copy;
  
  if ((assetName != (char *)0x0) && (*(int *)assetName == 0x5f646961)) {
    header = FindAssetHeader(assetName,1);
    if ((header != (AssetHeader *)0x0) && (str = header->dataPtr, str != (ushort *)0x0)) {
      inners_copy = malloc_((uint)*str);
      if (inners_copy != (objParams *)0x0) {
        memcpy(inners_copy,str,(uint)*str);
      }
      return inners_copy;
    }
  }
  return (objParams *)0x0;
}




background * Assets::CreateBackgroundFromAID(char *param_1)

{
  int i;
  background *bg;
  BackgroundParams params;
  char c;
  
  avatarParams::init(&params.avatarParams);
  params.avatarParams.objParams.typeIndex = 4;
  params.avatarParams.objParams.paramsSize = 0x334;
  params.avatarParams.objParams.objInitValue = 0x46;
  i = 0;
  do {
    c = g_GlobalAssetName[i];
    params.avatarParams.standAnimationAID[i] = c;
    i = i + 1;
  } while (c != '\0');
  params.avatarParams.scale = 1.0;
  i = 0x28 - (int)param_1;
  do {
    c = *param_1;
    param_1[(int)&params + i] = c;
    param_1 = param_1 + 1;
  } while (c != '\0');
                    // Create callout
  i = 0;
  do {
    c = "aid_callout_ghoulies_background"[i];
    params.avatarParams.calloutAID[i] = c;
    i = i + 1;
  } while (c != '\0');
  bg = (background *)CreateEntityFromParams((objParams *)&params);
  return bg;
}




void Assets::LoadNewMarker(char *param_1,char *param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  char *in_stack_ffffff80;
  
  iVar3 = 5;
  cVar2 = param_1[5];
  while (cVar2 != '_') {
    iVar1 = iVar3 + 1;
    iVar3 = iVar3 + 1;
    cVar2 = param_1[iVar1];
  }
  Utils::SprintfToUpper
            (&stack0xffffff80,"aid_%s_%s","marker",param_1 + iVar3 + 1,param_2,in_stack_ffffff80);
  Game::GameState.markerInstance = GetMarkerFromAID(&stack0xffffff80);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


long Assets::PlaycamAIDFromAID(char *param_1)

{
  char cVar1;
  uint chapter_index;
  char *pcVar2;
  char *pcVar3;
  long lVar4;
  char *pcVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  char local_40 [64];
  
  chapter_index = GetChapterIndexFromAID(param_1);
  if (chapter_index == 0) {
    return 0;
  }
  pcVar5 = "aid_script_ghoulies_chapter";
  pcVar3 = g_chapterStrings[chapter_index];
  do {
    cVar1 = *pcVar5;
    (&stack0xffcdd294)[(int)pcVar5] = cVar1;
    pcVar5 = pcVar5 + 1;
    pcVar2 = pcVar3;
  } while (cVar1 != '\0');
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  chapter_index = (int)pcVar2 - (int)pcVar3;
  pcVar5 = &stack0xffffffbf;
  do {
    pcVar2 = pcVar5 + 1;
    pcVar5 = pcVar5 + 1;
  } while (*pcVar2 != '\0');
  for (uVar6 = chapter_index >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (chapter_index = chapter_index & 3; pcVar2 = PTR_s__scene_00430d00, chapter_index != 0;
      chapter_index = chapter_index - 1) {
    *pcVar5 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    pcVar5 = pcVar5 + 1;
  }
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  chapter_index = (int)pcVar2 - (int)PTR_s__scene_00430d00;
  puVar8 = (undefined4 *)&stack0xffffffbf;
  do {
    pcVar3 = (char *)((int)puVar8 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  } while (*pcVar3 != '\0');
  puVar7 = (undefined4 *)PTR_s__scene_00430d00;
  for (uVar6 = chapter_index >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  pcVar3 = local_40;
  for (chapter_index = chapter_index & 3; chapter_index != 0; chapter_index = chapter_index - 1) {
    *(undefined1 *)puVar8 = *(undefined1 *)puVar7;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
    puVar8 = (undefined4 *)((int)puVar8 + 1);
  }
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  lVar4 = _atol(param_1 + ((int)pcVar3 - (int)(local_40 + 1)));
  return lVar4;
}




BOOL Assets::AIDIsRegularScript(char *param_1)

{
  BOOL success;
  uint uVar1;
  char *name1;
  
  name1 = AttractSequences[0];
                    // runs 6 times
  uVar1 = 0;
  do {
    success = AssetNamesMatch(name1,param_1);
    if (success != 0) {
      return 0;
    }
    uVar1 = uVar1 + 0x80;
    name1 = name1 + 0x80;
  } while (uVar1 < 0x300);
  return 1;
}




bool Assets::GetStatsheetTag(char *param_1)

{
  char c1;
  int iVar1;
  char c2;
  char *ptr;
  
  iVar1 = (int)"objTag_Null" - (int)param_1;
  while( true ) {
    c1 = *param_1;
    c2 = 'o';
    if (c1 == 'o') {
      c1 = 'o';
      ptr = param_1;
      do {
        ptr = ptr + 1;
        if (c1 == '\0') {
          return true;
        }
        c1 = *ptr;
        c2 = ptr[iVar1];
      } while (c1 == c2);
    }
    if (c1 == c2) break;
    param_1 = param_1 + 0x87;
    iVar1 = iVar1 + -0x87;
  }
  return true;
}




uint Assets::ValidateStatsheet(StatsheetEntry *param_1)

{
  char cVar1;
  int iVar2;
  char cVar3;
  StatsheetEntry *pSVar4;
  int tag_index;
  
  tag_index = 0;
  iVar2 = (int)"objTag_Null" - (int)param_1;
  while( true ) {
    cVar1 = param_1->tagName[0];
    cVar3 = 'o';
    if (cVar1 == 'o') {
      cVar1 = 'o';
      pSVar4 = param_1;
      do {
        pSVar4 = (StatsheetEntry *)(pSVar4->tagName + 1);
        if (cVar1 == '\0') goto LAB_00133bbb;
        cVar1 = pSVar4->tagName[0];
        cVar3 = pSVar4->tagName[iVar2];
      } while (cVar1 == cVar3);
    }
    if (cVar1 == cVar3) break;
    tag_index = tag_index + 1;
    param_1 = param_1 + 1;
    iVar2 = iVar2 + -0x87;
  }
LAB_00133bbb:
                    // Ensure all tags are in the statsheet
  return tag_index + 1;
}




int __fastcall createResourceFromName(char *param_1)

{
  int iVar2;
  ResourceLoaderStub *stub;
  void *resource;
  int extraout_EDX;
  int extraout_EDX_00;
  char c;
  int iVar1;
  
  iVar2 = 0;
  c = param_1[4];
                    // Get the asset type
  while (c != '_') {
    Assets::LoadingAssetType[iVar2] = c;
    iVar1 = iVar2 + 5;
    iVar2 = iVar2 + 1;
    c = param_1[iVar1];
  }
  Assets::LoadingAssetType[iVar2] = '\0';
  stub = GetResourceLoaderStub(Assets::LoadingAssetType);
  if ((stub != (ResourceLoaderStub *)0x0) && (stub->ctor != (AfterLoadFn *)0x0)) {
    (*stub->ctor)(resource);
    return extraout_EDX_00;
  }
  return extraout_EDX;
}




void __fastcall TriggerAssetTypeCallback3(undefined4 param_1,int param_2)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  ResourceLoaderStub *pRVar4;
  
  iVar3 = 0;
  cVar2 = *(char *)(param_2 + 4);
  while (cVar2 != '_') {
    Assets::LoadingAssetType[iVar3] = cVar2;
    pcVar1 = (char *)(param_2 + 5 + iVar3);
    iVar3 = iVar3 + 1;
    cVar2 = *pcVar1;
  }
  Assets::LoadingAssetType[iVar3] = '\0';
  pRVar4 = GetResourceLoaderStub(Assets::LoadingAssetType);
  if ((pRVar4 != (ResourceLoaderStub *)0x0) && (pRVar4->dtor != (code *)0x0)) {
                    // WARNING: Could not recover jumptable at 0x0013a9be. Too many branches
                    // WARNING: Treating indirect jump as call
    (*pRVar4->dtor)();
    return;
  }
  return;
}




BOOL Assets::OpenBoxFromAid(undefined4 param_1,char *ghoulyBoxAID,uint boxId,char *actorAttribsAID)

{
  char cVar1;
  weapon *pwVar2;
  undefined4 uVar3;
  int iVar4;
  char *pcVar5;
  Ghouly_OpenBoxFromAidMessage msg;
  avatar *setup_basic;
  
  pcVar5 = msg.ghoulyBoxAID;
  for (iVar4 = 0x41; iVar4 != 0; iVar4 = iVar4 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
  }
  msg.msgId = Ghouly_OpenBoxFromAid;
  pwVar2 = g_weapons->head;
  if (pwVar2 < g_weapons->tail) {
                    // Instantly failed first object checked
    while ((pwVar2->avatar).vtable != (AvatarVTable *)boxId) {
      pwVar2 = (weapon *)&(pwVar2->avatar).pos;
      if (g_weapons->tail <= pwVar2) {
                    // Return error
        return msg.success;
      }
    }
    setup_basic = *(avatar **)&(pwVar2->avatar).field_0x4;
    if (setup_basic != (avatar *)0x0) {
      iVar4 = 4 - (int)ghoulyBoxAID;
      do {
        cVar1 = *ghoulyBoxAID;
        ghoulyBoxAID[(int)&msg + iVar4] = cVar1;
        ghoulyBoxAID = ghoulyBoxAID + 1;
      } while (cVar1 != '\0');
      if (actorAttribsAID != (char *)0x0) {
        iVar4 = 0x84 - (int)actorAttribsAID;
        do {
          cVar1 = *actorAttribsAID;
          actorAttribsAID[(int)&msg + iVar4] = cVar1;
          actorAttribsAID = actorAttribsAID + 1;
        } while (cVar1 != '\0');
      }
                    // entityAvatarGhoulySetupBasic::onMessage
      (*setup_basic->vtable->onMessage)(setup_basic,&msg);
    }
  }
  msg._268_4_ = 0x13e979;
  uVar3 = EventLoop::SpawnGrimReaper();
  return uVar3;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void Assets::LoadGhoulieBinaryEntries(void)

{
  GhoulieBinaryEntry *pGVar1;
  
  List::Init((uint *)&ModelInstance::BinaryEntry);
  pGVar1 = g_ghoulieBinaryEntries;
  do {
    List::Init((uint *)pGVar1);
    pGVar1 = pGVar1 + 1;
  } while ((int)pGVar1 < 0x444120);
  g_ghoulieMetadataCount = 0;
  Graphics::SomeFlag1 = true;
  Game::GraphicsFlags = 0;
  ReadBinaryEntries();
  return;
}




void Assets::InitialiseGhoulieBinaryLookups(uint id,GhoulieBinValue1 *ptr1,GhoulieBinValue1 *ptr2)

{
  int offset;
  uint uVar1;
  
  uVar1 = g_ghoulieMetadataCount;
  if (ptr1 != (GhoulieBinValue1 *)0x0) {
    offset = g_ghoulieMetadataCount * 0x10;
    g_ghoulieMetadata[g_ghoulieMetadataCount].ptr1 = ptr1;
    g_ghoulieMetadata[uVar1].id = id | 0x80000000;
    FUN_00159a00(g_ghoulieBinaryEntries + (id | 0x80000000) % 0b11101111,&DAT_00444120 + offset);
    g_ghoulieMetadataCount = g_ghoulieMetadataCount + 1;
  }
  uVar1 = g_ghoulieMetadataCount;
  if (ptr2 != (GhoulieBinValue1 *)0x0) {
    offset = g_ghoulieMetadataCount * 0x10;
    g_ghoulieMetadata[g_ghoulieMetadataCount].ptr1 = ptr2;
    g_ghoulieMetadata[uVar1].id = id;
    FUN_00159a00(g_ghoulieBinaryEntries + id % 0b11101111,&DAT_00444120 + offset);
    g_ghoulieMetadataCount = g_ghoulieMetadataCount + 1;
  }
  return;
}




void Assets::ReadBinaryEntries(void)

{
  InitialiseGhoulieBinaryLookups(0,&GhoulieBinValue1_0032e6c8,(GhoulieBinValue1 *)&DAT_0032e6ec);
  InitialiseGhoulieBinaryLookups
            (0b00000001,&GhoulieBinValue1_0032e700,(GhoulieBinValue1 *)&LAB_0032e768);
  InitialiseGhoulieBinaryLookups
            (0b00100001,&GhoulieBinValue1_0032e7b0,(GhoulieBinValue1 *)&LAB_0032e898);
  InitialiseGhoulieBinaryLookups
            (0b00110001,(GhoulieBinValue1 *)&LAB_0032e960,(GhoulieBinValue1 *)&LAB_0032ea88);
  InitialiseGhoulieBinaryLookups
            (0b10100001,(GhoulieBinValue1 *)&LAB_0032eb90,(GhoulieBinValue1 *)&LAB_0032eca8);
  InitialiseGhoulieBinaryLookups
            (0b10110001,(GhoulieBinValue1 *)&LAB_0032eda0,(GhoulieBinValue1 *)&LAB_0032eef8);
  InitialiseGhoulieBinaryLookups
            (0b0000001000100001,(GhoulieBinValue1 *)&LAB_0032f030,(GhoulieBinValue1 *)&LAB_0032f198)
  ;
  InitialiseGhoulieBinaryLookups
            (0b0000001100110001,(GhoulieBinValue1 *)&LAB_0032f2e0,(GhoulieBinValue1 *)&LAB_0032f4c8)
  ;
  InitialiseGhoulieBinaryLookups
            (0b0000101010100001,(GhoulieBinValue1 *)&LAB_0032f690,(GhoulieBinValue1 *)&LAB_0032f858)
  ;
  InitialiseGhoulieBinaryLookups
            (0b0000101110110001,(GhoulieBinValue1 *)&LAB_0032fa00,(GhoulieBinValue1 *)&LAB_0032fc48)
  ;
  InitialiseGhoulieBinaryLookups(0x321,&GhoulieBinValue1_0032fe70,&GhoulieBinValue1_00330018);
  InitialiseGhoulieBinaryLookups(0xba1,&GhoulieBinValue1_003301a0,&GhoulieBinValue1_003303a8);
  InitialiseGhoulieBinaryLookups(2,&GhoulieBinValue1_00330590,&GhoulieBinValue1_00330638);
  InitialiseGhoulieBinaryLookups(3,&GhoulieBinValue1_003306c0,&GhoulieBinValue1_003307a8);
  InitialiseGhoulieBinaryLookups(10,&GhoulieBinValue1_00330870,&GhoulieBinValue1_00330948);
  InitialiseGhoulieBinaryLookups(0xb,&GhoulieBinValue1_00330a00,&GhoulieBinValue1_00330b18);
  InitialiseGhoulieBinaryLookups(0x22,&GhoulieBinValue1_00330c10,&GhoulieBinValue1_00330d38);
  InitialiseGhoulieBinaryLookups(0x33,&GhoulieBinValue1_00330e40,&GhoulieBinValue1_00330fe8);
  InitialiseGhoulieBinaryLookups(0xaa,&GhoulieBinValue1_00331170,&GhoulieBinValue1_003312f8);
  InitialiseGhoulieBinaryLookups(0xbb,&GhoulieBinValue1_00331460,&GhoulieBinValue1_00331668);
  InitialiseGhoulieBinaryLookups(0x32,&GhoulieBinValue1_00331850,&GhoulieBinValue1_003319b8);
  InitialiseGhoulieBinaryLookups(0xba,&GhoulieBinValue1_00331b00,&GhoulieBinValue1_00331cc8);
  InitialiseGhoulieBinaryLookups(0xe,&GhoulieBinValue1_00331e70,&GhoulieBinValue1_00331f78);
  InitialiseGhoulieBinaryLookups(0xee,&GhoulieBinValue1_00332060,&GhoulieBinValue1_00332248);
  InitialiseGhoulieBinaryLookups(0xeee,&GhoulieBinValue1_00332410,&GhoulieBinValue1_003326d8);
  InitialiseGhoulieBinaryLookups(0xf,(GhoulieBinValue1 *)&DAT_00332980,&GhoulieBinValue1_00332ac8);
  InitialiseGhoulieBinaryLookups(0xff,&GhoulieBinValue1_00332bf0,&GhoulieBinValue1_00332e58);
  InitialiseGhoulieBinaryLookups(0xfff,&GhoulieBinValue1_003330a0,&GhoulieBinValue1_00333428);
  InitialiseGhoulieBinaryLookups(0xe1,&GhoulieBinValue1_00333790,&GhoulieBinValue1_003338d8);
  InitialiseGhoulieBinaryLookups(0xee1,&GhoulieBinValue1_00333a00,&GhoulieBinValue1_00333c28);
  InitialiseGhoulieBinaryLookups(0xeee1,&GhoulieBinValue1_00333e30,&GhoulieBinValue1_00334138);
  InitialiseGhoulieBinaryLookups(0xf1,&GhoulieBinValue1_00334420,&GhoulieBinValue1_003345a8);
  InitialiseGhoulieBinaryLookups(0xff1,&GhoulieBinValue1_00334710,&GhoulieBinValue1_003349b8);
  InitialiseGhoulieBinaryLookups(0xfff1,&GhoulieBinValue1_00334c40,&GhoulieBinValue1_00335008);
  InitialiseGhoulieBinaryLookups(0x11,&GhoulieBinValue1_003353b0,&GhoulieBinValue1_00335458);
  InitialiseGhoulieBinaryLookups(0x111,&GhoulieBinValue1_003354e0,&GhoulieBinValue1_003355c8);
  return;
}




