#include "constraintwindow.hpp"
#include "ui_constraintwindow.h"

ConstraintWindow::ConstraintWindow(bool *ok, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConstraintWindow),
    m_ok(ok)
{
    m_labels[0] = nullptr;
    m_labels[1] = nullptr;

    m_lineEdits[0] = nullptr;
    m_lineEdits[1] = nullptr;

    ui->setupUi(this);
}

ConstraintWindow::~ConstraintWindow()
{
    delete ui;
}

QString ConstraintWindow::getTypeReadable() const
{
    return ui->typeComboBox->currentText();
}

void ConstraintWindow::valid()
{
    switch(ui->typeComboBox->currentIndex())
    {
        case 0:
            m_constraint.setType(Entity::Constraint::Type::EMAIL);
        break;

        case 1:
            m_constraint.setType(Entity::Constraint::Type::LENGTH);
        break;

        case 2:
            m_constraint.setType(Entity::Constraint::Type::URL);
        break;

        case 3:
            m_constraint.setType(Entity::Constraint::Type::BETWEEN);
        break;

        case 4:
            m_constraint.setType(Entity::Constraint::Type::NOTEQUAL);
        break;

        case 5:
            m_constraint.setType(Entity::Constraint::Type::LOWER);
        break;

        case 6:
            m_constraint.setType(Entity::Constraint::Type::LOWEROREQUAL);
        break;

        case 7:
            m_constraint.setType(Entity::Constraint::Type::GREATER);
        break;

        case 8:
            m_constraint.setType(Entity::Constraint::Type::GREATEROREQUAL);
        break;

        case 9:
            m_constraint.setType(Entity::Constraint::Type::USERPASSWORD);
        break;

        case 10:
            m_constraint.setType(Entity::Constraint::Type::REGEX);
        break;
    }

    for (int i = 0; i < m_nbParams; i++)
    {
        if (nullptr != m_lineEdits[i])
            if (!m_lineEdits[i]->text().isEmpty())
                m_params[i].setValue(m_lineEdits[i]->text());
    }

    *m_ok = true;
    close();
}

void ConstraintWindow::selectChange(int type)
{
    cleanForm();

    switch (type)
    {
        case 1: // Longueur

            m_nbParams = 2;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Minimum");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

            m_lineEdits[1] = new QLineEdit();
            m_labels[1] = new QLabel("Maximum");
            ui->formLayout->addRow( m_labels[1],  m_lineEdits[1] );

        break;

        case 3: // Entre X et Y

            m_nbParams = 2;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Minimum");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

            m_lineEdits[1] = new QLineEdit();
            m_labels[1] = new QLabel("Maximum");
            ui->formLayout->addRow( m_labels[1],  m_lineEdits[1] );

        break;

        case 4: // Non égal à

            m_nbParams = 1;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Nombre");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

        break;

        case 5: // Inférieur à

            m_nbParams = 1;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Nombre");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

        break;

        case 6: // Inférieur ou égal à

            m_nbParams = 1;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Nombre");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

        break;

        case 7: // Supérieur à

            m_nbParams = 1;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Nombre");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

        break;

        case 8: // Supérieur ou égal à

            m_nbParams = 1;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Nombre");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

        break;

        case 10: // Regex

            m_nbParams = 1;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Regex");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

        break;
    }

}

void ConstraintWindow::cleanForm()
{
    for (int i = 0; i < m_nbParams; i++)
    {
        if (nullptr != m_labels[i])
        {
            ui->formLayout->removeWidget(m_labels[i]);
            ui->formLayout->removeWidget(m_lineEdits[i]);
        }

        delete m_labels[i];
        delete m_lineEdits[i];
    }

    m_nbParams = 0;
}

void ConstraintWindow::persistConstraint(int idField)
{
    Utility::PersisterManager pm;

    pm.persistOne(m_constraint);

    Relation::Constrained constrained;
        constrained.setIdConstraint(m_constraint.getId());
        constrained.setIdField(idField);

    pm.persistOne(constrained);

    for (int i = 0; i < m_nbParams; i++)
    {
        if (m_params[i].isValid())
        {
            m_params[i].setIdConstraint(m_constraint.getId());
            pm.persistOne(m_params[i]);
        }
    }
}

