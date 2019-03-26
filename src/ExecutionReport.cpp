#include "ExecutionReport.h"
#include <iostream>

using namespace std;

ExecutionReport::ExecutionReport()
{
    this->numberOfAllelesOn = 0;
}

ExecutionReport::~ExecutionReport()
{
}

void ExecutionReport::setChromosome(unsigned int* chromosome, unsigned int size)
{
    this->chromosome = chromosome;
    this->chromosomeSize = size;

    for (unsigned int pos = 0; pos < size; ++pos)
        this->numberOfAllelesOn += this->chromosome[pos];
}

unsigned int* ExecutionReport::getChromosome()
{
    return this->chromosome;
}

unsigned int ExecutionReport::getFitnessValue()
{
    return this->fitnessValue;
}

unsigned int ExecutionReport::getNumberOfGenerations()
{
    return this->numberOfGenerations;
}

void ExecutionReport::setFitnessValue(unsigned int fitnessValue)
{
    this->fitnessValue = fitnessValue;
}

void ExecutionReport::setNumberOfGenerations(unsigned int numberOfGenerations)
{
    this->numberOfGenerations = numberOfGenerations;
}

unsigned int ExecutionReport::getKnapsackWeight()
{
    return this->knapsackWeight;
}

void ExecutionReport::setKnapsackWeight(unsigned int weight)
{
    this->knapsackWeight = weight;
}

unsigned int ExecutionReport::getNumberOfAllelesOn()
{
    return this->numberOfAllelesOn;
}

void ExecutionReport::print()
{
    cout << "Best Chromosome:" << endl;
    for (unsigned int pos = 0; pos < this->chromosomeSize; ++pos)
    {
        cout << this->chromosome[pos] << " ";
    }
    cout << endl << "Fitness Value: " << this->fitnessValue << endl;
    cout << "Knapsack Weight: " << this->knapsackWeight << endl;
    cout << "Number of Generations: " << this->numberOfGenerations << endl;
}

void ExecutionReport::printCompactedFormat()
{
    cout << this->getNumberOfAllelesOn() << ","
         << this->knapsackWeight << ","
         << this->fitnessValue;

    for (unsigned int pos = 0; pos < this->chromosomeSize;
        cout << "," << this->chromosome[pos++]);

    cout << endl;
}


