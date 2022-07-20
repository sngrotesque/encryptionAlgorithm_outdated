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
#define NUMBER_OF_ROUNDS  7    // 加密解密轮数

#define True 1
#define False 0

// * 用在加密与解密函数中的初始宏定义函数 * //
#define BIN_R(x) (x ^ 0xFF)

// * 基本的变量 * //
typedef struct {
    u8 *data;   // 用于加密或解密的数据
    u8 *token;  // 用于加密解密的口令，你可以理解为密钥
    u64 len;    // 数据的字节长度
} S2048_ctx;

// * 初始混淆值（用于打乱密钥的值 (可自定义)） * //
const static u8 *sbox = {
    "\x7d\xf6\x32\x6b\xd8\xa6\x46\x7d\x73\xd0\x74\x17\xe9\x15\xcd\xc3"
    "\x27\xd5\x2b\x2c\x57\xec\xef\x02\xea\x18\x61\x99\xcb\xa0\xc0\x98"
    "\x81\x19\x8a\x46\xd0\x7e\xa8\xda\xa9\xf5\x67\xe6\xdc\x37\x71\xba"
    "\xa3\xf5\xff\x2c\x4c\x85\x4b\xdb\xc4\x97\x13\xcc\x48\x50\x21\x66"
    "\x5a\x70\x8f\x0e\xe3\x76\x70\x7c\xcc\xd5\x38\x14\x01\x61\xed\x8d"
    "\x53\xaa\xcf\x41\xb9\x8a\xd6\x0f\x1c\xa7\xa2\x30\xba\xe5\x95\x82"
    "\x11\x97\x6d\xdc\xa6\x6f\xcd\xf7\x9e\x5a\xb9\x0c\x60\xe2\x75\x8d"
    "\x5b\x60\xbe\xc9\xc2\x73\x18\x5d\x99\xe3\x02\x35\x36\x1c\x8a\xa2"
    "\x6d\xd2\xc8\x51\x69\x0b\x58\x77\x89\xc6\x42\x2a\x49\xf7\xac\x0d"
    "\x48\x4f\x6b\xe5\xea\xdb\xea\x92\xb7\x47\x61\xfa\xa1\x7f\x6b\xf5"
    "\x73\xd4\x68\x73\xb2\x23\x33\x78\x05\x59\x8a\x63\xe9\x29\x12\x04"
    "\x91\xa0\xab\xd9\x5f\xbd\xb6\xbf\x51\x16\xb4\x67\x5b\x4e\x55\x18"
    "\x48\xa1\x26\x4d\x25\x48\xfe\xad\x90\x4c\x74\xf0\x4d\xb1\x65\xcd"
    "\xe6\xfe\x44\xc1\xc9\xf9\x54\xef\x97\x2f\x0f\xdf\x99\x7b\x1a\xe9"
    "\x47\x05\x1f\x40\x8e\x1d\x1f\x75\xf3\x0f\x86\x50\x93\x65\xef\xd8"
    "\x2d\xde\x28\xb1\x8c\x4c\xf5\x5f\x98\x79\x1b\x4c\x0f\x4b\x66\x9b"
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
*    用于将密钥填充为256字节长度倍数的函数。
* 
* 1. 如果密钥长度小于256，此函数会用其自身数据进行填充直到256字节长度。
*    如一个密钥为"123-456-789-0"，那么它会被填充为如下样式：
*    123-456-789-0123-456-789-0123-456-789-0123-456-789-0 ...
*
* 2. 如果密钥长度大于256，此函数不会修改任何内容。
*/
static void S2048_Key_Padding(S2048_ctx *data)
{
    size_t key_n = strlen((char *)data->token);
    u8 *temp = (u8 *)malloc(BLOCK_SIZE + 1);
    memcpy(temp, data->token, key_n);
    temp[BLOCK_SIZE] = 0x00;
    for(u32 x = key_n, index = 0; x < 256; ++x, ++index) {
        if(index == key_n) index = 0;
        temp[x] = data->token[index];
    } data->token = temp;
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
    u8 **key_set = (u8 **)malloc(NUMBER_OF_ROUNDS * 8);
    u8 *key_temp = (u8 *)malloc(BLOCK_SIZE), temp;
    for(u32 rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        key_set[rounds] = (u8 *)malloc(BLOCK_SIZE);
        memcpy(key_set[rounds], master_key, BLOCK_SIZE);
        for(u32 x = 0; x < BLOCK_SIZE; ++x) {
            switch(x) {
                case 0: temp = key_set[rounds][x] ^ key_set[rounds][255]; break;
                default: temp = key_set[rounds][x] ^ key_set[rounds][x-1]; break;
            }
            temp = temp ^ key_set[rounds][174];
            temp = ((x ^ temp) - rounds) ^ sbox[x];
            key_temp[x] = BIN_R(temp);
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
static int S2048_ENCRYPT(S2048_ctx *data, u8 **total_key)
{
    u8 keyindex; u64 rounds, x;
    for(rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        for(x = keyindex = 0; x < data->len; ++x, ++keyindex) {
            data->data[x] = BIN_R(data->data[x] ^ total_key[rounds][keyindex]);
        }
    }
    return 0;
}

/*
* 解密函数，没必要过多介绍。
*
* 请按照加密函数上的注释执行。
*/
static int S2048_DECRYPT(S2048_ctx *data, u8 **total_key)
{
    u8 keyindex; u64 rounds, x;
    for(rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        for(x = keyindex = 0; x < data->len; ++x, ++keyindex) {
            data->data[x] = BIN_R(data->data[x] ^ total_key[NUMBER_OF_ROUNDS - rounds - 1][keyindex]);
        }
    }
    return 0;
}
#endif



/*
* 这是一些我自己在调试时会使用到的函数
* 如果你需要请保留，如果不需要请删除
*/
#ifndef __MISC__
#include <errno.h>
#include <math.h>

static int64_t get_file_size(FILE *stream)
{
    int64_t file_size = -1;
    int64_t cur_offset = ftello64(stream);
    fseeko64(stream, 0, SEEK_END);
    file_size = ftello64(stream);
    fseeko64(stream, cur_offset, SEEK_SET);
    return file_size;
}

static uint8_t *file_read(FILE *stream)
{
    int64_t size = get_file_size(stream);
    u8 *data = (u8 *)malloc(size + 1);
    data[size] = 0x00;
    fread(data, 1, size, stream);
    return data;
}

static void PRINT(S2048_ctx *data)
{
    for(int x = 0;x < data->len; ++x) {
        if (data->data[x] == 0x00) {
            printf("\x1b[91m%02x\x1b[0m", data->data[x]);
        } else {
            printf("%02x", data->data[x]);
        }
        if((x+1) % 32 == 0) {printf("\n");} else {printf(" ");}
    }
}

static void PRINT_KEY(u8 **total_key)
{
    for(int x = 0; x < NUMBER_OF_ROUNDS; ++x) {
        for(int  y = 0; y < 256; ++y) {
            printf("%02x", total_key[x][y]);
            if((y+1) % 32 == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

static int to_int(int c)
{
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if(c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= '0' && c <= '9')
        return c - '0';
    return -1;
}

static uint8_t *htob(char *text)
{
    const uint32_t len = strlen(text);
    if (len % 2 != 0) {return NULL;}
    uint64_t i, j, x, top, bot;
    uint8_t *ch = (uint8_t *)calloc(len / 2, 1);
    for (i = j = x = 0; i < len; i += 2, x++) {
        top = to_int(text[i]), bot = to_int(text[i+1]);
        if (top == -1 || bot == -1) {
            printf("Non Hex!\n"); return NULL;
        } ch[x] = (top << 4) + bot;
    } return ch;
}

#endif
