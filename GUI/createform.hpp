#ifndef CREATEFORM_HPP
#define CREATEFORM_HPP

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QList>
#include <QCheckBox>
#include "../Model/Entity/Group.hpp"
#include "../Model/Entity/Tag.hpp"

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

    private:
        Ui::createForm *ui;
        QColor m_color;

        QList<QCheckBox*> m_listWriters;
        QVBoxLayout *m_listWritersLayout;

        QList<QCheckBox*> m_listReaders;
        QVBoxLayout *m_listReadersLayout;

        QList<QCheckBox*> m_listTags;
        QVBoxLayout *m_listTagsLayout;

};

#endif // CREATEFORM_HPP
