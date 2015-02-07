#ifndef ABOUTMYDEVS_H
#define ABOUTMYDEVS_H

#include <QDialog>

namespace Ui {
class AboutMyDevs;
}

class AboutMyDevs : public QDialog
{
    Q_OBJECT

public:
    explicit AboutMyDevs(QWidget *parent = 0);
    ~AboutMyDevs();

private:
    Ui::AboutMyDevs *ui;
};

#endif // ABOUTMYDEVS_H
