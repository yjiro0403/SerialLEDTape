#include <Adafruit_NeoPixel.h>
#define MAX_VAL 64  // 0 to 255 for brightness
#define DELAY_TIME 50 
#define DELAY_TIME2 20
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 9, NEO_GRB + NEO_KHZ800);

int sensorPin = 0;

//lighting LED Tape over this value
#define threshold 400

void setup(){
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop(){
 int val = analogRead(sensorPin);
 Serial.println(val);
 if(val > threshold){
   colorWipe(strip.Color(0, val, 0), DELAY_TIME); //lighting
   colorWipe(strip.Color(0, 0, 0), 0); // finish
 }
 
 delay(10); 
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
