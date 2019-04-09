#include <DS3231.h>
#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. of MAX7219s connected to the arduino
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

void loop() 
{
  String timeStr;
  timeStr = rtc.getTimeStr(); //HH:MM:SS
  int seconds = 10*atoi(timeStr[6]) + atoi(timeStr[7]); //Converting "SS" to integer
  Serial.println(seconds);
}
