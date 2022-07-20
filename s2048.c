#include "S2048.h"

int main(int argc, char **argv)
{
    // 初始化
    const static uint32_t BlockSize = 4096;
    if (argc != 4) {printf("./main [in_file] [out_file] [password]");return -1;}

    const char *load_file_name = argv[1];
    const char *output_file_name = argv[2];
    if(!strcmp(load_file_name, output_file_name)) {
        printf("输入与输出文件名不能相同！\n"); return -1;
    }

    FILE *fp_r = fopen(load_file_name, "rb");
    if(!fp_r) {printf("文件打开失败！\n");return -1;}
    FILE *fp_w = fopen(output_file_name, "wb");

    S2048_ctx *data = (S2048_ctx *)malloc(sizeof(S2048_ctx));
    data->data = (u8 *)malloc(BlockSize + 1);
    data->token = (u8 *)argv[3];
    data->data[BlockSize] = 0x00;

    S2048_Key_Padding(data);
    u8 **total_key = S2048_Round_key_obfuscation(data->token);

    do {
        memset(data->data, 0, BlockSize);
        data->len = fread(data->data, 1, BlockSize, fp_r);
        if(data->len != BlockSize) {S2048_Padding(data);}
        S2048_ENCRYPT(data, total_key);
        fwrite(data->data, 1, data->len, fp_w);
    } while(!feof(fp_r));

    fclose(fp_r);
    fclose(fp_w);
    free(data);
    return 0;
}
