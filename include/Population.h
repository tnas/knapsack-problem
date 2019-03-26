#ifndef POPULATION_H
#define POPULATION_H

#include <vector>

#define CROSSOVER_PROBABILITY 0.8
#define MUTATION_PROPABILITY  0.05
#define DEFAULT_THRESHOLD 10

using namespace std;

class Population
{
    unsigned int threshold;
    unsigned int offspringSize;
    unsigned int individualSize;
    float crossoverProbability;
    float mutationProbaility;

    public:
        Population();
        Population(int threshold, int offspringSize);
        virtual ~Population();
        vector<vector<int>> create(int individualSize);
        vector<vector<int>> reproduce(int first, int second);
        void addIndividual(vector<int> individual);
        void addIndividuals(vector<vector<int>> indivs);
        vector<int> getIndividual(unsigned int id);
        void join();
        void shrink(int selecteds[]);
        unsigned int* selectIndividual(unsigned int chromosome);
        void setThreshold(int size);
        void setOffspringSize(int size);
        unsigned int getIndividualSize();
        unsigned int getOffspringSize();
        int getAllele(int individual, int position);
        unsigned int getThreshold();
        int getCurrentSize();
        void show();
        void show(vector<vector<int>> generation);
        void showIndividual(vector<int> indiv);
        void showDescendants();
};

#endif // POPULATION_H
