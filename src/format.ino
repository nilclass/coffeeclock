
#include "time_stuff.h"



static String twoDigit(int i) {
  return (i < 10 ? "0" : "") + String(i);
}

String formatDate() {
  return
    twoDigit(RTC.day)   + "." +
    twoDigit(RTC.month) + "." +
    String(RTC.year);
}

String formatTime() {
  return
    twoDigit(RTC.hour)   + ":" +
    twoDigit(RTC.minute) + ":" +
    twoDigit(RTC.second);
}

String formatAlarm() {
  return
    twoDigit(Alarm.hour)   + ":"  +
    twoDigit(Alarm.minute) + ":"  +
    twoDigit(Alarm.second) + " #" +
    String(Alarm.channel);
}