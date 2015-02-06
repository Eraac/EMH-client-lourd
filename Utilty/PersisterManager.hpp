#ifndef PERSISTERMANAGER_HPP
#define PERSISTERMANAGER_HPP

#include <QList>
#include "../Model/Persistable.hpp"

namespace Utility
{
    class PersisterManager
    {
        public:
        PersisterManager();
        PersisterManager(QList<Model::Persistable> const& listPersistable);
        ~PersisterManager();

        void append(Model::Persistable& persistable);      // Ajoute un persistable dans la liste
        void persistOne(Model::Persistable& persistable);  // Periste une relation/entité immédiatement
        void persistAll();                                  // Persiste toutes les relations/entités dans la QList

        private:
        void sortList();                                    // Tri la QList

        QList<Model::Persistable> m_listPersistable;
    };
}

#endif // PERSISTERMANAGER_HPP
