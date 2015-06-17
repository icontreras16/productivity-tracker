#include "Profile.h"
#include "Day.h"

std::string name, window, filepath, line;
std::ifstream infile;
std::ofstream outfile, newfile;
DIR *dp;
struct dirent *dirp;
Day* daypt;
bool dayflag =false;

Profile::Profile() {
  this->name = "!";
}

Profile::Profile(std::string name, bool newmem) {
  this->name = name;
  if (newmem) {
    std::cout << "New profile created\n" << std::endl;
    std::string filename = name + ".stf";
    outfile.open(filename);
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
  dp = opendir(".");
  while ((dirp = readdir( dp ))) {
    filepath = std::string("./") + dirp->d_name;
    if (filepath.find(this->name) != std::string::npos) {
      return true;
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

/*Toggles the current day's list of factor flags according to newargs*/
void Profile::setRecord(std::string newargs) {
  
  Interval iv;
  std::string filename = this->name;
  std::string delim = "  ";
  std::string token;
  std::string oldargs = "";
  std::string newline = "";
  std::size_t pos;
  pos = 0;
  int value;
  bool toggle;
  bool datefound = false;
  filename.append(".stf");
  infile.open(filename); //infile has original file
  outfile.open("temp.txt", std::ofstream::app);
  while (getline(infile, line)) {
    outfile << line << "\n";
    if (line == iv.getDate()) {
      getline(infile, line);
      datefound = true;
      break;
    }
  }
  infile.close();
  if (!datefound) {
    outfile.close();
    outfile.open(filename, std::ofstream::app);
    outfile << iv.getDate() << "\n";
    outfile << "W:0  D:0  S:0  A:0  C:0" << "\n";
    outfile.close();
  }
  outfile.open("temp.txt", std::ofstream::app);
  outfile << iv.getDate() << "\n";
  outfile.close();

  infile.open(filename);
  line = "";
  while (line != iv.getDate()) {
    getline(infile, line);
  }
  getline(infile, line);
  infile.close();
  for (int i=0; i<newargs.length(); i++) {
    if (newargs[i] == ' ' || newargs[i] == '-') {continue;}
    if (newargs[i] == 'w') {
      if (line[2] == '0') {
	line[2] = '1';
	continue;
      }
      else {
	line[2] = '0';
	continue;
      }
    }
    if (newargs[i] == 'd') {
      if (line[7] == '0') {
	line[7] = '1';
	continue;
      }
      else {
	line[7] = '0';
	continue;
      }
    }
    if (newargs[i] == 's') {
      if (line[12] == '0') {
	line[12] = '1';
	continue;
      }
      else {
	line[12] = '0';
	continue;
      }
    }
    if (newargs[i] == 'a') {
      if (line[17] == '0') {
	line[17] = '1';
	continue;
      }
      else {
	line[17] = '0';
	continue;
      }
    }
    if (newargs[i] == 'c') {
      if (line[22] == '0') {
	line[22] = '1';
	continue;
      }
      else {
	line[22] = '0';
	continue;
      }
    } else {
      std::cout << "Invalid option input" << std::endl;
      remove("temp.txt");
      return;
    }
  }
  std::string copy = "";
  infile.open(filename);
  outfile.open("temp.txt", std::ofstream::app); //append newly toggled factors
  outfile << line << "\n";
  while (getline(infile, copy)) {
    if (copy.find("W:") != std::string::npos) {
      while (getline(infile, copy)) {
  	outfile << copy << "\n";
      }
    }
  }   
  infile.close();
  
  outfile.close();
  infile.open("temp.txt");
  outfile.open(filename);
  while (getline(infile, line)) { //start overwriting the save file
    outfile << line << "\n";
  }
  infile.close();
  outfile.close();
  remove("temp.txt");
}

void Profile::setIntervals(Interval& interval) {
  std::string filename = this->name;
  bool datefound = false;
  filename.append(".stf");
  infile.open(filename);
  while (getline(infile, line)) {
    if (line == interval.getDate()) {
      datefound = true;
      break;
    }
  }
  infile.close();
  outfile.open(filename, std::ofstream::app);
  if (!datefound) {
    outfile << interval.getDate() << "\n";
    outfile << "W:0  D:0  S:0  A:0  C:0" << "\n";
  }
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
      if (filepath.find(this->name) == std::string::npos) continue;
      // Display list of intervals
      infile.open(dirp->d_name);
      while (getline(infile, line)) {
	std::cout << line << std::endl;
      }
      infile.close();
    }
    closedir( dp );

    infile.open(dirp->d_name);
    infile.seekg (0, std::ios::end);
    getline(infile, line);
    infile.close();
  }
  std::cout << "\n" << std::endl;
}
