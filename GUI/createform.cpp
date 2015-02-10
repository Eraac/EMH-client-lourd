#include "createform.hpp"
#include "ui_createform.h"

createForm::createForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createForm), m_color(Qt::white)
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
}

void createForm::chooseColor()
{
    m_color = QColorDialog::getColor(m_color);
}

void createForm::addField()
{
    auto hlayout = new QHBoxLayout();

    hlayout->addWidget( new QLabel(ui->typeFieldBox->currentText()) );
    hlayout->addWidget( new QLabel("Prénom") );
    hlayout->addWidget( new QLabel("2 contraintes") );
    hlayout->addWidget( new QPushButton("Modifier") );
    hlayout->addWidget( new QPushButton("Supprimer") );

    m_fieldsLayout->addLayout(hlayout);
}

void createForm::valid()
{
    close();
}
