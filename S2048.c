#include "snCrypto.h"

void s2048_RoundKey(s2048_ctx *ctx)
{
    uint8_t t;
    uint16_t rounds;
    uint16_t x;
    for(rounds = 0; rounds < S2048_Rounds; ++rounds) {
        memcpy(ctx->keySet[rounds], ctx->key, S2048_BlockSize);
        for(x = 0; x < S2048_BlockSize; ++x) {
            t = ctx->keySet[rounds][x] ^ ctx->keySet[rounds][
                ((x-1) % S2048_BlockSize) & 0xff];
            t = t ^ ctx->keySet[rounds][174];
            t = ((x ^ t) - rounds) ^ S2048_IV[x];
            ctx->key[x] = t ^ 0xcb;
        }
    }
}

void s2048_encrypt(s2048_ctx *ctx)
{
    size_t rounds, x;
    uint8_t keyIndex;
    for(rounds = 0; rounds < S2048_Rounds; ++rounds) {
        for(x = keyIndex = 0; x < ctx->size; ++x, ++keyIndex) {
            ctx->data[x] = S2048_E(ctx->data[x], ctx->keySet[rounds][keyIndex]);
        }
    }
}

void s2048_decrypt(s2048_ctx *ctx)
{
    size_t rounds, x;
    uint8_t keyIndex;
    for(rounds = 0; rounds < S2048_Rounds; ++rounds) {
        for(x = keyIndex = 0; x < ctx->size; ++x, ++keyIndex) {
            ctx->data[x] = S2048_D(ctx->data[x],
                ctx->keySet[S2048_Rounds - rounds - 1][keyIndex]);
        }
    }
}
