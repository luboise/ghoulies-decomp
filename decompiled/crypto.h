/* crypto.h - Xbox PKCS1/SHA1 signature verification (XcSHA*, XcVerifyPKCS1Signature)
   From Ghidra decompilation of Grabbed by the Ghoulies default.xbe. */
#pragma once
#include "common.h"

/* ---- declarations ---- */
extern void XcSHAInit(PUCHAR pbSHAContext);
extern void XcSHAFinal(PUCHAR pbSHAContext,PUCHAR pbDigest);
extern BOOLEAN XcVerifyPKCS1Signature(PUCHAR pbSig,PUCHAR pbPubKey,PUCHAR pbDigest);
