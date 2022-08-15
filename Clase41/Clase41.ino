
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial reproductor(4, 5); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
delay(500);
   reproductor.begin(9600);
  Serial.begin(115200);
  

 if (!myDFPlayer.begin(reproductor)) {  //Use softwareSerial to communicate with mp3.
   
    while(true){
       
    }
  }

  myDFPlayer.volume(100);  //Set volume value. From 0 to 30
   //Play the first mp3
  myDFPlayer.play(1); 
  
}
void loop() {
 
}
