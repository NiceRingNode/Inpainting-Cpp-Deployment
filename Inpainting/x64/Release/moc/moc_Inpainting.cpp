/****************************************************************************
** Meta object code from reading C++ file 'Inpainting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Inpainting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Inpainting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Inpainting_t {
    QByteArrayData data[24];
    char stringdata0[377];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Inpainting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Inpainting_t qt_meta_stringdata_Inpainting = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Inpainting"
QT_MOC_LITERAL(1, 11, 11), // "eventFilter"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "watched"
QT_MOC_LITERAL(4, 32, 7), // "QEvent*"
QT_MOC_LITERAL(5, 40, 5), // "event"
QT_MOC_LITERAL(6, 46, 10), // "paintEvent"
QT_MOC_LITERAL(7, 57, 12), // "QPaintEvent*"
QT_MOC_LITERAL(8, 70, 14), // "dragEnterEvent"
QT_MOC_LITERAL(9, 85, 16), // "QDragEnterEvent*"
QT_MOC_LITERAL(10, 102, 9), // "dropEvent"
QT_MOC_LITERAL(11, 112, 11), // "QDropEvent*"
QT_MOC_LITERAL(12, 124, 15), // "mousePressEvent"
QT_MOC_LITERAL(13, 140, 12), // "QMouseEvent*"
QT_MOC_LITERAL(14, 153, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(15, 171, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(16, 186, 21), // "mouseDoubleClickEvent"
QT_MOC_LITERAL(17, 208, 23), // "on_lightmode_rb_toggled"
QT_MOC_LITERAL(18, 232, 7), // "checked"
QT_MOC_LITERAL(19, 240, 22), // "on_darkmode_rb_toggled"
QT_MOC_LITERAL(20, 263, 32), // "on_originsize_inpaint_rb_toggled"
QT_MOC_LITERAL(21, 296, 32), // "on_screensize_inpaint_rb_toggled"
QT_MOC_LITERAL(22, 329, 22), // "on_run_inpaint_clicked"
QT_MOC_LITERAL(23, 352, 24) // "on_clear_inpaint_clicked"

    },
    "Inpainting\0eventFilter\0\0watched\0QEvent*\0"
    "event\0paintEvent\0QPaintEvent*\0"
    "dragEnterEvent\0QDragEnterEvent*\0"
    "dropEvent\0QDropEvent*\0mousePressEvent\0"
    "QMouseEvent*\0mouseReleaseEvent\0"
    "mouseMoveEvent\0mouseDoubleClickEvent\0"
    "on_lightmode_rb_toggled\0checked\0"
    "on_darkmode_rb_toggled\0"
    "on_originsize_inpaint_rb_toggled\0"
    "on_screensize_inpaint_rb_toggled\0"
    "on_run_inpaint_clicked\0on_clear_inpaint_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Inpainting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x08 /* Private */,
       6,    1,   89,    2, 0x08 /* Private */,
       8,    1,   92,    2, 0x08 /* Private */,
      10,    1,   95,    2, 0x08 /* Private */,
      12,    1,   98,    2, 0x08 /* Private */,
      14,    1,  101,    2, 0x08 /* Private */,
      15,    1,  104,    2, 0x08 /* Private */,
      16,    1,  107,    2, 0x08 /* Private */,
      17,    1,  110,    2, 0x08 /* Private */,
      19,    1,  113,    2, 0x08 /* Private */,
      20,    1,  116,    2, 0x08 /* Private */,
      21,    1,  119,    2, 0x08 /* Private */,
      22,    0,  122,    2, 0x08 /* Private */,
      23,    0,  123,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7,    5,
    QMetaType::Void, 0x80000000 | 9,    5,
    QMetaType::Void, 0x80000000 | 11,    5,
    QMetaType::Void, 0x80000000 | 13,    5,
    QMetaType::Void, 0x80000000 | 13,    5,
    QMetaType::Void, 0x80000000 | 13,    5,
    QMetaType::Void, 0x80000000 | 13,    5,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Inpainting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Inpainting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 2: _t->dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 3: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 4: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->mouseDoubleClickEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->on_lightmode_rb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_darkmode_rb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_originsize_inpaint_rb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_screensize_inpaint_rb_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_run_inpaint_clicked(); break;
        case 13: _t->on_clear_inpaint_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Inpainting::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Inpainting.data,
    qt_meta_data_Inpainting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Inpainting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Inpainting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Inpainting.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Inpainting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
