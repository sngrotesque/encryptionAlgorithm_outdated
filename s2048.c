#include "S2048.h"

int main(int argc, char **argv)
{
    const char *plaintext = "Microsoft Windows NT 10.0, This is fucking shit!\n";
    u8 *password = S2048_Key_Padding((u8 *)"hello, world", 12);

    S2048_ctx *data = (S2048_ctx *)malloc(sizeof(S2048_ctx));
    data->data = (u8 *)malloc(1024);
    data->len = strlen(plaintext);
    data->key = S2048_Round_key_obfuscation(password);

    memcpy(data->data, plaintext, strlen(plaintext));

    S2048_Padding(data);

    S2048_ENCRYPT(data);

    printf("%s\n", data->data);

    S2048_DECRYPT(data);

    printf("%s\n", data->data);

    free(data);
    return 0;
}
