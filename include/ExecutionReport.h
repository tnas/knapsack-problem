#ifndef EXECUTIONREPORT_H
#define EXECUTIONREPORT_H


class ExecutionReport
{
    unsigned int chromosomeSize;
    unsigned int* chromosome;
    unsigned int fitnessValue;
    unsigned int numberOfGenerations;

    public:
        ExecutionReport();
        virtual ~ExecutionReport();
        unsigned int* getChromosome();
        unsigned int getFitnessValue();
        unsigned int getNumberOfGenerations();
        void setChromosome(unsigned int* chromosome, unsigned int size);
        void setFitnessValue(unsigned int fitnessValue);
        void setNumberOfGenerations(unsigned int numberOfGenerations);
        void print();
};

#endif // EXECUTIONREPORT_H
