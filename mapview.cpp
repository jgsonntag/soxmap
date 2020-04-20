// $Id: mapview.cpp,v 1.16 2007/06/22 20:44:42 mitchell Exp $
#include <sys/time.h>
//#include <math.h>
#include <iostream>
using namespace std;

#include <qframe.h>
#include <qcolordialog.h>
#include <qfont.h>

#include "mapview.h"
#include "utility.h"
#include "soxmap.h"    // just because Wright wanted more mods

extern SETTINGS settings;

int TargetWidth = 7;

Mapview::Mapview(coords_ll *flight,coords_ll *target1,coords_ll *target2,
                 coords_ll *target3,coords_ll *target4,wp_ll *waypoint,
                 wp_ll *poi,Position *cur,
                 QWidget *parent,const char *name )
    : QFrame( parent, name )
{
  paint = new QPainter;
  setBackgroundMode(NoBackground);
  //bgcolor = "black";
  //accolor = "white";
  //llcolor = accolor;
  //rrcolor = "yellow";
  //pathcolor = "green";
  //dicolor = "yellow";
  //target1color = QColor(85,255,255);
  //target2color = QColor(255,170,255);
  //target3color = QColor(255,170,0);
  //target4color = QColor(170,170,255);
  flightpath = flight;
  target1path = target1;
  target2path = target2;
  target3path = target3;
  target4path = target4;
  wppath = waypoint;
  poipath = poi;
  current = cur;

  // Initialize the zoom levels
  zoom[ 0] =    0.1;
  zoom[ 1] =    0.2;
  zoom[ 2] =    0.3;
  zoom[ 3] =    0.5;
  zoom[ 4] =    1.0;
  zoom[ 5] =    2.0;
  zoom[ 6] =    3.0;
  zoom[ 7] =    5.0;
  zoom[ 8] =   10.0;
  zoom[ 9] =   20.0;
  zoom[10] =   30.0;
  zoom[11] =   50.0;
  zoom[12] =  100.0;
  zoom[13] =  200.0;
  zoom[14] =  300.0;
  zoom[15] =  500.0;
  zoom[16] = 1000.0;
  currentzoom = 4;

  // Leader line initialization
  tleader_sec = 15.0;
  leader = new coords_ll();

  if ( settings.mode == EAARL )
    TargetWidth = 7;

  // Target drawing style initialization
  t1circles = true;
  t2circles = true;
  t3circles = true;
  t4circles = true;

}

Mapview::~Mapview()
{
  delete paint;
}


void Mapview::updatemap()
{
  update();
}


QColor Mapview::getbgcolor()
{
  return(bgcolor);
}


void Mapview::setbgcolor(QColor color)
{
  bgcolor = color;
}


QColor Mapview::getaccolor()
{
  return(accolor);
}


void Mapview::setaccolor(QColor color)
{
  accolor = color;
}


QColor Mapview::getllcolor()
{
  return(llcolor);
}


void Mapview::setllcolor(QColor color)
{
  llcolor = color;
}


QColor Mapview::getrrcolor()
{
  return(rrcolor);
}


void Mapview::setrrcolor(QColor color)
{
  rrcolor = color;
}


QColor Mapview::getpathcolor()
{
  return(pathcolor);
}


void Mapview::setpathcolor(QColor color)
{
  pathcolor = color;
}


QColor Mapview::getdicolor()
{
  return(dicolor);
}


void Mapview::setdicolor(QColor color)
{
  dicolor = color;
}


QColor Mapview::gett1color()
{
  return(target1color);
}


void Mapview::sett1color(QColor color)
{
  target1color = color;
}


QColor Mapview::gett2color()
{
  return(target2color);
}


void Mapview::sett2color(QColor color)
{
  target2color = color;
}


QColor Mapview::gett3color()
{
  return(target3color);
}


void Mapview::sett3color(QColor color)
{
  target3color = color;
}


QColor Mapview::gett4color()
{
  return(target4color);
}


void Mapview::sett4color(QColor color)
{
  target4color = color;
}


QColor Mapview::getwpcolor()
{
  return(waypointcolor);
}


void Mapview::setwpcolor(QColor color)
{
  waypointcolor = color;
}


QColor Mapview::getpoicolor()
{
  return(poicolor);
}


