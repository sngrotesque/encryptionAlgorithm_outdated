#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef __MBS256_H__
#define __MBS256_H__ 1

#define MBS256_BlockSize 32
#define MBS256_Round 3

typedef struct {
    uint8_t *data;
    uint8_t *PrivateKey;
    uint8_t _sub[32];
} mbs256_ctx;

static uint8_t MBS256_IV[MBS256_BlockSize] = {
    0x6a, 0xfa, 0xa9, 0x13, 0x97, 0xf6, 0x11, 0x45,
    0xa7, 0x4b, 0xca, 0xdc, 0x7b, 0x41, 0xda, 0x9f,
    0xb4, 0xc2, 0x76, 0x1b, 0x22, 0x54, 0x3d, 0xcf,
    0xfc, 0xb3, 0x4d, 0x12, 0xb7, 0x6e, 0x7e, 0x9e
};

static void mbs256_sub(mbs256_ctx *ctx)
{
    uint8_t index;
    for(index = 0; index < MBS256_BlockSize; ++index)
        ctx->_sub[index] = ctx->data[index];
    for(index = 0; index < MBS256_BlockSize; ++index)
        ctx->data[index] = ctx->_sub[(index+7) % 32];
}












#endif





