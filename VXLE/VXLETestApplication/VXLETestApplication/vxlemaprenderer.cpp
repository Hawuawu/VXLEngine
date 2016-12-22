#include "vxlemaprenderer.h"

VXLEMapRenderer::VXLEMapRenderer()
{

}

QSGNode *VXLEMapRenderer::updatePaintNode(QSGNode *node, UpdatePaintNodeData *data)
{
    Q_UNUSED(data)

    QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(node);
    if (!n) {
        n = new QSGSimpleTextureNode();
    }
   // image_->fill(Qt::red);
    qDebug() << "Image size" << image_.byteCount();

    n->setRect(x(), y(), image_.width(), image_.height());
    QSGTexture *texture = this->window()->createTextureFromImage(image_);
    n->setTexture(texture);
    n->setOwnsTexture(true);
    n->markDirty(QSGNode::DirtyGeometry);

    return n;
}


void VXLEMapRenderer::loadImage(QString source)
{
    QPixmap map;
    map.load(source);
    image_ = map.toImage();
     setFlag(ItemHasContents, true);
     update();
}

void VXLEMapRenderer::receivedImage(QImage image)
{
    image_ = image;
    setFlag(ItemHasContents, true);
    update();
}
