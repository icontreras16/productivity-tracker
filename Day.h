#include <ctime>
#include <string>

class Day {
 private:
  bool workout, alcohol, screen, eatlate, caffeine;
  std::string date;
  struct tm * temptime;
  
 public:
  Day();
  ~Day();
  std::string getDate();
  bool hasWorkout();
  void setWorkout(bool flag);
  bool hasAlcohol();
  void setAlcohol(bool flag);
  bool hasScreened();
  void setScreened(bool flag);
  bool hasEatenLate();
  void setEatenLate(bool flag);
  bool hasCaffeine();
  void setCaffeine(bool flag);
};
