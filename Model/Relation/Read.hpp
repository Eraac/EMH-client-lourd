#ifndef READ_HPP
#define READ_HPP

#include "Access.hpp"

namespace Relation
{
    class Read : public Access
    {
        public:
        Read();             // Constructeur par défaut
        virtual ~Read();    // Desctruteur

        static const int weight;    // Utilisé pour trier les relation
        virtual bool isValid() const;   // Retourne true si la relation est valide

        virtual void remove();          // Supprime la relation dans la base de données
        virtual void persist();         // Persiste la relation dans la base de données

        virtual int getWeight() const;      // Retourne le poids

    };
}

#endif // READ_HPP
