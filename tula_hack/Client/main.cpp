#include <QCoreApplication>
#include "clientgeneral.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ClientGeneral clientGeneral;

    return a.exec();
}
