/*********
  Wizard Lightning
*********/

/* I2C */
#include <Wire.h>
/* MULTIPLEXER */
#include <Adafruit_GFX.h>
/* LCD M0 M1*/
#include <LiquidCrystal_I2C.h>
/* GESTURE M2 M3*/
#include <SparkFun_APDS9960.h>
/* ACCELERATOR M2 M3 M4 M5*/
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
/* LED*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN_NEO_PIXEL  8
#define NUM_PIXELS     241

/*** DECLARATION MULTIPLEXER ***/
// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

/*** DECLARATION LCD ***/
LiquidCrystal_I2C lcd0(0x27 , 16, 2); // M0
LiquidCrystal_I2C lcd1(0x27 , 16, 2); // M1

/*** DECLARATION GESTURE ***/                        /*** USABLE VARIABLE ***/ 
/*** M2 ***/
SparkFun_APDS9960 apds2 = SparkFun_APDS9960();
uint16_t ambient_light2 = 0;
uint16_t red_light2 = 0;
uint16_t green_light2 = 0;
uint16_t blue_light2 = 0;
/*** M3 ***/
SparkFun_APDS9960 apds3 = SparkFun_APDS9960();
uint16_t ambient_light3 = 0;
uint16_t red_light3 = 0;
uint16_t green_light3 = 0;
uint16_t blue_light3 = 0;

/*** DECLARATION ACCELERATOR ***/                        /*** USABLE VARIABLE ***/ 
/*** M2 ***/
Adafruit_MPU6050 mpu2;
float temperature = 0;
float ax2=0;
float ay2=0;
float az2=0;
float gx2=0;
float gy2=0;
float gz2=0;

/*** M3 ***/
Adafruit_MPU6050 mpu3;
float ax3=0;
float ay3=0;
float az3=0;
float gx3=0;
float gy3=0;
float gz3=0;

/*** M4 ***/
Adafruit_MPU6050 mpu4;
float ax4=0;
float ay4=0;
float az4=0;
float gx4=0;
float gy4=0;
float gz4=0;

/*** M5 ***/
Adafruit_MPU6050 mpu5;
float ax5=0;
float ay5=0;
float az5=0;
float gx5=0;
float gy5=0;
float gz5=0;

/*** DECLARATION LED ***/
Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

/*** DECLARATION MEMORY ***/                        /*** USABLE VARIABLE ***/ 



void setup() {
  Serial.begin(115200);

   // Start I2C communication with the Multiplexer
  Wire.begin();

/*** INIT LCD0 M0 VIA MULTIPLEXER ***/
  TCA9548A(0); 
  lcd0.init();  //initialize the lcd
  lcd0.backlight();  //open the backlight
 
/*** INIT LCD1 M1 VIA MULTIPLEXER ***/
  TCA9548A(1); 
  lcd1.init();  //initialize the lcd
  lcd1.backlight();  //open the backlight
  
/*** INIT GESTURE M2 & M3 VIA MULTIPLEXER ***/
  // Initialize interrupt service routine
  // attachInterrupt(0, interruptRoutine, FALLING);
  
/*** M2 ***/
  TCA9548A(2); 
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds2.init() ) {
    Serial.println(F("APDS-9960 M2 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 M2 init!"));
  }
  // Start running the APDS-9960 light sensor
  if ( apds2.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  } 
  delay(500); // Wait for initialization and calibration to finish

/*** M3 ***/
  TCA9548A(3); 
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds3.init() ) {
    Serial.println(F("APDS-9960 M3 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 M3 init!"));
  }
  // Start running the APDS-9960 light sensor
  if ( apds3.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  } 
  delay(500); // Wait for initialization and calibration to finish
  
  
/*** INIT ACCELERATOR VIA MULTIPLEXER ***/
/*** M2 ***/
  TCA9548A(2); 
    // Try to initialize!
  if (!mpu2.begin()) {
    Serial.println("Failed to find MPU6050 M2 chip");
    while (1) {
      delay(10);
    }
  }
  mpu2.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu2.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu2.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100);
  
/*** M3 ***/
  TCA9548A(3); 
    // Try to initialize!
  if (!mpu3.begin()) {
    Serial.println("Failed to find MPU6050 M3 chip");
    while (1) {
      delay(10);
    }
  }
  mpu3.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu3.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu3.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100);
  
