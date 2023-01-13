#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    16

CRGB leds[NUM_LEDS];
CRGB lowTempColor = CRGB(60, 137, 208);
CRGB okTempColor = CRGB(0, 255, 0);
CRGB lowWarningTempColor = CRGB(251, 177, 23);
CRGB highWarningTempColor = CRGB(248, 114, 23);
CRGB criticalTempColor = CRGB(255, 0, 0);

#define DHTPIN 2     // Digital pin connected to the DHT sensor

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

void showStartAnimation1(void){
for (int i = 0; i < 5; i++) {
       leds[i] = CRGB (0, 0, 255);
       FastLED.show();
       delay(70);
     }
  for (int i = 12; i >= 8; i--) {
       leds[i] = CRGB (0, 0, 255);
       FastLED.show();
       delay(70);
      }
  for (int i = 5; i < 8; i++) {
       leds[i] = CRGB (0, 0, 255);
       FastLED.show();
       delay(70);
     }
  for (int i = 15; i >= 13; i--) {
       leds[i] = CRGB (0, 0, 255);
       FastLED.show();
       delay(70);
      }
      delay(100);
  }


void showStartAnimation2(void){
for (int i = 0; i < 8; i++) {
       leds[i] = CRGB (0, 0, 255);
       FastLED.show();
       delay(70);
       leds[i+8] = CRGB (0, 0, 255);
       FastLED.show();
       delay(70);
     }
      delay(100);
  }


void setup() {

  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));

  dht.begin();

  showStartAnimation2();
}

void loop() {

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
     
      lcd.home();
      lcd.setCursor(5,0);   
      lcd.print("SENSOR");
      lcd.setCursor(2,1);   
      lcd.print("NOT DETECTED");
      
      for (int i = 0; i < 16; i++) {
        leds[i] = CRGB (255, 0, 0);
        FastLED.show();
        delay(50);
      }
     
      lcd.clear();
      FastLED.clear();
      delay(1000);
      return;
      
    }
 

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("C"));

  
    // Print a message on both lines of the LCD.
  lcd.noBlink();
  lcd.noCursor();
  lcd.setCursor(2,0);   
  lcd.print("Temp: ");
  lcd.setCursor(8,0);   
  lcd.print(t);
  lcd.setCursor(13,0);   
  lcd.print("C");
  
  lcd.setCursor(2,1);   
  lcd.print("Hum : ");
  lcd.setCursor(8,1);   
  lcd.print(h);
  lcd.setCursor(13,1);   
  lcd.print("%");
    
     if(t < 15){
      fill_solid( leds, NUM_LEDS, lowTempColor);
       FastLED.show();
     }else if(t >= 15 && t <= 25){
      fill_solid( leds, NUM_LEDS, okTempColor);
       FastLED.show();
  
     }else if(t > 25 && t <= 30){
      fill_solid( leds, NUM_LEDS, lowWarningTempColor);
       FastLED.show();
     }
     else if(t > 30 && t <= 35){
      fill_solid( leds, NUM_LEDS, highWarningTempColor);
       FastLED.show();
     }
     else if(t >35){
      fill_solid( leds, NUM_LEDS, criticalTempColor);
       FastLED.show();
     }
 
  // Wait a few seconds between measurements.  
  delay(2000);
}
