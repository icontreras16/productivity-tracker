#include <ctime>
#include <string>
#ifndef DAY_H
#define DAY_H

class Day {
 private:
  bool workout, alcohol, screen, eatlate, caffeine;
  std::string date;
  struct tm * temptime;
  
 public:
  Day();
  ~Day();
  std::string getDate();
  void setRecord(std::string);
  bool hasWorkout();
  bool hasAlcohol();
  bool hasScreened();
  bool hasEatenLate();
  bool hasCaffeine();
};
#endif
