//
// CTA "L" RidershipAnalysis: class header file
//
// Dhrumil Patel
// U. of Illinois, Chicago
// CS341, Spring 2016
// HW #3
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Stop {
  
  public:
  string stop_names;
  string direction;
  string ADA;
  string red, blue, grn, brn, purp, purpExp, yel, pink, orng;
  
  Stop( string stopName, string Direction, string ada, string red, string blue, string grn, string brn, string purp, string purpExp, string yel, string pink, string orng );
  
};

class fileStation {
  
  public:
  int ID;
  long long    Ridership_Weekday;
  long long    Ridership_Saturday;
  long long    Ridership_SundayHoliday;
  
  fileStation(int id);
  
  void      UpdateRidership(string day_type, int rides);
  long long TotalRidership() const;
  
};

class Station
{
public:
  int          ID, Stops;
  long long total_rides;
  string  Name;
  vector<Stop> stop_names;

  Station(int id, string name, vector<Stop> stopNames);

  int       NumStops() const;
  void      UpdateRidership(int rides);
  void      UpdateStop(string stopName, string Direction, string ada, string red, string blue, string grn, string brn, string purp, string purpExp, string yel, string pink, string orng);
  long long TotalRidership() const;
  void print_stops(); 
};
