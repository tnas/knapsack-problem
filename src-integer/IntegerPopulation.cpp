#include "IntegerPopulation.h"
#include <iostream>
#include <algorithm>
#include <RandomHelper.h>

using namespace std;

static vector<vector<int>> individuals;
static Knapsack knapsackInstance;
static RandomHelper randomHelper;

IntegerPopulation::IntegerPopulation()
{
}

IntegerPopulation::~IntegerPopulation()
{
}

bool isItemInKnapsack(unsigned int item, vector<int> indiv)
{
    if (find(indiv.begin(), indiv.end(), item) != indiv.end())
        return true;
    else
        return false;
}

void equalizePopulation(vector<vector<int>>& generation, unsigned int limitSize)
{
    vector<vector<int>>::iterator it;

    for (it = generation.begin(); it != generation.end(); ++it)
    {
        while ((*it).size() > limitSize)
        {
            (*it).pop_back();
        }
    }
}

vector<vector<int>> Population::create(Knapsack knapsack)
{
    knapsackInstance = knapsack;
    unsigned int totalWeight;
    this->setIndividualSize(knapsack.getMaxNumberOfItens());
//    unsigned int lower = this->getIndividualSize();

    for (unsigned int nIndiv = 0; nIndiv < this->getThreshold(); ++nIndiv)
    {
        totalWeight = 0;
        vector<int> indiv;

        do
        {
            unsigned int item = randomHelper.getRandomBetweenZeroTo(this->getIndividualSize() - 1);

            if (!isItemInKnapsack(item, indiv))
            {
                totalWeight += knapsack.getItemWeight(item);

                if (totalWeight <= knapsack.getCapacity())
                {
                    indiv.push_back(item);
                }
            }
        } while (totalWeight <= knapsack.getCapacity());

//        if (indiv.size() < lower)
//            lower = indiv.size();

        individuals.push_back(indiv);
    }

    //cout << "lower: " << lower << endl;
    //equalizePopulation(firstGeneration, lower);

    return individuals;
}

unsigned int Population::getCurrentSize()
{
    return individuals.size();
}

vector<int> Population::getIndividual(unsigned int id)
{
    return individuals.at(id);
}

void Population::show(vector<vector<int>> generation)
{
    for (vector<int> indiv : generation)
    {
        for (int item : indiv)
        {
            cout << item << " ";
        }

        cout << endl;
    }
}
