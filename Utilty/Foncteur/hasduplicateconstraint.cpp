#include "hasduplicateconstraint.hpp"

void Utility::HasDuplicateConstraint::operator()(ConstraintWindow* constraint)
{
    if (m_types.contains(constraint->getType()))
        m_types[constraint->getType()]++;
    else
        m_types[constraint->getType()] = 1;
}

bool Utility::HasDuplicateConstraint::hasDuplicate() const
{
    return static_cast<bool> ( std::count_if(m_types.begin(), m_types.end(), isDuplicate) );
}

bool isDuplicate(int nb)
{
    return nb > 1;
}
