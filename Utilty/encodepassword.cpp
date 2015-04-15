#include "encodepassword.hpp"

QString Utility::EncodePassword::encodePassword(const QString &pPassword, const QString &pSalt)
{
    QString salted = mergePasswordAndSalt(pPassword, pSalt);

    QCryptographicHash hash(QCryptographicHash::Sha512);

    hash.addData(salted.toUtf8());

    auto digest = hash.result();

    for (int i = 1; i < 5000; i++)
    {
        hash.reset();
        hash.addData(digest.append(salted));
        digest = hash.result();
    }

    return digest.toBase64();
}

QString Utility::EncodePassword::mergePasswordAndSalt(const QString &pPassword, const QString &pSalt)
{
    if (pSalt.isEmpty())
        return pPassword;

    return pPassword + '{' + pSalt + '}';
}
