#ifndef CREATEFORM_HPP
#define CREATEFORM_HPP

#include <algorithm>
#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QList>
#include <QMap>
#include <QCheckBox>
#include "customqpushbutton.hpp"
#include "../Model/Entity/Form.hpp"
#include "../Model/Entity/Group.hpp"
#include "../Model/Entity/Tag.hpp"
#include "../Model/Relation/Belong.hpp"
#include "../Model/Relation/Write.hpp"
#include "../Model/Relation/Read.hpp"
#include "../Model/Relation/Categorizing.hpp"
#include "../GUI/fieldwindow.hpp"
#include "../Utilty/Foncteur/hascheckboxchecked.hpp"

namespace Ui {
    class createForm;
}

class createForm : public QDialog
{
    Q_OBJECT

    public:
        explicit createForm(QWidget *parent = 0);
        ~createForm();

        void validForm();

    public slots:
        void chooseColor();
        void addField();
        void valid();        
        void editField(int id);
        void deleteField(int id);
        void displayError(QString message);

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
        Entity::Form m_form;
        QMap<int, fieldWindow*> m_fieldsWindows;
        QMap<int, QHBoxLayout*> m_lines;
        QMap<int, CustomQPushButton*> m_edits;
        QMap<int, CustomQPushButton*> m_deletes;

        bool m_formIsValid;
};

#endif // CREATEFORM_HPP
