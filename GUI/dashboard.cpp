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

void Dashboard::clickDisconnect()
{
    emit disconnect();
}

void Dashboard::addUser()
{
    CreateUser createUser;
        createUser.exec();
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
                editUser.loadUser(user);
                editUser.exec();
        }
        else
        {
            QMessageBox::warning(this, "Utilisateur introuvable", "L'utilisateur " + email + " est introuvable.");
        }

    }

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

            QMessageBox::information(this, "Groupe créé", "Le groupe " + groupname + " est bien créé.");
        }
        else
        {
            QMessageBox::warning(this, "Groupe existant", "Le groupe " + groupname + " existe déjà.");
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

                    QMessageBox::information(this, "Groupe changé", "Le groupe " + groupname + " à bien été changé.");
                }
                else
                {
                    QMessageBox::warning(this, "Groupe existant", "Le groupe " + groupname + " existe déjà.");
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "Groupe inexistant", "Le groupe " + groupname + " n'existe pas.");
        }
    }
}

void Dashboard::addForm()
{

}

void Dashboard::editForm()
{

}
