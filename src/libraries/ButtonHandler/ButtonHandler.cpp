#include <Arduino.h>
#include <Bounce2.h>
#include <ButtonHandler.h>

// Empty constructor
ButtonHandler::ButtonHandler() {}

ButtonEvent ButtonHandler::getCurrent() 
{
    return (ButtonEvent) {-1, UNKNOWN};
}

boolean ButtonHandler::isEventsEmpty() {
    return false;
}

void ButtonHandler::resizeEvents() {

}