#include "Interval.h"
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
  bool init;
  
 public:
  Profile();
  Profile(std::string, bool);
  ~Profile();
  bool isInit();
  std::string getName();
  void setName(std::string);
  bool isName();
  std::string getTimeWindow();
  void setTimeWindow(std::string);
  void setIntervals(Interval&);
  void showIntervals();
};
