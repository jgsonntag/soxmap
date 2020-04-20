// $Id: soxgui.cpp,v 1.14 2007/05/13 21:29:31 sonntag Exp $
// Soxgui class implementation
//

#include <qapplication.h>
#include <qmessagebox.h>
#include <qvgroupbox.h>
#include <qvbuttongroup.h>
#include <qradiobutton.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qdatetime.h>
#include <qdir.h>


#include "soxmap.h"
#include "soxgui.h"
#include "setupgui.h"
#include "pathdialog.h"
#include "utility.h"

#include <stdlib.h>

#include <iostream>
using namespace std;

#define SWIDTH 750
#define SHEIGHT 800

int PROJ;
double LON0;
extern SETTINGS settings;

QString filedialog;

enum {
  MapWidth  = 370,
  MapHeight = 500,
};

Soxgui::Soxgui()
{

  // Get the saved user settings
  gpshost = usettings.readEntry("/soxmap/network/gpshost","localhost");
  gpsport = (Q_UINT16)(usettings.readNumEntry("/soxmap/network/gpsport",4040));
  gpscmd = usettings.readEntry("/soxmap/network/gpscmd","gga1hzstream");
  swathwidth = usettings.readDoubleEntry("/soxmap/map/swathwidth",180.0);
  double tleader_sec = usettings.readDoubleEntry("/soxmap/map/tleader_sec",
                                                 15.0);
  bool maporient = usettings.readBoolEntry("/soxmap/map/trackup",true);
  int currentzoom = usettings.readNumEntry("/soxmap/map/currentzoom",4);
  bool t1style = usettings.readBoolEntry("/soxmap/map/t1circles",true);
  bool t2style = usettings.readBoolEntry("/soxmap/map/t2circles",true);
  bool t3style = usettings.readBoolEntry("/soxmap/map/t3circles",true);
  bool t4style = usettings.readBoolEntry("/soxmap/map/t4circles",true);
  int pathskip = usettings.readNumEntry("/soxmap/map/pathskip",1);
  int t1skip = usettings.readNumEntry("/soxmap/map/t1skip",1);
  int t2skip = usettings.readNumEntry("/soxmap/map/t2skip",1);
  int t3skip = usettings.readNumEntry("/soxmap/map/t3skip",1);
  int t4skip = usettings.readNumEntry("/soxmap/map/t4skip",1);
  QColor bgcolor = readcolor("bgcolor","black");
  QColor accolor = readcolor("accolor","white");
  QColor llcolor = readcolor("llcolor","white");
  QColor rrcolor = readcolor("rrcolor","yellow");
  QColor pathcolor = readcolor("pathcolor","green");
  QColor dicolor = readcolor("dicolor","yellow");
  QColor t1color = readcolor("t1color","cyan");
  QColor t2color = readcolor("t2color","magenta");
  QColor t3color = readcolor("t3color","yellow");
  QColor t4color = readcolor("t4color","gray");
  QColor wpcolor = readcolor("wpcolor","white");
  QColor poicolor = readcolor("poicolor","yellow");
  logfile = usettings.readEntry("/soxmap/files/logfile","");
  target1name = usettings.readEntry("/soxmap/files/target1name","");
  target2name = usettings.readEntry("/soxmap/files/target2name","");
  target3name = usettings.readEntry("/soxmap/files/target3name","");
  target4name = usettings.readEntry("/soxmap/files/target4name","");
  wpname = usettings.readEntry("/soxmap/files/wpname","");
  poiname = usettings.readEntry("/soxmap/files/poiname","");

  // Size the window
  if (settings.mode==ATM)
    setFixedSize(SWIDTH,SHEIGHT);
  else
    setFixedSize(MapWidth,MapHeight);

  // Get network settings from user
  Setupgui *setup = new Setupgui(&gpshost,&gpsport,&gpscmd,this);
  while (setup->exec() == QDialog::Rejected)
  {
    QMessageBox::warning(this,"Invalid\n","Port number is invalid\n");
  }
  if (!gpscmd.contains('\n'))
    gpscmd.append('\n');

  // Set the background flags;
  target1flag = false;
  target2flag = false;
  target3flag = false;
  target4flag = false;
  wpflag = false;
  poiflag = false;

  // Construct linked lists for the coordinates
  flight = new coords_ll();
  target1 = new coords_ll();
  target2 = new coords_ll();
  target3 = new coords_ll();
  target4 = new coords_ll();
  waypoint = new wp_ll();
  poi = new wp_ll();

  // Construct the current position class;
  current = new Position();
  current->setleader(tleader_sec);

  // Build the main menubar and make connections
  mainmenu = new QMenuBar(this);
  filemenu = new QPopupMenu(mainmenu);
  QPopupMenu *mapmenu = new QPopupMenu(mainmenu);
  QPopupMenu *helpmenu = new QPopupMenu(mainmenu);

  // Build the map display
  map = new Mapview(flight,target1,target2,target3,target4,waypoint,
                    poi,current,this);
  if (settings.mode==ATM)
    map->setGeometry(0,mainmenu->height(),SWIDTH-140,SHEIGHT-mainmenu->height());
  else
    map->setGeometry(0,mainmenu->height(),MapWidth,MapHeight-mainmenu->height());
  map->setcurrentzoom(currentzoom);
  map->setbgcolor(bgcolor);
  map->setaccolor(accolor);
  map->setllcolor(llcolor);
  map->setrrcolor(rrcolor);
  map->setpathcolor(pathcolor);
  map->setdicolor(dicolor);
  map->sett1color(t1color);
  map->sett2color(t2color);
  map->sett3color(t3color);
  map->sett4color(t4color);
  map->setwpcolor(wpcolor);
  map->setpoicolor(poicolor);
  map->sett1circles(t1style);
  map->sett2circles(t2style);
  map->sett3circles(t3style);
  map->sett4circles(t4style);
  map->slotsetpathskip(pathskip);
  map->slotsett1skip(t1skip);
  map->slotsett2skip(t2skip);
  map->slotsett3skip(t3skip);
  map->slotsett4skip(t4skip);

  // Build the File menu
  idt1 = filemenu->insertItem("Open Target1 file",this,SLOT(slotTarget1()));
  idt2 = filemenu->insertItem("Open Target2 file",this,SLOT(slotTarget2()));
  idt3 = filemenu->insertItem("Open Target3 file",this,SLOT(slotTarget3()));
  idt4 = filemenu->insertItem("Open Target4 file",this,SLOT(slotTarget4()));
  idwp = filemenu->insertItem("Open Waypoint file",this,SLOT(slotWPFile()));
  idpoi = filemenu->insertItem("Open Points-of-Interest file",this,
                               SLOT(slotPOIFile()));
  filemenu->insertItem("Quit",qApp,SLOT(quit()));

  // Build the Map menu
  QPopupMenu *orientmenu = new QPopupMenu(mapmenu);
  QVButtonGroup *orientgroup = new QVButtonGroup(orientmenu);
  QRadioButton *northup = new QRadioButton("North up",orientgroup);
  QRadioButton *trackup = new QRadioButton("Track up",orientgroup);
  //trackup->setChecked(true);
  orientmenu->insertItem(orientgroup);
  mapmenu->insertItem("Map orientation",orientmenu);
  if (maporient)
  {
    map->slotsettrackup();
    trackup->setChecked(true);
  }
  else
  {
    map->slotsetnorthup();
    northup->setChecked(true);
  }
  QPopupMenu *colormenu = new QPopupMenu(mapmenu);
  colormenu->insertItem("Map background color",map,SLOT(slotselectbgcolor()));
  colormenu->insertItem("Aircraft symbol color",map,SLOT(slotselectaccolor()));
  colormenu->insertItem("Leader line color",map,SLOT(slotselectllcolor()));
  colormenu->insertItem("Range rings color",map,SLOT(slotselectrrcolor()));
  colormenu->insertItem("Flightpath color",map,SLOT(slotselectpathcolor()));
  colormenu->insertItem("Compass color",map,SLOT(slotselectdicolor()));
  colormenu->insertItem("Target1 color",map,SLOT(slotselecttarget1color()));
  colormenu->insertItem("Target2 color",map,SLOT(slotselecttarget2color()));
  colormenu->insertItem("Target3 color",map,SLOT(slotselecttarget3color()));
  colormenu->insertItem("Target4 color",map,SLOT(slotselecttarget4color()));
  colormenu->insertItem("Waypoint color",map,SLOT(slotselectwaypointcolor()));
  colormenu->insertItem("Points-of-interest color",map,
                        SLOT(slotselectpoicolor()));
  mapmenu->insertItem("Color selectors",colormenu);
  QPopupMenu *tstylemenu = new QPopupMenu(mapmenu);
  QPopupMenu *t1stylemenu = new QPopupMenu(tstylemenu);
  QVButtonGroup *t1stylegroup = new QVButtonGroup(t1stylemenu);
  QRadioButton *t1circles = new QRadioButton("Circles",t1stylegroup);
  QRadioButton *t1lines = new QRadioButton("Lines",t1stylegroup);
  if (t1style)
    t1circles->setChecked(true);
  else
    t1lines->setChecked(true);
  t1stylemenu->insertItem(t1stylegroup);
  tstylemenu->insertItem("Target1 style",t1stylemenu);
  QPopupMenu *t2stylemenu = new QPopupMenu(tstylemenu);
  QVButtonGroup *t2stylegroup = new QVButtonGroup(t2stylemenu);
  QRadioButton *t2circles = new QRadioButton("Circles",t2stylegroup);
  QRadioButton *t2lines = new QRadioButton("Lines",t2stylegroup);
  if (t2style)
    t2circles->setChecked(true);
  else
    t2lines->setChecked(true);
  t2stylemenu->insertItem(t2stylegroup);
  tstylemenu->insertItem("Target2 style",t2stylemenu);
  QPopupMenu *t3stylemenu = new QPopupMenu(tstylemenu);
  QVButtonGroup *t3stylegroup = new QVButtonGroup(t3stylemenu);
  QRadioButton *t3circles = new QRadioButton("Circles",t3stylegroup);
  QRadioButton *t3lines = new QRadioButton("Lines",t3stylegroup);
  if (t3style)
    t3circles->setChecked(true);
  else
    t3lines->setChecked(true);
  t3stylemenu->insertItem(t3stylegroup);
  tstylemenu->insertItem("Target3 style",t3stylemenu);
  QPopupMenu *t4stylemenu = new QPopupMenu(tstylemenu);
  QVButtonGroup *t4stylegroup = new QVButtonGroup(t4stylemenu);
  QRadioButton *t4circles = new QRadioButton("Circles",t4stylegroup);
  QRadioButton *t4lines = new QRadioButton("Lines",t4stylegroup);
  if (t4style)
    t4circles->setChecked(true);
  else
    t4lines->setChecked(true);
  t4stylemenu->insertItem(t4stylegroup);
  tstylemenu->insertItem("Target4 style",t4stylemenu);
  mapmenu->insertItem("Target drawing styles",tstylemenu);
  mapmenu->insertItem("Set swath width",this,SLOT(slotSetSwathWidth()));
  mapmenu->insertItem("Select leader line length",this,SLOT(slotSetLeader()));
  QPopupMenu *thinmenu = new QPopupMenu(mapmenu);
  QPopupMenu *paththinmenu = new QPopupMenu(thinmenu);
  QSpinBox *paththinsb = new QSpinBox(1,10,1,paththinmenu);
  paththinsb->setValue(pathskip);
  paththinmenu->insertItem(paththinsb);
  thinmenu->insertItem("Current path thinning",paththinmenu);
  QPopupMenu *t1thinmenu = new QPopupMenu(thinmenu);
  QSpinBox *t1thinsb = new QSpinBox(1,10,1,t1thinmenu);
  t1thinsb->setValue(t1skip);
  t1thinmenu->insertItem(t1thinsb);
  thinmenu->insertItem("Target1 thinning",t1thinmenu);
  QPopupMenu *t2thinmenu = new QPopupMenu(thinmenu);
  QSpinBox *t2thinsb = new QSpinBox(1,10,1,t2thinmenu);
  t2thinsb->setValue(t2skip);
  t2thinmenu->insertItem(t2thinsb);
  thinmenu->insertItem("Target2 thinning",t2thinmenu);
  QPopupMenu *t3thinmenu = new QPopupMenu(thinmenu);
  QSpinBox *t3thinsb = new QSpinBox(1,10,1,t3thinmenu);
  t3thinsb->setValue(t3skip);
  t3thinmenu->insertItem(t3thinsb);
  thinmenu->insertItem("Target3 thinning",t3thinmenu);
  QPopupMenu *t4thinmenu = new QPopupMenu(thinmenu);
  QSpinBox *t4thinsb = new QSpinBox(1,10,1,t4thinmenu);
  t4thinsb->setValue(t4skip);
  t4thinmenu->insertItem(t4thinsb);
  thinmenu->insertItem("Target4 thinning",t4thinmenu);
  mapmenu->insertItem("Display thinning",thinmenu);

  // Build the Help menu
  helpmenu->insertItem("About",this,SLOT(about()));

  if (settings.mode==EAARL)
    filedialog = "SOX (*.latlon *_sox.log);;latlon (*.latlon);; SOXMap log (*_sox.log);;All (*.*)";
  else
    filedialog = "latlon (*.latlon);; SOXMap log (*_sox.log);;All (*.*)";

  // Finish building the main menu
  mainmenu->insertItem("File",filemenu);
  mainmenu->insertItem("Map",mapmenu);
  if (settings.mode==EAARL)
  {
    mainmenu->insertItem("Zoom:In",map,SLOT(slotzoomin()));
    mainmenu->insertItem("Zoom:Out",map,SLOT(slotzoomout()));
  }
  mainmenu->insertItem("Help",helpmenu);

  // Build the state vector readout
  if (settings.mode==ATM)
  {
    QVGroupBox *currbox = new QVGroupBox(this);
    currbox->setGeometry(SWIDTH-130,mainmenu->height(),120,SHEIGHT-160);
    state = new Showstate(current,currbox);
  }

  // Build the zoom buttons
  if (settings.mode==ATM)
  {
    zoomin  = new QPushButton("Zoom In",this);
    zoomin->setGeometry(SWIDTH-130,mainmenu->height()+SHEIGHT-160,120,60);
    connect(zoomin,SIGNAL(clicked()),map,SLOT(slotzoomin()));
    zoomout = new QPushButton("Zoom Out",this);
    zoomout->setGeometry(SWIDTH-130,mainmenu->height()+SHEIGHT-95,120,60);
    connect(zoomout,SIGNAL(clicked()),map,SLOT(slotzoomout()));
  }

  // Build the network client
  client = new GenericClient(gpshost,gpsport,gpscmd,this);
  connect(client,SIGNAL(gotaline(QString)),this,SLOT(slotFirstGPS(QString)));

  // Connect remaining signals and slots
  connect(trackup,SIGNAL(clicked()),map,SLOT(slotsettrackup()));
  connect(northup,SIGNAL(clicked()),map,SLOT(slotsetnorthup()));
  connect(t1circles,SIGNAL(clicked()),map,SLOT(slotsett1circles()));
  connect(t1lines,SIGNAL(clicked()),map,SLOT(slotsett1lines()));
  connect(t2circles,SIGNAL(clicked()),map,SLOT(slotsett2circles()));
  connect(t2lines,SIGNAL(clicked()),map,SLOT(slotsett2lines()));
  connect(t3circles,SIGNAL(clicked()),map,SLOT(slotsett3circles()));
  connect(t3lines,SIGNAL(clicked()),map,SLOT(slotsett3lines()));
  connect(t4circles,SIGNAL(clicked()),map,SLOT(slotsett4circles()));
  connect(t4lines,SIGNAL(clicked()),map,SLOT(slotsett4lines()));
  connect(paththinsb,SIGNAL(valueChanged(int)),map,SLOT(slotsetpathskip(int)));
  connect(t1thinsb,SIGNAL(valueChanged(int)),map,SLOT(slotsett1skip(int)));
  connect(t2thinsb,SIGNAL(valueChanged(int)),map,SLOT(slotsett2skip(int)));
  connect(t3thinsb,SIGNAL(valueChanged(int)),map,SLOT(slotsett3skip(int)));
  connect(t4thinsb,SIGNAL(valueChanged(int)),map,SLOT(slotsett4skip(int)));

}


