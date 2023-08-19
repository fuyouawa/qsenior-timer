/****************************************************************************
** Meta object code from reading C++ file 'mainwin.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../frame/mainwin.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWinENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWinENDCLASS = QtMocHelpers::stringData(
    "MainWin",
    "on_btn_view_pwd_clicked",
    "",
    "checked",
    "on_btn_upload_saves_clicked",
    "on_btn_download_saves_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWinENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[8];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[28];
    char stringdata5[30];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWinENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWinENDCLASS_t qt_meta_stringdata_CLASSMainWinENDCLASS = {
    {
        QT_MOC_LITERAL(0, 7),  // "MainWin"
        QT_MOC_LITERAL(8, 23),  // "on_btn_view_pwd_clicked"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 7),  // "checked"
        QT_MOC_LITERAL(41, 27),  // "on_btn_upload_saves_clicked"
        QT_MOC_LITERAL(69, 29)   // "on_btn_download_saves_clicked"
    },
    "MainWin",
    "on_btn_view_pwd_clicked",
    "",
    "checked",
    "on_btn_upload_saves_clicked",
    "on_btn_download_saves_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWinENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x08,    1 /* Private */,
       4,    0,   35,    2, 0x08,    3 /* Private */,
       5,    0,   36,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWin::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWinENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWinENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWinENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWin, std::true_type>,
        // method 'on_btn_view_pwd_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_btn_upload_saves_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_download_saves_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWin *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btn_view_pwd_clicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->on_btn_upload_saves_clicked(); break;
        case 2: _t->on_btn_download_saves_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWinENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "qteasylib::EventHandler<ResponsedEvent>"))
        return static_cast< qteasylib::EventHandler<ResponsedEvent>*>(this);
    if (!strcmp(_clname, "qteasylib::EventHandler<ConnectedToServerEvent>"))
        return static_cast< qteasylib::EventHandler<ConnectedToServerEvent>*>(this);
    if (!strcmp(_clname, "qteasylib::EventHandler<LocalServerResponsedEvent>"))
        return static_cast< qteasylib::EventHandler<LocalServerResponsedEvent>*>(this);
    if (!strcmp(_clname, "qteasylib::EventHandler<ConnectErrorEvent>"))
        return static_cast< qteasylib::EventHandler<ConnectErrorEvent>*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
