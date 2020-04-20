// $Id: soxgui.h,v 1.8 2007/05/13 21:29:31 sonntag Exp $
// Soxgui class definition
//

#ifndef SOXGUI_H
#define SOXGUI_H

#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qwidget.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qsettings.h>
#include <qspinbox.h>

#include "genericclient.h"
#include "coords_ll.h"
#include "wp_ll.h"
#include "mapview.h"
#include "position.h"
#include "showstate.h"

#define FT2M (12.0*2.54/100.0)


class Soxgui : public QWidget
{

  Q_OBJECT

  public:
    Soxgui();  // Constructor
    ~Soxgui();  // Destructor

  private:
    void parseGGA(QString,double *,double *,double *,double *);
    QColor readcolor(QString,QString);
    void writecolor(QString,QColor);
    QSettings usettings;
    QMenuBar *mainmenu;
    QPopupMenu *filemenu;
    GenericClient *client;
    QString stemp,stemp1,stemp2;
    QString gpshost;
    Q_UINT16 gpsport;
    QString gpscmd;
    coords_ll *flight;
    coords_ll *target1,*target2,*target3,*target4;
    wp_ll *waypoint,*poi;
    bool target1flag,target2flag,target3flag,target4flag,wpflag,poiflag;
    Mapview *map;
    QPushButton *zoomin;
    QPushButton *zoomout;
    QPushButton *northup;
    QPushButton *trackup;
    Position *current;
    Showstate *state;
    QString logfile;
    QString newlogfile;
    QString logpath;
    QFile *pathfile;
    QTextStream *pathstream;
    QString target1name;
    QString target2name;
    QString target3name;
    QString target4name;
    QString wpname;
    QString poiname;
    QFile *target1file;
    QFile *target2file;
    QFile *target3file;
    QFile *target4file;
    QFile *wpfile;
    QFile *poifile;
    double swathwidth;  // swath width on the ground in meters
    double sec,latm,lonm,t,lat,lon,ht;
    int hr,min,latd,lond,idt1,idt2,idt3,idt4,idwp,idpoi;
    void ingest_latlon(QFile *, coords_ll *);
    void ingest_waypoint(QFile *, wp_ll *);

  private slots:
    void about();
    void slotFirstGPS(QString);
    void slotNewGPS(QString);
    void slotGPSClosed();
    void slotGPSError(int);
    void slotTarget1();
    void slotTarget2();
    void slotTarget3();
    void slotTarget4();
    void slotWPFile();
    void slotPOIFile();
    void slotSetSwathWidth();
    void slotSetLeader();

};

#endif // SOXGUI_H
