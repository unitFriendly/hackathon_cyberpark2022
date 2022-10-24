#ifndef SERVERGENERAL_H
#define SERVERGENERAL_H

#include <QObject>
#include <QWebSocketServer>
#include <QFile>
#include <QSslKey>
#include <QWebSocket>
#include <QJsonArray>
#include <../protocolcommunication.h>
#include "../../SuperServer/servercontroller.h"

struct DataClientOnline
{
    QWebSocket* socket;
    QString login;
    bool isAuthorized;
};

class ServerGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ServerGeneral(QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void onSslErrors(const QList<QSslError> &errors);

private:

    ServerController* controllerDB;

    const quint16 PORT_LISTENER = 1234;
    QWebSocketServer *webSocketServer;
    QVector<DataClientOnline> clientsOnline;

    void RemoveClient(QWebSocket *client);

    DataClientOnline* FindClient(QWebSocket *client);
    DataClientOnline* FindClient(QString login);

    void MainHandlerMessage(QJsonObject* object, DataClientOnline* client);

    void handlerAuthorization(QJsonObject* object, DataClientOnline *client);
    void handlerRegistration(QJsonObject* object, DataClientOnline *client);

    void handlerGetInformationAboutUser(QJsonObject* object, DataClientOnline *client);

    void handlerGetPlantsUser(QJsonObject* object, DataClientOnline *client);
    void handlerAddPlantForUser(QJsonObject* object, DataClientOnline *client);

    void handlerGetNameIdFromGlossary(QJsonObject* object, DataClientOnline *client);
    void handlerGetDescriptionFromGlossary(QJsonObject* object, DataClientOnline *client);
    void handlerGetCareInfoFromGlossary(QJsonObject* object, DataClientOnline *client);
    void handlerGetAvatarFromGlossary(QJsonObject* object, DataClientOnline *client);
    void handlerGetAllDataFromGlossary(QJsonObject* object, DataClientOnline *client);

    void handlerGetUserTask(QJsonObject* object, DataClientOnline *client);
    void handlerAddUserTask(QJsonObject* object, DataClientOnline *client);

    void handlerGetMediaForFarmerPlantAll(QJsonObject* object, DataClientOnline *client);
    void handlerGetMediaForFarmerPlantOne(QJsonObject* object, DataClientOnline *client);
    void handlerAddMediaForFarmerPlant(QJsonObject* object, DataClientOnline *client);

    void handlerGetLogForUser(QJsonObject* object, DataClientOnline *client);
    void handlerGetLogForPlant(QJsonObject* object, DataClientOnline *client);
    void handlerAddLog(QJsonObject* object, DataClientOnline *client);

    void handlerGetAchivementsUser(QJsonObject* object, DataClientOnline *client);
    void handlerGetInfoAboutAchivement(QJsonObject* object, DataClientOnline *client);
    void handlerGetAllDataAchivementsUser(QJsonObject* object, DataClientOnline *client);

    void handlerSetStatusPlant(QJsonObject* object, DataClientOnline *client);
    void handlerSetStagePlant(QJsonObject* object, DataClientOnline *client);


signals:

};

#endif // SERVERGENERAL_H
