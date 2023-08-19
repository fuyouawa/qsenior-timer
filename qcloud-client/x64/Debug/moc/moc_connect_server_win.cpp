/****************************************************************************
** Meta object code from reading C++ file 'connect_server_win.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../frame/connect_server_win.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connect_server_win.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSConnectServerWinENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSConnectServerWinENDCLASS = QtMocHelpers::stringData(
    "ConnectServerWin"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSConnectServerWinENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSConnectServerWinENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSConnectServerWinENDCLASS_t qt_meta_stringdata_CLASSConnectServerWinENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16)   // "ConnectServerWin"
    },
    "ConnectServerWin"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSConnectServerWinENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject ConnectServerWin::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSConnectServerWinENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSConnectServerWinENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSConnectServerWinENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ConnectServerWin, std::true_type>
    >,
    nullptr
} };

void ConnectServerWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *ConnectServerWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectServerWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSConnectServerWinENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "qteasylib::EventHandler<ResponsedEvent>"))
        return static_cast< qteasylib::EventHandler<ResponsedEvent>*>(this);
    if (!strcmp(_clname, "qteasylib::EventHandler<ConnectedToServerEvent>"))
        return static_cast< qteasylib::EventHandler<ConnectedToServerEvent>*>(this);
    if (!strcmp(_clname, "qteasylib::EventHandler<ConnectErrorEvent>"))
        return static_cast< qteasylib::EventHandler<ConnectErrorEvent>*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ConnectServerWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
