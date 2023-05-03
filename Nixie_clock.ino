// Define button pins
#define HOUR_BUTTON A0
#define MINUTE_BUTTON A1

// Define variables for storing time
int hours = 12;
int minutes = 0;
int seconds = 0;

//define digital pins
int pin1 = 8;

int pin2 = 9;
int pin3 = 11;
int pin4 = 12;
int pin5 = 10;

int pin6 = 6;
int pin7 = 7;
int pin8 = 13;

int pin9 = 2;
int pin10 = 3;
int pin11 = 4;
int pin12 = 5;

//counter for how long the button has been pressed
int hourCount = 0;
int minCount = 0;

// Define variable for keeping track of last time the time was updated
unsigned long lastUpdateTime = 0;

void setup() {
  // Set button pins as inputs with pull-up resistors
  pinMode(HOUR_BUTTON, INPUT);
  pinMode(MINUTE_BUTTON, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin11, OUTPUT);
  pinMode(pin12, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  
  // Read hour button state and debounce
  if (!digitalRead(HOUR_BUTTON))
  {
    hourCount = 0;      //reset counter if button not pressed
  }
  else
  {
    hourCount++;        //increment counter if pressed

    if (hourCount == 12)
    {
      hours++;          //if button pressed consistently then increment hour
      if (hours >= 13)
      {
        hours = 1;
      }
    }
  }

  if (!digitalRead(MINUTE_BUTTON))
  {
    minCount = 0;
  }
  else
  {
    minCount++;
    if (minCount == 15)
    {
      minutes++;
      if (minutes >=60)
      {
        minutes = 0;
      }
    }
  }
 
  // Increment time if 1 second has elapsed
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= 1000) {
    seconds++;
    if (seconds == 60) {
      seconds = 0;
      minutes++;
      if (minutes == 60) {
        minutes = 0;
        hours++;
      }
    }
    lastUpdateTime = currentTime;
  }
 
  int binStrHH = hours /10;
  int binStrHL = hours % 10;
  int binStrMH = minutes / 10;
  int binStrML = minutes % 10;
  
  // Output the hours tens place binary string to the four digital output pins
  //only need 1 pin for 0 and 1
  //if there are enough open pins add one to enable 24 hr time

  digitalWrite(pin1, bitRead(hours / 10, 0));

  digitalWrite(pin2, bitRead(hours % 10, 0));
  digitalWrite(pin3, bitRead(hours % 10, 1));
  digitalWrite(pin4, bitRead(hours % 10, 2));
  digitalWrite(pin5, bitRead(hours % 10, 3));

  digitalWrite(pin8, bitRead(minutes / 10, 0));
  digitalWrite(pin7, bitRead(minutes / 10, 1));
  digitalWrite(pin6, bitRead(minutes / 10, 2));
  //last digit completley doesn't light up, probably a bad connection or tube was damaged after my last test 
  digitalWrite(pin12, bitRead(minutes % 10, 0));
  digitalWrite(pin11, bitRead(minutes % 10, 1));
  digitalWrite(pin10, bitRead(minutes % 10, 2));
  digitalWrite(pin9, bitRead(minutes % 10, 3));

  /*//manually set pins for troubleshooting
  digitalWrite(pin1,HIGH);
  
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,LOW); 
  digitalWrite(pin4,HIGH);  //4
  digitalWrite(pin5,LOW);
  
  digitalWrite(pin6,LOW);
  digitalWrite(pin7,LOW);
  digitalWrite(pin8,LOW);
  
  digitalWrite(pin9,LOW);
  digitalWrite(pin10,LOW);
  digitalWrite(pin11,LOW);
  digitalWrite(pin12,LOW);
  */
  
  // Print time on Serial Monitor for troubleshooting
  Serial.print(hours / 10);
  Serial.print(hours % 10);
  Serial.print(":");
  Serial.print(minutes / 10);
  Serial.print(minutes % 10);
  Serial.println();
  Serial.print(bitRead(hours%10, 1));
  Serial.println();
  
  //delay(200);
}
