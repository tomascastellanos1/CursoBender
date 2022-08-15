#define outputA 6
#define outputB 7
#define boton 8

int seleccion = 0;
int aState;
int aLastState;

void setup() {
  
       pinMode (outputA,INPUT);
       pinMode (outputB,INPUT);
       pinMode (boton, INPUT_PULLUP);
       Serial.begin (9600);
       aLastState = digitalRead(outputA);   

}

void loop() {
  
    aState = digitalRead(outputA);
    if (aState != aLastState)
     {
        if (digitalRead(outputB) != aState) 
            seleccion +=1;
        else
            counter -=1;
  
        Serial.print("Seleccion: ");
        Serial.println(seleccion);
     }
    aLastState = aState; 

}