void Mapview::setpoicolor(QColor color)
{
  poicolor = color;
}


bool Mapview::gett1circles()
{
  return(t1circles);
}


bool Mapview::gett2circles()
{
  return(t2circles);
}


bool Mapview::gett3circles()
{
  return(t3circles);
}


bool Mapview::gett4circles()
{
  return(t4circles);
}


void Mapview::sett1circles(bool circles)
{
  t1circles = circles;
}


void Mapview::sett2circles(bool circles)
{
  t2circles = circles;
}


void Mapview::sett3circles(bool circles)
{
  t3circles = circles;
}


void Mapview::sett4circles(bool circles)
{
  t4circles = circles;
}


void Mapview::slotzoomin()
{
  if (currentzoom>0)
  {
    --currentzoom;
    update();
  }
}


void Mapview::slotzoomout()
{
  if (currentzoom<(NZOOM-1))
  {
    ++currentzoom;
    update();
  }
}

int Mapview::getcurrentzoom()
{
  return(currentzoom);
}


void Mapview::setcurrentzoom(int zoomlevel)
{
  currentzoom = zoomlevel;
}


int Mapview::getpathskip()
{
  return(pathskip);
}

void Mapview::slotsetpathskip(int nskip)
{
  pathskip = nskip;
}


int Mapview::gett1skip()
{
  return(t1skip);
}

void Mapview::slotsett1skip(int nskip)
{
  t1skip = nskip;
}


int Mapview::gett2skip()
{
  return(t2skip);
}

void Mapview::slotsett2skip(int nskip)
{
  t2skip = nskip;
}


int Mapview::gett3skip()
{
  return(t3skip);
}

void Mapview::slotsett3skip(int nskip)
{
  t3skip = nskip;
}


int Mapview::gett4skip()
{
  return(t4skip);
}

void Mapview::slotsett4skip(int nskip)
{
  t4skip = nskip;
}


void Mapview::slotsettrackup()
{
  trackup = true;
  acxp = (int)(width()/2.0);
  if ( settings.mode == ATM ) 
    acyp = (int)(height()*3.0/ 4.0);
  else               // EAARL
    acyp = (int)(height()*9.0/10.0);
  update();
}


void Mapview::slotsetnorthup()
{
  trackup = false;
  acxp = (int)(width()/2.0);
  acyp = (int)(height()/2.0);
  update();
}


bool Mapview::gettrackup()
{
  return(trackup);
}


