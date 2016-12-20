#ifndef VXLESRTMLOADER_H
#define VXLESRTMLOADER_H

#include <QObject>
#include <QPixmap>
#include <QFile>
#include <QDirIterator>
#include <QDebug>

struct SRTMPixmap {
    QPixmap pixmap;
    int N = 0;
    int S = 0;

    bool operator < (const SRTMPixmap& str) const
    {
           return (N <= str.N && S < str.S);
    }
};


class VXLESRTMLoader : public QObject
{
    Q_OBJECT
public:
    explicit VXLESRTMLoader(QObject *parent = 0);

    Q_INVOKABLE bool loadSRTMData(QString folder);

    Q_PROPERTY(QPixmap resultPixMap READ getResultPixMap WRITE setResultPixMap NOTIFY resultPixMapChanged)
    QPixmap getResultPixMap();
    void setResultPixMap(QPixmap);

    QPixmap getPixmapForCoordinates(QList<SRTMPixmap> dataIterator, int n, int s, int defaultWidth, int defaultHeight, bool sorted = false);

signals:
    void resultPixMapChanged();

    void loadStarted();
    void loadedPercent(int percent);
    void loadDone();

public slots:
private:
    QPixmap resultPixMap_;
};

#endif // VXLESRTMLOADER_H
