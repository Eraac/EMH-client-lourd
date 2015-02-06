#include "Contains.hpp"

const int Relation::Contains::weight = 1;

Relation::Contains::Contains() : m_idField(0), m_idForm(0)
{

}

Relation::Contains::~Contains()
{

}

bool Relation::Contains::isValid() const
{
    return (m_idField != 0 && m_idForm != 0); // TODO Ajouter un meilleur controle (vérification en base)
}

void Relation::Contains::persist()
{
    // TODO
}

void Relation::Contains::remove()
{
    // TODO
}

void Relation::Contains::setIdField(unsigned int id)
{
    m_idField = id;
}

void Relation::Contains::setIdForm(unsigned int id)
{
    m_idForm = id;
}

unsigned int Relation::Contains::getIdField() const
{
    return m_idField;
}

unsigned int Relation::Contains::getIdForm() const
{
    return m_idForm;
}

int Relation::Contains::getWeight() const
{
    return Contains::weight;
}
