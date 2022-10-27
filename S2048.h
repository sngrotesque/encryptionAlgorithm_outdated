#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __S2048_H__
#define __S2048_H__ 1

typedef unsigned char u8;

#define S2048_BLOCK_SIZE   256
#define PADDING_DATA       199
#define NUMBER_OF_ROUNDS   9
#define ENCRYPT(data, key) (u8)(((data - key) ^ ~(key + 78)) - ((u8)(key + 17) >> 1))
#define DECRYPT(data, key) (u8)((data + ((u8)(key + 17) >> 1) ^ ~(key + 78)) + key)

typedef struct {
    u8 *data;
    u8 **key;
    size_t size;
} S2048_ctx;

int S2048_Block_Padding(S2048_ctx *ctx);
u8 *S2048_Key_Padding(u8 *token);
u8 **S2048_RoundKey(u8 *master_key);
int S2048_encrypt(S2048_ctx *ctx);
int S2048_decrypt(S2048_ctx *ctx);

#endif