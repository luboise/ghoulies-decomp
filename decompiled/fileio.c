/* fileio.c - File/IO: FileContext, BND/bundle streaming, zlib, Bink movie */
#include "fileio.h"

void __fastcall runtime::loadObjparamsFromBundle(char *name)

{
  int iVar1;
  DWORD err;
  asset_name bnl_name;
  char bnl_filename [260];
  
  iVar1 = Assets::aidToBNLName(bnl_name,name);
  if (iVar1 == 0) {
    __snprintf(bnl_filename,0x102,"%s%s%s",RootDirectory,"bundles\\",bnl_name);
    builtin_strncpy(bnl_name + 0x50,"Z:\\",4);
    XAPILIB::lstrcpynA(bnl_name + 0x53,bnl_filename + 3,0x100);
    err = DoFileConsistencyCheck();
    if (err != 0) {
      ReadBNLFile(bnl_filename,bnl_name + 0x50,(astruct_20 **)0x0,0,0);
    }
  }
  return;
}




BundleContext * __fastcall BundleContext::bnlNameFromScriptAID(char *param_1)

{
  BundleContext *bundle_ctx;
  char *pcVar3;
  char *name_ptr;
  char bnl_widename [260];
  char cVar1;
  
  pcVar3 = bnl_widename;
  Assets::aidToBNLName(bnl_widename,param_1);
  bundle_ctx = (BundleContext *)GetBundleContext(bnl_widename);
                    // If the bundle isn't currently open
  if (bundle_ctx == (BundleContext *)0x0) {
    bundle_ctx = (BundleContext *)runtime::CreateBundleContext();
                    // Set the new context's name
    name_ptr = bundle_ctx->name;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      *name_ptr = cVar1;
      name_ptr = name_ptr + 1;
    } while (cVar1 != '\0');
  }
  bundle_ctx->isBeingRead_ = 0;
  bundle_ctx->someBool_ = 1;
  return bundle_ctx;
}




BundleContext * runtime::CreateBundleContext(void)

{
  AssetTempBuffer *pvVar2;
  AssetTempBuffer *pvVar3;
  BundleContext *pSVar1;
  BundleContext *some2c;
  
                    // Extend if full
  if (g_openBundles->tail == g_openBundles->end) {
    g_openBundles = (Buffer<> *)ExtendArray((Buffer *)g_openBundles);
  }
  some2c = g_openBundles->tail;
  g_openBundles->tail = (BundleContext *)((int)&some2c->fileCtx + (uint)g_openBundles->valueSize);
  some2c->isBeingRead_ = 0;
  some2c->isEmpty__ = 0;
  some2c->fileCtx = (FileContext *)0x0;
  some2c->assetDescriptions = (AssetDescription *)0x0;
  some2c->dataViewLists = (DataViewList *)0x0;
  some2c->descriptorSegment = (void *)0x0;
  pvVar2 = malloc_(0x104);
  some2c->name = (char *)pvVar2;
  pvVar3 = malloc_(0x104);
  some2c->bundlePath = (char *)pvVar3;
  some2c->numEntries = 0;
  g_openBundleContexts_ = g_openBundleContexts_ + 1;
  return some2c;
}




void BundleContext::delete(BundleContext *param_1)

{
  BundleContext **ppBVar1;
  char *pcVar2;
  Buffer<> *pBVar3;
  undefined4 uVar4;
  int iVar5;
  BundleContext *pBVar6;
  HeapTableEntry *pHVar7;
  
  if (param_1->isEmpty__ != 0) {
    g_some0x2cMinSize = g_some0x2cMinSize - 1;
  }
  g_openBundleContexts_ = g_openBundleContexts_ - 1;
  pcVar2 = param_1->name;
  iVar5 = FindHeapOf(pcVar2);
  uVar4 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar5].heapHandle == (HANDLE)0x0) {
    pHVar7 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar7 = g_HeapTableBase + iVar5;
  }
  runtime::CurrentHeapToAllocateFrom = iVar5;
  XAPILIB::HeapFree(pHVar7->heapHandle,0,pcVar2);
  pcVar2 = param_1->bundlePath;
  runtime::CurrentHeapToAllocateFrom = uVar4;
  iVar5 = FindHeapOf(pcVar2);
  uVar4 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar5].heapHandle == (HANDLE)0x0) {
    pHVar7 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar7 = g_HeapTableBase + iVar5;
  }
  runtime::CurrentHeapToAllocateFrom = iVar5;
  XAPILIB::HeapFree(pHVar7->heapHandle,0,pcVar2);
  pBVar3 = g_openBundles;
  ppBVar1 = &g_openBundles->tail;
  pBVar6 = (BundleContext *)((int)*ppBVar1 - (uint)g_openBundles->valueSize);
  runtime::CurrentHeapToAllocateFrom = uVar4;
  if (param_1 < pBVar6) {
    _memmove(param_1,(void *)((int)&param_1->fileCtx + (uint)g_openBundles->valueSize),
             (int)pBVar6 - (int)param_1);
    *ppBVar1 = (BundleContext *)((int)*ppBVar1 - (uint)pBVar3->valueSize);
    return;
  }
  *ppBVar1 = (BundleContext *)((int)*ppBVar1 - (uint)g_openBundles->valueSize);
  return;
}




void LoadBundleFromDisc(BundleContext *bundle,int param_2)

{
  char cVar1;
  DWORD err;
  BOOL BVar2;
  char *pcVar3;
  char *pcVar4;
  char local_104 [260];
  
  bundle->assetDescriptions = (AssetDescription *)0x0;
  bundle->dataViewLists = (DataViewList *)0x0;
  bundle->descriptorSegment = (void *)0x0;
  __snprintf(bundle->bundlePath,0x103,"%s%s%s",runtime::RootDirectory,"bundles\\",bundle->name);
  builtin_strncpy(local_104,"Z:\\",4);
  XAPILIB::lstrcpynA(local_104 + 3,bundle->bundlePath + 3,0x100);
  err = runtime::DoFileConsistencyCheck();
  if (err == 0) {
    pcVar4 = bundle->bundlePath;
    pcVar3 = local_104;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
  }
  err = FileContext::Create(&bundle->fileCtx,bundle->bundlePath,GENERIC_READ,3);
  if (err == 0) {
    g_lastBundleName = bundle->name;
    g_fileContextBytesRead = 0;
    BVar2 = FileContext::DecompressZStream
                      (bundle->fileCtx,&g_fileHandle,40,ProcessBNLFile,&g_fileContextBytesRead,
                       param_2);
    if (BVar2 == 0) {
      game::bundle_opened_successfully = 1;
    }
  }
  return;
}




void CloseBundleContextOnError(int param_1,BundleContext *param_2)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  char *pcVar3;
  int unaff_FS_OFFSET;
  
  game::bundle_opened_successfully = 0;
  if (param_2->fileCtx != (FileContext *)0x0) {
    FileContext::Close(param_2->fileCtx);
    param_2->fileCtx = (FileContext *)0x0;
  }
  closeBundleContext(param_2);
  pcVar3 = param_2->bundlePath;
  iVar2 = _strncmp(pcVar3,"Z:\\",4);
  if (iVar2 == 0) {
    bVar1 = runtime::MarkForDeletion(pcVar3);
    if (CONCAT31(extraout_var,bVar1) == 0) {
      pcVar3 = XAPILIB::GetLastError(unaff_FS_OFFSET);
      if (pcVar3 != (char *)0x0) goto LAB_000343bd;
    }
    return;
  }
LAB_000343bd:
  runtime::ExitGame(param_1);
  return;
}



void FUN_000343d0(int *param_1,undefined4 *param_2,int param_3,BNLFileStream *bnlFs,
                 BundleContext *bundleCtx)

{
  DataViewList *pDVar1;
  uint32_t uVar2;
  undefined4 uVar3;
  
  pDVar1 = bundleCtx->assetDescriptions[bnlFs->highestIndexWithAlloc].dataViewListPtr;
  bnlFs->status = New_Name_(3);
  uVar2 = pDVar1->items[bnlFs->field4_0x34].size;
  *param_2 = uVar2;
  uVar3 = XAPILIB::XPhysicalAlloc(uVar2,0xffffffff,0x80,0x404);
  *(undefined4 *)param_3 = uVar3;
  *param_1 = ((bnlFs->bnlHeader).someFlag & 1) << 1;
  pDVar1->items[bnlFs->field4_0x34].offset = *(uint32_t *)param_3;
  return;
}



void BundleContext::AllocateDescriptorSegment
               (BNLStatus *outStatus,void **outChunk4,uint32_t *outSize,BNLFileStream *bnlFStrm,
               BundleContext *bnlCtx)

{
  uint size;
  void *metadata_ptr;
  
  size = (bnlFStrm->bnlHeader).metadataLoc.size;
  bnlFStrm->status = ALLOCATED_METADATA;
  metadata_ptr = malloc_(size);
  bnlCtx->descriptorSegment = metadata_ptr;
  *outSize = (bnlFStrm->bnlHeader).metadataLoc.size;
  *outChunk4 = bnlCtx->descriptorSegment;
  *outStatus = ((bnlFStrm->bnlHeader).someFlag & 1) << 1;
  return;
}



uint ProcessBNLFile(FileContext *param_1,uint errorId,BNLFileStream *inBytes,uint nextReadOffsetPtr,
                   ZSCStatus *status,void **outAllocationPtr,uint *outAllocationSize)

{
  uint16_t uVar1;
  BNLFileStream *bnlFStrm;
  BundleContext *bundleCtx;
  AssetDescription *new_chnk1;
  DataViewList *new_chnk2;
  uint i;
  uint file_count;
  AssetDescription *he_ptr;
  char *local_4;
  astruct_42 *pcVar5;
  BNLFileStream *bnl_bytes;
  astruct_43 *puVar3;
  uint res_desc_size;
  DataViewList *res_desc;
  
  bnlFStrm = inBytes;
  bundleCtx = (BundleContext *)GetBundleContext(inBytes->bnlFile);
  if (errorId != 0) {
    GetErrorById(errorId,&local_4,(char **)&inBytes);
    CloseBundleContextOnError(errorId,bundleCtx);
    *outAllocationPtr = (void *)0x0;
    *outAllocationSize = 0;
    return errorId;
  }
  switch(bnlFStrm->status) {
  case INITIAL_STATE:
    bnlFStrm->status = GOT_FILE_HEADERS;
    bundleCtx->numEntries = (uint)(bnlFStrm->bnlHeader).fileCount;
    new_chnk1 = malloc_((bnlFStrm->bnlHeader).headerEntriesLoc.size);
    bundleCtx->assetDescriptions = new_chnk1;
    *outAllocationSize = (bnlFStrm->bnlHeader).headerEntriesLoc.size;
    *outAllocationPtr = bundleCtx->assetDescriptions;
    *status = (bnlFStrm->bnlHeader).someFlag & New_Name;
    return ERROR_CONTINUE;
  case GOT_FILE_HEADERS:
    res_desc_size = (bnlFStrm->bnlHeader).resourceDescriptionsLoc.size;
    if (res_desc_size != 0) {
      bnlFStrm->status = LOADING_RESOURCES;
      bnlFStrm->highestIndexWithAlloc = 0;
      bnlFStrm->field4_0x34 = 0;
      new_chnk2 = malloc_(res_desc_size);
      bundleCtx->dataViewLists = new_chnk2;
      *outAllocationSize = (bnlFStrm->bnlHeader).resourceDescriptionsLoc.size;
      *outAllocationPtr = bundleCtx->dataViewLists;
      *status = ((bnlFStrm->bnlHeader).someFlag & 1) << 1;
      return ERROR_CONTINUE;
    }
    BundleContext::AllocateDescriptorSegment
              (status,outAllocationPtr,outAllocationSize,bnlFStrm,bundleCtx);
    return ERROR_CONTINUE;
  case LOADING_RESOURCES:
                    // Load Header Entries
    i = 0;
    uVar1 = (bnlFStrm->bnlHeader).fileCount;
    bnlFStrm->highestIndexWithAlloc = -1;
    bnlFStrm->field4_0x34 = 0;
    if (uVar1 != 0) {
      he_ptr = (AssetDescription *)0x0;
      do {
                    // Add the offset of the start of the resource descriptions section to each
                    // resource description (each one now correctly maps into the programs memory),
                    // but only the ones which actually have data
        if ((*(int *)((int)&bundleCtx->assetDescriptions->totalAllocSize + (int)he_ptr) != 0) &&
           (*(int *)(he_ptr->name + (int)(bundleCtx->assetDescriptions->name + 0x98)) =
                 (int)&((DataViewList *)(bundleCtx->dataViewLists->items + -1))->listSize +
                 *(int *)(he_ptr->name + (int)(bundleCtx->assetDescriptions->name + 0x98)),
           bnlFStrm->highestIndexWithAlloc == -1)) {
          bnlFStrm->highestIndexWithAlloc = i;
        }
        i = i + 1;
        he_ptr = he_ptr + 1;
      } while (i < (bnlFStrm->bnlHeader).fileCount);
    }
    break;
  case New_Name_(3):
    res_desc = bundleCtx->assetDescriptions[bnlFStrm->highestIndexWithAlloc].dataViewListPtr;
    i = bnlFStrm->field4_0x34 + 1;
    bnlFStrm->field4_0x34 = i;
    if (i == res_desc->numItems) {
      file_count = (uint)(bnlFStrm->bnlHeader).fileCount;
      i = bnlFStrm->highestIndexWithAlloc + 1;
      bnlFStrm->field4_0x34 = 0;
      bnlFStrm->highestIndexWithAlloc = i;
      if ((int)i < (int)file_count) {
        do {
          if (bundleCtx->assetDescriptions[i].totalAllocSize != 0) break;
          i = i + 1;
          bnlFStrm->highestIndexWithAlloc = i;
        } while ((int)i < (int)(uint)(bnlFStrm->bnlHeader).fileCount);
      }
                    // If the number of resources with a size matches the number of subresources
      if (i == file_count) {
                    // If we've read all of them, allocate the segment
        BundleContext::AllocateDescriptorSegment
                  (status,outAllocationPtr,outAllocationSize,bnlFStrm,bundleCtx);
        return 0x4de;
      }
    }
    break;
  default:
    BundleContext::LoadResources(bundleCtx);
    FileContext::Close(bundleCtx->fileCtx);
    bundleCtx->fileCtx = (FileContext *)0x0;
    *outAllocationPtr = (void *)0x0;
    *outAllocationSize = 0;
    return 0;
  }
  FUN_000343d0((int *)status,outAllocationSize,(int)outAllocationPtr,bnlFStrm,bundleCtx);
  return 0x4de;
}




void BundleContext::LoadResources(BundleContext *param_1)

{
  int iVar1;
  
  param_1->isEmpty__ = 1;
  iVar1 = processBundleMetadata(param_1);
  if (iVar1 == 0) {
    if (param_1->isEmpty__ == 0) {
      delete(param_1);
    }
    else if (param_1->isBeingRead_ == 0) {
      param_1->someBool_ = 0;
      g_some0x2cBufferSize = 1;
    }
    game::bundle_opened_successfully = 0;
    g_some0x2cMinSize = g_some0x2cMinSize + 1;
    return;
  }
  g_some0x2cMinSize = g_some0x2cMinSize + 1;
  game::bundle_opened_successfully = 0;
  return;
}




undefined4 BundleContext::processBundleMetadata(BundleContext *bundleCtx)

{
  char *pcVar1;
  uchar bVar4;
  byte bVar3;
  int iVar4;
  byte *pbVar5;
  ResourceLoaderStub *loader;
  uint i;
  uint entry_i;
  uint32_t entry_ptr;
  AssetDescription *asset_desc;
  DataViewList *dvl;
  void *descriptor;
  AssetDescription *asset_descc;
  char c;
  int iVar2;
  
  entry_i = 0;
  if (bundleCtx->numEntries != 0) {
    entry_ptr = 0;
    do {
      i = 0;
                    // Load the current asset
                    // eg. aid_texture_ghoulies_blahblahblah
      asset_desc = bundleCtx->assetDescriptions;
                    // Update the file locator offset to be the real address in memory
      *(int *)(asset_desc->name + entry_ptr + 0x90) =
           *(int *)(asset_desc->name + entry_ptr + 0x90) + (int)bundleCtx->descriptorSegment;
      pcVar1 = asset_desc->name + entry_ptr + 0x88;
      pcVar1[0] = '\0';
      pcVar1[1] = '\0';
      pcVar1[2] = '\0';
      pcVar1[3] = '\0';
      asset_descc = bundleCtx->assetDescriptions;
      descriptor = *(void **)(asset_descc->name + entry_ptr + 0x90);
      dvl = *(DataViewList **)(asset_descc->name + entry_ptr + 0x98);
      iVar4 = 0;
      c = asset_descc->name[entry_ptr + 4];
      while (c != '_') {
        Assets::LoadingAssetType[iVar4] = c;
        iVar2 = iVar4 + entry_ptr + 5;
        iVar4 = iVar4 + 1;
        c = asset_descc->name[iVar2];
      }
      Assets::LoadingAssetType[iVar4] = '\0';
      loader = g_majorResourceLoaders;
      do {
                    // Check loader matches
        pbVar5 = (byte *)loader->typeStr;
        if (pbVar5 != (byte *)0x0) {
          iVar4 = (int)Assets::LoadingAssetType - (int)pbVar5;
          while( true ) {
            bVar4 = *pbVar5;
            if (0x20 < bVar4) {
              bVar4 = bVar4 & 0b11011111;
            }
            bVar3 = pbVar5[iVar4];
            if (0x20 < bVar3) {
              bVar3 = bVar3 & 0xdf;
            }
            if (bVar4 != bVar3) break;
            pbVar5 = pbVar5 + 1;
            if (bVar4 == 0) goto LAB_000347ea;
          }
          if (bVar4 == bVar3) {
LAB_000347ea:
            if ((i * 0x10 != -0x4df258) &&
               (g_majorResourceLoaders[i].processDescriptor != (code *)0x0)) {
                    // Goes to 
                    // 
                    // texture  - 0x53520
                    // anim   - 0x0002dd90
                    // model::readBundle - 0x00052910
              (*g_majorResourceLoaders[i].processDescriptor)(descriptor,descriptor,dvl);
            }
            break;
          }
        }
        i = i + 1;
        loader = loader + 1;
      } while (i < 0x10);
      if (g_some0x2cMinSize != 0) {
        Audio::Update(runtime::DeltaTime);
        Audio::UpdateListener();
        Audio::UpdatePlayerContexts();
      }
      entry_i = entry_i + 1;
      entry_ptr = entry_ptr + 0xa0;
    } while (entry_i < bundleCtx->numEntries);
  }
  return 1;
}




void closeBundleContext(BundleContext *param_1)

{
  int iVar1;
  PVOID BaseAddress;
  DataViewList *mem;
  AssetDescription *mem_00;
  undefined4 uVar2;
  HeapTableEntry *pHVar3;
  int iVar4;
  uint uVar5;
  uint local_4;
  
  iVar4 = 0;
  if (param_1->descriptorSegment != (void *)0x0) {
    free(param_1->descriptorSegment);
  }
  local_4 = 0;
  if (param_1->numEntries != 0) {
    do {
      iVar1 = *(int *)(param_1->assetDescriptions->name + iVar4 + 0x98);
      if ((iVar1 != 0) && (uVar5 = 0, *(int *)(iVar1 + 4) != 0)) {
        do {
          BaseAddress = *(PVOID *)(iVar1 + 8 + uVar5 * 8);
          if (BaseAddress != (PVOID)0x0) {
            XAPILIB::XPhysicalFree(BaseAddress);
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < *(uint *)(iVar1 + 4));
      }
      local_4 = local_4 + 1;
      iVar4 = iVar4 + 0xa0;
    } while (local_4 < param_1->numEntries);
  }
  mem = param_1->dataViewLists;
  if (mem != (DataViewList *)0x0) {
    iVar4 = FindHeapOf(mem);
    uVar2 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar4].heapHandle == (HANDLE)0x0) {
      pHVar3 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar3 = g_HeapTableBase + iVar4;
    }
    runtime::CurrentHeapToAllocateFrom = iVar4;
    XAPILIB::HeapFree(pHVar3->heapHandle,0,mem);
    runtime::CurrentHeapToAllocateFrom = uVar2;
  }
  mem_00 = param_1->assetDescriptions;
  if (mem_00 != (AssetDescription *)0x0) {
    iVar4 = FindHeapOf(mem_00);
    uVar2 = runtime::CurrentHeapToAllocateFrom;
    if (g_HeapTableBase[iVar4].heapHandle == (HANDLE)0x0) {
      pHVar3 = (HeapTableEntry *)0x0;
    }
    else {
      pHVar3 = g_HeapTableBase + iVar4;
    }
    runtime::CurrentHeapToAllocateFrom = iVar4;
    XAPILIB::HeapFree(pHVar3->heapHandle,0,mem_00);
    runtime::CurrentHeapToAllocateFrom = uVar2;
  }
  return;
}




BundleContext * GetBundleContext(char *param_1)

{
  byte bVar1;
  char *pbVar2;
  int iVar2;
  char *pbVar4;
  BundleContext *pBVar3;
  bool bVar4;
  char c;
  
  pBVar3 = g_openBundles->head;
  do {
    if (g_openBundles->tail <= pBVar3) {
      return (BundleContext *)0x0;
    }
    pbVar2 = pBVar3->name;
    pbVar4 = param_1;
    do {
      c = *pbVar2;
      bVar4 = (byte)c < (byte)*pbVar4;
      if (c != *pbVar4) {
LAB_00034a04:
        iVar2 = (1 - (uint)bVar4) - (uint)(bVar4 != 0);
        goto LAB_00034a09;
      }
      if (c == '\0') break;
      bVar1 = pbVar2[1];
      bVar4 = bVar1 < (byte)pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_00034a04;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar2 = 0;
LAB_00034a09:
    if (iVar2 == 0) {
      return pBVar3;
    }
    pBVar3 = (BundleContext *)((int)&pBVar3->fileCtx + (uint)g_openBundles->valueSize);
  } while( true );
}



ResourceLoadStatus
someResource::getAssetDescription
          (BundleContext **outBundleCtx_,char *inName,AssetDescription **outAssetDescription)

{
  BOOL success;
  AssetDescription *header_entry;
  BundleContext *bundle_ctx;
  
  success = Assets::BundleContext::getAssetDescriptionByName(inName,&bundle_ctx,&header_entry);
  if (success != 0) {
    *outAssetDescription = header_entry;
    return IN_BUNDLE?;
  }
  return ERROR;
}



BOOL Assets::BundleContext::getAssetDescriptionByName
               (char *name,BundleContext **outBundleCtx,AssetDescription **assetDescription)

{
  uint uVar1;
  BOOL match;
  AssetDescription *description;
  uint entry_index;
  BundleContext *head;
  BundleContext *tail;
  
  tail = g_openBundles->tail;
  head = g_openBundles->head;
  do {
    if (tail <= head) {
      return 0;
    }
    if (head->isEmpty__ != 0) {
      uVar1 = head->numEntries;
      entry_index = 0;
      if (uVar1 != 0) {
        description = head->assetDescriptions;
        do {
          match = AssetNamesMatch(name,description->name);
          if (match != 0) {
            *outBundleCtx = head;
            *assetDescription = head->assetDescriptions + entry_index;
            return 1;
          }
          entry_index = entry_index + 1;
          description = description + 1;
        } while (entry_index < uVar1);
      }
    }
    head = head + 1;
  } while( true );
}



uint someResource::SetFilePointerFromBundle
               (uint loaderId,AssetDescription *description,uint32_t *fileOffset,uint32_t *fileSize,
               undefined4 *resOffset,uint32_t *resSize)

{
  *fileOffset = description->descriptorPtr;
  *fileSize = description->descriptorSize;
  *resOffset = description->dataViewListPtr;
  *resSize = description->totalAllocSize;
  description->useCount = description->useCount + 1;
  return 1;
}




uint CreateFilePointer(char *filename,DemandFileContext *dfc,int param_3)

{
  DWORD err;
  int iVar1;
  DemandFileContext *pFVar2;
  bool bVar3;
  char *local_8;
  char *local_4;
  
  pFVar2 = dfc;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    pFVar2->fileCtx = (FileContext *)0x0;
    pFVar2 = (DemandFileContext *)&pFVar2->fileHandle;
  }
  *(undefined4 *)&dfc->field_0x48 = 0;
  err = FileContext::Create(&dfc->fileCtx,filename,0x80000000,3);
  if ((err == 0) &&
     (err = FileContext::DecompressZStream
                      (dfc->fileCtx,&dfc->fileHandle,40,FileContext::ReadAudioCallback_,(LPDWORD)dfc
                       ,(int)pFVar2), err == 0)) {
    err = FileContext::Update(dfc->fileCtx);
  }
  if (dfc->fileCtx != (FileContext *)0x0) {
    FileContext::Close(dfc->fileCtx);
  }
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar3 = err == 0;
  }
  else {
    bVar3 = err == 0x4de;
  }
  if (!bVar3) {
    GetErrorById(err,&local_4,&local_8);
  }
  return err;
}



char * FileContext::ReadAudioCallback_
                 (FileContext *param_1,char *param_2,char *param_3,int *param_4,undefined4 *param_5,
                 undefined4 *param_6,undefined4 *param_7)

{
  FileSizeBlock fsb;
  char *pcVar1;
  char *pcVar2;
  DWORD DVar3;
  void *pvVar4;
  undefined4 uVar5;
  uint unaff_EBP;
  
  pcVar2 = param_3;
  pcVar1 = param_2;
  if (param_2 != (char *)0x0) {
    *param_6 = 0;
    *param_7 = 0;
    if (0x3e5 < (int)param_2) {
      if (param_2 == (char *)0x4de) {
        return (char *)0x4de;
      }
      GetErrorById((uint)param_2,&param_3,&param_2);
      return pcVar1;
    }
    if (0x3e3 < (int)param_2) {
      return param_2;
    }
    GetErrorById((uint)param_2,&param_3,&param_2);
    return pcVar1;
  }
  DVar3 = 0;
  pcVar1 = param_3;
  if (*(int *)(param_3 + 0x48) == 0) {
    if (*(int *)(param_3 + 0xc) == 0x48e58836) {
      *(undefined4 *)(param_3 + 0x2c) = *(undefined4 *)(param_3 + 0x18);
      *(undefined4 *)(param_3 + 0x34) = *(undefined4 *)(param_3 + 0x14);
      if (*(int *)(param_3 + 0x20) != 0) {
        *(undefined4 *)(param_3 + 0x38) = *(undefined4 *)(param_3 + 0x24);
        *(undefined4 *)(param_3 + 0x40) = *(undefined4 *)(param_3 + 0x1c);
      }
    }
    else {
      pcVar1[0x34] = '\0';
      pcVar1[0x35] = '\0';
      pcVar1[0x36] = '\0';
      pcVar1[0x37] = '\0';
      pcVar1[0x48] = '\x02';
      pcVar1[0x49] = '\0';
      pcVar1[0x4a] = '\0';
      pcVar1[0x4b] = '\0';
      fsb.field1_0x4 = unaff_EBP;
      fsb.bigStruct = (DWORD)&param_2;
      DVar3 = GetFileSizeOuter(param_1,fsb);
      if (DVar3 == 0) {
        DVar3 = runtime::AlignZStream_(param_1,(ulong)param_2,(int *)(pcVar2 + 0x2c));
      }
    }
    if (*(uint *)(pcVar2 + 0x2c) != 0) {
      pcVar1[0x48] = '\x02';
      pcVar1[0x49] = '\0';
      pcVar1[0x4a] = '\0';
      pcVar1[0x4b] = '\0';
      pvVar4 = malloc_(*(uint *)(pcVar2 + 0x2c));
      *(void **)(pcVar2 + 0x30) = pvVar4;
    }
    if (*(uint *)(pcVar2 + 0x38) != 0) {
      pcVar1[0x48] = '\x01';
      pcVar1[0x49] = '\0';
      pcVar1[0x4a] = '\0';
      pcVar1[0x4b] = '\0';
      pvVar4 = malloc_(*(uint *)(pcVar2 + 0x38));
      *(void **)(pcVar2 + 0x3c) = pvVar4;
      pcVar1[0x44] = '\0';
      pcVar1[0x45] = '\0';
      pcVar1[0x46] = '\0';
      pcVar1[0x47] = '\0';
      *param_4 = *(int *)(pcVar2 + 0x40);
      *param_7 = *(undefined4 *)(pcVar2 + 0x38);
      *param_6 = *(undefined4 *)(pcVar2 + 0x3c);
      *param_5 = 0;
      return (char *)0x4de;
    }
    if (DVar3 != 0) {
      if (DVar3 == 0x4de) {
        return (char *)0x4de;
      }
      goto LAB_00035521;
    }
  }
  if (*(int *)(pcVar2 + 0x48) == 1) {
    if (*(uint *)(pcVar2 + 0x44) < *(uint *)(*(int *)(pcVar2 + 0x3c) + 4)) {
      *param_4 = *(int *)(*(int *)(pcVar2 + 0x3c) + 8 + *(uint *)(pcVar2 + 0x44) * 8) +
                 *(int *)(pcVar2 + 0x1c);
      uVar5 = *(undefined4 *)(*(int *)(pcVar2 + 0x3c) + 0xc + *(int *)(pcVar2 + 0x44) * 8);
      *param_7 = uVar5;
      uVar5 = XAPILIB::XPhysicalAlloc(uVar5,0xffffffff,0x80,0x404);
      *param_6 = uVar5;
      *param_5 = 0;
      *(undefined4 *)(*(int *)(pcVar2 + 0x3c) + 8 + *(int *)(pcVar2 + 0x44) * 8) = uVar5;
      *(int *)(pcVar2 + 0x44) = *(int *)(pcVar2 + 0x44) + 1;
      return (char *)0x4de;
    }
    pcVar1[0x48] = '\x02';
    pcVar1[0x49] = '\0';
    pcVar1[0x4a] = '\0';
    pcVar1[0x4b] = '\0';
  }
  if (*(int *)(pcVar2 + 0x48) == 2) {
    *param_4 = *(int *)(pcVar2 + 0x34);
    *param_6 = *(undefined4 *)(pcVar2 + 0x30);
    *param_7 = *(undefined4 *)(pcVar2 + 0x2c);
    *param_5 = 0;
    pcVar1[0x48] = '\x03';
    pcVar1[0x49] = '\0';
    pcVar1[0x4a] = '\0';
    pcVar1[0x4b] = '\0';
    return (char *)0x4de;
  }
LAB_00035521:
  *param_6 = 0;
  *param_7 = 0;
  return (char *)DVar3;
}



