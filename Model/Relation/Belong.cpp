#include "Belong.hpp"

const int Relation::Belong::weight = 1;

Relation::Belong::Belong() : m_idUser(0), m_idGroup(0)
{

}

Relation::Belong::~Belong()
{

}

bool Relation::Belong::isValid() const
{
    return (m_idUser != 0 && m_idGroup != 0);
}

void Relation::Belong::persist()
{
    // TODO
}

void Relation::Belong::remove()
{
    // TODO
}

void Relation::Belong::setIdUser(unsigned int id)
{
    m_idUser = id;
}

void Relation::Belong::setIdGroup(unsigned int id)
{
    m_idGroup = id;
}

unsigned int Relation::Belong::getIdUser() const
{
    return m_idUser;
}

unsigned int Relation::Belong::getIdGroup() const
{
    return m_idGroup;
}

int Relation::Belong::getWeight() const
{
    return Belong::weight;
}


