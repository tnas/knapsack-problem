#ifndef INTEGERGA_H
#define INTEGERGA_H

#include <Population.h>
#include <ExecutionReport.h>

class IntegerGA
{
    Knapsack knapsack;
    Population population;

    public:
        IntegerGA(Knapsack knapsack, Population population);
        virtual ~IntegerGA();
        void runFitnessEvaluation();
        ExecutionReport executeEvolution();
};

#endif // INTEGERGA_H