void Assets::createDirectoryResolver
               (GetHeaderEntryFn *getHeaderEntryFn,void *readBundleFn,void *freeFn,uint param_4,
               void **resolveDirectoryFn)

{
  uint uVar1;
  int i;
  LoaderCallbacks *loader;
  
  i = 0;
  uVar1 = 0;
  do {
    if (*(int *)((int)&directoryResolver[0].loaderId + uVar1) == 0) {
      loader = directoryResolver + i;
      goto LAB_0003555b;
    }
    uVar1 = uVar1 + 0x18;
    i = i + 1;
  } while (uVar1 < 0x180);
  loader = (LoaderCallbacks *)0x0;
LAB_0003555b:
  g_nextLoaderOffset_ = g_nextLoaderOffset_ + 1;
  uVar1 = g_nextLoaderOffset_;
  if (g_nextLoaderOffset_ == 0) {
    uVar1 = 1;
  }
  loader->getAssetHeader = getHeaderEntryFn;
  loader->updateHeaderEntryOffsets = readBundleFn;
  loader->closeBundle = freeFn;
  loader->flagsOrType = param_4;
  loader->loaderId = uVar1;
  loader->resolveDirectoryFn = resolveDirectoryFn;
  return;
}



uint Assets::LoadResourceAttributes_
               (Asset *asset,uint32_t *readerIndex,AssetDescription *defaultAssetDesc)

{
  BOOL res_load_status;
  ResourceReader *reader;
  uint success;
  uint loader_ptr;
  LoaderCallbacks *res_file_loader;
  AssetDescription *header_entry;
  
                    // If the resource has already been loaded, return null?
  if ((*readerIndex != 0) &&
     ((int *)((int)&g_resourceReaders->head->loaderId +
             (*readerIndex - 1) * (uint)g_resourceReaders->valueSize) != (int *)0x0)) {
    return 0;
  }
  res_file_loader = directoryResolver;
  loader_ptr = 0;
                    // ECX not actually used in callback
  header_entry = defaultAssetDesc;
  do {
                    // Calls 
                    // 
                    // 
                    // Generic loader???: {@address 0x00034e90}
                    // 
                    // 
    if (res_file_loader->loaderId != 0) {
                    // {@address 0x00034a30} Header From Open Bundle
                    // {@address 0x00034e90} Header From Binary
                    // {@address 0x000350a0} Header generated from open file???
                    // 
                    // 
                    // Also goes to demand
      res_load_status =
           (*res_file_loader->getAssetHeader)(res_file_loader->loaderId,asset->name,&header_entry);
                    // Find the loader and associate it with the reader
      if (res_load_status != 0) {
        reader = GetNewResourceHandle();
        *readerIndex = ((int)reader - (int)g_resourceReaders->head) /
                       (int)(uint)g_resourceReaders->valueSize + 1;
        reader->loaderId = res_file_loader->loaderId;
                    // Calls trigger asset onload
        reader->loadStatus = res_load_status;
                    // 0x34af0 for bundles (SetFilePointerFromBundle)
                    // 0x00035100 sometimes
        success = (*res_file_loader->updateHeaderEntryOffsets)
                            (res_file_loader->loaderId,header_entry,&reader->fileOffset,
                             &reader->useCount,&reader->resOffset,&reader->resSize);
        return success;
      }
    }
    loader_ptr = loader_ptr + 0x18;
    res_file_loader = res_file_loader + 1;
  } while (loader_ptr < 0x180);
  return 0;
}




BOOL LoadResourceFromFiles(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined1 local_4 [4];
  
  uVar2 = 0;
  do {
    iVar1 = *(int *)((int)&Assets::directoryResolver[0].loaderId + uVar2);
    if (iVar1 != 0) {
      iVar1 = (**(code **)((int)&Assets::directoryResolver[0].getAssetHeader + uVar2))
                        (iVar1,param_1,local_4);
      if (iVar1 != 0) {
        return 1;
      }
    }
    uVar2 = uVar2 + 0x18;
  } while (uVar2 < 0x180);
  return 0;
}




int LoadWavebanksInner(WavebankDrive *drive,char *filepath,CacheContext *param_3)

{
  XACTSoundbank *xactSoundbank;
  DWORD DVar1;
  uint e;
  char local_104 [260];
  
  param_3->wavebankDrive = drive;
  builtin_strncpy(local_104,"Z:\\",4);
  XAPILIB::lstrcpynA(local_104 + 3,filepath + 3,0x100);
  DVar1 = runtime::DoFileConsistencyCheck();
  if (DVar1 == 0) {
    xactSoundbank = (XACTSoundbank *)drive->loadType;
    if ((0 < (int)xactSoundbank) && ((int)xactSoundbank < 3)) {
      Audio::CreateStreamedWaveBankAtFileOffset
                (local_104,0,(HANDLE)0x0,0,xactSoundbank,&param_3->nextCache,drive->field1_0x4,
                 drive->field2_0x8,(undefined *)0x0,(HANDLE)0x0);
    }
    return 0;
  }
  e = runtime::ReadBNLFile(filepath,local_104,(astruct_20 **)param_3,FUN_00039d00,param_3);
  if (e != 0) {
    runtime::ExitGame(e);
  }
  return e;
}



// WARNING: Inlined function: FUN_0015d060


char * LoadFileSelectMovies(void)

{
  AllocatedMovie *movie;
  char *pcVar1;
  MovieLoadEntry *loadEntry;
  char *name;
  AllocatedMovie **movieList;
  undefined4 *puVar2;
  
  movieList = PTR_ARRAY_00506598;
  loadEntry = MovieLoadEntry_ARRAY_004290c8;
  do {
    movie = (AllocatedMovie *)LoadMovie(loadEntry->name,0b00010100);
    *movieList = movie;
    loadEntry = loadEntry + 1;
    movieList = movieList + 1;
  } while ((int)loadEntry < 0x429434);
  puVar2 = &DAT_005065a4;
  name = asset_name_0042941c;
  do {
    pcVar1 = (char *)LoadMovie(name,0x14);
    *puVar2 = pcVar1;
    name = name + 0x10c;
    puVar2 = puVar2 + 1;
  } while ((int)name < 0x429958);
  return pcVar1;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


void __fastcall CloseUnneededOpenFiles_(int param_1,z_stream *param_2)

{
  uLong uVar1;
  free_func pfVar2;
  uint uVar3;
  
  uVar1 = param_2->total_in;
  if (uVar1 == 0) {
    param_2->total_out = (uLong)runtime::CacheContext.wavebankDrive;
    param_2->zfree = (free_func)runtime::CacheContext.cache2;
    param_2->msg = (char *)0x0;
    uVar3 = FUN_000e9450(param_2);
    if (uVar3 != 0) goto LAB_000e92ff;
    param_2->total_in = 1;
    param_1 = 0;
  }
  else if (uVar1 == 1) {
    pfVar2 = (free_func)param_2->total_out;
    param_2->total_out = (uLong)param_2->zfree;
    param_2->zfree = pfVar2;
    param_1 = FUN_000e94d0();
    if (param_1 == 0) {
      param_1 = FUN_000e9450(param_2);
    }
    if (param_1 == 0x26) {
      param_2->total_in = 3;
      return;
    }
  }
  else if (uVar1 == 3) {
    UpdateFile_();
    MindMemory::dtor((MindMemoryTargetWantedToAttack *)param_2);
    return;
  }
  if (param_1 == 0) {
    return;
  }
LAB_000e92ff:
  FUN_000e9380();
  return;
}




void UpdateFile_(void)

{
  HANDLE hFile;
  BOOL success;
  int unaff_ESI;
  int unaff_FS_OFFSET;
  _FILETIME local_8;
  
  hFile = *(HANDLE *)(*(int *)(unaff_ESI + 0x20) + 8);
  success = XAPILIB::GetFileTime
                      (*(HANDLE *)(*(int *)(unaff_ESI + 0xc) + 8),(LPFILETIME)0x0,(LPFILETIME)0x0,
                       &local_8);
  if (success != 0) {
    success = XAPILIB::SetFileTime(hFile,(FILETIME *)0x0,(FILETIME *)0x0,&local_8);
    if (success != 0) goto LAB_000e934b;
  }
  XAPILIB::GetLastError(unaff_FS_OFFSET);
LAB_000e934b:
  FileContext::CloseInner(*(FileContext **)(unaff_ESI + 0x20));
  if (*(code **)(unaff_ESI + 0x2c) != (code *)0x0) {
    (**(code **)(unaff_ESI + 0x2c))
              (*(undefined4 *)(unaff_ESI + 0x20),0,*(undefined4 *)(unaff_ESI + 0x30));
  }
  FileContext::Close(*(FileContext **)(unaff_ESI + 0xc));
  FileContext::Close(*(FileContext **)(unaff_ESI + 0x20));
  return;
}



// WARNING: Enum "_D3DFORMAT": Some values do not have unique names
// WARNING: Struct "actorBodyFlags": ignoring multiple overlapping fields


uint FUN_000e9450(z_stream *param_1)

{
  FileSizeBlock fsb;
  uint err;
  internal_state *piVar1;
  int readSize;
  DWORD file_size;
  
  readSize = 0;
  fsb.field1_0x4 = 0;
  fsb.bigStruct = (DWORD)&file_size;
  err = FileContext::GetFileSizeOuter((FileContext *)param_1->next_out,fsb);
  if (err == 0) {
    piVar1 = (internal_state *)(file_size - (int)param_1->msg);
    if ((int)piVar1 < 1) {
      return 0x26;
    }
    if ((int)runtime::CacheContext.allocationSize <= (int)piVar1) {
      piVar1 = (internal_state *)runtime::CacheContext.allocationSize;
    }
    param_1->state = piVar1;
    err = runtime::AlignZStream_
                    ((FileContext *)param_1->next_out,(ulong)piVar1,(int *)&stack0xfffffff8);
    if (err == 0) {
      err = ReadNBytesOfFile((LPVOID)param_1->total_out,readSize,FUN_000e9510,
                             (ZStreamContext *)param_1,(FileContext *)param_1->next_out);
      param_1->msg = param_1->msg + readSize;
    }
  }
  return err;
}




DWORD runtime::DoFileConsistencyCheck(void)

{
  FILE *file1;
  char *pcVar1;
  FILE *file2;
  DWORD DVar1;
  int unaff_FS_OFFSET;
  
                    // Open 2 handles, keep the one that which opened first
  file1 = CreateFileHandle(0x80000000,7,0,3,0x20000080,0,0);
  if ((file1 == (FILE *)0xffffffff) &&
     (pcVar1 = XAPILIB::GetLastError(unaff_FS_OFFSET), pcVar1 != (char *)0x0)) {
    return (DWORD)pcVar1;
  }
  pcVar1 = (char *)0x0;
  file2 = CreateFileHandle(0x80000000,7,0,3,0x20000080,0,0);
  if ((file2 != (FILE *)0xffffffff) ||
     (pcVar1 = XAPILIB::GetLastError(unaff_FS_OFFSET), pcVar1 == (char *)0x0)) {
    DVar1 = GetFileTimeDifference(file1,file2);
    if (DVar1 != 0) {
      pcVar1 = (char *)0x51a;
    }
    if (file2 != (FILE *)0xffffffff) {
      XAPILIB::CloseHandle(file2);
    }
  }
  if (file1 != (FILE *)0xffffffff) {
    XAPILIB::CloseHandle(file1);
  }
  return (DWORD)pcVar1;
}




DWORD runtime::GetFileTimeDifference(HANDLE param_1,HANDLE param_2)

{
  uint uVar1;
  FILETIME local_10;
  FILETIME local_8;
  
  XAPILIB::GetFileTime(param_2,(LPFILETIME)0x0,(LPFILETIME)0x0,&local_10);
  XAPILIB::GetFileTime(param_1,(LPFILETIME)0x0,(LPFILETIME)0x0,&local_8);
  uVar1 = (local_10.dwHighDateTime - local_8.dwHighDateTime) -
          (uint)(local_10.dwLowDateTime < local_8.dwLowDateTime);
  if ((0x7fffffff < uVar1) &&
     (((int)uVar1 < -1 || (local_10.dwLowDateTime - local_8.dwLowDateTime < 0xfeced300)))) {
    return 0xffffffff;
  }
  if ((-1 < (int)uVar1) &&
     ((0 < (int)uVar1 || (20000000 < local_10.dwLowDateTime - local_8.dwLowDateTime)))) {
    return 1;
  }
  return 0;
}




void runtime::StreamFiles(void)

{
  FileContext *pFVar1;
  FileContext *fileCtx;
  undefined4 uVar2;
  int heapIndex;
  HeapTableEntry *pHVar3;
  FileContext **next;
  int open;
  
  pFVar1 = CacheContext.fileHead;
  while (fileCtx = pFVar1, fileCtx != (FileContext *)0x0) {
    open = fileCtx->fileStatus;
    next = &fileCtx->next;
    pFVar1 = *next;
    if (open != 0) {
      if (open == 1) {
        FileContext::ProcessLastChunk(fileCtx);
      }
      else if (open == 2) {
        if (fileCtx->prev != (FileContext *)0x0) {
          fileCtx->prev->next = pFVar1;
        }
        if (*next != (FileContext *)0x0) {
          (*next)->prev = fileCtx->prev;
        }
        fileCtx->prev = (FileContext *)0x0;
        *next = (FileContext *)0x0;
        heapIndex = FindHeapOf(fileCtx);
        uVar2 = CurrentHeapToAllocateFrom;
        if (g_HeapTableBase[heapIndex].heapHandle == (HANDLE)0x0) {
          pHVar3 = (HeapTableEntry *)0x0;
        }
        else {
          pHVar3 = g_HeapTableBase + heapIndex;
        }
        CurrentHeapToAllocateFrom = heapIndex;
        XAPILIB::HeapFree(pHVar3->heapHandle,0,fileCtx);
        CacheContext.field9_0x30 = CacheContext.field9_0x30 + -1;
        CurrentHeapToAllocateFrom = uVar2;
                    // 2 = done with the file
      }
    }
  }
  return;
}




uint AllocFileContext(FileContext **param_1)

{
  FileContext *fileCtx;
  FileContext *tail;
  FileContext *ppvVar1;
  char *local_8;
  char *local_4;
  
  fileCtx = malloc_(304);
  if (fileCtx != (FileContext *)0x0) {
    *param_1 = fileCtx;
    tail = (FileContext *)0x506618;
    if (runtime::CacheContext.fileHead != (FileContext *)0x0) {
      ppvVar1 = (FileContext *)&runtime::CacheContext.fileHead;
      do {
        tail = ppvVar1->prev;
        ppvVar1 = (FileContext *)&tail->next;
      } while (tail->next != (FileContext *)0x0);
    }
    tail->next = fileCtx;
    fileCtx->prev = tail;
    fileCtx->next = (FileContext *)0x0;
    runtime::CacheContext.field9_0x30 = runtime::CacheContext.field9_0x30 + 1;
    fileCtx->fileStatus = 0;
    fileCtx->filePtr = (FILE *)0xffffffff;
    (fileCtx->overlapped).Internal = 0;
    (fileCtx->overlapped).InternalHigh = 0;
    (fileCtx->overlapped).Offset = 0;
    (fileCtx->overlapped).OffsetHigh = 0;
    (fileCtx->overlapped).hEvent = (HANDLE)0x0;
    return 0;
  }
  GetErrorById(0xe,&local_4,&local_8);
  return 14;
}




DWORD FileContext::ProcessLastChunk(FileContext *fileCtx)

{
  uint32_t uVar1;
  code *pcVar2;
  BOOL success;
  char *error;
  int unaff_FS_OFFSET;
  DWORD bytes_transferred;
  
  error = (char *)0x0;
  success = XAPILIB::GetOverlappedResult
                      (fileCtx->filePtr,(LPOVERLAPPED)&fileCtx->overlapped,&bytes_transferred,0);
  if (success == 0) {
    error = XAPILIB::GetLastError(unaff_FS_OFFSET);
    if ((0x3e3 < (int)error) && ((int)error < 0x3e6)) {
      return 0x4de;
    }
    bytes_transferred = 0;
  }
  runtime::CacheContext.field10_0x34 = runtime::CacheContext.field10_0x34 + -1;
  uVar1 = (fileCtx->overlapped).Offset;
  pcVar2 = fileCtx->onReadCallback;
  fileCtx->fileStatus = 0;
  (fileCtx->overlapped).Offset = uVar1 + bytes_transferred;
  if ((pcVar2 != (code *)0x0) &&
     ((*pcVar2)(fileCtx,error,fileCtx->zStreamContext), fileCtx->fileStatus == 1)) {
    return 0x4de;
  }
  return (DWORD)error;
}



BOOL FileContext::DecompressZStream
               (FileContext *fileCtx,HANDLE hFile,uint startOffset,void *callback,
               LPDWORD lpNumberOfBytesRead,int param_6)

{
  uint file_size;
  ZStreamContext *zsc;
  bool bVar2;
  ZStreamContext *z;
  char *pcStack_4;
  FileSizeBlock fsb;
  
  fsb.field1_0x4 = param_6;
  fsb.bigStruct = (DWORD)&z;
  file_size = GetFileSizeOuter(fileCtx,fsb);
  zsc = z;
  if (file_size == 0) {
                    // If the file is bigger than 0x20000, decompress it?
    if (0x20000 < (int)z) {
      z = (ZStreamContext *)FUN_00020000;
    }
    file_size = runtime::AlignZStream_(fileCtx,(ulong)z,(int *)&z);
    zsc = z;
    if ((file_size == 0) && (file_size = ZStreamContext::new(&z,(int)z), zsc = z, file_size == 0)) {
      z->outWriteHead = hFile;
      z->startOffset = startOffset;
      z->postReadCallback = callback;
      z->bytesReadPtr_ = lpNumberOfBytesRead;
      file_size = ReadAssetFromBNLFile(fileCtx,0,z);
      if (file_size == 0) goto LAB_000ea0ee;
    }
  }
  if (zsc != (ZStreamContext *)0x0) {
    ZStreamContext::free(zsc);
  }
LAB_000ea0ee:
  if ((int)file_size < 0x3e6) {
    if (0x3e3 < (int)file_size) {
      return file_size;
    }
    bVar2 = file_size == 0;
  }
  else {
    bVar2 = file_size == 0x4de;
  }
  if (!bVar2) {
    GetErrorById(file_size,&pcStack_4,(char **)&z);
  }
  return file_size;
}




uint ZStreamContext::new(ZStreamContext **outZsc,int filesize)

{
  ZStreamContext *ptr;
  uint err;
  bool bVar1;
  char *local_4;
  
  ptr = malloc_(filesize + 0x48);
  if (ptr == (ZStreamContext *)0x0) {
    err = 8;
  }
  else {
    ptr->fileOffset = 0;
    ptr->nextReadOffset_ = 0;
    ptr->zscStatus = INIT_STATUS;
    ptr->chunkStart = (Bytef *)ptr->deflatedData;
    ptr->bytesRead = 0;
    ptr->chunkSize = filesize;
    ptr->outWriteHead = (void *)0x0;
    ptr->readHead = 0;
    ptr->startOffset = 0;
    err = newZStreamContext(&ptr->ctx);
    if (err != 0) {
      ::free(ptr);
      ptr = (ZStreamContext *)0x0;
    }
  }
  *outZsc = ptr;
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar1 = err == 0;
  }
  else {
    bVar1 = err == 0x4de;
  }
  if (!bVar1) {
    GetErrorById(err,&local_4,(char **)&outZsc);
  }
  return err;
}




void ZStreamContext::free(ZStreamContext *zsc)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  runtime::EndZSInflate(zsc->ctx);
  iVar2 = FindHeapOf(zsc);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,zsc);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}




uint ReadAssetFromBNLFile(FileContext *fileCtx,int someOffset,ZStreamContext *inZsc)

{
  DWORD err;
  ZStreamContext *zsc;
  bool bVar1;
  char *local_8;
  char *local_4;
  uint pcVar1;
  
  err = FileContext::Update(fileCtx);
  zsc = inZsc;
  if ((err != 0) || (err = runtime::AlignFileContextOffsets2_(fileCtx,inZsc,someOffset), err != 0))
  goto LAB_000ea2c3;
  pcVar1 = zsc->fileOffset;
  err = FileContext::Update(fileCtx);
  if ((err == 0) && (err = runtime::AlignZStream_(fileCtx,pcVar1,(int *)&local_8), err == 0)) {
    if ((pcVar1 == 0) || ((char *)pcVar1 == local_8)) {
      (fileCtx->overlapped).Offset = pcVar1;
    }
    else {
      err = 0x57;
LAB_000ea294:
      GetErrorById(err,&local_4,&local_8);
      zsc = inZsc;
    }
LAB_000ea2a5:
    if (err != 0) goto LAB_000ea2c3;
  }
  else {
    if (0x3e5 < (int)err) {
      if (err != 0x4de) goto LAB_000ea294;
      goto LAB_000ea2a5;
    }
    if (0x3e3 < (int)err) goto LAB_000ea2a5;
    if (err != 0) goto LAB_000ea294;
  }
  err = ReadNBytesOfFile(zsc->chunkStart,zsc->chunkSize,File::FileContext::OnReadCallback,zsc,
                         fileCtx);
LAB_000ea2c3:
  zsc->bytesRead = zsc->nextReadOffset_ - zsc->fileOffset;
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar1 = err == 0;
  }
  else {
    bVar1 = err == 0x4de;
  }
  if (!bVar1) {
    GetErrorById(err,&local_4,(char **)&inZsc);
  }
  return err;
}




void File::FileContext::OnReadCallback(FileContext *fileCtx,uint readErr,ZStreamContext *zsc)

{
  uInt uVar1;
  uint uVar2;
  z_streamp z;
  
  if (readErr == 0) {
    uVar1 = zsc->chunkSize;
    z = zsc->ctx;
    z->next_in = zsc->chunkStart;
    z->avail_in = uVar1;
  }
  else {
                    // Deflate all of the bytes that were read
    if (readErr != 0xea) goto LAB_000ea379;
  }
  do {
    while( true ) {
      readErr = ZStreamContext::UpdateAndInflate(zsc);
      zsc->nextReadOffset_ = zsc->bytesRead + zsc->fileOffset;
      if ((readErr == 0) &&
         (readErr = ZStreamContext::RunPostReadCallback(0,fileCtx,zsc), readErr == 0))
      goto LAB_000ea3a0;
      if (readErr != 0x4de) break;
      uVar2 = zsc->nextReadOffset_ - zsc->fileOffset;
      zsc->bytesRead = uVar2;
      if (((int)uVar2 < 0) || (zsc->chunkSize <= (int)uVar2)) goto LAB_000ea381;
    }
  } while (readErr == 0xea);
LAB_000ea379:
  if (readErr == 0x4de) {
LAB_000ea381:
    readErr = ReadAssetFromBNLFile(fileCtx,zsc->nextReadOffset_,zsc);
  }
  if (readErr == 0) {
    return;
  }
  ZStreamContext::RunPostReadCallback(readErr,fileCtx,zsc);
LAB_000ea3a0:
  ZStreamContext::free(zsc);
  return;
}




uint ZStreamContext::UpdateAndInflate(ZStreamContext *zsc)

{
  ZSCStatus ZVar1;
  uint err;
  bool bVar2;
  uLong read_length;
  char *local_4;
  
  ZVar1 = zsc->zscStatus;
  if (ZVar1 == INIT_STATUS) {
    err = CopyBytes(zsc);
  }
  else {
    if ((int)ZVar1 < 1) {
      return 0x4de;
    }
    if (2 < (int)ZVar1) {
      return 0x4de;
    }
    err = Inflate(zsc->ctx,&read_length);
    if ((err == 0) || (err == 0x4de)) {
      zsc->bytesRead = (int)zsc->ctx->next_in - (int)zsc->chunkStart;
    }
  }
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar2 = err == 0;
  }
  else {
    bVar2 = err == 0x4de;
  }
  if (!bVar2) {
    GetErrorById(err,&local_4,(char **)&read_length);
  }
  return err;
}




uint ZStreamContext::CopyBytes(ZStreamContext *zsc)

{
  uint bytes_remaining;
  uint uVar1;
  uint desired_copy_size;
  uint copy_size;
  int *read_ptr;
  int *puVar1;
  
  desired_copy_size = zsc->startOffset - zsc->readHead;
  bytes_remaining = zsc->chunkSize - zsc->bytesRead;
                    // If we're trying to read too many bytes, cap it
  copy_size = desired_copy_size;
  if ((int)bytes_remaining <= (int)desired_copy_size) {
    copy_size = bytes_remaining;
  }
  read_ptr = (int *)(zsc->chunkStart + zsc->bytesRead);
  puVar1 = (int *)((int)zsc->outWriteHead + zsc->readHead);
  for (uVar1 = copy_size >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar1 = *read_ptr;
    read_ptr = read_ptr + 1;
    puVar1 = puVar1 + 1;
  }
  for (uVar1 = copy_size & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(Bytef *)puVar1 = (Bytef)*read_ptr;
    read_ptr = (int *)((int)read_ptr + 1);
    puVar1 = (int *)((int)puVar1 + 1);
  }
  zsc->bytesRead = zsc->bytesRead + copy_size;
  zsc->readHead = zsc->readHead + copy_size;
                    // Return (read_size == desired_size) ? 0x4e3 : 0
  return (copy_size == desired_copy_size) - 1 & 0x4de;
}



uint __fastcall

ZStreamContext::RunPostReadCallback(uint errorId,FileContext *param_2,ZStreamContext *zsc)

