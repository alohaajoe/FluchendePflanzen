#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int pirPin = 12;

int pirVal = 0;
bool motionState = false; // We start with no motion detected.

void setup()
{
  pinMode(pirPin, INPUT);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial, false)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).
  delay(1000);
  
 //----Read volume----
  Serial.println("Volume:");
  Serial.println(myDFPlayer.readVolume()); //read current volume
 
}

void loop()
{
  pirVal = digitalRead(pirPin); // Read out the pirPin and store as val:

  // If motion is detected (pirPin = HIGH), do the following:
  if (pirVal == HIGH) {
    // Change the motion state to true (motion detected):
    if (motionState == false) {
      Serial.println("Motion detected!");
      motionState = true;
      myDFPlayer.play(2);
    }
  }
  // If no motion is detected (pirPin = LOW), do the following:
  else {
    // Change the motion state to false (no motion):
    if (motionState == true) {
      Serial.println("Motion ended!");
      motionState = false;
    }
  }
}