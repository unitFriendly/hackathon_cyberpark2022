#ifndef FARMER_H
#define FARMER_H

#include "instruments.h"

class Farmer
{


public:
    QString login;
    QString password;
    QString mail;
    QString user_name;
    QByteArray avatar;
    QDate birth_date;
    QDateTime registration_date;
    int carm;
    int exp;

    Farmer();
    Farmer(QString _login,QString _password, QString _mail, QString _user_name,  QByteArray _avatar, QDate _birth_date, QDateTime _registration_date = QDateTime::currentDateTime(), int _carm=100, int _exp=0):
    login(_login), password(_password), mail (_mail), user_name (_user_name),  avatar (_avatar), birth_date (_birth_date), registration_date (_registration_date), carm (_carm), exp (_exp){};
};

#endif // FARMER_H
