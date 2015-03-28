#include "Group.hpp"

#include <QMessageBox>

const int Entity::Group::weight = 1;

Entity::Group::Group() : Entity(), m_name("")
{
}

Entity::Group::~Group()
{
}

Entity::Entity::ErrorType Entity::Group::loadByName(const QString &name)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM groups WHERE name = ?");

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

Entity::Entity::ErrorType Entity::Group::load(unsigned int id)
{
    if (!initDB())
        return Entity::ErrorType::DATABASE_ERROR;

    QSqlQuery query = m_db.exec("SELECT * FROM groups WHERE id = ?");

    query.bindValue(0, id);
    query.exec();

    if (!query.first())
        return Entity::ErrorType::NOT_FOUND;

    m_id = query.value("id").toInt();
    m_name = query.value("name").toString();

    return Entity::ErrorType::NONE;
}

bool Entity::Group::groupExist(const QString &name)
{
    initDB();

    QSqlQuery query = m_db.exec("SELECT COUNT(*) FROM groups WHERE name = ?");

    if (name.isEmpty() && !m_name.isEmpty())
        query.bindValue(0, m_name);
    else if (!name.isEmpty())
        query.bindValue(0, name);
    else
        return false;

    query.exec();
    query.next();

    int count = query.value(0).toInt();

    return (count > 0) ? true : false;
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

    if (!initDB())
        return listGroup;

    QSqlQuery query = m_db.exec("SELECT name FROM groups");    

    while (query.next())
    {
        QString groupname = query.value(0).toString();
        listGroup.append(groupname);
    }

    return listGroup;
}

void Entity::Group::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec("UPDATE groups SET name = ? WHERE id = ?");

        query.bindValue(0, m_name);
        query.bindValue(1, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec("INSERT INTO groups (name) VALUES(?)");

        query.bindValue(0, m_name);
        query.exec();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::Group::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    if (m_id == 0)
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM groups WHERE id = ?");
    query.bindValue(0, m_id);

    query.exec();

    postRemove();
}

bool Entity::Group::isValid() const
{
    return !m_name.isEmpty();
}

int Entity::Group::getWeight() const
{
    return Group::weight;
}
