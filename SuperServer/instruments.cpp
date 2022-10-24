#include "instruments.h"


Instruments::Instruments()
{

}

QDate Instruments::getDate(QString dateText)
{
    QDate date;

    if(dateText.contains("-"))
    date=QDate::fromString(dateText, "dd-MM-yyyy");
else
        date=QDate::fromString(dateText.remove(0,3), "MMM dd yyyy");
    return date;
}

QDateTime Instruments::getDateTime(QString dateTimeText)
{
    QDateTime dateTime=QDateTime::fromString(dateTimeText, "yyyy-MM-dd hh:mm:ss");
    return dateTime;
}

QString Instruments::byteArrayToString(QByteArray bytes)
{
    return "";
}

QByteArray Instruments::StringToByteArray(QString string)
{
    QByteArray byteArray(string.size(), (char)255);

    for(int i = 0; i < byteArray.size(); i++)
    {
        byteArray[i] = string[i].toLatin1();
    }

    return byteArray;
}

QString Instruments::ByteArrayToString(QByteArray array)
{
    QString result(array.size(), QChar(255));

    for(int i = 0; i < array.size(); i++)
    {
        result[i] = array[i];
    }

    return result;
}
