/* I2C LCD with Arduino example code. More info: https://www.makerguides.com */
// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.
int nrOfCogs;
void setup() {
  // Initiate the LCD:
  pinMode(2,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  nrOfCogs = 0;
  lcd.init();
  lcd.backlight();
}
void loop() {
  // Print 'Hello World!' on the first line of the LCD:
  //lcd.clear();
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("Cogs to make: "); // Print the string "Hello World!"
  lcd.setCursor(0,1);
  lcd.print(nrOfCogs);
  while(digitalRead(7) == HIGH && digitalRead(2) == HIGH && digitalRead(4) == HIGH){
    
  }
  if(digitalRead(2) == LOW){
    nrOfCogs -= 1;
    lcd.setCursor(0,1);
  lcd.print(nrOfCogs);
    delay(300);
  }
  else{
    nrOfCogs += 1;
    lcd.setCursor(0,1);
  lcd.print(nrOfCogs);
    delay(300);
  }
  
}
