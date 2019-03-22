#include "Population.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <iostream>
//#include <RandomHelper.h>

#define RANDOM_UPPERBOUND 2

using namespace std;

vector<vector<int>> individuals;
//RandomHelper randomHelper;

Population::Population()
{
    this->size = this->offspringSize = DEFAULT_SIZE;
    this->crossoverProbability = CROSSOVER_PROBABILITY;
    this->mutationProbaility   = MUTATION_PROPABILITY;
    srand(time(NULL));
}

Population::Population(int size, int offspringSize)
{
    this->size = size;
    this->offspringSize = offspringSize;
}

Population::~Population()
{
}

void Population::setSize(int size)
{
    this->size = size;
}

void Population::setOffspringSize(int size)
{
    this->offspringSize = size;
}

void Population::create(int individualSize)
{
    this->individualSize = individualSize;

    for (int indiv = 0; indiv < this->size; ++indiv)
    {
        vector<int> individual;

        for (int allele = 0; allele < this->individualSize; ++allele)
        {
            individual.push_back(rand() % RANDOM_UPPERBOUND);
        }
        individuals.push_back(individual);
    }
}

void Population::makeCrossover(int first, int second)
{
//    int crossoverPoint = randomHelper.getRandomFromZero(this->individualSize);
//    cout << "CrossoverPoint: " << crossoverPoint << endl;

}

int Population::getAllele(int individual, int position)
{
    return individuals.at(individual).at(position);
}

int Population::getIndividualSize()
{
    return this->individualSize;
}

int Population::getSize()
{
    return this->size;
}

int Population::getOffspringSize()
{
    return this->offspringSize;
}

void Population::show()
{
    for (int indiv = 0; indiv < this->size; ++indiv)
    {
        for (int allele = 0; allele < this->individualSize; ++allele)
        {
            cout << individuals.at(indiv).at(allele) << " ";
        }

        cout << endl;
    }
}