Soxgui::~Soxgui()
{

  // Inform user of log file name and path
  cout << "Soxmap log file written to " << logfile << '\n';

  // Close the network connection
  client->closeConnection();

  // Close the path file
  if ( settings.log )
    pathfile->close();

  // Save user settings
  usettings.writeEntry("/soxmap/network/gpshost",gpshost);
  usettings.writeEntry("/soxmap/network/gpsport",gpsport);
  usettings.writeEntry("/soxmap/network/gpscmd",gpscmd);
  usettings.writeEntry("/soxmap/map/swathwidth",swathwidth);
  usettings.writeEntry("/soxmap/map/tleader_sec",current->getleader());
  usettings.writeEntry("/soxmap/map/trackup",map->gettrackup());
  usettings.writeEntry("/soxmap/map/currentzoom",map->getcurrentzoom());
  usettings.writeEntry("/soxmap/map/t1circles",map->gett1circles());
  usettings.writeEntry("/soxmap/map/t2circles",map->gett2circles());
  usettings.writeEntry("/soxmap/map/t3circles",map->gett3circles());
  usettings.writeEntry("/soxmap/map/t4circles",map->gett4circles());
  usettings.writeEntry("/soxmap/map/pathskip",map->getpathskip());
  usettings.writeEntry("/soxmap/map/t1skip",map->gett1skip());
  usettings.writeEntry("/soxmap/map/t2skip",map->gett2skip());
  usettings.writeEntry("/soxmap/map/t3skip",map->gett3skip());
  usettings.writeEntry("/soxmap/map/t4skip",map->gett4skip());
  writecolor("bgcolor",map->getbgcolor());
  writecolor("accolor",map->getaccolor());
  writecolor("llcolor",map->getllcolor());
  writecolor("rrcolor",map->getrrcolor());
  writecolor("pathcolor",map->getpathcolor());
  writecolor("dicolor",map->getdicolor());
  writecolor("t1color",map->gett1color());
  writecolor("t2color",map->gett2color());
  writecolor("t3color",map->gett3color());
  writecolor("t4color",map->gett4color());
  writecolor("wpcolor",map->getwpcolor());
  writecolor("poicolor",map->getpoicolor());
  usettings.writeEntry("/soxmap/files/logfile",logfile);
  usettings.writeEntry("/soxmap/files/target1name",target1name);
  usettings.writeEntry("/soxmap/files/target2name",target2name);
  usettings.writeEntry("/soxmap/files/target3name",target3name);
  usettings.writeEntry("/soxmap/files/target4name",target4name);
  usettings.writeEntry("/soxmap/files/wpname",wpname);
  usettings.writeEntry("/soxmap/files/poiname",poiname);

  // Delete the objects still out there
  delete mainmenu;
  delete client;
  delete flight;
}


