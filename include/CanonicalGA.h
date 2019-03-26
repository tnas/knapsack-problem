#ifndef AGCANONICO_H
#define AGCANONICO_H

#define MAX_GENERATIONS 1

#include <vector>
#include "Knapsack.h"
#include "Population.h"
#include <Fitness.h>
#include <ExecutionReport.h>

using namespace std;

enum class InfeasiblesModeration { Repair, Penalize };

class CanonicalGA
{
    int generationsLimit;
    Knapsack knapsack;
    Population population;
    InfeasiblesModeration moderation;

    public:
        CanonicalGA();
        CanonicalGA(Knapsack knapsack, Population population, InfeasiblesModeration moderation);
        virtual ~CanonicalGA();
        void setKnapsack(Knapsack knapsack);
        void setPopulation(Population population);
        void setGenerationsLimit(int limit);
        ExecutionReport executeEvolution();
        void repairInfeasibleIndividual(vector<int> indiv);
        void penalizeInfeasibleIndividual(vector<int> indiv);
};

#endif // AGCANONICO_H
