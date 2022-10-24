#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "dataleft.h"
#include <QQmlContext>
#include <../tula_hack/Client/clientgeneral.h>
#include "plantid_api.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    DateLeft dataleft;

    ClientGeneral client;
    PlantID_API planAPI;

    engine.rootContext()->setContextProperty("client", &client);
    engine.rootContext()->setContextProperty("dateLeft", &dataleft);
    engine.rootContext()->setContextProperty("planAPI", &planAPI);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
