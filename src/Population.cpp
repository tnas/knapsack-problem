#include "../include/Population.h"
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "../include/RandomHelper.h"

static vector<vector<int>> individuals;
static RandomHelper randomHelper;

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

vector<vector<int>> Population::create(int individualSize)
{
    this->individualSize = individualSize;
    vector<vector<int>> firstGeneration;

    for (unsigned int indiv = 0; indiv < this->threshold; ++indiv)
    {
        vector<int> individual;

        for (unsigned int allele = 0; allele < this->individualSize; ++allele)
        {
            individual.push_back(randomHelper.getRandomBetweenZeroTo(1));
        }

        firstGeneration.push_back(individual);
    }

    return firstGeneration;
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

    generation.push_back(stChild);
    generation.push_back(ndChild);

    return generation;
}

void Population::addIndividual(vector<int> individual)
{
    individuals.push_back(individual);
}

void Population::addIndividuals(vector<vector<int>>indivs)
{
    individuals.insert(end(individuals), begin(indivs), end(indivs));
}

vector<int> Population::getIndividual(unsigned int id)
{
    return individuals.at(id);
}

void Population::shrink(int selecteds[])
{
    vector<vector<int>> newGeneration;

    for (unsigned int pos = 0; pos < this->threshold; ++pos)
    {
        newGeneration.push_back(individuals.at(selecteds[pos]));
    }

    individuals.clear();
    this->addIndividuals(newGeneration);
}

void Population::destroy()
{
    individuals.clear();
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

void Population::showIndividual(vector<int> indiv)
{
    for (unsigned int pos = 0; pos < indiv.size(); ++pos)
    {
        cout << indiv.at(pos) << " ";
    }

    cout << endl;
}

void Population::show(vector<vector<int>> generation)
{
    for (unsigned int indiv = 0; indiv < generation.size(); ++indiv)
    {
        for (unsigned int allele = 0; allele < generation.at(0).size(); ++allele)
        {
            cout << generation.at(indiv).at(allele) << " ";
        }

        cout << endl;
    }
}

void Population::show()
{
    this->show(individuals);
}

