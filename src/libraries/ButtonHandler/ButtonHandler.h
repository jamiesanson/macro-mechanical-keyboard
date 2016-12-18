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

// Struct holding config information, i.e button pins and modes
struct ButtonConfig
{
    // Defines maximum amount of buttons able to be used, which is required
    // due to the use of fixed ISRs for each button event
    static const PROGMEM int MAX_BUTTONS = 6;

    int buttonPins[MAX_BUTTONS];
    ButtonMode buttonModes[MAX_BUTTONS];
};

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
        void onKeyOneDown();
        void onKeyOneUp();
        
        void onKeyTwoDown();
        void onKeyTwoUp();

        void onKeyThreeDown();
        void onKeyThreeUp();

        void onKeyFourDown();
        void onKeyFourUp();

        void onKeyFiveDown();
        void onKeyFiveUp();

        void onKeySixDown();
        void onKeySixUp();

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

        // Returns pointer to ISR function
        Isr getISR(int buttonIndex, boolean isRising);

        // Used for debouncing interrupts
        elapsedMillis _buttonTimeout;
};

// Extern as defined globally in c++ implementation file
extern ButtonHandler * _buttonHandler;

// A sad hack to allow access to member functions from a global scope
inline void keyOneDown() { _buttonHandler->onKeyOneDown(); }
inline void keyOneUp() { _buttonHandler->onKeyOneUp(); }
inline void keyTwoDown() { _buttonHandler->onKeyTwoDown(); }
inline void keyTwoUp() { _buttonHandler->onKeyTwoUp(); }
inline void keyThreeDown() { _buttonHandler->onKeyThreeDown(); }
inline void keyThreeUp() { _buttonHandler->onKeyThreeUp(); }
inline void keyFourDown() { _buttonHandler->onKeyFourDown(); }
inline void keyFourUp() { _buttonHandler->onKeyFourUp(); }
inline void keyFiveDown() { _buttonHandler->onKeyFiveDown(); }
inline void keyFiveUp() { _buttonHandler->onKeyFiveUp(); }
inline void keySixDown() { _buttonHandler->onKeySixDown(); }
inline void keySixUp() { _buttonHandler->onKeySixUp(); }

#endif