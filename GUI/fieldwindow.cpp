#include "fieldwindow.hpp"
#include "ui_fieldwindow.h"

fieldWindow::fieldWindow(bool *ok, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fieldWindow),
    m_field(), m_nbField(), m_ok(ok)
{
    ui->setupUi(this);

    m_constraintLayout = new QVBoxLayout();

    ui->scrollAreaConstraintsContents->setLayout(m_constraintLayout);
}

fieldWindow::~fieldWindow()
{
    delete ui;

    for (auto it = m_constraintsWindow.begin(); it != m_constraintsWindow.end(); ++it)
    {
        delete *it;
    }
}

void fieldWindow::persistField(int idForm)
{
    Utility::PersisterManager pm;

    pm.persistOne(m_field);

    Relation::Contains contains;
        contains.setIdField(m_field.getId());
        contains.setIdForm(idForm);

    pm.persistOne(contains);

    for (Entity::DefaultValue &defaultValue : m_defaultValues)
    {
        defaultValue.setIdField(m_field.getId());
        pm.persistOne(defaultValue);
    }

    for (auto it = m_constraintsWindow.begin(); it != m_constraintsWindow.end(); ++it)
    {
        (*it)->persistConstraint(m_field.getId());
    }
}

void fieldWindow::valid()
{
    m_field.setLabel(ui->labelLineEdit->text());
    m_field.setHelpText(ui->texteDAideLineEdit->text());
    m_field.setPlaceholder(ui->placeholderLineEdit->text());
    m_field.setIsRequired(ui->requisCheckBox->isChecked());
    m_field.setIsMultiple(ui->choixMultipleCheckBox->isChecked());

    QString typeString = ui->typeComboBox->currentText();
    auto type = Entity::Field::Type::NONE;

    if (typeString == "Texte")
        type = Entity::Field::Type::TEXT;
    else if (typeString == "Nombre")
        type = Entity::Field::Type::NUMBER;
    else if (typeString == "Email")
        type = Entity::Field::Type::EMAIL;
    else if (typeString == "URL")
        type = Entity::Field::Type::URL;
    else if (typeString == "Date")
         type = Entity::Field::Type::DATE;
    else if (typeString == "Heure")
         type = Entity::Field::Type::TIME;
    else if (typeString == "Date et heure")
        type = Entity::Field::Type::DATETIME;
    else if (typeString == "Choix multiple")
        type = Entity::Field::Type::RADIO;
    else
        type = Entity::Field::Type::TEXT;

    m_field.setType(type);

    *m_ok = true;
    close();
}

void fieldWindow::addConstraint()
{
    m_nbField++;

    bool ok = false;

    m_constraintsWindow.insert( m_nbField, new ConstraintWindow(&ok, this) );
        m_constraintsWindow.last()->exec();

    if (ok)
    {
        m_lines.insert( m_nbField, new QHBoxLayout() );
        m_edits.insert( m_nbField, new CustomQPushButton("Modifier", m_nbField) );
        m_deletes.insert( m_nbField, new CustomQPushButton("Supprimer", m_nbField) );

        QObject::connect(m_edits.last(), SIGNAL(customClicked(int)), this, SLOT(editConstraint(int)));
        QObject::connect(m_deletes.last(), SIGNAL(customClicked(int)), this, SLOT(deleteConstraint(int)));

        m_lines.last()->addWidget( new QLabel(m_constraintsWindow.last()->getTypeReadable()) );
        m_lines.last()->addWidget( m_edits.last() );
        m_lines.last()->addWidget( m_deletes.last() );

        m_constraintLayout->addLayout( m_lines.last() );
    }
    else
    {
        delete m_constraintsWindow.take(m_nbField);
    }
}

void fieldWindow::editConstraint(int id)
{
    m_constraintsWindow[id]->exec();

    QLabel *labelType = dynamic_cast<QLabel *> ( m_lines[id]->itemAt(0)->widget() );
        labelType->setText( m_constraintsWindow[id]->getTypeReadable() );
}

void fieldWindow::deleteConstraint(int id)
{
    // On déco les slots
    QObject::connect(m_edits[id], SIGNAL(customClicked(int)), this, SLOT(editConstraint(int)));
    QObject::connect(m_deletes[id], SIGNAL(customClicked(int)), this, SLOT(deleteConstraint(int)));

    // On supprime la fenêtre
    delete m_constraintsWindow.take(id);

    // On récupère le layout horizontal
    QHBoxLayout *line = m_lines.take(id);

    QLayoutItem *item;

    while ((item = line->takeAt(0)) != 0)
    {
        item->widget()->deleteLater();
        delete item;
    }

    delete line;
}

Entity::Field fieldWindow::getField() const
{
    return m_field;
}

int fieldWindow::getNbConstraint() const
{
    return m_constraintsWindow.count();
}


