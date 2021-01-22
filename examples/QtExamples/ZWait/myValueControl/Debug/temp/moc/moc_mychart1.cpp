/****************************************************************************
** Meta object code from reading C++ file 'mychart1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mychart1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mychart1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myChart1_t {
    QByteArrayData data[13];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myChart1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myChart1_t qt_meta_stringdata_myChart1 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myChart1"
QT_MOC_LITERAL(1, 9, 7), // "addData"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 4), // "data"
QT_MOC_LITERAL(4, 23, 18), // "setUseAntialiasing"
QT_MOC_LITERAL(5, 42, 3), // "use"
QT_MOC_LITERAL(6, 46, 18), // "getUseAntialiasing"
QT_MOC_LITERAL(7, 65, 22), // "setHorizontalLineColor"
QT_MOC_LITERAL(8, 88, 3), // "clr"
QT_MOC_LITERAL(9, 92, 12), // "setShowPoint"
QT_MOC_LITERAL(10, 105, 4), // "show"
QT_MOC_LITERAL(11, 110, 8), // "setTitle"
QT_MOC_LITERAL(12, 119, 3) // "str"

    },
    "myChart1\0addData\0\0data\0setUseAntialiasing\0"
    "use\0getUseAntialiasing\0setHorizontalLineColor\0"
    "clr\0setShowPoint\0show\0setTitle\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myChart1[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    1,   47,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x0a /* Public */,
      11,    1,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QColor,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void myChart1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myChart1 *_t = static_cast<myChart1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addData((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->setUseAntialiasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: { bool _r = _t->getUseAntialiasing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->setHorizontalLineColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 4: _t->setShowPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject myChart1::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myChart1.data,
      qt_meta_data_myChart1,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myChart1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myChart1::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myChart1.stringdata0))
        return static_cast<void*>(const_cast< myChart1*>(this));
    return QWidget::qt_metacast(_clname);
}

int myChart1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
