//
// $Id: main.cpp,v 1.4 2004/08/07 13:38:07 sonntag Exp $
//  Main program for SOXMAP
//

#include <qapplication.h>
#include "soxgui.h"
#include <string.h>
#include "soxmap.h"

extern void options( int argc, char *argv[]);
extern SETTINGS settings;

int main( int argc, char *argv[] )
{
  options(argc, argv);
  QApplication app( argc, argv );

  // Transfer control to the simulator GUI
  Soxgui gui;
  app.setMainWidget( &gui );
  gui.show();
  return app.exec();
}

