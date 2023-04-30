#include "szq.h"

/*
* 有关sbox与rsbox
*     sbox与rsbox均可自定义。
* 但由于通信双方需处于同一算法数据的情况下，此为默认sbox与rsbox
* -------------------------------------------- SZQ_sbox --------------------------------------------
* 0xf3, 0x54, 0xca, 0x34, 0x4f, 0xef, 0x55, 0x31, 0x0e, 0x50, 0xe4, 0x61, 0x17, 0xb2, 0x14, 0x94,
* 0xd2, 0x3d, 0x3f, 0x80, 0x84, 0x27, 0xd9, 0x1d, 0x4c, 0x12, 0x5c, 0x1e, 0x0f, 0x7e, 0x4a, 0x58,
* 0xd0, 0xe5, 0x3b, 0x03, 0x90, 0x62, 0x0c, 0xbf, 0xdc, 0xb1, 0xbe, 0x57, 0x21, 0xf2, 0xfc, 0x82,
* 0xbb, 0xf1, 0x6b, 0xda, 0xe7, 0xc4, 0x47, 0x39, 0xff, 0xa0, 0xd5, 0x66, 0xec, 0xb4, 0x48, 0x44,
* 0xc7, 0x08, 0x69, 0x13, 0x85, 0x25, 0x43, 0xe0, 0x7a, 0x4d, 0x67, 0xee, 0x1b, 0x41, 0x36, 0x30,
* 0xfe, 0xfb, 0xa2, 0x92, 0xdd, 0xfd, 0x95, 0x3e, 0x0d, 0x71, 0x9f, 0x53, 0x93, 0xc3, 0x42, 0x4b,
* 0x6a, 0xc8, 0xa5, 0x4e, 0xb3, 0x89, 0x29, 0x2b, 0x0a, 0x18, 0xc6, 0x00, 0x64, 0x26, 0x3a, 0x2d,
* 0x6c, 0xc5, 0x32, 0xd4, 0xd1, 0x88, 0x20, 0x7b, 0x87, 0x5e, 0xa6, 0x5f, 0x86, 0x5a, 0xb7, 0xde,
* 0xb5, 0x0b, 0xaa, 0xab, 0xa3, 0xa4, 0xce, 0x77, 0x9e, 0x8f, 0x1f, 0x19, 0x02, 0xf9, 0xed, 0xcd,
* 0x09, 0x91, 0xeb, 0x40, 0x46, 0x22, 0x1a, 0xe8, 0xc2, 0x70, 0x78, 0x28, 0x63, 0x79, 0x97, 0x83,
* 0x75, 0x2f, 0xf4, 0x15, 0xf0, 0x2e, 0x38, 0x7d, 0x5d, 0xd8, 0x23, 0x2a, 0x07, 0xbd, 0x8a, 0xf5,
* 0x9b, 0x11, 0x6d, 0x99, 0x6f, 0x98, 0xdb, 0xf6, 0x7c, 0xaf, 0x35, 0xe9, 0x60, 0x10, 0xe1, 0x7f,
* 0xa1, 0x9a, 0x24, 0x6e, 0x72, 0xb0, 0x9d, 0xe2, 0xae, 0xc0, 0x45, 0x49, 0x06, 0x52, 0x51, 0xd6,
* 0xac, 0xbc, 0xa8, 0xcc, 0xf7, 0x96, 0xa7, 0x05, 0x9c, 0xdf, 0xb8, 0xcf, 0xfa, 0x2c, 0x65, 0x76,
* 0x74, 0xe3, 0x59, 0xd3, 0xd7, 0x3c, 0x73, 0xf8, 0x8c, 0x5b, 0xb9, 0xad, 0xba, 0x01, 0x37, 0xb6,
* 0x56, 0xc9, 0xa9, 0x81, 0x1c, 0x68, 0xea, 0xc1, 0x8d, 0x8e, 0xcb, 0x04, 0x16, 0x8b, 0x33, 0xe6
*
* ------------------------------------------- SZQ_rsbox --------------------------------------------
* 0x6b, 0xed, 0x8c, 0x23, 0xfb, 0xd7, 0xcc, 0xac, 0x41, 0x90, 0x68, 0x81, 0x26, 0x58, 0x08, 0x1c,
* 0xbd, 0xb1, 0x19, 0x43, 0x0e, 0xa3, 0xfc, 0x0c, 0x69, 0x8b, 0x96, 0x4c, 0xf4, 0x17, 0x1b, 0x8a,
* 0x76, 0x2c, 0x95, 0xaa, 0xc2, 0x45, 0x6d, 0x15, 0x9b, 0x66, 0xab, 0x67, 0xdd, 0x6f, 0xa5, 0xa1,
* 0x4f, 0x07, 0x72, 0xfe, 0x03, 0xba, 0x4e, 0xee, 0xa6, 0x37, 0x6e, 0x22, 0xe5, 0x11, 0x57, 0x12,
* 0x93, 0x4d, 0x5e, 0x46, 0x3f, 0xca, 0x94, 0x36, 0x3e, 0xcb, 0x1e, 0x5f, 0x18, 0x49, 0x63, 0x04,
* 0x09, 0xce, 0xcd, 0x5b, 0x01, 0x06, 0xf0, 0x2b, 0x1f, 0xe2, 0x7d, 0xe9, 0x1a, 0xa8, 0x79, 0x7b,
* 0xbc, 0x0b, 0x25, 0x9c, 0x6c, 0xde, 0x3b, 0x4a, 0xf5, 0x42, 0x60, 0x32, 0x70, 0xb2, 0xc3, 0xb4,
* 0x99, 0x59, 0xc4, 0xe6, 0xe0, 0xa0, 0xdf, 0x87, 0x9a, 0x9d, 0x48, 0x77, 0xb8, 0xa7, 0x1d, 0xbf,
* 0x13, 0xf3, 0x2f, 0x9f, 0x14, 0x44, 0x7c, 0x78, 0x75, 0x65, 0xae, 0xfd, 0xe8, 0xf8, 0xf9, 0x89,
* 0x24, 0x91, 0x53, 0x5c, 0x0f, 0x56, 0xd5, 0x9e, 0xb5, 0xb3, 0xc1, 0xb0, 0xd8, 0xc6, 0x88, 0x5a,
* 0x39, 0xc0, 0x52, 0x84, 0x85, 0x62, 0x7a, 0xd6, 0xd2, 0xf2, 0x82, 0x83, 0xd0, 0xeb, 0xc8, 0xb9,
* 0xc5, 0x29, 0x0d, 0x64, 0x3d, 0x80, 0xef, 0x7e, 0xda, 0xea, 0xec, 0x30, 0xd1, 0xad, 0x2a, 0x27,
* 0xc9, 0xf7, 0x98, 0x5d, 0x35, 0x71, 0x6a, 0x40, 0x61, 0xf1, 0x02, 0xfa, 0xd3, 0x8f, 0x86, 0xdb,
* 0x20, 0x74, 0x10, 0xe3, 0x73, 0x3a, 0xcf, 0xe4, 0xa9, 0x16, 0x33, 0xb6, 0x28, 0x54, 0x7f, 0xd9,
* 0x47, 0xbe, 0xc7, 0xe1, 0x0a, 0x21, 0xff, 0x34, 0x97, 0xbb, 0xf6, 0x92, 0x3c, 0x8e, 0x4b, 0x05,
* 0xa4, 0x31, 0x2d, 0x00, 0xa2, 0xaf, 0xb7, 0xd4, 0xe7, 0x8d, 0xdc, 0x51, 0x2e, 0x55, 0x50, 0x38
*/

