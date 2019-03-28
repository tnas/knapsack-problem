#include "CGABenchmarking.h"

#include <string>

using namespace std;

//static unsigned int numberOfGenerations[] = { 10, 50, 100, 500, 1000 };
//static unsigned int sizeOfPopulations[] = { 10, 50, 100, 500, 1000 };

static list<ExecutionReport> reportsMemory;
static unsigned int numberOfGenerations[] = { 500 };
static unsigned int sizeOfPopulations[] = { 100 };
static InfeasiblesPolicy policies[] =
    { InfeasiblesPolicy::Repair, InfeasiblesPolicy::Penalize };

CGABenchmarking::~CGABenchmarking()
{
}

string toString(InfeasiblesPolicy policy)
{
    switch (policy)
    {
    case Repair :
        return "Repair";
    case Penalize :
        return "Penalize";
    }
}

void CGABenchmarking::setNumberOfExecutions(unsigned int executions)
{
    this->numberOfExecutions = executions;
}

void CGABenchmarking::run()
{
    ExecutionReport report;


    this->canonicalGA.setInfeasiblesPolicy(InfeasiblesPolicy::Repair);
}

list<ExecutionReport> CGABenchmarking::run(unsigned int numberOfGenerations,
                                           unsigned int populationSize,
                                           InfeasiblesPolicy policy)
{
    list<ExecutionReport> reportsList;
    ExecutionReport report;

    this->canonicalGA.setGenerationsLimit(numberOfGenerations);
    this->canonicalGA.setPopulationSize(populationSize);
    this->canonicalGA.setInfeasiblesPolicy(policy);

    for (unsigned int exec = 0; exec < this->numberOfExecutions; ++exec)
    {
        report = this->canonicalGA.executeEvolution();
        report.setNumberOfGenerations(numberOfGenerations);
        report.setSizeOfPopulation(populationSize);
        report.setInfeasiblesPolicy(toString(policy));
        reportsList.push_back(report);
    }

    return reportsList;
}