QColor Soxgui::readcolor(QString clabel,QString defaultcolor)
{
  QColor ctemp;
  QString stemp = "/soxmap/map/";
  stemp.append(clabel);
  QString stemp2 = stemp + "/red";
  int ired = usettings.readNumEntry(stemp2,-999);
  stemp2 = stemp + "/green";
  int igreen = usettings.readNumEntry(stemp2,-999);
  stemp2 = stemp + "/blue";
  int iblue = usettings.readNumEntry(stemp2,-999);
  if (ired!=-999||igreen!=-999||iblue!=-999)
    ctemp.setRgb(ired,igreen,iblue);
  else
    ctemp.setNamedColor(defaultcolor);
  return(ctemp);

}


void Soxgui::writecolor(QString clabel,QColor color)
{
  QString stemp = "/soxmap/map/";
  stemp.append(clabel);
  QString stemp2 = stemp + "/red";
  usettings.writeEntry(stemp2,color.red());
  stemp2 = stemp + "/green";
  usettings.writeEntry(stemp2,color.green());
  stemp2 = stemp + "/blue";
  usettings.writeEntry(stemp2,color.blue());
}


void Soxgui::ingest_latlon(QFile *infile, coords_ll *coords)
{
  const char *sline;
  double dtemp1,dtemp2,dtemp3,x,y;
  QString line;

  infile->open(IO_ReadOnly);
  QTextStream instream(infile);
  while (!instream.atEnd())
  {
    line = instream.readLine();
    sline = line.latin1();
    // if the line length is 0, pretend we got a -999 flag value
    if ( line.length() > 0 ) {
      sscanf(sline,"%lf %lf %lf ",&dtemp1,&dtemp2,&dtemp3);
    } else {
      dtemp1 = dtemp2 = -999.0;
    }
    coords->add_element(dtemp1,dtemp2,dtemp3*FT2M,&x,&y);
  }
  infile->close();
}


