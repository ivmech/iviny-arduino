#define USB_CFG_DEVICE_NAME     'I','V','B','l','i','n','k'
#define USB_CFG_DEVICE_NAME_LEN 7
#include <IVinyUSB.h>
byte in = 0;
int Blue = 0;
int Red = 0;
int Green = 0;

int next = 0;

void setup() {
    IVinyUSB.begin();
    pinMode(0,OUTPUT);
    pinMode(1,OUTPUT);
    pinMode(2,OUTPUT);
}


void loop() {
  setBlue();
      IVinyUSB.refresh();
      setBlue();
     if (IVinyUSB.available() > 0) {
       in = 0;
       
       in = IVinyUSB.read();
       if (next == 0){
         if(in == 115){
           next = 1;
           IVinyUSB.println("Start");
         }
       }
       else if (next == 1){
            Red = in;
            IVinyUSB.print("Red ");
            IVinyUSB.println(in,DEC);
            next = 2;
       }
       else if (next == 2){
            Green = in;
            IVinyUSB.print("Green ");
            IVinyUSB.println(in,DEC);
            next = 3;
       }
       else if (next == 3){
            Blue = in;
            IVinyUSB.print("Blue ");
            IVinyUSB.println(in,DEC);
            next = 0;
       }


        
        
     }
     

    analogWrite(0,Red);
    analogWrite(1,Green);
     setBlue();

     
   
}

void setBlue(){
    if(Blue == 0){
      digitalWrite(2,LOW);
      return;
    }
    else if(Blue == 255){
      digitalWrite(2,HIGH);
      return;
    }
    // On period  
    for (int x=0;x<Blue;x++){
    digitalWrite(2,HIGH);
    } 
    
    // Off period
    
    for(int x=0;x<(255-Blue);x++){
    digitalWrite(2,LOW);
    }
  
} 

