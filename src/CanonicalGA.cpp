#include "../include/CanonicalGA.h"
#include <RandomHelper.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

static vector<Fitness> fitnessStatus;
static RandomHelper randomHelper;

CanonicalGA::~CanonicalGA()
{
    fitnessStatus.clear();
}

bool isKnapsackFeasible(vector<int> indiv, Knapsack knapsack)
{
    bool isFeasible = false;
    unsigned int instanceSize = indiv.size();

    unsigned int* instance = new unsigned int[instanceSize]();
    for (unsigned int pos = 0; pos < instanceSize; ++pos)
    {
        instance[pos] = indiv.at(pos);
    }

    isFeasible = knapsack.isFeasible(instance, instanceSize);

    delete(instance);

    return isFeasible;
}

void CanonicalGA::runFitnessEvaluation()
{
    fitnessStatus.clear();
    int populationSize = this->population.getCurrentSize();
    unsigned int instanceSize = this->population.getIndividualSize();
    unsigned weight;
    int value;
    vector<int> individual;

    unsigned int* instance = new unsigned int[instanceSize]();

    for (int indiv = 0; indiv < populationSize; ++indiv)
    {
        individual = this->population.getIndividual(indiv);

        for (unsigned int item = 0; item < instanceSize; ++item)
        {
            instance[item] = individual.at(item);
        }

        value  = this->knapsack.evaluateValue(instance, instanceSize);
        weight = this->knapsack.evaluateWeight(instance, instanceSize);

        if (this->infeasiblesPolicy == InfeasiblesPolicy::Penalize &&
            (!isKnapsackFeasible(individual, knapsack)))
        {
            value -= this->penalizeInfeasibleIndividual(individual);
            value = value >= 0 ? value : 0;
        }

        fitnessStatus.push_back(Fitness(indiv, value, weight));
    }

    delete(instance);
}

void printFitness(Population population)
{
    for (Fitness fit : fitnessStatus)
    {
        cout << "Chromosome: " << fit.getId() <<
        " Value: " << fit.getValue() << endl;
    }
}

int CanonicalGA::runRouletteWhellSelection()
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

void CanonicalGA::moderateGeneration(vector<vector<int>> &generation)
{
    vector<vector<int>>::iterator it;

    if (this->infeasiblesPolicy == InfeasiblesPolicy::Repair)
    {
        for (it = generation.begin(); it != generation.end(); ++it)
        {
            if (!isKnapsackFeasible(*it, this->knapsack))
            {
                this->repairInfeasibleIndividual(*it);
            }
        }
    }
}

void CanonicalGA::repairInfeasibleIndividual(vector<int> &indiv)
{
    vector<int>::iterator it;
    vector<Fitness> allelesEvaluation;
    unsigned int pos, value, weight, totalWeight;

    pos = totalWeight = 0;

    for (it = indiv.begin(); it != indiv.end(); ++it)
    {
        int allele = *it;

        if (allele == 0)
        {
            value = weight = 0;
        }
        else
        {
            value  = this->knapsack.getItemValue(pos);
            weight = this->knapsack.getItemWeight(pos);
        }

        totalWeight += weight;
        allelesEvaluation.push_back(Fitness(pos, value, weight));
        ++pos;
    }

    sort(fitnessStatus.begin(), fitnessStatus.end());

    for (vector<Fitness>::iterator itFit = allelesEvaluation.begin();
         itFit != allelesEvaluation.end() && totalWeight > this->knapsack.getCapacity();
         ++itFit)
    {
        Fitness alleleFit = *itFit;
        if (alleleFit.getValue() == 0) continue;

        indiv.at(alleleFit.getId()) = 0;
        totalWeight -= alleleFit.getWeight();
    }
}

/**
 * https://arxiv.org/pdf/1610.00976.pdf
 */
unsigned int CanonicalGA::penalizeInfeasibleIndividual(vector<int> indiv)
{
    vector<int>::iterator it;
    unsigned int indivWeight, indivValue, pos;

    indivWeight = indivValue = pos = 0;

    for (it = indiv.begin(); it != indiv.end(); ++it, ++pos)
    {
        indivWeight += this->knapsack.getItemWeight(pos) * (*it);
        indivValue += this->knapsack.getItemValue(pos) * (*it);
    }

    double fIndivWeight = indivWeight;
    double fIndivValue = indivValue;
    double fCapacity = this->knapsack.getCapacity();
    double normPenaltyFactor = ((double)(fCapacity/(fIndivWeight + fCapacity)));

    return trunc(fIndivValue - (normPenaltyFactor * fIndivValue));
}

ExecutionReport CanonicalGA::executeEvolution()
{
    this->reset();

    vector<vector<int>> generation;
    vector<vector<int>>::iterator itChild;

    generation = this->population.create(this->knapsack.getMaxNumberOfItens());
    this->moderateGeneration(generation);
    this->population.addIndividuals(generation);

    this->runFitnessEvaluation();

    unsigned int generationNumber = 0;
    int stIndiv, ndIndiv;
    int selecteds[this->population.getThreshold()];
    unsigned int pos;
    vector<int> bestChromosome;
    unsigned int bestFitnessValue = 0;
    Fitness bestFromGeneration;

    while (generationNumber < this->generationsLimit)
    {
        generation.clear();

        for (unsigned int select = 0; select < this->population.getOffspringSize(); select+=2)
        {
            do
            {
                stIndiv = runRouletteWhellSelection();
                ndIndiv = runRouletteWhellSelection();
            } while (stIndiv == ndIndiv);

            generation = this->population.reproduce(stIndiv, ndIndiv);
            this->moderateGeneration(generation);
            this->population.addIndividuals(generation);
        }

        this->runFitnessEvaluation();

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

    ExecutionReport report(this->knapsack, bestChromosome);
    report.setNumberOfGenerations(generationNumber);
    report.setSizeOfPopulation(this->population.getThreshold());

    return report;
}

void CanonicalGA::reset()
{
    this->population.destroy();
    fitnessStatus.clear();
}

void CanonicalGA::setInfeasiblesPolicy(InfeasiblesPolicy policy)
{
    this->infeasiblesPolicy = policy;
}

void CanonicalGA::setGenerationsLimit(unsigned int limit)
{
    this->generationsLimit = limit;
}

void CanonicalGA::setPopulationSize(unsigned int size)
{
    this->population.setThreshold(size);
}

