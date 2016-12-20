#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QFile>


#include "vxlemenucontroller.h"
#include "vxlemenuitem.h"
#include "vxletestapplicationsettings.h"
#include <vxlesrtmloader.h>

int main(int argc, char *argv[])
{

    qmlRegisterType<VXLEMenuController>("com.vxle.testapplication", 1, 0, "MenuController");
    qmlRegisterType<VXLEMenuItem>("com.vxle.testapplication", 1, 0, "MenuItem");
    qmlRegisterType<VXLETestApplicationSettings>("com.vxle.testapplication", 1, 0, "ApplicationSettings");
    qmlRegisterType<VXLESRTMLoader>("com.vxle.testapplication", 1, 0, "SRTMLoader");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
