#include "chooseform.hpp"
#include "ui_chooseform.h"

ChooseForm::ChooseForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseForm),
    m_formName()
{
    ui->setupUi(this);
}

ChooseForm::~ChooseForm()
{
    delete ui;
}

void ChooseForm::setForms(QStringList listForms)
{
    ui->formulaireComboBox->addItems(listForms);
}

QString ChooseForm::getFormName() const
{
    return m_formName;
}

void ChooseForm::chooseForm()
{
    m_formName = ui->formulaireComboBox->currentText();
    close();
}
