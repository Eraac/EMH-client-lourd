#ifndef ENCODEPASSWORD_HPP
#define ENCODEPASSWORD_HPP

#include <QCryptographicHash>
#include <QString>

namespace Utility
{
    class EncodePassword
    {
        public:
        QString encodePassword(QString const& pPassword, QString const& pSalt = "");

        private:
        QString mergePasswordAndSalt(QString const& pPassword, QString const& pSalt);
    };
}

#endif // ENCODEPASSWORD_HPP

