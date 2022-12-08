#ifndef __S2048_H__ // S2048
#define __S2048_H__
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define S2048_BlockSize 256
#define S2048_Rounds 9
#define S2048_Maximum 16

#define S2048_E(m, k) ((((m - k) ^ ~(k+78)) - (((k+17) & 0xff) >> 1)) & 0xff)
#define S2048_D(c, k) ((((c + (((k+17) & 0xff) >> 1)) ^ ~(k+78)) + k) & 0xff)
#define S2048_RANGE(index) (((index - 7) % S2048_BlockSize) & 0xff)
#define S2048_INIT_RK(buf, iv, i, r) \
    S2048_D(S2048_D(buf, iv), S2048_D(buf ^ (iv - i), (i + r + (iv ^ buf))))

typedef uint8_t s2048_state_t[S2048_Maximum][S2048_Maximum];

typedef struct {
    uint8_t IV[S2048_BlockSize];
    uint8_t RK[S2048_Rounds][S2048_BlockSize];
} s2048_ctx;

void s2048_init_ctx(s2048_ctx *ctx, uint8_t *key);
#endif // S2048