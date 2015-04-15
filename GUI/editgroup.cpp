#include "editgroup.hpp"
#include "ui_editgroup.h"

EditGroup::EditGroup(QString const& groupName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGroup),
    m_oldGroupName(groupName)
{
    ui->setupUi(this);
}

EditGroup::~EditGroup()
{
    delete ui;
}

void EditGroup::enableButton(QString text)
{
    ui->changeButton->setEnabled(!text.isEmpty());
}

void EditGroup::deleteGroup()
{
    Entity::Group group{};
        group.loadByName(m_oldGroupName);
        group.remove();

    close();
}

void EditGroup::changeGroup()
{
    QString newGroupName = ui->nomLineEdit->text();

    Entity::Group group{};

    if (!group.groupExist(newGroupName))
    {
        group.loadByName(m_oldGroupName);
        group.setName(newGroupName);

        Utility::PersisterManager pm;
            pm.persistOne(group);

        emit groupModified();

        close();
    }
    else
    {
        ui->errorLabel->setText("Ce nom de groupe existe déjà");
    }
}
