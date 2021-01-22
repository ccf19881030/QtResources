/****************************************************************************
** Meta object code from reading C++ file 'myphotoview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../myphotoview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myphotoview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PYNum_t {
    QByteArrayData data[8];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PYNum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PYNum_t qt_meta_stringdata_PYNum = {
    {
QT_MOC_LITERAL(0, 0, 5), // "PYNum"
QT_MOC_LITERAL(1, 6, 8), // "setTotal"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "totalNum"
QT_MOC_LITERAL(4, 25, 8), // "setValue"
QT_MOC_LITERAL(5, 34, 5), // "value"
QT_MOC_LITERAL(6, 40, 8), // "DoFading"
QT_MOC_LITERAL(7, 49, 8) // "DoHiding"

    },
    "PYNum\0setTotal\0\0totalNum\0setValue\0"
    "value\0DoFading\0DoHiding"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PYNum[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    0,   40,    2, 0x08 /* Private */,
       7,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PYNum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PYNum *_t = static_cast<PYNum *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setTotal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->DoFading(); break;
        case 3: _t->DoHiding(); break;
        default: ;
        }
    }
}

const QMetaObject PYNum::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PYNum.data,
      qt_meta_data_PYNum,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PYNum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PYNum::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PYNum.stringdata0))
        return static_cast<void*>(const_cast< PYNum*>(this));
    return QWidget::qt_metacast(_clname);
}

int PYNum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_myPhotoView_t {
    QByteArrayData data[11];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myPhotoView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myPhotoView_t qt_meta_stringdata_myPhotoView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "myPhotoView"
QT_MOC_LITERAL(1, 12, 12), // "sig_setValue"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "value"
QT_MOC_LITERAL(4, 32, 12), // "sig_setTotal"
QT_MOC_LITERAL(5, 45, 5), // "total"
QT_MOC_LITERAL(6, 51, 4), // "load"
QT_MOC_LITERAL(7, 56, 9), // "strFolder"
QT_MOC_LITERAL(8, 66, 8), // "showNext"
QT_MOC_LITERAL(9, 75, 12), // "showPrevious"
QT_MOC_LITERAL(10, 88, 13) // "DoImageFading"

    },
    "myPhotoView\0sig_setValue\0\0value\0"
    "sig_setTotal\0total\0load\0strFolder\0"
    "showNext\0showPrevious\0DoImageFading"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myPhotoView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   50,    2, 0x0a /* Public */,
       8,    0,   53,    2, 0x0a /* Public */,
       9,    0,   54,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void myPhotoView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myPhotoView *_t = static_cast<myPhotoView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_setTotal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->load((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->showNext(); break;
        case 4: _t->showPrevious(); break;
        case 5: _t->DoImageFading(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (myPhotoView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myPhotoView::sig_setValue)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (myPhotoView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myPhotoView::sig_setTotal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject myPhotoView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myPhotoView.data,
      qt_meta_data_myPhotoView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myPhotoView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myPhotoView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myPhotoView.stringdata0))
        return static_cast<void*>(const_cast< myPhotoView*>(this));
    return QWidget::qt_metacast(_clname);
}

int myPhotoView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void myPhotoView::sig_setValue(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myPhotoView::sig_setTotal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
