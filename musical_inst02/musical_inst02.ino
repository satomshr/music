// musical_inst02.ino ; Arduino file of musical instruments using ultrasonic sensor
// author ; sato.mshr@gmail.com
// thanks to
//    https://www.sejuku.net/blog/24359
//    https://tomari.org/main/java/oto.html

#include "hcsr04.h"

// Arduino pin assign
// Use of the tone() function will interfere with PWM output on pins 3 and 11 (on boards other than the Mega)
// https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
#define US_TRIG 7
#define US_ECHO 8
#define SPEAKER_PIN 5

#define STR_LEN 10 // cm
#define END_LEN 130 // cm

#define DELAY_MSEC 20 // ms
#define BETA 0.8 // parameter for exponentially weight average

#define MY_DEBUG 1

Hcsr04 us(US_TRIG, US_ECHO); // ultrasonic ssensor
float cm, cm_prev, cm_now;
/*
int freq[] = {220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415,
              440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 830,
              880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661,
              1760};
*/
int freq[] = {440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 830,
              880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661,
              1760};

int tone_num, idx;

#ifdef MY_DEBUG
int loop_count; // loop counting
#endif

void setup() {
  // put your setup code here, to run once:
  #ifdef MY_DEBUG
    Serial.begin(9600);
    loop_count = 0;
  #endif

  cm_prev = STR_LEN;
  tone_num = sizeof(freq) / sizeof(int);
}

void loop() {
  // put your main code here, to run repeatedly:

  cm_now = us.distance();
  cm = BETA * cm_prev + (1-BETA) * cm_now;
  idx = (int)((cm - STR_LEN) / (END_LEN - STR_LEN) * tone_num);
  if(idx < 0){
      idx = 0;
  }else if(idx > tone_num-1){
    idx = tone_num - 1;
  }

  #ifdef MY_DEBUG
    if(loop_count == 0){
      Serial.print(cm);
      Serial.print("cm, ");
      Serial.print(freq[idx]);
      Serial.print("Hz");
      Serial.println();
    }
    if(++loop_count == (int)(1000 / DELAY_MSEC)){
      loop_count = 0;
    }
  #endif

  if(cm < END_LEN && cm_now < END_LEN){
    tone(SPEAKER_PIN, freq[idx]);
    cm_prev = cm;
  } else{
    noTone(SPEAKER_PIN);
  }

  delay(DELAY_MSEC);
}