// 此sbox与rsbox由"snCrypto_sbox_init"与"snCrypto_rsbox_init"两个函数生成
#ifndef __SZQ_SBOX__ // szq SZQ_sbox
static const uint8_t SZQ_sbox[256] = {
    // 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
    0xf3, 0x54, 0xca, 0x34, 0x4f, 0xef, 0x55, 0x31, 0x0e, 0x50, 0xe4, 0x61, 0x17, 0xb2, 0x14, 0x94,
    0xd2, 0x3d, 0x3f, 0x80, 0x84, 0x27, 0xd9, 0x1d, 0x4c, 0x12, 0x5c, 0x1e, 0x0f, 0x7e, 0x4a, 0x58,
    0xd0, 0xe5, 0x3b, 0x03, 0x90, 0x62, 0x0c, 0xbf, 0xdc, 0xb1, 0xbe, 0x57, 0x21, 0xf2, 0xfc, 0x82,
    0xbb, 0xf1, 0x6b, 0xda, 0xe7, 0xc4, 0x47, 0x39, 0xff, 0xa0, 0xd5, 0x66, 0xec, 0xb4, 0x48, 0x44,
    0xc7, 0x08, 0x69, 0x13, 0x85, 0x25, 0x43, 0xe0, 0x7a, 0x4d, 0x67, 0xee, 0x1b, 0x41, 0x36, 0x30,
    0xfe, 0xfb, 0xa2, 0x92, 0xdd, 0xfd, 0x95, 0x3e, 0x0d, 0x71, 0x9f, 0x53, 0x93, 0xc3, 0x42, 0x4b,
    0x6a, 0xc8, 0xa5, 0x4e, 0xb3, 0x89, 0x29, 0x2b, 0x0a, 0x18, 0xc6, 0x00, 0x64, 0x26, 0x3a, 0x2d,
    0x6c, 0xc5, 0x32, 0xd4, 0xd1, 0x88, 0x20, 0x7b, 0x87, 0x5e, 0xa6, 0x5f, 0x86, 0x5a, 0xb7, 0xde,
    0xb5, 0x0b, 0xaa, 0xab, 0xa3, 0xa4, 0xce, 0x77, 0x9e, 0x8f, 0x1f, 0x19, 0x02, 0xf9, 0xed, 0xcd,
    0x09, 0x91, 0xeb, 0x40, 0x46, 0x22, 0x1a, 0xe8, 0xc2, 0x70, 0x78, 0x28, 0x63, 0x79, 0x97, 0x83,
    0x75, 0x2f, 0xf4, 0x15, 0xf0, 0x2e, 0x38, 0x7d, 0x5d, 0xd8, 0x23, 0x2a, 0x07, 0xbd, 0x8a, 0xf5,
    0x9b, 0x11, 0x6d, 0x99, 0x6f, 0x98, 0xdb, 0xf6, 0x7c, 0xaf, 0x35, 0xe9, 0x60, 0x10, 0xe1, 0x7f,
    0xa1, 0x9a, 0x24, 0x6e, 0x72, 0xb0, 0x9d, 0xe2, 0xae, 0xc0, 0x45, 0x49, 0x06, 0x52, 0x51, 0xd6,
    0xac, 0xbc, 0xa8, 0xcc, 0xf7, 0x96, 0xa7, 0x05, 0x9c, 0xdf, 0xb8, 0xcf, 0xfa, 0x2c, 0x65, 0x76,
    0x74, 0xe3, 0x59, 0xd3, 0xd7, 0x3c, 0x73, 0xf8, 0x8c, 0x5b, 0xb9, 0xad, 0xba, 0x01, 0x37, 0xb6,
    0x56, 0xc9, 0xa9, 0x81, 0x1c, 0x68, 0xea, 0xc1, 0x8d, 0x8e, 0xcb, 0x04, 0x16, 0x8b, 0x33, 0xe6
};
#endif // szq SZQ_sbox

