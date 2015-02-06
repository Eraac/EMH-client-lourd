#include "DefaultValue.hpp"

const int Entity::DefaultValue::weight = 0;

Entity::DefaultValue::DefaultValue() : Entity(), m_value(""), m_idField(0)
{

}

Entity::DefaultValue::~DefaultValue()
{

}

void Entity::DefaultValue::setValue(const QString &value)
{
    m_value = value;
}

void Entity::DefaultValue::setIdField(const unsigned int id)
{
    m_idField = id;
}

QString Entity::DefaultValue::getValue() const
{
    return m_value;
}

unsigned int Entity::DefaultValue::getIdField() const
{
    return m_idField;
}

Entity::Entity::ErrorType Entity::DefaultValue::load(unsigned int id)
{
    // TODO
    m_id        = id;
    m_value     = "Valeur par défaut";
    m_idField   = 2;

    return Entity::ErrorType::NONE;
}

int Entity::DefaultValue::getWeight() const
{
    return DefaultValue::weight;
}

void Entity::DefaultValue::persist()
{
    // TODO
}

void Entity::DefaultValue::remove()
{
    // TODO
}

bool Entity::DefaultValue::isValid() const
{
    return !m_value.isEmpty();
}
