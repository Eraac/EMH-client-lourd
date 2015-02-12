#ifndef FIELDWINDOW_HPP
#define FIELDWINDOW_HPP

#include <QDialog>
#include <QList>
#include "../Model/Entity/Field.hpp"
#include "../Model/Entity/Constraint.hpp"
#include "../Model/Entity/param.hpp"
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

    private:
        Ui::fieldWindow *ui;

        Entity::Field m_field;
        QList<Entity::DefaultValue> m_defaultValues;
        QList<Entity::Constraint> m_constraints;
        QList<Entity::Param> m_params;
};

#endif // FIELDWINDOW_HPP
