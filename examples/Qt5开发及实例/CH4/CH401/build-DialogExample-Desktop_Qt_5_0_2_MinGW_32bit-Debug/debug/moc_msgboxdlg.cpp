/****************************************************************************
** Meta object code from reading C++ file 'msgboxdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DialogExample/msgboxdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msgboxdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MsgBoxDlg_t {
    QByteArrayData data[8];
    char stringdata[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MsgBoxDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MsgBoxDlg_t qt_meta_stringdata_MsgBoxDlg = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 15),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 18),
QT_MOC_LITERAL(4, 46, 14),
QT_MOC_LITERAL(5, 61, 15),
QT_MOC_LITERAL(6, 77, 12),
QT_MOC_LITERAL(7, 90, 14)
    },
    "MsgBoxDlg\0showQuestionMsg\0\0"
    "showInformationMsg\0showWarningMsg\0"
    "showCriticalMsg\0showAboutMsg\0"
    "showAboutQtMsg\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MsgBoxDlg[] = {

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
       1,    0,   44,    2, 0x08,
       3,    0,   45,    2, 0x08,
       4,    0,   46,    2, 0x08,
       5,    0,   47,    2, 0x08,
       6,    0,   48,    2, 0x08,
       7,    0,   49,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MsgBoxDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MsgBoxDlg *_t = static_cast<MsgBoxDlg *>(_o);
        switch (_id) {
        case 0: _t->showQuestionMsg(); break;
        case 1: _t->showInformationMsg(); break;
        case 2: _t->showWarningMsg(); break;
        case 3: _t->showCriticalMsg(); break;
        case 4: _t->showAboutMsg(); break;
        case 5: _t->showAboutQtMsg(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MsgBoxDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MsgBoxDlg.data,
      qt_meta_data_MsgBoxDlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *MsgBoxDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MsgBoxDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MsgBoxDlg.stringdata))
        return static_cast<void*>(const_cast< MsgBoxDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int MsgBoxDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
