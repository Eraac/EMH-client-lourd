#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <QMainWindow>

#include "../Model/Entity/User.hpp"
#include "../GUI/aboutmydevs.hpp"
#include "../GUI/databasesetting.hpp"

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit LoginWindow(QWidget *parent = 0);
        ~LoginWindow();

    signals:
        void connectUser(Entity::User const& user);

    public slots:
        void connectSlot();
        void formChange();
        void aboutMyDevs();

    private:
        Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_HPP
