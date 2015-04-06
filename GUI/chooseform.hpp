#ifndef CHOOSEFORM_HPP
#define CHOOSEFORM_HPP

#include <QDialog>

namespace Ui {
class ChooseForm;
}

class ChooseForm : public QDialog
{
    Q_OBJECT

    public:
        explicit ChooseForm(QWidget *parent = 0);
        ~ChooseForm();

        void setForms(QStringList listForms);
        QString getFormName() const;

    public slots:
        void chooseForm();

    signals:
        void selectForm(QString formName);

    private:
        Ui::ChooseForm *ui;
        QString m_formName;
};

#endif // CHOOSEFORM_HPP
