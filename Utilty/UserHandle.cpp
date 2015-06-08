#include "UserHandle.hpp"

UserHandle::UserHandle() : QWidget(), m_loginWidget(nullptr), m_dashboard(nullptr), m_session()
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

    // On log la connexion de l'utilisateur
    m_session.setUserId(user.getId());
    m_session.setLogin(QDateTime::currentDateTime());

    Utility::PersisterManager pm{};
        pm.persistOne(m_session);

    // Initialisation du tableau de bord
    m_dashboard = new Dashboard;
        // On charge l'utilisateur dans le tableau de bord
        m_dashboard->loadUser(user);
        // On affiche le tableau de bord
        m_dashboard->show();

    // On créer une liaison entre le bouton deconnexion et la méthode disconnect
    QObject::connect(m_dashboard, SIGNAL(disconnect()), this, SLOT(disconnect()));
}

void UserHandle::disconnect()
{
    // La fenêtre va-t-être supprimée il faut retirer la liaison
    QObject::disconnect(m_dashboard, SIGNAL(disconnect()), this, SLOT(disconnect()));

    // On supprime la fenêtre
    delete m_dashboard;

    // On log la deconnexion de l'utilisateur
    m_session.setLogout(QDateTime::currentDateTime());
    Utility::PersisterManager pm{};
        pm.persistOne(m_session);

    // On initialise la fenêtre de connexion
    m_loginWidget = new LoginWindow;
        // On affiche la fenêtre
        m_loginWidget->show();

    // === On créer une liaison entre le bouton connect et la méthode connect ===
    QObject::connect(m_loginWidget, SIGNAL(connectUser(Entity::User)), this, SLOT(connect(Entity::User)));
}
