
#include <LiquidCrystal.h>
#include <DS1307new.h>
//#include <SoftPWM.h>
#include <RCSwitch.h>

/**
 ** LCD
 **/

#define LCD_COLS 16
#define LCD_ROWS  2

#define DIM_TIMEOUT 3

extern LiquidCrystal lcd;

/**
 ** MODES
 **/

extern int mode;

#define MODE_SHOW_TIME  0
#define MODE_SET_TIME   1
#define MODE_SET_ALARM  2
#define MODE_CHECK_BAT  3
#define MODE_REM_SWITCH 4

const String modeNames[] = {
  "Show Time",
  "Set Time",
  "Set Alarm",
  "Check Battery",
  "Remote Switch"
};

void switchMode(int m);

// adjust this if you invent new modes.
#define MAX_MODE 4

#define DEFAULT_MODE MODE_SHOW_TIME


/**
 ** KEYPAD
 **/

#define KEY_RIGHT  0
#define KEY_UP     1
#define KEY_DOWN   2
#define KEY_LEFT   3
#define KEY_SELECT 4

int getKey();
void handleSetTimeKey(int key);
void handleRemoteSwitchKey(int key);

/**
 ** FORMAT FUNCTIONS
 **/

String formatDate();
String formatTime();
String formatAlarm();

/**
 ** DISPLAY FUNCTIONS
 **/

void initializeDisplay();
void displayDateTime();
void displayBatCheck();
void displaySetTime();
void displayAlarm();
void displayRemoteSwitch();

/**
 ** Setting Time:
 **   - Press SELECT until in mode "Set Time"
 **   - Choose part of time to set with LEFT / RIGHT
 **     (chooses between STP_*, current in setTimePart)
 **   - Adjust selected part with UP / DOWN
 **   - Time is adjusted on the fly, so just press SELECT
 **     to return to "Show Time" mode
 **/

// COMMON
#define STP_HOUR 0
#define STP_MIN  1
#define STP_SEC  2

// CLOCK
#define STP_CLK_DAY  3
#define STP_CLK_MON  4
#define STP_CLK_YEAR 5

// ALARM
#define STP_ALRM_CHAN 3

#define MAX_STP_CLOCK  5
#define MAX_STP_ALARM  3

#define STP_TARGET_CLOCK 0
#define STP_TARGET_ALARM 1

extern int setTimeTarget;
extern int setTimePart;

extern struct _Alarm {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t channel;
} Alarm;

void saveAlarm();
void loadAlarm();

/**
 ** REMOTE SWITCH
 **/

#define RC_SEND_PIN 22
#define RC_CHANNEL "01111"
#define RC_COFFEE 4

extern RCSwitch mySwitch;
extern uint8_t remoteSwitchState;
extern int currentRemoteSwitch;

void toggleRemoteSwitch(int n);

#define MAX_REMOTE_SWITCH 8

/**
 ** MUSIC
 **/

void startPlayMelody();


void adriPlayMelody(int base, int* melody, int melodyc, int* delays, int delaysc, int nloops);

void startPlayback();

void playAlarm();
