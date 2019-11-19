#include "ExecutionReport.h"

ExecutionReport::ExecutionReport(Knapsack knapsack, vector<int> chromosome)
{
    this->numberOfAllelesOn = 0;
    this->knapsack = knapsack;
    this->chromosome = chromosome;
    this->chromosomeSize = chromosome.size();

    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(this->chromosome, solution);

    for (unsigned int obj = 0; obj < solSize; ++obj)
    {
        if (solution[obj] != 0)
        {
            ++this->numberOfAllelesOn;
        }
    }

    delete(solution);
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

void ExecutionReport::setInfeasiblesPolicy(InfeasiblesPolicy policy)
{
    switch (policy)
    {
    case Repair :
        this->infeasiblesPolicy = "Repair";
        return;
    case Penalize :
        this->infeasiblesPolicy = "Penalize";
        return;
    default :
        this->infeasiblesPolicy = "No Identified";
    }
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

    output.append(string("\nFitness Value: "));
    output.append(string(to_string(this->getFitnessValue())));
    output.append(string("\n"));

    output.append(string("Knapsack Weight: "));
    output.append(string(to_string(this->getKnapsackWeight())));
    output.append(string("\n"));

    output.append(string("Number of Items: "));
    output.append(string(to_string(this->numberOfAllelesOn)));
    output.append(string("\n"));

    output.append("--------------------------------\n");
    output.append("Solution Details:\n");
    output.append(this->getShelvesDetails());

    cout << output;

    return output;
}

string ExecutionReport::getShelvesDetails()
{
    string output;

    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(this->chromosome, solution);

    unsigned int nShelves = this->knapsack.getNumberOfShelves();
    string* shelves = new string[nShelves];
    unsigned int* shelvesWeight = new unsigned[nShelves];
    unsigned int* shelvesValue = new unsigned[nShelves];

    memset(shelvesWeight, 0, nShelves*sizeof(*shelvesWeight));
    memset(shelvesValue, 0, nShelves*sizeof(*shelvesValue));

    for (unsigned int obj = 0; obj < solSize; ++obj)
    {
        if (solution[obj] != 0)
        {
            shelves[solution[obj]].append(string(to_string(obj + 1)) + " ");
            shelvesWeight[solution[obj]] += this->knapsack.getItemWeight(obj);
            shelvesValue[solution[obj]] += this->knapsack.getItemValue(obj);
        }
    }

    for (unsigned int shelf = 1; shelf < nShelves; ++shelf)
    {
        output.append("Compartment " + to_string(shelf) + " - ");
        output.append("Weight: " + to_string(shelvesWeight[shelf]) + " - " +
                      "Value: " + to_string(shelvesValue[shelf]) + "\n");
        output.append("Items: " + shelves[shelf] + "\n");
    }

    delete(solution);
    delete(shelves);
    delete(shelvesWeight);
    delete(shelvesValue);

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


