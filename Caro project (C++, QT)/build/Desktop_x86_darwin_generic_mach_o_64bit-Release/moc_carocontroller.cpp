/****************************************************************************
** Meta object code from reading C++ file 'carocontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../carocontroller.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'carocontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
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
struct qt_meta_stringdata_CLASSCaroControllerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSCaroControllerENDCLASS = QtMocHelpers::stringData(
    "CaroController",
    "caroChanged",
    "",
    "matrixChanged",
    "showWinScreenChanged",
    "move",
    "index",
    "checkWin",
    "getShowWinScreen",
    "playWithBot",
    "replayLastMatch",
    "caro",
    "QList<QList<int>>",
    "matrix",
    "QList<int>",
    "showWinScreen"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCaroControllerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       3,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    4 /* Public */,
       3,    0,   63,    2, 0x06,    5 /* Public */,
       4,    0,   64,    2, 0x06,    6 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   65,    2, 0x02,    7 /* Public */,
       7,    0,   68,    2, 0x02,    9 /* Public */,
       8,    0,   69,    2, 0x102,   10 /* Public | MethodIsConst  */,
       9,    1,   70,    2, 0x02,   11 /* Public */,
      10,    0,   73,    2, 0x02,   13 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

 // properties: name, type, flags
      11, 0x80000000 | 12, 0x0001590b, uint(0), 0,
      13, 0x80000000 | 14, 0x0001590b, uint(1), 0,
      15, QMetaType::Int, 0x00015903, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject CaroController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSCaroControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCaroControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCaroControllerENDCLASS_t,
        // property 'caro'
        QtPrivate::TypeAndForceComplete<QList<QList<int>>, std::true_type>,
        // property 'matrix'
        QtPrivate::TypeAndForceComplete<QList<int>, std::true_type>,
        // property 'showWinScreen'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CaroController, std::true_type>,
        // method 'caroChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'matrixChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showWinScreenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'move'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'checkWin'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'getShowWinScreen'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'playWithBot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'replayLastMatch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CaroController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CaroController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->caroChanged(); break;
        case 1: _t->matrixChanged(); break;
        case 2: _t->showWinScreenChanged(); break;
        case 3: _t->move((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: { int _r = _t->checkWin();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->getShowWinScreen();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->playWithBot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->replayLastMatch(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CaroController::*)();
            if (_t _q_method = &CaroController::caroChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CaroController::*)();
            if (_t _q_method = &CaroController::matrixChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CaroController::*)();
            if (_t _q_method = &CaroController::showWinScreenChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QList<int>> >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        }
    }  else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CaroController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QList<QList<int>>*>(_v) = _t->getCaro(); break;
        case 1: *reinterpret_cast< QList<int>*>(_v) = _t->getMatrix(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->getShowWinScreen(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CaroController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCaro(*reinterpret_cast< QList<QList<int>>*>(_v)); break;
        case 1: _t->setMatrix(*reinterpret_cast< QList<int>*>(_v)); break;
        case 2: _t->setShowWinScreen(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *CaroController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CaroController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCaroControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CaroController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CaroController::caroChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CaroController::matrixChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CaroController::showWinScreenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
