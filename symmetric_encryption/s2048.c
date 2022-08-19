#include "S2048.h"

int main()
{
    system("chcp 65001 > nul > nul");
    S2048_ctx *data = (S2048_ctx *)malloc(sizeof(S2048_ctx));
    FILE *fp_sbox   = fopen("keys/sn.sbox", "rb");
    FILE *fp_keys   = fopen("keys/sn.keys", "rb");
    FILE *fp_load_file  = NULL;
    FILE *fp_write_file = NULL;
    char load_filePath[256]  = {0};
    char write_filePath[256] = {0};
    char input_temp_buff;
    int choice;

    if (!fp_sbox || !fp_keys) {
        printf("请检查keys目录，需要%ssn.sbox%s与%ssn.keys%s这两个256字节的二进制文件\n",
        "\x1b[91m", "\x1b[0m", "\x1b[91m", "\x1b[0m");
        return EOF;
    }

    u8 *sbox = (u8 *)malloc(BLOCK_SIZE);
    fread(sbox, 1, BLOCK_SIZE, fp_sbox);

    u8 *keys = (u8 *)malloc(BLOCK_SIZE);
    fread(keys, 1, BLOCK_SIZE, fp_keys);

    static const size_t fileBlockSize = 4096;
    data->data = (u8 *)malloc(fileBlockSize);
    data->key = S2048_Round_obfuscation(keys);

    printf("导入文件路径: ");
    scanf("%[^\n]s", load_filePath);
    scanf("%c", &input_temp_buff);

    printf("导出文件路径: ");
    scanf("%[^\n]s", write_filePath);
    scanf("%c", &input_temp_buff);

    fp_load_file = fopen(load_filePath, "rb");
    if (!fp_load_file) {
        printf("请检查，%s%s%s文件载入失败\n", "\x1b[91m", load_filePath, "\x1b[0m");
        return EOF;
    }

    fp_write_file = fopen(write_filePath, "wb");

    printf("[1]. Encrypt.\n[2]. Decrypt.\n请输入: ");
    scanf("%1d", &choice);
    scanf("%c", &input_temp_buff);

    do {
        data->len = fread(data->data, 1, fileBlockSize, fp_load_file);
        switch(choice) {
            case 1: S2048_encrypt(data); break;
            case 2: S2048_decrypt(data); break;
        }
        fwrite(data->data, 1, data->len, fp_write_file);
    } while(!feof(fp_load_file));

    fclose(fp_sbox);
    fclose(fp_keys);
    fclose(fp_load_file);
    fclose(fp_write_file);
    free(data);
    return 0;
}
