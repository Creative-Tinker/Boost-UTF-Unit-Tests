
# Boost-UTF-Unit-Tests

## Justification
I chose to undertake this project because testing is a crucial aspect of software development, yet it's often overlooked in many personal passion projects on GitHub.
I noticed that I had fallen into the habit of neglecting tests in my own work, so I wanted to make a conscious effort to prioritize testing and ensure it's taken as seriously as the development process itself.

## Project Description
I designed and executed 10 unit tests using the Boost UTF test framework (located in track-tests.cpp under \tests) to validate the functionality of the 'mostEquatorialWaypoint()' function (found in track.cpp under \src). As documented in track.h, the purpose of the function is to identify the point on the track nearest to the equator. If two points are equally close, the function returns the one that appears first. It throws a std::domain_error if the track contains zero track points. However, it's important to note that the function is intentionally implemented incorrectly in track.cpp, meaning some of the tests I designed will fail while others will pass.


## Test Case Descriptions
### Typical Cases
The choice of latitude values, such as 45 for 'closestWP' in NorthernHemisphere and -45 for SouthernHemisphere, strategically represents points halfway between the equator (0) and the poles (90 or -90), respectively. Selecting values away from the latitudinal boundaries is important as testing near the boundaries will be conducted as separate test cases later, which is why these midpoints were chosen. Typical inputs are meant to represent the most common scenarios encountered in real-world usage which is why they cannot be edge or error cases as well. This separation into positive and negative latitudes allows for targeted investigations into hemisphere-specific behaviour. Isolating these scenarios aids in the efficient identification of any potential issues, contributing to the overall effectiveness of the testing process. Four more waypoints with values incremented by five are added to the track as well, all the way up to 65. Five trackpoints are utilised to ensure that one trackpoint lies precisely in the middle, a scenario not possible with four or two points. However, employing only three waypoints would be insufficient, and while testing every conceivable value is impractical, maintaining a balance between thoroughness and efficiency is essential for ensuring robustness. RealWorldLocation is created as the trackpoints within contain more complex data compared to the previously mentioned test cases, which only include longitude values of ten. These locations were selected because they are popular destinations and are likely to be encountered during program execution.

### Atypical Cases
These represent scenarios that are unconventional in comparison to the representative inputs. In RepeatedTrackpoints , by including two occurrences of 'closestTP' within the track, we test whether the function returns the most equatorial waypoint even when it is duplicated. 'BOOST_CHECK_CLOSE' was used with a tolerance of 0.1% for comparing the expected waypoint to the actual waypoint everywhere except in ZeroTrackpoints. This is essential as it ensures accurate comparison in floating-point values, preventing inaccuracies that may arise from direct floating-point comparisons. Additionally, AllOnEquator tests that the first trackpoint is returned if all trackpoints have latitude values of zero. Throughout all the test cases, 'closestTP' is placed in different positions within the Track, ensuring that ordering is irrelevant.

### Boundary Cases
JustBeneathEquator tests values that are slightly south of the equator, such as –0.000001 degrees whilst JustAboveEquator tests values that are barely north of the equator, such as 0.1. These values are extremely close to the equator, within a range of only a few decimal degrees. When tested in tandem both cases help identify that the equator is correctly in place (has a latitude of zero).
Initially, testing near the poles (90 and -90 degrees) was considered; however, due to constraints in the existing codebase, values above 90 and below -90 were not accepted as valid inputs. When attempting to test values near these boundaries, the program encountered errors that prevented meaningful testing. As a result, these pole-boundary tests were omitted from the test suite.

### Edge Cases 
If there is a SingleTrackpoint, it would be returned by default as the nearest since there is no other waypoint to compare it to. EquallyClose verifies that if two waypoints are the same exact distance from the equator then the function returns the one that comes earlier in the track. The first trackpoint is in the northern hemisphere, whereas the second trackpoint is in the southern hemisphere. Both are symmetrically placed apart from the equator 30 degrees out.  


### Error Case 
ZeroTrackpoints ensures that a 'std::domain_error' when the track is empty. The act step in the AAA pattern is implicitly performed within the ‘BOOST_CHECK_THROW’ macro. This is an error case and not an edge case as an error is expected to be thrown as specified within the given header comment. 

 