#ifndef __SZQ_RSBOX__ // szq SZQ_rsbox
static const uint8_t SZQ_rsbox[256] = {
    // 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
    0x6b, 0xed, 0x8c, 0x23, 0xfb, 0xd7, 0xcc, 0xac, 0x41, 0x90, 0x68, 0x81, 0x26, 0x58, 0x08, 0x1c,
    0xbd, 0xb1, 0x19, 0x43, 0x0e, 0xa3, 0xfc, 0x0c, 0x69, 0x8b, 0x96, 0x4c, 0xf4, 0x17, 0x1b, 0x8a,
    0x76, 0x2c, 0x95, 0xaa, 0xc2, 0x45, 0x6d, 0x15, 0x9b, 0x66, 0xab, 0x67, 0xdd, 0x6f, 0xa5, 0xa1,
    0x4f, 0x07, 0x72, 0xfe, 0x03, 0xba, 0x4e, 0xee, 0xa6, 0x37, 0x6e, 0x22, 0xe5, 0x11, 0x57, 0x12,
    0x93, 0x4d, 0x5e, 0x46, 0x3f, 0xca, 0x94, 0x36, 0x3e, 0xcb, 0x1e, 0x5f, 0x18, 0x49, 0x63, 0x04,
    0x09, 0xce, 0xcd, 0x5b, 0x01, 0x06, 0xf0, 0x2b, 0x1f, 0xe2, 0x7d, 0xe9, 0x1a, 0xa8, 0x79, 0x7b,
    0xbc, 0x0b, 0x25, 0x9c, 0x6c, 0xde, 0x3b, 0x4a, 0xf5, 0x42, 0x60, 0x32, 0x70, 0xb2, 0xc3, 0xb4,
    0x99, 0x59, 0xc4, 0xe6, 0xe0, 0xa0, 0xdf, 0x87, 0x9a, 0x9d, 0x48, 0x77, 0xb8, 0xa7, 0x1d, 0xbf,
    0x13, 0xf3, 0x2f, 0x9f, 0x14, 0x44, 0x7c, 0x78, 0x75, 0x65, 0xae, 0xfd, 0xe8, 0xf8, 0xf9, 0x89,
    0x24, 0x91, 0x53, 0x5c, 0x0f, 0x56, 0xd5, 0x9e, 0xb5, 0xb3, 0xc1, 0xb0, 0xd8, 0xc6, 0x88, 0x5a,
    0x39, 0xc0, 0x52, 0x84, 0x85, 0x62, 0x7a, 0xd6, 0xd2, 0xf2, 0x82, 0x83, 0xd0, 0xeb, 0xc8, 0xb9,
    0xc5, 0x29, 0x0d, 0x64, 0x3d, 0x80, 0xef, 0x7e, 0xda, 0xea, 0xec, 0x30, 0xd1, 0xad, 0x2a, 0x27,
    0xc9, 0xf7, 0x98, 0x5d, 0x35, 0x71, 0x6a, 0x40, 0x61, 0xf1, 0x02, 0xfa, 0xd3, 0x8f, 0x86, 0xdb,
    0x20, 0x74, 0x10, 0xe3, 0x73, 0x3a, 0xcf, 0xe4, 0xa9, 0x16, 0x33, 0xb6, 0x28, 0x54, 0x7f, 0xd9,
    0x47, 0xbe, 0xc7, 0xe1, 0x0a, 0x21, 0xff, 0x34, 0x97, 0xbb, 0xf6, 0x92, 0x3c, 0x8e, 0x4b, 0x05,
    0xa4, 0x31, 0x2d, 0x00, 0xa2, 0xaf, 0xb7, 0xd4, 0xe7, 0x8d, 0xdc, 0x51, 0x2e, 0x55, 0x50, 0x38
};
#endif // szq SZQ_rsbox

