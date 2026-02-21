/****************************************************************************
** Meta object code from reading C++ file 'GpsPositionSource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../GpsPositionSource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GpsPositionSource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GpsPositionSource_t {
    QByteArrayData data[20];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GpsPositionSource_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GpsPositionSource_t qt_meta_stringdata_GpsPositionSource = {
    {
QT_MOC_LITERAL(0, 0, 17), // "GpsPositionSource"
QT_MOC_LITERAL(1, 18, 13), // "activeChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "validChanged"
QT_MOC_LITERAL(4, 46, 15), // "positionChanged"
QT_MOC_LITERAL(5, 62, 5), // "error"
QT_MOC_LITERAL(6, 68, 7), // "message"
QT_MOC_LITERAL(7, 76, 12), // "fixAvailable"
QT_MOC_LITERAL(8, 89, 8), // "latitude"
QT_MOC_LITERAL(9, 98, 9), // "longitude"
QT_MOC_LITERAL(10, 108, 8), // "speedKmh"
QT_MOC_LITERAL(11, 117, 9), // "courseDeg"
QT_MOC_LITERAL(12, 127, 12), // "isoTimestamp"
QT_MOC_LITERAL(13, 140, 12), // "startUpdates"
QT_MOC_LITERAL(14, 153, 11), // "stopUpdates"
QT_MOC_LITERAL(15, 165, 13), // "requestUpdate"
QT_MOC_LITERAL(16, 179, 7), // "timeout"
QT_MOC_LITERAL(17, 187, 10), // "pollPigpio"
QT_MOC_LITERAL(18, 198, 6), // "active"
QT_MOC_LITERAL(19, 205, 5) // "valid"

    },
    "GpsPositionSource\0activeChanged\0\0"
    "validChanged\0positionChanged\0error\0"
    "message\0fixAvailable\0latitude\0longitude\0"
    "speedKmh\0courseDeg\0isoTimestamp\0"
    "startUpdates\0stopUpdates\0requestUpdate\0"
    "timeout\0pollPigpio\0active\0valid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GpsPositionSource[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       6,   88, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       7,    5,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   81,    2, 0x0a /* Public */,
      14,    0,   82,    2, 0x0a /* Public */,
      15,    1,   83,    2, 0x0a /* Public */,
      15,    0,   86,    2, 0x2a /* Public | MethodCloned */,
      17,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,    8,    9,   10,   11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      18, QMetaType::Bool, 0x00495103,
      19, QMetaType::Bool, 0x00495001,
       8, QMetaType::Double, 0x00495001,
       9, QMetaType::Double, 0x00495001,
      10, QMetaType::Double, 0x00495001,
      11, QMetaType::Double, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       2,
       2,
       2,

       0        // eod
};

void GpsPositionSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GpsPositionSource *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->validChanged(); break;
        case 2: _t->positionChanged(); break;
        case 3: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->fixAvailable((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 5: _t->startUpdates(); break;
        case 6: _t->stopUpdates(); break;
        case 7: _t->requestUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->requestUpdate(); break;
        case 9: _t->pollPigpio(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GpsPositionSource::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsPositionSource::activeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GpsPositionSource::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsPositionSource::validChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GpsPositionSource::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsPositionSource::positionChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GpsPositionSource::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsPositionSource::error)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GpsPositionSource::*)(double , double , double , double , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GpsPositionSource::fixAvailable)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GpsPositionSource *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->active(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->valid(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->latitude(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->longitude(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->speedKmh(); break;
        case 5: *reinterpret_cast< double*>(_v) = _t->courseDeg(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GpsPositionSource *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setActive(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GpsPositionSource::staticMetaObject = { {
    QMetaObject::SuperData::link<QGeoPositionInfoSource::staticMetaObject>(),
    qt_meta_stringdata_GpsPositionSource.data,
    qt_meta_data_GpsPositionSource,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GpsPositionSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GpsPositionSource::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GpsPositionSource.stringdata0))
        return static_cast<void*>(this);
    return QGeoPositionInfoSource::qt_metacast(_clname);
}

int GpsPositionSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGeoPositionInfoSource::qt_metacall(_c, _id, _a);
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
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GpsPositionSource::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GpsPositionSource::validChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GpsPositionSource::positionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GpsPositionSource::error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GpsPositionSource::fixAvailable(double _t1, double _t2, double _t3, double _t4, const QString & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
