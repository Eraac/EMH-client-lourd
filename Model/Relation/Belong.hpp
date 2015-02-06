#ifndef BELONG_HPP
#define BELONG_HPP

#include "Relation.hpp"

namespace Relation
{
    class Belong : public Relation::Relation
    {
        public:
        Belong();   // Constructeur par défaut
        ~Belong();  // Destructeur

        static const int weight;            // Utilisé pour trier les entités

        virtual bool isValid() const;       // Retourne true si la relation est valide
        virtual void persist();             // Persiste la relation dans la base de données
        virtual void remove();              // Supprime la relation de la base de données

        // === Get / Set ===
        void setIdUser(unsigned int id);    // Change l'id du l'utilisateur
        void setIdGroup(unsigned int id);   // Change l'id du groupe

        unsigned int getIdUser() const;     // Retourne l'id de l'utilisateur
        unsigned int getIdGroup() const;    // Retourne l'id du groupe
        virtual int getWeight() const;      // Retourne le poids

        private:
        unsigned int m_idUser;
        unsigned int m_idGroup;

    };
}

#endif // BELONG_HPP
