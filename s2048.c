#include "S2048.h"
#include <errno.h>
#include <math.h>

#define LOAD_FILE "SN_RANDOM_DATA_TEST_FILE.bin"
#define OUTPUT_FILE "SN_ENCRYPT_DATA_TEST_FILE.bin"

static long get_file_size(FILE *stream)
{
    long file_size = -1;
    long cur_offset = ftell(stream);
    fseek(stream, 0, SEEK_END);
    file_size = ftell(stream);
    fseek(stream, cur_offset, SEEK_SET);
    return file_size;
}

static uint8_t *file_read(FILE *stream)
{
    long len = get_file_size(stream);
    uint8_t *data = (uint8_t *)malloc(len);
    for(size_t x = 0; x < len; ++x) {
        data[x] = fgetc(stream);
    } return data;
}

static void PRINT(S2048_ctx *data)
{
    for(int x = 0;x < data->len; ++x) {
        if (data->data[x] == 0x00) {
            printf("\x1b[91m%02x\x1b[0m", data->data[x]);
        } else {
            printf("%02x", data->data[x]);
        }
        if((x+1) % 32 == 0) {printf("\n");} else {printf(" ");}
    }
}

int main(int argc, char **argv)
{
    // 变量初始化
    printf("正在打开%s文件，用于导入...\n", LOAD_FILE);
    printf("正在打开%s文件，用于导出...\n", OUTPUT_FILE);
    FILE *fp = fopen(LOAD_FILE, "rb");
    FILE *fp_write = fopen(OUTPUT_FILE, "wb");
    if(!fp || !fp_write) {
        printf("文件打开出错！\n");
        return -1;
    }
    printf("文件: %s，打开成功\n", LOAD_FILE);
    printf("文件: %s，打开成功\n", OUTPUT_FILE);

    printf("正在初始化必要变量...\n");
    S2048_ctx *data = (S2048_ctx *)malloc(sizeof(S2048_ctx));
    char password[257] = {
        "GET / HTTP/1.1\r\nHost: sngrotesque.com\r\nAccept: */*\r\n"
        "Connection: keep-alive\r\nContent-Type: applicaion/json\r\n"
        "Content-Length: 34\r\nUser-Agent: Moaillz (Android 10)\r\n"
        "\r\nuser=root&password=ZZHmihoyo0912%40%23&token=8676892"
    };
    const static int N = 256;
    data->data = (u8 *)calloc(N + 1, 1);
    data->token = (u8 *)password;
    printf("当前单次吞吐数据量为: %d字节\n", N);

    // 密钥填充与更新
    printf("正在填充密钥数据...\n");
    S2048_Key_Padding(data);
    printf("正在创建总密钥...\n");
    u8 **key = Round_key_obfuscation(data->token);

    // 加密
    printf("密钥处理完成，开始加密并写入文件...\n");
    do {
        memset(data->data, 0, N);
        data->len = fread(data->data, 1, N, fp);
        if(data->len != N) {S2048_Padding(data);}
        S2048_ENCRYPT(data, key);
        fwrite(data->data, 1, data->len, fp_write);
    } while(!feof(fp));
    printf("文件加密完成！\n");

    // 善后
    printf("正在处理善后工作...\n");
    fclose(fp);
    fclose(fp_write);
    free(data);
    printf("善后工作完成！\n");

    return 0;
}
