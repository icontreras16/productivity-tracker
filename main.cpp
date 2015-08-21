#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <dirent.h>

#include "Interval.h"
#include "Day.h"
#include "Profile.h"
#include <ctime>

/*main prompts user for commands and responds accordingly*/
int main() {
  std::string input, args;
  bool seshflag = false , dayflag = false, match = false;
  Interval* newsesh;
  Day* newday;
  Profile* propt;
  std::string filepath, line;
  std::ifstream infile;
  std::ofstream outfile;

  std::cout << "Enter username or N to create new profile\n" << std::endl;
  getline(std::cin, input);
  propt = new Profile(input, false);
  while (!propt->isName()) {    
    //Create a profile if user is new
    if (input == "N") {
      std::cout << "Creating new profile" << std::endl;
      std::cout << "Enter a username >> " << std::flush;
      getline(std::cin, input);
      delete propt;
      propt = new Profile(input, true);
      break;
    } else {
      delete propt;
      propt = new Profile(input, false);
      if (!propt->isName()) { // handle case for incorrect username
	std::cout << "\n";
	std::cout << "Username wrong or profile does not exist" << std::endl;
	std::cout << "Enter username or N to create new profile\n" << std::endl;
	getline(std::cin, input);
	delete propt;
	propt = new Profile(input, false);
      }
    }
  }
  /* Continue to execute program until user quits */
  while (true) {
    std::cout << "Enter Command >> " << std::flush;
    getline(std::cin, input);
    //specify how much time past 24:00 will count as a sleep interval for the previous day
    if (input.length() >= 2) {
      std::string time = "";
      std::string win = "w ";
      bool isvalid = true;
      match = true;
      for (int i=0; i<win.length(); i++) {
	if (input[i] != win[i]) {
	  match = false;
	  break;
	}
      }
      if (match && seshflag) {
	std::cout << "Error: Cannot change time window while a session is in progress\n" << std::endl;
	continue;
      }
      if (match) {
	input.erase(0, 2);
	if (input.length() != 5) {
	  std::cout << "Error: Not a valid time format\n" << std::endl;
	  isvalid = false;
	  continue;
	}
	for (int i=0; i<5; i++) {
	  if (i==2) {
	    if (input[i] != ':') {
	      std::cout << "Error: Not a valid time format\n" << std::endl;
	      isvalid = false;
	      continue;
	    }
	  }
	  if (!isdigit(input[i]) && input[i] != ':') {
	    std::cout << "Error: Not a valid time format\n" << std::endl;
	    isvalid = false;
	    continue;
	  }
	  if (input[i] == ':' && i != 2) {
	    std::cout << "Error: Not a valid time format\n" << std::endl;
	    isvalid = false;
	    continue;
	  }
	  time = input;
	}
	if (!isvalid) {continue;}
	else {
	  propt->setTimeWindow(time);
	  continue;
	}
      }
    }
    if (input.length() >= 7) {
      std::string time = "";
      std::string win = "window ";
      bool isvalid = true;
      match = true;
      for (int i=0; i<win.length(); i++) {
	if (input[i] != win[i]) {
	  match = false;
	  break;
	}
      }
      if (match && seshflag) {
	std::cout << "Error: Cannot change time window while a session is in progress\n" << std::endl;
	continue;
      }      
      if (match) {
	input.erase(0, 7);
	if (input.length() != 5) {
	  std::cout << "Error: Not a valid time format\n" << std::endl;
	  isvalid = false;
	  continue;
	}
	for (int i=0; i<5; i++) {
	  if (i==2) {
	    if (input[i] != ':') {
	      std::cout << "Error: Not a valid time format\n" << std::endl;
	      isvalid = false;
	      continue;
	    }
	  }
	  if ( !isdigit(input[i]) && input[i] != ':') {
	    std::cout << "Error: Not a valid time format\n" << std::endl;
	    isvalid = false;
	    continue;
	  }
	  if (input[i] == ':' && i != 2) {
	    std::cout << "Error: Not a valid time format\n" << std::endl;
	    isvalid = false;
	    continue;
	  }
	  time = input;
	}
	if (!isvalid) {continue;}
	else {
	  propt->setTimeWindow(time);
	  continue;
	}
      }
    }
    //record factors for current day that affect sleep
    if (input.length() >= 3) {
      if (input[0]=='r' && input[1]=='e' && input[2]==' ') {
	if (!dayflag) {
	  newday = new Day();
	  dayflag = true;
	}
	propt->setRecord(input.erase(0, 3));
	continue;
      }
    }
    if (input.length() >= 7) {
      std::string re = "record ";
      match = true;
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
	propt->setRecord(input.erase(0, 7));
	continue;
      }
    }
    //begin a new interval with the profile's offset if any
    if (input == "be" || input == "begin") {
      if (seshflag) {delete newsesh;} 
      newsesh = new Interval(propt->getTimeWindow());
      seshflag = true;
      std::cout << "New interval started\n" << std::endl;
      continue;
    }
    //display options if help requested
    if (input == "h" || input == "help") {
      std::cout << "The following commands are supported:\n" << std::endl;
      std::cout << "  h [ help ]            produce this help message"  << std::endl;
      std::cout << "  w [ window ] [HH:MM]	specify how much time past 24:00 will count as an interval for the previous day" << std::endl;
      std::cout << "  re [ record ] [OPTIONS]	record productivity/sleep affecting factors for current day" << std::endl;
      std::cout << "  be [ begin ]		begin a new interval"  << std::endl;
      std::cout << "  e [ end ] 		end and save current interval" << std::endl;
      std::cout << "  ca [ cancel ]		cancel current interval" << std::endl;
      std::cout << "  in [ intervals ]	display history of intervals" << std::endl;
      std::cout << "  fa [ factors ] 	display recorded factors for current day" << std::endl;
      std::cout << "  q [ quit ]	 	exit program\n" << std::endl;
      std::cout << "The following options are supported by record command:\n" << std::endl;
      std::cout << "-w, Worked out" << std::endl;
      std::cout << "-d, Drank alcohol" << std::endl;
      std::cout << "-s, Exposed to display screen at late hour" << std::endl;
      std::cout << "-a, Ate at late hour" << std::endl;
      std::cout << "-c, Had caffeine\n" << std::endl;
      continue;
    }
    //deallocate interval if cancelled
    if (input == "ca" || input == "cancel") {
      if (!seshflag) {
	std::cout << "No interval to cancel\n" << std::endl;
	continue;}
      delete(newsesh);
      seshflag = false;
      std::cout << "interval cancelled\n" << std::endl;
      continue;
    }
    //add the new interval with a terminated time
    if (input == "e" || input == "end") {
      if (!seshflag) {
	std::cout << "No interval to end\n" << std::endl;
	continue;}
      time_t t = time(0);
      newsesh->setTerm(t, propt->getTimeWindow());
      propt->setIntervals(*newsesh);
      delete(newsesh);
      seshflag = false;
      std::cout << "Interval ended\n" << std::endl;
      continue;
    }
    //display history of intervals and factors
    if (input == "in" || input == "intervals") {
      propt->showIntervals();
      continue;
    }
    if (input == "q" || input == "quit") {
      return 0;
    }
    std::cout << "Command not recognized (h for help)\n" << std::endl;
  }
  return 0;
}
