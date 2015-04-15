#include "createform.hpp"
#include "ui_createform.h"


createForm::createForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createForm), m_color(Qt::white), m_nbField(0),
    m_form(), m_formIsValid(false), m_newForm(true)
{
    ui->setupUi(this);

    // On initialise les layouts contenant les groupes et les champs
    m_listReadersLayout = new QVBoxLayout();
    m_listWritersLayout = new QVBoxLayout();
    m_listTagsLayout = new QVBoxLayout();
    m_fieldsLayout = new QVBoxLayout();

    // On assigne les layouts aux bon widget
    ui->scrollAreaReaders->setLayout(m_listReadersLayout);
    ui->scrollAreaWriters->setLayout(m_listWritersLayout);
    ui->scrollAreaTags->setLayout(m_listTagsLayout);
    ui->scrollAreaFields->setLayout(m_fieldsLayout);

    Entity::Group group;

    // On parcourt les groupes
    for (auto groupname : group.getAll())
    {
        // On ajoute dans le layout le groupe
        m_listReaders.append(new QCheckBox(groupname));
        m_listWriters.append(new QCheckBox(groupname));

        m_listReadersLayout->addWidget(m_listReaders.last());
        m_listWritersLayout->addWidget(m_listWriters.last());
    }

    // On parcourt les tags
    for (auto tagname : Entity::Tag::getAll())
    {
        // On ajoute dans le layout le tag
        m_listTags.append(new QCheckBox(tagname));

        m_listTagsLayout->addWidget(m_listTags.last());
    }
}

createForm::~createForm()
{
    delete ui;

    // On supprime les fenêtres pour gérer les champs
    for (auto it = m_fieldsWindows.begin(); it != m_fieldsWindows.end(); ++it)
        delete *it;
}

void createForm::chooseColor()
{
    // Permet de choisir une couleur via un classe toute faite
    m_color = QColorDialog::getColor(m_color);
}

void createForm::addField()
{
    // Permet d'avoir une ID unique pour les QMap
    m_nbField++;

    bool ok = false;

    // On ajoute une fenêtre dans la liste
    m_fieldsWindows.insert(m_nbField, new fieldWindow(this, &ok));
        // On l'execute
        m_fieldsWindows.last()->exec();

    // Si l'utilisateur a cliqué sur Valider et non Fermer
    if (ok)
    {
        // On ajoute la ligne dans le layout des champs
        m_lines.insert( m_nbField, new QHBoxLayout() );

        // Nous ajoutons nos boutons personnalisés
        m_edits.insert( m_nbField, new CustomQPushButton("Modifier", m_nbField) );
        m_deletes.insert( m_nbField, new CustomQPushButton("Supprimer", m_nbField) );

        // On connect les slots pour savoir qu'elle bouton est appuyer
        QObject::connect(m_edits.last(), SIGNAL(customClicked(int)), this, SLOT(editField(int)));
        QObject::connect(m_deletes.last(), SIGNAL(customClicked(int)), this, SLOT(deleteField(int)));

        // Nous ajoutons des informations du champs dans le layout
        m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getTypeReadable()) );
        m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getLabel()) );
        m_lines.last()->addWidget( new QLabel(QString("%1 contrainte(s)").arg(m_fieldsWindows.last()->getNbConstraint()) ) );
        m_lines.last()->addWidget( m_edits.last() );
        m_lines.last()->addWidget( m_deletes.last() );

        m_fieldsLayout->addLayout(m_lines.last());
    }
    // Si l'utilisateur ferme la fenêtre
    else
    {
        // On supprime la fenêtre
        delete m_fieldsWindows.take(m_nbField);
    }
}

void createForm::editField(int id)
{
    // On lance la fenêtre voulue
    m_fieldsWindows[id]->exec();

    // On update le layout pour avoir les bonnes informations écritent
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

    // On parcours les items du layout
    while ((item = line->takeAt(0)) != 0)
    {
        item->widget()->deleteLater();
        delete item;
    }

    // On supprime la ligne
    delete line;

    // TODO Stocker les fields supprimer pour call la méthode remove quand il s'agit d'un formulaire existant
}

