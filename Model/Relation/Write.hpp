#ifndef WRITE_HPP
#define WRITE_HPP

#include "Access.hpp"

namespace Relation
{
    class Write : public Access
    {
        public:
        Write();    // Constructeur par défaut
        virtual ~Write();   // Destructeur

        static const int weight;        // Utilisé pour trier les relations

        virtual bool isValid() const;   // Retourne true si la relation est valide
        virtual void persist();         // Persiste la relation dans la base de données
        virtual void remove();          // Supprime la relation de la base de données

        virtual int getWeight() const;  // Retourne le poids

    };
}

#endif // WRITE_HPP
