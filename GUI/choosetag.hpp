#ifndef CHOOSETAG_HPP
#define CHOOSETAG_HPP

#include <QDialog>

namespace Ui {
    class ChooseTag;
}

class ChooseTag : public QDialog
{
    Q_OBJECT

    public:
        explicit ChooseTag(QWidget *parent = 0);
        ~ChooseTag();

        void setTags(QStringList listTags);
        QString getTagName() const;

    public slots:
        void chooseTag();

    private:
        Ui::ChooseTag *ui;
        QString m_tagname;
};

#endif // CHOOSETAG_HPP
