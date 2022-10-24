#ifndef MEDIAPLANT_H
#define MEDIAPLANT_H

#include "instruments.h"

class MediaPlant
{
public:
    int id;
    int inst_id;
    QString description;
    QByteArray image;
    QDateTime dateTime;

    MediaPlant();
    MediaPlant(int _id, int _inst_id, QString _description, QByteArray _image, QDateTime _dateTime):
        id (_id), inst_id (_inst_id), description (_description), image (_image), dateTime (_dateTime) {};

    MediaPlant(int _inst_id, QString _description, QByteArray _image):
        id (-1), inst_id (_inst_id), description (_description), image (_image), dateTime (QDateTime::currentDateTime()) {};
};

#endif // MEDIAPLANT_H