void Soxgui::ingest_waypoint(QFile *infile, wp_ll *coords)
{
  const char *sline;
  char stemp[15];
  double dtemp1,dtemp2,dtemp3,x,y;
  QString line;

  infile->open(IO_ReadOnly);
  QTextStream instream(infile);
  while (!instream.atEnd())
  {
    line = instream.readLine();
    sline = line.latin1();
    sscanf(sline,"%s %lf %lf %lf",stemp,&dtemp2,&dtemp3,&dtemp1);
    coords->add_element(stemp,dtemp2,dtemp3,double(0.0),&x,&y);
  }
  infile->close();
}


void Soxgui::slotFirstGPS(QString gps)
{

  // Disconnect this slot - we only want to invoke it once!
  disconnect(client,SIGNAL(gotaline(QString)),this,SLOT(slotFirstGPS(QString)));

  // Determine the message type and parse as appropriate
  // This sets the central meridian for the map projection
  stemp = gps.section(',',0,0);
  if (stemp=="$GPGGA")
  {
    parseGGA(gps,&t,&lat,&lon,&ht);
    LON0 = lon;
    if (lat>59.0) PROJ=0;  //north polar stereographic
    else if (lat<=59.0&&lat>=-52.0) PROJ=1;  // mercator
    else PROJ=2;  // south polar stereographic
  }
  else if (stemp=="10")
  {
    stemp2 = gps.section(',',3,3);
    LON0 = stemp2.toDouble();
    stemp2 = gps.section(',',2,2);
    lat = stemp2.toDouble();
    if (lat>59.0) PROJ=0;  //north polar stereographic
    else if (lat<=59.0&&lat>=-52.0) PROJ=1;  // mercator
    else PROJ=2;  // south polar stereographic
  }
  else
  {
    cout << "Unrecognized network message type - exiting\n";
    exit(-1);
  }

  // Check for an existing path file
  QDate qdate = QDate::currentDate(Qt::UTC);
  int qyear = qdate.year();
  qyear -= 100*(int)(qdate.year()/100);
  QTime qtime = QTime::currentTime();

  if ( settings.log ) {
    newlogfile.sprintf("%04d%02d%02d_%02d%02d%02d_soxmap.log",qdate.year(),qdate.month(),
                qdate.day(),qtime.hour(),qtime.minute(),qtime.second());
    if (settings.mode==EAARL) {
      QDir d;
      logpath.sprintf("/data/%04d-%02d-%02d/etc", qdate.year(), qdate.month(), qdate.day());
      d.mkdir(logpath);
      newlogfile.sprintf("%s/%04d%02d%02d_%02d%02d%02d_sox.log",
        logpath.ascii(),
        qdate.year(), qdate.month(), qdate.day(),
        qtime.hour(), qtime.minute(), qtime.second()
      );
    }
    pathfile = new QFile(logfile);
    cout << logfile << "\n";
    if (pathfile->exists())
    {
      Pathdialog *pathsetup = new Pathdialog(logfile,this);
      if (pathsetup->exec() == QDialog::Accepted)
      {
        ingest_latlon(pathfile,flight); // read the file
        pathfile->open(IO_WriteOnly|IO_Append);
      }
      else
      {
        //pathfile->open(IO_WriteOnly);
        logfile = newlogfile;
        pathfile = new QFile(logfile);
        pathfile->open(IO_WriteOnly);
      }
    }
    else
    {
      logfile = newlogfile;
      pathfile = new QFile(logfile);
      pathfile->open(IO_WriteOnly);
    }
    pathstream = new QTextStream(pathfile);
  } else {
  }  // end of creating the log file


  // Now that we have the central meridian set, we can also ingest any
  // previously existing target files
  target1file = new QFile(target1name);
  if (target1file->exists())
  {
    ingest_latlon(target1file,target1);
    target1flag = true;
    stemp = QString("Close Target1 file (");
    stemp.append(target1name);
    stemp.append(")");
    filemenu->changeItem(idt1,stemp);
  }
  target2file = new QFile(target2name);
  if (target2file->exists())
  {
    ingest_latlon(target2file,target2);
    target2flag = true;
    stemp = QString("Close Target2 file (");
    stemp.append(target2name);
    stemp.append(")");
    filemenu->changeItem(idt2,stemp);
  }
  target3file = new QFile(target3name);
  if (target3file->exists())
  {
    ingest_latlon(target3file,target3);
    target3flag = true;
    stemp = QString("Close Target3 file (");
    stemp.append(target3name);
    stemp.append(")");
    filemenu->changeItem(idt3,stemp);
  }
  target4file = new QFile(target4name);
  if (target4file->exists())
  {
    ingest_latlon(target4file,target4);
    target4flag = true;
    stemp = QString("Close Target4 file (");
    stemp.append(target4name);
    stemp.append(")");
    filemenu->changeItem(idt4,stemp);
  }
  wpfile = new QFile(wpname);
  if (wpfile->exists())
  {
    ingest_waypoint(wpfile,waypoint);
    wpflag = true;
    stemp = QString("Close Waypoint file (");
    stemp.append(wpname);
    stemp.append(")");
    filemenu->changeItem(idwp,stemp);
  }
  poifile = new QFile(poiname);
  if (poifile->exists())
  {
    ingest_waypoint(poifile,poi);
    poiflag = true;
    stemp = QString("Close Points-of-Interest file (");
    stemp.append(poiname);
    stemp.append(")");
    filemenu->changeItem(idpoi,stemp);
  }

  // Now connect the network GPS signal with the regular map update etc
  connect(client,SIGNAL(gotaline(QString)),this,SLOT(slotNewGPS(QString)));

}


