#ifndef FITNESS_H
#define FITNESS_H

#include <algorithm>

class Fitness
{
    unsigned int chromosome;
    unsigned int value;
    unsigned int weight;

    public:
        Fitness();
        Fitness(unsigned int chromosome, unsigned int value);
        Fitness(unsigned int chromosome, unsigned int value, unsigned int weight);
        virtual ~Fitness();
        bool operator< (const Fitness &other) const;
        bool operator> (const Fitness &other) const;
        void setValue(unsigned int value);
        void setWeight(unsigned int weight);
        void setChromosome(unsigned int chromosome);
        unsigned int getValue();
        unsigned int getWeight();
        unsigned int getChromosome();
};

#endif // FITNESS_H
