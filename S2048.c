#include "S2048.h"

int s2048_BlockPaddingAdd(S2048_ctx *ctx)
{
    size_t padoffset, padding_n, index;
    u8 *__buffer = NULL, *__temp = NULL;
    int createNewMemoryData;

    if(!ctx->data || !ctx->size)
        return EOF;

    padoffset = S2048_PAD(ctx->size);
    padding_n = ctx->size + padoffset;

    __temp = ctx->data;
    createNewMemoryData = 0;
    for(index = ctx->size; index < padding_n; ++index) {
        switch(__temp[index]) {
            case 0x00:
                break;
            default:
                createNewMemoryData = 1;
                break;
        }
        if(createNewMemoryData)
            break;
    }

    if(createNewMemoryData) {
        __buffer = (u8 *)malloc(padding_n + 1);
        memcpy(__buffer, ctx->data, ctx->size);
    } else {
        __buffer = ctx->data;
    }

    for(index = ctx->size; index < padding_n-1; ++index)
        __buffer[index] = S2048_Padding;

    if(padoffset == S2048_BlockSize) {
        __buffer[padding_n - 2] = 0xff;
        __buffer[padding_n - 1] = 0xff;
    } else {
        __buffer[padding_n - 1] = padoffset;
    }
    __buffer[padding_n] = 0x00;

    ctx->data = __buffer;
    ctx->size = padding_n;

    return 0;
}

int s2048_BlockPaddingRemove(S2048_ctx *ctx)
{
    if(!ctx->size || ctx->size % S2048_BlockSize) {
        return EOF;
    }
    u8 *__buffer = NULL;
    size_t realSize = 0;

    switch(ctx->data[ctx->size-1] & ctx->data[ctx->size-2]) {
        case 0xff:
            realSize = ctx->size - S2048_BlockSize;
            break;
        default:
            realSize = ctx->size - ctx->data[ctx->size-1];
            break;
    }
    __buffer = (u8 *)malloc(realSize+1);
    __buffer[realSize] = 0x00;

    if(!memcpy(__buffer, ctx->data, realSize)) {
        return EOF;
    }

    ctx->data = __buffer;
    ctx->size = realSize;

    return 0;
}

u8 *s2048_keyPadding(u8 *token)
{
    if(!token)
        return NULL;
    if(strlen((char *)token) >= S2048_BlockSize)
        return token;

    u8 *_ptr = token;
    int tokenSize, tokenIndex, index, createNewMemoryData;

    tokenSize = (unsigned short)strlen((char *)_ptr);
    createNewMemoryData = 0;
    for(index = tokenSize; index < S2048_BlockSize; ++index) {
        switch(_ptr[index]) {
            case 0x00:
                break;
            default:
                createNewMemoryData = 1;
                break;
        }
        if(createNewMemoryData)
            break;
    }

    if(createNewMemoryData) {
        _ptr = (u8 *)malloc(S2048_BlockSize);
        memcpy(_ptr, token, tokenSize);
    }

    for(index = tokenSize, tokenIndex = 0; index < S2048_BlockSize; ++index, ++tokenIndex) {
        if(tokenIndex == tokenSize) {
            tokenIndex = 0;
        }
        _ptr[index] = _ptr[tokenIndex];
    }

    return _ptr;
}

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

void s2048_encrypt(S2048_ctx *ctx)
{
    size_t rounds, x;
    u8 keyIndex;

    for(rounds = 0; rounds < S2048_TotalRounds; ++rounds) {
        for(x = keyIndex = 0; x < ctx->size; ++x, ++keyIndex) {
            ctx->data[x] = S2048_E(ctx->data[x], ctx->key[rounds][keyIndex]);
        }
    }
}

void s2048_decrypt(S2048_ctx *ctx)
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
