#include "Day.h"

// boolean values to save whether or not a sleep-affecting factor
// occurred on this particular day
bool workout, alcohol, screen, eatlate, caffeine;
std::string date = "";
struct tm * temptime;

// this constructor does not take parameters because the use could be accessing Day object multiple times per day, adding in factors
Day::Day() {
  time_t t = time(0);
  this->workout = false;
  this->alcohol = false;
  this->screen = false;
  this->eatlate = false;
  this->caffeine = false;
  this->temptime = localtime( & t );
  this->date = std::to_string(this->temptime->tm_mon) + "-" + std::to_string(this->temptime->tm_mday) + "-" + std::to_string(this->temptime->tm_year + 1900);
}

Day::~Day() {}

std::string Day::getDate() {
  return this->date;
}

bool Day::hasWorkout() {
  return this->workout;
}

void Day::setWorkout(bool flag) {
  this->workout = flag;
}

bool Day::hasAlcohol() {
  return this->alcohol;
}

void Day::setAlcohol(bool flag) {
  this->alcohol = flag;
}

bool Day::hasScreened() {
  return this->screen;
}

void Day::setScreened(bool flag) {
  this->screen = flag;
}

bool Day::hasEatenLate() {
  return this->eatlate;
}

void Day::setEatenLate(bool flag) {
  this->eatlate = flag;
}

bool Day::hasCaffeine() {
  return this->caffeine;
}

void Day::setCaffeine(bool flag) {
  this->caffeine = flag;
}
