#include "Profile.h"


std::string name, window, filepath, line;
std::ifstream infile;
std::ofstream outfile;
DIR *dp;
struct dirent *dirp;

Profile::Profile() {
}

Profile::Profile(std::string name, bool newmem) {
  this->name = name;
  if (newmem) {
    outfile.open("intervals.txt");
    outfile << name << "\n";
    outfile.close();
  }
}

Profile::~Profile() {

}

std::string Profile::getName() {
  return this->name;
}
  
void Profile::setName(std::string newname) {
  this->name = newname;
}

bool Profile::isName() {
  return true;
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
}
