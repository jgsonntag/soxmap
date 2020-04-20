/****************************************************************************
** Soxgui meta object code from reading C++ file 'soxgui.h'
**
** Created: Fri Oct 4 15:08:44 2013
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "soxgui.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Soxgui::className() const
{
    return "Soxgui";
}

QMetaObject *Soxgui::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Soxgui( "Soxgui", &Soxgui::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Soxgui::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Soxgui", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Soxgui::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Soxgui", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Soxgui::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"about", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"slotFirstGPS", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"slotNewGPS", 1, param_slot_2 };
    static const QUMethod slot_3 = {"slotGPSClosed", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"slotGPSError", 1, param_slot_4 };
    static const QUMethod slot_5 = {"slotTarget1", 0, 0 };
    static const QUMethod slot_6 = {"slotTarget2", 0, 0 };
    static const QUMethod slot_7 = {"slotTarget3", 0, 0 };
    static const QUMethod slot_8 = {"slotTarget4", 0, 0 };
    static const QUMethod slot_9 = {"slotWPFile", 0, 0 };
    static const QUMethod slot_10 = {"slotPOIFile", 0, 0 };
    static const QUMethod slot_11 = {"slotSetSwathWidth", 0, 0 };
    static const QUMethod slot_12 = {"slotSetLeader", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "about()", &slot_0, QMetaData::Private },
	{ "slotFirstGPS(QString)", &slot_1, QMetaData::Private },
	{ "slotNewGPS(QString)", &slot_2, QMetaData::Private },
	{ "slotGPSClosed()", &slot_3, QMetaData::Private },
	{ "slotGPSError(int)", &slot_4, QMetaData::Private },
	{ "slotTarget1()", &slot_5, QMetaData::Private },
	{ "slotTarget2()", &slot_6, QMetaData::Private },
	{ "slotTarget3()", &slot_7, QMetaData::Private },
	{ "slotTarget4()", &slot_8, QMetaData::Private },
	{ "slotWPFile()", &slot_9, QMetaData::Private },
	{ "slotPOIFile()", &slot_10, QMetaData::Private },
	{ "slotSetSwathWidth()", &slot_11, QMetaData::Private },
	{ "slotSetLeader()", &slot_12, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"Soxgui", parentObject,
	slot_tbl, 13,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Soxgui.setMetaObject( metaObj );
    return metaObj;
}

void* Soxgui::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Soxgui" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool Soxgui::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: about(); break;
    case 1: slotFirstGPS((QString)static_QUType_QString.get(_o+1)); break;
    case 2: slotNewGPS((QString)static_QUType_QString.get(_o+1)); break;
    case 3: slotGPSClosed(); break;
    case 4: slotGPSError((int)static_QUType_int.get(_o+1)); break;
    case 5: slotTarget1(); break;
    case 6: slotTarget2(); break;
    case 7: slotTarget3(); break;
    case 8: slotTarget4(); break;
    case 9: slotWPFile(); break;
    case 10: slotPOIFile(); break;
    case 11: slotSetSwathWidth(); break;
    case 12: slotSetLeader(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Soxgui::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Soxgui::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool Soxgui::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
