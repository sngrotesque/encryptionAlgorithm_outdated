#include "snCrypto.h"

u8 **s2048_RoundKey(u8 *master_key)
{
    u8 **keySeq, *keyBuffer, t;
    short rounds, x;

    keySeq = (u8 **)malloc(8*S2048_TotalRounds);
    keyBuffer = (u8 *)malloc(S2048_BlockSize);

    if(!keySeq || !keyBuffer)
        return NULL;

    for(rounds = 0; rounds < S2048_TotalRounds; ++rounds) {
        keySeq[rounds] = (u8 *)malloc(S2048_BlockSize);
        memcpy(keySeq[rounds], master_key, S2048_BlockSize);
        
        for(x = 0; x < S2048_BlockSize; ++x) {
            switch(x) {
                case 0:
                    t = keySeq[rounds][x] ^ keySeq[rounds][255];
                    break;
                default:
                    t = keySeq[rounds][x] ^ keySeq[rounds][x-1];
                    break;
            }
            t = t ^ keySeq[rounds][174];
            t = ((x ^ t) - rounds) ^ S2048_IV[x];
            keyBuffer[x] = t ^ 0xcb;
        }
        
        master_key = keyBuffer;
    }

    return keySeq;
}

void s2048_encrypt(s2048_ctx *ctx)
{
    size_t rounds, x;
    u8 keyIndex;

    for(rounds = 0; rounds < S2048_TotalRounds; ++rounds) {
        for(x = keyIndex = 0; x < ctx->size; ++x, ++keyIndex) {
            ctx->data[x] = S2048_E(ctx->data[x], ctx->key[rounds][keyIndex]);
        }
    }
}

void s2048_decrypt(s2048_ctx *ctx)
{
    size_t rounds, x;
    u8 keyIndex;

    for(rounds = 0; rounds < S2048_TotalRounds; ++rounds) {
        for(x = keyIndex = 0; x < ctx->size; ++x, ++keyIndex) {
            ctx->data[x] = S2048_D(ctx->data[x],
                ctx->key[S2048_TotalRounds - rounds - 1][keyIndex]);
        }
    }
}
