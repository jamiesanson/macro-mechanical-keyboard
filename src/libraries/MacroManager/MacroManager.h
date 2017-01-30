/**
    This file, along with the accompanying implementation file contain code to handle the dispactching of HID
    keypress events when triggered. It stores a series of action vectors, which contain Key actions, which are
    dispatched in orger when indexed.
*/

#ifndef MacroManager_H
#define MacroManager_H

#include <Arduino.h>
#include <avr/pgmspace.h>

#define SUPPRESS_UNUSED(param) (void)param 

#define COMMAND_FLAG 0b10000000
#define COMMAND(t) (char) (t | COMMAND_FLAG) 
#define INVALID_ACTION -1
#define MAX_ACTIONVECTORS 6

// Enum containing individual actions
PROGMEM enum ActionType
{
    DELAY,
    MODIFIER_DOWN,
    MODIFIER_UP,
    SINGLE_PRESS,
    RAW_STRING
};

// Region action type definitions
class KeyAction {
    public:
        ActionType type;
        virtual void dummy();
};

class DelayAction : public KeyAction {
    int delayMillis;
    public:
        DelayAction(int delay) : delayMillis(delay) {
            type = DELAY;
        }

        int getDelay() { return delayMillis; }
};

class ModifierAction : public KeyAction {
    int payload;
    public:
        ModifierAction(int p, boolean up) : payload(p) {
            type = up ? MODIFIER_UP : MODIFIER_DOWN;
        }

        int getPayload() { return payload; }
};

class SinglePressAction : public KeyAction {
    char payload;
    public:
        SinglePressAction(char p) : payload(p) {
            type = SINGLE_PRESS;
        }

        char getPayload() { return payload; }
};

class RawStringAction : public KeyAction {
    String payload;
    public:
        RawStringAction(String p) : payload(p) {
            type = RAW_STRING;
        }

        String getPayload() { return payload; }
};
// End region

// Struct acting as type definition for a vector of actions, which represents an entire command
struct ActionVector
{
    int length;
    KeyAction actions[50];
};


class MacroManager
{
    public:
        MacroManager();

        void setupButton(int index, String actions);

        void dispatchForIndex(int index);

    private:
        ActionVector _actionVectors[MAX_ACTIONVECTORS];

        // Function for building an ActionVector from a given String
        ActionVector loadVector(String actionVector);
        
        // Runs the supplied ActionVector
        void runVector(ActionVector vector);

        // Iterates over the string to be loaded to get the number of actions
        // returns -1 if the actionVector is invalid 
        int getActionCount(String actionVector);

        // Reads command flag and returns correct ActionType
        ActionType getTypeForChar(char command);

        // Builds KeyAction for given string and type
        KeyAction getAction(String commandStr, ActionType type);
};

#endif
