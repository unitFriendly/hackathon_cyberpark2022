#ifndef DATELEFT_H
#define DATELEFT_H

#include <QObject>
#include <QDateTime>

class DateLeft : public QObject
{
    Q_OBJECT
public:
    explicit DateLeft(QObject *parent = nullptr);


    QDate date;

    bool isFromGoto = false;

public slots:
    int getLeftDaySecondCall();
    int getLeftDayFirstCall();

    void setIsFromGoto(bool value)
    {
        isFromGoto = value;
    };

    bool getIsFromGoto()
    {
        return isFromGoto;
    }


signals:

};

#endif // DATELEFT_H
