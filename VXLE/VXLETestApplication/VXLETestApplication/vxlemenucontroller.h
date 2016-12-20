#ifndef VXLEMENUCONTROLLER_H
#define VXLEMENUCONTROLLER_H

#include <QObject>
#include <QList>
#include <QDebug>

#include <vxlemenuitem.h>

class VXLEMenuController : public QObject
{
    Q_OBJECT
public:
    explicit VXLEMenuController(QObject *parent = 0);

    Q_INVOKABLE void registerMenuItem(QObject*);

signals:

public slots:
    void itemSelected(QObject*);

private:
    VXLEMenuItem *activeItem = 0;
    QList<VXLEMenuItem*> items;


};

#endif // VXLEMENUCONTROLLER_H
