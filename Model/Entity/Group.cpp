#include "Group.hpp"

const int Entity::Group::weight = 1;

Entity::Group::Group() : Entity(), m_name("")
{
}

Entity::Group::~Group()
{
}

Entity::Entity::ErrorType Entity::Group::loadByName(const QString &name)
{
    // TODO Requete SQL here pour charger group
    m_id = qrand() % ((1000 + 1) - 1);
    m_name = name;

    return Entity::ErrorType::NONE;
}

Entity::Entity::ErrorType Entity::Group::load(unsigned int id)
{
    m_id = id;
    m_name = "Medecin";

    return Entity::ErrorType::NONE;
}

bool Entity::Group::groupExist(const QString &name)
{
    // TODO requete SQL à faire
    return (name == "aaa"); // valeur de test
}

void Entity::Group::setName(const QString &name)
{
    if (!name.isEmpty())
        m_name = name;
}

QString Entity::Group::getName() const
{
    return m_name;
}

QStringList Entity::Group::getAll()
{
    QStringList listGroup;

    listGroup.append("Medecin");
    listGroup.append("Administratif");
    listGroup.append("Patient");

    return listGroup;
}

void Entity::Group::persist()
{
    // TODO
}

void Entity::Group::remove()
{
    // TODO
}

bool Entity::Group::isValid() const
{
    return !m_name.isEmpty();
}

int Entity::Group::getWeight() const
{
    return Group::weight;
}
