#include <FastLED.h>

#include <RotaryEncoder.h>

#define ROTARYSTEPS 1
#define ROTARYMIN -1
#define ROTARYMAX 36
#define START_POSITION 0

//LED strip input

#define NUM_LEDS 37
#define DATA_PIN 2
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 10

CRGB leds[NUM_LEDS]; 

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(5, 6);

// Last known rotary position.
int lastPos = -1;

void setup()
{
  Serial.begin(9600);
  
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
  
  encoder.setPosition(START_POSITION / ROTARYSTEPS);
} 


void loop()
{
  encoder.tick();

  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition() * ROTARYSTEPS;

  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;

  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
    
  } 


  if (lastPos != newPos) {

    if (newPos>lastPos){

    leds[newPos]=CRGB::Blue;
    FastLED.show();
      
      }else{
        
    leds[newPos+1]=CRGB::Black;
    FastLED.show();
        }
        
    Serial.print(newPos);
    Serial.println();
    lastPos = newPos;

   
  } 
  
} 
