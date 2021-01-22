/****************************************************************************
** Meta object code from reading C++ file 'imgprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImageProcessor/imgprocessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imgprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImgProcessor_t {
    QByteArrayData data[29];
    char stringdata[388];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ImgProcessor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ImgProcessor_t qt_meta_stringdata_ImgProcessor = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 11),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 12),
QT_MOC_LITERAL(4, 39, 13),
QT_MOC_LITERAL(5, 53, 14),
QT_MOC_LITERAL(6, 68, 10),
QT_MOC_LITERAL(7, 79, 11),
QT_MOC_LITERAL(8, 91, 12),
QT_MOC_LITERAL(9, 104, 13),
QT_MOC_LITERAL(10, 118, 13),
QT_MOC_LITERAL(11, 132, 18),
QT_MOC_LITERAL(12, 151, 20),
QT_MOC_LITERAL(13, 172, 16),
QT_MOC_LITERAL(14, 189, 8),
QT_MOC_LITERAL(15, 198, 15),
QT_MOC_LITERAL(16, 214, 9),
QT_MOC_LITERAL(17, 224, 11),
QT_MOC_LITERAL(18, 236, 13),
QT_MOC_LITERAL(19, 250, 16),
QT_MOC_LITERAL(20, 267, 12),
QT_MOC_LITERAL(21, 280, 24),
QT_MOC_LITERAL(22, 305, 15),
QT_MOC_LITERAL(23, 321, 3),
QT_MOC_LITERAL(24, 325, 8),
QT_MOC_LITERAL(25, 334, 13),
QT_MOC_LITERAL(26, 348, 8),
QT_MOC_LITERAL(27, 357, 3),
QT_MOC_LITERAL(28, 361, 25)
    },
    "ImgProcessor\0ShowNewFile\0\0ShowOpenFile\0"
    "ShowPrintText\0ShowPrintImage\0ShowZoomIn\0"
    "ShowZoomOut\0ShowRotate90\0ShowRotate180\0"
    "ShowRotate270\0ShowMirrorVertical\0"
    "ShowMirrorHorizontal\0ShowFontComboBox\0"
    "comboStr\0ShowSizeSpinBox\0spinValue\0"
    "ShowBoldBtn\0ShowItalicBtn\0ShowUnderlineBtn\0"
    "ShowColorBtn\0ShowCurrentFormatChanged\0"
    "QTextCharFormat\0fmt\0ShowList\0ShowAlignment\0"
    "QAction*\0act\0ShowCursorPositionChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImgProcessor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x09,
       3,    0,  120,    2, 0x09,
       4,    0,  121,    2, 0x09,
       5,    0,  122,    2, 0x09,
       6,    0,  123,    2, 0x09,
       7,    0,  124,    2, 0x09,
       8,    0,  125,    2, 0x09,
       9,    0,  126,    2, 0x09,
      10,    0,  127,    2, 0x09,
      11,    0,  128,    2, 0x09,
      12,    0,  129,    2, 0x09,
      13,    1,  130,    2, 0x09,
      15,    1,  133,    2, 0x09,
      17,    0,  136,    2, 0x09,
      18,    0,  137,    2, 0x09,
      19,    0,  138,    2, 0x09,
      20,    0,  139,    2, 0x09,
      21,    1,  140,    2, 0x09,
      24,    1,  143,    2, 0x09,
      25,    1,  146,    2, 0x09,
      28,    0,  149,    2, 0x09,

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
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,

       0        // eod
};

void ImgProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImgProcessor *_t = static_cast<ImgProcessor *>(_o);
        switch (_id) {
        case 0: _t->ShowNewFile(); break;
        case 1: _t->ShowOpenFile(); break;
        case 2: _t->ShowPrintText(); break;
        case 3: _t->ShowPrintImage(); break;
        case 4: _t->ShowZoomIn(); break;
        case 5: _t->ShowZoomOut(); break;
        case 6: _t->ShowRotate90(); break;
        case 7: _t->ShowRotate180(); break;
        case 8: _t->ShowRotate270(); break;
        case 9: _t->ShowMirrorVertical(); break;
        case 10: _t->ShowMirrorHorizontal(); break;
        case 11: _t->ShowFontComboBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->ShowSizeSpinBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->ShowBoldBtn(); break;
        case 14: _t->ShowItalicBtn(); break;
        case 15: _t->ShowUnderlineBtn(); break;
        case 16: _t->ShowColorBtn(); break;
        case 17: _t->ShowCurrentFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 18: _t->ShowList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->ShowAlignment((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 20: _t->ShowCursorPositionChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject ImgProcessor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ImgProcessor.data,
      qt_meta_data_ImgProcessor,  qt_static_metacall, 0, 0}
};


const QMetaObject *ImgProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImgProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImgProcessor.stringdata))
        return static_cast<void*>(const_cast< ImgProcessor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ImgProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