#define SZQ_GET_SBOX(n)  (SZQ_sbox[(n)])
#define SZQ_GET_RSBOX(n) (SZQ_rsbox[(n)])

/****************************************************
* Private Function                                  *
****************************************************/
// 列移位
static void SZQ_ShiftColumn(szqState_t *state)
{
    static uint8_t buf;

    // 第一列
    buf = (*state)[0][0];
    (*state)[0][0] = (*state)[1][0]; (*state)[1][0] = (*state)[2][0];
    (*state)[2][0] = (*state)[3][0]; (*state)[3][0] = (*state)[4][0];
    (*state)[4][0] = (*state)[5][0]; (*state)[5][0] = (*state)[6][0];
    (*state)[6][0] = (*state)[7][0]; (*state)[7][0] = buf;

    // 第二列
    buf = (*state)[0][1];
    (*state)[0][1] = (*state)[2][1]; (*state)[2][1] = (*state)[4][1];
    (*state)[4][1] = (*state)[6][1]; (*state)[6][1] = buf;

    buf = (*state)[1][1];
    (*state)[1][1] = (*state)[3][1]; (*state)[3][1] = (*state)[5][1];
    (*state)[5][1] = (*state)[7][1]; (*state)[7][1] = buf;

    // 第三列
    buf = (*state)[0][2];
    (*state)[0][2] = (*state)[3][2]; (*state)[3][2] = (*state)[6][2];
    (*state)[6][2] = (*state)[1][2]; (*state)[1][2] = (*state)[4][2];
    (*state)[4][2] = (*state)[7][2]; (*state)[7][2] = (*state)[2][2];
    (*state)[2][2] = (*state)[5][2]; (*state)[5][2] = buf;

    // 第四列
    buf = (*state)[0][3]; (*state)[0][3] = (*state)[4][3]; (*state)[4][3] = buf;
    buf = (*state)[1][3]; (*state)[1][3] = (*state)[5][3]; (*state)[5][3] = buf;
    buf = (*state)[2][3]; (*state)[2][3] = (*state)[6][3]; (*state)[6][3] = buf;
    buf = (*state)[3][3]; (*state)[3][3] = (*state)[7][3]; (*state)[7][3] = buf;

    // 第五列
    buf = (*state)[0][4];
    (*state)[0][4] = (*state)[5][4]; (*state)[5][4] = (*state)[2][4];
    (*state)[2][4] = (*state)[7][4]; (*state)[7][4] = (*state)[4][4];
    (*state)[4][4] = (*state)[1][4]; (*state)[1][4] = (*state)[6][4];
    (*state)[6][4] = (*state)[3][4]; (*state)[3][4] = buf;

    // 第六列
    buf = (*state)[0][5]; (*state)[0][5] = (*state)[6][5]; (*state)[6][5] = buf;
    buf = (*state)[1][5]; (*state)[1][5] = (*state)[7][5]; (*state)[7][5] = buf;
    buf = (*state)[2][5]; (*state)[2][5] = (*state)[6][5]; (*state)[6][5] = buf;
    buf = (*state)[3][5]; (*state)[3][5] = (*state)[7][5]; (*state)[7][5] = buf;
    buf = (*state)[4][5]; (*state)[4][5] = (*state)[6][5]; (*state)[6][5] = buf;
    buf = (*state)[5][5]; (*state)[5][5] = (*state)[7][5]; (*state)[7][5] = buf;

    // 第七列
    buf = (*state)[0][6]; (*state)[0][6] = (*state)[7][6]; (*state)[7][6] = buf;
    buf = (*state)[1][6]; (*state)[1][6] = (*state)[7][6]; (*state)[7][6] = buf;
    buf = (*state)[2][6]; (*state)[2][6] = (*state)[7][6]; (*state)[7][6] = buf;
    buf = (*state)[3][6]; (*state)[3][6] = (*state)[7][6]; (*state)[7][6] = buf;
    buf = (*state)[4][6]; (*state)[4][6] = (*state)[7][6]; (*state)[7][6] = buf;
    buf = (*state)[5][6]; (*state)[5][6] = (*state)[7][6]; (*state)[7][6] = buf;
    buf = (*state)[6][6]; (*state)[6][6] = (*state)[7][6]; (*state)[7][6] = buf;
}

