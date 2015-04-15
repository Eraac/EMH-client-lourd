#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>
#include <QVariant>

const QString DB_ADDRESS = "address";
const QString DB_NAME = "name";
const QString DB_USERNAME = "username";
const QString DB_PASSWORD = "password";
const QString DB_PORT = "port";

class Settings
{
    public:
    Settings();

    QVariant getValue(QString const& key, QString const& defautValue = "");
    void setValue(QString const& key, QString const& value);

    private:
    QSettings m_ini;
};

#endif // SETTINGS_HPP
