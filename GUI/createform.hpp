#ifndef CREATEFORM_HPP
#define CREATEFORM_HPP

#include <QDialog>
#include <QColor>
#include <QColorDialog>

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

};

#endif // CREATEFORM_HPP
