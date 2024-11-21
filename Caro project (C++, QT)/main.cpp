#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include"carocontroller.h"
#include"QQmlContext"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CaroController c;
    c.setMatrix();
    engine.rootContext()->setContextProperty("Caro",&c);
    //Caro.extend();


    //qDebug()<<"caro:"<<c.getCaro()[1][1];

    const QUrl url(QStringLiteral("qrc:/Assignment_06_ex_HIEUTH12/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
