#include "S2048.h"

static u8 S2048_SBOX[S2048_BlockSize] = {
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
            t = ((x ^ t) - rounds) ^ S2048_SBOX[x];
            keyBuffer[x] = t ^ 0xcb;
        }
        
        master_key = keyBuffer;
    }

    return keySeq;
}

int s2048_encrypt(S2048_ctx *ctx)
{
    u8 keyindex;
    size_t rounds;
    size_t x;

    for(rounds = 0; rounds < S2048_TotalRounds; ++rounds) {
        for(x = keyindex = 0; x < ctx->size; ++x, ++keyindex) {
            ctx->data[x] = S2048_E(ctx->data[x], ctx->key[rounds][keyindex]);
        }
    }

    return 0;
}

int s2048_decrypt(S2048_ctx *ctx)
{
    u8 keyindex;
    size_t rounds;
    size_t x;

    for(rounds = 0; rounds < S2048_TotalRounds; ++rounds) {
        for(x = keyindex = 0; x < ctx->size; ++x, ++keyindex) {
            ctx->data[x] = S2048_D(ctx->data[x],
                ctx->key[S2048_TotalRounds - rounds - 1][keyindex]);
        }
    }

    return 0;
}
