#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MBS256_BlockSize 32
#define MBS256_Round 3

#define _ENCRYPT(m, k) (uint16_t)((m << 4) ^ k)
#define _DECRYPT(c, k) (uint16_t)((c ^ k) >> 4)

typedef struct {
    uint8_t *message;
    size_t size;
    uint16_t *key;
    uint16_t *result;
} mbs256_ctx;

static const uint8_t sbox[4] = {
    0x9a, 0x2f, 0x18, 0xcd
};

static int mbs256_encrypt(mbs256_ctx *ctx)
{
    uint8_t __buff[5];
    for(int x = 0; x < ctx->size; ++x) {
        sprintf((char *)__buff, "%x", _ENCRYPT(ctx->message[x], ctx->key[x]));
        __buff[0] ^= sbox[0];
        __buff[1] ^= sbox[1];
        __buff[2] ^= sbox[2];
        __buff[3] ^= sbox[3];
        // 将__buff转整型，再与key做异或操作

        // for(int _ = 0; _ < 4; ++_) {
        //     printf("%02x ", __buff[_]);
        // } printf("\n");
    }

    return 0;
}








