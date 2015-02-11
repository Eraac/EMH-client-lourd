#ifndef FIELDWINDOW_HPP
#define FIELDWINDOW_HPP

#include <QDialog>

namespace Ui {
class fieldWindow;
}

class fieldWindow : public QDialog
{
    Q_OBJECT

public:
    explicit fieldWindow(QWidget *parent = 0);
    ~fieldWindow();

private:
    Ui::fieldWindow *ui;
};

#endif // FIELDWINDOW_HPP
