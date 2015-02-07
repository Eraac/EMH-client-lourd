#include "databasesetting.hpp"
#include "ui_databasesetting.h"

DatabaseSetting::DatabaseSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSetting),
    m_ini("settings.ini", QSettings::IniFormat)
{
    ui->setupUi(this);

    ui->addressLineEdit->setText(m_ini.value(DB_ADDRESS, "server.com").toString());
    ui->identifiantLineEdit->setText(m_ini.value(DB_USERNAME, "root").toString());
    ui->passwordLineEdit->setText(m_ini.value(DB_PASSWORD, "root").toString());
    ui->portSpinBox->setValue(m_ini.value(DB_PORT, "3306").toInt());
}

DatabaseSetting::~DatabaseSetting()
{
    delete ui;
}

void DatabaseSetting::formChange()
{
    // Si tous les champs sont remplis on active le bouton valider
    if (!ui->addressLineEdit->text().isEmpty() &&
        !ui->identifiantLineEdit->text().isEmpty() &&
        !ui->passwordLineEdit->text().isEmpty() &&
        !ui->portSpinBox->text().isEmpty())
    {
        ui->validButton->setEnabled(true);
    }
    else {
        ui->validButton->setEnabled(false);
    }
}

void DatabaseSetting::valid()
{
    // On enregistre les informations
    m_ini.setValue(DB_ADDRESS, ui->addressLineEdit->text());
    m_ini.setValue(DB_USERNAME, ui->identifiantLineEdit->text());
    m_ini.setValue(DB_PASSWORD, ui->passwordLineEdit->text());
    m_ini.setValue(DB_PORT, ui->portSpinBox->value());

    // On ferme la fenêtre
    this->close();
}