void Soxgui::parseGGA(QString gga,double *t,double *lat,
                      double *lon,double *ht)
{

  // Get the time
  stemp = gga.section(',',1);
  sec = stemp.toDouble();
  hr = int(sec/10000.0);
  sec = sec-hr*10000.0;
  min = int(sec/100.0);
  sec = sec-min*100.0;
  *t = hr*3600.0+min*60.0+sec;

  // Get the latitude
  stemp = gga.section(',',2);
  latm = stemp.toDouble();
  latd = (int)(latm/100.0);
  latm = latm - (double)(latd)*100.0;
  *lat = (double)(latd)+latm/60.0;
  stemp = gga.section(',',3,3);
  if (stemp.contains('N'))
    *lat *= 1.0;
  else
    *lat *= -1.0;

  // Get the longitude
  stemp = gga.section(',',4);
  lonm = stemp.toDouble();
  lond = (int)(lonm/100.0);
  lonm = lonm - (double)(lond)*100.0;
  *lon = (double)(lond)+lonm/60.0;
  stemp = gga.section(',',5,5);
  if (stemp.contains('E'))
    *lon *= 1.0;
  else
    *lon *= -1.0;
  if (*lon<0.0)
    *lon += 360.0;

  // Get the height
  stemp = gga.section(',',9,9);
  *ht = M2FT*stemp.toDouble();

}


