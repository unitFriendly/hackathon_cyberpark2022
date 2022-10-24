#include "servercontroller.h"

ServerController* ServerController::instance = nullptr;

ServerController::ServerController()
{
    startServer();
}

bool ServerController::startServer()
{
    QVector<QString> paths({
                               "C:/Users/Tihon/Desktop/sqlitestudio-3.3.3/SQLiteStudio/SuperDataBase",
                               "C:/Users/Rota5/Documents/cyberpark2022/SuperDataBase",
                               "C:/Users/Administrator/Desktop/SuperDataBase",
                               "C:/Users/test/Desktop/tula_hack/git/cyberpark2022/SuperDataBase", "C:\\Users\\rota\\Documents\\GitHub\\cyberpark2022\\SuperDataBase"
                           });

    db = QSqlDatabase::addDatabase("QSQLITE");

    foreach(QString p, paths){
        if(QFile::exists(p)){
            db.setDatabaseName(p);
        }
    }


    if(db.open()){
        return true;
    } else {
        return false;
    }
}

ServerController *ServerController::getInstance()
{
    if(!instance)
        instance = new ServerController();
    return instance;
}

int ServerController::getLastId(QString table, QString column, QString where)
{
    auto str = QString("SELECT %0 FROM %1 %3 ORDER BY %0 DESC LIMIT 1").arg(column).arg(table).arg(where);
    QSqlQuery query(str);
    query.first();
    return ivalue(0);
}

int ServerController::confirmAuthorization(QString login, QString passhash)
{
    auto str = QString("SELECT login, password FROM farmer where login = '%0';").arg(login.toLower());
    QSqlQuery query(str);

    if(!query.first()){
        qDebug() << QString("login '%0': not exist").arg(login.toLower());
        return 1;
    }
    else{
        QString true_hash_pass = svalue(1);
        if(true_hash_pass == passhash){
            // add user to adffklhaddgvklds
            qDebug() << QString("login '%0': successful authorization").arg(login.toLower());
            return 0;
        }
        else{
            // poshol
            qDebug() << QString("login '%0': wrong password").arg(login.toLower());
            return 2;
        }
    }
}

Farmer *ServerController::getUser(QString login)
{
    auto str = QString("SELECT mail, password, user_name, avatar, birth_date, registration_date, carm, exp "
"FROM farmer WHERE login = '%0';").arg(login);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    Farmer* user= new Farmer(login,svalue(0), svalue(1), svalue(2), query.value(3).toByteArray(), Instruments::getDate(svalue(4)), Instruments::getDateTime(svalue(5)), ivalue(6), ivalue(7));
    return user;
}

int ServerController::registrationUser(Farmer farmer)
{
    auto str = QString("SELECT login FROM farmer where login = '%0';").arg(farmer.login.toLower());
    QSqlQuery query(str);

    if(query.first()){
        qDebug() << QString("login '%0': exist").arg(farmer.login.toLower());
        return 1;
    }

    str = QString("SELECT mail FROM farmer where mail = '%0';").arg(farmer.mail.toLower());
    query = QSqlQuery(str);

    if(query.first()){
        qDebug() << QString("mail '%0': exist").arg(farmer.login.toLower());
        return 2;
    }

    str = QString("INSERT INTO farmer (login,password,mail,user_name,avatar,birth_date)"
                  " VALUES ('%0','%1','%2','%3','%4','%5');")
            .arg(farmer.login)
            .arg(farmer.password)
            .arg(farmer.mail)
            .arg(farmer.user_name)
            .arg(QString(farmer.avatar))
            .arg(farmer.birth_date.toString());

    query = QSqlQuery(str);
    query.exec();

    str = QString("SELECT id, aim FROM achivements;").arg(farmer.mail.toLower());
    query = QSqlQuery(str);
    while(query.next())
    {
        int id_ach=ivalue(0);
        int aim=ivalue(1);

        str = QString("INSERT INTO user_achivements (id_achivement,login,status)"
                      " VALUES ('%0','%1','%2');")
                .arg(id_ach)
                .arg(farmer.login)
                .arg(aim);
        query = QSqlQuery(str);
        query.exec();
    }



    return 0;
}

Plant *ServerController::getPlant(int id)
{
    auto str = QString("SELECT name, info_path, description_path, avatar FROM plant WHERE id = %0;").arg(id);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    Plant* plant= new Plant(id, svalue(0), query.value(1).toByteArray(),query.value(2).toByteArray(),query.value(3).toByteArray() );
    return plant;
}

