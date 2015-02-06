#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../GUI/loginwindow.hpp"

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
    //GUI::Dashboard      *m_dashboard;     // Tableau de bord

};


#endif // MAINWINDOW_HPP
