#include "Profile.h"


std::string name, window, filepath, line;
std::ifstream infile;
std::ofstream outfile;
DIR *dp;
struct dirent *dirp;
bool init;

Profile::Profile() {
  this->name = "!";
  this->init = false;
}

Profile::Profile(std::string name, bool newmem) {
  this->name = name;
  if (newmem) {
    std::cout << "New profile created\n" << std::endl;
    outfile.open("intervals.txt");
    outfile << name << "\n";
    outfile.close();
  }
  this->init = true;
}

Profile::~Profile() {

}

bool Profile::isInit() {
  return this->init;
}

std::string Profile::getName() {
  return this->name;
}
  
void Profile::setName(std::string newname) {
  this->name = newname;
}

bool Profile::isName() {
  dp = opendir(".");
  while ((dirp = readdir( dp ))) {
    filepath = std::string("./") + dirp->d_name;
    if (filepath == "./intervals.txt") {
      infile.open(dirp->d_name);
      getline(infile, line);
      if (line == this->name) {return true;}
    }
  }
  return false;
}
	     
std::string Profile::getTimeWindow() {
  return this->window;
}
	     
void Profile::setTimeWindow(std::string newwindow) {
  this->window = newwindow;
}
	     	     
void Profile::setIntervals(Interval& interval) {
  outfile.open("intervals.txt", std::ios_base::app);
  outfile << interval.getDate() << "\n";
  outfile << interval.getDurationString() << "\n";
  outfile.close();
}
	     
void Profile::showIntervals() {
  std::cout << "\n" << std::endl;
  dp = opendir(".");
  if (dp == NULL)
    {
      std::cout << "Error: No file found" << std::endl;
    } else {
    
    while ((dirp = readdir( dp ))) {
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
}
