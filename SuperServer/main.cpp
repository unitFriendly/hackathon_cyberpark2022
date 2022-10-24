#include <QCoreApplication>
#include <QtDebug>
#include "servercontroller.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   ServerController* controller = ServerController::getInstance();

    int a1=controller->confirmAuthorization("maksim","123");
    int a2=controller->confirmAuthorization("maksim","1234");

    Farmer* a3= controller->getUser("maksim");
    Farmer* a31= controller->getUser("login1");

    Plant* a4=controller->getPlant(1);
    auto a5=controller->getAllPlant();

    auto a6=controller->getFarmerPlant(1);
    auto a7=controller->getAlFarmerPlant("maksim");

    auto a8=controller->getAchivement(1,"maksim");
    auto a9=controller->getAllAchivements("maksim");

    auto a10=Farmer("login2", "123", "mail2@mail.ru", "Name Family", nullptr, QDate::currentDate());
    auto a11= controller->registrationUser(a10);

    auto a12=controller->getAllFarmerTask("maksim");

    QFile f1("C:/Users/Rota5/Downloads/1633906788_80-p-domashnii-mandarin-foto-86.jpg");
    f1.open(QIODevice::ReadOnly);
    QByteArray bytes=f1.readAll();
    f1.close();
    Achivement a13("УУУ помогатор", "Описание помогатора", 17, bytes);
    //controller->addAchivment(a13);

    //controller->addFarmerTask(FarmerTask("maksim","Что то сделать", QDateTime::currentDateTime().addDays(5)));
    //controller->removeFarmerTask(3,"maksim");

    //controller->addMediaPlant(MediaPlant(1,"Как же он хорош",bytes));
    //controller->removeMediaPlant(4);

    //controller->addFarmerPlant(FarmerPlant("maksim",1,0,1,0,"Cаня", bytes));
    //controller->removeFarmerPlant(3);

    //controller->completeAchivement(10,"login2");

    //controller->addLogPlant(LogPlant(1,1),"maksim");
    //controller->removeLogPlant(5,1);

    //controller->updateFarmerPlant(FarmerPlant(2,"maksim",1,1,1,1,"Cаня", bytes));
    return a.exec();
}
