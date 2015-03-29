#include "Require.hpp"

const int Relation::Require::weight = 1;

Relation::Require::Require() : m_idConstraint(0), m_idField(0)
{

}

Relation::Require::~Require()
{

}

bool Relation::Require::isValid() const
{
    return (m_idConstraint != 0 && m_idField != 0);
}

void Relation::Require::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    preInsert();

    QSqlQuery query = m_db.exec("INSERT INTO constrained (field_id, fieldConstraint_id) VALUES(?, ?)");

    query.bindValue(0, m_idField);
    query.bindValue(1, m_idConstraint);

    query.exec();

    postInsert();
}

void Relation::Require::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM constrained WHERE field_id = ? AND fieldConstraint_id = ?");

    query.bindValue(0, m_idField);
    query.bindValue(1, m_idConstraint);

    query.exec();

    postRemove();
}

void Relation::Require::setIdConstraint(unsigned int id)
{
    m_idConstraint = id;
}

void Relation::Require::setIdField(unsigned int id)
{
    m_idField = id;
}

unsigned int Relation::Require::getIdConstraint() const
{
    return m_idConstraint;
}

unsigned int Relation::Require::getIdField() const
{
    return m_idField;
}

int Relation::Require::getWeight() const
{
    return Require::weight;
}
