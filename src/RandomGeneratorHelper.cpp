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

int RandomGeneratorHelper::getRandomFromZero(int max)
{
    return rand() % (max + 1);
}


