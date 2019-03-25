#include <iostream>
#include "include/AGCanonico.h"
#include "include/Knapsack.h"
#include "include/Population.h"

using namespace std;

/*
 * Compiler parameters: -Wall -fexceptions -g -std=c++14
 */
int main()
{
    Knapsack knapsack;
    Population population;
    AGCanonico agCanonico(knapsack, population);

    agCanonico.executeEvolution();

    cout << "Hello world!" << endl;

    return 0;
}