void Mapview::paintEvent(QPaintEvent *)
{
  int xtick,itemp2;
  timeval time1,time2;
  bool my_trackup;
  //double dtemp1,dtemp2;

  // adjust trackup according to spd
  my_trackup = trackup;
  trackup = (current->getspd() > 10) ? trackup : !trackup;

  // Begin timing the redraw
  gettimeofday(&time1,NULL);

  // Set up an off-screen drawing buffer and paint to it
  QPixmap *drawbuffer = new QPixmap(width(),height());
  paint->begin(drawbuffer,this);

  // Fill the buffer with the background color
  paint->fillRect(0,0,width(),height(),QBrush(bgcolor,SolidPattern));

  // Compute the scale factors
  spixpnm = height()/(2.0*zoom[currentzoom]);
  spixpm  = spixpnm/1852.0;

  // Compute the angle distortion due to map projection
  get_angle_distortion(leader);

  // Draw the flightpath
  paint->setPen(QPen(pathcolor,1,QPen::SolidLine));
  drawcoords(flightpath,pathskip);

  // Draw the targets
  paint->setPen(QPen(target1color,1,QPen::SolidLine));
  if (t1circles)
    drawcoords(target1path,t1skip);
  else
  {
    paint->setPen(QPen(target1color,TargetWidth,QPen::SolidLine));
    drawlines(target1path);
  }
  paint->setPen(QPen(target2color,1,QPen::SolidLine));
  if (t2circles)
    drawcoords(target2path,t2skip);
  else
  {
    paint->setPen(QPen(target2color,TargetWidth,QPen::SolidLine));
    drawlines(target2path);
  }
  paint->setPen(QPen(target3color,1,QPen::SolidLine));
  if (t3circles)
    drawcoords(target3path,t3skip);
  else
  {
    paint->setPen(QPen(target3color,TargetWidth,QPen::SolidLine));
    drawlines(target3path);
  }
  paint->setPen(QPen(target4color,1,QPen::SolidLine));
  if (t4circles)
    drawcoords(target4path,t4skip);
  else
  {
    paint->setPen(QPen(target4color,TargetWidth,QPen::SolidLine));
    drawlines(target4path);
  }
  
  // Draw the waypoints
  paint->setPen(QPen(waypointcolor,1,QPen::SolidLine));
  paint->setBrush(QBrush(waypointcolor));
  drawwp(wppath);
  paint->setBrush(QBrush(NoBrush));

  // Draw the points-of-interest
  paint->setPen(QPen(poicolor,1,QPen::SolidLine));
  paint->setBrush(QBrush(poicolor));
  drawwp(poipath);
  paint->setBrush(QBrush(NoBrush));

  // Draw the airplane symbol
  paint->setPen(QPen(accolor,4,QPen::SolidLine));
  if (trackup)
  {
    acxf = acxp;
    acyf = acyp-ACLF;
    acxa = acxp;
    acya = acyp+ACLA;
    acxr = acxp+ACLW;
    acyr = acyp;
    acxl = acxp-ACLW;
    acyl = acyp;
    atxr = acxp+ACLT;
    atyr = acyp+ACLA;
    atxl = acxp-ACLT;
    atyl = acyp+ACLA;
  }
  else
  {
    theta = (90.0-current->gethdg()+distort)*PI/180.0;
    acxf = acxp+(int)(ACLF*cos(theta));
    acyf = acyp-(int)(ACLF*sin(theta));
    theta = (270.0-current->gethdg()+distort)*PI/180.0;
    acxa = acxp+(int)(ACLA*cos(theta));
    acya = acyp-(int)(ACLA*sin(theta));
    theta = (180.0-current->gethdg()+distort)*PI/180.0;
    acxr = acxp+(int)(ACLW*cos(theta));
    acyr = acyp-(int)(ACLW*sin(theta));
    atxr = acxa+(int)(ACLT*cos(theta));
    atyr = acya-(int)(ACLT*sin(theta));
    theta = (0.0-current->gethdg()+distort)*PI/180.0;
    acxl = acxp+(int)(ACLW*cos(theta));
    acyl = acyp-(int)(ACLW*sin(theta));
    atxl = acxa+(int)(ACLT*cos(theta));
    atyl = acya-(int)(ACLT*sin(theta));
  }
  paint->drawLine(acxf,acyf,acxa,acya);
  paint->drawLine(acxr,acyr,acxl,acyl);
  paint->drawLine(atxr,atyr,atxl,atyl);

  // Compute and draw the leader line
  //dleader_km = current->getspd()*current->getleader()/3600.0;
  //dleader_km *= 6080.0/M2FT/1000.0;
  //gcproject(current->getlat()*DEG2RAD,current->getlon()*DEG2RAD,
  //          current->gethdg()*DEG2RAD,dleader_km,&ldrlat,&ldrlon);
  lati = current->getlat()*DEG2RAD;
  loni = current->getlon()*DEG2RAD;
  hdgi = current->gethdg()*DEG2RAD;
  ti = 1.0;
  leader->empty();
  leader->add_element(current->getlat(),current->getlon(),0.0,&ddum,&ddum);
  while(ti<=current->getleader())
  {
    dleader_km = current->getspd()*1.0/3600.0;
    dleader_km *= 6080.0/M2FT/1000.0;
    gcproject(lati,loni,hdgi,dleader_km,&newlat,&newlon);
    leader->add_element(newlat/DEG2RAD,newlon/DEG2RAD,0.0,&ddum,&ddum);
    lati = newlat;
    loni = newlon;
    hdgi += (1.0*current->gethdgrate())*DEG2RAD;
    ti += 1.0;
  }
  ldrlat = lati/DEG2RAD;
  ldrlon = loni/DEG2RAD;
  //leader->empty();
  //leader->add_element(current->getlat(),current->getlon(),0.0,&ddum,&ddum);
  //leader->add_element(ldrlat,ldrlon,0.0,&ddum,&ddum);
  paint->setPen(QPen(llcolor,2,QPen::SolidLine));
  drawlines(leader);

  // Draw the range rings
  paint->setPen(QPen(rrcolor,1,QPen::SolidLine));
  int r1 = (int)(height()/2.0);
  int r2 = (int)(r1/2.0);
  paint->drawChord(acxp-r1,acyp-r1,2*r1,2*r1,0,5760);
  paint->drawChord(acxp-r2,acyp-r2,2*r2,2*r2,0,5760);
  //paint->setFont(QFont("Helvetica",8));
  int t1 = acxp+(int)(r1*0.707);
  int t2 = acyp-(int)(r1*0.707);
  if (zoom[currentzoom]<0.99)
    stemp.sprintf("%.1lf nm",zoom[currentzoom]);
  else
    stemp.sprintf("%.0lf nm",zoom[currentzoom]);
  paint->fillRect(t1-10,t2-7,20,14,QBrush(bgcolor,SolidPattern));
  QFont rrfont("Helvetica",14,QFont::Bold);
  rrfont.setPixelSize(12);
  //paint->setFont(QFont("Helvetica",10));
  paint->setFont(rrfont);
  paint->drawText(t1-25,t2-7,50,14,AlignHCenter|AlignVCenter,stemp);
  t1 = acxp-(int)(r1*0.707);
  paint->fillRect(t1-10,t2-7,20,14,QBrush(bgcolor,SolidPattern));
  paint->drawText(t1-25,t2-7,50,14,AlignHCenter|AlignVCenter,stemp);

  // Draw the direction indicator (compass)
  paint->setPen(QPen(dicolor,1,QPen::SolidLine));
  //paint->setFont(QFont("Helvetica",10));
  QFont difont("Helvetica",14,QFont::Normal);
  difont.setPixelSize(11);
  if (trackup)
  {
    theta = atan2(2.0*width(),3.0*height())*180.0/PI;
    double thetamin = current->gethdg()-theta;
    double thetamax = current->gethdg()+theta;
    double spixpdeg = width()/(thetamax-thetamin);
    int itemp = (int)(thetamin/2.0);
    while (itemp*2<=thetamax)
    {
      xtick = (int)((itemp*2-thetamin)*spixpdeg);
      if ( (double)((int)(itemp/5)) == (double)(itemp)/5.0)
      {
        paint->drawLine(xtick,0,xtick,10);
	itemp2 = itemp*2;
	if (itemp2<0) itemp2+=360;
	else if (itemp2>359) itemp2-=360;
        stemp.sprintf("%03d",itemp2);
        //paint->fillRect(t1-25,t2-7,50,14,QBrush(bgcolor,SolidPattern));
        paint->drawText(xtick-10,12,20,14,AlignHCenter|AlignVCenter,stemp);
      }
      else
        paint->drawLine(xtick,0,xtick,5);
      ++itemp;
    }
    QFont hdgfont("Helvetica",14,QFont::Bold);
    hdgfont.setPixelSize(16);
    paint->setFont(hdgfont);
    paint->fillRect(width()/2-30,30,60,20,QBrush(bgcolor,SolidPattern));
    paint->drawRect(width()/2-30,30,60,20);
    paint->drawLine(width()/2,0,width()/2,30);
    stemp.sprintf("%5.1lf ",current->gethdg());
    paint->setPen(QPen(accolor,1,QPen::SolidLine));
    paint->drawText(width()/2-30,30,60,20,AlignHCenter|AlignVCenter,stemp);
  }

  // Finish timing the redraw
  paint->setFont(QFont("Helvetica",8));
  paint->setPen(QPen("blue",1,QPen::SolidLine));
  gettimeofday(&time2,NULL);
  double tdiff = 1.0e6*(time2.tv_sec-time1.tv_sec)
                 + (double)(time2.tv_usec-time1.tv_usec);
  stemp.sprintf("%.2lf ms redraw\n%5.1lf cent mer\n%6.2lf deg distortion",
                tdiff/1000.0,LON0,distort);
//  paint->drawText(width()-155,height()-100,150,75,
//                  AlignRight|AlignVCenter,stemp);
  paint->drawText(10,height()-100,150,75,
                  AlignLeft|AlignTop,stemp);
  if (PROJ==0) stemp.sprintf("north polar stereographic\n");
  else if (PROJ==1) stemp.sprintf("mercator, cent mer=%5.1lf\n",LON0);
  else if (PROJ==2) stemp.sprintf("south polar stereographic\n");
  paint->drawText(10,height()-30,150,75,AlignLeft|AlignTop,stemp);

  // Done painting
  paint->end();

  // Copy the offscreen buffer to the onscreen widget
  bitBlt(this,0,0,drawbuffer);
  delete drawbuffer;

  // Reset trackup
  trackup = my_trackup;

}


