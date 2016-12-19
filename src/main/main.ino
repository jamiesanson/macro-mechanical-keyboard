/*
----------------------------------------------------------------------------------------
                            Macro mechanical keyboard main sketch
----------------------------------------------------------------------------------------

    Contains code relating to the operation of a Teensy LC board connected to 6 Cherry
    MX compatible switches. To use, refer to ButtonHandler library documentation as to
    how to set up pins in correct modes.

*/

#include "ButtonHandler.h"

#define SERIAL_BAUD 115200
#define BUTTON_PINS {2, 3, 5, 6, 7, 8}
#define BUTTON_MODES {MODIFIER, STANDARD, DISCONNECTED, DISCONNECTED, DISCONNECTED, DISCONNECTED}

ButtonConfig buttonConfig = (ButtonConfig){BUTTON_PINS, BUTTON_MODES};

ButtonHandler handler(buttonConfig);

void setup() {
  Serial.begin(SERIAL_BAUD);
  handler.setListener(onEvent);
}

void loop() {
  // Do nothing
}

void onEvent(ButtonEvent event) {
  Serial.println("Event: button number: " + String(event.number) + "; Event type: " + getEventTypeName(event.pressType));
  handler.eventComplete();
}

