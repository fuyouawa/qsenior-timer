/****************************************************************************
** Meta object code from reading C++ file 'client_looper.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../global/client_looper.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client_looper.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSClientLooperENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSClientLooperENDCLASS = QtMocHelpers::stringData(
    "ClientLooper",
    "writeError",
    "",
    "status",
    "readError",
    "connectError",
    "connectedToServer",
    "newMsgReceived",
    "PacketBuffer*",
    "packet",
    "eventLoopStopped",
    "Send",
    "buf"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSClientLooperENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[13];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[10];
    char stringdata5[13];
    char stringdata6[18];
    char stringdata7[15];
    char stringdata8[14];
    char stringdata9[7];
    char stringdata10[17];
    char stringdata11[5];
    char stringdata12[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSClientLooperENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSClientLooperENDCLASS_t qt_meta_stringdata_CLASSClientLooperENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "ClientLooper"
        QT_MOC_LITERAL(13, 10),  // "writeError"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 6),  // "status"
        QT_MOC_LITERAL(32, 9),  // "readError"
        QT_MOC_LITERAL(42, 12),  // "connectError"
        QT_MOC_LITERAL(55, 17),  // "connectedToServer"
        QT_MOC_LITERAL(73, 14),  // "newMsgReceived"
        QT_MOC_LITERAL(88, 13),  // "PacketBuffer*"
        QT_MOC_LITERAL(102, 6),  // "packet"
        QT_MOC_LITERAL(109, 16),  // "eventLoopStopped"
        QT_MOC_LITERAL(126, 4),  // "Send"
        QT_MOC_LITERAL(131, 3)   // "buf"
    },
    "ClientLooper",
    "writeError",
    "",
    "status",
    "readError",
    "connectError",
    "connectedToServer",
    "newMsgReceived",
    "PacketBuffer*",
    "packet",
    "eventLoopStopped",
    "Send",
    "buf"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSClientLooperENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       4,    1,   59,    2, 0x06,    3 /* Public */,
       5,    1,   62,    2, 0x06,    5 /* Public */,
       6,    0,   65,    2, 0x06,    7 /* Public */,
       7,    1,   66,    2, 0x06,    8 /* Public */,
      10,    0,   69,    2, 0x06,   10 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   70,    2, 0x00,   11 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::QByteArray,   12,

       0        // eod
};

Q_CONSTINIT const QMetaObject ClientLooper::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_CLASSClientLooperENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSClientLooperENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSClientLooperENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ClientLooper, std::true_type>,
        // method 'writeError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'readError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'connectError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'connectedToServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'newMsgReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<PacketBuffer *, std::false_type>,
        // method 'eventLoopStopped'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Send'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>
    >,
    nullptr
} };

void ClientLooper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientLooper *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->writeError((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->readError((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->connectError((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->connectedToServer(); break;
        case 4: _t->newMsgReceived((*reinterpret_cast< std::add_pointer_t<PacketBuffer*>>(_a[1]))); break;
        case 5: _t->eventLoopStopped(); break;
        case 6: { bool _r = _t->Send((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientLooper::*)(int );
            if (_t _q_method = &ClientLooper::writeError; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientLooper::*)(int );
            if (_t _q_method = &ClientLooper::readError; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientLooper::*)(int );
            if (_t _q_method = &ClientLooper::connectError; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientLooper::*)();
            if (_t _q_method = &ClientLooper::connectedToServer; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ClientLooper::*)(PacketBuffer * );
            if (_t _q_method = &ClientLooper::newMsgReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ClientLooper::*)();
            if (_t _q_method = &ClientLooper::eventLoopStopped; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *ClientLooper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientLooper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSClientLooperENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ClientLooper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ClientLooper::writeError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientLooper::readError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientLooper::connectError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientLooper::connectedToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ClientLooper::newMsgReceived(PacketBuffer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientLooper::eventLoopStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
