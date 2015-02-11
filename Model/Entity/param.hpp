#ifndef PARAM_HPP
#define PARAM_HPP

#include <QString>
#include "Entity.hpp"

namespace Entity
{
    class Param : public Entity
    {
        public:
            Param();
            virtual ~Param();

            static const int weight;

            Entity::ErrorType load(unsigned int id);

            void setValue(QString const& value);// Change la valeur
            void setIdConstraint(int id);       // Change l'id de la contrainte

            QString getValue() const;           // Retourne la valeur
            int getIdConstraint() const;        // Retourne l'id de la contrainte associée
            virtual int getWeight() const;      // Retourne le poids

            virtual void persist() override;    // Persiste l'entité dans le base de données
            virtual bool isValid() const;       // Retourne si l'entité est valide pour le base de données
            virtual void remove() override;     // Supprime l'entité de la base de données

        private:
            QString m_value;
            int m_idConstraint;
    };
}

#endif // PARAM_HPP

