#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MBS256_BlockSize 32

#define MBS256_Key_MIN 0x1000
#define MBS256_Key_MAX 0xff00

#define MBS256_Round 3

#define _ENCRYPT(m, k) (uint16_t)((m << 4) ^ k)
#define _DECRYPT(c, k) (uint16_t)((c ^ k) >> 4)

typedef struct {
    uint8_t *message;
    size_t size;
    uint16_t *key;
    uint16_t *result;
} mbs256;

static void setRandomSeed()
{
    clockid_t a = 0;
    struct timespec p;
    clock_gettime(a, &p);
    srand((unsigned)p.tv_nsec);
}

static uint32_t randint(uint32_t min, uint32_t max)
{
    return rand() % (max - min + 1) + min;
}

static uint16_t *mbs256_gen_key()
{
    setRandomSeed();
    uint16_t *_key = (uint16_t *)malloc(sizeof(uint16_t) * MBS256_BlockSize);
    for(uint8_t keyIndex = 0; keyIndex < MBS256_BlockSize; ++keyIndex) {
        _key[keyIndex] = randint(MBS256_Key_MIN, MBS256_Key_MAX);
    }
    return _key;
}

static int mbs256_encrypt(mbs256 *ctx)
{
    for(size_t x = 0; x < ctx->size; ++x) {
        ctx->result;
    }

    return 0;
}








