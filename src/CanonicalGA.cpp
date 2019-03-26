#include "../include/CanonicalGA.h"
#include <RandomGeneratorHelper.h>
#include <iostream>
#include <vector>

using namespace std;

static vector<Fitness> fitnessStatus;
static RandomGeneratorHelper randomHelper;
static ExecutionReport report;

CanonicalGA::CanonicalGA()
{
    this->generationsLimit = MAX_GENERATIONS;
}

CanonicalGA::CanonicalGA(Knapsack knapsack, Population population)
{
    this->knapsack = knapsack;
    this->population = population;
}

CanonicalGA::~CanonicalGA()
{
    fitnessStatus.clear();
}

void evaluateFitness(Population population, Knapsack knapsack)
{
    fitnessStatus.clear();
    int populationSize = population.getCurrentSize();
    unsigned int value;

    for (int indiv = 0; indiv < populationSize; ++indiv)
    {
        value = 0;

        for (unsigned int item = 0; item < population.getIndividualSize(); ++item)
        {

            value += knapsack.getItemValue(item) *
                population.getAllele(indiv, item);
        }

        fitnessStatus.push_back(Fitness(indiv, value));
    }
}

void printFitness(Population population)
{
    for (Fitness fit : fitnessStatus)
    {
        cout << "Chromosome: " << fit.getChromosome() <<
        " Value: " << fit.getValue() << endl;
    }
}

int runRouletteWhellSelection()
{
    double normFitness[fitnessStatus.size()];
    double factor, sum;
    unsigned int pos;

    factor = randomHelper.getRandomBetween0and1();

    sum = 0;
    for (Fitness fit : fitnessStatus)
         sum += fit.getValue();
    //cout << "Sum: " << sum << " Factor: " << factor << endl;

    pos = 0;
    for (Fitness fit : fitnessStatus)
    {
        normFitness[pos++] = fit.getValue()/sum;
        //cout << "Original value: " << fit.getValue() << " -- Normalized: " << normFitness[pos-1] << endl;
    }


    int ithIndiv = 0;
    sum = normFitness[0];
    //cout << "Sum: " << sum << " ithIndiv: " << ithIndiv << endl;

    while (sum < factor)
    {
        ++ithIndiv;
        sum += normFitness[ithIndiv];
        //cout << "Sum: " << sum << " ithIndiv: " << ithIndiv << endl;
    }

    return ithIndiv;
}

ExecutionReport CanonicalGA::executeEvolution()
{
    this->population.create(this->knapsack.getMaxNumberOfItens());

    //this->population.setThreshold(5);
    //this->population.create(5);

    evaluateFitness(this->population, this->knapsack);

    //this->population.show();
    ////cout << "Fitness: " << endl;
    //printFitness(this->population);

    int generation = 0;
    int stIndiv, ndIndiv;
    int selecteds[this->population.getThreshold()];

    unsigned int* bestChromosome;
    unsigned int bestFitnessValue = 0;
    Fitness bestFromGeneration;

    while (generation < MAX_GENERATIONS)
    {
        //cout << "runRouletteWhellSelection" << endl;
        for (unsigned int select = 0; select < this->population.getOffspringSize(); select+=2)
        {
            do
            {
                stIndiv = runRouletteWhellSelection();
                ndIndiv = runRouletteWhellSelection();
            } while (stIndiv == ndIndiv);

            //cout << "st: " << stIndiv << " nd: " << ndIndiv << endl;
            this->population.reproduce(stIndiv, ndIndiv);
        }

        //cout << "Descendants: " << endl;
        //this->population.showDescendants();

        this->population.join();

        evaluateFitness(this->population, this->knapsack);
        //cout << "Fitness: " << endl;
        //printFitness(this->population);

        sort(fitnessStatus.begin(), fitnessStatus.end(), greater<Fitness>());

        //cout << "Sorted Fitness: " << endl;
        //printFitness(this->population);

        //cout << "Selected chromosomes: " << endl;
        unsigned int pos = 0;
        vector<Fitness>::iterator it;
        for (it = fitnessStatus.begin();
            it != fitnessStatus.end() && pos < this->population.getThreshold(); ++it)
        {
            selecteds[pos++] = it->getChromosome();
            //cout << "Chrome: " << it->getChromosome() << " Val: " << it->getValue() << endl;
        }
        fitnessStatus.erase(it, fitnessStatus.end());

        //cout << "Fitness after shrinking population: " << endl;
        //printFitness(this->population);

        bestFromGeneration = fitnessStatus.at(0);

        if (bestFromGeneration.getValue() > bestFitnessValue)
        {
            bestChromosome = this->population.selectIndividual(bestFromGeneration.getChromosome());
            bestFitnessValue = bestFromGeneration.getValue();
        }

        this->population.shrink(selecteds);
        //cout << "Shrinked Population: " << endl;
        //this->population.show();

        //this->population.showDescendants();
        //cout << "generation " << generation << endl;
        ++generation;
    }

    report.setChromosome(bestChromosome, this->population.getIndividualSize());
    report.setFitnessValue(bestFitnessValue);
    report.setNumberOfGenerations(generation);

    return report;
}

void CanonicalGA::setKnapsack(Knapsack knapsack)
{
    this->knapsack = knapsack;
}

void CanonicalGA::setPopulation(Population population)
{
    this->population = population;
}

void CanonicalGA::setGenerationsLimit(int limit)
{
    this->generationsLimit = limit;
}
