#include "TrayMenu.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("AnotherKote'sSoftware");
    QApplication::setApplicationName("ClientMessenger");
    QApplication::setQuitOnLastWindowClosed(false);

    TrayMenu trayMenu;

    return a.exec();
}
