#include <LiquidCrystal.h>
#include <DHT11.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int GAS_SENSOR = A0;
const int FIRE = A1;
const int RED = 6;
const int GREEN = 5;
const int BUZZER = 2;
const int FAN = 4;

DHT11 dht11(3);
void setup()
{
  lcd.begin(16,2);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(FIRE, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(FAN, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("Kitchen Monitor");
  lcd.setCursor(2,1);
  lcd.print("System");
  delay(2000);
  lcd.clear();
}
void loop()
{
  int temperature = dht11.readTemperature();
  int gasADC = analogRead(GAS_SENSOR);
  int fireADC = analogRead(FIRE);
  int GAS = map(gasADC, 0, 1023, 0, 100);
  int fire = map(fireADC, 0, 1023, 0, 100);
   
  lcd.clear();
  if (GAS >= 60)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(FAN, HIGH);

    tone(BUZZER,1000);

    lcd.setCursor(0,0);
    lcd.print("GAS LEAK OP WIN");
    lcd.setCursor(0,1);
    lcd.print("G:");
    lcd.print(GAS);
    lcd.setCursor(8,1);
    lcd.print("T:");
    lcd.print(temperature);
  }
  else if (fire >= 50)
  {
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    tone(BUZZER,1000);
    lcd.setCursor(0,0);
    lcd.print("FIRE ALERT!");
    lcd.setCursor(0,1);
    lcd.print("F:");
    lcd.print(fire);
    lcd.setCursor(8,1);
    lcd.print("T:");
    lcd.print(temperature);
  }
  else if (temperature >= 50)
  {
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
    digitalWrite(FAN,HIGH);
    noTone(BUZZER);
    lcd.setCursor(0,0);
    lcd.print("TEMP HIGH OP WIN");
    lcd.setCursor(0,1);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
  }

  else
  {
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,HIGH);
    digitalWrite(FAN,LOW);
    noTone(BUZZER);
    lcd.setCursor(0,0);
    lcd.print("Kitchen Safe");
    lcd.setCursor(0,1);
    lcd.print("G:");
    lcd.print(GAS);
    lcd.setCursor(6,1);
    lcd.print("F:");
    lcd.print(fire);
    lcd.setCursor(11,1);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
  }

  delay(1000);
}