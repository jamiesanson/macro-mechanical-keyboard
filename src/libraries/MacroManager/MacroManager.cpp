#include <MacroManager.h>

MacroManager *_macroManager;

MacroManager::MacroManager(int cs, int cd) : _cs(cs), _cd(cd)
{
    // Attach ISR to card detect
    attachInterrupt(digitalPinToInterrupt(_cd), onCardStateChanged, CHANGE);
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
    String _fileName = MACRO_DIR + buttonName;

    _fileName.toCharArray(_fileNameBuffer, FN_BUF_SIZE);

    File _macro = SD.open(_fileNameBuffer, FILE_READ);

    // Only continue if the macro file opened properly
    if (_macro) 
    {
        
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