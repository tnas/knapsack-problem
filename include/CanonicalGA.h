#ifndef AGCANONICO_H
#define AGCANONICO_H

#define MAX_GENERATIONS 500

#include <config.h>
#include <vector>
#include "Knapsack.h"
#include "Population.h"
#include <Fitness.h>
#include <ExecutionReport.h>

using namespace std;

class CanonicalGA
{
    unsigned int generationsLimit;
    Knapsack knapsack;
    Population population;
    InfeasiblesPolicy infeasiblesPolicy;

    public:
        CanonicalGA(unsigned int generations, Knapsack knapsack, Population population, InfeasiblesPolicy infeasiblesPolicy):
            generationsLimit(generations), knapsack(knapsack), population(population), infeasiblesPolicy(infeasiblesPolicy){};
        CanonicalGA(Knapsack knapsack, Population population, InfeasiblesPolicy infeasiblesPolicy):
            CanonicalGA(MAX_GENERATIONS, knapsack, population, infeasiblesPolicy){};
        CanonicalGA(Knapsack knapsack, Population population):
            CanonicalGA(knapsack, population, InfeasiblesPolicy::Repair){};
        CanonicalGA():
            generationsLimit(MAX_GENERATIONS), infeasiblesPolicy(InfeasiblesPolicy::Repair){};
        virtual ~CanonicalGA();

        int runRouletteWhellSelection();
        ExecutionReport executeEvolution();
        void runFitnessEvaluation();
        void moderateGeneration(vector<vector<int>> &generation);
        void repairInfeasibleIndividual(vector<int> &indiv);
        unsigned int penalizeInfeasibleIndividual(vector<int> indiv);
        void reset();
        void setInfeasiblesPolicy(InfeasiblesPolicy policy);
        void setGenerationsLimit(unsigned int limit);
        void setPopulationSize(unsigned int size);
};

#endif // AGCANONICO_H
