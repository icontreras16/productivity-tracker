#include "Interval.h"
#include "Day.h"
#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

class Profile {
 private:
  std::string name, window;
  std::ifstream infile;
  std::ofstream outfile;
  DIR *dp;
  struct dirent *dirp;
  Day* daypt;
  bool dayflag;
  
 public:
  Profile();
  Profile(std::string, bool);
  ~Profile();
  std::string getName();
  void setName(std::string);
  bool isName();
  std::string getTimeWindow();
  void setTimeWindow(std::string);
  void setRecord(std::string);
  void setIntervals(Interval&);
  void showIntervals();
};
