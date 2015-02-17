#include "constraintwindow.hpp"
#include "ui_constraintwindow.h"

ConstraintWindow::ConstraintWindow(bool *ok, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConstraintWindow),
    m_ok(ok), m_nbParams(0)
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
    // TODO Retirer EMAIL et URL (les id changent)

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
    // TODO Supprimer EMAIL et URL (les id changent)
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
            ui->formLayout->addRow( m_labels[0], m_lineEdits[0] );

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
            delete m_labels[i];
        }

        if (nullptr != m_lineEdits[i])
        {
            ui->formLayout->removeWidget(m_lineEdits[i]);
            delete m_lineEdits[i];
        }
    }

    m_nbParams = 0;
}

void ConstraintWindow::persistConstraint(int idField)
{
    Utility::PersisterManager pm;

    pm.persistOne(m_constraint);

    Relation::Require require;
        require.setIdConstraint(m_constraint.getId());
        require.setIdField(idField);

    pm.persistOne(require);

    // On enregistre les parametres si besoin
    for (int i = 0; i < m_nbParams; i++)
    {
        if (m_params[i].isValid())
        {
            m_params[i].setIdConstraint(m_constraint.getId());
            pm.persistOne(m_params[i]);
        }
    }
}

bool ConstraintWindow::validConstraint(Entity::Field::Type fieldType) const
{
    // TODO Supprimer la vérification sur EMAIL et URL (contrainte)

    if (!m_constraint.isValid())
    {
        return false;
    }

    Entity::Constraint::Type constraintType = m_constraint.getType();

    // Vérifier si la contrainte est logique avec le type
    switch (constraintType)
    {
        case Entity::Constraint::Type::EMAIL:
            if (Entity::Field::Type::TEXT != fieldType &&
                Entity::Field::Type::PASSWORD != fieldType &&
                Entity::Field::Type::EMAIL != fieldType
                )
            {
                return false;
            }
        break;

        case Entity::Constraint::Type::LENGTH:
            if (Entity::Field::Type::TEXT != fieldType &&
                Entity::Field::Type::PASSWORD != fieldType &&
                Entity::Field::Type::EMAIL != fieldType &&
                Entity::Field::Type::URL != fieldType
                )
            {
                return false;
            }
        break;

        case Entity::Constraint::Type::URL:
            if (Entity::Field::Type::TEXT != fieldType &&
                Entity::Field::Type::PASSWORD != fieldType &&
                Entity::Field::Type::URL != fieldType
                )
            {
                return false;
            }
        break;

        case Entity::Constraint::Type::BETWEEN:
        case Entity::Constraint::Type::NOTEQUAL:
        case Entity::Constraint::Type::LOWER:
        case Entity::Constraint::Type::LOWEROREQUAL:
        case Entity::Constraint::Type::GREATER:
        case Entity::Constraint::Type::GREATEROREQUAL:
            if (Entity::Field::Type::NUMBER != fieldType)
            {
                return false;
            }
        break;

        case Entity::Constraint::Type::USERPASSWORD:
            if (Entity::Field::Type::TEXT != fieldType &&
                Entity::Field::Type::PASSWORD != fieldType
               )
            {
                return false;
            }
        break;

        case Entity::Constraint::Type::REGEX:
            if (Entity::Field::Type::TEXT != fieldType &&
                Entity::Field::Type::PASSWORD != fieldType &&
                Entity::Field::Type::NUMBER != fieldType &&
                Entity::Field::Type::EMAIL != fieldType &&
                Entity::Field::Type::URL != fieldType
               )
            {
                return false;
            }
        break;
    }

    // Vérification des paramètres
    switch (constraintType)
    {
        case Entity::Constraint::Type::BETWEEN: // (2 params)
            if (m_params[0].getValue().isEmpty() || m_params[1].getValue().isEmpty() ||
                    !m_params[0].getValue().contains(QRegExp("^[0-9]+$")) ||
                    !m_params[1].getValue().contains(QRegExp("^[0-9]+$")) ||
                    m_params[0].getValue().toInt() > m_params[1].getValue().toInt()
                )
            {
                return false;
            }
        break;

        case Entity::Constraint::Type::LENGTH: // (1-2 params)
        case Entity::Constraint::Type::NOTEQUAL: // (1 params)
        case Entity::Constraint::Type::LOWER: // (1 params)
        case Entity::Constraint::Type::LOWEROREQUAL: // (1 params)
        case Entity::Constraint::Type::GREATER: // (1 params)
        case Entity::Constraint::Type::GREATEROREQUAL: // (1 params)
            // Vérifier que nous avons un nombre
            if (m_params[0].getValue().isEmpty() || !m_params[0].getValue().contains(QRegExp("^[0-9]+$")))
            {
                return false;
            }
        break;

        case Entity::Constraint::Type::REGEX: // (1 params)
            QRegExp regex(m_params[0].getValue());

            if (!regex.isValid())
            {
                return false;
            }
        break;
    }

    if (Entity::Constraint::Type::LENGTH == constraintType)
    {
        if (!m_params[1].getValue().isEmpty() &&
               m_params[0].getValue().toInt() > m_params[1].getValue().toInt()
           )
        {
            return false;
        }
    }

    return true;
}
