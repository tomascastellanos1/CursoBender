#define outputA 7
#define outputB 6
#define boton 8

int seleccion = 0;
int aState;
int aLastState;
int pin_mq = 2;
int j = 255;

bool hablando = false;
bool temporizador = false;
int tiempo =0;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif
#define PIN        3 
#define NUMPIXELS 24



Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  
       pinMode (outputA,INPUT);
       pinMode (outputB,INPUT);
       pinMode (boton, INPUT_PULLUP);
       pinMode(pin_mq,INPUT);
       Serial.begin (9600);
       aLastState = digitalRead(outputA);   

        pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
        pixels.setBrightness(j);

}

void loop() {

    pixels.setPixelColor(20, pixels.Color(255, 255, 255));
    pixels.setPixelColor(21, pixels.Color(255, 255, 255));
    pixels.setPixelColor(22, pixels.Color(255, 255, 255));
    pixels.setPixelColor(23, pixels.Color(255, 255, 255));
  
    aState = digitalRead(outputA);
    
    if (aState != aLastState)
     { 
        if (digitalRead(outputB) != aState){
            seleccion +=1;
            temporizador=true;
        }else{
            seleccion -=1;
            temporizador=true;
  
        Serial.print("Seleccion: ");
        Serial.println(seleccion);
     }
     }
    aLastState = aState; 
    
//-------------------------

if (hablando==false){
  estatico();
}
if (hablando == true){
  habla();
}

if(seleccion<0){
  seleccion=19;
}
if(seleccion>19){
 seleccion=0;
}
if(temporizador==true){
  tiempo++;
}
if(tiempo>2000){
  tiempo=0;
  temporizador=false;
}
if(tiempo>1 && tiempo<2000){
  pixels.setPixelColor(seleccion, pixels.Color(0, 0, 0));

}


 





  pixels.show();   // Send the updated pixel colors to the hardware.  
}

void habla(){

//aqui va el codigo del habla
  
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
