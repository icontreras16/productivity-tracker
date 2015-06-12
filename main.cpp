#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Interval.h"
#include <vector>
#include <ctime>

using namespace std;

/*main prompts user for commands and responds accordingly*/
int main() {
  vector<Interval> intervals;
  string input = "";
  Interval* newsesh;
  string filepath, line;
  ifstream infile;
  ofstream outfile;
  int num;
  DIR *dp;
  struct dirent *dirp;
  
  while (true) {
    cout << "Enter Command >> " << flush;
    getline(cin, input);

    //allocate new object to ptr to start interval
    if (input == "start") {
      newsesh = new Interval();
      cout << "New interval started\n" << endl;
    }

    //display options if help requested
    if (input == "help") {
      cout << "Available commands:\n" << endl;
      cout << "start" << endl;
      cout << "end" << endl;
      cout << "cancel" << endl;
      cout << "intervals\n" << endl;
    }

    //deallocate object if interval is cancelled
    if (input == "cancel") {
      delete(newsesh);
      cout << "interval cancelled\n" << endl;
    }

    //add the new interval with a terminated time
    if (input == "end") {
      time_t t = time(0);
      string date = newsesh->getDate();
      newsesh->setTerm(t);
      intervals.insert(intervals.begin(), *newsesh);
      outfile.open("intervals.txt", ios_base::app);
      outfile << date << "\n";
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
      string lastdate = "";
      for (Interval& interval : intervals) {
	if (interval.getDate() != lastdate) {
	  lastdate = interval.getDate();
	  cout << lastdate << endl;
	}	  
	cout << interval.getDurationString() << "\n" << endl;
      }
    }
    
    if (input == "exit") {
      cout << "exiting\n" << endl;
      return 0;
    }
  }
  return 0;
}
