#ifndef __MBS512_H__ // MBS512
#define __MBS512_H__
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

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

void mbs512_roundKey(mbs512_ctx *ctx);
void mbs512_encrypt(mbs512_ctx *ctx);
void mbs512_decrypt(mbs512_ctx *ctx);
#endif // MBS512