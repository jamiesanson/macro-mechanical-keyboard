/**
    This file, along with the accompanying implementation file contain code to handle button press events
    from simple buttons, where a HI logic level represents a button pressed.
*/

#include <Arduino.h>
#include <avr/pgmspace.h>

#ifndef ButtonHandler_H
#define ButtonHandler_H

// Length of buffer containing current events
#define EVENT_BUFFER_LENGTH 50

#define BUTTON_DEBOUNCE_INTERVAL_MILLIS 75

#define SUPPRESS_UNUSED(param) (void)param 

// Defining event types for button presses, where up correspond to hold events
PROGMEM enum ButtonEventType 
{   
    UNKNOWN,
    BUTTON_DOWN,
    BUTTON_UP,
    BUTTON_PRESS
};

// Defines modes for which buttons can be initialised to. STANDARD only considers single press
// events, whereas MODIFIER considers both down, and up press action
//
// DISCONNECTED used for debugging to avoid unwanted events
PROGMEM enum ButtonMode
{
    STANDARD,
    MODIFIER,
    DISCONNECTED
};

// Struct for maintaining information regarding button events
struct ButtonEvent 
{
    int number;
    ButtonEventType pressType;
};

// Struct holding config information, i.e button pins and modes
struct ButtonConfig
{
    // Defines maximum amount of buttons able to be used, which is required
    // due to the use of fixed ISRs for each button event
    static const PROGMEM int MAX_BUTTONS = 6;

    int buttonPins[MAX_BUTTONS];
    ButtonMode buttonModes[MAX_BUTTONS];
};

// static function for getting a String describing the enum constant
const static String getEventTypeName(ButtonEventType type) {
    SUPPRESS_UNUSED(getEventTypeName);

    switch (type) {
        case BUTTON_DOWN:
            return "BUTTON_DOWN";
        case BUTTON_UP:
            return "BUTTON_UP";
        case BUTTON_PRESS:
            return "BUTTON_PRESS";
        case UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

// Global function pointer typedefs
typedef void (*Isr)(void);
typedef void (*EventListener)(ButtonEvent event);

class ButtonHandler 
{

    public:
        // Constructor
        ButtonHandler(ButtonConfig config);

        // Notified queue that the previously emitted event has been processed and that it should 
        // emit the next item in the queue if available
        void eventComplete();

        // Public reference to current config
        ButtonConfig _config;

        // For setting pointer to listener
        void setListener(EventListener listener);

        // ISR definitions. Have to be public to allow passing of pointer to non-member functions
        // to attachInterrupt call
        void onKeyOneEvent();        
        void onKeyTwoEvent();
        void onKeyThreeEvent();
        void onKeyFourEvent();
        void onKeyFiveEvent();
        void onKeySixEvent();

    private:  
        // Buffer of events, maintains a queue-like implementation when items are added or removed
        ButtonEvent _events[EVENT_BUFFER_LENGTH];        
        // For queue implementation
        int _lastIndex = 0; 

        // Used for maintaining information about whether the main sketch has finished processing the last 
        // emitted event
        boolean _processingComplete = true;

        // listener for new events to be emitted to
        EventListener _listener;

        // Does as the name implies
        boolean isEventsEmpty();
        
        // Shifts item indices in the buffer such that the first item is the current action
        void resizeEvents();

        // Adds event to queue
        void addEvent(ButtonEvent event);
        void addEventForButtonNumber(int buttonNumber);

        // Returns pointer to ISR function
        Isr getISR(int buttonIndex);

        // Used for debouncing interrupts
        elapsedMillis _buttonTimeout;

        // For modifier key states, true is pressed, false is open
        boolean _buttonStatePressed[ButtonConfig::MAX_BUTTONS];
};

// Extern as defined globally in c++ implementation file
extern ButtonHandler * _buttonHandler;

// A sad hack to allow access to member functions from a global scope
inline void keyOneAction() { _buttonHandler->onKeyOneEvent(); }
inline void keyTwoAction() { _buttonHandler->onKeyTwoEvent(); }
inline void keyThreeAction() { _buttonHandler->onKeyThreeEvent(); }
inline void keyFourAction() { _buttonHandler->onKeyFourEvent(); }
inline void keyFiveAction() { _buttonHandler->onKeyFiveEvent(); }
inline void keySixAction() { _buttonHandler->onKeySixEvent(); }

#endif