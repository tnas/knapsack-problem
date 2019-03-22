#include "RandomHelper.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

class RandomicHelper
{
public:

    RandomicHelper()
    {
        srand(time(NULL));
    }

    ~RandomicHelper()
    {
    }

    int getRandomFromZero(int max)
    {
        return rand() % (max + 1);
    }

};
