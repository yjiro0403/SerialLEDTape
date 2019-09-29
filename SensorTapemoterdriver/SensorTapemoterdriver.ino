#include <Adafruit_NeoPixel.h>
#include <Servo.h>
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
//Setting resistpin num
//const int potentiometerPin = 8;

//lighting LED Tape over this value
#define threshold 400

Servo servo;

const boolean useSeparatePWMPin = false; //TA729P is false

//moter drivers Pin
const int in1Pin = 11;
const int in2Pin = 12;

//forward 
void forward(int value){
 if(useSeparatePWMPin) {
 }else{
   analogWrite(in1Pin, value);
   analogWrite(in2Pin, 0);
   Serial.println(value);
 }
}
//reverse
void reverse(int value){
 if(useSeparatePWMPin){
 } else {
   analogWrite(in1Pin,0);
   analogWrite(in2Pin, value);
 }
}

//stop 
void despin(boolean useBrake = true){
 if(useBrake){
   digitalWrite(in1Pin, HIGH);
   digitalWrite(in2Pin, HIGH);
 } else {
   digitalWrite(in1Pin, LOW);
   digitalWrite(in2Pin, LOW);
 }
}

void setup(){
   //SET OUTPUTMODE: IN1, IN2, PWM 
 pinMode(in1Pin, OUTPUT);
 pinMode(in2Pin, OUTPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show();
  
  //SETTING: Servo Pin
  servo.attach(8);
}

void loop(){
 int val = analogRead(sensorPin);
 Serial.println(val);
 if(val > threshold){
   colorWipe(strip.Color(0, val, 0), DELAY_TIME); //lighting
   colorWipe(strip.Color(0, 0, 0), 0); // finish
   
     forward(255);
 delay(500);
 
 //stop 1000ms
 despin(true);
 delay(1000);
 
 reverse(255);
 Serial.println("Reverse");
 delay(500);
 
 despin(false);
 delay(1000);
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

