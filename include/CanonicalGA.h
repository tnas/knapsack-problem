#ifndef AGCANONICO_H
#define AGCANONICO_H

#define MAX_GENERATIONS 10

#include <vector>
#include "Knapsack.h"
#include "Population.h"
#include <Fitness.h>
#include <ExecutionReport.h>

using namespace std;

enum InfeasiblesPolicy { Repair, Penalize };

class CanonicalGA
{
    int generationsLimit;
    Knapsack knapsack;
    Population population;
    InfeasiblesPolicy infeasiblesPolicy;

    public:
        CanonicalGA();
        CanonicalGA(Knapsack knapsack, Population population, InfeasiblesPolicy infeasiblesPolicy);
        virtual ~CanonicalGA();
        void setKnapsack(Knapsack knapsack);
        void setPopulation(Population population);
        void setGenerationsLimit(int limit);
        ExecutionReport executeEvolution();
        void moderateGeneration(vector<vector<int>> &generation);
        void repairInfeasibleIndividual(vector<int> &indiv);
        void penalizeInfeasibleIndividual(vector<int> indiv);
};

#endif // AGCANONICO_H
