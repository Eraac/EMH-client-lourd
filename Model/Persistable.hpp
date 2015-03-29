#ifndef PERSISTABLE_HPP
#define PERSISTABLE_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

namespace Model
{
    class Persistable
    {
        public:
        Persistable();                      // Constructeur par défaut
        virtual ~Persistable();             // Destructeur

        virtual bool isValid() const;   // Retourne true si l'entité est valide pour l'insert ou l'update
        virtual void persist();         // Persiste l'entité dans le base de données
        virtual void remove();          // Supprime l'entité de la base de donnée
        virtual void prePersist();          // Appeler avant la méthode persist()
        virtual void postPersist();         // Appeler après la méthode persist
        virtual void preUpdate();           // Appeler avant un update
        virtual void postUpdate();          // Appeler après un update
        virtual void preInsert();           // Appeler avant un insert
        virtual void postInsert();          // Appeler après un insert
        virtual void preRemove();           // Appeler avant un remove
        virtual void postRemove();          // Appeler après un remove
        virtual int getWeight() const;  // Retourne le poids d'une entité pour obtenir l'ordre d'enregistrement

        protected:
        static bool initDB();

        static QSqlDatabase m_db;    // Connexion à la base de données

    };
}

#endif // PERSISTABLE_HPP
