#include "CGABenchmarking.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

static unsigned int execBests = 0;
static unsigned int execCompiled = 0;
static unsigned int execVerbose  = 0;
static string verboseFileNameRepair = "ag-verbose-repair.txt";
static string compiledFileNameRepair = "ag-compiled-repair.txt";
static string bestsFileNameRepair = "ag-bests-repair.txt";
static string verboseFileNamePenalty = "ag-verbose-penalty.txt";
static string compiledFileNamePenalty = "ag-compiled-penalty.txt";
static string bestsFileNamePenalty = "ag-bests-penalty.txt";
static vector<ExecutionReport> compiledExecutionHistory;
static vector<int> numberOfGenerations{ 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 };
static vector<int> sizeOfPopulations{ 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 };
static vector<InfeasiblesPolicy> policies{ InfeasiblesPolicy::Repair, InfeasiblesPolicy::Penalize };

CGABenchmarking::~CGABenchmarking()
{
}

void CGABenchmarking::setNumberOfExecutions(unsigned int executions)
{
    this->numberOfExecutions = executions;
}

void printHistory(string fileName, vector<ExecutionReport> reportsHistory)
{
    ofstream verboseFile(fileName, ios::app);
    unsigned int exec = fileName.find("verbose") != string::npos ? execVerbose :
        fileName.find("compiled") != string::npos ? execCompiled : execBests;

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

void compileReports(vector<ExecutionReport> reports, InfeasiblesPolicy policy)
{
    vector<ExecutionReport> bestInConfiguration;
    ExecutionReport bestExecution;
    bestExecution = reports.front();

    string compiledFileName = policy == InfeasiblesPolicy::Repair ?
            compiledFileNameRepair : compiledFileNamePenalty;


    for (ExecutionReport report : reports)
    {
        if (report.getFitnessValue() > bestExecution.getFitnessValue())
            bestExecution = report;
    }

    bestInConfiguration.push_back(bestExecution);
    printHistory(compiledFileName, bestInConfiguration);

    compiledExecutionHistory.push_back(bestExecution);
}


void bestCompiledReport(InfeasiblesPolicy policy)
{
    vector<ExecutionReport> bestCompiled;
    ExecutionReport bestExecution;

    string bestsFileName = policy == InfeasiblesPolicy::Repair ?
            bestsFileNameRepair : bestsFileNamePenalty;

    bestExecution = compiledExecutionHistory.front();

    for (ExecutionReport report : compiledExecutionHistory)
    {
        if (report.getFitnessValue() > bestExecution.getFitnessValue())
            bestExecution = report;
    }

    bestCompiled.push_back(bestExecution);
    printHistory(bestsFileName, bestCompiled);

    compiledExecutionHistory.clear();
}


void CGABenchmarking::run()
{
    vector<ExecutionReport> reports;
    string verboseFileName, bestsFileName;

    for (InfeasiblesPolicy policy : policies)
    {
        if (policy == InfeasiblesPolicy::Repair)
        {
            verboseFileName = verboseFileNameRepair;
            bestsFileName   = bestsFileNameRepair;
        }
        else
        {
            verboseFileName = verboseFileNamePenalty;
            bestsFileName   = bestsFileNamePenalty;
        }

        for (unsigned int generations : numberOfGenerations)
        {
            for (unsigned int population : sizeOfPopulations)
            {
                reports = this->run(population, generations, policy);
                compileReports(reports, policy);
                printHistory(verboseFileName, reports);
            }

            bestCompiledReport(policy);
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
        report.setInfeasiblesPolicy(policy);
        reportsList.push_back(report);
    }

    return reportsList;
}


