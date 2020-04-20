// $Id: position.cpp,v 1.3 2004/07/31 13:39:42 sonntag Exp $
#include <iostream>
using namespace std;

#include <stdlib.h>

#include "position.h"
#include "utility.h"


Position::Position(QWidget *parent,const char *name)
{
  tleader_sec = 15.0;
}

Position::~Position()
{
}

void Position::parseinput(QString input,double time1,double lat1,double lon1,
                          double ht1,double x,double y)
{

  // Determine the message type and parse as appropriate
  time = time1;
  lat = lat1;
  lon = lon1;
  ht  = ht1;
  stemp = input.section(',',0,0);
  if (stemp=="$GPGGA")
  {
    hdg = gccourse1(llat*DEG2RAD,llon*DEG2RAD,
                    lat*DEG2RAD,lon*DEG2RAD)/DEG2RAD;
    spd = 3600.0*RAD2NM*gcdist(llat*DEG2RAD,llon*DEG2RAD,
                    lat*DEG2RAD,lon*DEG2RAD) / (time-ltime);
    roc = 60.0*(ht-lht)/(time-ltime)*M2FT;
    llat = lat;
    llon = lon;
    lht = ht;

    // Compute heading rate
    hdgrate = (hdg-lhdg)/(time-ltime);
    lhdg = hdg;
    ltime = time;
  }
  else if (stemp=="10")
  {
    //stemp = input.section(',',1,1);
    //time  = stemp.toDouble();
    //stemp = input.section(',',2,2);
    //lat   = stemp.toDouble();
    //stemp = input.section(',',3,3);
    //lon   = stemp.toDouble();
    //stemp = input.section(',',4,4);
    //ht    = stemp.toDouble();
    stemp = input.section(',',5,5);
    hdg   = stemp.toDouble();
    stemp = input.section(',',6,6);
    spd   = stemp.toDouble();
    stemp = input.section(',',7,7);
    roc   = stemp.toDouble();

    // Compute heading rate
    hdgrate = (hdg-lhdg)/(time-ltime);
    lhdg = hdg;
    ltime = time;
  }
  else
  {
    cout << "Unrecognized network message type - exiting\n";
    exit(-1);
  }
  utmx = x;
  utmy = y;

  //cout << "heading rate:" << hdgrate << '\n';

}


QString Position::gettime()
{
  double sec = time;
  int dow = (int)(sec/86400.0);
  sec -= dow*86400;
  int hr = (int)(sec/3600.0);
  sec -= hr*3600;
  int min = (int)(sec/60.0);
  sec -= min*60.0;
  stemp.sprintf("%02d:%02d:%02d",hr,min,(int)(sec));
  return(stemp);
}

double Position::getlat()
{
  return(lat);
}



double Position::getlon()
{
  return(lon);
}


double Position::getht()
{
  return(ht);
}


double Position::gethdg()
{
  return(hdg);
}


double Position::getspd()
{
  return(spd);
}


double Position::getroc()
{
  return(roc);
}


double Position::gethdgrate()
{
  return(hdgrate);
}


double Position::getx()
{
  return(utmx);
}


double Position::gety()
{
  return(utmy);
}

double Position::getleader()
{
  return(tleader_sec);
}

void Position::setleader(double ddum)
{
  tleader_sec = ddum;
}
