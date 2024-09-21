#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mostEquatorialTestSuite
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <iostream>
#include "gpx-parser.h"
#include "track.h"
#include "earth.h"
#include "geometry.h"

using namespace GPS;
using namespace Earth;
using std::cout;
using std::endl;

BOOST_AUTO_TEST_SUITE(MostEquatorialWaypoint)

const double tolerance = 0.001; // Represents 0.1%
const Waypoint closestWP = Waypoint(45.0, 10.0, 150);
const Trackpoint closestTP = {closestWP, 1500};
const Waypoint wp1 = Waypoint(50.0, 10.0, 200);
const Trackpoint tp1 = {wp1, 2000};
const Waypoint wp2 = Waypoint(55.0, 10.0, 250);
const Trackpoint tp2 = {wp2, 2500};
const Waypoint wp4 = Waypoint(60.0, 10.0, 300);
const Trackpoint tp4 = {wp4, 3000};
const Waypoint wp5 = Waypoint(65.0, 10.0, 350);
const Trackpoint tp5 = {wp5, 3500};

//Typical Input: All trackpoints have positive latitude values
BOOST_AUTO_TEST_CASE(NorthernHemisphere) {
    std::vector<Trackpoint> northernTrackPoints = {tp1, tp2, closestTP, tp4, tp5};
    Track northernTrack = Track(northernTrackPoints);

    Waypoint expectedEquatorialWP = northernTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), closestWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), closestWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), closestWP.altitude(), tolerance);
}

// Atypical: Trackpoint duplication within track
BOOST_AUTO_TEST_CASE (RepeatedTrackpoints)
{
    std::vector<Trackpoint> repeatedTP = {tp2, closestTP, tp4, tp1, tp5, closestTP};
    Track repeatedTrack = Track(repeatedTP);

    Waypoint expectedEquatorialWP = repeatedTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), closestWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), closestWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), closestWP.altitude(), tolerance);
}

//Typical Input: All trackpoints have negative latitude values
BOOST_AUTO_TEST_CASE(SouthernHemisphere) {
    const Waypoint closestWP = Waypoint(-45.0, -10.0, 150);
    const Trackpoint closestTP = {closestWP, 1500};
    const Waypoint wp1 = Waypoint(-50.0, -10.0, 200);
    const Trackpoint tp1 = {wp1, 2500};
    const Waypoint wp3 = Waypoint(-55.0, -10.0, 250);
    const Trackpoint tp3 = {wp3, 3000};
    const Waypoint wp4 = Waypoint(-60.0, -10.0, 300);
    const Trackpoint tp4 = {wp4, 3000};
    const Waypoint wp5 = Waypoint(-65.0, -10.0, 350);
    const Trackpoint tp5 = {wp5, 3000};
    std::vector<Trackpoint> southernTrackPoints = {tp1, closestTP, tp3, tp4, tp5};
    Track southernTrack = Track(southernTrackPoints);

    Waypoint expectedEquatorialWP = southernTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), closestWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), closestWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), closestWP.altitude(), tolerance);
}

//Typical Input: Popular destinations with complex data likely to be used within program execution
BOOST_AUTO_TEST_CASE(RealWorldLocation)
{
    const Waypoint newYorkWP = Waypoint(40.7128, -74.0060, 10);
    const Waypoint londonWP = Waypoint(51.5074, -0.1278, 15);
    const Waypoint cairoWP = Waypoint(30.0444, 31.2357, 20);
    const Waypoint buenosAiresWP = Waypoint(-34.6037, -58.3816, 25);
    const Waypoint mumbaiWP = Waypoint(19.0760, 72.8777, 30);
    const Trackpoint tpNewYork = {newYorkWP, 1000};
    const Trackpoint tpLondon = {londonWP, 1100};
    const Trackpoint tpCairo = {cairoWP, 1200};
    const Trackpoint tpBuenosAires = {buenosAiresWP, 1300};
    const Trackpoint tpMumbai = {mumbaiWP, 1400};
    std::vector<Trackpoint> globalTrackPoints = {tpNewYork, tpLondon, tpBuenosAires, tpMumbai, tpCairo};
    Track globalTrack = Track(globalTrackPoints);

    Waypoint expectedEquatorialWP = globalTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), mumbaiWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), mumbaiWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), mumbaiWP.altitude(), tolerance);
}

