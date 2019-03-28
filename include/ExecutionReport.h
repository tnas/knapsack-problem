#ifndef EXECUTIONREPORT_H
#define EXECUTIONREPORT_H

#include <iostream>
#include <vector>
#include <string>
#include <Knapsack.h>

using namespace std;

class ExecutionReport
{
    unsigned int chromosomeSize;
    unsigned int numberOfAllelesOn;
    unsigned int* chromosome;
    unsigned int numberOfGenerations;
    unsigned int sizeOfPopulation;
    string infeasiblesPolicy;
    Knapsack knapsack;

    public:
        ExecutionReport();
        ExecutionReport(Knapsack knapsack, vector<int> chromosome);
        virtual ~ExecutionReport();
        unsigned int getFitnessValue();
        unsigned int getNumberOfGenerations();
        unsigned int getKnapsackWeight();
        unsigned int getNumberOfAllelesOn();
        unsigned int getPopulationSize();
        string getInfeasiblesPolicy();
        void setNumberOfGenerations(unsigned int numberOfGenerations);
        void setSizeOfPopulation(unsigned int populationSize);
        void setInfeasiblesPolicy(string policy);
        void print();
        void printCompactedFormat();
};

#endif // EXECUTIONREPORT_H
