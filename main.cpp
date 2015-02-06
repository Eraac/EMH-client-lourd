#include <QApplication>
#include "Utilty/UserHandle.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    UserHandle userHandle;
    userHandle.run();

    return app.exec();
}
