#include <IVinyUSB.h>

void setup() {
  IVinyUSB.begin();
}

void get_input() {
  int lastRead;
  // when there are no characters to read, or the character isn't a newline
  while (true) { // loop forever
    if (IVinyUSB.available()) {
      // something to read
      lastRead = IVinyUSB.read();
      IVinyUSB.write(lastRead);
      
      if (lastRead == '\n') {
        break; // when we get a newline, break out of loop
      }
    }
    
    // refresh the usb port for 10 milliseconds
    IVinyUSB.delay(10);
  }
}

void loop() {
  // print output
  IVinyUSB.println("Waiting for input...");
  // get input
  get_input();
}