void createForm::valid()
{
    // On rentre les informations de l'utilisateur dans le formulaire
    m_form.setColor(m_color);
    m_form.setDescription(ui->description->toPlainText());
    m_form.setIdAuthor( dynamic_cast<Dashboard*> ( parent() )->getUserId() );
    m_form.setImportant(ui->messageImportant->toPlainText());
    m_form.setInfo(ui->messageInformation->toPlainText());
    m_form.setName(ui->nomLineEdit->text());    

    // Selon le bouton cliqué on lui donne le bon Status
    if (ui->demandeRadioButton->isChecked())
        m_form.setStatus(Entity::Form::Status::DEMAND);
    else if (ui->informationRadioButton->isChecked())
        m_form.setStatus(Entity::Form::Status::INFORMATION);

    // On vérifie que tous est valide avant de persister les données
    validForm();

    // Si le formulaire est valide
    if (m_formIsValid)
    {
        // On instancie notre objet pour la base de données
        Utility::PersisterManager pm;

        // On persist notre formulaire
        pm.persistOne(m_form);

        // On enregistre ceux qui pourront utiliser le formulaire
        for (QCheckBox* writersBox : m_listWriters)
        {
            // Si un groupe est coché
            if (writersBox->isChecked())
            {
                // On instancie un groupe
                Entity::Group group;
                    // On charge le groupe
                    auto error = group.loadByName(writersBox->text());

                // Si aucune error
                if (Entity::Entity::ErrorType::NONE == error)
                {
                    // On instance une relation groupe <-> formulaire
                    Relation::Write writer;
                        writer.setIdForm(m_form.getId());
                        writer.setIdGroup(group.getId());

                    // On persist la relation
                    pm.persistOne(writer);
                }
            }
        }

        // On enregistre ceux qui pourront lire les soumissions du formulaire
        for (QCheckBox* readersBox : m_listReaders)
        {
            // Si un groupe est coché
            if (readersBox->isChecked())
            {
                // On instancie un groupe
                Entity::Group group;
                    // On charge le groupe
                    auto error = group.loadByName(readersBox->text());

                // Si aucune error
                if (Entity::Entity::ErrorType::NONE == error)
                {
                    // On instance une relation groupe <-> formulaire
                    Relation::Read reader;
                        reader.setIdForm(m_form.getId());
                        reader.setIdGroup(group.getId());

                    // On persist la relation
                    pm.persistOne(reader);
                }
            }
        }

        // Enregistre les tags liés au formulaire
        for (QCheckBox* tagBox : m_listTags)
        {
            // Si le tag est coché
            if (tagBox->isChecked())
            {
                // On instancie un tag
                Entity::Tag tag;
                    // On charge un tag par son nom
                    auto error = tag.loadByName(tagBox->text());

                // Si aucune erreur
                if (Entity::Entity::ErrorType::NONE == error)
                {
                    // On instancie une relation tag <-> form
                    Relation::Categorizing categorizing;
                        categorizing.setIdForm(m_form.getId());
                        categorizing.setIdTag(tag.getId());

                    // On persist le tag
                    pm.persistOne(categorizing);
                }
            }
        }

        // On parcours les fenêtres gérant les champs
        for (auto it = m_fieldsWindows.begin(); it != m_fieldsWindows.end(); ++it)
        {
            // On persist les champs
            (*it)->persistField(m_form.getId());            
        }

        // On ferme la fenêtre
        close();
    }
}

void createForm::displayError(QString message)
{
    // Si on doit affiché une erreur alors le formulaire n'est pas valide
    m_formIsValid = false;

    // On affiche un message d'erreur
    QMessageBox::critical(this, "Erreur", message);
}

