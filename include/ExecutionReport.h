#ifndef EXECUTIONREPORT_H
#define EXECUTIONREPORT_H

#include <iostream>
#include <vector>
#include <string>
#include <config.h>
#include <Knapsack.h>

using namespace std;

class ExecutionReport
{
    unsigned int chromosomeSize;
    unsigned int numberOfAllelesOn;
    vector<int> chromosome;
    unsigned int numberOfGenerations;
    unsigned int sizeOfPopulation;
    string infeasiblesPolicy;
    Knapsack knapsack;

    public:
        ExecutionReport(): numberOfAllelesOn(0){};
        ExecutionReport(Knapsack knapsack, vector<int> chromosome);
        virtual ~ExecutionReport();
        unsigned int getFitnessValue();
        unsigned int getNumberOfGenerations();
        unsigned int getKnapsackWeight();
        unsigned int getNumberOfAllelesOn();
        unsigned int getChromosomeSize();
        unsigned int getPopulationSize();
        string getInfeasiblesPolicy();
        void setNumberOfGenerations(unsigned int numberOfGenerations);
        void setSizeOfPopulation(unsigned int populationSize);
        void setInfeasiblesPolicy(InfeasiblesPolicy policy);
        string print();
        string printInteger();
        void printCompactedFormat();
};

#endif // EXECUTIONREPORT_H
