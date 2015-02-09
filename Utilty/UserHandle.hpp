#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../GUI/loginwindow.hpp"
#include "../GUI/dashboard.hpp"

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
    LoginWindow *m_loginWidget;
    Dashboard   *m_dashboard;

};


#endif // MAINWINDOW_HPP
