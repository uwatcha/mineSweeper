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