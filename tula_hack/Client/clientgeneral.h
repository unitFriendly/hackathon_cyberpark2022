#ifndef CLIENTGENERAL_H
#define CLIENTGENERAL_H

#include <QObject>
#include <QFile>
#include <QSslKey>
#include <QWebSocket>
#include <QJsonArray>
#include <QMap>
#include <qmath.h>

#include "../protocolcommunication.h"
#include "../../SuperServer/farmer.h"
#include "../../SuperServer/farmerplant.h"
#include "../../SuperServer/plant.h"
#include "../../SuperServer/farmertask.h"
#include "../../SuperServer/achivement.h"

class ClientGeneral : public QObject
{
    Q_OBJECT
public:
    explicit ClientGeneral(QObject *parent = nullptr);




private:
    const QUrl URL_SERVER = QUrl(QStringLiteral("ws://195.133.197.105:1234"));

    QWebSocket socketServer;

    Farmer farmer;
    QMap<int, FarmerPlant> plantsFarmer;
    QMap<int, Plant> plants;
    QMap<QString, QVector<Plant>> plantsChar;
    QMap<int, FarmerTask> tasksFarmer;
    QMap<int, Achivement> achivementFarmer;
    QMap<QByteArray, QString> pathFiles;

    bool isAuthorization = false;
    QString myLogin;

    void onConnected();
    void onTextMessageReceived(QString message);
    void onSslErrors(const QList<QSslError> &errors);

    void processingEventFromServer(QJsonObject* object);

    void handlerAuthorization(QJsonObject* object);
    void handlerRegistration(QJsonObject* object);

    void handlerInformationAboutUser(QJsonObject* object);

    void handlerPlantsUser(QJsonObject* object);

    void handlerNameIdFromGlossary(QJsonObject* object);
    void handlerDescriptionFromGlossary(QJsonObject* object);
    void handlerCareInfoFromGlossary(QJsonObject* object);
    void handlerAvatarFromGlossary(QJsonObject* object);
    void handlerAllDataFromGlossary(QJsonObject* object);

    void handlerUserTask(QJsonObject* object);

    void handlerMediaForFarmerPlantAll(QJsonObject* object);
    void handlerMediaForFarmerPlantOne(QJsonObject* object);

    void handlerLogForUser(QJsonObject* object);
    void handlerLogForPlant(QJsonObject* object);

    void handlerAchivementsUser(QJsonObject* object);
    void handlerInfoAboutAchivement(QJsonObject* object);
    void handlerAllDataAchivementsUser(QJsonObject* object);
public slots:


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на авторизацию
    void sendAuthorization(QString login, QString password);

    /// Отправка запроса на регистрацию
    void sendRegistration(QString login, QString password, QString email);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение информации о пользователи (из таблицы farmer)
    void sendGetInformationAboutUser();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение информации о растениях пользователя (из таблицы farmer_plant)
    void sendGetPlantsUser();

    /// Добавление нового растения к пользователю
    void sendAddPlantForUser(QString stage, QString typeGround, QString idPlant, QString name, QString avatar);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение информации из глоссария о всех растениях (имя и id)
    void sendGetNameIdFromGlossary();

    /// Отправка запроса на получение информации (статьи) о конкретном растении
    void sendGetDescriptionFromGlossary(QString idPlant);

    /// Отправка запроса на получение инструкции по уходу о конкретном растении
    void sendGetCareInfoFromGlossary(QString idPlant);

    /// Отправка запроса на получение аватара растения из глоссария
    void sendGetAvatarFromGlossary(QString idPlant);

    /// Отправка запроса на получении всей информации из глоссария
    void sendGetAllDataFromGlossary();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получения пользовательских задач
    void sendGetUserTask();

    /// Добавление пользовательской задачи
    void sendAddUserTask(QString login, QString text, QString datetime);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение всего медиа контента для растения
    void sendGetMediaForFarmerPlantAll(QString idPlant);

    /// Отправка запроса на получение конкретного медиа контента для конкретного растения
    void sendGetMediaForFarmerPlantOne(QString idMedia);

    /// Добавление нового медиа для конкретного растения
    void sendAddMediaForFarmerPlant(QString description, QString image, QString instID);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение всех логов для пользователя
    void sendGetLogForUser();

    /// Отправка запроса на получение логов для конкретного растения пользователя
    void sendGetLogForPlant(QString idPlant);

    /// Добавление новго лога пользователя по растению
    void sendAddLog(QString login, QString idPlant, QString idAction, QString datetime);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Отправка запроса на получение ачивок конкретного пользователя
    void sendGetAchivementsUser();

    /// Отправка запроса на получение информации об ачивки
    void sendGetInfoAboutAchivement(QString id);

    /// Отправка запроса на получение всех ачивок конкретного пользователя
    void sendGetAllDataAchivementsUser();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Изменение статуса растения
    void setStatusPlant(QString instID, QString newValueStatus);

    /// Изменение фазы роста растения
    void setStagePlant(QString instID, QString newValueStage);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    void emitPlantsFarmer();
    void loadGlossary();
    void loadAllMedia();

    QString getPathForQML(QString path);
    QString getNamePlant(int id_plant);
    QString getAvatarPlant(int id_plant);
    QString getDescriptPlant(int id_plant);

    QString getNamePlantFarmer(int id_plant);
    QString getAvatarPlantFarmer(int id_plant);
    int getTypeGrountPlantFarmer(int id_plant);
    QString getCreateTimePlantFarmer(int id_plant);
    int getStagePlantFarmer(int id_plant);

    QString getMyName();
    QString getMyAvatar();
    QString getMyLogin();
    int getMyExp();
    int getMyLvl();
    int getExpToNextLvl();
    QString getMyBirthDate();
    QString getMyCreateDate();

    int getCountCharPlants();
    QString getCharPlantsForIndex(int index);
    int getCountPlantsinChar(int index);
    int getPlantsForIndexChar(QString c, int index);


signals:
    void onAnswerAuthorization(bool result);
    void onAnswerRegistration(bool result);

    void onAnswerInformationAboutUser();

    void onAnswerPlantsUser();

    //void onAnswerNameIdFromGlossary();
    //void onAnswerDescriptionFromGlossary();
    //void onAnswerCareInfoFromGlossary();
    //void onAnswerAvatarFromGlossary();
    void onAnswerAllDataFromGlossary();

    void onAnswerUserTask();

    void onAnswerMediaForFarmerPlantAll();
    //void onAnswerMediaForFarmerPlantOne();

    void onAnswerLogForUser();
    //void onAnswerLogForPlant();

    //void onAnswerAchivementsUser();
    //void onAnswerInfoAboutAchivement();
    void onAnswerAllDataAchivementsUser();


    void onAddPlantFarmer(int id, QString namePlant, int plant_id, int stage, QString createdDate, int tipe_id, int status, QString name, QString pathAvatar);
    void onAddPlant(int id, QString name, QString pathDescription, QString pathInfo, QString pathAvatar);
    void onAddPlantMedia(int id, int inst_id, QString descrip, QString pathImage, QString dateTime);
};

#endif // CLIENTGENERAL_H
