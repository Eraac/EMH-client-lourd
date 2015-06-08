#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../GUI/loginwindow.hpp"
#include "../GUI/dashboard.hpp"
#include "../Model/Entity/session.hpp"
#include "PersisterManager.hpp"

class UserHandle : public QWidget
{
    Q_OBJECT

    public:
    UserHandle();                           // Constructeur

    void run();                             // Point de démarrage de l'application

    public slots:
    void connect(Entity::User const& user); // Change la fenêtre (passe du login au tableau de bord)
    void disconnect();                      // Change la fenêtre (passe du tableau de bord au login)

    private:
    LoginWindow     *m_loginWidget;
    Dashboard       *m_dashboard;
    Entity::Session m_session;

};


#endif // MAINWINDOW_HPP
