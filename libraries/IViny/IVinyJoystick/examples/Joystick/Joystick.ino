//IVinyJoystick test and usage documentation

#include "IVinyJoystick.h"

void setup() {
  // Do nothing? It seems as if the USB hardware is ready to go on reset
}


void loop() {
  // If not using plentiful DigiJoystick.delay() calls, make sure to
  //IVinyJoystick.update(); // call this at least every 50ms
  // calling more often than that is fine
  // this will actually only send the data every once in a while unless the data is different
  
  // you can set the values from a raw byte array with:
  // char myBuf[8] = {
  //   x, y, xrot, yrot, zrot, slider,
  //   buttonLowByte, buttonHighByte
  // };
  // IVinyJoystick.setValues(myBuf);
  
  // Or we can also set values like this:
  IVinyJoystick.setX((byte) (millis() / 100)); // scroll X left to right repeatedly
  IVinyJoystick.setY((byte) 0x30);
  IVinyJoystick.setXROT((byte) 0x60);
  IVinyJoystick.setYROT((byte) 0x90);
  IVinyJoystick.setZROT((byte) 0xB0);
  IVinyJoystick.setSLIDER((byte) 0xF0);
  
  // it's best to use DigiJoystick.delay() because it knows how to talk to
  // the connected computer - otherwise the USB link can crash with the 
  // regular arduino delay() function
  IVinyJoystick.delay(50); // wait 50 milliseconds
  
  // we can also set buttons like this (lowByte, highByte)
  //IVinyJoystick.setButtons(0x00, 0x00);
}
