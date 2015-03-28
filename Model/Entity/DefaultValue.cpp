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
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM defaultValue WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id        = query.value("id").toInt();
    m_value     = query.value("value").toString();
    m_idField   = query.value("field_id").toInt();

    return Entity::ErrorType::NONE;
}

int Entity::DefaultValue::getWeight() const
{
    return DefaultValue::weight;
}

void Entity::DefaultValue::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec("UPDATE defaultValue SET value = ?, field_id = ? WHERE id = ?");

        query.bindValue(0, m_value);
        query.bindValue(1, m_idField);
        query.bindValue(2, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec("INSERT INTO defaultValue (value, field_id) VALUES(?, ?)");

        query.bindValue(0, m_value);
        query.bindValue(1, m_idField);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::DefaultValue::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM defaultValue WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::DefaultValue::isValid() const
{
    return !m_value.isEmpty();
}
