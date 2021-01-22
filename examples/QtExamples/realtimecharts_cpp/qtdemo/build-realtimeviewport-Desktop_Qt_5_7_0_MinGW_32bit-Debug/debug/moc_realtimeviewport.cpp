/****************************************************************************
** Meta object code from reading C++ file 'realtimeviewport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../realtimeviewport/realtimeviewport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'realtimeviewport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RealTimeViewPort_t {
    QByteArrayData data[10];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RealTimeViewPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RealTimeViewPort_t qt_meta_stringdata_RealTimeViewPort = {
    {
QT_MOC_LITERAL(0, 0, 16), // "RealTimeViewPort"
QT_MOC_LITERAL(1, 17, 19), // "onMouseUsageChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 10), // "mouseUsage"
QT_MOC_LITERAL(4, 49, 6), // "onSave"
QT_MOC_LITERAL(5, 56, 19), // "onMouseMovePlotArea"
QT_MOC_LITERAL(6, 76, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 89, 5), // "event"
QT_MOC_LITERAL(8, 95, 18), // "onChartUpdateTimer"
QT_MOC_LITERAL(9, 114, 17) // "onViewPortChanged"

    },
    "RealTimeViewPort\0onMouseUsageChanged\0"
    "\0mouseUsage\0onSave\0onMouseMovePlotArea\0"
    "QMouseEvent*\0event\0onChartUpdateTimer\0"
    "onViewPortChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RealTimeViewPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    1,   42,    2, 0x08 /* Private */,
       5,    1,   45,    2, 0x08 /* Private */,
       8,    0,   48,    2, 0x08 /* Private */,
       9,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RealTimeViewPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RealTimeViewPort *_t = static_cast<RealTimeViewPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMouseUsageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onSave((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onMouseMovePlotArea((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->onChartUpdateTimer(); break;
        case 4: _t->onViewPortChanged(); break;
        default: ;
        }
    }
}

const QMetaObject RealTimeViewPort::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RealTimeViewPort.data,
      qt_meta_data_RealTimeViewPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RealTimeViewPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RealTimeViewPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RealTimeViewPort.stringdata0))
        return static_cast<void*>(const_cast< RealTimeViewPort*>(this));
    return QDialog::qt_metacast(_clname);
}

int RealTimeViewPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
