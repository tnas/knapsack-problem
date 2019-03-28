#ifndef CGABENCHMARKING_H
#define CGABENCHMARKING_H

#include <CanonicalGA.h>
#include <list>

#define DEFAULT_EXECUTIONS 10

using namespace std;

class CGABenchmarking
{
    CanonicalGA canonicalGA;
    unsigned int numberOfExecutions;

    public:
        CGABenchmarking();
        CGABenchmarking(CanonicalGA ga): canonicalGA(ga){};
        CGABenchmarking(CanonicalGA ga, unsigned int executions):
            canonicalGA(ga), numberOfExecutions(executions){};
        virtual ~CGABenchmarking();
        void setNumberOfExecutions(unsigned int executions);
        void run();
        list<ExecutionReport> run(unsigned int numberOfGenerations,
                                  unsigned int populationSize,
                                  InfeasiblesPolicy policy);
};

#endif // CGABENCHMARKING_H
