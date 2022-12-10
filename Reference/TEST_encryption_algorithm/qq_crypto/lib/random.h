#include "base_include.h"
#include <sys/timeb.h>
#include <time.h>

#ifndef __RANDOM_H__
#define __RANDOM_H__

static void setRandomSeed()
{
    clockid_t a = 0;
    struct timespec p = {0, 0};
    clock_gettime(a, &p);
    srand((unsigned)p.tv_nsec);
}

static uint32_t random_range(uint32_t min, uint32_t max)
{
    return (rand() * rand()) % (max - min + 1) + min;
}


#endif