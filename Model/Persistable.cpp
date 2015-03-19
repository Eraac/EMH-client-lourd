#include "Persistable.hpp"

QSqlDatabase Model::Persistable::m_db = QSqlDatabase::addDatabase("QMYSQL");

Model::Persistable::Persistable()
{

}

Model::Persistable::~Persistable()
{

}

bool Model::Persistable::initDB()
{
    if (m_db.isOpen())
        return true;

    m_db.setHostName("192.168.1.75"); // TODO recupèrer dans le fichier de conf
    m_db.setDatabaseName("qt");
    m_db.setUserName("qt");
    m_db.setPassword("qtpass");
    m_db.open();

    return m_db.isOpen();
}

bool Model::Persistable::isValid() const
{
    return false;
}

void Model::Persistable::prePersist()
{
    // If m_db is nullptr -> initialize
}

void Model::Persistable::postPersist()
{

}

void Model::Persistable::preUpdate()
{

}

void Model::Persistable::postUpdate()
{

}

void Model::Persistable::preInsert()
{

}

void Model::Persistable::postInsert()
{

}

void Model::Persistable::preRemove()
{

}

void Model::Persistable::postRemove()
{

}

void Model::Persistable::persist()
{

}

void Model::Persistable::remove()
{

}

int Model::Persistable::getWeight() const
{
    return 0;
}
