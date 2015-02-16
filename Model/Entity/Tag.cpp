#include "Tag.hpp"

const int Entity::Tag::weight = 0;

Entity::Tag::Tag() : Entity(), m_name("")
{

}

Entity::Tag::~Tag()
{

}

void Entity::Tag::setName(const QString &name)
{
    m_name = name;
}

QString Entity::Tag::getName() const
{
    return m_name;
}

Entity::Entity::ErrorType Entity::Tag::load(unsigned int id)
{
    // TODO
    m_id = id;
    m_name = "Demande";

    return Entity::ErrorType::NONE;
}

Entity::Entity::ErrorType Entity::Tag::loadByName(const QString& name)
{
    // TODO
    m_id = 5;
    m_name = name;

    return Entity::ErrorType::NONE;
}

QStringList Entity::Tag::getAll()
{
    // TODO
    QStringList listTag;

    listTag.append("Administration");
    listTag.append("Demande");
    listTag.append("Problème");
    listTag.append("Tag");

    return listTag;
}

int Entity::Tag::getWeight() const
{
    return Tag::weight;
}

void Entity::Tag::persist()
{
    // TODO
}

void Entity::Tag::remove()
{
    // TODO
}

bool Entity::Tag::isValid() const
{
    return !m_name.isEmpty();
}
