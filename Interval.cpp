#include "Interval.h"

int start;
time_t begin;
time_t terminate;
long duration;
bool complete;
int end;
struct tm * now;
std::string interval;

Interval::Interval() {
  this->begin = time(0);
  this->now = localtime( & this->begin );
  complete = false;
}

Interval::~Interval() {
}

std::string Interval::getDurationString() {
  long duration, sessionhrs,sessionmin, sessionsec;

  duration = this->getDuration();
  sessionhrs = (int) this->getDuration() / (60*60);
  duration -= sessionhrs*60*60;
  sessionmin = (int) duration / 60;
  duration -= sessionmin*60;
  sessionsec = (int) duration;
  std::string s = std::to_string(sessionhrs) + " hours " + std::to_string(sessionmin) + " min " + std::to_string(sessionsec) + " sec";
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
	
std::string Interval::getDate() {
  std::string s;
  s = std::to_string(this->now->tm_mon) + "-" + std::to_string(this->now->tm_mday) + "-" + std::to_string(this->now->tm_year + 1900);
  return s;
}
