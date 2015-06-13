#include <ctime>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
	
private:
  int start;
  time_t begin;
  time_t terminate;
  long duration;
  bool complete;
  int end;
  struct tm * now;
  std::string interval;
  
 public:
  Interval();
  ~Interval();
  std::string getDurationString();
  long getTerm();
  void setTerm(time_t term);
  bool isComplete();
  long getDuration();
  std::string getDate();

};
#endif