{
  int iVar1;
  z_streamp pzVar2;
  uint32_t uVar3;
  Bytef *pBVar4;
  uint uVar5;
  bool bVar6;
  void **local_8;
  char *pcStack_4;
  ZSCStatus *status;
  
  local_8 = &zsc->outWriteHead;
  status = &zsc->zscStatus;
                    // Goes to
                    // 0x00035320
                    // 0x00034470
  uVar5 = (*zsc->postReadCallback)
                    (param_2,errorId,zsc->bytesReadPtr_,&zsc->nextReadOffset_,status,local_8,
                     &zsc->startOffset);
  if (uVar5 == 0x4de) {
    if (*status == New_Name) {
      inflateReset(zsc->ctx);
      uVar5 = zsc->bytesRead;
      iVar1 = zsc->chunkSize;
      pzVar2 = zsc->ctx;
      *status = New_Name_(1);
      pzVar2->next_in = zsc->chunkStart + uVar5;
      pzVar2->avail_in = iVar1 - uVar5;
    }
    uVar3 = zsc->startOffset;
    pBVar4 = *local_8;
    zsc->readHead = 0;
    pzVar2 = zsc->ctx;
    pzVar2->next_out = pBVar4;
    pzVar2->avail_out = uVar3;
    return 0x4de;
  }
  if ((int)uVar5 < 0x3e6) {
    if (0x3e3 < (int)uVar5) {
      return uVar5;
    }
    bVar6 = uVar5 == 0;
  }
  else {
    bVar6 = uVar5 == 0x4de;
  }
  if (!bVar6) {
    GetErrorById(uVar5,&pcStack_4,(char **)&local_8);
  }
  return uVar5;
}




void InitReadCallbacks(void *callback,ReadPtrStruct *arg,ThreadContext *thread)

{
  uint uVar2;
  int iVar3;
  float10 fVar4;
  uint64_t uVar5;
  uint64_t uVar6;
  int local_134;
  LARGE_INTEGER LStack_128;
  undefined4 uStack_120;
  uint uStack_11c;
  int iStack_118;
  uint uStack_114;
  CHAR aCStack_110 [268];
  PRTL_CRITICAL_SECTION CriticalSection;
  HANDLE pvVar1;
  
  iVar3 = 0;
  local_134 = 0;
  fVar4 = (float10)FUN_001077d0();
  uVar5 = float10::to_uint64_t(fVar4 * (float10)1000.0);
  if (thread->threadHandle != (HANDLE)0x0) {
    CriticalSection = &thread->critical_section;
    RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)CriticalSection);
    *(void **)((int)&(thread->critical_section).SpinCount + 4) = callback;
    thread->threadArg = arg;
    thread->field7_0x2c = (HANDLE)0x1;
    RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)CriticalSection);
    XAPILIB::ResumeThread(thread->threadHandle);
    XAPILIB::SwitchToThread();
    do {
      RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)CriticalSection);
      pvVar1 = thread->field7_0x2c;
      RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)CriticalSection);
      if (g_AudioCallbacks != (runAudioCallbacksFn *)0x0) {
        XAPILIB::QueryPerformanceCounter(&LStack_128);
        iStack_118 = LStack_128.s.LowPart - g_PERFORMANCE_COUNTER;
        uVar2 = (LStack_128.s.HighPart - DAT_0050e0dc) -
                (uint)(LStack_128.s.LowPart < g_PERFORMANCE_COUNTER);
        uStack_114 = uVar2 & 0x7fffffff;
        uStack_11c = uVar2 & 0x80000000;
        uStack_120 = 0;
        uVar6 = float10::to_uint64_t
                          (((-(float10)(longlong)(((ulonglong)uVar2 & 0x80000000) << 0x20) +
                            (float10)(CONCAT44(uVar2,iStack_118) & 0x7fffffffffffffff)) /
                           (float10)_g_PERFORMANCE_FREQUENCY) * (float10)-1000.0);
        uVar2 = -(int)uVar6 - iVar3;
        if ((uint)INT_005462d4 <= uVar2) {
          iVar3 = iVar3 + uVar2;
          (*g_AudioCallbacks)();
          local_134 = local_134 + 1;
        }
      }
    } while (pvVar1 != (HANDLE)0x0);
    XAPILIB::SuspendThread(thread->threadHandle);
    fVar4 = (float10)FUN_001077d0();
    uVar6 = float10::to_uint64_t(fVar4 * (float10)-1000.0);
    iVar3 = -(int)uVar6 - (int)uVar5;
    __snprintf(aCStack_110,0x103,"%08d: %s : time = %d ms, syncNotifys = %d\n",iVar3 + (int)uVar5,
               &thread->field12_0x34,iVar3,local_134);
    XAPILIB::OutputDebugStringA(aCStack_110);
    return;
  }
  (*callback)(arg);
  return;
}




DWORD __fastcall FileContext::Update(FileContext *fileCtx)

{
  int iVar2;
  DWORD DVar3;
  DWORD err;
  HeapTableEntry *pHVar4;
  DWORD DVar1;
  int iVar1;
  
  XAPILIB::GetTickCount();
  DVar1 = 0;
  while( true ) {
    iVar1 = fileCtx->fileStatus;
    if (iVar1 == 0) {
      return 0;
    }
    if (iVar1 == 1) {
      err = ProcessLastChunk(fileCtx);
    }
    else if (iVar1 == 2) {
      if (fileCtx->prev != (FileContext *)0x0) {
        fileCtx->prev->next = fileCtx->next;
      }
      if (fileCtx->next != (FileContext *)0x0) {
        fileCtx->next->prev = fileCtx->prev;
      }
      fileCtx->prev = (FileContext *)0x0;
      fileCtx->next = (FileContext *)0x0;
      iVar2 = FindHeapOf(fileCtx);
      iVar1 = runtime::CurrentHeapToAllocateFrom;
      if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
        pHVar4 = (HeapTableEntry *)0x0;
      }
      else {
        pHVar4 = g_HeapTableBase + iVar2;
      }
      runtime::CurrentHeapToAllocateFrom = iVar2;
      XAPILIB::HeapFree(pHVar4->heapHandle,0,fileCtx);
      runtime::CacheContext.field9_0x30 = runtime::CacheContext.field9_0x30 + -1;
      runtime::CurrentHeapToAllocateFrom = iVar1;
      return 0;
    }
    if (((int)err < 0x3e4) || ((0x3e5 < (int)err && (err != 0x4de)))) break;
    if ((g_AudioCallbacks != (runAudioCallbacksFn *)0x0) &&
       (DVar3 = XAPILIB::GetTickCount(), (uint)INT_005462d4 <= DVar3 - DVar1)) {
      DVar1 = XAPILIB::GetTickCount();
      (*g_AudioCallbacks)();
    }
  }
  return err;
}



FILE * CreateFileHandle(ACCESS_MASK desiredAccess,ULONG shareAccess,undefined4 param_3,
                       uint fileDisposition,uint creationFlags,undefined4 param_6,int param_7)

{
  ReadPtrStruct new_file;
  
  new_file.field5_0x14 = param_3;
  new_file.fileDisposition = fileDisposition;
  new_file.creationFlags = creationFlags;
  new_file.desiredAccess = desiredAccess;
  new_file.shareAccess = shareAccess;
  __snprintf(0x506764,260,"CreateFile: File Handle(\"%s\")");
  InitReadCallbacks(InitFileReadPtr,&new_file,&runtime::CacheContext.ioThreadCtx);
  XAPILIB::SetLastError(new_file.lastError);
  return new_file.handle;
}




void InitFileReadPtr(ReadPtrStruct *file)

{
  HANDLE handle;
  char *pcVar1;
  int unaff_FS_OFFSET;
  
  handle = CreateFileForHandle(file->filename,file->desiredAccess,file->shareAccess,
                               (char *)file->field5_0x14,file->fileDisposition,file->creationFlags);
  file->handle = handle;
  pcVar1 = XAPILIB::GetLastError(unaff_FS_OFFSET);
  file->lastError = pcVar1;
  return;
}




undefined4 SetFileContextFilePtr(ULONG param_1,undefined4 param_2,uint param_3,uint param_4)

{
  ReadPtrStruct local_20;
  
  local_20.shareAccess = param_1;
  local_20.field5_0x14 = param_2;
  local_20.fileDisposition = param_3;
  local_20.creationFlags = param_4;
  __snprintf(0x506764,0x104,"SetFilePointerEx: File Handle(0x%08x)");
  InitReadCallbacks(FUN_000eaa60,&local_20,&runtime::CacheContext.ioThreadCtx);
  XAPILIB::SetLastError(local_20.lastError);
  return local_20.handle;
}




void FUN_000eaa60(astruct_21 *filePointer,DWORD moveMethod)

{
  BOOL success;
  char *pcVar1;
  int unaff_FS_OFFSET;
  
  success = XAPILIB::SetFilePointerEx
                      (filePointer->fileHandle,filePointer->moveDistance,filePointer->newFilePointer
                       ,moveMethod);
  filePointer->setFilePointerSuccess = success;
  pcVar1 = XAPILIB::GetLastError(unaff_FS_OFFSET);
  filePointer->lastError = (DWORD)pcVar1;
  return;
}




DWORD FileContext::Create(FileContext **file,char *fileName,uint desiredAccess,uint oops)

{
  char *assetName;
  uint err;
  char *iptr;
  FILE *new_file;
  FileContext *new_ctx;
  int unaff_FS_OFFSET;
  bool bVar1;
  FileContext *fileCtx;
  char c;
  
  assetName = fileName;
  fileCtx = (FileContext *)0x0;
  err = AllocFileContext(&fileCtx);
  new_ctx = fileCtx;
  if (err == 0) {
                    // Copy asset name
    iptr = assetName;
    do {
      c = *iptr;
      iptr[(int)fileCtx + (0xc - (int)assetName)] = c;
      iptr = iptr + 1;
    } while (c != '\0');
  }
  if ((((desiredAccess & FILE_FLAG_OVERLAPPED) != 0) && (oops != 0)) && ((oops < 3 || (oops == 4))))
  {
    err = runtime::CreateFile(assetName);
  }
  if ((char *)err == (char *)0x0) {
    new_file = CreateFileHandle(desiredAccess,7,0,oops,0x60000080,0,oops);
    new_ctx->filePtr = new_file;
    if ((new_file != (FILE *)0xffffffff) ||
       (err = (uint)XAPILIB::GetLastError(unaff_FS_OFFSET), (char *)err == (char *)0x0))
    goto NO_READ_ERRORS;
  }
                    // If there were errors, destroy the file
  if (new_ctx != (FileContext *)0x0) {
    new_ctx->fileStatus = 2;
    if (new_ctx->prev != (FileContext *)0x0) {
      new_ctx->prev->next = new_ctx->next;
    }
    if (new_ctx->next != (FileContext *)0x0) {
      new_ctx->next->prev = new_ctx->prev;
    }
    new_ctx->prev = (FileContext *)0x0;
    new_ctx->next = (FileContext *)0x0;
    free(new_ctx);
    runtime::CacheContext.field9_0x30 = runtime::CacheContext.field9_0x30 + -1;
    new_ctx = (FileContext *)0x0;
  }
NO_READ_ERRORS:
  *file = new_ctx;
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return (DWORD)(char *)err;
    }
    bVar1 = (char *)err == (char *)0x0;
  }
  else {
    bVar1 = (char *)err == (char *)0x4de;
  }
  if (!bVar1) {
    GetErrorById(err,(char **)&file,(char **)&desiredAccess);
  }
  return (DWORD)(char *)err;
}




DWORD FileContext::CloseInner(FileContext *fileCtx)

{
  BOOL BVar1;
  char *err;
  int unaff_FS_OFFSET;
  bool bVar2;
  char *local_8;
  char *local_4;
  
  if (fileCtx->filePtr == (FILE *)0xffffffff) {
    return 0;
  }
  BVar1 = XAPILIB::CloseHandle(fileCtx->filePtr);
  if (BVar1 != 0) {
    fileCtx->filePtr = (FILE *)0xffffffff;
    fileCtx->fileStatus = 0;
    return 0;
  }
  err = XAPILIB::GetLastError(unaff_FS_OFFSET);
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return (DWORD)err;
    }
    bVar2 = err == (char *)0x0;
  }
  else {
    bVar2 = err == (char *)0x4de;
  }
  if (bVar2) {
    return (DWORD)err;
  }
  GetErrorById((uint)err,&local_4,&local_8);
  return (DWORD)err;
}




DWORD FileContext::Close(FileContext *fileCtx)

{
  DWORD err;
  bool bVar1;
  char *local_8;
  char *local_4;
  
  err = CloseInner(fileCtx);
  if (err == 0) {
    fileCtx->fileStatus = 2;
    return 0;
  }
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar1 = err == 0;
  }
  else {
    bVar1 = err == 0x4de;
  }
  if (!bVar1) {
    GetErrorById(err,&local_4,&local_8);
  }
  return err;
}




uint runtime::CreateFile(char *assetName)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint id;
  bool bVar4;
  char *local_10c;
  char *local_108;
  char name [260];
  
  iVar2 = -(int)assetName;
  do {
    cVar1 = *assetName;
    assetName[(int)(name + iVar2)] = cVar1;
    assetName = assetName + 1;
  } while (cVar1 != '\0');
  pcVar3 = _strrchr(name,L'\\');
  if (pcVar3 == (char *)0x0) {
    id = 0xf;
  }
  else {
    *pcVar3 = '\0';
    id = CreateFileInner(name);
    if ((int)id < 0x3e6) {
      if (0x3e3 < (int)id) {
        return id;
      }
      bVar4 = id == 0;
    }
    else {
      bVar4 = id == 0x4de;
    }
    if (bVar4) {
      return id;
    }
  }
  GetErrorById(id,&local_10c,&local_108);
  return id;
}




char * runtime::CreateFileInner(char *param_1)

{
  uint uVar1;
  char *pcVar2;
  BOOL BVar3;
  int iVar4;
  char *pcVar5;
  int unaff_FS_OFFSET;
  bool bVar6;
  char *local_4;
  char *filepath;
  
  filepath = param_1;
  iVar4 = 2;
  bVar6 = true;
  pcVar2 = ":";
  pcVar5 = param_1;
  do {
    pcVar5 = pcVar5 + 1;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pcVar5 == *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (bVar6);
  if (bVar6) {
    return (char *)0x0;
  }
  uVar1 = QueryFile(param_1);
  if (uVar1 == 0xffffffff) {
    pcVar5 = XAPILIB::GetLastError(unaff_FS_OFFSET);
  }
  else {
    pcVar5 = (char *)((-(uint)((uVar1 & 0x10) != 0) & 0xffffff49) + 0xb7);
  }
  if (pcVar5 == (char *)0x3) {
    pcVar2 = _strrchr(filepath,0x5c);
    *pcVar2 = '\0';
    pcVar5 = (char *)CreateFileInner(filepath);
    *pcVar2 = '\\';
    if (pcVar5 != (char *)0x0) goto LAB_000ead68;
  }
  else {
LAB_000ead68:
    if (pcVar5 != (char *)0x2) goto LAB_000ead89;
  }
  BVar3 = CreateFile(filepath);
  if (BVar3 != 0) {
    return (char *)0x0;
  }
  pcVar5 = XAPILIB::GetLastError(unaff_FS_OFFSET);
LAB_000ead89:
  if ((int)pcVar5 < 0x3e6) {
    if (0x3e3 < (int)pcVar5) {
      return pcVar5;
    }
    bVar6 = pcVar5 == (char *)0x0;
  }
  else {
    bVar6 = pcVar5 == (char *)0x4de;
  }
  if (!bVar6) {
    GetErrorById((uint)pcVar5,&local_4,&param_1);
  }
  return pcVar5;
}




char * setFilePointer(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  char *id;
  int unaff_FS_OFFSET;
  bool bVar2;
  char *local_8;
  char *local_4;
  
  id = (char *)0x0;
  iVar1 = SetFileContextFilePtr(param_1,param_2,0,0);
  if (iVar1 == 0) {
    id = XAPILIB::GetLastError(unaff_FS_OFFSET);
    if ((int)id < 0x3e6) {
      if (0x3e3 < (int)id) {
        return id;
      }
      bVar2 = id == (char *)0x0;
    }
    else {
      bVar2 = id == (char *)0x4de;
    }
    if (!bVar2) {
      GetErrorById((uint)id,&local_4,&local_8);
    }
  }
  return id;
}




DWORD __thiscall FileContext::GetFileSizeInner(FileContext *this,LARGE_INTEGER *endOfFile)

{
  BOOL BVar1;
  char *err;
  int unaff_FS_OFFSET;
  bool bVar2;
  char *local_8;
  char *local_4;
  
  err = (char *)0x0;
  BVar1 = XAPILIB::GetFileSizeEx(this->filePtr,endOfFile);
  if (BVar1 == 0) {
    err = XAPILIB::GetLastError(unaff_FS_OFFSET);
    if ((int)err < 0x3e6) {
      if (0x3e3 < (int)err) {
        return (DWORD)err;
      }
      bVar2 = err == (char *)0x0;
    }
    else {
      bVar2 = err == (char *)0x4de;
    }
    if (!bVar2) {
      GetErrorById((uint)err,&local_4,&local_8);
    }
  }
  return (DWORD)err;
}




DWORD __thiscall FileContext::GetFileSizeOuter(FileContext *this,FileSizeBlock fsb)

{
  DWORD err;
  bool error_occurred;
  char *local_10;
  char *local_c;
  LARGE_INTEGER size;
  
  err = GetFileSizeInner(this,&size);
  if (err == 0) {
    *(DWORD *)fsb.bigStruct = size.s.LowPart;
    if (size.s.HighPart == 0) {
      return 0;
    }
    err = 1;
  }
  else {
    if ((int)err < 0x3e6) {
      if (0x3e3 < (int)err) {
        return err;
      }
      error_occurred = err == 0;
    }
    else {
      error_occurred = err == 0x4de;
    }
    if (error_occurred) {
      return err;
    }
  }
  GetErrorById(err,&local_c,&local_10);
  return err;
}




char * runtime::ReadFileContexts(FileContext *file1,FileContext *file2,void *param_3)

{
  FileContext *pFVar1;
  char *err;
  BOOL BVar2;
  int offset;
  int unaff_FS_OFFSET;
  bool bVar3;
  char *local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pFVar1 = file2;
  err = (char *)AlignZStream_(file1,(ulong)file2,(int *)&local_c);
  offset = (int)param_3 + (uint)CARRY4((int)local_c - (int)pFVar1,(uint)pFVar1);
  if ((((err == (char *)0x0) && (err = (char *)FUN_000eadc0(file1), err == (char *)0x0)) &&
      (err = (char *)setFilePointer(((int)local_c - (int)pFVar1) + (int)pFVar1,offset),
      err == (char *)0x0)) &&
     ((BVar2 = XAPILIB::SetEndOfFile(file1->filePtr), BVar2 != 0 ||
      (err = XAPILIB::GetLastError(unaff_FS_OFFSET), err == (char *)0x0)))) {
    err = (char *)setFilePointer(local_8,local_4);
  }
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar3 = err == (char *)0x0;
  }
  else {
    bVar3 = err == (char *)0x4de;
  }
  if (!bVar3) {
    GetErrorById((uint)err,&local_c,(char **)&file2);
  }
  return err;
}




uint __fastcall runtime::TryReadFileContexts(FileContext *param_1,FileContext *param_2)

{
  uint err;
  bool bVar1;
  FileContext *local_4;
  
  local_4 = param_1;
  err = ReadFileContexts(param_1,param_2,(void *)0x0);
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar1 = err == 0;
  }
  else {
    bVar1 = err == 0x4de;
  }
  if (!bVar1) {
    GetErrorById(err,(char **)&local_4,(char **)&param_2);
  }
  return err;
}




uint FileContext::GetSomething(FileContext *fileCtx,char **outName)

{
  uint size;
  char *err;
  int iVar1;
  int unaff_FS_OFFSET;
  bool bVar2;
  char firstChars [4];
  char *local_4;
  
  err = (char *)0x0;
  XAPILIB::lstrcpynA(firstChars,fileCtx->assetName,4);
                    // To uppercase
  if (0x60 < firstChars[0]) {
    firstChars[0] = firstChars[0] + -0x20;
  }
  iVar1 = (int)firstChars[0];
  if ((&runtime::CacheContext.ioThreadCtx.field12_0x34)[iVar1] == (HANDLE)0x0) {
    size = System__GetSizeOfFile(firstChars);
    (&runtime::CacheContext.ioThreadCtx.field12_0x34)[iVar1] = (HANDLE)size;
    if (size == 0) {
      err = XAPILIB::GetLastError(unaff_FS_OFFSET);
    }
  }
  *outName = (&runtime::CacheContext.ioThreadCtx.field12_0x34)[iVar1];
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return (uint)err;
    }
    bVar2 = err == (char *)0x0;
  }
  else {
    bVar2 = err == (char *)0x4de;
  }
  if (!bVar2) {
    GetErrorById((uint)err,&local_4,(char **)&outName);
  }
  return (uint)err;
}



uint ReadNBytesOfFile(LPVOID bytes,DWORD readSize,void *onReadCallback,ZStreamContext *zsc,
                     FileContext *fileCtx)

{
  DWORD err;
  BOOL success;
  int unaff_FS_OFFSET;
  bool bVar1;
  char *local_8;
  char *local_4;
  
  err = FileContext::Update(fileCtx);
  if (err == 0) {
    fileCtx->onReadCallback = onReadCallback;
    fileCtx->zStreamContext = zsc;
    success = XAPILIB::ReadFile(fileCtx->filePtr,bytes,readSize,(LPDWORD)0x0,
                                (LPOVERLAPPED)&fileCtx->overlapped);
    if (success == 0) {
      err = (DWORD)XAPILIB::GetLastError(unaff_FS_OFFSET);
      if ((char *)err == (char *)0x3e5) {
        err = 0;
      }
      else if ((char *)err != (char *)0x0) goto LAB_000eb14c;
    }
    runtime::CacheContext.field10_0x34 = runtime::CacheContext.field10_0x34 + 1;
    fileCtx->fileStatus = 1;
  }
LAB_000eb14c:
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return (uint)(char *)err;
    }
    bVar1 = (char *)err == (char *)0x0;
  }
  else {
    bVar1 = (char *)err == (char *)0x4de;
  }
  if (!bVar1) {
    GetErrorById(err,&local_4,&local_8);
  }
  return (uint)(char *)err;
}




char * FUN_000eb180(LPCVOID param_1,DWORD param_2,void *param_3,ZStreamContext *param_4)

{
  FileContext *in_EAX;
  char *id;
  BOOL BVar1;
  int unaff_FS_OFFSET;
  bool bVar2;
  char *local_8;
  char *local_4;
  
  id = (char *)FileContext::Update(in_EAX);
  if (id == (char *)0x0) {
    in_EAX->onReadCallback = param_3;
    in_EAX->zStreamContext = param_4;
    BVar1 = XAPILIB::WriteFile(in_EAX->filePtr,param_1,param_2,(LPDWORD)0x0,
                               (LPOVERLAPPED)&in_EAX->overlapped);
    if (BVar1 == 0) {
      id = XAPILIB::GetLastError(unaff_FS_OFFSET);
      if (id == (char *)0x3e5) {
        id = (char *)0x0;
      }
      else if (id != (char *)0x0) goto LAB_000eb1ec;
    }
    runtime::CacheContext.field10_0x34 = runtime::CacheContext.field10_0x34 + 1;
    in_EAX->fileStatus = 1;
  }
LAB_000eb1ec:
  if ((int)id < 0x3e6) {
    if (0x3e3 < (int)id) {
      return id;
    }
    bVar2 = id == (char *)0x0;
  }
  else {
    bVar2 = id == (char *)0x4de;
  }
  if (!bVar2) {
    GetErrorById((uint)id,&local_4,&local_8);
  }
  return id;
}




uint runtime::AlignZStream_(FileContext *param_1,ulong param_2,int *param_3)

{
  uint err;
  int iVar1;
  bool bVar2;
  char *unit_size;
  char *local_4;
  
  err = FileContext::GetSomething(param_1,&unit_size);
  if (err == 0) {
    iVar1 = (int)param_2 % (int)unit_size;
    if (iVar1 < 1) {
      if (iVar1 < 0) {
        param_2 = param_2 - iVar1;
      }
      *param_3 = param_2;
      return 0;
    }
    *param_3 = (int)(unit_size + (param_2 - iVar1));
    return 0;
  }
  if ((int)err < 0x3e6) {
    if (0x3e3 < (int)err) {
      return err;
    }
    bVar2 = err == 0;
  }
  else {
    bVar2 = err == 0x4de;
  }
  if (!bVar2) {
    GetErrorById(err,&local_4,&unit_size);
  }
  return err;
}




uint runtime::AlignFileContextOffsets2_(FileContext *param_1,ZStreamContext *param_2,int param_3)

{
  uint id;
  int iVar1;
  bool bVar2;
  char *local_8;
  char *local_4;
  
  id = FileContext::GetSomething(param_1,&local_8);
  if (id == 0) {
    iVar1 = param_3 % (int)local_8;
    if (iVar1 < 1) {
      if (iVar1 < 0) {
        param_3 = (param_3 - iVar1) - (int)local_8;
      }
      param_2->fileOffset = param_3;
      return 0;
    }
    param_2->fileOffset = param_3 - iVar1;
    return 0;
  }
  if ((int)id < 0x3e6) {
    if (0x3e3 < (int)id) {
      return id;
    }
    bVar2 = id == 0;
  }
  else {
    bVar2 = id == 0x4de;
  }
  if (!bVar2) {
    GetErrorById(id,&local_4,&local_8);
  }
  return id;
}




uint newZStreamContext(z_streamp *zstreamOut)

{
  z_streamp z;
  int iVar1;
  uint err;
  bool bVar2;
  char *local_4;
  
  err = 0;
  z = malloc_(56);
  if (z == (z_streamp)0x0) {
    err = 8;
  }
  else {
    z->zalloc = zstreamMalloc;
    z->zfree = zStreamFree;
    z->opaque = (voidpf)0x0;
    z->next_in = (Bytef *)0x0;
    z->avail_in = 0;
    iVar1 = inflateInit(z,"1.1.3",56);
    if (iVar1 != Z_OK) {
      err = 8;
      zStreamFree(0,z);
    }
  }
  *zstreamOut = z;
  if (err < 0x3e6) {
    if (0x3e3 < err) {
      return err;
    }
    bVar2 = err == 0;
  }
  else {
    bVar2 = err == 0x4de;
  }
  if (!bVar2) {
    GetErrorById(err,&local_4,(char **)&zstreamOut);
  }
  return err;
}




int __fastcall ZStreamContext::Inflate(z_stream *z,uLong *readLength)

{
  int status;
  char *local_8;
  char *local_4;
  
  status = inflate(z,Z_SYNC_FLUSH);
  if (readLength != (uLong *)0x0) {
    *readLength = 0;
  }
  if (status != Z_OK) {
    if (status != Z_STREAM_END) {
      GetErrorById(0xd,&local_4,&local_8);
      return 0xd;
    }
    if (readLength != (uLong *)0x0) {
      *readLength = z->total_out;
    }
    return 0;
  }
  if (z->avail_out == 0) {
    if (readLength != (uLong *)0x0) {
      *readLength = z->total_out;
    }
    return 0;
  }
  return 0x4de;
}




void runtime::EndZSInflate(z_stream *param_1)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  inflateEnd(param_1);
  iVar2 = FindHeapOf(param_1);
  uVar1 = CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,param_1);
  CurrentHeapToAllocateFrom = uVar1;
  return;
}




void * zstreamMalloc(undefined4 param_1,int param_2,int param_3)

{
  void *pvVar1;
  
  pvVar1 = malloc_(param_2 * param_3);
  return pvVar1;
}




void zStreamFree(undefined4 param_1,void *param_2)

