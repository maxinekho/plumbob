#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

int mood = 5;

void setup() {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // consider adding a serial settimeout to avoid falling behind
}

void loop() {
  getMood();
  lightMood(mood);
}


void getMood() {
  if (Serial.available() > 0) {     // If data is available to read,
    int inByte = Serial.parseInt(); // find the int within it
    if (inByte > 0) {               // if its more than 0, cut up the inbound message
      mood = inByte;
    }
  }
}

void lightMood(int mood) {
  if (mood == 1) {
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  } else if (mood == 2) {
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
  } else if (mood == 3) {
    colorWipe(strip.Color(127, 127, 0), 50); // Orange
  } else if (mood == 4) {
    colorWipe(strip.Color(0, 255, 0), 50); // Green
  } else if (mood == 5) {
    colorWipe(strip.Color(127, 127, 127), 50); // white

  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
