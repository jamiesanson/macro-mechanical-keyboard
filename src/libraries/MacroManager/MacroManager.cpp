#include <MacroManager.h>
#include <algorithm>

MacroManager::MacroManager()
{}

void MacroManager::setupButton(int index, String actions) {
    _actionVectors[index] = loadVector(actions);
}

void MacroManager::dispatchForIndex(int index) {
    runVector(_actionVectors[index]);
}

ActionVector MacroManager::loadVector(String actions)
{

    Serial.println("Loading for string: " + actions);

    ActionVector vector;
    int actionCount = getActionCount(actions);
    // Return early if the string is invalid
    if (actionCount == INVALID_ACTION) {
        Serial.println("Invalid");
        return vector;
    }

    KeyAction keyActions[50];
    int actionInd = 0;

    ActionType currAction;
    String commandStr = "";
    boolean entered = false;

    for (int i = 0; i < actions.length(); i++) {
        if ((actions[i] & COMMAND_FLAG) == COMMAND_FLAG) {
            currAction = getTypeForChar(actions[i]);
            entered = !entered;

            if (!entered) {
                keyActions[actionInd] = getAction(commandStr, currAction);
                actionInd++;
            }

            commandStr = "";
        } else {
            commandStr += String((char) actions[i]);
        }
    }

    std::copy(std::begin(keyActions), std::end(keyActions), std::begin(vector.actions));
    vector.length = actionInd;
    Serial.println("Length: " + String(actionInd));
    return vector;
}

void MacroManager::runVector(ActionVector vector)
{
    for (int i = 0; i < vector.length; i++) {
        Serial.println("Type: " + String(vector.actions[i].type));
        switch (vector.actions[i].type) {
            case DELAY:
            {
                delay(static_cast<DelayAction*>(&vector.actions[i])->getDelay());
                Serial.println("Delaying for: " + String(dynamic_cast<DelayAction*>(&vector.actions[i])->getDelay()));
                continue;
            }
            case MODIFIER_DOWN:
            {
                Serial.println("Mod down: " + String(dynamic_cast<ModifierAction*>(&vector.actions[i])->getPayload()));
                break;
            }
            case MODIFIER_UP:
            {
                Serial.println("Mod up: " + String(static_cast<ModifierAction*>(&vector.actions[i])->getPayload()));
                break;
            }
            case SINGLE_PRESS:
            {
                Serial.println("Single press: " + String(static_cast<SinglePressAction*>(&vector.actions[i])->getPayload()));
                break;
            }
            case RAW_STRING:
            {
                Serial.println("Raw string: " + String(static_cast<RawStringAction*>(&vector.actions[i])->getPayload()));
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

int MacroManager::getActionCount(String actions) {
    // Iterate over the string once to get the number of actions
    int cmdCount = 0;
    for (int i = 0; i < actions.length(); i++) {
        if ((actions[i] & COMMAND_FLAG) == COMMAND_FLAG) {
            cmdCount++;
        }
    }

    // If there is an uneven number of commands, the string is invalid
    return cmdCount % 2 == 0 ? cmdCount/2 : INVALID_ACTION;
}

ActionType MacroManager::getTypeForChar(char command) {
    // removes flag
    command = (char) (command & ~COMMAND_FLAG);
    switch(command) {
        case 't':
            return DELAY;
        case 'u':
            return MODIFIER_UP;
        case 'd':
            return MODIFIER_DOWN;
        case 'c':
            return SINGLE_PRESS;
        case 's':
            return RAW_STRING;
    }
}

KeyAction MacroManager::getAction(String commandStr, ActionType type) {
    char buff[20];

    if (type != RAW_STRING) {
        commandStr.toCharArray(buff, 20);
    }

    switch (type) {
        case DELAY:
        {
            int delayMillis = commandStr.toInt();
            return DelayAction(delayMillis);
        }
        case MODIFIER_UP:
        {
            int action = buff[0];
            return ModifierAction(action, true);
        }
        case MODIFIER_DOWN:
        {
            int action = buff[0];
            return ModifierAction(action, false);
        }
        case SINGLE_PRESS:
        {
            char action = buff[0];
            return SinglePressAction(action);
        }
        case RAW_STRING:
        {
            return RawStringAction(commandStr);
        }
    }

    return KeyAction();
}