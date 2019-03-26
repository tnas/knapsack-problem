#include "Fitness.h"

Fitness::Fitness()
{
}
Fitness::Fitness(unsigned int chromosome, unsigned int value)
{
    this->chromosome = chromosome;
    this->value = value;
}

Fitness::Fitness(unsigned int chromosome, unsigned int value, unsigned int weight)
{
    this->chromosome = chromosome;
    this->value = value;
    this->weight = weight;
}

Fitness::~Fitness()
{
}

bool Fitness::operator<(const Fitness& other) const
{
    return this->value < other.value;
}

bool Fitness::operator>(const Fitness& other) const
{
    return this->value > other.value;
}

void Fitness::setValue(unsigned int value)
{
    this->value = value;
}

void Fitness::setChromosome(unsigned int chromosome)
{
    this->chromosome = chromosome;
}

unsigned int Fitness::getValue()
{
    return this->value;
}

unsigned int Fitness::getChromosome()
{
    return this->chromosome;
}

void Fitness::setWeight(unsigned int weight)
{
    this->weight = weight;
}

unsigned int Fitness::getWeight()
{
    return this->weight;
}