QVector<Plant> ServerController::getAllPlant()
{
    auto str = QString("SELECT id FROM plant;");
    QSqlQuery query(str);

    QVector<Plant> plants;

    while(query.next())
    {
        int plant_id = ivalue(0);
        Plant* plant=getPlant(plant_id);
        plants.append(*plant);
    }

    return plants;
}

QString ServerController::getTypePlant(int id)
{
    auto str = QString("SELECT name FROM type_plant WHERE id = %0;").arg(id);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    return svalue(0);
}

MediaPlant *ServerController::getMediaPlant(int id_media)
{
    auto str = QString("SELECT inst_id, description, image, datetime FROM media_plant WHERE id = %0;").arg(id_media);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    MediaPlant* media= new MediaPlant(id_media, ivalue(0), svalue(1),  query.value(2).toByteArray(), Instruments::getDateTime(svalue(3)));
    return media;
}

QVector<MediaPlant> ServerController::getAllMediaPlant(int id)
{
    auto str = QString("SELECT id FROM media_plant WHERE inst_id=%0;").arg(id);
    QSqlQuery query(str);

    QVector<MediaPlant> mediasPlant;

    while(query.next())
    {
        int plant_id = ivalue(0);
        MediaPlant* mediaPlant=getMediaPlant(plant_id);
        mediasPlant.append(*mediaPlant);
    }

    return mediasPlant;
}

int ServerController::addMediaPlant(MediaPlant mediaPlant, QString login)
{
    auto str = QString("INSERT INTO  media_plant (inst_id, description, image)"
                  " VALUES ('%0','%1','%2');")
            .arg(mediaPlant.inst_id)
            .arg(mediaPlant.description)
            .arg(QString(mediaPlant.image));

    QSqlQuery query = QSqlQuery(str);
    //query.exec();

    checkAchivement(login,actionAchivement::addMedia);

    return 0;
}

int ServerController::removeMediaPlant(int id_mediaPlant)
{
    auto str = QString("DELETE FROM media_plant WHERE id = %0;")
            .arg(id_mediaPlant);

    QSqlQuery query = QSqlQuery(str);
    query.exec();

    return 0;
}

QString ServerController::getActionType(int id_action)
{
    auto str = QString("SELECT name FROM action_type WHERE id = %0;").arg(id_action);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    return svalue(0);
}

LogPlant* ServerController::getLogPlant(int id_log, int id_plant)
{
    auto str = QString("SELECT id_action, date FROM log WHERE id = %0 AND inst_id = %1;").arg(id_log).arg(id_plant);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;

    QString action=getActionType(ivalue(0));
    LogPlant* log= new LogPlant(id_log, id_plant, action,ivalue(0),  Instruments::getDateTime(svalue(1)));
    return log;
}

QVector<LogPlant> ServerController::getAllLogPlant(int id_plant)
{
    auto str = QString("SELECT id FROM log WHERE inst_id=%0;").arg(id_plant);
    QSqlQuery query(str);

    QVector<LogPlant> logs;

    while(query.next())
    {
        int log_id = ivalue(0);
        LogPlant* log=getLogPlant(log_id, id_plant);
        logs.append(*log);
    }

    return logs;
}

QVector<LogPlant> ServerController::getAllLogUser(QString login)
{
    auto str = QString("SELECT l.id, l.inst_id FROM farmer_plant f "
                        "JOIN log l ON f.inst_id=l.inst_id WHERE f.login = '%0';").arg(login);
    QSqlQuery query(str);

    QVector<LogPlant> logs;

    while(query.next())
    {
        int log_id = ivalue(0);
        int inst_id = ivalue(1);
        LogPlant* log=getLogPlant(log_id, inst_id);
        logs.append(*log);
    }

    return logs;
}

int ServerController::addLogPlant(LogPlant logPlant, QString login)
{
    int newId=getLastId("log","id", QString("WHERE inst_id = '%0'").arg(logPlant.inst_id))+1;

    auto str = QString("INSERT INTO  log (id, inst_id, id_action)"
                  " VALUES ('%0', %1, %2);")
            .arg(newId)
            .arg(logPlant.inst_id)
            .arg(logPlant.action_id);

    QSqlQuery query(str);
    query.exec();

    checkAchivement(login,actionAchivement::addLog);

    return 0;
}

