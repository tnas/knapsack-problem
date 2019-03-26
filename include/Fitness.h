#ifndef FITNESS_H
#define FITNESS_H

#include <algorithm>

class Fitness
{
    unsigned int id;
    unsigned int value;
    unsigned int weight;

    public:
        Fitness();
        Fitness(unsigned int id, unsigned int value);
        Fitness(unsigned int id, unsigned int value, unsigned int weight);
        virtual ~Fitness();
        bool operator< (const Fitness &other) const;
        bool operator> (const Fitness &other) const;
        void setValue(unsigned int value);
        void setWeight(unsigned int weight);
        void setId(unsigned int id);
        unsigned int getValue();
        unsigned int getWeight();
        unsigned int getId();
};

#endif // FITNESS_H
