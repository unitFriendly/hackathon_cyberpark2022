#include "servergeneral.h"

ServerGeneral::ServerGeneral(QObject *parent) : QObject(parent)
{
    controllerDB = ServerController::getInstance();

    webSocketServer = new QWebSocketServer(QStringLiteral("SSL Server"),
                                           QWebSocketServer::NonSecureMode,
                                           this);
    QSslConfiguration sslConfiguration;
    QFile certFile(QStringLiteral(":/localhost.cert"));
    QFile keyFile(QStringLiteral(":/localhost.key"));
    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);
    QSslCertificate certificate(&certFile, QSsl::Pem);
    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
    certFile.close();
    keyFile.close();
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    webSocketServer->setSslConfiguration(sslConfiguration);

    if (webSocketServer->listen(QHostAddress::Any, PORT_LISTENER))
    {
        qDebug() << "SSL Echo Server listening on port" << PORT_LISTENER;

        connect(webSocketServer,
                &QWebSocketServer::newConnection,
                this,
                &ServerGeneral::onNewConnection);

        connect(webSocketServer,
                &QWebSocketServer::sslErrors,
                this,
                &ServerGeneral::onSslErrors);
    }
}

void ServerGeneral::onNewConnection()
{
    QWebSocket *pSocket = webSocketServer->nextPendingConnection();

    qDebug() << "Client connected:" << pSocket->peerPort();

    connect(pSocket,
            &QWebSocket::textMessageReceived,
            this,
            &ServerGeneral::processTextMessage);

    connect(pSocket,
            &QWebSocket::binaryMessageReceived,
            this,
            &ServerGeneral::processBinaryMessage);

    connect(pSocket,
            &QWebSocket::disconnected,
            this,
            &ServerGeneral::socketDisconnected);

    clientsOnline.push_back({pSocket, "", false});
}

void ServerGeneral::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    QJsonObject object = ProtocolCommunication::StringToJsonObject(message);

    MainHandlerMessage(&object, FindClient(pClient));
}

void ServerGeneral::processBinaryMessage(QByteArray message)
{
    //QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qDebug() << message;
}

void ServerGeneral::socketDisconnected()
{
    qDebug() << "Client disconnected";

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (pClient)
    {
        RemoveClient(pClient);
        pClient->deleteLater();
    }
}

void ServerGeneral::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << "Ssl errors occurred " << errors;
}

void ServerGeneral::RemoveClient(QWebSocket *client)
{
    for(int i = 0; i < clientsOnline.count(); i++)
    {
        if((clientsOnline[i].socket->peerAddress() == client->peerAddress()) && (clientsOnline[i].socket->peerPort() == client->peerPort()))
        {
            clientsOnline.remove(i);
        }
    }
}

DataClientOnline* ServerGeneral::FindClient(QWebSocket *client)
{
    for(int i = 0; i < clientsOnline.count(); i++)
    {
        if((clientsOnline[i].socket->peerAddress() == client->peerAddress()) && (clientsOnline[i].socket->peerPort() == client->peerPort()))
        {
            return &(clientsOnline[i]);
        }
    }

    return nullptr;
}

DataClientOnline* ServerGeneral::FindClient(QString login)
{
    for(int i = 0; i < clientsOnline.count(); i++)
    {
        if(clientsOnline[i].login == login)
        {
            return &(clientsOnline[i]);
        }
    }

    return nullptr;
}

