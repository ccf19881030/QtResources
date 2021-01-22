/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[16];
    char stringdata0[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 18), // "on_btnLine_clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 19), // "on_btnLinex_clicked"
QT_MOC_LITERAL(4, 47, 19), // "on_btnLiney_clicked"
QT_MOC_LITERAL(5, 67, 17), // "on_btnBar_clicked"
QT_MOC_LITERAL(6, 85, 18), // "on_btnBarx_clicked"
QT_MOC_LITERAL(7, 104, 18), // "on_btnBary_clicked"
QT_MOC_LITERAL(8, 123, 21), // "on_btnScatter_clicked"
QT_MOC_LITERAL(9, 145, 15), // "on_btnK_clicked"
QT_MOC_LITERAL(10, 161, 17), // "on_btnPie_clicked"
QT_MOC_LITERAL(11, 179, 19), // "on_btnRadar_clicked"
QT_MOC_LITERAL(12, 199, 19), // "on_btnChord_clicked"
QT_MOC_LITERAL(13, 219, 19), // "on_btnGauge_clicked"
QT_MOC_LITERAL(14, 239, 20), // "on_btnFunnel_clicked"
QT_MOC_LITERAL(15, 260, 18) // "on_btnData_clicked"

    },
    "Widget\0on_btnLine_clicked\0\0"
    "on_btnLinex_clicked\0on_btnLiney_clicked\0"
    "on_btnBar_clicked\0on_btnBarx_clicked\0"
    "on_btnBary_clicked\0on_btnScatter_clicked\0"
    "on_btnK_clicked\0on_btnPie_clicked\0"
    "on_btnRadar_clicked\0on_btnChord_clicked\0"
    "on_btnGauge_clicked\0on_btnFunnel_clicked\0"
    "on_btnData_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnLine_clicked(); break;
        case 1: _t->on_btnLinex_clicked(); break;
        case 2: _t->on_btnLiney_clicked(); break;
        case 3: _t->on_btnBar_clicked(); break;
        case 4: _t->on_btnBarx_clicked(); break;
        case 5: _t->on_btnBary_clicked(); break;
        case 6: _t->on_btnScatter_clicked(); break;
        case 7: _t->on_btnK_clicked(); break;
        case 8: _t->on_btnPie_clicked(); break;
        case 9: _t->on_btnRadar_clicked(); break;
        case 10: _t->on_btnChord_clicked(); break;
        case 11: _t->on_btnGauge_clicked(); break;
        case 12: _t->on_btnFunnel_clicked(); break;
        case 13: _t->on_btnData_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
