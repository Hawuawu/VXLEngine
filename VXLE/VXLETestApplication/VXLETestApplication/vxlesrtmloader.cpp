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

    QList<SRTMPixmap> northWestData;
    QList<SRTMPixmap> northEastData;
    QList<SRTMPixmap> southWestData;
    QList<SRTMPixmap> southEastData;

    std::vector<std::vector<int>> locationMatrix(4, std::vector<int>(360));

    QDirIterator it(folder, QDirIterator::NoIteratorFlags);
    while(it.hasNext()) {
        emit loadedPercent(0);
        QString file = it.next();
        //(N[0-9]+E[0-9]+).*.jpg

        QRegExp neRx = QRegExp("N([0-9]+)E([0-9]+).*.jpg");
        QRegExp nwRx = QRegExp("N([0-9]+)W([0-9]+).*.jpg");
        QRegExp seRx = QRegExp("S([0-9]+)E([0-9]+).*.jpg");
        QRegExp swRx = QRegExp("S([0-9]+)W([0-9]+).*.jpg");

        neRx.indexIn(file);
        QStringList neQsl = neRx.capturedTexts();

        nwRx.indexIn(file);
        QStringList nwQsl = nwRx.capturedTexts();

        seRx.indexIn(file);
        QStringList seQsl = seRx.capturedTexts();

        swRx.indexIn(file);
        QStringList swQsl = swRx.capturedTexts();

        if(neQsl.count() == 3) {
            if(neQsl[0] != "") {
                int north = neQsl[1].toInt();
                int east = neQsl[2].toInt();

                locationMatrix[LOCATION_MATRIX_NORTH_INDEX][north] = 1;
                locationMatrix[LOCATION_MATRIX_EAST_INDEX][east] = 1;

                SRTMPixmap srtmPixmap;
                srtmPixmap.N = north;
                srtmPixmap.E = east;
                srtmPixmap.pixmap = QPixmap(file);
                srtmPixmap.originalFile = file;

                northEastData.append(srtmPixmap);

                int i = northEastData.length() - 1;
                while(i > 0 && northEastData[i].N > northEastData[i-1].N) {
                    SRTMPixmap temp = northEastData[i-1];
                    northEastData.replace(i - 1, northEastData[i]);
                    northEastData.replace(i, temp);
                    i --;
                }

                while(i > 0 && northEastData[i].E < northEastData[i-1].E) {
                    SRTMPixmap temp = northEastData[i-1];
                    northEastData.replace(i - 1, northEastData[i]);
                    northEastData.replace(i, temp);
                    i --;
                }

            }
        }

        if(nwQsl.count() == 3) {
            if(nwQsl[0] != "") {
                int north = nwQsl[1].toInt();
                int west = nwQsl[2].toInt();


                locationMatrix[LOCATION_MATRIX_NORTH_INDEX][north] = 1;
                locationMatrix[LOCATION_MATRIX_WEST_INDEX][west] = 1;

                SRTMPixmap srtmPixmap;
                srtmPixmap.N = north;
                srtmPixmap.W = west;
                srtmPixmap.pixmap = QPixmap(file);
                srtmPixmap.originalFile = file;

                northWestData.append(srtmPixmap);

                int i = northWestData.length() - 1;
                while(i > 0 && northWestData[i].N > northWestData[i-1].N) {
                    SRTMPixmap temp = northWestData[i-1];
                    northWestData.replace(i - 1, northWestData[i]);
                    northWestData.replace(i, temp);
                    i --;
                }

                while(i > 0 && northWestData[i].W < northWestData[i-1].W) {
                    SRTMPixmap temp = northWestData[i-1];
                    northWestData.replace(i - 1, northWestData[i]);
                    northWestData.replace(i, temp);
                    i --;
                }
            }
        }

        if(seQsl.count() == 3) {
            if(seQsl[0] != "") {
                int south = seQsl[1].toInt();
                int east = seQsl[2].toInt();

                locationMatrix[LOCATION_MATRIX_SOUTH_INDEX][south] = 1;
                locationMatrix[LOCATION_MATRIX_EAST_INDEX][east] = 1;

                SRTMPixmap srtmPixmap;
                srtmPixmap.S = south;
                srtmPixmap.E = east;
                srtmPixmap.pixmap = QPixmap(file);
                srtmPixmap.originalFile = file;

                southEastData.append(srtmPixmap);


                int i = southEastData.length() - 1;
                while(i > 0 && southEastData[i].S < southEastData[i-1].S) {
                    SRTMPixmap temp = southEastData[i-1];
                    southEastData.replace(i - 1, southEastData[i]);
                    southEastData.replace(i, temp);
                    i --;
                }

                while(i > 0 && southEastData[i].E < southEastData[i-1].E) {
                    SRTMPixmap temp = southEastData[i-1];
                    southEastData.replace(i - 1, southEastData[i]);
                    southEastData.replace(i, temp);
                    i --;
                }
            }
        }

        if(swQsl.count() == 3) {
            if(swQsl[0] != "") {
                int south = swQsl[1].toInt();
                int west = swQsl[2].toInt();

                locationMatrix[LOCATION_MATRIX_SOUTH_INDEX][south] = 1;
                locationMatrix[LOCATION_MATRIX_WEST_INDEX][west] = 1;

                SRTMPixmap srtmPixmap;
                srtmPixmap.S = south;
                srtmPixmap.W = west;
                srtmPixmap.pixmap = QPixmap(file);
                srtmPixmap.originalFile = file;

                southWestData.append(srtmPixmap);

                int i = southWestData.length() - 1;
                while(i > 0 && southWestData[i].S < southWestData[i-1].S) {
                    SRTMPixmap temp = southWestData[i-1];
                    southWestData.replace(i - 1, southWestData[i]);
                    southWestData.replace(i, temp);
                    i --;
                }

                while(i > 0 && southWestData[i].W < southWestData[i-1].W) {
                    SRTMPixmap temp = southWestData[i-1];
                    southWestData.replace(i - 1, southWestData[i]);
                    southWestData.replace(i, temp);
                    i --;
                }
            }
        }


        emit loadedPercent(100);
    }

    int widthCount = 0;
    int heightCount = 0;

    for(int i = 0; i < 360; i++) {
        heightCount += locationMatrix[LOCATION_MATRIX_NORTH_INDEX][i];
        heightCount += locationMatrix[LOCATION_MATRIX_SOUTH_INDEX][i];
        widthCount += locationMatrix[LOCATION_MATRIX_EAST_INDEX][i];
        widthCount += locationMatrix[LOCATION_MATRIX_WEST_INDEX][i];
    }

    emit loadedPercent(0);

    int expectedWidth = widthCount * DEFAULT_WIDTH;
    int expectedHeight = heightCount * DEFAULT_HEIGHT;


    int aspectRatio = expectedHeight / expectedWidth;

    int supportedWidth = 10000;
    int supportedHeight = 10000;

    float zoom = 1;

    if(aspectRatio <= 1) {
        if(supportedWidth < expectedWidth) zoom = (float) supportedWidth / (float) expectedWidth;
    } else {
        if(supportedHeight < expectedHeight) zoom = (float) supportedHeight / (float) expectedHeight;
    }

    QImage resultImage(expectedWidth * zoom , expectedHeight * zoom , QImage::Format_Grayscale8);
    QPainter p(&resultImage);
    qDebug() << expectedWidth * zoom  << " x " << expectedHeight * zoom << " - " << DEFAULT_WIDTH * zoom;

    int xDelta = 0;
    int yDelta = 0;

    qDebug() << "-------- NW --------";
    for (SRTMPixmap map : northWestData) {
        qDebug() << map.N << "-" << map.W;

    }

    if(northEastData.size() > 0) {
        int lastN = northEastData[0].N;
        int lastE = northEastData[0].E;

        int xOriginDelta = xDelta;

        qDebug() << "-------- NE --------";
        for (SRTMPixmap map : northEastData) {
            qDebug() << map.N << "-" << map.E;

            if(lastN == map.N && lastE != map.E) {
                xDelta ++;
            } else if(lastN != map.N) {
                yDelta ++;
                xDelta = xOriginDelta;
            }

             p.drawPixmap(
                         xDelta * DEFAULT_WIDTH * zoom - 1,
                         yDelta * DEFAULT_HEIGHT * zoom - 1,
                         map.pixmap.scaled(DEFAULT_WIDTH * zoom, DEFAULT_HEIGHT * zoom, Qt::IgnoreAspectRatio)
                         );

            emit loadedImage(xDelta * DEFAULT_WIDTH, yDelta * DEFAULT_HEIGHT, map.pixmap.toImage());
            lastN = map.N;
            lastE = map.E;
        }
    }

    qDebug() << "-------- SW --------";
    for (SRTMPixmap map : southWestData) {
        qDebug() << map.S << "-" << map.W;
    }

    qDebug() << "-------- SE --------";
    for (SRTMPixmap map : southEastData) {
        qDebug() << map.S << "-" << map.E;
    }

    QImage* temp = resultImage_;
    resultImage_ = &resultImage;

    if(resultImage_->width() > 0 && resultImage_->height() > 0)
    {
        resultImage_->save(tempImageFile_);
    }

    emit loadedPercent(100);
    emit loadDone();

    if(temp != 0) {
   //     delete temp;
    }

    return true;
}

QImage* VXLESRTMLoader::getResultMap()
{
    return resultImage_;
}

void VXLESRTMLoader::setResultMap(QImage* resultImage)
{
    resultImage_ = resultImage;
    emit resultMapChanged();
}

QString VXLESRTMLoader::getTempImageFile()
{
    return tempImageFile_;
}

void VXLESRTMLoader::setTempImageFile(QString tempImageFile)
{
    tempImageFile_ = tempImageFile;
    emit tempImageFileChanged();
}
