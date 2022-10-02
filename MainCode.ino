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

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define   BUTTON_PIN_SELECT  0    // Bouton du haut : select
#define   BUTTON_PIN_START   2    // Bouton du bas : start
#define   BUTTON_PIN_FLOOR   4    // Bouton pied de baton

#define   PIXEL_PIN          1    // Digital IO pin connected to the NeoPixels.

#define   NUM_LEDS           42
// baton d'alexis : led temoin : 17 & 18
#define   LED_TEMOIN         17

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
bool oldFloor = LOW;
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
*OK* l’interrupteur SELECT monte le programme
* l'interrupteur SELECT + FLOOR descend le pogramme OK A TESTER
* l’interrupteur START lance le programme OK A TESTER
* une led au dessus de la main indique sur quel programme on est OK
* l’interrupteur FLOOR lance des petits effets floorShow OK A TESTER
*/


void loop() { 
  selectLoop(); // lit l'interrupteur select ; sélectionne un programme ; lance selectshow qui allume les leds témoins
  startLoop();  // lit l'interrupteur start ; lance start show qui execute les effets
  floorLoop();   // lit l'interrupteur floor ; lance floorshow petits effets floor
}