{
  undefined4 uVar1;
  int iVar2;
  HeapTableEntry *pHVar3;
  
  iVar2 = FindHeapOf(param_2);
  uVar1 = runtime::CurrentHeapToAllocateFrom;
  if (g_HeapTableBase[iVar2].heapHandle == (HANDLE)0x0) {
    pHVar3 = (HeapTableEntry *)0x0;
  }
  else {
    pHVar3 = g_HeapTableBase + iVar2;
  }
  runtime::CurrentHeapToAllocateFrom = iVar2;
  XAPILIB::HeapFree(pHVar3->heapHandle,0,param_2);
  runtime::CurrentHeapToAllocateFrom = uVar1;
  return;
}




char * GetNextNonEmptyLine(char **something,int start,int end)

{
  char cVar1;
  char *pcVar2;
  char *current;
  char *pcVar3;
  
  do {
    do {
      current = *something;
      pcVar2 = current;
      if (end <= (int)current - start) {
        return (char *)0x0;
      }
      cVar1 = *current;
                    // Skip to next newline
      while ((cVar1 != '\0' && (pcVar3 = *something, *pcVar3 != '\n'))) {
        if (end <= (int)pcVar3 - start) {
          return (char *)0x0;
        }
        *something = pcVar3 + 1;
        cVar1 = pcVar3[1];
      }
                    // Fine the CRLF and blank them both out
      if (**something == '\n') {
        **something = '\0';
        (*something)[-1] = '\0';
      }
      pcVar3 = *something + 1;
      *something = pcVar3;
    } while (*current == '#');
    if (current < pcVar3) {
      do {
        if (' ' < *current) break;
        current = current + 1;
      } while (current < *something);
    }
    if (current != pcVar3) {
      return pcVar2;
    }
  } while( true );
}




char * __fastcall GetNextMoviePath(char *name)

{
  uint32_t id;
  uint uVar1;
  char *pcVar2;
  char *unaff_ESI;
  char *unaff_EDI;
  int unaff_FS_OFFSET;
  char *in_stack_ffffff78;
  char *local_84;
  char local_80 [128];
  
  if ((runtime::Config::IsPal != 0) && (runtime::Config::Use60Hz == 0)) {
                    // Prepends pal with name
    Utils::SprintfToUpper(local_80,"%spal",name,unaff_EDI,unaff_ESI,in_stack_ffffff78);
    id = Assets::GetNameHash(local_80);
    _sprintf(&g_drawingData[0xf].field_0x13,"%s%s%08x",runtime::RootDirectory,"movie\\",id);
    uVar1 = QueryFile(&g_drawingData[0xf].field_0x13);
    if (uVar1 == 0xffffffff) {
      pcVar2 = XAPILIB::GetLastError(unaff_FS_OFFSET);
    }
    else {
      pcVar2 = (char *)(-(uint)((uVar1 & 0x10) != 0) & 0x10b);
    }
    if (pcVar2 == (char *)0x0) goto LAB_00106f91;
  }
  id = Assets::GetNameHash(name);
  _sprintf(&g_drawingData[0xf].field_0x13,"%s%s%08x",runtime::RootDirectory,"movie\\",id);
LAB_00106f91:
  uVar1 = QueryFile(&g_drawingData[0xf].field_0x13);
  if (uVar1 == 0xffffffff) {
    pcVar2 = XAPILIB::GetLastError(unaff_FS_OFFSET);
  }
  else {
    pcVar2 = (char *)(-(uint)((uVar1 & 0x10) != 0) & 0x10b);
  }
  if (pcVar2 != (char *)0x0) {
    GetErrorById((uint)pcVar2,(char **)&stack0xffffff78,&local_84);
    runtime::ExitGame((int)pcVar2);
  }
  return &g_drawingData[0xf].field_0x13;
}




DWORD CloseMovieForReading(FileContext *fileCtx,char *movie,AllocatedMovie *param_3)

{
  char *err;
  char *local_4;
  AllocatedMovie *moviePtr;
  
  err = movie;
  if (movie != (char *)0x0) {
    GetErrorById((uint)movie,&local_4,&movie);
    runtime::ExitGame((int)err);
  }
  moviePtr = param_3;
  FileContext::Close(param_3->fileCtx);
  moviePtr->fileCtxClosed = 1;
  err = (char *)0x0;
  if (moviePtr->closeStatusCode != 0) {
    err = moviePtr->errorCode;
    g_MovieErrorCode = err;
  }
  return (DWORD)err;
}




int __fastcall CreateNewMovie(char *fileContents,AllocatedMovie *movie,char *name)

{
  FileContext **file;
  FileSizeBlock fsb;
  BOOL isLogoScaleUp;
  int status;
  DWORD err;
  void *pvVar1;
  char *pcVar2;
  uint uVar3;
  uint unaff_EBX;
  undefined4 uVar4;
  char *n;
  char *local_4;
  
  isLogoScaleUp = Assets::AssetNamesMatch("aid_movie_ghoulies_attractmode_logoscaleup",name);
  movie->closeStatusCode = isLogoScaleUp;
  pcVar2 = g_MovieErrorCode;
  if ((isLogoScaleUp != 0) && (g_MovieErrorCode != (char *)0x0)) {
    movie->fileCtx = (FileContext *)0x0;
    movie->errorCode = pcVar2;
    movie->fileCtxClosed = 1;
    return 0;
  }
  if ((movie->flags & 0b00010000) == 0) {
    status = GetNextMovieChunk(fileContents,movie->readFlags);
    movie->lastChunk = status;
    if (status == 0) {
      GetErrorById(0x6e,&local_4,&n);
      runtime::ExitGame(0x6e);
      return 0x6e;
    }
    FUN_001a7b70(status,0,0x4000);
    movie->fileCtx = (FileContext *)0x0;
    movie->errorCode = (char *)0x0;
    movie->fileCtxClosed = 1;
    return 0;
  }
  file = &movie->fileCtx;
  err = FileContext::Create(file,fileContents,0b10000000000000000000000000000000,3);
  if (err != 0) {
    GetErrorById(err,&n,&local_4);
    runtime::ExitGame(err);
    return err;
  }
  fsb.field1_0x4 = unaff_EBX;
  fsb.bigStruct = (DWORD)&n;
  err = FileContext::GetFileSizeOuter(*file,fsb);
  if (err == 0) {
    runtime::AlignZStream_(*file,(ulong)n,(int *)&n);
    uVar4 = 0;
    pcVar2 = n;
    pvVar1 = FUN_0014d377();
    pcVar2 = (char *)runtime::AllocateOnHeap(pvVar1,uVar4,pcVar2);
    movie->errorCode = pcVar2;
    if (pcVar2 == (char *)0x0) {
      return 14;
    }
    uVar3 = ReadNBytesOfFile(pcVar2,n,CloseMovieForReading,(ZStreamContext *)movie,*file);
    if (uVar3 == 0) {
      movie->fileCtxClosed = 0;
      return 0;
    }
    FUN_00107400(movie->errorCode);
  }
  status = FUN_001074a0();
  return status;
}




AllocatedMovie * LoadMovie(char *name,uint flags)

{
  char *moviePath;
  AllocatedMovie *new_movie;
  BOOL err;
  AllocatedMovie *old_tail;
  AllocatedMovie **head;
  uint uVar1;
  
  uVar1 = 0x100000;
  if (g_PushBufferValid == 0) {
    g_MovieListSentinel = 0;
    g_MovieListHead = (AllocatedMovie *)0x0;
    D3D8::D3D_SetPushBufferSize(0x1073e0,0x107400);
    g_PushBufferValid = 1;
  }
  moviePath = GetNextMoviePath(name);
  if (moviePath == (char *)0x0) {
    return (AllocatedMovie *)0x0;
  }
  if ((flags & 8) != 0) {
    uVar1 = 0x40100000;
  }
  new_movie = malloc_(60);
  new_movie->field5_0x14 = flags >> 2 & 1;
  new_movie->flags = flags;
  new_movie->flag2IsSet = 0;
  new_movie->field7_0x1c = 0;
  new_movie->field8_0x20 = 0;
  new_movie->field9_0x24 = 1;
  new_movie->lastChunk = 0;
  new_movie->readFlags = uVar1;
  new_movie->fileCtx = (FileContext *)0x0;
  new_movie->errorCode = (char *)0x0;
  new_movie->fileCtxClosed = 0;
  err = CreateNewMovie(moviePath,new_movie,name);
  if (err != 0) {
    if (new_movie->fileCtx != (FileContext *)0x0) {
      FileContext::Close(new_movie->fileCtx);
    }
    free(new_movie);
    return (AllocatedMovie *)0x0;
  }
                    // Mark movie as loaded
  new_movie->readFlags = uVar1 | 0x4000000;
  new_movie->field10_0x28 = 0;
  old_tail = (AllocatedMovie *)&g_MovieListSentinel;
                    // Go to the end of the movie list
  if (g_MovieListHead != (AllocatedMovie *)0x0) {
    head = &g_MovieListHead;
    do {
      old_tail = *head;
      head = (AllocatedMovie **)&((FileContext *)old_tail)->next;
    } while (((FileContext *)old_tail)->next != (FileContext *)0x0);
  }
  old_tail->nextMovie = (FileContext *)new_movie;
  new_movie->prevMovie = old_tail;
  new_movie->nextMovie = (FileContext *)0x0;
  if ((flags & 0b00000010) != 0) {
    new_movie->flag2IsSet = new_movie->flag2IsSet + 1;
  }
  return new_movie;
}




void AllocatedMovie::MustRead__(AllocatedMovie *movie)

{
  int iVar1;
  
  if ((movie->fileCtxClosed != 0) && (movie->field10_0x28 == 0)) {
    if (movie->lastChunk == 0) {
      iVar1 = GetNextMovieChunk(movie->errorCode,movie->readFlags);
      movie->lastChunk = iVar1;
      if (iVar1 == 0) {
        movie->field10_0x28 = 1;
        return;
      }
    }
    iVar1 = FUN_001a7870(movie->lastChunk);
    if ((iVar1 == 0) && (0 < movie->flag2IsSet)) {
      FUN_001a7d40(movie->lastChunk);
      movie->field7_0x1c = 1;
      if ((movie->field5_0x14 != 0) ||
         (*(uint *)(movie->lastChunk + 0xc) < *(uint *)(movie->lastChunk + 8))) {
        movie->field8_0x20 = movie->field8_0x20 + 1;
        FUN_001a8350(movie->lastChunk);
      }
    }
  }
  return;
}




BOOL __fastcall FUN_001460c0(bodyCollisionProfile *param_1)

{
  int iVar1;
  
  if ((param_1->field2367_0x93f != '\x01') &&
     ((param_1->field2367_0x93f != '\x02' ||
      ((iVar1 = param_1->field3468_0xd8c, iVar1 != 0 &&
       ((*(short *)(iVar1 + 0xcdc) == 2 || (*(int *)(iVar1 + 0x93c) != 0)))))))) {
    return 0;
  }
  return 1;
}




BOOL __fastcall FUN_00146100(bodyCollisionProfile *param_1)

{
  int iVar1;
  
  if ((param_1->field2367_0x93f != '\x01') &&
     ((param_1->field2367_0x93f != '\x02' ||
      ((iVar1 = param_1->field3468_0xd8c, iVar1 != 0 &&
       ((*(short *)(iVar1 + 0xcdc) == 2 || (*(int *)(iVar1 + 0x93c) != 0)))))))) {
    return (uint)(param_1->field2369_0x941 == '\0');
  }
  return 0;
}




void FUN_0014b0b6(int param_1,FILE_DIRECTORY_INFORMATION *param_2)

{
  uint uVar1;
  uint uVar2;
  LONG *pLVar3;
  LONG *pLVar4;
  
  param_2->NextEntryOffset = *(ULONG *)(param_1 + 0x38);
  param_2->FileIndex = *(ULONG *)(param_1 + 8);
  (param_2->CreationTime).s.LowPart = *(DWORD *)(param_1 + 0xc);
  (param_2->CreationTime).s.HighPart = *(LONG *)(param_1 + 0x10);
  (param_2->LastAccessTime).s.LowPart = *(DWORD *)(param_1 + 0x14);
  (param_2->LastAccessTime).s.HighPart = *(LONG *)(param_1 + 0x18);
  (param_2->LastWriteTime).s.LowPart = *(DWORD *)(param_1 + 0x1c);
  (param_2->LastWriteTime).s.HighPart = *(LONG *)(param_1 + 0x2c);
  (param_2->ChangeTime).s.LowPart = *(DWORD *)(param_1 + 0x28);
  uVar2 = *(uint *)(param_1 + 0x3c);
  pLVar3 = (LONG *)(param_1 + 0x40);
  pLVar4 = &(param_2->EndOfFile).s.HighPart;
  for (uVar1 = uVar2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pLVar4 = *pLVar3;
    pLVar3 = pLVar3 + 1;
    pLVar4 = pLVar4 + 1;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(char *)pLVar4 = (char)*pLVar3;
    pLVar3 = (LONG *)((int)pLVar3 + 1);
    pLVar4 = (LONG *)((int)pLVar4 + 1);
  }
  *(undefined1 *)((int)&param_2->EndOfFile + *(int *)(param_1 + 0x3c) + 4) = 0;
  *(undefined1 *)&param_2[4].EndOfFile = 0;
  return;
}




HANDLE System__OpenDirectory(PCSZ param_1,FILE_DIRECTORY_INFORMATION *outData)

{
  USHORT UVar1;
  uint uVar2;
  DWORD dwErrCode;
  undefined1 local_170 [328];
  _IO_STATUS_BLOCK local_28;
  _OBJECT_ATTRIBUTES local_20;
  STRING local_14;
  STRING local_c;
  
  RtlInitAnsiString(&local_c,param_1);
  local_20.ObjectName = &local_c;
  local_20.RootDirectory = (HANDLE)0xfffffffd;
  local_20.Attributes = 0x40;
  for (uVar2 = local_c._0_4_ & 0xffff; (uVar2 != 0 && (local_c.Buffer[uVar2 - 1] != '\\'));
      uVar2 = uVar2 - 1) {
  }
  UVar1 = (USHORT)uVar2;
  local_14.MaximumLength = local_c.Length - UVar1;
  local_14.Buffer = local_c.Buffer + uVar2;
  local_c.MaximumLength = UVar1;
  local_c.Length = UVar1;
  local_14.Length = local_14.MaximumLength;
  if ((UVar1 == 0) || (local_14.MaximumLength == 0)) {
    XAPILIB::SetLastError(0x57);
  }
  else {
    if ((((local_14.MaximumLength == 3) && (*local_14.Buffer == '*')) && (local_14.Buffer[1] == '.')
        ) && (local_14.Buffer[2] == '*')) {
      local_14.Length = 0;
    }
    dwErrCode = NtOpenFile(&param_1,0x100001,&local_20,&local_28,3,0x4021);
    if (-1 < (int)dwErrCode) {
      dwErrCode = NtQueryDirectoryFile
                            (param_1,(HANDLE)0x0,(PIO_APC_ROUTINE)0x0,(PVOID)0x0,&local_28,local_170
                             ,0x148,FileDirectoryInformation,&local_14,'\0');
      if (-1 < (int)dwErrCode) {
        FUN_0014b0b6(local_170,outData);
        return param_1;
      }
      NtClose(param_1);
    }
    XAPILIB::XapiSetLastNTError(dwErrCode);
  }
  return (HANDLE)0xffffffff;
}




bool FUN_0014b22f(HANDLE param_1,FILE_DIRECTORY_INFORMATION *param_2)

{
  DWORD dwErrCode;
  undefined1 local_154 [328];
  _IO_STATUS_BLOCK local_c;
  
  dwErrCode = NtQueryDirectoryFile
                        (param_1,(HANDLE)0x0,(PIO_APC_ROUTINE)0x0,(PVOID)0x0,&local_c,local_154,
                         0x148,FileDirectoryInformation,(POBJECT_STRING)0x0,'\0');
  if (-1 < (int)dwErrCode) {
    FUN_0014b0b6(local_154,param_2);
  }
  else {
    XAPILIB::XapiSetLastNTError(dwErrCode);
  }
  return -1 < (int)dwErrCode;
}



// WARNING: Variable defined which should be unmapped: object_attributes


uint QueryFile(char *filePath)

{
  DWORD status;
  _FILE_NETWORK_OPEN_INFORMATION attributes;
  OBJECT_ATTRIBUTES object_attributes;
  
  RtlInitAnsiString((PANSI_STRING)&object_attributes.Attributes,filePath);
  object_attributes.RootDirectory = &object_attributes.Attributes;
  object_attributes.Length = 0xfffffffd;
  object_attributes.ObjectName = (PUNICODE_STRING)0x40;
  status = NtQueryFullAttributesFile((POBJECT_ATTRIBUTES)&object_attributes,&attributes);
  if ((int)status < 0) {
    XAPILIB::XapiSetLastNTError(status);
    attributes.FileAttributes = 0xffffffff;
  }
  return attributes.FileAttributes;
}




bool runtime::MarkForDeletion(char *filename)

{
  bool success;
  DWORD err;
  OBJECT_ATTRIBUTES attribs;
  HANDLE handle;
  
  RtlInitAnsiString((PANSI_STRING)&attribs.SecurityQualityOfService,filename);
  attribs.RootDirectory = &attribs.SecurityQualityOfService;
  attribs.Length = 0xfffffffd;
  attribs.ObjectName = (PUNICODE_STRING)0x40;
  err = NtOpenFile(&handle,DELETE,(POBJECT_ATTRIBUTES)&attribs,(PIO_STATUS_BLOCK)&attribs.Attributes
                   ,7,0x4040);
  if ((int)err < 0) {
    XAPILIB::XapiSetLastNTError(err);
    success = false;
  }
  else {
    filename = (char *)CONCAT13(1,filename._0_3_);
    err = NtSetInformationFile
                    (handle,(PIO_STATUS_BLOCK)&attribs.Attributes,(PVOID)((int)&filename + 3),1,
                     FileDispositionInformation);
    NtClose(handle);
    if ((int)err < 0) {
      XAPILIB::XapiSetLastNTError(err);
    }
    success = (int)err >= 0;
  }
  return success;
}




uint System__GetSizeOfFile(char *filename)

{
  DWORD DVar1;
  char *pcVar2;
  int unaff_FS_OFFSET;
  undefined1 local_38 [20];
  uint size;
  _OBJECT_ATTRIBUTES local_20;
  _IO_STATUS_BLOCK local_14;
  STRING local_c;
  
  RtlInitAnsiString(&local_c,filename);
  local_20.ObjectName = &local_c;
  local_20.RootDirectory = (HANDLE)0xfffffffd;
  local_20.Attributes = 0x40;
  DVar1 = NtOpenFile(&filename,0x100001,&local_20,&local_14,3,0x800021);
  if ((int)DVar1 < 0) {
    XAPILIB::XapiSetLastNTError(DVar1);
    pcVar2 = XAPILIB::GetLastError(unaff_FS_OFFSET);
    if (pcVar2 == (char *)0x2) {
      XAPILIB::SetLastError(3);
    }
    size = 0;
  }
  else {
    DVar1 = NtQueryVolumeInformationFile(filename,&local_14,local_38,0x18,FileFsSizeInformation);
    NtClose(filename);
    if ((int)DVar1 < 0) {
      XAPILIB::XapiSetLastNTError(DVar1);
      size = 0;
    }
  }
  return size;
}



// WARNING: Unable to use type for symbol uVar1


BOOL runtime::CreateFile(PCSZ path)

{
  DWORD dwErrCode;
  _OBJECT_ATTRIBUTES local_20;
  _IO_STATUS_BLOCK local_14;
  STRING local_c;
  
  RtlInitAnsiString(&local_c,path);
  local_20.ObjectName = &local_c;
  local_20.RootDirectory = (HANDLE)0xfffffffd;
  local_20.Attributes = 0x40;
  dwErrCode = NtCreateFile(&path,0x100001,&local_20,&local_14,(PLARGE_INTEGER)0x0,0x80,3,2,0x4021);
  if ((int)dwErrCode < 0) {
    XAPILIB::XapiSetLastNTError(dwErrCode);
  }
  else {
    NtClose(path);
  }
  return (uint)((int)dwErrCode >= 0);
}




void GetNextNameTable(void *param_1,NamedCallbackTable **table)

{
  *table = param_1;
  *(int *)param_1 = (int)param_1 + 8;
  (*table)->count = 0;
  return;
}



// WARNING: Unable to use type for symbol basePtr


