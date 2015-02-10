#include "createform.hpp"
#include "ui_createform.h"


createForm::createForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createForm), m_color(Qt::white)
{
    ui->setupUi(this);
}


createForm::~createForm()
{
    delete ui;
}

void createForm::chooseColor()
{
    m_color = QColorDialog::getColor(m_color);
}
