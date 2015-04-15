#ifndef CHOOSEGROUP_H
#define CHOOSEGROUP_H

#include <QDialog>

namespace Ui {
    class ChooseGroup;
}

class ChooseGroup : public QDialog
{
    Q_OBJECT

    public:
        explicit ChooseGroup(QWidget *parent = 0);
        ~ChooseGroup();

        void setGroups(QStringList const& listGroups);
        QString getGroupName() const;

    public slots:
        void chooseGroups();

    private:
        Ui::ChooseGroup *ui;
        QString m_groupName;
};

#endif // CHOOSEGROUP_H
