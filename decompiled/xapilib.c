/* xapilib.c - Xbox XAPILIB wrapper (XGetLaunchInfo, XMemAlloc, XOpenFile, etc.) */
#include "xapilib.h"

void * XAPILIB::XMemAlloc(uint size,uint allocFlags)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 *puVar3;
  
  if ((int)allocFlags < 0) {
    if ((allocFlags & 0xf000000) == 0) {
      allocFlags = allocFlags & 0xfcffffff | 0xc000000;
    }
    uVar2 = allocFlags >> 0x18 & 0xf;
    if (uVar2 == 1) {
      puVar1 = (undefined4 *)
               FUN_0014aaba(size,0,0xffffff,0x1000,
                            *(undefined4 *)(&DAT_0032ca10 + (allocFlags >> 0x1c & 3) * 4));
    }
    else {
      puVar1 = (undefined4 *)
               XPhysicalAlloc(size,0xffffffff,1 << (sbyte)uVar2,
                              *(undefined4 *)(&DAT_0032ca10 + (allocFlags >> 0x1c & 3) * 4));
    }
    if ((puVar1 != (undefined4 *)0x0) && ((allocFlags & 0x40000000) != 0)) {
      puVar3 = puVar1;
      for (uVar2 = size >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      for (uVar2 = size & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar3 = 0;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
    }
  }
  else {
    puVar1 = LocalAlloc(allocFlags >> 0x18 & 0x40,CONCAT44(unaff_EBP,unaff_ESI));
  }
  return puVar1;
}




void XAPILIB::XMemFree(PVOID param_1,uint param_2)

{
  if ((param_2 & 0x80000000) == 0) {
    LocalFree(param_1);
  }
  else {
    XPhysicalFree(param_1);
  }
  return;
}




BOOL XAPILIB::IsBadReadPtr(void *lp,UINT_PTR ucb)

{
  uint uVar2;
  int in_stack_00000008;
  void *pvVar1;
  
  if (in_stack_00000008 != 0) {
    if ((lp == (void *)0x0) || (pvVar1 = (void *)((int)lp + in_stack_00000008 + -1), pvVar1 < lp)) {
      return 1;
    }
    for (uVar2 = (uint)lp & 0xfffff000; uVar2 != ((uint)pvVar1 & 0xfffff000); uVar2 = uVar2 + 0x1000
        ) {
    }
  }
  return 0;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


BOOL XAPILIB::IsBadWritePtr(LPVOID lp,UINT_PTR ucb)

{
  LPVOID pvVar1;
  undefined1 *puVar2;
  int in_stack_00000008;
  
  if (in_stack_00000008 != 0) {
    if ((lp == (LPVOID)0x0) || (pvVar1 = (LPVOID)((int)lp + in_stack_00000008 + -1), pvVar1 < lp)) {
      return 1;
    }
    *(undefined1 *)lp = *(undefined1 *)lp;
    puVar2 = (undefined1 *)((uint)lp & 0xfffff000);
    while (puVar2 != (undefined1 *)((uint)pvVar1 & 0xfffff000)) {
      puVar2 = puVar2 + 0x1000;
      *puVar2 = *puVar2;
    }
  }
  return 0;
}




BOOL XAPILIB::IsBadCodePtr(FARPROC lpfn)

{
  BOOL BVar1;
  undefined4 unaff_retaddr;
  
  BVar1 = IsBadReadPtr(lpfn,CONCAT44(lpfn,unaff_retaddr));
  return BVar1;
}




int XAPILIB::lstrcmpW(LPCWSTR lpString1,LPCWSTR lpString2)

{
  int iVar1;
  
  iVar1 = FUN_0014fb5b(0,lpString1,0xffffffff,lpString2,0xffffffff);
  if (iVar1 == 0) {
    if (lpString1 == (LPCWSTR)0x0) {
      iVar1 = -(uint)(lpString2 != (LPCWSTR)0x0);
    }
    else if (lpString2 == (LPCWSTR)0x0) {
      iVar1 = 1;
    }
    else {
      iVar1 = _wcscmp(lpString1,lpString2);
    }
  }
  else {
    iVar1 = iVar1 + -2;
  }
  return iVar1;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


LPWSTR XAPILIB::lstrcpyW(LPWSTR lpString1,LPCWSTR lpString2)

{
  LPWSTR pWVar1;
  
  pWVar1 = ::lstrcpyW(lpString1,lpString2);
  return pWVar1;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


LPWSTR XAPILIB::lstrcpynW(LPWSTR lpString1,LPCWSTR lpString2,int iMaxLength)

{
  LPWSTR pWVar1;
  
  pWVar1 = lpString1;
  if (iMaxLength != 0) {
    for (; iMaxLength != 0; iMaxLength = iMaxLength + -1) {
      if (*lpString2 == L'\0') {
        if (iMaxLength != 0) goto LAB_0014a9e4;
        break;
      }
      *pWVar1 = *lpString2;
      pWVar1 = pWVar1 + 1;
      lpString2 = lpString2 + 1;
    }
    pWVar1 = pWVar1 + -1;
LAB_0014a9e4:
    *pWVar1 = L'\0';
  }
  return lpString1;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


LPWSTR XAPILIB::lstrcatW(LPWSTR lpString1,LPCWSTR lpString2)

{
  wchar_t *pwVar1;
  
  pwVar1 = _wcscat(lpString1,lpString2);
  return pwVar1;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


int XAPILIB::lstrlenW(LPCWSTR lpString)

{
  int iVar1;
  
  if (lpString == (LPCWSTR)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00166ecb(lpString);
  }
  return iVar1;
}




PVOID XAPILIB::XPhysicalAlloc(SIZE_T param_1,ULONG_PTR param_2,ULONG_PTR param_3,ULONG param_4)

{
  ULONG_PTR HighestAcceptableAddress;
  PVOID pvVar1;
  
  if (param_2 == 0xffffffff) {
    param_2 = 0;
    HighestAcceptableAddress = 0xffffffff;
  }
  else {
    param_3 = 0;
    HighestAcceptableAddress = (param_1 - 1) + param_2;
  }
  pvVar1 = MmAllocateContiguousMemoryEx(param_1,param_2,HighestAcceptableAddress,param_3,param_4);
  if (pvVar1 == (PVOID)0x0) {
    SetLastError(8);
  }
  return pvVar1;
}



PVOID FUN_0014aaba(SIZE_T param_1,ULONG_PTR param_2,ULONG_PTR param_3,ULONG_PTR param_4,
                  ULONG param_5)

{
  PVOID pvVar1;
  
  pvVar1 = MmAllocateContiguousMemoryEx(param_1,param_2,param_3,param_4,param_5);
  if (pvVar1 == (PVOID)0x0) {
    XAPILIB::SetLastError(8);
  }
  return pvVar1;
}




void XAPILIB::XPhysicalFree(PVOID BaseAddress)

{
                    // WARNING: Could not recover jumptable at 0x0014aae7. Too many branches
                    // WARNING: Treating indirect jump as call
  MmFreeContiguousMemory(BaseAddress);
  return;
}




int XAPILIB::lstrcmpiA(LPCSTR lpString1,LPCSTR lpString2)

{
  int iVar1;
  
  iVar1 = FUN_0014fcf4(1,lpString1,0xffffffff,lpString2,0xffffffff);
  if (iVar1 == 0) {
    if (lpString1 == (LPCSTR)0x0) {
      iVar1 = -(uint)(lpString2 != (LPCSTR)0x0);
    }
    else if (lpString2 == (LPCSTR)0x0) {
      iVar1 = 1;
    }
    else {
      iVar1 = __stricmp(lpString1,lpString2);
    }
  }
  else {
    iVar1 = iVar1 + -2;
  }
  return iVar1;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog
// WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3


LPSTR XAPILIB::lstrcpynA(LPSTR lpString1,LPCSTR lpString2,int iMaxLength)

{
  LPSTR pcVar1;
  
  pcVar1 = lpString1;
  if (iMaxLength != 0) {
    for (; iMaxLength != 0; iMaxLength = iMaxLength + -1) {
      if (*lpString2 == '\0') {
        if (iMaxLength != 0) goto LAB_0014acf7;
        break;
      }
      *pcVar1 = *lpString2;
      pcVar1 = pcVar1 + 1;
      lpString2 = lpString2 + 1;
    }
    pcVar1 = pcVar1 + -1;
LAB_0014acf7:
    *pcVar1 = '\0';
  }
  return lpString1;
}




void XAPILIB::GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer)

{
  _MM_STATISTICS local_28;
  
  local_28.Length = 0x24;
  MmQueryStatistics(&local_28);
  lpBuffer->dwMemoryLoad = 0;
  *(undefined4 *)&lpBuffer->dwAvailPhys = 0;
  *(undefined4 *)((int)&lpBuffer->dwAvailPhys + 4) = 0;
  *(ULONG *)&lpBuffer->dwTotalPhys = local_28.TotalPhysicalPages << 0xc;
  *(ULONG *)((int)&lpBuffer->dwTotalPhys + 4) = local_28.AvailablePages << 0xc;
  *(undefined4 *)&lpBuffer->dwTotalPageFile = 0x7ffe0000;
  lpBuffer->dwLength = 0x20;
  *(ULONG *)((int)&lpBuffer->dwTotalPageFile + 4) = 0x7ffe0000 - local_28.VirtualMemoryBytesReserved
  ;
  return;
}




DWORD XAPILIB::XLaunchNewImageA(LPCSTR lpTitlePath,PLAUNCH_DATA pLaunchData)

{
  DWORD DVar1;
  int *piVar2;
  
  piVar2 = &DAT_0032c868;
  do {
    if (*piVar2 != 0) {
      DVar1 = (*(code *)*piVar2)(lpTitlePath,pLaunchData,1,0);
      return DVar1;
    }
    piVar2 = piVar2 + 1;
  } while (piVar2 < &DAT_0032c86c);
  DVar1 = FUN_0015028c(lpTitlePath,pLaunchData,0,0);
  return DVar1;
}



undefined4
FUN_0014ada8(LPCSTR param_1,char *param_2,int param_3,int param_4,undefined4 param_5,
            undefined4 *param_6)

{
  LPSTR lpString1;
  char cVar1;
  undefined4 *puVar2;
  PVOID pvVar3;
  undefined4 uVar4;
  LPSTR pCVar5;
  int iVar6;
  undefined4 *puVar7;
  
  if (*(int *)LaunchDataPage_exref == 0) {
    pvVar3 = MmAllocateContiguousMemory(0x1000);
    *(PVOID *)LaunchDataPage_exref = pvVar3;
  }
  if (*(PVOID *)LaunchDataPage_exref == (PVOID)0x0) {
    uVar4 = 0xc0000017;
  }
  else {
    MmPersistContiguousMemory(*(PVOID *)LaunchDataPage_exref,0x1000,'\x01');
    if (param_2 == (LPCSTR)0x0) {
      param_2 = "\\Device\\Cdrom0";
    }
    puVar2 = *(undefined4 **)LaunchDataPage_exref;
    lpString1 = (LPSTR)(puVar2 + 2);
    puVar7 = puVar2;
    for (iVar6 = 0x400; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    **(int **)LaunchDataPage_exref = param_4;
    *(undefined4 *)(*(int *)LaunchDataPage_exref + 4) = param_5;
    if (param_4 != -1) {
      puVar7 = (undefined4 *)(*(int *)LaunchDataPage_exref + 0x400);
      for (iVar6 = 0x300; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar7 = *param_6;
        param_6 = param_6 + 1;
        puVar7 = puVar7 + 1;
      }
    }
    iVar6 = 0;
    if (param_1 != (LPCSTR)0x0) {
      if ((param_2 != (LPCSTR)0x0) && (param_3 != 0)) {
        XAPILIB::lstrcpynA(lpString1,param_2,0x207);
        pCVar5 = lpString1;
        do {
          cVar1 = *pCVar5;
          pCVar5 = pCVar5 + 1;
        } while (cVar1 != '\0');
        iVar6 = (int)pCVar5 - ((int)puVar2 + 9);
        lpString1[iVar6] = ';';
        iVar6 = iVar6 + 1;
      }
      XAPILIB::lstrcpynA(lpString1 + iVar6,param_1,0x208 - iVar6);
    }
    uVar4 = 0;
  }
  return uVar4;
}




DWORD XAPILIB::XGetLaunchInfo(PDWORD pdwLaunchDataType,PLAUNCH_DATA pLaunchData)

{
  DWORD DVar3;
  int iVar4;
  undefined4 *puVar5;
  DWORD *pDVar1;
  PVOID uVar2;
  
  pDVar1 = *(DWORD **)LaunchDataPage_exref;
  if ((pDVar1 == (DWORD *)0x0) ||
     (((DVar3 = *pDVar1, DVar3 != 2 && (DVar3 != 3)) &&
      (pDVar1[1] != XBE_CERTIFICATE_HEADER_00010184.TitleID)))) {
    DVar3 = 0x490;
  }
  else {
    *pdwLaunchDataType = DVar3;
    puVar5 = (undefined4 *)(*(int *)LaunchDataPage_exref + 0x400);
    for (iVar4 = 0x300; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pLaunchData = *puVar5;
      puVar5 = puVar5 + 1;
      pLaunchData = (PLAUNCH_DATA)((int)pLaunchData + 4);
    }
    uVar2 = *(PVOID *)LaunchDataPage_exref;
    *(undefined4 *)LaunchDataPage_exref = 0;
    MmFreeContiguousMemory(uVar2);
    DVar3 = 0;
  }
  return DVar3;
}



void FUN_0014aeed(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  NTSTATUS Status;
  NTSTATUS extraout_EAX;
  int unaff_FS_OFFSET;
  
  Status = FUN_0014ada8(param_1,param_2,1,param_3,param_4,param_5);
  if (-1 < Status) {
    iVar1 = *(int *)(*(int *)(unaff_FS_OFFSET + 0x20) + 0x250);
    if (iVar1 != 0) {
      (**(code **)(iVar1 + 0x14))(2,0);
    }
    HalReturnToFirmware(HalQuickRebootRoutine);
    Status = extraout_EAX;
  }
  RtlNtStatusToDosError(Status);
  return;
}




PVOID XAPILIB::XLoadSectionByHandle(HANDLE handle)

{
  DWORD dwErrCode;
  PVOID pvVar1;
  
  dwErrCode = XeLoadSection(handle);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
    pvVar1 = (PVOID)0x0;
  }
  else {
    pvVar1 = *(PVOID *)((int)handle + 4);
  }
  return pvVar1;
}




bool XAPILIB::XFreeSectionByHandle(PXBEIMAGE_SECTION param_1)

{
  DWORD dwErrCode;
  
  dwErrCode = XeUnloadSection(param_1);
  if (-1 >= (int)dwErrCode) {
    XapiSetLastNTError(dwErrCode);
  }
  return -1 < (int)dwErrCode;
}




undefined4 XAPILIB::XGetSectionSize(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}




char * XAPILIB::GetLastError(int param_1)

{
  return *(char **)(*(int *)(*(int *)(param_1 + 4) + _tls_index * 4) + 8);
}




void XAPILIB::SetLastError(DWORD dwErrCode)

{
  int unaff_FS_OFFSET;
  
  *(DWORD *)(*(int *)(*(int *)(unaff_FS_OFFSET + 4) + _tls_index * 4) + 8) = dwErrCode;
  return;
}




void XAPILIB::XapiSetLastNTError(DWORD dwErrCode)

{
  ULONG uVar1;
  
  uVar1 = RtlNtStatusToDosError(dwErrCode);
  SetLastError(uVar1);
  return;
}



BOOL XAPILIB::GetOverlappedResult
               (HANDLE hFile,LPOVERLAPPED lpOverlapped,LPDWORD lpNumberOfBytesTransferred,BOOL bWait
               )

{
  HANDLE pvVar1;
  DWORD iVar2;
  
  if ((int)lpOverlapped->Internal == 0x103) {
    if (bWait == 0) {
      iVar2 = 0x102;
    }
    else {
      pvVar1 = (lpOverlapped->u).Pointer;
      if ((lpOverlapped->u).Pointer == (HANDLE)0x0) {
        pvVar1 = hFile;
      }
      iVar2 = WaitForSingleObject(pvVar1,0xffffffff);
    }
    if (iVar2 == 0x102) {
      SetLastError(0x3e4);
      return 0;
    }
    if (iVar2 != 0) {
      return 0;
    }
  }
  *lpNumberOfBytesTransferred = *(DWORD *)((int)&lpOverlapped->Internal + 4);
  iVar2 = (DWORD)lpOverlapped->Internal;
  if ((int)iVar2 < 0) {
    XapiSetLastNTError(iVar2);
    return 0;
  }
  return 1;
}




bool XAPILIB::XSetFileCacheSize(uint param_1)

{
  PFN_COUNT NumberOfCachePages;
  DWORD dwErrCode;
  
  NumberOfCachePages = param_1 >> 0xc;
  if ((param_1 & 0xfff) != 0) {
    NumberOfCachePages = NumberOfCachePages + 1;
  }
  dwErrCode = FscSetCacheSize(NumberOfCachePages);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
  }
  return (int)dwErrCode >= 0;
}




BOOL XAPILIB::CloseHandle(HANDLE hObject)

{
  DWORD dwErrCode;
  
  dwErrCode = NtClose(hObject);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
  }
  return (uint)((int)dwErrCode >= 0);
}



BOOL XAPILIB::ReadFile(HANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,
                      LPDWORD lpNumberOfBytesRead,LPOVERLAPPED lpOverlapped)

{
  _union_17 dwErrCode;
  _union_17 uVar1;
  _LARGE_INTEGER local_14;
  IO_STATUS_BLOCK local_c;
  
  if (lpNumberOfBytesRead != (LPDWORD)0x0) {
    *lpNumberOfBytesRead = 0;
  }
  if (lpOverlapped == (LPOVERLAPPED)0x0) {
    uVar1.Status = NtReadFile(hFile,(HANDLE)0x0,(PIO_APC_ROUTINE)0x0,(PVOID)0x0,&local_c,lpBuffer,
                              nNumberOfBytesToRead,(PLARGE_INTEGER)0x0);
    if (((uVar1.Status == 0x103) &&
        (dwErrCode.Status = NtWaitForSingleObject(hFile,'\0',(PLARGE_INTEGER)0x0),
        uVar1 = local_c.field0_0x0, dwErrCode.Status < 0)) || (dwErrCode = uVar1, uVar1.Status < 0))
    {
      if (dwErrCode.Status != 0xc0000011) {
        if ((dwErrCode.Status & 0xc0000000U) == 0x80000000) {
          *lpNumberOfBytesRead = local_c.Information;
        }
        goto LAB_0014b482;
      }
      *lpNumberOfBytesRead = 0;
    }
    else {
      *lpNumberOfBytesRead = local_c.Information;
    }
  }
  else {
    local_14.field0.LowPart = (ULONG)lpOverlapped->InternalHigh;
    local_14.field0.HighPart = *(LONG *)((int)&lpOverlapped->InternalHigh + 4);
    *(undefined4 *)&lpOverlapped->Internal = 0x103;
    dwErrCode.Status =
         NtReadFile(hFile,(lpOverlapped->u).Pointer,(PIO_APC_ROUTINE)0x0,
                    (PVOID)(~-(uint)(((uint)(lpOverlapped->u).Pointer & 1) != 0) &
                           (uint)lpOverlapped),(PIO_STATUS_BLOCK)lpOverlapped,lpBuffer,
                    nNumberOfBytesToRead,&local_14);
    if ((dwErrCode.Status < 0) || (dwErrCode.Status == 0x103)) {
      if (dwErrCode.Status == 0xc0000011) {
        if (lpNumberOfBytesRead != (LPDWORD)0x0) {
          *lpNumberOfBytesRead = 0;
        }
        dwErrCode.Pointer = (PVOID)0xc0000011;
      }
LAB_0014b482:
      XapiSetLastNTError(dwErrCode.Status);
      return 0;
    }
    if (lpNumberOfBytesRead != (LPDWORD)0x0) {
      *lpNumberOfBytesRead = *(DWORD *)((int)&lpOverlapped->Internal + 4);
    }
  }
  return 1;
}



BOOL XAPILIB::WriteFile(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,
                       LPDWORD lpNumberOfBytesWritten,LPOVERLAPPED lpOverlapped)

{
  _union_17 dwErrCode;
  _union_17 uVar1;
  _LARGE_INTEGER local_14;
  _union_17 local_c;
  DWORD local_8;
  
  if (lpNumberOfBytesWritten != (LPDWORD)0x0) {
    *lpNumberOfBytesWritten = 0;
  }
  if (lpOverlapped == (LPOVERLAPPED)0x0) {
    uVar1.Status = NtWriteFile(hFile,(HANDLE)0x0,(PIO_APC_ROUTINE)0x0,(PVOID)0x0,
                               (PIO_STATUS_BLOCK)&local_c,lpBuffer,nNumberOfBytesToWrite,
                               (PLARGE_INTEGER)0x0);
    if (((uVar1.Status != 0x103) ||
        (dwErrCode.Status = NtWaitForSingleObject(hFile,'\0',(PLARGE_INTEGER)0x0), uVar1 = local_c,
        -1 < dwErrCode.Status)) && (dwErrCode = uVar1, -1 < uVar1.Status)) {
      *lpNumberOfBytesWritten = local_8;
      return 1;
    }
    if ((dwErrCode.Status & 0xc0000000U) == 0x80000000) {
      *lpNumberOfBytesWritten = local_8;
    }
  }
  else {
    local_14.field0.LowPart = (ULONG)lpOverlapped->InternalHigh;
    local_14.field0.HighPart = *(LONG *)((int)&lpOverlapped->InternalHigh + 4);
    *(undefined4 *)&lpOverlapped->Internal = 0x103;
    dwErrCode.Status =
         NtWriteFile(hFile,(lpOverlapped->u).Pointer,(PIO_APC_ROUTINE)0x0,
                     (PVOID)(~-(uint)(((uint)(lpOverlapped->u).Pointer & 1) != 0) &
                            (uint)lpOverlapped),(PIO_STATUS_BLOCK)lpOverlapped,lpBuffer,
                     nNumberOfBytesToWrite,&local_14);
    if (((dwErrCode.Status & 0xc0000000U) != 0xc0000000) && (dwErrCode.Status != 0x103)) {
      if (lpNumberOfBytesWritten != (LPDWORD)0x0) {
        *lpNumberOfBytesWritten = *(DWORD *)((int)&lpOverlapped->Internal + 4);
      }
      return 1;
    }
  }
  XapiSetLastNTError(dwErrCode.Status);
  return 0;
}




BOOL XAPILIB::SetEndOfFile(HANDLE hFile)

{
  DWORD DVar1;
  _IO_STATUS_BLOCK local_24;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DVar1 = NtQueryInformationFile(hFile,&local_24,&local_c,8,FilePositionInformation);
  if ((int)DVar1 < 0) {
    XapiSetLastNTError(DVar1);
  }
  else {
    local_14 = local_c;
    local_10 = local_8;
    DVar1 = NtSetInformationFile(hFile,&local_24,&local_14,8,FileEndOfFileInformation);
    if (-1 < (int)DVar1) {
      local_1c = local_c;
      local_18 = local_8;
      DVar1 = NtSetInformationFile(hFile,&local_24,&local_1c,8,FileAllocationInformation);
      if (-1 < (int)DVar1) {
        return 1;
      }
    }
    XapiSetLastNTError(DVar1);
  }
  return 0;
}



DWORD XAPILIB::SetFilePointer
                (HANDLE hFile,LONG lDistanceToMove,PLONG lpDistanceToMoveHigh,DWORD dwMoveMethod)

{
  DWORD DVar1;
  uint uVar2;
  undefined1 local_4c [40];
  uint local_24;
  int local_20;
  _IO_STATUS_BLOCK local_14;
  DWORD local_c;
  uint local_8;
  
  if (lpDistanceToMoveHigh == (PLONG)0x0) {
    uVar2 = lDistanceToMove >> 0x1f;
  }
  else {
    uVar2 = *lpDistanceToMoveHigh;
  }
  if (dwMoveMethod == 0) {
    local_c = lDistanceToMove;
  }
  else {
    if ((dwMoveMethod == 1) || (dwMoveMethod != 2)) {
      DVar1 = NtQueryInformationFile(hFile,&local_14,&local_c,8,FilePositionInformation);
      local_24 = local_c;
    }
    else {
      DVar1 = NtQueryInformationFile(hFile,&local_14,local_4c,0x38,FileNetworkOpenInformation);
      local_8 = local_20;
    }
    if ((int)DVar1 < 0) {
      XapiSetLastNTError(DVar1);
      return 0xffffffff;
    }
    local_c = local_24 + lDistanceToMove;
    uVar2 = local_8 + uVar2 + (uint)CARRY4(local_24,lDistanceToMove);
  }
  local_8 = uVar2;
  if (((int)uVar2 < 1) && ((int)uVar2 < 0)) {
    DVar1 = 0x83;
  }
  else {
    if ((lpDistanceToMoveHigh != (PLONG)0x0) || ((uVar2 & 0x7fffffff) == 0)) {
      DVar1 = NtSetInformationFile(hFile,&local_14,&local_c,8,FilePositionInformation);
      if ((int)DVar1 < 0) {
        XapiSetLastNTError(DVar1);
        if (lpDistanceToMoveHigh != (PLONG)0x0) {
          *lpDistanceToMoveHigh = -1;
          return 0xffffffff;
        }
        return 0xffffffff;
      }
      if (lpDistanceToMoveHigh != (PLONG)0x0) {
        *lpDistanceToMoveHigh = local_8;
      }
      if (local_c == 0xffffffff) {
        SetLastError(0);
        return local_c;
      }
      return local_c;
    }
    DVar1 = 0x57;
  }
  SetLastError(DVar1);
  return 0xffffffff;
}



BOOL XAPILIB::SetFilePointerEx
               (HANDLE hFile,LARGE_INTEGER liDistanceToMove,PLARGE_INTEGER lpNewFilePointer,
               DWORD dwMoveMethod)

{
  DWORD dwErrCode;
  bool bVar1;
  uint in_stack_00000008;
  undefined1 local_4c [40];
  uint local_24;
  int local_20;
  _IO_STATUS_BLOCK local_14;
  uint local_c;
  int local_8;
  
  if (lpNewFilePointer != (PLARGE_INTEGER)0x0) {
    if ((lpNewFilePointer == (PLARGE_INTEGER)0x1) || (lpNewFilePointer != (PLARGE_INTEGER)0x2)) {
      dwErrCode = NtQueryInformationFile(hFile,&local_14,&local_c,8,FilePositionInformation);
      if ((int)dwErrCode < 0) goto LAB_0014b7a0;
      bVar1 = CARRY4(local_c,in_stack_00000008);
      in_stack_00000008 = local_c + in_stack_00000008;
      liDistanceToMove.s.LowPart = local_8 + liDistanceToMove.s.LowPart + (uint)bVar1;
    }
    else {
      dwErrCode = NtQueryInformationFile(hFile,&local_14,local_4c,0x38,FileNetworkOpenInformation);
      if ((int)dwErrCode < 0) goto LAB_0014b7a0;
      bVar1 = CARRY4(local_24,in_stack_00000008);
      in_stack_00000008 = local_24 + in_stack_00000008;
      liDistanceToMove.s.LowPart = local_20 + liDistanceToMove.s.LowPart + (uint)bVar1;
    }
  }
  local_c = in_stack_00000008;
  local_8 = liDistanceToMove.s.LowPart;
  if (((int)liDistanceToMove.s.LowPart < 1) && ((int)liDistanceToMove.s.LowPart < 0)) {
    SetLastError(0x83);
    return 0;
  }
  dwErrCode = NtSetInformationFile(hFile,&local_14,&local_c,8,FilePositionInformation);
  if (-1 < (int)dwErrCode) {
    if (liDistanceToMove.s.HighPart != 0) {
      *(uint *)liDistanceToMove.s.HighPart = local_c;
      *(int *)(liDistanceToMove.s.HighPart + 4) = local_8;
    }
    return 1;
  }
LAB_0014b7a0:
  XapiSetLastNTError(dwErrCode);
  return 0;
}



BOOL XAPILIB::GetFileTime
               (HANDLE hFile,LPFILETIME lpCreationTime,LPFILETIME lpLastAccessTime,
               LPFILETIME lpLastWriteTime)

{
  DWORD dwErrCode;
  BOOL BVar1;
  DWORD local_44;
  DWORD local_40;
  DWORD local_3c;
  DWORD local_38;
  DWORD local_34;
  DWORD local_30;
  _IO_STATUS_BLOCK local_c;
  
  dwErrCode = NtQueryInformationFile(hFile,&local_c,&local_44,0x38,FileNetworkOpenInformation);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
    BVar1 = 0;
  }
  else {
    if (lpCreationTime != (LPFILETIME)0x0) {
      lpCreationTime->dwLowDateTime = local_44;
      lpCreationTime->dwHighDateTime = local_40;
    }
    if (lpLastAccessTime != (LPFILETIME)0x0) {
      lpLastAccessTime->dwLowDateTime = local_3c;
      lpLastAccessTime->dwHighDateTime = local_38;
    }
    if (lpLastWriteTime != (LPFILETIME)0x0) {
      lpLastWriteTime->dwLowDateTime = local_34;
      lpLastWriteTime->dwHighDateTime = local_30;
    }
    BVar1 = 1;
  }
  return BVar1;
}



BOOL XAPILIB::SetFileTime
               (HANDLE hFile,FILETIME *lpCreationTime,FILETIME *lpLastAccessTime,
               FILETIME *lpLastWriteTime)

{
  DWORD dwErrCode;
  int iVar1;
  DWORD *pDVar2;
  DWORD local_34 [4];
  DWORD local_24;
  DWORD local_20;
  _IO_STATUS_BLOCK local_c;
  
  pDVar2 = local_34;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pDVar2 = 0;
    pDVar2 = pDVar2 + 1;
  }
  if (lpCreationTime != (FILETIME *)0x0) {
    local_34[0] = lpCreationTime->dwLowDateTime;
    local_34[1] = lpCreationTime->dwHighDateTime;
  }
  if (lpLastAccessTime != (FILETIME *)0x0) {
    local_34[2] = lpLastAccessTime->dwLowDateTime;
    local_34[3] = lpLastAccessTime->dwHighDateTime;
  }
  if (lpLastWriteTime != (FILETIME *)0x0) {
    local_24 = lpLastWriteTime->dwLowDateTime;
    local_20 = lpLastWriteTime->dwHighDateTime;
  }
  dwErrCode = NtSetInformationFile(hFile,&local_c,local_34,0x28,FileBasicInformation);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
  }
  return (uint)((int)dwErrCode >= 0);
}




BOOL XAPILIB::FlushFileBuffers(HANDLE hFile)

{
  DWORD dwErrCode;
  _IO_STATUS_BLOCK local_c;
  
  dwErrCode = NtFlushBuffersFile(hFile,&local_c);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
  }
  return (uint)((int)dwErrCode >= 0);
}




