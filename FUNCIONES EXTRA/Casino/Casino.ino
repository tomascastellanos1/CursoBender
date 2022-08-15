#define outputA 7
#define outputB 6
#define boton 8

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial reproductor(4, 5); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int seleccion = 0;
int aState;
int aLastState;
int pin_mq = 2;
int j = 255;

bool hablando = false;
bool temporizador = false;
int tiempo =0;
long frase;

bool viajetiempo =false;
long temporizadorviaje;
int temporizadorviaje2 = 0;
long fraseviaje;

bool alcohol = false;
int temporizadoralcohol=0;

long cancion;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif
#define PIN        3 
#define NUMPIXELS 24 

long randNumber;  //variable to hold random number value
int pos;          //used to track position of lit segment


#define PIN 3     //data pin used in for neopixel
int spins = 6;        //how many times to 'spin before starting to slow down and settle
#define dir 1  //set to 1 for clockwise rotation, 0 for counter clockwise.

bool casino =false;



Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);




void setup() {
 delay(500);
       pinMode (outputA,INPUT);
       pinMode (outputB,INPUT);
       pinMode (boton, INPUT_PULLUP);
       pinMode(pin_mq,INPUT);
     Serial.begin(9600);
       aLastState = digitalRead(outputA);   

        pixels.begin(); // INITIALIZE NeoPixel pixels object (REQUIRED)
        pixels.setBrightness(j);

        reproductor.begin(9600);
      
   randomSeed(analogRead(1+2+3+4+5));  //initialize floating pin (analog pins 1-5) as the seed for the RNG

 if (!myDFPlayer.begin(reproductor)) {  //Use softwareSerial to communicate with mp3.
   
    while(true){
       
    }
  }
  myDFPlayer.volume(100);  

}

void loop() {
  

    frase = random(10, 48);
    fraseviaje = random(3, 5);
    cancion = random(44, 49);
Serial.println(temporizadoralcohol);

//--USO DEL POTENCIÓMETRO  
    aState = digitalRead(outputA);
    if (aState != aLastState)
     { 
        if (digitalRead(outputB) != aState){
            seleccion +=1;
            temporizador=true;
        }else{
            seleccion -=1;
            temporizador=true;
     }
     }
    aLastState = aState; 
    
//-------------------------

if(viajetiempo==false && casino==false){
   pixels.setPixelColor(20, pixels.Color(255, 255, 255));
    pixels.setPixelColor(21, pixels.Color(255, 255, 255));
     pixels.setPixelColor(22, pixels.Color(255, 255, 255));
    pixels.setPixelColor(23, pixels.Color(255, 255, 255));
if (hablando==false){
  estatico();
}
if (hablando == true){
  habla();
}
}

if(seleccion<0){
  seleccion=0;
}
if(seleccion>10){
 seleccion=10;
}
if(temporizador==true){
  tiempo++;
}
if(tiempo>2000){
  tiempo=0;
  temporizador=false;
}




int estado = digitalRead(boton);
boolean play_state = digitalRead(9);

//--SELECTOR DE FUNCIONES
if(tiempo>1 && tiempo<2000){
  if(seleccion == 0){ //--BENDER HABLA
   pixels.setPixelColor(12, pixels.Color(196, 4, 195));
}
 if(seleccion == 2){ //--VIAJE EN EL TIEMPO
   pixels.setPixelColor(11, pixels.Color(6, 102, 155));
}
 if(seleccion == 4){//--ALCOHOLÍMETRO
   pixels.setPixelColor(10, pixels.Color(3, 255, 102));
}
 if(seleccion == 6){//--RULETA CASINO
   pixels.setPixelColor(9, pixels.Color(253, 255, 3));
}
 if(seleccion == 8){
   pixels.setPixelColor(8, pixels.Color(255, 144, 13));
}
 if(seleccion == 10){
   pixels.setPixelColor(7, pixels.Color(255, 16, 16));
}
}

if (estado==LOW){
  if(seleccion==0){ //SI SELECCIONAMOS EL HABLA
 myDFPlayer.playMp3Folder(frase); 
  delay(500);
  }
  
  if(seleccion==2){ //SI SELECCIONAMOS EL VIAJE EN EL TIEMPO
myDFPlayer.playMp3Folder(1);
  delay(3000);
  viaje_tiempo();
  viajetiempo=true;
  }
  
 if(seleccion==4){ //SI SELECCIONAMOS EL ALCOHOLIMETRO
 myDFPlayer.playMp3Folder(2);
  delay(3000);
  alcohol= true;
  }

  if(seleccion==6){ //SI SELECCIONAMOS EL CASINO
 casino=true;
  myDFPlayer.playMp3Folder(6);
  }

}
//-------------------

if (alcohol ==true){
  alcoholimetro();
  temporizadoralcohol++;
}

if(casino==true){
  tiempo = 0;
 pixels.clear();temporizador=false;

  pixels.setPixelColor(0, pixels.Color(23,200,50));
pixels.setPixelColor(1, pixels.Color(223,0,5));
pixels.setPixelColor(2, pixels.Color(23,200,50));
pixels.setPixelColor(3, pixels.Color(223,0,5));
pixels.setPixelColor(4, pixels.Color(23,200,50));
pixels.setPixelColor(5, pixels.Color(223,0,5));
pixels.setPixelColor(6, pixels.Color(23,200,50));
pixels.setPixelColor(7, pixels.Color(223,0,5));
pixels.setPixelColor(8, pixels.Color(23,200,50));
pixels.setPixelColor(9, pixels.Color(223,0,5));
pixels.setPixelColor(10, pixels.Color(23,200,50));
pixels.setPixelColor(11, pixels.Color(223,0,5));
pixels.setPixelColor(12, pixels.Color(23,200,50));
pixels.setPixelColor(13, pixels.Color(223,0,5));
pixels.setPixelColor(14, pixels.Color(23,200,50));
pixels.setPixelColor(15, pixels.Color(223,0,5));
pixels.setPixelColor(16, pixels.Color(23,200,50));
pixels.setPixelColor(17, pixels.Color(223,0,5));
pixels.setPixelColor(18, pixels.Color(23,200,50));
pixels.setPixelColor(19, pixels.Color(223,0,5));

  randNumber=random(0,20);  //fetch a random number between 1-16

  //call the wheel
           //color used for for odd segments, even segments, and for '0'
  roulette(pixels.Color(25,255,128),pixels.Color(255,23,21),pixels.Color(120,26,55));   
  }


if(play_state ==  HIGH ){
  hablando=false;
}else{
  if(seleccion == 0){
  hablando=true;
  }
}


//--VIAJES EN EL TIEMPO
if( temporizadorviaje2 >= temporizadorviaje){
  viajetiempo=false;
  temporizadorviaje2=0;
}
if(viajetiempo==true){
  temporizadorviaje2 +=temporizadorviaje/20;
}

//--------------------

  pixels.show();   // Send the updated pixel colors to the hardware.  
}




