#include <MacroManager.h>

MacroManager *_macroManager;

MacroManager::MacroManager(int cs, int cd) : _cs(cs), _cd(cd)
{
    _macroManager = this;
    _parser->setListener(_listener);

    // Attach ISR to card detect
    pinMode(_cd, INPUT);
    attachInterrupt(digitalPinToInterrupt(_cd), onCardStateChanged, CHANGE);

    updateCardState();

    // Start the SD card if it exists
    if (_cardPresent) 
    {
        beginSD();
    }
}

void MacroManager::buttonPressed(String buttonName) 
{
    String _fileName = MACRO_DIR + buttonName + F(".mac");

    _fileName.toCharArray(_fileNameBuffer, FN_BUF_SIZE);

    updateCardState();

    // Start the SD card if it exists
    if (_cardPresent && !_sdStarted) 
    {   
        _sdStarted = beginSD();

        if (!_sdStarted) {
            // If the user inserts a card while the program is running, restart the device
            WRITE_RESTART(0x5FA0004);
        }
    }

    if (_sdStarted) {
        File _macro = SD.open(_fileNameBuffer, FILE_READ);

        // Only continue if the macro file opened properly
        if (_macro) 
        {
            _parser->reset();

            while (_cardPresent && _macro.available()) 
            {
                
                _parser->parse(_macro.read());

                if (_listener->actionReady()) {
                    dispatchAction(_listener->getAction());
                }
            }
        } else {
            ERROR(F("File opening failed"));
        }

        _macro.close();
    }
}

void MacroManager::updateCardState() 
{
     // Pin will read high when card present
    _cardPresent = digitalRead(_cd);

    if (!_cardPresent) {
        _sdStarted = false;
    } 
}

bool MacroManager::beginSD()
{
    return SD.begin(_cs);
}

void MacroManager::dispatchAction(Action action)
{
    switch (action.type) 
    {
        case RAW_STRING:
            Keyboard.print(action.value);
            break;
        case NEWLINE:
            Keyboard.println("");
            break;
        case MODIFIER_DOWN:
            break;
        case MODIFIER_UP:
            break;
        case DELAY:
            delay(action.value.toInt());
            break;
        default:
            ERROR(F("Action type unsupported"));
    }   
}