#include "RandomSelectGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RandomSelectGUI w;
    w.show();
    return a.exec();
}
