// Lawrence Button Two Arduino DMX to WS2812 code
// Max Hunter, 2024

#include <DMXSerial.h>
#include <FastLED.h>

#define DMX_START_CHANNEL 510
#define NUM_LEDS 256

CRGB leds[NUM_LEDS];

void setup(void) {
  DMXSerial.init(DMXProbe);
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS);
}

void loop() {
  if (DMXSerial.receive()) {
    uint8_t red = DMXSerial.read(DMX_START_CHANNEL);
    uint8_t green = DMXSerial.read(DMX_START_CHANNEL + 1);
    uint8_t blue = DMXSerial.read(DMX_START_CHANNEL + 2);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(red, green, blue);
    }
    FastLED.show();
  }
  // } else {
  //   leds[0].setRGB(((millis() % 1000) < 200) * 50, 0, 0);  // debug: we are not getting DMX
  //   FastLED.show();
  // }
}