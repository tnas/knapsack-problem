#ifndef BINARY_POPULATION_H
#define BINARY_POPULATION_H

#include <Population.h>

#define DEFAULT_THRESHOLD 100

using namespace std;

class BinaryPopulation : public Population
{

    unsigned int offspringSize;
    float crossoverProbability;
    float mutationProbaility;

    public:
        BinaryPopulation()
        {
            this->offspringSize = DEFAULT_THRESHOLD;
            this->crossoverProbability = CROSSOVER_PROBABILITY;
            this->mutationProbaility = MUTATION_PROPABILITY;
            setThreshold(DEFAULT_THRESHOLD);
        }

        BinaryPopulation(unsigned int threshold, unsigned int offspringSize)
        {
            setThreshold(threshold);
            this->offspringSize = offspringSize;
        }

        virtual ~BinaryPopulation();
        vector<vector<int>> create(Knapsack knapsack);
        vector<vector<int>> reproduce(int first, int second);
        void addIndividual(vector<int> individual);
        void addIndividuals(vector<vector<int>> indivs);
        void shrink(int selecteds[]);
        void destroy();
        void setOffspringSize(int size);
        unsigned int getOffspringSize();
        int getAllele(int individual, int position);
        void show();
        void showIndividual(vector<int> indiv);
};

#endif // BINARY_POPULATION_H
