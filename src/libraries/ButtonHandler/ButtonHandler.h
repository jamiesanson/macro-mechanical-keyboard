/**
    This file, along with the accompanying implementation file contain code to handle button press events
    from simple buttons, where a HI logic level represents a button pressed.
*/

#include <Arduino.h>
#include <avr/pgmspace.h>

// Length of buffer containing current events
#define EVENT_BUFFER_LENGTH 50

// Defining event types for button presses, where up and down correspond to hold events,
// and press is a single item
PROGMEM enum ButtonEventType 
{   
    UNKNOWN,
    BUTTON_DOWN,
    BUTTON_UP,
    BUTTON_PRESS
};

// Defines modes for which buttons can be initialised to. STANDARD only considers single press
// events, whereas MODIFIER considers both down, and up press action
PROGMEM enum ButtonMode
{
    STANDARD,
    MODIFIER
};

// Struct for maintaining information regarding button events
struct ButtonEvent 
{
    int number;
    ButtonEventType pressType;
};


class ButtonHandler 
{
    public:
        // Constructor
        ButtonHandler(ButtonMode * modes);

        // Returns a pointer to the current event to process, where the event contains {-1, UNKNOWN}
        // if there is no current event
        ButtonEvent getCurrent();

    private:  
        // Buffer of events, maintains a queue-like implementation when items are added or removed
        ButtonEvent _events[EVENT_BUFFER_LENGTH];        
        // For queue implementation
        int _lastIndex = 0; 

        // Does as the name implies
        boolean isEventsEmpty();
        
        // Shifts item indices in the buffer such that the first item is the current action
        void resizeEvents();
};

