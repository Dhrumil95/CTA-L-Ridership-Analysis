//
// CTA "L" RidershipAnalysis: class function file
//
// Dhrumil Patel
// U. of Illinois, Chicago
// CS341, Spring 2016
// HW #3
//


#include "classes.h"

Stop::Stop( string stopName, string Direction, string ada, string Red, string Blue, string Grn, string Brn, string Purp, string PurpExp, string Yel, string Pink, string Orng ) : stop_names(stopName), direction(Direction), ADA(ada), red(Red), blue(Blue), grn(Grn), brn(Brn), purp(Purp), purpExp(PurpExp), yel(Yel), pink(Pink), orng(Orng)  {  }

fileStation::fileStation(int id) : ID(id), Ridership_Weekday(0), Ridership_Saturday(0), Ridership_SundayHoliday(0) { }

void fileStation::UpdateRidership( string day_type, int rides)
{
  if      (day_type == "W") Ridership_Weekday += rides;
  else if (day_type == "U") Ridership_SundayHoliday += rides;
  else if (day_type == "A") Ridership_Saturday += rides;
  else throw  invalid_argument("invalid day_type in UpdateRidership");
}


long long fileStation::TotalRidership() const
{
  return Ridership_Weekday + Ridership_Saturday + Ridership_SundayHoliday;
}


Station::Station(int id,  string name, vector<Stop> stopNames) : ID(id), Name(name), Stops(1), stop_names(stopNames), total_rides(0) { }

int Station::NumStops() const
{
  return Stops;
}

void Station::print_stops() {
  
  for (auto &v : stop_names) {
    cout << "\t" << v.stop_names << ": " << v.direction << ",";
    
    if (v.ADA == "TRUE" ) cout << " Handicap access";
    else cout << " *no* Handicap access";
    
    if (v.red == "TRUE") cout << ", Red";
    if (v.blue == "TRUE") cout << ", Blue";
    if (v.grn == "TRUE") cout << ", Green";
    if (v.brn == "TRUE") cout << ", Brown";
    if (v.purp == "TRUE") cout << ", Purple";
    if (v.purpExp == "TRUE") cout << ", Purple Express";
    if (v.yel == "TRUE") cout << ", Yellow";
    if (v.pink == "TRUE") cout << ", Pink";
    if (v.orng == "TRUE") cout << ", Orange";
   
   cout << endl;

  }
}

void Station::UpdateRidership(int rides)
{
  total_rides += rides;
}

void Station::UpdateStop(string stopName, string Direction, string ada, string red, string blue, string grn, string brn, string purp, string purpExp, string yel, string pink, string orng) {
  
  Stop s = Stop( stopName, Direction, ada, red, blue, grn, brn, purp, purpExp, yel, pink, orng);
  stop_names.push_back(s);
  
  Stops++;
  
}

long long Station::TotalRidership() const
{
  return total_rides;
}
