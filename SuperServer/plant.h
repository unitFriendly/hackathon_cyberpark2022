#ifndef PLANT_H
#define PLANT_H

#include "instruments.h"

class Plant
{
public:
    int id;
    QString name;
    QByteArray info_path;
    QByteArray description_path;
    QByteArray avatar;

    Plant();
    Plant(int _id, QString _name, QByteArray _info_path, QByteArray _description_path, QByteArray _avatar):
    id(_id), name (_name), info_path (_info_path), description_path (_description_path), avatar (_avatar){};
};

#endif // PLANT_H