void Soxgui::slotNewGPS(QString gps)
{
  double x,y;

  // Determine the message type and parse as appropriate
  stemp = gps.section(',',0,0);
  if (stemp=="$GPGGA")
  {
    parseGGA(gps,&t,&lat,&lon,&ht);
  }
  else if (stemp=="10")
  {
    stemp1 = gps.section(',',2,2);
    stemp2 = gps.section(',',3,3);
    lat = stemp1.toDouble();
    lon = stemp2.toDouble();
    stemp = gps.section(',',1,1);
    t = stemp.toDouble();
    stemp = gps.section(',',4,4);
    ht = stemp.toDouble();
  }
  else
  {
    cout << "Unrecognized network message type - exiting\n";
    exit(-1);
  }

  // Add to linked-list of positions for this flight
  if ( settings.log ) {
    pathstream->precision(8);
    *pathstream << lat << ' ' << lon << ' ' << swathwidth/FT2M << '\n';
  }
  flight->add_element(lat,lon,swathwidth,&x,&y);
  current->parseinput(gps,t,lat,lon,ht,x,y);
  map->updatemap();
  if (settings.mode==ATM)
    state->update();

}

void Soxgui::slotSetSwathWidth()
{
  bool ok;

  double dtemp = QInputDialog::getDouble("Swath width","Enter swath width (ft)",
                 swathwidth/FT2M,0.0,5000.0,0,&ok,this);
  if (ok)
    swathwidth = dtemp*FT2M;
}

