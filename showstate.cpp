// $Id: showstate.cpp,v 1.5 2005/07/22 20:38:16 sonntag Exp $
//#include <iostream>
//using namespace std;

#include <qfont.h>

#include "showstate.h"


Showstate::Showstate(Position *cur,QWidget *parent,const char *name )
    : QVBox(parent,name )
{
  QFont labfont("Helvetica",14);
  labfont.setPixelSize(11);
  QFont datfont("Helvetica",14,QFont::Bold);
  datfont.setPixelSize(16);
  
  current = cur;
  QLabel *lab1 = new QLabel("Time:",this);
  lab1->setFont(labfont);
  timelab = new QLabel(this);
  timelab->setFont(datfont);
  QLabel *lab2 = new QLabel("Lat (deg):",this);
  lab2->setFont(labfont);
  latlab = new QLabel(this);
  latlab->setFont(datfont);
  QLabel *lab3 = new QLabel("Lon (deg):",this);
  lab3->setFont(labfont);
  lonlab = new QLabel(this);
  lonlab->setFont(datfont);
  QLabel *lab4 = new QLabel("Altitude (ft):",this);
  lab4->setFont(labfont);
  htlab = new QLabel(this);
  htlab->setFont(datfont);
  QLabel *lab5 = new QLabel("True Trk (deg):",this);
  lab5->setFont(labfont);
  hdglab = new QLabel(this);
  hdglab->setFont(datfont);
  QLabel *lab6 = new QLabel("Gndspd (knots):",this);
  lab6->setFont(labfont);
  spdlab = new QLabel(this);
  spdlab->setFont(datfont);
  QLabel *lab7 = new QLabel("ROC (ft/min):",this);
  lab7->setFont(labfont);
  roclab = new QLabel(this);
  roclab->setFont(datfont);
}

Showstate::~Showstate()
{
}

void Showstate::update()
{
  char lats,lons;
  int latd,lond;
  double lat,lon,latm,lonm;
  QString latstring,lonstring;

  timelab->setText(current->gettime());
  lat = current->getlat();
  lon = current->getlon();
  if (lat<0.0)
  {
    lats = 'S';
    lat = fabs(lat);
  }
  else
  {
    lats = 'N';
  }
  latd = int(lat);
  latm = 60.0*(lat-double(latd));
  latstring.sprintf("%02d %04.1lf %c",latd,latm,lats);
  if (lon>180.0) lon -= 360.0;
  if (lon<0.0)
  {
    lons = 'W';
    lon = fabs(lon);
  }
  else
  {
    lons = 'E';
  }
  lond = int(lon);
  lonm = 60.0*(lon-double(lond));
  lonstring.sprintf("%03d %04.1lf %c",lond,lonm,lons);
  latlab->setText(latstring);
  lonlab->setText(lonstring);
  htlab->setNum(current->getht());
  hdglab->setNum(current->gethdg());
  spdlab->setNum(current->getspd());
  roclab->setNum(current->getroc());
}

