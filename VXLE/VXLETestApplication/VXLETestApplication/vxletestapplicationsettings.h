#ifndef VXLETESTAPPLICATIONSETTINGS_H
#define VXLETESTAPPLICATIONSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QGuiApplication>

class VXLETestApplicationSettings : public QObject
{
    Q_OBJECT
public:
    explicit VXLETestApplicationSettings(QObject *parent = 0);

    Q_PROPERTY(QString settingsFile READ getSettingsFile WRITE setSettingsFile)
    QString getSettingsFile();
    void setSettingsFile(QString);

    Q_PROPERTY(QString lastPath READ getLastPath WRITE setLastPath NOTIFY lastPathChanged)
    QString getLastPath();
    void setLastPath(QString);

signals:
    void lastPathChanged();

public slots:
private:
    QString lastPath_;
    QString settingsFile_;
};

#endif // VXLETESTAPPLICATIONSETTINGS_H