void Soxgui::slotSetLeader()
{
  bool ok;

  double dtemp = QInputDialog::getDouble("Leader line",
                 "Enter leader line length (sec)",
                 current->getleader(),0.0,5000.0,0,&ok,this);
  if (ok)
    current->setleader(dtemp);
}


void Soxgui::slotTarget1()
{

  // If target file not already open, allow user to open one
  if (!target1flag)
  {
    target1name = QFileDialog::getOpenFileName(".",
                  filedialog,
                  this,"target1","Select a Target 1 file");
    target1file = new QFile(target1name);
    if (target1file->exists())
    {
      if (target1flag)
        target1->empty();
      ingest_latlon(target1file,target1);
      target1flag = true;
      stemp = QString("Close Target1 file (");
      stemp.append(target1name);
      stemp.append(")");
      filemenu->changeItem(idt1,stemp);
    }
    //delete target1file;
  }

  // Otherwise null the target1 list
  else
  {
    target1->empty();
    target1flag = false;
    filemenu->changeItem(idt1,"Open Target1 file");
    target1name = "";
  }

}


void Soxgui::slotTarget2()
{

  // If target file not already open, allow user to open one
  if (!target2flag)
  {
    target2name = QFileDialog::getOpenFileName(".",
                       filedialog,
                       this,"target2","Select a Target 2 file");
    target2file = new QFile(target2name);
    if (target2file->exists())
    {
      if (target2flag)
        target2->empty();
      ingest_latlon(target2file,target2);
      target2flag = true;
      stemp = QString("Close Target2 file (");
      stemp.append(target2name);
      stemp.append(")");
      filemenu->changeItem(idt2,stemp);
    }
    //delete target2file;
  }

  // Otherwise null the target2 list
  else
  {
    target2->empty();
    target2flag = false;
    filemenu->changeItem(idt2,"Open Target2 file");
    target2name = "";
  }

}


