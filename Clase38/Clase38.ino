
#include <Arduino_GFX_Library.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
void printResult(HUSKYLENSResult result);

int ojo1X = 95;
int pin_mq = 2;

#if defined(DISPLAY1)
Arduino_GFX *ojo1 = create_default_Arduino_GFX();
#else 
Arduino_DataBus *bus = new Arduino_HWSPI(8 /* DC */, 9 /* CS */);
Arduino_GFX *ojo1 = new Arduino_GC9A01(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */);
#endif 


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif
#define PIN        3 
#define NUMPIXELS 22 


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



void setup(void)
{
    ojo1->begin();
    ojo1->fillScreen(ojo1->color565(255, 254, 196));
    pinMode(pin_mq,INPUT);
    Serial.begin(115200);
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }

    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(255);
    

}

void loop()
{
   ojo1->fillRect(ojo1X , 95 , 50 , 50 , BLACK);
   ojo1->fillRect(ojo1X+50 , 95 , 240 , 50 , ojo1->color565(255, 254, 196));
   ojo1->fillRect(ojo1X-240 , 95 , 240 , 50 ,ojo1->color565(255, 254, 196));
   
if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
        }    
    }

   boolean mq_estado = digitalRead(pin_mq);

  if (mq_estado){ //si no detecta alcohol
  ojo1->fillCircle(120,355,200, ojo1->color565(255, 254, 196));
  }
  else { //si detecta alcohol
  ojo1->fillCircle(120,355,200, BLACK);
  }

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
 

    pixels.show();   // Send the updated pixel colors to the hardware.

   
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("POSX:")+result.xCenter+F(",POSY:")+result.yCenter+F(" CARA_APRERNDIDA")+result.ID);
        ojo1X=(-result.xCenter/1.33f)+220;
    }
    else{
        Serial.println("No reconozco cara!");
    }
}
