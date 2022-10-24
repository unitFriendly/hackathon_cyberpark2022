#ifndef PROTOCOLCOMMUNICATION_H
#define PROTOCOLCOMMUNICATION_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>



class ProtocolCommunication : public QObject
{
    Q_OBJECT
private:
    const static QString DFLT_PATH_FILE;

public:
    explicit ProtocolCommunication(QObject *parent = nullptr);

    const static QString ___COMMAND;

    //~~~~~commands start~~~~~
    const static QString ___CMD_AUTHORIZATION;
    const static QString ___CMD_REGISTRATION;
    const static QString ___CMD_GET_INFO_ABOUT_USER;
    const static QString ___CMD_GET_PLANTS_USER;
    const static QString ___CMD_GET_NAME_ID_FROM_GLOSSARY;
    const static QString ___CMD_GET_DESCRIPTION_FROM_GLOSSARY;
    const static QString ___CMD_GET_CARE_INFO_FROM_GLOSSARY;
    const static QString ___CMD_GET_AVATAR_FROM_GLOSSARY;
    const static QString ___CMD_GET_ALL_DATA_FROM_GLOSSARY;
    const static QString ___CMD_GET_USER_TASK;
    const static QString ___CMD_ADD_USER_TASK;
    const static QString ___CMD_GET_MEDIA_FOR_PLANT_ALL;
    const static QString ___CMD_GET_MEDIA_FOR_PLANT_ONE;
    const static QString ___CMD_ADD_MEDIA_FOR_PLANT;
    const static QString ___CMD_ADD_PLANT_FOR_USER;
    const static QString ___CMD_GET_LOG_FOR_USER;
    const static QString ___CMD_GET_LOG_FOR_PLANT;
    const static QString ___CMD_ADD_LOG;
    const static QString ___CMD_GET_ACHIVEMENTS_USER;
    const static QString ___CMD_GET_ALL_DATA_ACHIVEMENTS_USER;
    const static QString ___CMD_GET_INFO_ABOUT_ACHIVEMENT;
    const static QString ___CMD_SET_STAGE_PLANT;
    const static QString ___CMD_SET_STATUS_PLANT;
    //~~~~~commands end~~~~~~~

    const static QString ___LOGIN;
    const static QString ___PASSWORD;
    const static QString ___STATUS;
    const static QString ___E_MAIL;
    const static QString ___NAME;
    const static QString ___IMAGE;
    const static QString ___BIRTH_DATE;
    const static QString ___DATE_TIME;
    const static QString ___CARM_USER;
    const static QString ___EXP_USER;
    const static QString ___ID;
    const static QString ___INST_ID;
    const static QString ___DESCRIPTION;
    const static QString ___STAGE_PLANT;
    const static QString ___TYPE_GROUND;
    const static QString ___STATUS_PLANT;
    const static QString ___ARRAY_DATA;
    const static QString ___TYPE_ACTION;
    const static QString ___AIM;
    const static QString ___PROGRESS;
    const static QString ___DATA;

    //~~~~~status start~~~~~
    const static QString ___STS_DONE;
    const static QString ___STS_NOPE;
    //~~~~~status end~~~~~~~

    static QString ByteArrayToString(QByteArray array);
    static QByteArray StringToByteArray(QString string);
    static bool CompareSocket(QWebSocket* a, QWebSocket* b);
    static void SaveBinaryFile(QString binary, QString name, QString type, QString idMedia, QString idInst);
    static QString SaveBinaryFile(QString binary, QString name, QString id);
    static void SendTextMessage(QString message, QWebSocket *client);
    static void SendBinaryMessage(QByteArray message, QWebSocket *client);
    static QString jsonObjectToString(QJsonObject *object);
    static QJsonObject StringToJsonObject(QString str);
    static QByteArray LoadBinaryFile(QString path);
    static QString GetTypeFromPathFile(QString path);
    static QString GetNameFromPathFile(QString path);

signals:

};

#endif // PROTOCOLCOMMUNICATION_H
