#ifndef RANDOMGENERATORHELPER_H
#define RANDOMGENERATORHELPER_H


class RandomGeneratorHelper
{
    public:
        RandomGeneratorHelper();
        virtual ~RandomGeneratorHelper();
        unsigned int getRandomBetweenZeroTo(int max);
        double getRandomBetween0and1();
};

#endif // RANDOMGENERATORHELPER_H
