#include "snCrypto.h"

static uint8_t S2048_IV[S2048_BlockSize] = {
    0xcb, 0x06, 0x4d, 0x01, 0x9f, 0xfd, 0x67, 0x56,
    0x36, 0x07, 0x32, 0x54, 0x0f, 0xfd, 0x80, 0x8a,
    0x5d, 0x85, 0xe7, 0xe0, 0xb5, 0x93, 0x06, 0x78,
    0xab, 0x90, 0x28, 0xc9, 0x2f, 0x90, 0x5f, 0x08,
    0xb3, 0x56, 0x4a, 0x13, 0x07, 0xda, 0x9d, 0x11,
    0xea, 0x7f, 0x2f, 0x9d, 0x7c, 0x4f, 0xbb, 0xa0,
    0x02, 0xd5, 0x10, 0x31, 0xcb, 0x81, 0x78, 0x49,
    0x61, 0x67, 0x9c, 0x92, 0x95, 0x68, 0xc6, 0xef,
    0xb4, 0xef, 0xdb, 0xb9, 0x77, 0xf1, 0xf7, 0x1c,
    0x46, 0x11, 0xaf, 0x1f, 0x28, 0xfb, 0x37, 0x03,
    0x6f, 0x70, 0xb2, 0x68, 0xbd, 0xe1, 0xbc, 0xb1,
    0xf5, 0xc8, 0xf1, 0x77, 0xd5, 0x96, 0xc1, 0xf7,
    0x32, 0x3d, 0x69, 0xcf, 0x5c, 0x40, 0x86, 0x7c,
    0x04, 0xb3, 0x75, 0x1b, 0xcf, 0x1d, 0xca, 0xd5,
    0x20, 0x5f, 0x51, 0xa8, 0x8a, 0x1c, 0x95, 0x81,
    0xa8, 0xa0, 0xcf, 0x47, 0xe9, 0x4e, 0x73, 0xa5,
    0x2a, 0x7c, 0x82, 0x5f, 0xa5, 0x2d, 0x69, 0x51,
    0x87, 0xd5, 0x54, 0x7e, 0x6e, 0xa2, 0x52, 0xed,
    0x10, 0x91, 0x6e, 0x2a, 0x60, 0xb8, 0x3d, 0x57,
    0x97, 0x2b, 0x6d, 0x6a, 0x25, 0x46, 0x9c, 0xa8,
    0x51, 0x0b, 0x92, 0x22, 0x6a, 0x7b, 0x1a, 0x5f,
    0x3c, 0x98, 0xf3, 0x02, 0x86, 0x47, 0x32, 0xf8,
    0xf4, 0xa5, 0x37, 0x8b, 0x5f, 0x2a, 0xc8, 0x74,
    0x1e, 0xb2, 0x96, 0x81, 0x57, 0xf5, 0xf8, 0x6c,
    0x73, 0x37, 0xec, 0x2a, 0x38, 0x23, 0x06, 0xb9,
    0xc1, 0x4f, 0x6c, 0x8a, 0x2a, 0xf0, 0x2c, 0xb7,
    0x60, 0x18, 0x97, 0x57, 0x08, 0x18, 0xad, 0x3c,
    0x86, 0x4b, 0xff, 0xc8, 0x43, 0x20, 0x24, 0xfc,
    0x19, 0x2c, 0x79, 0xec, 0x4e, 0x3d, 0x19, 0x01,
    0xd6, 0xd3, 0x00, 0xeb, 0x0e, 0xa6, 0x89, 0xc2,
    0xde, 0x2c, 0x93, 0x6b, 0x87, 0xbf, 0xb4, 0xc2,
    0x54, 0x02, 0x85, 0x30, 0x2f, 0x40, 0xe7, 0x78
};

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
