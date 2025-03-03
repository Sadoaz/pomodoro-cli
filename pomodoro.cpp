#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;

class Session {

private:
  vector<int> duration;
  vector<int> pauses;
};

void parseTime(int minutes) {

  ostringstream time_stream;

  int hours = (minutes / 60);

  int org_minutes = (minutes - (hours * 60)) % 60;

  int seconds = minutes * 60;

  int temp_seconds = 0;

  int paused = 0;

  while (seconds > 0) {

    int ch = getch();

    if (ch == ' ') {
      paused = !paused;
    }

    if (paused) {
      continue;
    }

    if (org_minutes == 0 && hours != 0) {
      org_minutes = 60;
      hours--;
    }

    if (temp_seconds == 0) {
      org_minutes--;
      temp_seconds = 60;
    }

    temp_seconds--;
    seconds--;

    time_stream.str("");

    time_stream << std::setw(2) << std::setfill('0') << hours << ":"
                << std::setw(2) << std::setfill('0') << org_minutes << ":"
                << std::setw(2) << std::setfill('0') << temp_seconds;

    mvprintw(10, 17, "%s", time_stream.str().c_str());
    refresh();
    napms(1000);
  }
}

int main() {

  initscr();

  nodelay(stdscr, TRUE); // Gjør getch() ikke-blokkerende

  mvprintw(5, 10, "Press space to pause/resume");
  refresh();

  curs_set(0); // Skjul markøren
               //  parseTime(50);
  parseTime(1);

  system("/home/william/go/bin/confetty &");
  sleep(1);                    // Vent i 5 sekunder
  system("pkill -f confetty"); // Dreper alle `confetty` prosesser

  endwin();

  return 0;
}