void ServerGeneral::MainHandlerMessage(QJsonObject *object, DataClientOnline *client)
{
    QString command = ((*object)[ProtocolCommunication::___COMMAND]).toString();

    if(command == ProtocolCommunication::___CMD_AUTHORIZATION)
    {
        handlerAuthorization(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_REGISTRATION)
    {
        handlerRegistration(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_INFO_ABOUT_USER)
    {
        handlerGetInformationAboutUser(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_PLANTS_USER)
    {
        handlerGetPlantsUser(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_NAME_ID_FROM_GLOSSARY)
    {
        handlerGetNameIdFromGlossary(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_DESCRIPTION_FROM_GLOSSARY)
    {
        handlerGetDescriptionFromGlossary(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_CARE_INFO_FROM_GLOSSARY)
    {
        handlerGetCareInfoFromGlossary(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_AVATAR_FROM_GLOSSARY)
    {
        handlerGetAvatarFromGlossary(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_USER_TASK)
    {
        handlerGetUserTask(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_ADD_USER_TASK)
    {
        handlerAddUserTask(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ALL)
    {
        handlerGetMediaForFarmerPlantAll(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ONE)
    {
        handlerGetMediaForFarmerPlantOne(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_ADD_MEDIA_FOR_PLANT)
    {
        handlerAddMediaForFarmerPlant(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_ADD_PLANT_FOR_USER)
    {
        handlerAddPlantForUser(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_LOG_FOR_USER)
    {
        handlerGetLogForUser(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_LOG_FOR_PLANT)
    {
        handlerGetLogForPlant(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_ADD_LOG)
    {
        handlerAddLog(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_ACHIVEMENTS_USER)
    {
        handlerGetAchivementsUser(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_INFO_ABOUT_ACHIVEMENT)
    {
        handlerGetInfoAboutAchivement(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_SET_STAGE_PLANT)
    {
        handlerSetStagePlant(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_SET_STATUS_PLANT)
    {
        handlerSetStatusPlant(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_ALL_DATA_FROM_GLOSSARY)
    {
        handlerGetAllDataFromGlossary(object, client);
    }
    else if(command == ProtocolCommunication::___CMD_GET_ALL_DATA_ACHIVEMENTS_USER)
    {
        handlerGetAllDataAchivementsUser(object, client);
    }
}

void ServerGeneral::handlerAuthorization(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();
    QString password = ((*object)[ProtocolCommunication::___PASSWORD]).toString();

    int result = controllerDB->confirmAuthorization(login, password);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_AUTHORIZATION)}
                                         });

    if(result == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        client->login = login;
        client->isAuthorized = true;
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerRegistration(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();
    QString password = ((*object)[ProtocolCommunication::___PASSWORD]).toString();
    QString email = ((*object)[ProtocolCommunication::___E_MAIL]).toString();

    Farmer* farmerNew = new Farmer(login, password, email, "", ProtocolCommunication::StringToByteArray(""), QDate());

    int result = controllerDB->registrationUser(*farmerNew);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_REGISTRATION)}
                                         });

    if(result == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        client->login = login;
        client->isAuthorized = true;
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetInformationAboutUser(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    Farmer* farmer = controllerDB->getUser(login);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_INFO_ABOUT_USER)}
                                         });

    if(!farmer)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        answer->insert(ProtocolCommunication::___E_MAIL, QJsonValue(farmer->mail));
        answer->insert(ProtocolCommunication::___NAME, QJsonValue(farmer->user_name));
        answer->insert(ProtocolCommunication::___BIRTH_DATE, QJsonValue(farmer->birth_date.toString()));
        answer->insert(ProtocolCommunication::___DATE_TIME, QJsonValue(farmer->registration_date.toString()));
        answer->insert(ProtocolCommunication::___CARM_USER, QJsonValue(QString::number(farmer->carm)));
        answer->insert(ProtocolCommunication::___EXP_USER, QJsonValue(QString::number(farmer->exp)));
        answer->insert(ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(farmer->avatar)));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetPlantsUser(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    QVector<FarmerPlant> plants = controllerDB->getAlFarmerPlant(login);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_PLANTS_USER)}
                                         });

    if(plants.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < plants.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(plants[i].avatar))},
                                                    {ProtocolCommunication::___DATE_TIME, QJsonValue(plants[i].created_date.toString())},
                                                    {ProtocolCommunication::___INST_ID, QJsonValue(QString::number(plants[i].inst_id))},
                                                    {ProtocolCommunication::___NAME, QJsonValue(plants[i].name)},
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(plants[i].plant_id))},
                                                    {ProtocolCommunication::___STAGE_PLANT, QJsonValue(QString::number(plants[i].stage))},
                                                    {ProtocolCommunication::___STATUS_PLANT, QJsonValue(QString::number(plants[i].status))},
                                                    {ProtocolCommunication::___TYPE_GROUND, QJsonValue(plants[i].type)}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerAddPlantForUser(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();
    QString stage = ((*object)[ProtocolCommunication::___STAGE_PLANT]).toString();
    QString plantID = ((*object)[ProtocolCommunication::___ID]).toString();
    QString typeGround = ((*object)[ProtocolCommunication::___TYPE_GROUND]).toString();
    QString name = ((*object)[ProtocolCommunication::___NAME]).toString();
    QString image = ((*object)[ProtocolCommunication::___IMAGE]).toString();

    FarmerPlant* farmerPlant = new FarmerPlant(login, plantID.toInt(), stage.toInt(), typeGround.toInt(), 1, name, ProtocolCommunication::StringToByteArray(image));

    controllerDB->addFarmerPlant(*farmerPlant);
}

void ServerGeneral::handlerGetNameIdFromGlossary(QJsonObject *object, DataClientOnline *client)
{
    QVector<Plant> plants = controllerDB->getAllPlant();

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_NAME_ID_FROM_GLOSSARY)}
                                         });

    if(plants.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < plants.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___NAME, QJsonValue(plants[i].name)},
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(plants[i].id))}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetDescriptionFromGlossary(QJsonObject *object, DataClientOnline *client)
{
    QString idPlant = ((*object)[ProtocolCommunication::___ID]).toString();

    Plant *plant = controllerDB->getPlant(idPlant.toInt());

    QByteArray description = plant->description_path;

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_DESCRIPTION_FROM_GLOSSARY)}
                                         });

    if(description.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        answer->insert(ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(description)));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetCareInfoFromGlossary(QJsonObject *object, DataClientOnline *client)
{
    QString idPlant = ((*object)[ProtocolCommunication::___ID]).toString();

    Plant *plant = controllerDB->getPlant(idPlant.toInt());

    QByteArray careInfo = plant->info_path;

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_CARE_INFO_FROM_GLOSSARY)}
                                         });

    if(careInfo.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        answer->insert(ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(careInfo)));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetAvatarFromGlossary(QJsonObject *object, DataClientOnline *client)
{
    QString idPlant = ((*object)[ProtocolCommunication::___ID]).toString();

    Plant *plant = controllerDB->getPlant(idPlant.toInt());

    QByteArray avatar = plant->avatar;

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_AVATAR_FROM_GLOSSARY)}
                                         });

    if(avatar.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        answer->insert(ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(avatar)));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetAllDataFromGlossary(QJsonObject *object, DataClientOnline *client)
{
    QVector<Plant> plants = controllerDB->getAllPlant();

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_ALL_DATA_FROM_GLOSSARY)}
                                         });

    if(plants.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < plants.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___NAME, QJsonValue(plants[i].name)},
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(plants[i].id))},
                                                    {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(plants[i].avatar))},
                                                    {ProtocolCommunication::___DESCRIPTION, QJsonValue(ProtocolCommunication::ByteArrayToString(plants[i].description_path))},
                                                    {ProtocolCommunication::___DATA, QJsonValue(ProtocolCommunication::ByteArrayToString(plants[i].info_path))}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetUserTask(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    QVector<FarmerTask> tasks = controllerDB->getAllFarmerTask(login);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_USER_TASK)}
                                         });

    if(tasks.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < tasks.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(tasks[i].id))},
                                                    {ProtocolCommunication::___DESCRIPTION, QJsonValue(tasks[i].text)},
                                                    {ProtocolCommunication::___DATE_TIME, QJsonValue(tasks[i].dateTime.toString())}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerAddUserTask(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();
    QString description = ((*object)[ProtocolCommunication::___DESCRIPTION]).toString();
    QString dataTime = ((*object)[ProtocolCommunication::___DATE_TIME]).toString();

    FarmerTask* farmerTask = new FarmerTask(login, description, QDateTime::fromString(dataTime));
    controllerDB->addFarmerTask(*farmerTask);
}

