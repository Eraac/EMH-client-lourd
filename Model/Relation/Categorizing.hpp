#ifndef CATEGORIZING_HPP
#define CATEGORIZING_HPP

#include "Relation.hpp"

namespace Relation
{
    class Categorizing : public Relation::Relation
    {
        public:
        Categorizing();                     // Constructeur par défaut
        virtual ~Categorizing();           // Destructeur

        static const int weight;            // Utilisé pour trier les relations

        virtual bool isValid() const;       // Retourne true si la relation est valide
        virtual void persist();             // Persiste la relation dans la base de données
        virtual void remove();              // Supprime la relation de la base de données

        // === Get / Set ===
        void setIdTag(unsigned int id);     // Change l'id du tag
        void setIdForm(unsigned int id);    // Change l'id du formulaire

        unsigned int getIdTag() const;      // Retourne l'id du tag
        unsigned int getIdForm() const;     // Retourne l'id du formulaire
        virtual int getWeight() const;      // Retourne le poids de la relation

        private:
        unsigned int m_idTag;
        unsigned int m_idForm;

    };
}

#endif // CATEGORIZING_HPP
