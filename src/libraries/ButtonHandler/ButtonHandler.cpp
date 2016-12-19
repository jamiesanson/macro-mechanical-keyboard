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
        if (_config.buttonModes[i] != DISCONNECTED) {
            pinMode(_config.buttonPins[i], INPUT);
            attachInterrupt(_config.buttonPins[i], getISR(i), RISING);

            // Only attach falling edge interrupts for those keys we care about holding down, i.e modifiers
            if (config.buttonModes[i] == MODIFIER) {
                attachInterrupt(_config.buttonPins[i], getISR(i), FALLING);
            }
        }
    }
}

// Setting the callback function used to emit events to
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
        
        // Invert pressed state after debouncing
        _buttonStatePressed[event.number-1] = !_buttonStatePressed[event.number-1];

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
void ButtonHandler::onKeyOneEvent()
{   
    addEventForButtonNumber(1);
}

void ButtonHandler::onKeyTwoEvent()
{   
    addEventForButtonNumber(2);
}

void ButtonHandler::onKeyThreeEvent()
{   
    addEventForButtonNumber(3);
}

void ButtonHandler::onKeyFourEvent()
{   
    addEventForButtonNumber(4);
}

void ButtonHandler::onKeyFiveEvent()
{   
    addEventForButtonNumber(5);
}

void ButtonHandler::onKeySixEvent()
{   
    addEventForButtonNumber(6);
}
// End region

void ButtonHandler::addEventForButtonNumber(int number)
{
    if (_config.buttonModes[number-1] == MODIFIER) {
        addEvent((ButtonEvent) {number, _buttonStatePressed[number-1] ? BUTTON_UP : BUTTON_DOWN});
    } else {        
        addEvent((ButtonEvent) {number, BUTTON_PRESS});
    }

    _buttonTimeout = 0;
}

// Upsetting spaghetti code to get a pointer to the ISR relating to the index of the button being initialised
Isr ButtonHandler::getISR(int buttonNumber)
{
    switch (buttonNumber) {
        case 0:
            return keyOneAction;
        case 1:
            return keyTwoAction;
        case 2:
            return keyThreeAction;
        case 3:
            return keyFourAction; 
        case 4:
            return keyFiveAction; 
        case 5:
            return keySixAction;
    }

    return NULL;
}

