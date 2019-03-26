#ifndef KNAPSACK_H
#define KNAPSACK_H

#define DEFAULT_CAPACITY 120

class Knapsack
{
    int capacity;

    public:
        Knapsack();
        Knapsack(int capacity);
        virtual ~Knapsack();
        int getMaxNumberOfItens();
        int getItemWeight(int item);
        int getItemValue(int item);
        void setCapacity(int capacity);

    protected:

};

#endif // KNAPSACK_H
