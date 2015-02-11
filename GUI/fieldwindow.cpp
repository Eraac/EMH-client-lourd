#include "fieldwindow.hpp"
#include "ui_fieldwindow.h"

fieldWindow::fieldWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fieldWindow)
{
    ui->setupUi(this);
}

fieldWindow::~fieldWindow()
{
    delete ui;
}
