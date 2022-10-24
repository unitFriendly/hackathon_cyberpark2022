#ifndef LOGPLANT_H
#define LOGPLANT_H

#include "instruments.h"

class LogPlant
{
public:
 int id;
 int inst_id;
 QString action;
 int action_id;
 QDateTime dateTime;

    LogPlant();
    LogPlant( int _id, int _inst_id, QString _action, int _action_id, QDateTime _dateTime):
        id (_id), inst_id (_inst_id),action (_action), action_id(_action_id), dateTime (_dateTime) {};
    LogPlant(int _inst_id, int _action_id):
        id (-1), inst_id (_inst_id),action_id (_action_id),dateTime (QDateTime::currentDateTime()) {};
};

#endif // LOGPLANT_H
