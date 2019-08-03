#include <Wire.h>                 // Wire.h is a first party libary
#include <LiquidCrystal_I2C.h>    // LiquidCrystal_I2C.h is a third party libary for LCD over serial communication
#include <dht.h>                  // dht.h is for the humidity temperature module (Third Party)
#include "RTClib.h"               // RTCLib.h is a third party libary for getting the time

#define key1 22   // Key 1 (Membrane Keyboard)
#define key2 28   // Key 2 (Membrane Keyboard)
#define key3 24   // Key 3 (Membrane Keyboard)
#define key4 26   // Key 4 (Membrane Keyboard)

#define DHT11_PIN 2

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);    //I2C pins declaration

dht DHT;    // start DHT Module

RTC_DS1307 rtc;   // start rtc module
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};   //RTC Days of the week

void setup(){

  lcd.begin(16,2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight(); //To Power ON the back light
  
  while (!Serial);
  
  Serial.begin(9600);   // Start Serial on 9600 Baud    - Temperature Module + Membrane Keyboard
  Serial.begin(57600);  // Start Serial on 57600 Baud   - RTC Module saying date and time
  
  pinMode(key1, INPUT_PULLUP); // setting pins to only take input
  pinMode(key2, INPUT_PULLUP);
  pinMode(key3, INPUT_PULLUP);
  pinMode(key4, INPUT_PULLUP);

  lcd.clear(); //clearing the LCD screen

      if (! rtc.begin()) {      // Checking for RTC Module
        Serial.println("Couldn't find RTC");
        while (1);
      }
    
      if (! rtc.isrunning()) {   // If RTC Module is NOT running set the time, (Battery May need to be replaced)
        Serial.println("RTC is NOT running!");
        // following line sets the RTC to the date & time this sketch was compiled
        // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // August 8, 2019 at 9am you would call:    - Delete the // under me once the time is set
        // rtc.adjust(DateTime(2019, 8, 21, 9, 0, 0));
      }

}
void loop () {
  
  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
  
  int key1S = digitalRead(key1); // read if key 1 is pressed
  int key2S = digitalRead(key2); // read if key 2 is pressed
  int key3S = digitalRead(key3); // read if key 3 is pressed
  int key4S = digitalRead(key4); // read if key 4 is pressed

      if(!key1S) {

        Serial.println("Key 1 has been pressed");
        
        lcd.clear();
        
        DateTime now = rtc.now();   // Asks RTC for the time

        delay(100);

        lcd.print("Time");
        
        delay(1);
        
        lcd.setCursor(0,1);             // LCD Print Time
        lcd.print(now.hour(), DEC);
        lcd.print("h ");
        lcd.print(now.minute(), DEC);
        lcd.print("m ");
        lcd.print(now.second(), DEC);
        lcd.print("s");

        Serial.print(now.hour(), DEC);  // Serial Print time (57600)
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.print(':');
        Serial.print(now.second(), DEC);
        Serial.println();

        delay(3000);

        lcd.clear();

      }
      if(!key2S) {

        Serial.println("Key 2 has been pressed");
        lcd.clear();


        delay(100);

        lcd.print("Due Dates");

      }

      if(!key3S) {
        
        lcd.clear();            //Loading animation beacause why not
        lcd.print("Loading");   // refer: https://github.com/MatthewSKC/arduino2.7int/commit/ad28c4e75fe6ab158ba2342b5c18635478b1f083
        delay(300);
        lcd.clear();
        lcd.print("lOading");
        delay(300);
        lcd.clear();
        lcd.print("loAding");
        delay(300);
        lcd.clear();
        lcd.print("loaDing");
        delay(300);
        lcd.clear();
        lcd.print("loadIng");
        delay(300);
        lcd.clear();
        lcd.print("loadiNg");
        delay(300);
        lcd.clear();
        lcd.print("loadinG");
        delay(300);
        lcd.clear();
        lcd.print("LOADED!");
        
        
        delay(500);    
        
        int chk = DHT.read11(DHT11_PIN);    //takes measurements from temperature sensor

        delay(10);

        Serial.print("Temperature = ");
        Serial.println(DHT.temperature);
        Serial.print("Humidity = ");
        Serial.println(DHT.humidity);
        Serial.println("Key 3 has been pressed");

        lcd.clear();

        delay(100);

        lcd.print("Temperature (C)");
        lcd.setCursor(0,1);
        delay(10);
        lcd.print(DHT.temperature);

        delay(3000);

        lcd.clear();
        
      }

      if(!key4S) {

        Serial.println("Key 4 has been pressed");
        lcd.clear();


        delay(100);

        lcd.print("reset .. idk");

      }
  
  delay(100);


}
