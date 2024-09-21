#ifndef GPS_TRACKPOINT_H
#define GPS_TRACKPOINT_H

#include <ctime>

#include "waypoint.h" /* Extends waypoint class */

namespace GPS
{
/* Combines waypoint and timestamp */
  struct Trackpoint
  {
     GPS::Waypoint waypoint;
     std::time_t timeStamp;  // time_t is usually a long int denoting the Unix Epoch (number of seconds since 1st January 1970)
  };
  // time_t  : integer value counting number of seconds (unix epoch - # of seconds ) its a standard library component
  // stores individual data entries - essentially one line
}

#endif
