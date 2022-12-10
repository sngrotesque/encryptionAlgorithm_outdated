#include "base_include.h"
#include "random.h"

/* // **
* 如果你要使用自定义二进制的'u_key'数据
* 请将它的取值范围控制在0x01 ~ 0xFF之间
* 不要有0x00存在
*/ // **

#ifndef __SN_OBJECT__ // 对象定义 - 开始
#define __SN_OBJECT__ 1

// 重命名类型名
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// 初始宏定义
#define FILL_DATA_N      256    // 256 Bytes
#define FILL_KEY_N       256    // 256 Bytes
#define FILL_DATA        121    // 0x79
#define NUMBER_OF_ROUNDS 16     // 加密解密轮数

// 主要变量
typedef struct {
    u8 *data;    // 数据
    u64 data_n;  // 数据长度
    u8 *u_key;   // 密码(密钥)
    u8 *iv;      // 初始混淆值
} sn;

#endif // 对象定义 - 结束

#ifndef __SN_FUNCTION__ // 函数定义 - 开始
#define __SN_FUNCTION__ 1

#define CV_FILE_NAME "SN_KEY.cv"
#define CV_FILE_N 344
#define CV_DATA_N 256
#define HEX_MIN 0x00
#define HEX_MAX 0xFF

// 创建初始化混淆值
static void CV_INIT(sn *data)
{
    setRandomSeed();
    data->iv = (u8 *)malloc(CV_DATA_N);
    for(u32 x = 0; x < FILL_KEY_N; ++x)
        data->iv[x] = random_range(HEX_MIN, HEX_MAX);
}

// 读取混淆值
static int CV_R(sn *data)
{
    FILE *p = fopen(CV_FILE_NAME, "rb");
    if(!p) {return EOF;}
    data->iv = b64de(file_read(p));
    fclose(p);
    return 0;
}

// 写入混淆值
static void CV_W(sn *data)
{
    FILE *p = fopen(CV_FILE_NAME, "wb");
    data->iv = b64en(data->iv, CV_DATA_N);
    file_write(p, data->iv, CV_FILE_N);
    fclose(p);
}

// 数据填充函数
static int PRESET_FILL_DATA(sn *data)
{
    if (data->data == NULL || data->data_n == 0) return EOF;
    u64 MOD = data->data_n % FILL_DATA_N, x = data->data_n;
    if (MOD == 0) {
        u32 FILL_N = FILL_DATA_N + data->data_n;
        u8 *T_DATA = (u8 *)malloc(FILL_N);
        memcpy(T_DATA, data->data, data->data_n);
        free(data->data); data->data = T_DATA;
        for(; x < FILL_N - 2; ++x) data->data[x] = FILL_DATA;
        data->data[FILL_N - 2] = data->data[FILL_N - 1] = 255;
        data->data_n = FILL_N;
    } else {
        u32 TEMP_N = FILL_DATA_N - MOD;
        u32 FILL_N = TEMP_N + data->data_n;
        u8 *T_DATA = (u8 *)malloc(FILL_N);
        memcpy(T_DATA, data->data, data->data_n);
        free(data->data); data->data = T_DATA;
        for(; x < FILL_N - 1; ++x) data->data[x] = FILL_DATA;
        data->data[FILL_N - 1] = TEMP_N;
        data->data_n = FILL_N;
    }
    return 0;
}

// 密钥填充函数
static int PRESET_FILL_KEY(sn *data)
{
    if (data->u_key == NULL || strlen((char *)data->u_key) == 0) return EOF;
    u64 key_len = strlen((char *)data->u_key);
    if (key_len > FILL_KEY_N) {
        u8 *temp = (u8 *)malloc(FILL_KEY_N);
        memcpy(temp, data->u_key, FILL_KEY_N);
        data->u_key = temp; temp = NULL;
    } else {
        for(int x = key_len, index = 0; x < FILL_KEY_N; ++x, ++index) {
            if (index == key_len) index = 0;
            data->u_key[x] = data->u_key[index];
        }
    }
    return 0;
}

// 密钥生成函数
static u8 **KEY_OBFUSCATION(sn *data)
{
    u8 **key = (u8 **)malloc(NUMBER_OF_ROUNDS * 8);
    u8 *key_t = (u8 *)malloc(FILL_KEY_N);
    for(u32 x = 0; x < NUMBER_OF_ROUNDS; ++x) {
        key[x] = (u8 *)malloc(FILL_KEY_N);
        memcpy(key[x], data->u_key, FILL_KEY_N);
        for(u32 y = 0; y < FILL_KEY_N; ++y) {
            switch (y) {
                case 0: key_t[y] = \
                    (y ^ ((key[x][y] ^ key[x][255]) ^ key[x][174]) ^ data->iv[y]) - x; break;
                default: key_t[y] = \
                    (y ^ ((key[x][y] ^ key[x][y-1]) ^ key[x][174]) ^ data->iv[y]) - x; break;
            }
        } data->u_key = key_t;
    } data->u_key = NULL; // 善后
    return key;
}

// 计算Base64编码后的数据长度
static u64 b64encode_n(u64 _n)
{
    if (_n % 3 == 0)
        _n = _n / 3 * 4;
    else if (_n % 3 == 1)
        _n = (_n + 2) / 3 * 4;
    else if (_n % 3 == 2)
        _n = (_n + 1) / 3 * 4;
    return _n;
}

// 计算Base64解码码后的数据长度
static u64 b64decode_n(u8 *data)
{
    u64 len = strlen((char *)data), _n;
    if (strstr((char *)data, "==")) {
        _n = len / 4 * 3 - 2;
    } else if (strstr((char *)data, "=")) {
        _n = len / 4 * 3 - 1;
    } else {
        _n = len / 4 * 3;
    } return _n;
}

// 加密函数
static int ENCRYPT_DATA(sn *data)
{
    if (data->data == NULL || data->data_n == 0 || data->u_key == NULL) {
        return EOF;}
    u8 **key = KEY_OBFUSCATION(data), keyindex;
    u64 rounds, x;
    for(rounds = 0; rounds < NUMBER_OF_ROUNDS; ++rounds) {
        for(x = keyindex = 0; x < data->data_n; ++x, ++keyindex) {
            data->data[x] ^= key[rounds][keyindex];
        }
    }
    data->data = b64en(data->data, data->data_n);
    data->data_n = b64encode_n(data->data_n);
    return 0;
}

// 解密函数
static int DECRYPT_DATA(sn *data)
{
    u8 **key = KEY_OBFUSCATION(data);
    data->data_n = b64decode_n(data->data);
    data->data = b64de(data->data);
    u64 r, x, FILL_N; u8 keyindex;
    for(r = 0; r < NUMBER_OF_ROUNDS; ++r) {
        for(x = keyindex = 0; x < data->data_n; ++x, ++keyindex) {
            data->data[x] = data->data[x] ^ key[NUMBER_OF_ROUNDS - r - 1][keyindex];
        }
    }

    u8 *temp;
    if(data->data[data->data_n - 1] == 255 && data->data[data->data_n - 2] == 255) {
        data->data_n = data->data_n - FILL_DATA_N;
        temp = (u8 *)malloc(data->data_n);
        memcpy(temp, data->data, data->data_n);
        data->data = temp; temp = NULL;
    } else {
        FILL_N = data->data[data->data_n - 1];
        u64 real_n = data->data_n - FILL_N;
        temp = (u8 *)malloc(real_n);
        memcpy(temp, data->data, real_n);
        data->data = temp; temp = NULL;
        data->data_n = real_n;
    }

    return 0;
}

#endif // 函数定义 - 结束