void ReadBinkChunk(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar1 = (undefined4 *)PTR_DAT_00336888;
  puVar4 = (undefined4 *)PTR_DAT_0033688c;
  if (DAT_00336890 == g_PushBufferLength_) {
    puVar1 = (undefined4 *)FUN_0015d3a0(DAT_00336890 << 4);
    puVar4 = (undefined4 *)PTR_DAT_00336888;
    puVar5 = puVar1;
    for (uVar2 = DAT_00336890 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    puVar4 = puVar1 + DAT_00336890 * 2;
    puVar5 = (undefined4 *)PTR_DAT_0033688c;
    puVar6 = puVar4;
    for (uVar2 = DAT_00336890 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    DAT_00336890 = DAT_00336890 * 2;
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    if (DAT_00336890 != 0x40) {
      FUN_0015d410(PTR_DAT_00336888);
    }
  }
  PTR_DAT_0033688c = (undefined *)puVar4;
  PTR_DAT_00336888 = (undefined *)puVar1;
  iVar3 = (param_2 + 0x1fU & 0xffffffe0) +
          (((DAT_004d9d90 >> 5) - (param_2 + 0x1fU >> 5)) + 1 & 0x1f) * 0x20;
  DAT_004d9d90 = DAT_004d9d90 + iVar3;
  *(int *)(PTR_DAT_0033688c + g_PushBufferLength_ * 4) = iVar3;
  *(undefined4 *)(PTR_DAT_00336888 + g_PushBufferLength_ * 4) = param_1;
  g_PushBufferLength_ = g_PushBufferLength_ + 1;
  return;
}




void GetNewChunk(uint size)

{
  int i;
  int *piVar1;
  uint stride;
  int iVar2;
  
                    // Align the size to a multiple of 32
  stride = size + 0b00011111 & 0b11111111111111111111111111100000;
  i = FUN_0015d3a0(DAT_004d9d90 + stride);
  DAT_004d9d90 = 0;
  if ((i != 0) && (i = i + stride, g_PushBufferLength_ != 0)) {
    iVar2 = (int)PTR_DAT_00336888 - (int)PTR_DAT_0033688c;
    piVar1 = (int *)PTR_DAT_0033688c;
    do {
      **(int **)(iVar2 + (int)piVar1) = i;
      i = i + *piVar1;
      piVar1 = piVar1 + 1;
      g_PushBufferLength_ = g_PushBufferLength_ + -1;
    } while (g_PushBufferLength_ != 0);
  }
  g_PushBufferLength_ = 0;
  return;
}




int inflateReset(z_stream *z)

{
  internal_state *state;
  
  if ((z != (z_stream *)0x0) && (state = z->state, state != (internal_state *)0x0)) {
    z->total_out = 0;
    z->total_in = 0;
    z->msg = (char *)0x0;
    state->strm = (z_streamp)(-(uint)(state->pending_buf_size != 0) & 0b00000111);
    FUN_00163080((astruct_45 *)z->state->pending,z,0);
    return Z_OK;
  }
  return Z_STREAM_ERROR;
}




int inflateEnd(z_streamp strm)

{
  int iVar1;
  
  if (((strm != (z_streamp)0x0) && (strm->state != (internal_state *)0x0)) &&
     (strm->zfree != (free_func)0x0)) {
    iVar1 = strm->state->pending;
    if (iVar1 != 0) {
      FUN_00163d10(iVar1,strm);
    }
    (*strm->zfree)(strm->opaque,strm->state);
    strm->state = (internal_state *)0x0;
    return 0;
  }
  return -2;
}




int inflateInit2_(z_streamp strm,int windowBits,char *version,int stream_size)

{
  internal_state *piVar1;
  int iVar2;
  
  if (((version == (char *)0x0) || (*version != '1')) || (stream_size != 0x38)) {
    return Z_VERSION_ERROR;
  }
  if (strm == (z_streamp)0x0) {
    return Z_STREAM_ERROR;
  }
  strm->msg = (char *)0x0;
  if (strm->zalloc == (alloc_func)0x0) {
    strm->zalloc = g_zalloc;
    strm->opaque = (voidpf)0x0;
  }
  if (strm->zfree == (free_func)0x0) {
    strm->zfree = g_zfree;
  }
  piVar1 = (*strm->zalloc)(strm->opaque,1,0x18);
  strm->state = piVar1;
  if (piVar1 != (internal_state *)0x0) {
    piVar1->pending = 0;
    strm->state->pending_buf_size = 0;
    if (windowBits < 0) {
      windowBits = -windowBits;
      strm->state->pending_buf_size = 1;
    }
    if ((windowBits < 8) || (0xf < windowBits)) {
      inflateEnd(strm);
      return Z_STREAM_ERROR;
    }
    strm->state->pending_out = (Bytef *)windowBits;
    iVar2 = FUN_00163100(strm,(strm->state->pending_buf_size != 0) - 1 & 0x163da0,
                         1 << ((byte)windowBits & 0x1f));
    strm->state->pending = iVar2;
    if (strm->state->pending != 0) {
      inflateReset(strm);
      return Z_OK;
    }
    inflateEnd(strm);
  }
  return Z_MEM_ERROR;
}




int inflateInit(z_streamp strm,char *version,int stream_size)

{
  int iVar1;
  
  iVar1 = inflateInit2_(strm,0xf,version,stream_size);
  return iVar1;
}




int inflate(z_stream *z,int f)

{
  Bytef **ppBVar1;
  byte bVar2;
  int iVar3;
  internal_state *piVar4;
  z_streamp pzVar5;
  uint uVar6;
  uint uVar7;
  
  if (((z == (z_stream *)0x0) || (z->state == (internal_state *)0x0)) ||
     (z->next_in == (Bytef *)0x0)) {
    return -2;
  }
  pzVar5 = z->state->strm;
  uVar7 = 0xfffffffb;
  uVar6 = (f != 4) - 1 & 0xfffffffb;
  if ((z_streamp)0xd < pzVar5) {
    return -2;
  }
  do {
    switch((&switchD_00162cd0::switchdataD_00163044)[(int)pzVar5]) {
    case (undefined *)0x162cd7:
      if (z->avail_in == 0) {
        return uVar7;
      }
      z->total_in = z->total_in + 1;
      z->avail_in = z->avail_in - 1;
      z->state->status = (uint)*z->next_in;
      piVar4 = z->state;
      iVar3 = piVar4->status;
      z->next_in = z->next_in + 1;
      if (((byte)iVar3 & 0xf) != 8) {
        piVar4->strm = (z_streamp)0xd;
        z->msg = "unknown compression method";
        z->state->status = 5;
        uVar7 = uVar6;
        break;
      }
      if ((Bytef *)(((uint)piVar4->status >> 4) + 8) <= piVar4->pending_out) {
        piVar4->strm = (z_streamp)0x1;
        uVar7 = uVar6;
        goto switchD_00162cd0_caseD_162d4d;
      }
      piVar4->strm = (z_streamp)0xd;
      z->msg = "invalid window size";
      goto LAB_00162f03;
    case (undefined *)0x162d4d:
switchD_00162cd0_caseD_162d4d:
      if (z->avail_in == 0) {
        return uVar7;
      }
      piVar4 = z->state;
      z->avail_in = z->avail_in - 1;
      z->total_in = z->total_in + 1;
      bVar2 = *z->next_in;
      z->next_in = z->next_in + 1;
      if ((piVar4->status * 0x100 + (uint)bVar2) % 0x1f == 0) {
        if ((bVar2 & 0x20) != 0) {
          z->state->strm = (z_streamp)0x2;
          uVar7 = uVar6;
          goto switchD_00162cd0_caseD_162f31;
        }
        piVar4->strm = (z_streamp)0x7;
        uVar7 = uVar6;
      }
      else {
        piVar4->strm = (z_streamp)0xd;
        z->msg = "incorrect header check";
        z->state->status = 5;
        uVar7 = uVar6;
      }
      break;
    case (undefined *)0x162db8:
      uVar7 = FUN_001631a0(z->state->pending,z,uVar7);
      if (uVar7 == 0xfffffffd) {
        z->state->strm = (z_streamp)0xd;
        z->state->status = 0;
        uVar7 = 0xfffffffd;
      }
      else {
        if (uVar7 == 0) {
          uVar7 = uVar6;
        }
        if (uVar7 != 1) {
          return uVar7;
        }
        FUN_00163080((astruct_45 *)z->state->pending,z,&z->state->status);
        piVar4 = z->state;
        if (piVar4->pending_buf_size == 0) {
          piVar4->strm = (z_streamp)0x8;
          uVar7 = uVar6;
          goto switchD_00162cd0_caseD_162e27;
        }
        piVar4->strm = (z_streamp)0xc;
        uVar7 = uVar6;
      }
      break;
    case (undefined *)0x162e27:
switchD_00162cd0_caseD_162e27:
      if (z->avail_in == 0) {
        return uVar7;
      }
      z->avail_in = z->avail_in - 1;
      z->total_in = z->total_in + 1;
      z->state->pending_buf = (Bytef *)((uint)*z->next_in << 0x18);
      z->next_in = z->next_in + 1;
      z->state->strm = (z_streamp)0x9;
      uVar7 = uVar6;
    case (undefined *)0x162e5b:
      if (z->avail_in == 0) {
        return uVar7;
      }
      z->avail_in = z->avail_in - 1;
      z->total_in = z->total_in + 1;
      z->state->pending_buf = z->state->pending_buf + (uint)*z->next_in * 0x10000;
      z->next_in = z->next_in + 1;
      z->state->strm = (z_streamp)0xa;
      uVar7 = uVar6;
switchD_00162cd0_caseD_162e90:
      if (z->avail_in == 0) {
        return uVar7;
      }
      z->avail_in = z->avail_in - 1;
      z->total_in = z->total_in + 1;
      z->state->pending_buf = z->state->pending_buf + (uint)*z->next_in * 0x100;
      z->next_in = z->next_in + 1;
      z->state->strm = (z_streamp)0xb;
      uVar7 = uVar6;
switchD_00162cd0_caseD_162ec6:
      if (z->avail_in == 0) {
        return uVar7;
      }
      z->avail_in = z->avail_in - 1;
      z->total_in = z->total_in + 1;
      ppBVar1 = &z->state->pending_buf;
      *ppBVar1 = *ppBVar1 + *z->next_in;
      z->next_in = z->next_in + 1;
      piVar4 = z->state;
      if ((Bytef *)piVar4->status == piVar4->pending_buf) {
        z->state->strm = (z_streamp)0xc;
switchD_00162cd0_caseD_163026:
        return 1;
      }
      piVar4->strm = (z_streamp)0xd;
      z->msg = "incorrect data check";
LAB_00162f03:
      z->state->status = 5;
      uVar7 = uVar6;
      break;
    case (undefined *)0x162e90:
      goto switchD_00162cd0_caseD_162e90;
    case (undefined *)0x162ec6:
      goto switchD_00162cd0_caseD_162ec6;
    case (undefined *)0x162f31:
switchD_00162cd0_caseD_162f31:
      if (z->avail_in == 0) {
        return uVar7;
      }
      z->total_in = z->total_in + 1;
      z->avail_in = z->avail_in - 1;
      z->state->pending_buf = (Bytef *)((uint)*z->next_in << 0x18);
      z->next_in = z->next_in + 1;
      z->state->strm = (z_streamp)0x3;
      uVar7 = uVar6;
    case (undefined *)0x162f61:
      if (z->avail_in != 0) {
        z->avail_in = z->avail_in - 1;
        z->total_in = z->total_in + 1;
        z->state->pending_buf = z->state->pending_buf + (uint)*z->next_in * 0x10000;
        z->next_in = z->next_in + 1;
        z->state->strm = (z_streamp)0x4;
        uVar7 = uVar6;
switchD_00162cd0_caseD_162f93:
        if (z->avail_in != 0) {
          z->avail_in = z->avail_in - 1;
          z->total_in = z->total_in + 1;
          z->state->pending_buf = z->state->pending_buf + (uint)*z->next_in * 0x100;
          z->next_in = z->next_in + 1;
          z->state->strm = (z_streamp)0x5;
          uVar7 = uVar6;
switchD_00162cd0_caseD_162fbd:
          if (z->avail_in != 0) {
            z->avail_in = z->avail_in - 1;
            z->total_in = z->total_in + 1;
            ppBVar1 = &z->state->pending_buf;
            *ppBVar1 = *ppBVar1 + *z->next_in;
            z->next_in = z->next_in + 1;
            z->adler = (uLong)z->state->pending_buf;
            z->state->strm = (z_streamp)0x6;
            return 2;
          }
        }
      }
      return uVar7;
    case (undefined *)0x162f93:
      goto switchD_00162cd0_caseD_162f93;
    case (undefined *)0x162fbd:
      goto switchD_00162cd0_caseD_162fbd;
    case (undefined *)0x162ff9:
      z->state->strm = (z_streamp)0xd;
      z->msg = "need dictionary";
      z->state->status = 0;
      return -2;
    case (undefined *)0x163026:
      goto switchD_00162cd0_caseD_163026;
    case (undefined *)0x163030:
      return -3;
    }
    pzVar5 = z->state->strm;
    if ((z_streamp)0xd < pzVar5) {
      return -2;
    }
  } while( true );
}




void FUN_00163080(astruct_45 *param_1,z_stream *param_2,int *param_3)

{
  uLong uVar1;
  
  if (param_3 != (int *)0x0) {
    *param_3 = param_1->field30_0x3c;
  }
  if ((param_1->field0_0x0 == 4) || (param_1->field0_0x0 == 5)) {
    (*param_2->zfree)(param_2->opaque,(voidpf)param_1->field6_0xc);
  }
  if (param_1->field0_0x0 == 6) {
    FUN_00164640(param_1->field1_0x4,param_2);
  }
  param_1->field28_0x34 = param_1->field22_0x28;
  param_1->field27_0x30 = param_1->field22_0x28;
  param_1->field0_0x0 = 0;
  param_1->field16_0x1c = 0;
  param_1->field17_0x20 = 0;
  if ((code *)param_1->callback != (code *)0x0) {
                    // Goes to 0x163da0
    uVar1 = (*(code *)param_1->callback)(0,0,0);
    param_1->field30_0x3c = uVar1;
    param_2->adler = uVar1;
  }
  return;
}




void * FUN_00163100(z_stream *param_1,BOOL someFlag,uInt param_3)

{
  void *puVar1;
  voidpf pvVar1;
  
  puVar1 = (*param_1->zalloc)(param_1->opaque,1,0x40);
  if (puVar1 != (void *)0x0) {
    pvVar1 = (*param_1->zalloc)(param_1->opaque,8,0x5a0);
    *(voidpf *)((int)puVar1 + 0x24) = pvVar1;
    if (pvVar1 != (voidpf)0x0) {
      pvVar1 = (*param_1->zalloc)(param_1->opaque,1,param_3);
      *(voidpf *)((int)puVar1 + 0x28) = pvVar1;
      if (pvVar1 == (voidpf)0x0) {
        (*param_1->zfree)(param_1->opaque,*(voidpf *)((int)puVar1 + 0x24));
        (*param_1->zfree)(param_1->opaque,puVar1);
        return (void *)0x0;
      }
      *(uInt *)((int)puVar1 + 0x2c) = (int)pvVar1 + param_3;
      *(BOOL *)((int)puVar1 + 0x38) = someFlag;
      *(undefined4 *)puVar1 = 0;
      FUN_00163080(puVar1,param_1,0);
      return puVar1;
    }
    (*param_1->zfree)(param_1->opaque,puVar1);
  }
  return (void *)0x0;
}




void FUN_001631a0(uint *param_1,z_streamp param_2,undefined4 param_3)

{
  uint *puVar1;
  voidpf pvVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  byte *pbVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *local_34;
  byte *local_30;
  byte *local_2c;
  byte *local_28;
  byte *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  byte *local_10;
  uint local_c;
  inflate_huft *local_8;
  inflate_huft *local_4;
  
  puVar1 = param_1;
  pbVar9 = (byte *)param_1[7];
  local_34 = (byte *)param_2->avail_in;
  local_30 = (byte *)param_1[0xd];
  if (local_30 < (byte *)param_1[0xc]) {
    local_2c = (byte *)param_1[0xc] + (-1 - (int)local_30);
  }
  else {
    local_2c = (byte *)(param_1[0xb] - (int)local_30);
  }
  uVar8 = *param_1;
  param_1 = (uint *)param_1[8];
  pbVar11 = param_2->next_in;
  do {
    local_28 = pbVar11;
    if (9 < uVar8) {
      param_3 = 0xfffffffe;
LAB_001631eb:
      puVar1[8] = (uint)param_1;
LAB_001631f2:
      puVar1[7] = (uint)pbVar9;
      param_2->avail_in = (uInt)local_34;
      param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
LAB_0016320a:
      param_2->next_in = pbVar11;
      puVar1[0xd] = (uint)local_30;
      FUN_00164dc0(puVar1,param_2,param_3);
      return;
    }
    switch((&switchD_0016322d::switchdataD_00163cd8)[uVar8]) {
    case (undefined *)0x163234:
      for (; local_28 = pbVar11, pbVar9 < (byte *)0x3; pbVar9 = pbVar9 + 8) {
        if (local_34 == (byte *)0x0) {
          puVar1[8] = (uint)param_1;
          puVar1[7] = (uint)pbVar9;
          param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
          param_2->avail_in = 0;
          param_2->next_in = pbVar11;
          puVar1[0xd] = (uint)local_30;
          FUN_00164dc0(puVar1,param_2,param_3);
          return;
        }
        local_34 = local_34 + -1;
        param_3 = 0;
        param_1 = (uint *)((uint)param_1 | (uint)*pbVar11 << ((byte)pbVar9 & 0x1f));
        pbVar11 = pbVar11 + 1;
      }
      puVar1[6] = (uint)param_1 & 1;
      switch(((uint)param_1 & 7) >> 1) {
      case 0:
        uVar8 = (uint)(pbVar9 + -3) & 7;
        param_1 = (uint *)(((uint)param_1 >> 3) >> (sbyte)uVar8);
        pbVar9 = pbVar9 + -3 + -uVar8;
        *puVar1 = 1;
        break;
      case 1:
        FUN_00164d90(&local_14,&local_18,&local_1c,&local_20,param_2);
        uVar8 = FUN_00163ef0(local_14,local_18,local_1c,local_20,param_2);
        puVar1[1] = uVar8;
        if (uVar8 == 0) {
          param_3 = 0xfffffffc;
          goto LAB_001631eb;
        }
        param_1 = (uint *)((uint)param_1 >> 3);
        pbVar9 = pbVar9 + -3;
        *puVar1 = 6;
        break;
      case 2:
        param_1 = (uint *)((uint)param_1 >> 3);
        pbVar9 = pbVar9 + -3;
        *puVar1 = 3;
        break;
      case 3:
        *puVar1 = 9;
        param_2->msg = "invalid block type";
        puVar1[8] = (uint)param_1 >> 3;
        pbVar9 = pbVar9 + -3;
        param_3 = 0xfffffffd;
        goto LAB_001631f2;
      }
      break;
    case (undefined *)0x16331c:
      for (; local_28 = pbVar11, pbVar9 < (byte *)0x20; pbVar9 = pbVar9 + 8) {
        if (local_34 == (byte *)0x0) goto LAB_00163b2d;
        local_34 = local_34 + -1;
        param_3 = 0;
        param_1 = (uint *)((uint)param_1 | (uint)*pbVar11 << ((byte)pbVar9 & 0x1f));
        pbVar11 = pbVar11 + 1;
      }
      uVar8 = (uint)param_1 & 0xffff;
      if (~(uint)param_1 >> 0x10 != uVar8) {
        *puVar1 = 9;
        param_2->msg = "invalid stored block lengths";
        goto switchD_0016322d_caseD_1639cb;
      }
      pbVar9 = (byte *)0x0;
      puVar1[1] = uVar8;
      param_1 = (uint *)0x0;
      if (uVar8 == 0) goto LAB_001634aa;
      *puVar1 = 2;
      break;
    case (undefined *)0x16338a:
      if (local_34 == (byte *)0x0) {
LAB_00163aee:
        puVar1[8] = (uint)param_1;
        puVar1[7] = (uint)pbVar9;
        param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
        param_2->avail_in = 0;
        param_2->next_in = pbVar11;
        puVar1[0xd] = (uint)local_30;
        FUN_00164dc0(puVar1,param_2,param_3);
        return;
      }
      if (local_2c == (byte *)0x0) {
        if (local_30 == (byte *)puVar1[0xb]) {
          local_2c = (byte *)puVar1[0xc];
          pbVar7 = (byte *)puVar1[10];
          if (pbVar7 != local_2c) {
            if (pbVar7 < local_2c) {
              local_2c = local_2c + (-1 - (int)pbVar7);
            }
            else {
              local_2c = (byte *)puVar1[0xb] + -(int)pbVar7;
            }
            local_30 = pbVar7;
            if (local_2c != (byte *)0x0) goto LAB_00163443;
          }
        }
        puVar1[0xd] = (uint)local_30;
        uVar4 = FUN_00164dc0(puVar1,param_2,param_3);
        local_24 = (byte *)puVar1[0xc];
        local_30 = (byte *)puVar1[0xd];
        if (local_30 < local_24) {
          local_2c = local_24 + (-1 - (int)local_30);
        }
        else {
          local_2c = (byte *)(puVar1[0xb] - (int)local_30);
        }
        local_10 = (byte *)puVar1[0xb];
        if (local_30 == local_10) {
          pbVar7 = (byte *)puVar1[10];
          if (pbVar7 != local_24) {
            local_30 = pbVar7;
            if (pbVar7 < local_24) {
              local_2c = local_24 + (-1 - (int)pbVar7);
            }
            else {
              local_2c = local_10 + -(int)pbVar7;
            }
          }
        }
        if (local_2c == (byte *)0x0) {
          puVar1[8] = (uint)param_1;
          puVar1[7] = (uint)pbVar9;
          param_2->avail_in = (uInt)local_34;
          param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
          param_2->next_in = pbVar11;
          puVar1[0xd] = (uint)local_30;
          FUN_00164dc0(puVar1,param_2,uVar4);
          return;
        }
      }
LAB_00163443:
      pbVar11 = (byte *)puVar1[1];
      if (local_34 < (byte *)puVar1[1]) {
        pbVar11 = local_34;
      }
      if (local_2c < pbVar11) {
        pbVar11 = local_2c;
      }
      pbVar7 = local_28;
      pbVar10 = local_30;
      for (uVar8 = (uint)pbVar11 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pbVar10 = *(undefined4 *)pbVar7;
        pbVar7 = pbVar7 + 4;
        pbVar10 = pbVar10 + 4;
      }
      for (uVar8 = (uint)pbVar11 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pbVar10 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar10 = pbVar10 + 1;
      }
      local_28 = local_28 + (int)pbVar11;
      uVar8 = puVar1[1];
      local_34 = local_34 + -(int)pbVar11;
      local_30 = local_30 + (int)pbVar11;
      local_2c = local_2c + -(int)pbVar11;
      param_3 = 0;
      puVar1[1] = uVar8 - (int)pbVar11;
      if (uVar8 - (int)pbVar11 == 0) {
LAB_001634aa:
        *puVar1 = -(uint)(puVar1[6] != 0) & 7;
      }
      break;
    case (undefined *)0x1634bb:
      for (; pbVar9 < (byte *)0xe; pbVar9 = pbVar9 + 8) {
        if (local_34 == (byte *)0x0) goto LAB_00163b2d;
        local_34 = local_34 + -1;
        param_3 = 0;
        param_1 = (uint *)((uint)param_1 | (uint)*pbVar11 << ((byte)pbVar9 & 0x1f));
        pbVar11 = pbVar11 + 1;
      }
      puVar1[1] = (uint)param_1 & 0x3fff;
      if ((((uint)param_1 & 0x1f) < 0x1e) &&
         (uVar8 = ((uint)param_1 & 0x3fff) >> 5 & 0x1f, uVar8 < 0x1e)) {
        pvVar2 = (*param_2->zalloc)(param_2->opaque,uVar8 + 0x102 + ((uint)param_1 & 0x1f),4);
        puVar1[3] = (uint)pvVar2;
        if (pvVar2 == (voidpf)0x0) {
          puVar1[8] = (uint)param_1;
          puVar1[7] = (uint)pbVar9;
          param_2->avail_in = (uInt)local_34;
          param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
          param_2->next_in = pbVar11;
          puVar1[0xd] = (uint)local_30;
          FUN_00164dc0(puVar1,param_2,0xfffffffc);
          return;
        }
        param_1 = (uint *)((uint)param_1 >> 0xe);
        pbVar9 = pbVar9 + -0xe;
        puVar1[2] = 0;
        *puVar1 = 4;
        goto switchD_0016322d_caseD_163552;
      }
      *puVar1 = 9;
      param_2->msg = "too many length or distance symbols";
      param_3 = 0xfffffffd;
      goto LAB_001631eb;
    case (undefined *)0x163552:
switchD_0016322d_caseD_163552:
      if (puVar1[2] < (puVar1[1] >> 10) + 4) {
        do {
          for (; pbVar9 < (byte *)0x3; pbVar9 = pbVar9 + 8) {
            if (local_34 == (byte *)0x0) goto LAB_00163b2d;
            local_34 = local_34 + -1;
            param_3 = 0;
            param_1 = (uint *)((uint)param_1 | (uint)*pbVar11 << ((byte)pbVar9 & 0x1f));
            pbVar11 = pbVar11 + 1;
          }
          *(uint *)(puVar1[3] + *(int *)(&DAT_00208c00 + puVar1[2] * 4) * 4) = (uint)param_1 & 7;
          puVar1[2] = puVar1[2] + 1;
          param_1 = (uint *)((uint)param_1 >> 3);
          pbVar9 = pbVar9 + -3;
        } while (puVar1[2] < (puVar1[1] >> 10) + 4);
      }
      uVar8 = puVar1[2];
      while (uVar8 < 0x13) {
        *(undefined4 *)(puVar1[3] + *(int *)(&DAT_00208c00 + puVar1[2] * 4) * 4) = 0;
        uVar8 = puVar1[2] + 1;
        puVar1[2] = uVar8;
      }
      puVar1[4] = 7;
      iVar5 = FUN_00164b50(puVar1[3],puVar1 + 4,puVar1 + 5,puVar1[9],param_2);
      if (iVar5 != 0) {
        (*param_2->zfree)(param_2->opaque,(voidpf)puVar1[3]);
        if (iVar5 == -3) {
          *puVar1 = 9;
        }
        puVar1[8] = (uint)param_1;
        puVar1[7] = (uint)pbVar9;
        param_2->avail_in = (uInt)local_34;
        param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
        param_2->next_in = pbVar11;
        puVar1[0xd] = (uint)local_30;
        FUN_00164dc0(puVar1,param_2,iVar5);
        return;
      }
      puVar1[2] = 0;
      *puVar1 = 5;
switchD_0016322d_caseD_163649:
      if (puVar1[2] < (puVar1[1] >> 5 & 0x1f) + 0x102 + (puVar1[1] & 0x1f)) {
        do {
          pbVar7 = (byte *)puVar1[4];
          if (pbVar9 < pbVar7) {
            do {
              if (local_34 == (byte *)0x0) goto LAB_00163aee;
              local_34 = local_34 + -1;
              bVar6 = (byte)pbVar9;
              pbVar7 = (byte *)puVar1[4];
              pbVar9 = pbVar9 + 8;
              param_3 = 0;
              param_1 = (uint *)((uint)param_1 | (uint)*pbVar11 << (bVar6 & 0x1f));
              pbVar11 = pbVar11 + 1;
            } while (pbVar9 < pbVar7);
          }
          iVar5 = puVar1[5] + (*(uint *)(&DAT_00337a18 + (int)pbVar7 * 4) & (uint)param_1) * 8;
          bVar6 = *(byte *)(iVar5 + 1);
          uVar8 = (uint)bVar6;
          local_c = *(uint *)(iVar5 + 4);
          if (local_c < 0x10) {
            param_1 = (uint *)((uint)param_1 >> (bVar6 & 0x1f));
            pbVar9 = pbVar9 + -uVar8;
            *(uint *)(puVar1[3] + puVar1[2] * 4) = local_c;
            puVar1[2] = puVar1[2] + 1;
          }
          else {
            if (local_c == 0x12) {
              local_24 = (byte *)0x7;
            }
            else {
              local_24 = (byte *)(local_c - 0xe);
            }
            local_28 = (byte *)((uint)(local_c == 0x12) * 8 + 3);
            local_10 = local_24 + uVar8;
            for (; pbVar9 < local_10; pbVar9 = pbVar9 + 8) {
              if (local_34 == (byte *)0x0) goto LAB_00163b2d;
              local_34 = local_34 + -1;
              param_3 = 0;
              param_1 = (uint *)((uint)param_1 | (uint)*pbVar11 << ((byte)pbVar9 & 0x1f));
              pbVar11 = pbVar11 + 1;
            }
            uVar3 = (uint)param_1 >> (bVar6 & 0x1f);
            local_28 = local_28 + (*(uint *)(&DAT_00337a18 + (int)local_24 * 4) & uVar3);
            param_1 = (uint *)(uVar3 >> ((byte)local_24 & 0x1f));
            pbVar9 = pbVar9 + -(int)(local_24 + uVar8);
            uVar8 = puVar1[2];
            if ((byte *)((puVar1[1] >> 5 & 0x1f) + 0x102 + (puVar1[1] & 0x1f)) < local_28 + uVar8) {
LAB_00163b56:
              (*param_2->zfree)(param_2->opaque,(voidpf)puVar1[3]);
              *puVar1 = 9;
              param_2->msg = "invalid bit length repeat";
              puVar1[8] = (uint)param_1;
              puVar1[7] = (uint)pbVar9;
              param_2->avail_in = (uInt)local_34;
              param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
              param_2->next_in = pbVar11;
              puVar1[0xd] = (uint)local_30;
              FUN_00164dc0(puVar1,param_2,0xfffffffd);
              return;
            }
            if (local_c == 0x10) {
              if (uVar8 == 0) goto LAB_00163b56;
              uVar4 = *(undefined4 *)((puVar1[3] - 4) + uVar8 * 4);
            }
            else {
              uVar4 = 0;
            }
            do {
              *(undefined4 *)(puVar1[3] + uVar8 * 4) = uVar4;
              uVar8 = uVar8 + 1;
              local_28 = local_28 + -1;
            } while (local_28 != (byte *)0x0);
            puVar1[2] = uVar8;
            local_28 = (byte *)0x0;
          }
        } while (puVar1[2] < (puVar1[1] >> 5 & 0x1f) + 0x102 + (puVar1[1] & 0x1f));
      }
      puVar1[5] = 0;
      local_28 = (byte *)0x9;
      local_24 = &DAT_00000006;
      iVar5 = inflate_trees_dynamic
                        ((puVar1[1] & 0x1f) + 0x101,(puVar1[1] >> 5 & 0x1f) + 1,(uIntf *)puVar1[3],
                         (uIntf *)&local_28,(uIntf *)&local_24,&local_4,&local_8,
                         (inflate_huft *)puVar1[9],param_2);
      (*param_2->zfree)(param_2->opaque,(voidpf)puVar1[3]);
      if (iVar5 != 0) {
        if (iVar5 == -3) {
          *puVar1 = 9;
        }
        puVar1[8] = (uint)param_1;
        puVar1[7] = (uint)pbVar9;
        param_2->avail_in = (uInt)local_34;
        param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
        param_2->next_in = pbVar11;
        puVar1[0xd] = (uint)local_30;
        FUN_00164dc0(puVar1,param_2,iVar5);
        return;
      }
      uVar8 = FUN_00163ef0(local_28,local_24,local_4,local_8,param_2);
      if (uVar8 == 0) {
        puVar1[8] = (uint)param_1;
        puVar1[7] = (uint)pbVar9;
        param_2->avail_in = (uInt)local_34;
        param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
        param_2->next_in = pbVar11;
        puVar1[0xd] = (uint)local_30;
        FUN_00164dc0(puVar1,param_2,0xfffffffc);
        return;
      }
      puVar1[1] = uVar8;
      *puVar1 = 6;
switchD_0016322d_caseD_1638a2:
      puVar1[8] = (uint)param_1;
      puVar1[7] = (uint)pbVar9;
      param_2->avail_in = (uInt)local_34;
      param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
      param_2->next_in = pbVar11;
      puVar1[0xd] = (uint)local_30;
      iVar5 = FUN_00163f30(puVar1,param_2,param_3);
      if (iVar5 != 1) {
        FUN_00164dc0(puVar1,param_2,iVar5);
        return;
      }
      param_3 = 0;
      FUN_00164640(puVar1[1],param_2);
      param_1 = (uint *)puVar1[8];
      local_30 = (byte *)puVar1[0xd];
      local_28 = param_2->next_in;
      local_34 = (byte *)param_2->avail_in;
      pbVar9 = (byte *)puVar1[7];
      if (local_30 < (byte *)puVar1[0xc]) {
        local_2c = (byte *)puVar1[0xc] + (-1 - (int)local_30);
      }
      else {
        local_2c = (byte *)(puVar1[0xb] - (int)local_30);
      }
      if (puVar1[6] != 0) {
        *puVar1 = 7;
switchD_0016322d_caseD_163c4b:
        pbVar11 = local_28;
        puVar1[0xd] = (uint)local_30;
        param_3 = FUN_00164dc0(puVar1,param_2,param_3);
        local_30 = (byte *)puVar1[0xd];
        if ((byte *)puVar1[0xc] == local_30) {
          *puVar1 = 8;
switchD_0016322d_caseD_163c9a:
          puVar1[8] = (uint)param_1;
          puVar1[7] = (uint)pbVar9;
          param_2->avail_in = (uInt)local_34;
          param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
          param_2->next_in = pbVar11;
          puVar1[0xd] = (uint)local_30;
          FUN_00164dc0(puVar1,param_2,1);
          return;
        }
        puVar1[8] = (uint)param_1;
        puVar1[7] = (uint)pbVar9;
        param_2->avail_in = (uInt)local_34;
        param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
        goto LAB_0016320a;
      }
      *puVar1 = 0;
      break;
    case (undefined *)0x163649:
      goto switchD_0016322d_caseD_163649;
    case (undefined *)0x1638a2:
      goto switchD_0016322d_caseD_1638a2;
    case (undefined *)0x1639cb:
switchD_0016322d_caseD_1639cb:
      puVar1[8] = (uint)param_1;
      puVar1[7] = (uint)pbVar9;
      param_2->avail_in = (uInt)local_34;
      param_2->total_in = (uLong)(local_28 + (param_2->total_in - (int)param_2->next_in));
      param_2->next_in = local_28;
      puVar1[0xd] = (uint)local_30;
      FUN_00164dc0(puVar1,param_2,0xfffffffd);
      return;
    case (undefined *)0x163c4b:
      goto switchD_0016322d_caseD_163c4b;
    case (undefined *)0x163c9a:
      goto switchD_0016322d_caseD_163c9a;
    }
    uVar8 = *puVar1;
    pbVar11 = local_28;
  } while( true );
LAB_00163b2d:
  puVar1[8] = (uint)param_1;
  puVar1[7] = (uint)pbVar9;
  param_2->total_in = (uLong)(pbVar11 + (param_2->total_in - (int)param_2->next_in));
  param_2->avail_in = 0;
  goto LAB_0016320a;
}




void g_zfree(undefined4 param_1,undefined4 param_2)

{
  FUN_00167f2e(param_2);
  return;
}



void FUN_00163ef0(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(**(code **)(param_5 + 0x20))(*(undefined4 *)(param_5 + 0x28),1,0x1c);
  if (puVar1 != (undefined4 *)0x0) {
    *(undefined1 *)(puVar1 + 4) = param_1;
    *(undefined1 *)((int)puVar1 + 0x11) = param_2;
    *puVar1 = 0;
    puVar1[5] = param_3;
    puVar1[6] = param_4;
  }
  return;
}




void __lock_file(uint param_1)

{
  if ((0x337cf7 < param_1) && (param_1 < 0x337f59)) {
    FUN_001681c1(((int)(param_1 - 0x337cf8) >> 5) + 0x10);
    return;
  }
  RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)(param_1 + 0x20));
  return;
}



