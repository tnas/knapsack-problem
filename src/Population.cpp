#include "../include/Population.h"
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "../include/RandomGeneratorHelper.h"

static vector<vector<int>> individuals;
static vector<vector<int>> descendants;
static RandomGeneratorHelper randomHelper;

Population::Population()
{
    this->threshold = this->offspringSize = DEFAULT_THRESHOLD;
    this->crossoverProbability = CROSSOVER_PROBABILITY;
    this->mutationProbaility   = MUTATION_PROPABILITY;
}

Population::Population(int threshold, int offspringSize)
{
    this->threshold = threshold;
    this->offspringSize = offspringSize;
}

Population::~Population()
{
}

void Population::setThreshold(int size)
{
    this->threshold = size;
}

void Population::setOffspringSize(int size)
{
    this->offspringSize = size;
}

void Population::create(int individualSize)
{
    this->individualSize = individualSize;

    for (unsigned int indiv = 0; indiv < this->threshold; ++indiv)
    {
        vector<int> individual;

        for (unsigned int allele = 0; allele < this->individualSize; ++allele)
        {
            //individual.push_back(rand() % RANDOM_UPPERBOUND);
            individual.push_back(randomHelper.getRandomBetweenZeroTo(1));
        }

        individuals.push_back(individual);
    }
}

void makeMutation(vector<int> individual, int allele)
{
    if (randomHelper.getRandomBetween0and1() < MUTATION_PROPABILITY)
        individual.at(allele) ^= 1;
}

bool isAlleleExchangeable()
{
    return randomHelper.getRandomBetween0and1() < CROSSOVER_PROBABILITY;
}

vector<vector<int>> Population::reproduce(int first, int second)
{
    unsigned int crossoverPoint = randomHelper.getRandomBetweenZeroTo(this->individualSize);
    unsigned int allele, stParent, ndParent;

    vector<vector<int>> generation;
    vector<int> stChild, ndChild;

    for (allele = 0; allele < crossoverPoint; ++allele)
    {
        stChild.push_back(individuals.at(first).at(allele));
        makeMutation(stChild, allele);

        ndChild.push_back(individuals.at(second).at(allele));
        makeMutation(ndChild, allele);
    }

    if (isAlleleExchangeable())
    {
        stParent = second;
        ndParent = first;
    }
    else
    {
        stParent = first;
        ndParent = second;
    }

    for (allele = crossoverPoint; allele < this->individualSize; ++allele)
    {
        stChild.push_back(individuals.at(stParent).at(allele));
        makeMutation(stChild, allele);

        ndChild.push_back(individuals.at(ndParent).at(allele));
        makeMutation(ndChild, allele);
    }


//    unsigned int* indiv = new unsigned int[this->individualSize]();
//    for (unsigned int allel = 0; allel < this->individualSize; ++ allel)
//    {
//        indiv[allel] = individuals.at(chromosome).at(allel);
//    }

    generation.push_back(stChild);
    generation.push_back(ndChild);

//    descendants.push_back(stChild);
//    descendants.push_back(ndChild);

    return generation;
}

void Population::addIndividual(vector<int> individual)
{
    individuals.push_back(individual);
}

vector<int> Population::getIndividual(unsigned int id)
{
    return individuals.at(id);
}


void Population::join()
{
    individuals.insert(end(individuals), begin(descendants), end(descendants));
}

void Population::shrink(int selecteds[])
{
    descendants.clear();

    for (unsigned int pos = 0; pos < this->threshold; ++pos)
    {
        descendants.push_back(individuals.at(selecteds[pos]));
    }

    individuals.clear();
    this->join();
}

unsigned int* Population::selectIndividual(unsigned int chromosome)
{
    unsigned int* indiv = new unsigned int[this->individualSize]();
    for (unsigned int allel = 0; allel < this->individualSize; ++ allel)
    {
        indiv[allel] = individuals.at(chromosome).at(allel);
    }

    return indiv;
}

int Population::getAllele(int individual, int position)
{
    return individuals.at(individual).at(position);
}

unsigned int Population::getIndividualSize()
{
    return this->individualSize;
}

unsigned int Population::getThreshold()
{
    return this->threshold;
}

unsigned int Population::getOffspringSize()
{
    return this->offspringSize;
}

int Population::getCurrentSize()
{
    return individuals.size();
}

void Population::show()
{
    for (unsigned int indiv = 0; indiv < individuals.size(); ++indiv)
    {
        for (unsigned int allele = 0; allele < this->individualSize; ++allele)
        {
            cout << individuals.at(indiv).at(allele) << " ";
        }

        cout << endl;
    }
}
void Population::showDescendants()
{
    for (unsigned int indiv = 0; indiv < descendants.size(); ++indiv)
    {
        for (unsigned int allele = 0; allele < this->individualSize; ++allele)
        {
            cout << descendants.at(indiv).at(allele) << " ";
        }

        cout << endl;
    }
}

