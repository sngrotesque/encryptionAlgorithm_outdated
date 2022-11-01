#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __S2048_H__
#define __S2048_H__ 1

typedef unsigned char u8;

#define S2048_BlockSize 256
#define S2048_Padding 0x07
#define S2048_TotalRounds 9

#define S2048_E(m, k) ((((m-k) ^ ~(k+78)) - (((k+17) & 0xff) >> 1)) & 0xff)
#define S2048_D(c, k) (((c + (((k+17) & 0xff) >> 1) ^ ~(k+78)) + k) & 0xff)

#define S2048_PAD(size) (S2048_BlockSize - size % S2048_BlockSize)

typedef struct {
    u8 *data;
    u8 **key;
    size_t size;
} S2048_ctx;

int s2048_BlockPaddingAdd(S2048_ctx *ctx);
int s2048_BlockPaddingRemove(S2048_ctx *ctx);
u8 *s2048_keyPadding(u8 *token);
u8 **s2048_RoundKey(u8 *master_key);
int s2048_encrypt(S2048_ctx *ctx);
int s2048_decrypt(S2048_ctx *ctx);

#endif