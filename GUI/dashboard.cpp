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

void Dashboard::loadUser(Entity::User const& user)
{
    m_user = user;

    ui->footer->setText("EMH v1.0 - " + m_user.getEmail());
}

void Dashboard::setFailMessage(const QString &message)
{
    ui->message->setStyleSheet("color: red");
    ui->message->setText(message);
}

void Dashboard::setSuccessMessage(const QString &message)
{
    ui->message->setStyleSheet("color: green");
    ui->message->setText(message);
}

void Dashboard::clickDisconnect()
{
    emit disconnect();
}

void Dashboard::addUser()
{
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
    QRegExp emailRegEx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
            emailRegEx.setCaseSensitivity(Qt::CaseInsensitive);
            emailRegEx.setPatternSyntax(QRegExp::RegExp);

    bool ok = false;

    QString email = QInputDialog::getText(this, "Email", "Quel est l'email de l'utilisateur ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !email.isEmpty() && emailRegEx.exactMatch(email))
    {
        Entity::User user;

        auto error = user.loadUserByEmail(email);

        if (error == Entity::User::ErrorType::NONE)
        {
            CreateUser editUser;

            QObject::connect(&editUser, SIGNAL(userEditSuccess()), this, SLOT(editUserSuccess()));
            QObject::connect(&editUser, SIGNAL(userDeleteSuccess()), this, SLOT(userDeleteSuccess()));

            editUser.loadUser(user);
            editUser.exec();

            QObject::disconnect(&editUser, SIGNAL(userEditSuccess()), this, SLOT(editUserSuccess()));
            QObject::disconnect(&editUser, SIGNAL(userDeleteSuccess()), this, SLOT(userDeleteSuccess()));
        }
        else
        {
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

    if (ok && !groupname.isEmpty())
    {
        if (!Entity::Group::groupExist(groupname))
        {
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

    QString groupname = QInputDialog::getText(this, "Ajouter un groupe", "Quel est le nom du nouveau groupe ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !groupname.isEmpty())
    {
        // Le groupe existe bien
        if (Entity::Group::groupExist(groupname))
        {
            groupname = QInputDialog::getText(this, "Nouveau nom", "Quel est le nouveau nom pour le groupe ?", QLineEdit::Normal, QString(), &ok);

            if (ok && !groupname.isEmpty())
            {
                // Le nouveau nom n'existe pas déjà
                if (!Entity::Group::groupExist(groupname))
                {
                    Entity::Group group;
                        group.loadByName(groupname);

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

}

void Dashboard::editForm()
{

}
