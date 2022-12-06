#include "../snCrypto.h"
#include "s1568.h"

void s1568_ctx_init(s1568_ctx *ctx, uint8_t *key)
{
    uint8_t round, index, keyBuffer[S1568_BlockSize];
    memcpy(keyBuffer, key, S1568_BlockSize);
    for(round = 0; round < S1568_Rounds; ++round) {
        memcpy(ctx->RoundKey[round], keyBuffer, S1568_BlockSize);
        for(index = 0; index < S1568_BlockSize; ++index) {
            keyBuffer[index] = S1568_RK(keyBuffer[index], ctx->iv[index]);
            keyBuffer[index] = keyBuffer[index] ^ (round + index);
            swap_uint8(&keyBuffer[index], &ctx->iv[index]);
            keyBuffer[index] = keyBuffer[index] - (((round + index) << 1) / 3);
            swap_uint8(&keyBuffer[index], &ctx->iv[index]);
            keyBuffer[index] = keyBuffer[index] ^ (round + index);
        }
    }
}

void ColumnMix(uint8_t r, s1568_matrix *buffer)
{
    uint8_t x, y, first, last;
    for(x = 0; x < r + 4 ; ++x) {
        for(y = 0; y < S1568_Maximum - 1; ++y) {
            first = y, last = S1568_RANGE(y);
            swap_uint8(&(*buffer)[r][first], &(*buffer)[r][last]);
        }
    }
}

void s1568_encrypt(s1568_ctx *ctx, uint8_t *buffer)
{
    uint8_t r, x, y;
    s1568_matrix *buffState = (s1568_matrix *)buffer;
    s1568_matrix *roundKey;
    
    for(r = 0; r < S1568_Rounds; ++r) {
        roundKey = (s1568_matrix *)ctx->RoundKey[r];
        for(x = 0; x < S1568_Maximum; ++x) {
            for(y = 0; y < S1568_Maximum; ++y) {
                (*buffState)[x][y] = (*buffState)[x][y] ^ (*roundKey)[x][y];
            }
        }
        ColumnMix(r, buffState);
        ColumnMix(r, roundKey);
    }
}
