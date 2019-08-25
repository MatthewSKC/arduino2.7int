#include <Wire.h>                 // Wire.h is a first party libary
#include <LiquidCrystal_I2C.h>    // LiquidCrystal_I2C.h is a third party libary for LCD over serial communication
#include <dht.h>                  // dht.h is for the humidity temperature module (Third Party)
#include "RTClib.h"               // RTCLib.h is a third party libary for getting the time
#include <SPI.h>                  // SPI.h is first party libary
#include <SD.h>                   // SD Card Module libary (1st Party)

#define key1 22   // Key 1 Function (Membrane Keyboard)
#define key2 28   // Key 2 Function (Membrane Keyboard)
#define key3 26   // Key 3 Function (Membrane Keyboard)
#define key4 24   // Key 4 Function (Membrane Keyboard)

#define DHT11_PIN 2

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);    //I2C pins declaration

dht DHT;    // start DHT Module

File dataFile;

RTC_DS1307 rtc;   // start rtc module
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};   //RTC Days of the week

File myFile;    // Start SD Card module

void setup(){

  lcd.begin(16,2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight(); //To Power ON the back light

  lcd.clear(); //clearing the LCD screen

  lcd.print("Intializing");
  
  delay(1000);
  
  while (!Serial);
 
  Serial.begin(57600);  // This is to confirm code is functioning on computer end
  
  pinMode(key1, INPUT_PULLUP); // setting pins to only take input
  pinMode(key2, INPUT_PULLUP);
  pinMode(key3, INPUT_PULLUP);
  pinMode(key4, INPUT_PULLUP);

  pinMode(48, OUTPUT);        // Reset Pin

  digitalWrite(48, LOW);      // Making sure there is no instant reset

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

  myFile.close();   // Closes any open file

  Serial.print("Initializing SD card...");

     if (!SD.begin(53)) {
      
       Serial.println("initialization failed!");
       
       lcd.clear();

       delay(200);
       
       lcd.print("SD CARD ERROR");
       
       while (1);
       
      }
      
  Serial.println("initialization done.");

  lcd.clear(); //clearing the LCD screen
  
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

        delay(1);
        
        DateTime future (now + TimeSpan(0,12,-3,0));    // Days, Hours, Minutes, Seconds -- Can have negitive intergers

        delay(100);

        lcd.print("Time-");                   // Note future.____ is used due to incorrectly setting up the module how ever it is easier to use for allowing it to be used in different time zones
        lcd.print(future.day(), DEC);
        lcd.print("/");
        lcd.print(future.month(), DEC);
        lcd.print("/");
        lcd.print(future.year(), DEC);

        Serial.print("Time - ");
        Serial.print(future.day(), DEC);
        Serial.print("/");
        Serial.print(future.month(), DEC);
        Serial.print("/");
        Serial.print(future.year(), DEC);
        
        delay(1);
        
        lcd.setCursor(0,1);             // LCD Print Time
        lcd.print(future.hour(), DEC);
        lcd.print("h ");
        lcd.print(future.minute(), DEC);
        lcd.print("m ");
        lcd.print(future.second(), DEC);
        lcd.print("s");

        Serial.print(future.hour(), DEC);  // Serial Print time (57600)
        Serial.print(':');
        Serial.print(future.minute(), DEC);
        Serial.print(':');
        Serial.print(future.second(), DEC);
        Serial.println();

        delay(3000);

        lcd.clear();

      }
      if(!key2S) {                // this can only take 16 charcters at a time or else it will display foreign text

        Serial.println("Key 2 has been pressed");
        lcd.clear();


        delay(100);

        lcd.print("Due Date;");

        myFile = SD.open("DUEDATES.txt");

        if (myFile) {
          Serial.println("DUEDATES.txt;");

          lcd.setCursor(0,1);
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {

            byte nextByte = myFile.read();
            
            lcd.print((char) nextByte);
            Serial.write((char) nextByte);

          }

          myFile.close();

        }

        else {
        // if the file didn't open, print an error:
        Serial.println("error opening DUEDATES.txt");

        lcd.setCursor(0, 1);
        
        lcd.print("SD CARD REMOVED");
        
        delay(500);
        
        }

      delay(3000);

      lcd.clear();

      }

      if(!key3S) {
        
        lcd.clear();            
        lcd.print("Loading");   // refer: https://github.com/MatthewSKC/arduino2.7int/commit/ad28c4e75fe6ab158ba2342b5c18635478b1f083

        delay(1000);    
        
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

        dataFile = SD.open("DHT11Log.txt", FILE_WRITE);
          
          Serial.print(":    Temperature = ");
        Serial.print(DHT.temperature);
        Serial.print("°C,    Humidity = ");
        Serial.print(DHT.humidity);
        Serial.println("%");
        // Write data to SD card file (DHT11Log.txt)
        dataFile.print("Temperature = ");
        dataFile.print(DHT.temperature);
        dataFile.print("°C,  Humidity = ");
        dataFile.print(DHT.humidity);
        dataFile.print("%");
        dataFile.println();
        dataFile.close();
          
delay(3000);

        lcd.clear();
        
      }

      if(!key4S) {

        lcd.clear();
        
        lcd.print("Monday;");

        myFile = SD.open("MO.txt");

        if (myFile) {
          Serial.println("MO.txt;");

          lcd.setCursor(0,1);
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {

            byte nextByte = myFile.read();
            
            lcd.print((char) nextByte);
            Serial.write((char) nextByte);

          }

          myFile.close();

        }

        else {
        // if the file didn't open, print an error:
        Serial.println("error opening MO.txt");

        lcd.setCursor(0, 1);
        
        lcd.print("SD CARD REMOVED");
        
        delay(500);
        
        }
       
      delay(3000);

      lcd.clear();

      delay(50);

      lcd.print("Tuesday;");

        myFile = SD.open("TU.txt");

        if (myFile) {
          Serial.println("TU.txt;");

          lcd.setCursor(0,1);
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {

            byte nextByte = myFile.read();
            
            lcd.print((char) nextByte);
            Serial.write((char) nextByte);

          }

          myFile.close();

        }

        else {
        // if the file didn't open, print an error:
        Serial.println("error opening TU.txt");

        lcd.setCursor(0, 1);
        
        lcd.print("SD CARD REMOVED");
        
        delay(500);
        
        }

      delay(3000);

      lcd.clear();

      lcd.print("Wensday;");

        myFile = SD.open("WE.txt");

        if (myFile) {
          Serial.println("WE.txt;");

          lcd.setCursor(0,1);
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {

            byte nextByte = myFile.read();
            
            lcd.print((char) nextByte);
            Serial.write((char) nextByte);

          }

          myFile.close();

        }

        else {
        // if the file didn't open, print an error:
        Serial.println("error opening WE.txt");

        lcd.setCursor(0, 1);
        
        lcd.print("SD CARD REMOVED");
        
        delay(500);
        
        }
       

      delay(3000);

      lcd.clear();

      lcd.print("Thursday;");

        myFile = SD.open("TH.txt");

        if (myFile) {
          Serial.println("TH.txt;");

          lcd.setCursor(0,1);
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {

            byte nextByte = myFile.read();
            
            lcd.print((char) nextByte);
            Serial.write((char) nextByte);

          }

          myFile.close();

        }

        else {
        // if the file didn't open, print an error:
        Serial.println("error opening TH.txt");

        lcd.setCursor(0, 1);
        
        lcd.print("SD CARD REMOVED");
        
        delay(500);
        
        }
       

      delay(3000);

      lcd.clear();

      lcd.print("Friday;");

        myFile = SD.open("FR.txt");

        if (myFile) {
          Serial.println("FR.txt;");

          lcd.setCursor(0,1);
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {

            byte nextByte = myFile.read();
            
            lcd.print((char) nextByte);
            Serial.write((char) nextByte);

          }

          myFile.close();

        }

        else {
        // if the file didn't open, print an error:
        Serial.println("error opening FR.txt");

        lcd.setCursor(0, 1);
        
        lcd.print("SD CARD REMOVED");
        
        delay(500);
        
        }
       

      delay(3000);

      lcd.clear();

      lcd.print("Sunday;");

        myFile = SD.open("SU.txt");

        if (myFile) {
          Serial.println("SU.txt;");

          lcd.setCursor(0,1);
      
          // read from the file until there's nothing else in it:
          while (myFile.available()) {

            byte nextByte = myFile.read();
            
            lcd.print((char) nextByte);
            Serial.write((char) nextByte);

          }

          myFile.close();

        }

        else {
        // if the file didn't open, print an error:
        Serial.println("error opening SU.txt");

        lcd.setCursor(0, 1);
        
        lcd.print("SD CARD REMOVED");
        
        delay(500);
        
        }
       

      delay(3000);

      lcd.clear();

   }
  
  delay(100);

}
