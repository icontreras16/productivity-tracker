#include "Day.h"
#include <iostream>
#include <string>

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

void Day::setRecord(std::string options) {
  std::cout << "Day options recorded\n" << std::endl;
  if (options.find("-w") != std::string::npos) {
    this->workout = true;}
  if (options.find("-d") != std::string::npos) {
    this->alcohol = true;}
  if (options.find("-s") != std::string::npos) {
    this->screen = true;}
  if (options.find("-a") != std::string::npos) {
    this->eatlate = true;}
  if (options.find("-c") != std::string::npos) {
    this->caffeine = true;}
}
bool Day::hasWorkout() {
  return this->workout;
}

bool Day::hasAlcohol() {
  return this->alcohol;
}

bool Day::hasScreened() {
  return this->screen;
}

bool Day::hasEatenLate() {
  return this->eatlate;
}

bool Day::hasCaffeine() {
  return this->caffeine;
}
