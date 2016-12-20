#include "vxlemenucontroller.h"

VXLEMenuController::VXLEMenuController(QObject *parent) : QObject(parent)
{

}

void VXLEMenuController::registerMenuItem(QObject* object)
{
    VXLEMenuItem *casted = qobject_cast<VXLEMenuItem *>(object);
    items.append(casted);
}

void VXLEMenuController::itemSelected(QObject* object)
{
   VXLEMenuItem *casted = qobject_cast<VXLEMenuItem *>(object);
    qDebug() << casted->getEnabled();
   if(casted->getEnabled()) {
       if(activeItem) {
          activeItem->deselect();
       }

       activeItem = casted;
       casted->select();
   }
}
