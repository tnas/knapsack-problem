#include "../include/Knapsack.h"

#define NUM_ITENS 42

int itensWeight[NUM_ITENS] = {
    3, 8, 12, 2, 8, 4, 4, 5, 1, 1, 8, 6, 4, 3, 3,
    5, 7, 3, 5, 7, 4, 3, 7, 2, 3, 5, 4, 3, 7, 19,
    20, 21, 11, 24, 13, 17, 18, 6, 15, 25, 12, 19
};

int itensValue[NUM_ITENS] = {
    1, 3, 1, 8, 9, 3, 2, 8, 5, 1, 1, 6, 3, 2, 5,
    2, 3, 8, 9, 3, 2, 4, 5, 4, 3, 1, 3, 2, 14, 32,
    20, 19, 15, 37, 18, 13, 19, 10, 15, 40, 17, 39
};

Knapsack::Knapsack()
{
    this->capacity = DEFAULT_CAPACITY;
}

Knapsack::Knapsack(unsigned int capacity)
{
    this->capacity = capacity;
}

Knapsack::~Knapsack()
{
}

unsigned int Knapsack::evaluateWeight(unsigned int* instance, unsigned int size)
{
    unsigned int totalWeight = 0;

    for (unsigned int pos = 0; pos < size; ++pos)
        totalWeight += instance[pos] * itensWeight[pos];

    return totalWeight;
}

unsigned int Knapsack::evaluateValue(unsigned int* instance, unsigned int size)
{
    unsigned int totalValue = 0;

    for (unsigned int pos = 0; pos < size; ++pos)
        totalValue += instance[pos] * itensValue[pos];

    return totalValue;
}

bool Knapsack::isFeasible(unsigned int* instance, unsigned int size)
{
    return evaluateWeight(instance, size) <= this->capacity;
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
