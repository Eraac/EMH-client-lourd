#ifndef CREATEFORM_HPP
#define CREATEFORM_HPP

#include <algorithm>
#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QList>
#include <QMap>
#include <QCheckBox>
#include "customqpushbutton.hpp"
#include "../Model/Entity/Form.hpp"
#include "../Model/Entity/Group.hpp"
#include "../Model/Entity/Tag.hpp"
#include "../Model/Relation/Belong.hpp"
#include "../Model/Relation/Write.hpp"
#include "../Model/Relation/Read.hpp"
#include "../Model/Relation/Categorizing.hpp"
#include "../GUI/dashboard.hpp"
#include "../GUI/fieldwindow.hpp"
#include "../Utilty/Foncteur/hascheckboxchecked.hpp"

namespace Ui {
    class createForm;
}

class createForm : public QDialog
{
    Q_OBJECT

    public:
        explicit createForm(QWidget *parent = 0);
        ~createForm();

        void loadForm(Entity::Form form);   // Charge un formulaire

        void validForm();   // Méthode appelée lors du clique sur le bouton "Valider"

    signals:
        void successAddForm();  // TODO A gerer
        void successEditForm();

    public slots:
        void chooseColor();                     // Pour choisir une couleur (onClick sur le bouton "Couleur")
        void addField();                        // Pour ajouter un champs (onClick sur le bouton "Ajouter un champs")
        void valid();                           // Pour stocker les informations dans l'attribut m_field (onClick sur le bouton "Valider")
        void editField(int id);                 // Pour modifier un champs (onClick sur le bouton "Modifier")
        void deleteField(int id);               // Pour supprimer un champs (onClick sur le bouton "Supprimer")
        void displayError(QString message);     // Affiche une erreur si elle reçoit un signal

        void deleteForm();

    private:
        Ui::createForm *ui;
        QColor m_color;

        QList<QCheckBox*> m_listWriters;
        QVBoxLayout *m_listWritersLayout;

        QList<QCheckBox*> m_listReaders;
        QVBoxLayout *m_listReadersLayout;

        QList<QCheckBox*> m_listTags;
        QVBoxLayout *m_listTagsLayout;

        QVBoxLayout *m_fieldsLayout;

        int m_nbField;                              // Permet d'avoir une id unique pour chaque champs ajouter sur les QMaps
        Entity::Form m_form;                        // Contient le formulaire
        bool m_newForm;
        QMap<int, fieldWindow*> m_fieldsWindows;    // Contient les fenêtres pour gérer les champs
        QMap<int, QHBoxLayout*> m_lines;            // Les layouts contenant les informations d'un champs
        QMap<int, CustomQPushButton*> m_edits;      // Les boutons "Modifier" pour chaque champs
        QMap<int, CustomQPushButton*> m_deletes;    // Les boutons "Supprimer" pour chaque champs

        bool m_formIsValid;                         // Pour savoir si un message à été affiché via displayError()
};

#endif // CREATEFORM_HPP
