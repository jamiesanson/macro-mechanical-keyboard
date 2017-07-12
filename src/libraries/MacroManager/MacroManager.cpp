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
    String _fileName = MACRO_DIR + buttonName + ".mac";

    _fileName.toCharArray(_fileNameBuffer, FN_BUF_SIZE);

    updateCardState();

    // Start the SD card if it exists
    if (_cardPresent && !_sdStarted) 
    {
        _sdStarted = beginSD();
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
            Serial.println("Opening: " + _fileName + " failed :(");
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
        case MODIFIER_DOWN:
            break;
        case MODIFIER_UP:
            break;
        case DELAY:
            break;
        default:
             Serial.println("ActionType: " + String(action.type) + "; ActionVal: " + String(action.value));
    }   
}