void Mapview::drawwp(wp_ll *coords)
{
  int dxpix,dypix,xpix,ypix;
  double xa,ya,dx,dy,dx1,dy1,spd;
  QString name;

  coords->go_to_top();
  double theta = (-current->gethdg()+distort)*PI/180.0;
  double ctheta = cos(theta);
  double stheta = sin(theta);
  while (coords->get_next_element(&name,&xa,&ya,&spd))
  {
    dx = xa-current->getx();
    dy = ya-current->gety();
    if (trackup)
    {
      dx1 =  ctheta*dx+stheta*dy;
      dy1 = -stheta*dx+ctheta*dy;
      dx = dx1;
      dy = dy1;
    }
    dxpix = (int)(dx*spixpm);
    dypix = (int)(dy*spixpm);
    xpix = acxp+dxpix;
    ypix = acyp-dypix;
    paint->drawRoundRect(xpix-5,ypix-5,10,10,62,62);
    QFont wpfont("Helvetica",10,QFont::Bold,true);
    wpfont.setPixelSize(16);
    //paint->setFont(QFont("Helvetica",10,QFont::Bold,true));
    paint->setFont(wpfont);
    paint->drawText(xpix+5,ypix-5,name);
  }

}


void Mapview::drawlines(coords_ll *coords)
{
  int dxpix,dypix,xpix,ypix,lastxpix,lastypix;
  double xa,ya,dx,dy,dx1,dy1,wswath;
  double rawx;
  coords->go_to_top();
  double theta = (-current->gethdg()+distort)*PI/180.0;
  double ctheta = cos(theta);
  double stheta = sin(theta);
  lastxpix = -999; lastypix = -999;
  while (coords->get_next_element(&xa,&ya,&wswath))
  {
    rawx = xa;
    dx = xa-current->getx();
    dy = ya-current->gety();
    if (trackup)
    {
      dx1 =  ctheta*dx+stheta*dy;
      dy1 = -stheta*dx+ctheta*dy;
      dx = dx1;
      dy = dy1;
    }
    dxpix = (int)(dx*spixpm);
    dypix = (int)(dy*spixpm);
    xpix = acxp+dxpix;
    ypix = acyp-dypix;
    if ( rawx > -19.0e6 ) {
      if (lastxpix != -999 )
        paint->drawLine(lastxpix,lastypix,xpix,ypix);
      lastxpix = xpix;
      lastypix = ypix;
    } else
      lastxpix = -999;
  }

}


