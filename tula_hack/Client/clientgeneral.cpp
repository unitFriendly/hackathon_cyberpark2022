#include "clientgeneral.h"

void ClientGeneral::onConnected()
{
    qDebug() << "WebSocketServer connected";
    connect(&socketServer,
            &QWebSocket::textMessageReceived,
            this,
            &ClientGeneral::onTextMessageReceived);
}

void ClientGeneral::onTextMessageReceived(QString message)
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());

    QJsonObject object = ProtocolCommunication::StringToJsonObject(message);

    if(ProtocolCommunication::CompareSocket(socket, &socketServer))
    {
        processingEventFromServer(&object);
    }
    else
    {
        qDebug() << "не от сервера";
    }
}

void ClientGeneral::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);
    socketServer.ignoreSslErrors();
}

void ClientGeneral::processingEventFromServer(QJsonObject *object)
{
    QString command = ((*object)[ProtocolCommunication::___COMMAND]).toString();

    if(command == ProtocolCommunication::___CMD_AUTHORIZATION)
    {
        handlerAuthorization(object);
    }
    else if(command == ProtocolCommunication::___CMD_REGISTRATION)
    {
        handlerRegistration(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_INFO_ABOUT_USER)
    {
        handlerInformationAboutUser(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_PLANTS_USER)
    {
        handlerPlantsUser(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_NAME_ID_FROM_GLOSSARY)
    {
        handlerNameIdFromGlossary(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_DESCRIPTION_FROM_GLOSSARY)
    {
        handlerDescriptionFromGlossary(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_CARE_INFO_FROM_GLOSSARY)
    {
        handlerCareInfoFromGlossary(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_AVATAR_FROM_GLOSSARY)
    {
        handlerAvatarFromGlossary(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_USER_TASK)
    {
        handlerUserTask(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ALL)
    {
        handlerMediaForFarmerPlantAll(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ONE)
    {
        handlerMediaForFarmerPlantOne(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_LOG_FOR_USER)
    {
        handlerLogForPlant(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_LOG_FOR_PLANT)
    {
        handlerLogForPlant(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_ACHIVEMENTS_USER)
    {
        handlerAchivementsUser(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_INFO_ABOUT_ACHIVEMENT)
    {
        handlerInfoAboutAchivement(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_ALL_DATA_FROM_GLOSSARY)
    {
        handlerAllDataFromGlossary(object);
    }
    else if(command == ProtocolCommunication::___CMD_GET_ALL_DATA_ACHIVEMENTS_USER)
    {
        handlerAllDataAchivementsUser(object);
    }
}

void ClientGeneral::handlerAuthorization(QJsonObject *object)
{
    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        // успешная авторизация
        isAuthorization = true;
        sendGetInformationAboutUser();
        emit onAnswerAuthorization(true);
    }
    else
    {
        // не авторизовался по какой то причине
        emit onAnswerAuthorization(false);
    }
}

void ClientGeneral::handlerRegistration(QJsonObject *object)
{
    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        // успешная регистрация
        isAuthorization = true;
        sendGetInformationAboutUser();
        emit onAnswerRegistration(true);
    }
    else
    {
        // не зарегистрировался по какой то причине
        emit onAnswerRegistration(false);
    }
}

void ClientGeneral::handlerInformationAboutUser(QJsonObject *object)
{
    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        // информация получена
        farmer.avatar = ProtocolCommunication::StringToByteArray(((*object)[ProtocolCommunication::___IMAGE]).toString());
        pathFiles[farmer.avatar] = ProtocolCommunication::SaveBinaryFile(ProtocolCommunication::ByteArrayToString(farmer.avatar),"avatarUser", myLogin);
        farmer.birth_date = QDate::fromString(((*object)[ProtocolCommunication::___BIRTH_DATE]).toString());
        farmer.carm = ((*object)[ProtocolCommunication::___CARM_USER]).toString().toInt();
        farmer.exp = ((*object)[ProtocolCommunication::___EXP_USER]).toString().toInt();
        farmer.login = myLogin;
        farmer.mail = ((*object)[ProtocolCommunication::___E_MAIL]).toString();
        farmer.registration_date = QDateTime::fromString(((*object)[ProtocolCommunication::___DATE_TIME]).toString());
        farmer.user_name = ((*object)[ProtocolCommunication::___NAME]).toString();

        emit onAnswerInformationAboutUser();
    }
    else
    {
        // информации нет
    }

}

void ClientGeneral::handlerPlantsUser(QJsonObject *object)
{
    plantsFarmer.clear();

    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        QJsonArray jArr = ((*object)[ProtocolCommunication::___ARRAY_DATA]).toArray();
        QJsonObject jObj;
        FarmerPlant* farmerPlant;

        for(int i = 0; i < jArr.size(); i++)
        {
            jObj = jArr[i].toObject();

            QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

            farmerPlant = new FarmerPlant(
                                            ((jObj)[ProtocolCommunication::___INST_ID]).toString().toInt(),
                                            myLogin,
                                            ((jObj)[ProtocolCommunication::___ID]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___STAGE_PLANT]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___TYPE_GROUND]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___STATUS_PLANT]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___NAME]).toString(),
                                            ProtocolCommunication::StringToByteArray(((jObj)[ProtocolCommunication::___IMAGE]).toString())
                                         );
            pathFiles[farmerPlant->avatar] = ProtocolCommunication::SaveBinaryFile(ProtocolCommunication::ByteArrayToString(farmerPlant->avatar),"avatarPlantuser", QString::number(farmerPlant->inst_id));
            sendGetMediaForFarmerPlantAll(QString::number(farmerPlant->inst_id));
            plantsFarmer[farmerPlant->inst_id] = *farmerPlant;
        }
        emit onAnswerPlantsUser();

        sendGetLogForUser();
        emitPlantsFarmer();

    }
    else
    {
        // нет информации о растениях пользователя
    }
}

void ClientGeneral::handlerNameIdFromGlossary(QJsonObject *object)
{
    //НЕ нужо
}

void ClientGeneral::handlerDescriptionFromGlossary(QJsonObject *object)
{
    //НЕ нужо
}

void ClientGeneral::handlerCareInfoFromGlossary(QJsonObject *object)
{
    //НЕ нужо
}

void ClientGeneral::handlerAvatarFromGlossary(QJsonObject *object)
{
    //НЕ нужо
}

void ClientGeneral::handlerAllDataFromGlossary(QJsonObject *object)
{
    plants.clear();

    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        QJsonArray jArr = ((*object)[ProtocolCommunication::___ARRAY_DATA]).toArray();
        QJsonObject jObj;
        Plant* plant;

        for(int i = 0; i < jArr.size(); i++)
        {
            jObj = jArr[i].toObject();

            plant = new Plant(
                                ((jObj)[ProtocolCommunication::___ID]).toString().toInt(),
                                ((jObj)[ProtocolCommunication::___NAME]).toString(),
                                ProtocolCommunication::StringToByteArray(((jObj)[ProtocolCommunication::___DATA]).toString()),
                                ProtocolCommunication::StringToByteArray(((jObj)[ProtocolCommunication::___DESCRIPTION]).toString()),
                                ProtocolCommunication::StringToByteArray(((jObj)[ProtocolCommunication::___IMAGE]).toString())
                             );
            pathFiles[plant->avatar] = ProtocolCommunication::SaveBinaryFile(ProtocolCommunication::ByteArrayToString(plant->avatar),"avatarPlan", QString::number(plant->id));
            pathFiles[plant->description_path] = ProtocolCommunication::SaveBinaryFile(ProtocolCommunication::ByteArrayToString(plant->description_path),"descriptionPlant", QString::number(plant->id));
            pathFiles[plant->info_path] = ProtocolCommunication::SaveBinaryFile(ProtocolCommunication::ByteArrayToString(plant->info_path),"infoPlant", QString::number(plant->id));

            plants[plant->id] = *plant;
            plantsChar[plant->name[0].toUpper()].push_back(*plant);
        }

        emit onAnswerAllDataFromGlossary();
    }
    else
    {
        // нет информации о растениях пользователя
    }
}

void ClientGeneral::handlerUserTask(QJsonObject *object)
{
    tasksFarmer.clear();

    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        QJsonArray jArr = ((*object)[ProtocolCommunication::___ARRAY_DATA]).toArray();
        QJsonObject jObj;
        FarmerTask* farmerTask;

        for(int i = 0; i < jArr.size(); i++)
        {
            jObj = jArr[i].toObject();

            farmerTask = new FarmerTask(
                                            ((jObj)[ProtocolCommunication::___ID]).toString().toInt(),
                                            myLogin,
                                            ((jObj)[ProtocolCommunication::___DESCRIPTION]).toString(),
                                            QDateTime::fromString(((jObj)[ProtocolCommunication::___DATE_TIME]).toString())
                                       );

            tasksFarmer[farmerTask->id] = *farmerTask;
        }

        emit onAnswerUserTask();
    }
    else
    {
        // нет информации о растениях пользователя
    }
}

void ClientGeneral::handlerMediaForFarmerPlantAll(QJsonObject *object)
{
    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        QJsonArray jArr = ((*object)[ProtocolCommunication::___ARRAY_DATA]).toArray();
        QJsonObject jObj;

        int inst_id = ((*object)[ProtocolCommunication::___INST_ID]).toString().toInt();

        plantsFarmer[inst_id].mediasPlant.clear();

        MediaPlant* mediaPlant;

        for(int i = 0; i < jArr.size(); i++)
        {
            jObj = jArr[i].toObject();

            mediaPlant = new MediaPlant(
                                            ((jObj)[ProtocolCommunication::___ID]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___INST_ID]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___DESCRIPTION]).toString(),
                                            ProtocolCommunication::StringToByteArray(((jObj)[ProtocolCommunication::___IMAGE]).toString()),
                                            QDateTime::fromString(((jObj)[ProtocolCommunication::___DATE_TIME]).toString())
                                       );
            pathFiles[mediaPlant->image] = ProtocolCommunication::SaveBinaryFile(ProtocolCommunication::ByteArrayToString(mediaPlant->image),"mediaPlant", QString::number(mediaPlant->id) +"_"+QString::number(mediaPlant->inst_id));
            plantsFarmer[inst_id].mediasPlant.push_back(*mediaPlant);
        }

        emit onAnswerMediaForFarmerPlantAll();
    }
    else
    {
        // нет информации о растениях пользователя
    }
}

void ClientGeneral::handlerMediaForFarmerPlantOne(QJsonObject *object)
{
    // НЕ нужо
}

void ClientGeneral::handlerLogForUser(QJsonObject *object)
{
    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {

        QList<int> keys = plantsFarmer.keys();

        for(int i = 0; i < keys.size(); i++)
        {
            plantsFarmer[keys[i]].logs.clear();
        }

        QJsonArray jArr = ((*object)[ProtocolCommunication::___ARRAY_DATA]).toArray();
        QJsonObject jObj;

        LogPlant* log;

        for(int i = 0; i < jArr.size(); i++)
        {
            jObj = jArr[i].toObject();

            log = new LogPlant(
                               ((jObj)[ProtocolCommunication::___ID]).toString().toInt(),
                               ((jObj)[ProtocolCommunication::___INST_ID]).toString().toInt(),
                               "",
                               ((jObj)[ProtocolCommunication::___TYPE_ACTION]).toString().toInt(),
                               QDateTime::fromString(((jObj)[ProtocolCommunication::___DATE_TIME]).toString())
                              );

            plantsFarmer[log->inst_id].logs.push_back(*log);
        }

        emit onAnswerLogForUser();
    }
    else
    {
        // нет информации о растениях пользователя
    }
}

void ClientGeneral::handlerLogForPlant(QJsonObject *object)
{
    // НЕ нужо
}

void ClientGeneral::handlerAchivementsUser(QJsonObject *object)
{
    // НЕ нужо
}

void ClientGeneral::handlerInfoAboutAchivement(QJsonObject *object)
{
    // НЕ нужо
}

void ClientGeneral::handlerAllDataAchivementsUser(QJsonObject *object)
{
    achivementFarmer.clear();

    QString resultStatus = ((*object)[ProtocolCommunication::___STATUS]).toString();

    if(resultStatus == ProtocolCommunication::___STS_DONE)
    {
        QJsonArray jArr = ((*object)[ProtocolCommunication::___ARRAY_DATA]).toArray();
        QJsonObject jObj;
        Achivement* achivement;

        for(int i = 0; i < jArr.size(); i++)
        {
            jObj = jArr[i].toObject();

            achivement = new Achivement (
                                            ((jObj)[ProtocolCommunication::___ID]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___NAME]).toString(),
                                            ((jObj)[ProtocolCommunication::___DESCRIPTION]).toString(),
                                            ((jObj)[ProtocolCommunication::___AIM]).toString().toInt(),
                                            ((jObj)[ProtocolCommunication::___PROGRESS]).toString().toInt(),
                                            ProtocolCommunication::StringToByteArray(((jObj)[ProtocolCommunication::___IMAGE]).toString())
                                        );

            pathFiles[achivement->image] = ProtocolCommunication::SaveBinaryFile(ProtocolCommunication::ByteArrayToString(achivement->image),"achivement", QString::number(achivement->id));
            achivementFarmer[achivement->id] = *achivement;
        }

        emit onAnswerAllDataAchivementsUser();
    }
    else
    {
        // нет информации о растениях пользователя
    }
}

