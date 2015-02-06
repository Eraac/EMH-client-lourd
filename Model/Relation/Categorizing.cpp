#include "Categorizing.hpp"

const int Relation::Categorizing::weight = 1;

Relation::Categorizing::Categorizing() : m_idTag(0), m_idForm(0)
{

}

Relation::Categorizing::~Categorizing()
{

}

bool Relation::Categorizing::isValid() const
{
    return (m_idTag != 0 && m_idForm != 0);
}

void Relation::Categorizing::persist()
{
    // TODO
}

void Relation::Categorizing::remove()
{
    // TODO
}

void Relation::Categorizing::setIdForm(unsigned int id)
{
    m_idForm = id;
}

void Relation::Categorizing::setIdTag(unsigned int id)
{
    m_idTag = id;
}

unsigned int Relation::Categorizing::getIdForm() const
{
    return m_idForm;
}

unsigned int Relation::Categorizing::getIdTag() const
{
    return m_idTag;
}

int Relation::Categorizing::getWeight() const
{
    return Categorizing::weight;
}
