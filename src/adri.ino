
/***** THIS FILE IS NOT IN USE *****/

#include "time_stuff.h"


#define OCTAVE 23
#define TUNE 1.0/(24*60*60)*pow(2,OCTAVE)
#define BPM 120

int note(int num, int octave=0){
    if(num > 12)
       octave = num /12;
    return round(
                 (TUNE+TUNE/12.0*(num%12))*pow(2,octave)
          );
}

unsigned int secs(float percent){
	 return round(
                      (60.0 *1000 * percent/ BPM)
                     );
}
void adriPlayMelody(int base, int* melody, int melodyc, int* delays, int delaysc, int nloops=0){
    unsigned int max=melodyc*nloops;
    for(int i = 0; max == 0 || i < max; i++){
     	    base += melody[i%(melodyc)];
     	    unsigned int t = delays[i%(delaysc)+1];
            noTone(23);
     	    tone(23, note(base));
            delay(t);
     }
    noTone(23);
}


