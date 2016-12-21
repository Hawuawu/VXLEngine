/****************************************************************************
** Meta object code from reading C++ file 'vxlemenuitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vxlemenuitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vxlemenuitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VXLEMenuItem_t {
    QByteArrayData data[13];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VXLEMenuItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VXLEMenuItem_t qt_meta_stringdata_VXLEMenuItem = {
    {
QT_MOC_LITERAL(0, 0, 12), // "VXLEMenuItem"
QT_MOC_LITERAL(1, 13, 7), // "enabled"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "disabled"
QT_MOC_LITERAL(4, 31, 8), // "selected"
QT_MOC_LITERAL(5, 40, 10), // "deselected"
QT_MOC_LITERAL(6, 51, 6), // "enable"
QT_MOC_LITERAL(7, 58, 7), // "disable"
QT_MOC_LITERAL(8, 66, 6), // "select"
QT_MOC_LITERAL(9, 73, 8), // "deselect"
QT_MOC_LITERAL(10, 82, 6), // "button"
QT_MOC_LITERAL(11, 89, 10), // "background"
QT_MOC_LITERAL(12, 100, 4) // "icon"

    },
    "VXLEMenuItem\0enabled\0\0disabled\0selected\0"
    "deselected\0enable\0disable\0select\0"
    "deselect\0button\0background\0icon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VXLEMenuItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       5,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x02 /* Public */,
       7,    0,   59,    2, 0x02 /* Public */,
       8,    0,   60,    2, 0x02 /* Public */,
       9,    0,   61,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       1, QMetaType::Bool, 0x00095103,
       4, QMetaType::Bool, 0x00095103,
      10, QMetaType::QObjectStar, 0x00095103,
      11, QMetaType::QObjectStar, 0x00095103,
      12, QMetaType::QObjectStar, 0x00095103,

       0        // eod
};

void VXLEMenuItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VXLEMenuItem *_t = static_cast<VXLEMenuItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enabled(); break;
        case 1: _t->disabled(); break;
        case 2: _t->selected(); break;
        case 3: _t->deselected(); break;
        case 4: _t->enable(); break;
        case 5: _t->disable(); break;
        case 6: _t->select(); break;
        case 7: _t->deselect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VXLEMenuItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLEMenuItem::enabled)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VXLEMenuItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLEMenuItem::disabled)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VXLEMenuItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLEMenuItem::selected)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VXLEMenuItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLEMenuItem::deselected)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        VXLEMenuItem *_t = static_cast<VXLEMenuItem *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->getEnabled(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->getSelected(); break;
        case 2: *reinterpret_cast< QObject**>(_v) = _t->getButton(); break;
        case 3: *reinterpret_cast< QObject**>(_v) = _t->getBackground(); break;
        case 4: *reinterpret_cast< QObject**>(_v) = _t->getIcon(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        VXLEMenuItem *_t = static_cast<VXLEMenuItem *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setSelected(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setButton(*reinterpret_cast< QObject**>(_v)); break;
        case 3: _t->setBackground(*reinterpret_cast< QObject**>(_v)); break;
        case 4: _t->setIcon(*reinterpret_cast< QObject**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject VXLEMenuItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VXLEMenuItem.data,
      qt_meta_data_VXLEMenuItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VXLEMenuItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VXLEMenuItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VXLEMenuItem.stringdata0))
        return static_cast<void*>(const_cast< VXLEMenuItem*>(this));
    return QObject::qt_metacast(_clname);
}

int VXLEMenuItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void VXLEMenuItem::enabled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void VXLEMenuItem::disabled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void VXLEMenuItem::selected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void VXLEMenuItem::deselected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