void Mapview::get_angle_distortion(coords_ll *coords)
{
  double xpix,ypix,dxpix,dypix,xa,ya,dx,dy,dx1,dy1;
  double lastxpix,lastypix,wswath,delx,dely;

  // Populate a 2-element linked list with current position and 
  // projected leader-line position as the two member elements
  dleader_km = current->getspd()*current->getleader()/3600.0;
  dleader_km *= 6080.0/M2FT/1000.0;
  gcproject(current->getlat()*DEG2RAD,current->getlon()*DEG2RAD,
            current->gethdg()*DEG2RAD,dleader_km,&ldrlat,&ldrlon);
  ldrlat /= DEG2RAD;
  ldrlon /= DEG2RAD;
  leader->empty();
  leader->add_element(current->getlat(),current->getlon(),0.0,&ddum,&ddum);
  leader->add_element(ldrlat,ldrlon,0.0,&ddum,&ddum);

  // Map the elements of the linked-list to screen coords and
  // compute the resulting distortion angle
  coords->go_to_top();
  double theta = -current->gethdg()*PI/180.0;
  double ctheta = cos(theta);
  double stheta = sin(theta);
  lastxpix = -999; lastypix = -999;
  while (coords->get_next_element(&xa,&ya,&wswath))
  {
    dx = xa-current->getx();
    dy = ya-current->gety();
    dx1 =  ctheta*dx+stheta*dy;
    dy1 = -stheta*dx+ctheta*dy;
    dx = dx1;
    dy = dy1;
    dxpix = dx*spixpm;
    dypix = dy*spixpm;
    xpix = acxp+dxpix;
    ypix = acyp-dypix;
    if (lastxpix != -999 )
    {

      // Angle distortion is computed here as the angle between a screen
      // vertical line and a leader line drawn in track-up coordinates, which
      // would be zero if there were no distortion
      delx = xpix-lastxpix;
      dely = ypix-lastypix;
      distort = 180.0*atan2(dely,delx)/PI;
      distort = 90.0-distort;
    }
    lastxpix = xpix;
    lastypix = ypix;
  }

}


