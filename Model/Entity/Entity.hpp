#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Persistable.hpp"

namespace Entity
{
    class Entity : public Model::Persistable
    {
        public:
        Entity();                           // Constructeur par défaut
        virtual ~Entity();                  // Destructeur

        enum class ErrorType {NONE, NOT_FOUND, DATABASE_ERROR}; // Liste d'erreur possible

        virtual Entity::ErrorType load(unsigned int id) = 0; // Charge une entité par son ID

        unsigned int getId() const;         // Retourne l'ID de l'entité

        protected:
        unsigned int m_id;                  // ID de l'entité dans le base de données

        void setId(unsigned int const id);       
    };
}

#endif // ENTITY_HPP
