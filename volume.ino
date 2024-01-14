int currentMode = -1;
int VOLUME_MARGIN = 8;

void volume() {
  int mode = getMode();
  if (currentMode != mode || currentMode==-1) {
    if (currentMode != -1) sound(VOLUME);
    currentMode = mode;
  }
}

int getMode() {
  float value = analogRead(VOLUME);
  if                      ( 0   <= value&&value <    30   -VOLUME_MARGIN) return  2;
  else if (VOLUME_MARGIN+  30   <  value&&value <   341   -VOLUME_MARGIN) return  3;
  else if (VOLUME_MARGIN+  341  <  value&&value <   682   -VOLUME_MARGIN) return  1;
  else if (VOLUME_MARGIN+  682  <  value&&value <   993   -VOLUME_MARGIN) return  4;
  else if (VOLUME_MARGIN+  993  <  value&&value <= 1023)                  return  2;
  else                                                                    return -1;
}