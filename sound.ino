#include "Dot.h"
const int doremi[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047};

void sound(uint8_t part) {
  if (part==BUTTON_A) {
    tone(SPEAKER, doremi[5]);
    delay(20);
  }
  else if (part==BUTTON_B) {
    tone(SPEAKER, doremi[20]);
    delay(35);
    tone(SPEAKER, doremi[18]);
    delay(15);
  }
  else if (part==BUTTON_C) {
    tone(SPEAKER, doremi[18]);
    delay(35);
    tone(SPEAKER, doremi[20]);
    delay(35);
    tone(SPEAKER, doremi[22]);
    delay(35);
  }
  else if (part==VOLUME) {
    tone(SPEAKER, doremi[2]);
    delay(1);  
  }
}

void fanfare() {
  tone(SPEAKER, doremi[12]);
  delay(375/3);
  noTone(SPEAKER);
  delay(5);
  tone(SPEAKER, doremi[12]);
  delay(375/3);
  noTone(SPEAKER);
  delay(5);
  tone(SPEAKER, doremi[12]);
  delay(375/3);
  noTone(SPEAKER);
  delay(5);
  tone(SPEAKER, doremi[12]);
  delay(375);
  tone(SPEAKER, doremi[8]);
  delay(375);
  tone(SPEAKER, doremi[10]);
  delay(375);
  tone(SPEAKER, doremi[12]);
  delay(100);
  noTone(SPEAKER);
  delay(150);
  tone(SPEAKER, doremi[10]);
  delay(375/3);
  tone(SPEAKER, doremi[12]);
  delay(375*2);
  noTone(SPEAKER);
  delay(5);
}

void miss() {
  tone(SPEAKER, 150);
  delay(375/2);
  noTone(SPEAKER);
  delay(375/2);
  tone(SPEAKER, 150);
  delay(375*1.5);
  noTone(SPEAKER);
  delay(375*1.5);

  tone(SPEAKER, doremi[17]);
  delay(375);
  tone(SPEAKER, doremi[16]);
  delay(375/2);
  tone(SPEAKER, doremi[15]);
  delay(375);
  tone(SPEAKER, doremi[14]);
  delay(375/2);
  tone(SPEAKER, doremi[13]);
  delay(375);
  tone(SPEAKER, doremi[8]);
  delay(375*1.5);
  tone(SPEAKER, doremi[13]);
  delay(375/2);
  tone(SPEAKER, doremi[12]);
  delay(375*2);
  noTone(SPEAKER);
  delay(375);
  tone(SPEAKER, doremi[24]);
  delay(375/3);
}