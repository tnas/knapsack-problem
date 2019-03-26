#include "../include/CanonicalGA.h"
#include <RandomGeneratorHelper.h>
#include <iostream>
#include <vector>

using namespace std;

static vector<Fitness> fitnessStatus;
static RandomGeneratorHelper randomHelper;
static ExecutionReport report;

CanonicalGA::CanonicalGA()
{
    this->generationsLimit = MAX_GENERATIONS;
}

CanonicalGA::CanonicalGA(Knapsack knapsack, Population population, InfeasiblesPolicy infeasiblesPolicy)
{
    this->knapsack = knapsack;
    this->population = population;
    this->infeasiblesPolicy = infeasiblesPolicy;
}

CanonicalGA::~CanonicalGA()
{
    fitnessStatus.clear();
}

void evaluateFitnessOld(Population population, Knapsack knapsack)
{
    fitnessStatus.clear();
    int populationSize = population.getCurrentSize();
    unsigned int value;

    for (int indiv = 0; indiv < populationSize; ++indiv)
    {
        value = 0;

        for (unsigned int item = 0; item < population.getIndividualSize(); ++item)
        {

            value += knapsack.getItemValue(item) *
                population.getAllele(indiv, item);
        }

        fitnessStatus.push_back(Fitness(indiv, value));
    }
}

void evaluateFitness(Population population, Knapsack knapsack)
{
    fitnessStatus.clear();
    int populationSize = population.getCurrentSize();
    unsigned int value, weight;
    unsigned int instanceSize = population.getIndividualSize();

    unsigned int* instance = new unsigned int[instanceSize]();

    for (int indiv = 0; indiv < populationSize; ++indiv)
    {
        for (unsigned int item = 0; item < population.getIndividualSize(); ++item)
        {
            instance[item] = population.getIndividual(indiv).at(item);
        }

        value  = knapsack.evaluateValue(instance, instanceSize);
        weight = knapsack.evaluateWeight(instance, instanceSize);
        fitnessStatus.push_back(Fitness(indiv, value, weight));
    }

    delete(instance);
}

void printFitness(Population population)
{
    for (Fitness fit : fitnessStatus)
    {
        cout << "Chromosome: " << fit.getId() <<
        " Value: " << fit.getValue() << endl;
    }
}

int runRouletteWhellSelection()
{
    double normFitness[fitnessStatus.size()];
    double factor, sum;
    unsigned int pos;

    factor = randomHelper.getRandomBetween0and1();

    sum = 0;
    for (Fitness fit : fitnessStatus)
         sum += fit.getValue();
    //cout << "Sum: " << sum << " Factor: " << factor << endl;

    pos = 0;
    for (Fitness fit : fitnessStatus)
    {
        normFitness[pos++] = fit.getValue()/sum;
        //cout << "Original value: " << fit.getValue() << " -- Normalized: " << normFitness[pos-1] << endl;
    }


    int ithIndiv = 0;
    sum = normFitness[0];
    //cout << "Sum: " << sum << " ithIndiv: " << ithIndiv << endl;

    while (sum < factor)
    {
        ++ithIndiv;
        sum += normFitness[ithIndiv];
        //cout << "Sum: " << sum << " ithIndiv: " << ithIndiv << endl;
    }

    return ithIndiv;
}

bool isKnapsackFeasible(vector<int> indiv, Knapsack knapsack)
{
    bool isFeasible = false;
    unsigned int instanceSize = indiv.size();

    unsigned int* instance = new unsigned int[instanceSize]();
    for (unsigned int pos = 0; pos < instanceSize; ++ pos)
    {
        instance[pos] = indiv.at(pos);
    }

    isFeasible = knapsack.isFeasible(instance, instanceSize);

    delete(instance);

    return isFeasible;
}

void CanonicalGA::moderateGeneration(vector<vector<int>> &generation)
{
    vector<vector<int>>::iterator it;

    if (this->infeasiblesPolicy == InfeasiblesPolicy::Repair)
    {
        for (it = generation.begin(); it != generation.end(); ++it)
        {
            if (!isKnapsackFeasible(*it, this->knapsack))
            {
                //cout << "Individual is not feasible!" << endl;
                this->repairInfeasibleIndividual(*it);
            }
        }
    }
    else
    {

    }
}

