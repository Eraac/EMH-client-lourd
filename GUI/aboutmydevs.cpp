#include "aboutmydevs.h"
#include "ui_aboutmydevs.h"

AboutMyDevs::AboutMyDevs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMyDevs)
{
    ui->setupUi(this);
}

AboutMyDevs::~AboutMyDevs()
{
    delete ui;
}
