/*
* RSA算法的核心
* Q = 171（实际的运用中，Q和P是非常大的数，至少是2的1024次方）
* P = 193
* N = P * Q（Q与P必须互质）
* L = lcm(Q-1, P-1)（欧拉函数求最小公倍数）
* PK = X（1 < PK < L，且PK与L必须互质）
* SK = X（1 < SK < L，且PK*SK % L = 1）
* C = M^PK % N
* M = C^SK % N

* 目前为了安全着想，请勿用此加密算法加密超过此长度的数据
*     SNKB_BLOCKLEN * 2（单位：字节 Bytes）
*
* 在开始你需要明白uint16_t类型是占用2字节也就是16bit
* 在计算机中数字类型的数据都是小端排序
* 比如7在内存表示为07 00，53391表示为 8f d0
*
* SNKB_BLOCKLEN
*     分组字节长度
* SNKB_N
*     加解密常量
* SNKB_P
*     是用于加密与解密的常量，与其他数的关系：65536 > SNKB_P > 1
*     主要使用情况为在加密时将经过S盒处理的数据与其异或，从而不会得到0
*     如果得到0，那么解密算法失效。
*
* 加密过程为：
*     加密函数中
*         buf总长度必须是2的倍数并且等于使用长度的2倍
*         size为buf实际使用的长度
*         比如使用了2字节，但是你必须有2*2字节的总空间
*         size为使用的长度也就是2
*     有原数据（使用8字节，留8字节）
*         ac ab 2d ad 27 4f 76 60 00 00 00 00 00 00 00 00
*     [1].经过倒转后
*         00 00 00 00 00 00 00 00 60 76 4f 27 ad 2d ab ac
*     [2].经过S盒置换
*         4b 4b 4b 4b 4b 4b 4b 4b 9d c2 26 f4 0d 35 da 25
*     [3].经过位切换
*         b4 b4 b4 b4 b4 b4 b4 b4 d9 2c 62 4f d0 53 ad 52
*     [4].经过S盒置换
*         e3 e3 e3 e3 e3 e3 e3 e3 3e b4 03 26 42 21 0d 51
*/
#ifndef __SNKB_H__
#define __SNKB_H__

#include <snBits.h>
#include <snError.h>
#include <snRand.h>

#define ENABLE_KEY_PROCESS 0

#if defined(ENABLE_KEY_PROCESS) && (ENABLE_KEY_PROCESS == 1)
#include <snKey.h>
#endif

#define SNKB_BLOCKLEN 128
#define SNKB_N 65537
#define SNKB_P 0xa703

#define SNKB_E(m, k) (((m * snPow(k, 3)) % SNKB_N) & 0xffff)
#define SNKB_D(c, k) (((c * snPow(k, 3)) % SNKB_N) & 0xffff)

#define SNKB_PRINT_N 16

typedef struct {
    sn_u16 publicKey[SNKB_BLOCKLEN];
    sn_u16 privateKey[SNKB_BLOCKLEN];
} snkb_ctx;

snVoid snkb_print(sn_u16 *buf, snSize size);
snVoid snkb_newkeys(snkb_ctx *ctx);
snVoid snkb_GenPublicKey(snkb_ctx *ctx);
snVoid snkb_GenPrivateKey(snkb_ctx *ctx);
sn_32 snkb_load_key(sn_u16 *keyBuf, const snChar *fn);
sn_32 snkb_save_key(sn_u16 *buf, const snChar *fn);
snVoid snkb_encrypt(snkb_ctx *ctx, snByte *buf, snSize bufSize);
snVoid snkb_decrypt(snkb_ctx *ctx, snByte *buf, snSize bufSize);
#endif // #ifndef __SNKB_H__
