#include "vxlemenuitem.h"

VXLEMenuItem::VXLEMenuItem(QObject *parent) : QObject(parent)
{

}

void VXLEMenuItem::enable()
{
    enabled_ = true;
    emit enabled();
}

void VXLEMenuItem::disable()
{
    enabled_ = false;
    emit disabled();
}


void VXLEMenuItem::select()
{
    selected_ = true;
    emit selected();
}

void VXLEMenuItem::deselect()
{
    selected_ = false;
    emit deselected();
}

bool VXLEMenuItem::getEnabled()
{
    return enabled_;
}

void VXLEMenuItem::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

bool VXLEMenuItem::getSelected()
{
    return selected_;
}

void VXLEMenuItem::setSelected(bool selected)
{
    selected_ = selected;
}

QObject* VXLEMenuItem::getBackground()
{
    return background_;
}

void VXLEMenuItem::setBackground(QObject* background)
{
    background_ = background;
}

QObject* VXLEMenuItem::getIcon()
{
    return icon_;
}

void VXLEMenuItem::setIcon(QObject* icon)
{
    icon_ = icon;
}

QObject* VXLEMenuItem::getButton()
{
    return button_;
}

void VXLEMenuItem::setButton(QObject* button)
{
    button_ = button;
}
