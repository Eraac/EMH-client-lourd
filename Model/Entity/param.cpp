#include "param.hpp"

const int Entity::Param::weight() = 1;

Entity::Param::Param() : Entity(), m_value(), m_idConstraint(0)
{

}

void Entity::Param::setValue(const QString &value)
{
    m_value = value;
}

void Entity::Param::setIdConstraint(int id)
{
    m_idConstraint = id;
}

QString Entity::Param::getValue() const
{
    return m_value;
}

int Entity::Param::getIdConstraint() const
{
    return m_idConstraint;
}

int Entity::Param::getWeight() const
{
    return Param::weight;
}

void Entity::Param::persist()
{
    // TODO
}

void Entity::Param::remove()
{
    // TOOD
}

void Entity::Param::isValid()
{
    return !(m_value.isEmpty() || m_idConstraint == 0);
}
