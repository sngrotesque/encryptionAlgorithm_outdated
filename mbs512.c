#include "snCrypto.h"

void mbs512_subKey(mbs512_ctx *ctx)
{
    uint8_t round, index;
    for(round = 0; round < MBS512_Rounds; ++round) {
        memcpy(ctx->keySet[round], ctx->key, MBS512_BlockSize);
        for(index = 0; index < MBS512_BlockSize; ++index) {
            ctx->key[index] = MBS512_SUB(
                ctx->key[index],
                ctx->key[MBS512_KEY_RANGE(index)],
                MBS512_SUBKEY_BOX[index],
                MBS512_SUBKEY_BOX[MBS512_BOX_RANGE(index)],
                (((index + round) << 1) ^ 0xff));
        }
    }
}

void mbs512_rowReverse(mbs512_ctx *ctx)
{
    uint8_t i, t;
    for(i = 0; i < MBS512_BlockSize / 2; ++i) {
        t = ctx->data[i];
        ctx->data[i] = ctx->data[MBS512_BlockSize - i - 1];
        ctx->data[MBS512_BlockSize - i - 1] = t;
    }
}

void mbs512_encrypt(mbs512_ctx *ctx)
{
    uint8_t round, index;
    for(round = 0; round < MBS512_Rounds; ++round) {
        for(index = 0; index < MBS512_BlockSize; ++index) {
            ctx->data[index] = MBS512_E(
                ctx->data[index],
                ctx->keySet[round][index],
                MBS512_IV[round][index]
            );
        }
    }
}

void mbs512_decrypt(mbs512_ctx *ctx)
{
    uint8_t round, index;
    for(round = 0; round < MBS512_Rounds; ++round) {
        for(index = 0; index < MBS512_BlockSize; ++index) {
            ctx->data[index] = MBS512_D(
                ctx->data[index],
                ctx->keySet[MBS512_Rounds - round - 1][index],
                MBS512_IV[MBS512_Rounds - round - 1][index]
            );
        }
    }
}

