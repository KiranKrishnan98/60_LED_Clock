#include <DS3231.h>
#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 2); //DIN, CLK, LOAD, No. of MAX7219s connected to the arduino
DS3231 rtc(SDA, SCL);

void setup() 
{
  Serial.begin(115200);
  lc.shutdown(0,false);
  
  lc.setIntensity(0,15); // Set brightness to a medium value. 0 --> Address of matrix, 8 --> Intensity (from 0 to 15 only)
  rtc.begin();

  //Uncomment to set day/date/time
  //rtc.setDOW(TUESDAY);
  //rtc.setTime(12, 0, 0); //HH:MM:SS 24 hr format
  //rtc.setDate(1, 1, 2014); //DD:MM:YYYY
  
}

const int sevenSeg[10][8] = {
//dp, a, b, c, d, e, f, g 
  {0, 1, 1, 1, 1, 1, 1, 0},         //0
  {0, 0, 1, 1, 0, 0, 0, 0},         //1
  {0, 1, 1, 0, 1, 1, 0, 1},         //2
  {0, 1, 1, 1, 1, 0, 0, 1},         //3
  {0, 0, 1, 1, 0, 0, 1, 1},         //4
  {0, 1, 0, 1, 1, 0, 1, 1},         //5
  {0, 1, 0, 1, 1, 1, 1, 1},         //6
  {0, 1, 1, 1, 0, 0, 0, 0},         //7
  {0, 1, 1, 1, 1, 1, 1, 1},         //8
  {0, 1, 1, 1, 0, 0, 1, 1}          //9
};

int timeDig[6];
String timeStr;

void setSevenSeg (int timeDig[]) {
  for (int i = 0; i<6; ++i) {
    for (int j = 0; j<8; ++j) {
      lc.setLed(0, i, j, sevenSeg[timeDig[i]][j]);
    }
  }
}

void loop() 
{
  timeStr = rtc.getTimeStr(); //HH:MM:SS

  //Isolate the digits (ASCII value of '0' is 48)
  timeDig[0] = (int)timeStr[7] - 48;    //s0
  timeDig[1] = (int)timeStr[6] - 48;    //s1
  timeDig[2] = (int)timeStr[4] - 48;    //m0
  timeDig[3] = (int)timeStr[3] - 48;    //m1
  timeDig[4] = (int)timeStr[1] - 48;    //h0
  timeDig[5] = (int)timeStr[0] - 48;    //h1

  //Get the seconds, minutes, and hours as integers
  int secs = (10*timeDig[1]) + timeDig[0];
  int mins = (10*timeDig[3]) + timeDig[2];
  int hrs = (10*timeDig[5]) + timeDig[4];
}
