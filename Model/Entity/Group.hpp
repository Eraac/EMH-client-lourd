#ifndef GROUP_HPP
#define GROUP_HPP

#include <QStringList>
#include "Entity.hpp"

namespace Entity
{
    class Group : public Entity
    {
        public:
        Group();                                    // Constructeur par défaut
        virtual ~Group();                                   // Destructeur

        static const int weight;                    // Utilisé pour trier
        static bool groupExist(QString const& name); // Retourne vrai si le groupe existe

        Entity::ErrorType loadByName(QString const& name); // Charge un groupe par son nom
        Entity::ErrorType load(unsigned int id);    // Charge l'entité depuis la base de données

        void setName(QString const& name);          // Change son nom

        QString getName() const;                    // Retourne le nom

        static QStringList getAll();                // Retourne le nom de tous les groupes
        virtual int getWeight() const;              // Retourne le poids

        virtual void persist() override;            // Persiste l'entité dans la base de données
        virtual void remove() override;             // Supprime l'entité de la base de données
        virtual bool isValid() const;               // Retourne si l'entité est valide pour le persiste

        private:
        QString m_name;
    };
}

#endif // GROUP_HPP
