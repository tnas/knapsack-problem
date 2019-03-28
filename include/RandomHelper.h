#ifndef RANDOMHELPER_H
#define RANDOMHELPER_H


class RandomHelper
{
    public:
        RandomHelper();
        virtual ~RandomHelper();
        unsigned int getRandomBetweenZeroTo(int max);
        double getRandomBetween0and1();
};

#endif // RANDOMHELPER_H
