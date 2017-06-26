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
#define SD_CS 10
#define SD_CD 15

#define BUTTON_COUNT 6
#define BUTTON_PINS {2, 3, 5, 6, 7, 8}
#define BUTTON_MODES {STANDARD, DISCONNECTED, DISCONNECTED, DISCONNECTED, DISCONNECTED, DISCONNECTED}

ButtonConfig buttonConfig = (ButtonConfig){BUTTON_PINS, BUTTON_MODES};

ButtonHandler handler(buttonConfig);
MacroManager manager(SD_CS, SD_CD);

void setup() {
  Serial.begin(SERIAL_BAUD);
  handler.setListener(onEvent);
}

void loop() {
  handler.onLoop();
}

void onEvent(ButtonEvent event) {
  Serial.println("Event: button number: " + String(event.number) + "; Event type: " + getEventTypeName(event.pressType));  
  manager.buttonPressed(String(1));
}

