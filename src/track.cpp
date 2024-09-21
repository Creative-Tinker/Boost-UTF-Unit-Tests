#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "geometry.h"

#include "track.h"

namespace GPS
{

Waypoint Track::mostEquatorialWaypoint() const
{
    if (trackPoints.size() <= 2) throw std::domain_error("Not enough track points!");

    Waypoint nearestPointSoFar = trackPoints[1].waypoint;
    for (unsigned int current = 1; current < trackPoints.size()-1; ++current)
    {
        if (std::abs(trackPoints[current].waypoint.latitude()) < std::abs(nearestPointSoFar.latitude()))
        {
            nearestPointSoFar = trackPoints[current].waypoint;
        }
    }
    return nearestPointSoFar;
}


}
