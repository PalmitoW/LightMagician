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

/******************** INTRODUCTION ENTREES SORTIES ********************/

// ANCIENNES LEDS
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
CRGB leds[NUM_LEDS];

#define   BUTTON_PIN_PLUS  0    // Bouton du haut : plus
#define   BUTTON_PIN_START   2    // Bouton du mileu : start
#define   BUTTON_PIN_MINUS   4    // Bouton du bas : moins

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
bool oldPlus = LOW;
bool oldStart = LOW;
bool oldMinus = LOW;
uint8_t showType = 0;
uint8_t floorType = 0;

/*************************** BOUCLE SETUP ***************************/
void setup() { 

  pinMode(BUTTON_PIN_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_START, INPUT_PULLUP);
  pinMode(BUTTON_PIN_FLOOR, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(100);

}

/************************ BOUCLE EST BOUCLEE ************************/
/*
* A FAIRE
* Objectifs:
*OK* Import librairie
* Définir les fonctions principales
* Définir la montée et descente des programmes
* Définir le lancement de programme
*/


void loop() { 
  selectLoop(); // lit l'interrupteur select ; sélectionne un programme ; lance selectshow qui allume les leds témoins
  startLoop();  // lit l'interrupteur start ; lance start show qui execute les effets
  floorLoop();   // lit l'interrupteur floor ; lance floorshow petits effets floor
}

