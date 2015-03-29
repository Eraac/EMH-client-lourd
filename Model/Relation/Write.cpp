#include "Write.hpp"

const int Relation::Write::weight = 0;

Relation::Write::Write() : Access()
{

}

Relation::Write::~Write()
{

}

bool Relation::Write::isValid() const
{
    return (m_idForm != 0 && m_idGroup != 0);
}

void Relation::Write::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    preInsert();

    QSqlQuery query = m_db.exec("INSERT INTO writer (form_id, usergroup_id) VALUES(?, ?)");

    query.bindValue(0, m_idForm);
    query.bindValue(1, m_idGroup);

    query.exec();

    postInsert();
}

void Relation::Write::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM writer WHERE form_id = ? AND usergroup_id = ?");

    query.bindValue(0, m_idForm);
    query.bindValue(1, m_idGroup);

    query.exec();

    postRemove();
}

int Relation::Write::getWeight() const
{
    return Write::weight;
}
