#include <IVinyUSB.h>

void setup() {
  IVinyUSB.begin();
}

void get_input() {
  // when there are no characters to read
  while (1==1) {
    if(IVinyUSB.available()){
      //something to read
      IVinyUSB.read();
      break;
    }
    // refresh the usb port
    IVinyUSB.refresh();
    delay(10);

  }

}

void loop() {
  IVinyUSB.refresh();
  //print output
  float value = analogRead(1); //This is Pin3
  if(value>1020)
    value = 255;
  else if(value<2)
    value = 0;
  else
    value = value/4;
   //send value
  
  value = round(byte(value));
  IVinyUSB.write(value);
  
  //wait for response
  get_input();
}
