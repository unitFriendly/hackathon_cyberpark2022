#ifndef FARMERTASK_H
#define FARMERTASK_H

#include "instruments.h"

class FarmerTask
{
public:
    int id;
    QString login;
    QString text;
    QDateTime dateTime;

    FarmerTask();
    FarmerTask(int _id,QString _login,QString _text,QDateTime _dateTime):
    id (_id),login (_login),text (_text),dateTime (_dateTime){};
    FarmerTask(QString _login,QString _text,QDateTime _dateTime):
    id (-1),login (_login),text (_text),dateTime (_dateTime){};
};

#endif // FARMERTASK_H
