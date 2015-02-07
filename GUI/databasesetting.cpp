#include "databasesetting.hpp"
#include "ui_databasesetting.h"

DatabaseSetting::DatabaseSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSetting)
{
    ui->setupUi(this);
}

DatabaseSetting::~DatabaseSetting()
{
    delete ui;
}
