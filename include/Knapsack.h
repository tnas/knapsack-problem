#ifndef KNAPSACK_H
#define KNAPSACK_H

#define DEFAULT_CAPACITY 120

class Knapsack
{
    unsigned int capacity;

    public:
        Knapsack();
        Knapsack(unsigned int capacity);
        virtual ~Knapsack();
        bool isFeasible(unsigned int* instance, unsigned int size);
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
