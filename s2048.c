#include "S2048.h"
#include <errno.h>

static long get_file_size(FILE *stream)
{
	long file_size = -1;
	long cur_offset = ftell(stream);	// 获取当前偏移位置
	if (cur_offset == -1) {
		printf("ftell failed :%s\n", strerror(errno));
		return -1;
	}
	if (fseek(stream, 0, SEEK_END) != 0) {	// 移动文件指针到文件末尾
		printf("fseek failed: %s\n", strerror(errno)); return -1;
	}
	file_size = ftell(stream);	// 获取此时偏移值，即文件大小
	if (file_size == -1) {
		printf("ftell failed :%s\n", strerror(errno));
	}
	if (fseek(stream, cur_offset, SEEK_SET) != 0) {	// 将文件指针恢复初始位置
		printf("fseek failed: %s\n", strerror(errno)); return -1;
	}
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

int main(int argc, char **argv)
{
    if(argc != 5) {
        printf("./main [输入文件路径] [输出文件路径] [密码] [e/d]\n");
        return EOF;
    }
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("请不要使用同一文件作为输入与输出文件\n");
        return EOF;
    }

    sn *data = (sn *)malloc(sizeof(sn));
    char *in_fileName = (char *)malloc(256);
    char *out_fileName = (char *)malloc(256);
    data->u_key = (u8 *)malloc(256);

    memcpy(in_fileName, argv[1], strlen(argv[1]));
    memcpy(out_fileName, argv[2], strlen(argv[2]));
    memcpy(data->u_key, argv[3], strlen(argv[3]));

    FILE *file_ip = fopen(in_fileName, "rb");
    if (!file_ip) {printf("文件打开失败\n"); return -1;}
    data->data = file_read(file_ip);
    data->data_n = get_file_size(file_ip);
    fclose(file_ip);

    SN_INIT_KEY(data);

    if (argv[4][0] == 'e') {
        SN_INIT_DATA(data);
        printf("开始加密...\n");
        ENCRYPT_DATA(data);
        printf("加密完成.\n");
    } else if (argv[4][0] == 'd') {
        DECRYPT_DATA(data);
    } else {
        printf("请确认是'加密'/'解密'.\n");
        return EOF;
    }

    FILE *file_op = fopen(out_fileName, "wb");
    for(u64 x = 0; x < data->data_n; ++x) {
        fputc(data->data[x], file_op);
    }
    fclose(file_op);

    free(data);
    return 0;
}