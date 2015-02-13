#ifndef FIELDWINDOW_HPP
#define FIELDWINDOW_HPP

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QList>
#include <QMap>
#include "../GUI/customqpushbutton.hpp"
#include "../Model/Entity/Field.hpp"
#include "../Model/Entity/DefaultValue.hpp"
#include "../Model/Relation/Require.hpp"
#include "../Model/Relation/Contains.hpp"
#include "../Utilty/PersisterManager.hpp"

namespace Ui {
    class fieldWindow;
}

class fieldWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit fieldWindow(QWidget *parent = 0);
        ~fieldWindow();

        void persistField(int idForm);

        Entity::Field getField() const;
        int getNbConstraint() const;

    public slots:
        void valid();
        void addConstraint();
        void editConstraint(int id);
        void deleteConstraint(int id);

    private:
        Ui::fieldWindow *ui;

        Entity::Field m_field;
        QList<Entity::DefaultValue> m_defaultValues;

        QVBoxLayout *m_constraintLayout;

        int m_nbField;
        //QMap sur la window pour les contraintes
        QMap<int, QHBoxLayout*> m_lines;
        QMap<int, CustomQPushButton*> m_edits;
        QMap<int, CustomQPushButton*> m_deletes;
};

#endif // FIELDWINDOW_HPP