// Library Function - Single Match
//  __lock_file2
// 
// Library: Visual Studio 2003 Release


void __lock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    FUN_001681c1(param_1 + 0x10);
    return;
  }
  RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)(param_2 + 0x20));
  return;
}



// Library Function - Single Match
//  __unlock_file
// 
// Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release


void __unlock_file(uint param_1)

{
  if ((0x337cf7 < param_1) && (param_1 < 0x337f59)) {
    FUN_0016810f(((int)(param_1 - 0x337cf8) >> 5) + 0x10);
    return;
  }
  RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)(param_1 + 0x20));
  return;
}



// Library Function - Single Match
//  __unlock_file2
// 
// Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release


void __unlock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    FUN_0016810f(param_1 + 0x10);
    return;
  }
  RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)(param_2 + 0x20));
  return;
}



// Library Function - Single Match
//  __filbuf
// 
// Library: Visual Studio 2003 Release


uint __thiscall __getwc_lk(undefined4 param_1,FILE *param_2)

{
  char **ppcVar1;
  char *pcVar2;
  FILE *__stream;
  undefined *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 local_8;
  
  __stream = param_2;
  local_8 = param_1;
  if (((uint)param_2->_IO_read_base & 0x40) == 0) {
    pcVar2 = param_2->_IO_write_base;
    if (pcVar2 == (char *)0xffffffff) {
      puVar3 = &DAT_00338250;
    }
    else {
      puVar3 = (undefined *)((&DAT_0054dc60)[(int)pcVar2 >> 5] + ((uint)pcVar2 & 0x1f) * 0x28);
    }
    if ((puVar3[4] & 0x80) != 0) {
      uVar7 = 1;
      ppcVar1 = &param_2->_IO_read_ptr;
      *ppcVar1 = *ppcVar1 + -1;
      if ((int)*ppcVar1 < 0) {
        uVar4 = __filbuf(param_2);
      }
      else {
        uVar4 = (uint)*(byte *)param_2->_flags;
        param_2->_flags = (int)((byte *)param_2->_flags + 1);
      }
      if (uVar4 != 0xffffffff) {
        local_8 = CONCAT31(local_8._1_3_,(char)uVar4);
        if ((PTR_DAT_00338180[(uVar4 & 0xff) * 2 + 1] & 0x80) != 0) {
          ppcVar1 = &__stream->_IO_read_ptr;
          *ppcVar1 = *ppcVar1 + -1;
          if ((int)*ppcVar1 < 0) {
            uVar4 = __filbuf(__stream);
          }
          else {
            uVar4 = (uint)*(byte *)__stream->_flags;
            __stream->_flags = (int)((byte *)__stream->_flags + 1);
          }
          if (uVar4 == 0xffffffff) {
            _ungetc((int)(char)local_8,__stream);
            return 0xffff;
          }
          local_8._0_2_ = CONCAT11((char)uVar4,(char)local_8);
          uVar7 = 2;
        }
        iVar5 = FUN_0016e07a((int)&param_2 + 2,&local_8,uVar7);
        if (iVar5 != -1) {
          return (uint)param_2 >> 0x10;
        }
        puVar6 = (undefined4 *)FUN_00168af5();
        *puVar6 = 0x2a;
      }
      return 0xffff;
    }
  }
  ppcVar1 = &param_2->_IO_read_ptr;
  *ppcVar1 = *ppcVar1 + -2;
  if ((int)*ppcVar1 < 0) {
    uVar4 = __filwbuf(param_2);
  }
  else {
    uVar4 = (uint)*(ushort *)param_2->_flags;
    param_2->_flags = (int)((ushort *)param_2->_flags + 1);
  }
  return uVar4;
}




void SetFileReadError(char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (int)g_ReadFileError - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return;
}




MovieChunk * GetNextMovieChunk(char *param_1,uint flags)

{
  undefined **ppuVar1;
  uint size;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  uint uVar6;
  uint uVar7;
  MovieChunk *piVar6;
  char *pcVar8;
  int c_i;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  int *piVar12;
  undefined1 *puVar13;
  code *pcVar14;
  undefined4 *puVar15;
  char **ppcVar16;
  MovieChunk *pMVar17;
  undefined4 *puVar18;
  bool bVar19;
  uint local_3cc;
  uint local_3c8;
  longlong local_3c4;
  undefined4 local_3bc;
  char *local_3b8;
  undefined4 uStack_3b4;
  int iStack_3b0;
  undefined4 uStack_3ac;
  int local_3a8;
  int local_3a4;
  int local_3a0;
  int local_39c;
  uint local_398;
  uint local_394;
  int local_390;
  int local_38c [5];
  int local_378;
  uint local_374;
  uint local_36c;
  uint local_368;
  undefined4 local_364;
  undefined4 uStack_2d0;
  int local_2c0;
  int local_2bc;
  uint local_2b8;
  uint local_2b4;
  undefined1 local_2b0 [4];
  uint local_2ac;
  uint local_2a8;
  undefined4 local_2a4;
  int local_2a0;
  int local_29c;
  code *apcStack_288 [2];
  undefined1 local_280 [4];
  undefined1 local_27c [20];
  code *local_268;
  int local_138;
  int local_134;
  undefined1 local_130 [4];
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  undefined1 local_124 [64];
  int local_e4;
  undefined4 local_d4;
  int local_d0;
  uint local_cc;
  uint local_c8;
  int local_c4;
  undefined1 local_c0 [4];
  undefined1 local_bc [4];
  undefined1 local_b8 [4];
  undefined1 local_b4 [4];
  undefined1 local_b0 [4];
  undefined1 local_ac [4];
  undefined1 local_a8 [28];
  undefined1 local_8c [16];
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c [23];
  char c;
  
  pcVar14 = FUN_001ae1c0;
  if ((flags & 0x4000) == 0) {
    INT_0054f7e0 = 1;
    DAT_0054f7e4 = 0;
  }
  piVar12 = local_38c;
  for (iVar11 = 0xe3; iVar11 != 0; iVar11 = iVar11 + -1) {
    *piVar12 = 0;
    piVar12 = piVar12 + 1;
  }
  local_d4 = FUN_001a8e80();
  uVar6 = flags & 0x4000000;
  g_ReadFileError[0] = '\0';
  if (uVar6 == 0) {
    if (((flags & 0x2000000) != 0) && (PTR_0054f804 != (void *)0x0)) {
      pcVar14 = PTR_0054f804;
    }
    PTR_0054f804 = (void *)0x0;
    iVar11 = (*pcVar14)(local_27c,param_1,flags);
    if (iVar11 == 0) {
      if (g_ReadFileError[0] == '\0') {
        SetFileReadError("Error opening file.");
      }
      return (MovieChunk *)0x0;
    }
    (*apcStack_288[0])(apcStack_288,0,&local_3c4,0x2c);
  }
  else {
    pcVar8 = param_1;
    ppcVar16 = &local_3b8;
    for (iVar11 = 0xb; iVar11 != 0; iVar11 = iVar11 + -1) {
      *ppcVar16 = *(char **)pcVar8;
      pcVar8 = pcVar8 + 4;
      ppcVar16 = ppcVar16 + 1;
    }
  }
  if ((((local_3b8 != (char *)0x664b4942) && (local_3b8 != (char *)0x674b4942)) &&
      (local_3b8 != (char *)0x684b4942)) && (local_3b8 != (char *)0x694b4942)) {
    SetFileReadError("Not a Bink file.");
    goto LAB_001a68e1;
  }
  if (iStack_3b0 == 0) {
    iVar11 = 0;
    do {
      c = "The file doesn\'t contain any compressed frames yet."[iVar11];
      g_ReadFileError[iVar11] = c;
      iVar11 = iVar11 + 1;
    } while (c != '\0');
    goto LAB_001a68e1;
  }
  uVar7 = (local_3a4 + 1U >> 1) + 7;
  local_2b8 = uVar7 & 0xfffffff8;
  local_2c0 = local_2b8 * 2;
  local_2b4 = (local_3a0 + 1U >> 1) + 7 & 0xfffffff8;
  local_2bc = local_2b4 * 2;
  local_2ac = (uVar7 & 0x7ffffff8) >> 3;
  local_36c = flags & 0x8fffffff;
  local_38c[0] = local_3a4;
  local_38c[1] = local_3a0;
  local_138 = local_3a4;
  local_134 = local_3a0;
  local_368 = local_394;
  if ((local_394 & 0x100000) == 0) {
    local_36c = flags & 0x8fefffff;
  }
  local_36c = local_394 & 0x20000 | local_36c;
  puVar13 = (undefined1 *)(flags & 0x70000000);
  if (puVar13 != (undefined1 *)0x70000000) {
    if (puVar13 == (undefined1 *)0x0) {
      puVar13 = (undefined1 *)(local_394 & 0x70000000);
    }
    local_36c = local_36c | (uint)puVar13;
    if (puVar13 < (undefined1 *)0x30000001) {
      if (puVar13 == (undefined1 *)0x30000000) {
        local_38c[0] = local_3a4 * 2;
      }
      else if ((puVar13 == (undefined1 *)0x10000000) || (puVar13 == (undefined1 *)0x20000000))
      goto LAB_001a623f;
    }
    else if ((puVar13 == (undefined1 *)0x40000000) || (puVar13 == &DAT_50000000)) {
      local_38c[0] = local_3a4 * 2;
LAB_001a623f:
      local_38c[1] = local_3a0 * 2;
    }
  }
  if ((local_3b8 == (char *)0x664b4942) || (local_3b8 == (char *)0x674b4942)) {
    local_36c = local_36c | 0x18000;
  }
  else if (local_3b8 == (char *)0x684b4942) {
    local_36c = local_36c | 0x8000;
  }
  local_38c[2] = iStack_3b0;
  local_2a0 = local_3a8;
  if (((flags & 0x1000) == 0) || (DAT_0054f7d4 == -1)) {
    local_378 = local_39c;
    local_374 = local_398;
  }
  else {
    local_378 = DAT_0054f7d4;
    local_374 = DAT_004d9b80;
    DAT_0054f7d4 = -1;
  }
  local_364 = uStack_3b4;
  local_29c = local_390;
  local_2a4 = uStack_3ac;
  local_d0 = local_39c;
  local_c8 = ((local_398 >> 1) + local_39c) / local_398;
  local_2a8 = local_2ac * local_2bc >> 4;
  local_cc = local_398;
  if (local_c8 == 0) {
    local_c8 = 1;
  }
  local_c4 = local_c8 * 4 + -4;
  ReadBinkChunk(local_2b0,local_2a8 + 0x10);
  ReadBinkChunk(local_c0,local_c8 * 4);
  ReadBinkChunk(local_bc,local_c8 * 4);
  ReadBinkChunk(local_b8,local_c8 * 4);
  ReadBinkChunk(local_b4,local_c8 * 4);
  ReadBinkChunk(local_b0,local_c8 * 4);
  ReadBinkChunk(local_ac,local_c8 * 4);
  ReadBinkChunk(local_a8,local_c8 * 4);
  iVar11 = INT_0054f7e0;
  if (INT_0054f7e0 == 0) {
    iVar11 = 1;
  }
  ReadBinkChunk(local_8c,iVar11 * 0x178);
  ReadBinkChunk(local_130,INT_0054f7e0 * 4);
  ReadBinkHeader_(&local_7c,local_2c0);
  ReadBinkChunk(&local_7c,local_7c);
  ReadBinkChunk(&local_78,local_78);
  ReadBinkChunk(&local_74,local_74);
  ReadBinkChunk(&local_70,local_70);
  ReadBinkChunk(&local_6c,local_6c);
  ReadBinkChunk(&local_68,local_68);
  ReadBinkChunk(&local_64,local_64);
  ReadBinkChunk(&local_60,local_60);
  ReadBinkChunk(local_5c,local_5c[0]);
  if (uVar6 == 0) {
    ReadBinkChunk(local_280,local_2a0 * 4 + 4);
    ReadBinkChunk(local_12c,local_29c * 4);
    ReadBinkChunk(local_128,local_29c * 4);
    ReadBinkChunk(local_124,local_29c * 4);
  }
  iVar11 = FUN_0015d520();
  local_e4 = local_e4 + 0x38c + iVar11;
  piVar6 = (MovieChunk *)GetNewChunk(908);
  if (piVar6 != (MovieChunk *)0x0) {
    piVar12 = local_38c;
    pMVar17 = piVar6;
    for (iVar11 = 0xe3; iVar11 != 0; iVar11 = iVar11 + -1) {
      pMVar17->field0_0x0 = *piVar12;
      piVar12 = piVar12 + 1;
      pMVar17 = (MovieChunk *)&pMVar17->field_0x4;
    }
    piVar6->field203_0x128 = (int *)piVar6;
    *piVar6->field564_0x2d0 = 0;
    *piVar6->field565_0x2d4 = 0;
    *piVar6->field566_0x2d8 = 0;
    *piVar6->field567_0x2dc = 0;
    *piVar6->field568_0x2e0 = 0;
    *piVar6->field569_0x2e4 = 0;
    if (uVar6 == 0) {
      ppuVar1 = &piVar6->field197_0x110;
      (*(code *)*ppuVar1)(ppuVar1,0xffffffff,piVar6->field485_0x260,piVar6->field183_0xf0 << 2);
      (*(code *)*ppuVar1)(ppuVar1,0xffffffff,piVar6->field486_0x264,piVar6->field183_0xf0 << 2);
      (*(code *)*ppuVar1)(ppuVar1,0xffffffff,piVar6->field487_0x268,piVar6->field183_0xf0 << 2);
      (*(code *)*ppuVar1)(ppuVar1,0xffffffff,piVar6->field196_0x10c,piVar6->field182_0xec * 4 + 4);
    }
    else {
      piVar6->field485_0x260 = param_1 + 0x2c;
      iVar11 = piVar6->field183_0xf0;
      piVar6->field486_0x264 = param_1 + iVar11 * 4 + 0x2c;
      piVar6->field487_0x268 = param_1 + iVar11 * 8 + 0x2c;
      piVar6->field196_0x10c = (uint *)(param_1 + iVar11 * 0xc + 0x2c);
    }
    iVar11 = FUN_001a5e40(piVar6->field5_0x8,piVar6->field555_0x2c4,&piVar6->field185_0xf8,
                          &local_3c8);
    piVar6->field184_0xf4 = iVar11;
    if ((piVar6->field17_0x20 & 0x100000) == 0) {
      uVar7 = local_3c8;
      if (local_3c8 == 0) goto LAB_001a672f;
    }
    else {
      ReadBinkChunk(&piVar6->field169_0xc4,piVar6->field171_0xcc * piVar6->field172_0xd0);
      uVar7 = local_3c8;
      if (local_3c8 == 0) {
        ReadBinkChunk(&piVar6->field170_0xc8,piVar6->field171_0xcc * piVar6->field172_0xd0);
LAB_001a672f:
        ReadBinkChunk(&piVar6->field168_0xc0,
                      piVar6->field172_0xd0 * piVar6->field171_0xcc +
                      piVar6->field174_0xd8 * piVar6->field173_0xd4 * 2);
      }
    }
    size = piVar6->field172_0xd0 * piVar6->field171_0xcc +
           piVar6->field174_0xd8 * piVar6->field173_0xd4 * 2;
    iVar11 = FUN_0015d520();
    piVar6->field539_0x2a8 = piVar6->field539_0x2a8 + iVar11 + size;
    iVar11 = GetNewChunk(size);
    piVar6->field167_0xbc = iVar11;
    if (iVar11 != 0) {
      if (uVar7 != 0) {
        piVar6->field168_0xc0 = iVar11;
        piVar6->field170_0xc8 = piVar6->field169_0xc4;
      }
      if (((flags & 0x1000000) == 0) || (DAT_0054f7d8 == 0xffffffff)) {
        piVar6->field475_0x250 = piVar6->field184_0xf4;
      }
      else {
        piVar6->field475_0x250 = DAT_0054f7d8;
        DAT_0054f7d8 = 0xffffffff;
      }
      if (((flags & 0x400000) == 0) || (DAT_0054f7dc == 0xffffffff)) {
        local_3c8 = 0;
      }
      else {
        local_3c8 = DAT_0054f7dc;
        DAT_0054f7dc = 0xffffffff;
      }
      if (uVar6 != 0) {
        piVar6->field195_0x108 = param_1 + (*piVar6->field196_0x10c & 0xfffffffe);
LAB_001a699b:
        *(undefined1 *)(piVar6->field180_0xe4 + piVar6->field175_0xdc) = 0;
        uVar6 = piVar6->field11_0x14;
        piVar6->field6_0xc = -1;
        if (uVar6 == 0) {
          piVar6->field516_0x288 = 2000;
        }
        else {
          local_3bc = 2000;
          piVar6->field516_0x288 =
               (int)(((ulonglong)piVar6->field12_0x18 * 2000) / (ulonglong)uVar6);
          local_3c8 = uVar6;
        }
        piVar6->field538_0x2a4 = 1;
        FUN_001a5d60();
        iVar11 = FUN_001a8e80();
        piVar6->field552_0x2b8 = iVar11 - piVar6->field552_0x2b8;
        *(undefined4 *)(piVar6->field591_0x300 + 0x68) = 0x10000;
        piVar6->field586_0x2f8 = 0;
        if (((piVar6->field183_0xf0 != 0) && (INT_0054f7e0 != 0)) && (uVar6 = 0, INT_0054f7e0 != 0))
        {
          do {
            iVar11 = 0;
            if (0 < piVar6->field183_0xf0) {
              piVar12 = (int *)piVar6->field487_0x268;
              do {
                if (*piVar12 == (&DAT_0054f7e4)[uVar6]) {
                  *(int *)(piVar6->field484_0x25c + piVar6->field586_0x2f8 * 4) = iVar11;
                  piVar6->field586_0x2f8 = piVar6->field586_0x2f8 + 1;
                  break;
                }
                iVar11 = iVar11 + 1;
                piVar12 = piVar12 + 1;
              } while (iVar11 < piVar6->field183_0xf0);
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < (uint)INT_0054f7e0);
        }
        DAT_0054f7e4 = 0;
        INT_0054f7e0 = 1;
        local_3cc = 0;
        if (piVar6->field586_0x2f8 != 0) {
          iVar11 = 0;
          do {
            *(undefined4 *)(piVar6->field591_0x300 + 0x2c + iVar11) = 0;
            if ((*(uint *)(piVar6->field486_0x264 +
                          *(int *)(piVar6->field484_0x25c + local_3cc * 4) * 4) & 0x90000000) != 0)
            {
              if (DAT_0054f7c4 == (code *)0x0) {
                if (DAT_0054f7c0 == (code *)0x0) {
LAB_001a6b12:
                  DAT_0054f7c0 = FUN_001aa4a0;
                }
                else if (DAT_0054f7c0 != FUN_001aa4a0) {
                  if (DAT_0054f7c8 != 0) goto LAB_001a6de9;
                  goto LAB_001a6b12;
                }
                pcVar14 = (code *)(*DAT_0054f7c0)(0);
                if (pcVar14 != (code *)0x0) {
                  DAT_0054f7c4 = pcVar14;
                }
                if (DAT_0054f7c4 == (code *)0x0) goto LAB_001a6de9;
              }
              uVar6 = *(uint *)(piVar6->field486_0x264 +
                               *(int *)(piVar6->field484_0x25c + local_3cc * 4) * 4);
              uVar7 = uVar6 & 0xffff;
              if ((local_378 != 0) && (local_374 != 0)) {
                dVar5 = (double)(int)local_cc;
                if ((int)local_cc < 0) {
                  dVar5 = dVar5 + 4294967296.0;
                }
                dVar4 = (double)local_378;
                if (local_378 < 0) {
                  dVar4 = dVar4 + 4294967296.0;
                }
                dVar2 = (double)local_d0;
                if (local_d0 < 0) {
                  dVar2 = dVar2 + 4294967296.0;
                }
                dVar3 = (double)(int)local_374;
                if ((int)local_374 < 0) {
                  dVar3 = dVar3 + 4294967296.0;
                }
                local_3c4 = (longlong)ROUND((dVar4 * dVar5 * (double)uVar7) / (dVar3 * dVar2));
                uVar7 = (uint)local_3c4;
              }
              iVar9 = (*DAT_0054f7c4)(piVar6->field591_0x300 + iVar11,uVar7,
                                      (uVar6 >> 0x1e & 1) * 8 + 8,(uVar6 >> 0x1d & 1) + 1,
                                      piVar6->field17_0x20,piVar6);
              if (iVar9 != 0) {
                piVar12 = (int *)(piVar6->field591_0x300 + 0x58 + iVar11);
                if (*piVar12 == 0) {
                  *piVar12 = -1;
                }
                *(uint *)(piVar6->field591_0x300 + 0x28 + iVar11) =
                     *(int *)(piVar6->field485_0x260 +
                             *(int *)(piVar6->field484_0x25c + local_3cc * 4) * 4) + 0xffU &
                     0xffffff00;
                uVar6 = *(uint *)(piVar6->field591_0x300 + 0x28 + iVar11);
                iVar9 = FUN_0015d520();
                piVar6->field539_0x2a8 = piVar6->field539_0x2a8 + iVar9 + uVar6;
                uVar10 = GetNewChunk(uVar6);
                *(undefined4 *)(piVar6->field591_0x300 + 0x2c + iVar11) = uVar10;
                iVar9 = piVar6->field591_0x300 + iVar11;
                if (*(int *)(piVar6->field591_0x300 + 0x2c + iVar11) == 0) {
                  (**(code **)(iVar9 + 0x1c))(iVar9);
                }
                else {
                  DAT_0054f7c8 = DAT_0054f7c8 + 1;
                  *(uint *)(iVar9 + 0x44) =
                       (uint)((*(uint *)(piVar6->field486_0x264 +
                                        *(int *)(piVar6->field484_0x25c + local_3cc * 4) * 4) >>
                               0x1b & 8) == 0);
                  iVar9 = piVar6->field591_0x300;
                  *(int *)(iVar9 + 0x30 + iVar11) =
                       *(int *)(iVar9 + 0x2c + iVar11) + *(int *)(iVar9 + 0x28 + iVar11);
                  *(undefined4 *)(piVar6->field591_0x300 + 0x34 + iVar11) =
                       *(undefined4 *)(piVar6->field591_0x300 + 0x2c + iVar11);
                  *(undefined4 *)(piVar6->field591_0x300 + 0x38 + iVar11) =
                       *(undefined4 *)(piVar6->field591_0x300 + 0x2c + iVar11);
                  local_3c8 = 0x2ee - *(int *)(piVar6->field591_0x300 + 100 + iVar11);
                  uVar6 = ((*(uint *)(piVar6->field486_0x264 +
                                     *(int *)(piVar6->field484_0x25c + local_3cc * 4) * 4) >> 0x1d &
                           1) + 1) * uVar7 * 2;
                  local_3bc = 1000;
                  local_3c4 = CONCAT44(local_3c4._4_4_,uVar6);
                  *(uint *)(piVar6->field591_0x300 + 0x4c + iVar11) =
                       (uint)(((ulonglong)uVar6 * (ulonglong)local_3c8) / 1000) & 0xfffffffc;
                  iVar9 = piVar6->field591_0x300;
                  uVar6 = *(uint *)(iVar9 + 0x28 + iVar11);
                  if (uVar6 < *(uint *)(iVar9 + 0x4c + iVar11)) {
                    *(uint *)(iVar9 + iVar11 + 0x4c) = uVar6;
                  }
                  uVar6 = *(uint *)(piVar6->field486_0x264 +
                                   *(int *)(piVar6->field484_0x25c + local_3cc * 4) * 4);
                  if (((int)uVar6 < 0) || ((uVar6 & 0x10000000) == 0)) {
                    uVar10 = 0;
                  }
                  else {
                    uVar10 = 1;
                  }
                  uVar10 = FUN_001a9620(uVar6 & 0xffff,(uVar6 >> 0x1d & 1) + 1,uVar10);
                  *(undefined4 *)(piVar6->field591_0x300 + 0x3c + iVar11) = uVar10;
                  *(uint *)(piVar6->field591_0x300 + 0x48 + iVar11) =
                       piVar6->field5_0x8 -
                       (uint)(piVar6->field553_0x2bc * 3) / (uint)(piVar6->field554_0x2c0 << 2);
                  *(undefined4 *)(piVar6->field591_0x300 + 0x40 + iVar11) = 0;
                }
              }
            }
LAB_001a6de9:
            if (*(int *)(piVar6->field591_0x300 + 0x68 + iVar11) == 0) {
              *(undefined4 *)(piVar6->field591_0x300 + 0x68 + iVar11) = 0x10000;
            }
            if (*(int *)(piVar6->field591_0x300 + 0x2c + iVar11) == 0) {
              uVar6 = piVar6->field586_0x2f8 - 1;
              puVar15 = (undefined4 *)(piVar6->field484_0x25c + local_3cc * 4);
              piVar6->field586_0x2f8 = uVar6;
              puVar18 = puVar15;
              for (uVar6 = uVar6 - local_3cc & 0x3fffffff; puVar15 = puVar15 + 1, uVar6 != 0;
                  uVar6 = uVar6 - 1) {
                *puVar18 = *puVar15;
                puVar18 = puVar18 + 1;
              }
              for (iVar9 = 0; iVar9 != 0; iVar9 = iVar9 + -1) {
                *(undefined1 *)puVar18 = *(undefined1 *)puVar15;
                puVar15 = (undefined4 *)((int)puVar15 + 1);
                puVar18 = (undefined4 *)((int)puVar18 + 1);
              }
            }
            else {
              local_3cc = local_3cc + 1;
              iVar11 = iVar11 + 0x178;
            }
          } while (local_3cc < piVar6->field586_0x2f8);
        }
        if (piVar6->field586_0x2f8 != 0) {
          bVar19 = DAT_0054f7d0 == 0;
          piVar6->field537_0x2a0 = 1;
          if (bVar19) {
            DAT_0054f7d0 = FUN_001a87d0(0xfffffff3);
            FUN_001a89b0(DAT_0054f7d0);
          }
          FUN_001a8880(DAT_0054f7d0,&piVar6->field664_0x34c,&LAB_001a5fb0,FUN_001a5fd0);
        }
        if (((piVar6->field17_0x20 & 0x8000000) == 0) && (piVar6->field195_0x108 == (char *)0x0)) {
          if (DAT_0054f7cc == 0) {
            DAT_0054f7cc = FUN_001a87d0(5);
            FUN_001a89b0(DAT_0054f7cc);
          }
          FUN_001a8880(DAT_0054f7cc,&piVar6->field413_0x20c,&LAB_001a5ed0,FUN_001a5f20);
        }
        piVar6->field411_0x204 = &LAB_001a5f80;
        piVar6->field409_0x1fc = &LAB_001a5f40;
        piVar6->field410_0x200 = &LAB_001a5f60;
        piVar6->field412_0x208 = &LAB_001a5fa0;
        if ((piVar6->field195_0x108 == (char *)0x0) && ((flags & 0x200000) == 0)) {
          do {
            iVar11 = (*(code *)piVar6->field201_0x120)(&piVar6->field197_0x110);
          } while (iVar11 != 0);
        }
        return piVar6;
      }
      ppuVar1 = &piVar6->field197_0x110;
      uVar6 = (*(code *)piVar6->field199_0x118)(ppuVar1,piVar6->field475_0x250);
      iVar11 = piVar6->field22_0x28;
      piVar6->field475_0x250 = uVar6;
      if ((uint)(iVar11 * 9) / 10 <= uVar6) {
        flags = flags | 0x2000;
        piVar6->field17_0x20 = piVar6->field17_0x20 | 0x2000;
      }
      if ((flags & 0x2000) == 0) {
        ReadBinkChunk(&piVar6->field194_0x104,piVar6->field181_0xe8);
        iVar11 = FUN_001a59e0();
        piVar6->field474_0x24c = iVar11;
        if (iVar11 == 0) {
          piVar6->field475_0x250 = 0;
        }
        (*(code *)piVar6->field200_0x11c)
                  (ppuVar1,iVar11,piVar6->field475_0x250,piVar6->field22_0x28 + 8,local_3c8);
        goto LAB_001a699b;
      }
      uVar6 = *piVar6->field196_0x10c;
      pcVar8 = (char *)FUN_001a59e0();
      piVar6->field195_0x108 = pcVar8;
      if (pcVar8 != (char *)0x0) {
        (*(code *)piVar6->field200_0x11c)(ppuVar1,0,0,piVar6->field22_0x28 + 8,local_3c8);
        (*(code *)piVar6->field198_0x114)
                  (ppuVar1,0,*piVar6->field196_0x10c & 0xfffffffe,piVar6->field195_0x108,
                   (iVar11 - (uVar6 & 0xfffffffe)) + 8);
        (*(code *)piVar6->field202_0x124)(ppuVar1);
        piVar6->field224_0x140 = 0;
        goto LAB_001a699b;
      }
      FUN_0015d410(uStack_2d0);
    }
    FUN_0015d410(piVar6);
  }
  c_i = 0;
  do {
    c = "Out of memory."[c_i];
    g_ReadFileError[c_i] = c;
    c_i = c_i + 1;
  } while (c != '\0');
LAB_001a68e1:
  if ((flags & 0x4000000) == 0) {
    (*local_268)(local_27c);
  }
  return (MovieChunk *)0x0;
}



uint FUN_001a6f60(uint *param_1,int param_2,int param_3,int param_4,undefined4 param_5,int param_6,
                 uint param_7,uint param_8,uint param_9,uint param_10,uint param_11)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  longlong lVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  char *pcVar11;
  uint uVar12;
  uint local_8;
  
  local_8 = 0;
  if ((param_1 == (uint *)0x0) || (param_2 == 0)) {
    return 0;
  }
  uVar5 = (uint)(((ulonglong)param_7 * (ulonglong)param_1[0x95]) / (ulonglong)*param_1);
  iVar6 = (int)(((ulonglong)param_9 * (ulonglong)param_1[0x95]) / (ulonglong)*param_1);
  uVar7 = (uint)(((ulonglong)param_8 * (ulonglong)param_1[0x96]) / (ulonglong)param_1[1]);
  param_10 = (uint)(((ulonglong)param_10 * (ulonglong)param_1[0x96]) / (ulonglong)param_1[1]);
  uVar3 = param_1[0x95];
  if (uVar3 <= uVar5) {
    uVar5 = uVar3;
  }
  uVar12 = param_1[0x96];
  if (uVar12 <= uVar7) {
    uVar7 = uVar12;
  }
  if (uVar3 < uVar5 + iVar6) {
    iVar6 = uVar3 - uVar5;
  }
  if (uVar12 < uVar7 + param_10) {
    param_10 = uVar12 - uVar7;
  }
  if (((iVar6 == 0) || (param_10 == 0)) || (param_1[0xc2] != 0)) {
    return param_1[0xc2];
  }
  uVar12 = param_11 | param_1[8] & 0x70030000;
  uVar3 = param_11 & 0xf;
  param_1[0x4e] = 1;
  FUN_001afae0(uVar3);
  if (param_3 < 0) {
    param_2 = param_2 - ((param_4 - param_6) + -1) * param_3;
    param_6 = 0;
  }
  if (((param_1[0xbe] != 0) && (param_1[5] != 0)) && (param_1[0x3f] == 0)) {
    FUN_001a5d30();
    iVar8 = FUN_001a8e80();
    lVar4 = (((ulonglong)((param_1[0x9c] - param_1[0xa1]) * 1000) * (ulonglong)param_1[6]) /
             (ulonglong)param_1[5] & 0xffffffff) * (ulonglong)*(uint *)(param_1[0xc0] + 0x68);
    uVar9 = (uint)lVar4 >> 0x10 | (int)((ulonglong)lVar4 >> 0x20) << 0x10;
    uVar10 = (iVar8 - param_1[0xce]) - param_1[0xa0];
    if (uVar9 <= uVar10) {
      if (param_1[0xa2] < uVar10 - uVar9) {
        uVar9 = param_1[0xcd];
        param_1[0xcd] = uVar9 + 1;
        if (uVar9 + 1 < 4) {
          if (((param_11 & 0x80000) == 0) && ((param_1[8] & 0x80000) == 0)) {
            param_1[0xc1] = 1;
            param_1[0xc3] = param_1[0xc3] + 1;
            param_1[0x4e] = 0;
            return 1;
          }
          local_8 = 1;
        }
        else {
          param_1[0xcd] = 0;
        }
        goto LAB_001a7200;
      }
      param_1[0xcd] = 0;
    }
    param_1[0xc1] = 0;
  }
LAB_001a7200:
  if (((param_1[0x42] == 0) && (param_1[0x4c] == 0)) &&
     (((param_1[0x56] + 1) * 100) / (param_1[0x55] + 1) < 0x4b)) {
    iVar8 = FUN_001a8a50(DAT_0054f7cc,param_1 + 0x83);
    if (iVar8 == 0) {
      if ((param_1[8] & 0x8000000) == 0) {
        FUN_001a8c20();
      }
    }
    else {
      (*(code *)param_1[0x48])(param_1 + 0x44);
      FUN_001a8b10(DAT_0054f7cc,param_1 + 0x83);
    }
  }
  param_1[0xba] = uVar12;
  if (-1 < (int)uVar12) {
    pcVar11 = (char *)param_1[0x37];
    pcVar1 = pcVar11 + 1;
    do {
      cVar2 = *pcVar11;
      pcVar11 = pcVar11 + 1;
    } while (cVar2 != '\0');
    if (param_1[0x39] <= (uint)((int)pcVar11 - (int)pcVar1)) goto switchD_001a72b7_switchD;
    switch(uVar3) {
    case 5:
      if (param_1[0x31] != 0) {
        FUN_001b4d90(param_2,param_5,param_6,param_3,param_1[0x37],param_1[0x38],
                     param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,param_10,param_1[0x33],
                     param_1[0x34],param_1[param_1[0x2e] + 0x31],uVar12);
        param_1[0x4e] = 0;
        return local_8;
      }
    case 3:
      FUN_001b39a0(param_2,param_5,param_6,param_3,param_1[0x37],param_1[0x38],
                   param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,param_10,param_1[0x33],
                   param_1[0x34],uVar12);
      param_1[0x4e] = 0;
      return local_8;
    case 7:
      if (param_1[0x31] != 0) {
        FUN_001b7530(param_2,param_5,param_6,param_3,param_1[0x37],param_1[0x38],
                     param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,param_10,param_1[0x33],
                     param_1[0x34],param_1[param_1[0x2e] + 0x31],uVar12);
        param_1[0x4e] = 0;
        return local_8;
      }
      break;
    case 8:
      if (param_1[0x31] != 0) {
        FUN_001b85e0(param_2,param_5,param_6,param_3,param_1[0x37],param_1[0x38],
                     param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,param_10,param_1[0x33],
                     param_1[0x34],param_1[param_1[0x2e] + 0x31],uVar12);
        param_1[0x4e] = 0;
        return local_8;
      }
      break;
    case 9:
    case 10:
    case 0xb:
    case 0xc:
      break;
    case 0xd:
      FUN_001b9700(param_2,param_5,param_6,param_3,param_1[0x37],param_1[0x38],
                   param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,param_10,param_1[0x33],
                   param_1[0x34],uVar12);
    default:
switchD_001a72b7_caseD_4:
      param_1[0x4e] = 0;
      return local_8;
    }
    FUN_001b6080(param_2,param_5,param_6,param_3,param_1[0x37],param_1[0x38],
                 param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,param_10,param_1[0x33],
                 param_1[0x34],uVar12);
    param_1[0x4e] = 0;
    return local_8;
  }
switchD_001a72b7_switchD:
  switch(uVar3) {
  default:
    goto switchD_001a72b7_caseD_4;
  case 5:
    if (param_1[0x31] != 0) {
      FUN_001b4d40(param_2,param_5,param_6,param_3,param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,
                   param_10,param_1[0x33],param_1[0x34],param_1[param_1[0x2e] + 0x31],uVar12);
      param_1[0x4e] = 0;
      return local_8;
    }
  case 3:
    FUN_001b3950(param_2,param_5,param_6,param_3,param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,
                 param_10,param_1[0x33],param_1[0x34],uVar12);
    param_1[0x4e] = 0;
    return local_8;
  case 7:
    if (param_1[0x31] != 0) {
      FUN_001b74e0(param_2,param_5,param_6,param_3,param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,
                   param_10,param_1[0x33],param_1[0x34],param_1[param_1[0x2e] + 0x31],uVar12);
      param_1[0x4e] = 0;
      return local_8;
    }
    break;
  case 8:
    if (param_1[0x31] != 0) {
      FUN_001b8590(param_2,param_5,param_6,param_3,param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,
                   param_10,param_1[0x33],param_1[0x34],param_1[param_1[0x2e] + 0x31],uVar12);
      param_1[0x4e] = 0;
      return local_8;
    }
    break;
  case 9:
  case 10:
  case 0xb:
  case 0xc:
    break;
  case 0xd:
    FUN_001b9680(param_2,param_5,param_6,param_3,param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,
                 param_10,param_1[0x33],param_1[0x34],uVar12);
    param_1[0x4e] = 0;
    return local_8;
  }
  FUN_001b6030(param_2,param_5,param_6,param_3,param_1[param_1[0x2e] + 0x2f],uVar5,uVar7,iVar6,
               param_10,param_1[0x33],param_1[0x34],uVar12);
  param_1[0x4e] = 0;
  return local_8;
}




