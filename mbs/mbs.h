#ifndef __MBS_H__
#define __MBS_H__
#include "../../bits.h"

/*
* 此算法只作为用来测试想法的加密算法
* 请不要将它带入实际加密场景中
* 此算法极度不安全，请勿在正式场合使用
*                     —— SN-Grotesque
*/

// #define MBS128
#define MBS512
// #define MBS2048

#if defined(MBS128)
#define MBS_BLOCKLEN 16 // 分组字节长度
#define MBS_NK 4        // 矩阵长宽
#define MBS_NR 5        // 加解密轮数
#elif defined(MBS512)
#define MBS_BLOCKLEN 64 // 分组字节长度
#define MBS_NK 8        // 矩阵长宽
#define MBS_NR 7        // 加解密轮数
#elif defined(MBS2048)
#define MBS_BLOCKLEN 256 // 分组字节长度
#define MBS_NK 16        // 矩阵长宽
#define MBS_NR 11        // 加解密轮数
#endif

#define MBS_E(m, k, s)  ((((m ^ k)  - (0xff ^ s))  ^ s) & 0xff)
#define MBS_D(m, k, rs) ((((c ^ rs) + (0xff ^ rs)) ^ k) & 0xff)

typedef snByte mbsState_t[MBS_NK][MBS_NK];
typedef struct {
    snByte iv[MBS_BLOCKLEN];
    snByte rk[MBS_NR][MBS_BLOCKLEN];
} MBS_ctx;

#endif // #ifndef __MBS_H__