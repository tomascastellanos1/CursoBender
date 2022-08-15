
#include <Arduino_GFX_Library.h>


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

}

void loop()
{
   ojo1->fillRect(95 , 95 , 50 , 50 , BLACK);
}
