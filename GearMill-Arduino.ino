#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

#define UP_PIN 4
#define DOWN_PIN 7
#define OK_PIN 2

#define STEP_PIN 9
#define DIR_PIN 8
#define MOTOR_STEPS 200

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
uint16_t nrOfCogs;
uint16_t motorStepsPerCog;
uint16_t rest;

void setup() {
  // Initiate the LCD:
  pinMode(OK_PIN,INPUT_PULLUP);
  pinMode(UP_PIN,INPUT_PULLUP);
  pinMode(DOWN_PIN,INPUT_PULLUP);
  
  pinMode(STEP_PIN,OUTPUT);
  pinMode(DIR_PIN,OUTPUT);
  
  nrOfCogs = 20;
  lcd.init();
  lcd.backlight();
}
void loop() {
  lcd.clear();
  startScreen();
  
}

void startScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Antal kuggar: ");
  lcd.setCursor(0,1);
  lcd.print(nrOfCogs);
  while(digitalRead(OK_PIN) == LOW){
    
  }
  while(true){
  while(digitalRead(UP_PIN) == HIGH && digitalRead(DOWN_PIN) == HIGH && digitalRead(OK_PIN) == HIGH){
    
  }
  if(digitalRead(DOWN_PIN) == LOW){
    if(nrOfCogs>1){
      nrOfCogs -= 1;
      lcd.setCursor(0,1);
      lcd.print(nrOfCogs);
      lcd.print("            ");
    }
    delay(250);
  }
  else if (digitalRead(UP_PIN) == LOW) {
    nrOfCogs += 1;
    lcd.setCursor(0,1);
    lcd.print(nrOfCogs);
    lcd.print("            ");
    delay(250);
  }
  else if (digitalRead(OK_PIN) == LOW) {
    delay(50);
    motorStepsPerCog = MOTOR_STEPS/nrOfCogs;
    rest = MOTOR_STEPS%nrOfCogs;
    stepFunction();
  }
  }
}

void stepFunction(){
  int8_t cogCount = 1;
  lcd.clear();
  while(true){
  lcd.setCursor(0, 0);
  lcd.print("Kugg nr: ");
  lcd.setCursor(9,0);
  lcd.print(cogCount);
    lcd.print("  ");
  lcd.setCursor(0,1);
  lcd.print("Avbryt med OK   ");
  lcd.print(cogCount);
  while(digitalRead(OK_PIN) == LOW){
    
  }
  while(digitalRead(UP_PIN) == HIGH && digitalRead(DOWN_PIN) == HIGH && digitalRead(OK_PIN) == HIGH){
    
  }
  if(digitalRead(DOWN_PIN) == LOW){
    cogCount-=1;
    if(cogCount <= 0){
      cogCount = 1;
    }
    else{
      digitalWrite(DIR_PIN, LOW);
      stepMotor(motorStepsPerCog, rest);
      delay(300);
    }
  }
  else if (digitalRead(UP_PIN) == LOW){
    cogCount+=1;
    if(cogCount > nrOfCogs){
      rest = MOTOR_STEPS%nrOfCogs;
      cogCount = 1;
    }
    digitalWrite(DIR_PIN, HIGH);
    stepMotor(motorStepsPerCog, rest);
    delay(300);
  }
  else if (digitalRead(OK_PIN) == LOW){
    delay(50);
    startScreen();
  }
  }
}

void stepMotor(uint16_t steps, uint16_t &rest){
  for(int x = 0; x < steps; x++){
    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(800);
    digitalWrite(STEP_PIN,LOW);
    delayMicroseconds(800);
  }
  if(rest > 0){
    digitalWrite(STEP_PIN,HIGH);
    delayMicroseconds(800);
    digitalWrite(STEP_PIN,LOW);
    delayMicroseconds(800);
    rest --;
  }
}
