
#include <Arduino_GFX_Library.h>

/*PANTALLA 1:
 * GND - GND
 * VCC - 3.3V
 * SCL - D52
 * SDA - D51
 * RES - D7
 * DC - D8
 * CS - D9
 */
#if defined(DISPLAY1)
Arduino_GFX *ojo1 = create_default_Arduino_GFX();
#else 
Arduino_DataBus *bus = new Arduino_HWSPI(8 /* DC */, 9 /* CS */);
Arduino_GFX *ojo1 = new Arduino_GC9A01(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */);
#endif 

/*PANTALLA 2:
 * GND - GND
 * VCC - 3.3V
 * SCL - D52
 * SDA - D51
 * RES - D6
 * DC - D5
 * CS - D4
 */
#if defined(DISPLAY2)
Arduino_GFX *ojo2 = create_default_Arduino_GFX();
#else 
Arduino_DataBus *bus2 = new Arduino_HWSPI(5 /* DC */, 4 /* CS */);
Arduino_GFX *ojo2 = new Arduino_GC9A01(bus2, 6 /* RST */, 0 /* rotation */, true /* IPS */);
#endif 





void setup(void)
{
    ojo1->begin();
    ojo1->fillScreen(ojo1->color565(255, 254, 196));

    ojo2->begin();
    ojo2->fillScreen(ojo2->color565(255, 254, 196));

}

void loop()
{
   ojo1->fillRect(95 , 95 , 50 , 50 , BLACK);
   ojo2->fillRect(95 , 95 , 50 , 50 , BLACK);
}
