#include "chooseuser.hpp"
#include "ui_chooseuser.h"

ChooseUser::ChooseUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseUser),
    m_email()
{
    ui->setupUi(this);
}

ChooseUser::~ChooseUser()
{
    delete ui;
}

void ChooseUser::setUsers(QStringList listUsers)
{
    ui->usersComboBox->addItems(listUsers);
}

QString ChooseUser::getUserEmail() const
{
    return m_email;
}

void ChooseUser::chooseUser()
{
    m_email = ui->usersComboBox->currentText();
    close();
}
