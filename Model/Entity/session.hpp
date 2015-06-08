#ifndef SESSION_HPP
#define SESSION_HPP

#include <QDateTime>
#include "Entity.hpp"

namespace Entity
{
    class Session : public Entity
    {
        public:
        Session();
        virtual ~Session();

        static const int weight;

        Entity::ErrorType load(unsigned int id);

        void setUserId(unsigned int const userId);
        void setLogin(QDateTime const& datetime);
        void setLogout(QDateTime const& datetime);

        virtual int getWeight() const;

        virtual void persist() override;
        virtual bool isValid() const;
        virtual void remove() override;

        private:
        QDateTime m_login;
        QDateTime m_logout;
        unsigned int m_userId;
    };
}

#endif // SESSION_HPP