void habla(){

tiempo=0;

uint16_t i;
   
  for (i = 0; i < 6; i++) { //linea arriba
       pixels.show();
    pixels.setPixelColor(i, 20, 20, 20);
  }
  for (i = 6; i < 13; i++) { //linea media
       pixels.show();
    pixels.setPixelColor(i, j, j, j);
  }
   for (i = 13; i < 20; i++) { //linea abajo
       pixels.show();
    pixels.setPixelColor(i, 20, 20, 20);
  }

  if(j>0){j+=50;}   if(j>256){j=40;}
 
   temporizador=false;
  
}

void estatico (){

    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.setPixelColor(1, pixels.Color(255, 255, 255));
    pixels.setPixelColor(2, pixels.Color(255, 255, 255));
    pixels.setPixelColor(3, pixels.Color(255, 255, 255));
    pixels.setPixelColor(4, pixels.Color(255, 255, 255));
    pixels.setPixelColor(5, pixels.Color(255, 255, 255));
    pixels.setPixelColor(6, pixels.Color(255, 255, 255));
    pixels.setPixelColor(7, pixels.Color(255, 255, 255));
    pixels.setPixelColor(8, pixels.Color(255, 255, 255));
    pixels.setPixelColor(9, pixels.Color(255, 255, 255));
    pixels.setPixelColor(10, pixels.Color(255, 255, 255));
    pixels.setPixelColor(11, pixels.Color(255, 255, 255));
    pixels.setPixelColor(12, pixels.Color(255, 255, 255));
    pixels.setPixelColor(13, pixels.Color(255, 255, 255));
    pixels.setPixelColor(14, pixels.Color(255, 255, 255));
    pixels.setPixelColor(15, pixels.Color(255, 255, 255));
    pixels.setPixelColor(16, pixels.Color(255, 255, 255));
    pixels.setPixelColor(17, pixels.Color(255, 255, 255));
    pixels.setPixelColor(18, pixels.Color(255, 255, 255));
    pixels.setPixelColor(19, pixels.Color(255, 255, 255));

}

void viaje_tiempo(){


tiempo = 0;
 pixels.clear();
temporizador=false;

temporizadorviaje = random (20000,30000);



 for(int i=0; i<20; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(3, 255, 102));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(temporizadorviaje/20); // Pause before next pass through loop
  }
  myDFPlayer.play(fraseviaje); 
  pixels.clear();
  delay(3000);
  
}

void alcoholimetro (){

  tiempo = 0;
 
temporizador=false;
 boolean mq_estado = digitalRead(pin_mq);

 if (mq_estado){ //si no detecta alcohol
  
 if(temporizadoralcohol==2000){
  
  myDFPlayer.playMp3Folder(28);
  temporizadoralcohol=0;
  alcohol=false;
 }
  }
  else { //si detecta alcohol
  myDFPlayer.playMp3Folder(41);
  temporizadoralcohol=0;
  delay (1200);
  alcohol=false;

  }
  
}
void roulette(uint32_t c,uint32_t d,uint32_t e) {

    //spin the number of times (variable 'spin') at full speed
      for (int i=0; i<16*spins; i++){
           advanceOne(c,d,e, 4);
      }   
     
      //slow down and 'settle' on final number
      for (int i=0; i<(16*6)+randNumber; i++){
           advanceOne(c,d,e, (i*.25)+4);
      }
myDFPlayer.playMp3Folder(7);
delay(3000);
  casino=false;

} //end 'roulette' function

void advanceOne(uint32_t c,uint32_t d,uint32_t e, uint16_t wait) {


            clr();//Clear the display

              if ((pos & 0x01) == 0) {    //check to see if position is an even number
                    pixels.setPixelColor(pos, c); //turn on the pixel at position 'pos'
               } else  //else it is odd
                 {pixels.setPixelColor(pos, d);
               }
 
              if (pos == 0) { //or check to see if it is '0'
                 pixels.setPixelColor(pos, e);
               }

            pixels.show(); 
            delay(wait);

            if (dir){    //if direction var is set to clockwise
                  pos--;  //decrement the position
                  if(pos<0)  {pos=15;}  //resets running count if < 0}
            }
                else{
                  pos++;  //increment the position
                  if(pos>15)  {pos=0;}  //resets running count if > 15}
            }

}//end advanceOne function


//──────────────────────┤ Clear all pixels Function ├────────────────────────────

//clears the display
void clr(){
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 0);
    pixels.show();
  } 
}
