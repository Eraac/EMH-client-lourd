#ifndef DATABASESETTING_HPP
#define DATABASESETTING_HPP

#include <QDialog>
#include <QString>
#include "Utilty/Settings.hpp"

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
        Settings m_ini;
};

#endif // DATABASESETTING_HPP
