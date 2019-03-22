#ifndef POPULATION_H
#define POPULATION_H

#define CROSSOVER_PROBABILITY 0.8
#define MUTATION_PROPABILITY  0.05
#define DEFAULT_SIZE 10

class Population
{
    int size;
    int offspringSize;
    int individualSize;
    float crossoverProbability;
    float mutationProbaility;

    public:
        Population();
        Population(int size, int offspringSize);
        virtual ~Population();
        void create(int individualSize);
        void makeCrossover(int first, int second);
        void setSize(int size);
        void setOffspringSize(int size);
        int getIndividualSize();
        int getOffspringSize();
        int getAllele(int individual, int position);
        int getSize();
        void show();
};

#endif // POPULATION_H
