// IVinyMouse test and usage documentation
// CAUTION!!!! This does click things!!!!!!!!
// Created by Sean Murphy (duckythescientist)

#include "IVinyMouse.h"

void setup() {
  // Do nothing? It seems as if the USB hardware is ready to go on reset
}

void loop() {
  // If not using plentiful IVinyMouse.delay(), make sure to call
  // DigiMouse.update() at least every 50ms
  
  // move across the screen
  // these are signed chars
  IVinyMouse.moveY(10); //down 10
  IVinyMouse.delay(500);
  IVinyMouse.moveX(20); //right 20
  IVinyMouse.delay(500);
  IVinyMouse.scroll(5);
  IVinyMouse.delay(500);
  
  // or IVinyMouse.move(X, Y, scroll) works
  
  // three buttons are the three LSBs of an unsigned char
  IVinyMouse.setButtons(1<<0); //left click
  IVinyMouse.delay(500);
  IVinyMouse.setButtons(0); //unclick all
  IVinyMouse.delay(500);
}
