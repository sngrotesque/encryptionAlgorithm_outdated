#ifndef __SNC_H__
#define __SNC_H__

#include "../../bits.h"

// #define SNC_256
#define SNC_512

#define SNC_NB 8
#define SNC_NR 11

#if defined(SNC_256)
#define SNC_BLOCKLEN 32
#define SNC_NK 4
#define SNC_BIT_SHIFT 5
#elif defined(SNC_512)
#define SNC_BLOCKLEN 64
#define SNC_NK 8
#define SNC_BIT_SHIFT 6
#endif

#define SNC_ADD_RK(index, n) ((index + n) % SNC_BLOCKLEN)
#define SNC_SUB_RK(index, n) (((index - n) % SNC_BLOCKLEN) & 0xff)

typedef snByte sncState_t[SNC_NB][SNC_NK];
typedef struct {
    snByte iv[SNC_BLOCKLEN];
    snByte rk[SNC_NR][SNC_BLOCKLEN];
} SNC_ctx;







#endif // #ifndef __SNC_H__