int ServerController::removeLogPlant(int id_log, int id_plant)
{
    auto str = QString("DELETE FROM log WHERE id = %0 AND inst_id = %1;")
            .arg(id_log)
            .arg(id_plant);

    QSqlQuery query = QSqlQuery(str);
    query.exec();

    return 0;
}

FarmerPlant *ServerController::getFarmerPlant(int id)
{
    auto str = QString("SELECT login, plant_id, stage, created_date, type_id, status, name, avatar FROM farmer_plant WHERE inst_id = %0;").arg(id);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    QString type=getTypePlant(ivalue(4));
    FarmerPlant* farmerPlant= new FarmerPlant(id, svalue(0), ivalue(1), ivalue(2), Instruments::getDateTime(svalue(3)), type,ivalue(5), svalue(6), query.value(7).toByteArray() );
    farmerPlant->mediasPlant=getAllMediaPlant(id);
    farmerPlant->logs=getAllLogPlant(id);

    return farmerPlant;
}

QVector<FarmerPlant> ServerController::getAlFarmerPlant(QString login_Famer)
{
    auto str = QString("SELECT inst_id FROM farmer_plant WHERE login = '%0';").arg(login_Famer);
    QSqlQuery query(str);

    QVector<FarmerPlant> farmerPlants;

    while(query.next())
    {
        int farmerPlant_id = ivalue(0);
        FarmerPlant* farmerPlant=getFarmerPlant(farmerPlant_id);
        farmerPlants.append(*farmerPlant);
    }

    return farmerPlants;
}

int ServerController::setStagePlant(int inst_id, int new_value_stage, QString login)
{
    auto str = QString("UPDATE farmer_plant "
                            "SET stage = %0 "
                            "WHERE inst_id = %1;")
            .arg(new_value_stage)
            .arg(inst_id);

    QSqlQuery query(str);
    query.exec();

    checkAchivement(login, actionAchivement::upStage);

    return 0;
}

int ServerController::setStatusPlant(int inst_id, int new_value_status, QString login)
{
    auto str = QString("UPDATE farmer_plant "
                            "SET stage = %0 "
                            "status inst_id = %1;")
            .arg(new_value_status)
            .arg(inst_id);

    QSqlQuery query(str);
    query.exec();

    checkAchivement(login, actionAchivement::upStatus);

    return 0;
}

int ServerController::addFarmerPlant(FarmerPlant farmerPlant)
{
    auto str = QString("INSERT INTO  farmer_plant (login, plant_id, stage, type_id, status, name, avatar)"
                  " VALUES ('%0', %1, %2, %3, %4, '%5', ?);")
            .arg(farmerPlant.login)
            .arg(farmerPlant.plant_id)
            .arg(farmerPlant.stage)
            .arg(farmerPlant.type_id)
            .arg(farmerPlant.status)
            .arg(farmerPlant.name);

    QSqlQuery query;
    query.prepare(str);
    query.addBindValue(farmerPlant.avatar);
    query.exec();

    checkAchivement(farmerPlant.login,actionAchivement::addPlant);

    return 0;
}

int ServerController::updateFarmerPlant(FarmerPlant farmerPlant)
{
    auto str = QString("UPDATE farmer_plant "
                            "SET stage = %0, type_id = %1, status = %2, name = '%3', avatar = '%4' "
                            "WHERE inst_id = %5;")
            .arg(farmerPlant.stage)
            .arg(farmerPlant.type_id)
            .arg(farmerPlant.status)
            .arg(farmerPlant.name)
            .arg(QString(farmerPlant.avatar))
            .arg(farmerPlant.inst_id);

    QSqlQuery query(str);
    query.exec();

    //checkAchivement(farmerPlant.login,actionAchivement::addPlant);

    return 0;
}

int ServerController::removeFarmerPlant(int id_plant)
{
    auto str = QString("DELETE FROM farmer_plant WHERE inst_id = %0;")
            .arg(id_plant);

    QSqlQuery query = QSqlQuery(str);
    query.exec();

    str = QString("DELETE FROM log WHERE inst_id = %0;")
            .arg(id_plant);

    query = QSqlQuery(str);
    query.exec();

    str = QString("DELETE FROM media_plant WHERE inst_id = %0;")
            .arg(id_plant);

    query = QSqlQuery(str);
    query.exec();

    return 0;
}

