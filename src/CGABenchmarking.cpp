#include "CGABenchmarking.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

static string verboseFileName = "ag-verbose.txt";
static string compiledFileName = "ag-compiled.txt";
static vector<ExecutionReport> verboseExecutionHistory;
static vector<ExecutionReport> compiledExecutionHistory;
static vector<int> numberOfGenerations{ 10, 50, 100, 500, 1000 };
static vector<int> sizeOfPopulations{ 10, 50, 100, 500, 1000 };
static vector<InfeasiblesPolicy> policies{ InfeasiblesPolicy::Repair, InfeasiblesPolicy::Penalize };

CGABenchmarking::~CGABenchmarking()
{
}

void CGABenchmarking::setNumberOfExecutions(unsigned int executions)
{
    this->numberOfExecutions = executions;
}

string toString(InfeasiblesPolicy policy)
{
    switch (policy)
    {
    case Repair :
        return "Repair";
    case Penalize :
        return "Penalize";
    default :
        return "No identified policy";
    }
}

void compileReports(vector<ExecutionReport> reports)
{
    ExecutionReport bestExecution;
    bestExecution = reports.front();

    for (ExecutionReport report : reports)
    {
        if (report.getFitnessValue() > bestExecution.getFitnessValue())
            bestExecution = report;
    }

    compiledExecutionHistory.push_back(bestExecution);
}

void CGABenchmarking::run()
{
    vector<ExecutionReport> reports;

    for (InfeasiblesPolicy policy : policies)
    {
        for (unsigned int generations : numberOfGenerations)
        {
            for (unsigned int population : sizeOfPopulations)
            {
                reports = this->run(population, generations, policy);
                compileReports(reports);
                verboseExecutionHistory.insert(verboseExecutionHistory.end(),
                    begin(reports), end(reports));
            }
        }
    }
}

vector<ExecutionReport> CGABenchmarking::run(unsigned int populationSize,
    unsigned int numberOfGenerations, InfeasiblesPolicy policy)
{
    vector<ExecutionReport> reportsList;
    ExecutionReport report;

    this->canonicalGA.setGenerationsLimit(numberOfGenerations);
    this->canonicalGA.setPopulationSize(populationSize);
    this->canonicalGA.setInfeasiblesPolicy(policy);

    for (unsigned int exec = 0; exec < this->numberOfExecutions; ++exec)
    {
        report = this->canonicalGA.executeEvolution();
        report.setInfeasiblesPolicy(toString(policy));
        reportsList.push_back(report);
    }

    return reportsList;
}

void printHistory(string fileName, vector<ExecutionReport> reportsHistory)
{
    ofstream verboseFile(fileName);
    unsigned int exec = 0;

    if (verboseFile.is_open())
    {
        for (ExecutionReport report : reportsHistory)
        {
            verboseFile << "Execution [" << exec++ << "]" << endl;
            verboseFile << report.print();
            verboseFile << "-------------------------------------------" << endl;
        }

        verboseFile.close();
    }
    else
    {
        cout << "Unable to generate " << fileName << " execution file history." << endl;
    }
}

void CGABenchmarking::printFile()
{
    printHistory(verboseFileName, verboseExecutionHistory);
    printHistory(compiledFileName, compiledExecutionHistory);
}



