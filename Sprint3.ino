// This #include statement was automatically added by the Particle IDE.
#include "lib1.h"

// This #include statement was automatically added by the Particle IDE.
#include "MCP9808/MCP9808.h"

//NOTE: THIS CODE WAS BUILT TO RUN IN THE PARTICLE BROWSER BASED IDE. MAY ALSO RUN ON ARDUINO, BUT UNTESTED
MCP9808 mcp = MCP9808();

int white1 = A1; 
int white2 = A2; 
int white3 = A0; 
int white4 = A3; 
int white5 = A4; 
int red1 = D2; 
int red2 = D7; 
int red3 = D4; 
int red4 = D5; 
int red5 = D6; 

bool white1_state = LOW; 
bool white2_state = LOW; 
bool white3_state = LOW;
bool white4_state = LOW; 
bool white5_state = LOW; 
bool red1_state = HIGH; 
bool red2_state = HIGH; 
bool red3_state = HIGH; 
bool red4_state = HIGH; 
bool red5_state = HIGH; 
 
 
unsigned long previousMillis1 = 0;        // will store last time LED was updated
unsigned long previousMillis2 = 0;        // will store last time LED was updated
unsigned long previousMillis3 = 0;        // will store last time LED was updated
 
const long interval1 = 125;           // interval at which to blink (milliseconds)
const long interval2 = 500;           // interval at which to blink (milliseconds)
const long interval3 = 3000;           // interval at which to blink (milliseconds)

float temperature = 0; 
float init_temperature = 0; 


void setup() {
    pinMode(white1, OUTPUT);
    pinMode(white2, OUTPUT);
    pinMode(white3, OUTPUT);
    pinMode(white4, OUTPUT);
    pinMode(white5, OUTPUT);
    pinMode(red1, OUTPUT); 
    pinMode(red2, OUTPUT); 
    pinMode(red3, OUTPUT); 
    pinMode(red4, OUTPUT); 
    pinMode(red5, OUTPUT); 
    
    
    while(! mcp.begin()){
        delay(1000);
    }
    mcp.setResolution(MCP9808_SLOWEST);
    
    digitalWrite(white1, HIGH); 
    digitalWrite(white2, HIGH); 
    digitalWrite(white3, LOW); 
    digitalWrite(white4, HIGH); 
    digitalWrite(white5, HIGH); 
    digitalWrite(red1, LOW); 
    digitalWrite(red2, LOW); 
    digitalWrite(red3, HIGH); 
    digitalWrite(red4, LOW); 
    digitalWrite(red5, LOW); 
    
    init_temperature = mcp.getTemperature(); 
    
    
  
}

void loop() {
  unsigned long currentMillis = millis();
  temperature = mcp.getTemperature();
  

  if((temperature - init_temperature) > 0.3){
    digitalWrite(white2, HIGH); 
    digitalWrite(white3, HIGH); 
    digitalWrite(white4, LOW); 
    digitalWrite(white5, LOW); 
    digitalWrite(red1, LOW); 
    digitalWrite(red2, LOW); 
    digitalWrite(red3, LOW); 
    digitalWrite(red4, HIGH); 
    digitalWrite(red5, HIGH); 
    
    if (currentMillis - previousMillis1 >= interval1) {
        previousMillis1 = currentMillis;

        white1_state = !white1_state; 
        digitalWrite(white1, white1_state); 
    }
      
  }
  
  else{
    digitalWrite(white2, HIGH); 
    digitalWrite(white3, LOW); 
    digitalWrite(white4, HIGH); 
    digitalWrite(red1, LOW); 
    digitalWrite(red2, LOW); 
    digitalWrite(red3, HIGH); 
    digitalWrite(red4, LOW); 
    digitalWrite(red5, LOW);
    
    if (currentMillis - previousMillis1 >= interval1) {
        previousMillis1 = currentMillis;

        white1_state = !white1_state; 
        white5_state = !white5_state; 
        digitalWrite(white1, white1_state); 
        digitalWrite(white5, white5_state);
    }
      
  }
   if (currentMillis - previousMillis2 >= interval2) {
       previousMillis2 = currentMillis; 
       Particle.publish("temperature_stream", String((temperature - init_temperature))); 
   }
 
}

