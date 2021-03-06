#include "loginwindow.hpp"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // On connecte les boutons du menu au bon SLOT
    QObject::connect(ui->actionChangeDatabase, SIGNAL(triggered()), this, SLOT(changeSettings()));
    QObject::connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QObject::connect(ui->actionAboutMyDev_s, SIGNAL(triggered()), this, SLOT(aboutMyDevs()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::connectSlot()
{
    auto error = Entity::User::ErrorType::NONE;

    Entity::User user = Entity::User();

    // On charge l'utilisateur
    error = user.loadUserByLogin(
                ui->emailLineEdit->text(),
                ui->passwordLineEdit->text()
            );

    // Si aucun problème on émet un signal avec l'utilisateur    
    if (Entity::User::ErrorType::NONE == error) {
        if (user.isAdmin())
            emit connectUser(user);
        else
            ui->errorLogin->setText("Ce compte n'est pas autorisé");
    }
    // Si on trouve pas l'utilisateur on l'indique à l'utilisateur
    else if (Entity::User::ErrorType::NOT_FOUND == error) {
        ui->errorLogin->setText("Compte inexistant");
    }
    // Sinon il y a eu un problème
    else {
        ui->errorLogin->setText("Connexion avec la <br>base de données impossible");
    }

}

void LoginWindow::formChange()
{
    // Avant d'activer le bouton connecter on s'assure que nous avons bien un email
    // ET un "mot de passe"

    QRegExp emailRegEx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
            emailRegEx.setCaseSensitivity(Qt::CaseInsensitive);
            emailRegEx.setPatternSyntax(QRegExp::RegExp);

    this->ui->connectButton->setEnabled(
                emailRegEx.exactMatch( ui->emailLineEdit->text() ) &&
                !ui->passwordLineEdit->text().isEmpty()
    );

}

void LoginWindow::aboutMyDevs()
{
    AboutMyDevs about;
    about.exec();
}

void LoginWindow::changeSettings()
{
    DatabaseSetting settings;
    settings.exec();
}
