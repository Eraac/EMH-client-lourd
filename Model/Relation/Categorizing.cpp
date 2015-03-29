#include "Categorizing.hpp"

const int Relation::Categorizing::weight = 1;

Relation::Categorizing::Categorizing() : m_idTag(0), m_idForm(0)
{

}

Relation::Categorizing::~Categorizing()
{

}

bool Relation::Categorizing::isValid() const
{
    return (m_idTag != 0 && m_idForm != 0);
}

void Relation::Categorizing::persist()
{
    if (!initDB())
        return; // TODO Add exception ?

    preInsert();

    QSqlQuery query = m_db.exec("INSERT INTO categorizing (form_id, tag_id) VALUES(?, ?)");

    query.bindValue(0, m_idForm);
    query.bindValue(1, m_idTag);

    query.exec();

    postInsert();
}

void Relation::Categorizing::remove()
{
    if (!initDB())
        return; // TODO Add exception ?

    preRemove();

    QSqlQuery query = m_db.exec("DELETE FROM categorizing WHERE form_id = ? AND tag_id = ?");

    query.bindValue(0, m_idForm);
    query.bindValue(1, m_idTag);

    query.exec();

    postRemove();
}

void Relation::Categorizing::setIdForm(unsigned int id)
{
    m_idForm = id;
}

void Relation::Categorizing::setIdTag(unsigned int id)
{
    m_idTag = id;
}

unsigned int Relation::Categorizing::getIdForm() const
{
    return m_idForm;
}

unsigned int Relation::Categorizing::getIdTag() const
{
    return m_idTag;
}

int Relation::Categorizing::getWeight() const
{
    return Categorizing::weight;
}
