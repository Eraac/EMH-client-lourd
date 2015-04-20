#ifndef EDITTAG_HPP
#define EDITTAG_HPP

#include <QDialog>
#include <QString>
#include "Model/Entity/Tag.hpp"
#include "Utilty/PersisterManager.hpp"

namespace Ui {
    class EditTag;
}

class EditTag : public QDialog
{
    Q_OBJECT

    public:
        explicit EditTag(QString const& tagName, QWidget *parent = 0);
        ~EditTag();

    public slots:
        void enableButton(QString text);
        void deleteTag();
        void changeTag();

    signals:
        void tagModified();

    private:
        Ui::EditTag *ui;
        QString m_oldTagName;
};

#endif // EDITTAG_HPP
