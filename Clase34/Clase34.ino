
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

  if (mq_estado){
 //aqui va el codigo sin presencia de alcohol
  }
  else {

 //aqui va el codigo con presencia de alcohol
    
  }
   
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
