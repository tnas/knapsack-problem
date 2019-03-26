#ifndef AGCANONICO_H
#define AGCANONICO_H

#define MAX_GENERATIONS 1

#include "Knapsack.h"
#include "Population.h"
#include <Fitness.h>
#include <ExecutionReport.h>

class CanonicalGA
{
    int generationsLimit;
    Knapsack knapsack;
    Population population;

    public:
        CanonicalGA();
        CanonicalGA(Knapsack knapsack, Population population);
        virtual ~CanonicalGA();

        void setKnapsack(Knapsack knapsack);
        void setPopulation(Population population);
        void setGenerationsLimit(int limit);
        ExecutionReport executeEvolution();
};

#endif // AGCANONICO_H
