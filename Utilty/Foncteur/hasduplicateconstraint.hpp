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

            bool hasDuplicate() const;

        private:
            QMap<Entity::Constraint::Type, int> m_types;
    };
}

bool isDuplicate(int nb);

#endif // HASDUPLICATECONSTRAINT_HPP

