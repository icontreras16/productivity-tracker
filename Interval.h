#include <ctime>
#include <iostream>
#include <string>
#include <iterator>
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
  Interval(std::string);
  ~Interval();
  std::string getDurationString();
  long getTerm();
  void setTerm(time_t, std::string);
  bool isComplete();
  long getDuration();
  std::string getDate();

};
#endif
