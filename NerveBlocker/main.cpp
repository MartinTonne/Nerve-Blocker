#include "gamehandler.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QtSql>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("NerveBlocker");
    app.setOrganizationDomain("mycompany.com");
    app.setApplicationName("NerveBlocker");
    QQmlApplicationEngine engine;
    GameHandler gamehandler;
    engine.rootContext()->setContextProperty("gamehandler", &gamehandler);
    qmlRegisterUncreatableType<Organ>("UllApp", 1, 0, "Organ", "Organ is uncreatable");
    qmlRegisterUncreatableType<Mode>("UllApp", 1, 0, "Mode", "Mode is uncreatable");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    database db;
    db.getDB();


    return app.exec();
}
