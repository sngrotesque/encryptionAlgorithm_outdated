/*
* W: 在开始之前，请确保你具有阅读此源代码的能力。
* 
* P.S: 此文档存在的目的是让使用此算法的人更好的理解它的工作原理。
* 
* 1. 每个区块的长度为2048位，就如目前市面上绝大多数的256位的加密算法。
* 2. 默认情况下的填充值为一个0-255区间的十六进制值。
* 
* 接下来请阅读每个函数的详细注释。
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef __SN_OBJECT__
#define __SN_OBJECT__ 1

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// * 初始的宏定义 * //
#define BLOCK_SIZE        256  // 256 Bytes
#define PADDING_DATA      199  // 填充值 0xc7
#define NUMBER_OF_ROUNDS  9    // 加密解密轮数
#define ENCRYPT(data, key) (u8)(((data - key) ^ ~(key + 13)) - ((key + 78) >> 1))
#define DECRYPT(data, key) (u8)((data + ((key + 78) >> 1) ^ ~(key + 13)) + key)

// * 基本的变量 * //
typedef struct {
    u8 *data;   // 待处理数据
    u8 **key;   // 密钥
    u64 len;    // 单位bytes
} S2048_ctx;

// * 初始sbox，请自定义 * //
static const uint8_t sbox[BLOCK_SIZE] = {
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
#endif

#ifndef __SN_FUNCTION__
#define __SN_FUNCTION__ 1

// * 在不使用填充函数的时候 * //
// * 请确保密钥与待处理数据的字节长度一致 * //
// * 或密钥的字节长度大于等于待处理的数据 * //

/*
*    用于将数据填充为256字节长度倍数的函数。
* 
* 1. 如果数据的字节长度并非为256的倍数，此函数将填充其至256的倍数。
*    如一段数据长度为121，那么此函数会将其填充至256字节。
*    其中，填充值为宏定义中的'PADDING_DATA'
*    而最后一字节的数据则为填充长度，此示例中为0x87。
* 
* 2. 如果数据字节长度原本就为256的倍数，此函数将填充256字节的数据。
*    但与第一种情况不同的是，最后两字节的数据会同时为0xff。
*
* 也就是说：
*    第一种填充方式的最后一字节为校验位
*    第二种填充方式的最后两字节为校验位
*/
static void S2048_Padding(S2048_ctx *data)
{
    u64 padoffset = BLOCK_SIZE - data->len % BLOCK_SIZE;
    u64 padding_n = data->len + padoffset;
    u8 *temp = (u8 *)malloc(padding_n + 1);
    memcpy(temp, data->data, data->len);
    temp[padding_n] = 0x00;
    for(u64 x = data->len; x < padding_n - 1; ++x) {
        temp[x] = PADDING_DATA;
    } data->data = temp;

    if(padoffset == 256) {
        data->data[padding_n - 2] = data->data[padding_n - 1] = 0xff;
    } else {
        data->data[padding_n - 1] = padoffset;
    }
    data->len = padding_n;
}

/*
*    用于生成一段随机产生的256字节数据，可用作密钥或sbox
*/
static u8 *S2048_gen_sbox_keys()
{
    clockid_t a;
    struct timespec p = {0, 0};
    clock_gettime(a, &p);
    srand((unsigned)p.tv_nsec);
    u8 *data = (u8 *)malloc(BLOCK_SIZE);
    if (data == NULL) return NULL;
    for(short x = 0; x < BLOCK_SIZE; ++x) {
        data[x] = rand() % (0xff - 0x00 + 1) + 0x00;
    }
    return data;
}

/*
*    用于将密钥填充为256字节长度倍数的函数。
* 
* 1. 如果密钥长度小于256，此函数会用其自身数据进行填充直到256字节长度。
*    如一个密钥为"123-456-789-0"，那么它会被填充为如下样式：
*    123-456-789-0123-456-789-0123-456-789-0123-456-789-0 ...
*
* 2. 如果密钥长度大于等于256，此函数不会修改任何内容。
*    但是长度都大于等于256了，你还执行这个函数干嘛？
*/
static u8 *S2048_Key_Padding(u8 *token, size_t token_n)
{
    u8 *tk_t = (u8 *)malloc(BLOCK_SIZE);
    memcpy(tk_t, token, token_n);
    for(u32 x = token_n, index = 0; x < 256; ++x, ++index) {
        if(index == token_n) index = 0;
        tk_t[x] = token[index];
    } return tk_t;
}

/*
*    轮密钥更新函数
*
* 1. 使用sbox中的数据对密钥的数据进行打乱和混淆，
*    根据算法设置的加密解密轮数来决定密钥的更新周期。
*
*    你可以将sbox添加到代码中，也可以将sbox作为另一种密钥
*    保存在文件目录中。
*
* 2. 即使去掉sbox，使用此函数同样可以让你的密钥保持安全性，
*    即使你使用的是诸如 12345678 这样的密码构成的密钥。
*
* 请注意：
*    ☆ 这一切的前提是你执行了密钥数据填充函数 ☆
*/
static u8 **S2048_Round_obfuscation(u8 *master_key)
{
    u8 **key_set = (u8 **)malloc(NUMBER_OF_ROUNDS * 8);
    u8 *key_temp = (u8 *)malloc(BLOCK_SIZE), temp = 0;
    for(u32 rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        key_set[rounds] = (u8 *)malloc(BLOCK_SIZE);
        memcpy(key_set[rounds], master_key, BLOCK_SIZE);
        for(u32 x = 0; x < BLOCK_SIZE; ++x) {
            switch(x) {
                case 0:
                    temp = key_set[rounds][x] ^ key_set[rounds][255];
                    break;
                default:
                    temp = key_set[rounds][x] ^ key_set[rounds][x-1];
                    break;
            }
            temp = temp ^ key_set[rounds][174];
            temp = ((x ^ temp) - rounds) ^ sbox[x];
            key_temp[x] = temp ^ 0xcb;
        }
        master_key = key_temp;
    }
    return key_set;
}

/*
* 加密函数，没必要过多介绍。
*
* 在加密之前请使用S2048_Round_key_obfuscation函数生成新密钥，
* 并在之后使用新密钥与此加密函数进行运算。
*/
static int S2048_encrypt(S2048_ctx *data)
{
    u8 keyindex; u64 rounds, x;
    for(rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        for(x = keyindex = 0; x < data->len; ++x, ++keyindex) {
            data->data[x] = ENCRYPT(data->data[x], data->key[rounds][keyindex]);
        }
    }
    return 0;
}

/*
* 解密函数，没必要过多介绍。
*
* 请按照加密函数上的注释执行。
*/
static int S2048_decrypt(S2048_ctx *data)
{
    u8 keyindex; u64 rounds, x;
    for(rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        for(x = keyindex = 0; x < data->len; ++x, ++keyindex) {
            data->data[x] = DECRYPT(data->data[x], data->key[NUMBER_OF_ROUNDS - rounds - 1][keyindex]);
        }
    }
    return 0;
}
#endif

