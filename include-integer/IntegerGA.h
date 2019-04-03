#ifndef INTEGERGA_H
#define INTEGERGA_H

#define MAX_GENERATIONS 500

#include <IntegerPopulation.h>
#include <ExecutionReport.h>

class IntegerGA
{
    unsigned int generationsLimit;
    Knapsack knapsack;
    IntegerPopulation population;

    public:
        IntegerGA(Knapsack knapsack, IntegerPopulation population);
        virtual ~IntegerGA();
        int runRouletteWhellSelection();
        void runFitnessEvaluation();
        ExecutionReport executeEvolution();
        bool isKnapsackFeasible(vector<int> indiv);
        void moderateGeneration(vector<vector<int>> &generation);
        void repairInfeasibleIndividual(vector<int> &indiv);
};

#endif // INTEGERGA_H
