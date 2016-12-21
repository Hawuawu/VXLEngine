#ifndef VXLESRTMLOADER_H
#define VXLESRTMLOADER_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QFile>
#include <QDirIterator>
#include <QDebug>

#define LOCATION_MATRIX_NORTH_INDEX 0
#define LOCATION_MATRIX_SOUTH_INDEX 1
#define LOCATION_MATRIX_EAST_INDEX 2
#define LOCATION_MATRIX_WEST_INDEX 3

#define DEFAULT_HEIGHT 1201
#define DEFAULT_WIDTH 1201

using namespace std;

struct SRTMPixmap {
    QPixmap pixmap;
    QString originalFile = "";

    int N = -1;
    int S = -1;
    int E = -1;
    int W = -1;

};


class VXLESRTMLoader : public QObject
{
    Q_OBJECT
public:
    explicit VXLESRTMLoader(QObject *parent = 0);

    Q_INVOKABLE bool loadSRTMData(QString folder);

    Q_PROPERTY(QImage *resultMap READ getResultMap WRITE setResultMap NOTIFY resultMapChanged)
    QImage* getResultMap();
    void setResultMap(QImage*);

    Q_PROPERTY(QString tempImageFile READ getTempImageFile WRITE setTempImageFile NOTIFY tempImageFileChanged)
    QString getTempImageFile();
    void setTempImageFile(QString);

signals:
    void resultMapChanged();
    void tempImageFileChanged();

    void loadStarted();
    void loadedImage(int x, int y, QImage image);
    void loadedPercent(int percent);
    void loadDone();

public slots:
private:
    QImage *resultImage_ = 0;
    QString tempImageFile_ = "temp.png";
};

#endif // VXLESRTMLOADER_H
