#include <ButtonHandler.h>

ButtonHandler * _buttonHandler;

ButtonHandler::ButtonHandler(ButtonConfig config) : _config(config)
{
    // Global reference needed for global ISR pointer
    _buttonHandler = this;
    InterruptHelper<ButtonConfig::MAX_BUTTONS - 1>::attach(_config);
}

// Setting the callback function used to emit events to
void ButtonHandler::setListener(EventListener listener) 
{
    _listener = listener;    
}

// Loop passthrough to handle event dispatching of queued items
void ButtonHandler::onLoop()
{
    if (!isEventsEmpty()) {
        _listener(_events[0]);
        resizeEvents();
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

    _lastIndex--;
}

// Adds event to the queue if there is room in the queue.
// If the consumer of the library is not processing an event, and the 
// events queue is empty then simply emit the event, and queue others
void ButtonHandler::addEvent(ButtonEvent event) {
    if (_lastIndex < EVENT_BUFFER_LENGTH && _buttonTimeout > BUTTON_DEBOUNCE_INTERVAL_MILLIS) {
        
        // Invert pressed state after debouncing, used for modifier presses only
        _buttonStatePressed[event.number-1] = !_buttonStatePressed[event.number-1];
        
        // Add event to buffer and increment last index
        _events[_lastIndex] = event;            
        _lastIndex++;
    }
}

void ButtonHandler::onPress(int number) 
{
    addEvent((ButtonEvent) {number, BUTTON_PRESS});
    _buttonTimeout = 0;
}

void ButtonHandler::onModifier(int number) 
{
    addEvent((ButtonEvent) {number, _buttonStatePressed[number-1] ? BUTTON_UP : BUTTON_DOWN});
    _buttonTimeout = 0;
}