void ReadBinkHeader_(uint *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_2 >> 3;
  param_1[1] = (param_2 >> 4) + 0x203 & 0xfffffffc;
  uVar1 = uVar2 + 0x203 & 0xfffffffc;
  *param_1 = uVar1;
  param_1[4] = uVar1;
  param_1[5] = uVar1;
  uVar1 = (uVar2 & 0xfffffff) * 2 + 0x403 & 0xfffffffc;
  param_1[2] = (uVar2 * 8 & 0x3ffffff) * 8 + 0x200;
  param_1[6] = uVar1;
  param_1[7] = uVar1;
  param_1[3] = (uVar2 & 0x3ffffff) * 8 + 0x200;
  param_1[8] = (uVar2 * 0x18 & 0xfffffff) * 2 + 0x200;
  return;
}



// WARNING (jumptable): Unable to track spacebase fully for stack
// WARNING: Restarted to delay deadcode elimination for space: stack

uint * BigConversionFunction_
                 (uint *param_1,uint *param_2,uint param_3,uint param_4,uint param_5,
                 undefined4 param_6,uint *param_7,uint param_8,uint *param_9,uint param_10)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  int iVar10;
  uint uVar11;
  byte bVar12;
  int iVar13;
  uint uVar14;
  ushort *puVar15;
  uint *puVar16;
  int iVar17;
  uint uVar18;
  uint *puVar19;
  uint *puVar20;
  uint uVar21;
  uint uVar22;
  int iVar23;
  undefined1 local_428 [388];
  undefined2 local_2a4 [64];
  undefined2 *local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  uint local_1fc;
  undefined4 local_1f8;
  undefined2 *local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  uint local_1cc;
  undefined4 local_1c8;
  undefined1 *local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined1 local_1b4 [16];
  undefined1 local_1a4 [4];
  undefined1 local_1a0 [4];
  uint local_19c;
  undefined4 local_198;
  undefined1 *local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined1 local_184 [16];
  undefined1 local_174 [4];
  undefined1 local_170 [4];
  uint local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  char *local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined1 local_114 [16];
  undefined1 local_104 [4];
  undefined1 local_100 [4];
  uint local_fc;
  undefined4 local_f8;
  char *local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined1 local_e4 [16];
  undefined1 local_d4 [4];
  undefined1 local_d0 [4];
  uint local_cc;
  undefined4 local_c8;
  byte *local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined1 local_b4 [16];
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  uint local_9c;
  undefined4 local_98;
  int local_94;
  code *local_90;
  int local_8c;
  int local_88;
  byte *local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined1 local_74 [16];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  uint local_5c;
  undefined4 local_58;
  uint *local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_2c;
  undefined4 local_28;
  uint local_24;
  uint *local_20;
  int local_1c;
  uint local_18;
  uint *local_14 [2];
  uint local_c;
  uint local_8;
  
  local_94 = param_5 * 8 - param_3;
  local_20 = param_2;
  local_1c = (int)param_7;
  local_18 = 0;
  local_90 = FUN_001aac70;
  local_8c = (int)((ulonglong)param_5 / (0x10 / (ulonglong)param_8));
  local_8 = 0;
  local_c = 0;
  if (-1 < (char)(param_10 >> 8)) {
    local_90 = FUN_001aaf50;
  }
  local_168 = *param_9;
  uVar22 = param_3 >> 3;
  uVar14 = uVar22 + 0x1ff;
  if (uVar14 < 129) {
    local_16c = (uint)(byte)(&DAT_002047f7)[uVar22];
  }
  else if (uVar14 < 0x800) {
    if (uVar14 < 0x200) {
      local_16c = 9 - (uVar14 < 0x100);
    }
    else {
      local_16c = 0xb - (uVar14 < 0x400);
    }
  }
  else if (uVar14 < 0x2000) {
    local_16c = 0xd - (uVar14 < 0x1000);
  }
  else {
    local_16c = 0xf - (uVar14 < 0x4000);
  }
  local_194 = (undefined1 *)0x0;
  local_190 = 0;
  local_188 = 0;
  local_198 = param_9[1];
  uVar21 = (param_3 >> 4) + 0x1ff;
  local_18c = 4;
  if (uVar21 < 0x81) {
    local_19c = (uint)(byte)(&DAT_002047f7)[param_3 >> 4];
  }
  else if (uVar21 < 0x800) {
    if (uVar21 < 0x200) {
      local_19c = 9 - (uVar21 < 0x100);
    }
    else {
      local_19c = 0xb - (uVar21 < 0x400);
    }
  }
  else if (uVar21 < 0x2000) {
    local_19c = 0xd - (uVar21 < 0x1000);
  }
  else {
    local_19c = 0xf - (uVar21 < 0x4000);
  }
  local_1c4 = (undefined1 *)0x0;
  local_1c0 = 0;
  local_1b8 = 0;
  local_28 = param_9[2];
  uVar21 = uVar22 * 0x40 + 0x1ff;
  local_1bc = 4;
  if (uVar21 < 0x81) {
    local_2c = (uint)(byte)(&DAT_002047f7)[uVar22 * 0x40];
  }
  else if (uVar21 < 0x800) {
    if (uVar21 < 0x200) {
      local_2c = 9 - (uVar21 < 0x100);
    }
    else {
      local_2c = 0xb - (uVar21 < 0x400);
    }
  }
  else if (uVar21 < 0x2000) {
    local_2c = 0xd - (uVar21 < 0x1000);
  }
  else {
    local_2c = 0xf - (uVar21 < 0x4000);
  }
  local_58 = param_9[3];
  uVar21 = uVar22 * 8 + 0x1ff;
  local_54 = (uint *)0x0;
  local_50 = 0;
  local_4c = 8;
  local_48 = 0;
  if (uVar21 < 0x81) {
    local_5c = (uint)(byte)(&DAT_002047f7)[uVar22 * 8];
  }
  else if (uVar21 < 0x800) {
    if (uVar21 < 0x200) {
      local_5c = 9 - (uVar21 < 0x100);
    }
    else {
      local_5c = 0xb - (uVar21 < 0x400);
    }
  }
  else if (uVar21 < 0x2000) {
    local_5c = 0xd - (uVar21 < 0x1000);
  }
  else {
    local_5c = 0xf - (uVar21 < 0x4000);
  }
  local_f8 = param_9[4];
  local_84 = (byte *)0x0;
  local_80 = 0;
  local_7c = 8;
  local_78 = 0;
  if (uVar14 < 0x81) {
    local_fc = (uint)(byte)(&DAT_002047f7)[uVar22];
  }
  else if (uVar14 < 0x800) {
    if (uVar14 < 0x200) {
      local_fc = 9 - (uVar14 < 0x100);
    }
    else {
      local_fc = 0xb - (uVar14 < 0x400);
    }
  }
  else if (uVar14 < 0x2000) {
    local_fc = 0xd - (uVar14 < 0x1000);
  }
  else {
    local_fc = 0xf - (uVar14 < 0x4000);
  }
  local_c8 = param_9[5];
  local_124 = (char *)0x0;
  local_120 = 0;
  local_11c = 5;
  local_118 = 0x10;
  if (uVar14 < 0x81) {
    local_cc = (uint)(byte)(&DAT_002047f7)[uVar22];
  }
  else if (uVar14 < 0x800) {
    if (uVar14 < 0x200) {
      local_cc = 9 - (uVar14 < 0x100);
    }
    else {
      local_cc = 0xb - (uVar14 < 0x400);
    }
  }
  else if (uVar14 < 0x2000) {
    local_cc = 0xd - (uVar14 < 0x1000);
  }
  else {
    local_cc = 0xf - (uVar14 < 0x4000);
  }
  local_1c8 = param_9[6];
  local_f4 = (char *)0x0;
  local_f0 = 0;
  local_ec = 5;
  local_e8 = 0x10;
  if (uVar14 < 0x81) {
    local_1cc = (uint)(byte)(&DAT_002047f7)[uVar22];
  }
  else if (uVar14 < 0x800) {
    if (uVar14 < 0x200) {
      local_1cc = 9 - (uVar14 < 0x100);
    }
    else {
      local_1cc = 0xb - (uVar14 < 0x400);
    }
  }
  else if (uVar14 < 0x2000) {
    local_1cc = 0xd - (uVar14 < 0x1000);
  }
  else {
    local_1cc = 0xf - (uVar14 < 0x4000);
  }
  local_1f8 = param_9[7];
  local_1f4 = (undefined2 *)0x0;
  local_1f0 = 0;
  local_1ec = 0xb;
  local_1e8 = 0;
  if (uVar14 < 0x81) {
    local_1fc = (uint)(byte)(&DAT_002047f7)[uVar22];
  }
  else if (uVar14 < 0x800) {
    if (uVar14 < 0x200) {
      local_1fc = 9 - (uVar14 < 0x100);
    }
    else {
      local_1fc = 0xb - (uVar14 < 0x400);
    }
  }
  else if (uVar14 < 0x2000) {
    local_1fc = 0xd - (uVar14 < 0x1000);
  }
  else {
    local_1fc = 0xf - (uVar14 < 0x4000);
  }
  uVar14 = uVar22 * 0x30 + 0x1ff;
  local_224 = (undefined2 *)0x0;
  local_220 = 0;
  local_98 = param_9[8];
  local_21c = 0xb;
  local_218 = 0x400;
  if (uVar14 < 0x81) {
    local_9c = (uint)(byte)(&DAT_002047f7)[uVar22 * 0x30];
  }
  else if (uVar14 < 0x800) {
    if (uVar14 < 0x200) {
      local_9c = 9 - (uVar14 < 0x100);
    }
    else {
      local_9c = 0xb - (uVar14 < 0x400);
    }
  }
  else if (uVar14 < 0x2000) {
    local_9c = 0xd - (uVar14 < 0x1000);
  }
  else {
    local_9c = 0xf - (uVar14 < 0x4000);
  }
  local_c4 = (byte *)0x0;
  local_c0 = 0;
  local_bc = 4;
  local_b8 = 0;
  FUN_001aa5e0(local_14,local_170,local_174,local_184);
  FUN_001aa5e0(local_14,local_1a0,local_1a4,local_1b4);
  FUN_001aa9a0(&local_54,local_14,local_428);
  FUN_001aa5e0(local_14,local_60,local_64,local_74);
  FUN_001aa5e0(local_14,local_100,local_104,local_114);
  FUN_001aa5e0(local_14,local_d0,local_d4,local_e4);
  FUN_001aa5e0(local_14,local_a0,local_a4,local_b4);
  local_24 = 0;
  if (param_4 != 0) {
    do {
      uVar21 = 0;
      FUN_001aaa10(&local_194,local_14);
      FUN_001aaa10(&local_1c4,local_14);
      (*local_90)(&local_54,local_14,local_428);
      FUN_001ab3f0(local_14);
      FUN_001ab5f0(&local_124,local_14);
      FUN_001ab5f0(&local_f4,local_14);
      FUN_001ab860(&local_1f4,local_14);
      FUN_001ab860(&local_224,local_14);
      FUN_001ab200(&local_c4,local_14);
      puVar19 = local_54;
      uVar11 = local_18;
      uVar14 = local_c;
      uVar22 = local_c;
      for (param_10 = param_3; local_c = uVar22, param_10 != 0; param_10 = param_10 - 8) {
        uVar4 = *local_194;
        local_194 = local_194 + 1;
        bVar12 = (byte)local_8;
        local_18 = uVar11;
        switch(uVar4) {
        case 0:
          uVar14 = local_20[1];
          uVar5 = *(undefined4 *)((int)local_20 + param_5);
          uVar6 = *(undefined4 *)((int)local_20 + param_5 + 4);
          puVar1 = (undefined4 *)((int)local_20 + param_5 * 2);
          *param_1 = *local_20;
          param_1[1] = uVar14;
          *(undefined4 *)((int)param_1 + param_5) = uVar5;
          *(undefined4 *)((int)param_1 + param_5 + 4) = uVar6;
          puVar2 = (undefined4 *)((int)param_1 + param_5 * 2);
          uVar5 = puVar1[1];
          uVar6 = *(undefined4 *)((int)puVar1 + param_5);
          uVar7 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          puVar3 = (undefined4 *)((int)puVar1 + param_5 * 2);
          *puVar2 = *puVar1;
          puVar2[1] = uVar5;
          *(undefined4 *)((int)puVar2 + param_5) = uVar6;
          *(undefined4 *)((int)puVar2 + param_5 + 4) = uVar7;
          puVar2 = (undefined4 *)((int)puVar2 + param_5 * 2);
          uVar5 = puVar3[1];
          uVar6 = *(undefined4 *)((int)puVar3 + param_5);
          uVar7 = *(undefined4 *)((int)puVar3 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar3 + param_5 * 2);
          *puVar2 = *puVar3;
          puVar2[1] = uVar5;
          *(undefined4 *)((int)puVar2 + param_5) = uVar6;
          *(undefined4 *)((int)puVar2 + param_5 + 4) = uVar7;
          puVar2 = (undefined4 *)((int)puVar2 + param_5 * 2);
          uVar5 = puVar1[1];
          uVar6 = *(undefined4 *)((int)puVar1 + param_5);
          uVar7 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          *puVar2 = *puVar1;
          puVar2[1] = uVar5;
          *(undefined4 *)((int)puVar2 + param_5) = uVar6;
          *(undefined4 *)((int)puVar2 + param_5 + 4) = uVar7;
          puVar19 = local_54;
          uVar21 = uVar11;
          uVar14 = uVar22;
          break;
        case 1:
          local_18 = uVar21;
          if ((local_24 & 8) == 0) {
            uVar4 = *local_1c4;
            local_1c4 = local_1c4 + 1;
            switch(uVar4) {
            case 3:
              if (local_8 < 4) {
                uVar14 = *local_14[0] << (bVar12 & 0x1f) | uVar14;
                uVar22 = *local_14[0] >> (4 - bVar12 & 0x1f);
                local_8 = local_8 + 0x1c;
                local_14[0] = local_14[0] + 1;
              }
              else {
                uVar22 = uVar14 >> 4;
                local_8 = local_8 - 4;
              }
              iVar17 = (uVar14 & 0xf) * 0x40;
              iVar23 = 0;
              local_18 = uVar11;
              do {
                if (local_8 == 0) {
                  uVar14 = *local_14[0];
                  local_14[0] = local_14[0] + 1;
                  local_8 = 0x1f;
                }
                else {
                  local_8 = local_8 - 1;
                  uVar14 = uVar22;
                }
                uVar22 = uVar14 >> 1;
                local_c = uVar22;
                if ((uVar14 & 1) == 0) {
                  bVar12 = *local_c4;
                  local_c4 = local_c4 + 1;
                  for (iVar13 = bVar12 + 1; iVar13 != 0; iVar13 = iVar13 + -1) {
                    *(char *)((int)&local_164 + (uint)(byte)(&DAT_00208768)[iVar23 + iVar17]) =
                         (char)*puVar19;
                    iVar23 = iVar23 + 1;
                    puVar19 = (uint *)((int)puVar19 + 1);
                    local_54 = puVar19;
                  }
                }
                else {
                  uVar14 = *puVar19;
                  puVar19 = (uint *)((int)puVar19 + 1);
                  bVar12 = *local_c4;
                  local_c4 = local_c4 + 1;
                  local_54 = puVar19;
                  for (iVar13 = bVar12 + 1; iVar13 != 0; iVar13 = iVar13 + -1) {
                    *(char *)((int)&local_164 + (uint)(byte)(&DAT_00208768)[iVar23 + iVar17]) =
                         (char)uVar14;
                    iVar23 = iVar23 + 1;
                  }
                }
              } while (iVar23 < 0x3f);
              if (iVar23 == 0x3f) {
                uVar14 = *puVar19;
                puVar19 = (uint *)((int)puVar19 + 1);
                *(char *)((int)&local_164 + (uint)(byte)(&DAT_002087a7)[iVar17]) = (char)uVar14;
                local_54 = puVar19;
              }
              puVar15 = (ushort *)&local_160;
              param_7 = (uint *)0x2;
              puVar20 = param_1;
              do {
                param_9 = (uint *)((int)puVar20 + param_5);
                uVar14 = (uint)puVar15[-2];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                *puVar20 = uVar14;
                *param_9 = uVar14;
                uVar14 = (uint)puVar15[-1];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar20[1] = uVar14;
                param_9[1] = uVar14;
                uVar14 = (uint)*puVar15;
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar20[2] = uVar14;
                param_9[2] = uVar14;
                uVar14 = (uint)puVar15[1];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                uVar22 = (uint)puVar15[2];
                puVar20[3] = uVar14;
                param_9[3] = uVar14;
                param_9 = (uint *)((int)param_9 + param_5);
                puVar20 = (uint *)((int)param_9 + param_5);
                uVar14 = ((uVar22 & 0xffffff00) << 8 | uVar22) << 8 | uVar22 & 0xff;
                *param_9 = uVar14;
                *puVar20 = uVar14;
                uVar14 = (uint)puVar15[3];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                param_9[1] = uVar14;
                puVar20[1] = uVar14;
                uVar14 = (uint)puVar15[4];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                param_9[2] = uVar14;
                puVar20[2] = uVar14;
                uVar14 = (uint)puVar15[5];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                param_9[3] = uVar14;
                puVar20[3] = uVar14;
                uVar14 = (uint)puVar15[6];
                puVar20 = (uint *)((int)puVar20 + param_5);
                puVar16 = (uint *)((int)puVar20 + param_5);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                *puVar20 = uVar14;
                *puVar16 = uVar14;
                uVar14 = (uint)puVar15[7];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar20[1] = uVar14;
                puVar16[1] = uVar14;
                uVar14 = (uint)puVar15[8];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar20[2] = uVar14;
                puVar16[2] = uVar14;
                uVar14 = (uint)puVar15[9];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                uVar22 = (uint)puVar15[10];
                puVar20[3] = uVar14;
                puVar16[3] = uVar14;
                puVar16 = (uint *)((int)puVar16 + param_5);
                puVar20 = (uint *)((int)puVar16 + param_5);
                uVar14 = ((uVar22 & 0xffffff00) << 8 | uVar22) << 8 | uVar22 & 0xff;
                *puVar16 = uVar14;
                *puVar20 = uVar14;
                uVar14 = (uint)puVar15[0xb];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[1] = uVar14;
                puVar20[1] = uVar14;
                uVar14 = (uint)puVar15[0xc];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[2] = uVar14;
                puVar20[2] = uVar14;
                uVar14 = (uint)puVar15[0xd];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[3] = uVar14;
                puVar20[3] = uVar14;
                puVar20 = (uint *)((int)puVar20 + param_5);
                puVar15 = puVar15 + 0x10;
                param_7 = (uint *)((int)param_7 + -1);
                uVar14 = local_c;
              } while (param_7 != (uint *)0x0);
              break;
            case 5:
              local_2a4[0] = *local_1f4;
              local_1f4 = local_1f4 + 1;
              local_18 = uVar11;
              FUN_001b1c20(local_2a4,local_14);
              if (local_8 < 4) {
                uVar14 = *local_14[0] << ((byte)local_8 & 0x1f) | local_c;
                local_c = *local_14[0] >> (4 - (byte)local_8 & 0x1f);
                local_8 = local_8 + 0x1c;
                local_14[0] = local_14[0] + 1;
              }
              else {
                local_8 = local_8 - 4;
                uVar14 = local_c;
                local_c = local_c >> 4;
              }
              FUN_001b1470(param_1,param_5,local_2a4,(ushort)uVar14 & 0xf);
              puVar19 = local_54;
              local_18 = uVar21;
              uVar14 = local_c;
              break;
            case 6:
              uVar8 = CONCAT11((char)*puVar19,(char)*puVar19);
              puVar19 = (uint *)((int)puVar19 + 1);
              uVar14 = CONCAT22(uVar8,uVar8);
              *param_1 = uVar14;
              param_1[1] = uVar14;
              param_1[2] = uVar14;
              param_1[3] = uVar14;
              *(uint *)((int)param_1 + param_5) = uVar14;
              *(uint *)((int)param_1 + param_5 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 + 0xc) = uVar14;
              *(uint *)((int)param_1 + param_5 * 2) = uVar14;
              *(uint *)((int)param_1 + param_5 * 2 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 * 2 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 * 2 + 0xc) = uVar14;
              *(uint *)((int)param_1 + param_5 * 3) = uVar14;
              *(uint *)((int)param_1 + param_5 * 3 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 * 3 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 * 3 + 0xc) = uVar14;
              param_1[param_5] = uVar14;
              param_1[param_5 + 1] = uVar14;
              param_1[param_5 + 2] = uVar14;
              param_1[param_5 + 3] = uVar14;
              *(uint *)((int)param_1 + param_5 * 5) = uVar14;
              *(uint *)((int)param_1 + param_5 * 5 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 * 5 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 * 5 + 0xc) = uVar14;
              *(uint *)((int)param_1 + param_5 * 6) = uVar14;
              *(uint *)((int)param_1 + param_5 * 6 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 * 6 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 * 6 + 0xc) = uVar14;
              *(uint *)((int)param_1 + param_5 * 7) = uVar14;
              *(uint *)((int)param_1 + param_5 * 7 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 * 7 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 * 7 + 0xc) = uVar14;
              param_1[param_5 * 2] = uVar14;
              param_1[param_5 * 2 + 1] = uVar14;
              param_1[param_5 * 2 + 2] = uVar14;
              param_1[param_5 * 2 + 3] = uVar14;
              *(uint *)((int)param_1 + param_5 * 9) = uVar14;
              *(uint *)((int)param_1 + param_5 * 9 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 * 9 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 * 9 + 0xc) = uVar14;
              *(uint *)((int)param_1 + param_5 * 10) = uVar14;
              *(uint *)((int)param_1 + param_5 * 10 + 4) = uVar14;
              *(uint *)((int)param_1 + param_5 * 10 + 8) = uVar14;
              *(uint *)((int)param_1 + param_5 * 10 + 0xc) = uVar14;
              puVar20 = (uint *)((int)param_1 + param_5 * 0xb);
              puVar16 = (uint *)((int)puVar20 + param_5);
              *puVar20 = uVar14;
              puVar20[1] = uVar14;
              puVar20[2] = uVar14;
              puVar20[3] = uVar14;
              puVar20 = (uint *)((int)puVar16 + param_5);
              *puVar16 = uVar14;
              puVar16[1] = uVar14;
              puVar16[2] = uVar14;
              puVar16[3] = uVar14;
              puVar16 = (uint *)((int)puVar20 + param_5);
              *puVar20 = uVar14;
              puVar20[1] = uVar14;
              puVar20[2] = uVar14;
              puVar20[3] = uVar14;
              *puVar16 = uVar14;
              puVar16[1] = uVar14;
              puVar16[2] = uVar14;
              puVar16[3] = uVar14;
              *(uint *)((int)puVar16 + param_5) = uVar14;
              *(uint *)((int)puVar16 + param_5 + 4) = uVar14;
              *(uint *)((int)puVar16 + param_5 + 8) = uVar14;
              *(uint *)((int)puVar16 + param_5 + 0xc) = uVar14;
              uVar14 = uVar22;
              local_54 = puVar19;
              break;
            case 8:
              uVar8 = CONCAT11((char)*puVar19,(char)*puVar19);
              uVar9 = CONCAT11(*(undefined1 *)((int)puVar19 + 1),*(undefined1 *)((int)puVar19 + 1));
              uVar21 = CONCAT22(uVar8,uVar8);
              uVar18 = CONCAT22(uVar9,uVar9);
              puVar19 = (uint *)((int)puVar19 + 2);
              local_88 = 2;
              param_9 = param_1;
              do {
                param_7 = (uint *)((int)param_9 + param_5);
                bVar12 = *local_84;
                iVar23 = (bVar12 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                *param_9 = uVar14;
                *param_7 = uVar14;
                iVar23 = (bVar12 >> 2 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                param_9[1] = uVar14;
                param_7[1] = uVar14;
                iVar23 = (bVar12 >> 4 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                param_9[2] = uVar14;
                param_7[2] = uVar14;
                iVar23 = (uint)(bVar12 >> 6) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                param_9[3] = uVar14;
                param_7[3] = uVar14;
                param_7 = (uint *)((int)param_7 + param_5);
                puVar20 = (uint *)((int)param_7 + param_5);
                bVar12 = local_84[1];
                iVar23 = (bVar12 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                *param_7 = uVar14;
                *puVar20 = uVar14;
                iVar23 = (bVar12 >> 2 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                param_7[1] = uVar14;
                puVar20[1] = uVar14;
                iVar23 = (bVar12 >> 4 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                param_7[2] = uVar14;
                puVar20[2] = uVar14;
                iVar23 = (uint)(bVar12 >> 6) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                param_7[3] = uVar14;
                puVar20[3] = uVar14;
                puVar20 = (uint *)((int)puVar20 + param_5);
                puVar16 = (uint *)((int)puVar20 + param_5);
                bVar12 = local_84[2];
                iVar23 = (bVar12 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                *puVar20 = uVar14;
                *puVar16 = uVar14;
                iVar23 = (bVar12 >> 2 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                puVar20[1] = uVar14;
                puVar16[1] = uVar14;
                iVar23 = (bVar12 >> 4 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                puVar20[2] = uVar14;
                puVar16[2] = uVar14;
                iVar23 = (uint)(bVar12 >> 6) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                puVar20[3] = uVar14;
                puVar16[3] = uVar14;
                puVar16 = (uint *)((int)puVar16 + param_5);
                param_9 = (uint *)((int)puVar16 + param_5);
                bVar12 = local_84[3];
                iVar23 = (bVar12 & 3) * 4;
                local_84 = local_84 + 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                *puVar16 = uVar14;
                *param_9 = uVar14;
                iVar23 = (bVar12 >> 2 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                puVar16[1] = uVar14;
                param_9[1] = uVar14;
                iVar23 = (bVar12 >> 4 & 3) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                puVar16[2] = uVar14;
                param_9[2] = uVar14;
                iVar23 = (uint)(bVar12 >> 6) * 4;
                uVar14 = *(uint *)(&DAT_00204530 + iVar23) & uVar18 |
                         *(uint *)(&DAT_00204540 + iVar23) & uVar21;
                puVar16[3] = uVar14;
                param_9[3] = uVar14;
                param_9 = (uint *)((int)param_9 + param_5);
                local_88 = local_88 + -1;
                local_18 = uVar11;
                uVar14 = uVar22;
                local_54 = puVar19;
              } while (local_88 != 0);
              break;
            case 9:
              puVar20 = (uint *)((int)param_1 + param_5);
              param_9 = (uint *)0x2;
              puVar16 = param_1;
              do {
                uVar14 = (uint)(ushort)*puVar19;
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                *puVar16 = uVar14;
                *puVar20 = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 2);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[1] = uVar14;
                puVar20[1] = uVar14;
                uVar14 = (uint)(ushort)puVar19[1];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[2] = uVar14;
                puVar20[2] = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 6);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[3] = uVar14;
                puVar20[3] = uVar14;
                uVar14 = (uint)(ushort)puVar19[2];
                puVar16 = (uint *)((int)puVar16 + param_5 * 2);
                puVar20 = (uint *)((int)puVar20 + param_5 * 2);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                *puVar16 = uVar14;
                *puVar20 = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 10);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[1] = uVar14;
                puVar20[1] = uVar14;
                uVar14 = (uint)(ushort)puVar19[3];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[2] = uVar14;
                puVar20[2] = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 0xe);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[3] = uVar14;
                puVar20[3] = uVar14;
                uVar14 = (uint)(ushort)puVar19[4];
                puVar16 = (uint *)((int)puVar16 + param_5 * 2);
                puVar20 = (uint *)((int)puVar20 + param_5 * 2);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                *puVar16 = uVar14;
                *puVar20 = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 0x12);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[1] = uVar14;
                puVar20[1] = uVar14;
                uVar14 = (uint)(ushort)puVar19[5];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[2] = uVar14;
                puVar20[2] = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 0x16);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[3] = uVar14;
                puVar20[3] = uVar14;
                uVar14 = (uint)(ushort)puVar19[6];
                puVar16 = (uint *)((int)puVar16 + param_5 * 2);
                puVar20 = (uint *)((int)puVar20 + param_5 * 2);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                *puVar16 = uVar14;
                *puVar20 = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 0x1a);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[1] = uVar14;
                puVar20[1] = uVar14;
                uVar14 = (uint)(ushort)puVar19[7];
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[2] = uVar14;
                puVar20[2] = uVar14;
                uVar14 = (uint)*(ushort *)((int)puVar19 + 0x1e);
                uVar14 = ((uVar14 & 0xffffff00) << 8 | uVar14) << 8 | uVar14 & 0xff;
                puVar16[3] = uVar14;
                puVar20[3] = uVar14;
                puVar16 = (uint *)((int)puVar16 + param_5 * 2);
                puVar20 = (uint *)((int)puVar20 + param_5 * 2);
                puVar19 = puVar19 + 8;
                param_9 = (uint *)((int)param_9 + -1);
                local_18 = uVar11;
                uVar14 = uVar22;
                local_54 = puVar19;
              } while (param_9 != (uint *)0x0);
            }
          }
          param_1 = param_1 + 2;
          local_20 = local_20 + 2;
          param_10 = param_10 - 8;
          *(undefined1 *)((local_18 >> 1) + local_1c) = 1;
          *(undefined1 *)((local_18 + param_8 >> 1) + local_1c) = 1;
          uVar21 = local_18 + param_8;
          break;
        case 2:
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          puVar19 = (uint *)((int)local_20 + (int)*local_124 + (int)*local_f4 * param_5);
          local_124 = local_124 + 1;
          local_f4 = local_f4 + 1;
          uVar14 = puVar19[1];
          uVar5 = *(undefined4 *)((int)puVar19 + param_5);
          uVar6 = *(undefined4 *)((int)puVar19 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar19 + param_5 * 2);
          *param_1 = *puVar19;
          param_1[1] = uVar14;
          *(undefined4 *)((int)param_1 + param_5) = uVar5;
          *(undefined4 *)((int)param_1 + param_5 + 4) = uVar6;
          puVar2 = (undefined4 *)((int)param_1 + param_5 * 2);
          uVar5 = puVar1[1];
          uVar6 = *(undefined4 *)((int)puVar1 + param_5);
          uVar7 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          puVar3 = (undefined4 *)((int)puVar1 + param_5 * 2);
          *puVar2 = *puVar1;
          puVar2[1] = uVar5;
          *(undefined4 *)((int)puVar2 + param_5) = uVar6;
          *(undefined4 *)((int)puVar2 + param_5 + 4) = uVar7;
          puVar2 = (undefined4 *)((int)puVar2 + param_5 * 2);
          uVar5 = puVar3[1];
          uVar6 = *(undefined4 *)((int)puVar3 + param_5);
          uVar7 = *(undefined4 *)((int)puVar3 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar3 + param_5 * 2);
          *puVar2 = *puVar3;
          puVar2[1] = uVar5;
          *(undefined4 *)((int)puVar2 + param_5) = uVar6;
          *(undefined4 *)((int)puVar2 + param_5 + 4) = uVar7;
          puVar2 = (undefined4 *)((int)puVar2 + param_5 * 2);
          uVar5 = puVar1[1];
          uVar6 = *(undefined4 *)((int)puVar1 + param_5);
          uVar7 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          *puVar2 = *puVar1;
          puVar2[1] = uVar5;
          *(undefined4 *)((int)puVar2 + param_5) = uVar6;
          *(undefined4 *)((int)puVar2 + param_5 + 4) = uVar7;
          puVar19 = local_54;
          uVar21 = uVar11;
          uVar14 = uVar22;
          break;
        case 3:
          if (local_8 < 4) {
            uVar14 = *local_14[0] << (bVar12 & 0x1f) | uVar14;
            uVar22 = *local_14[0] >> (4 - bVar12 & 0x1f);
            local_8 = local_8 + 0x1c;
            local_14[0] = local_14[0] + 1;
          }
          else {
            uVar22 = uVar14 >> 4;
            local_8 = local_8 - 4;
          }
          iVar17 = (uVar14 & 0xf) * 0x40;
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          iVar23 = 0;
          do {
            if (local_8 == 0) {
              uVar14 = *local_14[0];
              local_14[0] = local_14[0] + 1;
              local_8 = 0x1f;
            }
            else {
              local_8 = local_8 - 1;
              uVar14 = uVar22;
            }
            uVar22 = uVar14 >> 1;
            local_c = uVar22;
            if ((uVar14 & 1) == 0) {
              bVar12 = *local_c4;
              local_c4 = local_c4 + 1;
              for (iVar13 = bVar12 + 1; iVar13 != 0; iVar13 = iVar13 + -1) {
                iVar10 = iVar23 + iVar17;
                uVar14 = *puVar19;
                iVar23 = iVar23 + 1;
                puVar19 = (uint *)((int)puVar19 + 1);
                *(char *)((int)&local_164 + (uint)(byte)(&DAT_00208768)[iVar10]) = (char)uVar14;
                local_54 = puVar19;
              }
            }
            else {
              uVar14 = *puVar19;
              puVar19 = (uint *)((int)puVar19 + 1);
              bVar12 = *local_c4;
              local_c4 = local_c4 + 1;
              local_54 = puVar19;
              for (iVar13 = bVar12 + 1; iVar13 != 0; iVar13 = iVar13 + -1) {
                iVar10 = iVar23 + iVar17;
                iVar23 = iVar23 + 1;
                *(char *)((int)&local_164 + (uint)(byte)(&DAT_00208768)[iVar10]) = (char)uVar14;
              }
            }
          } while (iVar23 < 0x3f);
          if (iVar23 == 0x3f) {
            *(char *)((int)&local_164 + (uint)(byte)(&DAT_002087a7)[iVar17]) = (char)*puVar19;
            local_54 = (uint *)((int)puVar19 + 1);
          }
          *param_1 = local_164;
          param_1[1] = local_160;
          *(undefined4 *)((int)param_1 + param_5) = local_15c;
          *(undefined4 *)((int)param_1 + param_5 + 4) = local_158;
          puVar1 = (undefined4 *)((int)param_1 + param_5 * 2);
          *puVar1 = local_154;
          puVar1[1] = local_150;
          *(undefined4 *)((int)puVar1 + param_5) = local_14c;
          *(undefined4 *)((int)puVar1 + param_5 + 4) = local_148;
          puVar1 = (undefined4 *)((int)puVar1 + param_5 * 2);
          *puVar1 = local_144;
          puVar1[1] = local_140;
          *(undefined4 *)((int)puVar1 + param_5) = local_13c;
          *(undefined4 *)((int)puVar1 + param_5 + 4) = local_138;
          puVar1 = (undefined4 *)((int)puVar1 + param_5 * 2);
          *puVar1 = local_134;
          puVar1[1] = local_130;
          *(undefined4 *)((int)puVar1 + param_5) = local_12c;
          *(undefined4 *)((int)puVar1 + param_5 + 4) = local_128;
          puVar19 = local_54;
          uVar21 = local_18;
          uVar14 = local_c;
          break;
        case 4:
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          puVar19 = (uint *)((int)local_20 + (int)*local_124 + (int)*local_f4 * param_5);
          local_124 = local_124 + 1;
          local_f4 = local_f4 + 1;
          local_164 = *puVar19;
          local_160 = puVar19[1];
          local_15c = *(undefined4 *)((int)puVar19 + param_5);
          local_158 = *(undefined4 *)((int)puVar19 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar19 + param_5 * 2);
          local_154 = *puVar1;
          local_150 = puVar1[1];
          local_14c = *(undefined4 *)((int)puVar1 + param_5);
          local_148 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar1 + param_5 * 2);
          local_144 = *puVar1;
          local_140 = puVar1[1];
          local_13c = *(undefined4 *)((int)puVar1 + param_5);
          local_138 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar1 + param_5 * 2);
          local_134 = *puVar1;
          local_130 = puVar1[1];
          local_12c = *(undefined4 *)((int)puVar1 + param_5);
          local_128 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          if (local_8 < 7) {
            local_c = *local_14[0] >> (7 - bVar12 & 0x1f);
            uVar22 = *local_14[0] << (bVar12 & 0x1f) | uVar22;
            local_8 = local_8 + 0x19;
            local_14[0] = local_14[0] + 1;
          }
          else {
            local_c = uVar22 >> 7;
            local_8 = local_8 - 7;
          }
          FUN_001b2a40(param_1,param_5,local_14,uVar22 & 0x7f,&local_164);
          puVar19 = local_54;
          uVar21 = local_18;
          uVar14 = local_c;
          break;
        case 5:
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          local_2a4[0] = *local_1f4;
          local_1f4 = local_1f4 + 1;
          FUN_001b1c20(local_2a4,local_14);
          if (local_8 < 4) {
            uVar14 = *local_14[0] << ((byte)local_8 & 0x1f) | local_c;
            local_c = *local_14[0] >> (4 - (byte)local_8 & 0x1f);
            local_8 = local_8 + 0x1c;
            local_14[0] = local_14[0] + 1;
          }
          else {
            local_8 = local_8 - 4;
            uVar14 = local_c;
            local_c = local_c >> 4;
          }
          BigInitXBEFunction(param_1,param_5,local_2a4,uVar14 & 0xf);
          puVar19 = local_54;
          uVar14 = local_c;
          break;
        case 6:
          uVar14 = *puVar19;
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          uVar8 = CONCAT11((char)uVar14,(char)uVar14);
          uVar14 = CONCAT22(uVar8,uVar8);
          *param_1 = uVar14;
          param_1[1] = uVar14;
          *(uint *)((int)param_1 + param_5) = uVar14;
          *(uint *)((int)param_1 + param_5 + 4) = uVar14;
          *(uint *)((int)param_1 + param_5 * 2) = uVar14;
          *(uint *)((int)param_1 + param_5 * 2 + 4) = uVar14;
          *(uint *)((int)param_1 + param_5 * 3) = uVar14;
          *(uint *)((int)param_1 + param_5 * 3 + 4) = uVar14;
          puVar20 = param_1 + param_5;
          *puVar20 = uVar14;
          puVar20[1] = uVar14;
          puVar20 = (uint *)((int)puVar20 + param_5);
          *puVar20 = uVar14;
          puVar20[1] = uVar14;
          local_54 = (uint *)((int)puVar19 + 1);
          puVar20 = (uint *)((int)puVar20 + param_5);
          *puVar20 = uVar14;
          puVar20[1] = uVar14;
          *(uint *)((int)puVar20 + param_5) = uVar14;
          *(uint *)((int)puVar20 + param_5 + 4) = uVar14;
          puVar19 = local_54;
          uVar14 = uVar22;
          break;
        case 7:
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          puVar19 = (uint *)((int)local_20 + (int)*local_124 + (int)*local_f4 * param_5);
          local_124 = local_124 + 1;
          local_f4 = local_f4 + 1;
          local_164 = *puVar19;
          local_160 = puVar19[1];
          local_15c = *(undefined4 *)((int)puVar19 + param_5);
          local_158 = *(undefined4 *)((int)puVar19 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar19 + param_5 * 2);
          local_154 = *puVar1;
          local_150 = puVar1[1];
          local_14c = *(undefined4 *)((int)puVar1 + param_5);
          local_148 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar1 + param_5 * 2);
          local_144 = *puVar1;
          local_140 = puVar1[1];
          local_13c = *(undefined4 *)((int)puVar1 + param_5);
          local_138 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          puVar1 = (undefined4 *)((int)puVar1 + param_5 * 2);
          local_134 = *puVar1;
          local_130 = puVar1[1];
          local_12c = *(undefined4 *)((int)puVar1 + param_5);
          local_128 = *(undefined4 *)((int)puVar1 + param_5 + 4);
          local_2a4[0] = *local_224;
          local_224 = local_224 + 1;
          FUN_001b1c20(local_2a4,local_14);
          if (local_8 < 4) {
            uVar14 = *local_14[0];
            bVar12 = (byte)local_8;
            uVar22 = uVar14 << (bVar12 & 0x1f) | local_c;
            local_8 = local_8 + 0x1c;
            local_14[0] = local_14[0] + 1;
            local_c = uVar14 >> (4 - bVar12 & 0x1f);
          }
          else {
            local_8 = local_8 - 4;
            uVar22 = local_c;
            local_c = local_c >> 4;
          }
          FUN_001b14a0(param_1,param_5,local_2a4,uVar22 & 0xf,&local_164);
          puVar19 = local_54;
          uVar21 = local_18;
          uVar14 = local_c;
          break;
        case 8:
          uVar14 = *puVar19;
          uVar4 = *(undefined1 *)((int)puVar19 + 1);
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          uVar8 = CONCAT11((char)uVar14,(char)uVar14);
          uVar14 = CONCAT22(uVar8,uVar8);
          uVar8 = CONCAT11(uVar4,uVar4);
          local_54 = (uint *)((int)puVar19 + 2);
          uVar21 = CONCAT22(uVar8,uVar8);
          bVar12 = *local_84;
          iVar23 = (bVar12 & 0xf) * 4;
          *param_1 = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                     *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          param_1[1] = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                       *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          bVar12 = local_84[1];
          iVar23 = (bVar12 & 0xf) * 4;
          puVar19 = (uint *)((int)param_1 + param_5 * 2);
          *(uint *)((int)param_1 + param_5) =
               *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
               *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          *(uint *)((int)param_1 + param_5 + 4) =
               *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
               *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          bVar12 = local_84[2];
          iVar23 = (bVar12 & 0xf) * 4;
          puVar20 = (uint *)((int)puVar19 + param_5);
          *puVar19 = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                     *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          puVar19[1] = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                       *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          bVar12 = local_84[3];
          iVar23 = (bVar12 & 0xf) * 4;
          puVar19 = (uint *)((int)puVar20 + param_5);
          *puVar20 = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                     *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          puVar20[1] = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                       *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          bVar12 = local_84[4];
          iVar23 = (bVar12 & 0xf) * 4;
          puVar20 = (uint *)((int)puVar19 + param_5);
          *puVar19 = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                     *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          puVar19[1] = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                       *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          bVar12 = local_84[5];
          iVar23 = (bVar12 & 0xf) * 4;
          puVar19 = (uint *)((int)puVar20 + param_5);
          *puVar20 = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                     *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          puVar20[1] = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                       *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          bVar12 = local_84[6];
          iVar23 = (bVar12 & 0xf) * 4;
          *puVar19 = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                     *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          puVar19[1] = *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
                       *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          bVar12 = local_84[7];
          iVar23 = (bVar12 & 0xf) * 4;
          local_84 = local_84 + 8;
          *(uint *)((int)puVar19 + param_5) =
               *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
               *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          iVar23 = (uint)(bVar12 >> 4) * 4;
          *(uint *)((int)puVar19 + param_5 + 4) =
               *(uint *)(&DAT_002044b0 + iVar23) & uVar21 |
               *(uint *)(&DAT_002044f0 + iVar23) & uVar14;
          puVar19 = local_54;
          uVar21 = uVar11;
          uVar14 = uVar22;
          break;
        case 9:
          *(undefined1 *)((uVar21 >> 1) + local_1c) = 1;
          uVar14 = local_54[1];
          uVar21 = local_54[2];
          uVar18 = local_54[3];
          *param_1 = *local_54;
          param_1[1] = uVar14;
          *(uint *)((int)param_1 + param_5) = uVar21;
          *(uint *)((int)param_1 + param_5 + 4) = uVar18;
          puVar19 = (uint *)((int)param_1 + param_5 * 2);
          uVar14 = local_54[5];
          uVar21 = local_54[6];
          uVar18 = local_54[7];
          *puVar19 = local_54[4];
          puVar19[1] = uVar14;
          *(uint *)((int)puVar19 + param_5) = uVar21;
          *(uint *)((int)puVar19 + param_5 + 4) = uVar18;
          puVar19 = (uint *)((int)puVar19 + param_5 * 2);
          uVar14 = local_54[9];
          uVar21 = local_54[10];
          uVar18 = local_54[0xb];
          *puVar19 = local_54[8];
          puVar19[1] = uVar14;
          *(uint *)((int)puVar19 + param_5) = uVar21;
          *(uint *)((int)puVar19 + param_5 + 4) = uVar18;
          puVar19 = (uint *)((int)puVar19 + param_5 * 2);
          uVar14 = local_54[0xd];
          uVar21 = local_54[0xe];
          uVar18 = local_54[0xf];
          *puVar19 = local_54[0xc];
          puVar19[1] = uVar14;
          *(uint *)((int)puVar19 + param_5) = uVar21;
          *(uint *)((int)puVar19 + param_5 + 4) = uVar18;
          local_54 = local_54 + 0x10;
          puVar19 = local_54;
          uVar21 = uVar11;
          uVar14 = uVar22;
        }
        uVar21 = uVar21 + param_8;
        param_1 = param_1 + 2;
        local_20 = local_20 + 2;
        uVar11 = uVar21;
        uVar22 = local_c;
      }
      if (param_8 == 1) {
        if ((local_24 & 8) != 0) {
          local_1c = local_1c + local_8c;
        }
      }
      else {
        local_1c = local_1c + local_8c;
      }
      param_1 = (uint *)((int)param_1 + local_94);
      local_20 = (uint *)((int)local_20 + local_94);
      local_24 = local_24 + 8;
      local_18 = 0;
    } while (local_24 < param_4);
  }
  return local_14[0];
}



