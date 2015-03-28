#include "param.hpp"

const int Entity::Param::weight = 1;

Entity::Param::Param() : Entity(), m_value(), m_idConstraint(0)
{

}

Entity::Param::~Param()
{

}

Entity::Entity::ErrorType Entity::Param::load(unsigned int id)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM param WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id = query.value("id").toInt();
    m_value = query.value("value").toString();
    m_idConstraint = query.value("fieldConstraint_id").toInt();

    return Entity::ErrorType::NONE;
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
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec("UPDATE param SET value = ?, fieldConstraint_id WHERE id = ?");

        query.bindValue(0, m_value);
        query.bindValue(1, m_idConstraint);
        query.bindValue(2, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec("INSERT INTO param (value, fieldConstraint_id) VALUES(?, ?)");

        query.bindValue(0, m_value);
        query.bindValue(1, m_idConstraint);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::Param::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM param WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::Param::isValid() const
{
    return !(m_value.isEmpty() || m_idConstraint == 0);
}
