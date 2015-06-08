#include "session.hpp"

const int Entity::Session::weight = 1;

Entity::Session::Session() : Entity(), m_login(), m_logout(), m_userId(0)
{

}

Entity::Session::~Session()
{

}

Entity::Entity::ErrorType Entity::Session::load(unsigned int id)
{
    Q_UNUSED(id);
}

void Entity::Session::setUserId(const unsigned int userId)
{
    m_userId = userId;
}

void Entity::Session::setLogin(const QDateTime &datetime)
{
    m_login = datetime;
}

void Entity::Session::setLogout(const QDateTime &datetime)
{
    m_logout = datetime;
}

int Entity::Session::getWeight() const
{
    return Session::weight;
}

void Entity::Session::persist()
{
    if (!initDB())
        return;

    // Si déjà une ID alors update
    if (m_id != 0)
    {
        preUpdate();
        QSqlQuery query = m_db.exec("UPDATE session SET login = ?, logout = ?, user_id = ? WHERE id = ?");

        query.bindValue(0, m_login);
        query.bindValue(1, m_logout);
        query.bindValue(2, m_userId);
        query.bindValue(3, m_id);
        query.exec();

        postUpdate();
    }
    else
    {
        preInsert();
        QSqlQuery query = m_db.exec("INSERT INTO session (login, logout, user_id) VALUES(?, ?, ?)");

        query.bindValue(0, m_login);
        query.bindValue(1, m_logout);
        query.bindValue(2, m_userId);
        query.exec();

        qDebug() << query.lastError().text();

        postInsert();

        m_id = query.lastInsertId().toInt();
    }
}

void Entity::Session::remove()
{
    // Impossible de supprimer cette entite
}

bool Entity::Session::isValid() const
{
    return (m_userId != 0);
}
