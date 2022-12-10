#include "lib/S2048.h"
#include <windows.h>

#define FILE_PATH_N 512 // 文件路径的字节长度

// 输出文件路径为空时
char *add_file_name(char *in_f)
{
    int len = strlen(in_f);
    char *res = (char *)malloc(len + 6);
    memcpy(res, in_f, len);
    res[len]   = '.';
    res[len+1] = 's';
    res[len+2] = 'e';
    res[len+3] = 'n';
    res[len+4] = 'c';
    res[len+6] = 0b0;
    return res;
}

void CHECK_CV_FILE(sn *data)
{
    if (CV_R(data) == EOF) {
        CV_INIT(data);
        CV_W(data);
        printf("已将密钥保存至本地.\n");
    } else {
        CV_R(data);
        printf("已读取本地密钥.\n");
    }
}

BOOL exists(FILE *stream)
{
    if (!stream) {
        return FALSE;
    } else {
        return TRUE;
    }
}

// 输出帮助文档
static void HELP_DOCUMENT()
{
    system("cls");
    printf(
        "|----文档-----开始--------------------------------------------------------|\n"
        "|                                                                         |\n"
        "|    此加密算法原型由SN-Grotesque开发                                     |\n"
        "|    Github: https://github.com/sngrotesque/sn_cipher                     |\n"
        "|                                                                         |\n"
        "|    在确定了输入与输出的文件路径之后，程序会生成一份独属于你的安全密钥   |\n"
        "|    会保存至当前目录下，命名为'%s'，请妥善保存它                  |\n"
        "|                                                                         |\n"
        "|    输入文件路径时可以'拖入'                                             |\n"
        "|    加密后的保存路径如果为空的话将会直接保存在当前目录中。               |\n"
        "|                                                                         |\n"
        "|    [!] 如果保存路径中有相同名称的文件将会被直接覆盖掉 [!]               |\n"
        "|                                                                         |\n"
        "|----文档---------------------------------------------------------结束----|\n"
        "\n"
    , CV_FILE_NAME);
}

int main(int argc, char **argv)
{
    sn *data = (sn *)malloc(sizeof(sn));
    char *user_in_file_path = (char *)calloc(512, 1);
    char *user_out_file_path = (char *)calloc(512, 1);
    char user_input_buff;
    int user_xx;
    FILE *f_ptr_in, *f_ptr_out;

    HELP_DOCUMENT();

    printf("菜单:\n\t0. 退出程序.\n\t1. 加密数据.\n\t2. 解密数据.\n\t请输入: ");
    scanf("%d", &user_xx);
    scanf("%c", &user_input_buff);
    
    switch(user_xx) {
        case 0:
            printf("退出...\n");
            exit(0);
        case 1:
            printf("加密...\n");
            CHECK_CV_FILE(data);

            do {
                printf("请输入需加密的文件路径: ");
                scanf("%[^\n]s", user_in_file_path);
                scanf("%c", &user_input_buff);
            } while(*user_in_file_path == 0);
            
            printf("请输入需输出的文件路径: ");
            scanf("%[^\n]s", user_out_file_path);
            scanf("%c", &user_input_buff);

            f_ptr_in = fopen(user_in_file_path, "rb");
            if (!f_ptr_in) {
                printf("指定文件不存在或正被其他程序占用，请重试。\n");
                return -1;
            }
            data->data = file_read(f_ptr_in);
            data->data_n = get_file_size(f_ptr_in);
            
            
            break;
        case 2:
            printf("解密...\n");
            break;
        default:
            printf("错误输入.\n");
            break;
    }

    Sleep(3000);
    return 0;
}