#ifndef CREATEUSER_HPP
#define CREATEUSER_HPP

#include <QDialog>
#include <QList>
#include <QCheckBox>
#include <memory>
#include <QVBoxLayout>
#include "../Model/Entity/User.hpp"
#include "../Model/Entity/Group.hpp"
#include "../Model/Relation/Belong.hpp"
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

    signals:
        void userCreateSuccess();
        void userEditSuccess();

    private:
        Ui::CreateUser *ui;

        Entity::User m_user;
        bool newUser;
        QList<QCheckBox*> m_listGroups;
        QVBoxLayout *m_listGroupsLayout;
};

#endif // CREATEUSER_HPP
