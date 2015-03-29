#include "Read.hpp"

const int Relation::Read::weight = 0;

Relation::Read::Read() : Access()
{

}

Relation::Read::~Read()
{

}

bool Relation::Read::isValid() const
{
    return (m_idForm != 0 && m_idGroup != 0);
}

void Relation::Read::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    preInsert();

    QSqlQuery query = m_db.exec("INSERT INTO reader (form_id, usergroup_id) VALUES(?, ?)");

    query.bindValue(0, m_idForm);
    query.bindValue(1, m_idGroup);

    query.exec();

    postInsert();
}

void Relation::Read::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM reader WHERE form_id = ? AND usergroup_id = ?");

    query.bindValue(0, m_idForm);
    query.bindValue(1, m_idGroup);

    query.exec();

    postRemove();
}

int Relation::Read::getWeight() const
{
    return Read::weight;
}
