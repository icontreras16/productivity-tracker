#include "Interval.h"

int start;
time_t begin;
time_t terminate;
long duration;
bool complete;
int end;
struct tm * now;
string interval;

Interval::Interval() {
  this->begin = time(0);
  this->now = localtime( & this->begin );
  complete = false;
}

Interval::~Interval() {
}

string Interval::getDurationString() {
  long duration, sessionhrs,sessionmin, sessionsec;

  duration = this->getDuration();
  sessionhrs = (int) this->getDuration() / (60*60);
  duration -= sessionhrs*60*60;
  sessionmin = (int) duration / 60;
  duration -= sessionmin*60;
  sessionsec = (int) duration;
  string s = to_string(sessionhrs) + " hours " + to_string(sessionmin) + " min " + to_string(sessionsec) + " sec";
  return s;
}

		    
long Interval::getTerm() {
  return this->terminate;
}
	
void Interval::setTerm(time_t term) {
  this->terminate = term;
  complete = true;
}
	
bool Interval::isComplete() {
  return this->complete;
}
	
long Interval::getDuration() {
  return (long) (terminate - begin);
}
	
string Interval::getDate() {
  string s;
  s = to_string(this->now->tm_mon) + "-" + to_string(this->now->tm_mday) + "-" + to_string(this->now->tm_year + 1900);
  return s;
}
