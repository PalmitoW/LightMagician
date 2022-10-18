// Costume de GN lumineux
// #ProjetLightMagician
// Adafruit Metro Mini 328 - 5V 16MHz
// ATmega328 brains, 32K of flash, 2KB of RAM, clocked at 16MHz
// Capteur luminosité : TSL2591
// ?programme utilise 8036 byte ?
 // programme utilise 8036 byte
/*
*   
*   
*   Info: Delay est en milli secondes
*/

/******************** INTRODUCTION LEDS ********************/
#include <Adafruit_NeoPixel.h>
#include <sensor.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
CRGB leds[NUM_LEDS];

/******************** INTRODUCTION ACCELEROMETRE ********************/

// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpul;
Adafruit_MPU6050 mpur;


/******************** INTRODUCTION ENTREES SORTIES ********************/

#define   BUTTON_PIN_SELECT  0    // Bouton du haut : plus
#define   BUTTON_PIN_START   2    // Bouton du mileu : start

#define   SENSOR_PIN_GESTURE_RIGHT   5    // Capteur de geste droit
#define   SENSOR_PIN_GESTURE_LEFT   6    // Capteur de geste gauche
#define   SENSOR_PIN_ACCELEROMETER_RIGHT   7    // Capteur de geste droit
#define   SENSOR_PIN_ACCELEROMETER_LEFT   8    // Capteur de geste gauche

#define   PIXEL_PIN          1    // Digital IO pin connected to the NeoPixels.

#define   NUM_LEDS           241
#define   LED_TEMOIN         1

#define   MAXCASE            8

//int ledFadeTime = 5;

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

/******************** INTRODUCTION DES VARIABLES ********************/
bool oldSelect = LOW;
bool oldStart = LOW;
uint8_t showType = 0;
uint8_t floorType = 0;

/*************************** BOUCLE SETUP ***************************/
void setup() { 
/*** Boutons***/
  pinMode(BUTTON_PIN_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_START, INPUT_PULLUP);
 /*** LEDS ***/
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(100);
 /*** Acceleromettre***/

}

/************************ BOUCLE EST BOUCLEE ************************/
/*
* A FAIRE
* Objectifs:
*OK* Import librairie
* Définir les fonctions principales
  * Loop, SelectLoop, Startoop
* Définir les fonctions de lecture des capteurs
  * Lecture bonton start
  * Lecture bouton select
  * Lecture accéléromètre
  * Lecture capteur de geste
* Définir la montée et descente des programmes
* Définir le lancement de programme
* Fonctions inutiles
  * Konami Code
*/


void loop() { 
  selectLoop(); // lit l'interrupteur select ; sélectionne un programme ; lance selectshow qui allume les leds témoins
  startLoop();  // lit l'interrupteur start ; lance start show qui execute les effets
  randomLoop();   // lit l'interrupteur floor ; lance floorshow petits effets floor
}

/*************************** BUTTON LOOP ***************************/
void selectLoop(void){ // lit l'interrupteur select ; sélectionne un programme ; lance selectshow qui allume les leds témoins
    bool newSelect = digitalRead(BUTTON_PIN_SELECT);
    bool newFloor = digitalRead(BUTTON_PIN_FLOOR);
   // Check if state changed from low to high (button press).
  if (newSelect == HIGH && oldSelect == LOW) {
    // Short delay to debounce button.
    delay(10);
    // Check if button is still high after debounce.
    newSelect = digitalRead(BUTTON_PIN_SELECT);
    newFloor = digitalRead(BUTTON_PIN_FLOOR);
    if (newSelect == HIGH) {
      
      if (newFloor == LOW)
      {
        showType++;
        
        if (showType > MAXCASE)
          showType=0;
      }
      else
      {
        if(showType <= 0){
          showType=MAXCASE;
        }else{
          showType--;
        }
      }
    }
  }
  oldSelect = newSelect;
  oldFloor = newFloor;
  selectShow(showType);
}

void startLoop(void){ // lit l'interrupteur start ; lance start show qui execute les effets
  bool newStart = digitalRead(BUTTON_PIN_START);
  // Check if state changed from low to high (button press).
  if (newStart == HIGH && oldStart == LOW) {
    // Short delay to debounce button.
    delay(10);
    // Check if button is still high after debounce.
    newStart = digitalRead(BUTTON_PIN_START);
    if (newStart == HIGH) {
          startShow(showType);
    }
  }
  oldStart = newStart;
}
/*************************** SENSOR READER ***************************/
void sensorReader(void){ // Lit les deux accéléromètres 
  sensors_event_t al, gl, templ;
  sensors_event_t ar, gr, tempr;
  mpul.getEvent(&al, &gl, &templ);
  mpur.getEvent(&ar, &gr, &tempr); 
}

/*************************** GESTURE READER ***************************/
void gestureReader(void){ // Lit les deux gestes

 
}


/*************************** BOUCLE EFFETS DE BASE ***************************/
void startShow(uint8_t i) {
 
 
}

void randomLoop(void){ // ramdom programme
 
}

/**************************** FONCTION PARAMETRES **********************/

void showStrip() { // fonction interne ADAFRUIT
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) { // fonction interne ADAFRUIT
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) { // fonction interne ADAFRUIT
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
} 

bool startBreak(){
  bool newStart = digitalRead(BUTTON_PIN_START);
  bool breakBool = 0;
  // Check if state changed from low to high (button press).
  if (newStart == HIGH && oldStart == LOW) {
    // Short delay to debounce button.
    delay(10);
    // Check if button is still high after debounce.
    newStart = digitalRead(BUTTON_PIN_START);
    if (newStart == HIGH) {
          breakBool=1;
    }
    return breakBool; 
  }
}
