#include "../include/AGCanonico.h"
#include <iostream>
#include <time.h>

using namespace std;

int* fitness;

AGCanonico::AGCanonico()
{
    this->generationsLimit = MAX_GENERATIONS;
    srand(time(NULL));
}

AGCanonico::AGCanonico(Knapsack knapsack, Population population)
{
    this->knapsack = knapsack;
    this->population = population;
    fitness = new int[this->population.getSize()]();
}

AGCanonico::~AGCanonico()
{
    delete(fitness);
}

void evaluateFitness(Population population, Knapsack knapsack)
{
    for (int indiv = 0; indiv < population.getSize(); ++indiv)
    {
        for (int item = 0; item < population.getIndividualSize(); ++item)
        {
            fitness[indiv] = knapsack.getItemValue(item) *
                population.getAllele(indiv, item);
        }
    }
}

void printFitness(Population population)
{
    for (int indiv = 0; indiv < population.getSize(); ++indiv)
    {
        cout << fitness[indiv] << endl;
    }
}

int runRouletteWhellSelection(Population population)
{
    int indiv, sum;
    int normFitness[population.getSize()];
    double factor;

    factor = ((double) rand() / RAND_MAX);

    for (indiv = sum = 0; indiv < population.getSize(); ++indiv)
         sum += fitness[indiv];

    for (indiv = 0; indiv < population.getSize(); ++indiv)
        normFitness[indiv] = fitness[indiv]/sum;

    int ithIndiv = 0;
    sum = normFitness[0];

    while (sum < factor)
    {
        ++ithIndiv;
        sum += normFitness[ithIndiv];
    }

    return ithIndiv;
}



void AGCanonico::executeEvolution()
{
    //this->population.create(this->knapsack.getMaxNumberOfItens());
    this->population.create(20);
    evaluateFitness(this->population, this->knapsack);
    this->population.show();
    printFitness(this->population);

    int generation = 0;
    while (generation < MAX_GENERATIONS)
    {
        for (int select = 0; select < this->population.getOffspringSize(); select+=2)
        {
            int stIndiv = runRouletteWhellSelection(this->population);
            int ndIndiv = runRouletteWhellSelection(this->population);
            //this->population.makeCrossover(stIndiv, ndIndiv);
        }

        ++generation;
    }




}

void AGCanonico::setKnapsack(Knapsack knapsack)
{
    this->knapsack = knapsack;
}

void AGCanonico::setPopulation(Population population)
{
    this->population = population;
}

void AGCanonico::setGenerationsLimit(int limit)
{
    this->generationsLimit = limit;
}
