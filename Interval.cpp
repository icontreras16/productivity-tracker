#include "Interval.h"

vector<Session> sessions;
time_t date;
string lastdate;
  
void Interval::draw() {
  long duration, sessionhrs, sessionmin, sessionsec;

  for (Session& session : sessions) {
    string temp = session.getDate();

    if (lastdate != temp) {
      cout << temp << endl;
      lastdate = temp;
    }

    // print out session time interval
    duration = session.getDuration();
    sessionhrs = (int) session.getDuration() / (60*60);
    duration -= sessionhrs*60*60;
    sessionmin = (int) duration / 60;
    duration -= sessionmin*60;
    sessionsec = (int) duration;
    cout << "Duration: " << sessionhrs << " hours " << sessionmin << " minutes " << sessionsec << " seconds" << endl;
  }
}

Interval::Interval (vector<Session> sessions) {
  this->sessions = sessions;
}
