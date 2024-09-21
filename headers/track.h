#ifndef GPS_TRACK_H
#define GPS_TRACK_H

#include <string>
#include <vector>

#include "types.h"
#include "waypoint.h"
#include "trackpoint.h"

namespace GPS
{

/* Stores a vector of trackpoints */
/* Provides functionality for analysing / computing information about a sequence of GPS data */

  class Track
  {
    protected:
      const std::vector<Trackpoint> trackPoints;
      /* Stores all the lines in a single track object */
      /* Vector of trackpoints - sequence of trackpoints */
      /* Trackpoints - location in space and time */

    /* Constructor: need to give it a vector of trackpoints in order to construct object of class */
    public:
      Track(std::vector<Trackpoint>);

      /* This class comes after the parsing process and the purposes is to perform data analysis */

///////////////////////////////////////////////////////////////////////////////////////////////////

      /* The point on the track that is nearest to the equator.
       * If two points are equally closest to the equator, then the one that comes earlier is returned.
       * Throws a std::domain_error if the track contains zero track points.
       */
      Waypoint mostEquatorialWaypoint() const;

  };
}

#endif
