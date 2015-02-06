#include "Entity.hpp"

Entity::Entity::Entity() : Model::Persistable(), m_id(0)
{
}

Entity::Entity::~Entity()
{

}

unsigned int Entity::Entity::getId() const
{
    return m_id;
}

void Entity::Entity::setId(unsigned const int id)
{
    m_id = id;
}
