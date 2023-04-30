/*
* Copyright belongs to SN-Grotesque，版权所属于SN-Grotesque
* 允许使用，但请遵守Apache2.0协议。
*
* SNC是由SN-Grotesque开发的一个对称加密算法，它使用SP网络对数据进行分组加密与解密。
* 解密就是加密过程的逆运算，只不过加密是从第一轮子密钥直到最后一轮子密钥，解密与之相反。
*
* 此算法的区块长度为32字节（256位）。
* 密钥采用三种长度：256，512，768。
*     基础长度（256位）的密钥将进行9轮加密或解密。
*     扩展长度（512位）的密钥将进行11轮加密或解密。
*     扩展长度（768位）的密钥将进行13轮加密或解密。
*
* 目前提供了以下加密模式：
*     ECB, CBC
*
* 请注意，ECB模式在大多数专业人士眼中不被认为是足够安全的。
*/
#ifndef __SNC_H__
#define __SNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// #define SNC_256 // 32字节（32 bytes）
// #define SNC_512 // 64字节（64 bytes）
#define SNC_768 // 96字节（96 bytes）

#define SNC_BLOCKLEN 32 // 区块长度（Block size）

#define SNC_NB 8 // 纵向长度（Longitudinal length）
#define SNC_NK 4 // 横向长度（Transverse length）

#if defined(SNC_768)
#define SNC_NR 13 // 加解密轮数（Number of encryption and decryption rounds）
#define SNC_KEYLEN 96 // 密钥长度（Key length）
#elif defined(SNC_512)
#define SNC_NR 11
#define SNC_KEYLEN 64
#else
#define SNC_NR 9
#define SNC_KEYLEN 32
#endif

typedef uint8_t sncState_t[SNC_NB][SNC_NK]; // 声明区块类型
typedef struct {
    uint8_t iv[SNC_BLOCKLEN];
    uint8_t rk[SNC_NR][SNC_KEYLEN];
} SNC_ctx; // 声明SNC算法的数据结构

void SNC_init_ctx(SNC_ctx *ctx, const uint8_t *keyBuf);
void SNC_ECB_Encrypt(SNC_ctx *ctx, uint8_t *buf, size_t size);
void SNC_ECB_Decrypt(SNC_ctx *ctx, uint8_t *buf, size_t size);
void SNC_CBC_Encrypt(SNC_ctx *ctx, uint8_t *buf, size_t size);
void SNC_CBC_Decrypt(SNC_ctx *ctx, uint8_t *buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif // #ifndef __SNC_H__
