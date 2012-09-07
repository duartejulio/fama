/****************************************************************************
** Meta object code from reading C++ file 'janela.h'
**
** Created: Fri 7. Sep 17:26:56 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../InterfaceFAMA/janela.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'janela.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Janela[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      29,   23,    7,    7, 0x0a,
      60,   49,    7,    7, 0x0a,
      89,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Janela[] = {
    "Janela\0\0abrirArquivo()\0index\0"
    "habilitarBotao(int)\0row,column\0"
    "atributoSelecionado(int,int)\0"
    "definirParametros()\0"
};

void Janela::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Janela *_t = static_cast<Janela *>(_o);
        switch (_id) {
        case 0: _t->abrirArquivo(); break;
        case 1: _t->habilitarBotao((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->atributoSelecionado((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->definirParametros(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Janela::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Janela::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Janela,
      qt_meta_data_Janela, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Janela::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Janela::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Janela::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Janela))
        return static_cast<void*>(const_cast< Janela*>(this));
    return QWidget::qt_metacast(_clname);
}

int Janela::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
