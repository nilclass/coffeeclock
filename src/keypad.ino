
#include "time_stuff.h"

int adc_key_val[5] = { 80, 200, 390, 535, 760 };

int getKey() {
  int input = analogRead(0), k;
  if(input > adc_key_val[4]) {
    return -1;
  }
  for(k=0;k<5;k++) {
    if(input < adc_key_val[k]) {
      return k;
    }
  }
  if(k >= 5) {
    k = -1;
  }
  return k;
}


#define OFFSET(part, index) OFFSET_OBJ. part + (index == setTimePart ? offset : 0)

static void setCurrentTimePartClock(int offset) {

# define OFFSET_OBJ RTC

  RTC.getTime();

  RTC.stopClock();

  RTC.fillByYMD(
    OFFSET(year, STP_CLK_YEAR),
    OFFSET(month, STP_CLK_MON),
    OFFSET(day, STP_CLK_DAY)
  );

  RTC.fillByHMS(
    OFFSET(hour, STP_HOUR),
    OFFSET(minute, STP_MIN),
    OFFSET(second, STP_SEC)
  );

  RTC.setTime();
  RTC.startClock();

# undef OFFSET_OBJ
}

static void setCurrentTimePartAlarm(int offset) {

# define OFFSET_OBJ Alarm
# define MAX(part, n) Alarm. part = (Alarm. part == n ? 0 : (Alarm. part > n ? n - 1 : Alarm. part))

  Alarm.hour = OFFSET(hour, STP_HOUR);
  Alarm.minute = OFFSET(minute, STP_MIN);
  Alarm.second = OFFSET(second, STP_SEC);
  Alarm.channel = OFFSET(channel, STP_ALRM_CHAN);

  MAX(hour, 24);
  MAX(minute, 60);
  MAX(second, 60);
  MAX(channel, MAX_REMOTE_SWITCH);

  saveAlarm();

# undef MAX
# undef OFFSET_OBJ

}

#undef OFFSET


static void setCurrentTimePart(int offset) {
  if(setTimeTarget == STP_TARGET_CLOCK) {
    setCurrentTimePartClock(offset);
  } else {
    setCurrentTimePartAlarm(offset);
  }
}


void handleSetTimeKey(int key) {
  int maxStp = (setTimeTarget == STP_TARGET_CLOCK ?
                MAX_STP_CLOCK : MAX_STP_ALARM);

  switch(key) {
  case KEY_RIGHT:
    setTimePart = (setTimePart == maxStp ? 0 : setTimePart + 1);
    break;
  case KEY_LEFT:
    setTimePart = (setTimePart == 0 ? maxStp : setTimePart - 1);
    break;
  case KEY_UP:
    setCurrentTimePart(+1);
    break;
  case KEY_DOWN:
    setCurrentTimePart(-1);
    break;
  }

  lcd.clear();
}

void toggleRemoteSwitch(int n) {

  if(remoteSwitchState & (1 << n)) {
    mySwitch.switchOff(RC_CHANNEL, n);
  } else {
    mySwitch.switchOn(RC_CHANNEL, n);
  }

  remoteSwitchState ^= (1 << n);
}

void toggleCurrentRemoteSwitch() {
  toggleRemoteSwitch(currentRemoteSwitch);
}

void handleRemoteSwitchKey(int key) {
  switch(key) {
  case KEY_RIGHT:
    currentRemoteSwitch = (currentRemoteSwitch == MAX_REMOTE_SWITCH ? 0 :
                           currentRemoteSwitch + 1);
    break;
  case KEY_LEFT:
    currentRemoteSwitch = (currentRemoteSwitch == 0 ? MAX_REMOTE_SWITCH :
                           currentRemoteSwitch - 1);
    break;
  case KEY_UP:
  case KEY_DOWN:
    toggleCurrentRemoteSwitch();
    break;
  }
}