void Soxgui::slotTarget3()
{

  // If target file not already open, allow user to open one
  if (!target3flag)
  {
    target3name = QFileDialog::getOpenFileName(".",
                       filedialog,
                       this,"target3","Select a Target 3 file");
    target3file = new QFile(target3name);
    if (target3file->exists())
    {
      if (target3flag)
        target3->empty();
      ingest_latlon(target3file,target3);
      target3flag = true;
      stemp = QString("Close Target3 file (");
      stemp.append(target3name);
      stemp.append(")");
      filemenu->changeItem(idt3,stemp);
    }
    //delete target3file;
  }

  // Otherwise null the target3 list
  else
  {
    target3->empty();
    target3flag = false;
    filemenu->changeItem(idt3,"Open Target3 file");
    target3name = "";
  }

}


void Soxgui::slotTarget4()
{

  // If target file not already open, allow user to open one
  if (!target4flag)
  {
    target4name = QFileDialog::getOpenFileName(".",
                       filedialog,
                       this,"target4","Select a Target 4 file");
    target4file = new QFile(target4name);
    if (target4file->exists())
    {
      if (target4flag)
        target4->empty();
      ingest_latlon(target4file,target4);
      target4flag = true;
      stemp = QString("Close Target4 file (");
      stemp.append(target4name);
      stemp.append(")");
      filemenu->changeItem(idt4,stemp);
    }
    //delete target4file;
  }

  // Otherwise null the target4 list
  else
  {
    target4->empty();
    target4flag = false;
    filemenu->changeItem(idt4,"Open Target4 file");
    target4name = "";
  }

}


void Soxgui::slotWPFile()
{

  // If waypoint file not already open, allow user to open one
  if (!wpflag)
  {
    cout << "waypoint file not already open\n";
    wpname = QFileDialog::getOpenFileName(".",
                       "sequence (*.sequence);;All (*.*)",
                       this,"waypoint","Select a waypoint file");
    wpfile = new QFile(wpname);
    if (wpfile->exists())
    {
      if (wpflag)
        waypoint->empty();
      ingest_waypoint(wpfile,waypoint);
      wpflag = true;
      stemp = QString("Close waypoint file (");
      stemp.append(wpname);
      stemp.append(")");
      filemenu->changeItem(idwp,stemp);
    }
    //delete target4file;
  }

  // Otherwise null the waypoint list
  else
  {
    cout << "waypoint file already open\n";
    waypoint->empty();
    wpflag = false;
    filemenu->changeItem(idwp,"Open Waypoint file");
    wpname = "";
  }

}


void Soxgui::slotPOIFile()
{

  // If poi file not already open, allow user to open one
  if (!poiflag)
  {
    poiname = QFileDialog::getOpenFileName(".",
                       "sequence (*.sequence);;All (*.*)",
                       this,"waypoint","Select a POI file");
    poifile = new QFile(poiname);
    if (poifile->exists())
    {
      if (poiflag)
        poi->empty();
      ingest_waypoint(poifile,poi);
      poiflag = true;
      stemp = QString("Close Points-of-Interest file (");
      stemp.append(poiname);
      stemp.append(")");
      filemenu->changeItem(idpoi,stemp);
    }
    //delete target4file;
  }

  // Otherwise null the poi list
  else
  {
    poi->empty();
    poiflag = false;
    filemenu->changeItem(idpoi,"Open Points-of-Interest file");
    poiname = "";
  }

}


void Soxgui::slotGPSClosed()
{
  stemp.sprintf("Connection to GPS network server closed by the server");
  QMessageBox::critical(this,"GPS Connection Closed",stemp);
}


void Soxgui::slotGPSError(int err)
{
  if (err==QSocket::ErrConnectionRefused)
    stemp.sprintf("Connection to GPS server refused\n");
  else if (err==QSocket::ErrHostNotFound)
    stemp.sprintf("GPS server host not found\n");
  else if (err==QSocket::ErrSocketRead)
    stemp.sprintf("Socket read from GPS server failed");
  QMessageBox::critical(this,"GPS Network Error",stemp);
}


void Soxgui::about()
{
  QMessageBox::about(this,"About SOXMap",
                     "SOXMap\nAuthor: John G. Sonntag\n"
		     "Released: 22 February 2004\n"
                     "$Id: soxgui.cpp,v 1.14 2007/05/13 21:29:31 sonntag Exp $"
		    );
}
