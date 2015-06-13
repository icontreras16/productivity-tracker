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

/*main prompts user for commands and responds accordingly*/
int main() {
  std::string input, args;
  bool seshflag,dayflag = false;
  Interval* newsesh = new Interval();
  Day* newday;
  std::string filepath, line;
  std::ifstream infile;
  std::ofstream outfile;
  DIR *dp;
  struct dirent *dirp;
  
  while (true) {
    std::cout << "Enter Command >> " << std::flush;
    getline(std::cin, input);

    //record factors for current day that affect sleep
    if (input.length() >= 3) {
      if (input[0]=='r' && input[1]=='e' && input[2]==' ') {
	if (!dayflag) {
	  newday = new Day();
	  dayflag = true;
	}
	newday->setRecord(input.erase(0, 3));
      }
    }
    if (input.length() >= 7) {
      std::string re = "record ";
      bool match = true;
      for (int i=0; i<7; i++) {
	if (input[i] != re[i]) {
	  match = false;	  
	  break;
	}
      }
      
      if (match) {
	if (!dayflag) {
	  newday = new Day();
	  dayflag = true;
	}
	newday->setRecord(input.erase(0, 7));
      }
    }

    if (input == "fa" || input == "factors") {
      std::cout << "\n" << std::endl;
      std::cout << "Workout: " << newday->hasWorkout() << std::endl;
      std::cout << "Alcohol: " << newday->hasAlcohol() << std::endl;
      std::cout << "Screen: " << newday->hasScreened() << std::endl;
      std::cout << "Eaten Late: " << newday->hasEatenLate() << std::endl;
      std::cout << "Caffeine: " << newday->hasCaffeine() << "\n" << std::endl;
      continue;
    }
    
    //allocate new object to ptr to begin interval
    if (input == "be" || input == "begin") {
      if (seshflag) {delete newsesh;} 
      newsesh = new Interval();
      seshflag = true;
      std::cout << "New interval started\n" << std::endl;
      continue;
    }

    //display options if help requested
    if (input == "h" || input == "help") {
      std::cout << "The following commands are supported:\n" << std::endl;
      std::cout << "  h [ help ]            produce this help message"  << std::endl;
      std::cout << "  re [ record ] [OPTIONS]	record sleep affecting factors for current day" << std::endl;
      std::cout << "  be [ begin ]		begin a new sleep interval"  << std::endl;
      std::cout << "  e [ end ] 		end and save current sleep interval" << std::endl;
      std::cout << "  ca [ cancel ]		cancel current sleep interval" << std::endl;
      std::cout << "  in [ intervals ]	display history of sleep intervals" << std::endl;
      std::cout << "  fa [ factors ] 	display recorded sleep factors for current day" << std::endl;
      std::cout << "  q [ quit ]	 	exit Sleep Tracker\n" << std::endl;
      std::cout << "The following options are supported by record command:\n" << std::endl;
      std::cout << "-w, Worked out" << std::endl;
      std::cout << "-d, Drank alcohol" << std::endl;
      std::cout << "-s, Exposed to display screen at late hour" << std::endl;
      std::cout << "-a, Ate at late hour" << std::endl;
      std::cout << "-c, Had caffeine\n" << std::endl;
      continue;
    }

    //deallocate object if interval is cancelled
    if (input == "ca" || input == "cancel") {
      if (!seshflag) {
	std::cout << "No sleep interval to cancel\n" << std::endl;
	continue;}
      delete(newsesh); // deletes the previous session if a new one is started
      seshflag = false;
      std::cout << "interval cancelled\n" << std::endl;
      continue;
    }

    //add the new interval with a terminated time
    if (input == "e" || input == "end") {
      if (!seshflag) {
	std::cout << "No sleep interval to end\n" << std::endl;
	continue;}
      time_t t = time(0);
      newsesh->setTerm(t);
      outfile.open("intervals.txt", std::ios_base::app);
      outfile << newsesh->getDate() << "\n";
      outfile << newsesh->getDurationString() << "\n";
      outfile.close();
      delete(newsesh);
      seshflag = false;
      std::cout << "Session ended\n" << std::endl;
      continue;
    }

    //display history of intervals
    if (input == "in" || input == "intervals") {
      std::cout << "\n" << std::endl;
      dp = opendir(".");
      if (dp == NULL)
	{
	  std::cout << "Error(" << "No file found" << std::endl;
	} else {
    
	while ((dirp = readdir( dp )))
	  {
	    filepath = std::string("./") + dirp->d_name;

	    // If the file is not our text file, skip it
	    if (filepath != "./intervals.txt") continue;
	    // Display list of intervals
	    infile.open(dirp->d_name);
	    while (getline(infile, line)) {
	      std::cout << line << std::endl;
	    }
	    infile.close();
	  }
	closedir( dp );
      }
      std::cout << "\n" << std::endl;
      continue;
    }
    
    if (input == "q" || input == "quit") {
      return 0;
    }
  }
  return 0;
}
