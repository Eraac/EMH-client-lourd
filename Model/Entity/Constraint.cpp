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
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM fieldConstraint WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id = query.value("id").toInt();
    m_type = query.value("type").toInt();

    return Entity::ErrorType::NONE;
}

int Entity::Constraint::getWeight() const
{
    return Constraint::weight;
}

void Entity::Constraint::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec("UPDATE fieldConstraint SET type = ? WHERE id = ?");

        query.bindValue(0, m_type);
        query.bindValue(1, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec("INSERT INTO fieldConstraint (type) VALUES(?)");

        query.bindValue(0, m_type);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::Constraint::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM fieldConstraint WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::Constraint::isValid() const
{
    return (m_type != Constraint::Type::NONE);
}
