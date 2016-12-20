#include "vxlesrtmloader.h"

VXLESRTMLoader::VXLESRTMLoader(QObject *parent) : QObject(parent)
{

}

bool VXLESRTMLoader::loadSRTMData(QString folder)
{
    QFile *folderFile = new QFile(folder);
    if(!folderFile->exists()) {
        return false;
    }

    emit loadStarted();

    QList<SRTMPixmap> data;
    int northMin = 999999;
    int northMax = -999999;
    int southMin = 999999;
    int southMax = -999999;

    int defaultWidth = 1024;
    int defaultHeight = 1024;

    QDirIterator it(folder, QDirIterator::NoIteratorFlags);
    while(it.hasNext()) {
        emit loadedPercent(0);
        QString file = it.next();
        //(N[0-9]+E[0-9]+).*.jpg
        QRegExp rx = QRegExp("N([0-9]+)E([0-9]+).*.jpg");
        rx.indexIn(file);
        QStringList qsl = rx.capturedTexts();
        if(qsl.count() == 3) {
            if(qsl[0] != "") {
                int north = qsl[1].toInt();
                int south = qsl[2].toInt();
                if(north > 0 && south > 0) {
                    SRTMPixmap srtmPixmap;
                    srtmPixmap.N = north;
                    srtmPixmap.S = south;
                    srtmPixmap.pixmap = QPixmap(file);
                    data.append(srtmPixmap);


                    if(north < northMin ) {
                        northMin = north;
                    }

                    if(north > northMax) {
                        northMax = north;
                    }

                    if(south < southMin) {
                        southMin = south;
                    }

                    if(south > southMax) {
                        southMax = south;
                    }

                }
            }
        }

        emit loadedPercent(100);
    }

    emit loadedPercent(0);
    std::sort(data.begin(), data.end());
    emit loadedPercent(100);

    int deltaN = northMax - northMin;
    int deltaS = southMax - southMin;

    int totalIterations = deltaN * deltaS;

    emit loadedPercent(0);


    for(int n = northMin; n <= northMax; n++) {
        for(int s = southMin; s <= southMax; s++) {
             qDebug() << QString::number(s) << QString::number(n);
             QPixmap map = getPixmapForCoordinates(data, n, s, 1024, 1024, true);
           // emit loadedPercent(totalIterations);
        }
    }
    emit loadedPercent(100);
    emit loadDone();
    return true;
}


QPixmap VXLESRTMLoader::getPixmapForCoordinates(
        QList<SRTMPixmap> dataIterator,
        int n,
        int s,
        int defaultWidth,
        int defaultHeight,
        bool sorted
        ) {

    for(SRTMPixmap data : dataIterator) {
        if(data.N == n && data.S == s) {
            return data.pixmap;
        } else if (data.N > n && sorted)
        {
            QPixmap pixmap(defaultWidth, defaultHeight);
            return pixmap;
        }
    }

    QPixmap pixmap(defaultWidth, defa   ultHeight);
    return pixmap;
}


QPixmap VXLESRTMLoader::getResultPixMap()
{
    return resultPixMap_;
}

void VXLESRTMLoader::setResultPixMap(QPixmap resultPixMap)
{
    resultPixMap_ = resultPixMap;
    emit resultPixMapChanged();
}
