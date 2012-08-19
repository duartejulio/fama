#include <QtGui/QApplication>
#include "janela.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Janela w;
    w.show();

    return a.exec();
}
