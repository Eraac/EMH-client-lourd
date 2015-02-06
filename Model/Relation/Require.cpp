#include "Require.hpp"

const int Relation::Require::weight = 1;

Relation::Require::Require() : m_idConstraint(0), m_idField(0)
{

}

Relation::Require::~Require()
{

}

bool Relation::Require::isValid() const
{
    return (m_idConstraint != 0 && m_idField != 0);
}

void Relation::Require::persist()
{
    // TODO
}

void Relation::Require::remove()
{
    // TODO
}

void Relation::Require::setIdConstraint(unsigned int id)
{
    m_idConstraint = id;
}

void Relation::Require::setIdField(unsigned int id)
{
    m_idField = id;
}

unsigned int Relation::Require::getIdConstraint() const
{
    return m_idConstraint;
}

unsigned int Relation::Require::getIdField() const
{
    return m_idField;
}

int Relation::Require::getWeight() const
{
    return Require::weight;
}
