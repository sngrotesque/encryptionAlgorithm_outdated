#include "S2048.h"

int S2048_Block_Padding(S2048_ctx *ctx)
{
    size_t padoffset = S2048_BLOCK_SIZE - ctx->size % S2048_BLOCK_SIZE;
    size_t padding_n = ctx->size + padoffset;
    u8 *temp = (u8 *)malloc(padding_n + 1);
    if(!temp || !ctx->data || !ctx->size) return EOF;

    memcpy(temp, ctx->data, ctx->size);
    temp[padding_n] = 0x00;
    for(size_t x = ctx->size; x < padding_n - 1; ++x)
        temp[x] = PADDING_DATA;
    ctx->data = temp;

    if(padoffset == 256) {
        ctx->data[padding_n - 2] = ctx->data[padding_n - 1] = 0xff;
    } else {
        ctx->data[padding_n - 1] = padoffset;
    }
    ctx->size = padding_n;
    return 0;
}

u8 *S2048_Key_Padding(u8 *token)
{
    if(!token) return NULL;
    u8 *tk_t = (u8 *)malloc(S2048_BLOCK_SIZE);
    size_t token_n = strlen((char *)token);
    memcpy(tk_t, token, token_n);
    for(int x = token_n, index = 0; x < 256; ++x, ++index) {
        if(index == token_n) index = 0;
        tk_t[x] = token[index];
    } return tk_t;
}

u8 **S2048_RoundKey(u8 *master_key)
{
    u8 **key_set = (u8 **)malloc(sizeof(u8 **) * NUMBER_OF_ROUNDS);
    u8 *key_temp = (u8 *)malloc(S2048_BLOCK_SIZE), temp = 0;
    if(!key_set || !key_temp) return NULL;

    for(int rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        key_set[rounds] = (u8 *)malloc(S2048_BLOCK_SIZE);
        memcpy(key_set[rounds], master_key, S2048_BLOCK_SIZE);
        for(int x = 0; x < S2048_BLOCK_SIZE; ++x) {
            switch(x) {
                case 0:  temp = key_set[rounds][x] ^ key_set[rounds][255]; break;
                default: temp = key_set[rounds][x] ^ key_set[rounds][x-1]; break;
            }
            temp = temp ^ key_set[rounds][174];
            temp = ((x ^ temp) - rounds) ^ sbox[x];
            key_temp[x] = temp ^ 0xcb;
        }
        master_key = key_temp;
    }
    return key_set;
}

int S2048_encrypt(S2048_ctx *ctx)
{
    u8 keyindex; size_t rounds, x;
    for(rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        for(x = keyindex = 0; x < ctx->size; ++x, ++keyindex) {
            ctx->data[x] = ENCRYPT(ctx->data[x], ctx->key[rounds][keyindex]);
        }
    }
    return 0;
}

int S2048_decrypt(S2048_ctx *ctx)
{
    u8 keyindex; size_t rounds, x;
    for(rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        for(x = keyindex = 0; x < ctx->size; ++x, ++keyindex) {
            ctx->data[x] = DECRYPT(ctx->data[x],
                ctx->key[NUMBER_OF_ROUNDS - rounds - 1][keyindex]);
        }
    }
    return 0;
}