/*** M4 ***/
  TCA9548A(4); 
    // Try to initialize!
  if (!mpu4.begin()) {
    Serial.println("Failed to find MPU6050 M4 chip");
    while (1) {
      delay(10);
    }
  }
  mpu4.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu4.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu4.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100);
  
/*** M5 ***/
  TCA9548A(5); 
    // Try to initialize!
  if (!mpu5.begin()) {
    Serial.println("Failed to find MPU6050 M5 chip");
    while (1) {
      delay(10);
    }
  }
  mpu5.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu5.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu5.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100); 
  
  /*** INIT LED ***/
  NeoPixel.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}
 
void loop() {
  NeoPixel.clear();
  testled();
  printlcd(3,"Hello GeekPi",2,"Hello World",3,"Hello",2,"Little Rock");
  readGesture();
  readAccelerator();
}

  /*** PRINT LCD VIA MULTIPLEXER ***/
void printlcd(int col1,String raw1,int col2,String raw2,int col3,String raw3,int col4,String raw4){
  /*** M0 ***/
  TCA9548A(0);
  lcd0.setCursor(col1, 0);
  lcd0.print(raw1);
  
  lcd0.setCursor(col2, 1);
  lcd0.print(raw2);

  /*** M1 ***/
  TCA9548A(1);
  lcd1.setCursor(col3, 0);
  lcd1.print(raw3);
  lcd1.setCursor(col4, 1);
  lcd1.print(raw4);
}

/*** LECTURE ACCELERATOR VIA MULTIPLEXER ***/
void readAccelerator(){  
  sensors_event_t a, g, temp;
  TCA9548A(2);
  mpu2.getEvent(&a, &g, &temp);
  temperature=temp.temperature;
  ax2=a.acceleration.x;
  ay2=a.acceleration.y;
  az2=a.acceleration.z;
  gx2=g.gyro.x;
  gy2=g.gyro.y;
  gz2=g.gyro.z;

  /*** M3 ***/
  TCA9548A(3);
  mpu3.getEvent(&a, &g, &temp);
  ax3=a.acceleration.x;
  ay3=a.acceleration.y;
  az3=a.acceleration.z;
  gx3=g.gyro.x;
  gy3=g.gyro.y;
  gz3=g.gyro.z;

  /*** M4 ***/
  TCA9548A(4);
  mpu4.getEvent(&a, &g, &temp);
  ax4=a.acceleration.x;
  ay4=a.acceleration.y;
  az4=a.acceleration.z;
  gx4=g.gyro.x;
  gy4=g.gyro.y;
  gz4=g.gyro.z;

  /*** M5 ***/
  TCA9548A(5);
  mpu5.getEvent(&a, &g, &temp);
  ax5=a.acceleration.x;
  ay5=a.acceleration.y;
  az5=a.acceleration.z;
  gx5=g.gyro.x;
  gy5=g.gyro.y;
  gz5=g.gyro.z;
}

/*** READ GESTURE VIA MULTIPLEXER ***/
void readGesture(){
/*** M2 ***/ 
  TCA9548A(2);
   // Read the light levels (ambient, red, green, blue)
  if (  !apds2.readAmbientLight(ambient_light2) ||
        !apds2.readRedLight(red_light2) ||
        !apds2.readGreenLight(green_light2) ||
        !apds2.readBlueLight(blue_light2) ) {
    Serial.println("Error reading light values");
  }

 /*** M3 ***/ 
  TCA9548A(3);
   // Read the light levels (ambient, red, green, blue)
  if (  !apds3.readAmbientLight(ambient_light3) ||
        !apds3.readRedLight(red_light3) ||
        !apds3.readGreenLight(green_light3) ||
        !apds3.readBlueLight(blue_light3) ) {
    Serial.println("Error reading light values");
  }
}



void testled(){
	
  // turn pixels to green one by one with delay between each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) { // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0)); // it only takes effect if pixels.show() is called
    NeoPixel.show();   // send the updated pixel colors to the NeoPixel hardware.

    delay(200); // pause between each pixel
  }

  // turn off all pixels for two seconds
  NeoPixel.clear();
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(2000);     // off time

  // turn on all pixels to red at the same time for two seconds
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) { // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 0)); // it only takes effect if pixels.show() is called
  }
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(2000);     // on time

  // turn off all pixels for one seconds
  NeoPixel.clear();
  NeoPixel.show(); // send the updated pixel colors to the NeoPixel hardware.
  delay(2000);     // off time
}
