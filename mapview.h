// $Id: mapview.h,v 1.7 2007/05/13 21:29:31 sonntag Exp $
#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <qframe.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qstring.h>
#include <qcolor.h>
#include <qbrush.h>
#include <qstring.h>

#include "coords_ll.h"
#include "wp_ll.h"
#include "position.h"

#define NZOOM 17
#define ACLF 15
#define ACLA 20
#define ACLW 20
#define ACLT 8

extern int PROJ;
extern double LON0;

class Mapview : public QFrame
{
  Q_OBJECT

  public:
    Mapview(coords_ll *flight,coords_ll *bg1,coords_ll *bg2,
            coords_ll *bg3,coords_ll *bg4,wp_ll *wp,wp_ll *po,
            Position *cur,QWidget *parent=0,const char *name=0);
    ~Mapview();
    bool gettrackup();
    int getcurrentzoom();
    void setcurrentzoom(int);
    QColor getbgcolor();
    void setbgcolor(QColor);
    QColor getaccolor();
    void setaccolor(QColor);
    QColor getllcolor();
    void setllcolor(QColor);
    QColor getrrcolor();
    void setrrcolor(QColor);
    QColor getpathcolor();
    void setpathcolor(QColor);
    QColor getdicolor();
    void setdicolor(QColor);
    QColor gett1color();
    void sett1color(QColor);
    QColor gett2color();
    void sett2color(QColor);
    QColor gett3color();
    void sett3color(QColor);
    QColor gett4color();
    void sett4color(QColor);
    QColor getwpcolor();
    void setwpcolor(QColor);
    QColor getpoicolor();
    void setpoicolor(QColor);
    bool gett1circles();
    void sett1circles(bool);
    bool gett2circles();
    void sett2circles(bool);
    bool gett3circles();
    void sett3circles(bool);
    bool gett4circles();
    void sett4circles(bool);
    int getpathskip();
    int gett1skip();
    int gett2skip();
    int gett3skip();
    int gett4skip();

  private:
    void paintEvent(QPaintEvent *);
    void drawcoords(coords_ll *,int);
    void drawlines(coords_ll *);
    void get_angle_distortion(coords_ll *);
    void drawwp(wp_ll *);
    int pathskip;
    int t1skip;
    int t2skip;
    int t3skip;
    int t4skip;
    QPainter *paint;
    QString label;
    QColor bgcolor;  // Background color
    QColor accolor;  // Aircraft symbol color
    QColor llcolor;  // Leader line color
    QColor rrcolor;  // Rangerings color
    QColor pathcolor;  // Color of the breadcrumb (current flight) path
    QColor dicolor;  // Direction indicator color
    QColor target1color;  // Target1 color
    QColor target2color;  // Target2 color
    QColor target3color;  // Target3 color
    QColor target4color;  // Target4 color
    QColor waypointcolor;
    QColor poicolor;
    coords_ll *flightpath;
    coords_ll *target1path;
    coords_ll *target2path;
    coords_ll *target3path;
    coords_ll *target4path;
    wp_ll *wppath;
    wp_ll *poipath;
    coords_ll *leader;
    Position *current;
    bool trackup;
    bool t1circles;
    bool t2circles;
    bool t3circles;
    bool t4circles;
    double ddum;
    double tleader_sec;
    double distort;  // this is the constantly-updated angular distortion
                     // caused by the pseudo-UTM map projection
    double ldrlat;
    double ldrlon;
    double dleader_km;
    double lati,loni,hdgi,ti,newlat,newlon;
    double zoom[NZOOM];
    double spixpnm;  // map scale in pixels per nautical mile
    double spixpm;  // map scale in pixels per meter
    int currentzoom;  // Current zoom level array index
    int acxp;  // Aircraft screen x pos in pixels
    int acyp;  // Aircraft screen y pos in pixels
    int acxf;  // Aircraft nose x pos in pixels
    int acyf;  // Aircraft nose y pos in pixels
    int acxa;  // Aircraft tail x pos in pixels
    int acya;  // Aircraft tail y pos in pixels
    int acxr;  // Aircraft right x pos
    int acyr;  // Aircraft right y pos
    int acxl;  // Aircraft left x pos
    int acyl;  // Aircraft left y pos
    int atxr;  // Aircraft right tail x pos
    int atyr;  // Aircraft right tail y pos
    int atxl;  // Aircraft left tail x pos;
    int atyl;  // Aircraft left tail y pos;
    double theta;
    QString stemp;

  public slots:
    void updatemap();
    void slotzoomin();
    void slotzoomout();
    void slotsettrackup();
    void slotsetnorthup();
    void slotselectbgcolor();
    void slotselectaccolor();
    void slotselectllcolor();
    void slotselectrrcolor();
    void slotselectpathcolor();
    void slotselectdicolor();
    void slotselecttarget1color();
    void slotselecttarget2color();
    void slotselecttarget3color();
    void slotselecttarget4color();
    void slotselectwaypointcolor();
    void slotselectpoicolor();
    void slotsett1circles();
    void slotsett1lines();
    void slotsett2circles();
    void slotsett2lines();
    void slotsett3circles();
    void slotsett3lines();
    void slotsett4circles();
    void slotsett4lines();
    void slotsetpathskip(int);
    void slotsett1skip(int);
    void slotsett2skip(int);
    void slotsett3skip(int);
    void slotsett4skip(int);

};

#endif // MAPVIEW_H
