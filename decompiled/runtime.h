/* runtime.h - Runtime data structures: BigBlock, EDB2, buffers, loctext, fonts
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void runtime::TriggerAppError(void);
extern void SetupSomeAssetLoader(void);
extern void runtime::OpenOrDeleteFolder(PCSZ dirName,uint param_2,uint param_3);
extern void SetupWeirdStruct1Array(void);
extern void NothingApparently2_(void);
extern byte runtime::GetSpaceUsedByDiskType(DiskId diskId,uint *outSum1,uint *outSum2);
extern BOOL SetModelInParent(AvatarParent *parent,avatar *av,int *someAID);
extern void runtime::ClearAllCams(void);
extern void runtime::Clear_g_itemsToClear(void);
extern int DataViewList::GetResourceByAddress(DataViewList *resource,void *offsetIntoRes);
extern void runtime::InitialiseFontResources(void);
extern void ClearIDKBigStruct(void);
extern Buffer * runtime::ExtendArray(Buffer *buf);
extern void * ExtendBuffer2(Buffer **param_1,int param_2);
extern BOOL obj::returnOne(void);
extern void runtime::ClearSomeType3AssetNames(void);
extern int __fastcall runtime::GetValsFromCacheContext_(CacheContext *cacheCtx,uint *param_2,uint *param_3);
extern void GetErrorById(uint id,char **errorName,char **errorMessage);
extern void InitialiseCache(void);
extern void runtime::CreateHeapTables(uint param_1);
extern int FindHeapOf(void *mem);
extern void FreePhysical(LPVOID lpAddress);
extern int SizeOf_g_int_12__array(void);
extern char * __thiscall AllocateMoreAStruct_33(uint size,void *param_2);
extern void AllocateGlobalShorts(void);
extern BOOL IsValidString(LPWSTR str);
extern void runtime::UpdateClocks(void);
extern BOOL loctext::get_text(char *loctextAID,char *group,char *name,LPWSTR valueOut);
extern char * copy__a_zA_Z0_9__(char *out,char *in);
extern BOOL loctext::getStringFromLoctextResource(LPWSTR outStr,char *loctextAID,char *stringToGet);
extern void obj::getAllocDetails(ObjectAllocDetails *obj);
extern ObjectFullVTable * obj::GetVTable(void);
extern void __thiscall obj::destroy(Object *param_1,ushort param_2,int param_3);
extern BOOL obj::ctor(obj *object,objParams *params);
extern ushort GetActorTagIndex(char *param_1);
extern void CopySomeActorBodyList(SomeActorBodyList *src,SomeActorBodyList *dst);
extern void runtime::GetLatestLoadableScript(char *param_1,LPCWSTR param_2);
extern void runtime::ClearSceneInfo(void);
extern void runtime::FinaliseLoad(void);
extern void obj::closeObject(obj *param_1);
extern void Buffer<EDB2Entry>::addAvatarToSet(Buffer<EDB2Entry> *buf,avatar *av);
extern XBE_SECTION_HEADER * runtime::GetXbeSectionByName(PCHAR sectionName);
extern ushort * runtime::AllocateOnHeap(int param_1,uint flags,uint param_3);
extern void InitBigBlock(BigBlock *bigBlock,NamedCallbackTable *nameTable);
extern void BigBlock::SetTextures(undefined4 param_1,undefined4 numTextures);
extern void updateKeyValueTableOffsets(ModelSection1 *dataStart,int dataBase);
extern void GetBigBlock(BigBlock **param_1);
extern void NamedCallbackTable::addEntry(NamedCallbackTable *table,char *name,void *callback);
extern void BigBlock::findNameInCallbackTable(NamedCallbackTable *param_1,ndHeader *param_2);
extern int IndexOfKeyInTable(NamedCallbackTable *table,char *key);
extern void BigBlockCallbackCtx::getCallbackTable(BigBlockCallbackCtx *param_1,void **param_2);
extern void BigBlock::draw(int param_1,ushort param_2,ushort bigBlock44,ModelVariableData *param_4);
extern void SearchBinaryEntriesLL(undefined4 *param_1,void *param_2);
extern void List::Init(uint *param_1);
extern void List::PushGlobal(Node *root,Node *newSource);
extern char * runtime::GetLastError(int param_1);
extern void LoctextHeaderReader::init(LoctextHeader *param_1,LoctextLookupTable *param_2);
extern wchar_t * LoctextLookupTable::getByHash(LoctextLookupTable *lut,uint32_t hash);
extern void g_zalloc(undefined4 param_1,undefined4 param_2,undefined4 param_3);
extern void SetUnknownCallbacks(void *callback1,void *callback2);
extern void __thiscall std::basic_string<char>::assign(basic_string<char> *this,char *param_1);
extern int SkipStringWhitespace(int *param_1);
