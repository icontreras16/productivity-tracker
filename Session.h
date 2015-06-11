#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#ifndef SESSION_H
#define SESSION_H

using namespace std;

class Session {
	
private:
  int start;
  time_t begin;
  time_t terminate;
  long duration;
  bool complete;
  int end;
  struct tm * now;
  string interval;
  
 public:
  Session();
  ~Session();
  string getDurationString();
  long getBegin();
  long getTerm();
  void setTerm(time_t term);
  bool isComplete();
  long getDuration();
  string getDate();
  void setBegin(time_t time);
  int getStart();
  void setStart(int hrs);
  int getEnd();
  void setEnd(int min);
};
#endif
