#include "ExecutionReport.h"
#include <iostream>

using namespace std;

ExecutionReport::ExecutionReport()
{
}

ExecutionReport::~ExecutionReport()
{
}

void ExecutionReport::setChromosome(unsigned int* chromosome, unsigned int size)
{
    this->chromosome = chromosome;
    this->chromosomeSize = size;
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

void ExecutionReport::print()
{
    cout << "Best Chromosome:" << endl;
    for (unsigned int pos = 0; pos < this->chromosomeSize; ++pos)
    {
        cout << this->chromosome[pos] << " ";
    }
    cout << endl << "Fitness Value: " << this->fitnessValue << endl;
    cout << "Number of Generations: " << this->numberOfGenerations << endl;
}

