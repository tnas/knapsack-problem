#include "../include/Population.h"

unsigned int Population::individualToKnapsack(unsigned int* individual, unsigned int indivSize, unsigned int*& instance)
{

    unsigned int instanceSize = indivSize/2;
    instance = new unsigned int[instanceSize]();

    for (unsigned int pos = 0; pos < instanceSize; ++pos)
        instance[pos] = stoi(to_string(individual[2*pos]) +
                             to_string(individual[2*pos+1]), nullptr, 2);
    return instanceSize;
}

unsigned int Population::individualToKnapsack(vector<int> individual, unsigned int*& instance)
{
    unsigned int instanceSize = individual.size()/2;
    instance = new unsigned int[instanceSize]();

    for (unsigned int pos = 0; pos < instanceSize; ++pos)
        instance[pos] = stoi(to_string(individual.at(2*pos)) +
                             to_string(individual.at(2*pos+1)), nullptr, 2);
    return instanceSize;
}

void Population::defineAllelesAt(vector<int>& individual, unsigned int pos, int value)
{
    individual.at(2*pos) = individual.at(2*pos+1) = value;
}

Population::~Population()
{
}

void Population::setThreshold(int size)
{
    this->threshold = size;
}

void Population::setOffspringSize(int size)
{
    this->offspringSize = size;
}

/*
 The individual size is considered multiplied by 2
 because of its binary representation associated with
 the shelf it is allocated in. Then,
 00 -> individual is not in the any shelf
 01 -> individual is in the shelf 1
 10 -> individual is in the shelf 2
 11 -> individual is in the shelf 3
 */
void Population::create(unsigned int individualSize, vector<vector<int>>& generation)
{
    this->individualSize = individualSize * 2; // binary representation

    for (unsigned int indiv = 0; indiv < this->threshold; ++indiv)
    {
//        vector<int>* individual = new vector<int>();
        vector<int> individual(individualSize*2);

        for (unsigned int allele = 0; allele < individualSize; ++allele)
        {
            string binaryShelf = bitset<2>(this->randomHelper.getRandomBetweenZeroTo(3)).to_string();
            individual.at(2*allele)   = stoi(binaryShelf.substr(0,1));
            individual.at(2*allele+1) = stoi(binaryShelf.substr(1,1));
//            cout << "Indiv: " << indiv << " allele: " << allele << " --> str: " << binaryShelf
//            << " --> bits: " << individual.at(2*allele) << " - " << individual.at(2*allele+1) << endl;
        }

//        cout << "Before push_back: " << endl;
//        for (unsigned int allele = 0; allele < individualSize; ++allele)
//        {
//            cout << individual.at(2*allele) << individual.at(2*allele+1) << " ";
//        }
//        cout << endl;

        generation.push_back(individual);
//        delete(individual);
    }

//    cout << "Printing individuals: " << endl;
//    for (unsigned int indiv = 0; indiv < generation.size(); ++indiv)
//    {
//        for (unsigned int allele = 0; allele < this->individualSize/2; ++allele)
//        {
//            cout << generation[indiv][2*allele] << generation[indiv][2*allele+1] << " ";
//        }
//
//        cout << endl;
//    }
}

void Population::makeMutation(vector<int> individual, int allele)
{
    if (this->randomHelper.getRandomBetween0and1() < MUTATION_PROPABILITY)
        individual.at(allele) ^= 1;
}

bool Population::isAlleleExchangeable()
{
    return this->randomHelper.getRandomBetween0and1() < CROSSOVER_PROBABILITY;
}

vector<vector<int>> Population::reproduce(int first, int second)
{
    unsigned int crossoverPoint = randomHelper.getRandomBetweenZeroTo(this->individualSize);
    unsigned int allele, stParent, ndParent;

    vector<vector<int>> generation;
    vector<int> stChild, ndChild;

    for (allele = 0; allele < crossoverPoint; ++allele)
    {
        stChild.push_back(individuals.at(first).at(allele));
        makeMutation(stChild, allele);

        ndChild.push_back(individuals.at(second).at(allele));
        makeMutation(ndChild, allele);
    }

    if (isAlleleExchangeable())
    {
        stParent = second;
        ndParent = first;
    }
    else
    {
        stParent = first;
        ndParent = second;
    }

    for (allele = crossoverPoint; allele < this->individualSize; ++allele)
    {
        stChild.push_back(individuals.at(stParent).at(allele));
        makeMutation(stChild, allele);

        ndChild.push_back(individuals.at(ndParent).at(allele));
        makeMutation(ndChild, allele);
    }

    generation.push_back(stChild);
    generation.push_back(ndChild);

    return generation;
}

void Population::addIndividual(vector<int> individual)
{
    individuals.push_back(individual);
}

void Population::addIndividuals(vector<vector<int>>indivs)
{
    this->individuals.insert(end(individuals), begin(indivs), end(indivs));
}

vector<int> Population::getIndividual(unsigned int id)
{
    return this->individuals.at(id);
}

void Population::shrink(int selecteds[])
{
    vector<vector<int>> newGeneration;

    for (unsigned int pos = 0; pos < this->threshold; ++pos)
    {
        newGeneration.push_back(individuals.at(selecteds[pos]));
    }

    individuals.clear();
    this->addIndividuals(newGeneration);
}

void Population::destroy()
{
    this->individuals.clear();
}

int Population::getAllele(int individual, int position)
{
    return this->individuals.at(individual).at(position);
}

unsigned int Population::getIndividualSize()
{
    return this->individualSize;
}

unsigned int Population::getThreshold()
{
    return this->threshold;
}

unsigned int Population::getOffspringSize()
{
    return this->offspringSize;
}

int Population::getCurrentSize()
{
    return this->individuals.size();
}

void Population::showIndividual(vector<int> indiv)
{
    for (unsigned int allele = 0; allele < this->individualSize/2; ++allele)
    {
        string binaryIndiv = to_string(indiv[2*allele]) + to_string(indiv[2*allele+1]);
        cout << stoi(binaryIndiv, nullptr, 2) << " ";

//        cout << indiv[2*allele] << indiv[2*allele+1] << " ";
//        cout << str1 << str2 << " ";
    }

    cout << endl;
}

void Population::show(vector<vector<int>> generation)
{
    for (unsigned int indiv = 0; indiv < generation.size(); ++indiv)
        this->showIndividual(generation.at(indiv));
}


//void Population::show(vector<vector<int>> generation)
//{
//    for (unsigned int indiv = 0; indiv < generation.size(); ++indiv)
//    {
//        for (unsigned int allele = 0; allele < this->individualSize/2; ++allele)
//        {
//            cout << generation.at(indiv)[2*allele] << generation.at(indiv)[2*allele+1] << " ";
//        }
//
//        cout << endl;
//    }
//}

void Population::show()
{
    this->show(individuals);
}

