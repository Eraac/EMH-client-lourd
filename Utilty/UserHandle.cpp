#include "UserHandle.hpp"

UserHandle::UserHandle() : QWidget(), m_loginWidget(nullptr)
{

}

void UserHandle::run()
{
    // On initialise la fenêtre de connexion
    m_loginWidget = new LoginWindow;
        // On affiche la fenêtre
        m_loginWidget->show();

    // === On créer une liaison entre le bouton connect et la méthode connect ===
    QObject::connect(m_loginWidget, SIGNAL(connectUser(Entity::User)), this, SLOT(connect(Entity::User)));
}

void UserHandle::connect(Entity::User const& user)
{
    // La fenêtre va-t-être supprimée il faut retirer la liaison
    QObject::disconnect(m_loginWidget, SIGNAL(connectUser(Entity::User)), this, SLOT(connect(Entity::User)));

    // On supprime la fenêtre
    delete m_loginWidget;

    // Initialisation du tableau de bord
    //m_dashboard = new GUI::Dashboard(user);
        // On affiche le tableau de bord
        //m_dashboard->show();

    // On créer une liaison entre le bouton deconnexion et la méthode disconnect
    //QObject::connect(m_dashboard, SIGNAL(disconnect()), this, SLOT(disconnect()));
}

void UserHandle::disconnect()
{
    // La fenêtre va-t-être supprimée il faut retirer la liaison
    //QObject::disconnect(m_dashboard, SIGNAL(disconnect()), this, SLOT(disconnect()));

    // On supprime la fenêtre
    //delete m_dashboard;

    // On initialise la fenêtre de connexion
    m_loginWidget = new LoginWindow;
        // On affiche la fenêtre
        m_loginWidget->show();

    // === On créer une liaison entre le bouton connect et la méthode connect ===
    QObject::connect(m_loginWidget, SIGNAL(connectUser(Entity::User)), this, SLOT(connect(Entity::User)));
}
