#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
#include "../GUI/createuser.hpp"
#include "../GUI/createform.hpp"
#include "../GUI/chooseform.hpp"
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

        void loadUser(Entity::User const& user);        // Charge un utilisateur
        void setFailMessage(QString const& message);    // Affiche un message d'erreur
        void setSuccessMessage(QString const& message); // Affiche un message de succès
        unsigned int getUserId() const;                 // Retourne l'id de l'utilisateur

    signals:
        void disconnect();  // Ferme la fenêtre

    public slots:
        void clickDisconnect(); // onClick sur le bouton Déconnecter

        void addUser();             // onClick sur le bouton Ajouter utilisateur
        void addUserSuccess();      // Lorsque l'utilisateur est créé avec succès
        void editUser();            // onClick sur le bouton Modifier utilisateur
        void editUserSuccess();     // Lorsque l'utilisateur est modifié avec succès
        void userDeleteSuccess();   // Lorsque l'utilisateur est supprimé avec succès

        void addGroup();    // onClick sur le bouton Ajouter un groupe
        void editGroup();   // onClick sur le bouton Modifier un groupe

        void addForm();     // onClick sur le bouton Ajouter un formulaire
        void editForm();    // onClick sur le bouton Modifier un formulaire

    private:
        Ui::Dashboard *ui;
        Entity::User m_user;                
};

#endif // DASHBOARD_HPP
