#ifndef __QWY256_H__
#define __QWY256_H__
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define QWY256_BLOCKLEN 32
#define QWY256_ROUNDS 9
#define QWY256_Minimum 4
#define QWY256_Maximum 8

#define QWY256_E(m, k) ((((m ^ 0x912) - 0x204) ^ k) & 0xff)
#define QWY256_D(c, k) ((((c ^ k) + 0x204) ^ 0x912) & 0xff)
#define QWY256_RK(k, iv) ((((k ^ 0x1c) ^ (iv ^ 0xb3)) - 0xc9) & 0xff)
#define QWY256_RANGE(index) ((index + 1) % QWY256_Maximum)
#define GetSBOX_VALUE(n) (sbox[n])

typedef uint8_t qwy_state_t[QWY256_Minimum][QWY256_Maximum];
typedef struct {
    uint8_t IV[QWY256_BLOCKLEN];
    uint8_t RK[QWY256_ROUNDS][QWY256_BLOCKLEN];
} qwy256_ctx;

void ColumnMix(uint8_t r, qwy_state_t *buffer);
void qwy256_init_ctx(qwy256_ctx *ctx, uint8_t *key);
void qwy256_CBC_encrypt(qwy256_ctx *ctx, uint8_t *buf, size_t buf_size);

#endif