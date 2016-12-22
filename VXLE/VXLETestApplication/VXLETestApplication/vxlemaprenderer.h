#ifndef VXLEMAPRENDERER_H
#define VXLEMAPRENDERER_H

#include <QQuickItem>
#include <QImage>
#include <QObject>
#include <QMutex>
#include <QQuickItem>
#include <QSGSimpleTextureNode>
#include <QSGSimpleRectNode>
#include <QSGNode>
#include <QSGTexture>
#include <QQuickWindow>

class VXLEMapRenderer : public QQuickItem
{
    Q_OBJECT

public:
    VXLEMapRenderer();
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

public slots:
    void loadImage(QString source);
    void receivedImage(QImage image);

private:
    QImage image_;
};


#endif // VXLEMAPRENDERER_H
