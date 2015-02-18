#ifndef HASCHECKBOXCHECKED_HPP
#define HASCHECKBOXCHECKED_HPP

#include <QCheckBox>

namespace Utility
{
    class HasCheckBoxChecked
    {
        public:
            bool operator()(QCheckBox* checkbox) const;
    };
}

#endif // HASCHECKBOXCHECKED_HPP
