#ifndef CREATEFORM_HPP
#define CREATEFORM_HPP

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QList>
#include <QCheckBox>
#include "customqpushbutton.hpp"
#include "../Model/Entity/Group.hpp"
#include "../Model/Entity/Tag.hpp"
#include "../GUI/fieldwindow.hpp"

namespace Ui {
    class createForm;
}

class createForm : public QDialog
{
    Q_OBJECT

    public:
        explicit createForm(QWidget *parent = 0);
        ~createForm();

    public slots:
        void chooseColor();
        void addField();
        void valid();        
        void editField(int id);
        void deleteField(int id);

    private:
        Ui::createForm *ui;
        QColor m_color;

        QList<QCheckBox*> m_listWriters;
        QVBoxLayout *m_listWritersLayout;

        QList<QCheckBox*> m_listReaders;
        QVBoxLayout *m_listReadersLayout;

        QList<QCheckBox*> m_listTags;
        QVBoxLayout *m_listTagsLayout;

        QVBoxLayout *m_fieldsLayout;

        int m_nbField;
        QList<fieldWindow*> m_fieldsWindows;
        QList<QHBoxLayout*> m_lines;
        QList<CustomQPushButton*> m_edits;
        QList<CustomQPushButton*> m_deletes;
};

#endif // CREATEFORM_HPP
