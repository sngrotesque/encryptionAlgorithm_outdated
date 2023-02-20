#ifndef __SNC_H__
#define __SNC_H__

#include "../../bits.h"

// #define SNC_256 // 32 Bytes
// #define SNC_512 // 64 Bytes
// #define SNC_768 // 96 Bytes

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

#define SNC_CIPHER_XOR(x, y) (x ^= y) // 加解密块中的异或函数

typedef snByte sncState_t[SNC_NB][SNC_NK];
typedef struct {
    snByte iv[SNC_BLOCKLEN];
    snByte rk[SNC_NR][SNC_BLOCKLEN];
} SNC_ctx;

#endif