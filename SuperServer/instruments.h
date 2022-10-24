#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include <QString>
#include <QByteArray>
#include <QVector>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QFile>

class Instruments
{
public:
    Instruments();
    static QDate getDate(QString date);
    static QDateTime getDateTime(QString dateTime);
    static QString byteArrayToString(QByteArray bytes);

    static QByteArray StringToByteArray(QString string);
    static QString ByteArrayToString(QByteArray array);
};

#endif // INSTRUMENTS_H
