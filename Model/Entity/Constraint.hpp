#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "Entity.hpp"

namespace Entity
{
    class Constraint : public Entity
    {
        public:
        Constraint();               // Constructeur par défaut
        virtual ~Constraint();      // Destructeur

        static const int weight;    // Utilisé pour trier

        // TODO Vérifier par rapport à ceux de Symfony
        enum class Type {NONE, NOTNULL, EMAIL, LENGTH, URL,
                         REGEX, BETWEEN, NOTEQUAL, DATE, DATETIME,
                         TIME, USERPASSWORD, LOWER, LOWEROREQUAL,
                         GREATER, GREATEROREQUAL};           // Type de contrainte

        void setType(Constraint::Type const type);      // Change le type
        void setFieldId(unsigned int id);               // Change l'id du field

        Constraint::Type getType() const;               // Retourne le type
        QString getTypeReadable() const;                // Retourne le type sous forme de string
        QStringList getParams();                // Retourne les paramètres associés à la contrainte

        Entity::ErrorType load(unsigned int id);        // Charge l'entité depuis la base de données

        virtual int getWeight() const;                  // Retourne le poids (pour le tri)

        virtual void persist() override;                // Persiste l'entité dans la base de données
        virtual void remove() override;                 // Supprime l'entité de la base de données
        virtual bool isValid() const;                   // Retourne true si l'entité peut-être enregistré en base de données

        private:
        Constraint::Type m_type;
        unsigned int m_fieldId;
    };
}

#endif // CONSTRAINT_HPP