BOOL XAPILIB::GetFileSizeEx(HANDLE hFile,PLARGE_INTEGER endOfFile)

{
  DWORD dwErrCode;
  FILE_NETWORK_OPEN_INFORMATION info;
  _IO_STATUS_BLOCK local_c;
  
  dwErrCode = NtQueryInformationFile(hFile,&local_c,&info,0x38,FileNetworkOpenInformation);
  if (-1 < (int)dwErrCode) {
    (endOfFile->s).LowPart = info.EndOfFile.field0.LowPart;
    (endOfFile->s).HighPart = info.EndOfFile.field0.HighPart;
  }
  else {
    XapiSetLastNTError(dwErrCode);
  }
  return (uint)(-1 < (int)dwErrCode);
}




DWORD XAPILIB::GetFileSize(HANDLE hFile,LPDWORD lpFileSizeHigh)

{
  BOOL BVar1;
  LARGE_INTEGER local_c;
  
  BVar1 = GetFileSizeEx(hFile,&local_c);
  if (BVar1 == 0) {
    local_c.s.LowPart = 0xffffffff;
  }
  else {
    if (lpFileSizeHigh != (LPDWORD)0x0) {
      *lpFileSizeHigh = local_c.s.HighPart;
    }
    if (local_c.s.LowPart == 0xffffffff) {
      SetLastError(0);
    }
  }
  return local_c.s.LowPart;
}




