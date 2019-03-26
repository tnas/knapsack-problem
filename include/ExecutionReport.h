#ifndef EXECUTIONREPORT_H
#define EXECUTIONREPORT_H


class ExecutionReport
{
    unsigned int chromosomeSize;
    unsigned int* chromosome;
    unsigned int fitnessValue;
    unsigned int knapsackWeight;
    unsigned int numberOfGenerations;
    unsigned int numberOfAllelesOn;

    public:
        ExecutionReport();
        virtual ~ExecutionReport();
        unsigned int* getChromosome();
        unsigned int getFitnessValue();
        unsigned int getNumberOfGenerations();
        unsigned int getKnapsackWeight();
        unsigned int getNumberOfAllelesOn();
        void setChromosome(unsigned int* chromosome, unsigned int size);
        void setFitnessValue(unsigned int fitnessValue);
        void setNumberOfGenerations(unsigned int numberOfGenerations);
        void setKnapsackWeight(unsigned int weight);
        void print();
        void printCompactedFormat();
};

#endif // EXECUTIONREPORT_H
