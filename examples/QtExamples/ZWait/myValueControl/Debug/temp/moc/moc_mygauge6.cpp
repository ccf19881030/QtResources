/****************************************************************************
** Meta object code from reading C++ file 'mygauge6.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mygauge6.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mygauge6.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myGauge6_t {
    QByteArrayData data[12];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myGauge6_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myGauge6_t qt_meta_stringdata_myGauge6 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myGauge6"
QT_MOC_LITERAL(1, 9, 8), // "setValue"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 5), // "value"
QT_MOC_LITERAL(4, 25, 8), // "setRange"
QT_MOC_LITERAL(5, 34, 3), // "min"
QT_MOC_LITERAL(6, 38, 3), // "max"
QT_MOC_LITERAL(7, 42, 18), // "setUseAntialiasing"
QT_MOC_LITERAL(8, 61, 3), // "use"
QT_MOC_LITERAL(9, 65, 12), // "setAnimating"
QT_MOC_LITERAL(10, 78, 7), // "animate"
QT_MOC_LITERAL(11, 86, 11) // "UpdateGraph"

    },
    "myGauge6\0setValue\0\0value\0setRange\0min\0"
    "max\0setUseAntialiasing\0use\0setAnimating\0"
    "animate\0UpdateGraph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myGauge6[] = {

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
       1,    1,   39,    2, 0x0a /* Public */,
       4,    2,   42,    2, 0x0a /* Public */,
       7,    1,   47,    2, 0x0a /* Public */,
       9,    1,   50,    2, 0x0a /* Public */,
      11,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,

       0        // eod
};

void myGauge6::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myGauge6 *_t = static_cast<myGauge6 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->setRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->setUseAntialiasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setAnimating((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->UpdateGraph(); break;
        default: ;
        }
    }
}

const QMetaObject myGauge6::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myGauge6.data,
      qt_meta_data_myGauge6,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myGauge6::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myGauge6::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myGauge6.stringdata0))
        return static_cast<void*>(const_cast< myGauge6*>(this));
    return QWidget::qt_metacast(_clname);
}

int myGauge6::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
