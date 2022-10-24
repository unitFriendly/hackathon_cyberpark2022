#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H
#define svalue(a) query.value(a).toString()
#define ivalue(a) query.value(a).toInt()
#define tostr(a) QString::number(a)

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "instruments.h"
#include "farmer.h"
#include "plant.h"
#include "farmerplant.h"
#include "achivement.h"
#include "farmertask.h"

class ServerController
{
private:
    QSqlDatabase db;
    static ServerController* instance;
    bool startServer();
public:
    ServerController();
    ///Паерн синглтон
    static ServerController * getInstance();
    int getLastId(QString table, QString column, QString where="");


    //----------------------ФЕРМЕРЫ--------------------------------------------

    ///Ауентификация пользователя: 0 - удачно, 1 - нет пользователя, 2 - неправильный пароль
    int confirmAuthorization(QString login, QString passhash);
    ///Получить профиль по id
    Farmer* getUser(QString login);

    ///Регистрация пользователя: 0 - всё ок, 1 - логин занят, 2 - почта занята
    int registrationUser(Farmer farmer);

    //----------------------ГЛОССАРИЙ--------------------------------------------

    ///Получиь растение из глоссария по id
    Plant* getPlant(int id);
    ///Получить ВСЕ растения из глоссария
    QVector<Plant> getAllPlant();

    //-----------------------ЗАМЕТКИ РАСТЕНИЙ-------------------------------------------

    ///Получить заметки фермера для растения по id медиа
    MediaPlant* getMediaPlant(int id_media);
    ///Получить ВСЕ заметки фермера для id растения
    QVector<MediaPlant> getAllMediaPlant(int id);

    ///Добавить заметку
    int addMediaPlant(MediaPlant mediaPlant, QString login);

    ///Удалить заметку
    int removeMediaPlant(int id_mediaPlant);

    //-----------------------ЛОГИ РАСТЕНИЙ-------------------------------------------

    ///Получить название лога по id лога
    QString getActionType(int id_action);
    ///Получить лог по id лога и id цветка
    LogPlant *getLogPlant(int id_log, int id_plant);
    ///Получить ВСЕ логи по id цветка
    QVector<LogPlant> getAllLogPlant(int id_plant);
    ///Получить ВСЕ логи пользователя по всем цветкам
    QVector<LogPlant> getAllLogUser(QString login);

    ///Добавить лог
    int addLogPlant(LogPlant logPlant, QString login);

    ///Удалить лог
    int removeLogPlant(int id_lo, int id_plant);

    //-----------------------РАСТЕНИЯ ФЕРМЕРА-------------------------------------------

    ///Получить тип грунта
    QString getTypePlant(int id);

    ///Получить растения фермера по id растения
    FarmerPlant* getFarmerPlant(int id);
    ///Получить ВСЕ растения фермера
    QVector<FarmerPlant> getAlFarmerPlant(QString login_Farmer);

    ///Изменить этап роста растения
    int setStagePlant(int inst_id, int new_value_stage, QString login);

    ///Изменить статус растения
    int setStatusPlant(int inst_id, int new_value_status, QString login);

    ///Добавить растение фермера
    int addFarmerPlant(FarmerPlant farmerPlant);

    ///Обновить информацию об растение фермера
    int updateFarmerPlant(FarmerPlant farmerPlant);

    ///Удалить растение фермера
    int removeFarmerPlant(int id_plant);

    //-----------------------ЗАДАЧИ ФЕРМЕРА-------------------------------------------

    ///Получиь задачу фермера по id задачи и логину
    FarmerTask* getFarmerTask(int id_task, QString login);
    ///Получиь ВСЕ задачи фермера по логину
    QVector<FarmerTask> getAllFarmerTask(QString login);

    ///Добавить задачу
    int addFarmerTask(FarmerTask task);

    ///Удалить задачу
    int removeFarmerTask(int id_task, QString login);

    //---------------------------АЧИВКИ---------------------------------------

    ///Получить ачивку и прогресс для пользователя по id ачивки
    Achivement* getAchivement(int id_ach, QString login_Farmer);
    ///Получить прогресс ВСЕХ ачивок для пользователя
    QVector<Achivement> getAllAchivements(QString login_Farmer);

    ///Добавить ачивку
    int addAchivement(Achivement achivement);

    ///Выполнить ачивку
    int completeAchivement(int id_ach, QString login);

    ///Событие выполнение какого либо действия и выполнения ачивка
    int checkAchivement(QString login, actionAchivement action);

};

#endif // SERVERCONTROLLER_H
