/*
--- RSA算法的核心 ---
    Q = 171
    P = 193
    N = P * Q（Q与P必须有一个是质数）
    L = lcm(Q-1, P-1)（欧拉函数求最小公倍数）

    PK = X（1 < PK < L，且PK与L必须互质）
    SK = X（1 < SK < L，且PK*SK % L = 1）

    C = M^PK % N
    M = C^SK % N
*/
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define f(x) (uint8_t)((x + (((x - 1) & (x << 4) & (x >> 2)) + (x * 2 - 17))) + 4)

#define S000_PublicKey  17
#define S000_PrivateKey 11

#define _encrypt(m, k) (((m ^ k) - 193) & 0xff)
#define _decrypt(c, k) (((c - k) ^ 204) & 0xff)




