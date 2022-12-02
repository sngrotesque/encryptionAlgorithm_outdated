#ifndef __SN_CRYPTO__ // snCrypto
#define __SN_CRYPTO__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../swap.h"

static void elementShift(uint8_t *data, size_t size)
{
    for(size_t i = 0; i < size / 2; ++i) {
        swap_uint8(&data[i], &data[size - i - 1]);
    }
}

#ifndef __MBS512_H__ // MBS512
#define __MBS512_H__
#define MBS512_BlockSize 64
#define MBS512_Rounds 11
#define MBS512_E(m, k, iv) ((((m ^ k) - (0xff ^ k)) ^ iv) & 0xff)
#define MBS512_D(c, k, iv) ((((c ^ iv) + (0xff ^ k)) ^ k) & 0xff)
#define MBS512_SUB(k, k13, kb, kb17, m) \
    (((((k ^ kb) - (k13 - kb17)) & 0xff) - ((m << 2) ^ ((m << 4) / 3))) ^ 0xff)
#define MBS512_KEY_RANGE(i) ((i + (MBS512_BlockSize - 37)) % MBS512_BlockSize)
#define MBS512_BOX_RANGE(i) ((i + (MBS512_BlockSize - 41)) % MBS512_BlockSize)

typedef struct {
    uint8_t *data;
    uint8_t key[MBS512_BlockSize];
    uint8_t keySet[MBS512_Rounds][MBS512_BlockSize];
    size_t  size;
} mbs512_ctx;

void mbs512_subKey(mbs512_ctx *ctx);
void mbs512_encrypt(mbs512_ctx *ctx);
void mbs512_decrypt(mbs512_ctx *ctx);
#endif // MBS512

#ifndef __S2048_H__ // S2048
#define __S2048_H__
#define S2048_BlockSize 256
#define S2048_Rounds 9
#define S2048_E(m, k) ((((m-k) ^ ~(k+78)) - (((k+17) & 0xff) >> 1)) & 0xff)
#define S2048_D(c, k) ((((c + (((k+17) & 0xff) >> 1)) ^ ~(k+78)) + k) & 0xff)

typedef struct {
    uint8_t *data;
    uint8_t key[S2048_BlockSize];
    uint8_t keySet[S2048_Rounds][S2048_BlockSize];
    size_t  size;
} s2048_ctx;

void s2048_RoundKey(s2048_ctx *ctx);
void s2048_encrypt(s2048_ctx *ctx);
void s2048_decrypt(s2048_ctx *ctx);
#endif // S2048

#ifndef __S000_H__ // S000
/*
    RSA算法的核心
    Q = 171
    P = 193
    N = P * Q（Q与P必须有一个是质数）
    L = lcm(Q-1, P-1)（欧拉函数求最小公倍数）

    PK = X（1 < PK < L，且PK与L必须互质）
    SK = X（1 < SK < L，且PK*SK % L = 1）

    C = M^PK % N
    M = C^SK % N
*/

/*
s000公钥密码算法思路

公钥常数pkn为随意一个4位数字
由此常数求出公钥：
    pk = (pkn * (256 ** 24)) ^ (pkn ** 16)
加解密公式：
    c = m*pk mod N mod 256
    m = c*sk mod N mod 256
*/

// #define S000_F(x) (uint8_t)((x + (((x - 1) & (x << 4) & (x >> 2)) + (x * 2 - 17))) + 4)
// #define GetPK(pkn) (double)((pkn * pow(256, 24)) ^ pow(pkn, 16))
#endif // S000

#endif // snCrypto