#include <Wire.h>                 // Wire.h is a first party libary
#include <LiquidCrystal_I2C.h>    // LiquidCrystal_I2C.h is a third party libary for LCD over serial communication

#define key1 22
#define key2 28
#define key3 24
#define key4 26

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);    //I2C pins declaration

#include <dht.h>
dht DHT;
#define DHT11_PIN 2

void setup(){

  lcd.begin(16,2); //Defining 16 columns and 2 rows of lcd display
  lcd.backlight(); //To Power ON the back light
  
  Serial.begin(9600);

  pinMode(key1, INPUT_PULLUP); // setting pins to only take input
  pinMode(key2, INPUT_PULLUP);
  pinMode(key3, INPUT_PULLUP);
  pinMode(key4, INPUT_PULLUP);

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

        delay(100);

        lcd.print("Time");

      }
      if(!key2S) {

        Serial.println("Key 2 has been pressed");
        lcd.clear();


        delay(100);

        lcd.print("Due Dates");

      }

      if(!key3S) {
        
        lcd.clear();
        lcd.print("Loading...");
        
        delay(1500);    // refer: https://github.com/MatthewSKC/arduino2.7int/commit/ad28c4e75fe6ab158ba2342b5c18635478b1f083

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
        
      }

      if(!key4S) {

        Serial.println("Key 4 has been pressed");
            lcd.clear();


        delay(100);

        lcd.print("reset .. idk");

      }
  
  delay(100);

}
