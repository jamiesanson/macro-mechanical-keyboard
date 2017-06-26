/**
    This file, along with the accompanying implementation file contain code to handle the dispactching of HID
    keypress events when triggered. It also handles interaction with the SD card.
*/

#ifndef MacroManager_H
#define MacroManager_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SD.h>

#include "JsonStreamingParser.h"
#include "JsonListener.h"
#include "FileListener.h"

#define SUPPRESS_UNUSED(param) (void)param 

#define MACRO_DIR "/macros/"

#define FN_BUF_SIZE 20

// Enum containing individual actions
PROGMEM enum ActionType
{
    DELAY,
    MODIFIER_DOWN,
    MODIFIER_UP,
    SINGLE_PRESS,
    RAW_STRING
};

class MacroManager
{
    public:
        MacroManager(int cs, int cd);

        void buttonPressed(String buttonName);
        
        // Called by globally scoped ISR, not meant to be called external to library
        void updateCardState();

    private:
      
      // Chip select and Chip detect pins
      int _cs, _cd;

      bool _cardNotPresent;

      char _fileNameBuffer[FN_BUF_SIZE];

      FileListener *_listener = new FileListener();
      JsonStreamingParser *_parser = new JsonStreamingParser();

      void beginSD();

      void dispatchAction(Action action);
};

// Extern as defined globally in c++ implementation file
extern MacroManager *_macroManager;

// ISR called when card is ejected to put in
inline void onCardStateChanged() 
{
    _macroManager->updateCardState();
}

#endif
