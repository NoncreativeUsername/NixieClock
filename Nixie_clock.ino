// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int MinState;
int MinLastState = LOW;
int HrsState;
int HrsLastState = LOW;

void setup () {
  Serial.begin(57600);

  pinMode(6, INPUT_PULLUP);     //minutes set
  pinMode(5, INPUT_PULLUP);     //hours set

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // Dec 15, 2021 at 10:30am you would call:
  // rtc.adjust(DateTime(2021, 12, 15, 10, 30, 0));
}

void loop () {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(')');

    int Year = now.year();
    byte Month = now.month();
    byte Day = now.day();
    byte Hour = now.hour();
    byte Min = now.minute();
    byte sec = now.second();

    int MinState = digitalRead(6);    //read mins button
    int HrsState = digitalRead(5);    //read hours button


    if (MinLastState == HIGH && MinState == LOW)
    {
      Min = Min + 1;
     if (Min >= 60)
     {
      Min = 0;
      Hour = Hour + 1;
      if (Hour > 12)
      {
        Hour = 1; 
      }
     }
      rtc.adjust(DateTime(Year, Month, Day, Hour, Min, sec));
    }

    if (HrsLastState == HIGH && HrsState == LOW)
    {
      Hour = Hour + 1;
     if (Hour > 12)
     {
      Hour = 1;
     }
      rtc.adjust(DateTime(Year, Month, Day, Hour, Min, sec));
    }
    MinLastState = MinState;
    HrsLastState = HrsState;
    
    Serial.println();
    delay(2000);
}
