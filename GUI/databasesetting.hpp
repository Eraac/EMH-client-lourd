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
        void formChange();  // Lorsque le formulaire change on appel cette méthode
        void valid();       // onClick sur le bouton Valider (enregistre les données dans le fichier INI)

    private:
        Ui::DatabaseSetting *ui;
        QSettings m_ini;
};

#endif // DATABASESETTING_HPP
