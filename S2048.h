/*
* W: 在开始之前，请确保你具有阅读此源代码的能力。
* 
* P.S: 此文档存在的目的是让使用此算法的人更好的理解它的工作原理。
* 
* 1. 每个区块的长度为2048位，就如目前市面上绝大多数的256位的加密算法。
* 2. 默认情况下的填充值为一个0-255区间的十六进制值。
* 3. 默认情况下的加密次数为7次。
* 
* 接下来请阅读每个函数的详细注释。
*/

// #include <time.h>
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

#define ENCRYPT(data, key) (u8)((data - key ^ ~(key + 13)) - (key + 78 >> 1))
#define DECRYPT(data, key) (u8)((data + (key + 78 >> 1) ^ ~(key + 13)) + key)

// * 基本的变量 * //
typedef struct {
    u8 *data;   // 待处理数据
    u8 **key;   // 密钥
    u64 len;    // 单位bytes
} S2048_ctx;
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
* 2. 即使去掉sbox，使用此函数同样可以让你的密钥保持安全性，
*    即使你使用的是诸如 12345678 这样的密码构成的密钥。
*
* 请注意：
*    ☆ 这一切的前提是你执行了密钥数据填充函数 ☆
*/
static u8 **S2048_Round_key_obfuscation(u8 *master_key)
{
    u8 sbox[BLOCK_SIZE] = {
        0x05, 0xa0, 0x7a, 0x9f, 0xad, 0x90, 0x8a, 0xce,
        0x49, 0x01, 0x93, 0xf4, 0xd8, 0x90, 0xd9, 0x13,
        0x35, 0x68, 0x9e, 0x49, 0xb2, 0x37, 0x84, 0x79,
        0xe6, 0xa7, 0xe6, 0x54, 0x01, 0x0a, 0x94, 0x5a,
        0x15, 0x89, 0x68, 0x04, 0xbb, 0xca, 0xfa, 0xc3,
        0x9b, 0x7e, 0x6a, 0xd3, 0xce, 0x65, 0xe4, 0x75,
        0x12, 0x8b, 0x51, 0x8b, 0x3e, 0x36, 0xac, 0x86,
        0xc0, 0x42, 0xb9, 0x70, 0xa7, 0x7b, 0x25, 0x40,
        0xaf, 0x38, 0xa1, 0x4c, 0xfc, 0x22, 0x03, 0x99,
        0x40, 0x64, 0x3e, 0xeb, 0x03, 0xd3, 0xfb, 0x34,
        0x1f, 0xcf, 0x95, 0x9c, 0xda, 0x09, 0x42, 0x4e,
        0x99, 0xb8, 0x09, 0x45, 0x3e, 0xd7, 0x9e, 0x07,
        0x31, 0x4b, 0x7a, 0x23, 0xe0, 0xc8, 0xe0, 0x7e,
        0x46, 0xe5, 0xa7, 0x73, 0x8e, 0xac, 0x4e, 0x2b,
        0x11, 0x49, 0x05, 0x71, 0x7d, 0x40, 0xf3, 0x75,
        0x1f, 0x16, 0xb8, 0x81, 0x02, 0xb6, 0x0a, 0xaf,
        0x9f, 0xd4, 0xbf, 0xd5, 0xf2, 0x0a, 0x5b, 0x37,
        0x13, 0x25, 0x5a, 0xce, 0x8b, 0x81, 0xb0, 0x43,
        0xb4, 0xf7, 0x77, 0x41, 0x7f, 0x1f, 0xb2, 0xb1,
        0x39, 0x2b, 0xf4, 0x18, 0x79, 0x61, 0x6e, 0x0d,
        0x61, 0x69, 0x15, 0xe1, 0xfb, 0x10, 0xa9, 0x4c,
        0x25, 0x9f, 0x1e, 0xf0, 0x03, 0xf8, 0x20, 0xfb,
        0xce, 0x21, 0xd1, 0xbc, 0x2a, 0xf1, 0x5c, 0x27,
        0x76, 0xcd, 0x25, 0xe0, 0x31, 0x10, 0xe9, 0x54,
        0x64, 0x69, 0x9f, 0xd3, 0xbe, 0x23, 0xe0, 0x6a,
        0x5a, 0x2c, 0xae, 0xc6, 0x7f, 0x95, 0xde, 0x50,
        0xfe, 0xf5, 0xc6, 0xc8, 0xa6, 0xcf, 0x27, 0xae,
        0x44, 0x36, 0x90, 0xab, 0x27, 0x2d, 0x04, 0x47,
        0xc2, 0xde, 0x44, 0xb8, 0xb7, 0x72, 0x42, 0x83,
        0x6b, 0x53, 0x5e, 0x0c, 0xcf, 0x58, 0xf8, 0xfd,
        0xb1, 0xc9, 0x11, 0x44, 0xf5, 0x3f, 0xd4, 0x1c,
        0xd9, 0xe4, 0x3e, 0x52, 0xc1, 0x7a, 0x0e, 0x17
    };

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
static int S2048_ENCRYPT(S2048_ctx *data)
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
static int S2048_DECRYPT(S2048_ctx *data)
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

