#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dice.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //create objects
    dice dice_ob;

    //expose c++
    engine.rootContext()->setContextProperty("Dice", &dice_ob);

    //load qml
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
