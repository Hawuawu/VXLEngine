#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QFile>
#include <QQmlContext>


#include "vxlemenucontroller.h"
#include "vxlemenuitem.h"
#include "vxletestapplicationsettings.h"
#include <vxlesrtmloader.h>
#include <vxlemaprenderer.h>

int main(int argc, char *argv[])
{

    qmlRegisterType<VXLEMenuController>("com.vxle.testapplication", 1, 0, "MenuController");
    qmlRegisterType<VXLEMenuItem>("com.vxle.testapplication", 1, 0, "MenuItem");
    qmlRegisterType<VXLETestApplicationSettings>("com.vxle.testapplication", 1, 0, "ApplicationSettings");
    qmlRegisterType<VXLESRTMLoader>("com.vxle.testapplication", 1, 0, "SRTMLoader");
    qmlRegisterType<VXLEMapRenderer>("com.vxle.testapplication", 1, 0, "SRTMMap");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationPath", "file:///"+qApp->applicationDirPath()+ "/");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