// 逆列移位
static void SZQ_InvShiftColumn(szqState_t *state)
{
    static uint8_t buf;
    
    // 第七列
    buf = (*state)[7][6]; (*state)[7][6] = (*state)[6][6]; (*state)[6][6] = buf;
    buf = (*state)[7][6]; (*state)[7][6] = (*state)[5][6]; (*state)[5][6] = buf;
    buf = (*state)[7][6]; (*state)[7][6] = (*state)[4][6]; (*state)[4][6] = buf;
    buf = (*state)[7][6]; (*state)[7][6] = (*state)[3][6]; (*state)[3][6] = buf;
    buf = (*state)[7][6]; (*state)[7][6] = (*state)[2][6]; (*state)[2][6] = buf;
    buf = (*state)[7][6]; (*state)[7][6] = (*state)[1][6]; (*state)[1][6] = buf;
    buf = (*state)[7][6]; (*state)[7][6] = (*state)[0][6]; (*state)[0][6] = buf;
    
    // 第六列
    buf = (*state)[7][5]; (*state)[7][5] = (*state)[5][5]; (*state)[5][5] = buf;
    buf = (*state)[6][5]; (*state)[6][5] = (*state)[4][5]; (*state)[4][5] = buf;
    buf = (*state)[7][5]; (*state)[7][5] = (*state)[3][5]; (*state)[3][5] = buf;
    buf = (*state)[6][5]; (*state)[6][5] = (*state)[2][5]; (*state)[2][5] = buf;
    buf = (*state)[7][5]; (*state)[7][5] = (*state)[1][5]; (*state)[1][5] = buf;
    buf = (*state)[6][5]; (*state)[6][5] = (*state)[0][5]; (*state)[0][5] = buf;
    
    // 第五列
    buf = (*state)[3][4];
    (*state)[3][4] = (*state)[6][4]; (*state)[6][4] = (*state)[1][4];
    (*state)[1][4] = (*state)[4][4]; (*state)[4][4] = (*state)[7][4];
    (*state)[7][4] = (*state)[2][4]; (*state)[2][4] = (*state)[5][4];
    (*state)[5][4] = (*state)[0][4]; (*state)[0][4] = buf;
    
    // 第四列
    buf = (*state)[7][3]; (*state)[7][3] = (*state)[3][3]; (*state)[3][3] = buf;
    buf = (*state)[6][3]; (*state)[6][3] = (*state)[2][3]; (*state)[2][3] = buf;
    buf = (*state)[5][3]; (*state)[5][3] = (*state)[1][3]; (*state)[1][3] = buf;
    buf = (*state)[4][3]; (*state)[4][3] = (*state)[0][3]; (*state)[0][3] = buf;

    // 第三列
    buf = (*state)[5][2];
    (*state)[5][2] = (*state)[2][2]; (*state)[2][2] = (*state)[7][2];
    (*state)[7][2] = (*state)[4][2]; (*state)[4][2] = (*state)[1][2];
    (*state)[1][2] = (*state)[6][2]; (*state)[6][2] = (*state)[3][2];
    (*state)[3][2] = (*state)[0][2]; (*state)[0][2] = buf;

    // 第二列
    buf = (*state)[7][1];
    (*state)[7][1] = (*state)[5][1]; (*state)[5][1] = (*state)[3][1];
    (*state)[3][1] = (*state)[1][1]; (*state)[1][1] = buf;
    buf = (*state)[6][1];
    (*state)[6][1] = (*state)[4][1]; (*state)[4][1] = (*state)[2][1];
    (*state)[2][1] = (*state)[0][1];(*state)[0][1] = buf;
    
    // 第一列
    buf = (*state)[7][0];
    (*state)[7][0] = (*state)[6][0]; (*state)[6][0] = (*state)[5][0];
    (*state)[5][0] = (*state)[4][0]; (*state)[4][0] = (*state)[3][0];
    (*state)[3][0] = (*state)[2][0]; (*state)[2][0] = (*state)[1][0];
    (*state)[1][0] = (*state)[0][0]; (*state)[0][0] = buf;
}

