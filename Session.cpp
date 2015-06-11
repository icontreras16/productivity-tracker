#include "Session.h"

int start;
time_t begin;
time_t terminate;
long duration;
bool complete;
int end;
struct tm * now;
string interval;

string Session::getDurationString() {
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

time_t Session::getBegin() {
  return this->begin;
}

		    
long Session::getTerm() {
  return this->terminate;
}
	
void Session::setTerm(time_t term) {
  this->terminate = term;
  complete = true;
}
	
bool Session::isComplete() {
  return this->complete;
}
	
long Session::getDuration() {
  return (long) (terminate - begin);
}
	
string Session::getDate() {
  
  string s;
  s.append(to_string(this->now->tm_year + 1900)).append("-").append(to_string(this->now->tm_mon).append("-").append(to_string(this->now->tm_mday)));
  s = to_string(this->now->tm_mon) + "-" + to_string(this->now->tm_mday) + "-" + to_string(this->now->tm_year + 1900);
  return s;
}
	
int Session::getStart() {
  return start;
}
void Session::setStart(int hrs) {
  this->start = hrs;
}
int Session::getEnd() {
  return end;
}
void Session::setEnd(int min) {
  this->end = min;
}	

Session::Session() {
  this->begin = time(0);
  this->now = localtime( & this->begin );
  complete = false;
}

Session::~Session() {
  //delete now;
}
