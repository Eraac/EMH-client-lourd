#ifndef ACCESS_HPP
#define ACCESS_HPP

#include "Relation.hpp"

namespace Relation
{
    class Access : public Relation::Relation
    {
        public:
        Access();                           // Constructeur par défaut

        // === Get / Set ===
        void setIdGroup(unsigned int id);   // Change l'id du groupe
        void setIdForm(unsigned int id);    // Change l'id du formulaire

        unsigned int getIdGroup() const;    // Retourne l'id du groupe
        unsigned int getIdForm() const;     // Retourne l'id du formulaire

        protected:
        unsigned int m_idGroup;
        unsigned int m_idForm;
    };
}

#endif // ACCESS_HPP
