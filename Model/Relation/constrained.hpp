#ifndef CONSTRAINED_HPP
#define CONSTRAINED_HPP

#include "Relation.hpp"

namespace Relation
{
    class Constrained : public Relation::Relation
    {
        public:
            Constrained();
            virtual ~Constrained();

            static const int weight;

            virtual bool isValid() const;
            virtual void persist();
            virtual void remove();

            void setIdField(unsigned int id);
            void setIdConstraint(unsigned int id);

            unsigned int getIdField() const;
            unsigned int getIdConstraint() const;

            virtual int getWeight() const;

        private:
            unsigned int m_idField;
            unsigned int m_idConstraint;
    };
}

#endif // CONSTRAINED_HPP