void Mapview::drawcoords(coords_ll *coords,int nskip)
{
  int dxpix,dypix,xpix,ypix,rswathpix,count;
  double xa,ya,dx,dy,dx1,dy1,wswath;

  coords->go_to_top();
  double theta = (-current->gethdg()+distort)*PI/180.0;
  double ctheta = cos(theta);
  double stheta = sin(theta);
  count = 1;
  while (coords->get_next_element(&xa,&ya,&wswath))
  {
    if (count == nskip)
    {
      count = 1;
      double rswath = wswath/2.0;
      dx = xa-current->getx();
      dy = ya-current->gety();
      if (fabs(dx)<(2.0*1852*zoom[currentzoom])&&
          fabs(dy)<(2.0*1852*zoom[currentzoom]))
      {
        if (trackup)
        {
          dx1 =  ctheta*dx+stheta*dy;
          dy1 = -stheta*dx+ctheta*dy;
          dx = dx1;
          dy = dy1;
        }
        dxpix = (int)(dx*spixpm);
        dypix = (int)(dy*spixpm);
        xpix = acxp+dxpix;
        ypix = acyp-dypix;
        rswathpix = (int)(rswath*spixpm);
        if (rswathpix<=0) rswathpix = 1;
        paint->drawChord(xpix-rswathpix,ypix-rswathpix,2*rswathpix,2*rswathpix,
	                 0,5760);
      }
    }
    else
      ++count;
  }

}


void Mapview::slotselectbgcolor()
{
  bgcolor = QColorDialog::getColor(bgcolor,this);
}


void Mapview::slotselectaccolor()
{
  accolor = QColorDialog::getColor(accolor,this);
}


void Mapview::slotselectllcolor()
{
  llcolor = QColorDialog::getColor(llcolor,this);
}


void Mapview::slotselectrrcolor()
{
  rrcolor = QColorDialog::getColor(rrcolor,this);
}


void Mapview::slotselectpathcolor()
{
  pathcolor = QColorDialog::getColor(pathcolor,this);
}


void Mapview::slotselectdicolor()
{
  dicolor = QColorDialog::getColor(dicolor,this);
}


void Mapview::slotselecttarget1color()
{
  target1color = QColorDialog::getColor(target1color,this);
}


void Mapview::slotselecttarget2color()
{
  target2color = QColorDialog::getColor(target2color,this);
}


void Mapview::slotselecttarget3color()
{
  target3color = QColorDialog::getColor(target3color,this);
}


void Mapview::slotselecttarget4color()
{
  target4color = QColorDialog::getColor(target4color,this);
}


void Mapview::slotselectwaypointcolor()
{
  waypointcolor = QColorDialog::getColor(waypointcolor,this);
}


void Mapview::slotselectpoicolor()
{
  poicolor = QColorDialog::getColor(poicolor,this);
}


void Mapview::slotsett1circles()
{
  t1circles = true;
}


void Mapview::slotsett1lines()
{
  t1circles = false;
}


void Mapview::slotsett2circles()
{
  t2circles = true;
}


void Mapview::slotsett2lines()
{
  t2circles = false;
}


void Mapview::slotsett3circles()
{
  t3circles = true;
}


void Mapview::slotsett3lines()
{
  t3circles = false;
}


void Mapview::slotsett4circles()
{
  t4circles = true;
}


void Mapview::slotsett4lines()
{
  t4circles = false;
}

