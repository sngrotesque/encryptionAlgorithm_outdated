#ifndef __S000_H__ // S000
/*
    RSA算法的核心
    Q = 171
    P = 193
    N = P * Q（Q与P必须有一个是质数）
    L = lcm(Q-1, P-1)（欧拉函数求最小公倍数）

    PK = X（1 < PK < L，且PK与L必须互质）
    SK = X（1 < SK < L，且PK*SK % L = 1）

    C = M^PK % N
    M = C^SK % N
*/

/*
s000公钥密码算法思路

公钥常数pkn为随意一个4位数字
由此常数求出公钥：
    pk = (pkn * (256 ** 24)) ^ (pkn ** 16)
加解密公式：
    c = m*pk mod N mod 256
    m = c*sk mod N mod 256
*/

// #define S000_F(x) (uint8_t)((x + (((x - 1) & (x << 4) & (x >> 2)) + (x * 2 - 17))) + 4)
// #define GetPK(pkn) (double)((pkn * pow(256, 24)) ^ pow(pkn, 16))
#endif // S000