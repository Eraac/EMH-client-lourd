#include "Settings.hpp"

Settings::Settings() : m_ini("settings.ini", QSettings::IniFormat)
{

}

QVariant Settings::getValue(QString const& key, QString const& defautValue)
{
    return m_ini.value(key, defautValue);
}

void Settings::setValue(const QString &key, const QString &value)
{
    m_ini.setValue(key, value);
}
