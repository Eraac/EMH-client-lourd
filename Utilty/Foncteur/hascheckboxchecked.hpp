#ifndef HASCHECKBOXCHECKED_HPP
#define HASCHECKBOXCHECKED_HPP

#include <QCheckBox>

namespace Utility
{
    class HasCheckBoxChecked
    {
        public:
            bool operator()(QCheckBox* checkbox) const; // Vérifie que la checkbox soit checkée
    };
}

#endif // HASCHECKBOXCHECKED_HPP