void XAPILIB::OutputDebugStringA(LPCSTR lpOutputString)

{
  char cVar1;
  code *pcVar2;
  LPCSTR pCVar3;
  
  pCVar3 = lpOutputString;
  do {
    cVar1 = *pCVar3;
    pCVar3 = pCVar3 + 1;
  } while (cVar1 != '\0');
  pcVar2 = (code *)swi(0x2d);
  (*pcVar2)(lpOutputString);
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}




DWORD XAPILIB::GetTickCount(void)

{
  return *(DWORD *)KeTickCount_exref;
}




void XAPILIB::XapiCallThreadNotifyRoutines(undefined4 param_1)

{
  undefined **ppuVar1;
  undefined **ppuVar2;
  
  RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)FUN_0032c9c4);
  ppuVar2 = (undefined **)XapiThreadNotifyRoutineList;
  while (ppuVar2 != &XapiThreadNotifyRoutineList) {
    ppuVar1 = (undefined **)*ppuVar2;
    (*(code *)ppuVar2[2])(param_1);
    ppuVar2 = ppuVar1;
  }
  RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)FUN_0032c9c4);
  return;
}




BOOL XAPILIB::SetThreadPriority(HANDLE hThread,int nPriority)

{
  BOOLEAN BVar1;
  int3 extraout_var;
  BOOL BVar2;
  int Increment;
  
  BVar1 = ObReferenceObjectByHandle(hThread,(POBJECT_TYPE)PsThreadObjectType_exref,&hThread);
  if (extraout_var < 0) {
    XapiSetLastNTError(CONCAT31(extraout_var,BVar1));
    BVar2 = 0;
  }
  else {
    if (nPriority == 0xf) {
      Increment = 0x10;
    }
    else {
      Increment = nPriority;
      if (nPriority == -0xf) {
        Increment = -0x10;
      }
    }
    KeSetBasePriorityThread(hThread,Increment);
    ObfDereferenceObject(hThread);
    BVar2 = 1;
  }
  return BVar2;
}




