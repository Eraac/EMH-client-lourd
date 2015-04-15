#ifndef CHOOSEUSER_HPP
#define CHOOSEUSER_HPP

#include <QDialog>

namespace Ui {
    class ChooseUser;
}

class ChooseUser : public QDialog
{
    Q_OBJECT

    public:
        explicit ChooseUser(QWidget *parent = 0);
        ~ChooseUser();

        void setUsers(QStringList listUsers);
        QString getUserEmail() const;

    public slots:
        void chooseUser();

    private:
        Ui::ChooseUser *ui;
        QString m_email;
};

#endif // CHOOSEUSER_HPP
