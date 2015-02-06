#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <QMainWindow>

#include "../Model/Entity/User.hpp"

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit LoginWindow(QWidget *parent = 0);
        ~LoginWindow();

    private:
        Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_HPP
