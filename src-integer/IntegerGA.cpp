#include "IntegerGA.h"
#include <Fitness.h>
#include <RandomHelper.h>

static RandomHelper randomHelper;
static vector<Fitness> fitnessStatus;

IntegerGA::IntegerGA(Knapsack knapsack, IntegerPopulation population)
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
        cout << "Chromosome: " << fit.getId() + 1 <<
             " Value: " << fit.getValue() << endl;
    }
}

int IntegerGA::runRouletteWhellSelection()
{
    double normFitness[fitnessStatus.size()];
    double factor, sum;
    unsigned int pos;

    factor = randomHelper.getRandomBetween0and1();

    sum = 0;
    for (Fitness fit : fitnessStatus)
        sum += fit.getValue();

    pos = 0;
    for (Fitness fit : fitnessStatus)
    {
        normFitness[pos++] = fit.getValue()/sum;
    }

    int ithIndiv = 0;
    sum = normFitness[0];

    while (sum < factor)
    {
        ++ithIndiv;
        sum += normFitness[ithIndiv];
    }

    return ithIndiv;
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

        fitnessStatus.push_back(Fitness(nIndiv, value, weight));
    }
}

bool IntegerGA::isKnapsackFeasible(vector<int> indiv)
{
    unsigned int totalWeight = 0;

    for (vector<int>::iterator it = indiv.begin(); it != indiv.end(); ++it)
    {
        totalWeight += this->knapsack.getItemWeight(*it);
    }

    return totalWeight <= this->knapsack.getCapacity();
}

void IntegerGA::repairInfeasibleIndividual(vector<int> &indiv)
{
    vector<int>::iterator it;
    vector<Fitness> allelesEvaluation;
    unsigned int value, weight, totalWeight;

    totalWeight = 0;

    for (it = indiv.begin(); it != indiv.end(); ++it)
    {
        value  = this->knapsack.getItemValue(*it);
        weight = this->knapsack.getItemWeight(*it);

        totalWeight += weight;
        allelesEvaluation.push_back(Fitness(*it, value, weight));
    }

    sort(fitnessStatus.begin(), fitnessStatus.end());

    for (vector<Fitness>::iterator itFit = allelesEvaluation.begin();
            itFit != allelesEvaluation.end() && totalWeight > this->knapsack.getCapacity();
            ++itFit)
    {
        Fitness alleleFit = *itFit;

        indiv.erase(indiv.begin() + alleleFit.getId());
        totalWeight -= alleleFit.getWeight();
    }
}

void IntegerGA::moderateGeneration(vector<vector<int>> &generation)
{
    vector<vector<int>>::iterator it;

    for (it = generation.begin(); it != generation.end(); ++it)
    {
        if (!this->isKnapsackFeasible(*it))
        {
            this->repairInfeasibleIndividual(*it);
        }
    }
}

ExecutionReport IntegerGA::executeEvolution()
{
    vector<vector<int>> generation;
    unsigned int generationNumber, stIndiv, ndIndiv, pos;
    int selecteds[this->population.getThreshold()];
    unsigned int bestFitnessValue = 0;
    vector<int> bestChromosome;

    this->population.setThreshold(4);
    this->knapsack.setCapacity(50);
    this->generationsLimit = 1;

    generation = this->population.create(this->knapsack);
    this->population.show(generation);

    this->runFitnessEvaluation();
    printFitness();

    generationNumber = 0;
    Fitness bestFromGeneration;

    while (generationNumber < this->generationsLimit)
    {
        for (unsigned int select = 0; select < this->population.getThreshold(); select+=2)
        {
            do
            {
                stIndiv = runRouletteWhellSelection();
                ndIndiv = runRouletteWhellSelection();
            }
            while (stIndiv == ndIndiv);

            cout << "Roulette: " << stIndiv << " - " << ndIndiv << endl;

            generation = this->population.reproduce(stIndiv, ndIndiv);
            cout << "Offspring: " << endl;
            this->population.show(generation);

            this->moderateGeneration(generation);
            cout << "Moderated Offspring: " << endl;
            this->population.show(generation);

            this->population.addIndividuals(generation);
            cout << "New Generation: " << endl;
            this->population.show(generation);
        }

        this->runFitnessEvaluation();
        printFitness();

        sort(fitnessStatus.begin(), fitnessStatus.end(), greater<Fitness>());

        pos = 0;
        vector<Fitness>::iterator it;
        for (it = fitnessStatus.begin();
                it != fitnessStatus.end() && pos < this->population.getThreshold(); ++it)
        {
            selecteds[pos++] = it->getId();
        }
        fitnessStatus.erase(it, fitnessStatus.end());

        bestFromGeneration = fitnessStatus.at(0);

        if (bestFromGeneration.getValue() > bestFitnessValue)
        {
            bestChromosome = this->population.getIndividual(bestFromGeneration.getId());
            bestFitnessValue = bestFromGeneration.getValue();
        }

        this->population.shrink(selecteds);

        ++generationNumber;

    }

    ExecutionReport report;
    report.setNumberOfGenerations(generationNumber);
    report.setSizeOfPopulation(this->population.getThreshold());

    return report;
}



