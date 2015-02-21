#ifndef CONSTRAINTWINDOW_HPP
#define CONSTRAINTWINDOW_HPP

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QRegExp>
#include <array>
#include "../Utilty/PersisterManager.hpp"
#include "../Model/Entity/Field.hpp"
#include "../Model/Entity/Constraint.hpp"
#include "../Model/Relation/Require.hpp"
#include "../Model/Entity/param.hpp"

namespace Ui {
    class ConstraintWindow;
}

class ConstraintWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit ConstraintWindow(bool* ok, QWidget *parent = 0);
        ~ConstraintWindow();

        QString getTypeReadable() const;            // Retourne le type de la contrainte en QString
        Entity::Constraint::Type getType() const;   // Retourne le type de la contrainte sous forme d'enum
        void persistConstraint(int idField);        // Persit la contrainte

        bool validConstraint(Entity::Field::Type fieldType, QString const& label); // Vérifie que la contrainte est valide

    signals:
        void sendError(QString message); // Envoi un message d'erreur en cas de contrainte non valide

    public slots:
        void selectChange(int type);    // Lorsque le select change on appel cette méthode (pour changer un input dans le form)
        void valid();                   // Méthode appeler quand on ferme la fenêtre avec le bouton "Valider"

    private:
        Ui::ConstraintWindow *ui;
        bool *m_ok;
        int m_nbParams;

        Entity::Constraint m_constraint;        // Contient la contrainte
        std::array<Entity::Param, 2> m_params;  // Contient les paramètres nécessaire à la contrainte
        std::array<QLabel*, 2> m_labels;        // Les labels pour les lineEdits
        std::array<QLineEdit*, 2> m_lineEdits;  // Input pour entrer les paremètres de la contrainte

        void cleanForm(); // Vide les paramètres quand on change de type de contrainte
};

#endif // CONSTRAINTWINDOW_HPP
