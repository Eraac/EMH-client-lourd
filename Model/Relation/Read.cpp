#include "Read.hpp"

const int Relation::Read::weight = 0;

Relation::Read::Read() : Access()
{

}

Relation::Read::~Read()
{

}

bool Relation::Read::isValid() const
{
    return (m_idForm != 0 && m_idGroup != 0);
}

void Relation::Read::persist()
{
    // TODO
}

void Relation::Read::remove()
{
    // TODO
}

int Relation::Read::getWeight() const
{
    return Read::weight;
}
