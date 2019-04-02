#include "IntegerGA.h"
#include <Fitness.h>

static vector<Fitness> fitnessStatus;

IntegerGA::IntegerGA(Knapsack knapsack, Population population)
{
    this->population = population;
    this->knapsack = knapsack;
}

IntegerGA::~IntegerGA()
{
}

void printFitness()
{
    for (Fitness fit : fitnessStatus)
    {
        cout << "Chromosome: " << fit.getId() <<
        " Value: " << fit.getValue() << endl;
    }
}

void IntegerGA::runFitnessEvaluation()
{
    fitnessStatus.clear();

    int populationSize = this->population.getCurrentSize();
    unsigned weight, value;
    vector<int> individual;

    for (int nIndiv = 0; nIndiv < populationSize; ++nIndiv)
    {
        individual = this->population.getIndividual(nIndiv);

        value = weight = 0;

        for (vector<int>::iterator it = individual.begin(); it != individual.end(); ++it)
        {
            value  += this->knapsack.getItemValue(*it);
            weight += this->knapsack.getItemWeight(*it);
        }

//        if (this->infeasiblesPolicy == InfeasiblesPolicy::Penalize &&
//            (!isKnapsackFeasible(individual, knapsack)))
//        {
//            value -= this->penalizeInfeasibleIndividual(individual);
//            value = value >= 0 ? value : 0;
//        }

        fitnessStatus.push_back(Fitness(nIndiv, value, weight));
    }
}

ExecutionReport IntegerGA::executeEvolution()
{
      vector<vector<int>> generation;

      this->population.setThreshold(4);
      this->knapsack.setCapacity(24);
      generation = this->population.create(this->knapsack);
      this->population.show(generation);

      this->runFitnessEvaluation();
      printFitness();

      ExecutionReport report;

      return report;
}

