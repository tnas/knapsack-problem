#include <iostream>
#include "include/CanonicalGA.h"
#include "include/Knapsack.h"
#include "include/Population.h"
#include "include/CGABenchmarking.h"

using namespace std;

/*
 * Compiler parameters: -Wall -fexceptions -g -std=c++14
 */
int main()
{
    Knapsack knapsack;
    Population population;
    CanonicalGA canonicalGA(knapsack, population);

    CGABenchmarking cgaBenchmark(canonicalGA);
    cgaBenchmark.run();
    cgaBenchmark.printFile();

//    ExecutionReport report = canonicalGA.executeEvolution();
//    report.print();

    return 0;
}
