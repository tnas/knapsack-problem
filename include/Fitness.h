#ifndef FITNESS_H
#define FITNESS_H

#include <algorithm>

class Fitness
{
    unsigned int chromosome;
    unsigned int value;

    public:
        Fitness();
        Fitness(unsigned int chromosome, unsigned int value);
        virtual ~Fitness();
        bool operator< (const Fitness &other) const;
        bool operator> (const Fitness &other) const;
        void setValue(unsigned int value);
        void setChromosome(unsigned int chromosome);
        unsigned int getValue();
        unsigned int getChromosome();
};

#endif // FITNESS_H
