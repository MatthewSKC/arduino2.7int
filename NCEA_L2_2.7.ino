/* www.learningbuz.com */
/*Impport following Libraries*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
void setup() 
{

lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light
//lcd.backlight();// To Power OFF the back light
pinMode(22, INPUT_PULLUP);
pinMode(24, INPUT_PULLUP);
pinMode(26, INPUT_PULLUP);
pinMode(28, INPUT_PULLUP);
Serial.begin(9600);
delay(100);
digitalWrite(22, LOW);
digitalWrite(24, LOW);
digitalWrite(26, LOW);
digitalWrite(28, LOW);
}

void loop() 
{
//Write your code
lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.clear();
if (digitalRead(22) == HIGH) {
  lcd.clear();
  lcd.setCursor(0,0);
  delay(100);
  lcd.print("INPUT A");
  delay(100);
  Serial.println("A");
  digitalWrite(22, LOW);
}

if (digitalRead(24) == HIGH) {
  lcd.clear();
  lcd.setCursor(0,0);
  delay(100);
  lcd.print("INPUT B");
  Serial.println("B");
  delay(100);
  digitalWrite(24, LOW);
}

if (digitalRead(26) == HIGH) {
  lcd.clear();
  lcd.setCursor(0,0);
  delay(100);
  lcd.print("INPUT C");
  Serial.println("C");
  delay(100);
  digitalWrite(26, LOW);
}

if (digitalRead(28) == HIGH) {
  lcd.clear();
  lcd.setCursor(0,0);
  delay(100);
  lcd.print("INPUT D");
  Serial.println("D");
  delay(100);
  digitalWrite(28, LOW);
}
}
