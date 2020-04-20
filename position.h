// $Id: position.h,v 1.3 2004/07/31 13:39:42 sonntag Exp $
#ifndef POSITION_H
#define POSITION_H

#include <qwidget.h>
#include <qstring.h>

class Position
{
//  Q_OBJECT

  public:
    Position(QWidget *parent=0, const char *name=0);
    ~Position();
    void parseinput(QString input,double,double,double,double,double,double);
    QString gettime();
    double getlat();
    double getlon();
    double getht();
    double gethdg();
    double getspd();
    double getroc();
    double gethdgrate();
    double getx();
    double gety();
    double getleader();
    void setleader(double);

  private:
    QString stemp;
    double time,ltime;
    double lat,llat;
    double lon,llon;
    double ht,lht;
    double hdg,lhdg,hdgrate;
    double spd;
    double roc;
    double utmx;
    double utmy;
    double tleader_sec;

};

#endif // POSITION_H
