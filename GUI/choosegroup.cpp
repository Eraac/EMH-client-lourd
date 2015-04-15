#include "choosegroup.hpp"
#include "ui_choosegroup.h"

ChooseGroup::ChooseGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseGroup),
    m_groupName()
{
    ui->setupUi(this);
}

ChooseGroup::~ChooseGroup()
{
    delete ui;
}

void ChooseGroup::setGroups(const QStringList &listGroups)
{
    ui->groupsComboBox->addItems(listGroups);
}

QString ChooseGroup::getGroupName() const
{
    return m_groupName;
}

void ChooseGroup::chooseGroups()
{
    m_groupName = ui->groupsComboBox->currentText();
    close();
}
