#include "time_stuff.h"

void initializeDisplay() {

  lcd.begin(LCD_COLS, LCD_ROWS);

  lcd.clear();
  lcd.setCursor(0,0);
  // lcd.print("-- RESET --");
  // delay(400);
  // lcd.clear();
  // delay(400);
  // lcd.setCursor(0,0);
  lcd.print("-- RESET --");
  delay(400);

  lcd.clear();
}

void displayAlarm() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-- ALARM --");
}

void displayDateTime() {
  RTC.getTime();

  // first line: time
  lcd.setCursor(0, 0);
  lcd.print(formatTime());

  if(RTC.time2000 % 10 > 5) {

    // second line: date
    lcd.setCursor(0, 1);
    lcd.print("D: ");
    lcd.print(formatDate());
    lcd.print("   ");

  } else {

    // second line: current alarm
    lcd.setCursor(0, 1);
    lcd.print("A: ");
    lcd.print(formatAlarm());

  }
}

void displayBatCheck() {
  lcd.clear();
  int current = analogRead(A1);
  int voltage = analogRead(A2);

  current = map(current, 0, 51, 0, 160);
  
  voltage *= 71;

  float v = float(voltage) / 1000.0;

  lcd.setCursor(0, 0);
  lcd.print("Current: ");
  lcd.print(current);
  lcd.print(" mA");
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(v);
  lcd.print(" V");
  delay(200);
}


static void displaySetTimePart(String name, uint16_t value, int isDate) {
  lcd.setCursor(0, isDate ? 1 : 0);
  if(setTimeTarget == STP_TARGET_CLOCK) {
    lcd.print(isDate ? "   "  + formatDate() : formatTime());
  } else {
    lcd.print(formatAlarm());
  }

  lcd.setCursor(0, isDate ? 0 : 1);
  lcd.print("SET " + name + ": ");
  lcd.print(value);
}

void displaySetTime() {
  RTC.getTime();

# define DISPLAY_PART(name, attr, isDate) displaySetTimePart(name, setTimeTarget == STP_TARGET_CLOCK ? RTC. attr : Alarm. attr, isDate)

  switch(setTimePart) {
  case STP_HOUR:      DISPLAY_PART("Hours", hour, 0);       break;
  case STP_MIN:       DISPLAY_PART("Minutes", minute, 0);   break;
  case STP_SEC:       DISPLAY_PART("Seconds", second, 0);   break;
  }

  if(setTimeTarget == STP_TARGET_CLOCK) {
     switch(setTimePart) {
     case STP_CLK_DAY:   displaySetTimePart("Day", RTC.day, 1);          break;
     case STP_CLK_MON:   displaySetTimePart("Month", RTC.month, 1);      break;
     case STP_CLK_YEAR:  displaySetTimePart("Year", RTC.year, 1);        break;
     }
  } else {
    switch(setTimePart) {
    case STP_ALRM_CHAN: displaySetTimePart("Channel", Alarm.channel, 0); break;
    }
  }

# undef DISPLAY_PART

}

static bool getCurrentRemoteSwitchState() {
  return remoteSwitchState & (1 << currentRemoteSwitch);
}

void displayRemoteSwitch() {
  lcd.setCursor(0, 0);
  lcd.print("Remote Switch");
  lcd.setCursor(0, 1);
  lcd.print(" #" + String(currentRemoteSwitch) + ": ");
  lcd.print(getCurrentRemoteSwitchState() ? "ON  " : "OFF");
}

