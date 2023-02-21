#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int motionPin = 12;
int moisturePin = A0;

int motionVal = 0;
bool motionState = false; // We start with no motion detected.
int moistureVal = 0;
int moistureLimitValue = 500;
int volume = 30; //Set volume value (0~30).

void setup()
{
  pinMode(motionPin, INPUT);
  pinMode(moisturePin, INPUT);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial, false)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  //----Set volume----
  myDFPlayer.volume(volume);  //Set volume value (0~30).
  delay(1000); // so it hopefully saves the setting
  
 //----Read volume----
  Serial.println("Volume:");
  Serial.println(myDFPlayer.readVolume()); //read current volume
 
}

void loop()
{
  motionVal = digitalRead(motionPin);
  moistureVal = analogRead(moisturePin);


  // If motion is detected (pirPin = HIGH), do the following:
  if (motionVal == HIGH && moistureVal > moistureLimitValue) {
    // Change the motion state to true (motion detected):
    if (motionState == false) {
      Serial.println("Motion detected!");
      Serial.println(moistureVal);
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