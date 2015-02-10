#include "createuser.hpp"
#include "ui_createuser.h"


CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser),
    m_user(), newUser(true), m_deleteUserButton(nullptr)
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
    newUser = false;

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
            if ( (*it)->text() == groupname ) {
                (*it)->setChecked(true);
                continue;
            }
        }
    }

    m_deleteUserButton = new QPushButton("Supprimer");

    ui->formLayout->addWidget(m_deleteUserButton);
    ui->emailLineEdit->setEnabled(false);

    QObject::connect(m_deleteUserButton, SIGNAL(clicked()), this, SLOT(deleteUser()));
}

void CreateUser::valideUser()
{
    if (Entity::User::emailExist(ui->emailLineEdit->text()) && newUser)
    {
        ui->message->setText("L'email existe déjà");
    }
    else
    {
        m_user.setName(ui->nomLineEdit->text());
        m_user.setFirstName(ui->prenomLineEdit->text());

        if (!newUser)
            m_user.setEmail(ui->emailLineEdit->text());

        // Si l'utilisateur est nouveau OU si on rentre un nouveau mot de passe
        if (m_user.getId() == 0 || !ui->passwordLineEdit->text().isEmpty())
            m_user.setClearPassword(ui->passwordLineEdit->text());

        m_user.setIsAdmin(ui->administrateurCheckBox->isChecked());

        Utility::PersisterManager pm;

        pm.persistOne(m_user);

        // Déterminer les nouveaux est anciens groupes
        QList<Entity::Group> newGroups;
        QList<Entity::Group> oldGroups;

        // Boucle pour connaitre les nouveaux groupes
        // On parcourt les groupes
        for (auto it = m_listGroups.begin(); it != m_listGroups.end(); ++it)
        {
            // Si le groupe est coché
            if ( (*it)->isChecked() )
            {
                // Indiicateur pour savoir si il aussi dans les groupes de l'utilisateur
                bool find = false;

                // On parcourt les groupes de l'utilisateur
                for (auto groupname : m_user.getGroupsName())
                {
                    // Si on trouve le même nom de groupe dans ceux de l'utilisateur
                    if ( (*it)->text() == groupname ) {
                        find = true;
                        break; // On quitte la boucle
                    }
                }

                // Si on a rien trouvé
                if (!find)
                {
                    // On instancie un groupe
                    Entity::Group group;
                        // On charge le groupe par son nom
                        group.loadByName((*it)->text());

                    // On l'ajoute à la liste des nouveaux groupes
                    newGroups.append(group);
                }
            }
        }

        // Boucle pour connaitre les groupes retirés
        // On parcourt la liste des groupes de l'utilisateur
        for (auto groupname : m_user.getGroupsName())
        {
            bool find = false;

            // On parcourt la liste des groupes
            for (auto it = m_listGroups.begin(); it != m_listGroups.end(); ++it)
            {
                // Si le groupe est coché est corresponds au groupe de l'utilisateur
                if ( (*it)->isChecked() && (*it)->text() == groupname)
                {
                    find = true;
                    break;
                }
            }

            // Si on trouve pas de groupe associé
            if (!find)
            {
                Entity::Group group;
                    group.loadByName(groupname);

                oldGroups.append(group);
            }
        }

        // On persist un base les nouveaux groupes
        for (auto it = newGroups.begin(); it != newGroups.end(); ++it)
        {
            Relation::Belong belong;
                belong.setIdUser(m_user.getId());
                belong.setIdGroup((*it).getId());

            pm.persistOne(belong);
        }

        // On supprime les anciens groupes à l'utilisateur
        for (auto it = oldGroups.begin(); it != oldGroups.end(); ++it)
        {
            Relation::Belong belong;
                belong.setIdUser(m_user.getId());
                belong.setIdGroup((*it).getId());

            belong.remove();
        }

        if (newUser)
            emit userCreateSuccess();
        else
            emit userEditSuccess();

        this->close();
    }
}

void CreateUser::deleteUser()
{
    m_user.remove();

    emit userDeleteSuccess();

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
