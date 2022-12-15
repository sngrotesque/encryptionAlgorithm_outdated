#ifndef __S2048_H__ // S2048
#define __S2048_H__
#include <string.h>

#define S2048_BLOCKSIZE 256
#define S2048_ROUNDS    9
#define S2048_MAXIMUM   16

#define S2048_RANGE_ADD(index, n) ((index + n) % S2048_BLOCKSIZE)
#define S2048_RANGE_SUB(index, n) (((index - n) % S2048_BLOCKSIZE) & 0xff)
#define S2048_E(m, k) ((((m - k) ^ ~(k+78)) - (((k+17) & 0xff) >> 1)) & 0xff)
#define S2048_D(c, k) ((((c + (((k+17) & 0xff) >> 1)) ^ ~(k+78)) + k) & 0xff)
#define S2048_INIT_RK(buf, iv, i, r) \
    S2048_D(S2048_D(buf, iv), S2048_D(buf ^ (iv - i), (i + r + (iv ^ buf))))

typedef unsigned char uint8_t;
typedef uint8_t s2048_state_t[S2048_MAXIMUM][S2048_MAXIMUM];
typedef struct {
    uint8_t IV[S2048_BLOCKSIZE];
    uint8_t RK[S2048_ROUNDS][S2048_BLOCKSIZE];
} s2048_ctx;

void s2048_init_ctx(s2048_ctx *ctx, uint8_t *key);
void s2048_cbc_encrypt(s2048_ctx *ctx, uint8_t *buf, size_t size);
void s2048_cbc_decrypt(s2048_ctx *ctx, uint8_t *buf, size_t size);

#endif // S2048
