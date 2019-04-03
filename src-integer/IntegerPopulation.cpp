#include "IntegerPopulation.h"
#include <iostream>
#include <algorithm>
#include <RandomHelper.h>

using namespace std;

static vector<vector<int>> individuals;
static Knapsack knapsackInstance;
static RandomHelper randomHelper;

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

vector<vector<int>> IntegerPopulation::create(Knapsack knapsack)
{
    vector<vector<int>> firstGeneration;
    knapsackInstance = knapsack;
    unsigned int totalWeight;
    this->setIndividualSize(knapsack.getMaxNumberOfItens());

    for (unsigned int nIndiv = 0; nIndiv < getThreshold(); ++nIndiv)
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

        firstGeneration.push_back(indiv);
    }

    return firstGeneration;
}

void Population::makeMutation(vector<int> individual, int allele)
{
    if (randomHelper.getRandomBetween0and1() < MUTATION_PROPABILITY)
        individual.at(allele) ^= 1;
}

bool Population::isAlleleExchangeable()
{
    return randomHelper.getRandomBetween0and1() < CROSSOVER_PROBABILITY;
}

void makeRandomSwap(vector<int>& individual)
{
    unsigned int stPosition = randomHelper.getRandomBetweenZeroTo(individual.size() - 1);
    unsigned int ndPosition;

    do
    {
        ndPosition = randomHelper.getRandomBetweenZeroTo(individual.size() - 1);
    } while (ndPosition == stPosition);

    if (randomHelper.getRandomBetween0and1() < MUTATION_PROPABILITY)
    {
        unsigned int temp = individual.at(stPosition);
        individual.at(stPosition) = individual.at(ndPosition);
        individual.at(ndPosition) = temp;
    }
}

unsigned int runPMXMapping(vector<pmx_map> pmxOptions, unsigned int item)
{
    bool permuted = false;
    vector<pmx_map> updatedOptions;

    for (pmx_map option : pmxOptions)
    {
        if (option.from == item && !option.visited)
        {
            item = option.to;
            option.visited = true;
            permuted = true;
        }
        else if (option.to == item && !option.visited)
        {
            item = option.from;
            option.visited = true;
            permuted = true;
        }

        updatedOptions.push_back(option);
    }

    if (permuted)
    {
        runPMXMapping(updatedOptions, item);
    }

    return item;
}

vector<int> generatePMXChild(vector<int> stParent, vector<int> ndParent,
    vector<pmx_map> pmxOptions, unsigned int stCXBegin, unsigned int stCXEnd)
{
    vector<int> child(stParent);
    unsigned int allele, pmx;
    unsigned int stParentSize = stParent.size();
    unsigned int ndParentSize = ndParent.size();

    for (allele = 0; allele < stCXBegin; ++allele)
    {
        pmx = runPMXMapping(pmxOptions, stParent.at(allele));
        cout << "from: " << stParent.at(allele) << " -> to: " << pmx << endl;
        child.at(allele) = pmx;
    }

    for (allele = stCXBegin; allele <= stCXEnd; ++allele)
    {
        child.at(allele) = ndParent.at(allele % ndParentSize);
    }

    for (allele = stCXEnd + 1; allele < stParentSize; ++allele)
    {
        pmx = runPMXMapping(pmxOptions, stParent.at(allele));
        cout << "from: " << stParent.at(allele) << " -> to: " << pmx << endl;
        child.at(allele) = pmx;
    }

    return child;
}


vector<vector<int>> IntegerPopulation::reproduce(int first, int second)
{
    unsigned int stCXBegin, stCXEnd, ndCXBegin, ndCXEnd,
        stParentSize, ndParentSize, allele, temp;
    vector<pmx_map> pmxOptions;

    cout << "Population before reproduction: " << endl;
    show(individuals);

    if (getIndividual(first).size() > getIndividual(second).size())
    {
        temp = first;
        first = second;
        second = temp;
    }

    stParentSize  = getIndividual(first).size();
    ndParentSize  = getIndividual(second).size();

    cout << "stParent: " << first << " - ndParent: " << second << endl;
    showIndividual(getIndividual(first));
    showIndividual(getIndividual(second));

    stCXBegin = randomHelper.getRandomBetweenZeroTo(stParentSize - 1);

    do
    {
        stCXEnd = randomHelper.getRandomBetweenZeroTo(stParentSize - 1);
    } while (stCXEnd == stCXBegin);

    if (stCXBegin > stCXEnd)
    {
        temp = stCXBegin;
        stCXBegin = stCXEnd;
        stCXEnd = temp;
    }

    ndCXBegin = stCXBegin % ndParentSize;
    ndCXEnd   = stCXEnd % ndParentSize;

    cout << "Section [stB, stE, ndB, ndE] = " <<
        stCXBegin << stCXEnd << ndCXBegin << ndCXEnd << endl;

    vector<vector<int>> generation;
    vector<int> stParent = individuals.at(first);
    vector<int> ndParent = individuals.at(second);

    cout << "Section: " << endl;
    for (allele = stCXBegin; allele <= stCXEnd; ++allele)
    {
        pmx_map option;
        option.from = stParent.at(allele);
        option.to   = ndParent.at(allele % ndParentSize);
        option.visited = false;
        pmxOptions.push_back(option);
        cout << "[" << option.from << "," << option.to << "]" << endl;
    }

    vector<int> stChild = generatePMXChild(stParent, ndParent, pmxOptions,
        stCXBegin, stCXEnd);
    cout << "PMX child 1: " << endl;
    this->showIndividual(stChild);

    vector<int> ndChild = generatePMXChild(ndParent, stParent, pmxOptions,
        ndCXBegin, ndCXEnd);
    cout << "PMX child 2: " << endl;
    this->showIndividual(ndChild);

    makeRandomSwap(stChild);
    makeRandomSwap(ndChild);

    generation.push_back(stChild);
    generation.push_back(ndChild);

    return generation;
}

void Population::shrink(int selecteds[])
{
    vector<vector<int>> newGeneration;

    for (unsigned int pos = 0; pos < this->getThreshold(); ++pos)
    {
        newGeneration.push_back(individuals.at(selecteds[pos]));
    }

    individuals.clear();
    this->addIndividuals(newGeneration);
}


void Population::addIndividuals(vector<vector<int>>indivs)
{
    individuals.insert(end(individuals), begin(indivs), end(indivs));
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

void IntegerPopulation::showIndividual(vector<int> indiv)
{
    for (int item : indiv)
    {
        cout << item << " ";
    }

    cout << endl;
}
