
#include "time_stuff.h"

int mode = 0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int setTimePart = 0;
int setTimeTarget = STP_TARGET_CLOCK;
uint8_t remoteSwitchState = 0;
int currentRemoteSwitch = 0;

RCSwitch mySwitch = RCSwitch();

struct _Alarm Alarm = { 0, 0, 0, 0 };

/* set mode to given value, print debug message and clear display */
void switchMode(int m) {
  mode = m;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode: ");
  lcd.print(modeNames[mode]);
  delay(800);
  lcd.clear();
}

/* increment mode, until MAX_MODE reached, then reset to zero */
static void toggleMode() {
  switchMode((mode == MAX_MODE) ? 0 : (mode + 1));
}

void saveAlarm() {
  RTC.setRAM(0, (uint8_t *)&Alarm, sizeof(struct _Alarm));
}

void loadAlarm() {
  RTC.getRAM(0, (uint8_t *)&Alarm, sizeof(struct _Alarm));
}

/******************
 ** SETUP / LOOP **
 ******************/

void setup() {

  pinMode(23, OUTPUT);

  initializeDisplay();
  // SoftPWMBegin();
  // SoftPWMSetPercent(10, 100);

  Serial.begin(9600);

  RTC.startClock();

  mySwitch.enableTransmit(RC_SEND_PIN);
  mySwitch.setRepeatTransmit(8);

  loadAlarm();

  switchMode(DEFAULT_MODE);

}

int lastKey = -1;
uint8_t lastKeyTime = 0;

bool timeForAlarm() {
# define CMP(part) ( RTC. part == Alarm. part )

  return (CMP(hour) && CMP(minute) && RTC.second >= Alarm.second);

# undef CMP
}

void loop() {

  int key = getKey();

  if(key == lastKey) {
    key = -1;
  } else {
    lastKey = key;
  }

  RTC.getTime();

  if(key > -1) {
    lastKeyTime = RTC.time2000;
    Serial.print("Key pressed: ");
    Serial.println(key);
    //    SoftPWMSetPercent(10, 100);
  }

  // Turn off display light after DIM_TIMEOUT seconds
  if(lastKeyTime < (RTC.time2000 - DIM_TIMEOUT)) {
    //SoftPWMSetPercent(10, 0);
  }

  // press SELECT key to switch mode
  if(key == KEY_SELECT) {
    toggleMode();
    return;
  }

  switch(mode) {
  case MODE_SHOW_TIME:
    displayDateTime();
    if(timeForAlarm()) {
      displayAlarm();
      toggleRemoteSwitch(Alarm.channel);
      playAlarm();
      return;
    }
    break;
  case MODE_SET_TIME:
  case MODE_SET_ALARM:
    setTimeTarget = (mode == MODE_SET_TIME ? STP_TARGET_CLOCK : STP_TARGET_ALARM);
    if(key > -1) {
      handleSetTimeKey(key);
    }
    displaySetTime();
    break;
  case MODE_CHECK_BAT:
    displayBatCheck();
    break;
  case MODE_REM_SWITCH:
    if(key > -1) {
      handleRemoteSwitchKey(key);
    }
    displayRemoteSwitch();
    break;
  }

}

