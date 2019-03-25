#ifndef AGCANONICO_H
#define AGCANONICO_H

#define MAX_GENERATIONS 10

#include "Knapsack.h"
#include "Population.h"

class AGCanonico
{
    int generationsLimit;
    Knapsack knapsack;
    Population population;

    public:
        AGCanonico();
        AGCanonico(Knapsack knapsack, Population population);
        virtual ~AGCanonico();

        void setKnapsack(Knapsack knapsack);
        void setPopulation(Population population);
        void setGenerationsLimit(int limit);
        void executeEvolution();
};

#endif // AGCANONICO_H
