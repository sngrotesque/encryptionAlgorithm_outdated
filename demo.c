#include "S2048.h"
#include <math.h>

int main(int argc, char **argv)
{
    S2048_ctx *data = (S2048_ctx *)malloc(sizeof(S2048_ctx));
    data->token = (u8 *)"sngrotesque-21418571935dajhfbau31./5,/136,1+";
    S2048_Key_Padding(data);

    u8 **key = S2048_Round_key_obfuscation(data->token);

    free(data);
    free(key);
    return 0;
}
