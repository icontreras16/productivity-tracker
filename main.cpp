#include <iostream>
#include <string>
#include <sstream>
#include "Session.h"
#include "Interval.h"
#include <vector>
#include <ctime>

using namespace std;

int main() {
  vector<Session> sessions;
  Session test;
  string input = "";
  string output = std::to_string(test.getBegin());
  cout<< output << endl;
  cout << test.getDate() << endl;

  while (true) {
    cout << "Enter Command >>" << endl;
    getline(cin, input);

    if (input == "start") {
      Session newsesh;
      vector<Session>::iterator it = sessions.begin();
      sessions.insert(it, newsesh);
      
    }

    if (input == "end") {
      time_t t = time(0);
      for (Session& session : sessions) {
	if(!session.isComplete()) {
	  session.setTerm(t);
	}
      }
      Interval i (sessions);
      i.draw();
    }
    
    if (input == "exit") {
      cout << "exiting" << endl;
      return 0;
    }
  }
  return 0;
}
