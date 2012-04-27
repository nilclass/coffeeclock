
#include "time_stuff.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int NOTES[] = {
  31  , 
  33  , 
  35  , 
  37  , 
  39  , 
  41  , 
  44  , 
  46  , 
  49  , 
  52  , 
  55  , 
  58  , 
  62  , 
  65  , 
  69  , 
  73  , 
  78  , 
  82  , 
  87  , 
  93  , 
  98  , 
  104 , 
  110 , 
  117 , 
  123 , 
  131 , 
  139 , 
  147 , 
  156 , 
  165 , 
  175 , 
  185 , 
  196 , 
  208 , 
  220 , 
  233 , 
  247 , 
  262 , 
  277 , 
  294 , 
  311 , 
  330 , 
  349 , 
  370 , 
  392 , 
  415 , 
  440 , 
  466 , 
  494 , 
  523 , 
  554 , 
  587 , 
  622 , 
  659 , 
  698 , 
  740 , 
  784 , 
  831 , 
  880 , 
  932 , 
  988 , 
  1047, 
  1109, 
  1175, 
  1245, 
  1319, 
  1397, 
  1480, 
  1568, 
  1661, 
  1760, 
  1865, 
  1976, 
  2093, 
  2217, 
  2349, 
  2489, 
  2637, 
  2794, 
  2960, 
  3136, 
  3322, 
  3520, 
  3729, 
  3951, 
  4186, 
  4435, 
  4699, 
  4978, 
};

#define INT_PRIM           0
#define INT_SEKUNDE        2
#define INT_KLEINE_TERZ    3
#define INT_GROSSE_TERZ    4
#define INT_QUINTE         5
#define INT_QUARTE         7
#define INT_SIXTE          9
#define INT_SEPTIME       11
#define INT_OCTAVE        12

int melodyIntervals[] = {
  INT_PRIM,
  INT_KLEINE_TERZ,
  - INT_KLEINE_TERZ
};

int melodyIntervalLength = 2;

// (in ms)
#define NOTE_WIDTH 1000
#define BASE_NOTE 38
#define MUSIC_PIN 23

int melodyPos = 0;

int lastNote = BASE_NOTE;

/* void playMelodyNote() { */
/*   melodyPos = (melodyPos == (melodyIntervalLength - 1) ? 0 : melodyPos + 1); */
/*   int i = lastNote + melodyIntervals[melodyPos]; */
/*   lastNote = i; */
/*   int note = NOTES[ i % sizeof(NOTES) ]; */
/*   Serial.print("POS "); */
/*   Serial.print(melodyPos); */
/*   Serial.print(" -- "); */
/*   Serial.print("INTERVAL "); */
/*   Serial.print(melodyIntervals[melodyPos]); */
/*   Serial.print(" -- "); */
/*   Serial.print("TONE "); */
/*   Serial.println(note); */
/*   noTone(MUSIC_PIN); */
/*   tone(MUSIC_PIN, note); */
/* } */

/* void startPlayMelody() { */
/*   pinMode(23, OUTPUT); */

/*   noInterrupts(); */
/*   TCCR5A = 0; */
/*   TCCR5B = 0; */
/*   TCNT3  = 0; */

/*   OCR1A  = 31250; */
/*   TCCR1B |= (1 << WGM12); */
/*   TCCR1B |= (1 << CS12); */
/*   TIMSK1 |= (1 << OCIE1A); */
/*   interrupts(); */
/* } */

/* ISR(TIMER1_COMPA_vect) { */
/*   playMelodyNote(); */
/* } */

#define NL_EIGHTH 240
#define NL_SIXTEENTH (NL_EIGHTH / 2)
#define NL_QUARTER (NL_EIGHTH * 2)
#define NL_HALF  (NL_QUARTER * 2)
#define NL_FULL  (NL_HALF  * 2)

#define checkAbort() if(getKey() == KEY_SELECT) { return; }

void playAlarm() {
  tone(MUSIC_PIN, NOTE_C4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_D4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_E4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_F4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_HALF);    noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_HALF);    noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_FULL);    noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_A4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_FULL);    noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_F4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_F4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_F4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_F4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_E4); delay(NL_HALF);    noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_E4); delay(NL_HALF);    noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_G4); delay(NL_QUARTER); noTone(MUSIC_PIN); checkAbort(); 
  tone(MUSIC_PIN, NOTE_C4); delay(NL_FULL);    noTone(MUSIC_PIN); checkAbort(); 

}