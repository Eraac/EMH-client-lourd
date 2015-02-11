#ifndef PARAM_HPP
#define PARAM_HPP

#include <QString>

namespace Entity
{
    class Param : public Entity
    {
        public:
            Param();
            virtual ~Param();

            static const int weight();

            void setValue(QString const& value);
            void setIdConstraint(int id);

            QString getValue() const;
            int getIdConstraint() const;

        private:
            QString m_value;
            int m_idConstraint;
    };
}

#endif // PARAM_HPP

