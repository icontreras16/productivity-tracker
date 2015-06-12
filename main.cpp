#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Interval.h"
#include "Day.h"
#include <vector>
#include <ctime>

using namespace std;

/*main prompts user for commands and responds accordingly*/
int main() {
  vector<Interval> intervals;
  string input = "";
  Interval* newsesh;
  Day* newday;
  string filepath, line;
  ifstream infile;
  ofstream outfile;
  DIR *dp;
  struct dirent *dirp;
  
  while (true) {
    cout << "Enter Command >> " << flush;
    getline(cin, input);

    //record factors for current day that affect sleep
    if (input == "record") {
      while (true) {
	if (newday == NULL) {
	  newday = new Day();
	  cout << "New day being recorded" << endl;
	}
	cout << "Enter sleep arguments (h for help)>> " << flush;
	getline(cin, input);

	// handle list of arguments provided
	if (input == "h") {
	  cout << "All possible argument parameters:\n" << endl;
	  cout << "-w if you worked out" << endl;
	  cout << "-d if you drank alcohol" << endl;
	  cout << "-s if you were exposed to a display screen tonight" << endl;
	  cout << "-a if you ate at a late hour" << endl;
	  cout << "-c if you had caffeine" << endl;
	  cout << "q to quit" << endl;
	}
	if (input == "q") {break;}
	//this allows multiple arguments to be provided at once
	if (input.find("-w") != string::npos) {
	  *newday->setWorkout(true);
	}
	if (input.find("-d") != string::npos) {
	  *newday->setAlcohol(true);
	}
	if (input.find("-s") != string::npos) {
	  *newday->setScreened(true);
	}
	if (input.find("-a") != string::npos) {
	  *newday->setEatenLate(true);
	}
	if (input.find("-c") != string::npos) {
	  *newday->setCaffeine(true);
	}
      }
    }

    if (input == "test") {
      cout << "Workout: " << *newday->hasWorkout() << endl;
      cout << "Alcohol: " << *newday->hasAlcohol() << endl;
      cout << "Screen: " << *newday->hasScreened() << endl;
      cout << "Eaten Late: " << *newday->hasEatenLate() << endl;
      cout << "Caffeine: " << *newday->hasCaffeine() << endl;
    }
    //allocate new object to ptr to start interval
    if (input == "start") {
      newsesh = new Interval();
      cout << "New interval started\n" << endl;
    }

    //display options if help requested
    if (input == "help") {
      cout << "Available commands:\n" << endl;
      cout << "record" << endl;
      cout << "start" << endl;
      cout << "end" << endl;
      cout << "cancel" << endl;
      cout << "intervals" << endl;
      cout << "exit\n" << endl;
    }

    //deallocate object if interval is cancelled
    if (input == "cancel") {
      delete(newsesh);
      cout << "interval cancelled\n" << endl;
    }

    //add the new interval with a terminated time
    if (input == "end") {
      time_t t = time(0);
      newsesh->setTerm(t);
      intervals.insert(intervals.begin(), *newsesh);
      outfile.open("intervals.txt", ios_base::app);
      outfile << newsesh->getDate() << "\n";
      outfile << newsesh->getDurationString() << "\n";
      outfile.close();
      delete(newsesh);
    }

    //display history of intervals
    if (input == "intervals") {
      
      dp = opendir(".");
      if (dp == NULL)
	{
	  cout << "Error(" << "No file found" << endl;
	} else {
    
	while ((dirp = readdir( dp )))
	  {
	    filepath = string("./") + dirp->d_name;

	    // If the file is not our text file, skip it
	    if (filepath != "./intervals.txt") continue;
	    // Display list of intervals
	    infile.open(dirp->d_name);
	    while (getline(infile, line)) {
	      cout << line << endl;
	    }
	    infile.close();
	  }
	closedir( dp );
      }
    }
    
    if (input == "exit") {
      cout << "exiting\n" << endl;
      return 0;
    }
  }
  return 0;
}
