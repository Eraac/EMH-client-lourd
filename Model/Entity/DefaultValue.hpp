#ifndef DEFAULTVALUE_HPP
#define DEFAULTVALUE_HPP

#include <QString>
#include "Entity.hpp"

namespace Entity
{
    class DefaultValue : public Entity
    {
        public:
        DefaultValue();             // Constructeur par défaut
        virtual ~DefaultValue();    // Destructeur

        static const int weight;    // Utilisé pour trier

        void setValue(QString const& value);        // Change la valeur
        void setIdField(unsigned const int id);     // Change l'id du champs associé

        QString getValue() const;                   // Retourne la valeur
        unsigned int getIdField() const;            // Retourne l'id du champs associé

        Entity::ErrorType load(unsigned int id);    // Charge l'entité depuis la base de données

        virtual int getWeight() const;              // Retourne le poids de l'entité

        virtual void persist() override;            // Persiste l'entité dans la base de données
        virtual void remove() override;             // Supprime l'entité de la base de données
        virtual bool isValid() const;               // Retourne si l'entité est valide ou pas pour le persiste

        private:
        QString m_value;
        unsigned int m_idField;

    };
}

#endif // DEFAULTVALUE_HPP
