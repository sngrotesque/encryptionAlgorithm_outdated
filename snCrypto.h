#ifndef __SN_CRYPTO__ // snCrypto
#define __SN_CRYPTO__
#include <stdlib.h>
#include "../swap.h"
#include "../random/random.h"

static void elementShift(uint8_t *data, size_t size)
{
    for(size_t i = 0; i < size / 2; ++i) {
        swap_uint8(&data[i], &data[size - i - 1]);
    }
}

static void sbox_init(uint8_t *sbox, uint16_t size)
{
    setRandomSeed();
    uint16_t r, x, left, right;
    for(x = 0; x < size; ++x)
        sbox[x] = x;
    for(r = 0; r < 16; ++r) {
        for(x = 0; x < size; ++x) {
            do {
                left  = randint(0, size - 1);
                right = randint(0, size - 1);
            } while(left == right);
            swap_uint8(&sbox[left], &sbox[right]);
        }
    }
}

static void rsbox_init(uint8_t *sbox, uint8_t *rsbox, uint16_t size)
{
    for(uint16_t x = 0; x < size; ++x)
        rsbox[sbox[x]] = x;
}

#endif // snCrypto