void ServerGeneral::handlerGetMediaForFarmerPlantAll(QJsonObject *object, DataClientOnline *client)
{
    QString id = ((*object)[ProtocolCommunication::___ID]).toString();

    QVector<MediaPlant> mediaPlant = controllerDB->getAllMediaPlant(id.toInt());

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ALL)}
                                         });

    if(mediaPlant.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < mediaPlant.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___DATE_TIME, QJsonValue(mediaPlant[i].dateTime.toString())},
                                                    {ProtocolCommunication::___DESCRIPTION, QJsonValue(mediaPlant[i].description)},
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(mediaPlant[i].id))},
                                                    {ProtocolCommunication::___INST_ID, QJsonValue(QString::number(mediaPlant[i].inst_id))},
                                                    {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(mediaPlant[i].image))}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
        answer->insert(ProtocolCommunication::___INST_ID, id);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetMediaForFarmerPlantOne(QJsonObject *object, DataClientOnline *client)
{
    QString id = ((*object)[ProtocolCommunication::___ID]).toString();

    MediaPlant *mediaPlant = controllerDB->getMediaPlant(id.toInt());

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ONE)}
                                         });

    if(!mediaPlant)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));
        answer->insert(ProtocolCommunication::___DATE_TIME, QJsonValue(mediaPlant->dateTime.toString()));
        answer->insert(ProtocolCommunication::___DESCRIPTION, QJsonValue(mediaPlant->description));
        answer->insert(ProtocolCommunication::___ID, QJsonValue(QString::number(mediaPlant->id)));
        answer->insert(ProtocolCommunication::___INST_ID, QJsonValue(QString::number(mediaPlant->inst_id)));
        answer->insert(ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(mediaPlant->image)));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerAddMediaForFarmerPlant(QJsonObject *object, DataClientOnline *client)
{
    QString description = ((*object)[ProtocolCommunication::___DESCRIPTION]).toString();
    QString image = ((*object)[ProtocolCommunication::___IMAGE]).toString();
    QString instID = ((*object)[ProtocolCommunication::___INST_ID]).toString();

    MediaPlant *mediaPlant = new MediaPlant(instID.toInt(), description, ProtocolCommunication::StringToByteArray(image));

    controllerDB->addMediaPlant(*mediaPlant, client->login);
}

