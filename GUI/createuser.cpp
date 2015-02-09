#include "createuser.hpp"
#include "ui_createuser.h"

CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser),
    m_user()
{
    ui->setupUi(this);

    m_listGroupsLayout = new QVBoxLayout();

    // On charge les groupes
    for (auto groupname : Entity::Group::getAll())
    {
        m_listGroups.append(new QCheckBox(groupname));
        ui->scrollAreaWidgetContents->setLayout(m_listGroupsLayout);
        m_listGroupsLayout->addWidget(m_listGroups.last());
    }
}

CreateUser::~CreateUser()
{
    delete ui;
}

void CreateUser::loadUser(Entity::User user)
{
    m_user = user;

    ui->nomLineEdit->setText(m_user.getName());
    ui->prenomLineEdit->setText(m_user.getFirstName());
    ui->emailLineEdit->setText(m_user.getEmail());
    ui->administrateurCheckBox->setChecked(m_user.isAdmin());

    // On parcourt la liste des groupes de l'utilisateur
    for (auto groupname : m_user.getGroupsName())
    {
        // On parcourt les groupes
        for (auto it = m_listGroups.begin(); it != m_listGroups.end(); ++it)
        {
            if ( (*it)->text() == groupname )
                (*it)->setChecked(true);
        }
    }
}

void CreateUser::valideUser()
{
    m_user.setName(ui->nomLineEdit->text());
    m_user.setFirstName(ui->prenomLineEdit->text());
    m_user.setEmail(ui->emailLineEdit->text());

    // Si l'utilisateur est nouveau OU si on rentre un nouveau mot de passe
    if (m_user.getId() == 0 || !ui->passwordLineEdit->text().isEmpty())
        m_user.setClearPassword(ui->passwordLineEdit->text());

    m_user.setIsAdmin(ui->administrateurCheckBox->isChecked());

    Utility::PersisterManager pm;

    pm.persistOne(m_user);

    this->close();
}

void CreateUser::formChange()
{
    QRegExp emailRegEx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
            emailRegEx.setCaseSensitivity(Qt::CaseInsensitive);
            emailRegEx.setPatternSyntax(QRegExp::RegExp);

    if (!ui->nomLineEdit->text().isEmpty() &&
        !ui->prenomLineEdit->text().isEmpty() &&
        !ui->emailLineEdit->text().isEmpty() &&
        (!ui->passwordLineEdit->text().isEmpty() || m_user.getId() != 0) &&
        emailRegEx.exactMatch( ui->emailLineEdit->text() ))
            ui->validButton->setEnabled(true);
    else
        ui->validButton->setEnabled(false);
}
