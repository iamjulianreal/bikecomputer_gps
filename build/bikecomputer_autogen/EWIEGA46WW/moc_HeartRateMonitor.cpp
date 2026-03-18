/****************************************************************************
** Meta object code from reading C++ file 'HeartRateMonitor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../HeartRateMonitor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HeartRateMonitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HeartRateMonitor_t {
    QByteArrayData data[38];
    char stringdata0[681];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HeartRateMonitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HeartRateMonitor_t qt_meta_stringdata_HeartRateMonitor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "HeartRateMonitor"
QT_MOC_LITERAL(1, 17, 23), // "currentHeartRateChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 16), // "connectedChanged"
QT_MOC_LITERAL(4, 59, 17), // "heartRateReceived"
QT_MOC_LITERAL(5, 77, 9), // "heartRate"
QT_MOC_LITERAL(6, 87, 9), // "startScan"
QT_MOC_LITERAL(7, 97, 18), // "onDeviceDiscovered"
QT_MOC_LITERAL(8, 116, 20), // "QBluetoothDeviceInfo"
QT_MOC_LITERAL(9, 137, 6), // "device"
QT_MOC_LITERAL(10, 144, 14), // "onScanFinished"
QT_MOC_LITERAL(11, 159, 11), // "onScanError"
QT_MOC_LITERAL(12, 171, 37), // "QBluetoothDeviceDiscoveryAgen..."
QT_MOC_LITERAL(13, 209, 5), // "error"
QT_MOC_LITERAL(14, 215, 15), // "connectToDevice"
QT_MOC_LITERAL(15, 231, 21), // "onControllerConnected"
QT_MOC_LITERAL(16, 253, 24), // "onControllerDisconnected"
QT_MOC_LITERAL(17, 278, 17), // "onControllerError"
QT_MOC_LITERAL(18, 296, 27), // "QLowEnergyController::Error"
QT_MOC_LITERAL(19, 324, 19), // "onServiceDiscovered"
QT_MOC_LITERAL(20, 344, 14), // "QBluetoothUuid"
QT_MOC_LITERAL(21, 359, 11), // "serviceUuid"
QT_MOC_LITERAL(22, 371, 26), // "onServiceDiscoveryFinished"
QT_MOC_LITERAL(23, 398, 21), // "onServiceStateChanged"
QT_MOC_LITERAL(24, 420, 31), // "QLowEnergyService::ServiceState"
QT_MOC_LITERAL(25, 452, 8), // "newState"
QT_MOC_LITERAL(26, 461, 14), // "onServiceError"
QT_MOC_LITERAL(27, 476, 31), // "QLowEnergyService::ServiceError"
QT_MOC_LITERAL(28, 508, 23), // "onCharacteristicChanged"
QT_MOC_LITERAL(29, 532, 24), // "QLowEnergyCharacteristic"
QT_MOC_LITERAL(30, 557, 14), // "characteristic"
QT_MOC_LITERAL(31, 572, 5), // "value"
QT_MOC_LITERAL(32, 578, 19), // "onDescriptorWritten"
QT_MOC_LITERAL(33, 598, 20), // "QLowEnergyDescriptor"
QT_MOC_LITERAL(34, 619, 10), // "descriptor"
QT_MOC_LITERAL(35, 630, 23), // "publishPendingHeartRate"
QT_MOC_LITERAL(36, 654, 16), // "currentHeartRate"
QT_MOC_LITERAL(37, 671, 9) // "connected"

    },
    "HeartRateMonitor\0currentHeartRateChanged\0"
    "\0connectedChanged\0heartRateReceived\0"
    "heartRate\0startScan\0onDeviceDiscovered\0"
    "QBluetoothDeviceInfo\0device\0onScanFinished\0"
    "onScanError\0QBluetoothDeviceDiscoveryAgent::Error\0"
    "error\0connectToDevice\0onControllerConnected\0"
    "onControllerDisconnected\0onControllerError\0"
    "QLowEnergyController::Error\0"
    "onServiceDiscovered\0QBluetoothUuid\0"
    "serviceUuid\0onServiceDiscoveryFinished\0"
    "onServiceStateChanged\0"
    "QLowEnergyService::ServiceState\0"
    "newState\0onServiceError\0"
    "QLowEnergyService::ServiceError\0"
    "onCharacteristicChanged\0"
    "QLowEnergyCharacteristic\0characteristic\0"
    "value\0onDescriptorWritten\0"
    "QLowEnergyDescriptor\0descriptor\0"
    "publishPendingHeartRate\0currentHeartRate\0"
    "connected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeartRateMonitor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       2,  146, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    0,  105,    2, 0x06 /* Public */,
       4,    1,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  109,    2, 0x08 /* Private */,
       7,    1,  110,    2, 0x08 /* Private */,
      10,    0,  113,    2, 0x08 /* Private */,
      11,    1,  114,    2, 0x08 /* Private */,
      14,    1,  117,    2, 0x08 /* Private */,
      15,    0,  120,    2, 0x08 /* Private */,
      16,    0,  121,    2, 0x08 /* Private */,
      17,    1,  122,    2, 0x08 /* Private */,
      19,    1,  125,    2, 0x08 /* Private */,
      22,    0,  128,    2, 0x08 /* Private */,
      23,    1,  129,    2, 0x08 /* Private */,
      26,    1,  132,    2, 0x08 /* Private */,
      28,    2,  135,    2, 0x08 /* Private */,
      32,    2,  140,    2, 0x08 /* Private */,
      35,    0,  145,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   13,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 27,   13,
    QMetaType::Void, 0x80000000 | 29, QMetaType::QByteArray,   30,   31,
    QMetaType::Void, 0x80000000 | 33, QMetaType::QByteArray,   34,   31,
    QMetaType::Void,

 // properties: name, type, flags
      36, QMetaType::Int, 0x00495001,
      37, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void HeartRateMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HeartRateMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentHeartRateChanged(); break;
        case 1: _t->connectedChanged(); break;
        case 2: _t->heartRateReceived((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->startScan(); break;
        case 4: _t->onDeviceDiscovered((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 5: _t->onScanFinished(); break;
        case 6: _t->onScanError((*reinterpret_cast< QBluetoothDeviceDiscoveryAgent::Error(*)>(_a[1]))); break;
        case 7: _t->connectToDevice((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 8: _t->onControllerConnected(); break;
        case 9: _t->onControllerDisconnected(); break;
        case 10: _t->onControllerError((*reinterpret_cast< QLowEnergyController::Error(*)>(_a[1]))); break;
        case 11: _t->onServiceDiscovered((*reinterpret_cast< const QBluetoothUuid(*)>(_a[1]))); break;
        case 12: _t->onServiceDiscoveryFinished(); break;
        case 13: _t->onServiceStateChanged((*reinterpret_cast< QLowEnergyService::ServiceState(*)>(_a[1]))); break;
        case 14: _t->onServiceError((*reinterpret_cast< QLowEnergyService::ServiceError(*)>(_a[1]))); break;
        case 15: _t->onCharacteristicChanged((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 16: _t->onDescriptorWritten((*reinterpret_cast< const QLowEnergyDescriptor(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 17: _t->publishPendingHeartRate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothDeviceInfo >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothDeviceInfo >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyController::Error >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothUuid >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceState >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceError >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyDescriptor >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HeartRateMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeartRateMonitor::currentHeartRateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HeartRateMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeartRateMonitor::connectedChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HeartRateMonitor::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HeartRateMonitor::heartRateReceived)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<HeartRateMonitor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->currentHeartRate(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->connected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject HeartRateMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HeartRateMonitor.data,
    qt_meta_data_HeartRateMonitor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HeartRateMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeartRateMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HeartRateMonitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HeartRateMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
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
void HeartRateMonitor::currentHeartRateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void HeartRateMonitor::connectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void HeartRateMonitor::heartRateReceived(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
