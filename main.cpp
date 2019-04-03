#include <iostream>
#include <ctype.h>
#include <unistd.h>
#include "include/CanonicalGA.h"
#include "include/Knapsack.h"
#include "include/BinaryPopulation.h"
#include "include/CGABenchmarking.h"
#include <IntegerGA.h>
#include <IntegerPopulation.h>


using namespace std;

/*
 * Compiler parameters: -Wall -fexceptions -g -std=c++14 -O3
 */
int main(int argc, char* argv[])
{
    int opt;
    unsigned int populationSize, generations;
    InfeasiblesPolicy infeasiblePolicy;
    ExecutionType executionType = ExecutionType::Benchmark;

    while ((opt = getopt(argc, argv, "bstg:p:i:")) != EOF)
    {
        switch(opt)
        {
            case 'b':
                executionType = ExecutionType::Benchmark;
                break;
            case 's':
                executionType = ExecutionType::Single;
                break;
            case 't':
                executionType = ExecutionType::Integer;
                break;
            case 'g':
                generations = atoi(optarg);
                break;
            case 'p':
                populationSize = atoi(optarg);
                break;
            case 'i':
                infeasiblePolicy = atoi(optarg) == InfeasiblesPolicy::Repair ?
                    InfeasiblesPolicy::Repair : InfeasiblesPolicy::Penalize;
                break;
            default:
                cout <<endl;
                abort();
        }
    }

    Knapsack knapsack;
    BinaryPopulation population;
    CanonicalGA canonicalGA(knapsack, population);

    if (executionType == ExecutionType::Benchmark)
    {
        CGABenchmarking cgaBenchmark(canonicalGA);
        cgaBenchmark.run();
    }
    else if (executionType == ExecutionType::Single)
    {
        canonicalGA.setGenerationsLimit(generations);
        canonicalGA.setPopulationSize(populationSize);
        canonicalGA.setInfeasiblesPolicy(infeasiblePolicy);
        ExecutionReport report = canonicalGA.executeEvolution();
        report.print();
    }
    else if (executionType == ExecutionType::Integer)
    {
        IntegerPopulation integerPopulation;
        IntegerGA integerGA(knapsack, integerPopulation);
        ExecutionReport report = integerGA.executeEvolution();
        report.print();
    }

    return 0;
}
