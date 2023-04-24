// Define button pins
#define HOUR_BUTTON A0
#define MINUTE_BUTTON A1

// Define variables for storing time
int hours = 12;
int minutes = 0;
int seconds = 0;

//define digital pins
int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin4 = 5;
int pin5 = 6;
int pin6 = 7;
int pin7 = 8;
int pin8 = 9;
int pin9 = 10;
int pin10 = 11;

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

  //create 4 bit representation of each digit
  String binStrHH = String(hours / 10, BIN);    //hours tens place
  String binStrHL = String(hours % 10, BIN);    //hours ones place
  String binStrMH = String(hours / 10, BIN);    //minutes tens place
  String binStrML = String(hours % 10, BIN);    //minutes ones place

  // Output the hours tens place binary string to the four digital output pins
  //only need 1 pin for 0 and 1
  //if there are enough open pins add one to enable 24 hr time
  digitalWrite(pin1, binStrHH.charAt(3) == '1' ? HIGH : LOW);   //LSB

  // Output the binary string to the four digital output pins
  //only need 2 pins for 0-2
  digitalWrite(pin2, binStrHL.charAt(2) == '1' ? HIGH : LOW);
  digitalWrite(pin3, binStrHL.charAt(3) == '1' ? HIGH : LOW);   //LSB

  // Output the binary string to the four digital output pins
  //need three pins for 0-6
  digitalWrite(pin4, binStrMH.charAt(1) == '1' ? HIGH : LOW);   //MSB
  digitalWrite(pin5, binStrMH.charAt(2) == '1' ? HIGH : LOW);
  digitalWrite(pin6, binStrMH.charAt(3) == '1' ? HIGH : LOW);   //LSB

  // Output the binary string to the four digital output pins
  //need 4 pins for 0-9
  digitalWrite(pin7, binStrML.charAt(0) == '1' ? HIGH : LOW);   //MSB
  digitalWrite(pin8, binStrML.charAt(1) == '1' ? HIGH : LOW);
  digitalWrite(pin9, binStrML.charAt(2) == '1' ? HIGH : LOW);
  digitalWrite(pin10, binStrML.charAt(3) == '1' ? HIGH : LOW);   //LSB
  
  // Print time on Serial Monitor
  /*Serial.print(hours / 10);
  Serial.print(hours % 10);
  Serial.print(":");
  Serial.print(minutes / 10);
  Serial.print(minutes % 10);
  Serial.println();
  */
  //delay(200);
}
