#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef __COLOR__
#define RED   "\x1b[91m"
#define GREEN "\x1b[92m"
#define GOLD  "\x1b[93m"
#define BLUE  "\x1b[96m"
#define WHITE "\x1b[97m"
#define RESET "\x1b[0m"
#endif

#ifndef __SN_STRING_H__
#define __SN_STRING_H__
static char *slwr(const char *str)
{
    uint32_t x, len = strlen(str);
    char *res = (char *)calloc(len, 1);
    for(x = 0; x < len; ++x) {res[x] = str[x]; if (str[x] >= 0x41 && str[x] <= 0x5A) {res[x] += 0x20;}}
    return res;
}

static int to_int(int c)
{
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if(c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= '0' && c <= '9')
        return c - '0';
    return -1;
}

static uint8_t *stoh(const uint8_t *s, uint64_t _n)
{
    uint8_t *str = (uint8_t *)calloc((_n * 2) + 1, 1);
    char *tmp = (char *)malloc(2);
    for(uint64_t x = 0, y = 0; x < _n; ++x, y += 2) {
        sprintf(tmp, "%02x", s[x]);
        str[y] = tmp[0], str[y+1] = tmp[1];
    } return str;
}

static uint8_t *htos(char *text)
{
    const uint32_t len = strlen(text);
    if (len % 2 != 0) {return NULL;}
    uint64_t i, j, x, top, bot;
    uint8_t *ch = (uint8_t *)calloc(len / 2, 1);
    for (i = j = x = 0; i < len; i += 2, x++) {
        top = to_int(text[i]), bot = to_int(text[i+1]);
        if (top == -1 || bot == -1) {
            printf("Non Hex!\n"); return NULL;
        } ch[x] = (top << 4) + bot;
    } return ch;
}
#endif

#ifndef __BASE64_H__
#define __BASE64_H__
const char *const base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static uint8_t *b64en(const uint8_t *str, uint64_t str_len)
{
    uint64_t len, i, j; uint8_t *res;
    (str_len % 3 == 0) ? (len = str_len / 3 * 4) : (len = (str_len / 3 + 1) * 4);
    res = (uint8_t *)malloc(sizeof(uint8_t) * len + 1), res[len] = '\0';
    for (i = 0, j = 0; i < len - 2; j += 3, i += 4) {
        res[i]   = base64_table[str[j]>>2], res[i+1] = base64_table[(str[j] & 0x3) << 4 | (str[j+1] >> 4)];
        res[i+2] = base64_table[(str[j+1] & 0xf) << 2 | (str[j+2] >> 6)], res[i+3] = base64_table[str[j+2] & 0x3f];
    }
    switch (str_len % 3) {case 1: res[i - 2] = '='; res[i - 1] = '='; break; case 2: res[i - 1] = '='; break;}
    return res;
}

static uint8_t *b64de(const uint8_t *code)
{
    uint32_t table[123] = {
        0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
        0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  62, 0,  0,  0,  63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0, 0,
        0, 0, 0, 0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0,
        0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };
    uint64_t len = strlen((char *)code), i, j, str_len;
    uint8_t *res;
    (strstr((char *)code, "==")) ? (str_len = len / 4 * 3 - 2) : (strstr((char *)code, "=")) ? (str_len = len / 4 * 3 - 1) : (str_len = len / 4 * 3);
    res = (uint8_t *)malloc(sizeof(uint8_t) * str_len + 1), res[str_len] = '\0';
    for (i = 0, j = 0; i < len - 2; j += 3, i += 4) {
        res[j]   = ((uint8_t)table[code[i]])    << 2  | (((uint8_t)table[code[i+1]]) >> 4);
        res[j+1] = (((uint8_t)table[code[i+1]]) << 4) | (((uint8_t)table[code[i+2]]) >> 2);
        res[j+2] = (((uint8_t)table[code[i+2]]) << 6) | ((uint8_t)table[code[i+3]]);
    } return res;
}
#endif

#ifndef __GET_FILE_SIZE__
#define __GET_FILE_SIZE__

#if !defined (__WIN32) && !defined (__WIN64)
#include <sys/stat.h>
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
#endif

#ifdef __WIN32
static long get_file_size(FILE *stream)
{
    long n;
    fpos_t fpos;
    fgetpos(stream, &fpos);
    fseek(stream, 0, SEEK_END);
    n = ftell(stream);
    fsetpos(stream, &fpos);
    return n;
}

static uint8_t *file_read(FILE *stream)
{
    long len = get_file_size(stream);
    uint8_t *data = (uint8_t *)malloc(len);
    for(size_t x = 0; x < len; ++x) {
        data[x] = fgetc(stream);
    } return data;
}
#endif

static void file_write(FILE *stream, uint8_t *data, uint64_t data_n)
{
    for(uint64_t x = 0; x < data_n; ++x) {
        fputc(data[x], stream);
    }
}

#endif