FarmerTask *ServerController::getFarmerTask(int id_task, QString login)
{
    auto str = QString("SELECT text, date FROM user_task WHERE id = %0 AND login = '%1';").arg(id_task).arg(login);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    FarmerTask* farmerTask= new FarmerTask(id_task,login, svalue(0), Instruments::getDateTime(svalue(1)));

    return farmerTask;
}

QVector<FarmerTask> ServerController::getAllFarmerTask(QString login)
{
    auto str = QString("SELECT id FROM user_task WHERE login = '%0';").arg(login);
    QSqlQuery query(str);

    QVector<FarmerTask> farmerTasks;

    while(query.next())
    {
        int farmerTask_id = ivalue(0);
        FarmerTask* farmerTask=getFarmerTask(farmerTask_id, login);
        farmerTasks.append(*farmerTask);
    }

    return farmerTasks;
}

int ServerController::addFarmerTask(FarmerTask task)
{
    int newId=getLastId("user_task","id", QString("WHERE login = '%0'").arg(task.login))+1;

    auto str = QString("INSERT INTO  user_task (id, login, text, date)"
                  " VALUES ('%0','%1','%2', '%3');")
            .arg(newId)
            .arg(task.login)
            .arg(task.text)
            .arg(task.dateTime.toString());

    QSqlQuery query = QSqlQuery(str);
    query.exec();

    checkAchivement(task.login,actionAchivement::addFarmerTask);

    return 0;
}

int ServerController::removeFarmerTask(int id_task, QString login)
{
    auto str = QString("DELETE FROM user_task WHERE id = %0 AND login = '%1';")
            .arg(id_task)
            .arg(login);

    QSqlQuery query = QSqlQuery(str);
    query.exec();

    checkAchivement(login,actionAchivement::removeFarmerTask);

    return 0;
}

Achivement *ServerController::getAchivement(int id_ach, QString login_Farmer)
{
    auto str = QString("SELECT name, info, aim, status, image FROM user_achivements "
                            "JOIN achivements ON id_achivement=id "
                            "WHERE login = '%0' AND id = %1;")
            .arg(login_Farmer).arg(id_ach);
    QSqlQuery query(str);
    if(!query.first())
        return nullptr;
    Achivement* ach= new Achivement(id_ach, svalue(0), svalue(1), ivalue(2), ivalue(3), query.value(4).toByteArray());
    return ach;
}

QVector<Achivement> ServerController::getAllAchivements(QString login_Farmer)
{
    auto str = QString("SELECT id_achivement FROM user_achivements WHERE login = '%0';").arg(login_Farmer);
    QSqlQuery query(str);

    QVector<Achivement> achivements;

    while(query.next())
    {
        int achivement_id = ivalue(0);
        Achivement* achivement=getAchivement(achivement_id, login_Farmer);
        achivements.append(*achivement);
    }

    return achivements;
}

int ServerController::addAchivement(Achivement achivement)
{
    auto str = QString("INSERT INTO achivements (info, aim, name, image) VALUES ('%0', %1, '%2', '%3');")
            .arg(achivement.info)
            .arg(achivement.aim)
            .arg(achivement.name)
            .arg(QString(achivement.image));
    QSqlQuery query(str);
    //query.exec();

    int id_ach=getLastId("achivements","id");

    str = QString("SELECT login FROM farmer;");
    query = QSqlQuery(str);
    while(query.next())
    {
        QString login=svalue(0);

        str = QString("INSERT INTO user_achivements (id_achivement,login,status)"
                      " VALUES ('%0','%1','%2');")
                .arg(id_ach)
                .arg(login)
                .arg(achivement.aim);
        QSqlQuery queryAc = QSqlQuery(str);
        queryAc.exec();
    }

    return 0;
}

int ServerController::completeAchivement(int id_ach, QString login)
{
    auto str = QString("UPDATE user_achivements SET status = %2 WHERE id_achivement = %0 AND login = '%1';")
            .arg(id_ach)
            .arg(login)
            .arg(0);

    QSqlQuery queryAc(str);
    queryAc.exec();
}

int ServerController::checkAchivement(QString login, actionAchivement action)
{
    QVector<int> ids = Achivement::mapAchivement->value(action);

    foreach(int id, ids){
        auto str = QString("UPDATE user_achivements SET status = status - 1 WHERE id_achivement = %0 AND login = '%1';")
                .arg(id)
                .arg(login);

        QSqlQuery queryAc = QSqlQuery(str);
        //queryAc.exec();
    }

    return 0;
}


