//
// CTA "L" RidershipAnalysis: main program file
//
// Dhrumil Patel
// U. of Illinois, Chicago
// CS341, Spring 2016
// HW #3
//

#include "classes.h"

vector<fileStation> fileStations (string filename, int &valid) {
  
  vector<fileStation>  stations;
  ifstream             file(filename.c_str());
  string               line;
  
  /* If file was not found or if it was corrupted */
  if (!file.good()) { cout << "** Error: unable to open '" << filename << "', incorrect L line? "<< endl
                           << "** Please try again..." << endl << endl; 
                           valid = 0;
                           return stations; 
                    }

  /* Start reading the file line by line. Stores the line in a string "line"
   * stringstream breaks the line
   */
  while ( getline(file, line) ) {
     stringstream  ss(line);
     string  station_id;

     ss >> station_id;  // gets the Station ID

     int id =  stoi(station_id);  // String to Integer 
     
    /* Finds if station was already added 
     * Passed by Reference to speed up the process of comparing Station IDs
     */
     auto result = find_if(stations.begin(), stations.end(), [=](const fileStation& S) {
        if (S.ID == id) return true;
        else            return false;
      }
    );
    
   /* If station is not added, result reaches to end(). Station ID is pushed/Added to the vector */ 
   if (result == stations.end()) {
      fileStation station(id);
      stations.push_back(station);
    }
  }
  
  return stations; // return the vector
}

vector<Station> InputStations( string filename ) {
   
   vector<Station>  stations; 
   vector<Stop>     station_info;
   ifstream         file(filename.c_str());
   string           line;
  
  /* If file was not found or if it was corrupted */
  if (!file.good()) throw  invalid_argument("file '" + filename + "' not found!");

  getline(file, line); // ignores first line that includes the L line names
  
  /* Start reading the file line by line. Stores the line in a string "line"
  * stringstream breaks the line
  */
  while ( getline(file, line) ) {
  
    stringstream  ss(line);

    string  station_id, direction, stop_name, station_name, ada;
    string  red, blue, grn, brn, purp, purpExp, yel, pink, orng;
  
    /* Reads each line and breaks it into tokens and stores it in appropriate string var */
    getline(ss, station_id, ',');
    getline(ss, direction, ',');
    getline(ss, stop_name, ',');
    getline(ss, station_name, ',');
    getline(ss, ada, ',');
    getline(ss, red, ',');
    getline(ss, blue, ',');
    getline(ss, grn, ',');
    getline(ss, brn, ',');
    getline(ss, purp, ',');
    getline(ss, purpExp, ',');
    getline(ss, yel, ',');
    getline(ss, pink, ',');
    getline(ss, orng);

    int id =  stoi(station_id); // String to Interger converter for Station ID

    /* Finds if station was already added 
     * Passed by Reference to speed up the process of comparing Station IDs
     */
    auto result =  find_if(stations.begin(), stations.end(), [=](const Station& S) {
        if (S.ID == id) return true;
        else            return false;
      }
    );
    
    if (result == stations.end()) {
      /* Here Station is added for the first time */
      Stop s = Stop(stop_name, direction, ada, red, blue, grn, brn, purp, purpExp, yel, pink, orng); // creates stop object
      station_info.push_back(s); // add first stop info to station_info vector
      Station station(id, station_name, station_info); // create station object with station info
      stations.push_back(station); // adds overall info including direction, ada, stop name, etc to station vector
      station_info.clear(); // Clears station_info vector so that the Stops from other L lines is not added to wrong stations.
    }
    else  /* Station already exits.. Updates Stop Info */
      result->UpdateStop(stop_name, direction, ada, red, blue, grn, brn, purp, purpExp, yel, pink, orng); // add additional stops info
  }
  
  return stations; // return vector
}

