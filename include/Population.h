#ifndef POPULATION_H
#define POPULATION_H

#include "RandomHelper.h"
#include <vector>
#include <sstream>
#include <bitset>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#define CROSSOVER_PROBABILITY 0.95
#define MUTATION_PROPABILITY  0.3
#define DEFAULT_THRESHOLD 100

using namespace std;

class Population
{
    unsigned int threshold;
    unsigned int offspringSize;
    unsigned int individualSize;
    float crossoverProbability;
    float mutationProbaility;
    RandomHelper randomHelper;
    vector<vector<int>> individuals;

    void makeMutation(vector<int> individual, int allele);
    bool isAlleleExchangeable();

    public:

        static unsigned int individualToKnapsack(unsigned int* individual, unsigned int indivSize, unsigned int*& instance);
        static unsigned int individualToKnapsack(vector<int> individual, unsigned int*& instance);
        static void defineAllelesAt(vector<int>& individual, unsigned int pos, int value);

        Population(): threshold(DEFAULT_THRESHOLD), offspringSize(DEFAULT_THRESHOLD),
            crossoverProbability(CROSSOVER_PROBABILITY), mutationProbaility(MUTATION_PROPABILITY){};
        Population(int threshold, int offspringSize): threshold(threshold),
            offspringSize(offspringSize){};
        virtual ~Population();
        vector<vector<int>> create(unsigned int individualSize);
        vector<vector<int>> reproduce(int first, int second);
        void addIndividual(vector<int> individual);
        void addIndividuals(vector<vector<int>> indivs);
        void shrink(int selecteds[]);
        void destroy();
        vector<int> getIndividual(unsigned int id);
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
};

#endif // POPULATION_H
