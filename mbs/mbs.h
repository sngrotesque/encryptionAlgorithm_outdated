#ifndef __MBS_H__ // MBS
#define __MBS_H__
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MBS_BLOCKSIZE 64
#define MBS_ROUNDS 11
#define MBS_E(m, k, iv) ((((m ^ k) - (0xff ^ k)) ^ iv) & 0xff)
#define MBS_D(c, k, iv) ((((c ^ iv) + (0xff ^ k)) ^ k) & 0xff)
#define MBS_SUB(k, k13, kb, kb17, m) \
    (((((k ^ kb) - (k13 - kb17)) & 0xff) - ((m << 2) ^ ((m << 4) / 3))) ^ 0xff)
#define MBS_KEY_RANGE(i) ((i + (MBS_BLOCKSIZE - 37)) % MBS_BLOCKSIZE)
#define MBS_BOX_RANGE(i) ((i + (MBS_BLOCKSIZE - 41)) % MBS_BLOCKSIZE)

typedef struct {
    uint8_t key[MBS_BLOCKSIZE];
    uint8_t keySet[MBS_ROUNDS][MBS_BLOCKSIZE];
} mbs_ctx;

void mbs_init_ctx(mbs_ctx *ctx);
void mbs_encrypt(mbs_ctx *ctx, uint8_t *buf, size_t size);
void mbs_decrypt(mbs_ctx *ctx, uint8_t *buf, size_t size);
#endif // MBS