#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "Session.h"

using namespace std;

class Interval {
 private:
  vector<Session> sessions;
  time_t date;
  string lastdate;
  
 public:
  Interval(vector<Session> sessions);
  void draw();
};
