#include "protocolcommunication.h"

const QString ProtocolCommunication::DFLT_PATH_FILE = "C:\\tula_hack_att";

const QString ProtocolCommunication::___COMMAND = QString("command");
const QString ProtocolCommunication::___CMD_AUTHORIZATION = QString("authorization");
const QString ProtocolCommunication::___CMD_REGISTRATION = QString("registration");
const QString ProtocolCommunication::___CMD_GET_INFO_ABOUT_USER = QString("get_info_about_user");
const QString ProtocolCommunication::___CMD_GET_PLANTS_USER = QString("get_plants_user");
const QString ProtocolCommunication::___CMD_GET_NAME_ID_FROM_GLOSSARY = QString("get_name_id_from_glossary");
const QString ProtocolCommunication::___CMD_GET_DESCRIPTION_FROM_GLOSSARY = QString("get_description_from_glossary");
const QString ProtocolCommunication::___CMD_GET_CARE_INFO_FROM_GLOSSARY = QString("get_care_info_from_glossary");
const QString ProtocolCommunication::___CMD_GET_AVATAR_FROM_GLOSSARY = QString("get_avatar_from_glossary");
const QString ProtocolCommunication::___CMD_GET_ALL_DATA_FROM_GLOSSARY = QString("get_all_data_from_glossary");
const QString ProtocolCommunication::___CMD_GET_USER_TASK = QString("get_user_task");
const QString ProtocolCommunication::___CMD_ADD_USER_TASK = QString("add_user_task");
const QString ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ALL = QString("get_media_for_plant_all");
const QString ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ONE = QString("get_media_for_plant_one");
const QString ProtocolCommunication::___CMD_ADD_MEDIA_FOR_PLANT = QString("add_media_for_plant");
const QString ProtocolCommunication::___CMD_ADD_PLANT_FOR_USER = QString("add_plant_for_user");
const QString ProtocolCommunication::___CMD_GET_LOG_FOR_USER = QString("get_log_for_user");
const QString ProtocolCommunication::___CMD_GET_LOG_FOR_PLANT = QString("get_log_for_plant");
const QString ProtocolCommunication::___CMD_ADD_LOG = QString("add_log");
const QString ProtocolCommunication::___CMD_GET_ACHIVEMENTS_USER = QString("get_achivements_user");
const QString ProtocolCommunication::___CMD_GET_ALL_DATA_ACHIVEMENTS_USER = QString("get_all_data_achivements_user");
const QString ProtocolCommunication::___CMD_GET_INFO_ABOUT_ACHIVEMENT = QString("get_info_achivements");
const QString ProtocolCommunication::___CMD_SET_STAGE_PLANT = QString("set_stage_plant");
const QString ProtocolCommunication::___CMD_SET_STATUS_PLANT = QString("set_status_plant");
const QString ProtocolCommunication::___LOGIN = QString("login");
const QString ProtocolCommunication::___PASSWORD = QString("password");
const QString ProtocolCommunication::___STATUS = QString("status");
const QString ProtocolCommunication::___STS_DONE = QString("done");
const QString ProtocolCommunication::___STS_NOPE = QString("nope");
const QString ProtocolCommunication::___E_MAIL = QString("email");
const QString ProtocolCommunication::___NAME = QString("name");
const QString ProtocolCommunication::___IMAGE = QString("image");
const QString ProtocolCommunication::___BIRTH_DATE = QString("birth_date");
const QString ProtocolCommunication::___DATE_TIME = QString("date_time");
const QString ProtocolCommunication::___CARM_USER = QString("carm_user");
const QString ProtocolCommunication::___EXP_USER = QString("exp_user");
const QString ProtocolCommunication::___ID = QString("id");
const QString ProtocolCommunication::___INST_ID = QString("inst_id");
const QString ProtocolCommunication::___DESCRIPTION = QString("description");
const QString ProtocolCommunication::___STAGE_PLANT = QString("stage_plant");
const QString ProtocolCommunication::___TYPE_GROUND = QString("type_ground");
const QString ProtocolCommunication::___STATUS_PLANT = QString("status_plant");
const QString ProtocolCommunication::___ARRAY_DATA = QString("array_data");
const QString ProtocolCommunication::___TYPE_ACTION = QString("type_action");
const QString ProtocolCommunication::___AIM = QString("aim");
const QString ProtocolCommunication::___PROGRESS = QString("progress");
const QString ProtocolCommunication::___DATA = QString("data");

QString ProtocolCommunication::ByteArrayToString(QByteArray array)
{
    QString result(array.size(), QChar(255));

    for(int i = 0; i < array.size(); i++)
    {
        result[i] = array[i];
    }

    return result;
}

QByteArray ProtocolCommunication::StringToByteArray(QString string)
{
    QByteArray byteArray(string.size(), (char)255);

    for(int i = 0; i < byteArray.size(); i++)
    {
        byteArray[i] = string[i].toLatin1();
    }

    return byteArray;
}

void ProtocolCommunication::SaveBinaryFile(QString binary, QString name, QString type, QString idMedia, QString idInst)
{
    QFile file(DFLT_PATH_FILE + name + "." + type);

    QByteArray byteArray = StringToByteArray(binary);

    file.write(byteArray);
    file.close();
}

QString ProtocolCommunication::SaveBinaryFile(QString binary, QString name, QString id)
{
    QDir p=QDir::current();

    QString path = p.path()+"/" + name +"_"+id;
    QFile file(path);

    QByteArray byteArray = StringToByteArray(binary);

    file.open(QIODevice::WriteOnly);
    file.write(byteArray);
    file.close();

    return path;
}

void ProtocolCommunication::SendTextMessage(QString message, QWebSocket *client)
{
    client->sendTextMessage(message);
}

void ProtocolCommunication::SendBinaryMessage(QByteArray message, QWebSocket *client)
{
    client->sendBinaryMessage(message);
}

QString ProtocolCommunication::jsonObjectToString(QJsonObject *object)
{
    static QJsonDocument jDoc;
    jDoc.setObject(*object);
    return jDoc.toJson();
}

QJsonObject ProtocolCommunication::StringToJsonObject(QString str)
{
    static QJsonDocument jDoc;
    jDoc = QJsonDocument::fromJson(str.toUtf8());
    return jDoc.object();
}

bool ProtocolCommunication::CompareSocket(QWebSocket* a, QWebSocket* b)
{
    return ((a->peerAddress() == b->peerAddress()) && (a->peerPort() == b->peerPort()));
}

QByteArray ProtocolCommunication::LoadBinaryFile(QString path)
{
    QByteArray byteArray;
    QFile file(path);
    file.open(QFile::ReadOnly);
    byteArray = file.readAll();
    file.close();
    return byteArray;
}

QString ProtocolCommunication::GetTypeFromPathFile(QString path)
{
    int indexDot = path.lastIndexOf('.');
    indexDot++;
    int lenType = path.size() - indexDot;
    QString result(lenType, ' ');

    for(int i = 0; i < lenType; i++)
    {
        result[i] = path[indexDot + i];
    }

    return result;
}

QString ProtocolCommunication::GetNameFromPathFile(QString path)
{
    int indexDot = path.lastIndexOf('.');
    int indexStartName = path.lastIndexOf('\\') + 1;

    int lenType = indexDot - indexStartName;
    QString result(lenType, ' ');

    for(int i = 0; i < lenType; i++)
    {
        result[i] = path[indexStartName + i];
    }

    return result;
}

ProtocolCommunication::ProtocolCommunication(QObject *parent) : QObject(parent)
{

}
