#include <MacroManager.h>

MacroManager *_macroManager;

MacroManager::MacroManager(int cs, int cd) : _cs(cs), _cd(cd)
{
    _macroManager = this;
    _parser->setListener(_listener);
    // Attach ISR to card detect
    attachInterrupt(digitalPinToInterrupt(_cd), onCardStateChanged, CHANGE);
    pinMode(_cd, INPUT);

    updateCardState();

    // Start the SD card if it exists
    if (!_cardNotPresent) 
    {
        beginSD();
    }
}

// Public functions
void MacroManager::buttonPressed(String buttonName) 
{
    String _fileName = MACRO_DIR + buttonName + ".mac";

    Serial.println("Opening: " + _fileName);

    _fileName.toCharArray(_fileNameBuffer, FN_BUF_SIZE);

    beginSD();
    
    File _macro = SD.open(_fileNameBuffer, FILE_READ);

    // Only continue if the macro file opened properly
    if (_macro) 
    {
        Serial.println("file exists");
        while (!_cardNotPresent && _macro.available()) 
        {
            _parser->parse(_macro.read());

            if (_listener->actionReady()) {
                dispatchAction(_listener->getAction());
            }
        }
    } else {
        Serial.println("Opening: " + _fileName + " failed :(");
    }
}

void MacroManager::updateCardState() 
{
     // Pin will read high when card present
    _cardNotPresent = !digitalRead(_cd);
}

// Private functions
void MacroManager::beginSD()
{
    SD.begin(_cs);
}

void MacroManager::dispatchAction(Action action)
{
    Serial.println("ActionType: " + String(action.type) + "; ActionVal: " + String(action.value));
}