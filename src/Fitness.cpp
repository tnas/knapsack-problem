#include "../include/Fitness.h"

Fitness::Fitness()
{
}

Fitness::Fitness(unsigned int id, unsigned int value)
{
    this->id = id;
    this->value = value;
}

Fitness::Fitness(unsigned int id, unsigned int value, unsigned int weight)
{
    this->id = id;
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

void Fitness::setId(unsigned int id)
{
    this->id = id;
}

unsigned int Fitness::getValue()
{
    return this->value;
}

unsigned int Fitness::getId()
{
    return this->id;
}

void Fitness::setWeight(unsigned int weight)
{
    this->weight = weight;
}

unsigned int Fitness::getWeight()
{
    return this->weight;
}


