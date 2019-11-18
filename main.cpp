#include <iostream>
#include <ctype.h>
#include <unistd.h>
#include "include/CanonicalGA.h"
#include "include/Knapsack.h"
#include "include/Population.h"
#include "include/CGABenchmarking.h"

/*
 * Compiler parameters: -Wall -fexceptions -g -std=c++14 -O3
 */
int main(int argc, char* argv[])
{
    int opt;
    unsigned int populationSize, generations;
    InfeasiblesPolicy infeasiblePolicy;
    ExecutionType executionType;

    Knapsack knapsack;
    Population population;
    CanonicalGA canonicalGA(knapsack, population);

    while ((opt = getopt(argc, argv, "brg:p:i:")) != EOF)
    {
        switch(opt)
        {
            case 'b':
                executionType = ExecutionType::Benchmark;
                break;
            case 'r':
                executionType = ExecutionType::Single;
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

    if (executionType == ExecutionType::Benchmark)
    {
        CGABenchmarking cgaBenchmark(canonicalGA);
        cgaBenchmark.run();
    }
    else
    {
        canonicalGA.setGenerationsLimit(generations);
        canonicalGA.setPopulationSize(populationSize);
        canonicalGA.setInfeasiblesPolicy(infeasiblePolicy);
        ExecutionReport report = canonicalGA.executeEvolution();
        //report.print();
    }

    return 0;
}
