/*
----------------------------------------------------------------------------------------
                            Macro mechanical keyboard main sketch
----------------------------------------------------------------------------------------

    Contains code relating to the operation of a Teensy LC board connected to 6 Cherry
    MX compatible switches. 

    To use, refer to ButtonHandler library documentation for how to configure individual 
    buttons as different modes. Also, refer to the documentation for the MacroManager 
    library, used for doing the heavy lifting of actually dispatching the HID commands.
*/

#include "ButtonHandler.h"
#include "MacroManager.h" 

#define SERIAL_BAUD 115200
#define BUTTON_COUNT 6
#define BUTTON_PINS {2, 3, 5, 6, 7, 8}
#define BUTTON_MODES {STANDARD, STANDARD, DISCONNECTED, DISCONNECTED, DISCONNECTED, DISCONNECTED}

#define KEY_CTRL 69

ButtonConfig buttonConfig = (ButtonConfig){BUTTON_PINS, BUTTON_MODES};

ButtonHandler handler(buttonConfig);
MacroManager manager;

void setup() {
  Serial.begin(SERIAL_BAUD);
  handler.setListener(onEvent);
  while (!Serial.available());
  manager.setupButton(0, buildTestString());
}

void loop() {}

void onEvent(ButtonEvent event) {
  Serial.println("Event: button number: " + String(event.number) + "; Event type: " + getEventTypeName(event.pressType));  
  manager.dispatchForIndex(event.number - 1);   
  handler.eventComplete(); 
}

//void handleOne() {
//  Keyboard.set_key1(KEY_T);
//  Keyboard.send_now();
//  delay(50);
//  Keyboard.println("What a cunt!");
//  delay(100);
//  handler.eventComplete();
//}
//
//void handleTwo() {
//  Keyboard.set_key1(KEY_T);
//  Keyboard.send_now();
//  delay(50);
//  Keyboard.println("Nice meme!");
//  delay(100);
//  handler.eventComplete();
//}

String buildTestString() {
  String test = "";
  // delay
  test += COMMAND('t');
  test += String(2000);
  test += COMMAND('t');

  // modifier down
  test += COMMAND('d');
  test += String(KEY_CTRL);
  test += COMMAND('d');

  // modifier up
  test += COMMAND('u');
  test += String(KEY_CTRL);
  test += COMMAND('u');

  test += "Random text in the middle to try stuff things up";

  // single char
  test += COMMAND('c');
  test += String('k');
  test += COMMAND('c');

  // raw string
  test += COMMAND('s');
  test += String("This is a test string");
  test += COMMAND('s');
  
  return test;
}


