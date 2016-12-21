/****************************************************************************
** Meta object code from reading C++ file 'vxlesrtmloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vxlesrtmloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vxlesrtmloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VXLESRTMLoader_t {
    QByteArrayData data[17];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VXLESRTMLoader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VXLESRTMLoader_t qt_meta_stringdata_VXLESRTMLoader = {
    {
QT_MOC_LITERAL(0, 0, 14), // "VXLESRTMLoader"
QT_MOC_LITERAL(1, 15, 16), // "resultMapChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 20), // "tempImageFileChanged"
QT_MOC_LITERAL(4, 54, 11), // "loadStarted"
QT_MOC_LITERAL(5, 66, 11), // "loadedImage"
QT_MOC_LITERAL(6, 78, 1), // "x"
QT_MOC_LITERAL(7, 80, 1), // "y"
QT_MOC_LITERAL(8, 82, 5), // "image"
QT_MOC_LITERAL(9, 88, 13), // "loadedPercent"
QT_MOC_LITERAL(10, 102, 7), // "percent"
QT_MOC_LITERAL(11, 110, 8), // "loadDone"
QT_MOC_LITERAL(12, 119, 12), // "loadSRTMData"
QT_MOC_LITERAL(13, 132, 6), // "folder"
QT_MOC_LITERAL(14, 139, 9), // "resultMap"
QT_MOC_LITERAL(15, 149, 7), // "QImage*"
QT_MOC_LITERAL(16, 157, 13) // "tempImageFile"

    },
    "VXLESRTMLoader\0resultMapChanged\0\0"
    "tempImageFileChanged\0loadStarted\0"
    "loadedImage\0x\0y\0image\0loadedPercent\0"
    "percent\0loadDone\0loadSRTMData\0folder\0"
    "resultMap\0QImage*\0tempImageFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VXLESRTMLoader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       2,   66, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    3,   52,    2, 0x06 /* Public */,
       9,    1,   59,    2, 0x06 /* Public */,
      11,    0,   62,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    1,   63,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QImage,    6,    7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString,   13,

 // properties: name, type, flags
      14, 0x80000000 | 15, 0x0049510b,
      16, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void VXLESRTMLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VXLESRTMLoader *_t = static_cast<VXLESRTMLoader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultMapChanged(); break;
        case 1: _t->tempImageFileChanged(); break;
        case 2: _t->loadStarted(); break;
        case 3: _t->loadedImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3]))); break;
        case 4: _t->loadedPercent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->loadDone(); break;
        case 6: { bool _r = _t->loadSRTMData((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VXLESRTMLoader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::resultMapChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::tempImageFileChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::loadStarted)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoader::*_t)(int , int , QImage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::loadedImage)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoader::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::loadedPercent)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::loadDone)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        VXLESRTMLoader *_t = static_cast<VXLESRTMLoader *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QImage**>(_v) = _t->getResultMap(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getTempImageFile(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        VXLESRTMLoader *_t = static_cast<VXLESRTMLoader *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setResultMap(*reinterpret_cast< QImage**>(_v)); break;
        case 1: _t->setTempImageFile(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject VXLESRTMLoader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VXLESRTMLoader.data,
      qt_meta_data_VXLESRTMLoader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VXLESRTMLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VXLESRTMLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VXLESRTMLoader.stringdata0))
        return static_cast<void*>(const_cast< VXLESRTMLoader*>(this));
    return QObject::qt_metacast(_clname);
}

int VXLESRTMLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void VXLESRTMLoader::resultMapChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void VXLESRTMLoader::tempImageFileChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void VXLESRTMLoader::loadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void VXLESRTMLoader::loadedImage(int _t1, int _t2, QImage _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VXLESRTMLoader::loadedPercent(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VXLESRTMLoader::loadDone()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