void fileInputRidership( string filename,  vector<fileStation>& stations) {
   ifstream  file(filename.c_str());
   string    line;
  
  /* If file was not found or if it was corrupted */
  if (!file.good()) throw  invalid_argument("file '" + filename + "' not found!");


   getline(file, line); // ignores first line that includes the L line names
  
  /* Start reading the file line by line. Stores the line in a string "line"
   * stringstream breaks the line
   */
  while ( getline(file, line) ) {
     stringstream  ss(line);

     string  station_id, service_date, day_type, total_rides;

    /* Reads each line and breaks it into tokens and stores it in appropriate string var */
     getline(ss, station_id, ',');
     getline(ss, service_date, ',');
     getline(ss, day_type, ',');
     getline(ss, total_rides); 

    int id =  stoi(station_id); // String to Interger converter for Station ID
    
    /* Finds if station already exists 
     * Passed by Reference to speed up the process of comparing Station IDs
     */
    auto result =  find_if(stations.begin(), stations.end(), [=](const fileStation& S) {
        if (S.ID == id) return true;
        else            return false;
      }
    );

    if (result == stations.end())
    {
      //cout << "Station not found: " << id << endl;
    }
    else  {
      int rides =  stoi(total_rides);
      result->UpdateRidership(day_type, rides);
    }
  }
}

void InputRidership( string filename,  vector<Station>& stations) {
   ifstream  file(filename.c_str());
   string    line;
  
   /* If file was not found or if it was corrupted */
   if (!file.good()) throw  invalid_argument("file '" + filename + "' not found!");

   getline(file, line);  // ignores first line that includes the L line names

  /* Start reading the file line by line. Stores the line in a string "line"
   * stringstream breaks the line
   */
   while ( getline(file, line) ) {
     stringstream  ss(line);

     string  station_id, service_date, day_type, total_rides;
    
     /* Reads each line and breaks it into tokens and stores it in appropriate string var */
     getline(ss, station_id, ',');
     getline(ss, service_date, ',');
     getline(ss, day_type, ',');
     getline(ss, total_rides);  

    int id =  stoi(station_id); // String to Interger converter for Station ID
    
    /* Finds if station already exists 
     * Passed by Reference to speed up the process of comparing Station IDs
     */
    auto result =  find_if(stations.begin(), stations.end(), [=](const Station& S) {
        if (S.ID == id) return true;
        else            return false;
      }
    );

  if (result == stations.end())  
    {
      //cout << "Station not found: " << id << endl;
    }
    else {
      int rides =  stoi(total_rides);
      result->UpdateRidership(rides);
    }
  }
}

