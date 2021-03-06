#include "fieldwindow.hpp"
#include "ui_fieldwindow.h"

fieldWindow::fieldWindow(QWidget *parent, bool *ok) :
    QDialog(parent),
    ui(new Ui::fieldWindow),
    m_ok(ok), m_field(), m_defaultValueTextEdit(nullptr), m_nbField(),
    m_deletedConstraint()
{
    ui->setupUi(this);

    m_defaultValueLineEdit = ui->valeurParDefautLineEdit;

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
    for (auto constraint : m_deletedConstraint)
        constraint.remove();

    m_field.deleteAutoConstraint();
    m_field.deleteDefaultValue();

    Utility::PersisterManager pm;
    QStringList defaultValues;

    m_field.setFormId(idForm);
    pm.persistOne(m_field);

    Entity::Constraint constraint;

    constraint.setFieldId(m_field.getId());

    // Selon le type du champs on ajoute des contraintes (Date, Time, Datetime, Url, Email)
    switch (m_field.getType())
    {
        case Entity::Field::Type::DATE:
            constraint.setType(Entity::Constraint::Type::DATE);
        break;

        case Entity::Field::Type::TIME:
            constraint.setType(Entity::Constraint::Type::TIME);
        break;

        case Entity::Field::Type::DATETIME:
            constraint.setType(Entity::Constraint::Type::DATETIME);
        break;

        case Entity::Field::Type::URL:
            constraint.setType(Entity::Constraint::Type::URL);
        break;

        case Entity::Field::Type::EMAIL:
            constraint.setType(Entity::Constraint::Type::EMAIL);            
        break;
    }

    if (constraint.getType() != Entity::Constraint::Type::NONE)
        pm.persistOne(constraint);

    // Si le champs est requis on ajoute la contrainte not null
    if (m_field.getIsRequired())
    {
        Entity::Constraint constraintNotNull;

        constraintNotNull.setType(Entity::Constraint::Type::NOTNULL);
        constraintNotNull.setFieldId(m_field.getId());

        pm.persistOne(constraintNotNull);
    }

    // Plusieurs valeurs
    if (Entity::Field::Type::RADIO == m_field.getType())
    {
        if (!m_defaultValueTextEdit->toPlainText().isEmpty())
            defaultValues = m_defaultValueTextEdit->toPlainText().split('\n', QString::SkipEmptyParts);
    }
    // Une valeur
    else
    {
        if (!m_defaultValueLineEdit->text().isEmpty())
            defaultValues << m_defaultValueLineEdit->text().trimmed();
    }

    // Pour toutes les valeurs par défaut
    for (auto &value : defaultValues)
    {
        // On persist la l'entité
        Entity::DefaultValue defaultValue;
            defaultValue.setIdField(m_field.getId());
            defaultValue.setValue(value);

        pm.persistOne(defaultValue);
    }

    // Pour toute les fenêtres qui contient les contraintes
    for (auto it = m_constraintsWindow.begin(); it != m_constraintsWindow.end(); ++it)
    {
        // On persist la contrainte
        (*it)->persistConstraint(m_field.getId());
    }
}

