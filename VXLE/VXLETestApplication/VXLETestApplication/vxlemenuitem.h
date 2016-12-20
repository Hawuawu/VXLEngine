#ifndef VXLEMENUITEM_H
#define VXLEMENUITEM_H

#include <QObject>

class VXLEMenuItem : public QObject
{
    Q_OBJECT

public:
    explicit VXLEMenuItem(QObject *parent = 0);

    Q_INVOKABLE void enable();
    Q_INVOKABLE void disable();

    Q_INVOKABLE void select();
    Q_INVOKABLE void deselect();

    Q_PROPERTY(bool enabled READ getEnabled WRITE setEnabled)
    bool getEnabled();
    void setEnabled(bool);

    Q_PROPERTY(bool selected READ getSelected WRITE setSelected)
    bool getSelected();
    void setSelected(bool);

    Q_PROPERTY(QObject* button READ getButton WRITE setButton)
    QObject* getButton();
    void setButton(QObject*);

    Q_PROPERTY(QObject* background READ getBackground WRITE setBackground)
    QObject* getBackground();
    void setBackground(QObject*);

    Q_PROPERTY(QObject* icon READ getIcon WRITE setIcon)
    QObject* getIcon();
    void setIcon(QObject*);

signals:
    void enabled();
    void disabled();
    void selected();
    void deselected();

public slots:

private:
    bool enabled_ = true;
    bool selected_ = false;

    QObject* background_;
    QObject* icon_;
    QObject* button_;
};

#endif // VXLEMENUITEM_H
