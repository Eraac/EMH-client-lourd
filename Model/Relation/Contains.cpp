#include "Contains.hpp"

const int Relation::Contains::weight = 1;

Relation::Contains::Contains() : m_idField(0), m_idForm(0)
{

}

Relation::Contains::~Contains()
{

}

bool Relation::Contains::isValid() const
{
    return (m_idField != 0 && m_idForm != 0);
}

void Relation::Contains::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    preInsert();

    QSqlQuery query = m_db.exec("INSERT INTO contains (field_id, form_id) VALUES(?, ?)");

    query.bindValue(0, m_idField);
    query.bindValue(1, m_idForm);

    query.exec();

    postInsert();
}

void Relation::Contains::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM contains WHERE field_id = ? AND form_id = ?");

    query.bindValue(0, m_idField);
    query.bindValue(1, m_idForm);

    query.exec();

    postRemove();
}

void Relation::Contains::setIdField(unsigned int id)
{
    m_idField = id;
}

void Relation::Contains::setIdForm(unsigned int id)
{
    m_idForm = id;
}

unsigned int Relation::Contains::getIdField() const
{
    return m_idField;
}

unsigned int Relation::Contains::getIdForm() const
{
    return m_idForm;
}

int Relation::Contains::getWeight() const
{
    return Contains::weight;
}
