#include "RandomHelper.h"
#include <time.h>
#include <stdlib.h>

RandomHelper::RandomHelper()
{
    srand(time(NULL));
}

RandomHelper::~RandomHelper()
{
}

unsigned int RandomHelper::getRandomBetweenZeroTo(int max)
{
    return rand() % (max + 1);
}

double RandomHelper::getRandomBetween0and1()
{
    return ((double) rand() / RAND_MAX);
}