void createForm::validForm()
{
    // On considère le formulaire correct
    m_formIsValid = true;

    // On vérifie que le nom du formulaire n'existe pas
    if (m_form.formExist(m_form.getName()))
    {
        displayError("Le nom du formulaire est déjà existant.");
        return;
    }

    // On vérifie que le formulaire est valide
    if (!m_form.isValid()) {
        displayError("Le formulaire n'est pas valide (incomplet).");
        return;
    }

    // On instancie un foncteur qui vérifie si une CheckBox est coché
    Utility::HasCheckBoxChecked hascheckboxcheck;

    int nb = 0;

    // On appel l'algorithm count_if pour vérifier si il y a des readers
    nb = std::count_if(m_listReaders.begin(), m_listReaders.end(), hascheckboxcheck);

    // Si aucune case est coché on l'indique à l'utilisateur
    if (nb == 0)
    {
        displayError("Le formulaire doit avoir des lecteurs.");
        return;
    }

    // On appel l'algorithm count_if pour vérifier si il y a des writers
    nb = std::count_if(m_listWriters.begin(), m_listWriters.end(), hascheckboxcheck);

    // Si aucune case est coché on l'indique à l'utilisateur
    if (nb == 0)
    {
        displayError("Le formulaire doit avoir des utilisateurs.");
        return;
    }

    bool valid = false;

    // On parcours les fenêtres qui gèrent les champs
    for (auto &fieldWindow : m_fieldsWindows)
    {
        QObject::connect(fieldWindow, SIGNAL(sendError(QString)), this, SLOT(displayError(QString)));
        valid = !fieldWindow->validField();
        QObject::disconnect(fieldWindow, SIGNAL(sendError(QString)), this, SLOT(displayError(QString)));

        // Si un champs n'est pas valide
        if (!valid) {
            return;
        }
    }
}

void createForm::loadForm(Entity::Form form)
{
    m_form = form;

    QPushButton *supprimer = new QPushButton("Supprimer");

    ui->layoutButton->addWidget(supprimer);

    connect(supprimer, SIGNAL(clicked()), this, SLOT(deleteForm()));

    m_newForm = false;

    ui->nomLineEdit->setText(form.getName());
    ui->description->setPlainText(form.getDescription());
    ui->messageInformation->setPlainText(form.getInfo());
    ui->messageImportant->setPlainText(form.getImportant());

    if (form.getStatus() == Entity::Form::Status::DEMAND)
        ui->demandeRadioButton->setChecked(true);
    else
        ui->informationRadioButton->setChecked(true);

    m_color.setNamedColor("#" + form.getColor());

    QStringList writers = form.getWriters();

    // Ajout des utilisateurs
    for (QCheckBox* writerBox : m_listWriters)
    {
        if (writers.contains(writerBox->text()))
            writerBox->setChecked(true);
    }

    QStringList readers = form.getReaders();

    // Ajout des lecteurs
    for (QCheckBox* readerBox : m_listReaders)
    {
        if (readers.contains(readerBox->text()))
            readerBox->setChecked(true);
    }

    QStringList tags = form.getTags();

    // Ajout des tags
    for (QCheckBox* tagBox : m_listTags)
    {
        if (tags.contains(tagBox->text()))
            tagBox->setChecked(true);
    }

    QList<Entity::Field> fields = form.getFields();

    for (auto field : fields)
    {
        // Ajout des champs
        m_nbField++;

        // On ajoute une fenêtre dans la liste
        fieldWindow *fieldWd = new fieldWindow(this);
        fieldWd->load(field);
        m_fieldsWindows.insert(m_nbField, fieldWd);

        // On ajoute la ligne dans le layout des champs
        m_lines.insert( m_nbField, new QHBoxLayout() );

        // Nous ajoutons nos boutons personnalisés
        m_edits.insert( m_nbField, new CustomQPushButton("Modifier", m_nbField) );
        m_deletes.insert( m_nbField, new CustomQPushButton("Supprimer", m_nbField) );

        // On connect les slots pour savoir qu'elle bouton est appuyer
        QObject::connect(m_edits.last(), SIGNAL(customClicked(int)), this, SLOT(editField(int)));
        QObject::connect(m_deletes.last(), SIGNAL(customClicked(int)), this, SLOT(deleteField(int)));

        // Nous ajoutons des informations du champs dans le layout
        m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getTypeReadable()) );
        m_lines.last()->addWidget( new QLabel(m_fieldsWindows.last()->getField().getLabel()) );
        m_lines.last()->addWidget( new QLabel(QString("%1 contrainte(s)").arg(m_fieldsWindows.last()->getNbConstraint()) ) );
        m_lines.last()->addWidget( m_edits.last() );
        m_lines.last()->addWidget( m_deletes.last() );

        m_fieldsLayout->addLayout(m_lines.last());
    }
}

void createForm::deleteForm()
{
    m_form.remove();
    close();
}
