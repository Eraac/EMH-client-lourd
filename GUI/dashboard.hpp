#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <QWidget>
#include "../GUI/createuser.hpp"
#include "../Model/Entity/User.hpp"

namespace Ui {
    class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

    public:
        explicit Dashboard(QWidget *parent = 0);
        ~Dashboard();

        void loadUser(Entity::User const& user);

    signals:
        void disconnect();

    public slots:
        void clickDisconnect();
        void addUser();
        void editUser();
        void addGroup();
        void editGroup();
        void addForm();
        void editForm();

    private:
        Ui::Dashboard *ui;

        Entity::User m_user;
};

#endif // DASHBOARD_HPP
