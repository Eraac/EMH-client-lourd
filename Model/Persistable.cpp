#include "Persistable.hpp"

// TODO
//QSqlDatabase Model::Persistable::m_db = new QSqlDatabase{};

Model::Persistable::Persistable()
{

}

Model::Persistable::~Persistable()
{

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
