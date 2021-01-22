/****************************************************************************
** Meta object code from reading C++ file 'frmdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../frmdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmData_t {
    QByteArrayData data[9];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmData_t qt_meta_stringdata_frmData = {
    {
QT_MOC_LITERAL(0, 0, 7), // "frmData"
QT_MOC_LITERAL(1, 8, 15), // "on_btn4_clicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "on_btnOpen_clicked"
QT_MOC_LITERAL(4, 44, 15), // "on_btn3_clicked"
QT_MOC_LITERAL(5, 60, 15), // "on_btn2_clicked"
QT_MOC_LITERAL(6, 76, 15), // "on_btn1_clicked"
QT_MOC_LITERAL(7, 92, 12), // "ChangeEnable"
QT_MOC_LITERAL(8, 105, 1) // "b"

    },
    "frmData\0on_btn4_clicked\0\0on_btnOpen_clicked\0"
    "on_btn3_clicked\0on_btn2_clicked\0"
    "on_btn1_clicked\0ChangeEnable\0b"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmData[] = {

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
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void frmData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmData *_t = static_cast<frmData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn4_clicked(); break;
        case 1: _t->on_btnOpen_clicked(); break;
        case 2: _t->on_btn3_clicked(); break;
        case 3: _t->on_btn2_clicked(); break;
        case 4: _t->on_btn1_clicked(); break;
        case 5: _t->ChangeEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject frmData::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_frmData.data,
      qt_meta_data_frmData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *frmData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_frmData.stringdata0))
        return static_cast<void*>(const_cast< frmData*>(this));
    return QWidget::qt_metacast(_clname);
}

int frmData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
