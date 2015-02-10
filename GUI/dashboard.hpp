#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
#include "../GUI/createuser.hpp"
#include "../Model/Entity/User.hpp"
#include "../Utilty/PersisterManager.hpp"

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
        void setFailMessage(QString const& message);
        void setSuccessMessage(QString const& message);

    signals:
        void disconnect();

    public slots:
        void clickDisconnect();

        void addUser();
        void addUserSuccess();
        void editUser();
        void editUserSuccess();
        void userDeleteSuccess();

        void addGroup();
        void editGroup();

        void addForm();
        void editForm();

    private:
        Ui::Dashboard *ui;
        Entity::User m_user;                
};

#endif // DASHBOARD_HPP
