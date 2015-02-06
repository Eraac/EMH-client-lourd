#include "Write.hpp"

const int Relation::Write::weight = 0;

Relation::Write::Write() : Access()
{

}

Relation::Write::~Write()
{

}

bool Relation::Write::isValid() const
{
    return (m_idForm != 0 && m_idGroup != 0);
}

void Relation::Write::persist()
{
    // TODO
}

void Relation::Write::remove()
{
    // TODO
}

int Relation::Write::getWeight() const
{
    return Write::weight;
}