// 行混合
static void SZQ_RowsMix(szqState_t *state)
{
    register uint32_t i;

    for(i = 0; i < SZQ_NK; ++i) {
        (*state)[i][0] = ((*state)[i][0] ^ (*state)[i][3]) + i - 0x1f;
        (*state)[i][1] = ((*state)[i][1] ^ (*state)[i][4]) + i - 0x9c;
        (*state)[i][2] = ((*state)[i][2] ^ (*state)[i][5]) + i - 0xa9;
        (*state)[i][3] = ((*state)[i][3] ^ (*state)[i][6]) + i - 0x01;
        (*state)[i][4] = ((*state)[i][4] ^ (*state)[i][7]) + i - 0xfa;
        (*state)[i][5] = ((*state)[i][5] ^ (*state)[i][0]) + i - 0xd3;
        (*state)[i][6] = ((*state)[i][6] ^ (*state)[i][1]) + i - 0xb7;
        (*state)[i][7] = ((*state)[i][7] ^ (*state)[i][2]) + i - 0xe9;
    }
}

// 逆行混合
static void SZQ_InvRowsMix(szqState_t *state)
{
    register uint32_t i;

    for(i = 0; i < SZQ_NK; ++i) {
        (*state)[i][7] = ((*state)[i][7] + 0xe9 - i) ^ (*state)[i][2];
        (*state)[i][6] = ((*state)[i][6] + 0xb7 - i) ^ (*state)[i][1];
        (*state)[i][5] = ((*state)[i][5] + 0xd3 - i) ^ (*state)[i][0];
        (*state)[i][4] = ((*state)[i][4] + 0xfa - i) ^ (*state)[i][7];
        (*state)[i][3] = ((*state)[i][3] + 0x01 - i) ^ (*state)[i][6];
        (*state)[i][2] = ((*state)[i][2] + 0xa9 - i) ^ (*state)[i][5];
        (*state)[i][1] = ((*state)[i][1] + 0x9c - i) ^ (*state)[i][4];
        (*state)[i][0] = ((*state)[i][0] + 0x1f - i) ^ (*state)[i][3];
    }
}

// 字节置换
static void SZQ_SubBytes(szqState_t *state)
{
    register uint32_t i;

    for(i = 0; i < SZQ_NK; ++i) {
        (*state)[0][i] = SZQ_GET_SBOX((*state)[0][i]);
        (*state)[1][i] = SZQ_GET_SBOX((*state)[1][i]);
        (*state)[2][i] = SZQ_GET_SBOX((*state)[2][i]);
        (*state)[3][i] = SZQ_GET_SBOX((*state)[3][i]);
        (*state)[4][i] = SZQ_GET_SBOX((*state)[4][i]);
        (*state)[5][i] = SZQ_GET_SBOX((*state)[5][i]);
        (*state)[6][i] = SZQ_GET_SBOX((*state)[6][i]);
        (*state)[7][i] = SZQ_GET_SBOX((*state)[7][i]);
    }
}