void ServerGeneral::handlerGetLogForUser(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    QVector<LogPlant> logs = controllerDB->getAllLogUser(login);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_LOG_FOR_USER)}
                                         });

    if(logs.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < logs.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___DATE_TIME, QJsonValue(logs[i].dateTime.toString())},
                                                    {ProtocolCommunication::___TYPE_ACTION, QJsonValue(QString::number(logs[i].action_id))},
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(logs[i].id))},
                                                    {ProtocolCommunication::___INST_ID, QJsonValue(QString::number(logs[i].inst_id))}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetLogForPlant(QJsonObject *object, DataClientOnline *client)
{
    QString id = ((*object)[ProtocolCommunication::___ID]).toString();

    QVector<LogPlant> logs = controllerDB->getAllLogPlant(id.toInt());

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_LOG_FOR_PLANT)}
                                         });

    if(logs.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < logs.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___DATE_TIME, QJsonValue(logs[i].dateTime.toString())},
                                                    {ProtocolCommunication::___TYPE_ACTION, QJsonValue(QString::number(logs[i].action_id))},
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(logs[i].id))},
                                                    {ProtocolCommunication::___INST_ID, QJsonValue(QString::number(logs[i].inst_id))}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerAddLog(QJsonObject *object, DataClientOnline *client)
{
    QString instID = ((*object)[ProtocolCommunication::___INST_ID]).toString();
    QString typeAction = ((*object)[ProtocolCommunication::___TYPE_ACTION]).toString();
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    LogPlant* log = new LogPlant(instID.toInt(), typeAction.toInt());

    controllerDB->addLogPlant(*log, login);
}

