#include "Belong.hpp"

const int Relation::Belong::weight = 1;

Relation::Belong::Belong() : m_idUser(0), m_idGroup(0)
{

}

Relation::Belong::~Belong()
{

}

bool Relation::Belong::isValid() const
{
    return (m_idUser != 0 && m_idGroup != 0);
}

void Relation::Belong::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    preInsert();

    QSqlQuery query = m_db.exec("INSERT INTO belong (user_id, usergroup_id) VALUES(?, ?)");

    query.bindValue(0, m_idUser);
    query.bindValue(1, m_idGroup);

    query.exec();

    postInsert();
}

void Relation::Belong::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM belong WHERE user_id = ? AND usergroup_id = ?");

    query.bindValue(0, m_idUser);
    query.bindValue(1, m_idGroup);

    query.exec();

    postRemove();
}

void Relation::Belong::setIdUser(unsigned int id)
{
    m_idUser = id;
}

void Relation::Belong::setIdGroup(unsigned int id)
{
    m_idGroup = id;
}

unsigned int Relation::Belong::getIdUser() const
{
    return m_idUser;
}

unsigned int Relation::Belong::getIdGroup() const
{
    return m_idGroup;
}

int Relation::Belong::getWeight() const
{
    return Belong::weight;
}