DWORD XAPILIB::SuspendThread(HANDLE hThread)

{
  DWORD dwErrCode;
  
  dwErrCode = NtSuspendThread(hThread,(PULONG)&hThread);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
    hThread = (HANDLE)0xffffffff;
  }
  return (DWORD)hThread;
}




DWORD XAPILIB::ResumeThread(HANDLE hThread)

{
  DWORD dwErrCode;
  
  dwErrCode = NtResumeThread(hThread,(PULONG)&hThread);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
    hThread = (HANDLE)0xffffffff;
  }
  return (DWORD)hThread;
}



void XAPILIB::RaiseException
               (DWORD dwExceptionCode,DWORD dwExceptionFlags,DWORD nNumberOfArguments,
               ULONG_PTR *lpArguments)

{
  DWORD DVar1;
  ULONG_PTR *pUVar2;
  _EXCEPTION_RECORD local_54;
  
  local_54.ExceptionRecord = (_EXCEPTION_RECORD *)0x0;
  local_54.ExceptionCode = dwExceptionCode;
  local_54.ExceptionFlags = dwExceptionFlags & 1;
  local_54.ExceptionAddress = RaiseException;
  if (lpArguments == (ULONG_PTR *)0x0) {
    local_54.NumberParameters = 0;
  }
  else {
    if (0xf < nNumberOfArguments) {
      nNumberOfArguments = 0xf;
    }
    local_54.NumberParameters = nNumberOfArguments;
    if (nNumberOfArguments != 0) {
      pUVar2 = local_54.ExceptionInformation;
      for (DVar1 = nNumberOfArguments; DVar1 != 0; DVar1 = DVar1 - 1) {
        *pUVar2 = (ULONG_PTR)*lpArguments;
        lpArguments = (ULONG_PTR *)((int)lpArguments + 4);
        pUVar2 = pUVar2 + 1;
      }
    }
  }
  RtlRaiseException(&local_54);
  return;
}




BOOL XAPILIB::SwitchToThread(void)

{
  NTSTATUS NVar1;
  
  NVar1 = NtYieldExecution();
  return (uint)(NVar1 != 0x40000024);
}



LPTOP_LEVEL_EXCEPTION_FILTER

XAPILIB::SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)

{
  LPTOP_LEVEL_EXCEPTION_FILTER pPVar1;
  
  pPVar1 = g_XapiCurrentTopLevelFilter;
  g_XapiCurrentTopLevelFilter = lpTopLevelExceptionFilter;
  return pPVar1;
}




void XAPILIB::XRegisterThreadNotifyRoutine(PXTHREAD_NOTIFICATION pThreadNotification,BOOL fRegister)

{
  _LIST_ENTRY *p_Var1;
  _LIST_ENTRY *p_Var2;
  
  RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)FUN_0032c9c4);
  if (fRegister == 0) {
    p_Var1 = (pThreadNotification->Reserved).Flink;
    p_Var2 = (pThreadNotification->Reserved).Blink;
    p_Var2->Flink = p_Var1;
    p_Var1->Blink = p_Var2;
  }
  else {
    (pThreadNotification->Reserved).Flink = (_LIST_ENTRY *)&XapiThreadNotifyRoutineList;
    (pThreadNotification->Reserved).Blink = (_LIST_ENTRY *)PTR_XapiThreadNotifyRoutineList_0032c9e4;
    *(PXTHREAD_NOTIFICATION *)PTR_XapiThreadNotifyRoutineList_0032c9e4 = pThreadNotification;
    PTR_XapiThreadNotifyRoutineList_0032c9e4 = (undefined *)pThreadNotification;
  }
  RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)FUN_0032c9c4);
  return;
}




LONG XAPILIB::UnhandledExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo)

{
  int iVar1;
  int unaff_FS_OFFSET;
  
  iVar1 = *(int *)(*(int *)(unaff_FS_OFFSET + 0x20) + 0x250);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (**(code **)(iVar1 + 0x14))(0xc,0);
  }
  if (((iVar1 == 0) && (g_XapiCurrentTopLevelFilter != (code *)0x0)) &&
     (iVar1 = (*g_XapiCurrentTopLevelFilter)(ExceptionInfo), iVar1 == -1)) {
    return -1;
  }
  return 0;
}



// WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog


void XAPILIB::XapiThreadStartup(DWORD dwDummy1,DWORD dwDummy2)

{
  NTSTATUS ExitStatus;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int unaff_FS_OFFSET;
  
  puVar2 = *(undefined4 **)(*(int *)(unaff_FS_OFFSET + 0x28) + 0x28);
  puVar4 = puVar2 + 1;
  *puVar2 = puVar4;
  puVar2 = (undefined4 *)0;
  puVar3 = puVar4;
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  for (iVar1 = 0x24; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined1 *)puVar4 = 0;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  XapiCallThreadNotifyRoutines(1);
  ExitStatus = (*(code *)dwDummy1)(dwDummy2);
  XapiCallThreadNotifyRoutines(0);
                    // WARNING: Subroutine does not return
  PsTerminateSystemThread(ExitStatus);
}



HANDLE XAPILIB::CreateThread
                 (LPSECURITY_ATTRIBUTES lpThreadAttributes,SIZE_T dwStackSize,
                 LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,DWORD dwCreationFlags,
                 LPDWORD lpThreadId)

{
  HANDLE KernelStackSize;
  DWORD dwErrCode;
  int unaff_FS_OFFSET;
  HANDLE in_stack_00000008;
  
  KernelStackSize = in_stack_00000008;
  if (in_stack_00000008 == (HANDLE)0x0) {
    KernelStackSize = (HANDLE)0x10000;
  }
  dwErrCode = PsCreateSystemThreadEx
                        (&stack0x00000008,0,(SIZE_T)KernelStackSize,DAT_00549528,lpParameter,
                         (PKSTART_ROUTINE)dwStackSize,dwStackSize._4_4_,
                         (byte)((uint)lpStartAddress >> 2) & 1,'\0',XapiThreadStartup);
  if ((((int)dwErrCode < 0) && (*(byte *)(unaff_FS_OFFSET + 0x24) < 2)) &&
     (*(int *)(*(int *)(unaff_FS_OFFSET + 0x28) + 0x28) != 0)) {
    XapiSetLastNTError(dwErrCode);
    in_stack_00000008 = (HANDLE)0x0;
  }
  return in_stack_00000008;
}




DWORD XAPILIB::GetCurrentThreadId(void)

{
  int unaff_FS_OFFSET;
  
  return *(DWORD *)(*(int *)(unaff_FS_OFFSET + 0x28) + 300);
}




void XAPILIB::GetSystemTimeAsFileTime(PLARGE_INTEGER CurrentTime)

{
                    // WARNING: Could not recover jumptable at 0x0014bc60. Too many branches
                    // WARNING: Treating indirect jump as call
  KeQuerySystemTime(CurrentTime);
  return;
}




void XAPILIB::wvsprintfW(wchar_t *param_1,size_t param_2,wchar_t *param_3)

{
  __gnuc_va_list unaff_retaddr;
  
  _vswprintf(param_1,param_2,param_3,unaff_retaddr);
  return;
}




void XAPILIB::wsprintfW(undefined4 param_1,undefined4 param_2)

{
  wvsprintfW(param_1,param_2,&stack0x0000000c);
  return;
}




