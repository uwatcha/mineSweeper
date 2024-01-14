int currentMode = -1;
const int VOLUME_MARGIN = 8;
const int VOLUME_MIN = 0;
const int BORDER_BL = 30;
const int BORDER_LU = 341;
const int BORDER_UR = 682;
const int BORDER_RB = 993;
const int VOLUME_MAX = 1023;


void volume() {
  int mode = getMode();
  if (currentMode != mode || currentMode==-1) {
    if (currentMode != -1) sound(VOLUME);
    currentMode = mode;
  }
}

int getMode() {
  float value = analogRead(VOLUME);
  if                      ( VOLUME_MIN   <= value&&value <  BORDER_BL   -VOLUME_MARGIN) return  2;
  else if (VOLUME_MARGIN+   BORDER_BL    <  value&&value <  BORDER_LU   -VOLUME_MARGIN) return  3;
  else if (VOLUME_MARGIN+   BORDER_LU    <  value&&value <  BORDER_UR   -VOLUME_MARGIN) return  1;
  else if (VOLUME_MARGIN+   BORDER_UR    <  value&&value <  BORDER_RB   -VOLUME_MARGIN) return  4;
  else if (VOLUME_MARGIN+   BORDER_RB    <  value&&value <= VOLUME_MAX)                 return  2;
  else                                                                                  return -1;
}