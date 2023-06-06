//=====================================gps=====================================
#include <TinyGPS++.h> //https://github.com/mikalhart/TinyGPSPlus
TinyGPSPlus gps;
HardwareSerial neogps(2);
#define RXD2 16 //to tx neo
#define TXD2 17 //to rx neo
//=====================================Millis=====================================
unsigned long previousMillisTakeData = 0;        // will store last time LED was updated
const long intervalTakeData = 1000;           // intervalTakeData at which to blink (milliseconds)

void setup() {
  Serial.begin(115200);
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  unsigned long currentMillis = millis();
  bool newData = false;
  
  if (currentMillis - previousMillisTakeData >= intervalTakeData) {
    // save the last time you blinked the LED
    previousMillisTakeData = currentMillis;
    
    while(neogps.available())
    {
      if (gps.encode(neogps.read())) // Parsing semua data
      newData = true;
    }
  }
  if (newData)
  {
    Serial.print(F("Location: ")); 
    if (gps.location.isValid())
    {
      Serial.print(gps.location.lat(), 6);
      Serial.print(F(","));
      Serial.print(gps.location.lng(), 6);
    }
    else
    {
      Serial.print(F("INVALID"));
    }
    Serial.println();
  }
}