NTSTATUS XAPILIB::XapiSelectCachePartition(int param_1,uint *param_2,undefined4 *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  dword *__dest;
  int iVar5;
  uint uVar6;
  uint uVar7;
  dword *pdVar8;
  uint uVar9;
  uint local_230 [2];
  dword local_228;
  uint local_224 [2];
  dword local_21c [121];
  int local_38;
  _OBJECT_ATTRIBUTES local_30;
  _IO_STATUS_BLOCK local_24;
  _LARGE_INTEGER local_1c;
  dword local_14;
  NTSTATUS local_10;
  HANDLE local_c;
  uint local_8;
  
  local_14 = XBE_CERTIFICATE_HEADER_00010184.TitleID;
  local_30.RootDirectory = (HANDLE)0x0;
  local_30.Attributes = 0x40;
  local_30.ObjectName = (PANSI_STRING)&PTR_DAT_0020324c;
  local_10 = NtOpenFile(&local_c,0xc0100000,&local_30,&local_24,3,0x10);
  if (local_10 < 0) {
    return local_10;
  }
  local_1c.field0.LowPart = 0x800;
  local_1c.field0.HighPart = 0;
  local_10 = NtReadFile(local_c,(HANDLE)0x0,(PIO_APC_ROUTINE)0x0,(PVOID)0x0,&local_24,local_230,
                        0x200,&local_1c);
  if (local_10 < 0) goto LAB_0014bfbe;
  iVar1 = *(int *)HalDiskCachePartitionCount_exref;
  if (((local_230[0] != 0x97315286) || (local_38 != -0x55ab0000)) || (local_230[1] != 2)) {
    puVar4 = local_230;
    for (iVar5 = 0x80; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    local_230[0] = 0x97315286;
    local_230[1] = 2;
    local_38 = -0x55ab0000;
  }
  *param_3 = 1;
  uVar6 = *(uint *)HalDiskCachePartitionCount_exref;
  if (0x29 < uVar6) {
    uVar6 = 0x29;
  }
  uVar9 = uVar6 - 1;
  uVar7 = 0;
  uVar3 = 0;
  local_8 = uVar9;
  uVar2 = iVar1 - 1;
  if (uVar6 != 0) {
    pdVar8 = &local_228;
    do {
      if ((local_14 == *pdVar8) && (pdVar8[2] != 0)) {
        uVar7 = local_224[uVar3 * 3] + 3;
        *param_3 = 0;
        uVar2 = uVar3;
        uVar9 = local_8;
        if (uVar7 != 0) goto LAB_0014bf06;
        break;
      }
      uVar3 = uVar3 + 1;
      pdVar8 = pdVar8 + 3;
      uVar9 = local_8;
    } while (uVar3 < uVar6);
  }
  uVar3 = uVar2;
  param_3 = (undefined4 *)0x0;
  if (uVar6 == 0) {
LAB_0014bef4:
    uVar7 = local_224[uVar9 * 3] + 3;
  }
  else {
    do {
      local_8 = 0;
      puVar4 = local_224;
      do {
        if ((puVar4[1] != 0) && ((undefined4 *)*puVar4 == param_3)) break;
        local_8 = local_8 + 1;
        puVar4 = puVar4 + 3;
      } while (local_8 < uVar6);
      if (local_8 == uVar6) {
        uVar7 = (int)param_3 + 3;
      }
      param_3 = (undefined4 *)((int)param_3 + 1);
    } while (param_3 < uVar6);
    if (uVar7 == 0) goto LAB_0014bef4;
  }
LAB_0014bf06:
  if (uVar6 + 3 <= uVar7) {
    uVar7 = uVar6 + 2;
  }
  *param_2 = uVar7;
  DAT_0032c9f8 = -(uint)(param_1 != 0) & uVar9;
  if (DAT_0032c9f8 < uVar3) {
    pdVar8 = &local_228;
    __dest = local_21c;
    uVar9 = uVar3;
LAB_0014bf56:
    _memmove(__dest,pdVar8,uVar9 * 0xc);
  }
  else if (uVar3 < DAT_0032c9f8) {
    uVar9 = uVar9 - uVar3;
    __dest = &local_228 + uVar3 * 3;
    pdVar8 = local_21c + uVar3 * 3;
    goto LAB_0014bf56;
  }
  (&local_228)[DAT_0032c9f8 * 3] = local_14;
  local_224[DAT_0032c9f8 * 3] = uVar7 - 3;
  local_224[DAT_0032c9f8 * 3 + 1] = (uint)(param_1 == 0);
  NtWriteFile(local_c,(HANDLE)0x0,(PIO_APC_ROUTINE)0x0,(PVOID)0x0,&local_24,local_230,0x200,
              &local_1c);
LAB_0014bfbe:
  NtClose(local_c);
  return local_10;
}




BOOL XAPILIB::XMountUtilityDrive(BOOL fFormatClean)

{
  bool bVar1;
  DWORD dwErrCode;
  int iVar2;
  char local_118 [260];
  STRING local_14;
  STRING local_c;
  
  dwErrCode = XapiSelectCachePartition(fFormatClean,&local_c.Buffer,&local_14.Buffer);
  if ((int)dwErrCode < 0) goto LAB_0014c0c6;
  if ((fFormatClean != 0) || (bVar1 = false, local_14.Buffer != (PCHAR)0x0)) {
    bVar1 = true;
  }
  __snprintf(local_118,0x104,"\\Device\\Harddisk0\\Partition%d\\",local_c.Buffer);
  RtlInitAnsiString(&local_14,local_118);
  RtlInitAnsiString(&local_c,local_118);
  local_c.Length = local_c.Length - 1;
  if ((bVar1) && (iVar2 = FUN_0015118e(&local_c,0x10000), iVar2 == 0)) {
    return 0;
  }
  dwErrCode = FUN_00150833(&local_14,0x10000);
  if ((int)dwErrCode < 0) {
    if ((!bVar1) && (iVar2 = FUN_0015118e(&local_c,0x10000), iVar2 != 0)) {
      dwErrCode = FUN_00150833(&local_14,0x10000);
    }
    if (-1 < (int)dwErrCode) goto LAB_0014c0a2;
  }
  else {
LAB_0014c0a2:
    dwErrCode = IoCreateSymbolicLink((POBJECT_STRING)&PTR_SUB_0020321c,&local_c);
  }
  if (-1 < (int)dwErrCode != 0) {
    return (uint)(-1 < (int)dwErrCode);
  }
LAB_0014c0c6:
  XapiSetLastNTError(dwErrCode);
  return 0;
}




BOOL XAPILIB::XFormatUtilityDrive(void)

{
  DWORD DVar1;
  BOOL BVar2;
  char local_124 [260];
  ulong local_20;
  _OBJECT_ATTRIBUTES local_1c;
  STRING local_10;
  HANDLE local_8;
  
  local_1c.RootDirectory = (HANDLE)0x0;
  local_1c.Attributes = 0x40;
  local_1c.ObjectName = (PANSI_STRING)&PTR_SUB_0020321c;
  DVar1 = NtOpenSymbolicLinkObject(&local_8,&local_1c);
  if ((int)DVar1 < 0) {
    XapiSetLastNTError(DVar1);
    return 0;
  }
  local_10.Buffer = local_124;
  local_10.MaximumLength = 0x104;
  DVar1 = NtQuerySymbolicLinkObject(local_8,&local_10,&local_20);
  NtClose(local_8);
  if ((int)DVar1 < 0) {
    XapiSetLastNTError(DVar1);
    BVar2 = 0;
  }
  else {
    BVar2 = FUN_0015118e(&local_10,0x10000);
  }
  return BVar2;
}




BOOL XAPILIB::QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)

{
  undefined8 uVar1;
  
  uVar1 = rdtsc();
  (lpPerformanceCount->s).LowPart = (DWORD)uVar1;
  (lpPerformanceCount->s).HighPart = (LONG)((ulonglong)uVar1 >> 0x20);
  return 1;
}




BOOL XAPILIB::QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)

{
  (lpFrequency->s).HighPart = 0;
  (lpFrequency->s).LowPart = 0x2bb5c755;
  return 1;
}




void XAPILIB::XDeleteSaveGame(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  NTSTATUS Status;
  int iVar5;
  char local_148 [324];
  
  builtin_strncpy(local_148,"\\??\\",5);
  pcVar2 = local_148;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  iVar5 = (int)pcVar3 - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar5] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  pcVar2 = local_148;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_0014c2d5();
  pcVar3 = local_148;
  pcVar2 = local_148 + 1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar4 = "\\SaveMeta.xbx";
  do {
    cVar1 = *pcVar4;
    (pcVar3 + (int)(&stack0xffdfcc1c + -(int)pcVar2))[(int)pcVar4] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar5 = FUN_0014c633();
  pcVar3[(int)(local_148 + -(int)pcVar2)] = '\0';
  if (iVar5 == 0) {
    pcVar3[(int)(local_148 + (1 - (int)pcVar2))] = '\0';
    pcVar3[(int)(local_148 + -(int)pcVar2)] = '\\';
    Status = FUN_0015162f();
    RtlNtStatusToDosError(Status);
  }
  return;
}




HANDLE XAPILIB::XFindFirstSaveGame(LPCSTR lpRootPathName,XGAME_FIND_DATA *pFindGameData)

