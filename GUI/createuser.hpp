#ifndef CREATEUSER_HPP
#define CREATEUSER_HPP

#include <QDialog>
#include <QList>
#include <QCheckBox>
#include <memory>
#include <QVBoxLayout>
#include <QPushButton>
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

        void loadUser(Entity::User user);   // Charge un utilisateur

    public slots:
        void valideUser();  // Persist l'utilisateur si il est valide
        void deleteUser();  // Supprime l'utilisateur
        void formChange();  // Méthode qui vérifie que l'email est un email et que le mot de passe est fournis

    signals:
        void userCreateSuccess();   // Emit lors de la création d'un utilisateur en cas de succès
        void userEditSuccess();     // Emit lors de la modification d'un utilisateur avec succès
        void userDeleteSuccess();   // Emit lors de la suppression d'un utilisateur avec succès

    private:
        Ui::CreateUser *ui;

        Entity::User m_user;                // Contient l'utilisateur
        bool newUser;                       // True si l'utilisateur est nouveau
        QList<QCheckBox*> m_listGroups;     // Contient les groupes de l'utilisateur
        QVBoxLayout *m_listGroupsLayout;    // Layout qui contient les groupes disponible
        QPushButton *m_deleteUserButton;    // Bouton pour supprimer l'utilisateur
};

#endif // CREATEUSER_HPP
