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
    sn *data = (sn *)malloc(sizeof(sn));

    char temp[4096] = {
        "0000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000"
    };
    char key_temp[257] = {
        "----------------------------------------------------------------"
        "----------------------------------------------------------------"
        "----------------------------------------------------------------"
        "----------------------------------------------------------------"
    };
    data->data = (u8 *)temp;
    data->len = strlen(temp);
    data->token = (u8 *)key_temp;

    S2048_Padding(data);
    S2048_ENCRYPT(data);

    for(int x = 0;x < data->len; ++x) {
        printf("%02X", data->data[x]);
        if((x+1) % 16 == 0) {
            printf("\n");
        } else {
            printf(" ");
        }
    }

    return 0;
}