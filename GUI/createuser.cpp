#include "createuser.hpp"
#include "ui_createuser.h"


CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser),
    m_user(), newUser(true), m_deleteUserButton(nullptr)
{
    ui->setupUi(this);

    m_listGroupsLayout = new QVBoxLayout();
    ui->scrollAreaWidgetContents->setLayout(m_listGroupsLayout);

    Entity::Group group;

    // On charge les groupes
    for (auto groupname : group.getAll())
    {
        m_listGroups.append(new QCheckBox(groupname));        
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

    // On charge les données de l'utilisateur dans le formulaire
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
            // Si un groupe correspond
            if ( (*it)->text() == groupname ) {
                // On check la QCheckBox
                (*it)->setChecked(true);
                continue;
            }
        }
    }

    // On ajoute le bouton supprimer
    m_deleteUserButton = new QPushButton("Supprimer");

    // On l'ajouter au layout
    ui->formLayout->addWidget(m_deleteUserButton);

    // On désactive l'édition de l'email de l'utilisateur
    ui->emailLineEdit->setEnabled(false);

    QObject::connect(m_deleteUserButton, SIGNAL(clicked()), this, SLOT(deleteUser()));
}

void CreateUser::valideUser()
{
    // On vérifie que l'emaim n'existe pas si l'utilisateur est nouveau
    if (Entity::User::emailExist(ui->emailLineEdit->text()) && newUser)
    {
        ui->message->setText("L'email existe déjà");
    }
    else
    {
        m_user.setName(ui->nomLineEdit->text());
        m_user.setFirstName(ui->prenomLineEdit->text());

        // Si l'utilisateur est nouveau on stocke son email dans l'objet User
        if (newUser)
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

        // On envoi le bon signal si l'utilisateur est nouveau ou pas
        if (newUser)
            emit userCreateSuccess();
        else
            emit userEditSuccess();

        // On ferme la fenêtre
        close();
    }
}

void CreateUser::deleteUser()
{
    // On supprime l'utilisateur
    m_user.remove();

    // On envoi un signal pour indique la suppression
    emit userDeleteSuccess();

    // On ferme la fenêtre
    close();
}

void CreateUser::formChange()
{
    // Regex pour valider les emails
    QRegExp emailRegEx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
            emailRegEx.setCaseSensitivity(Qt::CaseInsensitive);
            emailRegEx.setPatternSyntax(QRegExp::RegExp);

    // Si le nom et le prénom et le mail et mot de passe sont vide ET email non valide alors on active le bouton valider
    if (!ui->nomLineEdit->text().isEmpty() &&
        !ui->prenomLineEdit->text().isEmpty() &&
        !ui->emailLineEdit->text().isEmpty() &&
        (!ui->passwordLineEdit->text().isEmpty() || m_user.getId() != 0) &&
        emailRegEx.exactMatch( ui->emailLineEdit->text() ))
            ui->validButton->setEnabled(true);
    else
        ui->validButton->setEnabled(false);
}
