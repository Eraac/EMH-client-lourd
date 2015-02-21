#ifndef HASDUPLICATECONSTRAINT_HPP
#define HASDUPLICATECONSTRAINT_HPP

#include <algorithm>
#include <QMap>
#include "../../Model/Entity/Constraint.hpp"
#include "../../GUI/constraintwindow.hpp"

namespace Utility
{
    class HasDuplicateConstraint
    {
        public:
            void operator()(ConstraintWindow* constraint);

            bool hasDuplicate() const; // Prédicat pour savoir si un élèment est présent plusieurs fois

        private:
            QMap<Entity::Constraint::Type, int> m_types; // Contient la liste des types présent dans la liste
    };
}

bool isDuplicate(int nb);

#endif // HASDUPLICATECONSTRAINT_HPP

