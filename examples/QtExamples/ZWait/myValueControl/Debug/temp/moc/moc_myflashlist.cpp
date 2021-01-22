/****************************************************************************
** Meta object code from reading C++ file 'myflashlist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../myflashlist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myflashlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myFlashList_t {
    QByteArrayData data[8];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myFlashList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myFlashList_t qt_meta_stringdata_myFlashList = {
    {
QT_MOC_LITERAL(0, 0, 11), // "myFlashList"
QT_MOC_LITERAL(1, 12, 19), // "sig_setCurrentIndex"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9), // "currIndex"
QT_MOC_LITERAL(4, 43, 15), // "sig_itemClicked"
QT_MOC_LITERAL(5, 59, 3), // "str"
QT_MOC_LITERAL(6, 63, 10), // "setMaximum"
QT_MOC_LITERAL(7, 74, 3) // "max"

    },
    "myFlashList\0sig_setCurrentIndex\0\0"
    "currIndex\0sig_itemClicked\0str\0setMaximum\0"
    "max"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myFlashList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void myFlashList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myFlashList *_t = static_cast<myFlashList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_itemClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setMaximum((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (myFlashList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myFlashList::sig_setCurrentIndex)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (myFlashList::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myFlashList::sig_itemClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject myFlashList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myFlashList.data,
      qt_meta_data_myFlashList,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myFlashList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myFlashList::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myFlashList.stringdata0))
        return static_cast<void*>(const_cast< myFlashList*>(this));
    return QWidget::qt_metacast(_clname);
}

int myFlashList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void myFlashList::sig_setCurrentIndex(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myFlashList::sig_itemClicked(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_PYFlashListPrivate_t {
    QByteArrayData data[12];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PYFlashListPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PYFlashListPrivate_t qt_meta_stringdata_PYFlashListPrivate = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PYFlashListPrivate"
QT_MOC_LITERAL(1, 19, 14), // "sig_setMaximum"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 3), // "max"
QT_MOC_LITERAL(4, 39, 19), // "sig_setCurrentIndex"
QT_MOC_LITERAL(5, 59, 9), // "currIndex"
QT_MOC_LITERAL(6, 69, 15), // "sig_itemClicked"
QT_MOC_LITERAL(7, 85, 3), // "str"
QT_MOC_LITERAL(8, 89, 15), // "setCurrentIndex"
QT_MOC_LITERAL(9, 105, 8), // "curIndex"
QT_MOC_LITERAL(10, 114, 10), // "DoRotation"
QT_MOC_LITERAL(11, 125, 15) // "UpdateItemCount"

    },
    "PYFlashListPrivate\0sig_setMaximum\0\0"
    "max\0sig_setCurrentIndex\0currIndex\0"
    "sig_itemClicked\0str\0setCurrentIndex\0"
    "curIndex\0DoRotation\0UpdateItemCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PYFlashListPrivate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   53,    2, 0x0a /* Public */,
      10,    0,   56,    2, 0x08 /* Private */,
      11,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PYFlashListPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PYFlashListPrivate *_t = static_cast<PYFlashListPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_setMaximum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sig_itemClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->DoRotation(); break;
        case 5: _t->UpdateItemCount(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PYFlashListPrivate::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PYFlashListPrivate::sig_setMaximum)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PYFlashListPrivate::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PYFlashListPrivate::sig_setCurrentIndex)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PYFlashListPrivate::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PYFlashListPrivate::sig_itemClicked)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject PYFlashListPrivate::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PYFlashListPrivate.data,
      qt_meta_data_PYFlashListPrivate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PYFlashListPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PYFlashListPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PYFlashListPrivate.stringdata0))
        return static_cast<void*>(const_cast< PYFlashListPrivate*>(this));
    return QWidget::qt_metacast(_clname);
}

int PYFlashListPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PYFlashListPrivate::sig_setMaximum(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PYFlashListPrivate::sig_setCurrentIndex(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PYFlashListPrivate::sig_itemClicked(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
