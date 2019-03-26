#include "RandomGeneratorHelper.h"
#include <time.h>
#include <stdlib.h>

RandomGeneratorHelper::RandomGeneratorHelper()
{
    srand(time(NULL));
}

RandomGeneratorHelper::~RandomGeneratorHelper()
{
}

unsigned int RandomGeneratorHelper::getRandomBetweenZeroTo(int max)
{
    return rand() % (max + 1);
}

double RandomGeneratorHelper::getRandomBetween0and1()
{
    return ((double) rand() / RAND_MAX);
}




