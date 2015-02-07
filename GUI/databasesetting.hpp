#ifndef DATABASESETTING_HPP
#define DATABASESETTING_HPP

#include <QDialog>
#include <QSettings>
#include <QString>

const QString DB_ADDRESS = "address";
const QString DB_USERNAME = "username";
const QString DB_PASSWORD = "password";
const QString DB_PORT = "port";

namespace Ui {
    class DatabaseSetting;
}

class DatabaseSetting : public QDialog
{
    Q_OBJECT

    public:
        explicit DatabaseSetting(QWidget *parent = 0);
        ~DatabaseSetting();

    public slots:
        void formChange();
        void valid();

    private:
        Ui::DatabaseSetting *ui;
        QSettings m_ini;
};

#endif // DATABASESETTING_HPP
