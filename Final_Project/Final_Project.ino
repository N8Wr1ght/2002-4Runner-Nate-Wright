#include <Servo.h>
Servo myservo;

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(20, 6);


int pos = 0;

// Neopixel Color Variables
uint32_t amber = strip.Color(255, 80, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t white = strip.Color(255, 255, 255);
uint32_t off = strip.Color(0,0,0);

// Button Pin Variables
int leftTurnSignals = 2;
int markerLights = 3;
int headLights = 4;
int rightTurnSignals = 5;

// Servo Pin Variables
int trunkServo = 0; // potentiometer pin
int potVal;

// States
// Left Turn Signal States
boolean currentLTState = false;
boolean prevLTState = false;

// Marker Lights States
boolean currentMLState = false;
boolean prevMLState = false;

// Head Lights States
boolean currentHLState = false;
boolean prevHLState = false;

// Right Turn Signals
boolean currentRTState = false;
boolean prevRTState = false;

boolean isLTState = true;
boolean isRTState = true;
boolean isMLState = false;
boolean isHLState = false;

void setup() {
Serial.begin (9600);

// Servo Pin
myservo.attach(9);  // servo pin

// More Button Stuff
pinMode(leftTurnSignals, INPUT);
pinMode(markerLights, INPUT);
pinMode(headLights, INPUT);
pinMode(rightTurnSignals, INPUT);
pinMode(trunkServo, INPUT);

// NeoPixel Starter Stuff
strip.begin();
strip.clear();
strip.show();
strip.setBrightness(255);
}

void loop() {
// State and Debounce Stuff
// turnSignals(9, amber, 1000);

// Left Turn Signal
 prevLTState = currentLTState;
  currentLTState = debounce(leftTurnSignals, prevLTState);

// Right Turn Signal
 prevRTState = currentRTState;
  currentRTState = debounce(rightTurnSignals, prevRTState);

// Marker Lights
 prevMLState = currentMLState;
  currentMLState = debounce(markerLights, prevMLState);

// Head Lights
 prevHLState = currentHLState;
  currentHLState = debounce(headLights, prevHLState);

// Make The Left Turn Signals Work
  if(currentLTState == true && prevLTState == false){
    if(isLTState == false){
 turnSignalsLeft(3, amber, 800);
 isLTState = true;
    }
    else{
       turnSignalsLeft(3, off, 800);
       isLTState = false;
    }
  }
      if(isLTState == false){
 turnSignalsLeft(3, amber, 800);
//  Serial.println("left");

    }
    else{
       turnSignalsLeft(3, off, 800);
    }

// Make The Right Turn Signals Work
  if(currentRTState == true && prevRTState == false){
    if(isRTState == false){
 turnSignalsRight(8, amber, 800);
 isRTState = true;
    }
    else{
       turnSignalsRight(8, off, 800);
       isRTState = false;
    }
  }
      if(isRTState == false){
 turnSignalsRight(8, amber, 800);
// Serial.println("right on");
    }
    else{
       turnSignalsRight(8, off, 800);
//       Serial.println("right off");
    }
  
// Make The Marker And Rear Lights Work
  if(currentMLState == true && prevMLState == false){
    if(isMLState == false){
    markerAndRearLights(2, white);
    markerAndRearLights(7, white);
    markerAndRearLights(10, red);
    markerAndRearLights(11, red);
    markerAndRearLights(16, red);
    markerAndRearLights(17, red);
    isMLState = true;
    }
      else{
    markerAndRearLights(2, 0);
    markerAndRearLights(7, 0);
    markerAndRearLights(10, 0);
    markerAndRearLights(11, 0);
    markerAndRearLights(16, 0);
    markerAndRearLights(17, 0);
    isMLState = false;
    }
  }


// Make The Head And Fog Lights Work
  if(currentHLState == true && prevHLState == false){
    if(isHLState == false){
    headAndFogLights(0, white);
    headAndFogLights(1, white);
    headAndFogLights(4, white);
    headAndFogLights(5, white);
    headAndFogLights(6, white);
    headAndFogLights(9, white);
    isHLState = true;
    }
    else{
    headAndFogLights(0, 0);
    headAndFogLights(1, 0);
    headAndFogLights(4, 0);
    headAndFogLights(5, 0);
    headAndFogLights(6, 0);
    headAndFogLights(9, 0);
    isHLState = false;
    }
  }

// Move The Trunk
  trunkMove();
 }

boolean debounce(int aButton, boolean aprevState) {
// track the button's current state
  boolean aButtonState = digitalRead(aButton);

// if you pressed the button this frame, then
// wait so you don't read the button again
// while it is bouncing
  if (aButtonState == HIGH && aprevState == LOW) {
    delay(15);
  }
// return the button's current state
  return aButtonState;
}

void turnSignalsLeft(int pix, uint32_t color, int interval){
  static unsigned long startTime = millis();
  unsigned long currentTime = millis();
  static boolean TSState = false;

if(currentTime - startTime >= interval){
  if(TSState == false){
  Serial.println("hi");
  if(TSState == false){
  strip.setPixelColor(pix, color);
  strip.setPixelColor(pix + 15, color);
  strip.show();
  TSState = true;
  }
 }
else{
  strip.setPixelColor(pix, 0);
  strip.setPixelColor(pix + 15, 0);
  strip.show();
  TSState = false;
  }
    startTime = millis();
 }
}

void turnSignalsRight(int pix, uint32_t color, int interval){
  static unsigned long startTime = millis();
  unsigned long currentTime = millis();
  static boolean TSState = false;

if(currentTime - startTime >= interval){
  if(TSState == false){
  Serial.println("hi");
  if(TSState == false){
  strip.setPixelColor(pix, color);
  strip.setPixelColor(pix + 4, color);
  strip.show();
  TSState = true;
  }
 }
else{
  strip.setPixelColor(pix, 0);
  strip.setPixelColor(pix + 4, 0);
  strip.show();
  TSState = false;
  }
    startTime = millis();
 }
}


void markerAndRearLights(int pix, uint32_t color){
  strip.setPixelColor(pix, color);
  strip.show();
}

void headAndFogLights(int pix, uint32_t color){
  strip.setPixelColor(pix, color);
  strip.show();
}

void trunkMove(){
      int servpos = map(potVal, 0, 1023, 0, 180);
 potVal = analogRead(trunkServo);
  //Serial.println(potVal);

    myservo.write(servpos);
      //Serial.println(servpos);
}