void ServerGeneral::handlerGetAchivementsUser(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    QVector<Achivement> achivement = controllerDB->getAllAchivements(login);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_ACHIVEMENTS_USER)}
                                         });

    if(achivement.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < achivement.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(achivement[i].id))}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetInfoAboutAchivement(QJsonObject *object, DataClientOnline *client)
{
    QString id = ((*object)[ProtocolCommunication::___ID]).toString();

    Achivement* achivement = controllerDB->getAchivement(id.toInt(), client->login);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_INFO_ABOUT_ACHIVEMENT)}
                                         });

    if(!achivement)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        answer->insert(ProtocolCommunication::___ID, QJsonValue(id));
        answer->insert(ProtocolCommunication::___AIM, QJsonValue(QString::number(achivement->aim)));
        answer->insert(ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(achivement->image)));
        answer->insert(ProtocolCommunication::___DESCRIPTION, QJsonValue(achivement->info));
        answer->insert(ProtocolCommunication::___NAME, QJsonValue(achivement->name));
        answer->insert(ProtocolCommunication::___PROGRESS, QJsonValue(QString::number(achivement->progress)));
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerGetAllDataAchivementsUser(QJsonObject *object, DataClientOnline *client)
{
    QString login = ((*object)[ProtocolCommunication::___LOGIN]).toString();

    QVector<Achivement> achivement = controllerDB->getAllAchivements(login);

    QJsonObject* answer = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_ALL_DATA_ACHIVEMENTS_USER)}
                                         });

    if(achivement.size() == 0)
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_NOPE));
    }
    else
    {
        answer->insert(ProtocolCommunication::___STATUS, QJsonValue(ProtocolCommunication::___STS_DONE));

        QJsonArray jArr;
        QJsonObject jObj;

        for(int i = 0; i < achivement.size(); i++)
        {
            QJsonObject* jObj = new QJsonObject({
                                                    {ProtocolCommunication::___ID, QJsonValue(QString::number(achivement[i].id))},
                                                    {ProtocolCommunication::___AIM, QJsonValue(QString::number(achivement[i].aim))},
                                                    {ProtocolCommunication::___PROGRESS, QJsonValue(QString::number(achivement[i].progress))},
                                                    {ProtocolCommunication::___NAME, QJsonValue(achivement[i].name)},
                                                    {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(achivement[i].image))},
                                                    {ProtocolCommunication::___DESCRIPTION, QJsonValue(achivement[i].info)}
                                               });

            jArr.push_back(*jObj);
        }

        answer->insert(ProtocolCommunication::___ARRAY_DATA, jArr);
    }

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(answer), client->socket);
}

void ServerGeneral::handlerSetStatusPlant(QJsonObject *object, DataClientOnline *client)
{
    QString instID = ((*object)[ProtocolCommunication::___INST_ID]).toString();
    QString newValueStatus = ((*object)[ProtocolCommunication::___STATUS_PLANT]).toString();

    controllerDB->setStatusPlant(instID.toInt(), newValueStatus.toInt(), client->login);
}

void ServerGeneral::handlerSetStagePlant(QJsonObject *object, DataClientOnline *client)
{
    QString instID = ((*object)[ProtocolCommunication::___INST_ID]).toString();
    QString newValueStage = ((*object)[ProtocolCommunication::___STAGE_PLANT]).toString();

    controllerDB->setStagePlant(instID.toInt(), newValueStage.toInt(), client->login);
}