// 逆字节置换
static void SZQ_InvSubBytes(szqState_t *state)
{
    register uint32_t i;

    for(i = 0; i < SZQ_NK; ++i) {
        (*state)[i][0] = SZQ_GET_RSBOX((*state)[i][0]);
        (*state)[i][1] = SZQ_GET_RSBOX((*state)[i][1]);
        (*state)[i][2] = SZQ_GET_RSBOX((*state)[i][2]);
        (*state)[i][3] = SZQ_GET_RSBOX((*state)[i][3]);
        (*state)[i][4] = SZQ_GET_RSBOX((*state)[i][4]);
        (*state)[i][5] = SZQ_GET_RSBOX((*state)[i][5]);
        (*state)[i][6] = SZQ_GET_RSBOX((*state)[i][6]);
        (*state)[i][7] = SZQ_GET_RSBOX((*state)[i][7]);
    }
}

// 加密块
static void SZQ_Cipher(szqState_t *state, szqState_t *RoundKey)
{
    register uint32_t i;

    SZQ_ShiftColumn(state);
    SZQ_SubBytes(state);
    SZQ_RowsMix(state);

    for(i = 0; i < SZQ_NK; ++i) {
        (*state)[i][0] ^= (*RoundKey)[i][0];
        (*state)[i][1] ^= (*RoundKey)[i][1];
        (*state)[i][2] ^= (*RoundKey)[i][2];
        (*state)[i][3] ^= (*RoundKey)[i][3];
        (*state)[i][4] ^= (*RoundKey)[i][4];
        (*state)[i][5] ^= (*RoundKey)[i][5];
        (*state)[i][6] ^= (*RoundKey)[i][6];
        (*state)[i][7] ^= (*RoundKey)[i][7];
    }
}

// 解密块
static void SZQ_InvCipher(szqState_t *state, szqState_t *RoundKey)
{
    register uint32_t i;

    for(i = 0; i < SZQ_NK; ++i) {
        (*state)[i][0] ^= (*RoundKey)[i][0];
        (*state)[i][1] ^= (*RoundKey)[i][1];
        (*state)[i][2] ^= (*RoundKey)[i][2];
        (*state)[i][3] ^= (*RoundKey)[i][3];
        (*state)[i][4] ^= (*RoundKey)[i][4];
        (*state)[i][5] ^= (*RoundKey)[i][5];
        (*state)[i][6] ^= (*RoundKey)[i][6];
        (*state)[i][7] ^= (*RoundKey)[i][7];
    }

    SZQ_InvRowsMix(state);
    SZQ_InvSubBytes(state);
    SZQ_InvShiftColumn(state);
}

static void SZQ_keyExtension(SZQ_ctx *ctx, uint8_t *key)
{
    register uint8_t i;
    register uint8_t buf;

    SZQ_SubBytes((szqState_t *)key);

    for(i = 0; i < SZQ_BLOCKLEN; ++i) {
        buf = \
            key[i]                 ^ ctx->iv[i]             ^ 
            key[SZQ_ADD_RK(i, 2)]  ^ key[SZQ_ADD_RK(i, 3)]  ^
            key[SZQ_ADD_RK(i, 4)]  ^ key[SZQ_ADD_RK(i, 5)]  ^
            key[SZQ_ADD_RK(i, 8)]  ^ key[SZQ_ADD_RK(i, 7)]  ^
            key[SZQ_SUB_RK(i, 16)] ^ key[SZQ_SUB_RK(i, 41)] ^
            key[SZQ_SUB_RK(i, 32)] ^ key[SZQ_SUB_RK(i, 53)] ^
            key[SZQ_SUB_RK(i, 48)] ^ ctx->iv[SZQ_ADD_RK(i, 17)];

        ctx->iv[i] ^= buf;

        buf = \
            buf                    ^ ctx->iv[i]             ^
            key[SZQ_ADD_RK(i, 10)] ^ key[SZQ_ADD_RK(i, 11)] ^
            key[SZQ_ADD_RK(i, 12)] ^ key[SZQ_ADD_RK(i, 17)] ^
            key[SZQ_ADD_RK(i, 16)] ^ key[SZQ_ADD_RK(i, 37)] ^
            key[SZQ_SUB_RK(i, 22)] ^ key[SZQ_SUB_RK(i, 67)] ^
            key[SZQ_SUB_RK(i, 30)] ^ key[SZQ_SUB_RK(i, 13)] ^
            key[SZQ_SUB_RK(i, 40)] ^ ctx->iv[SZQ_ADD_RK(i, 19)];

        ctx->iv[SZQ_SUB_RK(i, 47)] ^= buf;

        buf = buf ^ key[SZQ_BLOCKLEN - 1];
        buf = bitSwap(buf);
        buf = SZQ_GET_SBOX(buf);
        buf = bitSwap(buf);
        buf ^= 0xff;

        key[SZQ_ADD_RK(i, 7)]  = (buf ^ key[SZQ_ADD_RK(i, 7)])  + i;
        key[SZQ_ADD_RK(i, 14)] = (buf ^ key[SZQ_ADD_RK(i, 14)]) + i;
        key[SZQ_ADD_RK(i, 21)] = (buf ^ key[SZQ_ADD_RK(i, 21)]) + i;
        key[SZQ_ADD_RK(i, 28)] = (buf ^ key[SZQ_ADD_RK(i, 28)]) + i;
        key[SZQ_ADD_RK(i, 35)] = (buf ^ key[SZQ_ADD_RK(i, 35)]) + i;
        key[SZQ_ADD_RK(i, 42)] = (buf ^ key[SZQ_ADD_RK(i, 42)]) + i;

        key[i] = buf;
    }
}

