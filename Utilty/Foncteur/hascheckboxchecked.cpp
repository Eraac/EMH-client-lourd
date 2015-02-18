#include "hascheckboxchecked.hpp"

bool Utility::HasCheckBoxChecked::operator()(QCheckBox* checkbox) const
{
    return checkbox->isChecked();
}