// Boundary: Latitude values that are marginally higher than zero
BOOST_AUTO_TEST_CASE(JustAboveEquator) {
    const Waypoint closestWP = Waypoint(0.000001, 0.0, 0.0);
    const Waypoint wp2 = Waypoint(0.1, 0.0, 0.0);
    const Waypoint wp3 = Waypoint(1.0, 0.0, 0.0);
    const Trackpoint closestTP = {closestWP, 1000};
    const Trackpoint tp2 = {wp2, 1001};
    const Trackpoint tp3 = {wp3, 1002};
    std::vector<Trackpoint> topEquatorTrackPoints = {closestTP, tp2, tp3};
    Track aboveEquatorTrack = Track(topEquatorTrackPoints);

    Waypoint expectedEquatorialWP = aboveEquatorTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), closestWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), closestWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), closestWP.altitude(), tolerance);
}

// Boundary: Latitude values that are marginally below zero
BOOST_AUTO_TEST_CASE(JustBeneathEquator) {
    const Waypoint closestWP = Waypoint(-0.000001, 0.0, 0.0);
    const Waypoint wp1 = Waypoint(-0.1, 0.0, 0.0);
    const Waypoint wp2 = Waypoint(-1.0, 0.0, 0.0);
    const Trackpoint closestTP = {closestWP, 2000};
    const Trackpoint tp1 = {wp1, 2001};
    const Trackpoint tp2 = {wp2, 2002};
    std::vector<Trackpoint> bottomEquatorTrackPoints = {tp1, tp2, closestTP};
    Track belowEquatorTrack = Track(bottomEquatorTrackPoints);

    Waypoint expectedEquatorialWP = belowEquatorTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), closestWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), closestWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), closestWP.altitude(), tolerance);
}

// Atypical: Multiple trackpoints with lattiude values of 0 --> first is returned
BOOST_AUTO_TEST_CASE(AllOnEquator)
{
    const Waypoint intDateLineWP = Waypoint(0.0, -180.0, 100);
    const Waypoint primeMeridianWP = Waypoint(0.0, 0.0, 200);
    const Waypoint oppIntDateLineWP = Waypoint(0.0, 180.0, 300);
    const Trackpoint intDateLineTP = {intDateLineWP, 1000};
    const Trackpoint primeMeridianTP = {primeMeridianWP, 2000};
    const Trackpoint oppIntDateLineTP = {oppIntDateLineWP, 3000};
    std::vector<Trackpoint> onEquatorTrackPoints = {intDateLineTP, primeMeridianTP, oppIntDateLineTP};
    Track onEquatorTrack = Track(onEquatorTrackPoints);

    Waypoint expectedEquatorialWP = onEquatorTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), intDateLineWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), intDateLineWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), intDateLineWP.altitude(), tolerance);
}

//Edge: Since there is only one trackpoint it is returned by default as there is nothing to compare it to
BOOST_AUTO_TEST_CASE(SingleTrackpoint) {
    std::vector<Trackpoint> singleTP = {closestTP};
    Track singleTrack = Track(singleTP);

    Waypoint expectedEquatorialWP = singleTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), closestWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), closestWP.longitude(), tolerance );
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), closestWP.altitude(), tolerance);
}

//Edge: If two trackpoints are equidistance to the equator --> one that comes first is returned
BOOST_AUTO_TEST_CASE(EquallyClose) 
{
    const Waypoint northHemisphereWP = Waypoint(30.0, 0.0, 0.0);
    const Waypoint southHemisphereWP = Waypoint(-30.0, 0.0, 0.0);
    const Trackpoint northHemisphereTP = {northHemisphereWP, 1000};
    const Trackpoint southHemisphereTP = {southHemisphereWP, 2000};
    std::vector<Trackpoint> equallyCloseTrackPoints = {tp1, northHemisphereTP, southHemisphereTP, tp2};
    Track equallyCloseTrack = Track(equallyCloseTrackPoints);

    Waypoint expectedEquatorialWP = equallyCloseTrack.mostEquatorialWaypoint();

    BOOST_CHECK_CLOSE(expectedEquatorialWP.latitude(), northHemisphereWP.latitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.longitude(), northHemisphereWP.longitude(), tolerance);
    BOOST_CHECK_CLOSE(expectedEquatorialWP.altitude(), northHemisphereWP.altitude(), tolerance);

}

// Error: Fewest possible number of trackpoints --> throws domain error
BOOST_AUTO_TEST_CASE (ZeroTrackpoints)
{
    std::vector<Trackpoint> zeroWPTrackpoints = {};
    Track zeroTrack = Track(zeroWPTrackpoints);

    BOOST_CHECK_THROW(zeroTrack.mostEquatorialWaypoint(), std::domain_error);
}

BOOST_AUTO_TEST_SUITE_END()
