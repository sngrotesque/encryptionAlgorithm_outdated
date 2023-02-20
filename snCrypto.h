#ifndef __SN_CRYPTO__ // snCrypto
#define __SN_CRYPTO__
#include <stdint.h>
#include "../bits.h"
#include "../random/random.h"

#define SBOX_BLOCKLEN 256

static void sbox_init(uint8_t *sbox)
{
    setRandomSeed();
    uint16_t r;
    uint16_t x;
    uint16_t left;
    uint16_t right;
    uint8_t swap;

    for(x = 0; x < SBOX_BLOCKLEN; ++x)
        sbox[x] = x;

    for(r = 0; r < 16; ++r) {
        for(x = 0; x < SBOX_BLOCKLEN; ++x) {
            do {
                left  = randint(0, SBOX_BLOCKLEN - 1);
                right = randint(0, SBOX_BLOCKLEN - 1);
            } while(left == right);
            swap = sbox[left];
            sbox[left] = sbox[right];
            sbox[right] = swap;
        }
    }
}

static void rsbox_init(uint8_t *sbox, uint8_t *rsbox)
{
    for(uint16_t x = 0; x < SBOX_BLOCKLEN; ++x)
        rsbox[sbox[x]] = x;
}

#endif // snCrypto