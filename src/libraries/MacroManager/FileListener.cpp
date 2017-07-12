#include "FileListener.h"
#include "JsonListener.h"

void FileListener::whitespace(char c) {
}

void FileListener::startDocument() {
}

void FileListener::key(String key) 
{  
  _lastKey = key;
}

void FileListener::value(String value) 
{
  if (TYPE_KEY.equals(_lastKey)) 
  {
    _currActionType = value.toInt();
  } else if (PAYLOAD_KEY.equals(_lastKey)) 
  {
    _currActionPayload = value;
  }
}

void FileListener::endArray() {
}

void FileListener::endObject() {
  _actionReady = true;
}

void FileListener::endDocument() {
}

void FileListener::startArray() {
}

void FileListener::startObject() {
  _lastKey = "";
  _currActionPayload = "";
  _currActionType = -1;
}

bool FileListener::actionReady() 
{
    return _actionReady;
}

Action FileListener::getAction() {
    _actionReady = false;
    return (Action) {_currActionType, _currActionPayload};
}