void CanonicalGA::repairInfeasibleIndividual(vector<int> &indiv)
{
    vector<int>::iterator it;
    vector<Fitness> allelesEvaluation;
    unsigned int pos, value, weight, totalWeight;

    //cout << "Before reparing: ";
    //this->population.showIndividual(indiv);

    pos = totalWeight = 0;

    for (it = indiv.begin(); it != indiv.end(); ++it)
    {
        int allele = *it;

        if (allele == 0)
        {
            value = weight = 0;
        }
        else
        {
            value  = this->knapsack.getItemValue(pos);
            weight = this->knapsack.getItemWeight(pos);
        }

        totalWeight += weight;
        allelesEvaluation.push_back(Fitness(pos, value, weight));
        ++pos;
    }

    sort(fitnessStatus.begin(), fitnessStatus.end());

    for (vector<Fitness>::iterator itFit = allelesEvaluation.begin();
         itFit != allelesEvaluation.end() && totalWeight > this->knapsack.getCapacity();
         ++itFit)
    {
        Fitness alleleFit = *itFit;
        if (alleleFit.getValue() == 0) continue;

        indiv.at(alleleFit.getId()) = 0;
        totalWeight -= alleleFit.getWeight();
    }

    //cout << "After reparing: ";
    //this->population.showIndividual(indiv);
}

void CanonicalGA::penalizeInfeasibleIndividual(vector<int> indiv)
{

}

ExecutionReport CanonicalGA::executeEvolution()
{
    vector<vector<int>> generation;
    vector<vector<int>>::iterator itChild;
    generation = this->population.create(this->knapsack.getMaxNumberOfItens());

//    this->population.setThreshold(3);
//    generation = this->population.create(5);
//
//    cout << "Original Population: " << endl;
//    this->population.show(generation);

    this->moderateGeneration(generation);
    this->population.addIndividuals(generation);

//    cout << "Repaired Population: " << endl;
//    this->population.show();

    evaluateFitness(this->population, this->knapsack);

//    cout << "Fitness: " << endl;
//    printFitness(this->population);

    int generationNumber = 0;
    int stIndiv, ndIndiv;
    int selecteds[this->population.getThreshold()];

    unsigned int* bestChromosome;
    unsigned int bestFitnessValue = 0;
    Fitness bestFromGeneration;

    while (generationNumber < MAX_GENERATIONS)
    {
        //cout << "runRouletteWhellSelection" << endl;
        generation.clear();

        for (unsigned int select = 0; select < this->population.getOffspringSize(); select+=2)
        {
            do
            {
                stIndiv = runRouletteWhellSelection();
                ndIndiv = runRouletteWhellSelection();
            } while (stIndiv == ndIndiv);

            //cout << "st: " << stIndiv << " nd: " << ndIndiv << endl;
            generation = this->population.reproduce(stIndiv, ndIndiv);
            this->moderateGeneration(generation);
            this->population.addIndividuals(generation);

            while (!generation.empty())
            {
                vector<int> child = generation.back();
                generation.pop_back();

                if (isKnapsackFeasible(child, this->knapsack))
                {
                    this->population.addIndividual(child);
                }
                else
                {
                    //cout << "Child is not feasible!" << endl;
                }
            }
        }

        //cout << "Descendants: " << endl;
        //this->population.showDescendants();

        //this->population.join();

        evaluateFitness(this->population, this->knapsack);
        //cout << "Fitness: " << endl;
        //printFitness(this->population);

        sort(fitnessStatus.begin(), fitnessStatus.end(), greater<Fitness>());

        //cout << "Sorted Fitness: " << endl;
        //printFitness(this->population);

        //cout << "Selected chromosomes: " << endl;
        unsigned int pos = 0;
        vector<Fitness>::iterator it;
        for (it = fitnessStatus.begin();
            it != fitnessStatus.end() && pos < this->population.getThreshold(); ++it)
        {
            selecteds[pos++] = it->getId();
            //cout << "Chrome: " << it->getChromosome() << " Val: " << it->getValue() << endl;
        }
        fitnessStatus.erase(it, fitnessStatus.end());

        //cout << "Fitness after shrinking population: " << endl;
        //printFitness(this->population);

        bestFromGeneration = fitnessStatus.at(0);

        if (bestFromGeneration.getValue() > bestFitnessValue)
        {
            bestChromosome = this->population.selectIndividual(bestFromGeneration.getId());
            bestFitnessValue = bestFromGeneration.getValue();
        }

        this->population.shrink(selecteds);
        //cout << "Shrinked Population: " << endl;
        //this->population.show();

        //this->population.showDescendants();
        //cout << "generation " << generation << endl;
        ++generationNumber;
    }

    report.setChromosome(bestChromosome, this->population.getIndividualSize());
    report.setFitnessValue(bestFitnessValue);
    report.setKnapsackWeight(this->knapsack.evaluateWeight(bestChromosome,
        this->population.getIndividualSize()));
    report.setNumberOfGenerations(generationNumber);

    return report;
}

void CanonicalGA::setKnapsack(Knapsack knapsack)
{
    this->knapsack = knapsack;
}

void CanonicalGA::setPopulation(Population population)
{
    this->population = population;
}

void CanonicalGA::setGenerationsLimit(int limit)
{
    this->generationsLimit = limit;
}
