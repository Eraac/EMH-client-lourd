#include "constrained.hpp"

const int Relation::Constrained::weight = 1;

Relation::Constrained::Constrained() : m_idField(0), m_idConstraint(0)
{

}

Relation::Constrained::~Constrained()
{

}

bool Relation::Constrained::isValid() const
{
    return (m_idField != 0 && m_idConstraint != 0);
}

void Relation::Constrained::persist()
{
    // TODO
}

void Relation::Constrained::remove()
{
    // TODO
}

void Relation::Constrained::setIdField(unsigned int id)
{
    m_idField = id;
}

void Relation::Constrained::setIdConstraint(unsigned int id)
{
    m_idConstraint = id;
}

unsigned int Relation::Constrained::getIdField() const
{
    return m_idField;
}

unsigned int Relation::Constrained::getIdConstraint() const
{
    return m_idConstraint;
}

int Relation::Constrained::getWeight() const
{
    return Constrained::weight;
}