void fieldWindow::load(Entity::Field field)
{
    m_field = field;

    ui->labelLineEdit->setText(m_field.getLabel());
    ui->texteDAideLineEdit->setText(m_field.getHelpText());
    ui->placeholderLineEdit->setText(m_field.getPlaceholder());
    ui->requisCheckBox->setChecked(m_field.getIsRequired());
    ui->choixMultipleCheckBox->setChecked(m_field.getIsMultiple());

    int type = 0;

    switch(m_field.getType())
    {
        case Entity::Field::Type::DATE:
            type = 4;
        break;

        case Entity::Field::Type::DATETIME:
            type = 6;
        break;

        case Entity::Field::Type::EMAIL:
            type = 2;
        break;

        case Entity::Field::Type::NUMBER:
            type = 1;
        break;

        case Entity::Field::Type::TEXT:
            type = 0;
        break;

        case Entity::Field::Type::TIME:
            type = 5;
        break;

        case Entity::Field::Type::URL:
            type = 3;
        break;

        case Entity::Field::Type::RADIO:
            type = 7;
        break;

        case Entity::Field::Type::TEXTAREA:
            type = 9;
        break;

        case Entity::Field::Type::PASSWORD:
            type = 8;
        break;
    }

    ui->typeComboBox->setCurrentIndex(type);

    // Select avec multiple selection possible
    if (m_field.getType() == Entity::Field::Type::RADIO)
    {
        m_defaultValueTextEdit->setText(m_field.getDefaultValue());
    }
    else
    {
        m_defaultValueLineEdit->setText(m_field.getDefaultValue());
    }

    // Charge les contraintes

    QList<Entity::Constraint> constraints = m_field.getConstraints();

    for (auto constraint : constraints)
    {
        // Si la contrainte fait partie des contraintes "automatique" on ne l'affiche pas
        if (constraint.getType() == Entity::Constraint::Type::DATE ||
            constraint.getType() == Entity::Constraint::Type::TIME ||
            constraint.getType() == Entity::Constraint::Type::DATETIME ||
            constraint.getType() == Entity::Constraint::Type::URL ||
            constraint.getType() == Entity::Constraint::Type::EMAIL ||
            constraint.getType() == Entity::Constraint::Type::NOTNULL ||
            constraint.getType() == Entity::Constraint::Type::NONE
            ) {
            continue;
        }

        m_nbField++;

        // On ajoute un objet ConstraintWindow dans la QMap
        ConstraintWindow *constraintWd = new ConstraintWindow(this);
            constraintWd->load(constraint);

        m_constraintsWindow.insert( m_nbField, constraintWd );

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
}

void fieldWindow::valid()
{
    // On charge l'entité du champs selon les informations dans l'interface
    m_field.setLabel(ui->labelLineEdit->text());
    m_field.setHelpText(ui->texteDAideLineEdit->text());
    m_field.setPlaceholder(ui->placeholderLineEdit->text());
    m_field.setIsRequired(ui->requisCheckBox->isChecked());
    m_field.setIsMultiple(ui->choixMultipleCheckBox->isChecked());

    QString typeString = ui->typeComboBox->currentText();
    auto type = Entity::Field::Type::NONE;

    // On applique le bon type selon le choix de l'utilisateur
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
    else if (typeString == "Caché")
        type = Entity::Field::Type::PASSWORD;
    else if (typeString == "Long texte")
        type = Entity::Field::Type::TEXTAREA;
    else
        type = Entity::Field::Type::TEXT;

    m_field.setType(type);

    // On indique que l'utilisateur à cliqué sur OK
    if (m_ok != nullptr)
        *m_ok = true;

    close();
}

bool fieldWindow::validField()
{
    // Si aucune infomation n'est fourni dans les valeurs par défaut et que le type du champs RADIO
    if (Entity::Field::Type::RADIO == m_field.getType() && m_defaultValueTextEdit->toPlainText().isEmpty())
    {
        emit sendError("Des valeurs par défaut doivent être renseignées lorsque le type du champs est \"Choix multiple\”.\n\
                        Pour le champs : " + m_field.getLabel());
        return false;
    }

    // Si le champs n'est pas valide
    if (!m_field.isValid())
    {
        emit sendError("Les informations pour le champs " + m_field.getLabel() + " ne sont pas complète");
        return false;
    }

    bool valid = false;

    // Vérifier si doublon dans les contraintes
    Utility::HasDuplicateConstraint hasduplicateconstraint;

    // On vérifie qu'aucune contrainte n'est dupliqué
    hasduplicateconstraint = std::for_each(m_constraintsWindow.begin(), m_constraintsWindow.end(), hasduplicateconstraint);

    // Si une contrainte est dupliqué
    if (hasduplicateconstraint.hasDuplicate())
    {
        // On prévient l'utilisateur
        emit sendError("Une ou plusieurs contraintes sont en double dans le champs : " + m_field.getLabel());
        return false;
    }

    // On parcours les contraintes
    for (auto &constraint : m_constraintsWindow)
    {
        QObject::connect(constraint, SIGNAL(sendError(QString)), this->parent(), SLOT(displayError(QString)));
        valid = !constraint->validConstraint(m_field.getType(), m_field.getLabel());
        QObject::disconnect(constraint, SIGNAL(sendError(QString)), this->parent(), SLOT(displayError(QString)));

        // Si une n'est pas valide on quitte
        if (!valid) {
            return false;
        }
    }

    return true;
}

void fieldWindow::selectChange(int id)
{
    // Si l'utilisateur choisit "Choix multiple"
    if (7 == id)
    {    
        // On change le QLineEdit en QTextEdit
        m_defaultValueTextEdit = new QTextEdit();
        ui->choixMultipleCheckBox->setEnabled(true);
        ui->formLayout->replaceWidget(m_defaultValueLineEdit, m_defaultValueTextEdit);
        delete m_defaultValueLineEdit;
        m_defaultValueLineEdit = nullptr;
    }
    else
    {
        // Si avant ce n'était pas déjà le QLineEdit
        if (nullptr == m_defaultValueLineEdit)
        {
            // On change le QTextEdit en QLineEdit
            m_defaultValueLineEdit = new QLineEdit();
            ui->choixMultipleCheckBox->setChecked(false);
            ui->choixMultipleCheckBox->setEnabled(false);
            ui->formLayout->replaceWidget(m_defaultValueTextEdit, m_defaultValueLineEdit);
            delete m_defaultValueTextEdit;
            m_defaultValueTextEdit = nullptr;
        }
    }

}

void fieldWindow::editConstraint(int id)
{
    // On lance la fenêtre correspondant à la contrainte
    m_constraintsWindow[id]->exec();

    // On mets à jour l'interface
    QLabel *labelType = dynamic_cast<QLabel *> ( m_lines[id]->itemAt(0)->widget() );
        labelType->setText( m_constraintsWindow[id]->getTypeReadable() );
}

void fieldWindow::addConstraint()
{
    m_nbField++;

    bool ok = false;

    // On ajoute un objet ConstraintWindow dans la QMap
    m_constraintsWindow.insert( m_nbField, new ConstraintWindow(this, &ok) );
        m_constraintsWindow.last()->exec();

    // Si l'utilisateur à valider
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
    // Si l'utilisateur à fermer la fenêtre
    else
    {
        // On retire la fenêtre du QMap
        delete m_constraintsWindow.take(m_nbField);
    }
}

void fieldWindow::deleteConstraint(int id)
{
    // On déco les slots
    QObject::connect(m_edits[id], SIGNAL(customClicked(int)), this, SLOT(editConstraint(int)));
    QObject::connect(m_deletes[id], SIGNAL(customClicked(int)), this, SLOT(deleteConstraint(int)));

    // On supprime la fenêtre
    ConstraintWindow *constraintWd = m_constraintsWindow.take(id);

    m_deletedConstraint.append(constraintWd->getConstraint());

    delete constraintWd;

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


