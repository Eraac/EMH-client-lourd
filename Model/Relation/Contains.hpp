#ifndef CONTAINS_HPP
#define CONTAINS_HPP

#include "Relation.hpp"

namespace Relation
{
    class Contains : public Relation::Relation
    {
        public:
        Contains();                         // Default constructor
        virtual ~Contains();                // Destructor

        static const int weight;            // Use for sort entity

        virtual bool isValid() const;       // Return true if entity is valid for persist
        virtual void persist();             // Persist into database
        virtual void remove();              // Delete from database

        // === Get / Set ===
        void setIdField(unsigned int id);   // Set field id
        void setIdForm(unsigned int id);    // Set form id

        unsigned int getIdField() const;    // Get field id
        unsigned int getIdForm() const;     // Get form id

        virtual int getWeight() const;      // Return the weight

        private:
        unsigned int m_idField;
        unsigned int m_idForm;

    };
}

#endif // CONTAINS_HPP
