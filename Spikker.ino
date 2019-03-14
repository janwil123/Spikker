#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// D7 - Serial clock out (CLK oder SCLK)
// D6 - Serial data out (DIN)
// D5 - Data/Command select (DC oder D/C)
// D4 - LCD chip select (CE oder CS)
// D3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

int pinA = 10;  // Connected to CLK on KY-040
int pinB = 11;  // Connected to DT on KY-040
int encoderPosCount = 0; 
int pinALast;  
int aVal;
boolean bCW;


void set_text(int x,int y,String text,int color){
  
  display.setTextColor(color); // Textfarbe setzen, also Schwarz oder Weiss
  display.setCursor(x,y);      // Startpunkt-Position des Textes
  display.println(text);       // Textzeile ausgeben
  display.display();           // Display aktualisieren

  pinMode (pinA,INPUT);
  pinMode (pinB,INPUT);
   /* Read Pin A
   Whatever state it's in will reflect the last position   
   */
  pinALast = digitalRead(pinA); 
}

void setup()   {

  display.begin();

  // Kontrast setzen
  display.setContrast(60);
  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(1);
  //set_text(11,0,"Hello!",BLACK);
}


void loop() {
   aVal = digitalRead(pinA);
   if (aVal != pinALast){ // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       encoderPosCount--;
     }
     Serial.print ("Rotated: ");
     if (bCW){
       Serial.println ("clockwise");
       set_text(11,0,"clockwise",WHITE);
       set_text(11,0,"counterclockwise",WHITE);
       set_text(11,0,"clockwise",BLACK);
     }else{
       Serial.println("counterclockwise");
       set_text(11,0,"clockwise",WHITE);
       set_text(11,0,"counterclockwise",WHITE);
       set_text(11,0,"counterclockwise",BLACK);
     }
     Serial.print("Encoder Position: ");
     Serial.println(encoderPosCount);
     
   } 
   pinALast = aVal;
}
