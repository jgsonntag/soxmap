

/* 
   Parse commandline options
   $Id: options.cpp,v 1.2 2007/03/20 21:40:15 mitchell Exp $


   Options:
	-a		Tweaked for ATM
	-e		Tweaked for EAARL. See the EAARL specifics below
	-c server	Connect to "server" or "server:port"
	-p port		Use "port" 
        -n              Do not create a log file

EAARL Specifics:
   o Assumes port 2001 on the server.
   o Automatically makes connection request "gga1hzstream".
   o Zoom buttons located on the menu bar.
   o Displays a vertical line from the aircraft pictorial to the top.
   o Uses 0.1 degree resolution on heading display.
   o Doesn't display text data.
   o Displays GPS time in menu bar.
   o Smaller display window to coexist with "hsi", laser controller, etc.


*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "soxmap.h"
#include <string.h>
using namespace std;

SETTINGS settings;

extern char *optarg;

/*
   parse a connection commandline string:

  Inputs: 
    *s a pointer to a string of the form:
      192.168.1.211
      192.168.1.211:2001
      tans
      tans:2001

  Returns:
     1	if parse succeeded
     0  if parse failed
*/
int parse_connection(char *s) {
 char str[ MAXLEN ];
 strncpy (str, optarg, MAXLEN);
 return 1;
}

void options( int argc, char *argv[] ) {
  char str[ MAXLEN ];
  int opt,i;
  settings.mode = ATM;
  settings.log  = true;
  while ((opt=getopt(argc,argv, "anc:ep:")) != EOF ) {
    switch (opt) {
     case 'a':
      settings.mode = ATM;	
      break;

     case 'c':
        i = parse_connection( optarg );
      break;

     case 'e': 
      settings.mode = EAARL;	
      break;

    case 'n':
      settings.log = false;
      break;

     case 'p':
      break;
    }
  }
}
