#ifndef INTEGERPOPULATION_H
#define INTEGERPOPULATION_H

#include <Population.h>

typedef struct
{
    unsigned int from;
    unsigned int to;
    bool visited;
} pmx_map;

class IntegerPopulation : public Population
{
    public:
        IntegerPopulation();
        virtual ~IntegerPopulation();
        vector<vector<int>> create(Knapsack knapsack);
        vector<vector<int>> reproduce(int first, int second);
//        void addIndividuals(vector<vector<int>> indivs);
//        void makeMutation(vector<int> individual, int allele);
//        bool isAlleleExchangeable();
};

#endif // INTEGERPOPULATION_H
