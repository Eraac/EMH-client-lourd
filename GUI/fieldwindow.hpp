#ifndef FIELDWINDOW_HPP
#define FIELDWINDOW_HPP

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

namespace Ui {
    class fieldWindow;
}

class fieldWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit fieldWindow(bool *ok, QWidget *parent = 0);
        ~fieldWindow();

        void persistField(int idForm);

        Entity::Field getField() const;
        int getNbConstraint() const;

        bool validField() const;

    public slots:
        void valid();
        void addConstraint();
        void editConstraint(int id);
        void deleteConstraint(int id);        
        void selectChange(int id);

    private:
        Ui::fieldWindow *ui;
        bool *m_ok;

        Entity::Field m_field;

        QLineEdit *m_defaultValueLineEdit;
        QTextEdit *m_defaultValueTextEdit;

        QVBoxLayout *m_constraintLayout;

        int m_nbField;
        QMap<int, ConstraintWindow*> m_constraintsWindow;
        QMap<int, QHBoxLayout*> m_lines;
        QMap<int, CustomQPushButton*> m_edits;
        QMap<int, CustomQPushButton*> m_deletes;
};

#endif // FIELDWINDOW_HPP
