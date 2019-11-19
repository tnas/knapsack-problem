#include "../include/Knapsack.h"

#define NUM_ITENS 20
#define DEFAULT_CAPACITY 510
#define DEFAULT_NUMBER_SHELVES 3
#define NO_SHELF 0
#define SHELF1_CAPACITY 240
#define SHELF2_CAPACITY 190
#define SHELF3_CAPACITY 170

int itensWeight[NUM_ITENS] = {
    20, 25, 14, 46, 39, 57, 58, 47, 38, 30,
    53, 57, 38, 53, 58, 48, 14, 6, 40, 10
};

int itensValue[NUM_ITENS] = {
    7, 7, 8, 3, 5, 8, 1, 4, 9, 7,
    10, 8, 7, 1, 7, 9, 3, 2, 4, 2
};

Knapsack::Knapsack()
{
    this->capacity = DEFAULT_CAPACITY;
    this->nShelves = DEFAULT_NUMBER_SHELVES + 1; // zero position to NO_SHELF
    this->shelvesCapacity = new unsigned int[this->nShelves]();
    this->shelvesCapacity[0] = NO_SHELF;
    this->shelvesCapacity[1] = SHELF1_CAPACITY;
    this->shelvesCapacity[2] = SHELF2_CAPACITY;
    this->shelvesCapacity[3] = SHELF3_CAPACITY;
}

Knapsack::Knapsack(unsigned int capacity)
{
    this->capacity = capacity;
    this->shelvesCapacity = nullptr;
}

Knapsack::Knapsack(unsigned int capacity, unsigned int nShelves, unsigned int* shelvesCapacity)
{
    this->capacity = capacity;
    this->nShelves = nShelves;
    this->shelvesCapacity = shelvesCapacity;
}

Knapsack::~Knapsack()
{
    if (this->shelvesCapacity != nullptr) delete(this->shelvesCapacity);
}

unsigned int Knapsack::evaluateWeight(unsigned int* instance, unsigned int size)
{
    unsigned int totalWeight = 0;
    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(instance, size, solution);

    for (unsigned int obj = 0; obj < solSize; ++obj)
    {
        if (solution[obj] != 0)
        {
            totalWeight += itensWeight[obj];
        }
    }

    delete(solution);

    return totalWeight;
}

unsigned int Knapsack::evaluateValue(unsigned int* instance, unsigned int size)
{
    unsigned int totalValue = 0;
    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(instance, size, solution);

    for (unsigned int pos = 0; pos < solSize; ++pos)
    {
        if (solution[pos] != 0) totalValue += itensValue[pos];
    }

    delete(solution);

    return totalValue;
}

void Knapsack::evaluateWeightValue(vector<int>instance, unsigned int& indivWeight,
                                   unsigned int& indivValue)
{
    unsigned int totalWeight, totalValue;
    totalWeight = totalValue = 0;
    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(instance, solution);

    for (unsigned int obj = 0; obj < solSize; ++obj)
    {
        if (solution[obj] != 0)
        {
            totalWeight += itensWeight[obj];
            totalValue += itensValue[obj];
        }
    }

    delete(solution);
}

void Knapsack::evaluateWeightValue(vector<int>instance, unsigned int& indivWeight,
                                   unsigned int& indivValue, unsigned int*& shelfWeight)
{
    unsigned int totalWeight, totalValue;
    totalWeight = totalValue = 0;
    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(instance, solution);

    memset(shelfWeight, 0, this->nShelves*sizeof(*shelfWeight));

    for (unsigned int obj = 0; obj < solSize; ++obj)
    {
        if (solution[obj] != 0)
        {
            totalWeight += itensWeight[obj];
            totalValue += itensValue[obj];
            shelfWeight[solution[obj]] += itensWeight[obj];
        }
    }

    delete(solution);
}

bool Knapsack::checkKnapsackIsFeasible(unsigned int* solution, unsigned int solSize)
{
    bool isFeasible = true;
    unsigned int totalWeight = 0;
    unsigned int* shelfWeight = new unsigned int[this->nShelves]();
    memset(shelfWeight, 0, this->nShelves*sizeof(*shelfWeight));

    for (unsigned int obj = 0; obj < solSize; ++obj)
    {
        if (solution[obj] != 0)
        {
            totalWeight += itensWeight[obj];
            shelfWeight[solution[obj]] += itensWeight[obj];
        }
    }

    if (totalWeight > this->capacity)
    {
        isFeasible = false;
    }
    else
    {
        for (unsigned int shelf = 1; shelf < this->nShelves; ++shelf)
        {
            if (shelfWeight[shelf] > this->shelvesCapacity[shelf])
            {
                isFeasible = false;
                break;
            }
        }
    }

    delete(solution);
    delete(shelfWeight);

    return isFeasible;
}

bool Knapsack::isFeasible(unsigned int* instance, unsigned int size)
{
    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(instance, size, solution);
    return checkKnapsackIsFeasible(solution, solSize);
}

bool Knapsack::isFeasible(vector<int>instance)
{
    unsigned int* solution = nullptr;
    unsigned int solSize = Population::individualToKnapsack(instance, solution);
    return checkKnapsackIsFeasible(solution, solSize);
}

unsigned int Knapsack::getMaximumWeight()
{
    unsigned int maxWeight = 0;

    for (unsigned int pos = 0; pos < NUM_ITENS; ++pos)
        maxWeight += itensWeight[pos];

    return maxWeight;
}

int Knapsack::getItemWeight(int item)
{
    return itensWeight[item];
}

int Knapsack::getItemValue(int item)
{
    return itensValue[item];
}

int Knapsack::getMaxNumberOfItens()
{
    return NUM_ITENS;
}

void Knapsack::setCapacity(unsigned int capacity)
{
    this->capacity = capacity;
}

unsigned int Knapsack::getCapacity()
{
    return this->capacity;
}

unsigned int Knapsack::getNumberOfShelves()
{
    return this->nShelves;
}

unsigned int* Knapsack::getShelvesCapacity()
{
    return this->shelvesCapacity;
}

