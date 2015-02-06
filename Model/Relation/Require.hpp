#ifndef REQUIRE_HPP
#define REQUIRE_HPP

#include "Relation.hpp"

namespace Relation
{
    class Require : public Relation::Relation
    {
        public:
        Require();                              // Constructeur par défaut
        virtual ~Require();                     // Destructeur

        static const int weight;                // Utilisé pour trier les relations

        virtual bool isValid() const;           // Retourne true si la relation est valide
        virtual void remove();                  // Supprime la relation de la base de données
        virtual void persist();                 // Persiste la relation dans la base de données

        // === Get / Set ===
        void setIdConstraint(unsigned int id);  // Change l'id de la contrainte
        void setIdField(unsigned int id);       // Change l'id du champs

        unsigned int getIdConstraint() const;   // Retourne l'id de la contrainte
        unsigned int getIdField() const;        // Retourne l'id du champs
        virtual int getWeight() const;          // Retourne le poids

        private:
        unsigned int m_idConstraint;
        unsigned int m_idField;

    };
}

#endif // REQUIRE_HPP
