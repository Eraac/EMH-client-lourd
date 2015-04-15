#ifndef EDITGROUP_HPP
#define EDITGROUP_HPP

#include <QDialog>
#include <QString>
#include "Model/Entity/Group.hpp"
#include "Utilty/PersisterManager.hpp"

namespace Ui {
    class EditGroup;
}

class EditGroup : public QDialog
{
    Q_OBJECT

    public:
        explicit EditGroup(QString const& groupName, QWidget *parent = 0);
        ~EditGroup();

    public slots:
        void enableButton(QString text);
        void deleteGroup();
        void changeGroup();

    signals:
        void groupModified();

    private:
        Ui::EditGroup *ui;
        QString m_oldGroupName;
};

#endif // EDITGROUP_HPP
