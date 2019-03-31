#ifndef CGABENCHMARKING_H
#define CGABENCHMARKING_H

#include <CanonicalGA.h>
#include <vector>

#define DEFAULT_EXECUTIONS 10

using namespace std;

class CGABenchmarking
{
    CanonicalGA canonicalGA;
    unsigned int numberOfExecutions;

    public:
        CGABenchmarking():numberOfExecutions(DEFAULT_EXECUTIONS){};
        CGABenchmarking(CanonicalGA ga): canonicalGA(ga), numberOfExecutions(DEFAULT_EXECUTIONS){};
        CGABenchmarking(CanonicalGA ga, unsigned int executions):
            canonicalGA(ga), numberOfExecutions(executions){};
        virtual ~CGABenchmarking();
        void setNumberOfExecutions(unsigned int executions);
        void run();
        vector<ExecutionReport> run(unsigned int populationSize,
            unsigned int numberOfGenerations, InfeasiblesPolicy policy);
};

#endif // CGABENCHMARKING_H
