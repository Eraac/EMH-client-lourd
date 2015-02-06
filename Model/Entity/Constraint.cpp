#include "Constraint.hpp"

const int Entity::Constraint::weight = 1;

Entity::Constraint::Constraint() : Entity(), m_type(Constraint::Type::NONE)
{

}

Entity::Constraint::~Constraint()
{

}


void Entity::Constraint::setType(const Constraint::Type type)
{
    m_type = type;
}

Entity::Constraint::Type Entity::Constraint::getType() const
{
    return m_type;
}

Entity::Entity::ErrorType Entity::Constraint::load(unsigned int id)
{
    // TODO
    m_id    = id;
    m_type  = Constraint::Type::DATE;

    return Entity::ErrorType::NONE;
}

int Entity::Constraint::getWeight() const
{
    return Constraint::weight;
}

void Entity::Constraint::persist()
{
    // TODO
}

void Entity::Constraint::remove()
{
    // TODO
}

bool Entity::Constraint::isValid() const
{
    return (m_type != Constraint::Type::NONE);
}
