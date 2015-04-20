#include "choosetag.hpp"
#include "ui_choosetag.h"

ChooseTag::ChooseTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseTag)
{
    ui->setupUi(this);
}

ChooseTag::~ChooseTag()
{
    delete ui;
}

void ChooseTag::setTags(QStringList listTags)
{
    ui->tagsComboBox->addItems(listTags);
}

QString ChooseTag::getTagName() const
{
    return m_tagname;
}

void ChooseTag::chooseTag()
{
    m_tagname = ui->tagsComboBox->currentText();
    close();
}
