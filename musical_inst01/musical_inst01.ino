// musical_inst01.ino ; Arduino file of musical instruments using ultrasonic sensor
// author ; sato.mshr@gmail.com

#include "hcsr04.h"

// Arduino pin assign
// Use of the tone() function will interfere with PWM output on pins 3 and 11 (on boards other than the Mega)
// https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
#define US_TRIG 7
#define US_ECHO 8
#define SPEAKER_PIN 5

#define C0_LEN 40 // cm
#define C1_LEN 70 // cm
#define FAR_LEN 100 // cm
#define C0_HZ 440 // Hz

#define DELAY_MSEC 30 // ms
#define BETA 0.9 // parameter for exponentially weight average

#define MY_DEBUG 1

Hcsr04 us(US_TRIG, US_ECHO); // ultrasonic ssensor
float cm, cm_prev, cm_now, freq;

#ifdef MY_DEBUG
int loop_count; // loop counting
#endif

void setup() {
  // put your setup code here, to run once:
  #ifdef MY_DEBUG
    Serial.begin(9600);
    loop_count = 0;
  #endif

  cm_prev = C0_LEN;
}

void loop() {
  // put your main code here, to run repeatedly:

  cm_now = us.distance();
  cm = BETA * cm_prev + (1-BETA) * cm_now;
  freq = C0_HZ * pow(2, (cm - C0_LEN)/(C1_LEN - C0_LEN));

  #ifdef MY_DEBUG
    if(loop_count == 0){
      Serial.print(cm);
      Serial.print("cm, ");
      Serial.print(freq);
      Serial.print("Hz");
      Serial.println();
    }
    if(++loop_count == (int)(1000 / DELAY_MSEC)){
      loop_count = 0;
    }
  #endif

  if(cm < FAR_LEN && cm_now < FAR_LEN){
    tone(SPEAKER_PIN, (int)freq);
    cm_prev = cm;
  } else{
    noTone(SPEAKER_PIN);
  }

  delay(DELAY_MSEC);
}
