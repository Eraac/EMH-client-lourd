#include "createform.hpp"
#include "ui_createform.h"

#include <QMessageBox>

createForm::createForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createForm), m_color(Qt::white), m_nbField(0)
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

    m_fieldsWindows.append(new fieldWindow());

    //QMessageBox::information(this, "title", QString("%1").arg(m_fieldsWindows.count()));

        m_fieldsWindows.last()->exec();

    m_lines.append( new QHBoxLayout() );

    m_edits.append( new CustomQPushButton("Modifier", m_nbField) );
    m_deletes.append( new CustomQPushButton("Supprimer", m_nbField) );

    QObject::connect(m_edits.last(), SIGNAL(customClicked(int)), this, SLOT(editField(int)));
    QObject::connect(m_deletes.last(), SIGNAL(customClicked(int)), this, SLOT(deleteField(int)));

    m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getTypeReadable()) );
    m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getLabel()) );
    m_lines.last()->addWidget( new QLabel(QString("%1 contrainte(s)").arg(m_fieldsWindows.last()->getNbConstraint()) ) );
    m_lines.last()->addWidget( m_edits.last() );
    m_lines.last()->addWidget( m_deletes.last() );

    m_fieldsLayout->addLayout(m_lines.last());
}

void createForm::editField(int id)
{
    m_fieldsWindows.value(id - 1)->exec();

    // TODO Edit le layout
}

void createForm::deleteField(int id)
{
    m_nbField--;

    for (int i = id; i < m_edits.count(); i++)
        m_edits[i]->reduceId();

    for (int i = id; i < m_deletes.count(); i++)
        m_deletes[i]->reduceId();

    // On supprime la fenêtre
    m_fieldsWindows.removeAt(id - 1);

    // On récupère le layout horizontal
    QHBoxLayout* line = m_lines.takeAt(id - 1);

    // Supprime le horizontal layout du vertial layout
    m_fieldsLayout->removeItem( line );

    QLayoutItem *item;

    while ((item = line->takeAt(0)) != 0)
    {
        item->widget()->deleteLater();
        delete item;
    }

    delete line;

    // TODO Disconnect le signal
    // TODO Stocker les fields supprimer pour call la méthode remove

}

void createForm::valid()
{
    // Parcourir les fieldsWindow et générer les fields (vérifier qu'ils sont valides)
    // Persist les Readers et les Writers
    // Persist les tags

    close();
}
