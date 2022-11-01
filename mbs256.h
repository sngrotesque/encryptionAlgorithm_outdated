#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef __MBS256_H__
#define __MBS256_H__ 1

#define MBS256_BlockSize 32
#define MBS256_Round 3

#define _ENCRYPT(m, k) (uint16_t)((m << 4) ^ k)
#define _DECRYPT(c, k) (uint16_t)((c ^ k) >> 4)

static uint8_t sbox[4] = {
    96, 175, 229, 21
};

/*in_size
* in 是一个原文指针
* in_size为这个指向内容的长度
* key为密钥
* out为指向输出内容的指针，需要提前申请（in_file * 4）的内存长度。
*/
static int mbs256_encrypt(uint8_t *in, size_t in_size, uint16_t *key, uint8_t *out)
{
    if(!in || !in_size || !key || !out)
        return EOF;

    uint8_t __buff[5], keyIndex;
    size_t in_index, out_index;
    for(in_index = out_index = keyIndex = 0; in_index < in_size; ++in_index, ++keyIndex, out_index += 4) {
        if(keyIndex == MBS256_BlockSize)
            keyIndex = 0;
        sprintf((char *)__buff, "%04x", _ENCRYPT(in[in_index], key[keyIndex]));
        for(uint8_t tempIndex = 0; tempIndex < 4; ++tempIndex) {
            out[out_index + tempIndex] = __buff[tempIndex] ^ sbox[tempIndex];
        }
    }

    return 0;
}


#endif