{
  LPCSTR pCVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 *hObject;
  int iVar5;
  undefined4 *puVar6;
  char local_108 [260];
  char cVar1;
  
  pCVar2 = lpRootPathName;
  do {
    cVar1 = *pCVar2;
    pCVar2[(int)(local_108 + -(int)lpRootPathName)] = cVar1;
    pCVar2 = pCVar2 + 1;
  } while (cVar1 != '\0');
  pcVar3 = local_108;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar4 = "*";
  do {
    cVar1 = *pcVar4;
    pcVar4[(int)(&stack0xffdfcbd4 + ((int)pcVar3 - (int)(local_108 + 1)))] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  hObject = System__OpenDirectory(local_108,(FILE_DIRECTORY_INFORMATION *)pFindGameData);
  if (hObject == (undefined4 *)0xffffffff) {
    return (HANDLE)0xffffffff;
  }
  iVar5 = FUN_0014c532();
  if (iVar5 == 0) {
    pFindGameData = (XGAME_FIND_DATA *)FUN_0014b22f();
    if (pFindGameData != (XGAME_FIND_DATA *)0x0) {
      do {
        iVar5 = FUN_0014c532();
        if (iVar5 != 0) break;
        pFindGameData = (XGAME_FIND_DATA *)FUN_0014b22f();
      } while (pFindGameData != (XGAME_FIND_DATA *)0x0);
      if (pFindGameData != (XGAME_FIND_DATA *)0x0) goto LAB_0014caf8;
    }
    CloseHandle(hObject);
    hObject = (undefined4 *)0xffffffff;
    SetLastError(0x12);
  }
LAB_0014caf8:
  puVar6 = hObject;
  if (hObject != (undefined4 *)0xffffffff) {
    puVar6 = XMemAlloc(0x110,0x24830000);
    if (puVar6 == (undefined4 *)0x0) {
      CloseHandle(hObject);
      puVar6 = (undefined4 *)0xffffffff;
      SetLastError(8);
    }
    else {
      *puVar6 = 0x53425645;
      puVar6[1] = hObject;
      puVar6[2] = (int)pcVar3 - (int)(local_108 + 1);
      lstrcpynA((LPSTR)(puVar6 + 3),lpRootPathName,0x104);
    }
  }
  return puVar6;
}




int XAPILIB::XFindNextSaveGame(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0014b22f(*(undefined4 *)(param_1 + 4),param_2);
  if (iVar1 != 0) {
    do {
      iVar2 = FUN_0014c532(param_2,param_1 + 0xc,*(undefined4 *)(param_1 + 8));
      if (iVar2 != 0) {
        return iVar1;
      }
      iVar1 = FUN_0014b22f(*(undefined4 *)(param_1 + 4),param_2);
    } while (iVar1 != 0);
  }
  return 0;
}




BOOL XAPILIB::XFindClose(int *param_1)

{
  int iVar1;
  BOOL BVar2;
  HANDLE hObject;
  
  iVar1 = *param_1;
  if (iVar1 != 0x434f4e54) {
    if (iVar1 == 0x4e49434b) {
      XMemFree(param_1,0x24830000);
      return 1;
    }
    if (iVar1 != 0x53425645) {
      if (iVar1 != -0x41b41600) {
        return 0;
      }
      hObject = (HANDLE)param_1[3];
      goto LAB_0014cbd4;
    }
  }
  hObject = (HANDLE)param_1[1];
LAB_0014cbd4:
  XMemFree(param_1,0x24830000);
  BVar2 = CloseHandle(hObject);
  return BVar2;
}




undefined4 XAPILIB::XCalculateSignatureBeginEx(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (param_1 < 2) {
    uVar1 = FUN_0014cd37(param_1,param_2);
  }
  else if ((param_1 == 2) || (param_1 == 4)) {
    uVar1 = FUN_0014ce19();
  }
  else if (param_1 == 8) {
    uVar1 = (*DAT_00434228)(8);
  }
  else {
    SetLastError(0x32);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}




void XAPILIB::XCalculateSignatureBegin(undefined4 param_1)

{
  XCalculateSignatureBeginEx(param_1,XBE_CERTIFICATE_HEADER_00010184.TitleID);
  return;
}




undefined4 XAPILIB::XCalculateSignatureUpdate(uint *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = *param_1;
  if (uVar1 < 2) {
    uVar2 = FUN_0014ce4f(param_1,param_2,param_3);
  }
  else if ((uVar1 == 2) || (uVar1 == 4)) {
    uVar2 = FUN_0014ce4f(param_1,param_2,param_3);
  }
  else if (uVar1 == 8) {
    uVar2 = (*DAT_0043422c)(param_1,param_2,param_3);
  }
  else {
    uVar2 = 0x32;
  }
  return uVar2;
}




undefined4 XAPILIB::XCalculateSignatureEnd(uint *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = *param_1;
  if (uVar1 < 2) {
    uVar2 = FUN_0014cdb7(param_1,param_2);
  }
  else if ((uVar1 == 2) || (uVar1 == 4)) {
    uVar2 = FUN_0014ce69(param_1,param_2);
  }
  else if (uVar1 == 8) {
    uVar2 = (*DAT_00434230)(param_1,param_2);
  }
  else {
    uVar2 = 0x32;
  }
  return uVar2;
}




BOOL XAPILIB::CancelIo(HANDLE hFile)

{
  code *****pppppcVar1;
  code ****ppppcVar2;
  code ****ppppcVar3;
  BOOLEAN BVar4;
  KIRQL NewIrql;
  int3 extraout_var;
  BOOL BVar5;
  code *****pppppcVar6;
  KDPC local_28;
  code ****local_c;
  code ****local_8;
  
  local_c = (code ****)&local_c;
  local_8 = local_c;
  BVar4 = ObReferenceObjectByHandle(hFile,(POBJECT_TYPE)IoFileObjectType_exref,&hFile);
  if (extraout_var < 0) {
    XapiSetLastNTError(CONCAT31(extraout_var,BVar4));
    BVar5 = 0;
  }
  else {
    NewIrql = KeRaiseIrqlToDpcLevel();
    pppppcVar6 = *(code ******)(IdexChannelObject_exref + 0x28);
    if (pppppcVar6 != (code *****)(IdexChannelObject_exref + 0x28)) {
      do {
        pppppcVar1 = (code *****)*pppppcVar6;
        if ((pppppcVar6[9] == hFile) && (((byte)*(code *)((int)pppppcVar6 + -0x37) & 0x10) == 0)) {
          ppppcVar2 = pppppcVar6[1];
          ppppcVar3 = *pppppcVar6;
          *ppppcVar2 = (code ***)ppppcVar3;
          ppppcVar3[1] = (code ***)ppppcVar2;
          *pppppcVar6 = (code ****)&local_c;
          pppppcVar6[1] = local_8;
          *local_8 = (code ***)pppppcVar6;
          local_8 = (code ****)pppppcVar6;
        }
        pppppcVar6 = pppppcVar1;
      } while (pppppcVar1 != (code *****)(IdexChannelObject_exref + 0x28));
    }
    KfLowerIrql(NewIrql);
    if ((code *****)local_c != &local_c) {
      KeInitializeDpc(&local_28,FUN_0014cf9c,&local_c);
      KeInsertQueueDpc(&local_28,(PVOID)0x0,(PVOID)0x0);
    }
    ObfDereferenceObject(hFile);
    BVar5 = 1;
  }
  return BVar5;
}



HANDLE CreateFileForHandle(char *stringIn,ACCESS_MASK desiredAccess,ULONG shareAccess,char *writePtr
                          ,uint fileDisposition,uint flags)

{
  ULONG create_options;
  DWORD err;
  ACCESS_MASK AVar2;
  _OBJECT_ATTRIBUTES attribs;
  _IO_STATUS_BLOCK local_18;
  STRING ansi_string;
  HANDLE handle;
  uint uVar1;
  bool valid_pathname;
  
  AVar2 = desiredAccess;
  if (fileDisposition == 1) {
    desiredAccess = FILE_CREATE;
  }
  else if (fileDisposition == 2) {
    desiredAccess = FILE_OVERWRITE_IF;
  }
  else if (fileDisposition == 3) {
    desiredAccess = FILE_OPEN;
  }
  else if (fileDisposition == 4) {
    desiredAccess = FILE_OPEN_IF;
  }
  else if ((fileDisposition != 5) ||
          (uVar1 = desiredAccess & FILE_FLAG_OVERLAPPED, desiredAccess = FILE_OVERWRITE, uVar1 == 0)
          ) {
    XAPILIB::XapiSetLastNTError(0xc000000d);
    return (HANDLE)0xffffffff;
  }
  RtlInitAnsiString(&ansi_string,stringIn);
  if ((ansi_string.Length < 2) || (stringIn[ansi_string.Length - 1] != '\\')) {
    valid_pathname = false;
  }
  else {
    valid_pathname = true;
  }
  attribs.ObjectName = &ansi_string;
  create_options =
       ((((flags >> 4 & 0x8000000 | flags & 0x20000000) >> 1 | flags & 0x8000000) >> 8 |
        flags & 0x10000000) >> 6 | flags & 0x2000000) >> 0xb | ~(flags >> 0x19) & 0x20;
  attribs.RootDirectory = (HANDLE)0xfffffffd;
  attribs.Attributes = 0x40;
  if ((flags & 0x4000000) != 0) {
    create_options = create_options | FILE_DELETE_ON_CLOSE;
    AVar2 = AVar2 | DELETE;
  }
  if ((flags & 0x2000000) == 0) {
    create_options = create_options | FILE_NON_DIRECTORY_FILE;
  }
  err = NtCreateFile(&handle,AVar2 | 0x100080,&attribs,&local_18,(PLARGE_INTEGER)0x0,flags & 0x7fa7,
                     shareAccess,desiredAccess,create_options);
  if ((int)err < 0) {
    XAPILIB::XapiSetLastNTError(err);
    if (err == 0xc0000035) {
      err = 0x50;
    }
    else {
      if (err != 0xc00000ba) {
        return (HANDLE)0xffffffff;
      }
      if (valid_pathname) {
        err = 3;
      }
      else {
        err = 5;
      }
    }
    XAPILIB::SetLastError(err);
    return (HANDLE)0xffffffff;
  }
  if (((fileDisposition == 2) && (local_18.Information == 3)) ||
     ((fileDisposition == 4 && (local_18.Information == 1)))) {
    err = 0xb7;
  }
  else {
    err = 0;
  }
  XAPILIB::SetLastError(err);
  return handle;
}




HANDLE XAPILIB::HeapCreate(DWORD flOptions,SIZE_T dwInitialSize,SIZE_T dwMaximumSize)

{
  uint uVar1;
  HANDLE pvVar2;
  uint in_stack_00000008;
  
  uVar1 = flOptions & 0x5 | 0x1000;
  if ((uint)dwInitialSize < 0x1000) {
    if ((uint)dwInitialSize == 0) {
      uVar1 = flOptions & 0x5 | 0x1002;
      goto LAB_0014d33b;
    }
    dwInitialSize._0_4_ = 0x1000;
  }
  if ((uint)dwInitialSize < in_stack_00000008) {
    dwInitialSize._0_4_ = in_stack_00000008;
  }
LAB_0014d33b:
  pvVar2 = (HANDLE)XApiProbablyDoSomething1(uVar1,0,(uint)dwInitialSize,in_stack_00000008,0,0);
  if (pvVar2 == (HANDLE)0x0) {
    SetLastError(8);
  }
  return pvVar2;
}




BOOL XAPILIB::HeapFree(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem)

{
  uint uVar1;
  
  uVar1 = FUN_0014efed(hHeap,dwFlags,lpMem);
  return uVar1 & 0xff;
}




HLOCAL XAPILIB::LocalAlloc(UINT uFlags,SIZE_T uBytes)

{
  HLOCAL pvVar1;
  undefined4 in_stack_00000008;
  
  pvVar1 = (HLOCAL)runtime::AllocateOnHeap(PTR_SomeFunction,uFlags >> 3 & 8,in_stack_00000008);
  return pvVar1;
}




HLOCAL XAPILIB::LocalFree(HLOCAL hMem)

{
  char cVar1;
  
  cVar1 = FUN_0014efed(PTR_SomeFunction,0,hMem);
  return (HLOCAL)(~-(uint)(cVar1 != '\0') & (uint)hMem);
}




void * XAPILIB::XMemAllocDefault(uint size,uint allocFlags)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 *puVar3;
  
  if ((int)allocFlags < 0) {
    if ((allocFlags & 0xf000000) == 0) {
      allocFlags = allocFlags & 0xfcffffff | 0xc000000;
    }
    uVar2 = allocFlags >> 0x18 & 0xf;
    if (uVar2 == 1) {
      puVar1 = (undefined4 *)
               FUN_0014aaba(size,0,0xffffff,0x1000,
                            *(undefined4 *)(&DAT_0032ca10 + (allocFlags >> 0x1c & 3) * 4));
    }
    else {
      puVar1 = (undefined4 *)
               XPhysicalAlloc(size,0xffffffff,1 << (sbyte)uVar2,
                              *(undefined4 *)(&DAT_0032ca10 + (allocFlags >> 0x1c & 3) * 4));
    }
    if ((puVar1 != (undefined4 *)0x0) && ((allocFlags & 0x40000000) != 0)) {
      puVar3 = puVar1;
      for (uVar2 = size >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      for (uVar2 = size & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar3 = 0;
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
    }
  }
  else {
    puVar1 = LocalAlloc(allocFlags >> 0x18 & 0x40,CONCAT44(unaff_EBP,unaff_ESI));
  }
  return puVar1;
}




void XAPILIB::XMemFreeDefault(PVOID param_1,uint param_2)

{
  if ((param_2 & 0x80000000) == 0) {
    LocalFree(param_1);
  }
  else {
    XPhysicalFree(param_1);
  }
  return;
}




uint XAPILIB::XGetVideoStandard(void)

{
  NTSTATUS NVar1;
  ulong local_c;
  uint local_8;
  
  NVar1 = ExQueryNonVolatileSetting(0x103,&local_c,&local_8,4,(PULONG)0x0);
  if (-1 < NVar1) {
    return local_8 >> 8 & 0xff;
  }
  return 0;
}



// WARNING: Inlined function: XGetAVPack


uint XAPILIB::XGetVideoFlags(void)

{
  NTSTATUS NVar1;
  int iVar2;
  ulong local_c;
  uint local_8;
  
  NVar1 = ExQueryNonVolatileSetting(8,&local_c,&local_8,4,(PULONG)0x0);
  if (NVar1 < 0) {
    local_8 = 0;
  }
  else {
    local_8 = local_8 >> 0x10 & 0x5f;
  }
  if ((*(int *)HalBootSMCVideoMode_exref == 1) && (iVar2 = XGetVideoStandard(), iVar2 != 3)) {
    return local_8;
  }
  return local_8 & 0xfffffff1;
}




uint XAPILIB::XGetLanguage(void)

{
  NTSTATUS NVar1;
  DWORD DVar2;
  ulong local_c;
  uint local_8;
  
  NVar1 = ExQueryNonVolatileSetting(7,&local_c,&local_8,4,(PULONG)0x0);
  if (NVar1 < 0) {
    local_8 = 0;
  }
  else if (9 < local_8) {
    DVar2 = XGetGameRegion();
    return (DVar2 == XC_GAME_REGION_JAPAN) + 1;
  }
  return local_8;
}




undefined4 XAPILIB::mainXapiStartup(void)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int unaff_FS_OFFSET;
  
  FUN_001517b9();
  XapiInitProcess();
  iVar1 = *(int *)(*(int *)(unaff_FS_OFFSET + 0x20) + 0x250);
  if (iVar1 == 0) {
    puVar3 = (undefined1 *)0x0;
  }
  else {
    puVar3 = *(undefined1 **)(iVar1 + 0x24);
  }
  if (puVar3 != (undefined1 *)0x0) {
    iVar1 = *(int *)(*(int *)(unaff_FS_OFFSET + 4) + _tls_index * 4);
    iVar2 = *(int *)(*(int *)(unaff_FS_OFFSET + 0x28) + 0x28);
    *puVar3 = 1;
    *(int *)(puVar3 + 4) = (iVar1 - iVar2) + 8;
  }
  _rtinit();
  _cinit();
  main();
  XapiBootToDash(1,1,0);
  return 0;
}




void XAPILIB::XapiFormatObjectAttributes(undefined4 *param_1,PANSI_STRING param_2,PCSZ param_3)

{
  RtlInitAnsiString(param_2,param_3);
  param_1[1] = param_2;
  *param_1 = 0xfffffffc;
  param_1[2] = 0x80;
  return;
}




BOOL XAPILIB::SetEvent(HANDLE hEvent)

{
  DWORD dwErrCode;
  
  dwErrCode = NtSetEvent(hEvent,(PLONG)0x0);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
  }
  return (uint)((int)dwErrCode >= 0);
}



HANDLE XAPILIB::CreateMutexA
                 (LPSECURITY_ATTRIBUTES lpMutexAttributes,BOOL bInitialOwner,LPCSTR lpName)

{
  POBJECT_ATTRIBUTES ObjectAttributes;
  DWORD DVar1;
  undefined1 local_18 [12];
  undefined1 local_c [8];
  
  if (lpName == (LPCSTR)0x0) {
    ObjectAttributes = (POBJECT_ATTRIBUTES)0x0;
  }
  else {
    ObjectAttributes = (POBJECT_ATTRIBUTES)XapiFormatObjectAttributes(local_18,local_c,lpName);
  }
  DVar1 = NtCreateMutant(&lpName,ObjectAttributes,(BOOLEAN)bInitialOwner);
  if ((int)DVar1 < 0) {
    XapiSetLastNTError(DVar1);
    lpName = (LPCSTR)0x0;
  }
  else {
    if (DVar1 == 0x40000000) {
      DVar1 = 0xb7;
    }
    else {
      DVar1 = 0;
    }
    SetLastError(DVar1);
  }
  return lpName;
}




BOOL XAPILIB::ReleaseMutex(HANDLE hMutex)

{
  DWORD dwErrCode;
  
  dwErrCode = NtReleaseMutant(hMutex,(PLONG)0x0);
  if ((int)dwErrCode < 0) {
    XapiSetLastNTError(dwErrCode);
  }
  return (uint)((int)dwErrCode >= 0);
}




DWORD XAPILIB::WaitForSingleObjectEx(HANDLE hHandle,DWORD dwMilliseconds,BOOL bAlertable)

{
  PLARGE_INTEGER Timeout;
  DWORD dwErrCode;
  undefined1 local_c [8];
  
  Timeout = (PLARGE_INTEGER)FUN_0015059a(local_c,dwMilliseconds);
  while( true ) {
    dwErrCode = NtWaitForSingleObjectEx(hHandle,'\x01',(BOOLEAN)bAlertable,Timeout);
    if ((int)dwErrCode < 0) {
      XapiSetLastNTError(dwErrCode);
      return 0xffffffff;
    }
    if (bAlertable == 0) break;
    if (dwErrCode != 0x101) {
      return dwErrCode;
    }
  }
  return dwErrCode;
}



DWORD XAPILIB::WaitForMultipleObjectsEx
                (DWORD nCount,HANDLE *lpHandles,BOOL bWaitAll,DWORD dwMilliseconds,BOOL bAlertable)

{
  PLARGE_INTEGER Timeout;
  DWORD DVar1;
  HANDLE *ppvVar2;
  HANDLE local_10c [64];
  undefined1 local_c [8];
  
  if (nCount < 0x41) {
    ppvVar2 = local_10c;
    for (DVar1 = nCount; DVar1 != 0; DVar1 = DVar1 - 1) {
      *ppvVar2 = *lpHandles;
      lpHandles = lpHandles + 1;
      ppvVar2 = ppvVar2 + 1;
    }
    Timeout = (PLARGE_INTEGER)FUN_0015059a(local_c,dwMilliseconds);
    while (DVar1 = NtWaitForMultipleObjectsEx
                             ((int)(char)nCount,local_10c,(uint)(bWaitAll == 0),'\x01',
                              (BOOLEAN)bAlertable,Timeout), -1 < (int)DVar1) {
      if (bAlertable == 0) {
        return DVar1;
      }
      if (DVar1 != 0x101) {
        return DVar1;
      }
    }
    XapiSetLastNTError(DVar1);
  }
  else {
    XapiSetLastNTError(0xc000000d);
  }
  return 0xffffffff;
}




DWORD XAPILIB::SleepEx(DWORD dwMilliseconds,BOOL bAlertable)

{
  _LARGE_INTEGER *Interval;
  NTSTATUS NVar1;
  DWORD DVar2;
  _LARGE_INTEGER local_c;
  
  Interval = (PLARGE_INTEGER)FUN_0015059a(&local_c,dwMilliseconds);
  if (Interval == (PLARGE_INTEGER)0x0) {
    local_c.field0.LowPart = 0;
    local_c.field0.HighPart = -0x80000000;
    Interval = &local_c;
  }
  do {
    NVar1 = KeDelayExecutionThread('\x01',(BOOLEAN)bAlertable,Interval);
    if (bAlertable == 0) break;
  } while (NVar1 == 0x101);
  if (NVar1 == 0xc0) {
    DVar2 = 0xc0;
  }
  else {
    DVar2 = 0;
  }
  return DVar2;
}




DWORD XAPILIB::WaitForSingleObject(HANDLE hHandle,DWORD dwMilliseconds)

{
  DWORD DVar1;
  
  DVar1 = WaitForSingleObjectEx(hHandle,dwMilliseconds,0);
  return DVar1;
}



DWORD XAPILIB::WaitForMultipleObjects
                (DWORD nCount,HANDLE *lpHandles,BOOL bWaitAll,DWORD dwMilliseconds)

{
  DWORD DVar1;
  
  DVar1 = WaitForMultipleObjectsEx(nCount,lpHandles,bWaitAll,dwMilliseconds,0);
  return DVar1;
}




void XAPILIB::Sleep(DWORD dwMilliseconds)

{
  SleepEx(dwMilliseconds,0);
  return;
}




void XAPILIB::XQueryValue(ULONG param_1,PULONG param_2,PVOID param_3,ULONG param_4,PULONG param_5)

{
  NTSTATUS Status;
  
  Status = ExQueryNonVolatileSetting(param_1,param_2,param_3,param_4,param_5);
  RtlNtStatusToDosError(Status);
  return;
}




void XAPILIB::XapiBootToDash(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  int i;
  BYTE *pBVar2;
  _LAUNCH_DATA local_c04;
  
  if (XBE_CERTIFICATE_HEADER_00010184.TitleID != 0xfffe0000) {
    i = 0x300;
    pBVar2 = local_c04.Data;
    for (; i != 0; i = i + -1) {
      pBVar2[0] = '\0';
      pBVar2[1] = '\0';
      pBVar2[2] = '\0';
      pBVar2[3] = '\0';
      pBVar2 = pBVar2 + 4;
    }
    local_c04.Data[4] = '\0';
    local_c04.Data[5] = '\0';
    local_c04.Data[6] = '\0';
    local_c04.Data[7] = '\0';
    local_c04.Data._0_4_ = param_1;
    local_c04.Data._8_4_ = param_2;
    local_c04.Data._12_4_ = param_3;
    XLaunchNewImageA((LPCSTR)0x0,&local_c04);
    return;
  }
  HalReturnToFirmware(HalFatalErrorRebootRoutine);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}




void XAPILIB::XapiInitProcess(void)

{
  dword dVar1;
  int *piVar2;
  NTSTATUS NVar3;
  BOOL BVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int *BaseAddress;
  undefined4 *puVar9;
  undefined4 local_38 [12];
  dword local_8;
  
  uVar8 = 1;
  local_8 = 0;
  HalRegisterShutdownNotification((PHAL_SHUTDOWN_REGISTRATION)&PTR_LAB_0032cf18,'\x01');
  FUN_00151ab5();
  puVar9 = local_38;
  for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  local_38[0] = 0x30;
  PTR_SomeFunction = XApiProbablyDoSomething1(2,0,0x100000,0x1000,0,local_38);
  uVar7 = uVar8;
  if (PTR_SomeFunction == 0) goto LAB_00151092;
  FUN_00150e37();
  iVar6 = FUN_00151000(&PTR_DAT_0032cee8);
  if (-1 < iVar6) {
    if (((((byte)*XboxHardwareInfo_exref & 8) == 0) &&
        (NVar3 = IoCreateSymbolicLink
                           ((POBJECT_STRING)&PTR_SUB_0032ced8,(POBJECT_STRING)&PTR_LAB_0032cee0),
        NVar3 < 0)) && (NVar3 != -0x3fffffcb)) goto LAB_00151092;
    iVar6 = FUN_00150cc6(XBE_CERTIFICATE_HEADER_00010184.TitleID,0x10190);
    if (-1 < iVar6) {
      BVar4 = XMountUtilityDrive(0);
      if (BVar4 == 0) {
        XapiBootToDash(1,2,0);
      }
      dVar1 = XBE_CERTIFICATE_HEADER_00010184.GameRatings;
      uVar5 = XGetParentalControlSetting();
      if (uVar5 <= dVar1) {
        BaseAddress = (int *)0x0;
        if (((LaunchDataPage_exref != (code *)0x0) &&
            (piVar2 = *(int **)LaunchDataPage_exref, piVar2 != (int *)0x0)) &&
           (BaseAddress = piVar2, (*(byte *)(piVar2 + 0x85) & 1) != 0)) {
          *piVar2 = piVar2[0x86];
        }
        FUN_0015040d();
        if (BaseAddress == (int *)0x0) {
          return;
        }
        if (*BaseAddress != -1) {
          return;
        }
        *(undefined4 *)LaunchDataPage_exref = 0;
        MmFreeContiguousMemory(BaseAddress);
        return;
      }
      uVar8 = 1;
      uVar7 = 4;
      local_8 = dVar1;
      goto LAB_00151092;
    }
    if (iVar6 == -0x3fffff81) {
      local_8 = 0x10;
      uVar8 = 2;
      uVar7 = 0x54;
      goto LAB_00151092;
    }
  }
  uVar7 = 2;
LAB_00151092:
  XapiBootToDash(uVar8,uVar7,local_8);
  return;
}




undefined4 XAPILIB::XGetAVPack(void)

{
  return *(undefined4 *)HalBootSMCVideoMode_exref;
}




DWORD XAPILIB::XGetGameRegion(void)

{
  NTSTATUS NVar1;
  ulong local_c;
  DWORD local_8;
  
  NVar1 = ExQueryNonVolatileSetting(0x104,&local_c,&local_8,4,(PULONG)0x0);
  if (-1 < NVar1) {
    return local_8;
  }
  return 0;
}




void XAPILIB::_cinit(void)

{
  code *pcVar1;
  undefined4 *puVar2;
  
  if (PTR_FUN_00337a88 != (undefined *)0x0) {
    (*(code *)PTR_FUN_00337a88)();
  }
  puVar2 = &DAT_0032c838;
  do {
    pcVar1 = (code *)*puVar2;
    if ((pcVar1 != (code *)0x0) && (pcVar1 != (code *)0xffffffff)) {
      (*pcVar1)();
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_0032c84c);
  puVar2 = &DAT_0032c810;
  do {
    pcVar1 = (code *)*puVar2;
    if ((pcVar1 != (code *)0x0) && (pcVar1 != (code *)0xffffffff)) {
      (*pcVar1)();
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_0032c834);
  return;
}




void XAPILIB::_rtinit(void)

{
  code *pcVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_0032c800;
  do {
    pcVar1 = (code *)*puVar2;
    if ((pcVar1 != (code *)0x0) && (pcVar1 != (code *)0xffffffff)) {
      (*pcVar1)();
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_0032c80c);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


void XAPILIB::XComputeContentSignatureKey(undefined4 param_1,PUCHAR param_2)

{
  XcHMAC((PUCHAR)XboxHDKey_exref,0x10,(PUCHAR)&param_1,4,(PUCHAR)0x0,0,param_2);
  return;
}




undefined4 XAPILIB::XGetParentalControlSetting(void)

{
  NTSTATUS NVar1;
  ulong local_c;
  undefined4 local_8;
  
  NVar1 = ExQueryNonVolatileSetting(10,&local_c,&local_8,4,(PULONG)0x0);
  if (-1 < NVar1) {
    return local_8;
  }
  return 0;
}




void XAPILIB::XAutoPowerDownResetTimer(void)

{
  PKDPC unaff_retaddr;
  
  KeSetTimer((PKTIMER)&DAT_005494e0,(LARGE_INTEGER)0x5494c0ffffffcd,unaff_retaddr);
  return;
}




DWORD XAPILIB::GetTickCount(void)

{
  code *pcVar1;
  DWORD DVar2;
  
  pcVar1 = (code *)swi(3);
  DVar2 = (*pcVar1)();
  return DVar2;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address


HLOCAL XAPILIB::LocalAlloc(UINT uFlags,SIZE_T uBytes)

{
  code *pcVar1;
  HLOCAL pvVar2;
  
  pcVar1 = (code *)swi(3);
  pvVar2 = (HLOCAL)(*pcVar1)();
  return pvVar2;
}




uint XAPILIB::XGetAudioFlags(void)

{
  NTSTATUS NVar1;
  ulong local_c;
  uint local_8;
  
  NVar1 = ExQueryNonVolatileSetting(9,&local_c,&local_8,4,(PULONG)0x0);
  if (NVar1 < 0) {
    local_8 = 0;
  }
  if (*(int *)HalBootSMCVideoMode_exref == 3) {
    local_8 = 1;
  }
  else if (*(int *)HalBootSMCVideoMode_exref == 6) {
    local_8 = local_8 & 0xffff;
  }
  return local_8;
}




void XAPILIB::XInitDevices(DWORD dwPreallocTypeCount,PXDEVICE_PREALLOC_TYPE PreallocTypes)

{
  undefined **ppuVar1;
  undefined1 local_b8 [160];
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_14 [16];
  
  FUN_001ff1f0(dwPreallocTypeCount,PreallocTypes);
  ppuVar1 = &PTR_DAT_001fcdb4;
  do {
    if (*ppuVar1 != (undefined *)0x0) {
      (**(code **)(*ppuVar1 + 4))(local_b8);
    }
    ppuVar1 = ppuVar1 + 1;
  } while (ppuVar1 < &DAT_001fcdc0);
  FUN_001fd41e();
  FUN_001fd62c(local_14);
  FUN_001fd589(local_18,local_17);
  DAT_004dd388 = 0;
  FUN_001fd638();
  return;
}




int __thiscall XAPILIB::IUsbInit_GetMaxDeviceTypeCount(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  
  piVar1 = *(int **)(param_1 + 0x9c);
  uVar2 = 0;
  if ((piVar1 != (int *)0x0) && (piVar3 = piVar1, *(uint *)(param_1 + 0x98) != 0)) {
    do {
      if (*piVar3 == param_2) {
        return piVar1[uVar2 * 2 + 1];
      }
      uVar2 = uVar2 + 1;
      piVar3 = piVar3 + 2;
    } while (uVar2 < *(uint *)(param_1 + 0x98));
  }
  return 0;
}




undefined * __fastcall XAPILIB::GetTypeInformation_8(char param_1,char *param_2)

{
  undefined **ppuVar1;
  char cVar2;
  
  ppuVar1 = &g_DeviceTypeInfoTableBegin;
  cVar2 = '\0';
  *param_2 = '\0';
  do {
    if (*ppuVar1 != (char *)0x0) {
      if (**ppuVar1 == param_1) {
        *param_2 = cVar2;
        return *ppuVar1;
      }
      cVar2 = cVar2 + '\x01';
    }
    ppuVar1 = ppuVar1 + 1;
  } while (ppuVar1 < &g_DeviceTypeInfoTableEnd);
  return (undefined *)0x0;
}




undefined * __fastcall XAPILIB::GetTypeInformation_4(int param_1)

{
  undefined **ppuVar1;
  
  ppuVar1 = &g_DeviceTypeInfoTableBegin;
  while ((*ppuVar1 == (undefined *)0x0 || (*(int *)(*ppuVar1 + 4) != param_1))) {
    ppuVar1 = ppuVar1 + 1;
    if ((undefined **)((int)&PTR_DAT_001fcda8 + 3) < ppuVar1) {
      return (undefined *)0x0;
    }
  }
  return *ppuVar1;
}



HANDLE XAPILIB::XInputOpen(PXPP_DEVICE_TYPE DeviceType,DWORD dwPort,DWORD dwSlot,
                          PXINPUT_POLLING_PARAMETERS pPollingParameters)

{
  int iVar1;
  DWORD dwErrCode;
  HANDLE local_8;
  
  local_8 = (HANDLE)0x0;
  iVar1 = GetTypeInformation_4();
  if (iVar1 == 0) {
    SetLastError(0x57);
    local_8 = (HANDLE)0x0;
  }
  else {
    if (pPollingParameters == (PXINPUT_POLLING_PARAMETERS)0x0) {
      pPollingParameters = *(PXINPUT_POLLING_PARAMETERS *)(iVar1 + 0x10);
    }
    dwErrCode = FUN_001fe934(&local_8,pPollingParameters);
    if (local_8 == (HANDLE)0x0) {
      SetLastError(dwErrCode);
    }
  }
  return local_8;
}




void XAPILIB::XInputClose(HANDLE hDevice)

{
  XID_fCloseDevice();
  return;
}




DWORD XAPILIB::XInputGetState(HANDLE hDevice,PXINPUT_STATE pState)

{
  KIRQL NewIrql;
  uint uVar2;
  DWORD DVar3;
  undefined4 *puVar4;
  byte bVar1;
  
  DVar3 = 0;
  NewIrql = KeRaiseIrqlToDpcLevel();
  if ((*(byte *)(*(int *)((int)hDevice + 0xa3) + 0x28) & 0x10) == 0) {
    if ((*(int *)hDevice == 0) || ((*(byte *)(*(int *)hDevice + 4) & 2) != 0)) {
      DVar3 = 0x48f;
    }
    pState->dwPacketNumber = *(DWORD *)((int)hDevice + 8);
    *(byte *)((int)hDevice + 0xa2) = *(byte *)((int)hDevice + 0xa2) & 0xef;
    bVar1 = **(byte **)(*(int *)((int)hDevice + 0xa3) + 8);
    puVar4 = (undefined4 *)((int)hDevice + 0x14);
    for (uVar2 = (uint)(bVar1 >> 2); pState = (PXINPUT_STATE)&pState->field1_0x4, uVar2 != 0;
        uVar2 = uVar2 - 1) {
      *(undefined4 *)pState = *puVar4;
      puVar4 = puVar4 + 1;
    }
    for (uVar2 = bVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)pState = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      pState = (PXINPUT_STATE)((int)pState + 1);
    }
  }
  else {
    DVar3 = 0x57;
  }
  KfLowerIrql(NewIrql);
  return DVar3;
}




DWORD XAPILIB::XInputSetState(HANDLE hDevice,PXINPUT_FEEDBACK pFeedback)

{
  DWORD DVar1;
  
  if ((*(byte *)(*(int *)((int)hDevice + 0xa3) + 0x28) & 0x20) == 0) {
    (pFeedback->Header).Unknown2[0x30] = '\0';
    (pFeedback->Header).Unknown2[0x31] = **(char **)(*(int *)((int)hDevice + 0xa3) + 0xc) + '\x02';
    DVar1 = FUN_001fe634();
  }
  else {
    DVar1 = 0x57;
  }
  return DVar1;
}




void XAPILIB::XInitDevices(DWORD dwPreallocTypeCount,PXDEVICE_PREALLOC_TYPE PreallocTypes)

{
  undefined **ppuVar1;
  undefined1 auStack_b8 [160];
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 auStack_14 [16];
  
  FUN_001ff1f0(dwPreallocTypeCount,PreallocTypes);
  ppuVar1 = &PTR_DAT_001fcdb4;
  do {
    if (*ppuVar1 != (undefined *)0x0) {
      (**(code **)(*ppuVar1 + 4))(auStack_b8);
    }
    ppuVar1 = ppuVar1 + 1;
  } while (ppuVar1 < &DAT_001fcdc0);
  FUN_001fd41e();
  FUN_001fd62c(auStack_14);
  FUN_001fd589(uStack_18,uStack_17);
  DAT_004dd388 = 0;
  FUN_001fd638();
  return;
}




DWORD XAPILIB::XGetDevices(XPP_DEVICE_TYPE *DeviceType)

{
  DWORD DVar1;
  KIRQL NewIrql;
  
  NewIrql = KeRaiseIrqlToDpcLevel();
  DVar1 = DeviceType->CurrentConnected;
  DeviceType->ChangeConnected = 0;
  DeviceType->PreviousConnected = DVar1;
  KfLowerIrql(NewIrql);
  return DVar1;
}




BOOL XAPILIB::XGetDeviceChanges(PXPP_DEVICE_TYPE DeviceType,PDWORD pdwInsertions,PDWORD pdwRemovals)

{
  KIRQL NewIrql;
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if (DeviceType->ChangeConnected == 0) {
    *pdwInsertions = 0;
    *pdwRemovals = 0;
  }
  else {
    NewIrql = KeRaiseIrqlToDpcLevel();
    *pdwInsertions = ~DeviceType->PreviousConnected & DeviceType->CurrentConnected;
    uVar1 = ~DeviceType->CurrentConnected & DeviceType->PreviousConnected;
    *pdwRemovals = uVar1;
    uVar2 = DeviceType->ChangeConnected & DeviceType->PreviousConnected &
            DeviceType->CurrentConnected;
    *pdwRemovals = uVar1 | uVar2;
    *pdwInsertions = *pdwInsertions | uVar2;
    DeviceType->ChangeConnected = 0;
    DeviceType->PreviousConnected = DeviceType->CurrentConnected;
    KfLowerIrql(NewIrql);
    uVar1 = (uint)(*pdwInsertions != 0 || *pdwRemovals != 0);
  }
  return uVar1;
}




void __fastcall XAPILIB::XID_fCloseDevice(int *param_1)

{
  char *pcVar1;
  code *pcVar2;
  undefined1 local_18 [2];
  undefined1 local_16;
  undefined4 local_14;
  undefined4 **local_10;
  undefined4 **local_c;
  KIRQL local_5;
  
  local_5 = KeRaiseIrqlToDpcLevel();
  pcVar2 = *(code **)(*(int *)((int)param_1 + 0xa3) + 0x1c);
  if (pcVar2 != (code *)0x0) {
    (*pcVar2)();
  }
  if (*param_1 == 0) {
    KfLowerIrql(local_5);
  }
  else {
    *(byte *)((int)param_1 + 0xa2) = *(byte *)((int)param_1 + 0xa2) | 1;
    local_10 = &local_10;
    local_18[0] = 0;
    local_16 = 4;
    local_14 = 0;
    *(undefined1 **)((int)param_1 + 0x9e) = local_18;
    local_c = local_10;
    FUN_001fe3ad();
    KfLowerIrql(local_5);
    KeWaitForSingleObject(local_18,Executive,'\0','\0',(PLARGE_INTEGER)0x0);
  }
  pcVar1 = (char *)(*(int *)((int)param_1 + 0xa3) + 1);
  *pcVar1 = *pcVar1 + '\x01';
  *(int **)((int)param_1 + 0xa7) = DAT_004dd2f0;
  DAT_004dd2f0 = param_1;
  return;
}




void XAPILIB::XInputClose(HANDLE hDevice)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(1);
  (*pcVar1)();
  return;
}




BOOL XAPILIB::XGetDeviceChanges(PXPP_DEVICE_TYPE DeviceType,PDWORD pdwInsertions,PDWORD pdwRemovals)

{
  undefined4 in_EAX;
  
  return CONCAT31((int3)((uint)in_EAX >> 8),(char)in_EAX + -0x3d);
}




