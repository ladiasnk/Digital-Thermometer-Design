

/*
 The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.


  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3) as contrast
*/

// include the library code:
#include <LiquidCrystal.h>

#define TempPin A0

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// LCD screen setup RS,E,D4,D5,D6,D7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //serial communication with monitor begins
  Serial.begin(9600);
 
  
  //input 
  pinMode(TempPin,INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temperature");
  
}

void loop() {
  
  //getting the voltage reading from the temperature sensor
 int reading = analogRead(TempPin);  

 // converting that reading to voltage
 float voltage = reading * 5.0;
 
 voltage /= 1024.0; 
 
  
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ; 
 //converting from 10 mv per degree with 500 mV offset
 //to degrees ((voltage - 500mV) times 100)
 
//match the temperature values to a new pwmvoltage using 
//map function(minimum temperature -40, maximum temperature 125)
  
  int pwmvoltage=map(temperatureC,-40,125,0,255);
    analogWrite(9,pwmvoltage);

    
   Serial.println(voltage);
 
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
 //print the number of seconds since reset:
 // lcd.print("           ");
  //now print out the temperature
  lcd.print("              ");
  lcd.setCursor(0, 1);
  lcd.print(temperatureC);
  lcd.print(" C");
  delay(1000);
}

