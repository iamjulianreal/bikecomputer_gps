/****************************************************************************
** Meta object code from reading C++ file 'GpxLogger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../GpxLogger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GpxLogger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GpxLogger_t {
    QByteArrayData data[22];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GpxLogger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GpxLogger_t qt_meta_stringdata_GpxLogger = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GpxLogger"
QT_MOC_LITERAL(1, 10, 16), // "recordingChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "pointCountChanged"
QT_MOC_LITERAL(4, 46, 20), // "lastSavedPathChanged"
QT_MOC_LITERAL(5, 67, 10), // "saveFailed"
QT_MOC_LITERAL(6, 78, 7), // "message"
QT_MOC_LITERAL(7, 86, 8), // "addPoint"
QT_MOC_LITERAL(8, 95, 8), // "latitude"
QT_MOC_LITERAL(9, 104, 9), // "longitude"
QT_MOC_LITERAL(10, 114, 8), // "speedKmh"
QT_MOC_LITERAL(11, 123, 9), // "courseDeg"
QT_MOC_LITERAL(12, 133, 12), // "isoTimestamp"
QT_MOC_LITERAL(13, 146, 19), // "setCurrentHeartRate"
QT_MOC_LITERAL(14, 166, 9), // "heartRate"
QT_MOC_LITERAL(15, 176, 5), // "start"
QT_MOC_LITERAL(16, 182, 4), // "stop"
QT_MOC_LITERAL(17, 187, 5), // "clear"
QT_MOC_LITERAL(18, 193, 4), // "save"
QT_MOC_LITERAL(19, 198, 9), // "recording"
QT_MOC_LITERAL(20, 208, 10), // "pointCount"
QT_MOC_LITERAL(21, 219, 13) // "lastSavedPath"

    },
    "GpxLogger\0recordingChanged\0\0"
    "pointCountChanged\0lastSavedPathChanged\0"
    "saveFailed\0message\0addPoint\0latitude\0"
    "longitude\0speedKmh\0courseDeg\0isoTimestamp\0"
    "setCurrentHeartRate\0heartRate\0start\0"
    "stop\0clear\0save\0recording\0pointCount\0"
    "lastSavedPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GpxLogger[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       3,   88, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    5,   70,    2, 0x0a /* Public */,
      13,    1,   81,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      15,    0,   84,    2, 0x02 /* Public */,
      16,    0,   85,    2, 0x02 /* Public */,
      17,    0,   86,    2, 0x02 /* Public */,
      18,    0,   87,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,

 // properties: name, type, flags
      19, QMetaType::Bool, 0x00495001,
      20, QMetaType::Int, 0x00495001,
      21, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void GpxLogger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GpxLogger *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->recordingChanged(); break;
        case 1: _t->pointCountChanged(); break;
        case 2: _t->lastSavedPathChanged(); break;
        case 3: _t->saveFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->addPoint((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 5: _t->setCurrentHeartRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->start(); break;
        case 7: _t->stop(); break;
        case 8: _t->clear(); break;
        case 9: { QString _r = _t->save();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GpxLogger::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpxLogger::recordingChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GpxLogger::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpxLogger::pointCountChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GpxLogger::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpxLogger::lastSavedPathChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GpxLogger::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpxLogger::saveFailed)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GpxLogger *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->recording(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->pointCount(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->lastSavedPath(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GpxLogger::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GpxLogger.data,
    qt_meta_data_GpxLogger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GpxLogger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GpxLogger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GpxLogger.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GpxLogger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GpxLogger::recordingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GpxLogger::pointCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GpxLogger::lastSavedPathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GpxLogger::saveFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
