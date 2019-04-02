#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <Knapsack.h>

#define CROSSOVER_PROBABILITY 0.9
#define MUTATION_PROPABILITY  0.1

using namespace std;

class Population
{
    unsigned int individualSize;
    unsigned int threshold;

    public:
        Population();
        virtual ~Population();
        virtual vector<vector<int>> create(Knapsack knapsack);
        virtual void show(vector<vector<int>> generation);
        virtual unsigned int getCurrentSize();
        virtual vector<int> getIndividual(unsigned int id);

        void setIndividualSize(unsigned int size)
        {
            this->individualSize = size;
        }

        unsigned int getIndividualSize()
        {
            return this->individualSize;
        }

        void setThreshold(unsigned int size)
        {
            this->threshold = size;
        }

        unsigned int getThreshold()
        {
            return this->threshold;
        }
};

#endif // POPULATION_H
