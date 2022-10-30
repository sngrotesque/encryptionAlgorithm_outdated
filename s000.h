#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define f(x) (uint8_t)((x + (((x - 1) & (x << 4) & (x >> 2)) + (x * 2 - 17))) + 4)

#define S000_PublicKey  0x51
#define S000_PrivateKey 0xbc

#define _encrypt(m, k) (((m ^ k) - 193) & 0xff)
#define _decrypt(c, k) (((c - k) ^ 204) & 0xff)




