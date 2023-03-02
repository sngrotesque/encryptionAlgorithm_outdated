#ifndef __SNC_H__
#define __SNC_H__

#include "../../bits.h"

// #define SNC_256 // 32 Bytes
// #define SNC_512 // 64 Bytes
#define SNC_768 // 96 Bytes

#define SNC_BLOCKLEN 32

#define SNC_NB 8
#define SNC_NK 4

#if defined(SNC_768)
#define SNC_NR 13
#define SNC_KEYLEN 96
#elif defined(SNC_512)
#define SNC_NR 11
#define SNC_KEYLEN 64
#else
#define SNC_NR 9
#define SNC_KEYLEN 32
#endif

#ifndef bitSwitch
#define bitSwitch(x) (((x & 0x0f) << 4) ^ (x >> 4))
#endif

typedef snByte sncState_t[SNC_NB][SNC_NK];
typedef struct {
    snByte iv[SNC_BLOCKLEN];
    snByte rk[SNC_NR][SNC_KEYLEN];
} SNC_ctx;

snVoid SNC_init_ctx(SNC_ctx *ctx, const snByte *keyBuf);
snVoid SNC_ECB_Encrypt(SNC_ctx *ctx, snByte *buf, snSize_t size);
snVoid SNC_ECB_Decrypt(SNC_ctx *ctx, snByte *buf, snSize_t size);



#endif