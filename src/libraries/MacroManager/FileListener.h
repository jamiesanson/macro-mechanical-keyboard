#pragma once

#include "JsonListener.h"

#define TYPE_KEY String(F("type"))
#define PAYLOAD_KEY String(F("payload"))

// Struct defining an action to dispatch
struct Action {
  int type;
  String value;
};

class FileListener: public JsonListener {

  public:

    virtual void whitespace(char c);
  
    virtual void startDocument();

    virtual void key(String key);

    virtual void value(String value);

    virtual void endArray();

    virtual void endObject();

    virtual void endDocument();

    virtual void startArray();

    virtual void startObject();

    bool actionReady();

    Action getAction();

  private:

    String _lastKey = "";

    int _currActionType = -1;

    String _currActionPayload = "";
    
    bool _actionReady = false;

};