#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27 , 16 , 2);

const int lm35pin = A2;
const int lm35pin2 = A0 ;
#define kirmizi_led 8
#define buzzer 7

int zaman = 100;
int okunan_deger = 0;
int okunan_deger_2 = 0;
float sicaklik_gerilim = 0;
float sicaklik = 0;
float sicaklik_gerilim_2 = 0;
float sicaklik_2 = 0;
float sicaklik_toplam = 0;



void setup() {
  Serial.begin(9600);
  pinMode(kirmizi_led,OUTPUT); 
  pinMode(buzzer,OUTPUT);
  lcd.begin();

}

void loop() {
  lcd.backlight();
  delay(500);
  lcd.home();
  okunan_deger = analogRead(lm35pin);
  okunan_deger_2 = analogRead(lm35pin2);
  sicaklik_gerilim = (5000.0/1023.0) * okunan_deger;
  sicaklik = sicaklik_gerilim / 10.0;
  sicaklik_gerilim_2 = (5000.0/1023.0) * okunan_deger_2;
  sicaklik_2 = sicaklik_gerilim_2 / 10.0;
  sicaklik_toplam = (sicaklik + sicaklik_2) / 2.0;
  delay(zaman);
  Serial.println(sicaklik_toplam);
  lcd.print("Sicaklik = ");
  lcd.print(sicaklik_toplam);
  if(sicaklik_toplam > 20){
    digitalWrite(kirmizi_led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    digitalWrite(kirmizi_led,LOW);
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("Fatura kabarik...");
  }
  else{
    digitalWrite(kirmizi_led,LOW);
    digitalWrite(buzzer,LOW);
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("Yakabilirsin...");  
  }


}
