#ifndef CREATEUSER_HPP
#define CREATEUSER_HPP

#include <QDialog>
#include "../Model/Entity/User.hpp"
#include "../Utilty/PersisterManager.hpp"

namespace Ui {
    class CreateUser;
}

class CreateUser : public QDialog
{
    Q_OBJECT

    public:
        explicit CreateUser(QWidget *parent = 0);
        ~CreateUser();

        void loadUser(Entity::User user);

    public slots:
        void valideUser();
        void formChange();

    private:
        Ui::CreateUser *ui;

        Entity::User m_user;
};

#endif // CREATEUSER_HPP
