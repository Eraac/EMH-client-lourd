#include "PersisterManager.hpp"

Utility::PersisterManager::PersisterManager() : m_listPersistable()
{

}

Utility::PersisterManager::PersisterManager(QList<Model::Persistable> const& listPersistable)
    : m_listPersistable(listPersistable)
{

}

Utility::PersisterManager::~PersisterManager()
{

}

void Utility::PersisterManager::append(Model::Persistable& persistable)
{
    m_listPersistable.append(persistable);
}

void Utility::PersisterManager::persistOne(Model::Persistable& persistable)
{
    persistable.prePersist();
    persistable.persist();
    persistable.postPersist();
}

void Utility::PersisterManager::persistAll()
{
    sortList();

    for (auto i = m_listPersistable.begin(); i != m_listPersistable.end(); ++i)
    {
        persistOne(*i);
    }
}

void Utility::PersisterManager::sortList()
{
    // Trier par poids et retirer les non valide
}






