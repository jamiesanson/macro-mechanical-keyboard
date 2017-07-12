/**
    This file, along with the accompanying implementation file contain code to handle the dispactching of HID
    keypress events when triggered. It also handles interaction with the SD card.
*/

#ifndef MacroManager_H
#define MacroManager_H

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SD.h>
#include <SPI.h>

#include "JsonStreamingParser.h"
#include "JsonListener.h"
#include "FileListener.h"

#define SUPPRESS_UNUSED(param) (void)param 

#define MACRO_DIR F("/macros/")

#define FN_BUF_SIZE 20

// Definitions for software restart
#define RESTART_ADDR       0xE000ED0C
#define READ_RESTART()     (*(volatile uint32_t *)RESTART_ADDR)
#define WRITE_RESTART(val) ((*(volatile uint32_t *)RESTART_ADDR) = (val))

// Definition for error handling
#define ERROR(err) Serial.println(err)

// Enum containing individual actions
PROGMEM enum ActionType
{
    RAW_STRING,
    NEWLINE,
    MODIFIER_DOWN,
    MODIFIER_UP,
    DELAY
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

      bool _cardPresent;
      bool _sdStarted = false;

      char _fileNameBuffer[FN_BUF_SIZE];

      FileListener *_listener = new FileListener();
      JsonStreamingParser *_parser = new JsonStreamingParser();

      bool beginSD();

      void dispatchAction(Action action);
};

// Extern as defined globally in c++ implementation file
extern MacroManager *_macroManager;

// ISR called when card is ejected to put in
inline void onCardStateChanged() 
{
    delayMicroseconds(1);
    _macroManager->updateCardState();
}

#endif
