#include "dashboard.hpp"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}

unsigned int Dashboard::getUserId() const
{
    return m_user.getId();
}

void Dashboard::loadUser(Entity::User const& user)
{
    m_user = user;

    ui->footer->setText("EMH v1.0 - " + m_user.getEmail());
}

void Dashboard::setFailMessage(const QString &message)
{
    // Affiche un message rouge
    ui->message->setStyleSheet("color: red");
    ui->message->setText(message);
}

void Dashboard::setSuccessMessage(const QString &message)
{
    // Affiche un message vert
    ui->message->setStyleSheet("color: green");
    ui->message->setText(message);
}

void Dashboard::clickDisconnect()
{
    emit disconnect();
}

void Dashboard::addUser()
{
    // On instancie un objet pour créer un utilisateur et on l'execute
    CreateUser createUser;

    QObject::connect(&createUser, SIGNAL(userCreateSuccess()), this, SLOT(addUserSuccess()));

    createUser.exec();

    QObject::disconnect(&createUser, SIGNAL(userCreateSuccess()), this, SLOT(addUserSuccess()));
}

void Dashboard::addUserSuccess()
{
    setSuccessMessage("Utilisateur créé avec succès.");
}

void Dashboard::editUser()
{
    // Regex pour valider les emails
    QRegExp emailRegEx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
            emailRegEx.setCaseSensitivity(Qt::CaseInsensitive);
            emailRegEx.setPatternSyntax(QRegExp::RegExp);

    bool ok = false;

    // On récupère l'email de l'utilisateur que l'on souhaite modifier
    QString email = QInputDialog::getText(this, "Email", "Quel est l'email de l'utilisateur ?", QLineEdit::Normal, QString(), &ok);

    // Si on clique sur OK et que l'email est valide
    if (ok && !email.isEmpty() && emailRegEx.exactMatch(email))
    {
        // On instancie un User
        Entity::User user;

        // On charge l'utilisateur par son email
        auto error = user.loadUserByEmail(email);

        // Si aucune erreur pendant le chargement de l'utilisateur
        if (error == Entity::User::ErrorType::NONE)
        {
            // On lance la fenêtre pour éditer l'utilisateur
            CreateUser editUser;

            QObject::connect(&editUser, SIGNAL(userEditSuccess()), this, SLOT(editUserSuccess()));
            QObject::connect(&editUser, SIGNAL(userDeleteSuccess()), this, SLOT(userDeleteSuccess()));

            editUser.loadUser(user);
            editUser.exec();

            QObject::disconnect(&editUser, SIGNAL(userEditSuccess()), this, SLOT(editUserSuccess()));
            QObject::disconnect(&editUser, SIGNAL(userDeleteSuccess()), this, SLOT(userDeleteSuccess()));
        }
        // Si une erreur arrive
        else
        {
            // On indique à l'utilisateur
            QMessageBox::warning(this, "Utilisateur introuvable", "L'utilisateur " + email + " est introuvable.");
        }

    }

}

void Dashboard::editUserSuccess()
{
    setSuccessMessage("Utilisateur modifié avec succès.");
}

void Dashboard::userDeleteSuccess()
{
    setSuccessMessage("Utilisateur supprimé avec succès.");
}

void Dashboard::addGroup()
{
    bool ok = false;

    QString groupname = QInputDialog::getText(this, "Ajouter un groupe", "Quel est le nom du nouveau groupe ?", QLineEdit::Normal, QString(), &ok);

    // Si on clique sur ok et que le nom du groupe n'est pas vide
    if (ok && !groupname.isEmpty())
    {
        // Si le nom n'est pas déjà pris
        if (!Entity::Group::groupExist(groupname))
        {
            // On créer le groupe
            Entity::Group group;
                group.setName(groupname);

            Utility::PersisterManager pm;

            pm.persistOne(group);

            setSuccessMessage("Le groupe " + groupname + " est bien créé.");
        }
        else
        {
            setFailMessage("Le groupe " + groupname + " existe déjà.");
        }
    }
}

void Dashboard::editGroup()
{
    bool ok = false;

    // On demande le nom du groupe
    QString groupname = QInputDialog::getText(this, "Modifier un groupe", "Quel est le nom du nouveau groupe ?", QLineEdit::Normal, QString(), &ok);

    // Si l'utilisateur à cliqué sur OK et que le nom du groupe n'est pas vide
    if (ok && !groupname.isEmpty())
    {
        // Si groupe existe bien
        if (Entity::Group::groupExist(groupname))
        {
            // On demande le nouveau nom du groupe
            QString newGroupname = QInputDialog::getText(this, "Nouveau nom", "Quel est le nouveau nom pour le groupe ?", QLineEdit::Normal, QString(), &ok);

            // Si l'utilisateur à cliqué sur OK et que le nom du groupe n'est pas vide
            if (ok && !newGroupname.isEmpty())
            {
                // Le nouveau nom n'existe pas déjà
                if (!Entity::Group::groupExist(newGroupname))
                {
                    // On charge le groupe
                    Entity::Group group;
                        group.loadByName(groupname);
                        group.setName(newGroupname);

                    Utility::PersisterManager pm;
                    pm.persistOne(group);

                    setSuccessMessage("Le groupe " + groupname + " à bien été changé.");
                }
                else
                {
                    setFailMessage("Le groupe " + groupname + " existe déjà.");
                }
            }
        }
        else
        {
            setFailMessage("Le groupe " + groupname + " n'existe pas.");
        }
    }
}

void Dashboard::addForm()
{
    createForm createForm(this);
        createForm.exec();
}

void Dashboard::editForm()
{

}
