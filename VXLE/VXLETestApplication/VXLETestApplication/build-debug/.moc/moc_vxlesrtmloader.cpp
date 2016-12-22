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
struct qt_meta_stringdata_VXLESRTMLoaderWorker_t {
    QByteArrayData data[13];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VXLESRTMLoaderWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VXLESRTMLoaderWorker_t qt_meta_stringdata_VXLESRTMLoaderWorker = {
    {
QT_MOC_LITERAL(0, 0, 20), // "VXLESRTMLoaderWorker"
QT_MOC_LITERAL(1, 21, 11), // "loadStarted"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "loadedPercent"
QT_MOC_LITERAL(4, 48, 7), // "percent"
QT_MOC_LITERAL(5, 56, 13), // "statusMessage"
QT_MOC_LITERAL(6, 70, 8), // "loadDone"
QT_MOC_LITERAL(7, 79, 10), // "imageWidth"
QT_MOC_LITERAL(8, 90, 11), // "imageHeight"
QT_MOC_LITERAL(9, 102, 6), // "source"
QT_MOC_LITERAL(10, 109, 14), // "workerFinished"
QT_MOC_LITERAL(11, 124, 11), // "startWorker"
QT_MOC_LITERAL(12, 136, 21) // "checkForFileEmptiness"

    },
    "VXLESRTMLoaderWorker\0loadStarted\0\0"
    "loadedPercent\0percent\0statusMessage\0"
    "loadDone\0imageWidth\0imageHeight\0source\0"
    "workerFinished\0startWorker\0"
    "checkForFileEmptiness"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VXLESRTMLoaderWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    2,   45,    2, 0x06 /* Public */,
       6,    3,   50,    2, 0x06 /* Public */,
      10,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   58,    2, 0x0a /* Public */,
      12,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    7,    8,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VXLESRTMLoaderWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VXLESRTMLoaderWorker *_t = static_cast<VXLESRTMLoaderWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadStarted(); break;
        case 1: _t->loadedPercent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->loadDone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->workerFinished(); break;
        case 4: _t->startWorker(); break;
        case 5: _t->checkForFileEmptiness(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VXLESRTMLoaderWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoaderWorker::loadStarted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoaderWorker::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoaderWorker::loadedPercent)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoaderWorker::*_t)(int , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoaderWorker::loadDone)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoaderWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoaderWorker::workerFinished)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject VXLESRTMLoaderWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VXLESRTMLoaderWorker.data,
      qt_meta_data_VXLESRTMLoaderWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VXLESRTMLoaderWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VXLESRTMLoaderWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VXLESRTMLoaderWorker.stringdata0))
        return static_cast<void*>(const_cast< VXLESRTMLoaderWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int VXLESRTMLoaderWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VXLESRTMLoaderWorker::loadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void VXLESRTMLoaderWorker::loadedPercent(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VXLESRTMLoaderWorker::loadDone(int _t1, int _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VXLESRTMLoaderWorker::workerFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
struct qt_meta_stringdata_VXLESRTMLoader_t {
    QByteArrayData data[17];
    char stringdata0[193];
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
QT_MOC_LITERAL(5, 66, 13), // "loadedPercent"
QT_MOC_LITERAL(6, 80, 7), // "percent"
QT_MOC_LITERAL(7, 88, 13), // "statusMessage"
QT_MOC_LITERAL(8, 102, 8), // "loadDone"
QT_MOC_LITERAL(9, 111, 10), // "imageWidth"
QT_MOC_LITERAL(10, 122, 11), // "imageHeight"
QT_MOC_LITERAL(11, 134, 6), // "source"
QT_MOC_LITERAL(12, 141, 12), // "loadSRTMData"
QT_MOC_LITERAL(13, 154, 6), // "folder"
QT_MOC_LITERAL(14, 161, 9), // "resultMap"
QT_MOC_LITERAL(15, 171, 7), // "QImage*"
QT_MOC_LITERAL(16, 179, 13) // "tempImageFile"

    },
    "VXLESRTMLoader\0resultMapChanged\0\0"
    "tempImageFileChanged\0loadStarted\0"
    "loadedPercent\0percent\0statusMessage\0"
    "loadDone\0imageWidth\0imageHeight\0source\0"
    "loadSRTMData\0folder\0resultMap\0QImage*\0"
    "tempImageFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VXLESRTMLoader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    2,   47,    2, 0x06 /* Public */,
       8,    3,   52,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    1,   59,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,    9,   10,   11,

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
        case 3: _t->loadedPercent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->loadDone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: { bool _r = _t->loadSRTMData((*reinterpret_cast< QString(*)>(_a[1])));
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
            typedef void (VXLESRTMLoader::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::loadedPercent)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (VXLESRTMLoader::*_t)(int , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VXLESRTMLoader::loadDone)) {
                *result = 4;
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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
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
void VXLESRTMLoader::loadedPercent(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VXLESRTMLoader::loadDone(int _t1, int _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
