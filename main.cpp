#include <QApplication>
#include "GUI/loginwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow window;
    window.show();

    return app.exec();
}
