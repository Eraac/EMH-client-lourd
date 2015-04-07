#ifndef FIELDWINDOW_HPP
#define FIELDWINDOW_HPP

#include <algorithm>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QDialog>
#include <QList>
#include <QMap>
#include "../GUI/customqpushbutton.hpp"
#include "../GUI/constraintwindow.hpp"
#include "../Model/Entity/Field.hpp"
#include "../Model/Entity/DefaultValue.hpp"
#include "../Model/Relation/Require.hpp"
#include "../Model/Relation/Contains.hpp"
#include "../Utilty/PersisterManager.hpp"
#include "../Utilty/Foncteur/hasduplicateconstraint.hpp"

namespace Ui {
    class fieldWindow;
}

class fieldWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit fieldWindow(QWidget *parent = 0, bool *ok = nullptr);
        ~fieldWindow();

        void persistField(int idForm);  // Persist le champs
        void load(Entity::Field field); // Charge un champs

        Entity::Field getField() const; // Retourne le champs
        int getNbConstraint() const;    // Retourne le nombre de contraintes liées au champs

        bool validField();      // Retourne true si le champs est valide

    signals:
        void sendError(QString message); // Envoi un message d'erreur à la fenêtre createForm

    public slots:
        void valid();                   // onClick sur le bouton Valider
        void addConstraint();           // Ajoute une contrainte sur le champs
        void editConstraint(int id);    // Edite une contrainte
        void deleteConstraint(int id);  // Supprime une contrainte
        void selectChange(int id);      // Méthode appelé quand le formulaire change

    private:
        Ui::fieldWindow *ui;
        bool *m_ok;

        Entity::Field m_field;  // Contient le champs

        QLineEdit *m_defaultValueLineEdit; // Pour les valeurs par défaut des champs qui ne sont pas TYPE::RADIO
        QTextEdit *m_defaultValueTextEdit; // Pour les valeurs par défaut des champs qui sont TYPE::RADIO

        QVBoxLayout *m_constraintLayout;

        int m_nbField;
        QMap<int, ConstraintWindow*> m_constraintsWindow;
        QMap<int, QHBoxLayout*> m_lines;
        QMap<int, CustomQPushButton*> m_edits;
        QMap<int, CustomQPushButton*> m_deletes;
};

#endif // FIELDWINDOW_HPP
