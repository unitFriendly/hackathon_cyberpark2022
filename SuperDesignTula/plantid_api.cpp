#include "plantid_api.h"

QString JsonObjectToString(QJsonObject *object)
{
    static QJsonDocument jDoc;
    jDoc.setObject(*object);
    return jDoc.toJson();
}

QJsonObject StringToJsonObject(QString str)
{
    static QJsonDocument jDoc;
    jDoc = QJsonDocument::fromJson(str.toUtf8());
    return jDoc.object();
}

PlantID_API::PlantID_API(QObject *parent) : QObject(parent)
{
    URL = QUrl(QStringLiteral("https://api.plant.id/v2/identify"));
}

void PlantID_API::onResult(QNetworkReply *reply_)
{
    qDebug() << "PlantID_API::onResult";

    if(reply_->error())
    {
        qDebug() << "ERROR";
        qDebug() << reply->errorString();

        // ошибка в запросе
    }
    else
    {
        QJsonObject jObj = StringToJsonObject(QString(reply->readAll()));

        QJsonArray jArr = jObj["images"].toArray();



        jArr = jObj["suggestions"].toArray();
        QJsonObject plantAI = jArr[0].toObject();

        plant_name = plantAI["plant_name"].toString();
        probability = QString::number(plantAI["probability"].toDouble() * 100);

        jObj = plantAI["plant_details"].toObject();
        url =  jObj["url"].toString();

        plantAI = jObj["wiki_description"].toObject();
        value = plantAI["value"].toString();

        plantAI = jObj["wiki_image"].toObject();
        QString urlPic = plantAI["value"].toString();

        disconnect(manager, &QNetworkAccessManager::finished, this, &PlantID_API::onResult);

        //createRequestDownloadPicture(QUrl(urlPic));

        emit dataReceived(plant_name, probability, url, value);
    }
}

void PlantID_API::createRequest(QByteArray image)
{
    QJsonObject jObj;
    jObj.insert("api_key", QJsonValue(API_KEY));

    QJsonArray jArrImage;
    jArrImage.push_back(QJsonValue(QLatin1String(image.toBase64())));

    jObj.insert("images", jArrImage);

    jObj.insert("plant_language", QJsonValue(QLatin1String("en")));

    QJsonArray jArrPlantDetails ;
    jArrPlantDetails.push_back(QJsonValue(QLatin1String("url")));
    jArrPlantDetails.push_back(QJsonValue(QLatin1String("wiki_description")));

    jObj.insert("plant_details", jArrPlantDetails);

    QJsonDocument jDoc(jObj);

    QByteArray data = jDoc.toJson(QJsonDocument::Indented);

    manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished, this, &PlantID_API::onResult);

    QNetworkRequest request(URL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    reply = manager->post(request, data);
}

void PlantID_API::createRequestFromPath(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    file.close();
    qDebug() << "PlantID_API::createRequestFromPath";
    createRequest(array);
}

void SaveBinaryFile(QByteArray binary, QString fullPath)
{
    QFile file(fullPath);
    file.open(QIODevice::WriteOnly);
    file.write(binary);
    file.close();
}

QString GetTypeFromPathFile(QString path)
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

QString GetNameFromPathFile(QString path)
{
    int indexDot = path.lastIndexOf('.');
    int indexStartName = path.lastIndexOf('/') + 1;

    int lenType = indexDot - indexStartName;
    QString result(lenType, ' ');

    for(int i = 0; i < lenType; i++)
    {
        result[i] = path[indexStartName + i];
    }

    return result;
}

void PlantID_API::onResultDownloadPicture(QNetworkReply *reply)
{
    QString fullPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    fullPath += "/";
    fullPath += GetNameFromPathFile(reply->url().toString());
    fullPath += ".";
    fullPath += GetTypeFromPathFile(reply->url().toString());

    SaveBinaryFile(reply->readAll(), fullPath);

    //emit dataReceived(plant_name, probability, url, value);
}

void PlantID_API::createRequestDownloadPicture(QUrl urlPic)
{
    connect(manager, &QNetworkAccessManager::finished, this, &PlantID_API::onResultDownloadPicture);

    QNetworkRequest request(urlPic);

    reply = manager->get(request);
}