/****************************************************
* Public Function                                   *
****************************************************/

void SZQ_Print(const char *text, uint8_t *buf)
{
    szqState_t *a = (szqState_t *)buf;
    for(int x = 0; x < SZQ_NK; ++x) {
        printf("%s: ", text);
        for(int y = 0; y < SZQ_NK; ++y) {
            printf("%3.02x", (*a)[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

void SZQ_init_ctx(SZQ_ctx *ctx, const uint8_t *keyBuf)
{
    register uint32_t r;
    static uint8_t key[SZQ_BLOCKLEN];

    memcpy(key, keyBuf, SZQ_BLOCKLEN);

    for(r = 0; r < SZQ_NR; ++r) {
        memcpy(ctx->rk[r], key, SZQ_BLOCKLEN);
        SZQ_keyExtension(ctx, key);

        SZQ_Cipher((szqState_t *)key, (szqState_t *)ctx->rk[r]);
        SZQ_Cipher((szqState_t *)key, (szqState_t *)ctx->iv);
    }
}

void SZQ_CBC_Encrypt(SZQ_ctx *ctx, uint8_t *buf, size_t size)
{
    register size_t r;
    register size_t i;
    register size_t n;
    static size_t addr;

    size >>= SZQ_BIN_SHIFT;

    for(r = 0; r < SZQ_NR; ++r) {
        for(i = addr = 0; i < size; addr = ((i + 1) << SZQ_BIN_SHIFT), ++i) {
            SZQ_Cipher((szqState_t *)(buf + addr), (szqState_t *)ctx->rk[r]);
        }
    }
}

void SZQ_CBC_Decrypt(SZQ_ctx *ctx, uint8_t *buf, size_t size)
{
    register size_t r;
    register size_t i;
    register size_t n;
    static size_t addr;

    size >>= SZQ_BIN_SHIFT;

    for(r = 0; r < SZQ_NR; ++r) {
        for(i = addr = 0; i < size; addr = ((i + 1) << SZQ_BIN_SHIFT), ++i) {
            SZQ_InvCipher((szqState_t *)(buf + addr), (szqState_t *)ctx->rk[SZQ_NR - r - 1]);
        }
    }
}

void SZQ_CTR_Xcrypt(SZQ_ctx *ctx, uint8_t *buf, size_t size)
{
    static uint8_t buffer[SZQ_BLOCKLEN];
    static size_t i;
    static size_t bi;

    for(i = 0, bi = SZQ_BLOCKLEN; i < size; ++i, ++bi) {
        if(bi == SZQ_BLOCKLEN) {
            memcpy(buffer, ctx->iv, SZQ_BLOCKLEN);
            SZQ_Cipher((szqState_t *)buffer, (szqState_t *)ctx->rk[i]);

            for(bi = (SZQ_BLOCKLEN - 1); bi; --bi) {
                /* inc will overflow */
                if (ctx->iv[bi] == 255) {
                    ctx->iv[bi] = 0;
                    continue;
                }
                ctx->iv[bi] += 1;
                break;
            }
            bi = 0;
        }
        buf[i] ^= buffer[bi];
    }
}
