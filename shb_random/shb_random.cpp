#include "shb_random.h"



long int shbRandom(long int i)
{
    srand(i);
    i = rand() % 10;
    return i;
}