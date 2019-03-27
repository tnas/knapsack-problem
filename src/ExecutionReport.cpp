#include "ExecutionReport.h"

ExecutionReport::ExecutionReport()
{
    this->numberOfAllelesOn = 0;
}

ExecutionReport::~ExecutionReport()
{
    delete(this->chromosome);
}

ExecutionReport::ExecutionReport(Knapsack knapsack, vector<int>chromosome)
{
    this->numberOfAllelesOn = 0;
    this->knapsack = knapsack;
    this->chromosome = new unsigned int[chromosome.size()];
    this->chromosomeSize = chromosome.size();

    for (unsigned int pos = 0; pos < this->chromosomeSize; ++pos)
    {
        this->chromosome[pos] = chromosome.at(pos);
        this->numberOfAllelesOn += this->chromosome[pos];
    }
}

unsigned int ExecutionReport::getFitnessValue()
{
    return this->knapsack.evaluateValue(this->chromosome, this->chromosomeSize);
}

unsigned int ExecutionReport::getNumberOfGenerations()
{
    return this->numberOfGenerations;
}

void ExecutionReport::setNumberOfGenerations(unsigned int numberOfGenerations)
{
    this->numberOfGenerations = numberOfGenerations;
}

unsigned int ExecutionReport::getKnapsackWeight()
{
    return this->knapsack.evaluateWeight(this->chromosome, this->chromosomeSize);
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
    cout << endl << "Fitness Value: " << this->getFitnessValue() << endl;
    cout << "Knapsack Weight: " << this->getKnapsackWeight() << endl;
    cout << "Number of Generations: " << this->numberOfGenerations << endl;
}

void ExecutionReport::printCompactedFormat()
{
    cout << this->getNumberOfAllelesOn() << ","
         << this->getKnapsackWeight() << ","
         << this->getFitnessValue();

    for (unsigned int pos = 0; pos < this->chromosomeSize;
        cout << "," << this->chromosome[pos++]);

    cout << endl;
}