void ClientGeneral::sendAuthorization(QString login, QString password)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_AUTHORIZATION)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(login)},
                                                {ProtocolCommunication::___PASSWORD, QJsonValue(password)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);

    myLogin = login;
}

void ClientGeneral::sendRegistration(QString login, QString password, QString email)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_AUTHORIZATION)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(login)},
                                                {ProtocolCommunication::___PASSWORD, QJsonValue(password)},
                                                {ProtocolCommunication::___E_MAIL, QJsonValue(email)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);

    myLogin = login;
}

void ClientGeneral::sendGetInformationAboutUser()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_INFO_ABOUT_USER)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(myLogin)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetPlantsUser()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_PLANTS_USER)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(myLogin)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendAddPlantForUser(QString stage, QString typeGround, QString idPlant, QString name, QString avatar)
{
    if(name=="") name=getNamePlant(idPlant.toInt());
    QByteArray bytes = ProtocolCommunication::LoadBinaryFile(avatar.remove(0,8));

    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_ADD_PLANT_FOR_USER)},
                                                {ProtocolCommunication::___STAGE_PLANT, QJsonValue(stage)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(myLogin)},
                                                {ProtocolCommunication::___TYPE_GROUND, QJsonValue(typeGround)},
                                                {ProtocolCommunication::___ID, QJsonValue(idPlant)},
                                                {ProtocolCommunication::___NAME, QJsonValue(name)},
                                                {ProtocolCommunication::___IMAGE, QJsonValue(ProtocolCommunication::ByteArrayToString(bytes))}
                                            });

    FarmerPlant pl(myLogin, idPlant.toInt(), stage.toInt(), typeGround.toInt(),1,name, bytes);
    plantsFarmer[-1]=pl;

    sendGetPlantsUser();

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetNameIdFromGlossary()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_NAME_ID_FROM_GLOSSARY)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetDescriptionFromGlossary(QString idPlant)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_DESCRIPTION_FROM_GLOSSARY)},
                                                {ProtocolCommunication::___ID, QJsonValue(idPlant)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetCareInfoFromGlossary(QString idPlant)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_CARE_INFO_FROM_GLOSSARY)},
                                                {ProtocolCommunication::___ID, QJsonValue(idPlant)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetAvatarFromGlossary(QString idPlant)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_AVATAR_FROM_GLOSSARY)},
                                                {ProtocolCommunication::___ID, QJsonValue(idPlant)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetAllDataFromGlossary()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_ALL_DATA_FROM_GLOSSARY)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetUserTask()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_USER_TASK)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(myLogin)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendAddUserTask(QString login, QString text, QString datetime)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_ADD_USER_TASK)},
                                                {ProtocolCommunication::___DESCRIPTION, QJsonValue(text)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(login)},
                                                {ProtocolCommunication::___DATE_TIME, QJsonValue(datetime)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetMediaForFarmerPlantAll(QString idPlant)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ALL)},
                                                {ProtocolCommunication::___ID, QJsonValue(idPlant)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetMediaForFarmerPlantOne(QString idMedia)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_MEDIA_FOR_PLANT_ONE)},
                                                {ProtocolCommunication::___ID, QJsonValue(idMedia)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendAddMediaForFarmerPlant(QString description, QString image, QString instID)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_ADD_MEDIA_FOR_PLANT)},
                                                {ProtocolCommunication::___DESCRIPTION, QJsonValue(description)},
                                                {ProtocolCommunication::___IMAGE, QJsonValue(image)},
                                                {ProtocolCommunication::___INST_ID, QJsonValue(instID)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetLogForUser()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_LOG_FOR_USER)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(myLogin)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetLogForPlant(QString idPlant)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_LOG_FOR_PLANT)},
                                                {ProtocolCommunication::___INST_ID, QJsonValue(idPlant)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendAddLog(QString login, QString idPlant, QString idAction, QString datetime)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_ADD_LOG)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(login)},
                                                {ProtocolCommunication::___INST_ID, QJsonValue(idPlant)},
                                                {ProtocolCommunication::___TYPE_ACTION, QJsonValue(idAction)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetAchivementsUser()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_ACHIVEMENTS_USER)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(myLogin)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetInfoAboutAchivement(QString id)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_INFO_ABOUT_ACHIVEMENT)},
                                                {ProtocolCommunication::___ID, QJsonValue(id)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::sendGetAllDataAchivementsUser()
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_GET_ALL_DATA_ACHIVEMENTS_USER)},
                                                {ProtocolCommunication::___LOGIN, QJsonValue(myLogin)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::setStatusPlant(QString instID, QString newValueStatus)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_SET_STATUS_PLANT)},
                                                {ProtocolCommunication::___STATUS_PLANT, QJsonValue(newValueStatus)},
                                                {ProtocolCommunication::___INST_ID, QJsonValue(instID)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::setStagePlant(QString instID, QString newValueStage)
{
    QJsonObject* jObj = new QJsonObject({
                                                {ProtocolCommunication::___COMMAND, QJsonValue(ProtocolCommunication::___CMD_SET_STATUS_PLANT)},
                                                {ProtocolCommunication::___STAGE_PLANT, QJsonValue(newValueStage)},
                                                {ProtocolCommunication::___INST_ID, QJsonValue(instID)}
                                            });

    ProtocolCommunication::SendTextMessage(ProtocolCommunication::jsonObjectToString(jObj), &socketServer);
}

void ClientGeneral::emitPlantsFarmer()
{
    foreach(FarmerPlant farmerPlant, plantsFarmer){
        emit onAddPlantFarmer(
                    farmerPlant.inst_id,
                    getNamePlant(farmerPlant.plant_id),
                    farmerPlant.plant_id,
                    farmerPlant.stage,
                    farmerPlant.created_date.toString(),
                    farmerPlant.type_id,
                    farmerPlant.status,
                    farmerPlant.name,
                    getPathForQML(pathFiles[farmerPlant.avatar])
                    );
    }
}

void ClientGeneral::loadGlossary()
{
    foreach(Plant plant, plants){
        emit onAddPlant(
                    plant.id,
                    plant.name,
                    getPathForQML(pathFiles[plant.description_path]),
                    getPathForQML(pathFiles[plant.info_path]),
                    getPathForQML(pathFiles[plant.avatar])
                    );
    }
}

void ClientGeneral::loadAllMedia()
{
    foreach(FarmerPlant plant, plantsFarmer){
        foreach(MediaPlant m , plant.mediasPlant)
        emit onAddPlantMedia(
                    m.id,
                    plant.inst_id,
                    m.description,

                    getPathForQML(pathFiles[m.image]),
                    m.dateTime.toString("dd.MM.yyyy hh:mm")
                    );
    }
    qDebug() <<"ClientGeneral::loadAllMedia";
}

QString ClientGeneral::getPathForQML(QString path)
{
    return "file:///"+path;
}

QString ClientGeneral::getNamePlant(int id_plant)
{
    return plants[id_plant].name;
}

QString ClientGeneral::getAvatarPlant(int id_plant)
{
    return getPathForQML(pathFiles[plants[id_plant].avatar]);
}

QString ClientGeneral::getDescriptPlant(int id_plant)
{
    return getPathForQML(pathFiles[plants[id_plant].info_path]);
}

QString ClientGeneral::getNamePlantFarmer(int id_plant)
{
    return plantsFarmer[id_plant].name;
}

QString ClientGeneral::getAvatarPlantFarmer(int id_plant)
{
    return getPathForQML(pathFiles[plantsFarmer[id_plant].avatar]);
}

int ClientGeneral::getTypeGrountPlantFarmer(int id_plant)
{
    return plantsFarmer[id_plant].type_id;
}

QString ClientGeneral::getCreateTimePlantFarmer(int id_plant)
{
    return plantsFarmer[id_plant].created_date.toString("dd.MM.yyyy hh:mm");
}

int ClientGeneral::getStagePlantFarmer(int id_plant)
{
    return plantsFarmer[id_plant].stage;
}

QString ClientGeneral::getMyName()
{
    return farmer.user_name;
}

QString ClientGeneral::getMyAvatar()
{
    return getPathForQML(pathFiles[farmer.avatar]);
}

QString ClientGeneral::getMyLogin()
{
    return farmer.login;
}

int ClientGeneral::getMyExp()
{
    return farmer.exp;
}

int ClientGeneral::getMyLvl()
{
    return qRound(log2(farmer.exp));
}

int ClientGeneral::getExpToNextLvl()
{
    return qRound(pow(2,getMyLvl()+1));
}

QString ClientGeneral::getMyBirthDate()
{
    return farmer.birth_date.toString("dd-MM-yyyy");
}

QString ClientGeneral::getMyCreateDate()
{
    return farmer.registration_date.toString();
}

int ClientGeneral::getCountCharPlants()
{
    return plantsChar.count();
}

QString ClientGeneral::getCharPlantsForIndex(int index)
{
    return plantsChar.keys()[index];
}

int ClientGeneral::getCountPlantsinChar(int index)
{
    return plantsChar[plantsChar.keys()[index]].count();
}

int ClientGeneral::getPlantsForIndexChar(QString c, int index)
{
    return plantsChar[c][index].id;
}

ClientGeneral::ClientGeneral(QObject *parent) : QObject(parent)
{
    connect(&socketServer,
            &QWebSocket::connected,
            this,
            &ClientGeneral::onConnected);

    connect(&socketServer,
            QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this,
            &ClientGeneral::onSslErrors);

    socketServer.open(URL_SERVER);
}

