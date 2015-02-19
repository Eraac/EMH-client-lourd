#include "constraintwindow.hpp"
#include "ui_constraintwindow.h"

ConstraintWindow::ConstraintWindow(bool *ok, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConstraintWindow),
    m_ok(ok), m_nbParams(2)
{
    ui->setupUi(this);

    m_lineEdits[0] = new QLineEdit();
    m_labels[0] = new QLabel("Minimum");
    ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

    m_lineEdits[1] = new QLineEdit();
    m_labels[1] = new QLabel("Maximum");
    ui->formLayout->addRow( m_labels[1],  m_lineEdits[1] );
}

ConstraintWindow::~ConstraintWindow()
{
    delete ui;
}

QString ConstraintWindow::getTypeReadable() const
{
    return ui->typeComboBox->currentText();
}

Entity::Constraint::Type ConstraintWindow::getType() const
{
    return m_constraint.getType();
}

void ConstraintWindow::valid()
{

    switch(ui->typeComboBox->currentIndex())
    {
        case 0:
            m_constraint.setType(Entity::Constraint::Type::LENGTH);
        break;

        case 1:
            m_constraint.setType(Entity::Constraint::Type::BETWEEN);
        break;

        case 2:
            m_constraint.setType(Entity::Constraint::Type::NOTEQUAL);
        break;

        case 3:
            m_constraint.setType(Entity::Constraint::Type::LOWER);
        break;

        case 4:
            m_constraint.setType(Entity::Constraint::Type::LOWEROREQUAL);
        break;

        case 5:
            m_constraint.setType(Entity::Constraint::Type::GREATER);
        break;

        case 6:
            m_constraint.setType(Entity::Constraint::Type::GREATEROREQUAL);
        break;

        case 7:
            m_constraint.setType(Entity::Constraint::Type::USERPASSWORD);
        break;

        case 8:
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
        case 0: // Longueur
        case 1: // Entre X et Y

            m_nbParams = 2;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Minimum");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

            m_lineEdits[1] = new QLineEdit();
            m_labels[1] = new QLabel("Maximum");
            ui->formLayout->addRow( m_labels[1],  m_lineEdits[1] );

        break;

        case 2: // Non égal à
        case 3: // Inférieur à
        case 4: // Inférieur ou égal à
        case 5: // Supérieur à
        case 6: // Supérieur ou égal à

            m_nbParams = 1;

            m_lineEdits[0] = new QLineEdit();
            m_labels[0] = new QLabel("Nombre");
            ui->formLayout->addRow( m_labels[0],  m_lineEdits[0] );

        break;

        case 8: // Regex

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

bool ConstraintWindow::validConstraint(Entity::Field::Type fieldType, QString const& label)
{
    if (!m_constraint.isValid())
    {
        emit sendError("Contrainte non valide pour le champs : " + label);
        return false;
    }

    Entity::Constraint::Type constraintType = m_constraint.getType();

    // Vérifier si la contrainte est logique avec le type
    switch (constraintType)
    {
        case Entity::Constraint::Type::LENGTH:
            if (Entity::Field::Type::TEXT != fieldType &&
                Entity::Field::Type::PASSWORD != fieldType &&
                Entity::Field::Type::EMAIL != fieldType &&
                Entity::Field::Type::URL != fieldType
                )
            {
                emit sendError("Contrainte non logique pour le champs : " + label);
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
                emit sendError("Contrainte non logique pour le champs : " + label);
                return false;
            }
        break;

        case Entity::Constraint::Type::USERPASSWORD:
            if (Entity::Field::Type::TEXT != fieldType &&
                Entity::Field::Type::PASSWORD != fieldType
               )
            {
                emit sendError("Contrainte non logique pour le champs : " + label);
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
                emit sendError("Contrainte non logique pour le champs : " + label);
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
                emit sendError("Contrainte \"Entre X et Y\” doit contenir des nombres et \
                                le minimum doit être inférieur au maximum. Pour le champs : " + label);
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
                emit sendError("Une contrainte a un paramètre manquant ou n'est pas un nombre. Pour le champs : " + label);
                return false;
            }
        break;

        case Entity::Constraint::Type::REGEX: // (1 params)
            QRegExp regex(m_params[0].getValue());

            if (!regex.isValid())
            {
                emit sendError("La regex n'est pas valide. Pour le champs : " + label);
                return false;
            }
        break;
    }

    // Pour gérer le cas de 1 ou 2 paramètres
    if (Entity::Constraint::Type::LENGTH == constraintType)
    {
        if (!m_params[1].getValue().isEmpty() &&
               m_params[0].getValue().toInt() > m_params[1].getValue().toInt()
           )
        {
            emit sendError("La contrainte longueur du champs " + label + " n'est pas valide. Le nombre minimum est supérieur au nombre maximum.");
            return false;
        }
    }

    return true;
}

