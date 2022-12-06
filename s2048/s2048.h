#ifndef __S2048_H__ // S2048
#define __S2048_H__
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define S2048_BlockSize 256
#define S2048_Rounds 9
#define S2048_E(m, k) ((((m-k) ^ ~(k+78)) - (((k+17) & 0xff) >> 1)) & 0xff)
#define S2048_D(c, k) ((((c + (((k+17) & 0xff) >> 1)) ^ ~(k+78)) + k) & 0xff)

typedef struct {
    uint8_t *data;
    uint8_t key[S2048_BlockSize];
    uint8_t keySet[S2048_Rounds][S2048_BlockSize];
    size_t  size;
} s2048_ctx;

void s2048_roundKey(s2048_ctx *ctx);
void s2048_encrypt(s2048_ctx *ctx);
void s2048_decrypt(s2048_ctx *ctx);
#endif // S2048