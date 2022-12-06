#ifndef __S1568_H__ // S1568
#define __S1568_H__
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define S1568_BlockSize 196
#define S1568_Rounds 7
#define S1568_Maximum 14

#define S1568_E(m, k) (m ^ k)
#define S1568_D(c, k) (c ^ k)

#define S1568_RK(k, n) ((k ^ ((((k << 8) * (n << 4)) - (k ^ n)) % 0xff)) ^ 0x3c)

#define S1568_RANGE(index) ((index + 1) % S1568_Maximum)

typedef uint8_t s1568_matrix[S1568_Maximum][S1568_Maximum];
typedef struct {
    uint8_t iv[S1568_BlockSize];
    uint8_t RoundKey[S1568_Rounds][S1568_BlockSize];
} s1568_ctx;

// void s1568_ctx_init(s1568_ctx *ctx);
// void s1568_encrypt(uint8_t *buff, uint8_t *key);

#endif // S1568