#ifndef PLANTID_API_H
#define PLANTID_API_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QStandardPaths>

class PlantID_API : public QObject
{
    Q_OBJECT

private:
    const QString API_KEY = "9railhnFfOTaOEBJHIFne63btqszoZSulkFDTEQq2GqTX3ZtGv";
    QUrl URL;

    QNetworkAccessManager *manager;
    QNetworkRequest *request;
    QNetworkReply *reply;

    QString plant_name;
    QString probability;
    QString url;
    QString value;
    QString path;

public:
    explicit PlantID_API(QObject *parent = nullptr);

public slots:
    void onResult(QNetworkReply *reply);
    void createRequest(QByteArray image);
    void createRequestFromPath(QString path);

    void onResultDownloadPicture(QNetworkReply *reply);
    void createRequestDownloadPicture(QUrl urlPic);

signals:
    void dataReceived(QString, QString, QString, QString);
};

#endif // PLANTID_API_H
