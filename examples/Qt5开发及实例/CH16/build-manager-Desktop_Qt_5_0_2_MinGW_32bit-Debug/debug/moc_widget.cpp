/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../manager/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[13];
    char stringdata[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Widget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 40),
QT_MOC_LITERAL(2, 48, 0),
QT_MOC_LITERAL(3, 49, 4),
QT_MOC_LITERAL(4, 54, 30),
QT_MOC_LITERAL(5, 85, 24),
QT_MOC_LITERAL(6, 110, 20),
QT_MOC_LITERAL(7, 131, 20),
QT_MOC_LITERAL(8, 152, 21),
QT_MOC_LITERAL(9, 174, 20),
QT_MOC_LITERAL(10, 195, 19),
QT_MOC_LITERAL(11, 215, 42),
QT_MOC_LITERAL(12, 258, 38)
    },
    "Widget\0on_sellBrandComboBox_currentIndexChanged\0"
    "\0arg1\0on_sellNumSpinBox_valueChanged\0"
    "on_sellCancelBtn_clicked\0on_sellOkBtn_clicked\0"
    "on_updateBtn_clicked\0on_manageMenu_clicked\0"
    "on_chartMenu_clicked\0on_quitMenu_clicked\0"
    "on_sellFactoryComboBox_currentIndexChanged\0"
    "on_factoryComboBox_currentIndexChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

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
       1,    1,   64,    2, 0x08,
       4,    1,   67,    2, 0x08,
       5,    0,   70,    2, 0x08,
       6,    0,   71,    2, 0x08,
       7,    0,   72,    2, 0x08,
       8,    0,   73,    2, 0x08,
       9,    0,   74,    2, 0x08,
      10,    0,   75,    2, 0x08,
      11,    1,   76,    2, 0x08,
      12,    1,   79,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        switch (_id) {
        case 0: _t->on_sellBrandComboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_sellNumSpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_sellCancelBtn_clicked(); break;
        case 3: _t->on_sellOkBtn_clicked(); break;
        case 4: _t->on_updateBtn_clicked(); break;
        case 5: _t->on_manageMenu_clicked(); break;
        case 6: _t->on_chartMenu_clicked(); break;
        case 7: _t->on_quitMenu_clicked(); break;
        case 8: _t->on_sellFactoryComboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_factoryComboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, 0, 0}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
