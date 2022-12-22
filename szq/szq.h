/*
* Name of SZQ encryption algorithm: SN ZZH QWY.
*
* SZQ is a symmetric packet encryption algorithm. By default, 512 bit packets
* are used. There are three packets to choose from: 512, 968, 2048bit.
*
* At present, there are two encryption modes, CBC and CFB, which are used to
* better support various encryption modes.
*
* In CBC mode, the blocks can be encrypted separately as needed, rather than
* simultaneously, which provides a method of multi-threaded encryption.
*/
#ifndef __SZQ_H__ // SZQ
#define __SZQ_H__
#include <string.h>

#define SZQ_ROUNDS 9

#define SZQ_512
// #define SZQ_968
// #define SZQ_2048

#if defined(SZQ_512)
#define SZQ_BLOCKSIZE 64  // 512 bit
#define SZQ_MAXIMUM 8
#elif defined(SZQ_968)
#define SZQ_BLOCKSIZE 121 // 968 bit
#define SZQ_MAXIMUM 11
#elif defined(SZQ_2048)
#define SZQ_BLOCKSIZE 256 // 2048 bit
#define SZQ_MAXIMUM 16
#endif

#define SZQ_RANGE_ADD(index, n) ((index + n) % SZQ_BLOCKSIZE)
#define SZQ_RANGE_SUB(index, n) (((index - n) % SZQ_BLOCKSIZE) & 0xff)
#define SZQ_E(m, k) ((((m - k) ^ ~(k+78)) - (((k+17) & 0xff) >> 1)) & 0xff)
#define SZQ_D(c, k) ((((c + (((k+17) & 0xff) >> 1)) ^ ~(k+78)) + k) & 0xff)
#define SZQ_INIT_RK(buf, iv, i, r) \
    SZQ_D(SZQ_D(buf, iv), SZQ_D(buf ^ (iv - i), (i + r + (iv ^ buf))))

typedef unsigned char uint8_t;
typedef uint8_t szq_state_t[SZQ_MAXIMUM][SZQ_MAXIMUM];
typedef struct {
    uint8_t IV[SZQ_BLOCKSIZE];
    uint8_t RK[SZQ_ROUNDS][SZQ_BLOCKSIZE];
} szq_ctx;

void szq_init_ctx(szq_ctx *ctx, uint8_t *key);
void szq_cbc_encrypt(szq_ctx *ctx, uint8_t *buf, size_t size);
void szq_cbc_decrypt(szq_ctx *ctx, uint8_t *buf, size_t size);

#endif // SZQ
