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

/* Initialize new Profile with date, flags, and saved flags file */
Profile::Profile(std::string name, bool newmem) {
  this->name = name;
  this->window = "00:00";
  Interval iv;
  if (newmem) {
    std::cout << "\nNew profile created\n" << std::endl;
    std::string filename = name + ".stf";
    outfile.open(filename);
    outfile << iv.getDate() << " + " << this->window << "\n";
    outfile << "W:0  D:0  S:0  A:0  C:0" << "\n";
    outfile << "Total Session Time: 0 hours 0 min 0 sec\n";
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
  std::string checkname = this->name + ".stf";
  while ((dirp = readdir( dp ))) {
    filepath = std::string("./") + dirp->d_name;
    if (filepath.find(checkname) != std::string::npos) {
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
  std::ifstream infile;
  std::ofstream outfile, newfile;
  std::string filename = this->name + ".stf";
  std::string line;
  Interval iv;
  bool datematch = false;
  infile.open(filename);
  while (getline(infile, line)) {
    if (line.find(iv.getDate()) != std::string::npos) {
      datematch = true;
      break;
    }
  }
  infile.close();
  if (!datematch) {
    outfile.open(filename, std::ios::app);
    outfile << iv.getDate() << " + " << newwindow << "\n";
    outfile << "W:0  D:0  S:0  A:0  C:0" << "\n";
    outfile.close();
    return;
  }
  infile.open(filename);
  newfile.open("temp.txt");
  while (getline(infile, line)) {
    if (line.find(iv.getDate()) != std::string::npos) {
      newfile << iv.getDate() << " + " << newwindow << "\n"; //replace with the date + window
      while(getline(infile, line)) {
	newfile << line << "\n"; //retrieve factor flags and intervals as well
      }
      break;
    }
  }
  infile.close();
  newfile.close();
  remove(filename.c_str());
  rename("temp.txt", filename.c_str());
}

/*Toggles the current day's list of factor flags according to newargs*/
void Profile::setRecord(std::string newargs) {
  Interval iv;
  std::string filename = this->name;
  std::string token;
  std::string oldargs = "";
  std::string newline = "";
  bool datefound = false;
  filename.append(".stf");
  infile.open(filename); //infile has original file
  outfile.open("temp.txt", std::ofstream::app);
  while (getline(infile, line)) {
    outfile << line << "\n";
    if (line.find(iv.getDate()) != std::string::npos) {
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
  while (line.find(iv.getDate()) != std::string::npos) { 
    getline(infile, line);
  }
  getline(infile, line); //advance twice to get to current factors
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
  std::string oldval = "", newval = line;
  infile.open(filename);
  outfile.open("temp.txt", std::ofstream::app); //append newly toggled factors
  outfile << line << "\n";
  while (getline(infile, copy)) {
    if (copy.find(iv.getDate()) != std::string::npos) {
      getline(infile, copy); // go to next flags line
      oldval = copy;
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
  std::string newfile = "temp.stf";
  std::string stringval = "";
  bool datefound = false, intoken = false;
  filename.append(".stf");
  infile.open(filename);
  while (getline(infile, line)) {
    if (line.find(interval.getDate()) != std::string::npos) {
      datefound = true;
      break;
    }
  }
  infile.close();
  if (!datefound) {
    outfile.open(filename, std::ofstream::app); // will append to very bottom of file
    outfile << interval.getDate() << "\n";
    outfile << "W:0  D:0  S:0  A:0  C:0" << "\n";
    outfile << interval.getDurationString() << "\n";
    outfile << "Total Session Time: " << interval.getDurationString() << "\n";
    outfile.close();
    return;
  } else {
    int toadd = 0;
    int sumhrs = 0, summin = 0, sumsec = 0;
    int HMS [3] = {1,0,0}; // tracks if we're in hours, minutes, or seconds
    line = "";
    infile.open(filename);
    outfile.open(newfile, std::ofstream::app);
    getline(infile, line);
    while (line.find(interval.getDate()) == std::string::npos) { // get history up to current interval date
      outfile << line << "\n";
      getline(infile, line);
    }
    while(line.find("Total") == std::string::npos) { // get current date's intervals up to total
      outfile << line << "\n";
      getline(infile, line);
    }
    outfile << interval.getDurationString() << "\n"; // insert current interval
    std::vector<std::string> tosum = {line, interval.getDurationString()};
     // sum up current interval and total time
    for (int i = 0; i < tosum.size(); i++) {
      std::string addend = tosum[i];
      for (int j = 0; j < addend.length(); j++) {
	if (isdigit(addend[j])) {
	  stringval += addend[j];
	  intoken = true;
	}
	if (isdigit(addend[j]) == 0 && intoken && HMS[0] == 1) {
	  toadd = atoi(stringval.c_str());
	  sumhrs += toadd;
	  stringval = "";
	  intoken = false;
	  HMS[0] = 0;
	  HMS[1] = 1;
	}
	if (isdigit(addend[j]) == 0 && intoken && HMS[1] == 1) {
	  toadd = atoi(stringval.c_str());
	  summin += toadd;
	  stringval = "";
	  intoken = false;
	  HMS[1] = 0;
	  HMS[2] = 1;
	}
	if (isdigit(addend[j]) == 0 && intoken && HMS[2] == 1) {
	  toadd = atoi(stringval.c_str());
	  sumsec += toadd;
	  stringval = "";
	  intoken = false;
	  HMS[2] = 0;
	  HMS[0] = 1;
	}
      }
    }
    summin += (sumsec / 60); // consolidate seconds and minutes overflow
    sumsec = (sumsec % 60);
    sumhrs += (summin / 60);
    summin = (summin % 60);
    stringval = "Total Session Time: " + std::to_string(sumhrs) + " hours " + std::to_string(summin) + " min " + std::to_string(sumsec) + " sec";
    outfile << stringval << "\n";
    while (getline(infile, line)) { // get rest of history if any is left
      outfile << line << "\n";
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());
    rename("temp.stf", filename.c_str());
  }
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
      if (filepath.find(this->name + ".stf") == std::string::npos) continue;
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
