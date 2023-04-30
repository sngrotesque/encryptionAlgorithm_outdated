#ifndef __SN_CRYPTO__ // snCrypto
#define __SN_CRYPTO__
#include <snBits.h>
#include <snRand.h>

static void snCrypto_sbox_init(snByte *sbox)
{
    snSetRandomTimerSeed(1934830);
    static sn_u32 r, x, left, right;
    static snByte swap;

    for(x = 0; x < 256; ++x)
        sbox[x] = x;

    for(r = 0; r < 16; ++r) {
        for(x = 0; x < 256; ++x) {
            do {
                left  = randint(911, 0, 255);
                right = randint(911, 0, 255);
            } while(left == right);
            swap = sbox[left];
            sbox[left] = sbox[right];
            sbox[right] = swap;
        }
    }
}

static void snCrypto_rsbox_init(snByte *sbox, snByte *rsbox)
{
    for(sn_u32 x = 0; x < 256; ++x)
        rsbox[sbox[x]] = x;
}

#endif // snCrypto