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
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM tag WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id = query.value("id").toInt();
    m_name = query.value("name").toString();

    return Entity::ErrorType::NONE;
}

Entity::Entity::ErrorType Entity::Tag::loadByName(const QString& name)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM tag WHERE name = ?");

    if (name.isEmpty())
        return Entity::ErrorType::NOT_FOUND;

    query.bindValue(0, name);

    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id = query.value("id").toInt();
    m_name = query.value("name").toString();

    return Entity::ErrorType::NONE;
}

QStringList Entity::Tag::getAll()
{
    QStringList listTag;

    if (!initDB())
        return listTag;

    QSqlQuery query = m_db.exec("SELECT name FROM tag");

    while (query.next())
    {
        QString tagname = query.value(0).toString();
        listTag.append(tagname);
    }

    return listTag;
}

int Entity::Tag::getWeight() const
{
    return Tag::weight;
}

void Entity::Tag::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec("UPDATE tag SET name = ? WHERE id = ?");

        query.bindValue(0, m_name);
        query.bindValue(1, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec("INSERT INTO tag (name) VALUES(?)");

        query.bindValue(0, m_name);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::Tag::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM tag WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::Tag::isValid() const
{
    return !m_name.isEmpty();
}
