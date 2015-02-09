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

}

void Dashboard::editGroup()
{

}

void Dashboard::addForm()
{

}

void Dashboard::editForm()
{

}
