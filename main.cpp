#include <iostream>
#include <string>
#include <sstream>
#include "Session.h"
#include <vector>
#include <ctime>

using namespace std;

int main() {
  vector<Session> sessions;
  string input = "";
  Session* newsesh;

  while (true) {
    cout << "Enter Command >>" << endl;
    getline(cin, input);

    if (input == "start") {
      newsesh = new Session();
      cout << "New session started\n" << endl;
    }

    if (input == "help") {
      cout << "Available commands:\n" << endl;
      cout << "start" << endl;
      cout << "end" << endl;
      cout << "cancel" << endl;
      cout << "sessions\n" << endl;
    }
    
    if (input == "cancel") {
      delete(newsesh);
      cout << "session cancelled\n" << endl;
    }

    if (input == "end") {
      time_t t = time(0);
      newsesh->setTerm(t);
      sessions.insert(sessions.begin(), *newsesh);
      delete(newsesh);
    }

    if (input == "sessions") {      
      string lastdate = "";
      for (Session& session : sessions) {
	if (session.getDate() != lastdate) {
	  lastdate = session.getDate();
	  cout << lastdate << endl;
	}	  
	cout << session.getDurationString() << "\n" << endl;
      }
    }
    
    if (input == "exit") {
      cout << "exiting\n" << endl;
      return 0;
    }
  }
  return 0;
}
