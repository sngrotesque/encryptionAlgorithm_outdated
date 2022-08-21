#include "s000.h"
#include "../../random/random.h"
#include "../../misc_include/misc.h"

int main(int argc, char **argv)
{
    setRandomSeed();
    uint8_t *public_key  = (uint8_t *)malloc(256);
    uint8_t *private_key = (uint8_t *)malloc(256);
    uint32_t x;

    for(x = 0; x < 256; ++x) {
        private_key[x] = randint(0, 255);
        public_key[x] = f(private_key[x]);
    }

    printf("Public Key:\n");
    PRINT(public_key, 256);
    printf("\n");
    printf("Private Key:\n");
    PRINT(private_key, 256);

    free(public_key);
    free(private_key);
    return 0;
}





