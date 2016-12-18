#include <Arduino.h>
#include <ButtonHandler.h>

ButtonHandler * _buttonHandler;

// Empty constructor
ButtonHandler::ButtonHandler(ButtonConfig config) : _config(config)
{
    // Global reference needed for global ISR pointer
    _buttonHandler = this;

    for (int i = 0; i < ButtonConfig::MAX_BUTTONS; i++) 
    {
        pinMode(_config.buttonPins[i], INPUT);
        attachInterrupt(_config.buttonPins[i], getISR(i, true), RISING);

        if (config.buttonModes[i] == MODIFIER) {
            attachInterrupt(_config.buttonPins[i], getISR(i, false), FALLING);
        }
    }
}

void ButtonHandler::setListener(EventListener listener) {
    _listener = listener;
}

// Emits the next queued event if it exists
void ButtonHandler::eventComplete() 
{
    
    if (!isEventsEmpty()) {
        _listener(_events[0]);
        resizeEvents();
    } else {
        _processingComplete = true;
    }
}

// Returns whether or not the event queue is empty
boolean ButtonHandler::isEventsEmpty() 
{
    return _lastIndex == 0;
}

// Shifts event array down an indices such that index 1 -> index 0 etc.
void ButtonHandler::resizeEvents() 
{
    for (int i = 0; i < _lastIndex; i++) {
        _events[i] = _events[i+1];
    }

    _lastIndex -= 1;
    Serial.println(String(_lastIndex));
}

// Adds event to the queue if there is room in the queue.
// If the consumer of the library is not processing an event, and the 
// events queue is empty then simply emit the event, and queue others
void ButtonHandler::addEvent(ButtonEvent event) {
    if (_lastIndex < EVENT_BUFFER_LENGTH && _buttonTimeout > BUTTON_DEBOUNCE_INTERVAL_MILLIS) {
        noInterrupts();
        if (_processingComplete && isEventsEmpty()) {
            _processingComplete = false;
            _listener(event);
        } else {            
            _events[_lastIndex] = event;            
            _lastIndex += 1;
        }
        interrupts();
    }
}

// Region ISR implementation
void ButtonHandler::onKeyOneUp()
{   
    addEvent((ButtonEvent) {1, BUTTON_UP});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyOneDown()
{
    addEvent((ButtonEvent) {1, _config.buttonModes[0] == STANDARD ? BUTTON_PRESS : BUTTON_DOWN});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyTwoUp()
{
    addEvent((ButtonEvent) {2, BUTTON_UP});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyTwoDown()
{
    addEvent((ButtonEvent) {2, _config.buttonModes[1] == STANDARD ? BUTTON_PRESS : BUTTON_DOWN});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyThreeUp()
{
    addEvent((ButtonEvent) {3, BUTTON_UP});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyThreeDown()
{
    addEvent((ButtonEvent) {3, _config.buttonModes[2] == STANDARD ? BUTTON_PRESS : BUTTON_DOWN});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyFourUp()
{
    addEvent((ButtonEvent) {4, BUTTON_UP});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyFourDown()
{
    addEvent((ButtonEvent) {4, _config.buttonModes[3] == STANDARD ? BUTTON_PRESS : BUTTON_DOWN});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyFiveUp()
{
    addEvent((ButtonEvent) {5, BUTTON_UP});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeyFiveDown()
{
    addEvent((ButtonEvent) {5, _config.buttonModes[4] == STANDARD ? BUTTON_PRESS : BUTTON_DOWN});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeySixUp()
{
    addEvent((ButtonEvent) {6, BUTTON_UP});
    _buttonTimeout = 0;
}

void ButtonHandler::onKeySixDown()
{
    addEvent((ButtonEvent) {6, _config.buttonModes[5] == STANDARD ? BUTTON_PRESS : BUTTON_DOWN});
    _buttonTimeout = 0;
}
// End region

// Upsetting spaghetti code to get a pointer to the ISR relating to the index of the button being initialised
Isr ButtonHandler::getISR(int buttonNumber, boolean isRising)
{
    switch (buttonNumber) {
        case 0:
            return isRising ? keyOneDown : keyOneUp;
        case 1:
            return isRising ? keyTwoDown : keyTwoUp;
        case 2:
            return isRising ? keyThreeDown : keyThreeUp;
        case 3:
            return isRising ? keyFourDown : keyFourUp;
        case 4:
            return isRising ? keyFiveDown : keyFiveUp;
        case 5:
            return isRising ? keySixDown : keySixUp;
    }

    return NULL;
}

