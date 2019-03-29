#include "ExecutionReport.h"

ExecutionReport::ExecutionReport(Knapsack knapsack, vector<int> chromosome)
{
    this->numberOfAllelesOn = 0;
    this->knapsack = knapsack;
    this->chromosome = chromosome;
    this->chromosomeSize = chromosome.size();

    for (int allele : chromosome)
    {
        this->numberOfAllelesOn += allele;
    }
}

ExecutionReport::~ExecutionReport()
{
}

unsigned int* getKnapsackInstance(vector<int> chromosome)
{
    unsigned int instanceSize = chromosome.size();
    unsigned int* instance = new unsigned int[instanceSize];

    for (unsigned int pos = 0; pos < instanceSize; ++pos)
    {
        instance[pos] = chromosome.at(pos);
    }

    return instance;
}

unsigned int ExecutionReport::getFitnessValue()
{
    unsigned int value;
    unsigned int* instance = getKnapsackInstance(this->chromosome);
    value = this->knapsack.evaluateValue(instance, this->chromosomeSize);
    delete instance;

    return value;
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
    unsigned int value;
    unsigned int* instance = getKnapsackInstance(this->chromosome);
    value = this->knapsack.evaluateWeight(instance, this->chromosomeSize);
    delete instance;

    return value;

}

unsigned int ExecutionReport::getNumberOfAllelesOn()
{
    return this->numberOfAllelesOn;
}

unsigned int ExecutionReport::getPopulationSize()
{
    return this->sizeOfPopulation;
}

void ExecutionReport::setSizeOfPopulation(unsigned int populationSize)
{
    this->sizeOfPopulation = populationSize;
}

string ExecutionReport::getInfeasiblesPolicy()
{
    return this->infeasiblesPolicy;
}

void ExecutionReport::setInfeasiblesPolicy(string policy)
{
    this->infeasiblesPolicy = policy;
}

string ExecutionReport::print()
{
    string output;

    output.append(string("["));
    output.append(string("Infeasibles Policy: "));
    output.append(this->infeasiblesPolicy);
    output.append(string(", "));

    output.append(string("Number of Generations: "));
    output.append(string(to_string(this->numberOfGenerations)));
    output.append(string(", "));

    output.append(string("Population Size: "));
    output.append(string(to_string(this->sizeOfPopulation)));
    output.append(string("]\n"));

    output.append(string("Best Chromosome: "));
    for (unsigned int pos = 0; pos < this->chromosomeSize; ++pos)
    {
        output.append(string(to_string(this->chromosome[pos])));
        output.append(string(" "));
    }

    output.append(string("Fitness Value: "));
    output.append(string(to_string(this->getFitnessValue())));
    output.append(string("\n"));

    output.append(string("Knapsack Weight: "));
    output.append(string(to_string(this->getKnapsackWeight())));
    output.append(string("\n"));

    output.append(string("Number of Itens: "));
    output.append(string(to_string(this->numberOfAllelesOn)));
    output.append(string("\n"));

    cout << output;

    return output;
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


