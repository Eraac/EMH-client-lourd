#include "fieldwindow.hpp"
#include "ui_fieldwindow.h"

fieldWindow::fieldWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fieldWindow),
    m_field()
{
    ui->setupUi(this);
}

fieldWindow::~fieldWindow()
{
    delete ui;
}

void fieldWindow::persistField(int idForm)
{
    // TODO Remplir l'objet m_field avec les infos dans le formulaire

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

    for (Entity::Constraint &constraint : m_constraints)
    {
        pm.persistOne(constraint);

        Relation::Require require;
            require.setIdField(m_field.getId());
            require.setIdConstraint(constraint.getId());

        pm.persistOne(require);
    }

    for (Entity::Param &param : m_params)
        pm.persistOne(param);
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

    close();
}

Entity::Field fieldWindow::getField() const
{
    return m_field;
}

int fieldWindow::getNbConstraint() const
{
    return m_constraints.count();
}
