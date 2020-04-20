
/*
   $Id: soxmap.h,v 1.2 2007/03/20 21:40:15 mitchell Exp $

*/

#define MAXLEN 256

enum MODE {ATM=1, EAARL=2};

typedef struct {
 MODE mode;
 bool log;
 char sock_name[ MAXLEN];
 unsigned int port;
} SETTINGS;


