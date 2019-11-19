#include "../include/CanonicalGA.h"

CanonicalGA::~CanonicalGA()
{
    fitnessStatus.clear();
}

void CanonicalGA::runFitnessEvaluation()
{
    fitnessStatus.clear();
    int populationSize = this->population.getCurrentSize();
    unsigned weight, value;
    vector<int> individual;

    for (int indiv = 0; indiv < populationSize; ++indiv)
    {
        individual = this->population.getIndividual(indiv);
        this->knapsack.evaluateWeightValue(individual, weight, value);

        if (this->infeasiblesPolicy == InfeasiblesPolicy::Penalize &&
            (!this->knapsack.isFeasible(individual)))
        {
            value -= this->penalizeInfeasibleIndividual(individual);
            value = value >= 0 ? value : 0;
        }

        fitnessStatus.push_back(Fitness(indiv, value, weight));
    }
}

void CanonicalGA::printFitness(Population population)
{
    for (Fitness fit : this->fitnessStatus)
    {
        cout << "Chromosome: " << fit.getId() <<
        " Value: " << fit.getValue() << endl;
    }
}

int CanonicalGA::runRouletteWhellSelection()
{
    double normFitness[this->fitnessStatus.size()];
    double factor, sum;
    unsigned int pos;

    factor = this->randomHelper.getRandomBetween0and1();

    sum = 0;
    for (Fitness fit : fitnessStatus)
         sum += fit.getValue();

    pos = 0;
    for (Fitness fit : fitnessStatus)
    {
        normFitness[pos++] = fit.getValue()/sum;
    }

    int ithIndiv = 0;
    sum = normFitness[0];

    while (sum < factor)
    {
        ++ithIndiv;
        sum += normFitness[ithIndiv];
    }

    return ithIndiv;
}

void CanonicalGA::moderateGeneration(vector<vector<int>>& generation)
{
    vector<vector<int>>::iterator it;

    if (this->infeasiblesPolicy == InfeasiblesPolicy::Repair)
    {
        for (it = generation.begin(); it != generation.end(); ++it)
        {
            if (!this->knapsack.isFeasible(*it))
            {
                cout << "Infeasible!!!" << endl << "Before repairing: ";
                this->population.showIndividual(*it);
                this->repairInfeasibleIndividual(*it);
                cout << endl << "After repairing: ";
                this->population.showIndividual(*it);
                cout << endl;
            }
        }
    }
}

void CanonicalGA::repairInfeasibleIndividual(vector<int>& indiv)
{
    vector<int>::iterator it;
    vector<Fitness> allelesEvaluation;
    unsigned int pos, value, weight, totalWeight;

    pos = totalWeight = 0;

    for (it = indiv.begin(); it != indiv.end(); ++it)
    {
        int stAllele = *it;
        int ndAllele = *(++it);

        if (stAllele == 0 && ndAllele == 0)
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

        Population::defineAllelesAt(indiv, alleleFit.getId(), 0);
        totalWeight -= alleleFit.getWeight();
    }
}

unsigned int CanonicalGA::penalizeInfeasibleIndividual(vector<int> indiv)
{
    unsigned int indivWeight, indivValue, nShelves;
    nShelves = this->knapsack.getNumberOfShelves();
    unsigned int* shelfWeight = new unsigned int[nShelves]();
    this->knapsack.evaluateWeightValue(indiv, indivWeight, indivValue, shelfWeight);

    double fIndivWeight = indivWeight;
    double fIndivValue = indivValue;
    double fCapacity = this->knapsack.getCapacity();
    double normPenaltyFactor = 0;

    if (fIndivWeight <= fCapacity)
    {
        fCapacity = fIndivWeight = 0;

        for (unsigned int shelf = 1; shelf < nShelves; ++shelf)
        {
            if (shelfWeight[shelf] > this->knapsack.getShelvesCapacity()[shelf])
            {
                fCapacity += this->knapsack.getShelvesCapacity()[shelf];
                fIndivWeight += shelfWeight[shelf];
            }
        }
    }

    delete(shelfWeight);
    normPenaltyFactor = ((double)(fCapacity/(fIndivWeight + fCapacity)));

    return trunc(fIndivValue - (normPenaltyFactor * fIndivValue));
}

ExecutionReport CanonicalGA::executeEvolution()
{
    this->reset();

    vector<vector<int>> generation;
    vector<vector<int>>::iterator itChild;

    generation = this->population.create(this->knapsack.getMaxNumberOfItens());
    this->moderateGeneration(generation); // avoiding infeasibilities
    this->population.addIndividuals(generation);
    this->runFitnessEvaluation();

    unsigned int generationNumber = 0;
    int stIndiv, ndIndiv;
    int selecteds[this->population.getThreshold()];
    unsigned int pos;
    vector<int> bestChromosome;
    unsigned int bestFitnessValue = 0;
    Fitness bestFromGeneration;

    while (generationNumber < this->generationsLimit)
    {
        generation.clear();

        for (unsigned int select = 0; select < this->population.getOffspringSize(); select+=2)
        {
            do
            {
                stIndiv = runRouletteWhellSelection();
                ndIndiv = runRouletteWhellSelection();
            } while (stIndiv == ndIndiv);

            generation = this->population.reproduce(stIndiv, ndIndiv);
            this->moderateGeneration(generation); // avoiding infeasibilities
            this->population.addIndividuals(generation);
        }

        this->runFitnessEvaluation();
        sort(fitnessStatus.begin(), fitnessStatus.end(), greater<Fitness>());

        pos = 0;
        vector<Fitness>::iterator it;
        for (it = fitnessStatus.begin();
            it != fitnessStatus.end() && pos < this->population.getThreshold(); ++it)
        {
            selecteds[pos++] = it->getId();
        }
        fitnessStatus.erase(it, fitnessStatus.end());

        bestFromGeneration = fitnessStatus.at(0);

        if (bestFromGeneration.getValue() > bestFitnessValue)
        {
            bestChromosome = this->population.getIndividual(bestFromGeneration.getId());
            bestFitnessValue = bestFromGeneration.getValue();
        }

        this->population.shrink(selecteds);

        ++generationNumber;
    }

    ExecutionReport report(this->knapsack, bestChromosome);
    report.setNumberOfGenerations(generationNumber);
    report.setSizeOfPopulation(this->population.getThreshold());
    report.setInfeasiblesPolicy(this->infeasiblesPolicy);

    return report;
}

void CanonicalGA::reset()
{
    this->population.destroy();
    fitnessStatus.clear();
}

void CanonicalGA::setInfeasiblesPolicy(InfeasiblesPolicy policy)
{
    this->infeasiblesPolicy = policy;
}

void CanonicalGA::setGenerationsLimit(unsigned int limit)
{
    this->generationsLimit = limit;
}

void CanonicalGA::setPopulationSize(unsigned int size)
{
    this->population.setThreshold(size);
}

