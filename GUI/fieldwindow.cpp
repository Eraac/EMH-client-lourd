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
