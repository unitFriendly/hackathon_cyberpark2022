#include <QCoreApplication>
#include "servergeneral.h"
#include "../../SuperServer/servercontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerGeneral serverGeneral;




    return a.exec();
}
