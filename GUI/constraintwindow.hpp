#ifndef CONSTRAINTWINDOW_HPP
#define CONSTRAINTWINDOW_HPP

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <array>
#include "../Utilty/PersisterManager.hpp"
#include "../Model/Entity/Constraint.hpp"
#include "../Model/Relation/constrained.hpp"
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

        QString getTypeReadable() const;
        void persistConstraint(int idField);

    public slots:
        void selectChange(int type);
        void valid();

    private:
        Ui::ConstraintWindow *ui;
        bool *m_ok;
        int m_nbParams;

        Entity::Constraint m_constraint;
        std::array<Entity::Param, 2> m_params;
        std::array<QLabel*, 2> m_labels;
        std::array<QLineEdit*, 2> m_lineEdits;

        void cleanForm();
};

#endif // CONSTRAINTWINDOW_HPP
