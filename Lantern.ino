/** Simulated fire with 6 modes.
 *  Orginalcode from :https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/mehrere-feuer-programme-fuer-unsere-stimmungslaterne
 *  I remove the remote and replace with a single button (Pin 5) 
 *  And remove some redundance.
 *  Its not perfect but in the short time its a stable solution for its reason.
 *  Last Author: Fabienne Fedier aka linuxfabi
 */
#include <Adafruit_NeoPixel.h>

#define PIN        6  // Which pin on the Arduino is connected to the NeoPixels?
#define NUMPIXELS 12 // How many NeoPixels are attached to the Arduino? // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long FirelastTime  = 0;
long IRlastTime    = 0;
long TimerlastTime = 0;
int  interval;
byte FireSequence = 0;

void setup() {
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
  interval = 300;
  randomSeed(analogRead(0));

  pinMode(5, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(5)) {
    FireSequence++;
    if (FireSequence > 5) FireSequence = 0;
    delay(300);
  }
  SimulateFire(FireSequence);
}

void SimulateFire (byte FireSq) {
  byte LightValue[NUMPIXELS * 3];

  if (millis() - FirelastTime >= interval) {
    FirelastTime = millis();
    interval = 200;
    
    if (FireSq == 0) {
      for (int i = 0; i < NUMPIXELS; i++) {
        LightValue[i * 3] = random(200, 255); // 250
        LightValue[i * 3 + 1] = random(30, 70); // 50
        LightValue[i * 3 + 2] = 0;
      }
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, LightValue[i * 3], LightValue[i * 3 + 1], LightValue[i * 3 + 2]);
      }
      noInterrupts();
      pixels.show();
      interrupts();
    }
    
    if (FireSq == 1) {
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, 250, 50, 0);
      }
      noInterrupts();
      pixels.show();
      interrupts();
    }
    
    if (FireSq == 2) {
      interval = random(50, 100);
      for (int i = 0; i < NUMPIXELS; i++) {
        LightValue[i * 3] = random(240, 255); // 250
        LightValue[i * 3 + 1] = random(30, 60); // 50
        LightValue[i * 3 + 2] = 0;
      }
      // Switch some lights out
      byte LightsOff  = random(0, 6);
      for (int i = 0; i < LightsOff; i++) {
        byte Selected = random(NUMPIXELS);
        LightValue[Selected * 3] = 0;
        LightValue[Selected * 3 + 1] = 0;
        LightValue[Selected * 3 + 2] = 0;
      }
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, LightValue[i * 3], LightValue[i * 3 + 1], LightValue[i * 3 + 2]);
      }
      noInterrupts();
      pixels.show();
      interrupts();
    }
    
    if (FireSq == 3) {
      interval = random(80);
      for (int i = 0; i < NUMPIXELS; i++) {
        LightValue[i * 3] = 250; //random(240,255); // 250
        LightValue[i * 3 + 1] =  50; //random(30,60); // 50
        LightValue[i * 3 + 2] = 0;
      }
      // Switch some lights out if Chance Hit

      byte ChanceforLightsOff  = random(0, 40);
      if (ChanceforLightsOff > 35) {
        byte LightsOff  = random(5);
        for (int i = 0; i < LightsOff; i++) {
          byte Selected = random(NUMPIXELS);
          LightValue[Selected * 3] = 0;
          LightValue[Selected * 3 + 1] = 0;
          LightValue[Selected * 3 + 2] = 0;
        }
      }
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, LightValue[i * 3], LightValue[i * 3 + 1], LightValue[i * 3 + 2]);
      }
      noInterrupts();
      pixels.show();
      interrupts();
    }
    
    if (FireSq == 4) {
      interval = random(150, 200);
      for (int i = 0; i < NUMPIXELS; i++) {
        LightValue[i * 3] = random(240, 255); // 250
        LightValue[i * 3 + 1] = random(30, 60); // 50
        LightValue[i * 3 + 2] = 0;
      }
      // Switch some lights darker
      byte LightsOff  = random(0, 4);
      for (int i = 0; i < LightsOff; i++) {
        byte Selected = random(NUMPIXELS);
        LightValue[Selected * 3] = random(50, 60);
        LightValue[Selected * 3 + 1] = random(5, 10);
        LightValue[Selected * 3 + 2] = 0;
      }
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, LightValue[i * 3], LightValue[i * 3 + 1], LightValue[i * 3 + 2]);
      }
      noInterrupts();
      pixels.show();
      interrupts();
    }
    
    if (FireSq == 5) {
      interval = random(80);
      for (int i = 0; i < NUMPIXELS; i++) {
        LightValue[i * 3] = random(240, 255); // 250
        LightValue[i * 3 + 1] = random(40, 60); // 50
        LightValue[i * 3 + 2] = 0;
      }
      // Switch some lights out if Chance Hit
      byte ChanceforLightsOff  = random(0, 40);
      if (ChanceforLightsOff > 35) {
        byte LightsOff  = random(5);
        for (int i = 0; i < LightsOff; i++) {
          byte Selected = random(NUMPIXELS);
          LightValue[Selected * 3] = 0;
          LightValue[Selected * 3 + 1] = 0;
          LightValue[Selected * 3 + 2] = 0;
        }
      }
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, LightValue[i * 3], LightValue[i * 3 + 1], LightValue[i * 3 + 2]);
      }
      noInterrupts();
      pixels.show();
      interrupts();
    }
  }
}
