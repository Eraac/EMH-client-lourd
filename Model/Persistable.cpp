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

    Settings settings;

    m_db.setHostName(settings.getValue(DB_ADDRESS).toString());
    m_db.setDatabaseName(settings.getValue(DB_NAME).toString());
    m_db.setUserName(settings.getValue(DB_USERNAME).toString());
    m_db.setPassword(settings.getValue(DB_PASSWORD).toString());
    m_db.setPort(settings.getValue(DB_PORT).toInt());
    m_db.open();

    return m_db.isOpen();
}

bool Model::Persistable::isValid() const
{
    return false;
}

void Model::Persistable::prePersist()
{

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
