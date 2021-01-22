/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyselfQQ/widget.h"
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
    QByteArrayData data[21];
    char stringdata[342];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Widget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 23),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 18),
QT_MOC_LITERAL(4, 51, 11),
QT_MOC_LITERAL(5, 63, 19),
QT_MOC_LITERAL(6, 83, 29),
QT_MOC_LITERAL(7, 113, 1),
QT_MOC_LITERAL(8, 115, 30),
QT_MOC_LITERAL(9, 146, 4),
QT_MOC_LITERAL(10, 151, 19),
QT_MOC_LITERAL(11, 171, 7),
QT_MOC_LITERAL(12, 179, 21),
QT_MOC_LITERAL(13, 201, 24),
QT_MOC_LITERAL(14, 226, 20),
QT_MOC_LITERAL(15, 247, 13),
QT_MOC_LITERAL(16, 261, 15),
QT_MOC_LITERAL(17, 277, 3),
QT_MOC_LITERAL(18, 281, 19),
QT_MOC_LITERAL(19, 301, 20),
QT_MOC_LITERAL(20, 322, 18)
    },
    "Widget\0processPendingDatagrams\0\0"
    "on_sendBtn_clicked\0getFileName\0"
    "on_sendTBtn_clicked\0on_fontCbx_currentFontChanged\0"
    "f\0on_sizeCbx_currentIndexChanged\0arg1\0"
    "on_boldTBtn_clicked\0checked\0"
    "on_italicTBtn_clicked\0on_underlineTBtn_clicked\0"
    "on_colorTBtn_clicked\0curFmtChanged\0"
    "QTextCharFormat\0fmt\0on_saveTBtn_clicked\0"
    "on_clearTBtn_clicked\0on_exitBtn_clicked\0"
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
       1,    0,   84,    2, 0x08,
       3,    0,   85,    2, 0x08,
       4,    1,   86,    2, 0x08,
       5,    0,   89,    2, 0x08,
       6,    1,   90,    2, 0x08,
       8,    1,   93,    2, 0x08,
      10,    1,   96,    2, 0x08,
      12,    1,   99,    2, 0x08,
      13,    1,  102,    2, 0x08,
      14,    0,  105,    2, 0x08,
      15,    1,  106,    2, 0x08,
      18,    0,  109,    2, 0x08,
      19,    0,  110,    2, 0x08,
      20,    0,  111,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QFont,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        switch (_id) {
        case 0: _t->processPendingDatagrams(); break;
        case 1: _t->on_sendBtn_clicked(); break;
        case 2: _t->getFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_sendTBtn_clicked(); break;
        case 4: _t->on_fontCbx_currentFontChanged((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 5: _t->on_sizeCbx_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_boldTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_italicTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_underlineTBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_colorTBtn_clicked(); break;
        case 10: _t->curFmtChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 11: _t->on_saveTBtn_clicked(); break;
        case 12: _t->on_clearTBtn_clicked(); break;
        case 13: _t->on_exitBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
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
