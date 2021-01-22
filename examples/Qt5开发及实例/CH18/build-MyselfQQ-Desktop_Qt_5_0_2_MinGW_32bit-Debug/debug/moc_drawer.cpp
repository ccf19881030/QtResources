/****************************************************************************
** Meta object code from reading C++ file 'drawer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyselfQQ/drawer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Drawer_t {
    QByteArrayData data[11];
    char stringdata[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Drawer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Drawer_t qt_meta_stringdata_Drawer = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 15),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 15),
QT_MOC_LITERAL(4, 40, 15),
QT_MOC_LITERAL(5, 56, 15),
QT_MOC_LITERAL(6, 72, 15),
QT_MOC_LITERAL(7, 88, 15),
QT_MOC_LITERAL(8, 104, 15),
QT_MOC_LITERAL(9, 120, 15),
QT_MOC_LITERAL(10, 136, 15)
    },
    "Drawer\0showChatWidget1\0\0showChatWidget2\0"
    "showChatWidget3\0showChatWidget4\0"
    "showChatWidget5\0showChatWidget6\0"
    "showChatWidget7\0showChatWidget8\0"
    "showChatWidget9\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Drawer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08,
       3,    0,   60,    2, 0x08,
       4,    0,   61,    2, 0x08,
       5,    0,   62,    2, 0x08,
       6,    0,   63,    2, 0x08,
       7,    0,   64,    2, 0x08,
       8,    0,   65,    2, 0x08,
       9,    0,   66,    2, 0x08,
      10,    0,   67,    2, 0x08,

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

       0        // eod
};

void Drawer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Drawer *_t = static_cast<Drawer *>(_o);
        switch (_id) {
        case 0: _t->showChatWidget1(); break;
        case 1: _t->showChatWidget2(); break;
        case 2: _t->showChatWidget3(); break;
        case 3: _t->showChatWidget4(); break;
        case 4: _t->showChatWidget5(); break;
        case 5: _t->showChatWidget6(); break;
        case 6: _t->showChatWidget7(); break;
        case 7: _t->showChatWidget8(); break;
        case 8: _t->showChatWidget9(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Drawer::staticMetaObject = {
    { &QToolBox::staticMetaObject, qt_meta_stringdata_Drawer.data,
      qt_meta_data_Drawer,  qt_static_metacall, 0, 0}
};


const QMetaObject *Drawer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Drawer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Drawer.stringdata))
        return static_cast<void*>(const_cast< Drawer*>(this));
    return QToolBox::qt_metacast(_clname);
}

int Drawer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
