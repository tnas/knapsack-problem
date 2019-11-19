#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "Population.h"
#include <string.h>
#include <limits>

class Knapsack
{
    unsigned int capacity;
    unsigned int nShelves;
    unsigned int* shelvesCapacity;

    bool checkKnapsackIsFeasible(unsigned int* solution, unsigned int solSize);

    public:
        Knapsack();
        Knapsack(unsigned int capacity);
        Knapsack(unsigned int capacity, unsigned int nShelves, unsigned int* shelvesCapacity);
        ~Knapsack();
        bool isFeasible(unsigned int* instance, unsigned int size);
        bool isFeasible(vector<int> instance);
        unsigned int evaluateWeight(unsigned int* instance, unsigned int size);
        unsigned int evaluateValue(unsigned int* instance, unsigned int size);
        int getMaxNumberOfItens();
        int getItemWeight(int item);
        int getItemValue(int item);
        unsigned int getCapacity();
        unsigned int getMaximumWeight();
        void setCapacity(unsigned int capacity);

    protected:

};

#endif // KNAPSACK_H
