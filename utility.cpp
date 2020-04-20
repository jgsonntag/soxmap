// $Id: utility.cpp,v 1.3 2004/07/31 13:39:42 sonntag Exp $
#include "utility.h"

#include <iostream>
using namespace std;


double timediff(timeval t1, timeval t2)
{
  double secs,usecs;

  secs = (double)(t1.tv_sec - t2.tv_sec);
  usecs = (double)(t1.tv_usec - t2.tv_usec);
  return(secs+usecs/1.0e6);
}


double gcdist(double lat1,double lon1,double lat2,double lon2)
{
  double dist;

  lon1 = -lon1;
  lon2 = -lon2;
  dist = acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2));
  return(dist);

}


double gccourse1(double lat1,double lon1,double lat2,
                 double lon2)
{
  double dist,tc1;

  /*  Change longitude sign convention  */
  if (lon1<0.0)
    lon1 += 2.0*PI;
  if (lon2<0.0)
    lon2 += 2.0*PI;
  lon1 = -lon1;
  lon2 = -lon2;

  /*  Check for pole  */
  if (cos(lat1) < 0.00001)
  {
    if (lat1 > 0)
      tc1 = PI;
    else
      tc1 = 0;
  }

  /*  Check for meridian  */
  //else if (lon1 == lon2)
  else if (fabs(lon1-lon2)<(0.000001*DEG2RAD))
  {
    if (lat1>lat2)
    {
      tc1 = PI;
    }
    else
    {
      tc1 = 0.0;
    }
  }

  /*  Point 1 not a pole  */
  else
  {
    dist = acos(sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(lon1-lon2));
    tc1 = acos((sin(lat2)-sin(lat1)*cos(dist))/(sin(dist)*cos(lat1)));
    if (sin(lon2-lon1)>=0)
      tc1 = 2*PI-tc1;
  }

  /*  Return the result  */
  return(tc1);

}


double gcproject(double lat1,double lon1,double tc1,double dist,
                 double *lat2,double *lon2)
{
  double templon;

  // Compute point 2
  lon1 = -lon1;
  dist /= RAD2KM;
  *lat2 = asin(sin(lat1)*cos(dist)+cos(lat1)*sin(dist)*cos(tc1));
  templon = atan2(sin(tc1)*sin(dist)*cos(lat1),cos(dist)-sin(lat1)*sin(*lat2));
  /* lonb = (lona-templon+PI)%(2.0*PI) - PI;  */
  *lon2 = -(lon1 - templon);


}
