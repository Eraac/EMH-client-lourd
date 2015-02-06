#include "Field.hpp"

const int Entity::Field::weight = 1;

Entity::Field::Field() : Entity(), m_type(Field::Type::NONE), m_isMultiple(false),
                         m_label(""), m_placeholder(""), m_helpText("")
{

}

Entity::Field::~Field()
{

}

void Entity::Field::setType(const Field::Type type)
{
    m_type = type;
}

void Entity::Field::setLabel(const QString &label)
{
    m_label = label;
}

void Entity::Field::setPlaceholder(const QString &placeholder)
{
    m_placeholder = placeholder;
}

void Entity::Field::setHelpText(const QString &helpText)
{
    m_helpText = helpText;
}

Entity::Field::Type Entity::Field::getType() const
{
    return m_type;
}

QString Entity::Field::getLabel() const
{
    return m_label;
}

QString Entity::Field::getPlaceholder() const
{
    return m_placeholder;
}

QString Entity::Field::getHelpText() const
{
    return m_helpText;
}

Entity::Entity::ErrorType Entity::Field::load(unsigned int id)
{
    m_id = id;
    m_isMultiple = false;
    m_label = "Prenom";
    m_placeholder = "Votre prénom";
    m_helpText = "Entrez votre prénom pas votre nom";

    return Entity::ErrorType::NONE;
}

int Entity::Field::getWeight() const
{
    return Field::weight;
}

void Entity::Field::persist()
{
    // TODO
}

void Entity::Field::remove()
{
    // TODO
}

bool Entity::Field::isValid() const
{
    return (m_type != Field::Type::NONE && !m_label.isEmpty()); // TODO Vérifier si les droits sont configurés
}