void FUN_001ad9f0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 int param_6,int param_7,uint param_8,uint param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,uint param_13,uint param_14)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  if (((param_14 & 0x100000) != 0) && ((param_13 & 0x100000) != 0)) {
    BigConversionFunction_
              (param_3,param_4,param_6 + 7U & 0xfffffff8,param_7 + 7U & 0xfffffff8,param_8,param_11,
               param_5,1,param_12,param_13);
  }
  BigConversionFunction_
            (param_1,param_2,param_6 + 7U & 0xfffffff8,param_7 + 7U & 0xfffffff8,param_8,param_11,
             param_5,1,param_12,param_13);
  if ((param_13 & 0x20000) == 0) {
    param_2 = param_2 + param_8 * param_9;
    param_1 = param_1 + param_8 * param_9;
    uVar2 = (param_6 + 1U >> 1) + 7 & 0xfffffff8;
    param_8 = param_8 >> 1;
    uVar3 = (param_7 + 1U >> 1) + 7 & 0xfffffff8;
    BigConversionFunction_(param_1,param_2,uVar2,uVar3,param_8,param_11,param_5,2,param_12,param_13)
    ;
    iVar1 = param_8 * (param_9 >> 1);
    BigConversionFunction_
              (iVar1 + param_1,param_2 + iVar1,uVar2,uVar3,param_8,param_11,param_5,2,param_12,
               param_13);
  }
  return;
}




