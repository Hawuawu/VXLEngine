#include "vxletestapplicationsettings.h"

VXLETestApplicationSettings::VXLETestApplicationSettings(QObject *parent) : QObject(parent)
{

}

QString VXLETestApplicationSettings::getSettingsFile()
{
    return settingsFile_;
}

void VXLETestApplicationSettings::setSettingsFile(QString settingsFile)
{
    settingsFile_ = settingsFile;
    QString fullPath = QGuiApplication::applicationDirPath() + "/" + settingsFile;

    QFile *sf = new QFile(fullPath);
    qDebug() << sf->exists();
    if(!sf->exists()) {
        QSettings *settings = new QSettings(fullPath, QSettings::IniFormat);
        settings->setValue("lastPath", "");
        settings->sync();
    }

    QSettings *settings = new QSettings(fullPath, QSettings::IniFormat);
    lastPath_ = settings->value("lastPath").toString();

}

QString VXLETestApplicationSettings::getLastPath()
{
    return lastPath_;
}

void VXLETestApplicationSettings::setLastPath(QString lastPath)
{
    lastPath_ = lastPath;
    QString fullPath = QGuiApplication::applicationDirPath() + "/" + settingsFile_;
    QSettings *settings = new QSettings(fullPath, QSettings::IniFormat);
    settings->setValue("lastPath", lastPath);
    settings->sync();
    emit lastPathChanged();
}
