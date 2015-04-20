#include "edittag.hpp"
#include "ui_edittag.h"

EditTag::EditTag(QString const& tagName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTag),
    m_oldTagName(tagName)
{
    ui->setupUi(this);
}

EditTag::~EditTag()
{
    delete ui;
}

void EditTag::enableButton(QString text)
{
    ui->changeButton->setEnabled(!text.isEmpty());
}

void EditTag::deleteTag()
{
    Entity::Tag tag{};
        tag.loadByName(m_oldTagName);
        tag.remove();

    close();
}

void EditTag::changeTag()
{
    QString newTagName = ui->nomLineEdit->text();

    Entity::Tag tag{};

    if (!tag.tagExist(newTagName))
    {
        tag.loadByName(m_oldTagName);
        tag.setName(newTagName);

        Utility::PersisterManager pm;
            pm.persistOne(tag);

        emit tagModified();

        close();
    }
    else
    {
        ui->errorLabel->setText("Ce nom de tag existe déjà");
    }
}
