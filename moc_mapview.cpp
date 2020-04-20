/****************************************************************************
** Mapview meta object code from reading C++ file 'mapview.h'
**
** Created: Fri Oct 4 15:08:43 2013
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mapview.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Mapview::className() const
{
    return "Mapview";
}

QMetaObject *Mapview::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Mapview( "Mapview", &Mapview::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Mapview::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Mapview", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Mapview::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Mapview", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Mapview::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QFrame::staticMetaObject();
    static const QUMethod slot_0 = {"updatemap", 0, 0 };
    static const QUMethod slot_1 = {"slotzoomin", 0, 0 };
    static const QUMethod slot_2 = {"slotzoomout", 0, 0 };
    static const QUMethod slot_3 = {"slotsettrackup", 0, 0 };
    static const QUMethod slot_4 = {"slotsetnorthup", 0, 0 };
    static const QUMethod slot_5 = {"slotselectbgcolor", 0, 0 };
    static const QUMethod slot_6 = {"slotselectaccolor", 0, 0 };
    static const QUMethod slot_7 = {"slotselectllcolor", 0, 0 };
    static const QUMethod slot_8 = {"slotselectrrcolor", 0, 0 };
    static const QUMethod slot_9 = {"slotselectpathcolor", 0, 0 };
    static const QUMethod slot_10 = {"slotselectdicolor", 0, 0 };
    static const QUMethod slot_11 = {"slotselecttarget1color", 0, 0 };
    static const QUMethod slot_12 = {"slotselecttarget2color", 0, 0 };
    static const QUMethod slot_13 = {"slotselecttarget3color", 0, 0 };
    static const QUMethod slot_14 = {"slotselecttarget4color", 0, 0 };
    static const QUMethod slot_15 = {"slotselectwaypointcolor", 0, 0 };
    static const QUMethod slot_16 = {"slotselectpoicolor", 0, 0 };
    static const QUMethod slot_17 = {"slotsett1circles", 0, 0 };
    static const QUMethod slot_18 = {"slotsett1lines", 0, 0 };
    static const QUMethod slot_19 = {"slotsett2circles", 0, 0 };
    static const QUMethod slot_20 = {"slotsett2lines", 0, 0 };
    static const QUMethod slot_21 = {"slotsett3circles", 0, 0 };
    static const QUMethod slot_22 = {"slotsett3lines", 0, 0 };
    static const QUMethod slot_23 = {"slotsett4circles", 0, 0 };
    static const QUMethod slot_24 = {"slotsett4lines", 0, 0 };
    static const QUParameter param_slot_25[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_25 = {"slotsetpathskip", 1, param_slot_25 };
    static const QUParameter param_slot_26[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_26 = {"slotsett1skip", 1, param_slot_26 };
    static const QUParameter param_slot_27[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_27 = {"slotsett2skip", 1, param_slot_27 };
    static const QUParameter param_slot_28[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_28 = {"slotsett3skip", 1, param_slot_28 };
    static const QUParameter param_slot_29[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_29 = {"slotsett4skip", 1, param_slot_29 };
    static const QMetaData slot_tbl[] = {
	{ "updatemap()", &slot_0, QMetaData::Public },
	{ "slotzoomin()", &slot_1, QMetaData::Public },
	{ "slotzoomout()", &slot_2, QMetaData::Public },
	{ "slotsettrackup()", &slot_3, QMetaData::Public },
	{ "slotsetnorthup()", &slot_4, QMetaData::Public },
	{ "slotselectbgcolor()", &slot_5, QMetaData::Public },
	{ "slotselectaccolor()", &slot_6, QMetaData::Public },
	{ "slotselectllcolor()", &slot_7, QMetaData::Public },
	{ "slotselectrrcolor()", &slot_8, QMetaData::Public },
	{ "slotselectpathcolor()", &slot_9, QMetaData::Public },
	{ "slotselectdicolor()", &slot_10, QMetaData::Public },
	{ "slotselecttarget1color()", &slot_11, QMetaData::Public },
	{ "slotselecttarget2color()", &slot_12, QMetaData::Public },
	{ "slotselecttarget3color()", &slot_13, QMetaData::Public },
	{ "slotselecttarget4color()", &slot_14, QMetaData::Public },
	{ "slotselectwaypointcolor()", &slot_15, QMetaData::Public },
	{ "slotselectpoicolor()", &slot_16, QMetaData::Public },
	{ "slotsett1circles()", &slot_17, QMetaData::Public },
	{ "slotsett1lines()", &slot_18, QMetaData::Public },
	{ "slotsett2circles()", &slot_19, QMetaData::Public },
	{ "slotsett2lines()", &slot_20, QMetaData::Public },
	{ "slotsett3circles()", &slot_21, QMetaData::Public },
	{ "slotsett3lines()", &slot_22, QMetaData::Public },
	{ "slotsett4circles()", &slot_23, QMetaData::Public },
	{ "slotsett4lines()", &slot_24, QMetaData::Public },
	{ "slotsetpathskip(int)", &slot_25, QMetaData::Public },
	{ "slotsett1skip(int)", &slot_26, QMetaData::Public },
	{ "slotsett2skip(int)", &slot_27, QMetaData::Public },
	{ "slotsett3skip(int)", &slot_28, QMetaData::Public },
	{ "slotsett4skip(int)", &slot_29, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"Mapview", parentObject,
	slot_tbl, 30,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Mapview.setMetaObject( metaObj );
    return metaObj;
}

void* Mapview::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Mapview" ) )
	return this;
    return QFrame::qt_cast( clname );
}

bool Mapview::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: updatemap(); break;
    case 1: slotzoomin(); break;
    case 2: slotzoomout(); break;
    case 3: slotsettrackup(); break;
    case 4: slotsetnorthup(); break;
    case 5: slotselectbgcolor(); break;
    case 6: slotselectaccolor(); break;
    case 7: slotselectllcolor(); break;
    case 8: slotselectrrcolor(); break;
    case 9: slotselectpathcolor(); break;
    case 10: slotselectdicolor(); break;
    case 11: slotselecttarget1color(); break;
    case 12: slotselecttarget2color(); break;
    case 13: slotselecttarget3color(); break;
    case 14: slotselecttarget4color(); break;
    case 15: slotselectwaypointcolor(); break;
    case 16: slotselectpoicolor(); break;
    case 17: slotsett1circles(); break;
    case 18: slotsett1lines(); break;
    case 19: slotsett2circles(); break;
    case 20: slotsett2lines(); break;
    case 21: slotsett3circles(); break;
    case 22: slotsett3lines(); break;
    case 23: slotsett4circles(); break;
    case 24: slotsett4lines(); break;
    case 25: slotsetpathskip((int)static_QUType_int.get(_o+1)); break;
    case 26: slotsett1skip((int)static_QUType_int.get(_o+1)); break;
    case 27: slotsett2skip((int)static_QUType_int.get(_o+1)); break;
    case 28: slotsett3skip((int)static_QUType_int.get(_o+1)); break;
    case 29: slotsett4skip((int)static_QUType_int.get(_o+1)); break;
    default:
	return QFrame::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Mapview::qt_emit( int _id, QUObject* _o )
{
    return QFrame::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Mapview::qt_property( int id, int f, QVariant* v)
{
    return QFrame::qt_property( id, f, v);
}

bool Mapview::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
