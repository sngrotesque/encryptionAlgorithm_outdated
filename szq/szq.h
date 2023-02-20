/*
* SZQ加密算法名称由来: SN ZZH QWY
* Name of SZQ encryption algorithm: SN ZZH QWY.
*
* SZQ是一个对称分组加密算法，分组大小为512位
* SZQ is a symmetric packet encryption algorithm with a packet size of 512 bits.
*
* 目前和未来有两种加密模式，CBC和CFB，用于更好地支持各种加密场景。
* At present and in the future, there are two encryption modes, CBC and CFB, to
* better support various encryption scenarios.
*
* 在CBC模式下，块也可以根据需要单独加密，而非同时加密，这提供了一种多线程加密方式。
* In CBC mode, blocks can also be encrypted separately as needed instead of
* simultaneously, which provides a multi-threaded encryption method.
*
* **安全性报告****(1.解决)****(0.存在)**************************
* 1. 在只修改密钥或初始向量的末尾几位时，将不会出现雪崩效应  (1)
* 2. 不修改密钥或初始向量时，修改明文只会改变小于4字节的数据 (1)
* 3. 列移位函数执行之后，无法使用逆列移位函数完整还原内容    (1)
* 4. 如果输入的数据完全一样，不同区块输出的内容也完全一样    (0)
*    不过目前版本，在16384这个固定长度的区块下开始，也将会按此长
*    度变为一样的区块
* **************************************************************
*
* 添加256bit加密分组，将目前的SZQ_NK设置为基本单位，即SZQ_NB，加密
* 轮数为9，将默认的512位加密轮数改为11
*/
#ifndef __SZQ_H__ // SZQ
#define __SZQ_H__

#include "../../bits.h"

#define SZQ_BLOCKLEN 64  // 512 bit
#define SZQ_NK 8
#define SZQ_NR 11

#define SZQ_BIN_SHIFT 6

#define SZQ_ADD_RK(index, n) ((index + n) % SZQ_BLOCKLEN)
#define SZQ_SUB_RK(index, n) (((index - n) % SZQ_BLOCKLEN) & 0xff)

#define SZQ_E(m, k) ((((m - k) ^ ~(k+78)) - (((k+17) & 0xff) >> 1)) & 0xff)
#define SZQ_D(c, k) ((((c + (((k+17) & 0xff) >> 1)) ^ ~(k+78)) + k) & 0xff)

typedef snByte szqState_t[SZQ_NK][SZQ_NK];
typedef struct {
    snByte iv[SZQ_BLOCKLEN];
    snByte rk[SZQ_NR][SZQ_BLOCKLEN];
} SZQ_ctx;

snVoid SZQ_init_ctx(SZQ_ctx* ctx, const snByte* keyBuf);
snVoid SZQ_CBC_Encrypt(SZQ_ctx* ctx, snByte* buf, snSize_t size);
snVoid SZQ_CBC_Decrypt(SZQ_ctx *ctx, snByte *buf, snSize_t size);
snVoid SZQ_CTR_Xcrypt(SZQ_ctx *ctx, snByte *buf, snSize_t size);

#endif // SZQ
