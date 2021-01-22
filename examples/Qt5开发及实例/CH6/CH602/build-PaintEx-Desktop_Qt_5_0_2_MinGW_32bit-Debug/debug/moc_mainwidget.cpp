/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PaintEx/mainwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWidget_t {
    QByteArrayData data[12];
    char stringdata[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWidget_t qt_meta_stringdata_MainWidget = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 9),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 12),
QT_MOC_LITERAL(4, 35, 12),
QT_MOC_LITERAL(5, 48, 12),
QT_MOC_LITERAL(6, 61, 10),
QT_MOC_LITERAL(7, 72, 11),
QT_MOC_LITERAL(8, 84, 15),
QT_MOC_LITERAL(9, 100, 12),
QT_MOC_LITERAL(10, 113, 14),
QT_MOC_LITERAL(11, 128, 9)
    },
    "MainWidget\0ShowShape\0\0ShowPenWidth\0"
    "ShowPenColor\0ShowPenStyle\0ShowPenCap\0"
    "ShowPenJoin\0ShowSpreadStyle\0ShowFillRule\0"
    "ShowBrushColor\0ShowBrush\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x09,
       3,    1,   67,    2, 0x09,
       4,    0,   70,    2, 0x09,
       5,    1,   71,    2, 0x09,
       6,    1,   74,    2, 0x09,
       7,    1,   77,    2, 0x09,
       8,    0,   80,    2, 0x09,
       9,    0,   81,    2, 0x09,
      10,    0,   82,    2, 0x09,
      11,    1,   83,    2, 0x09,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void MainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWidget *_t = static_cast<MainWidget *>(_o);
        switch (_id) {
        case 0: _t->ShowShape((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ShowPenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ShowPenColor(); break;
        case 3: _t->ShowPenStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ShowPenCap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->ShowPenJoin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->ShowSpreadStyle(); break;
        case 7: _t->ShowFillRule(); break;
        case 8: _t->ShowBrushColor(); break;
        case 9: _t->ShowBrush((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget.data,
      qt_meta_data_MainWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget.stringdata))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_END_MOC_NAMESPACE
