#ifndef FARMERPLANT_H
#define FARMERPLANT_H

#include "instruments.h"
#include "mediaplant.h"
#include "logplant.h"

class FarmerPlant
{
public:
    int inst_id;
    QString login;
    int plant_id;
    int stage;
    QDateTime created_date;
    QString type;
    int type_id;
    int status;
    QString name;
    QByteArray avatar;

    QVector<MediaPlant> mediasPlant;
    QVector<LogPlant> logs;

    FarmerPlant();
    FarmerPlant(int _inst_id,QString _login,int _plant_id,int _stage,QDateTime _created_date,QString _type,int _status,QString _name,QByteArray _avatar):
       inst_id(_inst_id),login (_login),plant_id (_plant_id),stage (_stage),created_date (_created_date),type (_type),status (_status),name (_name),avatar (_avatar) {};
    FarmerPlant(int _inst_id,QString _login,int _plant_id,int _stage,int _type_id,int _status,QString _name,QByteArray _avatar):
       inst_id(_inst_id),login (_login),plant_id (_plant_id),stage (_stage),created_date (QDateTime::currentDateTime()),type_id (_type_id),status (_status),name (_name),avatar (_avatar) {};
    FarmerPlant(QString _login,int _plant_id,int _stage, int _type_id, int _status,QString _name,QByteArray _avatar):
       inst_id(-1),login (_login),plant_id (_plant_id),stage (_stage),created_date (QDateTime::currentDateTime()),type_id (_type_id),status (_status),name (_name),avatar (_avatar) {};

};

#endif // FARMERPLANT_H
