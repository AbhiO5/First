#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,  16, 2);
#define MQ2pin (0)
int buzzer = 10;
int led =9;
int sensorValue;  //variable to store sensor value
void setup()
{
  lcd.init();
  pinMode(buzzer, OUTPUT);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  GAS SENSOR ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("  WARMING UP ! ");
  delay(20000); // allow the MQ-2 to warm up for 20s
}
void loop()
{
  lcd.clear();
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
  lcd.setCursor(0,0);
  lcd.print("VALUE: ");
  lcd.print(sensorValue);
  lcd.print("ppm");
  if(sensorValue > 250)
  {
    lcd.setCursor(0,1);
    lcd.print("SMOKE DETECTED");
    tone(buzzer, 2000, 2000);
    digitalWrite(led, HIGH);
  }
  else if( sensorValue>=120 && sensorValue<=250 )
  {
    lcd.setCursor(0,1);
    lcd.print("Poor Air");
    digitalWrite(led, HIGH);
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print(" Fresh Air  ");
    noTone(buzzer);
    digitalWrite(led, LOW);
  }
  delay(2000); // wait 2s for next reading
}