int main()
{
  /* Welcome menu */
  cout << "** CTA L Ridership Analysis Program **" << endl << endl
       << "** Inputting data..." << endl;

  /* Vector to store Station objects */
  vector<Station>  stations;
  
  /* Processing starts here 
   * Stores data about stations and stops.
  */
  
  stations = InputStations("CTA-L-Stops.csv");

  int stops = 0;

  for (const Station& S : stations)
  {
    // cout << s.ID << ": " << s.Name << endl;
    stops += S.NumStops();
  }
  /* Compares the Station ID's and stores the ridership data in appropriate variable (i.e total_rides) */
  InputRidership("CTA-L-Ridership-Daily.csv", stations);
  
  /* Needs to be 64-bit due to large data 
   * total_ridership      - Stores total riderships.
   * total_ridership_file - Stores the total ridership of the given L line
  */
  long long total_ridership = 0, total_ridership_file = 0;
  
  /* Adds riderships of all L lines regardless Holiday/Sunday, Saturday, or Weekdays */
  for (const Station& S : stations) total_ridership += S.TotalRidership();
  
  /* Overall stats. Contains info about all the L lines */
  cout << "   Num stations: " << stations.size() << endl
       << "   Num stops:    " << stops << endl
       << "   Total ridership: " << total_ridership << " (CTA-L-Ridership-Daily.csv)" << endl
       << "** Ready" 
       << endl << endl;
      
  while (1) {
    /* file string to store L line color */
    string inputFile;
    /* check if blueline is valid */
    int valid = 1;
    /* Prompt user to input the L line */
    cout << ">> Please enter an L line (e.g. Blue), or ENTER to quit: ";
    /* getline is used to differentiate between empty string. So that the program would terminate if nothing was entered */
    getline(cin, inputFile);
   
    /* Input lines. Opens corresponding L line text file. For testing!
    if ( inputFile.empty() ) exit(0);
    else if ( inputFile == "Blue" || inputFile == "blue" )     { inputFile = "Blue.txt";    }
    else if ( inputFile == "Red" || inputFile == "red" )       { inputFile = "Red.txt";     }
    else if ( inputFile == "Pink" || inputFile == "pink" )     { inputFile = "Pink.txt";    }
    else if ( inputFile == "Orange" || inputFile == "orange" ) { inputFile = "Orange.txt";  }
    else if ( inputFile == "Yellow" || inputFile == "yellow" ) { inputFile = "Yellow.txt";  }
    else if ( inputFile == "Green" || inputFile == "green" )   { inputFile = "Green.txt";   }
    else if ( inputFile == "Brown" || inputFile == "brown" )   { inputFile = "Brown.txt";   }
    else if ( inputFile == "Purple" || inputFile == "purple" ) { inputFile = "Purple.txt";  }
    else if ( inputFile == "PurpExp" || inputFile == "purpExp" || inputFile == "purpexp") { inputFile = "PurpleExp.txt";  }
    else { cout << "** Error: unable to open '" << inputFile << ".txt', incorrect L line? "<< endl
                << "** Please try again..." << endl << endl; 
                continue; 
         }
     */
    
    
    /* Exit if empty string or enter was pressed */
    if ( inputFile.empty() ) exit(0);

    inputFile = inputFile + ".txt"; // Adds .txt to filename string.
    /* This vector stores the stations that are in the particular L line .txt file */
    vector<fileStation> filestations;
    /* Data gets stored */
    filestations = fileStations(inputFile, valid);
    if ( valid == 0 ) continue;
    /* Compares the Station ID's and stores the ridership data in appropriate variable (i.e day) */
    fileInputRidership("CTA-L-Ridership-Daily.csv", filestations);
    
    /* Declare variables to store the ridership data 
     * Needs to be 64-bit because the data is quite large
    */ 
    long long Weekday = 0, Saturday = 0, SundayHoliday = 0;
    
    /* Calculate total Ridership alongwith riderships on Weekdays, Saturday, and Holiday/Sunday */
    for (const fileStation& S : filestations) {
      total_ridership_file += S.TotalRidership();
      Weekday += S.Ridership_Weekday;
      Saturday += S.Ridership_Saturday;
      SundayHoliday += S.Ridership_SundayHoliday;
    }
    
    /* Percentage of particular L line ridership based on total of all L lines ridership */
    float percent = (float)total_ridership_file / (float)total_ridership * 100.0F;
  
    /* Stats about the particular L line */
    cout << endl << "** Line contains " << filestations.size() << " stations"<< endl
         << "** Weekday ridership: \t" << " " << Weekday << endl
         << "** Saturday ridership: \t" << " " << Saturday << endl
         << "** Sunday/Holiday: \t" << " " << SundayHoliday << endl
         << "** % " << "of Total ridership: " << percent << "%" << endl << endl;
  //cout << "Total ridership: " << total_ridership_file << endl;
  
    int i = 1; // counter for tracking number of stations
    for (const fileStation& s : filestations ) {

      auto result = find_if(stations.begin(), stations.end(), [=](const Station& v) {
        if ( s.ID == v.ID ) return true;
        else                return false;
        }
      );
      
      if ( result != stations.end() ) {
        cout << i << ". " << result->Name << endl; 
        result->print_stops();
        i++;
      }
    }
    
    /* Reset the counters */
    Weekday = 0; Saturday = 0;
    SundayHoliday = 0;  total_ridership_file = 0;
    percent = 0; i = 0; 
    filestations.clear();
    
    cout << endl;
  }
}
