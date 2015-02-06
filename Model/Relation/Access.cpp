#include "Access.hpp"

Relation::Access::Access() : m_idGroup(0), m_idForm(0)
{

}

void Relation::Access::setIdGroup(unsigned int id)
{
    m_idGroup = id;
}

void Relation::Access::setIdForm(unsigned int id)
{
    m_idForm = id;
}

unsigned int Relation::Access::getIdGroup() const
{
    return m_idGroup;
}

unsigned int Relation::Access::getIdForm() const
{
    return m_idForm;
}
