// Disables pragma messages from LED ring on compile
#define FASTLED_INTERNAL

// Libraries
#include <SPI.h>     // rfid
#include <MFRC522.h> // rfid
#include <FastLED.h> // lighting
#include <Bounce2.h> // button

// PINS
#define RST_PIN 9   // reset pin (rfid)
#define SS_PIN 10   // serial data pin (rfid)
#define DATA_PIN 8  // data-in (lighting)
#define NUM_LEDS 12 // number of leds (lighting)
#define TILT_PIN 2  // data-out (tilt switch)

// Brand colors
#define HUE_LOCAL 125 // main color
#define SAT_LOCAL 220
#define HUE_POI 200   // secondary color
#define SAT_POI 200

// Create a gradient palette
// |-----------------------|
// BLUE...RED...BLUE
DEFINE_GRADIENT_PALETTE(blue_red_p) {
  0,   0, 120, 90,
  85,  0,  80,  45,
  170, 0,  30,  10,
  255, 0,   0,   0
};
CRGBPalette256 my_gradient = blue_red_p;

// Hardware components (instances)
MFRC522 mfrc522(SS_PIN, RST_PIN); // rfid-reader
CRGB leds[NUM_LEDS];              // lighting
Bounce button = Bounce();         // button

// Global variables
uint8_t blinking_count, blinking_value, shake_count, pos, tilt_state, tilt_state_previous, waving_brightness;
bool blinking_switch;

// How many pulses per minute
uint8_t bpm = 30;

void setup() {
  Serial.begin(9600); // start serial connection
  SPI.begin();        // start SPI bus

  mfrc522.PCD_Init(); // init rfid module

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // init lighting
  FastLED.setBrightness(30);                               // set brightness
  FastLED.clear();                                         // clear lighting data

  button.attach(A0, INPUT_PULLUP); // init button

  pinMode(TILT_PIN, INPUT_PULLUP); // init tilt switch with an active in-built pull-up resistor
}

void checkRFIDContact() {
  mfrc522.PICC_IsNewCardPresent(); // check for rfid contact
  mfrc522.PICC_ReadCardSerial();   // check for rfid contact

  //for (int i = 0; i < mfrc522.uid.size; i++) {
  //Serial.print(mfrc522.uid.uidByte[i], HEX);
  //Serial.print(" ");
  //}
}

void playDemoLocal() {
  resetValues();
  newNotification(HUE_LOCAL, SAT_LOCAL);
  delay(3000);
  findingLocal();
  delay(300);
  connectToLocal();
  delay(3000);
  turnOffLighting();
  delay(10000);
}

// resets variables for the local-demo
void resetValues() {
  blinking_count = 0;
  blinking_value = 31;
  blinking_switch = true;
  shake_count = 0;
  pos = 0;
  waving_brightness = 0;
}

// blinking 3 times (pulsing with an easing)
void newNotification(int hue, int saturation) {
  while (blinking_count < 6) {
    EVERY_N_MILLIS_I(timer, 5) {
      if (blinking_value == 30 || blinking_value == 175) {
        blinking_switch = !blinking_switch;
        blinking_count++;
      }

      if (blinking_switch) {
        blinking_value++;
        timer.setPeriod(6);
      } else {
        blinking_value--;
        timer.setPeriod(2);
      }
    }

    fill_solid(leds, NUM_LEDS, CHSV(hue, saturation, blinking_value));
    FastLED.show();
  }
  turnOffLighting();
}

// turns off the lighting
void turnOffLighting() {
  FastLED.clear();
  FastLED.show();
}

// animation when user is actively looking for the local
void findingLocal() {
  while (shake_count < 5) {
    countShakes();
    movingDot();
  }
  turnOffLighting();
}

void countShakes() {
  tilt_state = digitalRead(TILT_PIN); // read state of tilt switch
  if (tilt_state != tilt_state_previous) {
    shake_count++;
  }
  tilt_state_previous = tilt_state;
}

void movingDot() {
  EVERY_N_MILLIS(1) {
    Serial.println(pos);
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      // Calculate position with map() then use pos to cycle it around the ring a bit
      uint8_t this_position = map(i, 0, NUM_LEDS - 1, 0, 255) + pos;
      leds[i] = ColorFromPalette(my_gradient, this_position);
    }
    FastLED.show();
    pos++;
  }
}

void connectToLocal() {
  FastLED.setBrightness(0);                               // set brightness
  fill_solid(leds, NUM_LEDS, CHSV(HUE_LOCAL, SAT_LOCAL, 175));
  FastLED.show();
  while (waving_brightness < 30) {
    EVERY_N_MILLIS(30) {
      FastLED.setBrightness(waving_brightness++);                               // set brightness
      //fill_solid(leds, NUM_LEDS, CHSV(HUE_LOCAL, SAT_LOCAL, 175));
      FastLED.show();
      //FastLED.clear();
    }
  }
}

void fillCircle() {
  EVERY_N_MILLIS(5) {

    // beat8(x) returns a number from 0 to 255, looping x times per minute
    uint8_t pos = beat8(bpm);

    // Convert the position to an index for the LED on our strip
    uint8_t led = map8(pos, 0, NUM_LEDS - 1);
    leds[led] = CRGB::White;
    FastLED.show();
  }
}

void loop() {
  playDemoLocal();
  //  button.update();
  //  if (button.rose()) {
  //    die();
  //  }
  //
  //  if (digitalRead(BUTTON_PIN) == HIGH) { // demo-mode#1: meeting a local
  //    playDemoLocal();
  //  } else {                             // demo-mode#2: connect with POI
  //    playDemoPOI();
  //  }
}
