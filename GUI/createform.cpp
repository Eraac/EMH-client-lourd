#include "createform.hpp"
#include "ui_createform.h"

createForm::createForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createForm), m_color(Qt::white), m_nbField(0), m_form()
{
    ui->setupUi(this);

    m_listReadersLayout = new QVBoxLayout();
    m_listWritersLayout = new QVBoxLayout();
    m_listTagsLayout = new QVBoxLayout();
    m_fieldsLayout = new QVBoxLayout();

    ui->scrollAreaReaders->setLayout(m_listReadersLayout);
    ui->scrollAreaWriters->setLayout(m_listWritersLayout);
    ui->scrollAreaTags->setLayout(m_listTagsLayout);
    ui->scrollAreaFields->setLayout(m_fieldsLayout);

    // On parcourt les groupes
    for (auto groupname : Entity::Group::getAll())
    {
        m_listReaders.append(new QCheckBox(groupname));
        m_listWriters.append(new QCheckBox(groupname));

        m_listReadersLayout->addWidget(m_listReaders.last());
        m_listWritersLayout->addWidget(m_listWriters.last());
    }

    // On parcourt les tags
    for (auto tagname : Entity::Tag::getAll())
    {
        m_listTags.append(new QCheckBox(tagname));

        m_listTagsLayout->addWidget(m_listTags.last());
    }
}

createForm::~createForm()
{
    delete ui;

    for (auto it = m_fieldsWindows.begin(); it != m_fieldsWindows.end(); ++it)
        delete *it;
}

void createForm::chooseColor()
{
    m_color = QColorDialog::getColor(m_color);
}

void createForm::addField()
{
    m_nbField++;

    bool ok = false;

    m_fieldsWindows.insert(m_nbField, new fieldWindow(&ok));
        m_fieldsWindows.last()->exec();

    if (ok)
    {
        m_lines.insert( m_nbField, new QHBoxLayout() );

        m_edits.insert( m_nbField, new CustomQPushButton("Modifier", m_nbField) );
        m_deletes.insert( m_nbField, new CustomQPushButton("Supprimer", m_nbField) );

        QObject::connect(m_edits.last(), SIGNAL(customClicked(int)), this, SLOT(editField(int)));
        QObject::connect(m_deletes.last(), SIGNAL(customClicked(int)), this, SLOT(deleteField(int)));

        m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getTypeReadable()) );
        m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getLabel()) );
        m_lines.last()->addWidget( new QLabel(QString("%1 contrainte(s)").arg(m_fieldsWindows.last()->getNbConstraint()) ) );
        m_lines.last()->addWidget( m_edits.last() );
        m_lines.last()->addWidget( m_deletes.last() );

        m_fieldsLayout->addLayout(m_lines.last());
    }
    else
    {
        delete m_fieldsWindows.take(m_nbField);
    }
}

void createForm::editField(int id)
{
    m_fieldsWindows[id]->exec();

    QLabel *labelType = dynamic_cast<QLabel*>(m_lines[id]->itemAt(0)->widget());
        labelType->setText( m_fieldsWindows[id]->getField().getTypeReadable() );

    QLabel *labelName = dynamic_cast<QLabel*>(m_lines[id]->itemAt(1)->widget());
        labelName->setText( m_fieldsWindows[id]->getField().getLabel() );

    QLabel *nbConstraints = dynamic_cast<QLabel*>(m_lines[id]->itemAt(2)->widget());
        nbConstraints->setText( QString("%1 contrainte(s)").arg(m_fieldsWindows[id]->getNbConstraint()) );
}

void createForm::deleteField(int id)
{
    // On deco les slots
    QObject::disconnect(m_edits[id], SIGNAL(customClicked(int)), this, SLOT(editField(int)));
    QObject::disconnect(m_deletes[id], SIGNAL(customClicked(int)), this, SLOT(deleteField(int)));

    // On supprime la fenêtre
    delete m_fieldsWindows.take(id);

    // On récupère le layout horizontal
    QHBoxLayout* line = m_lines.take(id);

    // Supprime le horizontal layout du vertial layout
    m_fieldsLayout->removeItem( line );

    QLayoutItem *item;

    while ((item = line->takeAt(0)) != 0)
    {
        item->widget()->deleteLater();
        delete item;
    }

    delete line;

    // TODO Stocker les fields supprimer pour call la méthode remove quand il s'agit d'un formulaire existant
}

void createForm::valid()
{
    // Parcourir les fieldsWindow et générer les fields (vérifier qu'ils sont valides)
    // Persist les Readers et les Writers
    // Persist les tags

    Utility::PersisterManager pm;

    m_form.setColor(m_color);
    m_form.setDescription(ui->description->toPlainText());
    m_form.setIdAuthor(1); // TODO
    m_form.setImportant(ui->messageImportant->toPlainText());
    m_form.setInfo(ui->messageInformation->toPlainText());
    m_form.setName(ui->nomLineEdit->text());

    if (ui->demandeRadioButton->isChecked())
        m_form.setStatus(Entity::Form::Status::DEMAND);
    else
        m_form.setStatus(Entity::Form::Status::INFORMATION);

    pm.persistOne(m_form);

    for (auto &tag : m_listTags)
    {

    }

    close();
}
