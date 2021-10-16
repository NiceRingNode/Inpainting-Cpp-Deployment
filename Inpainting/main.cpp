#include "Inpainting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Inpainting w;
    w.show();
    return a.exec();
}
