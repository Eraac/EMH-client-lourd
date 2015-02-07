#ifndef DATABASESETTING_HPP
#define DATABASESETTING_HPP

#include <QDialog>

namespace Ui {
    class DatabaseSetting;
}

class DatabaseSetting : public QDialog
{
    Q_OBJECT

    public:
        explicit DatabaseSetting(QWidget *parent = 0);
        ~DatabaseSetting();

    public slots:
        void formChange();

    private:
        Ui::DatabaseSetting *ui;
};

#endif // DATABASESETTING_HPP
